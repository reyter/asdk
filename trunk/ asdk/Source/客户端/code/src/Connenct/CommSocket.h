#pragma once
//#include "../Winunit/IUserWin.h"
#include "synch.h"
#include "ProxyOption.h"

#define MAX_RECV_LEN	512 * 1024 * 4
#define MAX_DATA_LEN	512 * 1024 * 4
// CCommSocket 命令目标
struct SReq{
	unsigned short	m_usSeq;//顺序号
	unsigned short	m_usType;//类型
	HWND			m_hwndFrom;//来源窗口
	char		*	m_pReqData;//请求
	int				m_nReqDataLen;//请求长度
};

struct SRep{
	unsigned short	m_usSeq;//顺序号
	unsigned short	m_usType;//类型
	HWND			m_hwndFrom;//来源窗口
	char		*	m_pRepData;//应答数据
	int				m_nRepDataLen;//应答数据长度
};

//int SendFunc(IUserWin * c_pWnd,char * c_pData,int c_nLen,char * c_pRetBuf,int c_nMaxLen,bool c_bWaitReturn=true);

class CData;
class CProxyOption;
class CCommSocket// : public CSocket
{
public:
	CCommSocket();
	virtual ~CCommSocket();
	unsigned short m_usState;//0未连接，1已经连接，-1出错
	// 接收到的总长度
	unsigned int m_uiRecvLen;
	// 收到有效包的长度
	unsigned int m_uiPackLen;
	// 接收数据
	char *m_pRecvBuf;
	//有效包
	char *m_pPackData;
	int  m_nPackLen;
	bool m_bRecving;//正在接收
	int m_iSocketHeart;
	bool ClearSocketHeart();
	bool SetSocketHeart(int);
public:	
	SOCKET m_socket;
	char m_acHost[256];
	int m_nPort;

	unsigned short m_usWaitRecvSeq;
	HANDLE	m_hRecvEvent;//接收数据事件

	LockSingle m_lockSocket;//m_pSocket访问控制锁
	HANDLE m_hThreadRecv;

	CProxyOption *m_pproxyOption;

	SOCKET ConnectTo(CString c_strHost, int c_nPort);
	SOCKET ConnectTo(char * c_pHost, int c_nPort);
	void Disconnect();
	bool RecvDataOld(unsigned short &c_usType);
	bool RecvData(unsigned short &c_usType);
	int SendData(char * c_pBuf,int c_nLen,bool c_bNew=true,char * c_pRetBuf=NULL,int c_nRetBufMaxLen=-1);
};

extern CCommSocket * gpCommSocket;