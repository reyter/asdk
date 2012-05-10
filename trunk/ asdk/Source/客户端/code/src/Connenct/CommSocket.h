#pragma once
//#include "../Winunit/IUserWin.h"
#include "synch.h"
#include "ProxyOption.h"

#define MAX_RECV_LEN	512 * 1024 * 4
#define MAX_DATA_LEN	512 * 1024 * 4
// CCommSocket ����Ŀ��
struct SReq{
	unsigned short	m_usSeq;//˳���
	unsigned short	m_usType;//����
	HWND			m_hwndFrom;//��Դ����
	char		*	m_pReqData;//����
	int				m_nReqDataLen;//���󳤶�
};

struct SRep{
	unsigned short	m_usSeq;//˳���
	unsigned short	m_usType;//����
	HWND			m_hwndFrom;//��Դ����
	char		*	m_pRepData;//Ӧ������
	int				m_nRepDataLen;//Ӧ�����ݳ���
};

//int SendFunc(IUserWin * c_pWnd,char * c_pData,int c_nLen,char * c_pRetBuf,int c_nMaxLen,bool c_bWaitReturn=true);

class CData;
class CProxyOption;
class CCommSocket// : public CSocket
{
public:
	CCommSocket();
	virtual ~CCommSocket();
	unsigned short m_usState;//0δ���ӣ�1�Ѿ����ӣ�-1����
	// ���յ����ܳ���
	unsigned int m_uiRecvLen;
	// �յ���Ч���ĳ���
	unsigned int m_uiPackLen;
	// ��������
	char *m_pRecvBuf;
	//��Ч��
	char *m_pPackData;
	int  m_nPackLen;
	bool m_bRecving;//���ڽ���
	int m_iSocketHeart;
	bool ClearSocketHeart();
	bool SetSocketHeart(int);
public:	
	SOCKET m_socket;
	char m_acHost[256];
	int m_nPort;

	unsigned short m_usWaitRecvSeq;
	HANDLE	m_hRecvEvent;//���������¼�

	LockSingle m_lockSocket;//m_pSocket���ʿ�����
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