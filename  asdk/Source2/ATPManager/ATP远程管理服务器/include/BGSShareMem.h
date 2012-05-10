#ifndef _VIGILDEFINE_HEAD_

#define _VIGILDEFINE_HEAD_


#define ID_SVR_STOPPROCESS		28800	//, OnSvrStopProcess)		//��������
#define ID_SVR_STARTPROCESS		28801	//, OnSvrStartProcess)		//��������
#define ID_SVR_RESTARTPROCESS	28802	//, OnSvrRestartProcess)	//������������
#define ID_SVR_REMOVE			28803	//, OnSvrRemoveItem)
#define ID_SVR_SET				28804	//, OnSvrSet)
#define ID_SVR_OPENFILELOCATION	28805	//, OnSvrOpenFileLocation)
#define ID_SVR_ACTIVEPROCESS	28806	//, OnSvrActiveProcess)

extern char *g_pVigilMem;

struct ATPMainHead
{
	int		nHeadSize;
	int		nDate;
	int		nTime;
	int		nItemSize;
	char	chATPName[32];	//ϵͳ����
	int		nPort;			//�ֲ�ʽ���������˿�
	int		nMainFlag;		//��ϵͳ��־
	int		nMaxItems;
	int		nSvcItems;		//�������
	int		nAlgItems;		//�㷨����
	int     nStartAlgOuttime;
	//�㷨ID����
	int		nAlgIDCount;
	//����Դ��Ϣ
	int		nCPUUsage;
	int		nMemUsage;
	//ͨѶ����
	int		nSendBytes;
	int		nRecvBytes;
	__int64 iTotalSendBytes;
	__int64 iTotalRecvBytes;
	//ATPMain���ھ��
	HWND	hWndATPMain;
#ifdef _M_IX86
	int		nWndATPMainFill;
#endif
};

#define ID_ATPFLAGS_TASKSET			0x00008000	//�����ƻ�����
#define ID_ATPFLAGS_WORKDATE		0x00004000	//������
#define ID_ATPFLAGS_TIMINGSTART		0x00000001	//��ʱ����
#define ID_ATPFLAGS_TIMINGSTOP		0x00000002	//��ʱֹͣ
#define ID_ATPFLAGS_TIMINGRESTART1	0x00000004	//��ʱ����1
#define ID_ATPFLAGS_TIMINGRESTART2	0x00000008	//��ʱ����2
#define ID_ATPFLAGS_VIGILSET		0x80000000	//�����ػ�
#define ID_ATPFLAGS_NORESPONSE		0x00010000	//��������Ӧʱ��������
#define ID_ATPFLAGS_ABNORMAL		0x00020000	//�����쳣ʱ��������

struct ATPMainItem
{
	//������Ϣ
	int	 nServiceClass;	//�������
	int	 nServiceID;	//����ID
	char chService[36];	//��������
	char chExec[128];	//����
	char chAccount[48];	//�˺�
	//�ƻ�����&�ػ�����
	int	 nTaskFlags;	//0x80000000:�����ػ� 0x01:��ʱ���� 0x02:��ʱ���� 0x04:��ʱ����1 0x08:��ʱ����2 0x00004000:�ڹ�����ִ�мƻ����� 0x8000:�����ƻ�����
	int  nStartupTime;	//����ʱ��
	int  nStopTime;		//����ʱ��
	int  nRestartTime1;	//����ʱ��1
	int  nRestartTime2;	//����ʱ��2
	int  nNoresponseCheckTime;	//����Ӧ���ʱ��
	//��������״̬
	char bExecRunning;
	char chRunCount;
	char chServiceRequestRestart; //=='e' ����������������
	char chStartupCheck;	//������������
	char chRunFlags;		//���м�ر�־
	char chDPSStartFlag;	//�ֲ�ʽ������־
	char chResv[2];
	int	 nRestartDate;
	int  nRestartTime;
	int	 nRestartDate1;
	int	 nRestartDate2;
	int  nStatusChangeFlags;
	int  nStatus;
	char chStatus[128];
	int	 nStartTime;		//����ʱ��
	int	 nStartDate;		//��������
	int  nCheckCount;		//����Ӧ������
	int	 nLastTime;			//���ʱ��
	char chLog[128];
	//ͳ����Ϣ///////
	int  nSendDataCount;	//������Ϣ
	int  nRecvDataCount;	//������Ϣ
	int	 nProcessedDataCount;//�Ѵ�����Ϣ
	int  nInfoData[32];
	//////////////////////////////////
	char chServerIP[32];
	int  nServerPort;
	//////////////////////////////////
	DWORD  dwProcessID;		//����ID
	HANDLE hProcess;		//���̾��
#ifdef _M_IX86
	char chHPROCESSFill[4];	
#endif
	__int64 iCurrentCPUUsage;
	__int64 iLastCPUUsage;
	__int64	iStartTick;		//����ʱ��Tick
	int  nCpuUsage;			//CPUʹ����*100
	int  nMemoryUsage;		//�ڴ�ʹ��(KB)
	int  nHandleCount;		//���
	int	 nThreadsCount;		//�߳�
	int  nRefreshTime;		//ˢ�¼��ʱ��
	int  nRefreshCount;		//ˢ�¼���
	HICON hIcon;			//ͼ��
#ifdef _M_IX86
	char chHICONFill[4];	
#endif
	HWND hWndBGS;			//����ͨѶ���ھ��
#ifdef _M_IX86
	char chHWNDFill[4];	
#endif
};


#endif