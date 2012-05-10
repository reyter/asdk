#include "stdafx.h"
#include "StockQueue.h"
#include "DataProcess.h"
#include "OtcMarket.h"
#include "../../public/ShareData.h"
#include "../../public/data_struct.h"

extern CShareData		g_ShareData;
extern SSystemParam		g_SystemParam;
extern COtcMarket * g_pOtcMarket;

int CStockQueue::Match()//撮合
{
	if (g_pOtcMarket->m_msState != ONTRADE)//非开盘时间不做撮合
		return 0;
	int nMatch = 0;
	if(qBuy.size() == 0 || qSale.size() == 0)
		return 0;
	if ((*qBuy.begin())->fPrice < (*qSale.begin())->fPrice)
		return 0;
	int nMatchAmount = 0;
	float fMatchPrice = 0;
	std::list<tagStockDelegate *>::iterator iterBuy,iterSale;
	for(iterBuy=qBuy.begin(); iterBuy!=qBuy.end(); iterBuy++)
	{
		for(iterSale=qSale.begin(); iterSale!=qSale.end(); iterSale++)
		{
			if ((*iterSale)->nAmountLeft == 0)
				continue;
			if ((*iterBuy)->fPrice < (*iterSale)->fPrice)
			{
				break;
			}
			else
			if ((*iterBuy)->fPrice == (*iterSale)->fPrice)//等价
			{
				fMatchPrice = (*iterBuy)->fPrice;
			}
			else//买价大于卖价
			{
				if(fLastPrice <= (*iterSale)->fPrice)//上次成交价小于等于卖价
					fMatchPrice = (*iterSale)->fPrice;
				else
				if(fLastPrice > (*iterBuy)->fPrice)//上次成交价大于买价
					fMatchPrice = (*iterBuy)->fPrice;
				else//上次成交价在买价和卖价之间
					fMatchPrice = fLastPrice;
			}

			if (fOpen == 0)
			{
				if (g_pOtcMarket->m_nMinuteTime <= 600)//10点前成交价格算是开盘价格
					fOpen = fMatchPrice;
				else
				{
					Quote *pQuote = (Quote *)g_ShareData.GetStockById(nStockId);
					if (pQuote)
						fOpen = float(pQuote->zrsp) / 1000;
				}
			}
			if ((*iterBuy)->nAmountLeft >= (*iterSale)->nAmountLeft)
			{
				nMatchAmount = (*iterSale)->nAmountLeft;
				(*iterBuy)->nAmountLeft -= (*iterSale)->nAmountLeft;
				(*iterBuy)->nAmountDone += (*iterSale)->nAmountLeft;
				if ((*iterBuy)->nAmountLeft == 0)
					(*iterBuy)->nStatus = 4;
				else
					(*iterBuy)->nStatus = 2;
				(*iterSale)->nAmountLeft = 0;
				(*iterSale)->nStatus = 4;
				(*iterSale)->nAmountDone = (*iterSale)->nAmount;
				if (nMatchAmount > 0)
				LogMatch(*iterBuy,*iterSale,nMatchAmount,fMatchPrice);
			}
			else
			{
				nMatchAmount = (*iterBuy)->nAmountLeft;
				(*iterSale)->nAmountLeft -= (*iterBuy)->nAmountLeft;
				(*iterSale)->nAmountDone += (*iterBuy)->nAmountLeft;
				if ((*iterSale)->nAmountLeft == 0)
					(*iterSale)->nStatus = 4;
				else
					(*iterSale)->nStatus = 2;
				(*iterBuy)->nAmountLeft = 0;
				(*iterBuy)->nStatus = 4;
				(*iterBuy)->nAmountDone = (*iterBuy)->nAmount;
				if (nMatchAmount > 0)
				{
					LogMatch(*iterBuy,*iterSale,nMatchAmount,fMatchPrice);
				}
			}
			fLastPrice = fMatchPrice;
			if (fLastPrice > fHigh)
				fHigh = fLastPrice;
			if (fLastPrice < fLow || fLow == 0.0)
				fLow = fLastPrice;

			if ((*iterBuy)->nAmountLeft == 0)
				break;
		}
	}
	iterBuy = qBuy.begin();
	while(iterBuy != qBuy.end())
	{
		if ((*iterBuy)->nAmountLeft == 0)
		{
			delete *iterBuy;
			iterBuy = qBuy.erase(iterBuy);
		}
		else
			iterBuy++;
	}
	iterSale = qSale.begin();
	while(iterSale != qSale.end())
	{
		if ((*iterSale)->nAmountLeft == 0)
		{
			g_pOtcMarket->OnCompleteConsign(*iterSale);
			delete *iterSale;
			iterSale = qSale.erase(iterSale);
		}
		else
			iterSale++;
	}

	return nMatch;
};

int CStockQueue::Match(tagStockDelegate * c_pItem)//撮合
{
	int nMatch = 0;
	if((c_pItem->nBuySale == 1 && qBuy.size() == 0) || (c_pItem->nBuySale == 0 && qSale.size() == 0))
		return 0;
	if (c_pItem->nBuySale == 0)
	{
		if (c_pItem->nStockDelegateId != (*qBuy.begin())->nStockDelegateId)//不是排在第一个则不需要进行撮合
			return 0;
	}
	else
	if (c_pItem->nBuySale == 1)
	{
		if (c_pItem->nStockDelegateId != (*qSale.begin())->nStockDelegateId)//不是排在第一个则不需要进行撮合
			return 0;
	}

	int nMatchAmount = 0;
	float fMatchPrice = 0;
	std::list<tagStockDelegate *>::iterator iterBuy,iterSale;
	if (c_pItem->nBuySale == 0)//买单
	{
		iterBuy = qBuy.begin();
		for(iterSale=qSale.begin(); iterSale!=qSale.end(); iterSale++)
		{
			if ((*iterSale)->nAmountLeft == 0)
				continue;
			if ((*iterBuy)->fPrice < (*iterSale)->fPrice)
			{
				break;
			}
			else
			{
				fMatchPrice = (*iterSale)->fPrice;
			}

			if (fOpen == 0)
			{
				if (g_pOtcMarket->m_nMinuteTime <= 600)//10点前成交价格算是开盘价格
					fOpen = fMatchPrice;
				else
				{
					Quote *pQuote = (Quote *)g_ShareData.GetStockById(nStockId);
					if (pQuote)
						fOpen = float(pQuote->zrsp) / 1000;
				}
			}
			if ((*iterBuy)->nAmountLeft >= (*iterSale)->nAmountLeft)
			{
				nMatchAmount = (*iterSale)->nAmountLeft;
				(*iterBuy)->nAmountLeft -= (*iterSale)->nAmountLeft;
				(*iterBuy)->nAmountDone += (*iterSale)->nAmountLeft;
				if ((*iterBuy)->nAmountLeft == 0)
					(*iterBuy)->nStatus = 4;
				else
					(*iterBuy)->nStatus = 2;
				(*iterSale)->nAmountLeft = 0;
				(*iterSale)->nStatus = 4;
				(*iterSale)->nAmountDone = (*iterSale)->nAmount;
				if (nMatchAmount > 0)
				LogMatch(*iterBuy,*iterSale,nMatchAmount,fMatchPrice);
			}
			else
			{
				nMatchAmount = (*iterBuy)->nAmountLeft;
				(*iterSale)->nAmountLeft -= (*iterBuy)->nAmountLeft;
				(*iterSale)->nAmountDone += (*iterBuy)->nAmountLeft;
				if ((*iterSale)->nAmountLeft == 0)
					(*iterSale)->nStatus = 4;
				else
					(*iterSale)->nStatus = 2;
				(*iterBuy)->nAmountLeft = 0;
				(*iterBuy)->nStatus = 4;
				(*iterBuy)->nAmountDone = (*iterBuy)->nAmount;
				if (nMatchAmount > 0)
				{
					LogMatch(*iterBuy,*iterSale,nMatchAmount,fMatchPrice);
				}
			}
			fLastPrice = fMatchPrice;
			if (fLastPrice > fHigh)
				fHigh = fLastPrice;
			if (fLastPrice < fLow || fLow == 0.0)
				fLow = fLastPrice;
			if ((*iterBuy)->nAmountLeft == 0)
				break;
		}
	}
	else
	{
		iterSale = qSale.begin();
		for(iterBuy=qBuy.begin(); iterBuy!=qBuy.end(); iterBuy++)
		{
			if ((*iterBuy)->nAmountLeft == 0)
				continue;
			if ((*iterBuy)->fPrice < (*iterSale)->fPrice)
			{
				break;
			}
			else
			{
				fMatchPrice = (*iterBuy)->fPrice;
			}

			if (fOpen == 0)
			{
				if (g_pOtcMarket->m_nMinuteTime <= 600)//10点前成交价格算是开盘价格
					fOpen = fMatchPrice;
				else
				{
					Quote *pQuote = (Quote *)g_ShareData.GetStockById(nStockId);
					if (pQuote)
						fOpen = float(pQuote->zrsp) / 1000;
				}
			}
			if ((*iterSale)->nAmountLeft >= (*iterBuy)->nAmountLeft)
			{
				nMatchAmount = (*iterBuy)->nAmountLeft;
				(*iterSale)->nAmountLeft -= (*iterBuy)->nAmountLeft;
				(*iterSale)->nAmountDone += (*iterBuy)->nAmountLeft;
				if ((*iterSale)->nAmountLeft == 0)
					(*iterSale)->nStatus = 4;
				else
					(*iterSale)->nStatus = 2;
				(*iterBuy)->nAmountLeft = 0;
				(*iterBuy)->nStatus = 4;
				(*iterBuy)->nAmountDone = (*iterBuy)->nAmount;
				if (nMatchAmount > 0)
				LogMatch(*iterBuy,*iterSale,nMatchAmount,fMatchPrice);
			}
			else
			{
				nMatchAmount = (*iterSale)->nAmountLeft;
				(*iterBuy)->nAmountLeft -= (*iterSale)->nAmountLeft;
				(*iterBuy)->nAmountDone += (*iterSale)->nAmountLeft;
				if ((*iterBuy)->nAmountLeft == 0)
					(*iterBuy)->nStatus = 4;
				else
					(*iterBuy)->nStatus = 2;
				(*iterSale)->nAmountLeft = 0;
				(*iterSale)->nStatus = 4;
				(*iterSale)->nAmountDone = (*iterSale)->nAmount;
				if (nMatchAmount > 0)
				{
					LogMatch(*iterBuy,*iterSale,nMatchAmount,fMatchPrice);
				}
			}
			fLastPrice = fMatchPrice;
			if (fLastPrice > fHigh)
				fHigh = fLastPrice;
			if (fLastPrice < fLow || fLow == 0.0)
				fLow = fLastPrice;

			if ((*iterBuy)->nAmountLeft == 0)
				break;
		}
	}
	iterBuy = qBuy.begin();
	while(iterBuy != qBuy.end())
	{
		if ((*iterBuy)->nAmountLeft == 0)
		{
			delete *iterBuy;
			iterBuy = qBuy.erase(iterBuy);
		}
		else
			iterBuy++;
	}
	iterSale = qSale.begin();
	while(iterSale != qSale.end())
	{
		if ((*iterSale)->nAmountLeft == 0)
		{
			g_pOtcMarket->OnCompleteConsign(*iterSale);
			delete *iterSale;
			iterSale = qSale.erase(iterSale);
		}
		else
			iterSale++;
	}

	return nMatch;
};

void CStockQueue::OutPut()
	{
		while(qBuyPrice.size())
		{
			delete qBuyPrice.back();
			qBuyPrice.pop_back();
		}
		while(qSalePrice.size())
		{
			delete qSalePrice.back();
			qSalePrice.pop_back();
		}
		while(qMakerBuyPrice.size())
		{
			delete qMakerBuyPrice.back();
			qMakerBuyPrice.pop_back();
		}
		while(qMakerSalePrice.size())
		{
			delete qMakerSalePrice.back();
			qMakerSalePrice.pop_back();
		}

		tagPriceVol *pItem = NULL;
		std::list<tagStockDelegate *>::iterator iter;
		REPORT(MN, T("Queue %06d\n",nStockId), RPT_INFO);
		REPORT(MN, T("BUY %d\n",qBuy.size()), RPT_INFO);
		for(iter=qBuy.begin(); iter!=qBuy.end(); iter++)
		{
			if (pItem == NULL)
			{
				pItem = new tagPriceVol();
				pItem->fPrice = (*iter)->fPrice;
				pItem->nAmount = (*iter)->nAmountLeft;
				qBuyPrice.push_back(pItem);
			}
			else
			{
				if (pItem->fPrice == (*iter)->fPrice)
				{
					pItem->nAmount += (*iter)->nAmountLeft;
				}
				else
				{
					pItem = new tagPriceVol();
					pItem->fPrice = (*iter)->fPrice;
					pItem->nAmount = (*iter)->nAmountLeft;
					qBuyPrice.push_back(pItem);
				}
			}
			REPORT(MN, T("id=%d price=%.3f,amount=%d,amountdone=%d,amountleft=%d\n",(*iter)->nStockDelegateId,(*iter)->fPrice,(*iter)->nAmount,(*iter)->nAmountDone,(*iter)->nAmountLeft), RPT_ERROR);
		}
		pItem = NULL;
		for(iter=qBuy.begin(); iter!=qBuy.end(); iter++)
		{
			if ((*iter)->nMakerQuoteDetailId == 0)
				continue;
			if (pItem == NULL)
			{
				pItem = new tagPriceVol();
				pItem->fPrice = (*iter)->fPrice;
				pItem->nAmount = (*iter)->nAmountLeft;
				qMakerBuyPrice.push_back(pItem);
			}
			else
			{
				if (pItem->fPrice == (*iter)->fPrice)
				{
					pItem->nAmount += (*iter)->nAmountLeft;
				}
				else
				{
					pItem = new tagPriceVol();
					pItem->fPrice = (*iter)->fPrice;
					pItem->nAmount = (*iter)->nAmountLeft;
					qMakerBuyPrice.push_back(pItem);
				}
			}
		}

		pItem = NULL;
		REPORT(MN, T("SAL %d\n",qSale.size()), RPT_INFO);
		for(iter=qSale.begin(); iter!=qSale.end(); iter++)
		{
			if (pItem == NULL)
			{
				pItem = new tagPriceVol();
				pItem->fPrice = (*iter)->fPrice;
				pItem->nAmount = (*iter)->nAmountLeft;
				qSalePrice.push_back(pItem);
			}
			else
			{
				if (pItem->fPrice == (*iter)->fPrice)
				{
					pItem->nAmount += (*iter)->nAmountLeft;
				}
				else
				{
					pItem = new tagPriceVol();
					pItem->fPrice = (*iter)->fPrice;
					pItem->nAmount = (*iter)->nAmountLeft;
					qSalePrice.push_back(pItem);
				}
			}
			REPORT(MN, T("id=%d price=%.3f,amount=%d,amountdone=%d,amountleft=%d\n",(*iter)->nStockDelegateId,(*iter)->fPrice,(*iter)->nAmount,(*iter)->nAmountDone,(*iter)->nAmountLeft), RPT_ERROR);
		}
		for(iter=qSale.begin(); iter!=qSale.end(); iter++)
		{
			if ((*iter)->nMakerQuoteDetailId == 0)
				continue;
			if (pItem == NULL)
			{
				pItem = new tagPriceVol();
				pItem->fPrice = (*iter)->fPrice;
				pItem->nAmount = (*iter)->nAmountLeft;
				qMakerSalePrice.push_back(pItem);
			}
			else
			{
				if (pItem->fPrice == (*iter)->fPrice)
				{
					pItem->nAmount += (*iter)->nAmountLeft;
				}
				else
				{
					pItem = new tagPriceVol();
					pItem->fPrice = (*iter)->fPrice;
					pItem->nAmount = (*iter)->nAmountLeft;
					qMakerSalePrice.push_back(pItem);
				}
			}
		}

	}

int CStockQueue::LogEnd(tagStockDelegate * c_pConsign)
{
	if (c_pConsign)
	{
		char acSql[1024];
		sprintf(acSql,"update StockDelegate set CancelDate=getdate() where StockDelegateId=%d",c_pConsign->nStockDelegateId);
		pProcess->m_sqlServUser.Execute(acSql);
		//其他处理，如释放冻结的资金//
		REPORT(MN, T("END CONSIGN SUCC %d-%d\n",c_pConsign->nStockDelegateId,c_pConsign->nAmountLeft), RPT_INFO);
	}
	return 0;
}

int CStockQueue::LogCancel(tagStockDelegate * c_pConsign,tagStockDelegate * c_pCancel)
{
	if (c_pConsign)
	{
		g_pOtcMarket->OnCancelConsign(c_pConsign);
		char acSql[1024];
		sprintf(acSql,"update StockDelegate set status=%d where StockDelegateId=%d",c_pCancel->nStatus,c_pCancel->nStockDelegateId);
		pProcess->m_sqlServUser.Execute(acSql);
		sprintf(acSql,"update StockDelegate set status=%d,CancelId=%d where StockDelegateId=%d",c_pConsign->nStatus,c_pCancel->nStockDelegateId,c_pConsign->nStockDelegateId);
		pProcess->m_sqlServUser.Execute(acSql);
		REPORT(MN, T("CANCEL SUCC %d-%d\n",c_pConsign->nStockDelegateId,c_pCancel->nStockDelegateId), RPT_INFO);
	}
	else//没有在队列中找到对应的委托
	{
		char acSql[1024];
		sprintf(acSql,"update StockDelegate set status=%d where StockDelegateId=%d",c_pCancel->nStatus,c_pCancel->nStockDelegateId);
		pProcess->m_sqlServUser.Execute(acSql);
		REPORT(MN, T("CANCEL FAIL %d\n",c_pCancel->nStockDelegateId), RPT_INFO);
	}
	return 0;
};

void CStockQueue::LogMatch(tagStockDelegate * c_pBuy,tagStockDelegate * c_pSale,int c_nAmount,float c_fPrice)
{
	char acSql[1024];
	sprintf(acSql,"insert into StockDetail(BuyDelegateId,SaleDelegateId,BuyMemberId,SaleMemberId,DonePrice,DoneAmount,DoneMoney,DoneDate) values(%d,%d,%d,%d,%.3f,%d,%.3f,getdate())",c_pBuy->nStockDelegateId,c_pSale->nStockDelegateId,c_pBuy->nMemberId,c_pSale->nMemberId,c_fPrice,c_nAmount,c_nAmount*c_fPrice);
	pProcess->m_sqlServUser.Execute(acSql);

	sprintf(acSql,"insert into StockDone (StockId,MemberId,DelegateId,BuySale,DonePrice,DoneAmount,DoneMoney,DoneDate,SellFee) values(%d,%d,%d,%d,%.3f,%d,%.3f,getdate(),%.3f)",c_pBuy->nStockId,c_pBuy->nMemberId,c_pBuy->nStockDelegateId,c_pBuy->nBuySale,c_fPrice,c_nAmount,c_fPrice*c_nAmount,c_fPrice*c_nAmount*0.003);
	pProcess->m_sqlServUser.Execute(acSql);
	sprintf(acSql,"insert into StockDone (StockId,MemberId,DelegateId,BuySale,DonePrice,DoneAmount,DoneMoney,DoneDate,SellFee) values(%d,%d,%d,%d,%.3f,%d,%.3f,getdate(),%.3f)",c_pSale->nStockId,c_pSale->nMemberId,c_pSale->nStockDelegateId,c_pSale->nBuySale,c_fPrice,c_nAmount,c_fPrice*c_nAmount,c_fPrice*c_nAmount*0.003);
	pProcess->m_sqlServUser.Execute(acSql);
	//REPORT(MN,T("%s\n",acSql),RPT_INFO);

	pProcess->RecordStockBook(0,1,c_pBuy->nStockDelegateId,c_pBuy->nMemberId,c_pSale->nMemberId,c_pBuy->nStockId,c_nAmount,c_nAmount);//买入锁定
	pProcess->RecordStockBook(0,1,c_pSale->nStockDelegateId,c_pSale->nMemberId,c_pBuy->nMemberId,c_pSale->nStockId,-c_nAmount,-c_nAmount);//不影响可用

	float fFee = 0;
	fFee = g_SystemParam.CalcFee(0,c_fPrice * c_nAmount);
	pProcess->RecordMoneyBook(0,1,c_pBuy->nStockDelegateId,c_pBuy->nMemberId,c_pSale->nMemberId,-c_nAmount * c_fPrice,-c_nAmount * c_fPrice,1);//不影响可用
	pProcess->RecordMoneyBook(0,1,c_pBuy->nStockDelegateId,c_pBuy->nMemberId,g_SystemParam.nOtcId,-fFee,-fFee,2);//不影响可用
	pProcess->RecordMoneyBook(0,1,c_pBuy->nStockDelegateId,g_SystemParam.nOtcId,c_pBuy->nMemberId,fFee,0,2);//不影响可用

	fFee = g_SystemParam.CalcFee(1,c_fPrice * c_nAmount);
	pProcess->RecordMoneyBook(0,1,c_pSale->nStockDelegateId,c_pSale->nMemberId,c_pBuy->nMemberId,c_nAmount * c_fPrice,0,1);////不影响可用
	pProcess->RecordMoneyBook(0,1,c_pSale->nStockDelegateId,c_pSale->nMemberId,g_SystemParam.nOtcId,-fFee,-fFee,2);////不影响可用
	pProcess->RecordMoneyBook(0,1,c_pSale->nStockDelegateId,g_SystemParam.nOtcId,c_pSale->nMemberId,fFee,0,2);//不影响可用


	sprintf(acSql,"update StockDelegate set AmountDone=%d,AmountLeft=%d,Status=%d,DoneDate=getdate() where StockDelegateId=%d",c_pBuy->nAmountDone,c_pBuy->nAmountLeft,c_pBuy->nStatus,c_pBuy->nStockDelegateId);
	pProcess->m_sqlServUser.Execute(acSql);

	sprintf(acSql,"update StockDelegate set AmountDone=%d,AmountLeft=%d,Status=%d,DoneDate=getdate() where StockDelegateId=%d",c_pSale->nAmountDone,c_pSale->nAmountLeft,c_pSale->nStatus,c_pSale->nStockDelegateId);
	pProcess->m_sqlServUser.Execute(acSql);

	REPORT(MN,T("MATCH buy=%d,sale=%d,amount=%d,price=%.3f\n",c_pBuy->nStockDelegateId,c_pSale->nStockDelegateId,c_nAmount,c_fPrice),RPT_INFO);
	nMatchCount++;
	nTotalAmount += c_nAmount;
	fTotalMoney += c_nAmount * c_fPrice;
	tagPriceVol * pItem = new tagPriceVol();
	pItem->fPrice = c_fPrice;
	pItem->nAmount = c_nAmount;
	qTick.push_back(pItem);
	TickUnit tick;
	tick.Price = int(c_fPrice * 1000);
	tick.Volume = c_nAmount;
	tick.Time = g_pOtcMarket->m_nMinuteTime;
	tick.Way = '0';
	g_ShareData.AddTick(nStockId,&tick);
	g_ShareData.AddMinK(nStockId,tick.Time,tick.Volume,tick.Price);
}
//写到行情文件中
void CStockQueue::FreshQuote()
{
	if(g_pOtcMarket->m_msState != ONTRADE  && g_pOtcMarket->m_msState != PREOPEN)
		return;

	Quote *pQuote = (Quote *)g_ShareData.GetStockById(nStockId);
	if (pQuote)
	{
		pQuote->zgjg = int(fHigh * 1000);
		pQuote->zdjg = int(fLow * 1000);
		pQuote->jrkp = int(fOpen * 1000);
		pQuote->zjjg = int(fLastPrice * 1000);
		pQuote->zjcj = nLastAmount;
		pQuote->cjje = int(fTotalMoney * 1000);
		pQuote->cjsl = nTotalAmount;
		pQuote->cjbs = nMatchCount;//
		if (pQuote->zrsp > 0 && pQuote->zjjg > 0)
		{
			pQuote->zd = pQuote->zjjg - int(pQuote->zrsp);
			pQuote->zdf = int(float(pQuote->zd) * 1000 / pQuote->zrsp);
		}
		else
		{
			pQuote->zd = 0;
			pQuote->zdf = 0;
		}
		std::list<tagPriceVol *>::iterator iter;
		int nIndex = 0;
		pQuote->BM1 = 0;
		pQuote->BP1 = 0;
		pQuote->BM2 = 0;
		pQuote->BP2 = 0;
		pQuote->BM3 = 0;
		pQuote->BP3 = 0;
		pQuote->BM4 = 0;
		pQuote->BP4 = 0;
		pQuote->BM5 = 0;
		pQuote->BP5 = 0;
		pQuote->SM1 = 0;
		pQuote->SP1 = 0;
		pQuote->SM2 = 0;
		pQuote->SP2 = 0;
		pQuote->SM3 = 0;
		pQuote->SP3 = 0;
		pQuote->SM4 = 0;
		pQuote->SP4 = 0;
		pQuote->SM5 = 0;
		pQuote->SP5 = 0;

		pQuote->MBM1 = 0;
		pQuote->MBP1 = 0;
		pQuote->MBM2 = 0;
		pQuote->MBP2 = 0;
		pQuote->MBM3 = 0;
		pQuote->MBP3 = 0;
		pQuote->MBM4 = 0;
		pQuote->MBP4 = 0;
		pQuote->MBM5 = 0;
		pQuote->MBP5 = 0;
		pQuote->MSM1 = 0;
		pQuote->MSP1 = 0;
		pQuote->MSM2 = 0;
		pQuote->MSP2 = 0;
		pQuote->MSM3 = 0;
		pQuote->MSP3 = 0;
		pQuote->MSM4 = 0;
		pQuote->MSP4 = 0;
		pQuote->MSM5 = 0;
		pQuote->MSP5 = 0;

		for(iter=qBuyPrice.begin(); iter!=qBuyPrice.end(); iter++)
		{
			nIndex++;
			
			switch(nIndex)
			{
			case 1:
				pQuote->BM1 = (*iter)->nAmount;
				pQuote->BP1 = int((*iter)->fPrice * 1000);
				break;
			case 2:
				pQuote->BM2 = (*iter)->nAmount;
				pQuote->BP2 = int((*iter)->fPrice * 1000);
				break;
			case 3:
				pQuote->BM3 = (*iter)->nAmount;
				pQuote->BP3 = int((*iter)->fPrice * 1000);
				break;
			case 4:
				pQuote->BM4 = (*iter)->nAmount;
				pQuote->BP4 = int((*iter)->fPrice * 1000);
				break;
			case 5:
				pQuote->BM5 = (*iter)->nAmount;
				pQuote->BP5 = int((*iter)->fPrice * 1000);
				break;
			default:
				break;
			}
		}
		nIndex = 0;
		for(iter=qSalePrice.begin(); iter!=qSalePrice.end(); iter++)
		{
			nIndex++;
			
			switch(nIndex)
			{
			case 1:
				pQuote->SM1 = (*iter)->nAmount;
				pQuote->SP1 = int((*iter)->fPrice * 1000);
				break;
			case 2:
				pQuote->SM2 = (*iter)->nAmount;
				pQuote->SP2 = int((*iter)->fPrice * 1000);
				break;
			case 3:
				pQuote->SM3 = (*iter)->nAmount;
				pQuote->SP3 = int((*iter)->fPrice * 1000);
				break;
			case 4:
				pQuote->SM4 = (*iter)->nAmount;
				pQuote->SP4 = int((*iter)->fPrice * 1000);
				break;
			case 5:
				pQuote->SM5 = (*iter)->nAmount;
				pQuote->SP5 = int((*iter)->fPrice * 1000);
				break;
			default:
				break;
			}
		}

		nIndex = 0;
		for(iter=qMakerBuyPrice.begin(); iter!=qMakerBuyPrice.end(); iter++)
		{
			nIndex++;
			
			switch(nIndex)
			{
			case 1:
				pQuote->MBM1 = (*iter)->nAmount;
				pQuote->MBP1 = int((*iter)->fPrice * 1000);
				break;
			case 2:
				pQuote->MBM2 = (*iter)->nAmount;
				pQuote->MBP2 = int((*iter)->fPrice * 1000);
				break;
			case 3:
				pQuote->MBM3 = (*iter)->nAmount;
				pQuote->MBP3 = int((*iter)->fPrice * 1000);
				break;
			case 4:
				pQuote->MBM4 = (*iter)->nAmount;
				pQuote->MBP4 = int((*iter)->fPrice * 1000);
				break;
			case 5:
				pQuote->MBM5 = (*iter)->nAmount;
				pQuote->MBP5 = int((*iter)->fPrice * 1000);
				break;
			default:
				break;
			}
		}
		nIndex = 0;
		for(iter=qMakerSalePrice.begin(); iter!=qMakerSalePrice.end(); iter++)
		{
			nIndex++;
			
			switch(nIndex)
			{
			case 1:
				pQuote->MSM1 = (*iter)->nAmount;
				pQuote->MSP1 = int((*iter)->fPrice * 1000);
				break;
			case 2:
				pQuote->MSM2 = (*iter)->nAmount;
				pQuote->MSP2 = int((*iter)->fPrice * 1000);
				break;
			case 3:
				pQuote->MSM3 = (*iter)->nAmount;
				pQuote->MSP3 = int((*iter)->fPrice * 1000);
				break;
			case 4:
				pQuote->MSM4 = (*iter)->nAmount;
				pQuote->MSP4 = int((*iter)->fPrice * 1000);
				break;
			case 5:
				pQuote->MSM5 = (*iter)->nAmount;
				pQuote->MSP5 = int((*iter)->fPrice * 1000);
				break;
			default:
				break;
			}
		}

	}
	g_pOtcMarket->UpdateStockCurrent(pQuote,0);
	while(qTick.size())
	{
		delete qTick.back();
		qTick.pop_back();
	}
}