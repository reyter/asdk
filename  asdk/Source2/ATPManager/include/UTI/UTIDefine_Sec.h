/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 交易接口类(证券、权证、ETF等).
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-4		李伟		 创建
2010-7-12		郭智铭		 增加了UTI_SEC_MakeOrderResult，UTI_SEC_CancelOrderResult，UTI_SEC_QueryMaxVolumeReq的结构体定义
-------------------------------------------------------------
*/

#pragma once
#ifndef __UTIDEFINE_SEC_H_
#define __UTIDEFINE_SEC_H_
#include "UTIDefine.h"


#pragma pack(push,1)

/**
下单内容
*/
struct UTI_SEC_Order
{
	/**
	市场.
	*/
	char szMarket[4];	

	/**
	代码.
	*/ 	
	char szCode[12];	

	/**
	名称.
	*/ 	
	char szName[16];

	/**
	买卖方向,
	<table border="1">
	<tr><td>'B'</td><td>证券、ETF买(Buy)</td></tr>
	<tr><td>'S'</td><td>证券、ETF卖(Sell)</td></tr>
	<tr><td>'P'</td><td>基金认购、ETF申购(Purchase)</td></tr>
	<tr><td>'R'</td><td>基金赎回、ETF赎回(Redeem)</td></tr>
	</table>
	*/
	char cBSSide;		

	/**
	价格.放大一万倍，正数表示限价，负数表示委托方式如下：
	<table border="1">
	<tr><td>-1</td><td>对方最优价格</td></tr>
	<tr><td>-2</td><td>本方最优价格</td></tr>
	<tr><td>-3</td><td>即时成交剩余撤销</td></tr>
	<tr><td>-4</td><td>五档成交剩余撤销</td></tr>
	<tr><td>-5</td><td>全额成交或撤销</td></tr>
	<tr><td>-6</td><td>五档成交剩余现价</td></tr>
	</table>
	*/
	int nPrice;	

	/**
	数量.
	*/
	unsigned int nVolume;


	/**
	批号
	*/
    char szOrderGroup[LEN_ORDERGROUP];
};

/**
下单结果
*/
struct UTI_SEC_MakeOrderResult
{
	/**
	下单内容
	*/
	UTI_SEC_Order order;

	/**
	成功标志
	*/
	int nSucFlag;

	/**
	* 出错信息.
	*/
	char chErrMsg[LEN_ERROR];

	/**
	* 委托序号.
	*/
	char chOrderNumber[LEN_ORDERNUMBER];

};


/**
委托记录,同时也是可撤单记录格式与此相同.
*/
struct UTI_SEC_OrderRecord
{
	/**
	订单内容
	*/
	UTI_SEC_Order order;

	/**
	* 定位串.
	*/
	char chPostStr[LEN_POSTSTR];

	/**
	当前状态
	<table border="1">
	<tr><td>0</td><td>未报:委托成功未报盘</td></tr>
	<tr><td>1</td><td>正报：正在报盘</td></tr>
	<tr><td>2</td><td>已报：报盘成功</td></tr>
	<tr><td>3</td><td>已报待撤：已经报盘，未成交，且发了撤单委托指令</td></tr>
	<tr><td>4</td><td>已撤：未成交，全部已经撤单成功</td></tr>
	<tr><td>5</td><td>部成：部分成交</td></tr>
	<tr><td>6</td><td>部成待撤：部分成交，且发了撤单委托指令</td></tr>
	<tr><td>7</td><td>部撤：部分成交，剩余数量已经撤单成功</td></tr>
	<tr><td>8</td><td>已成：全部成交</td></tr>
	<tr><td>9</td><td>废单</td></tr>
	<tr><td>10</td><td>待报</td></tr>
	</table>
	*/
	DWORD    dwStatus;

	/**
	* 委托日期 格式是YYYYMMDD.
	*/
	int	 nOrderDate;

	/**
	* 委托时间 格式是HHMMSS.
	*/
	int	 nOrderTime;	


	/**
	* 成交数量.
	*/
	int  nMadeVolume;				
	/**
	* 成交均价，扩大了10000倍.
	*/
	int  nMadePrice;				
	/**
	* 撤单数量.
	*/
	int  nCancelVolume;				

	/**
	* 委托序号.
	*/
	char chOrderNumber[LEN_ORDERNUMBER];


	/**
	* 委托冻结金额.
	*/
	double dOrderFrozAmt;	
	/**
	* 成交金额.
	*/
	double dMadeAmt;


};


/**
撤单返回结果.
*/
struct UTI_SEC_CancelOrderResult
{
	/**
	成功标志
	*/
	int nSucFlag;

	/**
	* 出错信息.
	*/
	char chErrMsg[LEN_ERROR];

	/**
	* 委托序号.
	*/
	char chOrderNumber[LEN_ORDERNUMBER];
};


/**
持仓信息
*/
struct UTI_SEC_Position
{
	/**
	市场.
	*/
	char szMarket[4];	

	/**
	代码.
	*/ 	
	char szCode[12];

	/**
	证券名称
	*/
	char szName[12];

	/**
	股份余额
	*/
	__int64	 i64Balance;				

	/**
	股份可用
	*/
	__int64  i64Available;				

	/**
	股份冻结
	*/
	__int64  i64Forzen;				

	/**
	当日买入数
	*/
	__int64  i64Buy;					

	/**
	当日卖出数
	*/
	__int64  i64Sale;			

	/**
	当前拥股数
	*/
	__int64  i64Qty;					

	/**
	可申赎数量
	*/
	__int64  i64Diff;	

	/**
	成本价格，扩大了10000倍
	*/
	int  nCostPrice;					

	/**
	当前成本
	*/
	int  nBuyCost;						
	
	/**
	市值
	*/
	double dMktVal;						

	/**
	盈亏
	*/
	double dIncome;						

};


/**
成交
*/
struct UTI_SEC_Match
{
	/**
	订单内容
	*/
	UTI_SEC_Order order;

	/**
	* 定位串.
	*/
	char chPostStr[LEN_POSTSTR];

	/**
	成交状态 0-正常 1-撤单 2-废单
	*/
	int nStatus;				

	/**
	委托日期，格式是YYYYMMDD
	*/
	int	 nOrderDate;					

	/**
	委托时间，格式是HHMMSS
	*/
	int	 nOrderTime;								

	/**
	成交数量
	*/
	int  nMadeVolume;					

	/**
	成交价格，扩大了10000倍
	*/
	int  nMadePrice;					
	/**
	撤单数量
	*/
	int  nCancelVolume;										

	/**
	成交时间
	*/
	int	 nMadeTime;											

	/**
	委托序号
	*/
	char chOrderNumber[LEN_ORDERNUMBER];	
	
	/**
	成交编号
	*/
	char chMadeNumber[LEN_MADENUMBER];		

	/**
	说明
	*/
	char chRemark[LEN_REMARK];			
	/**
	其它说明
	*/
	char chRemark1[LEN_REMARK];			

	/**
	成交金额
	*/
	double dMadeAmt;

};


/**
资产记录
*/
struct UTI_SEC_Assets
{
	/**
	* 币种类型 '0'-人民币 '1'-港币 '2'-美元.
	*/
	char chMoneyType;					
	/**
	* 说明.
	*/
	char chRemark[LEN_REMARK];			
	/**
	* 资金可用.
	*/
	double dFundAvl;					
	/**
	* 资金余额.
	*/
	double dFundBal;				
	/**
	* 持仓市值资产.
	*/
	double dStkValue;					
	/**
	* 资金资产.
	*/
	double dFundValue;				
	/**
	* 总资产.
	*/
	double dMarketValue;				
	/**
	* 总盈亏.
	*/
	double dIncome;					
	/**
	* 冻结资金.
	*/
	double dFundFroz;				
	/**
	* 其他资金.
	*/
	double dOther;						
	/**
	* 今日买入金额.
	*/
	double dFundBuy;				
	/**
	* 今日卖出金额.
	*/
	double dFundSell;	

};

/**
最大可交易量查询结构.
*/
struct UTI_SEC_QueryMaxVolumeReq
{
	/**
	市场.
	*/
	char szMarket[4];	

	/**
	代码.
	*/ 	
	char szCode[12];	
	/**
	买卖方向,
	<table border="1">
	<tr><td>'B'</td><td>证券、ETF买(Buy)</td></tr>
	<tr><td>'S'</td><td>证券、ETF卖(Sell)</td></tr>
	<tr><td>'P'</td><td>基金认购、ETF申购(Purchase)</td></tr>
	<tr><td>'R'</td><td>基金赎回、ETF赎回(Redeem)</td></tr>
	</table>
	*/
	char cBSSide;		

	/**
	价格.放大一万倍，正数表示限价，负数表示委托方式如下：
	<table border="1">
	<tr><td>-1</td><td>对方最优价格</td></tr>
	<tr><td>-2</td><td>本方最优价格</td></tr>
	<tr><td>-3</td><td>即时成交剩余撤销</td></tr>
	<tr><td>-4</td><td>五档成交剩余撤销</td></tr>
	<tr><td>-5</td><td>全额成交或撤销</td></tr>
	<tr><td>-6</td><td>五档成交剩余现价</td></tr>
	</table>
	*/
	int nPrice;	

};


#pragma pack(pop)
#endif __UTIDEFINE_SEC_H_
