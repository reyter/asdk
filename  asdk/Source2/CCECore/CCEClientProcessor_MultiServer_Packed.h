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
	*	�������Ͻ��յ����ݵĻص�����
	*	@param pData		������ʼ��ַ
	*	@param nLength		���ݳ���
	*/
	virtual void OnRecvRawData(const void* pData,int nLength)
	{
		/** 
		*	�ú�������������������麯��
		*	virtual bool OnReceivePacket(void *pPacket,int nLength)=0;
		*	�������д����ĺ���������������
		*/
		CCCEPacket<CPacketHead,nMinHeadLength>::OnRecvBinarayData(pData,nLength);
	}

	/**
	*	�����жϣ�����øú�����Ȼ��ɾ����Ӧ��Processor.
	*	��ˣ������࣬���ڴ���һЩ��Դ�ͷ��Եȶ���Ĺ�����
	*	�������True ,��ʾ����Ҫɾ����Processor.���򣬲�ɾ��.
	*	������Ĭ�Ϸ���TRUE.
	*/
	virtual bool OnClose()
	{
		CCCEPacket<CPacketHead,nMinHeadLength>::OnClose();
		return CCCEClientProcessor_MultiServer::OnClose();
	}
};



#endif	//_CCECLIENTPROCESSOR_MULTISERVER_PACKED_H_