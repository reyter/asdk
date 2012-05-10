#pragma once

#include "HHCriticalSectionApp.h"
#include "OtherMidDrv.h"
#include "TradingHandler.h"
#include "TradingHandler_Security.h"
#include "TradingHandler_Futures.h"

/**
 ֤ȯ����������ջ.
*/
struct PushStackStru_Security
{
	/**
	֤ȯ���״�����ָ��.
	*/
	CTradingHandler_Security *pTH_Security;
	/**
	������־.
	*/
	BOOL nBatchFlag;
	/**
	����������.
	*/
	int nBatchIndex;
	/**
	����ID.
	*/
	int nBatchID;

	/**
	ѹջʱ��.
	*/
	time_t nPushTime;
	/**
	ѹ��ջʱ��.
	*/
	time_t nSubPushTime;

	/**
	��������.
	*/
	char *pReqProc;
	/**
	�������ݴ�С.
	*/
	int nReqProcSize;
};

/**
 �ڻ�����������ջ.
*/
struct PushStackStru_Futures
{
	/**
	�ڻ����״�����ָ��.
	*/
	CTradingHandler_Futures *pTH_Futures;
	/**
	������־.
	*/
	BOOL nBatchFlag;
	/**
	����������.
	*/
	int nBatchIndex;
	/**
	����ID.
	*/
	int nBatchID;

	/**
	ѹջʱ��.
	*/
	time_t nPushTime;
	/**
	ѹ��ջʱ��.
	*/
	time_t nSubPushTime;

	/**
	��������.
	*/
	char *pReqProc;
	/**
	�������ݴ�С.
	*/
	int nReqProcSize;
};

#include "SubTradeThread_Security.h"
#include "TradeThread_Security.h"
#include "SubTradeThread_Futures.h"
#include "TradeThread_Futures.h"

#define MAXPUSHSTACK		2048
#define MAXSUBPUSHSTACK		1600
#define MAXSUBTHREADS		100

extern CRITICAL_SECTION g_csCount_Sec;
extern CRITICAL_SECTION g_csCount_Fut;

/**
�����������.
*/
struct _Config_ini
{
	/**
	���׽ӿ�����.
	*/
	int nDllType;
	/**
	�����߳���.
	*/
	int nThreadNum;
	/**
	���׳�ʱʱ��.
	*/
	int nTimeout;
	/**
	DLL�ӿ�·��.
	*/
	char szDllFilePath[MAX_PATH];
	/**
	�ӿ�����·��.
	*/
	char szIniFilePath[MAX_PATH];

	_Config_ini()
	{
		memset(this, 0 ,sizeof(_Config_ini));
	}
};

extern BOOL LoadTradeDll(COtherMidDrv *pMidDrv, char *szDllFilePath);
extern int InitAllInfo();
extern int ClearAllInfo();

extern _Config_ini Config_ini;

extern COtherMidDrv *g_pMidDrv;

extern PushStackStru_Security *g_pPushStack_Sec;
extern int g_nStackHead_Sec, g_nStackTail_Sec;
extern int PushStack_Security(CTradingHandler_Security *pTH_Security, char *pReqProc, int nReqProcSize, BOOL bBatchFlag, int nBatchIndex, int nBatchID);

extern CSubTradeThread_Security *g_pSubThread_Sec[MAXSUBTHREADS];
extern CTradeThread_Security *g_pTradeThread_Sec;

extern PushStackStru_Futures *g_pPushStack_Fut;
extern int g_nStackHead_Fut, g_nStackTail_Fut;
extern int PushStack_Futures(CTradingHandler_Futures *pTH_Futures, char *pReqProc, int nReqProcSize, BOOL bBatchFlag, int nBatchIndex, int nBatchID);

extern CSubTradeThread_Futures *g_pSubThread_Fut[MAXSUBTHREADS];
extern CTradeThread_Futures *g_pTradeThread_Fut;


