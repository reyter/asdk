
#ifndef __QUOTE_DATA_STRUCT_H__
#define __QUOTE_DATA_STRUCT_H__
#include <vector>

#define STR_XH	_T("序号")
#define STR_DM	_T("代码")
#define STR_JC    _T("简称")
#define STR_ZS		_T("昨收")
#define STR_XJ    _T("现价")
#define STR_CJL   _T("成交量")
#define STR_ZDF   _T("涨幅")
#define STR_ZD		_T("涨跌")
#define STR_W_ZDF	_T("周涨幅")
#define STR_M_ZDF   _T("月涨幅")
#define STR_PJ    _T("评级")
#define STR_YLYC    _T("盈利预测")
#define STR_M3_YLYC	_T("三月前预测")
#define STR_ZRSP    _T("昨收")
#define STR_JRKP    _T("今开")
#define STR_ZGJG   _T("最高")
#define STR_ZDJG   _T("最低")
#define STR_HSL    _T("换手%")
#define STR_QHSL    _T("换手率")
#define STR_LB		_T("量比")
#define STR_ZHANGSU		_T("涨速")
#define STR_ZF		_T("振幅%")
#define STR_SYL    _T("市盈率")
#define STR_SYLYC    _T("预测市盈率")
#define STR_CJJE    _T("成交额")
#define STR_BUY   _T("叫买")
#define STR_SELL   _T("叫卖")
//#define STR_MGSY    "每股收益"
#define STR_LTSZ    _T("流通市值")
#define STR_PB		_T("PB")
#define STR_PE		_T("PE")
#define STR_ZSZ    _T("总市值")
#define STR_JGCG	_T("机构持股")
#define STR_DIAGNOSE _T("个股诊断")
#define STR_INDUSTRYNAME	_T("行业")
#define STR_WEAKSTRING_YEAR	_T("52周强弱")
#define STR_PJ_JG		_T("评级机构")
#define STR_PJ_RQ		_T("评级日期")
#define STR_PJ_THIS			_T("本次评级")
#define STR_PJ_LAST		_T("上次评级")
#define STR_YC_JG		_T("预测机构")
#define STR_YC_RQ		_T("预测日期")
#define STR_YC_THIS		_T("本次预测")
#define STR_YC_LAST		_T("上次预测")
#define STR_YC_YEAR		_T("预测年份")
#define STR_MBJ			_T("目标价")
#define STR_MBJ_JCFD	_T("上涨空间")
#define STR_PJ_STR		_T("当前评级")
#define STR_SRZZ		_T("收入增长")
#define STR_YLZZ		_T("盈利增长")

#define STR_LX12YLZZ	_T("连续12月盈利增长")
#define STR_WL12YLZZ	_T("未来12月盈利增长")
#define STR_ZXJDYLZZ	_T("最新季度盈利增长")
#define STR_LX12SRZZ	_T("连续12月收入增长")
#define STR_LX12ROE		_T("连续12月ROE")

#define STR_M3_ZDF		_T("三月涨跌幅")
#define STR_M6_ZDF		_T("半年涨跌幅")
#define STR_M12_ZDF		_T("一年涨跌幅")
#define STR_WZJLR		_T("一周资金流入(百万)")
#define STR_WZJLRZB		_T("一周资金流入占比")

#define STR_JGCGBL		_T("机构持股比例")
#define STR_JGCGBL_LAST		_T("上期持股比例")
#define STR_SZKJ		_T("上涨空间")
#define STR_FXSQXZS		_T("分析师情绪指数")

#define STR_INDUSTRY_WEAKSTRONG	_T("行业强弱")
#define STR_INDUSTRY_SORT		_T("行业看涨排名")

#define STR_DIAGNOSE_QUICK_BTN	_T("诊断摘要")
#define STR_CHANGE_STOCK_BTN	_T("换股")

#define STR_GROUP_STOCK_VOLUME				_T("数量")
#define STR_GROUP_STOCK_AVGPRICE			_T("均价")
#define STR_GROUP_STOCK_VALUE			_T("市值")
#define STR_GROUP_STOCK_INCOME			_T("盈亏")
#define STR_GROUP_STOCK_INCOME_PER			_T("盈亏比")

#define LIST_HEIGHT		24		//表格行高

#define STOCK_CODE_LEN	16
#define STOCK_NAME_LEN	64
#define STOCK_SPELL_LEN 4
#define STOCK_KIND_LEN	16
#define STOCK_PYDM_LEN	6
#define TICK_PERBLOCK	120
#define MINK_PERBLOCK	60
#define QUOTEHEAD		(STOCK_CODE_LEN+STOCK_NAME_LEN)
#define QUOTETAIL		(STOCK_KIND_LEN+sizeof(unsigned int)*4)

#define DIALOG_BNK_COLOR        RGB(230, 240, 255)
#define BORDER_COLOR            RGB(150, 166, 192)//边框色

#define WM_REQUEST_INFO			WM_USER + 50	//获取当前用户ID及即时通讯服务器及端口

#define WM_UPDATE_QUOTEDATA		WM_USER + 101//行情数据更新

#define WM_CONNECT_SUCCESS		WM_USER + 102//连接成功
#define WM_UPDATE_NEWSSET		WM_USER + 103//更新资讯设置

#define WM_ENTER_KEY				WM_USER + 127//按了回车键

#define WM_EXTRA_COMMAND		WM_USER + 200	//发送给窗体的命令

#define WM_ALERT_INFO			WM_USER + 201	//信息提示窗口
#define WM_UPDATE_RUN_INFO		WM_USER + 202	//跑马灯
#define WM_PERSONAL_SET			WM_USER + 203	//个性化定制
#define WM_SHORT_START          WM_USER + 205
#define WM_CREATE_LISTCTRL_INI  WM_USER + 206
#define WM_CANCEL_ALERT         WM_USER + 207
#define WM_SET_INFO_CLOSE       WM_USER + 208
#define WM_SET_INFO_STOCK       WM_USER + 209
//#define WM_COLUMNSORT           WM_USER + 207


#define WM_LOG_SUCCESS			WM_USER + 210	//登陆成功
#define WM_LOG					WM_USER + 212	//重新登陆
#define WM_DATA_PROGRESS		WM_USER + 213	//数据进度
#define WM_SHOW_NEWS			WM_USER + 214	//显示新闻
#define WM_GOTO_STOCK			WM_USER + 217
#define	WM_SWITCH_PIC_TYPE		WM_USER + 218	//切换Trend->Hisk,Hisk->Trend

#define WM_FORCE_QUIT			WM_USER + 215	//强制退出

#define WM_ADD_STOCK_TO_GROUP	WM_USER + 216	//增加股票到自选股组合

#define WM_CONTAINER			WM_USER + 219

#define WM_ADD_STOCK_TO_PIC		WM_USER + 220	//叠加K线

#define WM_GET_NEWSWND			WM_USER + 221	//取一个新闻窗口

#define WM_GROUP_CHANGED		WM_USER + 222	//组合内容更新了

#define WM_CHANGE_VIEWMODE		WM_USER + 223	//切换显示模式

#define WM_OPEN_TECH_FILE		WM_USER + 224	//打开技术图形文件
#define CONTAINER_MIN			1
#define CONTAINER_MAX			2
#define CONTAINER_HIDE			3

const unsigned int		CREATE_GROUP_COMMAND = 101;	//创建组合
const unsigned int		ADD_STOCK_COMMAND = 102;		//增加自选股
const unsigned int		INFO_SET_SUCCESS = 103;	//设置自己选择股
const unsigned int		PERSONAL_SET_COMMAND = 104;		//定制个性化
const unsigned int      CREATE_INI = 105;
const unsigned int      GROUP_OPERATE = 106;
const unsigned int      NEWS_OPERATE = 107;
const unsigned int		BUY_STOCK = 108;		//买入股票
const unsigned int		SALE_STOCK = 109;		//卖出股票
const unsigned int		PIC_2_STOCK = 110;		//图形比较


const unsigned int		VIEW_GROUP_NEWS = 122;	//显示组合新闻
const unsigned int		VIEW_INDUSTRY_NEWS	= 123;//显示行业新闻
const unsigned int		VIEW_STOCK_NEWS	= 124;//显示个股新闻
const unsigned int		GOTO_NEXT_STOCK = 125;//去下一支股票
const unsigned int		GOTO_LAST_STOCK = 126;//去上一支股票


//const unsigned int      SET_NEW_OPEN = 109;
//const unsigned int      SET_INFO_CLOSE = 110;

const unsigned int		SHOW_GROUP_WINDOW = 120;	//显示组合窗口
const unsigned int		SHOW_INFO_WINDOW = 121;		//显示资讯窗口
const unsigned int		SHOW_F10		= 127;		//显示F10信息
const unsigned int		SHOW_STOCKS		= 128;		//排名
const unsigned int	    SHOW_GORUP		= 129;		//显示组合

const unsigned int		SHOW_SENDMSG	= 130;		//发送消息
const unsigned int		SHOW_TRADEWND	= 131;		//显示交易窗口
const unsigned int		SHOW_TRACEWND	= 132;		//分笔窗口
const unsigned int		SHOW_TRACEPRICEWND = 133;	//分笔价格窗口
const unsigned int		ESCAPE_TRACEWND	= 134;		//撤消分笔窗口
const unsigned int		ESCAPE_TRACEPRICEWND	= 135;		//撤消分笔价格窗口

const unsigned int		STOCK_FROM_GROUP = 150;		//从组合
const unsigned int		STOCK_FROM_LIST	= 151;		//从列表
const unsigned int		STOCK_FROM_BOTTOM_LIST = 152;		//从下面列表
const unsigned int		STOCK_FROM_CHANGE = 153;	//从换股来的

const unsigned int		VIEW_INDUSTRY_STOCKS	= 154;//显示行业中股票列表
const unsigned int		VIEW_CHANGE_STOCKS		= 155;//显示换股窗口

const unsigned int      RUN_HEIGHT = 23;
const unsigned int      ALERT_HEIGHT = 199;
const unsigned int      ALERT_WIDTH = 338;

const unsigned int      LOG_WIDTH = 500;
const unsigned int      LOG_HEIGHT = 400;

const unsigned int      TITILE_BUTTON_HEIGHT = 25;

const	unsigned short	INITDATA=0x0001;		//市场初始化
const	unsigned short	INITDATANEW=0x000A;		//市场初始化
const	unsigned short	TRACEDATA=0x0002;	//成交明细
const	unsigned short	REPORTDATA=0x0003;	//自选股报价
const	unsigned short	REALMINSDATA=0x0004;	//分钟走势
const	unsigned short	HISKDAYDATA=0x0005;		//历史K线日
const	unsigned short	HISKWEEKDATA=0x0006;		//历史K线周
const	unsigned short	HISKMONTHDATA=0x0007;		//历史K线月
const	unsigned short	HISKMINDATA=0x0101;			//1分钟线
const	unsigned short	HISKMIN5DATA=0x0105;			//5分钟线
const	unsigned short	HISKMIN15DATA=0x010F;			//15
const	unsigned short	HISKMIN30DATA=0x011E;			//30
const	unsigned short	HISKMIN60DATA=0x013C;			//60分钟线
const	unsigned short	REALMINSDATA2=0x0008;			//两日分时
const	unsigned short	ONLINEINITDATA=0x0009;			//在线分析师初始化

const	unsigned short	ONLINEINITDATA_A=0x0013;			//在线分析师初始化A
const	unsigned short	ONLINEINITDATA_B=0x0014;			//在线分析师初始化B
const	unsigned short	ONLINEINITDATA_C=0x0015;			//在线分析师初始化C
const	unsigned short	ONLINEINITDATA_D=0x0016;			//在线分析师初始化D
const	unsigned short	ONLINEINITDATA_E=0x0017;			//在线分析师初始化E
const	unsigned short	ONLINEINITDATA_F=0x001E;			//在线分析师初始化F

const	unsigned short	SERVERLIST		=0x0018;			//服务器列表
const	unsigned short	SENDMSG=0x0011;				//发送消息

const	unsigned short	ONLINEINITREQ=3011;//在线分析师初始化
const	unsigned short  STOCKCHANGEREQ=3014;//换股
const	unsigned short  TRADEMEMOREQ=3015;//交易备忘
const	unsigned short  MARKETTECHREQ=3016;//大盘指标资金
const	unsigned short  RPSTECHREQ=3017;//RPS指标
const	unsigned short  WEAKSTRONGTECHREQ=3018;//大盘指标强弱
const	unsigned short	STOCKPBPEREQ = 3019;//个股的PBPE历史

const	unsigned short	STOCKTECHREQ = 3030;//个股数据,以后个股的数据由此功能完成,不再有单独的请求

const	unsigned short  STOCKDIAGNOSEREQ=3013;//个股诊断 
const	unsigned short  STOCKDIAGNOSEREQNEW=3051;//个股诊断 
const	unsigned short	STOCKBLOCKREQ=3048;//板块

const	unsigned short  REPORTPARAMS=3115;	//研究报告参数
const	unsigned short	ANALYSTREQ=3116;	//研究员

const	unsigned short	STOCKDIVIDEDREQ = 3120;//个股分红信息

const	unsigned short	LINETESTREQ=0x0000;//线路测试请求包
const	unsigned short	LINETESTREP=0x0100;//线路测试应答包

const	unsigned short	LISTOFUSER=0x0019;			//在线用户列表
const	unsigned short	OFFLINEUSER=0x001A;			//让用户下线
const	unsigned short	ISUSERONLINE=0x001B;		//用户是否在线
const	unsigned short	REPORTURL=0x001C;			//研究报告URL
const	unsigned short	UPGRADEFILE=0x001D;			//下载升级文件

const	unsigned short	STOCKBASEDATA=0x0021;		//股票基础数据
const	unsigned short	COLLECTSORT=0x0022;			//综合排行
const	unsigned short	USERDEFREPORTDATA=0x0023;	//自定义报价表
const	unsigned short	QUOTESORTDATA=0x0024;		//标准排行榜
const	unsigned short	INVEST66SORT=0x0025;		//66排行
const	unsigned short	INVESTINDUTOTAL=0x0026;		//行业统计
const	unsigned short	BESTSTOCKS=0x0027;			//龙虎榜

const	unsigned short	MACRODATA=0x0028;			//宏观数据
const	unsigned short	STOCKTRADEDATA=0x0029;			//股票交易数据
const	unsigned short	STOCKSELECTDATA=0x0030;		//股票自选数据
const	unsigned short	TABLEDATA=0x0031;			//自定义字段数据,MACRODATA指定的是类型，在服务端转换成字段
const	unsigned short	BUYSALELIST=0x0032;			//买卖队列
const	unsigned short	REALPUSHREQ=0x1000;	//推送请求

#define REAL_PUSH_REQ					4096	//请求推送

#define ID_URL_PERSONAL_SET				101	//个性化设置
#define ID_URL_NEWS_SET					102 //资讯定制
#define ID_URL_STOCK					103 //个股
#define ID_URL_NEWS						104 //资讯
#define ID_URL_SERVICE					105 //服务
#define ID_URL_INDEX					106 //指数

//权限
#define	ROLE_YJBG						0x0001		//研究报告
#define ROLE_YJBG_HZ					0x0002		//合作机构
#define ROLE_YJBG_FHZ					0x0004		//非合作机构
#define ROLE_HLDXG						0x0008		//红绿灯选股
#define ROLE_LEDS_HIST					0x0010		//红绿灯历史
#define ROLE_LEDS_CHANGE				0x0020		//红绿灯变化
#define ROLE_ALERT						0x0040		//交易预警
#define ROLE_PRICE_ALERT				0x0080		//价格提示
#define ROLE_MARKET_RADA				0x0100		//市场雷达
#define ROLE_TRADE_AREA					0x0200		//交易区间
#define ROLE_CUT_LINE					0x0400		//止损线
#define ROLE_MACRO_DATA					0x0800		//宏观数据
#define ROLE_NBJY						0x1000		//内部交易
#define	ROLE_JGMM						0x2000		//机构买卖



/// 定义行情源发送过来的数据的列标志
#define  FD_ZRSP                 1
#define  FD_JRKP                 2
#define  FD_ZJCJ                 3
#define  FD_CJSL                 4
#define  FD_CJJE                 5
#define  FD_CJBS                 6
#define  FD_ZGCJ                 7
#define  FD_ZDCJ                 8
#define  FD_SYL1                 9
#define  FD_SYL2                10
#define  FD_JSD1                11
#define  FD_JSD2                12
#define  FD_HYCC                13
#define  FD_SJW5                14
#define  FD_SSL5                15
#define  FD_SJW4                16
#define  FD_SSL4                17
#define  FD_SJW3                18
#define  FD_SSL3                19
#define  FD_SJW2                20
#define  FD_SSL2                21
#define  FD_SJW1                22
#define  FD_SSL1                23
#define  FD_BJW1                24
#define  FD_BSL1                25
#define  FD_BJW2                26
#define  FD_BSL2                27
#define  FD_BJW3                28
#define  FD_BSL3                29
#define  FD_BJW4                30
#define  FD_BSL4                31
#define  FD_BJW5                32
#define  FD_BSL5                33
#define  FD_XXJYDW				34
#define  FD_XXMGMZ				35
#define  FD_XXZFXL				36
#define  FD_XXLTGS				37
#define  FD_XXSNLR				38
#define  FD_XXBNLR				39
#define  FD_XXJSFL				40
#define  FD_XXYHSL				41
#define  FD_XXGHFL				42
#define  FD_XXMBXL				43
#define  FD_XXBLDW				44
#define  FD_XXSLDW				45
#define  FD_XXJGDW				46
#define  FD_XXJHCS				47
#define  FD_XXLXCS				48
#define  FD_XXXJXZ				49
#define  FD_XXZTJG				50
#define  FD_XXDTJG				51
#define  FD_XXZHBL				52


#define QFD_STOCKCODE	1
#define QFD_STOCKNAME	2
#define QFD_ZRSP		3
#define QFD_JRKP		4
#define QFD_ZTJG		5
#define QFD_DTJG		6
#define QFD_SYL1		7
#define QFD_SYL2		8
#define QFD_ZGJG		9
#define QFD_ZDJG		10
#define QFD_ZJJG		11
#define QFD_ZJCJ		12				
#define QFD_CJSL		13
#define QFD_CJJE		14
#define QFD_CJBS		15
#define QFD_BP1			16
#define QFD_BM1			17
#define QFD_BP2			18
#define QFD_BM2			19
#define QFD_BP3			20
#define QFD_BM3			21
#define QFD_BP4			22
#define QFD_BM4			23
#define QFD_BP5			24
#define QFD_BM5			25
#define QFD_SP1			26
#define QFD_SM1			27
#define QFD_SP2			28
#define QFD_SM2			29
#define QFD_SP3			30
#define QFD_SM3			31
#define QFD_SP4			32
#define QFD_SM4			33
#define QFD_SP5			34
#define QFD_SM5			35
#define QFD_5RPJZS		36
#define QFD_PJJG		37
#define QFD_WB			38
#define QFD_LB			39
#define QFD_NP			40
#define QFD_WP			41
#define QFD_ZDF			42
#define QFD_ZF			43

#pragma pack(1)
//行情结构
struct Quote
{
	int	nStockId;						//Id
	char szStockCode[STOCK_CODE_LEN];	//品种代码
	char szStockName[STOCK_NAME_LEN];	//股票简称
	unsigned int zrsp;					//昨收
	unsigned int jrkp;					//今开
	unsigned int ztjg;					//涨停价
	unsigned int dtjg;					//跌停价
	unsigned int syl1;					//市盈率1
	unsigned int syl2;					//市盈率2
	unsigned int zgjg;					//最高价格
	unsigned int zdjg;					//最低价格
	unsigned int zjjg;					//最近成交价
	unsigned int zjcj;					//最近成交量
	unsigned int cjsl;					//总成交量
	unsigned int cjje;					//成交金额
	unsigned int cjbs;					//成交笔数
	unsigned int BP1;
	unsigned int BM1;
	unsigned int BP2;
	unsigned int BM2;
	unsigned int BP3;
	unsigned int BM3;
	unsigned int BP4;
	unsigned int BM4;
	unsigned int BP5;
	unsigned int BM5;
	unsigned int SP1;
	unsigned int SM1;
	unsigned int SP2;
	unsigned int SM2;
	unsigned int SP3;
	unsigned int SM3;
	unsigned int SP4;
	unsigned int SM4;
	unsigned int SP5;
	unsigned int SM5;

	unsigned int MBP1;
	unsigned int MBM1;
	unsigned int MBP2;
	unsigned int MBM2;
	unsigned int MBP3;
	unsigned int MBM3;
	unsigned int MBP4;
	unsigned int MBM4;
	unsigned int MBP5;
	unsigned int MBM5;
	unsigned int MSP1;
	unsigned int MSM1;
	unsigned int MSP2;
	unsigned int MSM2;
	unsigned int MSP3;
	unsigned int MSM3;
	unsigned int MSP4;
	unsigned int MSM4;
	unsigned int MSP5;
	unsigned int MSM5;

	unsigned int day5pjzs;				//5日平均总手
	unsigned int pjjg;					//均价
	int wb;								//委比
	unsigned int lb;					//量比
	unsigned int np;					//内盘
	unsigned int wp;					//外盘
	int zd;
	int zdfd;							//涨跌幅
	int zf;								//振幅
	//增加
	int hsl;							//换手率
};

//分笔成交结构
struct TickUnit
{
	unsigned int Time;					//时间，格式：HHMM
	unsigned int Price;					//成交价
	unsigned int Volume;				//成交量
	unsigned char Way;					//成交方向，0-未知，1-内盘，2-外盘
};

struct TickBlock
{
	TickUnit unit[TICK_PERBLOCK];
	unsigned int next;
};

//内存分钟K线结构
struct MinUnit
{
	unsigned int Time;					//时间，格式：HHMM
	unsigned int OpenPrice;
	unsigned int MaxPrice;
	unsigned int MinPrice;
	unsigned int NewPrice;
	unsigned int Volume;
	unsigned int AvgPrice;				//均价
};

struct MinBlock
{
	MinUnit unit[MINK_PERBLOCK];
	unsigned int next;
};

struct RINDEX
{
	int idxQuote;				//行情索引
	int idxTick;				//分笔成交索引
	int cntTick;				//分笔成交个数
	int idxMinK;				//分钟K线索引
	int cntMinK;				//分钟K线个数
};

//个股
struct SStock
{
	CString m_strName;	
	char m_acKind[STOCK_KIND_LEN + 1];
	char m_acSpell[STOCK_SPELL_LEN + 1];
	unsigned int m_unPrevClose;
	Quote m_sQuote;
	double m_dZgb;//总股本
	double m_dLtg;//流通股
	float	m_fRJCG;//人均持股

	double	m_dValue;//总市值
	double  m_dLtValue;//流通市值

	int m_nMinItemCount;
	char * m_pMinData;//数据
	int m_nLastMinTime;//最后分钟
	bool m_bIsMaker;//是否是庄家

	void init()
	{
		memset(&m_sQuote,0,sizeof(Quote));
		m_nMinItemCount = 0;
		m_pMinData = NULL;//数据
		m_nLastMinTime = 0;
		m_bIsMaker = false;
	}
};

//通讯的头部
struct SCommHead{
	CommxHead	m_head;//标准头
	unsigned short	m_usFuncNo;//功能编号
	unsigned short m_usReqCount;//包的命令个数
};
struct tagUserLogReq
{
	int			nEncrypt;
	char		acCode[64];
	char		acPass[64];
};

struct tagUserInfo
{
	int				nMemberType;//会员类型
	unsigned int    nUserId;          //用户编号
	char			szLoginCode[64];	//登陆名称
	char            szNickName[64];   //昵称
};

struct tagChangePass
{
	int				nUserId;//用户ID
	char			acCode[16];//代码
	char			acPass[32];//现密码
	char			acNewPass[32];//新密码
	int				nType;//0查询密码，1交易密码
};

struct tagPass
{
	int			nId;
	char		acCode[16];
	char		acPass[32];
};

struct tagAccount//帐户信息
{
	float		fAssets;//总资产
	float		fCash;//现金总额
	float		fFreezeCash;//冻结现金
	float		fProfit;//盈亏
};

struct tagPosition//持仓
{
	int		nStockId;
	int		nAmount;//数量
	int		nFreezeAmount;//冻结数量
	float	fCost;//成本价格
	int		nBuyToDay;
	int		nSellToday;
};

struct tagConsign
{
	int		nOperate;//操作，1委托买，2委托卖，3撤单
	int		nStockId;	
	int		nAmount;//数量
	float	fPrice;//价格
	int		nConsignID;//对于撤单此值为待撤单的委托号
};

struct tagMakerConsignReq//庄家委托
{
	int		nStockId;//股票Id
	int		nBuyAmount;//买入数量
	float	fBuyPrice;//买入价格
	int		nSaleAmount;//卖出数量
	float	fSalePrice;//卖出价格
	int		nType;//0追加，1撤销先前的委托
};

struct tagConsignHistoryReq
{
	char	acBeginDate[24];
	char	acEndDate[24];
};

struct tagConsignHistory//委托历史
{
	int		nConsignID;//委托号
	int		nOperate;
	int		nStockId;
	int		nAmount;
	float	fPrice;
	int		nBargainAmount;
	int		nState;
	char	acDateTime[24];
};

struct tagBargainReq
{
	char	acBeginDate[24];
	char	acEndDate[24];
};

struct tagBargain
{
	int		nConsignID;//委托号
	int		nOperate;
	int		nStockId;
	int		nAmount;
	float	fMoney;
	float	fPrice;
	float	fFee;
	int		nState;
	char	acDateTime[24];
};

//函数定义
class CData;
typedef void (*_SetData)(CData * c_pData);
typedef CWnd *(*_CreateWnd)(char *,CRect *,CWnd *,unsigned short c_usID);
typedef int  (*_DoCmd)(CWnd *,char *);
//发送数据,数据包中seq高位为c_usID,低两位为真正的序号
typedef int (*_SendData)(CWnd * c_pWnd,char * c_pData,int c_nLen,bool c_bWaitReturn);
//处理收到的数据
typedef int (*_OnRecvData)(char * c_pWndName,CWnd * c_pWnd,char * c_pData,int c_nLen);
//
typedef void (*_OnMessage)(char * c_pWndName,CWnd * c_pWnd,MSG * c_pMsg);
//设置SendData函数
typedef void (*_SetSendData)(_SendData c_p);
//Wnd dll接口
struct SWndDllInterface
{
	_CreateWnd	m_pCreateWnd;//创建窗口
	_DoCmd		m_pDoCmd;//执行命令
	_SendData	m_pSendData;//发送数据
	_OnRecvData	m_pOnRecvData;//处理接收到的数据
	_OnMessage  m_pOnMessage;
};
struct SDllDef
{
	HMODULE	m_hHandle;
	char m_acDllFile[MAX_PATH];
	SWndDllInterface m_interFace;
};

struct SQuickKey
{
	char m_acKeyDesc[20];
	char m_acKey[8];
};

#pragma pack()

#endif
