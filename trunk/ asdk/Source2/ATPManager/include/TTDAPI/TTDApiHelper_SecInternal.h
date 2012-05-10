#pragma once
#include "TTDApiHelper_Sec.h"

#ifndef __TTDAPIHELPER_SECINTERNAL_H__
#define __TTDAPIHELPER_SECINTERNAL_H__


#ifdef __cplusplus
extern "C"
{
#endif

/*
 *	获取算法日志的类别
 *	@param	guidAlgo	算法的GUID
 *	@param	ppAns		返回的日志类别结果
 *	@param	pnItems		日志类别数目
 *	@return	错误代码	0表示无错误产生，非零表示有错误，用TTD_SEC_GetError查看错误说明信息
 */
TTDAPI(int) TTD_SEC_GetAlgoLogCategory(GUID guidAlgo,ATP_Msg_Algo_LogCategory **ppAns,int *pnItems);


/**
*	订阅日志
*	@param	guidAlgo	算法的GUID
*	@param	pArr	订阅的类别
*	@param nItems	类别数目
*	@param	pResult	订阅结果
*	@return	错误代码	0表示无错误产生，非零表示有错误，用TTD_SEC_GetError查看错误说明信息
*/
TTDAPI(int) TTD_SEC_SubscribeAlgoLog(GUID guidAlgo,int *pArr,int nItems,ATP_Msg_Algo_LogSubscribe_Result *pResult);

/*
 *	获取算法今天的历史日志
 *	@param	guidAlgo	算法的GUID
 *	@param	ppAns		返回的日志结果
 *	@param	pnItems		日志数目
 *	@return	错误代码	0表示无错误产生，非零表示有错误，用TTD_SEC_GetError查看错误说明信息
 */
TTDAPI(int)	TTD_SEC_GetAlgoTodayLog(GUID guidAlgo,ATP_Msg_AlgoLog **ppAns,int *pnItems);

/*
 *	下载日志文件
 *	@param guidAlgo	算法id
 *	@param nDate	日期
 */
TTDAPI(int) TTD_SEC_GetHistoryLog(GUID guidAlgo,int nDate);

#ifdef __cplusplus
}
#endif


#endif	//__TTDAPIHELPER_SECINTERNAL_H__