/**
* @Copyright �����д���Ƽ����޹�˾(www.hh.com.cn)
* @System	 ͨ��ͨ�ſ�(Common Communication Environment Core)
* @Brief	 �����������
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
};

//template <class CPacketHead,
//int nMinHeadLength=sizeof(CPacketHead)>
//IMPLEMENT_DYNCREATE(CCCEProcessor_Packed,CCCEProcessor)



#endif //_CCEPROCESSOR_PACKED_