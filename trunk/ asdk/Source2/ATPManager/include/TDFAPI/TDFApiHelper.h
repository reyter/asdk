/**
* @Copyright 深圳市创真科技有限公司(www.hh.com.cn)
* @System	 宏汇TDF系统(Transend Data Feed System)
* @Brief	 宏汇行情快递系统API函数接口.
* @Author	 何培 梁兴其
* @Date      2010-10-8
*
*	支持多句柄同时连接、多服务器地址。
* 使用方法, 
*   首先，调用 TDF_CreateHandler 创建句柄。
*   然后，调用 TDF_AddServer    向其中设置服务器连接信息.
*   根据需要  TDF_SetRequestDate，TDF_SetRequestMarkets,
*   调用 TDF_SetOnTDFRecvDataHandler 设置回调事件处理函数 ，
*	调用 TDF_SaveSnapshot 指示是否要保存快照
*	调用 TDF_Begin 开始
*	API 调用回调，通知数据到达。
*	调用 TDF_End 结束
*	调用 TDF_DestroyHandler 销毁句柄，释放资源.
*/
#pragma once

#ifndef _TDFAPIHELPER_H_
#define _TDFAPIHELPER_H_

#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif

#include "TDFApiDefine.h"
//#include "..\\Include\\Common\\CommLogger.h"


#ifdef _TDFAPILIB
#define TDFAPI(type)  type __declspec(dllexport) 
#else
#define TDFAPI(type)  type __declspec(dllimport) 
#endif

#ifdef __cplusplus
extern "C"
{
#endif



#pragma pack(push,1)

struct TDF_API_ReqMarkets
{
	/**
	*	要请求的市场，如"SZ","SH","CF"等.
	*/ 
	char chMarket[4];

	/**
	*   请求的市场标志,可以是下列数据的组合.(系统默认会以压缩方式传送)
	*   ID_HDFDATAFLAGS_RETRANSALTE		 数据从头传送（即从所请求交易日开市前传送，否则从最新时点传送数据.）
	*	ID_HDFDATAFLAGS_NOTRANSACTION    不传送逐笔成交数据
	*   ID_HDFDATAFLAGS_NOABQUEUE        不传送委托队列数据
	*	ID_HDFDATAFLAGS_NOINDEX          不传送指数数据
	*/
	DWORD dwFlag;
};

/**
*	获取批量行情结构体.
*/
typedef struct tagTDF_GetBacthMarketData
{
	/**
	*	要请求的市场，如"SZ","SH","CF"等.
	*/ 
	char szMarket[4];
	/**
	*	代码,如:600000.
	*/ 
	char szCode[8];

	/**
	*	行情数据.返回到这里.
	*/
	TDFDefine_MarketData marketData;

	/**
	* 错误代码,成功为0;
	*/
	int nError;
}TDF_GetBacthMarketData;

/**
*	获取批量股指期货行情结构体.
*/
typedef struct tagTDF_GetBacthMarketDataFutures
{
	/**
	*	要请求的市场，如"SZ","SH","CF"等.
	*/ 
	char szMarket[4];
	/**
	*	代码,如:600000.
	*/ 
	char szCode[8];

	/**
	*	行情数据.返回到这里.
	*/
	TDFDefine_MarketData_Futures marketData;

	/**
	* 错误代码,成功为0;
	*/
	int nError;
}TDF_GetBacthMarketDataFutures;

/**
*	获取批量指数行情结构体.
*/
typedef struct tagTDF_GetBacthMarketDataIndex
{
	/**
	*	要请求的市场，如"SZ","SH","CF"等.
	*/ 
	char szMarket[4];
	/**
	*	代码,如:600000.
	*/ 
	char szCode[8];

	/**
	*	行情数据.返回到这里.
	*/
	TDFDefine_IndexData marketData;

	/**
	* 错误代码,成功为0;
	*/
	int nError;
}TDF_GetBacthMarketDataIndex;

#pragma pack(pop)


/**
*	TDF处理器句柄.
*/
typedef void*  HTDF;

/**
*	创建一个处理器句柄.
*	@return 返回所创建的处理器.
*/
TDFAPI(HTDF) TDF_CreateHandler();

/**
*	销毁一个处理器.
*	@param handler 要销毁的处理器.
*/
TDFAPI(int) TDF_DestroyHandler(HTDF hTdf);

/**
*	添加TDF服务器地址.	可以添加多个TDF服务器地址，以实现多服务器支持.
*	这样，当连接一个服务器失败时，
*	会自动连接到下一服务器。
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
*	@param lpUserName 连接该服务器时，所使用的用户名.
*	@param lpPassword 连接该服务器时，所使用的密码。
*	
*/
TDFAPI(int) TDF_AddServer(HTDF hTdf,
						   LPCSTR lpServer,
						   int nPort,
						   int nLevel,
							int  iProxyType,		//使用的代理类型.无代理时为零 
							char* szProxyHost,	//代理地址, 无代理时为""
							int  iProxyPort,	//代理端口, 无代理时为0
							char* szProxyUser,	//代理用户名, 无代理时为""
							char* szProxyPass,	//代理密码),无代理时为""
						    LPCSTR lpUserName,
						   LPCSTR lpPassword
						   );

/**
*	设置请求的数据日期,若不调用该函数，则默认请求最后交易日的数据.
*	@param handler  处理器.
*	因为TDF可以支持数据回溯，利用该功能，便可完成对历史数据的回溯.
*	@param nDate	要访问的数据日期, 格式：YYYYMMDD ,如 20101008
*	@param dSpeed   回放时的倍速.最小为1，当小于1时，系统，自动调为1，当系统的IO能力，不足，参数所
*					支持的倍速时，则系统以最大速度播放。
*/
TDFAPI(int) TDF_SetRequestDate(HTDF hTdf,int nDate,double dSpeed);

/**
*	设置要访问数据的市场.
*	@param handler  处理器.
*	@param pMarkets 请求数据的市场及标志,的数组.
*	@param nItems   记录数.
*	@remark 能访问的市场数据，还将受服务器上的数据内容，及所使用的帐号的相关权限的限制.
*			如果不调用此函数，则默认请求该帐号支持的所有市场。
*/ 
TDFAPI(int) TDF_SetRequestMarkets(
	HTDF hTdf,
	TDF_API_ReqMarkets* pMarkets,
	int nItems
	);

/**
*	 设置订阅,系统默认推送所请求的并且有权限的市场的全部品种的数据.
*	 在设置订阅后，系统只发送所订阅品种的数据，以节省传输带宽.
*	 @param handler  处理器.
*	 @param nSubscriptionType	订阅方式: 0：设置  1:增加  2:删除  3: 还原.
*	 @param pData  待操作的数据的起始地址.
*	 @param nItems 数据项数.
*	 @remark  当 nSubscriptionType = 3 时，会取消息所有订阅，恢复为传输所有数据. 
*/
TDFAPI(int) TDF_SetSubscription(
								HTDF hTdf,
								int nSubscriptionType,
								TDFDefine_SubscriptionData* pData,
								int nItems
								);


//---------------------------------------------------------------------
//事件回调

/**
*	TDF状态改变时的回调函数.
*	@param	nStatus  连接状态.
*					 0  尚未连接
*					 1  已经建立连接
*					 2  已经登录成功
*					 3  接收代表码完成
*					 4  正在接收数据.
*/
typedef bool (CALLBACK *ON_TDF_STATUS_CHANGED)(HTDF hTdf,int nStatus);

/**
*	TDF中断时回调函数原型.
*	@return 如果返回TRUE，则API重新登录连接.
*			如果返回FALSE，API不再进行重新连接.
*/
typedef bool (CALLBACK* ON_TDF_DISCONNECT_HANDLER)(HTDF /*handler*/);

/**
*	TDF登录结果回调函数原型.
*/
typedef void (CALLBACK* ON_TDF_LOGINRESULT_HANDLER)(HTDF /*handler*/,const TDFDefine_LoginAnswer* /*pAnswer*/);

/**
*	接收到来自TDF服务器的数据回调通知函数.
*	@param handler 处理器.
*	@param pHead 消息头.
*	@param pApplicationHead 应用头，通常指明后面数据的内容\标识\记录数等。某此消息无此应用头，故此参数可能为NULL.
*	@param nApplicationHeadSize 应用头长度,可能为零.
*	@param pData 解压后的数据的起始位置.数据类型，需根据 pHead 中 sDataType 的值来进行转换.
*				具体sDataType后所跟的消息格式，可参见 接口pdf 及 示例代码.
*	@param nItemSize 每一条记录的大小.
*	@param nItems 记录数.
*/
typedef void (CALLBACK* ON_TDF_RECV_DATA_HANDLER)(
												  HTDF /*handler*/,
												  const TDFDefine_MsgHead* /*pHead*/,//消息头中常用的数据成员sDataType和nTime.sDataType指明数据类型.后面的参数,根据sDataType来强制转换为对应的结构.nTime为服务器发出数据的机器时间,格式为HHMMSSmmm.
												  const void* /*pApplicationHead*/,
												  int /*nApplicationHeadSize*/,
												  const void* /*pData*/,
												  int /*nItemSize*/,
												  int /*nItems*/
												  );

/**
*	设置TDF状态改变的处理函数.
*	@param HTDF  处理器.
*/
TDFAPI(ON_TDF_STATUS_CHANGED) TDF_SetOnStatusChanged(HTDF hTdf,ON_TDF_STATUS_CHANGED pHandler);

/**
*	设置连接中断时的处理函数.
*	返回之前的中断处理函数.默认中断函数不做任何处理，返回TRUE，以便连接下一服务器.
*	@param HTDF  处理器.
*	@param pHandler	   中断事件处理器	.
*/
TDFAPI(ON_TDF_DISCONNECT_HANDLER)  TDF_SetOnTDFDisconnectHandler(HTDF hTdf,ON_TDF_DISCONNECT_HANDLER pHandler);
/**
*	设置登录结果的处理函数.
*	返回之前的登录结果处理函数,系统默认为NULL,不处理.
*	@param HTDF  处理器.
*	@param pHandler	   登录应答事件处理器	.
*/
TDFAPI(ON_TDF_LOGINRESULT_HANDLER)  TDF_SetOnTDFLoginResultHandler(HTDF hTdf,ON_TDF_LOGINRESULT_HANDLER pHandler);
/**
*	设置接收到的数据处理函数.
*	返回之前的数据处理函数. 系统默认为NULL，不处理.
*	@param HTDF  处理器.
*	@param pHandler	   接收到数据的处理函数	.
*/
TDFAPI(ON_TDF_RECV_DATA_HANDLER)  TDF_SetOnTDFRecvDataHandler(HTDF hTdf,ON_TDF_RECV_DATA_HANDLER pHandler);
//------------------------------------------------------------------------

/**
*	开始
*	将开始连接数据，并发起请求.
*	 @param handler  处理器.
*/
TDFAPI(int) TDF_Begin(HTDF hTdf);

/**
*	主动断开与服务器的连接。主动断开后，不会自动重新连接服务器，
*   如果需要重新连接，请再次调用<a href="#TDF_Begin">TDF_Begin</a>
*	 @param handler  处理器.
*/
TDFAPI(int) TDF_End(HTDF hTdf);

/**
*	是否要保存行情快照。此函数宜在 所有的 TDF_Begin 之前调用。
*	保存行情快照后，可使用 
*	TDF_GetLastMarketData 、TDF_GetLastMarketData_Index 、 TDF_GetLastMarketData_Futures 查询最新的行情快照。
*	@param bSave 是否让API保存每个品种的最新行情快照于内存中。
*/
TDFAPI(int) TDF_SaveSnapshot(bool bSave);


/**
* 清除开发包保存的行情和状态
* 在用于回溯时，可在某天完成后调用该函数,然后再请求别一日的数据.
*
*/
TDFAPI(void) TDF_Clear();



/**
*	查询最新的行情数据.
*	@param  lpMarket 市场
*	@param  lpCode   代码
*	@param  pMarketData  [out]返回最新的行情。
*	@return 如果获取成功，则返回0,否则，返回非零。
*/
TDFAPI(int) TDF_GetLastMarketData(
		LPCSTR lpMarket,
		LPCSTR lpCode,
		TDFDefine_MarketData *pMarketData
		);

/**
*	查询指数最新的行情数据.
*	@param  lpMarket 市场
*	@param  lpCode   代码
*	@param  pMarketData  [out]返回最新的行情。
*	@return 如果获取成功，则返回0,否则，返回非零。
*/
TDFAPI(int) TDF_GetLastMarketData_Index(
		LPCSTR lpMarket,
		LPCSTR lpCode,
		TDFDefine_IndexData *pMarketData
		);

/**
*	查询期货品种最新的行情数据.
*	@param  lpMarket 市场
*	@param  lpCode   代码
*	@param  pMarketData  [out]返回最新的行情。
*	@return 如果获取成功，则返回0,否则，返回非零。
*/
TDFAPI(int) TDF_GetLastMarketData_Futures(
	LPCSTR lpMarket,
	LPCSTR lpCode,
	TDFDefine_MarketData_Futures *pMarketData
	);

/**
*	批量查询最新的行情数据.
*	@param  pTdfGetBatchMarketData 请求内容.
*	@param	nItems				数量.
*/
TDFAPI(int) TDF_GetBatchLastMarketData(
	TDF_GetBacthMarketData *pTdfGetBatchMarketData,
	int nItems
	);

/**
*	批量查询股指期货最新的行情数据.
*	@param  pTdfGetBatchMarketData 请求内容.
*	@param	nItems				数量.
*/
TDFAPI(int) TDF_GetBatchLastMarketDataFutures(
	TDF_GetBacthMarketDataFutures *pTdfGetBatchMarketData,
	int nItems
);

/**
*	批量查询指数最新的行情数据.
*	@param  pTdfGetBatchMarketData 请求内容.
*	@param	nItems				数量.
*/
TDFAPI(int) TDF_GetBatchLastMarketDataIndex(
	TDF_GetBacthMarketDataIndex *pTdfGetBatchMarketData,
	int nItems
	);

/**
*	获取代码表.
*	@param  lpMarket 市场
*	@param nItems 数据项数.
*	@param pRetData 返回数据.
*
**/
TDFAPI(int) TDF_GetCodeTable(
	LPCSTR lpMarket,
	int *pnItems,
	TDFDefine_SecurityCode **pRetData
	);

/**
*	取处理器的连接状态.
*	@param handler 处理器.
*	@param pI64Send  [out]发送字节数
*	@param pI64Recv  [out]接收字节数
*	@Return          返回当前状态
*					 0  尚未连接
*					 1  已经建立连接
*					 2  已经登录成功
*					 3  接收代表码完成
*					 4  正在接收数据..
*/
TDFAPI(int)	TDF_GetStatus(HTDF hTdf,__int64 *pI64Send = NULL,__int64 *pI64Recv = NULL);

/**
*	取对方地址
*	@param handler 处理器.
*	@param pPeerAddr [out]如果未连接，返回零。否则对方地址.
*	@Return  函数是否成功获取网络地址.

*/
TDFAPI(int)	TDF_GetPeerAddr(HTDF hTdf,sockaddr_in *pPeerAddr);
/**
*	取对方地址
*	@param hTdf 处理器.
*	@param pszAddr [out]尝试或者正在连接的对方目标地址.
*	@Return  返回是否已经连接

*/
TDFAPI(int)	TDF_GetConnectingAddrString(HTDF hTdf,LPTSTR pszAddr,int nLength);

/**
*	释放内存.
*/
TDFAPI(int)	TDF_Release(void *pData);

/**
*	获取错误字符串.
*	@param	nErrorCode	错误值.
*	@return 返回错误说明的字符串.
*/
TDFAPI(LPCTSTR) TDF_GetError(int nErrorCode);

/**
*	获取股东类型.
*	@param lpszMarket	市场代码 SZ SH
*	@param lpszSecCode	证券代码 600000 000001
*	@return 返回股东类型.1:深圳A股,2:深圳B股,3:上海A股,4:上海B股. 5:股指期货 6 上海期货 7 郑州期货 8 大连期货
*    找不到则返回-1
*   @remark 根据TDF接收到的代码表情况来判断。
*/
TDFAPI(int) TDF_GetHolderType(LPCTSTR lpszMarket,LPCSTR lpszSecCode); 

/**
*	获取证券类型.
*	@param lpszMarket	市场代码 SZ SH
*	@param lpszSecCode	证券代码 600000 000001
*	@return 返回证券类型.
*	证券类型
*	基本分类（位与判断）
*	0x80000000 正股(有权证的股票)
*	0x00 指数
*	0x10 股票
*	0x20 基金
*	0x30 债券 & 可转债
*	0x40 回购
*	0x60 权证
*	0x70 期货
*	0x80 外汇
*	0xd0 银行利率
*	0xe0 贵金
*/
TDFAPI(int) TDF_GetSecurityType(LPCTSTR lpszMarket,LPCSTR lpszSecCode,int *pnType); 

/**
*	根据市场返回最近推送行情的最新时间.
*	@param lpszMarket	市场代码 SZ SH
*	@return 行情时间 格式为:HHMMSS.
*/
TDFAPI(int) TDF_GetLastMarketTime(LPCTSTR lpszMarket);


/**
*	根据市场参考时间.
*	@param lpszMarket	市场代码 SZ SH
*	@return 行情时间 格式为:HHMMSS.
*   @remark 注：此时间由行情时间与本地时间结合计算。并不能保证该时间的完全正确.审慎使用.
*			当交易所发布时间，未达到毫秒级时，参考时间更新频率，略高于 TDF_GetLastMarketTime 的更新频率.
*   注意，当回放速度小于1位速时，请不要使用该函数.
*/
TDFAPI(int) TDF_GetMarketReferenceTime(LPCTSTR lpszMarket);



/**
*	返回最新日期
*/
TDFAPI(int) TDF_GetLastMarketDate(LPCTSTR lpszMarket);

/**
* 设置日志记录函数.
*/
//DECLARE_COMMON_LOG_FUN(TDF,TDFAPI);

typedef void (CALLBACK* TDF_LOG_FUN)(LPCTSTR,LPVOID);

/**
* 设置TDF日志记录
* @param pFun 日志记录函数
* @param lParam 回调给日志记录函数的参数
*/
TDFAPI(void) TDF_SetLogFun(TDF_LOG_FUN pFun,LPVOID lParam);



#ifdef __cplusplus
}
#endif


#endif //_TDFAPIHELPER_H_