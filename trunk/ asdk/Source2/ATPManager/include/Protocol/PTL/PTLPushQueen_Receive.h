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
	* ���յ�ȫ����ѹ������.	
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
			insert(make_pair<INT64,Item*>(pNew.nIdentity,pNew));	//��ӽ�Queen��.
		}

		Unlock();

		AfterUpdateQueen();
	}
	
	/**
	* ���յ�ȫ��ѹ��.
	* ���յ�ȫ��ѹ��ʱ����Ҫ��ѹ.
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
			//���sizeof(int)�ĳ��ȣ�
			char* pDecmpPos = pData;
			int   nDecmpLengh = 0;			//��ѹ������.

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
				pDecmpPos += nLen;	//������һ����¼.
				insert(make_pair<INT64,Item*>(pNew->nIdentity,pNew));	//��ӽ�Queen��.
			}
		}
		Unlock();

		AfterUpdateQueen();
	}


	/**
	* ���յ��仯ѹ��ʱ.
	*/
	void OnReceivePartCompress(char* pData,int nLength)
	{
		Lock();

		ASSERT(nLength>0);
		if(nLength>0)
		{
			//���sizeof(int)�ĳ��ȣ�
			char* pDecmpPos = pData;
			int   nDecmpLengh = 0;			//��ѹ������.

			int nItems = *((int*)pData);
			pDecmpPos += sizeof(int);
			nDecmpLengh += sizeof(int);


			
			for(int i=0;i<nItems;++i)
			{
				
				//�Ƚ�ѹ��������id.
				//������ɣĲ�ѹ��.
				PARTCOMPRESS_HEAD* pHead = (PARTCOMPRESS_HEAD*)pDecmpPos;
				
				pDecmpPos += sizeof(*pHead);

				switch(pHead->nMethod)
				{
				case ATP_PUSH_ITEM_ADD:
					{
						//insert(Item_Pair(1,NULL));
						//����һ����¼.
						Item* pNew = new Item();
						if (!pNew)
						{
							Unlock();
							return;
						}
						ZeroMemory(pNew,sizeof(Item));
						int nLen = ptl_decmpress(pDecmpPos,nLength - nDecmpLengh,pNew);				
						pDecmpPos += nLen; //������һ����¼.
						insert(Item_Pair(pNew->nIdentity,pNew));	//��ӽ�Queen��.

					}break;
				case ATP_PUSH_ITEM_DELETE:
					{
						//ɾ��������¼
						iterator it = find(pHead->nId);
						if(it!=end())
						{
							delete it->second;
							erase(it);
						}else
						{
							//���û�У���ɾ�����϶�������.
							//ASSERT(false);
							Unlock();
							throw "Error";
						}
					}break;
				case ATP_PUSH_ITEM_UPDATE:
					{
						//�޸Ĳ����ֶ�.
						iterator it = find(pHead->nId);
						if(it!=end())
						{
							int nLen = ptl_comparedecmpress(pDecmpPos,nLength - nDecmpLengh,it->second);
							pDecmpPos += nLen;  //������һ����¼.							
						}else
						{
							//���û�У����޸ģ��϶�������.
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
* �㷨״̬��Ϣ����
*/
typedef CPTLPushQueen_Receive<ATP_Msg_CurrentAlgoStatus> CPushAlgoStatusQueen;


#endif //_PTLPUSHQUEEN_RECEIVE_H_
