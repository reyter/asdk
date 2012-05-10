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

	/**
	* ���ԭ�еģ�
	* �����ֳɵ�.
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
	* ���ӻ��������.
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
				push_back(pItems[i]);	//����.
			}
		}
		Unlock();
	}


	/**
	* ������ȡ�����飬����new���䣬��Ҫ��delete []ɾ��
	* @param pItems [out] �������
	* @param nItems [out] ������ݸ���.
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

		//�����㹻���ڴ�
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
	* �������ݱȽ�.�ó�Ӧ���͵�����.
	* �Ƚ���ɺ󣬲����³�������.���������޸���ID.
	* @param newQueen	��һ����(��������),thisΪ�ɶ���.
	* @param nMethod	[out]�ó�ȫ�������Ƿ�ȫ������
	* @param pComData	[out]�ó�����,��Ҫ����delete []ɾ��.
	* @param nLength	[out]�������ݳ���.
	* @param bDelete    �Ƿ�ɾ��������û�е�Ԫ����.
	*/
	bool CompareAndUpdateQueen(/*const */Item* pItems,int nNewItems,
		ATP_MSG_PUSH_PACKET_METHOD& nMethod,
		char*&  pComData,
		int&  nLength,
		int&  nCmpItems,
		bool bDelete = true
		)
	{
		//�����㹻���ڴ�
		int nAllocSize = 1.5 * (sizeof(Item)+sizeof(PARTCOMPRESS_HEAD))* max( nNewItems,size()) + 1024;

		char* pPartCmp = new char[nAllocSize];		//�����洢.
		if (!pPartCmp)
		{
			return false;
		}
		ZeroMemory(pPartCmp,nAllocSize);

		//Ϊ��ʡ�ãУգ�������ȫ��ѹ����Ȼ��Ƚϣ�ֱ�Ӳ���������ʽ.

		int nPartCmpLen = 0;	//�仯ѹ���ܳ���.
		

		char* pCmpPos = pPartCmp;	

		int* pCmpItems = (int*)pCmpPos;
		
		pCmpPos	+= sizeof(int);
		nPartCmpLen += sizeof(int);


		nCmpItems = 0;			   //ѹ��ļ�¼��.



		Lock();
		//newQueen.Unlock();

		for(int i=0;i<nNewItems;++i)
		{
			bool bFind=false;
			for(iterator itOld = begin();itOld!=end();++itOld)
			{
				//�����ͬһ����¼
				if(IsTheSameItem(*itOld,pItems[i]))
				{
					//�����ͬ������ҪУ����ԭʼID.
					//Modify by wli 2010-5-10
					pItems[i].nIdentity = (*itOld).nIdentity;


					//�����ͬ���򲻴���,�����ͬ.��ָʾ������¼��Ҫ����.
					if( !((*itOld) == pItems[i])	)
					{
						//ָʾ������¼��Ҫ����.
						//lsCmpItems.push_back(CPushItem<Item>(ATP_PUSH_ITEM_UPDATE,*it));
						//ѹ��仯����.
						//�Ƚ�ѹ��
						PARTCOMPRESS_HEAD* pHead = (PARTCOMPRESS_HEAD*)pCmpPos;
						pHead->nMethod = ATP_PUSH_ITEM_UPDATE;
						pHead->nId     = pItems[i].nIdentity;

						pCmpPos += sizeof(PARTCOMPRESS_HEAD);
						nPartCmpLen += sizeof(PARTCOMPRESS_HEAD);


						int nLen = ptl_comparecmpress(&pItems[i],&(*itOld),pCmpPos,nAllocSize-nPartCmpLen);
						nPartCmpLen += nLen;
						pCmpPos += nLen;
						++nCmpItems;

						//���¼�¼.
						(*itOld) = pItems[i];

					}
					bFind = true;
					break;	//�ٶ�Ψһ.
				}
			}

			if(!bFind)
			{
				//���û���ҵ�����Ϊ����.

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

				//����
				push_back(pItems[i]);
			}
		}

		if(bDelete)
		{
			//��Ҫ�Ƚ��Ƿ���ɾ����.
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
					//���û���ҵ���

					PARTCOMPRESS_HEAD* pHead = (PARTCOMPRESS_HEAD*)pCmpPos;
					pHead->nMethod = ATP_PUSH_ITEM_DELETE;
					pHead->nId     = (*itOld).nIdentity;

					pCmpPos += sizeof(PARTCOMPRESS_HEAD);
					nPartCmpLen += sizeof(PARTCOMPRESS_HEAD);


					//lsCmpItems.push_back(CPushItem<Item>(ATP_PUSH_ITEM_DELETE,*itOld));
					/*int nLen = ptl_comparecmpress(NULL,&(*itOld),pCmpPos,nAllocSize-nPartCmpLen);
					nPartCmpLen += nLen;
					pCmpPos += nLen;*/
					//������ѹ��������
					++nCmpItems;

					itOld = erase(itOld);		//ɾ������Ҫɾ����ǰ��¼��
				}else
				{
					//�ҵ�
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
	//* �������ݱȽ�.�ó�Ӧ���͵�����.
	//* �Ƚ���ɺ󣬲����³�������.
	//* @param newQueen	��һ����(��������),thisΪ�ɶ���.
	//* @param nMethod	[out]�ó�ȫ�������Ƿ�ȫ������
	//* @param pComData	[out]�ó�����,��Ҫ����delete []ɾ��.
	//* @param nLength	[out]�������ݳ���.
	//*/
	//bool CompareAndUpdateQueen(CPTLPushQueen_Send<Item>& newQueen,
	//	ATP_MSG_PUSH_PACKET_METHOD& nMethod,
	//	char*&  pComData,
	//	int&  nLength,
	//	int&  nItems
	//	)
	//{
	//	//�����㹻���ڴ�
	//	int nAllocSize = 1.5 * (sizeof(Item)+sizeof(PARTCOMPRESS_HEAD))* max( newQueen.size(),size()) + 1024;

	//	char* pPartCmp = new char[nAllocSize];		//�����洢.

	//	//Ϊ��ʡ�ãУգ�������ȫ��ѹ����Ȼ��Ƚϣ�ֱ�Ӳ���������ʽ.
	//	
	//	int nPartCmpLen = 0;	//�仯ѹ���ܳ���.
	//	char* pCmpPos = pPartCmp;	

	//	int* pCmpItems = (int*)pCmpPos;
	//	nItems = 0;			   //ѹ��ļ�¼��.

	//	Lock();
	//	newQueen.Unlock();
	//	
	//	for(iterator it = newQueen.begin();it!=newQueen.end();++it)
	//	{
	//		bool bFind=false;
	//		for(iterator itOld = begin();itOld!=end();++itOld)
	//		{
	//			//�����ͬһ����¼
	//			if(IsTheSameItem(*itOld,*it))
	//			{
	//				//�����ͬ���򲻴���,�����ͬ.��ָʾ������¼��Ҫ����.
	//				if(*itOld != *it)						
	//				{
	//					//ָʾ������¼��Ҫ����.
	//					//lsCmpItems.push_back(CPushItem<Item>(ATP_PUSH_ITEM_UPDATE,*it));
	//					//ѹ��仯����.
	//					//�Ƚ�ѹ��
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
	//				break;	//�ٶ�Ψһ.
	//			}
	//		}

	//		if(!bFind)
	//		{
	//			//���û���ҵ�����Ϊ����.

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

	//	//��Ҫ�Ƚ��Ƿ���ɾ����.
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
	//			//���û���ҵ���

	//			PARTCOMPRESS_HEAD* pHead = pCmpPos;
	//			pHead->nMethod = ATP_PUSH_ITEM_DELETE;
	//			pHead->nId     = (*itOld).nIdentity;

	//			pCmpPos += sizeof(PARTCOMPRESS_HEAD);
	//			nPartCmpLen += sizeof(PARTCOMPRESS_HEAD);


	//			//lsCmpItems.push_back(CPushItem<Item>(ATP_PUSH_ITEM_DELETE,*itOld));
	//			/*int nLen = ptl_comparecmpress(NULL,&(*itOld),pCmpPos,nAllocSize-nPartCmpLen);
	//			nPartCmpLen += nLen;
	//			pCmpPos += nLen;*/
	//			//������ѹ��������
	//			++nItems;
	//		}
	//	}            


	//	nMethod = ATP_PUSH_PACKET_PART_MODIFY;
	//	nLength = nPartCmpLen;

	//	//��������.
	//	clear();
	//	copy<iterator,iterator>(newQueen.begin(),newQueen.end(),begin());
	//	newQueen.Unlock();
	//	Unlock();
	//}

};

//ͨ��
typedef CPTLPushQueen_Send<ATP_Msg_CurrentAlgoStatus> CSendAlgoStatusQueen;


//֤ȯ
typedef CPTLPushQueen_Send<ATP_Msg_Sec_HoldPosition> CSecSendHoldPositionQueen;
typedef CPTLPushQueen_Send<ATP_Msg_Sec_QueryOrderRecords_Answer> CSecSendOrderRecordsQueen;
typedef CPTLPushQueen_Send<ATP_Msg_Sec_QueryMatch_Answer> CSecSendMatchQueen;
typedef CPTLPushQueen_Send<ATP_Msg_Sec_QueryAssets_Answer> CSecSendAssetsQueen;

//�ڻ�
typedef CPTLPushQueen_Send<ATP_Msg_Fut_HoldPosition> CFutSendHoldPositionQueen;
typedef CPTLPushQueen_Send<ATP_Msg_Fut_QueryOrderRecords_Answer> CFutSendOrderRecordsQueen;
typedef CPTLPushQueen_Send<ATP_Msg_Fut_QueryMatch_Answer> CFutSendMatchQueen;
typedef CPTLPushQueen_Send<ATP_Msg_Fut_QueryAssets_Answer> CFutSendAssetsQueen;
//typedef CPTLPushQueen_Send<ATP_Msg_CurrentAlgoStatus> CSendAlgoStatusQueen;


#endif //_PTLPUSHQUEEN_SEND_H_