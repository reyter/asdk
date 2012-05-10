#pragma once
class CProxyOption;
class CShortSocket
{
public:
	CShortSocket(void);
	~CShortSocket(void);
public:
	/**
	*	@ʹ�ô�������.
	*	@param proxy ������Ϣ��.
	*/
	SOCKET	ConnectTo(CProxyOption * proxy);
	/**
	*	@���ӵ�.
	*	@param c_pHost
	*	@param c_nPort �˿�.
	*	@param proxy ������Ϣ��.
	*/
	SOCKET	ConnectTo(char * c_pHost,int c_nPort,CProxyOption * proxy);
	/**
	*	@�Ͽ�����.
	*/
	void Disconnect();

	/**
	*	@��������.
	*	@param c_pData ��Ҫ���͵���Ϣ.
	*	@param c_nLen ������Ϣ�ĳ���.
	*/
	int SendData(char * c_pData,int c_nLen);

	/**
	*	@��������.
	*	@param c_pBuf ���յ�����.
	*	@param c_nMaxLen ���ܵ���󳤶�.
	*	@param c_hwndNotify ֪ͨ���ڵľ��.
	*/
	int RecvData(char * c_pBuf,int c_nMaxLen,HWND c_hwndNotify);




	int HttpRecvData(char * c_pBuf,int c_nMaxLen,HWND c_hwndNotify);
	int SendAndRecv(CString c_strHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption * proxy);
	int SendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption * proxy);
	int HttpSendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption * proxy);
	int HttpSMGSendAndRecv(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRecvBuf,int c_nMaxLen,HWND c_hwndNotify,CProxyOption * proxy);
	bool TestConnect(char *,int,CProxyOption * proxy);
	
	/**
	*	@���ñ�������.
	*	@param c_b �Ƿ񱣳����ӱ��.
	*/
	inline void SetKeepLive(bool c_b)
	{
		m_bKeepLive = c_b;
	};
public:
	SOCKET m_socket;//�׽���
	char m_acHost[256];
	int m_nPort;//�˿�
	bool m_bKeepLive;//�Ƿ񱣳����ӣ��ȴ������Ͽ�
	CProxyOption	*m_pProxy;//����
};
