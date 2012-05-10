#pragma once

#include "UTIDefine_Fut.h"
#include "UTIApiHelper.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
*	UTI期货交易句柄.
*/
typedef void*  HUTI_FUT;

/**
*	回调的信息类型(期货)
*/
enum UTI_FUT_UPDATE_TYPE
{
	/**
	*	持仓信息
	*/
	UTI_FUT_UPDATE_POSITION = 0,	
	/**
	*	成交信息
	*/
	UTI_FUT_UPDATE_MATCH = 1,
	/**
	*	委托信息
	*/
	UTI_FUT_UPDATE_ORDER = 2,
	/**
	*	资金信息
	*/
	UTI_FUT_UPDATE_ASSETS = 3,
	/**
	*	可撤单信息
	*/
	UTI_FUT_UPDATE_CANCANCEL = 4
};

/**
*	信息更新回调函数(期货).
*	@param handler 期货交易句柄.
*	@param nType 信息类型.
*	@param lParam 传入信息，原值返回.
*/
typedef void (CALLBACK* LP_UTI_FUT_UPDATE_CALLBACK_FUN)(HUTI_FUT /*handler*/,UTI_FUT_UPDATE_TYPE /*nType*/,LPVOID /*lParam*/);

/**
*	创建一个期货交易句柄.
*	@return 返回所创建的期货交易句柄.
*/
UTIAPI(HUTI_FUT) UTI_FUT_CreateHandler();

/**
*	销毁一个期货交易句柄.
*	@param handler 要销毁的期货交易句柄.
*	@return 销毁成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_DestroyHandler(HUTI_FUT handler);

/**
*	设置信息更新回调函数(期货).
*	@param handler 期货交易句柄.
*	@param nType 信息类型.
*	@param lParam 传入信息，原值返回.
*	@return 设置成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_SetUpdateCallBackFun(HUTI_FUT handler,LP_UTI_FUT_UPDATE_CALLBACK_FUN pFun,LPVOID lParam);

/**
*	拷贝登陆账号信息(期货).
*	@param handlerTo 待写入的证券交易句柄.
*	@param handlerFrom 被读出的证券交易句柄.
*	@return 拷贝成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_CopyHandler(HUTI_FUT handlerTo, HUTI_FUT handlerFrom);

/**
*	登录(期货).
*	@param handler 期货交易句柄.
*	@param pLogin 登录请求.
*	@param pLoginAnswer [out]登录应答.
*	@return 登录成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_Login(HUTI_FUT handler, const UTI_LoginRequest* pLogin,UTI_LoginAnswer* pLoginAnswer);

/**
*	登出(期货).
*	@param handler 期货交易句柄.
*	@return 登出成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_Logout(HUTI_FUT handler);

/**
*	期货开仓.
*	@param handler 期货交易句柄.
*	@param lpszCode 代码.
*	@param lpszMarket 市场.
*	@param nHolderType 交易编码类型.
<table border="1">
<tr><td>5</td><td>股指期货.</td></tr>
<tr><td>6</td><td>上海期货.</td></tr>
<tr><td>7</td><td>郑州期货.</td></tr>
<tr><td>8</td><td>大连期货.</td></tr>
</table>
*	@param nPrice 价格，放大10000倍.	
*	@param nVolume 委托量.
*	@param chBsSide 买卖方向.
<table border="1">
<tr><td>'B'</td><td>买.</td></tr>
<tr><td>'S'</td><td>卖.</td></tr>
</table>
*	@param szOrderNumber [out]返回合同号.
*	@param nLenOrderNumber szOrderNumber的长度，建议至少28位.
*	@param nHedgeFlag 投机套保标志.
<table border="1">
<tr><td>0</td><td>投机.</td></tr>
<tr><td>1</td><td>套期保值.</td></tr>
</table>
*	@param lpszOrderGroup 带批号下单.
*	@return 下单成功则返回0，否则返回其它值.
*/ 
UTIAPI(int) UTI_FUT_Open(HUTI_FUT handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,int nPrice,int nVolume,char chBsSide,char* szOrderNumber,int nLenOrderNumber,int nHedgeFlag, LPCSTR lpszOrderGroup);

/**
*	期货平仓.
*	@param handler 期货交易句柄.
*	@param lpszCode 代码.
*	@param lpszMarket 市场.
*	@param nHolderType 交易编码类型.
<table border="1">
<tr><td>5</td><td>股指期货.</td></tr>
<tr><td>6</td><td>上海期货.</td></tr>
<tr><td>7</td><td>郑州期货.</td></tr>
<tr><td>8</td><td>大连期货.</td></tr>
</table>
*	@param nPrice 价格，放大10000倍.	
*	@param nVolume 委托量.
*	@param chBsSide 买卖方向.
<table border="1">
<tr><td>'B'</td><td>买.</td></tr>
<tr><td>'S'</td><td>卖.</td></tr>
</table>
*	@param szOrderNumber [out]返回合同号.
*	@param nLenOrderNumber szOrderNumber的长度，建议至少28位.
*	@param nHedgeFlag 投机套保标志.
<table border="1">
<tr><td>0</td><td>投机.</td></tr>
<tr><td>1</td><td>套期保值.</td></tr>
</table>
*	@param lpszOrderGroup 带批号下单.
*	@return 下单成功则返回0，否则返回其它值.	
*/
UTIAPI(int) UTI_FUT_Close(HUTI_FUT handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,int nPrice,int nVolume,char chBsSide,char* szOrderNumber,int nLenOrderNumber,int nHedgeFlag, LPCSTR lpszOrderGroup);

/**
*	下单(期货).
*	@param handler 期货交易句柄.
*	@param pOrder 下单内容.
*	@param pMoResult [out]下单结果.
*	@return 下单成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_MakeOrder(HUTI_FUT handler, const UTI_FUT_Order* pOrder,UTI_FUT_MakeOrderResult* pMoResult);

/**
*	批量下单(期货).
*	@param handler 期货交易句柄.
*	@param pOrders 下单内容，数组数量不小于nItems.
*	@param nItems 下单个数.
*	@param pMoResults [out]下单结果，与下单内容一一对应，数组数量不小于nItems.
*	@return 批量下单成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_MakeBatchOrder(HUTI_FUT handler, const UTI_FUT_Order* pOrders,int nItems,UTI_FUT_MakeOrderResult* pMoResults);

/**
*	撤单(期货).
*	@param handler 期货交易句柄.
*	@param pRecord 委托记录/可撤单记录.
*	@param pCoResult [out]撤单结果.
*	@return 撤单成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_CancelOrder(HUTI_FUT handler, const UTI_FUT_OrderRecord* pRecord,UTI_FUT_CancelOrderResult* pCoResult);

/**
*	通过合同号进行撤单(期货).
*	@param handler 期货交易句柄.
*	@param lpszOrderNumber 委托编号.
*	@param pCoResult 撤单结果.
*	@return 撤单成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_CancelOrderByOrderNumber(HUTI_FUT handler, LPCSTR lpszOrderNumber,UTI_FUT_CancelOrderResult* pCoResult);

/**
*	批量撤单(期货).
*	@param handler 期货交易句柄.
*	@param pRecords 撤单内容，数组数量不小于nRecords.
*	@param nRecords 撤单个数.
*	@param pcoResults [out]撤单结果，与撤单内容一一对应，数组数量不小于nRecords.
*	@return 批量撤单成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_CancelBatchOrder(HUTI_FUT handler, const UTI_FUT_OrderRecord* pRecords,int nRecords,UTI_FUT_CancelOrderResult* pCoResults);

/**
*	全撤(期货).
*	@param handler 期货交易句柄.
*	@return 全撤成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_CancelAllOrder(HUTI_FUT handler);

/**
*	查询全部持仓(期货).
*	@param handler 期货交易句柄.
*	@param ppPositions [out]持仓，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryHoldPositions(HUTI_FUT handler, UTI_FUT_Position** ppPositions,int* pnItems);

/**
*	按市场查询持仓(期货).
*	@param handler 期货交易句柄.
*	@param lpszMarket 市场.
*	@param nHolderType 交易编码类型.
<table border="1">
<tr><td>5</td><td>股指期货.</td></tr>
<tr><td>6</td><td>上海期货.</td></tr>
<tr><td>7</td><td>郑州期货.</td></tr>
<tr><td>8</td><td>大连期货.</td></tr>
</table>
*	@param ppPositions [out]持仓，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryHoldPositionsByMarket(HUTI_FUT handler, LPCSTR lpszMarket,int nHolderType, UTI_FUT_Position** ppPositions,int* pnItems);

/**
*	按品种查询持仓(期货).
*	@param handler 期货交易句柄.
*	@param lpszCode 代码.
*	@param lpszMarket 市场.
*	@param nHolderType 交易编码类型.
<table border="1">
<tr><td>5</td><td>股指期货.</td></tr>
<tr><td>6</td><td>上海期货.</td></tr>
<tr><td>7</td><td>郑州期货.</td></tr>
<tr><td>8</td><td>大连期货.</td></tr>
</table>
*	@param ppPositions [out]持仓，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryHoldPositionsByCode(HUTI_FUT handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_FUT_Position** ppPositions,int* pnItems);

/**
*	查询全部成交(期货).
*	@param handler 期货交易句柄.
*	@param ppMatch [out]成交，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryMatch(HUTI_FUT handler, UTI_FUT_Match** ppMatch,int* pnItems);

/**
*	查询最新的成交(期货)，每次查询成功后更新定位串.
*	@param handler 期货交易句柄.
*	@param ppMatch [out]成交，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryNewMatch(HUTI_FUT handler, UTI_FUT_Match** ppMatch,int* pnItems);

/**
*	按定位串查询成交(期货).
*	@param handler 期货交易句柄.
*	@param lpszPostStr 定位串.
*	@param ppMatch [out]成交，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryMatchByPostStr(HUTI_FUT handler, LPCSTR lpszPostStr, UTI_FUT_Match** ppMatch,int* pnItems);

/**
*	按市场查询成交(期货).
*	@param handler 期货交易句柄.
*	@param lpszMarket 市场.
*	@param nHolderType 交易编码类型.
<table border="1">
<tr><td>5</td><td>股指期货.</td></tr>
<tr><td>6</td><td>上海期货.</td></tr>
<tr><td>7</td><td>郑州期货.</td></tr>
<tr><td>8</td><td>大连期货.</td></tr>
</table>
*	@param ppMatch [out]成交，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryMatchByMarket(HUTI_FUT handler, LPCSTR lpszMarket,int nHolderType, UTI_FUT_Match** ppMatch,int* pnItems);

/**
*	按品种查询成交(期货).
*	@param handler 期货交易句柄.
*	@param lpszCode 代码.
*	@param lpszMarket 市场.
*	@param nHolderType 交易编码类型.
<table border="1">
<tr><td>5</td><td>股指期货.</td></tr>
<tr><td>6</td><td>上海期货.</td></tr>
<tr><td>7</td><td>郑州期货.</td></tr>
<tr><td>8</td><td>大连期货.</td></tr>
</table>
*	@param ppMatch [out]成交，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryMatchByCode(HUTI_FUT handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_FUT_Match** ppMatch,int* pnItems);

/**
*	按合同号查询成交(期货).
*	@param handler 期货交易句柄.
*	@param lpszOrderNumber 合同号.
*	@param ppMatch [out]成交，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryMatchByOrderNumber(HUTI_FUT handler, LPCSTR lpszOrderNumber,UTI_FUT_Match** ppMatch,int* pnItems);

/**
*	按委托记录查询成交(期货).
*	@param handler 期货交易句柄.
*	@param pRecord 委托记录.
*	@param ppMatch [out]成交，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryMatchByOrder(HUTI_FUT handler, const UTI_FUT_OrderRecord* pRecord,UTI_FUT_Match** ppMatch,int* pnItems);

/**
*	按合同号合并查询成交(期货).
*	@param handler 期货交易句柄.
*	@param lpszOrderNumber 合同号.
*	@param pMatch [out]合并后的成交.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryMatch_Merge(HUTI_FUT handler, LPCSTR lpszOrderNumber,UTI_FUT_Match* pMatch);

/**
*	按委托记录合并查询成交(期货).
*	@param handler 期货交易句柄.
*	@param pRecord 委托记录.
*	@param pMatch [out]合并后的成交.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryMatchByOrder_Merge(HUTI_FUT handler, const UTI_FUT_OrderRecord* pRecord,UTI_FUT_Match* pMatch);

/**
*	查询全部委托(期货).
*	@param handler 期货交易句柄.
*	@param ppRecord [out]委托，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryOrderRecords(HUTI_FUT handler, UTI_FUT_OrderRecord** ppRecord,int* pnItems);

/**
*	查指定市场的委托(期货).
*	@param handler 期货交易句柄.
*	@param lpszMarket 市场.
*	@param nHolderType 交易编码类型.
<table border="1">
<tr><td>5</td><td>股指期货.</td></tr>
<tr><td>6</td><td>上海期货.</td></tr>
<tr><td>7</td><td>郑州期货.</td></tr>
<tr><td>8</td><td>大连期货.</td></tr>
</table>
*	@param ppRecord [out]委托，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryOrderRecordsByMarket(HUTI_FUT handler, LPCSTR lpszMarket,int nHolderType,UTI_FUT_OrderRecord** ppRecord,int* pnItems);

/**
*	查指定品种的委托(期货).
*	@param handler 期货交易句柄.
*	@param lpszCode 代码.
*	@param lpszMarket 市场.
*	@param nHolderType 交易编码类型.
<table border="1">
<tr><td>5</td><td>股指期货.</td></tr>
<tr><td>6</td><td>上海期货.</td></tr>
<tr><td>7</td><td>郑州期货.</td></tr>
<tr><td>8</td><td>大连期货.</td></tr>
</table>
*	@param ppRecord [out]委托，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryOrderRecordsByCode(HUTI_FUT handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_FUT_OrderRecord** ppRecord,int* pnItems);

/**
*	按合同号查委托(期货).
*	@param handler 期货交易句柄.
*	@param lpszOrderNumber 合同号.
*	@param pOrderRecord [out]委托记录.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryOrderByNumber(HUTI_FUT handler, LPCSTR lpszOrderNumber,UTI_FUT_OrderRecord* pOrderRecord);

/**
*	查询全部可撤委托(期货).
*	@param handler 期货交易句柄.
*	@param ppRecord [out]委托，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryCanCancel(HUTI_FUT handler, UTI_FUT_OrderRecord** ppRecord,int* pnItems);

/**
*	查指定市场的可撤委托(期货).
*	@param handler 期货交易句柄.
*	@param lpszMarket 市场.
*	@param nHolderType 交易编码类型.
<table border="1">
<tr><td>5</td><td>股指期货.</td></tr>
<tr><td>6</td><td>上海期货.</td></tr>
<tr><td>7</td><td>郑州期货.</td></tr>
<tr><td>8</td><td>大连期货.</td></tr>
</table>
*	@param ppRecord [out]委托，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryCanCancelByMarket(HUTI_FUT handler, LPCSTR lpszMarket,int nHolderType,UTI_FUT_OrderRecord** ppRecord,int* pnItems);

/**
*	查指定品种的可撤委托(期货).
*	@param handler 期货交易句柄.
*	@param lpszCode 代码.
*	@param lpszMarket 市场.
*	@param nHolderType 交易编码类型.
<table border="1">
<tr><td>5</td><td>股指期货.</td></tr>
<tr><td>6</td><td>上海期货.</td></tr>
<tr><td>7</td><td>郑州期货.</td></tr>
<tr><td>8</td><td>大连期货.</td></tr>
</table>
*	@param ppRecord [out]委托，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryCanCancelByCode(HUTI_FUT handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_FUT_OrderRecord** ppRecord,int* pnItems);

/**
*	按合同号查可撤委托(期货).
*	@param handler 期货交易句柄.
*	@param lpszOrderNumber 合同号.
*	@param pOrderRecord [out]委托记录.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryCanCancelByNumber(HUTI_FUT handler, LPCSTR lpszOrderNumber,UTI_FUT_OrderRecord* pOrderRecord);

/**
*	查可用资金(期货).
*	@param handler 期货交易句柄.
*	@param pdFreeCapital [out]可用资金.
*	@param chCurrencyType 币种.
<table border="1">
<tr><td>'0'</td><td>人民币.</td></tr>
<tr><td>'1'</td><td>港币.</td></tr>
<tr><td>'2'</td><td>美元.</td></tr>
</table>
*	@return 查询成功则返回0，否则返回其它值.
*/	
UTIAPI(int) UTI_FUT_QueryFreeCapital(HUTI_FUT handler, double* pdFreeCapital,char chCurrencyType);

/**
*	查询全部资金信息(期货).
*	@param handler 期货交易句柄.
*	@param ppAssets [out]资产记录，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryAssets(HUTI_FUT handler, UTI_FUT_Assets** ppAssets,int* pnItems);

/**
*	按币种查资金信息(期货).
*	@param handler 期货交易句柄.
*	@param chCurrencyType 币种.
<table border="1">
<tr><td>'0'</td><td>人民币.</td></tr>
<tr><td>'1'</td><td>港币.</td></tr>
<tr><td>'2'</td><td>美元.</td></tr>
</table>
*	@param pAssets [out]资产记录.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryAssetsByCurrency(HUTI_FUT handler, char chCurrencyType,UTI_FUT_Assets* pAssets);

/**
*	查询最大可交易量(期货).
*	@param handler 期货交易句柄.
*	@param pMaxVolReq 查询最大可交易量请求.
*	@param piVolume [out]输出最大可交易量.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_QueryMaxBSVolume(HUTI_FUT handler, const UTI_FUT_QueryMaxVolumeReq* pMaxVolReq,INT64* piVolume);

/**
*	查询全部合约(期货).
*	@param handler 期货交易句柄.
*	@param ppAgreement [out]合约信息，采用new分配，必须调用UTI_Release方法删除.
*	@param pnItems [out]返回记录数.
*	@return 查询成功则返回0，否则返回其它值.
*/ 
UTIAPI(int) UTI_FUT_QueryAgreement(HUTI_FUT handler, UTI_FUT_Agreement** ppAgreement,int* pnItems);

/**
*	按品种查询合约(期货).
*	@param handler 期货交易句柄.
*	@param lpszCode 代码.
*	@param lpszMarket 市场.
*	@param nHolderType 交易编码类型.
<table border="1">
<tr><td>5</td><td>股指期货.</td></tr>
<tr><td>6</td><td>上海期货.</td></tr>
<tr><td>7</td><td>郑州期货.</td></tr>
<tr><td>8</td><td>大连期货.</td></tr>
</table>
*	@param pAgreement [out]合约信息.
*	@return 查询成功则返回0，否则返回其它值.
*/ 
UTIAPI(int) UTI_FUT_QueryAgreementByCode(HUTI_FUT handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_FUT_Agreement* pAgreement);

/**
*	查询文本账单(期货).
*	@param handler 期货交易句柄.
*	@param nDate 账单日期.
*	@param ppBill [out]文本账单信息，采用new分配，必须调用UTI_Release方法删除.
*	@param pnInfoLen [out]返回文本信息长度.
*	@return 查询成功则返回0，否则返回其它值.
*/ 
UTIAPI(int) UTI_FUT_QueryBill(HUTI_FUT handler, int nDate , char** ppBill,int* pnInfoLen);

/**
*	结算单确认(期货).
*	@param handler 期货交易句柄.
*	@return 查询成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_FUT_ConfirmSettlement(HUTI_FUT handler);


/**
*	获取错误字符串.
*	@param	nErrorCode	错误值.
*   @param  pszError    返回错误值
*   @param  nLength     返回错误值的内存的长度
*	@return             0、已知错误，1、动态错误，-1 未知错误
*   @remark 由于某些错误由柜台产生，
*	@若是柜台产生的错误，需要使用handler取,仅能取出最后一次错误.
*/
UTIAPI(int) UTI_FUT_GetError(int nErrorCode,HUTI_FUT handler,char* pszError,int nLength);

#ifdef __cplusplus
}
#endif