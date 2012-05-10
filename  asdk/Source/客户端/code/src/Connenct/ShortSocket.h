#pragma once
#include "ProxyOption.h"
class CProxyOption;
class CShortSocket
{
public:
	CShortSocket(void);
	~CShortSocket(void);
public:
	SOCKET	ConnectTo(CProxyOption * proxy);
	SOCKET	ConnectTo(char * c_pHost,int c_nPort,CProxyOption * proxy);
	SOCKET	ConnectTo(CString strIpAddress,int c_nPort,CProxyOption * proxy);
	void Disconnect();
	int SendData(char * c_pData,int c_nLen);
	int RecvData(char * c_pBuf,int c_nMaxLen,HWND c_hwndNotify);
	int HttpRecvData(char * c_pBuf,int c_nMaxLen,HWND c_hwndNotify);
	int SendAndRecv(CString c_strHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption * proxy);
	int SendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption * proxy);
	int HttpSendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption * proxy);
	int HttpSMGSendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption * proxy);
	bool TestConnect(char *,int,CProxyOption * proxy);
	void SetKeepLive(bool c_b){m_bKeepLive = c_b;};
public:
	SOCKET m_socket;
	char m_acHost[256];
	int m_nPort;
	bool m_bKeepLive;//是否保持连接，等待主动断开
	CProxyOption	*m_pProxy;
};
