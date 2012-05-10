/**
* @Copyright �����д���Ƽ����޹�˾(www.hh.com.cn)
* @System	 ͨ��ͨ�ſ�(Common Communication Environment Core)
* @Brief	 �����
* @Author	 wli
* @Date      2010-10-21
*/

/**
*	���������.
*	CPacketHead ���ݰ�ͷ��.
*	CPacketHead ����Ҫָ����������.
*	1.��ͷ��Ҫ����С���ݳ��ȣ�
*	2.��Ҫ�ɴ���Сͷ���ȵ������ṩ�������ĳ�����Ϣ.) 
*		size_t GetPacketLength(CPacketHead* pHead)
*	3.��ϢͷУ�麯�� 
*		bool IsValid(CPacketHead* pHead)
*/ 

#pragma once

#ifndef _CCEPACKET_H_
#define _CCEPACKET_H_

#pragma warning(disable: 4267)
#pragma warning(disable: 4244)
#pragma warning(disable: 4018)

template<class CPacketHead,
		int nMinHeadLength=sizeof(CPacketHead)>
class CCCEPacket
{
protected:


	/**
	*	���������д�ĺ���.
	*/
	virtual void OnReceivePacket(const void *pPacket,int nLength)=0;


public:

	CCCEPacket()
		:m_nRecvOffset(0)
	{
		//��Ĭ�Ϸ�������128���ֽ�.
		m_nAllocRealDataItem = max(nMinHeadLength,128);		
		m_pRealData = new BYTE[m_nAllocRealDataItem];	
	}

	~CCCEPacket()
	{
		if(m_pRealData)
		{
			delete []m_pRealData;
			m_pRealData = NULL;
		}
	}

	/**
	* ������Ա����½���.
	*/ 	
	void ClearRecvBuffer()
	{	
		m_nRecvOffset = 0;
		//ASSERT(AfxCheckMemory());
	}

	/**
	*	�������Ͻ��յ����ݵĻص�����
	*	@param pData		������ʼ��ַ
	*	@param nLength		���ݳ���
	*/
	virtual void OnRecvBinarayData(const void* pData,int nLength)
	{
		//Modify wli on 2010-10-25
		//�ɵݹ�,��Ϊѭ��,�����Ч��.

		if(nLength<0)
		{
			ASSERT(false);
			throw "Error_OnReceiveData";
			//ASSERT(AfxCheckMemory());
			return;

		}

		int nDealLength = 0;	//�Ѿ���������ݳ���.
		
		do
		{
			pData  =  ((BYTE*)pData +  nDealLength );
			nLength -= nDealLength;	

			nDealLength = 0;		//���ôδ���ĳ�������.

			if(nLength ==0 )
			{
				//ASSERT(AfxCheckMemory());
				return;		//��ǰ�����Ѿ�ȫ��������.
			}

			//����Ҫ��ͷ�ĳ���.
			int nHeadNeed = nMinHeadLength - m_nRecvOffset;

			//�鿴ͷ�Ƿ��������.
			if( nHeadNeed > 0  )
			{
				//�Ƚ���ͷ��Ҫ�Ĳ���.
				if(nLength >= nHeadNeed )
				{
					ASSERT(m_nAllocRealDataItem >= nMinHeadLength );
					//���Կ���ͷ�Ĳ���,
					memcpy(m_pRealData + m_nRecvOffset,pData,nHeadNeed);
					m_nRecvOffset += nHeadNeed;
					//��ͷ���м���

					if(!IsValid((CPacketHead*)m_pRealData))
					{
						throw "Invalid Message";	//ͷ���鲻��.
						//ASSERT(AfxCheckMemory());
						return;						//�յ��Ƿ�����,���ٴ���������Ϣ.
					}

					//������ͷ,�ٴ��Ա����俽������.
					nDealLength += nHeadNeed;


					if( m_nRecvOffset == GetPacketLength((CPacketHead*)m_pRealData) )
					{
						//���ֻ��ͷ��Ϣ��
						//���ݰ�������������֪ͨ���ݰ�����.
						OnReceivePacket(m_pRealData,m_nRecvOffset);
						//���������ݺ󣬲�ɾ�����Ա��´θ��á�
						m_nRecvOffset = 0;	//�����¿�ʼ��
					}
					


					continue;					//��������.
				}else
				{
					//������������ͷ��Ϣ
					memcpy((char*)m_pRealData+m_nRecvOffset,pData,nLength);
					m_nRecvOffset += nLength;					
					return;								
				}
			}else
			{
				//ASSERT(m_nRecvOffset == nMinHeadLength);

				//ȡͷ�������ݰ��ĳ��ȣ�����ͷ��
				__int64 nPacketLength = GetPacketLength((CPacketHead*)m_pRealData);

				if(nPacketLength<0)
				{
					throw "Error packet";
					//ASSERT(AfxCheckMemory());
					return;
				}

				if( nPacketLength > m_nAllocRealDataItem)
				{

					BYTE* pNew  = new BYTE[nPacketLength];	//������ô��ռ䣬�Դ洢����.
					memset(pNew,0,nPacketLength);

					memcpy(pNew,m_pRealData,m_nRecvOffset);	//��ԭ�������ݿ�����ȥ��

					if(!m_pRealData)
					{
						delete []m_pRealData;
						m_pRealData= NULL;
					}
					m_pRealData = pNew;	
					m_nAllocRealDataItem = nPacketLength;	//�·����ڴ�Ĵ�С��
				}


				ASSERT(nPacketLength>=nMinHeadLength);

				int nNeed  =   nPacketLength - m_nRecvOffset;
				if(nLength<nNeed)
				{
					memcpy(m_pRealData+m_nRecvOffset,pData,nLength);	//ȫ������.
					m_nRecvOffset += nLength;
					//���ݲ��㣬��Ҫ����һ�ν���.
					//ASSERT(AfxCheckMemory());
					return;
				}else		
				{
					//���ݳ���
					//����Ҫ����ȫ������.
					memcpy(m_pRealData+m_nRecvOffset,pData,nNeed);	//ȫ������

					//���ݰ�������������֪ͨ���ݰ�����.
					OnReceivePacket(m_pRealData,nPacketLength);
					//���������ݺ󣬲�ɾ�����Ա��´θ��á�
					m_nRecvOffset = 0;	//�����¿�ʼ��
					nDealLength +=  nNeed;		//����Ѿ������.
					continue;
				}
			}
		}while(true);
		//ASSERT(AfxCheckMemory());
	}

	bool OnClose()
	{
		m_nRecvOffset = 0;
		return false;
	}

protected:
	CPacketHead*		m_pHead;
	BYTE*               m_pRealData;
	size_t					m_nAllocRealDataItem;
	size_t		m_nRecvOffset;				//���յ����ݵ�����.
};


#endif //_CCEPACKET_H_