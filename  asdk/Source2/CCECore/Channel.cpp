#include "stdafx.h"
#include "Channel.h"
#include "HHWPConnection.h"
#include "ChannelManager.h"


/////////////////////////////////////////////////////////////////////////////


int CALLBACK CChannel::ConnectAcceptCondition(IN LPWSABUF lpCallerId,
											  IN LPWSABUF lpCallerData,
											  IN OUT LPQOS lpSQOS,
											  IN OUT LPQOS lpGQOS,
											  IN LPWSABUF lpCalleeId,
											  OUT LPWSABUF lpCalleeData,
											  OUT GROUP FAR *g,
											  IN DWORD dwCallbackData)
{
	/*sockaddr_in* pCaller=(sockaddr_in*)lpCallerId->buf;
	if(CSystemConfigure::GetInstance()->IsAddrInBlockList(pCaller->sin_addr.S_un.S_addr))
	{
	return CF_REJECT;
	}*/
	return CF_ACCEPT;
}

UINT CChannel::ListnerThreadProc(LPVOID pParam)
{
	WSAEVENT wHEvent = WSACreateEvent();

	linger templinger;
	templinger.l_linger = 0; //
	templinger.l_onoff = 1;
	int nSockReuse = 1; 

	CChannel * pChan = (CChannel*)pParam;

	if(pChan)
	{
		while(!pChan->m_bShutdown)
		{
			DWORD dwRet;
			dwRet = WSAWaitForMultipleEvents(1,
				&pChan->m_hEventAccept,FALSE,100,FALSE);
			if(pChan->m_bShutdown)
				break;
			if(dwRet == WSA_WAIT_TIMEOUT)
				continue;

			WSANETWORKEVENTS events;
			int nRet = WSAEnumNetworkEvents(pChan->m_sListenSocket,pChan->m_hEventAccept,&events);

			if(nRet == SOCKET_ERROR)
			{
				//AppendLog("ListnerThreadProc error!");
				break;
			}
			if(events.lNetworkEvents & FD_ACCEPT)
			{
				if(events.iErrorCode[FD_ACCEPT_BIT] == 0 && !pChan->m_bShutdown)
				{
					//准备接收连接
					SOCKET clinetsocket = INVALID_SOCKET;
					int nRet = -1;
					SOCKADDR_IN temp;
					int nLen = sizeof(SOCKADDR_IN);
					//clinetsocket = WSAAccept(pChan->m_sListenSocket,(SOCKADDR*)&temp,&nLen,ConnectAcceptCondition,(DWORD_PTR)pChan);
					clinetsocket = accept(pChan->m_sListenSocket,(SOCKADDR*)&temp,&nLen);
					//接收连接,不做任何验证。
					if(clinetsocket!=SOCKET_ERROR)
					{

						//创建连接对象，关联到完成端口						
						setsockopt(clinetsocket,SOL_SOCKET,SO_REUSEADDR,(const char*)&nSockReuse,sizeof(nSockReuse));					
						setsockopt(clinetsocket,SOL_SOCKET,SO_LINGER,(const char*)&templinger,sizeof(templinger));						
						CHHWPConnection* pConn = new CHHWPConnection(clinetsocket,pChan);						

					}
				}
			}

		}
		//停止.
		extern void AppendLog(const char* pLog);
		CString str;
		str.Format("端口停止%d",pChan->m_core.nLocalPort);
		AppendLog(str);
        
	}
	WSACloseEvent(wHEvent);
	return 0xdead;
}

//void CChannel:://AppendLog(LPCTSTR mesg)
//{
//	CHHWPIOCP::g_pHHWPIOCP->//AppendLog(mesg);
//}

bool CChannel::Open()
{
	//Create Listen.
	m_sListenSocket = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_IP,NULL,0,WSA_FLAG_OVERLAPPED);	//Overlap
	if(m_sListenSocket == INVALID_SOCKET)
	{
		//AppendLog("Create WSASocket Failed(StartListen)!");
		return false;
	}

	m_hEventAccept = WSACreateEvent();

	if(m_hEventAccept == WSA_INVALID_EVENT)
	{
		//AppendLog("WSAEvent Error!");
		return false;
	}

	int nRet = WSAEventSelect(m_sListenSocket,m_hEventAccept,FD_ACCEPT);

	if(nRet == SOCKET_ERROR)
	{
		//AppendLog("WSAEventSelect 失败 ");
		closesocket(m_sListenSocket);
		m_sListenSocket = INVALID_SOCKET;
		return false;
	}
	SOCKADDR_IN saServer;
	saServer.sin_port = htons(m_core.nLocalPort);
	saServer.sin_family = AF_INET;
	saServer.sin_addr.S_un.S_addr = INADDR_ANY;

	//bool bReuse = true;
	//setsockopt(m_sListenSocket,SOL_SOCKET,SO_REUSEADDR,(char*)&bReuse,sizeof(BOOL));

	nRet = bind(m_sListenSocket,(SOCKADDR*)&saServer,sizeof(saServer));

	if(nRet == SOCKET_ERROR )
	{
		m_core.nChannelStatus = ST_CANNOTOPEN;
		//AppendLog("绑定端口失败！");		
		::MessageBox(AfxGetMainWnd()->m_hWnd,"本地端口已经被占用，无法开启!","警告",MB_OK|MB_ICONEXCLAMATION);
		closesocket(m_sListenSocket);
		m_sListenSocket = INVALID_SOCKET;
		return false;
	}

	nRet = listen(m_sListenSocket,15);
	if(nRet == SOCKET_ERROR )
	{
		m_core.nChannelStatus = ST_CANNOTOPEN;
		//AppendLog("开启侦听失败！");		
		::MessageBox(AfxGetMainWnd()->m_hWnd,"开启侦听失败，无法开启!","警告",MB_OK|MB_ICONEXCLAMATION);
		closesocket(m_sListenSocket);
		m_sListenSocket = INVALID_SOCKET;
		return false;
	}

	m_bShutdown = false;
	m_pListenThread = AfxBeginThread(CChannel::ListnerThreadProc,this);
	m_core.nChannelStatus = ST_OPENING;	//打开

	if(!m_pListenThread)
	{
		m_core.nChannelStatus = ST_CANNOTOPEN;
		//AppendLog("创建侦听线程失败！");		
		::MessageBox(AfxGetMainWnd()->m_hWnd,"创建侦听线程失败，无法开启!","警告",MB_OK|MB_ICONEXCLAMATION);
		closesocket(m_sListenSocket);
		m_sListenSocket = INVALID_SOCKET;
		return false;
	}
	CString strOpen;	
	strOpen.Format("开启通道[ %s ]",m_core.szChannelName);
	//AppendLog(strOpen);
	return true;
}
bool CChannel::EditChannel(CHANNEL_INFO_CORE* pNewCore)
{
	//int nStatus = m_core.nChannelStatus;
	pNewCore->nChannelStatus = m_core.nChannelStatus;	//保持状态！
	m_core = *pNewCore;		
	CChannelManager::GetInstance()->AfterEditChannel(this);
	return false;
}


CChannel::CChannel(CHANNEL_INFO_CORE* core):m_nMaxConnection(0)
{
	m_core = *core;
	InitializeCriticalSection(&m_cslsConn);
	m_client2Server=0;
	m_server2Client=0;
	m_pListenThread= NULL;
	m_bShutdown = false;
}
CChannel::~CChannel()
{
	//此处应删除通道内的所有连接.
	EnterCriticalSection(&m_cslsConn);
	POSITION pos = m_lsConnection.GetHeadPosition();
	while(pos)
	{
		CHHWPConnection* pConn = (CHHWPConnection*)m_lsConnection.GetNext(pos);
		if(pConn)
			pConn->NotifyExit();
	}
	LeaveCriticalSection(&m_cslsConn);
	DeleteCriticalSection(&m_cslsConn);
}
void  CChannel::GetChannelInfo(HHWP_CHANNELINFO* pInfo)
{
	pInfo->client2server = m_client2Server/1024/1024.0;
	pInfo->server2client = m_server2Client/1024/1024.0;	
	strcpy(pInfo->szChanName,m_core.szChannelName);
	//状态
	pInfo->nChannelStatus = m_core.nChannelStatus;
	pInfo->pChannel = this;
	pInfo->nConnect = m_lsConnection.GetCount();
	pInfo->nMaxConnect = m_nMaxConnection;
}

INT_PTR  CChannel::GetConnectionCount()
{
	return m_lsConnection.GetCount();
}

void CChannel::AddConnection(LPVOID pConnection)
{
	

	EnterCriticalSection(&m_cslsConn);
	if(!m_bShutdown)
		m_lsConnection.AddTail((CHHWPConnection*)pConnection);
	m_nMaxConnection = max(m_nMaxConnection,m_lsConnection.GetCount());
	LeaveCriticalSection(&m_cslsConn);

}
void CChannel::DeleteConnection(LPVOID pConnection)
{
	EnterCriticalSection(&m_cslsConn);
	POSITION pos = m_lsConnection.Find((CHHWPConnection*)pConnection);
	if(pos)
		m_lsConnection.RemoveAt(pos);
	LeaveCriticalSection(&m_cslsConn);
}

void  CChannel::Quit()
{
	HANDLE handle =  m_pListenThread ? m_pListenThread->m_hThread:NULL;
	m_bShutdown = true;

	EnterCriticalSection(&m_cslsConn);
	//终止接收线程
	if(handle)
	{
		int nRet = WaitForSingleObject(m_pListenThread->m_hThread,500);
		if(nRet == WAIT_TIMEOUT)
		{
			TerminateThread(handle,-1);
		}		
		closesocket(m_sListenSocket);
		//CloseHandle(m_pListenThread->m_hThread);
	}
	//然后,通知所有的连接退出 
	POSITION pos = m_lsConnection.GetHeadPosition();
	while(pos)
	{
		CHHWPConnection* pConn = (CHHWPConnection*)m_lsConnection.GetNext(pos);
		if(pConn)
		{
			pConn->NotifyExit();
		}
	}	
	m_lsConnection.RemoveAll();
	m_pListenThread = NULL;
	LeaveCriticalSection(&m_cslsConn);
	CString strLog;
	strLog.Format("停止通道 [ %s ]",m_core.szChannelName);
	//AppendLog(strLog);
}

void CChannel::Stop()
{
	m_core.nChannelStatus = ST_CLOSE;
	CChannelManager::GetInstance()->SaveConfig();
	Quit();
}
void  CChannel::GetConnForDisPlay(CONNECT_INFO_SHOW*& pInfo,INT_PTR& nAlloc,INT_PTR& nData)
{	
	EnterCriticalSection(&m_cslsConn);
	INT_PTR nCount = m_lsConnection.GetCount();
	nData = nCount;
	if(nCount==0 && nData ==0)
	{
		LeaveCriticalSection(&m_cslsConn);
		return;
	}
	if(nCount >= nAlloc )
	{
		nAlloc = nCount;
		if(pInfo)
			delete []pInfo;
		pInfo = new CONNECT_INFO_SHOW[nAlloc];
	}
	POSITION pos = m_lsConnection.GetHeadPosition();
	for(int i=0;pos;++i)
	{
		CHHWPConnection* pConn = (CHHWPConnection*)m_lsConnection.GetNext(pos);
		if(pConn)
		{
			pConn->GetConnInfo(pInfo+i);
		}
	}
	LeaveCriticalSection(&m_cslsConn);
}