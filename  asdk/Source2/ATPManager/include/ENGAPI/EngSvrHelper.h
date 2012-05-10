//�������������ӿ�,д�������ʱ����Ҫʹ��.
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
	* ����¼�ɹ�ʱ����Ҫ��֮���档�����û���¼�ɹ���
	* �����Ƚ��û���Ϣ������Ƿ�����Ϣ��Ҫ���Ÿ��û�.
	* @param pLogin �û���Ϣ.
	* @param lParam ��ʶ���û��ģ�������Ϣ,�����ͨ���˲����ص����֪ͨ.
	*/
	ENGAPI(void) ENG_FRAMEWORK_OnLoginUser(int nServiceType,ATP_Msg_Login* pLogin,LPVOID lParam);


	/**
	* ��ʶ���û��Ĺ�����Ϣ.
	*/ 
	ENGAPI(void) ENG_FRAMEWORK_OnUserDisconnect(int nServiceType,
		ATP_Msg_Login* pLogin,LPVOID lParam);


	/**
	* ֪ͨ�㷨״̬����ԭ��.
	*/ 	
	typedef void (CALLBACK* ENG_SVR_ON_ALGO_STATUS_UPDATE_FUN)(LPVOID /*lParam*/,
		const ATP_Msg_CurrentAlgoStatus* /*pStatus*/);


	/**
	* ֪ͨ�㷨�Ѿ����.
	*/ 	
	typedef void (CALLBACK* ENG_SVR_ON_ALGO_FINISH_FUN)(LPVOID /*lParam*/,
		const ATP_Msg_AlgoFinish* /*pStatus*/);

	/**
	* �������ͻص�.
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
		//Ϊ��־���͡����ӵĻص�����
		ENG_SVR_ON_DATA_OR_MSG_PUSH		  pfnPush;
	};
#pragma pack(pop)
	
	/**
	* ע�����ص�.
	*/	
	ENGAPI(int)  ENG_FRAMEWORK_RegisterSvrCallBack(int nService,
		ENG_SVR_CALLBACK* pCallBack);
	

#ifdef __cplusplus
}
#endif

#endif