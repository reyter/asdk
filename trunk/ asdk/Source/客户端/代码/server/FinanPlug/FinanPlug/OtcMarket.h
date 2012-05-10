#pragma once
#include <map>
#include <vector>

typedef enum{IDLE=0,PREOPEN,ONTRADE,PAUSE,CLOSED,NOTWORKDAY,NOTWORKTIME} MarketState;//市场状态

struct tagSection
{
	int			nBegin;
	int			nEnd;
	int			nIn;
	MarketState	state;
	void Set(int c_nBegin,int c_nEnd,int c_nId,MarketState c_msState)
	{
		nBegin = c_nBegin;
		nEnd = c_nEnd;
		nIn = c_nId;
		state = c_msState;
	}
};
//IDLE 空闲													 00:00-9:20
//OPEN开盘前准备，集合竞价前准备最新的数据，更新股票列表，	 9:20-9:30
//ONTRADE，开始交易，接收报价，撮合							 9:30-11:30
//PAUSE，暂时停止交易，接收报价，不撮合，不更新行情			 11:30-13:00
//ONTRADE													 13:00-15:00
//CLOSED，收盘了											 15:00-24:00
/////////////////////////////////////////////////////////////////////////////
class CDataProcess;
class CWorkThread;
struct tagStockDelegate;
struct Quote;

class COtcMarket
{
public:
	COtcMarket(void);
	~COtcMarket(void);
protected:
	static UINT WINAPI _TradeThread(void* pParam);
public:
	int Init();
	void Uninit();
	
	UINT TradeThread();

	void InitSections();//初始化时间序列
	MarketState CheckMarketState(int c_nTime);//检查状态
	int OnNewMarketState(MarketState c_nOldState,MarketState c_nNewState,int,int,int);//出现新的状态

	void OpenMarket(int);
	void CloseMarket();
	void EnterOnTrade();//进入工作状态

	int	GetStockDelegate(int &c_nLastId);
	void DealStockDelegate(tagStockDelegate * c_pItem);
	void UpdateStockCurrent(Quote * c_pQuote,int c_nState);

	int OnConsign(int c_nMemberId,int c_nStockId,int c_nAmount,float c_fPrice,int c_nOperate,int c_nMakerDelegateId=0);//新委托
	int OnCancelConsign(tagStockDelegate * c_pItem);//撤销委托
	int OnCompleteConsign(tagStockDelegate * c_pItem);//完成委托

	int CheckConsign(int c_nMemberId,int c_nStockId,int c_nAmount,float c_fPrice,int c_nOperate);//检查委托，返回<0不能接受
	int CheckMakerConsign(int c_nMberId,int c_nStockId,int c_nAmountBuy,float c_fPriceBuy,int c_AmountSale,float c_fPriceSale);//检查庄家委托，返回<0不能接受
public:
	CDataProcess * m_pDataProc;
	CWorkThread* m_pTradeThread;	  //交易线程
	MarketState  m_msState;//市场状态
	BOOL		 m_bTradeThreadRun;		//交易线程运行标志
	char		 m_acTradeDate[24];	//时间

	int						m_nTradeDay;//交易日
	int						m_nTradeTime;//交易时间
	int						m_nMinuteTime;//分钟时间
	int						m_nLastStockDelegateId;//上次委托号
	std::map<int,void *>	m_mapStock;//股票队列

	std::vector<tagSection *>	m_vecSections;
};
