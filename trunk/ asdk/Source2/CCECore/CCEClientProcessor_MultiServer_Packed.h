#pragma once
#ifndef _CCECLIENTPROCESSOR_MULTISERVER_PACKED_H_
#define _CCECLIENTPROCESSOR_MULTISERVER_PACKED_H_

#include "CCEClientProcessor_MultiServer.h"
#include "CCEPacket.h"



template <class CPacketHead,
int nMinHeadLength=sizeof(CPacketHead)>
class CCEClientProcessor_MultiServer_Packed
	:public CCCEClientProcessor_MultiServer,public CCCEPacket<CPacketHead,nMinHeadLength>
{

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

	/**
	*	网络中断，会调用该函数，然后删除对应的Processor.
	*	因此，派生类，可在此做一些资源释放性等额外的工作。
	*	如果返回True ,表示，需要删除该Processor.否则，不删除.
	*	本基类默认返回TRUE.
	*/
	virtual bool OnClose()
	{
		CCCEPacket<CPacketHead,nMinHeadLength>::OnClose();
		return CCCEClientProcessor_MultiServer::OnClose();
	}
};



#endif	//_CCECLIENTPROCESSOR_MULTISERVER_PACKED_H_