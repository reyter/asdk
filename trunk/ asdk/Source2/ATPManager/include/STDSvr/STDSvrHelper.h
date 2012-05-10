/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法交易平台帮助协议.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-10-26		李伟		 创建
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
	*	服务处理器句柄.
	*   每一个处理器句柄，对应一个客户SOCKET连接.
	*/
	typedef void*  SVRHANDLER;


	/**
	* 连接句柄.
	*/ 
	typedef void*  CONNHANDLER;			

	
	/**
	*	回调原型，将通知处理对象创建一处理器句柄.
	*	当有Socket连接上时，将调用该函数
	*	@param conn 指示与之关联的连接。
	*	@return     返回一个服务句柄
	*/	
	typedef SVRHANDLER (CALLBACK* CREATE_SVR_HANDLER_FUN)(CONNHANDLER /*conn*/);



	/**
	* 当连接中断时，调用此函数.
	*/
	typedef void (CALLBACK* DESTORY_SVR_HANDLER_FUN)(SVRHANDLER /*handler*/);


	/**
	* 要求通讯协议，必须使用 ATP_MsgHead 头。
	*/
	typedef void (CALLBACK* ON_SVR_RECV_DATA_FUN)(SVRHANDLER /*hHandler*/,const void* /*pData*/,int /*nPacketLength*/);



#pragma pack(push,1)
	/**
	*   服务信息结构.
	*/	
	struct  SVR_HANDLER_INFO
	{
		CREATE_SVR_HANDLER_FUN		 pfunCreate;	//创建函数
		DESTORY_SVR_HANDLER_FUN		 pfunDestory;	//销毁函数
		ON_SVR_RECV_DATA_FUN		 pfunOnRecv;	//接收数据处理函数
	};
#pragma pack(pop)



	/**
	*	中断该连接.
	*	@param hConnHandler 连接句柄，
	*/ 	
	STDSVR(void) STDSVR_Disconnect(CONNHANDLER hConnHandler);


	/**
	*   取对方地址
	*
	*/
	STDSVR(void) STDSVR_GetPeerAddr(CONNHANDLER hConnHandler,sockaddr_in* pPeerAddr);


	/**
	* 用该连接发送数据.
	* @param hConnHandler 连接句柄
	* @param pData        数据起始地址
	* @param nLength      数据长度.
	*/	
	STDSVR(void) STDSVR_SendRawData(CONNHANDLER hConnHandler,const void* pData,int nLength);



	/**
	* 用该连接发送数据.发送完该数据后，断开连接.
	* @param hConnHandler 连接句柄
	* @param pData        数据起始地址
	* @param nLength      数据长度.
	*/	
	STDSVR(void) STDSVR_SendRawDataThenClose(CONNHANDLER hConnHandler,const void* pData,int nLength);


	/**
	* 注册服务.
	* @param nServiceType   服务类型.
	* @param pInfo          服务处理信息.
	*/	
	STDSVR(bool) STDSVR_RegisterService(int nServiceType,const SVR_HANDLER_INFO* pInfo);

	/**
	* 查询
	* @parma ppService     返回已经注册的服务.
	* @param pnItem        服务项.
	*/
	STDSVR(int)  STDSVR_QueryRegisteredService(int** ppService,int* pnItem);


	/**
	*	打开服务
	*	@param lpszServiceName, 服务名称
	*	@param nServiceType 服务类型，该类型必须经过注册.
	*	@param nPort        服务所在的商品
	*/	
	STDSVR(bool) STDSVR_BeginService(LPCTSTR lpszServiceName,int nServiceType,USHORT nPort);


	STDSVR(void) STDSVR_Release(void* pData);


#ifdef __cplusplus
}
#endif


#endif //__STDSVRHELPER_H__
