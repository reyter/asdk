/**
* @Copyright 深圳市创真科技有限公司(www.hh.com.cn)
* @System	 通用通信库(Common Communication Environment Core)
* @Brief	 组包处理器类
* @Author	 wli
* @Date      2010-10-25
*/

#include "CCEPacket.h"

#ifndef _CCEPROCESSOR_PACKED_
#define _CCEPROCESSOR_PACKED_


template <class CPacketHead,
int nMinHeadLength=sizeof(CPacketHead)>
class CCCEProcessor_Packed
	:public CCCEProcessor,public CCCEPacket<CPacketHead,nMinHeadLength>
{
	//DECLARE_DYNCREATE(CCCEProcessor_Packed);
	//
	//

protected:
	/**
	*	从网络上接收到数据的回调函数
	*	@param pData		数据起始地址
	*	@param nLength		数据长度
	*/
	virtual void OnRecvRawData(const void* pData,int nLength)
	{
		/** 
		*	该函数会组包，并调用其虚函数
		*	virtual bool OnReceivePacket(void *pPacket,int nLength)=0;
		*	子类可重写上面的函数，来完成组包。
		*/
		CCCEPacket<CPacketHead,nMinHeadLength>::OnRecvBinarayData(pData,nLength);
	}
};

//template <class CPacketHead,
//int nMinHeadLength=sizeof(CPacketHead)>
//IMPLEMENT_DYNCREATE(CCCEProcessor_Packed,CCCEProcessor)



#endif //_CCEPROCESSOR_PACKED_