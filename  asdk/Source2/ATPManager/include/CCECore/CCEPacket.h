/**
* @Copyright 深圳市创真科技有限公司(www.hh.com.cn)
* @System	 通用通信库(Common Communication Environment Core)
* @Brief	 组包类
* @Author	 wli
* @Date      2010-10-21
*/

/**
*	数据组包类.
*	CPacketHead 数据包头类.
*	CPacketHead 类需要指出下列内容.
*	1.该头需要的最小数据长度，
*	2.需要由此最小头长度的数据提供整个包的长度信息.) 
*		size_t GetPacketLength(CPacketHead* pHead)
*	3.消息头校验函数 
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
	*	子类必须重写的函数.
	*/
	virtual void OnReceivePacket(const void *pPacket,int nLength)=0;


public:

	CCCEPacket()
		:m_nRecvOffset(0)
	{
		//先默认分配至少128个字节.
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
	* 清除，以便重新接收.
	*/ 	
	void ClearRecvBuffer()
	{	
		m_nRecvOffset = 0;
		//ASSERT(AfxCheckMemory());
	}

	/**
	*	从网络上接收到数据的回调函数
	*	@param pData		数据起始地址
	*	@param nLength		数据长度
	*/
	virtual void OnRecvBinarayData(const void* pData,int nLength)
	{
		//Modify wli on 2010-10-25
		//由递归,改为循环,以提高效率.

		if(nLength<0)
		{
			ASSERT(false);
			throw "Error_OnReceiveData";
			//ASSERT(AfxCheckMemory());
			return;

		}

		int nDealLength = 0;	//已经处理的数据长度.
		
		do
		{
			pData  =  ((BYTE*)pData +  nDealLength );
			nLength -= nDealLength;	

			nDealLength = 0;		//将该次处理的长度清零.

			if(nLength ==0 )
			{
				//ASSERT(AfxCheckMemory());
				return;		//当前数据已经全部处理完.
			}

			//还需要的头的长度.
			int nHeadNeed = nMinHeadLength - m_nRecvOffset;

			//查看头是否接收完整.
			if( nHeadNeed > 0  )
			{
				//先接收头需要的部份.
				if(nLength >= nHeadNeed )
				{
					ASSERT(m_nAllocRealDataItem >= nMinHeadLength );
					//可以拷入头的部分,
					memcpy(m_pRealData + m_nRecvOffset,pData,nHeadNeed);
					m_nRecvOffset += nHeadNeed;
					//对头进行检验

					if(!IsValid((CPacketHead*)m_pRealData))
					{
						throw "Invalid Message";	//头检验不过.
						//ASSERT(AfxCheckMemory());
						return;						//收到非法数据,不再处理后面的消息.
					}

					//处理完头,再次以便让其拷入数据.
					nDealLength += nHeadNeed;


					if( m_nRecvOffset == GetPacketLength((CPacketHead*)m_pRealData) )
					{
						//如果只有头信息。
						//数据包，接收完整，通知数据包到达.
						OnReceivePacket(m_pRealData,m_nRecvOffset);
						//接收完数据后，不删除，以便下次复用。
						m_nRecvOffset = 0;	//再重新开始。
					}
					


					continue;					//继续处理.
				}else
				{
					//如果不足以完成头信息
					memcpy((char*)m_pRealData+m_nRecvOffset,pData,nLength);
					m_nRecvOffset += nLength;					
					return;								
				}
			}else
			{
				//ASSERT(m_nRecvOffset == nMinHeadLength);

				//取头整个数据包的长度（包含头）
				__int64 nPacketLength = GetPacketLength((CPacketHead*)m_pRealData);

				if(nPacketLength<0)
				{
					throw "Error packet";
					//ASSERT(AfxCheckMemory());
					return;
				}

				if( nPacketLength > m_nAllocRealDataItem)
				{

					BYTE* pNew  = new BYTE[nPacketLength];	//分配这么多空间，以存储数据.
					memset(pNew,0,nPacketLength);

					memcpy(pNew,m_pRealData,m_nRecvOffset);	//将原来的数据拷贝进去。

					if(!m_pRealData)
					{
						delete []m_pRealData;
						m_pRealData= NULL;
					}
					m_pRealData = pNew;	
					m_nAllocRealDataItem = nPacketLength;	//新分配内存的大小。
				}


				ASSERT(nPacketLength>=nMinHeadLength);

				int nNeed  =   nPacketLength - m_nRecvOffset;
				if(nLength<nNeed)
				{
					memcpy(m_pRealData+m_nRecvOffset,pData,nLength);	//全部拷入.
					m_nRecvOffset += nLength;
					//数据不足，还要等下一次接收.
					//ASSERT(AfxCheckMemory());
					return;
				}else		
				{
					//数据充足
					//将需要部分全部拷入.
					memcpy(m_pRealData+m_nRecvOffset,pData,nNeed);	//全部拷入

					//数据包，接收完整，通知数据包到达.
					OnReceivePacket(m_pRealData,nPacketLength);
					//接收完数据后，不删除，以便下次复用。
					m_nRecvOffset = 0;	//再重新开始。
					nDealLength +=  nNeed;		//添加已经处理的.
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
	size_t		m_nRecvOffset;				//接收到数据的内容.
};


#endif //_CCEPACKET_H_