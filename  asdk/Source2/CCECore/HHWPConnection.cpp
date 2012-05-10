#include "StdAfx.h"

#ifdef _DEBUG
#define  new DEBUG_NEW
#endif

//#define MAX_PACKET_LENGTH  8*1024	//最小默认包长度。


#include "HHWPIOCP.h"
#include "ChannelManager.h"
#include ".\hhwpconnection.h"
#include "CCEProcessor.h"
#include "ResourceLock.h"


#define  SIO_KEEPALIVE_VALS  (IOC_IN | IOC_VENDOR | 4)


extern __int64   g_iTotalClient;
extern __int64   g_iTotalServer;





struct tcp_keepalive {
	u_long  onoff;
	u_long  keepalivetime;
	u_long  keepaliveinterval;
};

//缓冲
CSendBuffer::CSendBuffer()
{

	InitializeCriticalSection(&m_cs);
}
bool CSendBuffer::AddSendData(void* pData,int nLength)
{
	CResourceLock ls(&m_cs);
	if(size()>10)
	{
		return false;	//最大缓存10个记录.
	}else
	{
		WSABUFPLUS* pPlus = new WSABUFPLUS(pData,nLength);
		push_back(pPlus);
		return true;
	}
}
CSendBuffer::~CSendBuffer()
{
	DeleteCriticalSection(&m_cs);

	for(list<void*>::iterator it = begin(); it != end();++it)
	{
		WSABUFPLUS* pBuff = (WSABUFPLUS*)(*it);
		delete pBuff;
	}
	//清队内存
}

WSABUFPLUS*   CSendBuffer::GetSendData()
{
	CResourceLock ls(&m_cs);
	WSABUFPLUS* pBuffer=NULL;
	if(size())
	{
		pBuffer = (WSABUFPLUS*)(*begin());
		pop_front();
		return pBuffer;
		
	}else	//任务数小于25时才分配.
	{
		return NULL;
	}
}

void CHHWPConnection::Init()
{
	

	if(!CHHWPIOCP::g_pHHWPIOCP)
		CHHWPIOCP::Init();

	InitializeCriticalSection(&m_csSend);
	//m_bCanNotGetRecvBuff = false;

	{

		BOOL bLive = TRUE,bNoDelay=TRUE;
		setsockopt(m_hSockets,SOL_SOCKET,SO_KEEPALIVE,(char*)&bLive,sizeof(bLive));
		setsockopt(m_hSockets,IPPROTO_TCP,TCP_NODELAY,(char*)&bNoDelay,sizeof(bNoDelay));

		tcp_keepalive inVal;
		inVal.onoff =1;
		inVal.keepalivetime = 5000;
		inVal.keepaliveinterval = 300;	

		DWORD nReturned;
		WSAIoctl(m_hSockets,SIO_KEEPALIVE_VALS,&inVal,sizeof(inVal),NULL,0,&nReturned,NULL,NULL);

	}

	m_bDeleteProcessor = false;

	CreateIoCompletionPort((HANDLE)m_hSockets,CHHWPIOCP::g_pHHWPIOCP->m_hCompletionPort,(ULONG_PTR)this,0);


	m_nRefCount = 0;
	

	m_bError =false;
	memset(&m_connInfo,0,sizeof(m_connInfo));

	SOCKADDR_IN addr;
	int ncount = sizeof(addr);
	getpeername(m_hSockets,(SOCKADDR*)&addr,&ncount);

	m_connInfo.addrFromOuter = addr.sin_addr;	//外网地址。

	m_connInfo.pConnection = this;
	time(&m_connInfo.connTime);
	
	m_pProcessor->OnConnectionInitFinish();

}


CHHWPConnection::CHHWPConnection(SOCKET sockPeer,CChannel* pChannel)

{	
	memset(&m_connInfo,0,sizeof(m_connInfo));

	m_pChannel = pChannel;
	
	m_pProcessor = (CCCEProcessor*)pChannel->m_core.pSvrRunTimeClass->CreateObject();
	m_pProcessor->m_lParam = pChannel->m_core.lParam;

	//m_pProcessor = (CCCEProcessor*)(*(pChannel->m_core.pSvrRunTimeClass->m_pfnCreateObject))();

	m_pProcessor->SetConnectionPointer(this);
	SetRecvBufferSize(m_pProcessor->m_nRecvBufferSize);

	m_hSockets =sockPeer;

	Init();

	CChannelManager::AddConnection(this);

	WSARecvData();						//接收数据.

	//发送自己的IP地址信息.
	//WSASendMyIPAddr();					//发送自己的IP地址.
	
}

CHHWPConnection::CHHWPConnection(SOCKET sockPeer,CCCEProcessor* pProcessor)

{
	memset(&m_connInfo,0,sizeof(m_connInfo));

	m_pChannel = NULL;
	m_pProcessor = pProcessor ;
	m_pProcessor->SetConnectionPointer(this);
	SetRecvBufferSize(m_pProcessor->m_nRecvBufferSize);

	m_hSockets =sockPeer;

	//ASSERT(AfxCheckMemory());

	Init();

	//ASSERT(AfxCheckMemory());

	WSARecvData();						//接收数据.
}



CHHWPConnection::~CHHWPConnection(void)
{
	LeaveCriticalSection(&m_csSend);
	DeleteCriticalSection(&m_csSend);
	
	if(m_bDeleteProcessor && m_pProcessor)
		delete m_pProcessor;

	if(m_pChannel)
	{
		// 如果通道存在，则要求通道删除自己
		//m_pChannel->DeleteConnection(this);
		//CM_Param param;
		//param.nOperator = 2;	//DELETE.
		//param.pConnection = this;
		//CWinThread_ConnManager::OpConnection(&param);
		CChannelManager::DeleteConnection(this);
	}

}

void CHHWPConnection::OnError(OVERLAPPLUS* lpOverlapped)
{
	InterlockedDecrement(&m_nRefCount);
	int nType = lpOverlapped->ntype;
	ReleaseOverlapPlus(lpOverlapped);

	int nErrorWhere=-1;
	switch(nType)
	{
	case eIORead:
		{
			nErrorWhere = WSARecvData_FUN;
		}break;
	case eIOWrite:
		{
			nErrorWhere = WSASendData_FUN;
		}break;
	default:
		{
			ASSERT(false);
			::MessageBoxA(NULL,"未知错误","",MB_OK);
		}
		
	}

	//表示从IOCP Queue中接收到的错误。
	SetErrorFlag(nErrorWhere,true);
}

bool  CHHWPConnection::IsError()
{
	return m_bError;
}


OVERLAPPLUS* CHHWPConnection::GetOverlapPlus(int nType,WSABUFPLUS *pBuff)
{
	return   new OVERLAPPLUS(nType,pBuff);	
}

void CHHWPConnection::SendRegisterUserCommand(int nCommand,LPVOID lParam)
{
	if(!CHHWPIOCP::g_pHHWPIOCP)
	{
		CHHWPIOCP::Init();
	}

	OVERLAPPLUS* pPlus = GetOverlapPlus(nCommand,NULL);
	pPlus->nUserDefineType = lParam;
	LPOVERLAPPED lpOverlapped = (LPOVERLAPPED)pPlus;
	PostQueuedCompletionStatus(CHHWPIOCP::g_pHHWPIOCP->m_hCompletionPort,1,(ULONG_PTR)NULL,lpOverlapped);
}


void CHHWPConnection::ReleaseOverlapPlus(OVERLAPPLUS* pOverlapplus)
{
	if( pOverlapplus)
	{
		//ASSERT(HasOverlappedIoCompleted(&pOverlapplus->_olp));
		delete pOverlapplus;
	}
}

int CHHWPConnection::WSASendData(const void* pData,int nLength,int nFlags)
{	
	CResourceLock ls(&m_csSend);	//因为发送完，才能发送另一个.
	if( (!pData) && nLength==-1 )
	{	
		//系统通知退出.			
		InterlockedDecrement(&m_nRefCount);
		SetErrorFlag(WSASendData_FUN);
		return -1;		
	}else
	{
		WSABUFPLUS* pPlus = new WSABUFPLUS(pData,nLength);
		//否则发送数据
		LPWSAOVERLAPPED poverlapped= (LPWSAOVERLAPPED)GetOverlapPlus(eIOWrite,pPlus);

		//增加的内容
		OVERLAPPLUS* pOverPlus = (OVERLAPPLUS*)poverlapped;
		pOverPlus->nUserDefineType = (LPVOID)nFlags;			//放到nUserDefineType里面.

		DWORD sendbyte;
		int nRet = ::WSASend(m_hSockets,(WSABUF*)pPlus,1,&sendbyte,0,poverlapped,NULL);
		int dwError = WSAGetLastError();
		if(nRet == 0 || dwError == WSA_IO_PENDING || dwError == ERROR_IO_PENDING)
		{	
			//InterlockedDecrement(&m_nRefCount);					
			return 1;			
		}else
		{	
			//TRACE0("发送数据出错--0\r\n");
			InterlockedDecrement(&m_nRefCount);	
			ReleaseOverlapPlus((OVERLAPPLUS*)poverlapped);
			SetErrorFlag(WSASendData_FUN);		
			return -1;
		}
	}
	return 1;
}

//void CHHWPConnection::PostIoExitComplateStatues(
//						  LPOVERLAPPED lpOverlapped
//						  )
//{
//	//CResourceLock lockcs(&m_cs);
//	//--m_nRefCount;
//	InterlockedIncrement(&m_nRefCount);	//统一用接收.
//	PostQueuedCompletionStatus(CHHWPIOCP::g_pHHWPIOCP->m_hCompletionPort,1,(ULONG_PTR)this,lpOverlapped);			
//}


int CHHWPConnection::WSARecvData(OVERLAPPLUS* lpOw)
{    

	if(m_bError)
	{
		SetErrorFlag(WSARecvData_FUN);
		return 0;
	}

	WSABUFPLUS* pPlus;
	if( (!lpOw) || (m_nRecvBufferSize != lpOw->pBuff->wsabuf.len))
	{
		if(lpOw)
		{
			ReleaseOverlapPlus(lpOw);
			//delete lpOw;
		}

		pPlus = new WSABUFPLUS(m_nRecvBufferSize);	//用最大的包大小.
		lpOw = GetOverlapPlus(eIORead,pPlus);		//重新分配.
	}else
	{
		pPlus = lpOw->pBuff;
	}
	
	DWORD dwRecv=0;
	DWORD lpFlag=0;
	int nRet = ::WSARecv(m_hSockets,(WSABUF*)pPlus,1,&dwRecv,&lpFlag,(LPWSAOVERLAPPED)lpOw,NULL);
	int dwError = WSAGetLastError();
	if(nRet == 0 || dwError == WSA_IO_PENDING  || dwError == ERROR_IO_PENDING)
	{
		InterlockedIncrement(&m_nRefCount);
		return 1;		
	}else
	{
		ReleaseOverlapPlus(lpOw);		
		SetErrorFlag(WSARecvData_FUN);
		return -1;
	}
}


UINT CHHWPConnection::OnReceiveData(DWORD numBerOfBytes,OVERLAPPLUS* lpOverlapped)
{
	//修改为在退出时才改变引用计数，更能增加系统稳定性。
	//--m_nRefCount;	
	//lpOverlapped->pBuff->wsabuf.len = numBerOfBytes;	//实际数
	//ReleaseOverlapPlus(lpOverlapped);					//释放
	//发送数据，接收数据	
	//接收到数据.再接收数据.

	//ASSERT(AfxCheckMemory());
	
	bool bError = false;
	if(numBerOfBytes>0)
	{
		m_connInfo.recvBytes += numBerOfBytes;
		m_pChannel && (m_pChannel->m_client2Server += numBerOfBytes);

		//如果是Debug时，直接让程序出错。
//#ifndef _DEBUG
		try{
//#endif
		//接收到数据的处理
		//ASSERT(AfxCheckMemory());
		m_pProcessor->OnRecvRawData(lpOverlapped->pBuff->wsabuf.buf,numBerOfBytes);
		//ASSERT(AfxCheckMemory());
//#ifndef _DEBUG
		}catch(...)
		{	
			CString str;
			sockaddr_in addr;
			GetPeerAddr(addr);
			
			str.Format("处理来自%d.%d.%d.%d的数据异常！将断开其连接",
				addr.sin_addr.S_un.S_un_b.s_b1,
				addr.sin_addr.S_un.S_un_b.s_b2,
				addr.sin_addr.S_un.S_un_b.s_b3,
				addr.sin_addr.S_un.S_un_b.s_b4);
			AppendLog(str);
			bError = true;
		}
//#endif

	}else
	{
		bError = true;
	}

	if(!bError)
	{
		memset(&lpOverlapped->_olp,0,sizeof(lpOverlapped->_olp));
		lpOverlapped->ntype = eIORead;

		InterlockedDecrement(&m_nRefCount);
		WSARecvData(lpOverlapped);	// 继续使用该内存接收.
		return 1;	
	}else
	{
		//处理到异常，需要断开连接.
		ReleaseOverlapPlus(lpOverlapped);				
		NotifyExit();
		InterlockedDecrement(&m_nRefCount);		
		SetErrorFlag(WSARecvData_FUN);
		return -1;
	}
}


UINT CHHWPConnection::OnSendDataFin(DWORD numBerOfBytes,OVERLAPPLUS* lpOverlapped)	//发送数据完成
{
	bool bClose = false;
	if( lpOverlapped->nUserDefineType == (LPVOID)SD_FLAG_SEND_THEN_CLOSE )
	{
		//发送完成后需要关闭.
		bClose = true;
	}

	m_pProcessor->OnSendDataFinish(lpOverlapped->pBuff->wsabuf.buf,numBerOfBytes);


	ReleaseOverlapPlus(lpOverlapped);		//删除内存.			
	m_connInfo.sendBytes += numBerOfBytes;		//总发送数据.
	m_pChannel && (m_pChannel->m_server2Client += numBerOfBytes);
	


	if(bClose)
		NotifyExit();
	InterlockedDecrement(&m_nRefCount);
	return 1;	
}



//UINT CHHWPConnection::OnIOCPExit(OVERLAPPLUS* lpOverLapped)
//{
//	OnError(lpOverLapped);
//	return 0;
//}

//void CHHWPConnection::OnSendBufferData(OVERLAPPLUS* lpOverLapped)
//{
//	ReleaseOverlapPlus(lpOverLapped);
//    WSASendData();
//}

//UINT CHHWPConnection::SendUserDefine(int nCommand)
//{
//	CResourceLock lockcs(&m_cs);
//
//	InterlockedIncrement(&m_nRefCount);	//统一用接收.
//	OVERLAPPLUS* pPlus = GetOverlapPlus(eUserDefine,NULL);
//	pPlus->nUserDefineType = (LPVOID)nCommand;
//	LPOVERLAPPED lpOverlapped = (LPOVERLAPPED)pPlus;
//	PostQueuedCompletionStatus(CHHWPIOCP::g_pHHWPIOCP->m_hCompletionPort,1,(ULONG_PTR)this,lpOverlapped);	
//	return true;
//}

//UINT CHHWPConnection::OnUserDefine(OVERLAPPLUS* pOverlapPlus)
//{
//	CResourceLock lockcs(&m_cs);
//
//	if(m_pProcessor)
//		m_pProcessor->OnUserDefine((int)pOverlapPlus->nUserDefineType);	//取其高四位.
//	ReleaseOverlapPlus(pOverlapPlus);
//	InterlockedDecrement(&m_nRefCount);	//统一用接收.
//	return 0;
//}

void CHHWPConnection::NotifyExit()
{
	if(m_hSockets!=INVALID_SOCKET)
	{
		closesocket(m_hSockets);	//关闭
		m_hSockets = INVALID_SOCKET;
	}
	//InterlockedIncrement(&m_nRefCount);
	//WSASendData(NULL,-1);	//尝试发送数据.	//必然会返回错误.	
}


void CHHWPConnection::GetConnInfo(CONNECT_INFO_SHOW* pInfo)
{
	/*strncpy(pInfo->addrFrom,m_szsockAddrClient,sizeof(pInfo->addrFrom)-1);
	strcpy(pInfo->connTime,m_szConnTime);
	pInfo->client2server = m_client2server;
	pInfo->server2client = m_server2client;*/ 
	*pInfo  = m_connInfo;	
	pInfo->pConnection = this;
}

bool CHHWPConnection::SendData(const void* pData,int nLength,int nFlags)
 {
	 if(pData && nLength>0)
	 {
		 InterlockedIncrement(&m_nRefCount);
		 return WSASendData(pData,nLength,nFlags)!=-1;
		 
	 }
	 else
		 return false;
}


 void CHHWPConnection::PostDeleteThisMessage()
 {
	 //肯定已经初始化.

	 OVERLAPPLUS* pPlus = GetOverlapPlus(eIODeleteThis,NULL);	
	 LPOVERLAPPED lpOverlapped = (LPOVERLAPPED)pPlus;
	 PostQueuedCompletionStatus(CHHWPIOCP::g_pHHWPIOCP->m_hCompletionPort,1,(ULONG_PTR)this,lpOverlapped);
 }

 long CHHWPConnection::GetRefCount()
 {
	 return m_nRefCount;
 }


void CHHWPConnection::SetErrorFlag(int nWhere,bool bFromIOCP)
{
	

	if(bFromIOCP ||  (nWhere!=WSASendData_FUN))
		EnterCriticalSection(&m_csSend);

	
	//如果没有出错，则生成出错标记。
	//在RecvData中删除的好处是，之后不会再有
	if( (nWhere == WSARecvData_FUN) &&
		!m_bsErrorFlag.test(WSARecvData_FUN) )	//这里保证了，只会调用一次。
	{
		if(m_pProcessor)
		{	
			if(m_pProcessor->OnClose())	//尽早通知.
			{
				m_pProcessor->m_pConnection = NULL;	//防止其未掉用基类.
				m_bDeleteProcessor  = true;				
			}else
			{
				m_pProcessor = NULL;	// 断绝关系 
			}
		}
	}

	if(!m_bError)
	{
		closesocket(m_hSockets);
		m_hSockets = INVALID_SOCKET;
		m_bError = true;		
	}

	m_bsErrorFlag.set(nWhere,true);

	

	//如果所有的位置都出错，则表示，不全再增加新的错误，
	//如果引用计数为0，表示是最后一个错误返回.
	if(m_nRefCount == 0)
	{
		if(m_bsErrorFlag.count() == m_bsErrorFlag.size())	//确保不会再被调用，方或删除。
		{
			PostDeleteThisMessage();
			//::delete this;
			return;
		}else
		{
			//如果引用计数为零，而标志为被置，应该是 Read 没有出错。故引发其出错.
			LeaveCriticalSection(&m_csSend);			
			if(nWhere!=WSASendData_FUN)
			{
				InterlockedIncrement(&m_nRefCount);
				WSASendData(NULL,-1);
				return;
			}
		}
	}

	if(bFromIOCP ||  (nWhere!=WSASendData_FUN) )
		LeaveCriticalSection(&m_csSend);
}

void CHHWPConnection::SetInnerIpAddr(in_addr& addr)
{
	m_connInfo.addrFromInner = addr;
}


void CHHWPConnection::SetRecvBufferSize(int nSize)
{
	m_nRecvBufferSize = max(nSize,CCE_DEFAULT_RECV_LEN);
}

void CHHWPConnection::GetPeerAddr(sockaddr_in& addr)
{
	memset(&addr,0,sizeof(addr));
	if(m_hSockets!=INVALID_SOCKET)
	{
		int nLen = sizeof(addr);
		getpeername(m_hSockets,(sockaddr*)&addr,&nLen);
	}
}

void CHHWPConnection::GetThisAddr(sockaddr_in& addr)
{
	memset(&addr,0,sizeof(addr));
	if(m_hSockets!=INVALID_SOCKET)
	{
		int nLen = sizeof(addr);
		getsockname(m_hSockets,(sockaddr*)&addr,&nLen);
	}
}

//
//
//void CHHWPConnection::EnterLock()
//{
//	EnterCriticalSection(&m_cs);
//}
//void CHHWPConnection::LeaveLock()
//{
//	LeaveCriticalSection(&m_cs);
//}