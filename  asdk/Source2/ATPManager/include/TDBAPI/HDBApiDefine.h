///////////////////////////////////////////////////////////////////
// 宏汇 高频数据 API 数据结构定义
// 2009.12.8
// 深圳创真科技有限公司
///////////////////////////////////////////////////////////////////
// 所有价格都使用int,定点小数4位, 比如:10.75表示为107500
// IOPV、利息也使用int,定点小数4位
///////////////////////////////////////////////////////////////////
//@history                     2010-8-13                    修改
//           增加公开协议,增加数据压缩功能.                   
///////////////////////////////////////////////////////////////////

#ifndef _HDBAPIDEFINE_H_
#define _HDBAPIDEFINE_H_

#ifndef _WINDOWS
#define __int64 longlong
#endif

#pragma pack(push,1)



//新一代TDB协议版本起始号
#define TDB_VERSION_NG_START		(0x6000)
#define TDB_VERSION_NX_START_6001	(0x6001)	//当前使用最新版本号.






//数据类型定义
#define ID_HDBTELE_LOGIN			1		//登录（Login）
#define ID_HDBTELE_LOGINANSWER		2		//登录应答
#define ID_HDBTELE_LOGOUT			3		//登出（Logout）
#define ID_HDBTELE_SYSMSG			4		//系统消息.


//数据请求
#define ID_HDBTELE_REQCODETABLE			100		//请求代码表
#define ID_HDBTELE_REQKDATA				101		//请求K线数据
#define ID_HDBTELE_REQTICKDATA			102		//请求Tick数据
#define ID_HDBTELE_REQSAVEDATA			103		//请求L2数据
#define ID_HDBTELE_REQTICK_EX			104		//请求扩展Tick数据,后面跟结构 HDBDefine_RequestTick_Ex, 扩展支持多日与除权等信息
#define ID_HDBTELE_REQSECTOR			105		//请求板块信息			@operation:add @author:梁兴其 @date:2011/9/2
#define ID_HDBTELE_REQSECTOR_CODETABLE	106		//请求板块的代码表息	@operation:add @author:梁兴其 @date:2011/9/2
//-------------------------------------------------------------------------------------------------------------------------------------
#define ID_HDBTELE_REQKDATA_DYN			602		//请求动态K线数据
#define ID_HDBTELE_REQTICKDATA_DYN		603		//请求动态Tick数据
#define ID_HDBTELE_REQSAVEDATA_DYN		604		//请求动态L2数据
#define ID_HDBTELE_REQTERMINATE_DYN		701		//终止动态数据传送 added @2011/7/7 by 梁兴其		
//#define ID_HDBTELE_REQTICK_EX_DYN		108		//请求动态扩展Tick数据,后面跟结构 HDBDefine_RequestTick_Ex, 扩展支持多日与除权等信息
//--------------------------------------------------------------------------------------------------------------------------------------
#define ID_HDBTELE_REQBASEDATA		120		//请求基本资料
#define ID_HDBTELE_REQHZB			130		//请求基本资料汇总表
#define ID_HDBTELE_REQMARKETDATA	200		//请求历史行情数据
#define ID_HDBTELE_CANCEL			300		//中断传送

//数据应答
#define ID_HDBTELE_COCDETABLE			1000	//证劵索引表(Security Directory)
#define ID_HDBTELE_DAYKDATA				1010	//K线数据
#define ID_HDBTELE_DAYKDATA_INDEX		1011	//K线数据
//----------------------------------------------------------------------
#define ID_HDBTELE_DAYKDATA_DYN			6010	//动态K线数据
#define ID_HDBTELE_DAYKDATA_INDEX_DYN	6011	//动态指数K线数据
//----------------------------------------------------------------------

#define ID_HDBTELE_TICKKDATA				1020	//Tick数据
#define ID_HDBTELE_TICKKDATA_AB				1022	//Tick数据
#define ID_HDBTELE_TICKKDATA_INDEX			1023	//Tick数据
#define ID_HDBTELE_TICKKDATA_ACC			1024	//Tick数据(带累计成交量、累计成交额)
#define ID_HDBTELE_TICKKDATA_AB_ACC			1025	//Tick数据(带累计成交量、累计成交额)
#define ID_HDBTELE_TICKKDATA_INDEX_ACC		1026	//Tick数据(带累计成交量、累计成交额)
#define ID_HDBTELE_TICKKDATA_ALL			1027	//全部Tick(带累计成交量、累计成交额,带买卖盘，带最高最低).
#define ID_HDBTELE_TICKKDATA_INDEX_ALL		1028	//全部Tick(带累计成交量、累计成交额,带买卖盘，带最高最低).


//--------------------------------------------------------------------------------------------------------------
//动态数据
#define ID_HDBTELE_TICKKDATA_DYN				6020	//Tick数据
#define ID_HDBTELE_TICKKDATA_AB_DYN				6022	//Tick数据
#define ID_HDBTELE_TICKKDATA_INDEX_DYN			6023	//Tick数据
#define ID_HDBTELE_TICKKDATA_ACC_DYN			6024	//Tick数据(带累计成交量、累计成交额)
#define ID_HDBTELE_TICKKDATA_AB_ACC_DYN			6025	//Tick数据(带累计成交量、累计成交额)
#define ID_HDBTELE_TICKKDATA_INDEX_ACC_DYN		6026	//Tick数据(带累计成交量、累计成交额)
#define ID_HDBTELE_TICKKDATA_ALL_DYN			6027	//全部Tick(带累计成交量、累计成交额,带买卖盘，带最高最低).
#define ID_HDBTELE_TICKKDATA_INDEX_ALL_DYN		6028	//全部Tick(带累计成交量、累计成交额,带买卖盘，带最高最低).
//--------------------------------------------------------------------------------------------------------------
//易编公式指标
#define ID_HDBTELE_EZFORMULA_ADD				6050	//向服务器增加或替换一个公式
#define ID_HDBTELE_EZFORMULA_ADD_ANSWER			6051	//向服务器增加或替换一个公式应答
#define ID_HDBTELE_EZFORMULA_DEL				6052	//从服务器删除一个公式
#define ID_HDBTELE_EZFORMULA_DEL_ANSWER			6053	//从服务器删除一个公式应答
#define ID_HDBTELE_EZFORMULA_GET				6054	//读取服务器公式列表
#define ID_HDBTELE_EZFORMULA_GET_ANSWER			6055	//读取服务器公式列表应答
#define ID_HDBTELE_EZFORMULA_CALC				6056	//请求服务器计算公式指标
#define ID_HDBTELE_EZFORMULA_CALC_ANSWER		6057	//服务器公式计算指标应答
#define ID_HDBTELE_EZFORMULA_CALC_DYN			6058	//请求服务器计算公式指标（动态）
#define ID_HDBTELE_EZFORMULA_CALC_ANSWER_DYN	6059	//服务器公式计算指标应答（动态）




#define ID_HDBTELE_TRANSACTION		1030	//逐笔成交(Transaction)
#define ID_HDBTELE_ORDERQUEUE		1031	//委托队列(Queue)
#define ID_HDBTELE_ORDER			1035	//逐笔委托(Order)
#define ID_HDBTELE_BROKERQUEUE		1036	//经纪队列(港股)
#define ID_HDBTELE_BASEDATA_FP		1200	//基本资料-分配方案
#define ID_HDBTELE_HZB_BASE			1300	//基本资料汇总表-基本信息
#define ID_HDBTELE_MARKETDATA		2000	//历史行情
#define ID_HDBTELE_SECTOR_ANS				2001	//板块信息应答		@operation:add @author:梁兴其 @date:2011/9/2
#define ID_HDBTELE_SECTOR_CODETABLE_ANS		2002	//板块代码表应答	@operation:add @author:梁兴其 @date:2011/9/2
//--------------------------------------------------------------------------
//动态数据
#define ID_HDBTELE_TRANSACTION_DYN		6030	//逐笔成交(Transaction)
#define ID_HDBTELE_ORDERQUEUE_DYN		6031	//委托队列(Queue)
#define ID_HDBTELE_ORDER_DYN			6035	//逐笔委托(Order)
//--------------------------------------------------------------------------

//证券类型定义/////////////////////////////////////////////////////////////////////////
//证券基本分类定义
#define ID_BASECLASS_INDEX		0x00	//指数
#define ID_BASECLASS_SHARES		0x10	//股票
#define ID_BASECLASS_FUND		0x20	//基金
#define ID_BASECLASS_BOND		0x30	//债券 & 可转债
#define ID_BASECLASS_REPO		0x40	//回购
#define ID_BASECLASS_QZ			0x60	//权证
#define ID_BASECLASS_FUTURES	0x70	//期货
#define ID_BASECLASS_FOREX		0x80	//外汇
#define ID_BASECLASS_BANKRATE	0xd0	//银行利率
#define ID_BASECLASS_NMETAL		0xe0	//贵金属(noble metal)
#define ID_BASECLASS_OTHER		0xf0	//其他

//证券扩展分类定义
#define ID_BTEX_HASWARRANT		0x80000000	//正股(有权证的股票)
//证券基本分类定义(细分)
#define ID_BT_INDEX				0x01	//交易所指数
#define ID_BT_INDEX_ASIA		0x03	//亚洲指数
#define ID_BT_INDEX_FOREIGN		0x04	//国际指数
#define ID_BT_INDEX_HH			0x05	//系统分类指数
#define ID_BT_INDEX_USER		0x06	//用户分类指数
#define ID_BT_INDEX_MD			0x08	//指数现货
#define ID_BT_SHARES_A			0x10	//A股
#define ID_BT_SHARES_S			0x11	//中小板股
#define ID_BT_SHARES_G			0x12	//创业板股
#define ID_BT_SHARES_B			0x16	//B股
#define ID_BT_SHARES_H			0x17	//H股(在香港上市的A股，2008.12.4为上海Level2行情H股增加)
#define ID_BT_SHARES_US			0x1a	//US
#define ID_BT_SHARES_USADR		0x1b	//US ADR
#define ID_BT_SHARES_E			0x1e	//扩展板块股票(港)
#define ID_BT_FUND				0x20	//基金
#define ID_BT_FUND_OPEN			0x21	//未上市开放基金
#define ID_BT_FUND_LOF			0x22	//上市开放基金
#define ID_BT_FUND_ETF			0x23	//交易型开放式指数基金
#define ID_BT_FUND_ETS			0x25	//扩展板块基金(港)
#define ID_BT_BOND_NA			0x30	//政府债券
#define ID_BT_BOND_CORP			0x31	//企业债券
#define ID_BT_BOND_FIN			0x32	//金融债券
#define ID_BT_BOND_CON			0x33	//可转债券
#define ID_BT_REPO_NA			0x40	//国债回购
#define ID_BT_REPO_CORP			0x41	//企债回购
#define ID_BT_QZ				0x60	//权证
#define ID_BT_QZ_C				0x61	//认购权证
#define ID_BT_QZ_P				0x62	//认沽权证
#define ID_BT_QZ_C_B			0x64	//认购权证(B股)
#define ID_BT_QZ_P_B			0x65	//认沽权证(B股)
#define ID_BT_QZ_M				0x66	//牛证（moo-cow）
#define ID_BT_QZ_B				0x67	//熊证（bear）

#define ID_BT_FUTURES_IDX		0x70	//指数期货
#define ID_BT_FUTURES			0x71	//商品期货
#define ID_BT_FUTURES_SHA		0x72	//股票期货
#define ID_BT_FUTURES_IBOR		0x73	//同业拆借利率期货
#define ID_BT_FUTURES_EFN		0x74	//Exchange Fund Note Futures
#define ID_BT_FUTURES_CX_IDX	0x78	//指数期货连线CX
#define ID_BT_FUTURES_CC_IDX	0x79	//指数期货连线CC
#define ID_BT_FUTURES_CX		0x7a	//商品期货连线CX
#define ID_BT_FUTURES_CC		0x7b	//商品期货连线CC
#define ID_BT_FUTURES_CX_SHA	0x7c	//股票期货连线CX
#define ID_BT_FUTURES_CC_SHA	0x7d	//股票期货连线CC

#define ID_BT_FOREX_BASE		0x80	//基本汇率
#define ID_BT_FOREX_CROSE		0x81	//交叉汇率
#define ID_BT_FOREX_REVERSE		0x82	//反向汇率
#define ID_BT_BANKRATE			0xd0	//银行利率
#define ID_BT_BANKRATE_HK		0xd1	//银行利率(HK)
#define ID_BT_BANKRATE_WORLD	0xd2	//银行利率(Interal)
#define ID_BT_NMETAL			0xe0	//贵金属(noble metal)
#define ID_BT_OTHERS			0xf0	//其他
#define ID_BT_OTHER_SHARES_SG_A	0xf1	//A股新股申购
#define ID_BT_OTHER_SHARES_ZF_A	0xf2	//A股增发
//end of 证券类型定义/////////////////////////////////////////////////////////

//数据包识别头
struct HDBDefine_MsgHead
{
	unsigned short  	sFlags;		//16字节 标识符         0x5348
    unsigned short  	sDataType;	//16字节 数据类型	          
	int					nDataLen;	//32字节 数据长度（不含本识别头）
    int					nTime;		//32字节 时间戳（精确到毫秒HHMMSSmmmm）
    int     			nOrder;		//32字节 流水号（当返回数据太大时有效，每个请求顺序编码）
	int					nChannel;	//通道号 （数据按通道传送，通道号自由定义）
};

//登陆
struct HDBDefine_Login
{
	char chUserName[16];	//用户名称
	char chPassword[32];	//用户密码
	char chID[8];			//保留
	char chMD5[32];			//保留
};

//登陆应答
struct HDBDefine_LoginAnswer
{
	char chInfo[64];			//信息
	int  nAnswer;				//1=登陆成功，其他失败
	int  nMarkets;				//支持市场个数
	char chMarketFlag[32][4];	//市场标志
	int  nDynDate[32];			//动态数据日期
	//授权信息（保留）
	struct CertifucationInfo
	{
		int  nBeginDate;		//数据授权开始日期
		int  nEndDate;			//数据授权截止日期
	}CertiDate[12];
};

struct HDBDefine_SysMsg
{
	int nType;					//消息类别.	0 调试 1 信息 2 警告 3 错误
	char chMsg[256];			//消息内容.
};


///1.1 证券索引表
//请求市场代码(所有代码，包含停牌品种)
struct HDBDefine_RequestCodeTable
{
	char chMarketFlag[4];		//市场标志
};

//应答数据包
struct HDBDefine_SecurityCode_Head
{
	char chMarket[4];
	int  nTotalItems;	//数据总数
	int  nItemSize;		//每条记录大小
};

//代码表
struct HDBDefine_SecurityCode
{
	char chSecurityCode[8];		//证券代码
	char chSymbol[16];			//证券名称
	int  nType;					//证券类型
};


//1.2 请求K线数据
struct HDBDefine_RequestKData
{
	char chCode[8];		//证券代码
	char chMarket[4];	//证券市场(SZ,SH,PT)
	int  nFlags;		
	int  nCQFlag;		//除权标志(0:原始数据 1:除权数据 2:复权数据)
	int  nCQDate;		//复权日期(-1:全程复权)
	int  nQJFlag;		//全价标志(债券)(0:净价 1:全价)
	int  nCyc;			//数据周期(0:分钟 1:日线 2:周线 3:月线 4:季线 5:半年线 6:年线 7:自定义日线 8:自定义周线 9:自定义月线)
	int  nCycUserDef;	//自定义周期(nCyc=0时，nCycUserDef为分钟定义，nCyc=7时nCycUserDef=3表示3日线，nCyc=8时nCycUserDef=3表示3周线，nCyc=9时nCycUserDef=3表示3月线)
	int  nBeginDate;	//开始日期(-1:从上市日期开始)
	int  nEndDate;		//结束日期(-1:当前日期) ★动态的数据肯定是到今天的，因此动态K线一定得是-1★
	int  nResv1;		//保留 ★★★★-1为请求动态K线数据★★★★
	int  nResv2;		//保留,如果nResv2 == 1 并且，所请求数据为1分钟K线，当一分钟K线不足240根时，将K线数据扩展至 240 根。(扩展、深圳、上海市场.)
	int  nLastDataTime;		//上次最新数据的时间 单元：秒 为-1时说明是动态K线的非动态部分[服务器端使用 客户端无需此字段]
	double	 dLastVolume;	//上次成交量[服务器端使用 客户端无需此字段]
	double	 dLastClosePrice;	//上次收盘价[服务器端使用 客户端无需此字段]	
};

//K线数据包头
struct HDBDefine_KData_Head
{
	char chCode[8];
	char chMarket[4];
	int  nFlags;		
	int  nCQFlag;		//除权标志(0:原始数据 1:除权数据 2:复权数据)
	int  nCQDate;		//复权日期(-1:全程复权)
	int  nQJFlag;		//全价标志(债券)(0:净价 1:全价)
	int  nCyc;			//数据周期(0:分钟 1:日线 2:周线 3:月线 4:季线 5:半年线 6:年线 7:自定义日线 8:自定义周线 9:自定义月线)
	int  nCycUserDef;	//自定义周期(nCyc=0时，nCycUserDef为分钟定义，nCyc=7时nCycUserDef=3表示3日线，nCyc=8时nCycUserDef=3表示3周线，nCyc=9时nCycUserDef=3表示3月线)
	int  nItemSize;		//每条记录大小
	int  nItems;		//本次数据条数
	int  nResv;			//保留
	int  nOverFlag;		//结束标志(1:传送完毕，0:还有下一个数据包, -1:表示没有授权或者不在授权期内)
};
//K线数据结构
struct HDBDefine_KData
{
	int     nDate;		//日期
	int     nTime;		//时间
	int		nOpen;		//开盘
	int		nHigh;		//最高
	int		nLow;		//最低
	int		nClose;		//收盘
	__int64 iVolume;	//成交量
	__int64	iTurover;	//成交额(元)
	int	  	nMatchItems;//成交笔数
	int   	nInterest;	//持仓量(期货)、IOPV(基金)、利息(债券)
};

struct HDBDefine_KData_Index
{
	int     nDate;		//日期
	int     nTime;		//时间
	int		nOpen;		//开盘
	int		nHigh;		//最高
	int		nLow;		//最低
	int		nClose;		//收盘
	__int64 iVolume;	//成交量
	__int64	iTurover;	//成交额(元)
	int	  	nMatchItems;//成交笔数
	int   	nStocks;	//品种总数
	int   	nUps;		//上涨品种数
	int   	nDowns;		//下跌品种数
	int   	nHoldLines;	//持平品种数
};


struct HDBDefine_RequestTickData
{
	char chCode[8];
	char chMarket[4];
	int  nFlags;		//0x01:包含买卖盘数据,0x02:包含当日累计成交量， (等于0x8000时返回带最高最低价的Tick.不可与前面组合)
	int  nDate;			//数据日期
	int  nBeginItem;	//开始位置
	int  nEndItem;		//结束位置(-1: 最后位置)
	int  nResv1;		//保留
	int  nResv2;		//保留
	int  nLastDataTime;	//上次最新数据的时间 单元：秒 为-1时说明是动态K线的非动态部分[服务器端使用 客户端无需此字段]
};

struct HDBDefine_TickData_Head
{
	char chCode[8];
	char chMarket[4];
	int  nFlags;		//0x01:包含买卖盘数据
	int  nDate;			//数据日期
	int  nTotalItems;
	int  nItemSize;		//每条记录大小
	int  nBeginItem;	//本次开始位置
	int  nItems;		//本次数据条数
	int  nOverFlag;		//结束标志(1:传送完毕，0:还有下一个数据包, -1:表示没有授权或者不在授权期内)
};

struct HDBDefine_TickData
{
	int   	nTime;		//时间
	int	  	nPrice;		//成交价
	__int64 iVolume;	//成交量
	__int64	iTurover;	//成交额(元)
	int   	nMatchItems;//成交笔数
	int   	nInterest;	//持仓量(期货)、IOPV(基金)、利息(债券)
	char   	chTradeFlag;//成交标志
	char   	chBSFlag;	//BS标志
};


//不带买卖盘、带累计成交量与累计成交额的Tick数据.
struct HDBDefine_TickData_ACC
{
	int   	nTime;		//时间
	int	  	nPrice;		//成交价
	__int64 iVolume;	//成交量
	__int64	iTurover;	//成交额(元)
	int   	nMatchItems;//成交笔数
	int   	nInterest;	//持仓量(期货)、IOPV(基金)、利息(债券)
	char   	chTradeFlag;//成交标志
	char   	chBSFlag;	//BS标志
	__int64 iAccVolume;	//当日累计成交量
	__int64	iAccTurover;//当日成交额(元)
};



struct HDBDefine_TickData_AB
{
	int   	 nTime;				//时间
	int	 	 nPrice;			//成交价
	__int64	 iVolume;			//成交量
	__int64	 iTurover;			//成交额
	int   	 nMatchItems;		//成交笔数
	int   	 nInterest;			//持仓量(期货)、IOPV(基金)、利息(债券)
	char   	 chTradeFlag;		//成交标志
	char   	 chBSFlag;	 		//BS标志
	int		 nAskPrice[10];		//叫卖价
	unsigned nAskVolume[10];	//叫卖量
	int		 nBidPrice[10];		//叫买价
	unsigned nBidVolume[10];	//叫买量
	int		 nAskAvPrice;		//加权平均叫卖价(上海L2)
	int		 nBidAvPrice;		//加权平均叫买价(上海L2)
	__int64  iTotalAskVolume;	//叫卖总量(上海L2)
	__int64  iTotalBidVolume;	//叫买总量(上海L2)
};


//带买卖盘、带累计成交量的Tick数据.
struct HDBDefine_TickData_AB_ACC
{
	int   	 nTime;				//时间
	int	 	 nPrice;			//成交价
	__int64	 iVolume;			//成交量
	__int64	 iTurover;			//成交额
	int   	 nMatchItems;		//成交笔数
	int   	 nInterest;			//持仓量(期货)、IOPV(基金)、利息(债券)
	char   	 chTradeFlag;		//成交标志
	char   	 chBSFlag;	 		//BS标志
	__int64 iAccVolume;			//当日累计成交量
	__int64	iAccTurover;		//当日成交额(元)
	int		 nAskPrice[10];		//叫卖价
	unsigned nAskVolume[10];	//叫卖量
	int		 nBidPrice[10];		//叫买价
	unsigned nBidVolume[10];	//叫买量
	int		 nAskAvPrice;		//加权平均叫卖价(上海L2)
	int		 nBidAvPrice;		//加权平均叫买价(上海L2)
	__int64  iTotalAskVolume;	//叫卖总量(上海L2)
	__int64  iTotalBidVolume;	//叫买总量(上海L2)
};


//带买卖盘、带累计成交量的Tick数据.
struct HDBDefine_TickData_ALL
{
	int   	 nTime;				//时间
	int	 	 nPrice;			//成交价
	__int64	 iVolume;			//成交量
	__int64	 iTurover;			//成交额
	int   	 nMatchItems;		//成交笔数
	int   	 nInterest;			//持仓量(期货)、IOPV(基金)、利息(债券)
	char   	 chTradeFlag;		//成交标志
	char   	 chBSFlag;	 		//BS标志
	__int64 iAccVolume;			//当日累计成交量
	__int64	iAccTurover;		//当日成交额(元)
	int		 nAskPrice[10];		//叫卖价
	unsigned nAskVolume[10];	//叫卖量
	int		 nBidPrice[10];		//叫买价
	unsigned nBidVolume[10];	//叫买量
	int		 nAskAvPrice;		//加权平均叫卖价(上海L2)
	int		 nBidAvPrice;		//加权平均叫买价(上海L2)
	__int64  iTotalAskVolume;	//叫卖总量(上海L2)
	__int64  iTotalBidVolume;	//叫买总量(上海L2)
	int      nHigh;				//最高
	int      nLow;				//最低
};



struct HDBDefine_TickData_Index
{
	int   	 nTime;				//时间
	int	 	 nPrice;			//成交价
	__int64	 iVolume;			//成交量
	__int64	 iTurover;			//成交额
	int   	 nMatchItems;		//成交笔数
	int   	 nIndex;			//不加权指数
	int   	 nStocks;			//品种总数
	int   	 nUps;				//上涨品种数
	int   	 nDowns;			//下跌品种数
	int   	 nHoldLines;		//持平品种数
};


struct HDBDefine_TickData_Index_ACC
{
	int   	 nTime;				//时间
	int	 	 nPrice;			//成交价
	__int64	 iVolume;			//成交量
	__int64	 iTurover;			//成交额
	int   	 nMatchItems;		//成交笔数
	int   	 nIndex;			//不加权指数
	int   	 nStocks;			//品种总数
	int   	 nUps;				//上涨品种数
	int   	 nDowns;			//下跌品种数
	int   	 nHoldLines;		//持平品种数
	__int64 iAccVolume;			//当日累计成交量
	__int64	iAccTurover;		//当日成交额(元)
};


struct HDBDefine_TickData_Index_ALL
{
	int   	 nTime;				//时间
	int	 	 nPrice;			//成交价
	__int64	 iVolume;			//成交量
	__int64	 iTurover;			//成交额
	int   	 nMatchItems;		//成交笔数
	int   	 nIndex;			//不加权指数
	int   	 nStocks;			//品种总数
	int   	 nUps;				//上涨品种数
	int   	 nDowns;			//下跌品种数
	int   	 nHoldLines;		//持平品种数
	__int64 iAccVolume;			//当日累计成交量
	__int64	iAccTurover;		//当日成交额(元)
	int      nHigh;				//最高
	int      nLow;				//最低
};


/**
* 扩展Tick数据请求.
*/
struct HDBDefine_RequestTick_Ex
{
	char chCode[8];
	char chMarket[4];
	int  nCQFlags;		//0，原始数据. 1,全程向前复权，2，全程向后复权，3，定点复权，当为定点复权时.
	int  nDateBegin;	//数据开始日期
	int  nDateEnd;		//数据结束日期
	int  nCQDate;		//除复权日期
	int  nResv1;		//保留
	int  nResv2;		//保留
	int  nLastDataTime;	//上次最新数据的时间 单元：秒 为-1时说明是动态K线的非动态部分[服务器端使用 客户端无需此字段]
};


//1.3 历史Level2数据
struct HDBDefine_RequestSaveData
{
	char chCode[8];
	char chMarket[4];
	int  nFlags;
	int  nDate;			//数据日期
	int  nType;			//0:逐笔成交(深沪L2港股) 1:委托队列(深沪L2) 2:逐笔委托(深圳L2) 3:经纪队列(港股)
	int  nBeginItem;	//开始位置
	int  nEndItem;		//结束位置(-1: 最后位置)
	int  nResv1;		//保留
	int  nResv2;		//保留
	int  nLastDataTime;	//上次最新数据的时间 单元：秒 为-1时说明是动态K线的非动态部分[服务器端使用 客户端无需此字段]
	int nLastItems;		//上一次数据量
};


struct HDBDefine_SaveData_Head
{
	char chCode[8];
	char chMarket[4];
	int  nFlags;
	int  nDate;			//数据日期
	int  nType;			//0:逐笔成交(深沪L2港股) 1:委托队列(深沪L2) 2:逐笔委托(深圳L2) 3:经纪队列(港股)
	int  nTotalItems;
	int  nItemSize;		//每条记录大小
	int  nBeginItem;	//开始位置
	int  nItems;		//本次传送记录数
	int  nOverFlag;		//结束标志(1:传送完毕，0:还有下一个数据包, -1:表示没有授权或者不在授权期内)
};

//1.4 逐笔数据
struct HDBDefine_Transaction
{
	int 	nTradeRef;		//成交编号
	int 	nTradeTime;		//成交时间
	char    chTradeFlag;	//成交标志
	char    chBSFlag;		//BS标志
	int		nTradePrice;	//成交价格
	int 	nTradeVolume;	//成交数量
};

//1.5 逐笔委托
struct HDBDefine_Order
{
	int 	nOrderRef;		//委托编号
	int 	nOrderTime;		//委托时间
	char    chOrderFlag;	//委托类别
	char    chBSFlag;		//委托买卖类型
	int		nOrderPrice;	//委托价格
	int 	nOrderVolume;	//委托数量
};

//1.6 订单队列(Queue)
struct HDBDefine_OrderQueue
{
	int 	nTime;			//订单编号(HHMMSS)
	int     nSide;			//买卖方向('B':Bid 'A':Ask)
	int		nPrice;			//成交价格
	int 	nOrderItems;	//订单数量
	int 	nABItems;		//明细个数
	int 	nABVolume[50];	//订单明细
};

//1.7 历史行情数据
struct HDBDefine_RequestMarketData
{
	char chMarket[4];
	int  nFlags;
	int  nDate;			//数据日期
	int  nClassType;	//行情分类ID(待扩展)
	GUID guidType;		//行情分类guid(待扩展)
	int  nHotType;		//排行类型(待扩展)
	int  nHotOrder;		//排行方式(待扩展)
	int  nResv1;		//保留1
	int  nResv2;		//保留2
};

struct HDBDefine_MarketData_Head
{
	char chMarket[4];
	int  nFlags;
	int  nDate;			//数据日期
	int  nTotalItems;	//数据总数
	int  nItemSize;		//每条记录大小
	int  nBeginItem;	//本次开始位置
	int  nItems;		//本次数据条数
	int  nClassType;	//行情分类ID(待扩展)
	GUID guidType;		//行情分类guid(待扩展)
	int  nHotType;		//排行类型(待扩展)
	int  nHotOrder;		//排行方式(待扩展)
	int  nResv1;		//保留
	int  nResv2;		//保留
	int  nResv3;		//保留
	int  nOverFlag;		//结束标志(1:传送完毕，0:还有下一个数据包, -1:表示没有授权或者不在授权期内)
};

struct HDBDefine_MarketData
{
	char	chCode[8];	//证券代码
	char	chName[16];	//证券名称
	int   	nType;		//证券类型
	int	  	nPreClose;	//前收盘
	int	  	nOpen;		//开盘价
	int	  	nHigh;		//最高价
	int	  	nLow;		//最低价
	int	  	nPrice;		//最后成交价
	__int64 iVolume;	//成交量
	__int64	iTurover;	//成交额(元)
	int   	nMatchItems;//成交笔数
	int   	nInterest;	//持仓量(期货)、IOPV(基金)、利息(债券)
};

//除权分配资料(2010.1.25新增)
struct HDBDefine_RequestBaseData
{
	char chCode[8];
	char chMarket[4];
	int  nFlags;
	int  nType;			//=0:除权分配方案
	int  nBeginItem;	//开始位置
	int  nEndItem;		//结束位置(-1: 最后位置)
	int  nResv1;		//保留
	int  nResv2;		//保留
};

struct HDBDefine_BaseData_Head
{
	char chCode[8];
	char chMarket[4];
	int  nFlags;
	int  nType;			//=0:除权分配方案
	int  nTotalItems;
	int  nItemSize;		//每条记录大小
	int  nBeginItem;	//开始位置
	int  nItems;		//本次传送记录数
	int  nOverFlag;		//结束标志(1:传送完毕，0:还有下一个数据包, -1:表示没有授权或者不在授权期内)
};

struct HDBDefine_BaseData_FP
{
	int 	nDateDJ;	//登记日期, 主要用于企业债券，输入下次计息的起息日期
	int 	nDateCQ;	//除权日期
	int 	nZGB;		//变更后总股本(万股)
	int 	nFXL;		//变更后发行量(万股)
	int 	nKLT;		//变更后可流通股本(万股)
	int 	nLTG;		//变更后流通股本(万股)
	int 	nYearFP;	//分配年度
	int  	nCQJG;		//除权价格
	int  	nPGJG;		//配股价格
	int		nZFJG;		//增发价格
	float	fPXS;		//派息数量
	float	fSGS;		//送股数量
	float	fPGS;		//配股数量
	float	fZZGS;		//转增数量
	float	fZFGS;		//增发数量
	char	chFPFA[64];	//分配方案
};

//基本资料汇总表

//请求基本资料汇总表
struct HDBDefine_RequestHZB
{
	char chMarketFlag[4];		//市场标志
	int  nFlags;				//保留
	int  nType;					//0:基本信息汇总表
};

struct HDBDefine_HZB_Head
{
	char chMarket[4];
	int  nFlags;		//保留
	int	 nType;			//数据类型
	int  nTotalItems;	//数据总数
	int  nItemSize;		//每条记录大小
	int  nBegin;		//开始传送位置
	int  nItems;		//本次传送个数
	int  nOverFlag;		//结束标志(1:传送完毕，0:还有下一个数据包, -1:表示没有授权或者不在授权期内)
};

struct HDBDefine_HZB_BaseInfo
{
	char	chCode[8];		//证券代码
	char    chStkName[16];	//证券简称
	char    chCompany[36];	//证券全称
	char    chClass[4];		//证监会行业分类
	char	chExitFlag;		//退市标志
	int		nIssDate;		//发行日期
	int		nIssVolume;		//发行量
	int		nIssPrice;		////发行价
	int		nIssValue;		//发行面值
	float	fIssProfit;		//发行市盈	//率债券为本息和
	char	chIssNote;		//发行方式
	int		nListDate;		//上市日期	
	int		nEndDate;		//退市日期	//债券为到期日

	int		nGBFXL;			//发行量
	int		nGBKLT;			//可流通量
	int		nGBLTG;			//流通股
};

struct HDBDefine_EZFormula_Add
{
	char chEZFName[24];		//公式名称
	int  nParametes;		// 产生个数
	int  nEZFLen;
	char chEZFormula[4];
};

struct HDBDefine_EZFormula_Add_Answer
{
	int  nResult;				//结果0:成功
	int  nErrLine;				//错误行
	char chCode[128];			//错误公式行
	char chInfo[64];			//信息
};

struct HDBDefine_EZFormula_Del
{
	char chEZFName[24];		//公式名称
};

struct HDBDefine_EZFormula_Del_Answer
{
	int  nResult;				//结果0:成功
	char chEZFName[24];			//删除的指标名称
	char chInfo[64];			//删除信息
};

struct HDBDefine_EZFormula_Get
{
	char chEZFName[24];			//指标名称（空表示查询所有指标）
};

struct HDBDefine_EZFormula_Get_Answer
{
	int nItems;					//指标个数
	int nItemSize;				//每个指标信息大小
};

struct HDBDefine_EZFormula_Item
{
	char chEZFName[24];			//指标名称
	char chParam[128];			//参数
};

struct HDBDefine_EZFormula_Calc
{
	char chEZFName[24];		//公式名称
	char chParam[128];		//参数, "N1=5,N2=10, N3='000001'
	char chCode[8];			//证券代码
	char chMarket[4];		//证券市场
	int  nFlags;			//保留，必须为0
	int  nResv;				//保留，必须为0
	int  nCyc;				//数据周期
	int  nCyc1;				//数据周期1
	int  nCQFlag;			//除权标志
	int  nBondDataType;
	int  nCQDate;
	int  nCalcMaxItems;		//计算的最大数据量
	int  nResultMaxItems;	//传送的结果最大数据量
	int  nDynResultMaxItems;//动态传送的结果最大数据量
};

struct HDBDefine_EZFormula_Calc_Answer
{
	int	 nHeadSize;
	char chEZFName[24];		//公式名称
	char chCode[8];			//证券代码
	char chMarket[4];		//证券市场
	int  nCyc;				//数据周期
	int  nCyc1;				//数据周期1
	int  nCQFlag;			//除权标志
	int  nBondDataType;
	int  nCQDate;
	int  nCalcMaxItems;		//计算的最大数据量
	int  nResultMaxItems;	//传送的结果最大数据量
	int  nDynResultMaxItems;//动态传送的结果最大数据量

	int	 nResultesFlags;	//结果标志
	int  nResultes;			//结果数据组数
};


struct EZFResult
{
	char chName[24];		//字段名称
	int nBegin;				//开始条数
	int nEnd;				//结束条数
	double *pdData;			//数据 
};

struct HDBDefine_EZFormula_ResultData
{
	int nTotalItems;			//总数
	int *pnDate;				//日期
	int *pnTime;				//时间
	struct EZFResult Result[48];//结果集
};

//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////////////////////////////////////// 

/*
 *	请求板块信息
 */
struct HDBDefine_RequestSector
{
	int nTest;
};

/*
 *	板块类别消息头 
 *	@operation:add
 *	@author:梁兴其
 *	@date:2011/9/2
 */
struct HDBDefine_Sector_Head
{
	int nItems;
	int nItemSize;
};

/*
 *	板块类别
 *	@operation:add
 *	@author:梁兴其
 *	@date:2011/9/2
 */
struct HDBDefine_Sector 
{
	GUID	guid;		
	int		nID;
	int     nMarket;				//包含市场 0x01深圳 0x02上海 0x04PT 0x08HZ 0x10SEL 0x20MI 0x40港股 0x80国内期货 0x100外汇
	int     nSelMarket;				//选择的市场
	int     nPriceType;				//报价栏目类型 
	char	szSectorName[64];		//板块名称 
	int		nChild;					//子版块数目 为0则说明没有子板块
};

/*
 *	请求板块代码表
 */
struct HDBDefine_RequestSectorCodeTable
{
	GUID guidSector;				///>板块的GUID
	int		nID;
	int     nMarket;				//包含市场 0x01深圳 0x02上海 0x04PT 0x08HZ 0x10SEL 0x20MI 0x40港股 0x80国内期货 0x100外汇
	int     nSelMarket;				//选择的市场
	int     nPriceType;				//报价栏目类型 
};

#pragma pack(pop)
#endif
