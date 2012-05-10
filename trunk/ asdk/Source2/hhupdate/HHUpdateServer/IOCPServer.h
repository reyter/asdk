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
	*	@处理客户端请求.
	*	@param lpszFileName 请求的文件路径，含文件名.
	*	@param nFlag 请求标志. RE_TYPE_README.  RE_TYPE_XML.  RE_TYPE_HH.
	*	@param pPerSockData 请求对象.
	**/
	BOOL DealWithRequest(const LPCTSTR lpszFileName,int nFlag, CPerSocketData *pPerSockData,CString strVer);

	/*
	*	@线程函数.
	**/
	static DWORD WINAPI ThreadPoolProc(LPVOID lpParam);

	CPerSocketData *AssignSocketToCompletionPort(SOCKET tSocket);

	/*
	*	@停止服务器
	**/
	void StopServer();
	/*****/
	void GetLastAppVersion(LPCTSTR lpAppid,LPCTSTR lpAppVer);

	/****/
	void MaxVersion(LPCTSTR lpVer1,LPCTSTR lpVer2,LPCTSTR lpVerMax);
	//void OverLapExRemoveAt(COverLappedEx *pOverLaps);
private:
	CWnd *m_pWnd;

	LONG m_lThreadNums;				//线程数量

	SOCKET m_ListenSocket;			//侦听套接字
	HANDLE m_hCompletionPort;		//完成端口句柄

	LSPerSocketData m_LsSocketData;	//保存通讯对象
	LSOverLappedEx m_LsOverLapEx;	//保存通讯数据链表

	CHHTyXml m_hhTyXml;				//处理xml对象
	CHHCompress m_hhCompress;		//处理解压缩对象
	CCriticalSection m_cs;			//临界区对象

	CString m_strErrorMsg;			//错误信息
	//;				//版本
};
