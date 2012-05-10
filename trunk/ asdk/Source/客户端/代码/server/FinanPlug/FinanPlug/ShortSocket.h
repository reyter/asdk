#pragma once
#include <winsock2.h>
#include <mswsock.h>
class CShortSocket
{
public:
	CShortSocket(void);
	~CShortSocket(void);
public:
	SOCKET	ConnectTo();
	SOCKET	ConnectTo(char * c_pHost,int c_nPort);
	void Disconnect();
	int SendData(char * c_pData,int c_nLen);
	int RecvData(char * c_pBuf,int c_nMaxLen);
	int HttpRecvData(char * c_pBuf,int c_nMaxLen);	
	int SendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen);
	int HttpSendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen);	
public:
	SOCKET m_socket;
	char m_acHost[256];
	int m_nPort;
};
