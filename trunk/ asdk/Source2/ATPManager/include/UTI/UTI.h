#pragma once

#include "HHCriticalSectionApp.h"
#include "OtherMidDrv.h"
#include "TradingHandler.h"
#include "TradingHandler_Security.h"
#include "TradingHandler_Futures.h"

/**
 证券待处理数据栈.
*/
struct PushStackStru_Security
{
	/**
	证券交易处理类指针.
	*/
	CTradingHandler_Security *pTH_Security;
	/**
	批量标志.
	*/
	BOOL nBatchFlag;
	/**
	批量索引号.
	*/
	int nBatchIndex;
	/**
	批次ID.
	*/
	int nBatchID;

	/**
	压栈时间.
	*/
	time_t nPushTime;
	/**
	压子栈时间.
	*/
	time_t nSubPushTime;

	/**
	请求数据.
	*/
	char *pReqProc;
	/**
	请求数据大小.
	*/
	int nReqProcSize;
};

/**
 期货待处理数据栈.
*/
struct PushStackStru_Futures
{
	/**
	期货交易处理类指针.
	*/
	CTradingHandler_Futures *pTH_Futures;
	/**
	批量标志.
	*/
	BOOL nBatchFlag;
	/**
	批量索引号.
	*/
	int nBatchIndex;
	/**
	批次ID.
	*/
	int nBatchID;

	/**
	压栈时间.
	*/
	time_t nPushTime;
	/**
	压子栈时间.
	*/
	time_t nSubPushTime;

	/**
	请求数据.
	*/
	char *pReqProc;
	/**
	请求数据大小.
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
交易相关配置.
*/
struct _Config_ini
{
	/**
	交易接口类型.
	*/
	int nDllType;
	/**
	交易线程数.
	*/
	int nThreadNum;
	/**
	交易超时时间.
	*/
	int nTimeout;
	/**
	DLL接口路径.
	*/
	char szDllFilePath[MAX_PATH];
	/**
	接口配置路径.
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


