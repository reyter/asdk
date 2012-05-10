/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法交易平台 算法相关接口

			 算法需要调用本头文件中的函数进行交易. 

* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			 作者         修改说明
2010-10-26	 李伟		 创建
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
	*   算法处理句柄.
	*/

	typedef void*  HALG;


	/**
	*  在实现算法函数中，需要先对算法参数进行检查，如果算法参数不合法。
	*  该函数在算法中必须调用。默认在算法启动后两分钟内应当调用该函数，否则，框架认为超时。将作超时处理.
	*  @param hAlgHandler 传入的句柄
	*  @param bPass       是否通过算法检查
	*  @param nRet        未通过时的退出码
	*  @param szInfo      未通过时的相关信息.
	*/
	ALGAPI(void) ALG_CheckParamtersResult(HALG hAlgHandler,bool bPass,int nRet,LPCTSTR szInfo);







	typedef void*  HTRD;

	/**
	* 获取全部TDB处理器句柄.
	* @param ppHandlers  返回句柄数组，需要调用 ALG_Release 删除。
	* @param pnHandlers   返回数据个数。
	*/
	ALGAPI(int)	ALG_GetAllTDBHandler(HTDB** ppHandlers,int* pnHandlers);


	/**
	* 获取 支持某一个市场的TDB处理器句柄
	* @param pszMarket 市场代码，如"SZ","SH","CF","SP"
	* @return 返回TDB处理句柄，如果服务器上无支持该市场的TDB句柄，则返回NULL。
	*/
	ALGAPI(HTDB)  ALG_GetTDBHandler(const char* pszMarket);


	/**
	* 快照类型.
	*/
	enum SNAP_TYPE
	{
		SNAP_TYPE_SEC = 0,	//证券
		SNAP_TYPE_FUT = 1,	//期货
		SNAP_TYPE_IND = 2	//指数
	};


	/**
	* 行情变化回调,
	* ALG_SetSnapCallBack 需要调用  ALG_SetSnapCallBack 后起作用.
	* @param pszMarket 市场
	* @param pszCode   代码
	* @param nSnapType 快照类型
	* @param pData     当 nSnapType为 SNAP_TYPE_SEC 时, 对应 TDFDefine_MarketData 指针
	*				   当 nSnapType为 SNAP_TYPE_FUT 时, 对应 TDFDefine_MarketData_Futures 指针
	*                  当 nSnapType为 SNAP_TYPE_IND 时, 对应 TDFDefine_IndexData 指针 
	*				   (由于最新行情可来自不同源,请忽略其中nIdNum项.以市场和代码为准).
	*/
	//typedef void (CALLBACK* ON_MARKET_SNAP_UPDATE_FUN)(const char* /*pszMarket*/,
	//											const char* /*pszCode*/,
	//											SNAP_TYPE /*nSnapType*/,
	//											const void* /*pData*/);

	//市场最新快照订阅.


	/**
	* 设置行情快照回调处理.
	* @param hAlgHandler		    算法处理句柄.
	* @param pfunOnSnapUpdate       行情更新回调函数.要求高效，立即返回。不要阻塞。
	*/
	//ALGAPI(HTDF)   ALG_SetSnapCallBack(HALG hAlgHandler,
	//	ON_MARKET_SNAP_UPDATE_FUN pfunOnSnapUpdate);



	
	/**
	*	 在 ALG_SetSnapCallBack 回调后,
	*	 系统默认回调所请求的市场的全部品种的数据行情更新.
	*    为提高效率，可设置关注的品种，其他品种的行情则不进行通知。	
	*	 @param hAlgHandler  处理器.
	*	 @param nSubscriptionType	订阅方式: 0：设置  1:增加  2:删除  3: 还原.
									(多次调用，会基于原来的订阅进行更改)
	*	 @param pData	待操作的数据的起始地址.
	*	 @param nItems	数据项数.
	*	 @remark  当 nSubscriptionType = 3 时，会取消息所有订阅，恢复为回调所有品种. 
	*/
	/*ALGAPI(void)   ALG_SetSubscription(HALG hAlgHandler,
										int nSubscriptionType,
										TDFDefine_SubscriptionData* pData,
										int nItems);*/
	

	/**
	*    取对应的日志句柄,在该日志句柄上写的日志会记录在算法交易服务器上.
	*    可在此日志句柄上进行日志操作.
	*	 @param	   hAlgHandler 算法会话句柄
	*	 @return   返回日志处理句柄.
	*/
	ALGAPI(HLOG)    ALG_GetLogHandler(HALG hAlgHandler);



	/**
	* 取指定会话上的交易处理句柄
	* @param hAlgHandler 算法会话句柄
	* @parma pnHandlerType [out]指示交易句柄类型, 1 证券交易句柄，2 期货交易句柄.
	* @return  返回的句柄,根据 pnHandlerType 转换为  HUTI_SEC 或  HUTI_FUT 使用.
	*/
    ALGAPI(HTRD)   ALG_GetTradeHandler(HALG hAlgHandler,int* pnHandlerType);


	/**
	*  更新当前算法状态.
	*  当算法状态信息发生变化时，算法内调用此函数，更新算法状态。
	*  若启动该算法的用户连接在服务器上时，会推送此更新到客户端。
	*  @param hAlgHandler 算法会话句柄
	*  @param pStatus     算法的当前状态.	
	*/
	ALGAPI(int)	 ALG_UpdateAlgStatus(HALG hAlgHandler,const ATP_Msg_CurrentAlgoStatus* pStatus);



	/**
	* 推送某个算法中的消息到客户端.
	* @param hAlgHandler   算法句柄.
	* @param nClass        类别
	* @param pszMessage    推送消息、以零字符结束的消息.
	*/
	ALGAPI(int) ALG_PushMsg2Client(HALG hAlgHandler,int nClass,LPCSTR pszMessage);

	/**
	* 推送某个算法中的消息到客户端(二进制数据).
	* @param hAlgHandler   算法句柄.
	* @param nClass        类别
	* @param pData		   数据地始地址
	* @param nLength	   数据长度.
	*/	
	ALGAPI(int) ALG_PushData2Client(HALG hAlgHandler,int nClass,const void* pData,int nLength);


	/**
	*  删除 ALG_Xxxx 函数返回的动态内存
	*/
	ALGAPI(void) ALG_Release(void* pData);






#ifdef __cplusplus
}
#endif

#endif	//_ALGTRDHELPER_H_