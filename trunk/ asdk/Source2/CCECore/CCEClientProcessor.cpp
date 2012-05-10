// HHIOCPClientProcessor.cpp : 实现文件
//

#include "stdafx.h"
//#include "TCECore.h"
#include "CCEClientProcessor.h"
#include "HHWPIOCP.h"
#include "HHWPConnection.h"
#include "CBase64Coding.hpp"

//从接字安全发送数据，如果全部发送成功，返回True，否则返回FALSE
bool SafeSendData(SOCKET sock,char* buff, size_t nLen,int nFlags=0)
{
	size_t nSend = 0;
	size_t i = 0;
	while(nSend < nLen)
	{
		i = send(sock,buff+nSend,nLen-nSend,nFlags);
		if(i>0)
		{
			nSend +=i;
		}else if(i==0)
		{
			// 对方已经关闭了套接字。

			return false;			
		}
		else
		{
			//出错
			return false; //网络出错
		}
	}
	return true;
}
//从套接安全接收数据，如果全部接收成功，则返回TRUE,否则返回False
bool SafeRecvData(SOCKET sock,char* buff,int nLen,int nFlags=0)
{
	int nRecv =0;
	int i =0;
	while(nRecv < nLen)
	{
		i = recv(sock,buff+nRecv,nLen-nRecv,nFlags);
		if(i>0)
		{
			nRecv +=i;
		}else if (i==0)
		{
			return false;
		}
		else
		{
			return false;
		}
	}
	return true;
}

#define safe_recv  SafeRecvData
#define safe_send  SafeSendData



IMPLEMENT_DYNAMIC(CCCEClientProcessor,CCCEProcessor)


//由该函数来发起连接.
void CALLBACK  CCECreateConnection(LPVOID lParam)
{
	if(!lParam)
		return ;

	CCCEClientProcessor*  pProcessor = (CCCEClientProcessor*)lParam;
	pProcessor->_CCEConnect();
}

// CCCEClientProcessor

CCCEClientProcessor::CCCEClientProcessor()
:m_nCurrentStatus(CCE_CONN_STATUS_OFFLINE)
,m_bMannualEnd(false)
{
	static bool bRegister = false;
	if(!bRegister)
	{		
		CHHWPIOCP::RegisterIOCPUserCommand(CCE_CREATE_CONNECTION,CCECreateConnection);
		bRegister = true;
	}
}

CCCEClientProcessor::~CCCEClientProcessor()
{
}
// CCCEClientProcessor 成员函数

int g_nConnectTimeOut=10;

int ConnectWithTimeOut( IN SOCKET s, IN const struct sockaddr FAR * name, IN int namelen,const bool* pBStop=NULL)
{
	int nRet=-1;
	unsigned long ul = 1; 
	ioctlsocket(s,FIONBIO,(unsigned long*)&ul);
	if(connect(s,name,namelen))
	{
		timeval val;
		val.tv_sec = 1;
		val.tv_usec = 0;
		fd_set fs;
		FD_ZERO(&fs);
		FD_SET(s,&fs);

		for(int i=0;i<g_nConnectTimeOut;++i)
		{
            if(pBStop && (*pBStop))
			{
				nRet = -1;
				break;
			}

			int rs = select(s,NULL,&fs,NULL,&val);
			if(rs<=0)
			{
				nRet = -1;	//失败
			}
			else 
			{
				nRet = 0;
				break;
			}
		}
	}else
	{
		nRet = 0;	
	}
	ul =0;
	ioctlsocket(s,FIONBIO,(unsigned long*)&ul);	
	return nRet;
}


bool CCCEClientProcessor::ConnectWithProxy(const char* svrAddress,UINT nPort,bool* pBStop)
{
	m_strReAddr = svrAddress;
	//m_hSocket = WSASocket(PF_INET,SOCK_STREAM,IPPROTO_IP,NULL,0,WSA_FLAG_OVERLAPPED);
	m_hSocket = socket(PF_INET,SOCK_STREAM,0);
	if(m_hSocket == INVALID_SOCKET)
		return false;

	try
	{
		if(m_proxy_data.iProxyType!=PROXYTYPE_NOPROXY)
		{
			/*USES_CONVERSION;

			LPCSTR lpszAscii = T2A((LPTSTR)((LPCTSTR)m_pObject->m_strAddr));
			ULONG ulIP = inet_addr(lpszAscii);
			if (INADDR_NONE != ulIP)
			{
			m_nPeerIP = ulIP;
			}
			else
			{
			LPHOSTENT lphost = gethostbyname(lpszAscii);
			if (lphost != NULL)
			{
			m_nPeerIP = ((LPIN_ADDR)lphost->h_addr)->s_addr;
			}
			}
			m_pDock->m_usProxyPeerPort = htons(m_pObject->m_nPort);

			pConnect = new CWSASock;
			pConnect->Create();
			pConnect->Connect(m_proxy_data.szProxyHost,m_proxy_data.iProxyPort);*/

			//连接代理服务器

			sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(m_proxy_data.iProxyPort);
			//addr.sin_addr.s_addr = 	inet_addr(svrAddress);
			struct hostent* svr_host= gethostbyname(m_proxy_data.szProxyHost);
			if(svr_host == NULL)
				return false;
			addr.sin_addr.s_addr = ((struct in_addr*)(svr_host->h_addr))->s_addr;


			/*struct hostent**/
			svr_host= gethostbyname(svrAddress);
			if(svr_host == NULL)
				throw "连接地址不正确";

			m_nPeerIP = ((struct in_addr*)(svr_host->h_addr))->s_addr;


			m_nSvrPort = nPort;

			
			if(ConnectWithTimeOut(m_hSocket,(sockaddr*)&addr,sizeof(addr),pBStop))						
					throw "Connect Failed";
			

			if(PROXYTYPE_SOCKS4 == m_proxy_data.iProxyType)
			{
				if(!connect_sock4(m_hSocket))
					throw ("Error connect sock4");
			}
			else if(PROXYTYPE_SOCKS4A == m_proxy_data.iProxyType)
			{
				if(!connect_sock4(m_hSocket))
					throw ("Error connect sock4a");
			}
			else if(PROXYTYPE_SOCKS5 == m_proxy_data.iProxyType)
			{
				if(!connect_sock5(m_hSocket))
					throw ("Error connect sock5");
			}
			else if(PROXYTYPE_HTTP11 == m_proxy_data.iProxyType)
			{
				if(!connect_http11(m_hSocket))
					throw ("Error connect http11");
			}else
				throw "Unknow ...";
		}
		else
		{
			sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(nPort);
			//addr.sin_addr.s_addr = 	inet_addr(svrAddress);
			struct hostent* svr_host= gethostbyname(svrAddress);
			if(svr_host == NULL)
				return false;
			addr.sin_addr.s_addr = ((struct in_addr*)(svr_host->h_addr))->s_addr;

			if(ConnectWithTimeOut(m_hSocket,(sockaddr*)(&addr),sizeof(addr),pBStop))
				throw "直连失败!";
			return true;

		}
	}
	catch (...) 
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
		return false;
	}
	return true;
}

BOOL  CCCEClientProcessor::connect_sock4(SOCKET hConnect)
{
	//CDockSock* m_pDock = (CDockSock*)m_pObject;

	//SOCKET hConnect = (SOCKET)(*pConnect);
	CHAR pch[256];
	//STEP1:
	{
		//Send request
		//USES_CONVERSION;

		LPCSTR lpszAscii = (LPCTSTR)m_strReAddr;


		char *command = pch;
		memset(command,0,9 + strlen(lpszAscii) + 1);
		int len = 9;

		command[0] = 4;
		command[1] = 1; //(/*m_nProxyOpID*/PROXYOP_CONNECT == PROXYOP_CONNECT) ? 1 : 2; //CONNECT or BIND request
		//		memcpy(&command[2], &m_nCurPort, 2);
		//ASSERT(m_l!=0 || m_nPeerIP != INADDR_NONE);
		DWORD wData = htons(m_nSvrPort);
		command[2] = (char)( wData & 0x00ff );
		command[3] = (char)( (wData>>8) & 0x00ff);


		memcpy(&command[4], &m_nPeerIP, 4);

		if(!SafeSendData(hConnect,pch,len))
			throw ("Error send");
	}
	//STEP2:
	{
		if(!SafeRecvData(hConnect,pch,8))
			throw ("Error recv");

		if (pch[1]!=90 || pch[0]!=0)
		{
			return FALSE;
		}
		return TRUE;
	}

	return FALSE;
}

BOOL CCCEClientProcessor::connect_sock5(SOCKET hConnect)
{
	CHAR pch[256];
	//Step1:请求验证方法
	{
		//Send initialization request
		unsigned char* command = (unsigned char*)pch;
		memset(command,0,10);

		command[0] = 5; //VN
		//CAsyncProxySocketLayer supports to logon types: No logon and
		//cleartext username/password (if set) logon
		command[1] = TRUE ? 2 : 1; //Number of logon types
		command[2] = TRUE ? 2 : 0; //2=user/pass, 0=no logon
		command[3] = 0; // 0 = no logon

		int len = TRUE ? 4 : 3; //length of request

		if(!SafeSendData(hConnect,pch,len))
			throw ("Error send");
	}
	//STEP2:
	{
		if(!SafeRecvData(hConnect,pch,2))
			throw ("Error recv");

		if (pch[0] != 5)
			return FALSE;

LABLE_CONTINUE:
		if(pch[1] == 0)//no logon needed
		{
			//m_proxy_data.bUseLogon = FALSE;

			//No auth needed
			//Send connection request
			LPCSTR lpszAsciiHost = m_strReAddr ? m_strReAddr : ""; 
			char *command = pch;
			memset(command,0,10+strlen(lpszAsciiHost)+1);
			command[0] = 5;
			command[1] = /*(m_nProxyOpID == PROXYOP_CONNECT)*/TRUE ? 1 : 2;
			command[2] = 0;
			command[3] = m_nPeerIP ? 1 : 3;
			size_t len = 4;
			if (m_nPeerIP )
			{
				memcpy(&command[len],&m_nPeerIP,4);
				len += 4;
			}
			else
			{
				command[len] = (char)strlen(lpszAsciiHost);
				strcpy(&command[len+1],lpszAsciiHost);
				len += strlen(lpszAsciiHost) + 1;
			}
			short port = htons(m_nSvrPort);//m_proxy_data.iProxyPort);
			memcpy(&command[len],&port,2);
			len += 2;

			if(!SafeSendData(hConnect,pch,len))
				throw ("Error send");

			//STEP3:
			{
				if(!SafeRecvData(hConnect,pch,5))
					throw ("Error recv");

				if(pch[0]!=5 || pch[1]!=0)
					return FALSE;

				if(pch[3] == 1)
				{
					if(!safe_recv(hConnect,pch,5))
						throw ("Error recv");
					return TRUE;
				}
				else
				{
					if(!safe_recv(hConnect,pch,pch[4]+2))
						throw ("Error recv");
					return TRUE;
				}
			}
		}
		else if(pch[1] == 2)//logon needed
		{
			//m_proxy_data.bUseLogon = TRUE;
			//Send authentication
			LPCSTR lpszAsciiUser = m_proxy_data.szProxyUser;
			LPCSTR lpszAsciiPass = m_proxy_data.szProxyPass;
			ASSERT(strlen(lpszAsciiUser)<=255);
			ASSERT(strlen(lpszAsciiPass)<=255);
			unsigned char *buffer = (unsigned char*)pch;
			sprintf((char *)buffer, "  %s %s", 
				lpszAsciiUser ? lpszAsciiUser : "", lpszAsciiPass ? lpszAsciiPass : "");
			buffer[0] = 5; //VN
			buffer[1] = static_cast<unsigned char>(strlen(lpszAsciiUser));
			buffer[2 + strlen(lpszAsciiUser)] = static_cast<unsigned char>(strlen(lpszAsciiPass));
			size_t len = 3 + strlen(lpszAsciiUser) + strlen(lpszAsciiPass);

			if(!SafeSendData(hConnect,pch,len))
				throw  ("Error send");

			if(!SafeRecvData(hConnect,pch,2))
				throw  ("Error recv");

			if(pch[1] != 0)
				return FALSE;

			goto LABLE_CONTINUE;
		}
		else
		{
			return FALSE;
		}

		return TRUE;
	}
	return FALSE;

}
BOOL CCCEClientProcessor::connect_http11(SOCKET hConnect)
{
	CHAR pch[256];

	{
		char str[4096]; //This should be large enough

		char pHost[4096];

		if (!m_strReAddr.IsEmpty())
		{
			strcpy(pHost, (LPCTSTR)m_strReAddr);
		}
		else
		{
			sprintf(pHost, "%d.%d.%d.%d", m_nPeerIP%256, (m_nPeerIP>>8) % 256, (m_nPeerIP>>16) %256, m_nPeerIP>>24);
		}

		if (!strlen(m_proxy_data.szProxyUser))
		{
			//CONNECT
			sprintf(str, "CONNECT %s:%d HTTP/1.1\r\nHost: %s:%d\r\n\r\n", 
				pHost, m_nSvrPort,
				m_proxy_data.szProxyHost, m_proxy_data.iProxyPort);

		}
		else
		{
			//CONNECT
			sprintf(str, "CONNECT %s:%d HTTP/1.1\r\nHost: %s:%d\r\n", pHost, m_nSvrPort,
				m_proxy_data.szProxyHost, m_proxy_data.iProxyPort);

			char userpass[4096];
			sprintf(userpass, "%s:%s", m_proxy_data.szProxyUser ? m_proxy_data.szProxyUser : "", m_proxy_data.szProxyPass ? m_proxy_data.szProxyPass : "");
			char base64str[4096];

			CBase64Coding base64coding;
			if (!base64coding.Encode(userpass, strlen(userpass), base64str))
			{
				return FALSE;
			}

			strcat(str, "Authorization: Basic ");
			strcat(str, base64str);
			strcat(str, "\r\nProxy-Authorization: Basic ");
			strcat(str, base64str);
			strcat(str, "\r\n\r\n");
		}

		if(!safe_send(hConnect,str,strlen(str)))
		{
			throw ("Error send");
		}
	}
	{
		pch[0] = 0;
		int nBytesReceived = 0;
		for(;;)
		{
			if(strlen(pch) > 0)
			{
				if(!safe_recv(hConnect,pch + nBytesReceived,1))
					throw	("Error recv");
				nBytesReceived += 1;
			}
			else
			{
				if(!safe_recv(hConnect,pch,8))
					throw	("Error recv");
				nBytesReceived += 8;
			}
			pch[nBytesReceived] = 0;

			//Response begins with HTTP/
			const char start[] = "HTTP/";
			if (memcmp(start, pch, (strlen(start)>strlen(pch)) ? strlen(pch) : strlen(start)))
			{
				return FALSE;
			}

			char *pos = strstr(pch, "\r\n");
			if (pos)
			{
				char *pos2 = strstr(pch, " ");
				if (!pos2 || *(pos2+1) !='2' || pos2>pos)
				{
					return FALSE;
				}
			}

			if (strlen(pch)>3 && !memcmp(pch+strlen(pch)-4, "\r\n\r\n", 4)) //End of the HTTP header
			{
				return TRUE;
			}
		}//end for(;;)
	}
	return FALSE;

}


bool CCCEClientProcessor::ConnectToServer(const CString& host,int nPort,
											 CCE_PROXYTYPE  iProxyType,		//使用的代理类型.
											 const char* szProxyHost,	//代理地址
											 int  iProxyPort,		//代理端口
											 const char* szProxyUser,	//代理用户名
											 const char* szProxyPass,	//代理密码)
											 bool* pBStop)
{
	//设置要使用的代理
	SetProxy(iProxyType,		//使用的代理类型.
		szProxyHost,	//代理地址
		iProxyPort,		//代理端口
		szProxyUser,	//代理用户名
		szProxyPass	//代理密码)
		);

    if(ConnectWithProxy(host,nPort,pBStop))
	{
		linger templinger;
		templinger.l_linger = 0; //
		templinger.l_onoff = 0;

		int nSockReuse = 1; 

		//需要将其与一对着关联.
		setsockopt(m_hSocket,SOL_SOCKET,SO_REUSEADDR,(const char*)&nSockReuse,sizeof(nSockReuse));					
		setsockopt(m_hSocket,SOL_SOCKET,SO_LINGER,(const char*)&templinger,sizeof(templinger));						
		//CHHWPConnection* pConn = new CHHWPConnection(m_hSocket,this);
		//ASSERT(AfxCheckMemory());

		GenConnectionObject();

		//ASSERT(AfxCheckMemory());
		
		m_nCurrentStatus = CCE_CONN_STATUS_ONLINE;	// 在线.
		//连接成功.
		//OnConnectResult(true);
		return true;
	}else
	{
		//OnConnectResult(false);
	}
	return false;
}

void CCCEClientProcessor::OnConnectResult(bool bRet)
{
	//if(!bRet)
	//{
	//	//连接失败，再次重连.
	//}else
	//{
	//	
	//}
}

void CCCEClientProcessor::GenConnectionObject()
{
	//生成一个新的对象，该对象会在网络出错时自动析构.
	new CHHWPConnection(m_hSocket,this);	
}

void CCCEClientProcessor::SetProxy(CCE_PROXYTYPE  iProxyType,		//使用的代理类型.
			  const char* szProxyHost,	//代理地址
			  int  iProxyPort,		//代理端口
			  const char* szProxyUser,	//代理用户名
			  const char* szProxyPass	//代理密码)
			  )
{
	if(iProxyType<0 || iProxyType>4)
		return;
	m_proxy_data.iProxyType = iProxyType;
	m_proxy_data.iProxyPort = iProxyPort;
	if(szProxyHost)
		strncpy(m_proxy_data.szProxyHost,szProxyHost,sizeof(m_proxy_data.szProxyHost)-1);
	else
		strncpy(m_proxy_data.szProxyHost,"",sizeof(m_proxy_data.szProxyHost)-1);

	if(szProxyUser)
		strncpy(m_proxy_data.szProxyUser,szProxyUser,sizeof(m_proxy_data.szProxyUser)-1);
	else
		strncpy(m_proxy_data.szProxyUser,"",sizeof(m_proxy_data.szProxyUser)-1);

	if(szProxyPass)
		strncpy(m_proxy_data.szProxyPass,szProxyPass,sizeof(m_proxy_data.szProxyPass)-1);
	else
		strncpy(m_proxy_data.szProxyPass,"",sizeof(m_proxy_data.szProxyPass)-1);
}

bool CCCEClientProcessor::OnClose()
{
	bool bRet =  __super::OnClose();
	m_nCurrentStatus = CCE_CONN_STATUS_OFFLINE;
	
	if(!m_bMannualEnd)
			return false;	//默认不销毁。
	else
			return true;	//如果主动断开，则销毁之.
}


void CCCEClientProcessor::Disconnect()
{
	m_bMannualEnd = true;

	if(m_pConnection)
	{
		CHHWPConnection* pConnection = m_pConnection;
		m_pConnection = NULL;

		pConnection->m_pProcessor = NULL; //不要再回调回来。
		pConnection->NotifyExit();

		m_nCurrentStatus = CCE_CONN_STATUS_OFFLINE;		
	}
}


/**
* 非阻塞，异步连接到指定服务器
*/
void CCCEClientProcessor::SetSvrInfoAndConnect(const CString& host,
						  int nPort,
						  CCE_PROXYTYPE  iProxyType,		//使用的代理类型.
						  const char* szProxyHost,	//代理地址
						  int  iProxyPort,		//代理端口
						  const char* szProxyUser,	//代理用户名
						  const char* szProxyPass	//代理密码)
						  )
{
	//ASSERT(AfxCheckMemory());
	m_strReAddr.Format("%s",host);	//避免同一字串带来的释放.
	m_nSvrPort  = nPort;
	//设置要使用的代理
	SetProxy(iProxyType,		//使用的代理类型.
		szProxyHost,	//代理地址
		iProxyPort,		//代理端口
		szProxyUser,	//代理用户名
		szProxyPass	//代理密码)
		);
	CHHWPIOCP::SendUserRegisterCommand(CCE_CREATE_CONNECTION,this);

}

void CCCEClientProcessor::_CCEConnect()
{
	bool bStop = false;
	if(ConnectToServer(m_strReAddr,m_nSvrPort,
		m_proxy_data.iProxyType,
		m_proxy_data.szProxyHost,	//代理地址
		m_proxy_data.iProxyPort,		//代理端口
		m_proxy_data.szProxyUser,	//代理用户名
		m_proxy_data.szProxyPass,	//代理密码)
		&bStop
		))
	{
		OnConnectResult(true);
	}else
	{
		m_pConnection = NULL;
		OnConnectResult(false);
	}
}