#include "stdafx.h"
#include "PTLPushQueen.h"


int ptl_compress(const ATP_Msg_Sec_HoldPosition* pPosition,char* pData,int nLength)
{
	int nclen = 0;
	int *pLen = (int*)pData;
	pData += sizeof(int);


	//全量解压
	NCH_BEGIN_CMP_VERSION(pData,nLength ,1)
		NCH_CMP_INT64_STEP( pData,pPosition->nIdentity)
		NCH_CMP_STRING_STEP(pData,pPosition->szMarket);
		NCH_CMP_INT_STEP( pData,pPosition->nHolderType);
		NCH_CMP_STRING_STEP(pData,pPosition->szCode);
		NCH_CMP_STRING_STEP(pData,pPosition->szName);
		NCH_CMP_INT64_STEP( pData,pPosition->i64Balance);
		NCH_CMP_INT64_STEP( pData,pPosition->i64Available);
		NCH_CMP_INT64_STEP( pData,pPosition->i64Forzen);
		NCH_CMP_INT64_STEP( pData,pPosition->i64Buy);
		NCH_CMP_INT64_STEP( pData,pPosition->i64Sale);
		NCH_CMP_INT64_STEP( pData,pPosition->i64Qty);
		NCH_CMP_INT64_STEP( pData,pPosition->i64Diff);
		NCH_CMP_INT_STEP( pData,pPosition->nCostPrice);
		NCH_CMP_INT_STEP( pData,pPosition->nBuyCost);
		NCH_CMP_DOUBLE4_STEP( pData,pPosition->dMktVal);
		NCH_CMP_DOUBLE4_STEP( pData,pPosition->dIncome);
	NCH_END_CMP(pData,nclen);

	*pLen = nclen;
	return nclen + sizeof(int);	//返回长度.

}

int ptl_decmpress(char* pData,int nLength,ATP_Msg_Sec_HoldPosition* pPosition)
{
	int ndeclen = 0;

	int nItemLen = *( (int*)pData);	//后面数据长度.

	pData += sizeof(int);

	//全量解压
	NCH_BEGIN_DCMP_VERSION(pData,nLength ,1)
		NCH_DCMP_INT64_STEP( pData,pPosition->nIdentity)
		NCH_DCMP_STRING_STEP(pData,pPosition->szMarket,sizeof(pPosition->szMarket));
		NCH_DCMP_INT_STEP( pData,pPosition->nHolderType);
		NCH_DCMP_STRING_STEP(pData,pPosition->szCode,sizeof(pPosition->szCode));
		NCH_DCMP_STRING_STEP(pData,pPosition->szName,sizeof(pPosition->szName));
		NCH_DCMP_INT64_STEP( pData,pPosition->i64Balance);
		NCH_DCMP_INT64_STEP( pData,pPosition->i64Available);
		NCH_DCMP_INT64_STEP( pData,pPosition->i64Forzen);
		NCH_DCMP_INT64_STEP( pData,pPosition->i64Buy);
		NCH_DCMP_INT64_STEP( pData,pPosition->i64Sale);
		NCH_DCMP_INT64_STEP( pData,pPosition->i64Qty);
		NCH_DCMP_INT64_STEP( pData,pPosition->i64Diff);
		NCH_DCMP_INT_STEP( pData,pPosition->nCostPrice);
		NCH_DCMP_INT_STEP( pData,pPosition->nBuyCost);
		NCH_DCMP_DOUBLE4_STEP( pData,pPosition->dMktVal);
		NCH_DCMP_DOUBLE4_STEP( pData,pPosition->dIncome);
	NCH_END_DCMP(pData,ndeclen);

	return nItemLen+sizeof(int);	//返回长度.
}



int ptl_comparecmpress(const ATP_Msg_Sec_HoldPosition* pNew,
					   const ATP_Msg_Sec_HoldPosition* pOld,
							  char* pData,
							  int nLength)
{
	ASSERT(pNew && pOld);	//必须要有一个不为空

	int nclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);
	

	NCH_BEGIN_CCMP_VERSION(pData,nLength,1,4)
		NCH_CCMP_INT64_STEP( pData,pNew->nIdentity,pOld->nIdentity)
		NCH_CCMP_STRING_STEP(pData,pNew->szMarket,pOld->szMarket);
		NCH_CCMP_INT_STEP( pData,pNew->nHolderType,pOld->nHolderType);
		NCH_CCMP_STRING_STEP(pData,pNew->szCode,pOld->szCode);
		NCH_CCMP_STRING_STEP(pData,pNew->szName,pOld->szName);
		NCH_CCMP_INT64_STEP( pData,pNew->i64Balance,pOld->i64Balance);
		NCH_CCMP_INT64_STEP( pData,pNew->i64Available,pOld->i64Available);
		NCH_CCMP_INT64_STEP( pData,pNew->i64Forzen,pOld->i64Forzen);
		NCH_CCMP_INT64_STEP( pData,pNew->i64Buy,pOld->i64Buy);
		NCH_CCMP_INT64_STEP( pData,pNew->i64Sale,pOld->i64Sale);
		NCH_CCMP_INT64_STEP( pData,pNew->i64Qty,pOld->i64Qty);
		NCH_CCMP_INT64_STEP( pData,pNew->i64Diff,pOld->i64Diff);
		NCH_CCMP_INT_STEP( pData,pNew->nCostPrice,pOld->nCostPrice);
		NCH_CCMP_INT_STEP( pData,pNew->nBuyCost,pOld->nBuyCost);
		NCH_CCMP_DOUBLE4_STEP( pData,pNew->dMktVal,pOld->dMktVal);
		NCH_CCMP_DOUBLE4_STEP( pData,pNew->dIncome,pOld->dIncome);
	NCH_END_CCMP(pData,nclen);
	
	*pLen = nclen;		
    return nclen+sizeof(int);
}


int ptl_comparedecmpress(char* pData,
						 int nLength,
					   ATP_Msg_Sec_HoldPosition* pPosition
					   )
{
	int ndclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);

	NCH_BEGIN_DCCMP_VERSION(pData,nLength,1)
		NCH_DCCMP_INT64_STEP( pData,pPosition->nIdentity)
		NCH_DCCMP_STRING_STEP(pData,pPosition->szMarket,sizeof(pPosition->szMarket));
		NCH_DCCMP_INT_STEP( pData,pPosition->nHolderType);
		NCH_DCCMP_STRING_STEP(pData,pPosition->szCode,sizeof(pPosition->szCode));
		NCH_DCCMP_STRING_STEP(pData,pPosition->szName,sizeof(pPosition->szName));
		NCH_DCCMP_INT64_STEP( pData,pPosition->i64Balance);
		NCH_DCCMP_INT64_STEP( pData,pPosition->i64Available);
		NCH_DCCMP_INT64_STEP( pData,pPosition->i64Forzen);
		NCH_DCCMP_INT64_STEP( pData,pPosition->i64Buy);
		NCH_DCCMP_INT64_STEP( pData,pPosition->i64Sale);
		NCH_DCCMP_INT64_STEP( pData,pPosition->i64Qty);
		NCH_DCCMP_INT64_STEP( pData,pPosition->i64Diff);
		NCH_DCCMP_INT_STEP( pData,pPosition->nCostPrice);
		NCH_DCCMP_INT_STEP( pData,pPosition->nBuyCost);
		NCH_DCCMP_DOUBLE4_STEP( pData,pPosition->dMktVal);
		NCH_DCCMP_DOUBLE4_STEP( pData,pPosition->dIncome);
	NCH_END_DCCMP(pData,ndclen);

	return *pLen+sizeof(int);
}




/**
* 压缩成交记录信息到指定的内存中
* @param pMatch  成交记录
* @param pData   指写的内存
* @param nLength 内存长度
*/
int ptl_compress(const ATP_Msg_Sec_QueryMatch_Answer* pMatch,char* pData,int nLength)
{
	int nclen = 0;
	int *pLen = (int*)pData;
	pData += sizeof(int);


	//全量解压
	NCH_BEGIN_CMP_VERSION(pData,nLength ,1)
		NCH_CMP_INT64_STEP(pData,pMatch->nIdentity);

		NCH_CMP_STRING_STEP(pData,pMatch->order.szMarket);
		NCH_CMP_INT_STEP(pData,pMatch->order.nHolderType);
		NCH_CMP_STRING_STEP(pData,pMatch->order.szCode);
		NCH_CMP_STRING_STEP(pData,pMatch->order.szName);
		NCH_CMP_INT_STEP(pData,pMatch->order.cBSSide);
		NCH_CMP_INT_STEP(pData,pMatch->order.nPrice);
		NCH_CMP_INT_STEP(pData,pMatch->order.nVolume);
		NCH_CMP_STRING_STEP(pData,pMatch->order.szOrderGroup);
		
		
		NCH_CMP_STRING_STEP(pData,pMatch->chPostStr);
		NCH_CMP_INT_STEP(pData,pMatch->nStatus);				
		NCH_CMP_INT_STEP(pData,pMatch->nOrderDate);
		NCH_CMP_INT_STEP(pData,pMatch->nOrderTime);
		NCH_CMP_INT_STEP(pData,pMatch->nMadeVolume);
		NCH_CMP_INT_STEP(pData,pMatch->nMadePrice);
		NCH_CMP_INT_STEP(pData,pMatch->nCancelVolume);
		NCH_CMP_INT_STEP(pData,pMatch->nMadeTime);	
		NCH_CMP_STRING_STEP(pData,pMatch->chOrderNumber);
		NCH_CMP_STRING_STEP(pData,pMatch->chMadeNumber);
		NCH_CMP_STRING_STEP(pData,pMatch->chRemark);
		NCH_CMP_STRING_STEP(pData,pMatch->chRemark1);
		NCH_CMP_DOUBLE4_STEP(pData,pMatch->dMadeAmt);
	NCH_END_CMP(pData,nclen);

	*pLen = nclen;
	return nclen + sizeof(int);	//返回长度.

}


/**
* 从指定的内存中解压缩成交信息
* @param pData      指写的内存
* @param nBufferLen 内存长度
* @param pMatch  成交记录
*/
int ptl_decmpress(char* pData,int nLength,ATP_Msg_Sec_QueryMatch_Answer* pMatch)
{
	int ndeclen = 0;

	int nItemLen = *( (int*)pData);	//后面数据长度.

	pData += sizeof(int);

	//全量解压
	NCH_BEGIN_DCMP_VERSION(pData,nLength ,1)
		NCH_DCMP_INT64_STEP(pData,pMatch->nIdentity);

		NCH_DCMP_STRING_STEP(pData,pMatch->order.szMarket,sizeof(pMatch->order.szMarket));
		NCH_DCMP_INT_STEP(pData,pMatch->order.nHolderType);
		NCH_DCMP_STRING_STEP(pData,pMatch->order.szCode,sizeof(pMatch->order.szCode));
		NCH_DCMP_STRING_STEP(pData,pMatch->order.szName,sizeof(pMatch->order.szName));
		NCH_DCMP_INT_STEP(pData,pMatch->order.cBSSide);
		NCH_DCMP_INT_STEP(pData,pMatch->order.nPrice);
		NCH_DCMP_INT_STEP(pData,pMatch->order.nVolume);
		NCH_DCMP_STRING_STEP(pData,pMatch->order.szOrderGroup,sizeof(pMatch->order.szOrderGroup));


		NCH_DCMP_STRING_STEP(pData,pMatch->chPostStr,sizeof(pMatch->chPostStr));
		NCH_DCMP_INT_STEP(pData,pMatch->nStatus);				
		NCH_DCMP_INT_STEP(pData,pMatch->nOrderDate);
		NCH_DCMP_INT_STEP(pData,pMatch->nOrderTime);
		NCH_DCMP_INT_STEP(pData,pMatch->nMadeVolume);
		NCH_DCMP_INT_STEP(pData,pMatch->nMadePrice);
		NCH_DCMP_INT_STEP(pData,pMatch->nCancelVolume);
		NCH_DCMP_INT_STEP(pData,pMatch->nMadeTime);	
		NCH_DCMP_STRING_STEP(pData,pMatch->chOrderNumber,sizeof(pMatch->chOrderNumber));
		NCH_DCMP_STRING_STEP(pData,pMatch->chMadeNumber,sizeof(pMatch->chMadeNumber));
		NCH_DCMP_STRING_STEP(pData,pMatch->chRemark,sizeof(pMatch->chRemark));
		NCH_DCMP_STRING_STEP(pData,pMatch->chRemark1,sizeof(pMatch->chRemark1));
		NCH_DCMP_DOUBLE4_STEP(pData,pMatch->dMadeAmt);
		
	NCH_END_DCMP(pData,ndeclen);

	return nItemLen+sizeof(int);	//返回长度.
}



/**
* 压缩资产记录信息到指定的内存中
* @param pAssets 资产记录
* @param pData   指写的内存
* @param nLength 内存长度
*/
int ptl_compress(const ATP_Msg_Sec_QueryAssets_Answer* pAssets,char* pData,int nLength)
{
	int nclen = 0;
	int *pLen = (int*)pData;
	pData += sizeof(int);


	//全量解压
	NCH_BEGIN_CMP_VERSION(pData,nLength ,1)		
		NCH_CMP_INT64_STEP(pData,pAssets->nIdentity);
		NCH_CMP_INT_STEP(pData,pAssets->chMoneyType);	
		NCH_CMP_STRING_STEP(pData,pAssets->chRemark);
		NCH_CMP_DOUBLE4_STEP(pData,pAssets->dFundAvl);					
		NCH_CMP_DOUBLE4_STEP(pData,pAssets->dFundBal);				
		NCH_CMP_DOUBLE4_STEP(pData,pAssets->dStkValue);					
		NCH_CMP_DOUBLE4_STEP(pData,pAssets->dFundValue);				
		NCH_CMP_DOUBLE4_STEP(pData,pAssets->dMarketValue);				
		NCH_CMP_DOUBLE4_STEP(pData,pAssets->dIncome);					
		NCH_CMP_DOUBLE4_STEP(pData,pAssets->dFundFroz);				
		NCH_CMP_DOUBLE4_STEP(pData,pAssets->dOther);						
		NCH_CMP_DOUBLE4_STEP(pData,pAssets->dFundBuy);				
		NCH_CMP_DOUBLE4_STEP(pData,pAssets->dFundSell);	
	NCH_END_CMP(pData,nclen);

	*pLen = nclen;
	return nclen + sizeof(int);	//返回长度.


}


/**
* 从指定的内存中解压缩资产信息
* @param pData      指写的内存
* @param nBufferLen 内存长度
* @param pAssets  资产记录
*/
int ptl_decmpress(char* pData,int nLength,ATP_Msg_Sec_QueryAssets_Answer* pAssets)
{
	int ndeclen = 0;

	int nItemLen = *( (int*)pData);	//后面数据长度.

	pData += sizeof(int);

	//全量解压
	NCH_BEGIN_DCMP_VERSION(pData,nLength ,1)
		NCH_DCMP_INT64_STEP(pData,pAssets->nIdentity);
		NCH_DCMP_INT_STEP(pData,pAssets->chMoneyType);	
		NCH_DCMP_STRING_STEP(pData,pAssets->chRemark,sizeof(pAssets->chRemark));
		NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dFundAvl);					
		NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dFundBal);				
		NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dStkValue);					
		NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dFundValue);				
		NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dMarketValue);				
		NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dIncome);					
		NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dFundFroz);				
		NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dOther);						
		NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dFundBuy);				
		NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dFundSell);	
	NCH_END_DCMP(pData,ndeclen);

	return nItemLen+sizeof(int);	//返回长度.

}




/**
* 对比压缩持仓信息到指定的内存中
* @param pNew		新的委托信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的委托信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
int ptl_compress(const ATP_Msg_Sec_QueryOrderRecords_Answer* pOrderRecord,char* pData,int nLength)
{
	int nclen = 0;
	int *pLen = (int*)pData;
	pData += sizeof(int);


	//全量解压
	NCH_BEGIN_CMP_VERSION(pData,nLength ,1)
		NCH_CMP_INT64_STEP(pData,pOrderRecord->nIdentity);

		NCH_CMP_STRING_STEP(pData,pOrderRecord->order.szMarket);
		NCH_CMP_INT_STEP(pData,pOrderRecord->order.nHolderType);
		NCH_CMP_STRING_STEP(pData,pOrderRecord->order.szCode);
		NCH_CMP_STRING_STEP(pData,pOrderRecord->order.szName);
		NCH_CMP_INT_STEP(pData,pOrderRecord->order.cBSSide);
		NCH_CMP_INT_STEP(pData,pOrderRecord->order.nPrice);
		NCH_CMP_INT_STEP(pData,pOrderRecord->order.nVolume);
		NCH_CMP_STRING_STEP(pData,pOrderRecord->order.szOrderGroup);


		NCH_CMP_STRING_STEP(pData,pOrderRecord->chPostStr);
		NCH_CMP_INT_STEP(pData,pOrderRecord->dwStatus);
		NCH_CMP_INT_STEP(pData,pOrderRecord->nOrderDate);
		NCH_CMP_INT_STEP(pData,pOrderRecord->nOrderTime);	
		NCH_CMP_INT_STEP(pData,pOrderRecord->nMadeVolume);				
		NCH_CMP_INT_STEP(pData,pOrderRecord->nMadePrice);				
		NCH_CMP_INT_STEP(pData,pOrderRecord->nCancelVolume);				
		NCH_CMP_STRING_STEP(pData,pOrderRecord->chOrderNumber);
		NCH_CMP_DOUBLE4_STEP(pData,pOrderRecord->dOrderFrozAmt);	
		NCH_CMP_DOUBLE4_STEP(pData,pOrderRecord->dMadeAmt);
	NCH_END_CMP(pData,nclen);

	*pLen = nclen;
	return nclen + sizeof(int);	//返回长度.

}


int ptl_decmpress(char* pData,int nLength,ATP_Msg_Sec_QueryOrderRecords_Answer* pOrderRecord)
{
	int ndeclen = 0;

	int nItemLen = *( (int*)pData);	//后面数据长度.

	pData += sizeof(int);

	//全量解压
	NCH_BEGIN_DCMP_VERSION(pData,nLength ,1)
		NCH_DCMP_INT64_STEP(pData,pOrderRecord->nIdentity);

		NCH_DCMP_STRING_STEP(pData,pOrderRecord->order.szMarket,sizeof(pOrderRecord->order.szMarket));
		NCH_DCMP_INT_STEP(pData,pOrderRecord->order.nHolderType);
		NCH_DCMP_STRING_STEP(pData,pOrderRecord->order.szCode,sizeof(pOrderRecord->order.szCode));
		NCH_DCMP_STRING_STEP(pData,pOrderRecord->order.szName,sizeof(pOrderRecord->order.szName));
		NCH_DCMP_INT_STEP(pData,pOrderRecord->order.cBSSide);
		NCH_DCMP_INT_STEP(pData,pOrderRecord->order.nPrice);
		NCH_DCMP_INT_STEP(pData,pOrderRecord->order.nVolume);
		NCH_DCMP_STRING_STEP(pData,pOrderRecord->order.szOrderGroup,sizeof(pOrderRecord->order.szOrderGroup));


		NCH_DCMP_STRING_STEP(pData,pOrderRecord->chPostStr,sizeof(pOrderRecord->chPostStr));
		NCH_DCMP_INT_STEP(pData,pOrderRecord->dwStatus);
		NCH_DCMP_INT_STEP(pData,pOrderRecord->nOrderDate);
		NCH_DCMP_INT_STEP(pData,pOrderRecord->nOrderTime);	
		NCH_DCMP_INT_STEP(pData,pOrderRecord->nMadeVolume);				
		NCH_DCMP_INT_STEP(pData,pOrderRecord->nMadePrice);				
		NCH_DCMP_INT_STEP(pData,pOrderRecord->nCancelVolume);				
		NCH_DCMP_STRING_STEP(pData,pOrderRecord->chOrderNumber,sizeof(pOrderRecord->chOrderNumber));
		NCH_DCMP_DOUBLE4_STEP(pData,pOrderRecord->dOrderFrozAmt);	
		NCH_DCMP_DOUBLE4_STEP(pData,pOrderRecord->dMadeAmt);
	NCH_END_DCMP(pData,ndeclen);

	return nItemLen+sizeof(int);	//返回长度.
}


/**
* 对比压缩持仓信息到指定的内存中
* @param pNew		新的委托信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的委托信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
int ptl_comparecmpress(const ATP_Msg_Sec_QueryOrderRecords_Answer* pNew,const ATP_Msg_Sec_QueryOrderRecords_Answer* pOld,
							  char* pData,int nLength)
{
	ASSERT(pNew && pOld);	//必须要有一个不为空

	int nclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);


	NCH_BEGIN_CCMP_VERSION(pData,nLength,1,4)
		NCH_CCMP_INT64_STEP(pData,pNew->nIdentity,pOld->nIdentity);

		NCH_CCMP_STRING_STEP(pData,pNew->order.szMarket,pOld->order.szMarket);
		NCH_CCMP_INT_STEP(pData,pNew->order.nHolderType,pOld->order.nHolderType);
		NCH_CCMP_STRING_STEP(pData,pNew->order.szCode,pOld->order.szCode);
		NCH_CCMP_STRING_STEP(pData,pNew->order.szName,pOld->order.szName);
		NCH_CCMP_INT_STEP(pData,pNew->order.cBSSide,pOld->order.cBSSide);
		NCH_CCMP_INT_STEP(pData,pNew->order.nPrice,pOld->order.nPrice);
		NCH_CCMP_INT_STEP(pData,pNew->order.nVolume,pOld->order.nVolume);
		NCH_CCMP_STRING_STEP(pData,pNew->order.szOrderGroup,pOld->order.szOrderGroup);


		NCH_CCMP_STRING_STEP(pData,pNew->chPostStr,pOld->chPostStr);
		NCH_CCMP_INT_STEP(pData,pNew->dwStatus,pOld->dwStatus);
		NCH_CCMP_INT_STEP(pData,pNew->nOrderDate,pOld->nOrderDate);
		NCH_CCMP_INT_STEP(pData,pNew->nOrderTime,pOld->nOrderTime);	
		NCH_CCMP_INT_STEP(pData,pNew->nMadeVolume,pOld->nMadeVolume);				
		NCH_CCMP_INT_STEP(pData,pNew->nMadePrice,pOld->nMadePrice);				
		NCH_CCMP_INT_STEP(pData,pNew->nCancelVolume,pOld->nCancelVolume);				
		NCH_CCMP_STRING_STEP(pData,pNew->chOrderNumber,pOld->chOrderNumber);
		NCH_CCMP_DOUBLE4_STEP(pData,pNew->dOrderFrozAmt,pOld->dOrderFrozAmt);	
		NCH_CCMP_DOUBLE4_STEP(pData,pNew->dMadeAmt,pOld->dMadeAmt);
	NCH_END_CCMP(pData,nclen);

	*pLen = nclen;		
	return nclen+sizeof(int);
}


int ptl_comparedecmpress(char* pData,int nLength,ATP_Msg_Sec_QueryOrderRecords_Answer* pOrderRecord)
{
	int ndclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);

	NCH_BEGIN_DCCMP_VERSION(pData,nLength,1)
		NCH_DCCMP_INT64_STEP(pData,pOrderRecord->nIdentity);

		NCH_DCCMP_STRING_STEP(pData,pOrderRecord->order.szMarket,sizeof(pOrderRecord->order.szMarket));
		NCH_DCCMP_INT_STEP(pData,pOrderRecord->order.nHolderType);
		NCH_DCCMP_STRING_STEP(pData,pOrderRecord->order.szCode,sizeof(pOrderRecord->order.szCode));
		NCH_DCCMP_STRING_STEP(pData,pOrderRecord->order.szName,sizeof(pOrderRecord->order.szName));
		NCH_DCCMP_INT_STEP(pData,pOrderRecord->order.cBSSide);
		NCH_DCCMP_INT_STEP(pData,pOrderRecord->order.nPrice);
		NCH_DCCMP_INT_STEP(pData,pOrderRecord->order.nVolume);
		NCH_DCCMP_STRING_STEP(pData,pOrderRecord->order.szOrderGroup,sizeof(pOrderRecord->order.szOrderGroup));


		NCH_DCCMP_STRING_STEP(pData,pOrderRecord->chPostStr,sizeof(pOrderRecord->chPostStr));
		NCH_DCCMP_INT_STEP(pData,pOrderRecord->dwStatus);
		NCH_DCCMP_INT_STEP(pData,pOrderRecord->nOrderDate);
		NCH_DCCMP_INT_STEP(pData,pOrderRecord->nOrderTime);	
		NCH_DCCMP_INT_STEP(pData,pOrderRecord->nMadeVolume);				
		NCH_DCCMP_INT_STEP(pData,pOrderRecord->nMadePrice);				
		NCH_DCCMP_INT_STEP(pData,pOrderRecord->nCancelVolume);				
		NCH_DCCMP_STRING_STEP(pData,pOrderRecord->chOrderNumber,sizeof(pOrderRecord->chOrderNumber));
		NCH_DCCMP_DOUBLE4_STEP(pData,pOrderRecord->dOrderFrozAmt);	
		NCH_DCCMP_DOUBLE4_STEP(pData,pOrderRecord->dMadeAmt);
	NCH_END_DCCMP(pData,ndclen);

	return *pLen+sizeof(int);
}


/**
* 对比压缩成交信息到指定的内存中
* @param pNew		新的委托信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的委托信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
int ptl_comparecmpress(const ATP_Msg_Sec_QueryMatch_Answer* pNew,const ATP_Msg_Sec_QueryMatch_Answer* pOld,
							  char* pData,int nLength)
{
	ASSERT(pNew && pOld);	//必须要有一个不为空

	int nclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);


	NCH_BEGIN_CCMP_VERSION(pData,nLength,1,4)
		NCH_CCMP_INT64_STEP(pData,pNew->nIdentity,pOld->nIdentity);

		NCH_CCMP_STRING_STEP(pData,pNew->order.szMarket,pOld->order.szMarket);
		NCH_CCMP_INT_STEP(pData,pNew->order.nHolderType,pOld->order.nHolderType);
		NCH_CCMP_STRING_STEP(pData,pNew->order.szCode,pOld->order.szCode);
		NCH_CCMP_STRING_STEP(pData,pNew->order.szName,pOld->order.szName);
		NCH_CCMP_INT_STEP(pData,pNew->order.cBSSide,pOld->order.cBSSide);
		NCH_CCMP_INT_STEP(pData,pNew->order.nPrice,pOld->order.nPrice);
		NCH_CCMP_INT_STEP(pData,pNew->order.nVolume,pOld->order.nVolume);
		NCH_CCMP_STRING_STEP(pData,pNew->order.szOrderGroup,pOld->order.szOrderGroup);


		NCH_CCMP_STRING_STEP(pData,pNew->chPostStr,pOld->chPostStr);
		NCH_CCMP_INT_STEP(pData,pNew->nStatus,pOld->nStatus);				
		NCH_CCMP_INT_STEP(pData,pNew->nOrderDate,pOld->nOrderDate);
		NCH_CCMP_INT_STEP(pData,pNew->nOrderTime,pOld->nOrderTime);
		NCH_CCMP_INT_STEP(pData,pNew->nMadeVolume,pOld->nMadeVolume);
		NCH_CCMP_INT_STEP(pData,pNew->nMadePrice,pOld->nMadePrice);
		NCH_CCMP_INT_STEP(pData,pNew->nCancelVolume,pOld->nCancelVolume);
		NCH_CCMP_INT_STEP(pData,pNew->nMadeTime,pOld->nMadeTime);	
		NCH_CCMP_STRING_STEP(pData,pNew->chOrderNumber,pOld->chOrderNumber);
		NCH_CCMP_STRING_STEP(pData,pNew->chMadeNumber,pOld->chMadeNumber);
		NCH_CCMP_STRING_STEP(pData,pNew->chRemark,pOld->chRemark);
		NCH_CCMP_STRING_STEP(pData,pNew->chRemark1,pOld->chRemark1);
		NCH_CCMP_DOUBLE4_STEP(pData,pNew->dMadeAmt,pOld->dMadeAmt);
	NCH_END_CCMP(pData,nclen);

	*pLen = nclen;		
	return nclen+sizeof(int);
}


int ptl_comparedecmpress(char* pData,int nLength,ATP_Msg_Sec_QueryMatch_Answer* pMatch)
{
	int ndclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);

	NCH_BEGIN_DCCMP_VERSION(pData,nLength,1)
		NCH_DCCMP_INT64_STEP(pData,pMatch->nIdentity);

		NCH_DCCMP_STRING_STEP(pData,pMatch->order.szMarket,sizeof(pMatch->order.szMarket));
		NCH_DCCMP_INT_STEP(pData,pMatch->order.nHolderType);
		NCH_DCCMP_STRING_STEP(pData,pMatch->order.szCode,sizeof(pMatch->order.szCode));
		NCH_DCCMP_STRING_STEP(pData,pMatch->order.szName,sizeof(pMatch->order.szName));
		NCH_DCCMP_INT_STEP(pData,pMatch->order.cBSSide);
		NCH_DCCMP_INT_STEP(pData,pMatch->order.nPrice);
		NCH_DCCMP_INT_STEP(pData,pMatch->order.nVolume);
		NCH_DCCMP_STRING_STEP(pData,pMatch->order.szOrderGroup,sizeof(pMatch->order.szOrderGroup));


		NCH_DCCMP_STRING_STEP(pData,pMatch->chPostStr,sizeof(pMatch->chPostStr));
		NCH_DCCMP_INT_STEP(pData,pMatch->nStatus);				
		NCH_DCCMP_INT_STEP(pData,pMatch->nOrderDate);
		NCH_DCCMP_INT_STEP(pData,pMatch->nOrderTime);
		NCH_DCCMP_INT_STEP(pData,pMatch->nMadeVolume);
		NCH_DCCMP_INT_STEP(pData,pMatch->nMadePrice);
		NCH_DCCMP_INT_STEP(pData,pMatch->nCancelVolume);
		NCH_DCCMP_INT_STEP(pData,pMatch->nMadeTime);	
		NCH_DCCMP_STRING_STEP(pData,pMatch->chOrderNumber,sizeof(pMatch->chOrderNumber));
		NCH_DCCMP_STRING_STEP(pData,pMatch->chMadeNumber,sizeof(pMatch->chMadeNumber));
		NCH_DCCMP_STRING_STEP(pData,pMatch->chRemark,sizeof(pMatch->chRemark));
		NCH_DCCMP_STRING_STEP(pData,pMatch->chRemark1,sizeof(pMatch->chRemark1));
		NCH_DCCMP_DOUBLE4_STEP(pData,pMatch->dMadeAmt);

	NCH_END_DCCMP(pData,ndclen);

	return *pLen+sizeof(int);
}

/**
* 对比压缩资产信息到指定的内存中
* @param pNew		新的资产信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的资产信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
int ptl_comparecmpress(const ATP_Msg_Sec_QueryAssets_Answer* pNew,const ATP_Msg_Sec_QueryAssets_Answer* pOld,
							  char* pData,int nLength)
{
	ASSERT(pNew && pOld);	//必须要有一个不为空

	int nclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);


	NCH_BEGIN_CCMP_VERSION(pData,nLength,1,4)
		NCH_CCMP_INT64_STEP(pData,pNew->nIdentity,pOld->nIdentity);
		NCH_CCMP_INT_STEP(pData,pNew->chMoneyType,pOld->chMoneyType);	
		NCH_CCMP_STRING_STEP(pData,pNew->chRemark,pOld->chRemark);
		NCH_CCMP_DOUBLE4_STEP(pData,pNew->dFundAvl,pOld->dFundAvl);					
		NCH_CCMP_DOUBLE4_STEP(pData,pNew->dFundBal,pOld->dFundBal);				
		NCH_CCMP_DOUBLE4_STEP(pData,pNew->dStkValue,pOld->dStkValue);					
		NCH_CCMP_DOUBLE4_STEP(pData,pNew->dFundValue,pOld->dFundValue);				
		NCH_CCMP_DOUBLE4_STEP(pData,pNew->dMarketValue,pOld->dMarketValue);				
		NCH_CCMP_DOUBLE4_STEP(pData,pNew->dIncome,pOld->dIncome);					
		NCH_CCMP_DOUBLE4_STEP(pData,pNew->dFundFroz,pOld->dFundFroz);				
		NCH_CCMP_DOUBLE4_STEP(pData,pNew->dOther,pOld->dOther);						
		NCH_CCMP_DOUBLE4_STEP(pData,pNew->dFundBuy,pOld->dFundBuy);				
		NCH_CCMP_DOUBLE4_STEP(pData,pNew->dFundSell,pOld->dFundSell);
		
	NCH_END_CCMP(pData,nclen);

	*pLen = nclen;		
	return nclen+sizeof(int);

}


int ptl_comparedecmpress(char* pData,int nLength,ATP_Msg_Sec_QueryAssets_Answer* pAssets)
{
	int ndclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);

	NCH_BEGIN_DCCMP_VERSION(pData,nLength,1);
		NCH_DCCMP_INT64_STEP(pData,pAssets->nIdentity);
		NCH_DCCMP_INT_STEP(pData,pAssets->chMoneyType);	
		NCH_DCCMP_STRING_STEP(pData,pAssets->chRemark,sizeof(pAssets->chRemark));
		NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dFundAvl);					
		NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dFundBal);				
		NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dStkValue);					
		NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dFundValue);				
		NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dMarketValue);				
		NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dIncome);					
		NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dFundFroz);				
		NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dOther);						
		NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dFundBuy);				
		NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dFundSell);
		

	NCH_END_DCCMP(pData,ndclen);

	return *pLen+sizeof(int);
}


//////////////////////////////////////////////////////////////////////////
//下单结构体
int ptl_compress(const ATP_Msg_Sec_MakeOrder* pPosition,char* pData,int nLength)
{
	int nclen = 0;
	int *pLen = (int*)pData;
	pData += sizeof(int);


	//全量解压
	NCH_BEGIN_CMP_VERSION(pData,nLength ,1);
	NCH_CMP_STRING_STEP(pData,pPosition->szMarket);
	NCH_CMP_INT_STEP( pData,pPosition->nHolderType);
	NCH_CMP_STRING_STEP(pData,pPosition->szCode);
	NCH_CMP_STRING_STEP(pData,pPosition->szName);
	NCH_CMP_INT_STEP( pData,pPosition->cBSSide);
	NCH_CMP_INT_STEP( pData,pPosition->nPrice);
	NCH_CMP_INT_STEP( pData,pPosition->nVolume);
	NCH_CMP_STRING_STEP( pData,pPosition->szOrderGroup);
	NCH_END_CMP(pData,nclen);

	*pLen = nclen;
	return nclen + sizeof(int);	//返回长度.

}

int ptl_decmpress(char* pData,int nLength,ATP_Msg_Sec_MakeOrder* pPosition)
{
	int ndeclen = 0;

	int nItemLen = *( (int*)pData);	//后面数据长度.

	pData += sizeof(int);

	//全量解压
	NCH_BEGIN_DCMP_VERSION(pData,nLength ,1);
	NCH_DCMP_STRING_STEP(pData,pPosition->szMarket,4);
	NCH_DCMP_INT_STEP( pData,pPosition->nHolderType);
	NCH_DCMP_STRING_STEP(pData,pPosition->szCode,12);
	NCH_DCMP_STRING_STEP(pData,pPosition->szName,16);
	NCH_DCMP_INT_STEP( pData,pPosition->cBSSide);
	NCH_DCMP_INT_STEP( pData,pPosition->nPrice);
	NCH_DCMP_INT_STEP( pData,pPosition->nVolume);
	NCH_DCMP_STRING_STEP( pData,pPosition->szOrderGroup,LEN_ORDERGROUP);
	NCH_END_DCMP(pData,ndeclen);

	return nItemLen+sizeof(int);	//返回长度.
}



int ptl_comparecmpress(const ATP_Msg_Sec_MakeOrder* pNew,
	const ATP_Msg_Sec_MakeOrder* pOld,
	char* pData,
	int nLength)
{
	ASSERT(pNew && pOld);	//必须要有一个不为空

	int nclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);


	NCH_BEGIN_CCMP_VERSION(pData,nLength,1,4);
	NCH_CCMP_STRING_STEP(pData,pNew->szMarket,pOld->szMarket);
	NCH_CCMP_INT_STEP( pData,pNew->nHolderType,pOld->nHolderType);
	NCH_CCMP_STRING_STEP(pData,pNew->szCode,pOld->szCode);
	NCH_CCMP_STRING_STEP(pData,pNew->szName,pOld->szName);
	NCH_CCMP_INT_STEP( pData,pNew->cBSSide,pOld->cBSSide);
	NCH_CCMP_INT_STEP( pData,pNew->nPrice,pOld->nPrice);
	NCH_CCMP_INT_STEP( pData,pNew->nVolume,pOld->nVolume);
	NCH_CCMP_STRING_STEP( pData,pNew->szOrderGroup,pOld->szOrderGroup);
	NCH_END_CCMP(pData,nclen);

	*pLen = nclen;		
	return nclen+sizeof(int);
}


//////////////////////////////////////////////////////////////////////////

//期货部分

int ptl_compress(const ATP_Msg_Fut_HoldPosition* pPosition,char* pData,int nLength)
{
	int nclen = 0;
	int *pLen = (int*)pData;
	pData += sizeof(int);


	//全量解压
	NCH_BEGIN_CMP_VERSION(pData,nLength ,1);
	NCH_CMP_INT64_STEP( pData,pPosition->nIdentity)
	NCH_CMP_STRING_STEP(pData,pPosition->szMarket);
	NCH_CMP_INT_STEP( pData,pPosition->nHolderType);
	NCH_CMP_STRING_STEP(pData,pPosition->szCode);
	NCH_CMP_STRING_STEP(pData,pPosition->szName);
	NCH_CMP_CHAR_STEP( pData,pPosition->cBSSide);
	NCH_CMP_INT_STEP( pData,pPosition->nBeginVol);
	NCH_CMP_INT_STEP( pData,pPosition->nEnableVol);
	NCH_CMP_INT_STEP( pData,pPosition->nRealVol);
	NCH_CMP_INT_STEP( pData,pPosition->nTodayOpenVol);
	NCH_CMP_INT_STEP( pData,pPosition->nPreDropVol);
	NCH_CMP_INT_STEP( pData,pPosition->nCostPrice);
	NCH_CMP_INT_STEP( pData,pPosition->nNewPrice);
	NCH_CMP_DOUBLE4_STEP( pData,pPosition->dHoldProfit);
	NCH_CMP_DOUBLE4_STEP( pData,pPosition->dHoldProfitFloat);
	NCH_CMP_DOUBLE4_STEP( pData,pPosition->dHoldBal);
	NCH_CMP_STRING_STEP( pData,pPosition->chRemark);
	NCH_END_CMP(pData,nclen);

	*pLen = nclen;
	return nclen + sizeof(int);	//返回长度.

}

int ptl_decmpress(char* pData,int nLength,ATP_Msg_Fut_HoldPosition* pPosition)
{
	int ndeclen = 0;

	int nItemLen = *( (int*)pData);	//后面数据长度.

	pData += sizeof(int);

	//全量解压
	NCH_BEGIN_DCMP_VERSION(pData,nLength ,1);
	NCH_DCMP_INT64_STEP( pData,pPosition->nIdentity);
	NCH_DCMP_STRING_STEP(pData,pPosition->szMarket,sizeof(pPosition->szMarket));
	NCH_DCMP_INT_STEP( pData,pPosition->nHolderType);
	NCH_DCMP_STRING_STEP(pData,pPosition->szCode,sizeof(pPosition->szCode));
	NCH_DCMP_STRING_STEP(pData,pPosition->szName,sizeof(pPosition->szName));
	NCH_DCMP_CHAR_STEP( pData,pPosition->cBSSide);
	NCH_DCMP_INT_STEP( pData,pPosition->nBeginVol);
	NCH_DCMP_INT_STEP( pData,pPosition->nEnableVol);
	NCH_DCMP_INT_STEP( pData,pPosition->nRealVol);
	NCH_DCMP_INT_STEP( pData,pPosition->nTodayOpenVol);
	NCH_DCMP_INT_STEP( pData,pPosition->nPreDropVol);
	NCH_DCMP_INT_STEP( pData,pPosition->nCostPrice);
	NCH_DCMP_INT_STEP( pData,pPosition->nNewPrice);
	NCH_DCMP_DOUBLE4_STEP( pData,pPosition->dHoldProfit);
	NCH_DCMP_DOUBLE4_STEP( pData,pPosition->dHoldProfitFloat);
	NCH_DCMP_DOUBLE4_STEP( pData,pPosition->dHoldBal);
	NCH_DCMP_STRING_STEP( pData,pPosition->chRemark,sizeof(pPosition->chRemark));
	NCH_END_DCMP(pData,ndeclen);

	return nItemLen+sizeof(int);	//返回长度.
}



int ptl_comparecmpress(const ATP_Msg_Fut_HoldPosition* pNew,
					   const ATP_Msg_Fut_HoldPosition* pOld,
					   char* pData,
					   int nLength)
{
	ASSERT(pNew && pOld);	//必须要有一个不为空

	int nclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);


	NCH_BEGIN_CCMP_VERSION(pData,nLength,1,4);
		NCH_CCMP_INT64_STEP( pData,pNew->nIdentity,pOld->nIdentity);
		NCH_CCMP_STRING_STEP(pData,pNew->szMarket,pOld->szMarket);
		NCH_CCMP_INT_STEP( pData,pNew->nHolderType,pOld->nHolderType);
		NCH_CCMP_STRING_STEP(pData,pNew->szCode,pOld->szCode);
		NCH_CCMP_STRING_STEP(pData,pNew->szName,pOld->szName);
		NCH_CCMP_INT_STEP( pData,pNew->cBSSide,pOld->cBSSide);
		NCH_CCMP_INT_STEP( pData,pNew->nBeginVol,pOld->nBeginVol);
		NCH_CCMP_INT_STEP( pData,pNew->nEnableVol,pOld->nEnableVol);
		NCH_CCMP_INT_STEP( pData,pNew->nRealVol,pOld->nRealVol);
		NCH_CCMP_INT_STEP( pData,pNew->nTodayOpenVol,pOld->nTodayOpenVol);
		NCH_CCMP_INT_STEP( pData,pNew->nPreDropVol,pOld->nPreDropVol);
		NCH_CCMP_INT_STEP( pData,pNew->nCostPrice,pOld->nCostPrice);
		NCH_CCMP_INT_STEP( pData,pNew->nNewPrice,pOld->nNewPrice);
		NCH_CCMP_DOUBLE4_STEP( pData,pNew->dHoldProfit,pOld->dHoldProfit);
		NCH_CCMP_DOUBLE4_STEP( pData,pNew->dHoldProfitFloat,pOld->dHoldProfitFloat);
		NCH_CCMP_DOUBLE4_STEP( pData,pNew->dHoldBal,pOld->dHoldBal);
		NCH_CCMP_STRING_STEP(pData,pNew->chRemark,pOld->chRemark);
	NCH_END_CCMP(pData,nclen);

	*pLen = nclen;		
	return nclen+sizeof(int);
}


int ptl_comparedecmpress(char* pData,
						 int nLength,
						 ATP_Msg_Fut_HoldPosition* pPosition
						 )
{
	int ndclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);

	NCH_BEGIN_DCCMP_VERSION(pData,nLength,1);
	NCH_DCCMP_INT64_STEP( pData,pPosition->nIdentity);
	NCH_DCCMP_STRING_STEP(pData,pPosition->szMarket,sizeof(pPosition->szMarket));
	NCH_DCCMP_INT_STEP( pData,pPosition->nHolderType);
	NCH_DCCMP_STRING_STEP(pData,pPosition->szCode,sizeof(pPosition->szCode));
	NCH_DCCMP_STRING_STEP(pData,pPosition->szName,sizeof(pPosition->szName));
	NCH_DCCMP_INT_STEP( pData,pPosition->cBSSide);
	NCH_DCCMP_INT_STEP( pData,pPosition->nBeginVol);
	NCH_DCCMP_INT_STEP( pData,pPosition->nEnableVol);
	NCH_DCCMP_INT_STEP( pData,pPosition->nRealVol);
	NCH_DCCMP_INT_STEP( pData,pPosition->nTodayOpenVol);
	NCH_DCCMP_INT_STEP( pData,pPosition->nPreDropVol);
	NCH_DCCMP_INT_STEP( pData,pPosition->nCostPrice);
	NCH_DCCMP_INT_STEP( pData,pPosition->nNewPrice);
	NCH_DCCMP_DOUBLE4_STEP( pData,pPosition->dHoldProfit);
	NCH_DCCMP_DOUBLE4_STEP( pData,pPosition->dHoldProfitFloat);
	NCH_DCCMP_DOUBLE4_STEP( pData,pPosition->dHoldBal);
	NCH_DCCMP_STRING_STEP(pData,pPosition->chRemark,sizeof(pPosition->chRemark));
	NCH_END_DCCMP(pData,ndclen);

	return *pLen+sizeof(int);
}




/**
* 压缩成交记录信息到指定的内存中
* @param pMatch  成交记录
* @param pData   指写的内存
* @param nLength 内存长度
*/
int ptl_compress(const ATP_Msg_Fut_QueryMatch_Answer* pMatch,char* pData,int nLength)
{
	int nclen = 0;
	int *pLen = (int*)pData;
	pData += sizeof(int);


	//全量解压
	NCH_BEGIN_CMP_VERSION(pData,nLength ,1);
	NCH_CMP_INT64_STEP(pData,pMatch->nIdentity);

	NCH_CMP_STRING_STEP(pData,pMatch->order.szMarket);
	NCH_CMP_INT_STEP(pData,pMatch->order.nHolderType);
	NCH_CMP_STRING_STEP(pData,pMatch->order.szCode);
	NCH_CMP_STRING_STEP(pData,pMatch->order.szName);
	NCH_CMP_INT_STEP(pData,pMatch->order.cBSSide);
	NCH_CMP_INT_STEP(pData,pMatch->order.nPrice);
	NCH_CMP_INT_STEP(pData,pMatch->order.nKPFlag);
	NCH_CMP_INT_STEP(pData,pMatch->order.nPrice);
	NCH_CMP_INT_STEP(pData,pMatch->order.nHedgeType);
	NCH_CMP_STRING_STEP(pData,pMatch->order.szOrderGroup);


	NCH_CMP_STRING_STEP(pData,pMatch->chPostStr);
	NCH_CMP_INT_STEP(pData,pMatch->nStatus);				
	NCH_CMP_INT_STEP(pData,pMatch->nMadeVolume);
	NCH_CMP_INT_STEP(pData,pMatch->nMadePrice);
	NCH_CMP_INT_STEP(pData,pMatch->nCancelVolume);
	NCH_CMP_INT_STEP(pData,pMatch->nMadeTime);	
	NCH_CMP_STRING_STEP(pData,pMatch->chOrderNumber);
	NCH_CMP_STRING_STEP(pData,pMatch->chMadeNumber);
	NCH_CMP_STRING_STEP(pData,pMatch->chRemark);
	NCH_CMP_STRING_STEP(pData,pMatch->chRemark1);
	NCH_CMP_DOUBLE4_STEP(pData,pMatch->dFrozFee);
	NCH_CMP_DOUBLE4_STEP(pData,pMatch->dDropProfit);
	NCH_CMP_DOUBLE4_STEP(pData,pMatch->dDropFrofitFloat);
	NCH_END_CMP(pData,nclen);

	*pLen = nclen;
	return nclen + sizeof(int);	//返回长度.

}


/**
* 从指定的内存中解压缩成交信息
* @param pData      指写的内存
* @param nBufferLen 内存长度
* @param pMatch  成交记录
*/
int ptl_decmpress(char* pData,int nLength,ATP_Msg_Fut_QueryMatch_Answer* pMatch)
{
	int ndeclen = 0;

	int nItemLen = *( (int*)pData);	//后面数据长度.

	pData += sizeof(int);

	//全量解压
	NCH_BEGIN_DCMP_VERSION(pData,nLength ,1);
	NCH_DCMP_INT64_STEP(pData,pMatch->nIdentity);

	NCH_DCMP_STRING_STEP(pData,pMatch->order.szMarket,sizeof(pMatch->order.szMarket));
	NCH_DCMP_INT_STEP(pData,pMatch->order.nHolderType);
	NCH_DCMP_STRING_STEP(pData,pMatch->order.szCode,sizeof(pMatch->order.szCode));
	NCH_DCMP_STRING_STEP(pData,pMatch->order.szName,sizeof(pMatch->order.szName));
	NCH_DCMP_INT_STEP(pData,pMatch->order.cBSSide);
	NCH_DCMP_INT_STEP(pData,pMatch->order.nKPFlag);
	NCH_DCMP_INT_STEP(pData,pMatch->order.nHedgeType);
	NCH_DCMP_INT_STEP(pData,pMatch->order.nPrice);
	NCH_DCMP_INT_STEP(pData,pMatch->order.nVolume);
	NCH_DCMP_STRING_STEP(pData,pMatch->order.szOrderGroup,sizeof(pMatch->order.szOrderGroup));


	NCH_DCMP_STRING_STEP(pData,pMatch->chPostStr,sizeof(pMatch->chPostStr));
	NCH_DCMP_INT_STEP(pData,pMatch->nStatus);				
	NCH_DCMP_INT_STEP(pData,pMatch->nMadeVolume);
	NCH_DCMP_INT_STEP(pData,pMatch->nMadePrice);
	NCH_DCMP_INT_STEP(pData,pMatch->nCancelVolume);
	NCH_DCMP_INT_STEP(pData,pMatch->nMadeTime);	
	NCH_DCMP_STRING_STEP(pData,pMatch->chOrderNumber,sizeof(pMatch->chOrderNumber));
	NCH_DCMP_STRING_STEP(pData,pMatch->chMadeNumber,sizeof(pMatch->chMadeNumber));
	NCH_DCMP_STRING_STEP(pData,pMatch->chRemark,sizeof(pMatch->chRemark));
	NCH_DCMP_STRING_STEP(pData,pMatch->chRemark1,sizeof(pMatch->chRemark1));
	NCH_DCMP_DOUBLE4_STEP(pData,pMatch->dFrozFee);
	NCH_DCMP_DOUBLE4_STEP(pData,pMatch->dDropProfit);
	NCH_DCMP_DOUBLE4_STEP(pData,pMatch->dDropFrofitFloat);

	NCH_END_DCMP(pData,ndeclen);

	return nItemLen+sizeof(int);	//返回长度.
}



/**
* 压缩资产记录信息到指定的内存中
* @param pAssets 资产记录
* @param pData   指写的内存
* @param nLength 内存长度
*/
int ptl_compress(const ATP_Msg_Fut_QueryAssets_Answer* pAssets,char* pData,int nLength)
{
	int nclen = 0;
	int *pLen = (int*)pData;
	pData += sizeof(int);


	//全量解压
	NCH_BEGIN_CMP_VERSION(pData,nLength ,1);	
	NCH_CMP_INT64_STEP(pData,pAssets->nIdentity);
	NCH_CMP_INT_STEP(pData,pAssets->chMoneyType);	
	NCH_CMP_STRING_STEP(pData,pAssets->chRemark);
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dCurrentBal);					
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dEnableBal);				
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dFetchBal);					
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dFrozBal);				
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dRealHoldBalA);				
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dRealHoldBalB);					
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dHoldProfit);				
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dHoldProfitFloat);						
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dPreRightsBal);				
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dRightsBal);	
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dRightsBalFloat);
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dRealDrop);
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dRealDrop_Float);
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dBailBalance);
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dRealOpen);
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dRealOpen_Float);
	NCH_CMP_DOUBLE4_STEP(pData,pAssets->dIntrBal);
	NCH_END_CMP(pData,nclen);

	*pLen = nclen;
	return nclen + sizeof(int);	//返回长度.


}


/**
* 从指定的内存中解压缩资产信息
* @param pData      指写的内存
* @param nBufferLen 内存长度
* @param pAssets  资产记录
*/
int ptl_decmpress(char* pData,int nLength,ATP_Msg_Fut_QueryAssets_Answer* pAssets)
{
	int ndeclen = 0;

	int nItemLen = *( (int*)pData);	//后面数据长度.

	pData += sizeof(int);

	//全量解压
	NCH_BEGIN_DCMP_VERSION(pData,nLength ,1);
	NCH_DCMP_INT64_STEP(pData,pAssets->nIdentity);
	NCH_DCMP_INT_STEP(pData,pAssets->chMoneyType);	
	NCH_DCMP_STRING_STEP(pData,pAssets->chRemark,sizeof(pAssets->chRemark));
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dCurrentBal);					
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dEnableBal);				
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dFetchBal);					
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dFrozBal);				
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dRealHoldBalA);				
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dRealHoldBalB);					
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dHoldProfit);				
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dHoldProfitFloat);						
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dPreRightsBal);				
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dRightsBal);	
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dRightsBalFloat);
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dRealDrop);
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dRealDrop_Float);
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dBailBalance);
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dRealOpen);
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dRealOpen_Float);
	NCH_DCMP_DOUBLE4_STEP(pData,pAssets->dIntrBal);	
	NCH_END_DCMP(pData,ndeclen);

	return nItemLen+sizeof(int);	//返回长度.

}




/**
* 对比压缩持仓信息到指定的内存中
* @param pNew		新的委托信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的委托信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
int ptl_compress(const ATP_Msg_Fut_QueryOrderRecords_Answer* pOrderRecord,char* pData,int nLength)
{
	int nclen = 0;
	int *pLen = (int*)pData;
	pData += sizeof(int);


	//全量解压
	NCH_BEGIN_CMP_VERSION(pData,nLength ,1);
	NCH_CMP_INT64_STEP(pData,pOrderRecord->nIdentity);

	NCH_CMP_STRING_STEP(pData,pOrderRecord->order.szMarket);
	NCH_CMP_INT_STEP(pData,pOrderRecord->order.nHolderType);
	NCH_CMP_STRING_STEP(pData,pOrderRecord->order.szCode);
	NCH_CMP_STRING_STEP(pData,pOrderRecord->order.szName);
	NCH_CMP_INT_STEP(pData,pOrderRecord->order.cBSSide);
	NCH_CMP_INT_STEP(pData,pOrderRecord->order.nPrice);
	NCH_CMP_INT_STEP(pData,pOrderRecord->order.nKPFlag);
	NCH_CMP_INT_STEP(pData,pOrderRecord->order.nPrice);
	NCH_CMP_INT_STEP(pData,pOrderRecord->order.nHedgeType);
	NCH_CMP_STRING_STEP(pData,pOrderRecord->order.szOrderGroup);


	NCH_CMP_STRING_STEP(pData,pOrderRecord->chPostStr);
	NCH_CMP_INT_STEP(pData,pOrderRecord->dwStatus);
	NCH_CMP_INT_STEP(pData,pOrderRecord->nOrderDate);
	NCH_CMP_INT_STEP(pData,pOrderRecord->nOrderTime);	
	NCH_CMP_INT_STEP(pData,pOrderRecord->nMadeVolume);				
	NCH_CMP_INT_STEP(pData,pOrderRecord->nMadePrice);				
	NCH_CMP_INT_STEP(pData,pOrderRecord->nCancelVolume);				
	NCH_CMP_STRING_STEP(pData,pOrderRecord->chOrderNumber);
	NCH_CMP_DOUBLE4_STEP(pData,pOrderRecord->dHoldBal);	
	NCH_CMP_DOUBLE4_STEP(pData,pOrderRecord->dFrozFare);
	NCH_CMP_STRING_STEP(pData,pOrderRecord->chNeedInfo);

	NCH_END_CMP(pData,nclen);

	*pLen = nclen;
	return nclen + sizeof(int);	//返回长度.

}


int ptl_decmpress(char* pData,int nLength,ATP_Msg_Fut_QueryOrderRecords_Answer* pOrderRecord)
{
	int ndeclen = 0;

	int nItemLen = *( (int*)pData);	//后面数据长度.

	pData += sizeof(int);

	//全量解压
	NCH_BEGIN_DCMP_VERSION(pData,nLength ,1);
	NCH_DCMP_INT64_STEP(pData,pOrderRecord->nIdentity);

	NCH_DCMP_STRING_STEP(pData,pOrderRecord->order.szMarket,sizeof(pOrderRecord->order.szMarket));
	NCH_DCMP_INT_STEP(pData,pOrderRecord->order.nHolderType);
	NCH_DCMP_STRING_STEP(pData,pOrderRecord->order.szCode,sizeof(pOrderRecord->order.szCode));
	NCH_DCMP_STRING_STEP(pData,pOrderRecord->order.szName,sizeof(pOrderRecord->order.szName));
	NCH_DCMP_INT_STEP(pData,pOrderRecord->order.cBSSide);
	NCH_DCMP_INT_STEP(pData,pOrderRecord->order.nPrice);
	NCH_DCMP_INT_STEP(pData,pOrderRecord->order.nKPFlag);
	NCH_DCMP_INT_STEP(pData,pOrderRecord->order.nPrice);
	NCH_DCMP_INT_STEP(pData,pOrderRecord->order.nHedgeType);
	NCH_DCMP_STRING_STEP(pData,pOrderRecord->order.szOrderGroup,sizeof(pOrderRecord->order.szOrderGroup));


	NCH_DCMP_STRING_STEP(pData,pOrderRecord->chPostStr,sizeof(pOrderRecord->chPostStr));
	NCH_DCMP_INT_STEP(pData,pOrderRecord->dwStatus);
	NCH_DCMP_INT_STEP(pData,pOrderRecord->nOrderDate);
	NCH_DCMP_INT_STEP(pData,pOrderRecord->nOrderTime);	
	NCH_DCMP_INT_STEP(pData,pOrderRecord->nMadeVolume);				
	NCH_DCMP_INT_STEP(pData,pOrderRecord->nMadePrice);				
	NCH_DCMP_INT_STEP(pData,pOrderRecord->nCancelVolume);				
	NCH_DCMP_STRING_STEP(pData,pOrderRecord->chOrderNumber,sizeof(pOrderRecord->chOrderNumber));
	NCH_DCMP_DOUBLE4_STEP(pData,pOrderRecord->dHoldBal);	
	NCH_DCMP_DOUBLE4_STEP(pData,pOrderRecord->dFrozFare);
	NCH_DCMP_STRING_STEP(pData,pOrderRecord->chNeedInfo,sizeof(pOrderRecord->chNeedInfo));
	NCH_END_DCMP(pData,ndeclen);

	return nItemLen+sizeof(int);	//返回长度.
}


/**
* 对比压缩持仓信息到指定的内存中
* @param pNew		新的委托信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的委托信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
int ptl_comparecmpress(const ATP_Msg_Fut_QueryOrderRecords_Answer* pNew,const ATP_Msg_Fut_QueryOrderRecords_Answer* pOld,
					   char* pData,int nLength)
{
	ASSERT(pNew && pOld);	//必须要有一个不为空

	int nclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);


	NCH_BEGIN_CCMP_VERSION(pData,nLength,1,4);
	NCH_CCMP_INT64_STEP(pData,pNew->nIdentity,pOld->nIdentity);

	NCH_CCMP_STRING_STEP(pData,pNew->order.szMarket,pOld->order.szMarket);
	NCH_CCMP_INT_STEP(pData,pNew->order.nHolderType,pOld->order.nHolderType);
	NCH_CCMP_STRING_STEP(pData,pNew->order.szCode,pOld->order.szCode);
	NCH_CCMP_STRING_STEP(pData,pNew->order.szName,pOld->order.szName);
	NCH_CCMP_INT_STEP(pData,pNew->order.cBSSide,pOld->order.cBSSide);
	NCH_CCMP_INT_STEP(pData,pNew->order.nKPFlag,pOld->order.nKPFlag);
	NCH_CCMP_INT_STEP(pData,pNew->order.nHedgeType,pOld->order.nHedgeType);
	NCH_CCMP_INT_STEP(pData,pNew->order.nPrice,pOld->order.nPrice);
	NCH_CCMP_INT_STEP(pData,pNew->order.nVolume,pOld->order.nVolume);
	NCH_CCMP_STRING_STEP(pData,pNew->order.szOrderGroup,pOld->order.szOrderGroup);


	NCH_CCMP_STRING_STEP(pData,pNew->chPostStr,pOld->chPostStr);
	NCH_CCMP_INT_STEP(pData,pNew->dwStatus,pOld->dwStatus);
	NCH_CCMP_INT_STEP(pData,pNew->nOrderDate,pOld->nOrderDate);
	NCH_CCMP_INT_STEP(pData,pNew->nOrderTime,pOld->nOrderTime);	
	NCH_CCMP_INT_STEP(pData,pNew->nMadeVolume,pOld->nMadeVolume);				
	NCH_CCMP_INT_STEP(pData,pNew->nMadePrice,pOld->nMadePrice);				
	NCH_CCMP_INT_STEP(pData,pNew->nCancelVolume,pOld->nCancelVolume);				
	NCH_CCMP_STRING_STEP(pData,pNew->chOrderNumber,pOld->chOrderNumber);
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dHoldBal,pOld->dHoldBal);
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dFrozFare,pOld->dFrozFare);
	NCH_CCMP_STRING_STEP(pData,pNew->chNeedInfo,pOld->chNeedInfo);
	NCH_END_CCMP(pData,nclen);

	*pLen = nclen;		
	return nclen+sizeof(int);
}


int ptl_comparedecmpress(char* pData,int nLength,ATP_Msg_Fut_QueryOrderRecords_Answer* pOrderRecord)
{
	int ndclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);

	NCH_BEGIN_DCCMP_VERSION(pData,nLength,1);
	NCH_DCCMP_INT64_STEP(pData,pOrderRecord->nIdentity);

	NCH_DCCMP_STRING_STEP(pData,pOrderRecord->order.szMarket,sizeof(pOrderRecord->order.szMarket));
	NCH_DCCMP_INT_STEP(pData,pOrderRecord->order.nHolderType);
	NCH_DCCMP_STRING_STEP(pData,pOrderRecord->order.szCode,sizeof(pOrderRecord->order.szCode));
	NCH_DCCMP_STRING_STEP(pData,pOrderRecord->order.szName,sizeof(pOrderRecord->order.szName));
	NCH_DCCMP_INT_STEP(pData,pOrderRecord->order.cBSSide);
	NCH_DCCMP_INT_STEP(pData,pOrderRecord->order.nKPFlag);
	NCH_DCCMP_INT_STEP(pData,pOrderRecord->order.nHedgeType);
	NCH_DCCMP_INT_STEP(pData,pOrderRecord->order.nPrice);
	NCH_DCCMP_INT_STEP(pData,pOrderRecord->order.nVolume);
	NCH_DCCMP_STRING_STEP(pData,pOrderRecord->order.szOrderGroup,sizeof(pOrderRecord->order.szOrderGroup));


	NCH_DCCMP_STRING_STEP(pData,pOrderRecord->chPostStr,sizeof(pOrderRecord->chPostStr));
	NCH_DCCMP_INT_STEP(pData,pOrderRecord->dwStatus);
	NCH_DCCMP_INT_STEP(pData,pOrderRecord->nOrderDate);
	NCH_DCCMP_INT_STEP(pData,pOrderRecord->nOrderTime);	
	NCH_DCCMP_INT_STEP(pData,pOrderRecord->nMadeVolume);				
	NCH_DCCMP_INT_STEP(pData,pOrderRecord->nMadePrice);				
	NCH_DCCMP_INT_STEP(pData,pOrderRecord->nCancelVolume);				
	NCH_DCCMP_STRING_STEP(pData,pOrderRecord->chOrderNumber,sizeof(pOrderRecord->chOrderNumber));
	NCH_DCCMP_DOUBLE4_STEP(pData,pOrderRecord->dHoldBal);
	NCH_DCCMP_DOUBLE4_STEP(pData,pOrderRecord->dFrozFare);
	NCH_DCCMP_STRING_STEP(pData,pOrderRecord->chNeedInfo,sizeof(pOrderRecord->chNeedInfo));
	NCH_END_DCCMP(pData,ndclen);

	return *pLen+sizeof(int);
}


/**
* 对比压缩成交信息到指定的内存中
* @param pNew		新的委托信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的委托信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
int ptl_comparecmpress(const ATP_Msg_Fut_QueryMatch_Answer* pNew,const ATP_Msg_Fut_QueryMatch_Answer* pOld,
					   char* pData,int nLength)
{
	ASSERT(pNew && pOld);	//必须要有一个不为空

	int nclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);


	NCH_BEGIN_CCMP_VERSION(pData,nLength,1,4);
	NCH_CCMP_INT64_STEP(pData,pNew->nIdentity,pOld->nIdentity);

	NCH_CCMP_STRING_STEP(pData,pNew->order.szMarket,pOld->order.szMarket);
	NCH_CCMP_INT_STEP(pData,pNew->order.nHolderType,pOld->order.nHolderType);
	NCH_CCMP_STRING_STEP(pData,pNew->order.szCode,pOld->order.szCode);
	NCH_CCMP_STRING_STEP(pData,pNew->order.szName,pOld->order.szName);
	NCH_CCMP_INT_STEP(pData,pNew->order.cBSSide,pOld->order.cBSSide);
	NCH_CCMP_INT_STEP(pData,pNew->order.nKPFlag,pOld->order.nKPFlag);
	NCH_CCMP_INT_STEP(pData,pNew->order.nHedgeType,pOld->order.nHedgeType);
	NCH_CCMP_INT_STEP(pData,pNew->order.nPrice,pOld->order.nPrice);
	NCH_CCMP_INT_STEP(pData,pNew->order.nVolume,pOld->order.nVolume);
	NCH_CCMP_STRING_STEP(pData,pNew->order.szOrderGroup,pOld->order.szOrderGroup);


	NCH_CCMP_STRING_STEP(pData,pNew->chPostStr,pOld->chPostStr);
	NCH_CCMP_INT_STEP(pData,pNew->nStatus,pOld->nStatus);				
	NCH_CCMP_INT_STEP(pData,pNew->nMadeVolume,pOld->nMadeVolume);
	NCH_CCMP_INT_STEP(pData,pNew->nMadePrice,pOld->nMadePrice);
	NCH_CCMP_INT_STEP(pData,pNew->nCancelVolume,pOld->nCancelVolume);
	NCH_CCMP_INT_STEP(pData,pNew->nMadeTime,pOld->nMadeTime);	
	NCH_CCMP_STRING_STEP(pData,pNew->chOrderNumber,pOld->chOrderNumber);
	NCH_CCMP_STRING_STEP(pData,pNew->chMadeNumber,pOld->chMadeNumber);
	NCH_CCMP_STRING_STEP(pData,pNew->chRemark,pOld->chRemark);
	NCH_CCMP_STRING_STEP(pData,pNew->chRemark1,pOld->chRemark1);
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dDropProfit,pOld->dDropProfit);
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dDropFrofitFloat,pOld->dDropFrofitFloat);
	NCH_END_CCMP(pData,nclen);

	*pLen = nclen;		
	return nclen+sizeof(int);
}


int ptl_comparedecmpress(char* pData,int nLength,ATP_Msg_Fut_QueryMatch_Answer* pMatch)
{
	int ndclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);

	NCH_BEGIN_DCCMP_VERSION(pData,nLength,1);
	NCH_DCCMP_INT64_STEP(pData,pMatch->nIdentity);

	NCH_DCCMP_STRING_STEP(pData,pMatch->order.szMarket,sizeof(pMatch->order.szMarket));
	NCH_DCCMP_INT_STEP(pData,pMatch->order.nHolderType);
	NCH_DCCMP_STRING_STEP(pData,pMatch->order.szCode,sizeof(pMatch->order.szCode));
	NCH_DCCMP_STRING_STEP(pData,pMatch->order.szName,sizeof(pMatch->order.szName));
	NCH_DCCMP_INT_STEP(pData,pMatch->order.cBSSide);
	NCH_DCCMP_INT_STEP(pData,pMatch->order.nPrice);
	NCH_DCCMP_INT_STEP(pData,pMatch->order.nVolume);
	NCH_DCCMP_STRING_STEP(pData,pMatch->order.szOrderGroup,sizeof(pMatch->order.szOrderGroup));


	NCH_DCCMP_STRING_STEP(pData,pMatch->chPostStr,sizeof(pMatch->chPostStr));
	NCH_DCCMP_INT_STEP(pData,pMatch->nStatus);				
	NCH_DCCMP_INT_STEP(pData,pMatch->nMadeVolume);
	NCH_DCCMP_INT_STEP(pData,pMatch->nMadePrice);
	NCH_DCCMP_INT_STEP(pData,pMatch->nCancelVolume);
	NCH_DCCMP_INT_STEP(pData,pMatch->nMadeTime);	
	NCH_DCCMP_STRING_STEP(pData,pMatch->chOrderNumber,sizeof(pMatch->chOrderNumber));
	NCH_DCCMP_STRING_STEP(pData,pMatch->chMadeNumber,sizeof(pMatch->chMadeNumber));
	NCH_DCCMP_STRING_STEP(pData,pMatch->chRemark,sizeof(pMatch->chRemark));
	NCH_DCCMP_STRING_STEP(pData,pMatch->chRemark1,sizeof(pMatch->chRemark1));
	NCH_DCCMP_DOUBLE4_STEP(pData,pMatch->dFrozFee);
	NCH_DCCMP_DOUBLE4_STEP(pData,pMatch->dDropProfit);
	NCH_DCCMP_DOUBLE4_STEP(pData,pMatch->dDropFrofitFloat);

	NCH_END_DCCMP(pData,ndclen);

	return *pLen+sizeof(int);
}

/**
* 对比压缩资产信息到指定的内存中
* @param pNew		新的资产信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的资产信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
int ptl_comparecmpress(const ATP_Msg_Fut_QueryAssets_Answer* pNew,const ATP_Msg_Fut_QueryAssets_Answer* pOld,
					   char* pData,int nLength)
{
	ASSERT(pNew && pOld);	//必须要有一个不为空

	int nclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);


	NCH_BEGIN_CCMP_VERSION(pData,nLength,1,4);
	NCH_CCMP_INT64_STEP(pData,pNew->nIdentity,pOld->nIdentity);
	NCH_CCMP_INT_STEP(pData,pNew->chMoneyType,pOld->chMoneyType);	
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dCurrentBal,pOld->dCurrentBal);
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dEnableBal,pOld->dEnableBal);					
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dFetchBal,pOld->dFetchBal);				
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dFrozBal,pOld->dFrozBal);					
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dRealHoldBalA,pOld->dRealHoldBalA);				
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dRealHoldBalB,pOld->dRealHoldBalB);				
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dHoldProfit,pOld->dHoldProfit);					
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dHoldProfitFloat,pOld->dHoldProfitFloat);				
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dPreRightsBal,pOld->dPreRightsBal);						
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dRightsBal,pOld->dRightsBal);				
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dRightsBalFloat,pOld->dRightsBalFloat);
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dRealDrop,pOld->dRealDrop);
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dRealDrop_Float,pOld->dRealDrop_Float);
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dFrozenFare,pOld->dFrozenFare);
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dBailBalance,pOld->dBailBalance);
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dRealOpen,pOld->dRealOpen);
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dRealOpen_Float,pOld->dRealOpen_Float);
	NCH_CCMP_DOUBLE4_STEP(pData,pNew->dIntrBal,pOld->dIntrBal);

	NCH_END_CCMP(pData,nclen);

	*pLen = nclen;		
	return nclen+sizeof(int);

}


int ptl_comparedecmpress(char* pData,int nLength,ATP_Msg_Fut_QueryAssets_Answer* pAssets)
{
	int ndclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);

	NCH_BEGIN_DCCMP_VERSION(pData,nLength,1);
	NCH_DCCMP_INT64_STEP(pData,pAssets->nIdentity);
	NCH_DCCMP_INT_STEP(pData,pAssets->chMoneyType);	
	NCH_DCCMP_STRING_STEP(pData,pAssets->chRemark,sizeof(pAssets->chRemark));
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dCurrentBal);					
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dEnableBal);				
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dFetchBal);					
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dFrozBal);				
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dRealHoldBalA);				
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dRealHoldBalB);					
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dHoldProfit);				
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dHoldProfitFloat);						
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dPreRightsBal);				
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dRightsBal);
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dRightsBalFloat);
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dRealDrop);
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dRealDrop_Float);
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dFrozenFare);
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dBailBalance);
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dRealOpen);
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dRealOpen_Float);
	NCH_DCCMP_DOUBLE4_STEP(pData,pAssets->dIntrBal);


	NCH_END_DCCMP(pData,ndclen);

	return *pLen+sizeof(int);
}

//////////////////////////////////////////////////////////////////////////
//下单结构体
int ptl_compress(const ATP_Msg_Fut_MakeOrder* pPosition,char* pData,int nLength)
{
	int nclen = 0;
	int *pLen = (int*)pData;
	pData += sizeof(int);


	//全量解压
	NCH_BEGIN_CMP_VERSION(pData,nLength ,1);
	NCH_CMP_STRING_STEP(pData,pPosition->szMarket);
	NCH_CMP_INT_STEP( pData,pPosition->nHolderType);
	NCH_CMP_STRING_STEP(pData,pPosition->szCode);
	NCH_CMP_STRING_STEP(pData,pPosition->szName);
	NCH_CMP_INT_STEP( pData,pPosition->cBSSide);
	NCH_CMP_INT_STEP( pData,pPosition->nKPFlag);
	NCH_CMP_INT_STEP( pData,pPosition->nHedgeType);
	NCH_CMP_INT_STEP( pData,pPosition->nPrice);
	NCH_CMP_INT_STEP( pData,pPosition->nVolume);
	NCH_CMP_STRING_STEP( pData,pPosition->szOrderGroup);
	NCH_END_CMP(pData,nclen);

	*pLen = nclen;
	return nclen + sizeof(int);	//返回长度.

}

int ptl_decmpress(char* pData,int nLength,ATP_Msg_Fut_MakeOrder* pPosition)
{
	int ndeclen = 0;

	int nItemLen = *( (int*)pData);	//后面数据长度.

	pData += sizeof(int);

	//全量解压
	NCH_BEGIN_DCMP_VERSION(pData,nLength ,1);
	NCH_DCMP_STRING_STEP(pData,pPosition->szMarket,4);
	NCH_DCMP_INT_STEP( pData,pPosition->nHolderType);
	NCH_DCMP_STRING_STEP(pData,pPosition->szCode,12);
	NCH_DCMP_STRING_STEP(pData,pPosition->szName,16);
	NCH_DCMP_INT_STEP( pData,pPosition->cBSSide);
	NCH_DCMP_INT_STEP( pData,pPosition->nKPFlag);
	NCH_DCMP_INT_STEP( pData,pPosition->nHedgeType);
	NCH_DCMP_INT_STEP( pData,pPosition->nPrice);
	NCH_DCMP_INT_STEP( pData,pPosition->nVolume);
	NCH_DCMP_STRING_STEP( pData,pPosition->szOrderGroup,LEN_ORDERGROUP);
	NCH_END_DCMP(pData,ndeclen);

	return nItemLen+sizeof(int);	//返回长度.
}



int ptl_comparecmpress(const ATP_Msg_Fut_MakeOrder* pNew,
	const ATP_Msg_Fut_MakeOrder* pOld,
	char* pData,
	int nLength)
{
	ASSERT(pNew && pOld);	//必须要有一个不为空

	int nclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);


	NCH_BEGIN_CCMP_VERSION(pData,nLength,1,4);
	NCH_CCMP_STRING_STEP(pData,pNew->szMarket,pOld->szMarket);
	NCH_CCMP_INT_STEP( pData,pNew->nHolderType,pOld->nHolderType);
	NCH_CCMP_STRING_STEP(pData,pNew->szCode,pOld->szCode);
	NCH_CCMP_STRING_STEP(pData,pNew->szName,pOld->szName);
	NCH_CCMP_INT_STEP( pData,pNew->cBSSide,pOld->cBSSide);
	NCH_CCMP_INT_STEP( pData,pNew->nKPFlag,pOld->nKPFlag);
	NCH_CCMP_INT_STEP( pData,pNew->nHedgeType,pOld->nHedgeType);
	NCH_CCMP_INT_STEP( pData,pNew->nPrice,pOld->nPrice);
	NCH_CCMP_INT_STEP( pData,pNew->nVolume,pOld->nVolume);
	NCH_CCMP_STRING_STEP( pData,pNew->szOrderGroup,pOld->szOrderGroup);
	NCH_END_CCMP(pData,nclen);

	*pLen = nclen;		
	return nclen+sizeof(int);
}



//////////////////////////////////////////////////////////////////////////


int ptl_compress(const ATP_Msg_CurrentAlgoStatus* pStatus,char* pData,int nLength)
{
	int nclen = 0;
	int *pLen = (int*)pData;
	pData += sizeof(int);


	//全量压缩
	NCH_BEGIN_CMP_VERSION(pData,nLength ,1)	
		NCH_CMP_INT64_STEP(pData,pStatus->nIdentity);
		NCH_CMP_STRING_STEP(pData,pStatus->szName);
		NCH_CMP_INT_STEP(pData,pStatus->nBeginTime);
		NCH_CMP_INT_STEP(pData,pStatus->nMakeOrderTimes);
		NCH_CMP_INT_STEP(pData,pStatus->nFinish);
		NCH_CMP_INT_STEP(pData,pStatus->nTotal);
		NCH_CMP_STRING_STEP(pData,pStatus->szStatus);
	NCH_END_CMP(pData,nclen);

	*pLen = nclen;
	return nclen + sizeof(int);	//返回长度.

	
}


int ptl_decmpress(char* pData,int nLength,ATP_Msg_CurrentAlgoStatus* pStatus)
{
	int ndeclen = 0;

	int nItemLen = *( (int*)pData);	//后面数据长度.

	pData += sizeof(int);

	//全量解压
	NCH_BEGIN_DCMP_VERSION(pData,nLength ,1)
		NCH_DCMP_INT64_STEP(pData,pStatus->nIdentity);
		NCH_DCMP_STRING_STEP(pData,pStatus->szName,sizeof(pStatus->szName));
		NCH_DCMP_INT_STEP(pData,pStatus->nBeginTime);
		NCH_DCMP_INT_STEP(pData,pStatus->nMakeOrderTimes);
		NCH_DCMP_INT_STEP(pData,pStatus->nFinish);
		NCH_DCMP_INT_STEP(pData,pStatus->nTotal);
		NCH_DCMP_STRING_STEP(pData,pStatus->szStatus,sizeof(pStatus->szStatus));
	NCH_END_DCMP(pData,ndeclen);

	return nItemLen+sizeof(int);	//返回长度

	
}


/**
* 对比压缩资产信息到指定的内存中
* @param pNew		新的资产信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的资产信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
int ptl_comparecmpress(const ATP_Msg_CurrentAlgoStatus* pNew,const ATP_Msg_CurrentAlgoStatus* pOld,
							  char* pData,int nLength)
{
	ASSERT(pNew && pOld);	//必须要有一个不为空

	int nclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);


	NCH_BEGIN_CCMP_VERSION(pData,nLength,1,4)
		NCH_CCMP_INT64_STEP(pData,pNew->nIdentity,pOld->nIdentity);
		NCH_CCMP_STRING_STEP(pData,pNew->szName,pOld->szName);
		NCH_CCMP_INT_STEP(pData,pNew->nBeginTime,pOld->nBeginTime);
		NCH_CCMP_INT_STEP(pData,pNew->nMakeOrderTimes,pOld->nMakeOrderTimes);
		NCH_CCMP_INT_STEP(pData,pNew->nFinish,pOld->nFinish);
		NCH_CCMP_INT_STEP(pData,pNew->nTotal,pOld->nTotal);
		NCH_CCMP_STRING_STEP(pData,pNew->szStatus,pOld->szStatus);
	NCH_END_CCMP(pData,nclen);

	*pLen = nclen;		
	return nclen+sizeof(int);
	

}


int ptl_comparedecmpress(char* pData,int nLength,ATP_Msg_CurrentAlgoStatus* pStatus)
{
	int ndclen = 0;

	int *pLen = (int*)pData;
	pData += sizeof(int);

	NCH_BEGIN_DCCMP_VERSION(pData,nLength,1)
		NCH_DCCMP_INT64_STEP(pData,pStatus->nIdentity);
		NCH_DCCMP_STRING_STEP(pData,pStatus->szName,sizeof(pStatus->szName));
		NCH_DCCMP_INT_STEP(pData,pStatus->nBeginTime);
		NCH_DCCMP_INT_STEP(pData,pStatus->nMakeOrderTimes);
		NCH_DCCMP_INT_STEP(pData,pStatus->nFinish);
		NCH_DCCMP_INT_STEP(pData,pStatus->nTotal);
		NCH_DCCMP_STRING_STEP(pData,pStatus->szStatus,sizeof(pStatus->szStatus));
	NCH_END_DCCMP(pData,ndclen);

	return *pLen+sizeof(int);

}

//////////////////////////////////////////////////////////////////////////
//推送日志压缩
extern int ptl_compress(const ATP_Msg_AlgoLog* pLog,
						char* pData,
						int nLength)
{
	int nclen = 0;
	int *pLen = (int*)pData;
	pData += sizeof(int);


	//全量压缩
	NCH_BEGIN_CMP_VERSION(pData,nLength ,1);
		NCH_CMP_INT_STEP(pData,pLog->nId);
		NCH_CMP_INT_STEP(pData,pLog->nType);
		NCH_CMP_INT_STEP(pData,pLog->nCategory);
		NCH_CMP_INT_STEP(pData,pLog->nGrade);
		NCH_CMP_INT_STEP(pData,pLog->nTime);
		NCH_CMP_INT_STEP(pData,pLog->nDataLen);
		NCH_CMP_BINDATA_STEP(pData,pLog->pData,pLog->nDataLen);
		//为了兼容沛然的客户端
		NCH_CMP_INT64_STEP(pData,pLog->iSrcIdentity);
	NCH_END_CMP(pData,nclen);

	*pLen = nclen;
	return nclen + sizeof(int);	//返回长度.
}


extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_AlgoLog* pLog)
{
	int ndeclen = 0;

	int nItemLen = *( (int*)pData);	//后面数据长度.

	pData += sizeof(int);

	//全量解压
	NCH_BEGIN_DCMP_VERSION(pData,nLength ,1);
	NCH_DCMP_INT_STEP(pData,pLog->nId);
	NCH_DCMP_INT_STEP(pData,pLog->nType);
	NCH_DCMP_INT_STEP(pData,pLog->nCategory);
	NCH_DCMP_INT_STEP(pData,pLog->nGrade);
	NCH_DCMP_INT_STEP(pData,pLog->nTime);
	NCH_DCMP_INT_STEP(pData,pLog->nDataLen);
	pLog->pData = /*(void *)*/new char[pLog->nDataLen];
	int nOutLen = 0;
	if (pLog->pData)
	{
		memset(pLog->pData,0,pLog->nDataLen);
		NCH_DCMP_BINDATA_STEP(pData,pLog->pData,pLog->nDataLen,nOutLen);
	}
	//为了兼容沛然的客户端
	NCH_DCMP_INT64_STEP(pData,pLog->iSrcIdentity);
	
	NCH_END_DCMP(pData,ndeclen);

	return nItemLen+sizeof(int);	//返回长度
}

//////////////////////////////////////////////////////////////////////////
//日志类别
extern int ptl_compress(const ATP_Msg_Algo_LogCategory* pCate,
						char* pData,
						int nLength)
{
	int nclen = 0;
	int *pLen = (int*)pData;
	pData += sizeof(int);


	//全量压缩
	NCH_BEGIN_CMP_VERSION(pData,nLength ,1);
	NCH_CMP_INT_STEP(pData,pCate->nCate);
	NCH_CMP_STRING_STEP(pData,pCate->szDescription);
	NCH_END_CMP(pData,nclen);

	*pLen = nclen;
	return nclen + sizeof(int);	//返回长度.
}


extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Algo_LogCategory* pCate)
{
	int ndeclen = 0;

	int nItemLen = *( (int*)pData);	//后面数据长度.

	pData += sizeof(int);

	//全量解压
	NCH_BEGIN_DCMP_VERSION(pData,nLength ,1);
	NCH_DCMP_INT_STEP(pData,pCate->nCate);
	NCH_DCMP_STRING_STEP(pData,pCate->szDescription,sizeof(pCate->szDescription));
	NCH_END_DCMP(pData,ndeclen);

	return nItemLen+sizeof(int);	//返回长度
}