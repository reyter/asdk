#pragma once

//�������Ͷ���
#define ID_ATPSVC_MAIN		0	//ϵͳ������		ATPMain.exe
#define ID_ATPSVC_MANAGER	1	//ϵͳ�������	ATPManager.exe
#define ID_ATPSVC_ACCEPT	2	//�û��������	ATPAccept.exe
#define ID_ATPSVC_UTI		3	//����׷���	ATPUTI.exe
#define ID_ATPSVC_TDF		4	//TDF���ݷ���	ATPTDF.exe
#define ID_ATPSVC_TDB		5	//TDB���ݷ���	ATPTDF.exe
#define ID_ATPSVC_MC		6	//ϵͳ��ط���	ATPMC.exe
#define ID_ATPSVC_ALG		8	//�㷨			ATPALG.exe
#define ID_ATPSVC_DPS		9	//�ֲ�ʽ�㷨����	ATPDPSMain.exe

//���׷���ID
#define ID_ATPUTI_CNSE		0	//����֤ȯ���׷���
#define ID_ATPUTI_CNIF		1	//��ָ�ڻ����׷���
#define ID_ATPUTI_CNFU		2	//��Ʒ�ڻ����׷���

//ͨѶ��Ϣ
#define ID_APTSTAT_SENDPACKETS		0	//���̷������ݰ�����
#define ID_APTSTAT_SENDBYTES		1	//���̷��������ֽ�
#define ID_APTSTAT_RECVPACKETS		2	//���̽������ݰ�����
#define ID_APTSTAT_RECVBYTES		3	//���̽��������ֽ�

//������Ϣͳ��
#define ID_ATPSTAT_UTI_BUY			10	//����
#define ID_ATPSTAT_UTI_SALE			11	//����
#define ID_ATPSTAT_UTI_CANCEL		12	//����
#define ID_ATPSTAT_UTI_MATCH		13	//�ɽ���ѯ
#define ID_ATPSTAT_UTI_ORDER		14	//ί�в�ѯ
#define ID_ATPSTAT_UTI_CANCANCEL	15	//�ɳ�����ѯ
#define ID_ATPSTAT_UTI_CAPITAL		16	//�ʽ��ѯ
#define ID_ATPSTAT_UTI_OTHER		17	//������ѯ

// CWndBGSManager
#define ID_HHFCBGSACTIVEAPP (WM_USER+96)		//���ǰ����ʾ
#define ID_HHFCBGSKILLAPP	(WM_USER+97)		//�ֶ���������ǰ����Ϣ֪ͨ

#define ID_HHFCBGSDATA	  (WM_USER+98)
#define ID_HHFCBGSMESSAGE (WM_USER+99)

class AFX_EXT_CLASS CWndBGSManager : public CWnd
{
public:
	/**
	* ��ʼ��BGS����
	* @param nServiceClass	[in] ��������
	* @param nServiceID		[in] ����ID
	* @return 0�������ɹ�
	*	m_pWndGBS = new CWndBGS;
	*	int i = m_pWndGBS->Create(6, 0, this);
	*	if(i<0)
	*	{
	*		CString str;
	*		str.Format("%d", i);
	*		MessageBox("����ʧ��!", str);
	*		exit(-1);
	*	}
	*/
	LRESULT Create(int nServiceClass, int nServiceID, CWnd *pWndParent);

	/**
	* ��ָ������������
	* @param nServiceClass	[in] ��������
	* @param nServiceID		[in] ����ID
	* @param lParam			[in] ����
	* @param pData			[in] ����ָ��
	* @param nLen			[in] ���ݳ���
	* @return ���ͳ���
	*/
	int SendData(int nServiceClass, int nServiceID, int nID, void *pData, int nLen);

	/**
	* ���շ������ݣ����º�����
	* @param nServiceClass	[in] ��������
	* @param nServiceID		[in] ����ID
	* @param lParam			[in] ����
	* @param pData			[in] ����ָ��
	* @param nLen			[in] ���ݳ���
	* @param bDel			[out] �Ƿ���ϵͳɾ��pData, ȱʡΪTRUE, ���Ӧ�ó�����Ҫ����pDataֱ��ʹ�þͽ�bDel=FALSE 
	*/
	virtual int OnRecvData(int nServiceClass, int nServiceID, int nID, void *pData, int nLen, BOOL &bDel);

	/**
	* ������Ϣ����
	* @param nID	[in] ��ϢID (0-32)
	* @param nData	[in] ͳ������
	* @return >=0 �ɹ�
	*/
	int SetInfoData(int nInfoID, int nData);

	/**
	* ���ü��״̬��Ϣ
	* @param pchStatus [in] ״̬�ı�
	* @return >=0 �ɹ�
	*/
	int SetStatusInfo(char *pchStatus);

	/**
	* ���ü����־��Ϣ
	* @param pchLog [in] ��־�ı�
	* @return >=0 �ɹ�
	*/
	int SetLogInfo(char *pchLog);

	/**
	* ����MD5��
	* @param pData [in] Դ����
	* @param nLen  [in] ����
	* @return MD5��
	*/
	static CString GetMD5(char *pData, int nLen);

	/**
	* ��ȡ����������
	*/
	int GetServiceClass();

	/**
	* ��ȡ������ID
	*/
	int GetServiceID();

	/**
	* �����ڲ�����BGS�������м���־��֪ͨ��������������
	* @param nCheckTime [in] �ڲ����ü���־ʱ��(s)
	*/
	void EnableInternalBGSCheckFlag(int nCheckTime);

	/**
	* ����BGS�������м���־��֪ͨ��������������
	*/
	int SetBGSCheckFlag();

	/**
	* ��ȡATP����
	* @param char *pchATPName [out] ����(��󳤶�32)
	*/
	void GetATPName(char *pchName);


	DECLARE_DYNCREATE(CWndBGSManager)

public:
	CWndBGSManager();
	virtual ~CWndBGSManager();

protected:
	DECLARE_MESSAGE_MAP()

	LRESULT OnHHFCBGSMessage(WPARAM wParam, LPARAM lParam);
	LRESULT OnHHFCBGSData(WPARAM wParam, LPARAM lParam);
	int m_nServiceClass;
	int m_nServiceID;
	HANDLE m_hBGSHandle;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


