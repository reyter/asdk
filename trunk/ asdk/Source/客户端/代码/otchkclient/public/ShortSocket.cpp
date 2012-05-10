#include "StdAfx.h"
#include "ProxySocket.h"
#include "ShortSocket.h"

CShortSocket::CShortSocket(void)
{
	memset(m_acHost,0,sizeof(m_acHost));
	m_socket = INVALID_SOCKET;
	m_bKeepLive = false;
	m_pProxy = NULL;
}

CShortSocket::~CShortSocket(void)
{
}
SOCKET CShortSocket::ConnectTo(CProxyOption * proxy)
{
	m_pProxy = proxy;
	if (strlen(m_acHost) == 0 || m_nPort == 0)
		return INVALID_SOCKET;
	if (m_socket != INVALID_SOCKET)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
	return ConnectTo(m_acHost, m_nPort,proxy);
}
SOCKET CShortSocket::ConnectTo(char * c_pHost, int c_nPort,CProxyOption * proxy)
{
	m_pProxy = proxy;
	if (m_bKeepLive && strcmp(m_acHost,c_pHost) == 0 && c_nPort == m_nPort && m_socket != INVALID_SOCKET)
	{
		return m_socket;
	}
	else
	{
		strcpy(m_acHost,c_pHost);
		m_nPort = c_nPort;
		if (m_socket != INVALID_SOCKET)
			Disconnect();
	}
	int nSock = INVALID_SOCKET;
	nSock = socket(AF_INET,SOCK_STREAM,0);
	if (nSock > 0)
	{
		int timeout ;
		timeout = 5 * 1000 ; // 5秒
		setsockopt(nSock , SOL_SOCKET , SO_RCVTIMEO , (char *)&timeout ,  sizeof(timeout)) ;
		timeout = 5 * 1000 ; // 5秒
		setsockopt(nSock , SOL_SOCKET , SO_SNDTIMEO , (char *)&timeout ,  sizeof(timeout)) ;

		CProxySocket::_instance->ConnectByHostInfo(nSock,c_pHost,c_nPort,proxy);
	}
	m_socket = nSock;
	return (SOCKET)nSock;
	/*
	int iRtnCode;
	SOCKET   iConSock;
	WSADATA wsaData;
	strncpy(m_acHost,c_pHost,sizeof(m_acHost)-1);
	m_nPort = c_nPort;
	struct sockaddr_in stServAddr;
	
	memset(&stServAddr,0, sizeof(stServAddr));
	stServAddr.sin_family = AF_INET;
	stServAddr.sin_addr.s_addr =inet_addr(c_pHost);
	stServAddr.sin_port = htons(c_nPort);

	if(WSAStartup( MAKEWORD( 2, 2 ), &wsaData )!=0)
		return INVALID_SOCKET;

	iConSock=socket(AF_INET, SOCK_STREAM, 0);
	if(iConSock == INVALID_SOCKET )
	{
		return iConSock;
	}
    int timeout ;
    timeout = 5 * 1000 ; // 5秒
    setsockopt(iConSock , SOL_SOCKET , SO_RCVTIMEO , (char *)&timeout ,  sizeof(timeout)) ;
    setsockopt(iConSock , SOL_SOCKET , SO_SNDTIMEO , (char *)&timeout ,  sizeof(timeout)) ;
	iRtnCode=connect(iConSock, (struct sockaddr*) &stServAddr, sizeof(stServAddr));

	if(iRtnCode <0)
	{
		closesocket(iConSock);
		return INVALID_SOCKET;
	}
	m_socket = iConSock;
	return iConSock;*/
}

void CShortSocket::Disconnect()
{
	if (m_socket != INVALID_SOCKET)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
}

bool CShortSocket::TestConnect(char * c_pHost, int c_nPort,CProxyOption * proxy)
{
	int nSock = 0;
	int nRet = -1;
	nSock = socket(AF_INET,SOCK_STREAM,0);
	if (nSock > 0)
	{
		int timeout ;
		timeout = 5 * 1000 ; // 5秒
		setsockopt(nSock , SOL_SOCKET , SO_RCVTIMEO , (char *)&timeout ,  sizeof(timeout)) ;
		setsockopt(nSock , SOL_SOCKET , SO_SNDTIMEO , (char *)&timeout ,  sizeof(timeout)) ;

		nRet = CProxySocket::_instance->ConnectByHostInfo(nSock,c_pHost,c_nPort,proxy);
		if (nRet >= 0)
			closesocket(nSock);
	}
	
	if (nRet >= 0)
		return true;
	else
		return false;
	/*
	int iRtnCode;
	SOCKET   iConSock;
	WSADATA wsaData;
	strncpy(m_acHost,c_pHost,sizeof(m_acHost)-1);
	m_nPort = c_nPort;
	struct sockaddr_in stServAddr;
	
	memset(&stServAddr,0, sizeof(stServAddr));
	stServAddr.sin_family = AF_INET;
	stServAddr.sin_addr.s_addr =inet_addr(c_pHost);
	stServAddr.sin_port = htons(c_nPort);

	if(WSAStartup( MAKEWORD( 2, 2 ), &wsaData )!=0)
		return false;

	iConSock=socket(AF_INET, SOCK_STREAM, 0);
	if(iConSock == INVALID_SOCKET )
	{
		return false;
	}
    int timeout ;
    timeout = 5 * 1000 ; // 5秒
    setsockopt(iConSock , SOL_SOCKET , SO_RCVTIMEO , (char *)&timeout ,  sizeof(timeout)) ;
    setsockopt(iConSock , SOL_SOCKET , SO_SNDTIMEO , (char *)&timeout ,  sizeof(timeout)) ;
	iRtnCode=connect(iConSock, (struct sockaddr*) &stServAddr, sizeof(stServAddr));

	closesocket(iConSock);
	if(iRtnCode <0)
	{		
		return false;
	}	
	return true;
	*/
}

int CShortSocket::SendData(char * c_pData,int c_nLen)
{
	if (m_socket == INVALID_SOCKET)
		return -999;
	char acHttp[1024];
	int iRet = 0;
	if (m_pProxy && m_pProxy->m_bUseHttpHead)
	{
		sprintf(acHttp,"GET http://%s:%d HTTP/1.0\r\ncontent-type: audio/mp3;\r\ncontent-source : invest\r\nUser-Agent: analyonline\r\nContent-Length: %d\r\nCache-Control: no-cache\r\nProxy-Connection: Keep-Alive\r\n\r\n",m_acHost,m_nPort,c_nLen);
		send(m_socket,acHttp,strlen(acHttp),0);
		if (iRet < 0)
		{
			Disconnect();
			return iRet;
		}
	}
	iRet = send(m_socket,c_pData,c_nLen,0);
	if (iRet < 0)
	{
		Disconnect();
	}
	return iRet;
}

int CShortSocket::RecvData(char * c_pBuf,int c_nMaxLen,HWND c_hwndNotify)
{
	int iLen;
	char acBuf[4096];
	memset(acBuf,0,sizeof(acBuf));
	int timeout ;
	timeout = 15 * 1000 ; // 50秒
	setsockopt(m_socket , SOL_SOCKET , SO_RCVTIMEO , (char *)&timeout ,  sizeof(timeout)) ;

	iLen = recv(m_socket,acBuf,8,0);
	if (iLen < 0)
		return iLen;
	if (strnicmp(acBuf,"http",4) == 0)//是http协议，需要跳过http头
	{
		while(strncmp(acBuf+strlen(acBuf) - 4,"\r\n\r\n",4) != 0)
		{
			iLen = recv(m_socket,acBuf + strlen(acBuf),1,0);
			if (iLen < 0)
			{
				return iLen;
			}
			if (strlen(acBuf) > 1024)
				return -1024;
		}
		iLen = recv(m_socket,acBuf,8,0);
		if (iLen < 8)
			return -8;
	}
	memcpy(c_pBuf,acBuf,8);
	int iReadLen = 8;
	int iNeedLen = *(unsigned int *)(c_pBuf + 4) + 8;
	if (c_nMaxLen < iNeedLen)
		return -999;
	while(iNeedLen > iReadLen)
	{
		if (iNeedLen - iReadLen > 4096)
			iLen = recv(m_socket,c_pBuf+iReadLen,4096,0);
		else
			iLen = recv(m_socket,c_pBuf+iReadLen,iNeedLen - iReadLen,0);
		if (iLen < 0)
		{
			Disconnect();
			return iLen;
		}
		iReadLen += iLen;
		if (c_hwndNotify)
		::PostMessage(c_hwndNotify,WM_DATA_PROGRESS,iNeedLen,iReadLen);
	}
	return iReadLen;
}

int CShortSocket::SendAndRecv(CString c_strHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption * proxy)
{
	char acHost[32];
	acHost[30] = 0;
	unicodeToAscii(c_strHost,acHost,30);
	return SendAndRecv(acHost,c_nPort,c_pSendData,c_nSendLen,c_pRecvBuf,c_nMaxLen,c_hwndNotify,proxy);
}

int CShortSocket::SendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption * proxy)
{
	m_socket = INVALID_SOCKET;
	ConnectTo(c_pHost,c_nPort,proxy);
	if (m_socket == INVALID_SOCKET)
		return -1001;
	int nSend = SendData(c_pSendData,c_nSendLen);
	if (nSend != c_nSendLen)
	{
		Disconnect();
		return -1002;
	}
	int nRecv = RecvData(c_pRecvBuf,c_nMaxLen,c_hwndNotify);
	if (m_bKeepLive == false)
		Disconnect();	
	return nRecv;
}

int CShortSocket::HttpSendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption *proxy)
{
	ConnectTo(c_pHost,c_nPort,proxy);
	if (m_socket == INVALID_SOCKET)
		return -1001;
	
	int timeout = 5000 * 4; //3s

	setsockopt(m_socket,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout));

	setsockopt(m_socket,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));

	char acHttp[1024];
	sprintf(acHttp,"GET /simu_trade.do HTTP/1.1\r\nHost: %s:%d \r\ncontent-type: audio/mp3;\r\ncontent-source : invest\r\nUser-Agent: analyonline\r\nContent-Length: %d\r\nCache-Control: no-cache\r\n\r\n",c_pHost,c_nPort,c_nSendLen);
	int nLen = strlen(acHttp);	
		
	memcpy(acHttp + nLen,c_pSendData,c_nSendLen);
	/*
	FILE *f;
	f = fopen("c:\\test.pk","wb");
	if (f)
	{
		fwrite(acHttp,1,nLen + c_nSendLen,f);
		fclose(f);
	}
	*/
	int nSend = SendData(acHttp,nLen + c_nSendLen);
	if (nSend != nLen + c_nSendLen)
	{		
		Disconnect();
		return -1002;
	}
/*
	nSend = SendData(c_pSendData,c_nSendLen);
	if (nSend != c_nSendLen)
	{
		Disconnect();
		return -1002;
	}*/
	int nRecv = HttpRecvData(c_pRecvBuf,c_nMaxLen,c_hwndNotify);
	Disconnect();
	return nRecv;
}

int CShortSocket::HttpSMGSendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption *proxy)
{
	ConnectTo(c_pHost,c_nPort,proxy);
	if (m_socket == INVALID_SOCKET)
		return -1001;
	
	int timeout = 5000 * 4; //3s

	setsockopt(m_socket,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout));

	setsockopt(m_socket,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));

	char acHttp[1024*2];
	char acUtf8[1024];
	int nUtf8 = toUtf8(c_pSendData,acUtf8,c_nSendLen);
	sprintf(acHttp,"POST /services/ReceiverService.jws HTTP/1.1\r\nHost: %s:%d \r\nContent-Type: text/xml; charset=utf-8\r\nSOAPAction: \"\"\r\ncontent-source : invest\r\nUser-Agent: Investoday Client v1.0\r\nContent-Length: %d\r\n\r\n",c_pHost,c_nPort,nUtf8);
	int nLen = strlen(acHttp);	
			
	memcpy(acHttp + nLen,acUtf8,nUtf8);
	
	FILE *f;
	f = fopen("c:\\test\\get.d","wb");
	if (f)
	{
		fwrite(acHttp,1,nLen + nUtf8,f);
		fclose(f);
	}
	
	int nSend = SendData(acHttp,nLen + nUtf8);
	if (nSend != nLen + nUtf8)
	{		
		Disconnect();
		return -1002;
	}
/*
	nSend = SendData(c_pSendData,c_nSendLen);
	if (nSend != c_nSendLen)
	{
		Disconnect();
		return -1002;
	}*/
	int nRecv = HttpRecvData(c_pRecvBuf,c_nMaxLen,c_hwndNotify);
	Disconnect();
	return nRecv;
}

int CShortSocket::HttpRecvData(char * c_pBuf,int c_nMaxLen,HWND c_hwndNotify)
{
	int iLen,iRead;
	char *pBuf = (char *)malloc(c_nMaxLen);
	memset(pBuf,0,c_nMaxLen);
	iLen = 0;
	iRead = 0;
	char *pData = NULL;
	int nHeadLen = 0;
	int nDataLen = 0;
	while(iLen < c_nMaxLen)
	{		
		int nToRead = c_nMaxLen - iLen;
		iRead = recv(m_socket,pBuf + iLen,nToRead,0);
		if (iRead <= 0)
			break;
		iLen += iRead;
		if (nDataLen == 0 && nHeadLen == 0)
		{
			pData = strstr(pBuf,"\r\n\r\n");
			if (pData)
			{
				nHeadLen = pData - pBuf + 4;
				char *pLenth = strstr(pBuf,"Content-Length:");
				if (!pLenth)
				{
					iLen = -1;
					break;
				}
				char *pEnd = strstr(pLenth,"\r\n");
				char acLen[32];
				memset(acLen,0,sizeof(acLen));
				pLenth += 15;
				strncpy(acLen,pLenth,pEnd - pLenth);
				nDataLen = atoi(acLen);
			}
		}
		if (nDataLen + nHeadLen <= iLen)
			break;
	}
	/*
	FILE *f;
	f = fopen("c:\\test\\answer.data","wb");
	if (f)
	{
		fwrite(acBuf,1,iLen,f);
		fclose(f);
	}*/
	if (iLen <= 0)
	{
		free(pBuf);
		return iLen;
	}
	
	memcpy(c_pBuf,pBuf + nHeadLen,nDataLen);
	free(pBuf);
	return nDataLen;
	/*
	memcpy(c_pBuf,acBuf,8);
	int iReadLen = 8;
	int iNeedLen = *(unsigned int *)(c_pBuf + 4) + 8;
	if (c_nMaxLen < iNeedLen)
		return -999;
	while(iNeedLen > iReadLen)
	{
		if (iNeedLen - iReadLen > 4096)
			iLen = recv(m_socket,c_pBuf+iReadLen,4096,0);
		else
			iLen = recv(m_socket,c_pBuf+iReadLen,iNeedLen - iReadLen,0);
		if (iLen < 0)
		{
			Disconnect();
			return iLen;
		}
		iReadLen += iLen;
		if (c_hwndNotify)
		::PostMessage(c_hwndNotify,WM_DATA_PROGRESS,iNeedLen,iReadLen);
	}
	return iReadLen;*/
}
