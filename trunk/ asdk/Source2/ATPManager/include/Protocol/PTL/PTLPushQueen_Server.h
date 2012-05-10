/* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法交易平台 推送模板库.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			 作者         修改说明
2010-12-4	 李伟		 创建
-------------------------------------------------------------
*/

#pragma once
#ifndef _PTLPUSHQUEEN_SERVER_H_
#define _PTLPUSHQUEEN_SERVER_H_

#include "TDPushProtocol.h"
#include "..\\..\\..\\include\\UTIAPI\\UTIDefine_Sec.h"
#include "..\\..\\..\\include\\UTIAPI\\UTIDefine_Fut.h"


#include "atlcore.h"
#include <list>
#include <algorithm>
using namespace std;

extern bool IsTheSameItem(const ATP_Msg_CurrentAlgoStatus& left,const ATP_Msg_CurrentAlgoStatus& right);
extern bool operator == (const ATP_Msg_CurrentAlgoStatus& left,const ATP_Msg_CurrentAlgoStatus& right);



extern bool IsTheSameItem(const UTI_SEC_OrderRecord& left,const UTI_SEC_OrderRecord& right);
extern bool IsTheSameItem(const UTI_SEC_Position& left,const UTI_SEC_Position& right);
extern bool IsTheSameItem(const UTI_SEC_Match& left,const UTI_SEC_Match& right);
extern bool IsTheSameItem(const UTI_SEC_Assets& left,const UTI_SEC_Assets& right);


extern bool IsTheSameItem(const UTI_FUT_OrderRecord& left,const UTI_FUT_OrderRecord& right);
extern bool IsTheSameItem(const UTI_FUT_Position& left,const UTI_FUT_Position& right);
extern bool IsTheSameItem(const UTI_FUT_Match& left,const UTI_FUT_Match& right);
extern bool IsTheSameItem(const UTI_FUT_Assets& left,const UTI_FUT_Assets& right);


extern bool operator == (const UTI_SEC_OrderRecord& left,const UTI_SEC_OrderRecord& right);
extern bool operator == (const UTI_SEC_Position& left,const UTI_SEC_Position& right);
extern bool operator == (const UTI_SEC_Match& left,const UTI_SEC_Match& right);
extern bool operator == (const UTI_SEC_Assets& left,const UTI_SEC_Assets& right);


extern bool operator == (const UTI_FUT_OrderRecord& left,const UTI_FUT_OrderRecord& right);
extern bool operator == (const UTI_FUT_Position& left,const UTI_FUT_Position& right);
extern bool operator == (const UTI_FUT_Match& left,const UTI_FUT_Match& right);
extern bool operator == (const UTI_FUT_Assets& left,const UTI_FUT_Assets& right);



/**
*  供服务源端使用，在一次会话中自动维持唯一编号.
*/
template <class Item>
class CPTLPushQueen_Server
	:protected list<Item>,
	protected CComAutoCriticalSection
{
public:
	CPTLPushQueen_Server()
	{
	}

	virtual ~CPTLPushQueen_Server()
	{
	}

public:
	/**
	* 判断证券持仓记录是否相同，只考虑数量部分
	* @param pItems				新数据项
	* @param nItems				数据项数	
	* @return 					相同则返回true，不同则返回false.
	*/
	bool IsSameHoldPosition_Sec(Item* pItems,int nItems)
	{
		bool bSame = true;
		bool bFind = false;
		Lock();
		for(int i=0;i<nItems;++i)
		{
			bFind = false;	//查找结果.
			for(iterator it= begin();it!=end();++it)
			{
				if(IsTheSameItem(pItems[i],*it))
				{
					bFind = true;

					if(pItems[i].i64Balance != (__int64)((*it).i64Balance)
						|| pItems[i].i64Available != (__int64)((*it).i64Available)
						|| pItems[i].i64Forzen != (__int64)((*it).i64Forzen)
						|| pItems[i].i64Buy != (__int64)((*it).i64Buy)
						|| pItems[i].i64Sale != (__int64)((*it).i64Sale)
						|| pItems[i].i64Qty != (__int64)((*it).i64Qty)
						|| pItems[i].i64Diff != (__int64)((*it).i64Diff))
					{
						bSame = false;
						break;
					}

				}
			}

			if(!bFind)
			{
				bSame = false;
			}

			if(!bSame)
			{
				break;
			}
		}

		Unlock();

		return bSame;
	}
	/**
	* 判断期货持仓记录是否相同，只考虑数量部分
	* @param pItems				新数据项
	* @param nItems				数据项数	
	* @return 					相同则返回true，不同则返回false.
	*/
	bool IsSameHoldPosition_Fut(Item* pItems,int nItems)
	{
		bool bSame = true;
		bool bFind = false;
		Lock();
		for(int i=0;i<nItems;++i)
		{
			bFind = false;	//查找结果.
			for(iterator it= begin();it!=end();++it)
			{
				if(IsTheSameItem(pItems[i],*it))
				{
					bFind = true;

					if(pItems[i].nBeginVol != (int)((*it).nBeginVol)
						|| pItems[i].nEnableVol != (int)((*it).nEnableVol)
						|| pItems[i].nRealVol != (int)((*it).nRealVol)
						|| pItems[i].nTodayOpenVol != (int)((*it).nTodayOpenVol)
						|| pItems[i].nPreDropVol != (int)((*it).nPreDropVol))
					{
						bSame = false;
						break;
					}

				}
			}

			if(!bFind)
			{
				bSame = false;
			}

			if(!bSame)
			{
				break;
			}
		}

		Unlock();

		return bSame;
	}
	/**
	* 向其中更新，添加，成员，并维护同一项的nIdentity不变，
	* 并为Item.nIdentity 自动分配新编号.
	* 通常该ＩＤ由服务端维护，客户端使用.
	* @param pItems				新数据项
	* @param nItems				数据项数	
	* @param bDelete			是否删除pItems中没有的项.
	* @param bChanged			[out]返回当前Queen与pItems中的数据是否相同.如果不同，输出true.
	*/
	void Update2QueenAndAssignID(Item* pItems,int nItems,bool bDelete,bool& bChanged)
	{
		bChanged = false;
		Lock();
		for(int i=0;i<nItems;++i)
		{
			bool bFind = false;	//查找结果.
			for(iterator it= begin();it!=end();++it)
			{
				if(IsTheSameItem(pItems[i],*it))
				{
					bFind = true;

					//如果是同一条记录.
					//更新.
					pItems[i].nIdentity = (INT64)((*it).nIdentity);

					if( !( pItems[i] == (*it)) )
					{	
						bChanged = true;						
						*it = *(pItems+i);		//更新数据.												
					}
				}
			}

			if(!bFind)
			{
				push_back(pItems[i]);
				iterator it = end();
				--it;
				(*it).nIdentity = (INT64)(&(*it));	//自动分配ＩＤ.
				bChanged = true;
			}
		}

		if(bDelete)
		{
			//删除队列中没有的项.
			for(iterator it = begin();it!=end();)
			{
				bool bFind = false;
				for(int i =0 ;i<nItems;++i)
				{
					if(IsTheSameItem(pItems[i],*it))
					{
						//找到相同的项.
						bFind = true;
						break;
					}
				}
				if(!bFind)
				{					
					it = erase(it);
					bChanged = true;
				}else
					++it;
			}
		}
		Unlock();
	}





	/**
	* 将数据取成数组，采用new分配，需要用delete []删除
	* @param pItems [out] 输出数组
	* @param nItems [out] 输出数据个数.
	*/
	void GetData(Item*& pItems,int& nItems)
	{
		Lock();
		nItems = size();

		if(nItems>0)
		{
			pItems = new Item[nItems];
			copy<iterator,Item*>(begin(),end(),pItems);
		}else
		{
			pItems = NULL;
		}
		Unlock();		
	}
};


typedef CPTLPushQueen_Server<UTI_SEC_OrderRecord> CSecServerOrderRecordQueen;

typedef CPTLPushQueen_Server<UTI_SEC_Position>	  CSecServerPositionQueen;

typedef CPTLPushQueen_Server<UTI_SEC_Match>       CSecServerMatchQueen;

typedef CPTLPushQueen_Server<UTI_SEC_Assets>	  CSecServerAssetsQueen;


typedef CPTLPushQueen_Server<UTI_FUT_OrderRecord> CFutServerOrderRecordQueen;

typedef CPTLPushQueen_Server<UTI_FUT_Position>	  CFutServerPositionQueen;

typedef CPTLPushQueen_Server<UTI_FUT_Match>       CFutServerMatchQueen;

typedef CPTLPushQueen_Server<UTI_FUT_Assets>	  CFutServerAssetsQueen;



#endif //_PTLPUSHQUEEN_SERVER_H_