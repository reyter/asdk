/**
* @Copyright 深圳市创真科技有限公司(www.hh.com.cn)
* @System	 (TDBHelper)
* @Brief	 TDB-API函数接口.
* @Author	 何培
* @Date      2010-8-17
* @Usage 
	调用  TDB_CreateHanler 创建一句柄，
	然后  调用  TDB_AddServer 向句柄中加入服务器地址。
	调用  TDB_Begin           开始发起连接和登录。
	调用  TDB_GetStatus       检查连接状态。
	调用  TDB_GetKData		  等从TDB服务器上接收数据。
	---使用数据。
	调用  TDB_Release         释放返回的数据内存(必须，否则会造成内存泄漏)
	调用  TDB_End			  中断与服务器的连接。
	调用  TDB_DestroyHandler  销毁句柄

* @History   
*	wli            2010-10-26             Modify.( 修改代理，修改逐笔成交，增加少量注释 )
*/

#pragma once
#ifndef __TDBAPI_H__
#define __TDBAPI_H__

#ifndef _WINSOCK2API_
#include <winsock2.h>
#endif

#include "HDBApiDefine.h"
//#include "..\\include\\Common\\commlogger.h"


#ifdef _TDBHELPERLIB_
#define TDBAPI(type) _declspec(dllexport) type
#else	
#define TDBAPI(type) _declspec(dllimport) type
#endif


#ifdef __cplusplus
extern "C"
{
#endif


	/**
	*	TDB处理器句柄.
	*/
	typedef void*  HTDB;

	/**
	*	创建一个处理器句柄.
	*	@return 返回所创建的处理器.
	*/
	TDBAPI(HTDB) TDB_CreateHandler();

	/**
	*	销毁一个处理器.
	*	@param handler 要销毁的处理器.
	*/
	TDBAPI(void) TDB_DestroyHandler(HTDB hTdb);

	/**
	*	添加TDB服务器地址.	可以添加多个TDB服务器地址，以实现多服务器支持.
	*	这样，当连接一个服务器失败时，会自动连接到下一服务器。
	*	尝试连接顺序与添加的顺序相同.
	*	@param handler  处理器.
	*	@param chServer 服务器地址，可以是IP，或者域名。
	*   @param nPort	服务器端口.
	*	@param nLevel   服务器连接优先级,nLevel值越大，则越进行优先连接，
	*					可将Level2主服务器的优先级设置大一些,将Level1服务的优先级设置为最低.
	*	@param iProxyType 使用的代理类型<br>	
		<li>0			不使用代理.
		<li>1			SOCK4
		<li>2			SOCK4A
		<li>3			SOCK5
		<li>4			HTTP1.1
	*	@param szProxyHost	代理服务器地址. 
	*   @param iProxyPort	代理服务器端口. 
	*	@param szProxyUser  用户名 无用户名密码时，为零长度字符串"" .
	*	@param szProxyPass	密码. 
	*	@param lpUserName 连接该服务器时，所使用的用户名.
	*	@param lpPassword 连接该服务器时，所使用的密码。
	*	
	*/
	TDBAPI(int) TDB_AddServer(HTDB hTdb,
		LPCSTR lpServer,
		int nPort,				
		int nLevel,				//连接优先级.
		int  iProxyType,		//使用的代理类型.无代理时为零 
		char* szProxyHost,	//代理地址, 无代理时为""
		int  iProxyPort,	//代理端口, 无代理时为0
		char* szProxyUser,	//代理用户名, 无代理时为""
		char* szProxyPass,	//代理密码),无代理时为""
		LPCSTR lpUserName,	//HDB用户名
		LPCSTR lpPassword	//HDB密码
		);

	/**
	*	取处理器的连接状态.
	*	@param handler 处理器.
	*	@param pI64Send  [out]发送字节数
	*	@param pI64Recv  [out]接收字节数
	*	@Return          状态
	*					 0 未连接
	*					 1 连接建立
	*					 2 登陆成功.
	*					 3 当日代码表接收完成.
	*/
	TDBAPI(int)	TDB_GetStatus(HTDB hTdb,
		__int64 *pI64Send,
		__int64 *pI64Recv);

	/**
	*	取对方地址
	*	@param handler 处理器.
	*	@param pPeerAddr [out]如果未连接，返回零。否则对方地址.
	*	@Return  返回是否已经连接

	*/
	TDBAPI(int)	TDB_GetPeerAddr(HTDB hTdb,sockaddr_in *pPeerAddr);



	/**
	*	取对方地址
	*	@param handler 处理器.
	*	@param pszAddr [out]尝试或者正在连接的对方目标地址.
	*	@Return  返回是否已经连接

	*/
	TDBAPI(int)	TDB_GetConnectingAddrString(HTDB hTdb,LPTSTR pszAddr,int nLength);


	/**
	*	开始.
	*	将开始连接数据，并发起请求.
	*	 @param handler  处理器.
	*/
	TDBAPI(int) TDB_Begin(HTDB hTdb);

	/**
	*	主动断开与服务器的连接。主动断开后，不会自动重新连接服务器，
	*   如果需要重新连接，请再次调用<a href="#TDB_Begin">TDB_Begin</a>
	*	 @param handler  处理器.
	*/
	TDBAPI(int) TDB_End(HTDB hTdb);



	/**
	*	检查当前句柄是否含有指定市场的数据.
	*	@param pszMarket 市场."SZ","SH","CF","SP"
	*/
	TDBAPI(int) TDB_BeSupportedMarket(HTDB hTdb,const char *pszMarket);

	/**
	*	获取K线数据.
	*	@param handler  处理器.
	*	@param pRequestKData	请求命令.
	*	@param nItems			返回数据项数.
	*	@param pRetData			返回数据. (处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*	@param dwTimeOut			超时.毫秒，INFINITE 表示一直等待。
	*	@Return					返回处理结果. 0 表示成功，其他为错误码.
	*/
	TDBAPI(int) TDB_GetKData(HTDB hTdb,const HDBDefine_RequestKData *pRequestKData,
		int *pnItems,
		HDBDefine_KData **ppRetData,DWORD dwTimeOut);

	
	/**
	*	获取指数K线数据.
	*	@param handler  处理器.
	*	@param pRequestKData_Index	请求命令.
	*	@param nItems				[out]数据项数.
	*	@param pRetData				[out]返回数据.(处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*	@param dwTimeOut				超时.毫秒，INFINITE 表示一直等待。
	*	@Return						返回处理结果. 0 表示成功，其他为错误码.
	*/
	TDBAPI(int) TDB_GetKDataIndex(HTDB hTdb,const HDBDefine_RequestKData *pRequestKData_Index,
		int *pnItems,
		HDBDefine_KData_Index **ppRetData,DWORD dwTimeOut);

	
	/**
	*	获取Tick数据.
	*	@param handler  处理器.
	*	@param pRequestTickData	请求命令.
	*	@param pnItems			[out]数据项数.
	*	@param pRetData			[out]返回数据.(处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*   @param dwTimeOut			超时. 毫秒，INFINITE 表示一直等待。
	*	@Return					返回处理结果. 0 表示成功，其他为错误码.
	*/
	TDBAPI(int) TDB_GetTickData(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickData,
		int *pnItems,
		HDBDefine_TickData **ppRetData,DWORD dwTimeOut);//Tick
	/**
	*	获取Tick买卖盘数据.
	*	@param handler  处理器.
	*	@param pRequestTickABData	请求命令.
	*	@param pnItems				[out]数据项数.
	*	@param pRetData				[out]返回数据.(处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*   @param dwTimeOut				超时.毫秒，INFINITE 表示一直等待。
	*	@Return 返回处理结果. 0 表示成功，其他为错误码.
	*/
	TDBAPI(int) TDB_GetTickData_AB(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickABData,
		int *pnItems,
		HDBDefine_TickData_AB **ppRetData,DWORD dwTimeOut);//Tick
	/**
	*	获取Tick累计成交量数据.
	*	@param handler  处理器.
	*	@param pRequestTickACCData	请求命令.
	*	@param nItems				[out]数据项数.
	*	@param pRetData				[out]返回数据.(处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*   @param dwTimeOut				超时.超时.毫秒，INFINITE 表示一直等待。
	*	@Return						返回处理结果.0 表示成功，其他为错误码.
	*/
	TDBAPI(int) TDB_GetTickData_ACC(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickACCData,
		int *pnItems,
		HDBDefine_TickData_ACC **ppRetData,DWORD dwTimeOut);//Tick
	/**
	*	获取Tick买卖盘和累计成交量数据.
	*	@param handler  处理器.
	*	@param pRequestTickABACCData	请求命令.
	*	@param pnItems					[out]数据项数.
	*	@param pRetData					[out]返回数据. (处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*   @param dwTimeOut					超时.毫秒，INFINITE 表示一直等待。
	*	@Return 返回处理结果.0 表示成功，其他为错误码.
	*/
	TDBAPI(int) TDB_GetTickData_ABACC(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickABACCData,
		int *pnItems,
		HDBDefine_TickData_AB_ACC **ppRetData,DWORD dwTimeOut);//Tick
	/**
	*	获取Tick指数数据.
	*	@param handler  处理器.
	*	@param pRequestTickData_Index	请求命令.
	*	@param pnItems					[out]数据项数.
	*	@param pRetData					[out]返回数据.(处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*   @param dwTimeOut					超时.毫秒，INFINITE 表示一直等待。
	*	@Return							返回处理结果.0 表示成功，其他为错误码.
	*/
	TDBAPI(int) TDB_GetTickData_Index(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickData_Index,
		int *pnItems,
		HDBDefine_TickData_Index **ppRetData,DWORD dwTimeOut);//Tick
	/**
	*	获取Tick买卖盘数据指数数据.
	*	@param handler  处理器.
	*	@param pRequestTickABData_Index	请求命令.
	*	@param pnItems					[out]数据项数.
	*	@param pRetData					[out]返回数据. (处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*   @param dwTimeOut					超时.
	*	@Return							返回处理结果.
	*/
	TDBAPI(int) TDB_GetTickABData_Index(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickABData_Index,
		int *pnItems,
		HDBDefine_TickData_Index **ppRetData,DWORD dwTimeOut);//Tick
	/**
	*	获取Tick累计成交量指数数据.
	*	@param handler  处理器.
	*	@param pRequestTickACCData_Index	请求命令.
	*	@param pnItems						[out]数据项数.
	*	@param pRetData						[out]返回数据. (处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*   @param dwTimeOut						超时.毫秒，INFINITE 表示一直等待。
	*	@Return								返回处理结果.0 表示成功，其他为错误码.
	*/
	TDBAPI(int) TDB_GetTickACCData_Index(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickACCData_Index,
		int *pnItems,
		HDBDefine_TickData_Index_ACC **ppRetData,DWORD dwTimeOut);//Tick
	/**
	*	获取Tick买卖盘和累计成交量指数数据.
	*	@param handler  处理器.
	*	@param pRequestTickABACCData_Index	请求命令.
	*	@param pnItems						[out]数据项数.
	*	@param pRetData						[out]返回数据. (处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*   @param dwTimeOut						超时.毫秒，INFINITE 表示一直等待。
	*	@Return								返回处理结果.0 表示成功，其他为错误码.
	*/
	TDBAPI(int) TDB_GetTickABACCData_Index(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickABACCData_Index,
		int *pnItems,
		HDBDefine_TickData_Index_ACC **ppRetData,DWORD dwTimeOut);//Tick
	
	
	
	
	
	/**
	*	获取逐笔成交.
	*	@param handler  处理器.
	*	@param pRequestSaveData	请求命令.
	*	@param pnItems			[out]数据项数.
	*	@param pRetData			[out]返回数据. (处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*   @param dwTimeOut			超时.毫秒，INFINITE 表示一直等待。
	*	@Return 返回处理结果.0 表示成功，其他为错误码.
	*/	
	TDBAPI(int) TDB_GetTransaction(HTDB hTdb,const HDBDefine_RequestSaveData *pRequestSaveData,
		int *pnItems,
		HDBDefine_Transaction **ppRetData,DWORD dwTimeOut);
	/**
	*	委托队列数据.
	*	@param handler  处理器.
	*	@param pRequestOrderQueue	请求命令.
	*	@param pnItems			[out]数据项数.
	*	@param pRetData			[out]返回数据. (处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*   @param dwTimeOut			超时.毫秒，INFINITE 表示一直等待。
	*	@Return 返回处理结果.0 表示成功，其他为错误码.
	*/	
	TDBAPI(int) TDB_GetOrderQueue(HTDB hTdb,const HDBDefine_RequestSaveData *pRequestOrderQueue,
		int *pnItems,
		HDBDefine_OrderQueue **ppRetData,DWORD dwTimeOut);
	/**
	*	逐笔委托数据.
	*	@param handler  处理器.
	*	@param pRequestOrder	请求命令.
	*	@param pnItems			[out]数据项数.
	*	@param pRetData			[out]返回数据.(处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*   @param dwTimeOut			超时.毫秒，INFINITE 表示一直等待。
	*	@Return 返回处理结果.0 表示成功，其他为错误码.
	*/	
	TDBAPI(int) TDB_GetOrder(HTDB hTdb,const HDBDefine_RequestSaveData *pRequestOrder,
		int *pnItems,
		HDBDefine_Order **ppRetData,DWORD dwTimeOut);
	
	/**
	*	获取历史行情数据.
	*	@param handler  处理器.
	*	@param pRequestMarketData	请求命令.
	*	@param pnItems				[out]数据项数.
	*	@param pRetData				[out]返回数据. (处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*   @param dwTimeOut				超时.毫秒，INFINITE 表示一直等待。
	*	@Return						返回处理结果.0 表示成功，其他为错误码.
	*/	
	TDBAPI(int) TDB_GetMarketData(HTDB hTdb,const HDBDefine_RequestMarketData *pRequestMarketData,
		int *pnItems,
		HDBDefine_MarketData **ppRetData,DWORD dwTimeOut);
	/**  
	*	获取除权分配方案数据.
	*	@param handler  处理器.
	*	@param pRequestBaseData	请求命令.
	*	@param pnItems			[out]数据项数.
	*	@param pRetData			[out]返回数据. (处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*   @param dwTimeOut			超时.毫秒，INFINITE 表示一直等待。
	*	@Return					返回处理结果.0 表示成功，其他为错误码.
	*/	
	TDBAPI(int) TDB_GetBaseData_FP(HTDB hTdb,const HDBDefine_RequestBaseData *pRequestBaseData,
		int *pnItems,
		HDBDefine_BaseData_FP **ppRetData,DWORD dwTimeOut);
	/**
	*	获取基本信息汇总表数据.
	*	@param handler  处理器.
	*	@param pRequestHZB		请求命令.
	*	@param pnItems			[out]数据项数.
	*	@param pRetData			[out]返回数据.    (处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*   @param dwTimeOut			超时.毫秒，INFINITE 表示一直等待。
	*	@Return					返回处理结果.0 表示成功，其他为错误码.
	*/
	TDBAPI(int) TDB_GetHZB_BaseInfo(HTDB hTdb,const HDBDefine_RequestHZB *pRequestHZB,
		int *pnItems,
		HDBDefine_HZB_BaseInfo **ppRetData,DWORD dwTimeOut);

	/**
	*	获取代码表.
	*	@param handler  处理器.
	*	@param pnItems			[out]数据项数.
	*	@param pRetData			[out]返回数据.    (处理完后 需调用 TDB_Release(*pRetData) 释放内存 )
	*	@Return					返回处理结果.0 表示成功，其他为错误码.
	*
	**/
	TDBAPI(int) TDB_GetCodeTable(HTDB hTdb,int *pnItems,
		HDBDefine_SecurityCode **ppRetData);

	/**
	 *	获取板块信息
	 *	@param	hTdb			[IN]TDB处理器句柄
	 *	@param	ppSectorArr		[OUT]板块信息.
	 *	@param	pnItems			[OUT]记录数目.
	 *	@return 成功返回0,错误返回错误代码.
	 */
	TDBAPI(int) TDB_GetSector(HTDB hTdb,HDBDefine_Sector **ppSectorArr,int *pnItems);

	/**
	 *	获取板块的代码表
	 *	@param	hTdb		[IN]TDB处理器句柄
	 *	@param	pRequest	[IN]请求.  
	 *	@param	ppCodeArr	[OUT]代码表.
	 *	@param	pnItems		[OUT]记录数目.
	 *	@return 成功返回0,错误返回错误代码.
	 */
	TDBAPI(int) TDB_GetSectorCodeTable(HTDB hTdb,HDBDefine_RequestSectorCodeTable *pRequest,HDBDefine_SecurityCode **ppCodeArr,int *pnItems);

	/**
	 *	上传指标
	 *	@param	hTdb		[IN]TDB处理器句柄
	 *	@param	lpszEZFName			指标名称
	 *	@param	lpszEZFContent		指标内容
	 *	@return 成功返回0.
	 */
	TDBAPI(int) TDB_AddEZFormula(HTDB hTdb,LPCTSTR lpszEZFName,LPCTSTR lpszEZFContent);

	/**
	 *	删除指标
	 *	@param	hTdb		[IN]TDB处理器句柄
	 *	@param	lpszEZFName			指标名称
	 *	@return 成功返回0.
	 */
	TDBAPI(int) TDB_DeleteEZFormula(HTDB hTdb,LPCTSTR lpszEZFName);


	/**
	 *	获取服务器上的指标
	 *	?@param	hTdb		[IN]TDB处理器句柄
	 *	@param	lpszEZFName			指标名称(空指针则查找所有)
	 *	@return 成功返回0.
	 */
	TDBAPI(int) TDB_GetEZFormula(HTDB hTdb,LPCTSTR lpszEZFName,HDBDefine_EZFormula_Item **ppEZF,int *pnItems);

	/**
	 *	获取指标计算的结果
	 *	?@param	hTdb			[IN]TDB处理器句柄
	 *	@param	pEZFCalc		要计算的指标的相关信息
	 *	@param	pCalcResult		指标运行的结果 返回数据使用后记得用TDB_ClearEZFResult清理结果
	 *	@return 成功返回0.
	 */
	TDBAPI(int) TDB_GetCalcEZFormulaResult(HTDB hTdb,HDBDefine_EZFormula_Calc *pEZFCalc,HDBDefine_EZFormula_ResultData *pCalcResult);

	/**
	 *	清楚指标数据
	 *	@param	hTdb		[IN]TDB处理器句柄
	 *	@param	pEZFResult 要清除的指标运行结果数据
	 */
	TDBAPI(int) TDB_ClearEZFResult(HTDB hTdb,HDBDefine_EZFormula_ResultData *pEZFResult);

	//////////////////////////////////////////////////////////////////////////
	//事件回调

	/**
	*	TDB中断时回调函数原型.
	*	@return 如果返回TRUE，则API重新登录连接.
	*			如果返回FALSE，API不再进行重新连接.
	*/
	typedef bool (CALLBACK* ON_TDB_DISCONNECT_HANDLER)(HTDB /*hTdb*/);

	/**
	*	TDB登录结果回调函数原型.
	*/
	typedef void (CALLBACK* ON_TDB_LOGINRESULT_HANDLER)(HTDB /*hTdb*/,const HDBDefine_LoginAnswer * /*pAnswer*/);
	
	/**
	*	设置连接中断时的处理函数.
	*	返回之前的中断处理函数.默认中断函数不做任何处理，返回TRUE，以便连接下一服务器.
	*	@param tdfHandler  处理器.
	*	@param pHandler	   中断事件处理器	.
	*/
	TDBAPI(ON_TDB_DISCONNECT_HANDLER)  TDB_SetOnTDBDisconnectHandler(HTDB hTdb,
		ON_TDB_DISCONNECT_HANDLER pHandler);

	/**
	*	设置登录结果的处理函数.
	*	返回之前的登录结果处理函数,系统默认为NULL,不处理.
	*	@param tdfHandler  处理器.
	*	@param pHandler	   登录应答事件处理器	.
	*/
	TDBAPI(ON_TDB_LOGINRESULT_HANDLER)  TDB_SetOnTDBLoginResultHandler(HTDB hTdb,
		ON_TDB_LOGINRESULT_HANDLER pHandler);

	/**
	*	释放内存.
	*	@param pRetData 要释放的内存指针
	*/
	TDBAPI(int) TDB_Release(void *pRetData);


	

	/**
	*	获取最后错误信息.
	*	@param nErrorCode 错误代号.
	*/
	TDBAPI(LPCTSTR) TDB_GetError(int nErrorCode);


	
	/**
	* TDB 日志记录
	*/
	//DECLARE_COMMON_LOG_FUN(TDB,TDBAPI);

	/**
	* 设置日志记录函数.
	*/
	//DECLARE_COMMON_LOG_FUN(TDF,TDFAPI);
	typedef void (CALLBACK* TDB_LOG_FUN)(LPCTSTR,LPVOID);

	/**
	* 设置TDB日志记录
	* @param pFun 日志记录函数
	* @param lParam 回调给日志记录函数的参数
	*/
	TDBAPI(void) TDB_SetLogFun(TDB_LOG_FUN pFun,LPVOID lParam);


#ifdef __cplusplus
}
#endif
#endif //__TDBAPI_H__