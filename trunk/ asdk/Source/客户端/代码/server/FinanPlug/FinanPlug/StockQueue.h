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
	void Open()//����
	{
		nTotalAmount = 0;//�ɽ�����
		fTotalMoney = 0;//�ɽ��ܽ��
		nMatchCount = 0;//�ɽ�����
		nLastAmount = 0;//�ɽ�����
		fLastPrice = 0;//�ϴγɽ��۸�
		fHigh = 0;//��߼�
		fLow = 0;//��ͼ�
		fClose = 0;//���̼�
		fOpen = 0;//���̼�	
	};
	void Close()//����
	{
		fClose = fLastPrice;//�������̼�
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
	int AddConsign(tagStockDelegate * c_pItem)//����ί��
	{
		bool bFind = false;
		tagStockDelegate * pItem = new tagStockDelegate();
		memcpy(pItem,c_pItem,sizeof(tagStockDelegate));
		std::list<tagStockDelegate *>::iterator iter;
		if(c_pItem->nBuySale == 0)
		{
			for(iter=qBuy.begin(); iter!=qBuy.end(); iter++)
			{
				if(((c_pItem->nMakerQuoteDetailId == 0 || c_pItem->nMakerQuoteDetailId > 0)&& c_pItem->fPrice > (*iter)->fPrice)//ׯ������
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
	int CancelConsign(tagStockDelegate * c_pItem)//����ί��
	{
		std::list<tagStockDelegate *>::iterator iter;
		if (c_pItem->nMakerQuoteDetailId > 0)//����ׯ��ί��
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

	int Match();//���
	int Match(tagStockDelegate *);
	void OutPut();//
	void LogMatch(tagStockDelegate * c_pBuy,tagStockDelegate * c_pSale,int c_nAmount,float c_fPrice);
	void FreshQuote();//д��������ȥ
public:
	CDataProcess *pProcess;
	int			nStockId;
	int			nTotalAmount;//�ɽ�����
	float		fTotalMoney;//�ɽ��ܽ��
	int			nMatchCount;//�ɽ�����
	int			nLastAmount;//�ɽ�����
	float		fLastPrice;//�ϴγɽ��۸�
	float		fHigh;//��߼�
	float		fLow;//��ͼ�
	float		fClose;//���̼�
	float		fOpen;//���̼�
	std::list<tagStockDelegate *>	qBuy;//�����
	std::list<tagStockDelegate *>	qSale;//������
	std::list<tagPriceVol *>		qBuyPrice;//�����
	std::list<tagPriceVol *>		qSalePrice;//������

	std::list<tagPriceVol *>		qMakerBuyPrice;//ׯ�������
	std::list<tagPriceVol *>		qMakerSalePrice;//ׯ��������
	
	std::list<tagPriceVol *>		qTick;//�ɽ�
};