#pragma once

//������ܵ��ã������⹫���ĺ���.

#ifndef _ENGFRAMEWORK_H_
#define _ENGFRAMEWORK_H_


#include "..\\include\\TDBAPI\\tdbapihelper.h"
#include "AlgHelper.h"


#ifdef _ENGAPILIB
#define ENGAPI(type)  type __declspec(dllexport) 
#else
#define ENGAPI(type)  type __declspec(dllimport) 
#endif

#ifdef __cplusplus
extern "C"
{
#endif
	
	//���HTB���.
	ENGAPI(void) ENG_FRAMEWORK_AddHTB(HTDB hTtd);

	//ָʾ������ٴ�����.
	typedef int (*DESTORY_TRD_HANDLER_FUN)(HTRD /*htrd*/);

	//����ִ���㷨.
	ENGAPI(int)	 ENG_FRAMEWORK_DoAlgo(
		LPVOID lParam,
		DESTORY_TRD_HANDLER_FUN pfnDestory,
		ATP_Msg_Login* pLogin,
		int nServiceType,
		HTRD	hTrd,
		GUID*   pGuid,
		ATP_Msg_MakeOrderByAlgo_ParamValue* pParamters,
		int nItems,
		LPSTR lpOut,
		int nMaxOutLen);


	



	/**
	* ��ѯ֧��ָ���������͵��㷨.
	* @param nServiceType ��������
	* @param pnItems      ��¼��.
	* @return �����㷨��Ϣ���顣Ҫ��ALG_Release�ͷ�.
	*/
	ENGAPI(int) ENG_FRAMEWORK_QueryRegisteredAlgo(int nServiceType,Atp_Algorithm_Info** pInfo,int* pnItems);


	/**
	* ��ѯ�����㷨.	
	* @param pnItems      ��¼��.
	* @return �����㷨��Ϣ���顣Ҫ��ALG_Release�ͷ�.
	*/
	ENGAPI(int) ENG_FRAMEWORK_QueryAllRegisteredAlgo(Atp_Algorithm_Info** pInfo,int* pnItems);


	/**
	* ��ȡ�㷨����
	*/ 	
	ENGAPI(int)  ENG_FRAMEWORK_GetAlgoParater(int m_nServiceType,GUID* guidAlgo,BYTE** pParaters,int* pnOutLength,ATP_Msg_QueryAlgoParamterInfo_Answer_Head* pAnswerHead);

	/**
	* ��ȡ����������Ϣ.
	*/ 	
	ENGAPI(LPCTSTR) ENG_FRAMEWORK_GetError(int nErrorCode);


	/**
	* ������־��¼Ŀ¼
	* @param lpszLogDir ��־��¼Ŀ¼.
	*/	
	ENGAPI(void)    ENG_FRAMEWORK_SetLogDir(LPCTSTR lpszLogDir);


	/**
	* ������־��¼Ŀ¼
	* @return ��־��¼Ŀ¼.
	*/	
	ENGAPI(LPCTSTR)    ENG_FRAMEWORK_GetLogDir();

	
	/**
	* ���ص�ǰ�������е��㷨��.
	*/ 	
	ENGAPI(int)    ENG_FRAMEWORK_GetCurrentRunAlgoCount();

	
	/**
	* ֪ͨ���㷨����.
	*/ 	
	ENGAPI(int)    ENG_FRAMEWORK_OnKillAlgo(UINT_PTR algoIdentity);

	
	/**
	* ȡ��ǰ�������е��㷨��־.
	*/
	ENGAPI(int)	   ENG_FRAMEWORK_GetAlgoLog(UINT_PTR algoIdentity);



	/**
	* ǿ��ɱ�������������е��㷨��
	* ע��,�÷������ҽ��������˳�ʱʹ��.
	*/
	ENGAPI(int)	ENG_FRAMEWORK_KillAllAlgo();


#ifdef __cplusplus
}
#endif


#endif	//_ENGFRAMEWORK_H_