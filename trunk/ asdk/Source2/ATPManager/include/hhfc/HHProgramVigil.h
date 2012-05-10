#pragma once
#include "psapi.h"
#define ID_VIGILLOGFLAGS_ALARM		0x80000000	//����
#define ID_VIGILLOGFLAGS_ALARMSTOP  0x40000000	//�������

class AFX_EXT_CLASS CHHProgramVigil
{
public:
	/**
	* ������ؽ���
	* @param szVigilExec [in] ִ���ļ�����, �Ѿ�����������ΪNULL
	* @param nCheckTime	 [in] ����������Ӧ�ļ��ʱ��(��)��-1:�����
	* @return 1:�ɹ�
	*/
	static BOOL StartVigilProcess(LPCSTR szVigilExec, int nCheckTime=-1);

	/**
	* ������ؽ���
	* @param szVigilExec [in] ִ���ļ�����, �Ѿ�����������ΪNULL
	* @return 1:�ɹ�
	*/
	static BOOL StopVigilProcess(LPCSTR szVigilExec);

	/**
	* ���ü�ؽ�����Ϣ(֪ͨ������������), ��������˽�������Ӧ���ʱ�䣬�ͱ����ڼ��ʱ������ô˺���
	* @param szVigilExec [in] ִ���ļ�����, �Ѿ�����������ΪNULL
	* @return 1:�ɹ�
	*/
	static BOOL SetVigilProcessOK(LPCSTR szVigilExec);

	/**
	* ���ü�ؽ���ʱ��(�����ϴμ��ʱ��)
	* @param szVigilExec [in] ִ���ļ�����, �Ѿ�����������ΪNULL
	* @param nCheckTime	 [in] ����������Ӧ�ļ��ʱ��(��)��-1:�����
	* @return 1:�ɹ�
	*/
	static int  SetVigilProcessCheckTime(LPCSTR szVigilExec, int nCheckTime);

public:
	/**
	* ��ȡ������Ϣ
	* @param szPathFile [in] ִ���ļ�����
	* @param pMemInfo	[out] �ڴ���Ϣ
	* @param dwProcessID[out] ����ID
	* @return 1:�ɹ�
	*/
	static BOOL GetProcessMemoryInfo(LPCSTR szPathFile,PPROCESS_MEMORY_COUNTERS pMemInfo,DWORD& dwProcessID);

	/**
	* ����ָ����ִ���ļ��Ľ���
	* @param szPathFile [in] ִ���ļ�����
	* @return 1:�ɹ�
	*/
	static BOOL KillProcess(LPCSTR szPathFile);

	/**
	* ��������
	* @param szPathFile [in] ִ���ļ�����
	* @return 1:�ɹ�
	*/
	static BOOL StartProcess(LPCSTR szPathFile);

	/**
	* ���ü�ؽ��̵ĸ�����Ϣ
	* @param nType  [in] ��Ϣ����
	* @param pInfo	[in] ��Ϣ����
	* @param nSize	[in] ��Ϣ���ݳ���
	* @return 1:�ɹ�
	*/
	static BOOL SetVigilProcessData(int nType, char *pInfo, int nSize);

	/**
	* ��ȡ��ؽ��̵ĸ�����Ϣ
	* @param nIndex  [in] ��Ϣ����
	* @param nType	 [in] ��Ϣ����
	* @param pchExecFile [out] ִ���ļ�
	* @param pInfo	 [out] ��Ϣ����
	* @param nSize	 [out] ��Ϣ���ݳ���
	* @param nRunningFlag [out] �������б�־
	*/
	static int GetVigilProcessData(int nIndex, int nType, char *pchExecFile, char *pInfo, int &nSize, int &nRunningFlag);
	
	/**
	* ��ȡ��ؽ��̵���Ϣ
	* @param nIndex [in] ��Ϣ����
	* @param nType	[in] ��Ϣ����
	* @param pInfo	[out] ��Ϣ����
	* @param nSize	[out] ��Ϣ���ݳ���
	*/
	static int GetVigilProcessInfo(int nIndex, int nType, char *pInfo, int &nSize);
	
	/**
	* ��ȡ�ػ���־(nIDΪ��־��¼Ψһʶ���, ˳������, �������ֵΪ-1��ʾ��־�Ѿ�����, nID=-1ʱ��ȡ���һ����־)
	* @param nID [in] ��־��¼Ψһʶ���,nID=-1ʱ��ȡ���һ����־
	* @param pLog [out] ��־����
	* @param nSize [out] ��־���ݳ���
	*/
	static int GetVigilLog(int nID, char *pLog, int &nSize);
	
	/**
	* ����Ӧ�ó����������
	* @param nAppType	[in] Ӧ����������
	* @param nAppDate	[in] ���ݸ������� yyyymmdd
	* @param nAppTime	[in] ���ݸ���ʱ�� hhmmss
	*/
	static BOOL SetVigilProcessAppUpdateTime(int nAppType, int nAppDate, int nAppTime);

	/**
	* ����Ӧ�ó���״̬
	* @param nStatus	[in] ״̬
	* @param pchStatus	[in] ״̬��Ϣ
	*/
	static BOOL SetVigilProcessAppStatus(int nStatus, char *pchStatus);
	
	/**
	* ����Ӧ�ó���������Ϣ
	* @param pchMessage [in] ��Ϣ
	* @return 1:�ɹ�
	*/
	static BOOL SetVigilProcessTxtMessage(char *pchMessage);
	
	//2010.11.18����ͨѶ�˿���Ϣ
	static int SetVigilPortInfo(int nLocalPort, int  nRemotePort, int nRemoteIP, char *pchAccount, char *pchStatus=NULL, char *pchInfo1=NULL, char *pchInfo2=NULL);
	static int SetVigilPortInfo(int nLocalPort, int  nRemotePort, int nRemoteIP, char *pchAccount, int  nAppType ,int  nAppDate, int  nAppTime);
	static int RemoveVigilPortInfo(int nLocalPort, int  nRemotePort, int nRemoteIP);
	static int RemoveAllVigilPortInfo();
	

	/**
	* ����Ӧ�ó�����־��Ϣ(2011.5.24������־����)
	* @param nLogFlags	[in] ��־��־, �μ� ID_VIGILLOGFLAGS_ ����
	* @param pLog		[in] ��־����
	* @param nLogSize	[in] ��־���ݳ���(����<128)
	* @return �ɹ�:��־��¼��  ʧ��:0:�ػ�����û������
	*/
	static int SetVigilProcessLog(int nLogFlags, char *pLog, int nLogSize);
	
	/**
	* HHFC�ڲ�ʹ�ú���
	*/
	static char *GetVigilPortInfo(int &nItems, int &nItemSize);
public:
	CHHProgramVigil(void);
	~CHHProgramVigil(void);
};
