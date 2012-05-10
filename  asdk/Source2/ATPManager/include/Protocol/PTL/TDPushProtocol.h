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
#include "..\\TDProtocolCommon.h"

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
	int							nItemSize;
	
};


/**
* 1000 - 10000Ϊ����.
*/
enum ATP_PUSH_MESSAGE
{
	/**
	*����ʼ����
	*/
	ATP_MSG_REQ_BEGIN_PUSH	= 1000,

///////////////////////////////////////////
	/**
	* ֤ȯ�ɽ�����
	*/
	ATP_MSG_SEC_PUSH_MATCH = 1001,

	/**
	* ֤ȯ�ʲ�����
	*/
	ATP_MSG_SEC_PUSH_ASSETS = 1002,

	/**
	* ֤ȯί������
	*/ 
	ATP_MSG_SEC_PUSH_ORDER = 1003,

	/**
	* ֤ȯ�ɳ�����
	*/ 
	ATP_MSG_SEC_PUSH_CANCANCEL = 1004,

	/**
	* ֤ȯ�ֲ�����
	*/ 
	ATP_MSG_SEC_PUSH_HOLDPOSITION = 1005,
	

//////////////////////////////////////////////////////////////////

	/**
	* �ڻ��ɽ�����
	*/
	ATP_MSG_FUT_PUSH_MATCH = 2001,

	/**
	* �ڻ��ʲ�����
	*/
	ATP_MSG_FUT_PUSH_ASSETS = 2002,

	/**
	* �ڻ�ί������
	*/ 
	ATP_MSG_FUT_PUSH_ORDER = 2003,

	/**
	* �ڻ��ɳ�����
	*/ 
	ATP_MSG_FUT_PUSH_CANCANCEL = 2004,

	/**
	* �ڻ��ֲ�����
	*/ 
	ATP_MSG_FUT_PUSH_HOLDPOSITION = 2005,

/////////////////////////////////////////////////////////////////////////////////

	/**
	* �㷨����״̬����
	*/ 
	ATP_MSG_PUSH_ALGO_STATUS = 3000,	

	/**
	 *	�㷨��־����
	 */
	 ATP_MSG_PUSH_ALGO_LOG = 3001

};


#pragma pack(pop)

#endif //_TDPUSHPROTOCOL_H_

