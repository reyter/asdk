/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨����ƽ̨����Э��.
	 

* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			 ����         �޸�˵��
2010-11-25	 ��ΰ		 ����
-------------------------------------------------------------
*/

/**
*  ������Ϣ.
*/

#pragma once
#ifndef _TDPUSHPROTOCOL_H_
#define _TDPUSHPROTOCOL_H_

//
//��Ϣ���Ͳμ� TDProtocolCommon.h
#include "TDProtocolCommon.h"

#pragma pack(push,1)

/**
* �������ĸ��·���.
* 
*/
enum ATP_MSG_PUSH_PACKET_METHOD
{
	/*
	* ȫ������
	*/
	ATP_PUSH_PACKET_ALL_SET = 1,		

	/**
	* �����޸�
	*/
	ATP_PUSH_PACKET_PART_MODIFY=2		
};


/**
* ������¼�ķ���
* 
*/
enum ATP_MSG_PUSH_ITEM_METHOD
{
	/**
	* ������, ����Ϊ ATP_PUSH_PACKET_ALL_SET ȫ������ʱ��������¼���·��������á�
	*/
	ATP_PUSH_ITEM_NA = 0,

	/** 
	* ����
	*/
	ATP_PUSH_ITEM_ADD = 1,			

	/**
	* ɾ��
	*/
	ATP_PUSH_ITEM_DELETE=2,				

	/**
	* �޸�
	*/
	ATP_PUSH_ITEM_UPDATE=3				

};


/**
* ���Ͱ���Ϣͷ
*/
struct ATP_Msg_PushHead
{
	/**
	* ��ʹ�÷���
	*/
	ATP_MSG_PUSH_PACKET_METHOD nPushPacketMethod;

	/**
	* �����ļ�¼��
	*/
    int						   nItems;	

	/**
	* ������¼�ĳ���.
	*/
	int							nItemsize;
	
};



template <class PushObject>
struct CPushItem
{	
	/**
	* ������¼�ĸ��·���
	*/
	ATP_MSG_PUSH_ITEM_METHOD  nMessageHead;

	/**
	* ���͵�������Ŀ.
	*/
    PushObject			       item;  
};


#pragma pack(pop)

#endif //_TDPUSHPROTOCOL_H_

