#pragma once

//仅供框架调用，不对外公开的函数.

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
	
	//添加HTB句柄.
	ENGAPI(void) ENG_FRAMEWORK_AddHTB(HTDB hTtd);

	//指示如何销毁处理句柄.
	typedef int (*DESTORY_TRD_HANDLER_FUN)(HTRD /*htrd*/);

	//调用执行算法.
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
	* 查询支持指定服务类型的算法.
	* @param nServiceType 服务类型
	* @param pnItems      记录数.
	* @return 返回算法信息数组。要用ALG_Release释放.
	*/
	ENGAPI(int) ENG_FRAMEWORK_QueryRegisteredAlgo(int nServiceType,Atp_Algorithm_Info** pInfo,int* pnItems);


	/**
	* 查询所有算法.	
	* @param pnItems      记录数.
	* @return 返回算法信息数组。要用ALG_Release释放.
	*/
	ENGAPI(int) ENG_FRAMEWORK_QueryAllRegisteredAlgo(Atp_Algorithm_Info** pInfo,int* pnItems);


	/**
	* 获取算法参数
	*/ 	
	ENGAPI(int)  ENG_FRAMEWORK_GetAlgoParater(int m_nServiceType,GUID* guidAlgo,BYTE** pParaters,int* pnOutLength,ATP_Msg_QueryAlgoParamterInfo_Answer_Head* pAnswerHead);

	/**
	* 获取错误描述信息.
	*/ 	
	ENGAPI(LPCTSTR) ENG_FRAMEWORK_GetError(int nErrorCode);


	/**
	* 设置日志记录目录
	* @param lpszLogDir 日志记录目录.
	*/	
	ENGAPI(void)    ENG_FRAMEWORK_SetLogDir(LPCTSTR lpszLogDir);


	/**
	* 设置日志记录目录
	* @return 日志记录目录.
	*/	
	ENGAPI(LPCTSTR)    ENG_FRAMEWORK_GetLogDir();

	
	/**
	* 返回当前正在运行的算法数.
	*/ 	
	ENGAPI(int)    ENG_FRAMEWORK_GetCurrentRunAlgoCount();

	
	/**
	* 通知让算法结束.
	*/ 	
	ENGAPI(int)    ENG_FRAMEWORK_OnKillAlgo(UINT_PTR algoIdentity);

	
	/**
	* 取当前正在运行的算法日志.
	*/
	ENGAPI(int)	   ENG_FRAMEWORK_GetAlgoLog(UINT_PTR algoIdentity);



	/**
	* 强行杀死所有正在运行的算法。
	* 注意,该方法当且仅当程序退出时使用.
	*/
	ENGAPI(int)	ENG_FRAMEWORK_KillAllAlgo();


#ifdef __cplusplus
}
#endif


#endif	//_ENGFRAMEWORK_H_