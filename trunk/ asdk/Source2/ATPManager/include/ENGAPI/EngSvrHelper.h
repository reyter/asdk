//引擎与网络服务接口,写网络服务时，需要使用.
#pragma once

#ifndef _ENGSVRHELPER_H_
#define _ENGSVRHELPER_H_


#include "..\\include\\protocol\\OpenTDProtocol.h"


#ifdef _ENGAPILIB
#define ENGAPI(type)  type __declspec(dllexport) 
#else
#define ENGAPI(type)  type __declspec(dllimport) 
#endif

#ifdef __cplusplus
extern "C"
{
#endif


	ENGAPI(int) ENG_FRAMEWORK_GetOnesAlgoState(int nServiceType,ATP_Msg_Login* pLogin,ATP_Msg_CurrentAlgoStatus** ppStatus);


	/**
	* 当登录成功时，需要告之引擎。有新用户登录成功。
	* 引擎会比较用户信息，检查是否有信息需要抢着给用户.
	* @param pLogin 用户信息.
	* @param lParam 标识该用户的，关联信息,引擎会通过此参数回调相关通知.
	*/
	ENGAPI(void) ENG_FRAMEWORK_OnLoginUser(int nServiceType,ATP_Msg_Login* pLogin,LPVOID lParam);


	/**
	* 标识该用户的关联信息.
	*/ 
	ENGAPI(void) ENG_FRAMEWORK_OnUserDisconnect(int nServiceType,
		ATP_Msg_Login* pLogin,LPVOID lParam);


	/**
	* 通知算法状态更新原型.
	*/ 	
	typedef void (CALLBACK* ENG_SVR_ON_ALGO_STATUS_UPDATE_FUN)(LPVOID /*lParam*/,
		const ATP_Msg_CurrentAlgoStatus* /*pStatus*/);


	/**
	* 通知算法已经完成.
	*/ 	
	typedef void (CALLBACK* ENG_SVR_ON_ALGO_FINISH_FUN)(LPVOID /*lParam*/,
		const ATP_Msg_AlgoFinish* /*pStatus*/);

	/**
	* 数据推送回调.
	*/
	typedef void (CALLBACK* ENG_SVR_ON_DATA_OR_MSG_PUSH)(
		LPVOID /*lParam*/,
		INT64 /*nSrcIdentity*/,
		int /*nType*/,
		int /*nClass*/,
		const void* /*pData*/,
		int /*nLength*/,
		int /*nDate*/,
		int /*nTime*/,
		int /*nSN*/
		);


#pragma pack(push,1)
	struct ENG_SVR_CALLBACK
	{
		ENG_SVR_ON_ALGO_STATUS_UPDATE_FUN pfnUpdate;
		ENG_SVR_ON_ALGO_FINISH_FUN		  pfnFinish;
		//为日志推送、增加的回调函数
		ENG_SVR_ON_DATA_OR_MSG_PUSH		  pfnPush;
	};
#pragma pack(pop)
	
	/**
	* 注册服务回调.
	*/	
	ENGAPI(int)  ENG_FRAMEWORK_RegisterSvrCallBack(int nService,
		ENG_SVR_CALLBACK* pCallBack);
	

#ifdef __cplusplus
}
#endif

#endif