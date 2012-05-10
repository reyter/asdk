#include "StdAfx.h"
#include "OtcMarket.h"
#include "WorkThread.h"
#include "FinanPlugDef.h"
#include "StockQueue.h"
#include "DataProcess.h"
#include "Calc.h"
#include "../../public/data_struct.h"
#include "../../public/ShareData.h"

extern CShareData		g_ShareData;
extern SSystemParam		g_SystemParam;

COtcMarket::COtcMarket(void)
{
	m_nTradeDay = 0;//������
	m_nTradeTime = 0;//����ʱ��
	m_nLastStockDelegateId = 0;//�ϴ�ί�к�
	m_msState = IDLE;
	m_bTradeThreadRun = TRUE;
}

COtcMarket::~COtcMarket(void)
{
}

int COtcMarket::Init()
{
	m_pDataProc = new CDataProcess();
	m_pDataProc->InitDB();
	InitSections();
	m_pTradeThread = new CWorkThread(_TradeThread, this);
	if (m_pTradeThread == NULL)
	{
		REPORT(MN, T("���������߳�ʧ�ܣ�new CWorkThread() failed\n"), RPT_ERROR);
		return -1;
	}
	REPORT(MN, T("���������̳߳ɹ���\n"), RPT_INFO);
	if (!m_pTradeThread->Start())
	{
		REPORT(MN, T("���������߳�ʧ�ܣ�m_pTradeThread->Start() failed\n"), RPT_ERROR);
		return -1;
	}
	return 0;
}

void COtcMarket::Uninit()
{
	m_bTradeThreadRun = FALSE;
	if (m_pTradeThread != NULL)
	{
		m_pTradeThread->Stop();
		delete m_pTradeThread;
		m_pTradeThread = NULL;
	}
	delete m_pDataProc;
}

void COtcMarket::InitSections()//��ʼ��ʱ������
{
	while(m_vecSections.size())
	{
		delete m_vecSections.back();
		m_vecSections.pop_back();
	}
	tagSection * pItem = NULL;
	pItem = new tagSection();
	pItem->Set(000000, 92000,0,IDLE);
	m_vecSections.push_back(pItem);

	pItem = new tagSection();
	pItem->Set( 92000, 93000,0,PREOPEN);
	m_vecSections.push_back(pItem);

	pItem = new tagSection();
	pItem->Set( 93000,113000,0,ONTRADE);
	m_vecSections.push_back(pItem);

	pItem = new tagSection();
	pItem->Set(113000,130000,0,PAUSE);
	m_vecSections.push_back(pItem);

	pItem = new tagSection();
	pItem->Set(130000,150000,0,ONTRADE);
	m_vecSections.push_back(pItem);
	pItem = new tagSection();
	pItem->Set(150000,240000,0,CLOSED);
	m_vecSections.push_back(pItem);
}

MarketState COtcMarket::CheckMarketState(int c_nTime)//��鵱ǰ״̬
{
	std::vector<tagSection *>::iterator iter;
	for(iter=m_vecSections.begin(); iter!=m_vecSections.end(); iter++)
	{
		if ((*iter)->nBegin <= c_nTime && (*iter)->nEnd > c_nTime)
		{
			return (*iter)->state;
		}
	}
}

int COtcMarket::OnNewMarketState(MarketState c_nOldState,MarketState c_nNewState,int c_nRunDay,int c_nRunTime,int c_nRunMinute)//�µ�״̬
{
	if (c_nNewState == PREOPEN)//����ǰ
	{
		OpenMarket(c_nRunDay);
		return 1;
	}
	else
	if (c_nNewState == ONTRADE)//�ȴ����̣����ռ��Ͼ��۽���
	{
		if (m_nTradeDay != c_nRunDay)
			OpenMarket(c_nRunDay);
			EnterOnTrade();
		return 1;
	}	
	else
	if (c_nNewState == ONTRADE)//��ͣ
	{
		if (m_nTradeDay != c_nRunDay)
			OpenMarket(c_nRunDay);
		return 1;
	}
	else
	if (c_nNewState == CLOSED)//����
	{
		if (m_nTradeDay != c_nRunDay)
			OpenMarket(c_nRunDay);
		CloseMarket();
		return 1;
	}
	return 0;
}

UINT COtcMarket::_TradeThread(void* pParam)
{
	COtcMarket* pDataPro = (COtcMarket*)pParam;
	return pDataPro->TradeThread();
}

UINT COtcMarket::TradeThread()
{
	MarketState nCurMarketState = IDLE;
	
	m_bTradeThreadRun = TRUE;
	bool bFirst = true;
	m_pDataProc->InitStockInfo();
	m_pDataProc->GetSystemParam();
	int nnn = 0;
	int nGet = 0;
	bool bWorkDay = true;//�Ƿ��ǹ�����
	int  nRunDay = 0;//��ǰ��
	int	 nRunTime = 0;//��ǰʱ��
	int  nRunMinuteTime = 0;//��ǰ���Ӽ�ʱ

	m_nTradeDay = g_ShareData.GetWorkDay();//��ǰ������
	m_nTradeTime = g_ShareData.GetWorkTime();//��ǰ����ʱ��
	m_nMinuteTime = g_ShareData.GetWorkMinuteTime();//��ǰ����ʱ��,�����Ӽ���
	nCurMarketState = CheckMarketState(m_nTradeTime);
	REPORT(MN,T("TradeDay=%d TradeTime=%d MarketState=%d\n",m_nTradeDay,m_nTradeTime,nCurMarketState),RPT_INFO);
	while(m_bTradeThreadRun)
	{
		time_t cur;
		time(&cur);
		struct tm *ltCur = localtime(&cur);
		unsigned int unYear = ltCur->tm_year + 1990;
		unsigned int unMonth = ltCur->tm_mon + 1;
		unsigned int unDay = ltCur->tm_mday;
		unsigned int unHour = ltCur->tm_hour;
		unsigned int unMinute = ltCur->tm_min;
		unsigned int unSecond = ltCur->tm_sec;
		nRunDay = unYear * 10000 + unMonth * 100 + unDay;		
		nRunTime = unHour*10000 + unMinute * 100 + unSecond;
		nRunMinuteTime = unHour*60 + unMinute;
		sprintf(m_acTradeDate,"%d-%d-%d",unYear,unMonth,unDay);

		if (nRunDay != m_nTradeDay)//�µ�����
		{
			if (ltCur->tm_wday != 0 && ltCur->tm_wday != 6)
				bWorkDay = m_pDataProc->IsWorkDay(nRunDay);
			else
				bWorkDay = false;
			if(bWorkDay)
			{
				REPORT(MN,T("%d �ǹ�����\n",nRunDay),RPT_INFO);
				m_msState = NOTWORKTIME;//�����趨Ϊ�ǹ���ʱ��
			}
			else
			{
				REPORT(MN,T("%d �ǹ�����\n",nRunDay),RPT_INFO);
				m_msState = NOTWORKDAY;
			}
		}
		if (bWorkDay == false)//�ǹ�����
		{			
			g_ShareData.SetState(NOTWORKDAY);//���óɷǹ�����
			GetStockDelegate(m_nLastStockDelegateId);
			Sleep(1000);
			continue;
		}
		MarketState nNewMarketState = CheckMarketState(unHour*10000 + unMinute * 100 + unSecond);
		if (nNewMarketState != nCurMarketState)//״̬�����仯
		{
			OnNewMarketState(nCurMarketState,nNewMarketState,nRunDay,nRunTime,nRunMinuteTime);
		}
		if (m_nTradeDay == nRunDay)
		{
			m_nTradeTime = unHour*10000 + unMinute * 100 + unSecond;
			m_nMinuteTime = unHour*60 + unMinute;
			g_ShareData.SetWorkMinuteTime(m_nMinuteTime);
			nCurMarketState = nNewMarketState;
			m_msState = nNewMarketState;

			g_ShareData.SetState(m_msState);
			g_ShareData.SetWorkTime(m_nTradeTime);
		}
		else
		{
			//�ǹ���ʱ��
		}
		nGet = GetStockDelegate(m_nLastStockDelegateId);
		if (nGet != 0)
			REPORT(MN,T("TradeThread nGet = %d,LastId = %d\n",nGet,m_nLastStockDelegateId),RPT_INFO);
		
		Sleep(1000);
	}
	return 0;
}

//���̶���
//�����µĹ�Ʊ�б�
//��ʼ����������
//��������
void COtcMarket::OpenMarket(int c_nDay)
{
	REPORT(MN,T("PreOpenMarket %d======================================\n",c_nDay),RPT_INFO);
	m_pDataProc->GetSystemParam();
	m_pDataProc->InitStockInfo();

	m_nTradeDay = c_nDay;
	g_ShareData.SetWorkDay(m_nTradeDay);

	int nIndex = 0;
	while(true)
	{
		Quote *pQuote = (Quote *)g_ShareData.GetStockByIndex(nIndex++);
		if (pQuote == NULL)
			return;
		REPORT(MN,T("PreOpenMarket stock=%d zsrp=%d ipo=%d======================================\n",pQuote->nStockId,pQuote->zrsp,pQuote->ipoprice),RPT_INFO);
		if (pQuote->zrsp > 0)
			pQuote->Open(pQuote->zrsp,g_SystemParam.fUpLimit,g_SystemParam.fDownLimit);
		else
			pQuote->Open(pQuote->ipoprice,0.2,0.2);//����

		int nStockId = pQuote->nStockId;
		CStockQueue * pStockQueue = NULL;
		if (m_mapStock.find(nStockId) == m_mapStock.end())
		{
			pStockQueue = new CStockQueue(nStockId,m_pDataProc);
			m_mapStock[nStockId] = (void *)pStockQueue;
		}
		else
			pStockQueue = (CStockQueue *)m_mapStock[nStockId];
		if (pStockQueue)
		{
			pStockQueue->Open();
			pStockQueue->FreshQuote();
		}
		//StockCurrent
		UpdateStockCurrent(pQuote,-1);
	}
}

//���̶���
void COtcMarket::CloseMarket()
{
	int nIndex = 0;
	REPORT(MN,T("CloseMarket======================================\n"),RPT_INFO);
	while(true)
	{
		Quote *pQuote = (Quote *)g_ShareData.GetStockByIndex(nIndex++);
		if (pQuote == NULL)
			return;

		int nStockId = pQuote->nStockId;
		CStockQueue * pStockQueue = NULL;
		if (m_mapStock.find(nStockId) != m_mapStock.end())
			pStockQueue = (CStockQueue *)m_mapStock[nStockId];
		if (pStockQueue)
		{
			pStockQueue->Close();
		}
		pQuote->Close();
		if (pQuote->cjsl == 0)
			UpdateStockCurrent(pQuote,0);
		UpdateStockCurrent(pQuote,1);
	}
}

//����OnTrade
void COtcMarket::EnterOnTrade()
{
	int nIndex = 0;
	int nAuctionAmount = 0;
	float fAuctionPrice = 0;
	REPORT(MN,T("EnterOnTrade======================================\n"),RPT_INFO);
	while(true)
	{
		Quote *pQuote = (Quote *)g_ShareData.GetStockByIndex(nIndex++);
		if (pQuote == NULL)
			return;

		int nStockId = pQuote->nStockId;
		CStockQueue * pStockQueue = NULL;
		if (m_mapStock.find(nStockId) != m_mapStock.end())
			pStockQueue = (CStockQueue *)m_mapStock[nStockId];
		if (pStockQueue)
		{
			nAuctionAmount = 0;
			fAuctionPrice = 0;
			pStockQueue->Match();
			pStockQueue->OutPut();
			UpdateStockCurrent(pQuote,0);
			pStockQueue->FreshQuote();
		}
	}
}

int COtcMarket::GetStockDelegate(int &c_nLastId)
{
	CRecordSet recset(&m_pDataProc->m_sqlServUser);
	char acSql[1024];

	//sprintf(acSql,"SELECT * FROM StockDelegate WHERE (Status=1 or Status=2) and StockDelegateID>%d and convert(int,CONVERT(varchar(12),DelegateDate,112))>=%d order by StockDelegateId",m_nLastStockDelegateId,m_nTradeDay);
	sprintf(acSql,"SELECT * FROM StockDelegate WHERE (Status=1 or Status=2) and StockDelegateID>%d and CancelDate is null  order by StockDelegateId",c_nLastId);

	if (!recset.Open(acSql))
	{
		REPORT(MN, T("Open [%s] failed\n", acSql), RPT_ERROR);
		if (m_pDataProc->CheckUserDBConnect())
		{
			if (!recset.Open(acSql))
				return -1;
		}
		else return -1;
	}

	int nCount = 0;
	tagStockDelegate	item;
	double dPrice;
	while(!recset.IsEOF())
	{
		int nId;
		recset.GetCollect("STOCKDELEGATEID",item.nStockDelegateId);
		recset.GetCollect("STOCKID", item.nStockId);
		recset.GetCollect("MEMBERID", item.nMemberId);
		recset.GetCollect("AMOUNT",item.nAmount);
		recset.GetCollect("AMOUNTDONE",item.nAmountDone);
		recset.GetCollect("AMOUNTLEFT",item.nAmountLeft);
		recset.GetCollect("DELEGATEDATE",item.acDelegateDate,24);
		recset.GetCollect("PRICE",dPrice);
		item.fPrice = dPrice;
		recset.GetCollect("BUYSALE",item.nBuySale);
		recset.GetCollect("STATUS",item.nStatus);
		recset.GetCollect("CANCELID",item.nCancelId);
		recset.GetCollect("MakerQuoteDetailID",item.nMakerQuoteDetailId);
		recset.MoveNext();
		nCount++;
		c_nLastId = item.nStockDelegateId;
		if ((item.nBuySale == 0 || item.nBuySale == 1) && item.nAmountLeft > 0)
			DealStockDelegate(&item);
		else
		if (item.nBuySale == 2)
			DealStockDelegate(&item);
	}
	recset.Close();
	return nCount;
}

void COtcMarket::DealStockDelegate(tagStockDelegate * c_pItem)
{
	CStockQueue * pStockQueue = NULL;
	int nAuctionAmount = 0;
	float fAuctionPrice = 0;
	if (m_mapStock.find(c_pItem->nStockId) == m_mapStock.end())
	{
		pStockQueue = new CStockQueue(c_pItem->nStockId,m_pDataProc);
		m_mapStock[c_pItem->nStockId] = (void *)pStockQueue;
	}
	else
		pStockQueue = (CStockQueue *)m_mapStock[c_pItem->nStockId];
	if (pStockQueue)
	{
		if (c_pItem->nBuySale == 0 || c_pItem->nBuySale == 1)
		{
			pStockQueue->AddConsign(c_pItem);//�ȼ��뵽������
			if(m_msState == ONTRADE)
			{
				pStockQueue->Match(c_pItem);//�Դ�ί�н��д��
				pStockQueue->OutPut();
			}
		}
		else
		if (c_pItem->nBuySale == 2)
		{
			int nRet = pStockQueue->CancelConsign(c_pItem);
			if (nRet > 0)
			{
				if (m_msState == ONTRADE)
				{
					pStockQueue->OutPut();
				}
			}
			else//û���ҵ���Ӧ������Ŀ
			{

			}
		}
		pStockQueue->FreshQuote();
	}
}

void COtcMarket::UpdateStockCurrent(Quote * c_pQuote,int c_nState)
{
	if (c_nState == -1)
	{
		char acSql[1024];
		sprintf(acSql,"insert into StockCurrent(StockId,StockDate,LastClosePrice,TodayOpenPrice,CurrentPrice,TodayClosePrice,HighPrice,LowPrice,ChangeRate,ChangePrice,DoneAmount,DoneMoney,Status) values(%d,'%s',%.3f,0,0,0,0,0,0,0,0,0,1)",c_pQuote->nStockId,m_acTradeDate,float(c_pQuote->zrsp)/1000);
		m_pDataProc->m_sqlServUser.Execute(acSql);
		return;
	}
	if (c_nState == 0)
	{
		char acSql[1024];
		sprintf(acSql,"update StockCurrent set TodayOpenPrice=%.3f,CurrentPrice=%.3f,HighPrice=%.3f,LowPrice=%.3f,ChangeRate=%.3f,ChangePrice=%.3f,DoneAmount=%d,DoneMoney=%.3f where StockId=%d and status=1",float(c_pQuote->jrkp)/1000,float(c_pQuote->zjjg)/1000,float(c_pQuote->zgjg)/1000,float(c_pQuote->zdjg)/1000,float(c_pQuote->zdf)/1000,float(c_pQuote->zd)/1000,c_pQuote->cjsl,float(c_pQuote->cjje)/1000,c_pQuote->nStockId);
		m_pDataProc->m_sqlServUser.Execute(acSql);
		REPORT(MN,T("UPDATESTOCKCURRENT:%s\n",acSql),RPT_INFO);
		return;
	}
	if (c_nState == 1)
	{
		char acSql[1024];
		sprintf(acSql,"update StockCurrent set Status=0,TodayClosePrice=%.3f where StockId=%d and status=1",float(c_pQuote->zjjg)/1000,c_pQuote->nStockId);
		m_pDataProc->m_sqlServUser.Execute(acSql);
		return;
	}
}

int COtcMarket::CheckConsign(int c_nMemberId,int c_nStockId,int c_nAmount,float c_fPrice,int c_nOperate)
{
	return 1;
}

int COtcMarket::CheckMakerConsign(int c_nMemberId,int c_nStockId,int c_nAmountBuy,float c_fPriceBuy,int c_nAmountSale,float c_fPriceSale)
{
	return 1;
}

int COtcMarket::OnConsign(int c_nMemberId,int c_nStockId,int c_nAmount,float c_fPrice,int c_nOperate,int c_nMakerDelegateId)//��ί��
{
	CRecordSet recset(&m_pDataProc->m_sqlServUser);

	char acSql[256];
	sprintf(acSql,"select * from StockDelegate where MemberId=%d and StockId=%d",c_nMemberId,c_nStockId);
	if (!recset.Open(acSql))
		return 0;
	
	if (!recset.AddNew())
	{
		recset.Close();
		return 0;
	}
	recset.PutCollect("MemberId",long(c_nMemberId));
	recset.PutCollect("StockId",long(c_nStockId));
	recset.PutCollect("Amount",long(c_nAmount));
	recset.PutCollect("Price",double(c_fPrice));
	char acTime[24];
	FormatSysDateTime(acTime);	
	recset.PutCollect("DelegateDate",acTime);
	recset.PutCollect("AmountDone",long(0));
	recset.PutCollect("AmountLeft",long(c_nAmount));
	recset.PutCollect("Status",long(1));
	recset.PutCollect("BuySale",long(c_nOperate));
	recset.PutCollect("Sign",long(1));
	recset.PutCollect("OperatorName","otchkclient");
	double dFee = g_SystemParam.CalcFee(c_nOperate,c_fPrice*c_nAmount);
	recset.PutCollect("TotalFee",double(dFee));
	recset.PutCollect("MakerQuoteDelegateId",long(c_nMakerDelegateId));
	recset.Update();
	int nId = 0;
	recset.GetCollect("StockDelegateId",nId);
	recset.Close();
	REPORT(MN,T("OnConsgin StockDelegateId = %d\n",nId),RPT_INFO);
	
	if (c_nOperate == 1)
	{
		//��Ʊ̨������
		m_pDataProc->RecordStockBook(0,0,nId,c_nMemberId,c_nMemberId,c_nStockId,0,c_nAmount);//̨����,�������ʱ��ȥ
	}
	else
	if(c_nOperate == 0)
	{
		//�ʽ�̨������
		m_pDataProc->RecordMoneyBook(0,0,nId,c_nMemberId,c_nMemberId,0,c_nAmount * c_fPrice + dFee,0);//̨����,,�������ʱ��ȥ
	}
	return 1;
						//sprintf(acSql,"insert into StockDelegate(StockId,MemberId,Price,Amount,DelegateDate,AmountDone,AmountLeft,Status,BuySale,OperatorName,Sign,totalfee)\
			//values(%d,%d,%.3f,%d,GETDATE(),0,%d,1,0,'client',1,0)",pConsign->nStockId,pPass->nId,pConsign->fPrice,pConsign->nAmount,pConsign->nAmount);
}

int COtcMarket::OnCancelConsign(tagStockDelegate * c_pItem)//����ί��
{
	if (c_pItem->nBuySale == 0)
	{
		float fAmountDone = 0;
		float fMoneyDone = 0;
		float fDoneFee = 0;
		m_pDataProc->GetMoneyDone(c_pItem->nStockDelegateId,fAmountDone,fMoneyDone);
		fDoneFee = g_SystemParam.CalcFee(c_pItem->nBuySale,fMoneyDone);
		float fFee = g_SystemParam.CalcFee(c_pItem->nBuySale,c_pItem->nAmount * c_pItem->fPrice);
		float fReturnMoney = c_pItem->fPrice*c_pItem->nAmount + fFee - fMoneyDone - fDoneFee;
		m_pDataProc->RecordMoneyBook(1,2,c_pItem->nStockDelegateId,c_pItem->nMemberId,c_pItem->nMemberId,0,-fReturnMoney,0);//̨�ʼ�,���ü�
	}
	else
	if (c_pItem->nBuySale == 1)
	{
		m_pDataProc->RecordStockBook(1,2,c_pItem->nStockDelegateId,c_pItem->nMemberId,c_pItem->nMemberId,c_pItem->nStockId,0,-c_pItem->nAmountLeft);//̨�ʼ�,���ü�
	}
	return 1;
}

int COtcMarket::OnCompleteConsign(tagStockDelegate * c_pItem)//ί�����
{
	if (c_pItem->nBuySale == 0)
	{
		float fAmountDone = 0;
		float fMoneyDone = 0;
		float fDoneFee = 0;
		m_pDataProc->GetMoneyDone(c_pItem->nStockDelegateId,fAmountDone,fMoneyDone);
		fDoneFee = g_SystemParam.CalcFee(c_pItem->nBuySale,fMoneyDone);
		float fFee = g_SystemParam.CalcFee(c_pItem->nBuySale,c_pItem->nAmount * c_pItem->fPrice);
		float fReturnMoney = c_pItem->fPrice*c_pItem->nAmount + fFee - fMoneyDone - fDoneFee;
		m_pDataProc->AddMemberMoney(c_pItem->nMemberId,fReturnMoney  );//̨�ʵ��ʽ��ʻ�
		m_pDataProc->RecordMoneyBook(1,2,c_pItem->nStockDelegateId,c_pItem->nMemberId,c_pItem->nMemberId,-fReturnMoney,-fReturnMoney,0);//̨�ʼ�
	}
	else
	if (c_pItem->nBuySale == 1)
	{
	}
	return 1;
}
