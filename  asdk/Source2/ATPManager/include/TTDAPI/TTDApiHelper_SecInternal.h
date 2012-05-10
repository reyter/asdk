#pragma once
#include "TTDApiHelper_Sec.h"

#ifndef __TTDAPIHELPER_SECINTERNAL_H__
#define __TTDAPIHELPER_SECINTERNAL_H__


#ifdef __cplusplus
extern "C"
{
#endif

/*
 *	��ȡ�㷨��־�����
 *	@param	guidAlgo	�㷨��GUID
 *	@param	ppAns		���ص���־�����
 *	@param	pnItems		��־�����Ŀ
 *	@return	�������	0��ʾ�޴�������������ʾ�д�����TTD_SEC_GetError�鿴����˵����Ϣ
 */
TTDAPI(int) TTD_SEC_GetAlgoLogCategory(GUID guidAlgo,ATP_Msg_Algo_LogCategory **ppAns,int *pnItems);


/**
*	������־
*	@param	guidAlgo	�㷨��GUID
*	@param	pArr	���ĵ����
*	@param nItems	�����Ŀ
*	@param	pResult	���Ľ��
*	@return	�������	0��ʾ�޴�������������ʾ�д�����TTD_SEC_GetError�鿴����˵����Ϣ
*/
TTDAPI(int) TTD_SEC_SubscribeAlgoLog(GUID guidAlgo,int *pArr,int nItems,ATP_Msg_Algo_LogSubscribe_Result *pResult);

/*
 *	��ȡ�㷨�������ʷ��־
 *	@param	guidAlgo	�㷨��GUID
 *	@param	ppAns		���ص���־���
 *	@param	pnItems		��־��Ŀ
 *	@return	�������	0��ʾ�޴�������������ʾ�д�����TTD_SEC_GetError�鿴����˵����Ϣ
 */
TTDAPI(int)	TTD_SEC_GetAlgoTodayLog(GUID guidAlgo,ATP_Msg_AlgoLog **ppAns,int *pnItems);

/*
 *	������־�ļ�
 *	@param guidAlgo	�㷨id
 *	@param nDate	����
 */
TTDAPI(int) TTD_SEC_GetHistoryLog(GUID guidAlgo,int nDate);

#ifdef __cplusplus
}
#endif


#endif	//__TTDAPIHELPER_SECINTERNAL_H__