#pragma once

#include "UTIDefine_Sec.h"
#include "UTIApiHelper.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
*	UTI证券交易句柄.
*/
typedef void*  HUTI_SEC;

/**
*	回调的信息类型(证券)
*/
enum UTI_SEC_UPDATE_TYPE
{
	/**
	*	持仓信息
	*/
	UTI_SEC_UPDATE_POSITION = 0,	
	/**
	*	成交信息
	*/
	UTI_SEC_UPDATE_MATCH = 1,
	/**
	*	委托信息
	*/
	UTI_SEC_UPDATE_ORDER = 2,
	/**
	*	资金信息
	*/
	UTI_SEC_UPDATE_ASSETS = 3,
	/**
	*	可撤单信息
	*/
	UTI_SEC_UPDATE_CANCANCEL = 4
};

/**
*	信息更新回调函数(证券).
*	@param handler 证券交易句柄.
*	@param nType 信息类型.
*	@param lParam 传入信息，原值返回.
*/
typedef void (CALLBACK* LP_UTI_SEC_UPDATE_CALLBACK_FUN)(HUTI_SEC /*handler*/,UTI_SEC_UPDATE_TYPE /*nType*/,LPVOID /*lParam*/);

/**
*	创建证券交易句柄.
*	@return 返回所创建的证券交易句柄.
*/
UTIAPI(HUTI_SEC) UTI_SEC_CreateHandler();

/**
*	销毁证券交易句柄.
*	@param handler 要销毁的证券交易句柄.
*	@return 销毁成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_DestroyHandler(HUTI_SEC handler);

/**
*	设置信息更新回调函数(证券).
*	@param handler 证券交易句柄.
*	@param nType 信息类型.
*	@param lParam 传入信息，原值返回.
*	@return 设置成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_SetUpdateCallBackFun(HUTI_SEC handler,LP_UTI_SEC_UPDATE_CALLBACK_FUN pFun,LPVOID lParam);

/**
*	拷贝登陆账号信息(证券).
*	@param handlerTo 待写入的证券交易句柄.
*	@param handlerFrom 被读出的证券交易句柄.
*	@return 拷贝成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_CopyHandler(HUTI_SEC handlerTo, HUTI_SEC handlerFrom);

/**
*	登录(证券).
*	@param handler 证券交易句柄.
*	@param pLogin 登录请求.
*	@param pLoginAnswer [out]登录应答.
*	@return 登录成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_Login(HUTI_SEC handler, const UTI_LoginRequest* pLogin,UTI_LoginAnswer* pLoginAnswer);

/**
*	登出(证券).
*	@param handler 证券交易句柄.
*	@return 登出成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_Logout(HUTI_SEC handler);

/**
*	证券买入.
*	@param handler 证券交易句柄.
*	@param lpszCode 代码.
*	@param lpszMarket 市场.
*	@param nHolderType 股东类型.
<table border="1">
<tr><td>1</td><td>深圳A股.</td></tr>
<tr><td>2</td><td>深圳B股.</td></tr>
<tr><td>3</td><td>上海A股.</td></tr>
<tr><td>4</td><td>上海B股.</td></tr>
</table>
*	@param nPrice 价格，放大10000倍，正数表示限价，负数表示市价委托方式.
<table border="1">
<tr><td>-1</td><td>对方最优价格.</td></tr>
<tr><td>-2</td><td>本方最优价格.</td></tr>
<tr><td>-3</td><td>即时成交剩余撤销.</td></tr>
<tr><td>-4</td><td>五档成交剩余撤销.</td></tr>
<tr><td>-5</td><td>全额成交或撤销.</td></tr>
<tr><td>-6</td><td>五档成交剩余现价.</td></tr>
</table>
*	@param nVolume 委托量.
*	@param szOrderNumber [out]返回合同号.
*	@param nLenOrderNumber szOrderNumber的长度，建议至少28位.
*	@param lpszOrderGroup 带批号下单.
*	@return 下单成功则返回0，否则返回其它值.
*/ 
UTIAPI(int) UTI_SEC_Buy(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,int nPrice,int nVolume,char* szOrderNumber,int nLenOrderNumber,LPCSTR lpszOrderGroup);

/**
*	证券卖出.
*	@param handler 证券交易句柄.
*	@param lpszCode 代码.
*	@param lpszMarket 市场.
*	@param nHolderType 股东类型.
<table border="1">
<tr><td>1</td><td>深圳A股.</td></tr>
<tr><td>2</td><td>深圳B股.</td></tr>
<tr><td>3</td><td>上海A股.</td></tr>
<tr><td>4</td><td>上海B股.</td></tr>
</table>
*	@param nPrice 价格，放大10000倍，正数表示限价，负数表示市价委托方式.
<table border="1">
<tr><td>-1</td><td>对方最优价格.</td></tr>
<tr><td>-2</td><td>本方最优价格.</td></tr>
<tr><td>-3</td><td>即时成交剩余撤销.</td></tr>
<tr><td>-4</td><td>五档成交剩余撤销.</td></tr>
<tr><td>-5</td><td>全额成交或撤销.</td></tr>
<tr><td>-6</td><td>五档成交剩余现价.</td></tr>
</table>
*	@param nVolume 委托量.
*	@param szOrderNumber [out]返回合同号.
*	@param nLenOrderNumber szOrderNumber的长度，建议至少28位.
*	@param lpszOrderGroup 带批号下单.
*	@return 下单成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_Sell(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,int nPrice,int nVolume,char* szOrderNumber,int nLenOrderNumber,LPCSTR lpszOrderGroup);

/**
*	申购.
*	@param handler 证券交易句柄.
*	@param lpszCode 代码.
*	@param lpszMarket 市场.
*	@param nHolderType 股东类型.
<table border="1">
<tr><td>1</td><td>深圳A股.</td></tr>
<tr><td>2</td><td>深圳B股.</td></tr>
<tr><td>3</td><td>上海A股.</td></tr>
<tr><td>4</td><td>上海B股.</td></tr>
</table>
*	@param nVolume 委托量.
*	@param szOrderNumber [out]返回合同号.
*	@param nLenOrderNumber szOrderNumber的长度，建议至少28位.
*	@return 下单成功则返回0，否则返回其它值.
*/ 
UTIAPI(int) UTI_SEC_ETFPurchase(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,int nVolume,char* szOrderNumber,int nLenOrderNumber);

/**
*	赎回.
*	@param handler 证券交易句柄.
*	@param lpszCode 代码.
*	@param lpszMarket 市场.
*	@param nHolderType 股东类型.
<table border="1">
<tr><td>1</td><td>深圳A股.</td></tr>
<tr><td>2</td><td>深圳B股.</td></tr>
<tr><td>3</td><td>上海A股.</td></tr>
<tr><td>4</td><td>上海B股.</td></tr>
</table>
*	@param nVolume 委托量.
*	@param szOrderNumber [out]返回合同号.	
*	@param nLenOrderNumber szOrderNumber的长度，建议至少28位.
*	@return 下单成功则返回0，否则返回其它值.
*/ 
UTIAPI(int) UTI_SEC_ETFRedeem(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,int nVolume,char* szOrderNumber,int nLenOrderNumber);

/**
*	下单(证券).
*	@param handler 证券交易句柄.
*	@param pOrder 下单内容.
*	@param pMoResult [out]下单结果.
*	@return 下单成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_MakeOrder(HUTI_SEC handler, const UTI_SEC_Order* pOrder,UTI_SEC_MakeOrderResult* pMoResult);

/**
*	批量下单(证券).
*	@param handler 证券交易句柄.
*	@param pOrders 下单内容，数组数量不小于nItems.
*	@param nItems 下单个数.
*	@param pMoResults [out]下单结果，与下单内容一一对应，数组数量不小于nItems.
*	@return 批量下单成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_MakeBatchOrder(HUTI_SEC handler, const UTI_SEC_Order* pOrders,int nItems,UTI_SEC_MakeOrderResult* pMoResults);

/**
*	撤单(证券).
*	@param handler 证券交易句柄.
*	@param pRecord 委托记录/可撤单记录.
*	@param pCoResult [out]撤单结果.
*	@return	撤单成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_CancelOrder(HUTI_SEC handler, const UTI_SEC_OrderRecord* pRecord,UTI_SEC_CancelOrderResult* pCoResult);

/**
*	通过合同号进行撤单(证券).
*	@param handler 证券交易句柄.
*	@param lpszOrderNumber 委托编号.
*	@param pCoResult [out]撤单结果.
*	@return	撤单成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_CancelOrderByOrderNumber(HUTI_SEC handler, LPCSTR lpszOrderNumber,UTI_SEC_CancelOrderResult* pCoResult);

/**
*	批量撤单(证券).
*	@param handler 证券交易句柄.
*	@param pRecords 撤单内容，数组数量不小于nRecords.
*	@param nRecords	撤单个数.
*	@param pCoResults [out]撤单结果，与撤单内容一一丢应，数组数量不小于nRecords.
*	@return 批量撤单成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_CancelBatchOrder(HUTI_SEC handler, const UTI_SEC_OrderRecord* pRecords,int nRecords,UTI_SEC_CancelOrderResult* pCoResults);

/**
*	全撤(证券).
*	@param handler 证券交易句柄.
*	@return 全撤成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_CancelAllOrder(HUTI_SEC handler);

/**
*	查询全部持仓(证券).
*	@param handler 证券交易句柄.
*	@param ppPositions [out]持仓，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryHoldPositions(HUTI_SEC handler, UTI_SEC_Position** ppPositions,int* pnItems);

/**
*	按市场查询持仓(证券).
*	@param handler 证券交易句柄.
*	@param lpszMarket 市场.
*	@param nHolderType 股东类型.
<table border="1">
<tr><td>1</td><td>深圳A股.</td></tr>
<tr><td>2</td><td>深圳B股.</td></tr>
<tr><td>3</td><td>上海A股.</td></tr>
<tr><td>4</td><td>上海B股.</td></tr>
</table>
*	@param ppPositions [out]持仓，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryHoldPositionsByMarket(HUTI_SEC handler, LPCSTR lpszMarket,int nHolderType, UTI_SEC_Position** ppPositions,int* pnItems);

/**
*	按品种查询持仓(证券).
*	@param handler 证券交易句柄.
*	@param lpszCode 代码.
*	@param lpszMarket 市场.
*	@param nHolderType 股东类型.
<table border="1">
<tr><td>1</td><td>深圳A股.</td></tr>
<tr><td>2</td><td>深圳B股.</td></tr>
<tr><td>3</td><td>上海A股.</td></tr>
<tr><td>4</td><td>上海B股.</td></tr>
</table>
*	@param ppPositions [out]持仓，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryHoldPositionsByCode(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_SEC_Position** ppPositions,int* pnItems);

/**
*	查询全部成交(证券).
*	@param handler 证券交易句柄.
*	@param ppMatch [out]成交，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryMatch(HUTI_SEC handler, UTI_SEC_Match** ppMatch,int* pnItems);

/**
*	查询最新的成交(证券)，每次查询成功后更新定位串.
*	@param handler 证券交易句柄.
*	@param ppMatch [out]成交，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryNewMatch(HUTI_SEC handler, UTI_SEC_Match** ppMatch,int* pnItems);

/**
*	按定位串查询成交(证券).
*	@param handler 证券交易句柄.
*	@param lpszPostStr 定位串.
*	@param ppMatch [out]成交，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryMatchByPostStr(HUTI_SEC handler, LPCSTR lpszPostStr, UTI_SEC_Match** ppMatch,int* pnItems);

/**
*	按市场查询成交(证券).
*	@param handler 证券交易句柄.
*	@param lpszMarket 市场.
*	@param nHolderType 股东类型.
<table border="1">
<tr><td>1</td><td>深圳A股.</td></tr>
<tr><td>2</td><td>深圳B股.</td></tr>
<tr><td>3</td><td>上海A股.</td></tr>
<tr><td>4</td><td>上海B股.</td></tr>
</table>
*	@param ppMatch [out]成交，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryMatchByMarket(HUTI_SEC handler, LPCSTR lpszMarket,int nHolderType, UTI_SEC_Match** ppMatch,int* pnItems);

/**
*	按品种查询成交(证券).
*	@param handler 证券交易句柄.
*	@param lpszCode	代码.
*	@param lpszMarket 市场.
*	@param nHolderType 股东类型.
<table border="1">
<tr><td>1</td><td>深圳A股.</td></tr>
<tr><td>2</td><td>深圳B股.</td></tr>
<tr><td>3</td><td>上海A股.</td></tr>
<tr><td>4</td><td>上海B股.</td></tr>
</table>
*	@param ppMatch [out]成交，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryMatchByCode(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_SEC_Match** ppMatch,int* pnItems);

/**
*	按合同号查询成交(证券).
*	@param handler 证券交易句柄.
*	@param lpszOrderNumber 合同号.
*	@param ppMatch [out]成交，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryMatchByOrderNumber(HUTI_SEC handler, LPCSTR lpszOrderNumber,UTI_SEC_Match** ppMatch,int* pnItems);

/**
*	按委托记录查询成交(证券).
*	@param handler 证券交易句柄.
*	@param pRecord 委托记录.
*	@param ppMatch [out]成交，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryMatchByOrder(HUTI_SEC handler, const UTI_SEC_OrderRecord* pRecord,UTI_SEC_Match** ppMatch,int* pnItems);

/**
*	按合同号合并查询成交(证券).
*	@param handler 证券交易句柄.
*	@param lpszOrderNumber 合同号.
*	@param pMatch [out]合并后的成交.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryMatch_Merge(HUTI_SEC handler, LPCSTR lpszOrderNumber,UTI_SEC_Match* pMatch);

/**
*	按委托记录合并查询(证券).
*	@param handler 证券交易句柄.
*	@param pRecord 委托记录.
*	@param pMatch [out]合并后的成交.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryMatchByOrder_Merge(HUTI_SEC handler, const UTI_SEC_OrderRecord* pRecord,UTI_SEC_Match* pMatch);

/**
*	查询全部委托(证券).
*	@param handler 证券交易句柄.
*	@param ppRecord	[out]委托记录，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryOrderRecords(HUTI_SEC handler, UTI_SEC_OrderRecord** ppRecord,int* pnItems);

/**
*	查指定市场的委托(证券).
*	@param handler 证券交易句柄.
*	@param lpszMarket 市场.	
*	@param nHolderType 股东类型.
<table border="1">
<tr><td>1</td><td>深圳A股.</td></tr>
<tr><td>2</td><td>深圳B股.</td></tr>
<tr><td>3</td><td>上海A股.</td></tr>
<tr><td>4</td><td>上海B股.</td></tr>
</table>
*	@param ppRecord	[out]委托记录，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryOrderRecordsByMarket(HUTI_SEC handler, LPCSTR lpszMarket,int nHolderType,UTI_SEC_OrderRecord** ppRecord,int* pnItems);

/**
*	查指定品种的委托(证券).
*	@param handler 证券交易句柄.
*	@param lpszCode 代码.
*	@param lpszMarket 市场.
*	@param nHolderType 股东类型.
<table border="1">
<tr><td>1</td><td>深圳A股.</td></tr>
<tr><td>2</td><td>深圳B股.</td></tr>
<tr><td>3</td><td>上海A股.</td></tr>
<tr><td>4</td><td>上海B股.</td></tr>
</table>
*	@param ppRecord	[out]委托记录，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryOrderRecordsByCode(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_SEC_OrderRecord** ppRecord,int* pnItems);

/**
*	按合同号查委托(证券).
*	@param handler 证券交易句柄.
*	@param lpszOrderNumber 合同号.
*	@param pOrderRecord [out]委托记录.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryOrderByNumber(HUTI_SEC handler, LPCSTR lpszOrderNumber,UTI_SEC_OrderRecord* pOrderRecord);

/**
*	查询全部可撤委托(证券).
*	@param handler 证券交易句柄.
*	@param ppRecord [out]委托记录，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryCanCancel(HUTI_SEC handler, UTI_SEC_OrderRecord** ppRecord,int* pnItems);

/**
*	查指定市场的可撤委托(证券).
*	@param handler 证券交易句柄.
*	@param lpszMarket 市场.
*	@param nHolderType 股东类型.
<table border="1">
<tr><td>1</td><td>深圳A股.</td></tr>
<tr><td>2</td><td>深圳B股.</td></tr>
<tr><td>3</td><td>上海A股.</td></tr>
<tr><td>4</td><td>上海B股.</td></tr>
</table>
*	@param ppRecord [out]委托记录，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryCanCancelByMarket(HUTI_SEC handler, LPCSTR lpszMarket,int nHolderType,UTI_SEC_OrderRecord** ppRecord,int* pnItems);

/**
*	查指定品种的可撤委托(证券).
*	@param handler 证券交易句柄.
*	@param lpszCode 代码.
*	@param lpszMarket 市场.
*	@param nHolderType 股东类型.
<table border="1">
<tr><td>1</td><td>深圳A股.</td></tr>
<tr><td>2</td><td>深圳B股.</td></tr>
<tr><td>3</td><td>上海A股.</td></tr>
<tr><td>4</td><td>上海B股.</td></tr>
</table>
*	@param ppRecord [out]委托记录，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryCanCancelByCode(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_SEC_OrderRecord** ppRecord,int* pnItems);

/**
*	按合同号查可撤委托(证券).
*	@param handler 证券交易句柄.
*	@param lpszOrderNumber 合同号.
*	@param pOrderRecord [out]委托记录.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryCanCancelByNumber(HUTI_SEC handler, LPCSTR lpszOrderNumber,UTI_SEC_OrderRecord* pOrderRecord);

/**
*	查可用资金(证券).
*	@param handler 证券交易句柄.
*	@param pdFreeCapital [out]可用资金.
*	@param chCurrencyType 币种.
<table border="1">
<tr><td>'0'</td><td>人民币.</td></tr>
<tr><td>'1'</td><td>港币.</td></tr>
<tr><td>'2'</td><td>美元.</td></tr>
</table>
*	@return 查询成功则返回0，否则返回其它值.
*/	
UTIAPI(int) UTI_SEC_QueryFreeCapital(HUTI_SEC handler, double* pdFreeCapital,char chCurrencyType);

/**
*	查询全部资金信息(证券).
*	@param handler 证券交易句柄.
*	@param ppAssets [out]资产记录，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryAssets(HUTI_SEC handler, UTI_SEC_Assets** ppAssets,int* pnItems);

/**
*	按币种查资金信息(证券).
*	@param handler 证券交易句柄.
*	@param chCurrencyType 币种.
<table border="1">
<tr><td>'0'</td><td>人民币.</td></tr>
<tr><td>'1'</td><td>港币.</td></tr>
<tr><td>'2'</td><td>美元.</td></tr>
</table>
*	@param ppAssets [out]资产记录.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryAssetsByCurrency(HUTI_SEC handler, char chCurrencyType,UTI_SEC_Assets* pAssets);

/**
*	查询最大可交易量(证券).
*	@param handler 证券交易句柄.
*	@param pMaxVolReq 查询最大可交易量请求.
*	@param piVolume [out]输出最大可交易量.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SEC_QueryMaxBSVolume(HUTI_SEC handler, const UTI_SEC_QueryMaxVolumeReq* pMaxVolReq,INT64* piVolume);


/**
*	获取错误字符串.
*	@param	nErrorCode	错误值.
*   @param  pszError    返回错误值
*   @param  nLength     返回错误值的内存的长度
*	@return             0、已知错误，1、动态错误，-1 未知错误
*   @remark 由于某些错误由柜台产生，
*	@若是柜台产生的错误，需要使用handler取,仅能取出最后一次错误.
*/
UTIAPI(int) UTI_SEC_GetError(int nErrorCode,HUTI_SEC handler,char* pszError,int nLength);


#ifdef __cplusplus
}
#endif