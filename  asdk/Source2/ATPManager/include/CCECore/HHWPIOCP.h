#pragma once
/**
* �����д���Ƽ����޹�˾����ΰ
*
*/

//IO����
enum IOTYPE
{
	//eIOInit,	//��ʼ��
	eIORead,		//��ȡ���
	eIOWrite,		//�������
	eIOExit,		//�˳�
	eIOSysIdle,		//ϵͳ����.
	eIOSendBufferData,	//֪ͨ���ͻ������е�����.
	eIODeleteThis,		//ɾ�����Ӷ���
	eUserDefine,		//�û��Զ��壬��������������������.

	eIOMAXSYS=100		//ϵͳ����100���µġ�
};


typedef void (CALLBACK* LPUSERCOMMANDFUN)(LPVOID /*lParam*/);

class AFX_EXT_CLASS CHHWPIOCP
{
protected:
	CHHWPIOCP(void);

public:
	virtual ~CHHWPIOCP(void);
	static 	CHHWPIOCP* Init();
	static  void UnInit();

	static UINT    ThreadIOCPFun(LPVOID lParam);			//�ɣϣãй����߳�

	//д��ϵͳ��־��Ϣ
	//static void AppendLog(LPCSTR sMesg);


	//��������.
	static void SendUserRegisterCommand(int nCommand,LPVOID lParam);
	static bool RegisterIOCPUserCommand(int nCommand,LPUSERCOMMANDFUN pFun);

	/**
	* ����һ������ͨ��
	*
	*
	*/
//	BOOL StartListen(CChannel& channel);


    
	/**
	* ��¼��־��Ϣ
	*/
	//virtual void //AppendLog(LPCSTR mesg);

public:

	static CHHWPIOCP* g_pHHWPIOCP;

public:
	HANDLE m_hCompletionPort; //Io Completion Port;

	
};

//ϵͳ��æ��ʱ����øú���.
void OnSysIdle();