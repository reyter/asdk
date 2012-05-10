/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨����ƽ̨ �㷨��ؽӿ�

			 �㷨��Ҫ���ñ�ͷ�ļ��еĺ������н���. 

* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			 ����         �޸�˵��
2010-10-26	 ��ΰ		 ����
-------------------------------------------------------------
*/

#pragma once



#ifndef _ALGTRDHELPER_H_
#define _ALGTRDHELPER_H_


#include "..\\include\\Protocol\\TDFApiDefine.h"
#include "..\\include\\Protocol\\OpenTDProtocol.h"
#include "..\\include\\TDBAPI\\TDBApiHelper.h"
#include "..\\include\\TDFAPI\\TDFApiHelper.h"
#include "..\\include\\LOGAPI\\LogApiHelper.h"
#include "..\\include\\UTIAPI\\UTIApiHelper.h"





#ifdef _ENGAPILIB
#define ALGAPI(type)  type __declspec(dllexport) 
#else
#define ALGAPI(type)  type __declspec(dllimport) 
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	/**
	*   �㷨������.
	*/

	typedef void*  HALG;


	/**
	*  ��ʵ���㷨�����У���Ҫ�ȶ��㷨�������м�飬����㷨�������Ϸ���
	*  �ú������㷨�б�����á�Ĭ�����㷨��������������Ӧ�����øú��������򣬿����Ϊ��ʱ��������ʱ����.
	*  @param hAlgHandler ����ľ��
	*  @param bPass       �Ƿ�ͨ���㷨���
	*  @param nRet        δͨ��ʱ���˳���
	*  @param szInfo      δͨ��ʱ�������Ϣ.
	*/
	ALGAPI(void) ALG_CheckParamtersResult(HALG hAlgHandler,bool bPass,int nRet,LPCTSTR szInfo);







	typedef void*  HTRD;

	/**
	* ��ȡȫ��TDB���������.
	* @param ppHandlers  ���ؾ�����飬��Ҫ���� ALG_Release ɾ����
	* @param pnHandlers   �������ݸ�����
	*/
	ALGAPI(int)	ALG_GetAllTDBHandler(HTDB** ppHandlers,int* pnHandlers);


	/**
	* ��ȡ ֧��ĳһ���г���TDB���������
	* @param pszMarket �г����룬��"SZ","SH","CF","SP"
	* @return ����TDB���������������������֧�ָ��г���TDB������򷵻�NULL��
	*/
	ALGAPI(HTDB)  ALG_GetTDBHandler(const char* pszMarket);


	/**
	* ��������.
	*/
	enum SNAP_TYPE
	{
		SNAP_TYPE_SEC = 0,	//֤ȯ
		SNAP_TYPE_FUT = 1,	//�ڻ�
		SNAP_TYPE_IND = 2	//ָ��
	};


	/**
	* ����仯�ص�,
	* ALG_SetSnapCallBack ��Ҫ����  ALG_SetSnapCallBack ��������.
	* @param pszMarket �г�
	* @param pszCode   ����
	* @param nSnapType ��������
	* @param pData     �� nSnapTypeΪ SNAP_TYPE_SEC ʱ, ��Ӧ TDFDefine_MarketData ָ��
	*				   �� nSnapTypeΪ SNAP_TYPE_FUT ʱ, ��Ӧ TDFDefine_MarketData_Futures ָ��
	*                  �� nSnapTypeΪ SNAP_TYPE_IND ʱ, ��Ӧ TDFDefine_IndexData ָ�� 
	*				   (����������������Բ�ͬԴ,���������nIdNum��.���г��ʹ���Ϊ׼).
	*/
	//typedef void (CALLBACK* ON_MARKET_SNAP_UPDATE_FUN)(const char* /*pszMarket*/,
	//											const char* /*pszCode*/,
	//											SNAP_TYPE /*nSnapType*/,
	//											const void* /*pData*/);

	//�г����¿��ն���.


	/**
	* ����������ջص�����.
	* @param hAlgHandler		    �㷨������.
	* @param pfunOnSnapUpdate       ������»ص�����.Ҫ���Ч���������ء���Ҫ������
	*/
	//ALGAPI(HTDF)   ALG_SetSnapCallBack(HALG hAlgHandler,
	//	ON_MARKET_SNAP_UPDATE_FUN pfunOnSnapUpdate);



	
	/**
	*	 �� ALG_SetSnapCallBack �ص���,
	*	 ϵͳĬ�ϻص���������г���ȫ��Ʒ�ֵ������������.
	*    Ϊ���Ч�ʣ������ù�ע��Ʒ�֣�����Ʒ�ֵ������򲻽���֪ͨ��	
	*	 @param hAlgHandler  ������.
	*	 @param nSubscriptionType	���ķ�ʽ: 0������  1:����  2:ɾ��  3: ��ԭ.
									(��ε��ã������ԭ���Ķ��Ľ��и���)
	*	 @param pData	�����������ݵ���ʼ��ַ.
	*	 @param nItems	��������.
	*	 @remark  �� nSubscriptionType = 3 ʱ����ȡ��Ϣ���ж��ģ��ָ�Ϊ�ص�����Ʒ��. 
	*/
	/*ALGAPI(void)   ALG_SetSubscription(HALG hAlgHandler,
										int nSubscriptionType,
										TDFDefine_SubscriptionData* pData,
										int nItems);*/
	

	/**
	*    ȡ��Ӧ����־���,�ڸ���־�����д����־���¼���㷨���׷�������.
	*    ���ڴ���־����Ͻ�����־����.
	*	 @param	   hAlgHandler �㷨�Ự���
	*	 @return   ������־������.
	*/
	ALGAPI(HLOG)    ALG_GetLogHandler(HALG hAlgHandler);



	/**
	* ȡָ���Ự�ϵĽ��״�����
	* @param hAlgHandler �㷨�Ự���
	* @parma pnHandlerType [out]ָʾ���׾������, 1 ֤ȯ���׾����2 �ڻ����׾��.
	* @return  ���صľ��,���� pnHandlerType ת��Ϊ  HUTI_SEC ��  HUTI_FUT ʹ��.
	*/
    ALGAPI(HTRD)   ALG_GetTradeHandler(HALG hAlgHandler,int* pnHandlerType);


	/**
	*  ���µ�ǰ�㷨״̬.
	*  ���㷨״̬��Ϣ�����仯ʱ���㷨�ڵ��ô˺����������㷨״̬��
	*  ���������㷨���û������ڷ�������ʱ�������ʹ˸��µ��ͻ��ˡ�
	*  @param hAlgHandler �㷨�Ự���
	*  @param pStatus     �㷨�ĵ�ǰ״̬.	
	*/
	ALGAPI(int)	 ALG_UpdateAlgStatus(HALG hAlgHandler,const ATP_Msg_CurrentAlgoStatus* pStatus);



	/**
	* ����ĳ���㷨�е���Ϣ���ͻ���.
	* @param hAlgHandler   �㷨���.
	* @param nClass        ���
	* @param pszMessage    ������Ϣ�������ַ���������Ϣ.
	*/
	ALGAPI(int) ALG_PushMsg2Client(HALG hAlgHandler,int nClass,LPCSTR pszMessage);

	/**
	* ����ĳ���㷨�е���Ϣ���ͻ���(����������).
	* @param hAlgHandler   �㷨���.
	* @param nClass        ���
	* @param pData		   ���ݵ�ʼ��ַ
	* @param nLength	   ���ݳ���.
	*/	
	ALGAPI(int) ALG_PushData2Client(HALG hAlgHandler,int nClass,const void* pData,int nLength);


	/**
	*  ɾ�� ALG_Xxxx �������صĶ�̬�ڴ�
	*/
	ALGAPI(void) ALG_Release(void* pData);






#ifdef __cplusplus
}
#endif

#endif	//_ALGTRDHELPER_H_