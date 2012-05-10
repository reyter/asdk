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
#ifndef _PTLPUSHQUEEN_RECEIVE_H_
#define _PTLPUSHQUEEN_RECEIVE_H_

#pragma warning(disable:4267)

#include "TDPushProtocol.h"


#include "atlcore.h"
#include <list>
#include <algorithm>
using namespace std;


#include "PTLPushQueen.h"

template <class Item>
class CPTLPushQueen_Receive
	:protected map<INT64,Item*>,
	protected CComAutoCriticalSection
{
	typedef pair<INT64,Item*> Item_Pair;
public:
	CPTLPushQueen_Receive()
	{
	}

	virtual ~CPTLPushQueen_Receive()
	{
		Clear();
	}

	virtual void AfterUpdateQueen(){}
public:

	void Clear()
	{
		Lock();
		for(iterator it = begin();it!=end();++it)
		{
			delete it->second;
		}
		clear();
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
			if (!pItems)
			{
				Unlock();
				return;
			}
			ZeroMemory(pItems,nItems*sizeof(Item));

			int i=0;
			for( iterator it = begin();it!= end();++it,++i)
			{
				pItems[i] = *(it->second);
			}
		}else
		{
			pItems = NULL;
		}
		Unlock();		
	}


	/**
	* 接收到全量非压缩数据.	
	*/
	void OnReceiveFull(Item* pItems,int nItems)
	{
		Lock();
		//Delete all the items.
		for(iterator it= begin();it!=end();++it)
		{
			delete it->second;
		}
		clear();

		for(int i=0;i<nItems;++i)
		{
			Item* pNew = new Item(pItems[i]);	
			if (!pNew)
			{
				Unlock();
				return;
			}
			ZeroMemory(pNew,pItems[i]*sizeof(Item));
			insert(make_pair<INT64,Item*>(pNew.nIdentity,pNew));	//添加进Queen中.
		}

		Unlock();

		AfterUpdateQueen();
	}
	
	/**
	* 接收到全量压缩.
	* 接收到全量压缩时，需要解压.
	*/
	void OnReceiveFullCompress(char* pData,int nLength)
	{
		Lock();
		//Delete all the items.
		for(iterator it= begin();it!=end();++it)
		{
			delete it->second;
		}
		clear();

		//Add new Items.
		if(nLength>0)
		{
			//解出sizeof(int)的长度，
			char* pDecmpPos = pData;
			int   nDecmpLengh = 0;			//解压缩长度.

			int nItems = *((int*)pData);
			pDecmpPos += sizeof(int);
			nDecmpLengh += sizeof(int);


			for(int i=0;i<nItems;++i)
			{
				Item* pNew = new Item();	
				if (!pNew)
				{
					Unlock();
					return;
				}
				ZeroMemory(pNew,sizeof(Item));
				int nLen = ptl_decmpress(pDecmpPos,nLength - nDecmpLengh,pNew);				
				pDecmpPos += nLen;	//移至下一条记录.
				insert(make_pair<INT64,Item*>(pNew->nIdentity,pNew));	//添加进Queen中.
			}
		}
		Unlock();

		AfterUpdateQueen();
	}


	/**
	* 接收到变化压缩时.
	*/
	void OnReceivePartCompress(char* pData,int nLength)
	{
		Lock();

		ASSERT(nLength>0);
		if(nLength>0)
		{
			//解出sizeof(int)的长度，
			char* pDecmpPos = pData;
			int   nDecmpLengh = 0;			//解压缩长度.

			int nItems = *((int*)pData);
			pDecmpPos += sizeof(int);
			nDecmpLengh += sizeof(int);


			
			for(int i=0;i<nItems;++i)
			{
				
				//先解压出方法与id.
				//方法与ＩＤ不压缩.
				PARTCOMPRESS_HEAD* pHead = (PARTCOMPRESS_HEAD*)pDecmpPos;
				
				pDecmpPos += sizeof(*pHead);

				switch(pHead->nMethod)
				{
				case ATP_PUSH_ITEM_ADD:
					{
						//insert(Item_Pair(1,NULL));
						//增加一条记录.
						Item* pNew = new Item();
						if (!pNew)
						{
							Unlock();
							return;
						}
						ZeroMemory(pNew,sizeof(Item));
						int nLen = ptl_decmpress(pDecmpPos,nLength - nDecmpLengh,pNew);				
						pDecmpPos += nLen; //移至下一条记录.
						insert(Item_Pair(pNew->nIdentity,pNew));	//添加进Queen中.

					}break;
				case ATP_PUSH_ITEM_DELETE:
					{
						//删除该条记录
						iterator it = find(pHead->nId);
						if(it!=end())
						{
							delete it->second;
							erase(it);
						}else
						{
							//如果没有，叫删除，肯定出错了.
							//ASSERT(false);
							Unlock();
							throw "Error";
						}
					}break;
				case ATP_PUSH_ITEM_UPDATE:
					{
						//修改部分字段.
						iterator it = find(pHead->nId);
						if(it!=end())
						{
							int nLen = ptl_comparedecmpress(pDecmpPos,nLength - nDecmpLengh,it->second);
							pDecmpPos += nLen;  //移至下一条记录.							
						}else
						{
							//如果没有，叫修改，肯定出错了.
							//ASSERT(false);
							Unlock();
							throw "Error";
						}
					}break;
				}
			}
		}
		Unlock();

		AfterUpdateQueen();
	}
};


/**
* 算法状态信息队列
*/
typedef CPTLPushQueen_Receive<ATP_Msg_CurrentAlgoStatus> CPushAlgoStatusQueen;


#endif //_PTLPUSHQUEEN_RECEIVE_H_
