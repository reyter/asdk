/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨����ƽ̨����Э��.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-10-26		��ΰ		 ����
-------------------------------------------------------------
*/


#pragma once
#ifndef __STDSVRHELPER_H__
#define __STDSVRHELPER_H__

#include "winsock2.h"


#ifdef _STDSVRLIB_
#define STDSVR(type) _declspec(dllexport) type
#else	
#define STDSVR(type) _declspec(dllimport) type
#endif


#ifdef __cplusplus
extern "C"
{
#endif


	/**
	*	�����������.
	*   ÿһ���������������Ӧһ���ͻ�SOCKET����.
	*/
	typedef void*  SVRHANDLER;


	/**
	* ���Ӿ��.
	*/ 
	typedef void*  CONNHANDLER;			

	
	/**
	*	�ص�ԭ�ͣ���֪ͨ������󴴽�һ���������.
	*	����Socket������ʱ�������øú���
	*	@param conn ָʾ��֮���������ӡ�
	*	@return     ����һ��������
	*/	
	typedef SVRHANDLER (CALLBACK* CREATE_SVR_HANDLER_FUN)(CONNHANDLER /*conn*/);



	/**
	* �������ж�ʱ�����ô˺���.
	*/
	typedef void (CALLBACK* DESTORY_SVR_HANDLER_FUN)(SVRHANDLER /*handler*/);


	/**
	* Ҫ��ͨѶЭ�飬����ʹ�� ATP_MsgHead ͷ��
	*/
	typedef void (CALLBACK* ON_SVR_RECV_DATA_FUN)(SVRHANDLER /*hHandler*/,const void* /*pData*/,int /*nPacketLength*/);



#pragma pack(push,1)
	/**
	*   ������Ϣ�ṹ.
	*/	
	struct  SVR_HANDLER_INFO
	{
		CREATE_SVR_HANDLER_FUN		 pfunCreate;	//��������
		DESTORY_SVR_HANDLER_FUN		 pfunDestory;	//���ٺ���
		ON_SVR_RECV_DATA_FUN		 pfunOnRecv;	//�������ݴ�����
	};
#pragma pack(pop)



	/**
	*	�жϸ�����.
	*	@param hConnHandler ���Ӿ����
	*/ 	
	STDSVR(void) STDSVR_Disconnect(CONNHANDLER hConnHandler);


	/**
	*   ȡ�Է���ַ
	*
	*/
	STDSVR(void) STDSVR_GetPeerAddr(CONNHANDLER hConnHandler,sockaddr_in* pPeerAddr);


	/**
	* �ø����ӷ�������.
	* @param hConnHandler ���Ӿ��
	* @param pData        ������ʼ��ַ
	* @param nLength      ���ݳ���.
	*/	
	STDSVR(void) STDSVR_SendRawData(CONNHANDLER hConnHandler,const void* pData,int nLength);



	/**
	* �ø����ӷ�������.����������ݺ󣬶Ͽ�����.
	* @param hConnHandler ���Ӿ��
	* @param pData        ������ʼ��ַ
	* @param nLength      ���ݳ���.
	*/	
	STDSVR(void) STDSVR_SendRawDataThenClose(CONNHANDLER hConnHandler,const void* pData,int nLength);


	/**
	* ע�����.
	* @param nServiceType   ��������.
	* @param pInfo          ��������Ϣ.
	*/	
	STDSVR(bool) STDSVR_RegisterService(int nServiceType,const SVR_HANDLER_INFO* pInfo);

	/**
	* ��ѯ
	* @parma ppService     �����Ѿ�ע��ķ���.
	* @param pnItem        ������.
	*/
	STDSVR(int)  STDSVR_QueryRegisteredService(int** ppService,int* pnItem);


	/**
	*	�򿪷���
	*	@param lpszServiceName, ��������
	*	@param nServiceType �������ͣ������ͱ��뾭��ע��.
	*	@param nPort        �������ڵ���Ʒ
	*/	
	STDSVR(bool) STDSVR_BeginService(LPCTSTR lpszServiceName,int nServiceType,USHORT nPort);


	STDSVR(void) STDSVR_Release(void* pData);


#ifdef __cplusplus
}
#endif


#endif //__STDSVRHELPER_H__
