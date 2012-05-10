///////////////////////////////////////////////////////////////////
// 宏汇 Open DataFeed API 数据结构定义
// 所有价格都用int表示，其值为实际价格x10000
// 例如：成交价为 16.80 表示为 168000
// @System Transend Open DataFeed API (TDF)
// @Date 2010.4.21
// @Copyright 深圳创真科技有限公司
///////////////////////////////////////////////////////////////////
// @Author wli
// @History 
//     2010-4-21	增加期货行情接口
///////////////////////////////////////////////////////////////////

#ifndef _TDFAPIDEFINE_H_
#define _TDFAPIDEFINE_H_

#ifndef _WINDOWS
#define __int64 longlong
#endif

#pragma pack(push,1)

//数据类型定义
#define ID_TDFTELE_LOGIN			1		//登录(Login)
#define ID_TDFTELE_LOGINANSWER		2		//登录应答
#define ID_TDFTELE_LOGOUT			3		//登出(Logout)
#define ID_TDFTELE_CLOSE			4		//服务器关闭(Server Close)
#define ID_TDFTELE_COCDETABLE		6		//证劵索引表(Security Directory)
#define ID_TDFTELE_REQDATA			7		//请求行情数据
#define ID_TDFTELE_MARKETCLOSE		8		//闭市信息	
#define ID_TDFTELE_TRADINGMESSAGE	9		//交易信息
#define ID_TDFTELE_TRANSACTION		1101	//成交(Transaction)
#define ID_TDFTELE_ORDERQUEUE		1102	//委托队列(Queue)
#define ID_TDFTELE_ORDER			1103	//逐笔委托(Order)
#define ID_TDFTELE_ORDERQUEUE_FAST	1104	//委托队列(FAST Queue)
#define ID_TDFTELE_MARKETDATA		1012	//行情数据(Market Data)
#define ID_HDFTELE_MARKETDATA_FUTURES	1016	//期货行情数据(Futures Market Data)	1016
#define ID_TDFTELE_INDEXDATA		1113	//指数(Index)
#define ID_TDFTELE_MARKETOVERVIEW	1115	//市场概况(Market Overview)


#define ID_TDFTELE_ADDCODE			2001	//添加代码.


struct TDFDefine_MsgHead
{
	unsigned short  	sFlags;		//16字节 标识符(0x5340)
    unsigned short  	sDataType;	//16字节 数据类型	          
	int					nDataLen;	//32字节 数据长度
    int					nTime;		//32字节 时间戳（精确到毫秒HHMMSSmmmm）
    int     			nOrder;		//32字节 流水号
};

struct TDFDefine_Login
{
	char chUserName[16];
	char chPassword[32];
	char chID[8];
	char chMD5[32];
};

struct TDFDefine_LoginAnswer
{
	char chInfo[64];			//信息
	int  nAnswer;				//1:登陆成功
	int  nMarkets;
	char chMarketFlag[32][4];	//市场标志
	int  nDynDate[32];			//动态数据日期
};

struct TDFDefine_RequestCodeTable
{
	char chMarketFlag[4];		//市场标志(SZ;SH;HK;CF)
	int  nDate;					//数据日期，-1:表示动态数据，
};

#define ID_HDFDATAFLAGS_RETRANSALTE			0x00000001	//数据从开始传送
#define ID_HDFDATAFLAGS_NOTRANSACTION		0x00000100	//不传送逐笔成交数据
#define ID_HDFDATAFLAGS_NOABQUEUE			0x00000200	//不传送委托队列数据
#define ID_HDFDATAFLAGS_NOINDEX				0x00000400	//不传送指数数据
#define ID_HDFDATAFLAGS_NOMARKETOVERVIEW	0x00000800	//不传送 Market OverView 数据
#define ID_HDFDATAFLAGS_NOORDER				0x00001000	//不传送逐笔委托数据（SZ-Level2）
#define ID_HDFDATAFLAGS_COMPRESSED			0x00010000	//启用数据压缩
#define ID_HDFDATAFLAGS_ABQUEUE_FAST		0x00020000	//以FAST方式提供委托队列数据

struct TDFDefine_RequestMarketData
{
	char chMarketFlag[4];		//市场标志(SZ;SH;HK;CF)
	int  nFlags;				//由ID_HDFDATAFLAGS_定义
};

///1.1.1 证券索引表（Security Directory）
struct TDFDefine_SecurityCodeHead
{
	int  nSource;	//交易所 0:深圳 2:上海
	int  nDate;		//数据日期
	int  nCount;	//数据总数(-1:未授权)
	int  nFlags;	//(保留)
};

struct TDFDefine_SecurityCode
{
	int  nIdnum;				//本日编号(交易所编号*100 + 交易所编号)
	int  nType;					//证券类型
	char chSecurityCode[8];		//证券代码
	char chSymbol[16];			//证券名称
};

//1.1.2 逐笔成交(Transaction)
struct TDFDefine_TransactionHead
{
	int 	nIdnum;			//本日编号
	int     nItems;			//数据个数
};

struct TDFDefine_Transaction
{
	int 	nTime;		//成交时间(HHMMSSmmmm)
	int 	nIndex;		//成交编号
	int		nPrice;		//成交价格
	int 	nVolume;	//成交数量
	int		nTurnover;	//成交金额
};

//1.1.2 逐笔委托(Order)
struct TDFDefine_OrderHead
{
	int 	nIdnum;			//本日编号
	int     nItems;			//数据个数
};

struct TDFDefine_Order
{
	int 	nTime;		//委托时间(HHMMSSmmmm)
	int 	nIndex;		//委托编号
	int		nPrice;		//委托价格
	int 	nVolume;	//委托数量
	char    chType;		//委托类别
	char    chBSFlag;	//委托买卖类型('B','S','C')
	char    chResv[2];	//保留
};

//1.1.3 订单队列(Queue)
struct TDFDefine_OrderQueueHead
{
	int     nItems;			//数据个数
};

struct TDFDefine_OrderQueue
{
	int 	nIdnum;			//本日编号
	int 	nTime;			//订单编号(HHMMSSmmmm)
	int     nSide;			//买卖方向('B':Bid 'S':Ask)
	int		nPrice;			//成交价格
	int 	nOrders;		//订单数量
	int 	nABItems;		//明细个数
	int 	nABVolume[200];	//订单明细
};

//1.1.3.1 订单队列(上海FAST Queue)
struct TDFDefine_OrderQueue_FAST
{
	int  nIdnum;			//本日编号
	int  nTime;				//订单时间（HHMMSS）
	int  nSide;				//买卖方向（'B':Bid 'A':Ask）
 	int  nImageStatus;		//操作状态（1-Full Image 2-Update）
	int  nNoPriceLevel;		//操作的价位数
}; 

struct TDFDefine_OrderQueue_FAST_Operate
{
	int		nPriceOperate;	// 1.add , 2 Update ,3 Delete  0. absent 
	int     nPrice;			//价格
	int		nNumOrders;		//委托笔数
	int		nOqLevel;		//当前价位上要操作的订单数
};

struct TDFDefine_OrderQueue_FAST_OperateItem
{
	int nOperate;	//操作方式: 1 Add ,2 Update,3 Delete
	int nEntryID;   //操作ID:  Oreder Queue Operator Entry ID
	int nQty;		//订单数量
};

//1.1.4 行情数据(Market Data)
struct TDFDefine_MarketDataHead
{
	int     nItems;			//数据个数
};

typedef TDFDefine_MarketDataHead TDFDefine_MarketDataFuturesHead;

struct TDFDefine_MarketData
{
	int		nIdnum;						//本日编号
	int		nTime;						//时间(HHMMSSmmmm)
	int		nStatus;					//状态
	unsigned int nPreClose;				//前收盘价
	unsigned int nOpen;					//开盘价
	unsigned int nHigh;					//最高价
	unsigned int nLow;					//最低价
	unsigned int nMatch;				//最新价
	unsigned int nAskPrice[10];			//申卖价
	unsigned int nAskVol[10];			//申卖量
	unsigned int nBidPrice[10];			//申买价
	unsigned int nBidVol[10];			//申买量
	unsigned int nNumTrades;			//成交笔数
	__int64	iVolume;					//成交总量
	__int64	iTurnover;					//成交总金额
	__int64	nTotalBidVol;				//委托买入总量
	__int64	nTotalAskVol;				//委托卖出总量
	unsigned int nWeightedAvgBidPrice;	//加权平均委买价格
	unsigned int nWeightedAvgAskPrice;  //加权平均委卖价格
	int		nIOPV;						//IOPV净值估值
	int		nYieldToMaturity;			//到期收益率
	unsigned int nHighLimited;			//涨停价
	unsigned int nLowLimited;			//跌停价
	char	chPrefix[4];				//证券信息前缀
};

//1.1.5 指数(Index)
struct TDFDefine_IndexDataHead
{
	int     nItems;				//数据个数
};

struct TDFDefine_IndexData
{
	int		nIdnum;			//本日编号
	int     nTime;			//时间(HHMMSSmmmm)
	int		nOpenIndex;		//今开盘指数
	int 	nHighIndex;		//最高指数
	int 	nLowIndex;		//最低指数
	int 	nLastIndex;		//最新指数
	__int64	iTotalVolume;	//参与计算相应指数的交易数量
	__int64	iTurnover;		//参与计算相应指数的成交金额
	int		nPreCloseIndex;	//前盘指数
};


//1.1.6 市场概况(Market Overview)
struct TDFDefine_MarketOverview
{
	int		nSource;
	int		nOrigTime;			//时间(HHMMSSmmmm)
	int		nOrigDate;			//日期
	char	chEndOfDayMarket;	//结束标志
};


//f)	闭市(Close)
struct TDFDefine_MarketClose
{
	int		nSource;
	int		nTime;				//时间(HHMMSSmmmm)
	char	chInfo[64];			//闭市信息
};

//g)	交易信息通知 (Trading Message)
struct TDFDefine_TradingMessage
{
	int		nIdnum;				//本日编号
	char	chSecurityId[8];	//证券代码
	char	chInfo[128];		//信息
	int		nTime;				//时间(HHMMSSmmmm)
};


//期货Markets Data.
struct TDFDefine_MarketData_Futures
{
	int nIdnum;							//本日编号
	int	nTime;							//时间(HHMMSSmmmm)	
	int		nStatus;					//状态
	__int64 iPreOpenInterest;			//昨持仓
	unsigned int nPreClose;				//昨收盘价
	unsigned int nPreSettlePrice;		//昨结算
	unsigned int nOpen;					//开盘价	
	unsigned int nHigh;					//最高价
	unsigned int nLow;					//最低价
	unsigned int nMatch;				//最新价
	__int64	iVolume;					//成交总量
	__int64	iTurnover;					//成交总金额
	__int64 iOpenInterest;				//持仓总量
	unsigned int nClose;				//今收盘
	unsigned int nSettlePrice;			//今结算
	unsigned int nHighLimited;		//涨停价
	unsigned int nLowLimited;		//跌停价
	int		nPreDelta;			        //昨虚实度
	int     nCurrDelta;                 //今虚实度
	unsigned int nAskPrice[5];			//申卖价
	unsigned int nAskVol[5];			//申卖量
	unsigned int nBidPrice[5];			//申买价
	unsigned int nBidVol[5];			//申买量
};

#pragma pack(pop)
#endif
