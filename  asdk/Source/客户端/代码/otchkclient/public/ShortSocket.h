#pragma once
class CProxyOption;
class CShortSocket
{
public:
	CShortSocket(void);
	~CShortSocket(void);
public:
	/**
	*	@使用代理连接.
	*	@param proxy 代理信息类.
	*/
	SOCKET	ConnectTo(CProxyOption * proxy);
	/**
	*	@连接到.
	*	@param c_pHost
	*	@param c_nPort 端口.
	*	@param proxy 代理信息类.
	*/
	SOCKET	ConnectTo(char * c_pHost,int c_nPort,CProxyOption * proxy);
	/**
	*	@断开连接.
	*/
	void Disconnect();

	/**
	*	@发送数据.
	*	@param c_pData 需要发送的信息.
	*	@param c_nLen 发送信息的长度.
	*/
	int SendData(char * c_pData,int c_nLen);

	/**
	*	@接收数据.
	*	@param c_pBuf 接收的数据.
	*	@param c_nMaxLen 接受的最大长度.
	*	@param c_hwndNotify 通知窗口的句柄.
	*/
	int RecvData(char * c_pBuf,int c_nMaxLen,HWND c_hwndNotify);




	int HttpRecvData(char * c_pBuf,int c_nMaxLen,HWND c_hwndNotify);
	int SendAndRecv(CString c_strHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption * proxy);
	int SendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption * proxy);
	int HttpSendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption * proxy);
	int HttpSMGSendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption * proxy);
	bool TestConnect(char *,int,CProxyOption * proxy);
	
	/**
	*	@设置保持连接.
	*	@param c_b 是否保持连接标记.
	*/
	inline void SetKeepLive(bool c_b)
	{
		m_bKeepLive = c_b;
	};
public:
	SOCKET m_socket;//套接字
	char m_acHost[256];
	int m_nPort;//端口
	bool m_bKeepLive;//是否保持连接，等待主动断开
	CProxyOption	*m_pProxy;//代理
};
