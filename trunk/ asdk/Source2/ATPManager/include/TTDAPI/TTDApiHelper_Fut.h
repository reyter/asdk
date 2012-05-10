/**
 *@Copyright 深圳市创真科技有限公司(www.hh.com.cn)
 *@System	 宏汇算法交易平台系统
 *@Brief	 TTD-API
 *@Author	 梁兴其
 *@Date      2010-10-15
*
*	期货交易API.
*	首先调用Begin函数开始网络工作.
*	然后登录服务器.
*	在客户端准备就绪后,可调用TTD_Fut_StartPush启动推送
*	之后可以服务器发送指定的操作请求,服务器返回应答后,
*	库将会调用相应的回调函数.
*	结束时请用TTD_Fut_Release释放由TTD分配的内存,然后用TTD_Fut_End终止TTD的工作..	
*/
#pragma once

#include "../Include/utiapi/utidefine_FUT.h"
#include "../include/Protocol/tdprotocolcommon.h"
#include "../include/Protocol/TDFUTProtocol.h"
#include "../Include/utiapi/utidefine.h"


#ifdef _TTDAPILIB
#define TTDAPI(type)  type __declspec(dllexport) 
#else
#define TTDAPI(type)  type __declspec(dllimport) 
#endif

#ifdef __cplusplus
extern "C"
{
#endif


#ifndef __TTDAPILIB_TYPE_DEFINE__
#define __TTDAPILIB_TYPE_DEFINE__

	/**
	*	网络事件类型.
	*/
	enum TTD_NETEVENT_TYPE
	{
		TTD_NETEVENT_CONNECTED,		//连接上服务器了.
		TTD_NETEVENT_DISCONNECTED	//断开服务器连接了.
	};

	/**
	*	网络事件回调函数原型.
	*	@param	uType	网络事件类型.
	*	@return 返回类型bool,返回false则不会删除连接连接对象。
	*/
	typedef bool (CALLBACK *ON_TTD_NET_EVENT)(TTD_NETEVENT_TYPE uType);

	/**
	 *  接收到来自TDF服务器的数据回调通知函数
	*	@param handler  处理器.
	*	@param pHead 消息头, 消息头中常用的数据成员 sDataType 和 nTime .
	*				 sDataType 指明数据类型，后面的参数，根据sDataType来强制转换为对应的结构.
	*				 nTime     为服务器发出数据的机器时间,格式为 HHMMSSmmm.
	*	@param pApplicationHead  应用头，通常指明后面数据的内容\标识\记录数等。某此消息无此应用头，故此参数可能为NULL.
	*	@param nApplicationHeadSize  应用头长度,可能为零。
	*	@param pData                 解压后的数据的起始位置.数据类型，需根据 pHead 中 sDataType 的值来进行转换.
	*								 具体sDataType后所跟的消息格式，可参见 接口pdf 及 示例代码。
	*	@param nItemSize			 每一条记录的大小。
	*	@param nItems				 记录数	.
	*	
	*	@Remark	一般情况下,pHead后面就是pData,pApplicationHead、nItemSize和nItems并不一定有效
	*	建议根据相关消息的定义,从pHead和pData里读取想要的数据.
	*/
	typedef void (CALLBACK *ON_TTD_RECV_DATA_HANDLER)(
		const ATP_MsgHead * /*pHead*/,
		const void * /*pApplicationHead*/,
		int /*nApplicationHeadSize*/,
		const void * /*pData*/,
		int /*nItemSize*/,
		int /*nItems*/);

	

#endif  //end of __TTDAPILIB_TYPE_DEFINE__

	/**
	*	期货结算单下单结果返回
	*	@param pszTip 以后NULL为结尾的字符串
	*/
	typedef void (CALLBACK *ON_TTD_FUT_RECV_SETTLEMENT)(char *pszTip);

	/**
	设置通讯代理服务器. 
	在调用 <a href="#TTD_FUT_Begin">TTD_FUT_Begin</a>之前调用，
	若不通过代理服务器进行连接，可不调用该函数.
	在调用TTD_FUT_SetServerInfo后代理设置才会生效。

	*	@param iProxyType 使用的代理类型<br>	
	<li>0			不使用代理.
	<li>1			SOCK4
	<li>2			SOCK4A
	<li>3			SOCK5
	<li>4			HTTP1.1
	*	@param szProxyHost	代理服务器地址. 
	*   @param iProxyPort	代理服务器端口 
	*	@param szProxyUser  用户名 无用户名密码时，为零长度字符串"" .
	*	@param szProxyPass	密码. 
	*/
	TTDAPI(int) TTD_FUT_SetProxy( 
		int  iProxyType,		//使用的代理类型.
		char *lpszProxyHost,	//代理地址
		int  iProxyPort,		//代理端口
		char *lpszProxyUser,	//代理用户名
		char *lpszProxyPass		//代理密码)
		);

	/**
	*	设置服务器信息.
	*	@param lpszServer	服务器ip地址.
	*	@param	uPort		服务器端口.
	*/
	TTDAPI(int) TTD_FUT_SetServerInfo(char *lpszServer,UINT uPort);

	/**
	*	设置用户信息.
	*	@param ttdHandler				处理器句柄.
	*	@param lpszUserName				用户名.
	*	@param lpszPassword				密码.
	*	@param lpszSaleDepartmentCode	营业部编号，8字节长度.
	*/
	TTDAPI(int) TTD_FUT_SetUserInfo(char *lpszUserName,char *lpszPassword,char *lpszSaleDepartmentCode);

	/**
	*	网络开始工作.
	*	进行连接服务器,连接成功,可触发连接成功网络事件.
	*/
	TTDAPI(int) TTD_FUT_Begin();

	/**
	*	停止工作.
	*	断开网络连接,可触发断开连接网络事件.
	*/
	TTDAPI(int) TTD_FUT_End();


	/**
	*	是否已经连接上服务器.
	*	@return 已经连上服务器返回true,否则返回false.
	*/
	TTDAPI(bool) TTD_FUT_IsConnect();

	/**
	*	用户是否已经登录进系统.
	*	@return 登录了返回true,否则返回false.
	*/
	TTDAPI(bool) TTD_FUT_IsLogin();

	/**
	*	释放由库自己分配的内存.
	*/
	TTDAPI(int) TTD_FUT_Release(void *pData);

	/**
	*	释放算法参数信息内存
	*/
	TTDAPI(int) TTD_FUT_ReleaseAlgoparam(Atp_Algoparam_Info *pAlgoparam);

	/**
	*	登录.
	*	@param	pAns 返回登录结果.
	*	@return 返回类型为int型,返回系统错误代码,等于零表示无错误产生.
	*/
	TTDAPI(int) TTD_FUT_Login(UTI_FUT_LoginAnswer *pAns);

	/**
	*	启动推送
	*/
	TTDAPI(int) TTD_FUT_StartPush();

	/**
	*	确认期货结算
	*/
	TTDAPI(int) TTD_FUT_SetTlement();

	/**
	*	请求算法信息.
	*	@param	ppArrAns	返回算法的信息,用完后需要用Release函数释放内存.
	*	@param	pnSize	返回结果记录的数目.
	*	@return 返回类型为int型,返回系统错误代码,等于零表示无错误产生.
	*/
	TTDAPI(int) TTD_FUT_GetAlgoInfo(Atp_Algorithm_Info **ppArrAns,int *pnSize);

	/**
	*	请求算法所含参数信息.
	*	@param	pQuery	算法的标识Guid信息.
	*	@param	ppArrAns	返回算法参数的数组,用完后需要用Release函数释放内存.
	*	@param	pnSize	返回结果记录的数目.
	*	@return 返回类型为int型,返回系统错误代码,等于零表示无错误产生.
	*/
	TTDAPI(int) TTD_FUT_GetAlgoParamsInfo(ATP_Msg_QueryAlgoParamterInfo *pQuery,Atp_Algoparam_Info **ppArrAns, int *pnSize);

	/**
	*	获取算法状态信息..
	*	@param	pQuery	算法的标识Guid信息.
	*	@param	ppArrAns	返回算法参数的数组,用完后需要用Release函数释放内存.
	*	@param	pnSize	返回结果记录的数目.
	*	@return 返回类型为int型,返回系统错误代码,等于零表示无错误产生.
	*/
	TTDAPI(int) TTD_FUT_GetAlgoStatus(ATP_Msg_CurrentAlgoStatus **ppArrAns, int *pnSize);

	/**
	*	普通下单.
	*	@param	pArr		下单数组指针.
	*	@param	ppArrAns		存储下单结果信息的数组指针,此块内存需要用户自己分配,内存要能够容纳下nArrSize个体返回结构体.
	*	@param	nArrSize	数组的大小.
	*	@return 返回类型为int型,返回系统错误代码,等于零表示无错误产生.
	*/
	TTDAPI(int) TTD_FUT_GetCommonMakeOrder(const ATP_Msg_Fut_MakeOrder *pArrAsk,ATP_Msg_Fut_MakeOrder_Answer **ppArrAns,int nArrSize);

	/**
	*	算法下单请求.

	*	@param	algoGuid	算法标识Guid,指定要使用的算法.
	*	@param	pArr		算法参数值的数组,顺序要和算法指定的顺序一致.
	*	@param	pAns		存储算法下单结果信息的指针,此块内存需要用户自己分配.
	*	@param	nArrSize	数组的大小.
	*	@return 返回类型为int型,返回系统错误代码,等于零表示无错误产生.
	*/
	TTDAPI(int) TTD_FUT_GetAlgoMakeOrder(
		GUID algoGuid,
		ATP_Msg_Fut_MakeOrderByAlgo_ParamValue *pArr,
		ATP_Msg_Fut_MakeOrderByAlgo_Answer *pAns,int nArrSize
		);

	/**
	*	撤单操作请求.
	*	@param	pArr		委托编号数组.
	*	@param	nArrSize	数组的大小.
	*	@param	ppArrAns		存储算法下单结果信息的数组指针,此块内存需要用户自己分配,内存要能够容纳下nArrSize个体返回结构体.
	*	@return 返回类型为int型,返回系统错误代码,等于零表示无错误产生.
	*/
	TTDAPI(int) TTD_FUT_GetMakeCancelOrder(ATP_Msg_Fut_MakeCancelOrder *pArr,ATP_Msg_Fut_MakeCancelOrder_Answer **pArrAns,int nArrSize);

	/**
	*	终止正在运行的算法.
	*	@param	pQuery 要终止的算法信息.
	*	@return 返回类型为int型,返回系统错误代码,等于零表示无错误产生.
	*/
	TTDAPI(int) TTD_FUT_TerminateAlgos(ATP_Msg_FUT_Run_Algo_Info *pQuery);

	/**
	*	持仓查询请求.
	*	@param	pQuery		可设定股票代码和查询方式.
	*	@param	ppArrAns		返回结果的数组指针,用完后需要用Release函数释放内存.
	*	@param	pnSize		返回结果中记录的数目.
	*	@return 返回类型为int型,返回系统错误代码,等于零表示无错误产生.
	*/
	TTDAPI(int) TTD_FUT_GetHoldPosQuery(
		ATP_Msg_Fut_QueryHoldPositions *pQuery,
		ATP_Msg_Fut_HoldPosition **ppArrAns,
		int *pnSize
		);

	/**
	*	成交查询请求.
	*	@param	query			可设定股票代码和查询方式.
	*	@return 返回类型为int型,返回系统错误代码,等于零表示无错误产生.
	*/
	TTDAPI(int) TTD_FUT_GetMatchQuery(
		ATP_Msg_Fut_QueryMatch *pQuery,
		ATP_Msg_Fut_QueryMatch_Answer **ppArrAns,
		int *pnSize
		);

	/**
	*	委托查询请求.
	*	@param	pQuery		可设定股票代码和查询方式.
	*	@param	ppArrAns		返回结果的数组指针,用完后需要用Release函数释放内存.
	*	@param	pnSize		返回结果中记录的数目.
	*	@return 返回类型为int型,返回系统错误代码,等于零表示无错误产生.
	*/
	TTDAPI(int) TTD_FUT_GetOrderRecordsQuery(
		ATP_Msg_Fut_QueryOrderRecords *pQuery,
		ATP_Msg_Fut_QueryOrderRecords_Answer **ppArrAns,
		int *pnSize
		);

	/**
	*	可撤单查询请求.	
	*	@param	pQuery		可设定股票代码和查询方式.
	*	@param	ppArrAns		返回结果的数组指针,用完后需要用Release函数释放内存.
	*	@param	pnSize		返回结果中记录的数目.
	*	@return 返回类型为int型,返回系统错误代码,等于零表示无错误产生.
	*/
	TTDAPI(int) TTD_FUT_GetCanCancelQuery(
		ATP_Msg_Fut_QueryCanCancel *pQuery,
		ATP_Msg_Fut_QueryCanCancel_Answer **ppArrAns,
		int *pnSize
		);

	/**
	*	资产查询请求.	
	*	@param	pQuery		可设定股票代码和查询方式.
	*	@param	ppArrAns		返回结果的数组指针,用完后需要用Release函数释放内存.
	*	@param	pnSize		返回结果中记录的数目.
	*	@return 返回类型为int型,返回系统错误代码,等于零表示无错误产生.
	*/
	TTDAPI(int) TTD_FUT_GetAssetsQuery(
		ATP_Msg_Fut_QueryAssets *pQuery,
		ATP_Msg_Fut_QueryAssets_Answer **ppArrAns,
		int *pnSize
		);

	/**
	*	最大可成交量查询请求.
	*	@param	pQuery		可设定股票代码和查询方式.
	*	@param	pAns		返回最大成交量的结果,用户自己的内存.
	*	@return 返回类型为int型,返回系统错误代码,等于零表示无错误产生.
	*/
	TTDAPI(int) TTD_FUT_GetMaxVolumeQuery(
		ATP_Msg_Fut_QueryMaxVolume *pQuery,
		ATP_Msg_Fut_QueryMaxVolume_Answer *pAns
		);

	

	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------------------------------------
	//事件.
	//////////////////////////////////////////////////////////////////////////


	/**
	*	设置回调函数.
	*	@param	ttdHandler					处理器句柄,指定要设置的处理器.
	*	@param	pNetEventHandler			网络事件回调函数.
	*	@param	pServerAnsEventHandler		服务器应答事件回调函数.
	*	@return void.
	*/
	TTDAPI(int) TTD_FUT_SetTTDEventHandler(
		ON_TTD_NET_EVENT pNetEventHandler,
		ON_TTD_RECV_DATA_HANDLER pRecvDataHandler
		);
	/**
	*	设置网络事件回调函数.
	*	@param	pNetEventHandler			网络事件回调函数.
	*	@return 返回原来的网络事件回调函数地址.
	*/
	TTDAPI(ON_TTD_NET_EVENT) TTD_FUT_SetTTDNetEventHandler(
		ON_TTD_NET_EVENT pNetEventHandler
		);

	/**
	*	设置服务器应答事件回调函数.
	*	@param	pServerAnsEventHandler		服务器应答事件回调函数.
	*	@return 返回原来的服务器应答事件回调函数地址.
	*/
	TTDAPI(ON_TTD_RECV_DATA_HANDLER) TTD_FUT_SetTTDServerAnsEventHandler(
		ON_TTD_RECV_DATA_HANDLER pRecvDataHandler
		);

	/**
	*	设置接收是否期货结算回调函数.
	*	@param	pRecvFutSetTlementHandler		否期货结算事件回调函数.
	*	@return 返回原来的否期货结算事件回调函数地址.
	*/
// 	TTDAPI(ON_TTD_FUT_RECV_SETTLEMENT) TTD_FUT_SetTTDFutSetTlementHandler(
// 		ON_TTD_FUT_RECV_SETTLEMENT pRecvFutSetTlementHandler
// 		);
	TTDAPI(ON_TTD_FUT_RECV_SETTLEMENT) TTD_FUT_SetTTDFutSetTlementHandler(ON_TTD_FUT_RECV_SETTLEMENT pHandler);

	/**
	*	获取错误字符串.
	*	@param	nErrorCode	错误值.
	*	@return 返回错误说明的字符串.
	*/
	TTDAPI(LPCTSTR) TTD_FUT_GetError(int nErrorCode);
	//compatibilit with c plus plus
#ifdef __cplusplus
}
#endif


/**
*	
*/















