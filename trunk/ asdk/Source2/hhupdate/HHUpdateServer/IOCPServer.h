#pragma once
#include <afxtempl.h>

#include "OverLappedEx.h"
#include "PerSocketData.h"
#include "..\\include\\HHXml\\HHTyXml.h"
#include "..\include\\Compress\\HHCompress.h"
typedef CList <COverLappedEx *, COverLappedEx *> LSOverLappedEx;
typedef CList <CPerSocketData *, CPerSocketData *> LSPerSocketData;
class CIOCPServer
{
public:
	CIOCPServer(void);
	~CIOCPServer(void);
public:
	void SetLastErrorMsg(CString strErrorMsg);
	CString GetLastErrorMsg();
	BOOL WinSockInit();
	void AssociateWnd(CWnd *pWnd);
	BOOL StartServer(UINT uListenPort);
	BOOL PostAccept(CPerSocketData *pSockData);
	BOOL PostRecv(CPerSocketData *pSockData);
	BOOL PostSend(_tagAnswer *pAnswerBuf, DWORD dwSizeInBytes, CPerSocketData *pPerSockData);
	/*
	*	@����ͻ�������.
	*	@param lpszFileName ������ļ�·�������ļ���.
	*	@param nFlag �����־. RE_TYPE_README.  RE_TYPE_XML.  RE_TYPE_HH.
	*	@param pPerSockData �������.
	**/
	BOOL DealWithRequest(const LPCTSTR lpszFileName,int nFlag, CPerSocketData *pPerSockData,CString strVer);

	/*
	*	@�̺߳���.
	**/
	static DWORD WINAPI ThreadPoolProc(LPVOID lpParam);

	CPerSocketData *AssignSocketToCompletionPort(SOCKET tSocket);

	/*
	*	@ֹͣ������
	**/
	void StopServer();
	/*****/
	void GetLastAppVersion(LPCTSTR lpAppid,LPCTSTR lpAppVer);

	/****/
	void MaxVersion(LPCTSTR lpVer1,LPCTSTR lpVer2,LPCTSTR lpVerMax);
	//void OverLapExRemoveAt(COverLappedEx *pOverLaps);
private:
	CWnd *m_pWnd;

	LONG m_lThreadNums;				//�߳�����

	SOCKET m_ListenSocket;			//�����׽���
	HANDLE m_hCompletionPort;		//��ɶ˿ھ��

	LSPerSocketData m_LsSocketData;	//����ͨѶ����
	LSOverLappedEx m_LsOverLapEx;	//����ͨѶ��������

	CHHTyXml m_hhTyXml;				//����xml����
	CHHCompress m_hhCompress;		//�����ѹ������
	CCriticalSection m_cs;			//�ٽ�������

	CString m_strErrorMsg;			//������Ϣ
	//;				//�汾
};
