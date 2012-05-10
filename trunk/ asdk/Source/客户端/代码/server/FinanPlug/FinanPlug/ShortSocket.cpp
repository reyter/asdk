#include "StdAfx.h"
#include "ShortSocket.h"

#pragma comment(lib,"ws2_32.lib")

CShortSocket::CShortSocket(void)
{
	memset(m_acHost,0,sizeof(m_acHost));
	m_socket = INVALID_SOCKET;
}

CShortSocket::~CShortSocket(void)
{
}
SOCKET CShortSocket::ConnectTo()
{
	if (strlen(m_acHost) == 0 || m_nPort == 0)
		return INVALID_SOCKET;
	if (m_socket != INVALID_SOCKET)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
	return ConnectTo(m_acHost, m_nPort);
}
SOCKET CShortSocket::ConnectTo(char * c_pHost, int c_nPort)
{/*
	int nSock = INVALID_SOCKET;
	nSock = socket(AF_INET,SOCK_STREAM,0);
	if (nSock > 0)
	{
		int timeout ;
		timeout = 5 * 1000 ; // 5√Î
		setsockopt(nSock , SOL_SOCKET , SO_RCVTIMEO , (char *)&timeout ,  sizeof(timeout)) ;
		setsockopt(nSock , SOL_SOCKET , SO_SNDTIMEO , (char *)&timeout ,  sizeof(timeout)) ;

		CProxySocket::_instance->ConnectByHostInfo(nSock,c_pHost,c_nPort,&gCfg.m_proxyOption);
	}
	m_socket = nSock;
	return (SOCKET)nSock;*/
	
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
    timeout = 5 * 1000 ; // 5√Î
    setsockopt(iConSock , SOL_SOCKET , SO_RCVTIMEO , (char *)&timeout ,  sizeof(timeout)) ;
    setsockopt(iConSock , SOL_SOCKET , SO_SNDTIMEO , (char *)&timeout ,  sizeof(timeout)) ;
	iRtnCode=connect(iConSock, (struct sockaddr*) &stServAddr, sizeof(stServAddr));

	if(iRtnCode <0)
	{
		closesocket(iConSock);
		return INVALID_SOCKET;
	}
	m_socket = iConSock;
	return iConSock;
}

void CShortSocket::Disconnect()
{
	if (m_socket != INVALID_SOCKET)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
}

int CShortSocket::SendData(char * c_pData,int c_nLen)
{
	if (m_socket == INVALID_SOCKET)
		return -999;
	int iRet = send(m_socket,c_pData,c_nLen,0);
	if (iRet < 0)
	{
		Disconnect();
	}
	return iRet;
}

int CShortSocket::RecvData(char * c_pBuf,int c_nMaxLen)
{
	int iLen;
	char acBuf[4096];
	memset(acBuf,0,sizeof(acBuf));
	iLen = recv(m_socket,acBuf,8,0);
	if (iLen < 0)
		return iLen;
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
	}
	return iReadLen;
}

int CShortSocket::SendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen)
{
	m_socket = INVALID_SOCKET;
	ConnectTo(c_pHost,c_nPort);
	if (m_socket == INVALID_SOCKET)
		return -1001;
	int nSend = SendData(c_pSendData,c_nSendLen);
	if (nSend != c_nSendLen)
	{
		Disconnect();
		return -1002;
	}
	int nRecv = RecvData(c_pRecvBuf,c_nMaxLen);
	Disconnect();
	return nRecv;
}

int CShortSocket::HttpSendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen)
{
	ConnectTo(c_pHost,c_nPort);
	if (m_socket == INVALID_SOCKET)
		return -1001;
	int nSend = SendData(c_pSendData,c_nSendLen);
	if (nSend != c_nSendLen)
	{
		Disconnect();
		return -1002;
	}
	int nRecv = HttpRecvData(c_pRecvBuf,c_nMaxLen);
	Disconnect();
	return nRecv;
}

int CShortSocket::HttpRecvData(char * c_pBuf,int c_nMaxLen)
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
		if (iLen > strlen("HTTP/1.1 200 OK"))
		{
			if (!strstr(pBuf,"HTTP/1.1 200 OK"))
			{
				free(pBuf);
				return -999;
			}
		}
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
