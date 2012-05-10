/* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨����ƽ̨ ����ģ���.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			 ����         �޸�˵��
2010-12-4	 ��ΰ		 ����
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
*  ������Դ��ʹ�ã���һ�λỰ���Զ�ά��Ψһ���.
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
	* �ж�֤ȯ�ֲּ�¼�Ƿ���ͬ��ֻ������������
	* @param pItems				��������
	* @param nItems				��������	
	* @return 					��ͬ�򷵻�true����ͬ�򷵻�false.
	*/
	bool IsSameHoldPosition_Sec(Item* pItems,int nItems)
	{
		bool bSame = true;
		bool bFind = false;
		Lock();
		for(int i=0;i<nItems;++i)
		{
			bFind = false;	//���ҽ��.
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
	* �ж��ڻ��ֲּ�¼�Ƿ���ͬ��ֻ������������
	* @param pItems				��������
	* @param nItems				��������	
	* @return 					��ͬ�򷵻�true����ͬ�򷵻�false.
	*/
	bool IsSameHoldPosition_Fut(Item* pItems,int nItems)
	{
		bool bSame = true;
		bool bFind = false;
		Lock();
		for(int i=0;i<nItems;++i)
		{
			bFind = false;	//���ҽ��.
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
	* �����и��£���ӣ���Ա����ά��ͬһ���nIdentity���䣬
	* ��ΪItem.nIdentity �Զ������±��.
	* ͨ���ãɣ��ɷ����ά�����ͻ���ʹ��.
	* @param pItems				��������
	* @param nItems				��������	
	* @param bDelete			�Ƿ�ɾ��pItems��û�е���.
	* @param bChanged			[out]���ص�ǰQueen��pItems�е������Ƿ���ͬ.�����ͬ�����true.
	*/
	void Update2QueenAndAssignID(Item* pItems,int nItems,bool bDelete,bool& bChanged)
	{
		bChanged = false;
		Lock();
		for(int i=0;i<nItems;++i)
		{
			bool bFind = false;	//���ҽ��.
			for(iterator it= begin();it!=end();++it)
			{
				if(IsTheSameItem(pItems[i],*it))
				{
					bFind = true;

					//�����ͬһ����¼.
					//����.
					pItems[i].nIdentity = (INT64)((*it).nIdentity);

					if( !( pItems[i] == (*it)) )
					{	
						bChanged = true;						
						*it = *(pItems+i);		//��������.												
					}
				}
			}

			if(!bFind)
			{
				push_back(pItems[i]);
				iterator it = end();
				--it;
				(*it).nIdentity = (INT64)(&(*it));	//�Զ�����ɣ�.
				bChanged = true;
			}
		}

		if(bDelete)
		{
			//ɾ��������û�е���.
			for(iterator it = begin();it!=end();)
			{
				bool bFind = false;
				for(int i =0 ;i<nItems;++i)
				{
					if(IsTheSameItem(pItems[i],*it))
					{
						//�ҵ���ͬ����.
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
	* ������ȡ�����飬����new���䣬��Ҫ��delete []ɾ��
	* @param pItems [out] �������
	* @param nItems [out] ������ݸ���.
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