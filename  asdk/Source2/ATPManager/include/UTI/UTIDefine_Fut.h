/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 交易接口类(期货类).
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-4		李伟		 创建
-------------------------------------------------------------
*/

#pragma once
#ifndef __UTIDEFINE_FUT_H_
#define __UTIDEFINE_FUT_H_
#include "UTIDefine.h"


#pragma pack(push,1)



/**
下单内容
*/
struct UTI_FUT_Order
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
	<tr><td>'B'</td><td>买(Buy)</td></tr>
	<tr><td>'S'</td><td>卖(Sell)</td></tr>
	</table>
	*/
	char cBSSide;	

	/**
	开平方向,
	<table border="1">
	<tr><td>0</td><td>开仓</td></tr>
	<tr><td>1</td><td>平仓</td></tr>
	<tr><td>2</td><td>平今仓</td></tr>
	</table>
	*/
	int nKPFlag;

	/**
	投保标志,
	<table border="1">
	<tr><td>0</td><td>投机</td></tr>
	<tr><td>1</td><td>保值</td></tr>
	</table>
	*/
	int nHedgeType;

	/**
	价格.放大一万倍
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
struct UTI_FUT_MakeOrderResult
{
	
	/**
	下单内容
	*/
	UTI_FUT_Order order;

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
struct UTI_FUT_OrderRecord
{
	
	/**
	订单内容
	*/
	UTI_FUT_Order order;

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
	</table>
	*/
	DWORD    dwStatus;

	/**
	* 委托日期 格式是HHMMSS.
	*/
	int	 nOrderDate;

	/**
	* 委托时间 格式是YYYYMMDD.
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
	* 开他冻结保证金.
	*/
	double dHoldBal;					

	/**
	* 冻结总费用.
	*/
	double dFrozFare;		

};


/**
撤单返回结果.
*/
struct UTI_FUT_CancelOrderResult
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
struct UTI_FUT_Position
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
	买卖方向,
	<table border="1">
	<tr><td>'B'</td><td>买(Buy)</td></tr>
	<tr><td>'S'</td><td>卖(Sell)</td></tr>
	</table>
	*/
	char cBSSide;

	/**
	期初数量
	*/
	int  nBeginVol;					
	/**
	可用数量
	*/
	int  nEnableVol;				
	/**
	当日可平仓数量
	*/
	int	 nRealVol;					

	/**
	当日开仓可用数量
	*/
	int  nTodayOpenVol;			
	/**
	实际上日平仓数量
	*/
	int	 nPreDropVol;			
	
	/**
	成本价格-平均价，扩大了10000倍
	*/
	int  nCostPrice;				
	/**
	最新价格
	*/
	int  nNewPrice;					

	/**
	盯市盈亏
	*/
	double dHoldProfit;				
	/**
	持仓浮动盈亏
	*/
	double dHoldProfitFloat;		
	/**
	上交易日保证金
	*/
	double dHoldBal;				

	/**
	说明
	*/
	char chRemark[LEN_REMARK];		

};


/**
成交
*/
struct UTI_FUT_Match
{

	/**
	订单内容
	*/
	UTI_FUT_Order order;

	/**
	* 定位串.
	*/
	char chPostStr[LEN_POSTSTR];

	/**
	成交状态 0-正常 1-撤单 
	*/
	int nStatus;											

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
	冻结总费用
	*/
	double dFrozFee;					

	/**
	平仓盈亏
	*/
	double dDropProfit;					

	/**
	平仓浮动盈亏
	*/
	double dDropFrofitFloat;			

};


/**
资产记录
*/
struct UTI_FUT_Assets
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
	* 资金余额.
	*/
	double dCurrentBal;				
	/**
	* 可用资金.
	*/
	double dEnableBal;				
	/**
	* 可取资金.
	*/
	double dFetchBal;				
	/**
	* 履约保证金.
	*/
	double dFrozBal;				
	/**
	* 当日开仓预冻结金额.
	*/
	double dRealHoldBalA;			
	/**
	* 当日开仓预冻结保证金和费用.
	*/
	double dRealHoldBalB;			
	/**
	* 盯市盈亏.
	*/
	double dHoldProfit;				
	/**
	* 总浮动盈亏.
	*/
	double dHoldProfitFloat;		
	/**
	* 期初客户权益.
	*/
	double dPreRightsBal;			
	/**
	* 客户权益.
	*/
	double dRightsBal;				
	/**
	* 浮动客户权益.
	*/
	double dRightsBalFloat;			

	/**
	* 盯市平仓盈亏.
	*/
	double	dRealDrop;				
	/**
	* 浮动平仓盈亏.
	*/
	double	dRealDrop_Float;		
	/**
	* 冻结费用.
	*/
	double	dFrozenFare;		
	/**
	* 客户保证金.
	*/
	double	dBailBalance;			

	/**
	* 盯市开仓盈亏.
	*/
	double	dRealOpen;				
	/**
	* 浮动开仓盈亏.
	*/
	double	dRealOpen_Float;		
	/**
	* 预计利息.
	*/
	double dIntrBal;				
};

/**
最大可交易量查询结构.
*/
struct UTI_FUT_QueryMaxVolumeReq
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
	<tr><td>'B'</td><td>买(Buy)</td></tr>
	<tr><td>'S'</td><td>卖(Sell)</td></tr>
	</table>
	*/
	char cBSSide;	

	/**
	开平方向,
	<table border="1">
	<tr><td>0</td><td>开仓</td></tr>
	<tr><td>1</td><td>平仓</td></tr>
	<tr><td>2</td><td>平今仓</td></tr>
	</table>
	*/
	int nKPFlag;

	/**
	投保标志,
	<table border="1">
	<tr><td>0</td><td>投机</td></tr>
	<tr><td>1</td><td>保值</td></tr>
	</table>
	*/
	int nHedgeType;

	/**
	价格.放大一万倍
	*/
	int nPrice;	

};

/**
期货合约
*/
struct UTI_FUT_Agreement
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
	'1'-按手存放  '2'-按吨存放.
	*/
	char chPriceUnit;				
	/**
	合约代码类别.
	*/
	char chFutType;					
	/**
	开始交易标志，'0'-正常  '1'-停止.
	*/
	char chStopFlag;				
	/**
	申报单位.
	*/
	char chReportUnit;				
	/**
	每手吨数.
	*/
	int nAmountPerHand;				
		
	/**
	最小价差.
	*/
	double dPriceStep;				
	/**
	开仓最小单位.
	*/
	double dHoldUnit;				
	/**
	平仓最小单位.
	*/
	double dDropUnit;			
	/**
	市价委托每笔最大下单数量.
	*/
	double dMarketAmount;			
	/**
	限价委托每笔最大下单数量.
	*/
	double dLimitedAmount;			

	/**
	开仓保证金比例.
	*/
	double	dOpenBailRatio;			
	/**
	开仓保证金.
	*/
	double	dOpenBailBalance;		
	/**
	平仓保证金比例.
	*/
	double	dDropBailRatio;			
	/**
	平仓保证金.
	*/
	double	dDropBailBalance;		
	/**
	交割保证金比例.
	*/
	double	dDeliverBailRatio;		
	/**
	交割保证金.
	*/
	double	dDeliverBailBalance;	
	/**
	平今仓保证金比例.
	*/
	double	dDropcuBailRatio;		
	/**
	平今仓保证金.
	*/
	double	dDropcuBailBalance;		

	/**
	说明.
	*/
	char chRemark[LEN_REMARK];		
};

#pragma pack(pop)
#endif __UTIDEFINE_FUT_H_
