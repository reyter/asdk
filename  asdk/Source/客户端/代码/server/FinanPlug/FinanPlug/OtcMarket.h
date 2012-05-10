#pragma once
#include <map>
#include <vector>

typedef enum{IDLE=0,PREOPEN,ONTRADE,PAUSE,CLOSED,NOTWORKDAY,NOTWORKTIME} MarketState;//�г�״̬

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
//IDLE ����													 00:00-9:20
//OPEN����ǰ׼�������Ͼ���ǰ׼�����µ����ݣ����¹�Ʊ�б�	 9:20-9:30
//ONTRADE����ʼ���ף����ձ��ۣ����							 9:30-11:30
//PAUSE����ʱֹͣ���ף����ձ��ۣ�����ϣ�����������			 11:30-13:00
//ONTRADE													 13:00-15:00
//CLOSED��������											 15:00-24:00
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

	void InitSections();//��ʼ��ʱ������
	MarketState CheckMarketState(int c_nTime);//���״̬
	int OnNewMarketState(MarketState c_nOldState,MarketState c_nNewState,int,int,int);//�����µ�״̬

	void OpenMarket(int);
	void CloseMarket();
	void EnterOnTrade();//���빤��״̬

	int	GetStockDelegate(int &c_nLastId);
	void DealStockDelegate(tagStockDelegate * c_pItem);
	void UpdateStockCurrent(Quote * c_pQuote,int c_nState);

	int OnConsign(int c_nMemberId,int c_nStockId,int c_nAmount,float c_fPrice,int c_nOperate,int c_nMakerDelegateId=0);//��ί��
	int OnCancelConsign(tagStockDelegate * c_pItem);//����ί��
	int OnCompleteConsign(tagStockDelegate * c_pItem);//���ί��

	int CheckConsign(int c_nMemberId,int c_nStockId,int c_nAmount,float c_fPrice,int c_nOperate);//���ί�У�����<0���ܽ���
	int CheckMakerConsign(int c_nMberId,int c_nStockId,int c_nAmountBuy,float c_fPriceBuy,int c_AmountSale,float c_fPriceSale);//���ׯ��ί�У�����<0���ܽ���
public:
	CDataProcess * m_pDataProc;
	CWorkThread* m_pTradeThread;	  //�����߳�
	MarketState  m_msState;//�г�״̬
	BOOL		 m_bTradeThreadRun;		//�����߳����б�־
	char		 m_acTradeDate[24];	//ʱ��

	int						m_nTradeDay;//������
	int						m_nTradeTime;//����ʱ��
	int						m_nMinuteTime;//����ʱ��
	int						m_nLastStockDelegateId;//�ϴ�ί�к�
	std::map<int,void *>	m_mapStock;//��Ʊ����

	std::vector<tagSection *>	m_vecSections;
};
