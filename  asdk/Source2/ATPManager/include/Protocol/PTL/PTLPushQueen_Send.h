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
#ifndef _PTLPUSHQUEEN_SEND_H_
#define _PTLPUSHQUEEN_SEND_H_
#include "TDPushProtocol.h"

#include "atlcore.h"
#include <list>
#include <algorithm>
using namespace std;

#include "PTLPushQueen.h"
#include "PTLPushQueen_Server.h"

template <class Item>
class CPTLPushQueen_Send
	:protected list<Item>,
	protected CComAutoCriticalSection
{
public:
	CPTLPushQueen_Send()
	{
	}

	virtual ~CPTLPushQueen_Send()
	{
	}

public:
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

	/**
	* 清除原有的，
	* 更新现成的.
	*/
	void SetFullData(const Item* pItems,int nItems)
	{
		Lock();
		clear();
        if(nItems>0)
			copy<const Item*,iterator>(pItems,pItems+nItems,begin());
		Unlock();
	}
	
	/**
	* 增加或更新新项.
	*/
	void AddOrUpdate(const Item* pItems,int nItems)
	{
        Lock();
		for(int i=0;i<nItems;++i)
		{
			bool bFind = false;
			for(iterator it = begin();it!=end();++it)
			{
				if((*it).nIdentity == pItems[i].nIdentity)
				{
					(*it) = pItems[i];
					break;
				}
			}
			if(!bFind)
			{
				push_back(pItems[i]);	//插入.
			}
		}
		Unlock();
	}


	/**
	* 将数据取成数组，采用new分配，需要用delete []删除
	* @param pItems [out] 输出数组
	* @param nItems [out] 输出数据个数.
	*/
	void GetFullCmpressData(char*& pData,
							int& nLength,
							int& nItems)
	{
		Lock();
		nItems = size();

		if(nItems>0)
		{
			int nAllocLen  = sizeof(Item)*nItems*1.5+1024;
			pData = new char[nAllocLen];
			char* pCmpPos = pData;
			nLength =0 ;

		
			int* pCmpItems = (int*)pCmpPos;
			(*pCmpItems) = nItems;

			pCmpPos	+= sizeof(int);			
			nLength += sizeof(int);

			for(iterator it = begin();it!=end();++it)
			{
				PARTCOMPRESS_HEAD* pHead = (PARTCOMPRESS_HEAD*)pCmpPos;
				pHead->nMethod = ATP_PUSH_ITEM_ADD;
				pHead->nId     = (*it).nIdentity;

				pCmpPos += sizeof(PARTCOMPRESS_HEAD);
				nLength += sizeof(PARTCOMPRESS_HEAD);


				ASSERT(nAllocLen>nLength);
				int ncmplen = ptl_compress(&(*it),pCmpPos,nAllocLen-nLength);
				pCmpPos += ncmplen;
				nLength += ncmplen;
			}


		}else
		{
			nLength =0;
			pData = NULL;
		}
		Unlock();		
	}


	static void GetFullCmpressData(const Item* pItems,int nItems,char*& pData,int& nLength)
	{
		if(nItems>0)
		{
			int nAllocLen  = sizeof(Item)*nItems*1.5+1024;
			pData = new char[nAllocLen];
			char* pCmpPos = pData;
			nLength =0 ;

			int* pnItems = (int*)pCmpPos;
			*pnItems = nItems;
			nLength += sizeof(int);

			for(int i=0;i<nItems;++i)
			{
				ASSERT(nAllocLen>nLength);
				int ncmplen = ptl_compress(pItems+i,pCmpPos,nAllocLen-nLength);
				pCmpPos += ncmplen;
				nLength += ncmplen;
			}
		}else
		{
			nLength =0;
			pData = NULL;
		}
	}


	void DeleteAndUpdateQueen(INT64 nIdentity,
		char*&  pComData,
		int&  nLength)
	{
		nLength = sizeof(int) + sizeof(PARTCOMPRESS_HEAD);
		pComData = new char[nLength];
		
		*((int*)pComData) = 1;

		PARTCOMPRESS_HEAD* pHead = (PARTCOMPRESS_HEAD*)(pComData+sizeof(int));
		pHead->nMethod = ATP_PUSH_ITEM_DELETE;
		pHead->nId     = nIdentity;

		Lock();

		//分配足够的内存
		for(iterator it = begin();it!=end();++it)
		{
			if(( *it).nIdentity == nIdentity)
			{
				erase(it);
				break;
			}
		}

		Unlock();
	}


	/**
	* 队列数据比较.得出应推送的数据.
	* 比较完成后，并更新成新数据.函数可能修改其ID.
	* @param newQueen	另一队列(完整队列),this为旧队列.
	* @param nMethod	[out]得出全量，还是非全量方法
	* @param pComData	[out]得出数据,需要调用delete []删除.
	* @param nLength	[out]返回数据长度.
	* @param bDelete    是否删除新组中没有的元素项.
	*/
	bool CompareAndUpdateQueen(/*const */Item* pItems,int nNewItems,
		ATP_MSG_PUSH_PACKET_METHOD& nMethod,
		char*&  pComData,
		int&  nLength,
		int&  nCmpItems,
		bool bDelete = true
		)
	{
		//分配足够的内存
		int nAllocSize = 1.5 * (sizeof(Item)+sizeof(PARTCOMPRESS_HEAD))* max( nNewItems,size()) + 1024;

		char* pPartCmp = new char[nAllocSize];		//变量存储.
		if (!pPartCmp)
		{
			return false;
		}
		ZeroMemory(pPartCmp,nAllocSize);

		//为节省ＣＰＵ，不进行全量压缩，然后比较，直接采用增量方式.

		int nPartCmpLen = 0;	//变化压缩总长度.
		

		char* pCmpPos = pPartCmp;	

		int* pCmpItems = (int*)pCmpPos;
		
		pCmpPos	+= sizeof(int);
		nPartCmpLen += sizeof(int);


		nCmpItems = 0;			   //压入的记录数.



		Lock();
		//newQueen.Unlock();

		for(int i=0;i<nNewItems;++i)
		{
			bool bFind=false;
			for(iterator itOld = begin();itOld!=end();++itOld)
			{
				//如果是同一条记录
				if(IsTheSameItem(*itOld,pItems[i]))
				{
					//如果相同，必须要校正其原始ID.
					//Modify by wli 2010-5-10
					pItems[i].nIdentity = (*itOld).nIdentity;


					//如果相同，则不处理,如果不同.则指示该条记录需要更新.
					if( !((*itOld) == pItems[i])	)
					{
						//指示该条记录需要更新.
						//lsCmpItems.push_back(CPushItem<Item>(ATP_PUSH_ITEM_UPDATE,*it));
						//压入变化数据.
						//比较压缩
						PARTCOMPRESS_HEAD* pHead = (PARTCOMPRESS_HEAD*)pCmpPos;
						pHead->nMethod = ATP_PUSH_ITEM_UPDATE;
						pHead->nId     = pItems[i].nIdentity;

						pCmpPos += sizeof(PARTCOMPRESS_HEAD);
						nPartCmpLen += sizeof(PARTCOMPRESS_HEAD);


						int nLen = ptl_comparecmpress(&pItems[i],&(*itOld),pCmpPos,nAllocSize-nPartCmpLen);
						nPartCmpLen += nLen;
						pCmpPos += nLen;
						++nCmpItems;

						//更新记录.
						(*itOld) = pItems[i];

					}
					bFind = true;
					break;	//假定唯一.
				}
			}

			if(!bFind)
			{
				//如果没有找到，则为增加.

				PARTCOMPRESS_HEAD* pHead = (PARTCOMPRESS_HEAD*)pCmpPos;
				pHead->nMethod = ATP_PUSH_ITEM_ADD;
				pHead->nId     = pItems[i].nIdentity;

				pCmpPos += sizeof(PARTCOMPRESS_HEAD);
				nPartCmpLen += sizeof(PARTCOMPRESS_HEAD);


				//lsCmpItems.push_back(CPushItem<Item>(ATP_PUSH_ITEM_ADD,*it));
				int nLen = ptl_compress(&pItems[i],pCmpPos,nAllocSize-nPartCmpLen);
				nPartCmpLen += nLen;
				pCmpPos += nLen;
				++nCmpItems;

				//增加
				push_back(pItems[i]);
			}
		}

		if(bDelete)
		{
			//还要比较是否有删除的.
			for(iterator itOld = begin();itOld!=end();)
			{
				bool bFind = false;

				for(int i=0;i<nNewItems;++i)
				{
					if(IsTheSameItem(*itOld,pItems[i]))
					{
						bFind = true;
						break;
					}
				}

				if(!bFind)
				{
					//如果没有找到。

					PARTCOMPRESS_HEAD* pHead = (PARTCOMPRESS_HEAD*)pCmpPos;
					pHead->nMethod = ATP_PUSH_ITEM_DELETE;
					pHead->nId     = (*itOld).nIdentity;

					pCmpPos += sizeof(PARTCOMPRESS_HEAD);
					nPartCmpLen += sizeof(PARTCOMPRESS_HEAD);


					//lsCmpItems.push_back(CPushItem<Item>(ATP_PUSH_ITEM_DELETE,*itOld));
					/*int nLen = ptl_comparecmpress(NULL,&(*itOld),pCmpPos,nAllocSize-nPartCmpLen);
					nPartCmpLen += nLen;
					pCmpPos += nLen;*/
					//不用再压缩数据了
					++nCmpItems;

					itOld = erase(itOld);		//删除后，需要删除当前记录。
				}else
				{
					//找到
					++itOld;
				}

			}    
		}
		
		*pCmpItems = nCmpItems;

		nMethod = ATP_PUSH_PACKET_PART_MODIFY;
		nLength = nPartCmpLen;
		

		pComData = pPartCmp;

		Unlock();
		return true;
	}







	///**
	//* 队列数据比较.得出应推送的数据.
	//* 比较完成后，并更新成新数据.
	//* @param newQueen	另一队列(完整队列),this为旧队列.
	//* @param nMethod	[out]得出全量，还是非全量方法
	//* @param pComData	[out]得出数据,需要调用delete []删除.
	//* @param nLength	[out]返回数据长度.
	//*/
	//bool CompareAndUpdateQueen(CPTLPushQueen_Send<Item>& newQueen,
	//	ATP_MSG_PUSH_PACKET_METHOD& nMethod,
	//	char*&  pComData,
	//	int&  nLength,
	//	int&  nItems
	//	)
	//{
	//	//分配足够的内存
	//	int nAllocSize = 1.5 * (sizeof(Item)+sizeof(PARTCOMPRESS_HEAD))* max( newQueen.size(),size()) + 1024;

	//	char* pPartCmp = new char[nAllocSize];		//变量存储.

	//	//为节省ＣＰＵ，不进行全量压缩，然后比较，直接采用增量方式.
	//	
	//	int nPartCmpLen = 0;	//变化压缩总长度.
	//	char* pCmpPos = pPartCmp;	

	//	int* pCmpItems = (int*)pCmpPos;
	//	nItems = 0;			   //压入的记录数.

	//	Lock();
	//	newQueen.Unlock();
	//	
	//	for(iterator it = newQueen.begin();it!=newQueen.end();++it)
	//	{
	//		bool bFind=false;
	//		for(iterator itOld = begin();itOld!=end();++itOld)
	//		{
	//			//如果是同一条记录
	//			if(IsTheSameItem(*itOld,*it))
	//			{
	//				//如果相同，则不处理,如果不同.则指示该条记录需要更新.
	//				if(*itOld != *it)						
	//				{
	//					//指示该条记录需要更新.
	//					//lsCmpItems.push_back(CPushItem<Item>(ATP_PUSH_ITEM_UPDATE,*it));
	//					//压入变化数据.
	//					//比较压缩
	//					PARTCOMPRESS_HEAD* pHead = pCmpPos;
	//					pHead->nMethod = ATP_PUSH_ITEM_UPDATE;
	//					pHead->nId     = (*it).nIdentity;
	//					
	//					pCmpPos += sizeof(PARTCOMPRESS_HEAD);
	//					nPartCmpLen += sizeof(PARTCOMPRESS_HEAD);


	//					int nLen = ptl_comparecmpress(&(*it),&(*itOld),pCmpPos,nAllocSize-nPartCmpLen);
	//					nPartCmpLen += nLen;
	//					pCmpPos += nLen;
	//					++nItems;

	//				}
	//				bFind = true;
	//				break;	//假定唯一.
	//			}
	//		}

	//		if(!bFind)
	//		{
	//			//如果没有找到，则为增加.

	//			PARTCOMPRESS_HEAD* pHead = pCmpPos;
	//			pHead->nMethod = ATP_PUSH_ITEM_ADD;
	//			pHead->nId     = (*it).nIdentity;

	//			pCmpPos += sizeof(PARTCOMPRESS_HEAD);
	//			nPartCmpLen += sizeof(PARTCOMPRESS_HEAD);


	//			//lsCmpItems.push_back(CPushItem<Item>(ATP_PUSH_ITEM_ADD,*it));
	//			int nLen = ptl_cmpress(&(*it),pCmpPos,nAllocSize-nPartCmpLen);
	//			nPartCmpLen += nLen;
	//			pCmpPos += nLen;
	//			++nItems;
	//		}
	//	}

	//	//还要比较是否有删除的.
	//	for(iterator itOld = begin();itOld!=end();++itOld)
	//	{
	//		bool bFind = false;
	//		for(iterator it = newQueen.begin();it!=newQueen.end();++it)
	//		{
	//			if(IsTheSameItem(*itOld,*it))
	//			{
	//				bFind = true;
	//				break;
	//			}
	//		}
	//		if(!bFind)
	//		{
	//			//如果没有找到。

	//			PARTCOMPRESS_HEAD* pHead = pCmpPos;
	//			pHead->nMethod = ATP_PUSH_ITEM_DELETE;
	//			pHead->nId     = (*itOld).nIdentity;

	//			pCmpPos += sizeof(PARTCOMPRESS_HEAD);
	//			nPartCmpLen += sizeof(PARTCOMPRESS_HEAD);


	//			//lsCmpItems.push_back(CPushItem<Item>(ATP_PUSH_ITEM_DELETE,*itOld));
	//			/*int nLen = ptl_comparecmpress(NULL,&(*itOld),pCmpPos,nAllocSize-nPartCmpLen);
	//			nPartCmpLen += nLen;
	//			pCmpPos += nLen;*/
	//			//不用再压缩数据了
	//			++nItems;
	//		}
	//	}            


	//	nMethod = ATP_PUSH_PACKET_PART_MODIFY;
	//	nLength = nPartCmpLen;

	//	//拷贝数据.
	//	clear();
	//	copy<iterator,iterator>(newQueen.begin(),newQueen.end(),begin());
	//	newQueen.Unlock();
	//	Unlock();
	//}

};

//通用
typedef CPTLPushQueen_Send<ATP_Msg_CurrentAlgoStatus> CSendAlgoStatusQueen;


//证券
typedef CPTLPushQueen_Send<ATP_Msg_Sec_HoldPosition> CSecSendHoldPositionQueen;
typedef CPTLPushQueen_Send<ATP_Msg_Sec_QueryOrderRecords_Answer> CSecSendOrderRecordsQueen;
typedef CPTLPushQueen_Send<ATP_Msg_Sec_QueryMatch_Answer> CSecSendMatchQueen;
typedef CPTLPushQueen_Send<ATP_Msg_Sec_QueryAssets_Answer> CSecSendAssetsQueen;

//期货
typedef CPTLPushQueen_Send<ATP_Msg_Fut_HoldPosition> CFutSendHoldPositionQueen;
typedef CPTLPushQueen_Send<ATP_Msg_Fut_QueryOrderRecords_Answer> CFutSendOrderRecordsQueen;
typedef CPTLPushQueen_Send<ATP_Msg_Fut_QueryMatch_Answer> CFutSendMatchQueen;
typedef CPTLPushQueen_Send<ATP_Msg_Fut_QueryAssets_Answer> CFutSendAssetsQueen;
//typedef CPTLPushQueen_Send<ATP_Msg_CurrentAlgoStatus> CSendAlgoStatusQueen;


#endif //_PTLPUSHQUEEN_SEND_H_