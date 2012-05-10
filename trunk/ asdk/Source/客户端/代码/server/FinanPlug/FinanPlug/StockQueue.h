#pragma once
#include "FinanPlugdef.h"

class CDataProcess;
class CStockQueue
{
public:
	CStockQueue(int c_nStockId,CDataProcess *c_pProcess)
	{
		pProcess = c_pProcess;
		nStockId = c_nStockId;
		nTotalAmount = 0;
		fTotalMoney = 0;
		nMatchCount = 0;
		nLastAmount = 0;
		fLastPrice  = 0;
		fHigh = 0;
		fLow = 0;
		fOpen = 0;
		fClose = 0;
	};
	~CStockQueue(void)
	{
		while(qBuy.size())
		{
			delete qBuy.back();
			qBuy.pop_back();
		}
		while (qSale.size())
		{
			delete qSale.back();
			qSale.pop_back();
		}
	};

public:
	void Open()//开盘
	{
		nTotalAmount = 0;//成交总量
		fTotalMoney = 0;//成交总金额
		nMatchCount = 0;//成交笔数
		nLastAmount = 0;//成交数量
		fLastPrice = 0;//上次成交价格
		fHigh = 0;//最高价
		fLow = 0;//最低价
		fClose = 0;//收盘价
		fOpen = 0;//开盘价	
	};
	void Close()//收盘
	{
		fClose = fLastPrice;//计算收盘价
		while(qBuy.size())
		{
			LogEnd(qBuy.back());
			delete qBuy.back();
			qBuy.pop_back();
		}

		while(qSale.size())
		{
			LogEnd(qSale.back());
			delete qSale.back();
			qSale.pop_back();
		}
	}

public:
	int AddConsign(tagStockDelegate * c_pItem)//加入委托
	{
		bool bFind = false;
		tagStockDelegate * pItem = new tagStockDelegate();
		memcpy(pItem,c_pItem,sizeof(tagStockDelegate));
		std::list<tagStockDelegate *>::iterator iter;
		if(c_pItem->nBuySale == 0)
		{
			for(iter=qBuy.begin(); iter!=qBuy.end(); iter++)
			{
				if(((c_pItem->nMakerQuoteDetailId == 0 || c_pItem->nMakerQuoteDetailId > 0)&& c_pItem->fPrice > (*iter)->fPrice)//庄家优先
				||(c_pItem->nMakerQuoteDetailId > 0 && c_pItem->nMakerQuoteDetailId == 0 && c_pItem->fPrice >= (*iter)->fPrice))
				{
					bFind = true;
					qBuy.insert(iter,pItem);
					break;
				}
			}
			if (bFind == false)
			{
				qBuy.push_back(pItem);
			}
		}
		else
		{
			for(iter=qSale.begin(); iter!=qSale.end(); iter++)
			{
				if(((c_pItem->nMakerQuoteDetailId == 0 || c_pItem->nMakerQuoteDetailId > 0)&& c_pItem->fPrice < (*iter)->fPrice)
				||(c_pItem->nMakerQuoteDetailId > 0 && c_pItem->nMakerQuoteDetailId == 0 && c_pItem->fPrice <= (*iter)->fPrice))
				{
					bFind = true;
					qSale.insert(iter,pItem);
					break;
				}
			}
			if (bFind == false)
			{
				qSale.push_back(pItem);
			}
		}

		return 1;
	};
	int CancelConsign(tagStockDelegate * c_pItem)//撤销委托
	{
		std::list<tagStockDelegate *>::iterator iter;
		if (c_pItem->nMakerQuoteDetailId > 0)//撤销庄家委托
		{
			for(iter=qBuy.begin(); iter!=qBuy.end(); iter++)
			{
				if ((*iter)->nMakerQuoteDetailId>0 &&c_pItem->nMemberId == (*iter)->nMemberId)
				{
					if ((*iter)->nStatus == 1)
						(*iter)->nStatus = -1;//complete cancel
					else
						(*iter)->nStatus = 3;//part cancel
					(*iter)->nCancelId = c_pItem->nCancelId;
					c_pItem->nStatus = 4;
					LogCancel(*iter,c_pItem);
					delete *iter;
					qBuy.erase(iter);
					return 1;
				}
			}
			for(iter=qSale.begin(); iter!=qSale.end(); iter++)
			{
				if ((*iter)->nMakerQuoteDetailId>0 &&c_pItem->nMemberId == (*iter)->nMemberId)
				{
					if ((*iter)->nStatus == 1)
						(*iter)->nStatus = -1;//complete cancel
					else
						(*iter)->nStatus = 3;//part cancel
					(*iter)->nCancelId = c_pItem->nCancelId;
					LogCancel(*iter,c_pItem);
					delete *iter;
					qSale.erase(iter);
					return 1;
				}
			}
		}
		else
		{
			for(iter=qBuy.begin(); iter!=qBuy.end(); iter++)
			{
				if ((*iter)->nStockDelegateId == c_pItem->nCancelId)
				{
					if ((*iter)->nStatus == 1)
						(*iter)->nStatus = -1;//complete cancel
					else
						(*iter)->nStatus = 3;//part cancel
					(*iter)->nCancelId = c_pItem->nCancelId;
					c_pItem->nStatus = 4;
					LogCancel(*iter,c_pItem);
					delete *iter;
					qBuy.erase(iter);
					return 1;
				}
			}
			for(iter=qSale.begin(); iter!=qSale.end(); iter++)
			{
				if ((*iter)->nStockDelegateId == c_pItem->nCancelId)
				{
					if ((*iter)->nStatus == 1)
						(*iter)->nStatus = -1;//complete cancel
					else
						(*iter)->nStatus = 3;//part cancel
					(*iter)->nCancelId = c_pItem->nCancelId;
					LogCancel(*iter,c_pItem);
					delete *iter;
					qSale.erase(iter);
					return 1;
				}
			}
		}
		c_pItem->nStatus = -1;
		LogCancel(NULL,c_pItem);
		return 0;
	};
	
	int LogEnd(tagStockDelegate * c_pConsign);
	int LogCancel(tagStockDelegate * c_pConsign,tagStockDelegate * c_pCancel);

	int Match();//撮合
	int Match(tagStockDelegate *);
	void OutPut();//
	void LogMatch(tagStockDelegate * c_pBuy,tagStockDelegate * c_pSale,int c_nAmount,float c_fPrice);
	void FreshQuote();//写到行情中去
public:
	CDataProcess *pProcess;
	int			nStockId;
	int			nTotalAmount;//成交总量
	float		fTotalMoney;//成交总金额
	int			nMatchCount;//成交笔数
	int			nLastAmount;//成交数量
	float		fLastPrice;//上次成交价格
	float		fHigh;//最高价
	float		fLow;//最低价
	float		fClose;//收盘价
	float		fOpen;//开盘价
	std::list<tagStockDelegate *>	qBuy;//买队列
	std::list<tagStockDelegate *>	qSale;//卖队列
	std::list<tagPriceVol *>		qBuyPrice;//买价量
	std::list<tagPriceVol *>		qSalePrice;//卖价量

	std::list<tagPriceVol *>		qMakerBuyPrice;//庄家买价量
	std::list<tagPriceVol *>		qMakerSalePrice;//庄家卖价量
	
	std::list<tagPriceVol *>		qTick;//成交
};