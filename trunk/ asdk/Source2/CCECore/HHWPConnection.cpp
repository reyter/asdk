#include "StdAfx.h"

#ifdef _DEBUG
#define  new DEBUG_NEW
#endif

//#define MAX_PACKET_LENGTH  8*1024	//��СĬ�ϰ����ȡ�


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

//����
CSendBuffer::CSendBuffer()
{

	InitializeCriticalSection(&m_cs);
}
bool CSendBuffer::AddSendData(void* pData,int nLength)
{
	CResourceLock ls(&m_cs);
	if(size()>10)
	{
		return false;	//��󻺴�10����¼.
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
	//����ڴ�
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
		
	}else	//������С��25ʱ�ŷ���.
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

	m_connInfo.addrFromOuter = addr.sin_addr;	//������ַ��

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

	WSARecvData();						//��������.

	//�����Լ���IP��ַ��Ϣ.
	//WSASendMyIPAddr();					//�����Լ���IP��ַ.
	
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

	WSARecvData();						//��������.
}



CHHWPConnection::~CHHWPConnection(void)
{
	LeaveCriticalSection(&m_csSend);
	DeleteCriticalSection(&m_csSend);
	
	if(m_bDeleteProcessor && m_pProcessor)
		delete m_pProcessor;

	if(m_pChannel)
	{
		// ���ͨ�����ڣ���Ҫ��ͨ��ɾ���Լ�
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
			::MessageBoxA(NULL,"δ֪����","",MB_OK);
		}
		
	}

	//��ʾ��IOCP Queue�н��յ��Ĵ���
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
	CResourceLock ls(&m_csSend);	//��Ϊ�����꣬���ܷ�����һ��.
	if( (!pData) && nLength==-1 )
	{	
		//ϵͳ֪ͨ�˳�.			
		InterlockedDecrement(&m_nRefCount);
		SetErrorFlag(WSASendData_FUN);
		return -1;		
	}else
	{
		WSABUFPLUS* pPlus = new WSABUFPLUS(pData,nLength);
		//����������
		LPWSAOVERLAPPED poverlapped= (LPWSAOVERLAPPED)GetOverlapPlus(eIOWrite,pPlus);

		//���ӵ�����
		OVERLAPPLUS* pOverPlus = (OVERLAPPLUS*)poverlapped;
		pOverPlus->nUserDefineType = (LPVOID)nFlags;			//�ŵ�nUserDefineType����.

		DWORD sendbyte;
		int nRet = ::WSASend(m_hSockets,(WSABUF*)pPlus,1,&sendbyte,0,poverlapped,NULL);
		int dwError = WSAGetLastError();
		if(nRet == 0 || dwError == WSA_IO_PENDING || dwError == ERROR_IO_PENDING)
		{	
			//InterlockedDecrement(&m_nRefCount);					
			return 1;			
		}else
		{	
			//TRACE0("�������ݳ���--0\r\n");
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
//	InterlockedIncrement(&m_nRefCount);	//ͳһ�ý���.
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

		pPlus = new WSABUFPLUS(m_nRecvBufferSize);	//�����İ���С.
		lpOw = GetOverlapPlus(eIORead,pPlus);		//���·���.
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
	//�޸�Ϊ���˳�ʱ�Ÿı����ü�������������ϵͳ�ȶ��ԡ�
	//--m_nRefCount;	
	//lpOverlapped->pBuff->wsabuf.len = numBerOfBytes;	//ʵ����
	//ReleaseOverlapPlus(lpOverlapped);					//�ͷ�
	//�������ݣ���������	
	//���յ�����.�ٽ�������.

	//ASSERT(AfxCheckMemory());
	
	bool bError = false;
	if(numBerOfBytes>0)
	{
		m_connInfo.recvBytes += numBerOfBytes;
		m_pChannel && (m_pChannel->m_client2Server += numBerOfBytes);

		//�����Debugʱ��ֱ���ó������
//#ifndef _DEBUG
		try{
//#endif
		//���յ����ݵĴ���
		//ASSERT(AfxCheckMemory());
		m_pProcessor->OnRecvRawData(lpOverlapped->pBuff->wsabuf.buf,numBerOfBytes);
		//ASSERT(AfxCheckMemory());
//#ifndef _DEBUG
		}catch(...)
		{	
			CString str;
			sockaddr_in addr;
			GetPeerAddr(addr);
			
			str.Format("��������%d.%d.%d.%d�������쳣�����Ͽ�������",
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
		WSARecvData(lpOverlapped);	// ����ʹ�ø��ڴ����.
		return 1;	
	}else
	{
		//�����쳣����Ҫ�Ͽ�����.
		ReleaseOverlapPlus(lpOverlapped);				
		NotifyExit();
		InterlockedDecrement(&m_nRefCount);		
		SetErrorFlag(WSARecvData_FUN);
		return -1;
	}
}


UINT CHHWPConnection::OnSendDataFin(DWORD numBerOfBytes,OVERLAPPLUS* lpOverlapped)	//�����������
{
	bool bClose = false;
	if( lpOverlapped->nUserDefineType == (LPVOID)SD_FLAG_SEND_THEN_CLOSE )
	{
		//������ɺ���Ҫ�ر�.
		bClose = true;
	}

	m_pProcessor->OnSendDataFinish(lpOverlapped->pBuff->wsabuf.buf,numBerOfBytes);


	ReleaseOverlapPlus(lpOverlapped);		//ɾ���ڴ�.			
	m_connInfo.sendBytes += numBerOfBytes;		//�ܷ�������.
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
//	InterlockedIncrement(&m_nRefCount);	//ͳһ�ý���.
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
//		m_pProcessor->OnUserDefine((int)pOverlapPlus->nUserDefineType);	//ȡ�����λ.
//	ReleaseOverlapPlus(pOverlapPlus);
//	InterlockedDecrement(&m_nRefCount);	//ͳһ�ý���.
//	return 0;
//}

void CHHWPConnection::NotifyExit()
{
	if(m_hSockets!=INVALID_SOCKET)
	{
		closesocket(m_hSockets);	//�ر�
		m_hSockets = INVALID_SOCKET;
	}
	//InterlockedIncrement(&m_nRefCount);
	//WSASendData(NULL,-1);	//���Է�������.	//��Ȼ�᷵�ش���.	
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
	 //�϶��Ѿ���ʼ��.

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

	
	//���û�г��������ɳ����ǡ�
	//��RecvData��ɾ���ĺô��ǣ�֮�󲻻�����
	if( (nWhere == WSARecvData_FUN) &&
		!m_bsErrorFlag.test(WSARecvData_FUN) )	//���ﱣ֤�ˣ�ֻ�����һ�Ρ�
	{
		if(m_pProcessor)
		{	
			if(m_pProcessor->OnClose())	//����֪ͨ.
			{
				m_pProcessor->m_pConnection = NULL;	//��ֹ��δ���û���.
				m_bDeleteProcessor  = true;				
			}else
			{
				m_pProcessor = NULL;	// �Ͼ���ϵ 
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

	

	//������е�λ�ö��������ʾ����ȫ�������µĴ���
	//������ü���Ϊ0����ʾ�����һ�����󷵻�.
	if(m_nRefCount == 0)
	{
		if(m_bsErrorFlag.count() == m_bsErrorFlag.size())	//ȷ�������ٱ����ã�����ɾ����
		{
			PostDeleteThisMessage();
			//::delete this;
			return;
		}else
		{
			//������ü���Ϊ�㣬����־Ϊ���ã�Ӧ���� Read û�г��������������.
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