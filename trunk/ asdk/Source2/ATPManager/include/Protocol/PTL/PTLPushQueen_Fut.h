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
#ifndef _PTLPUSHQUEEN_FUT_H_
#define _PTLPUSHQUEEN_FUT_H_


#include "PTLPushQueen_Receive.h"

/**
* ֤ȯ�ֱֲ�
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Fut_HoldPosition> CFutHoldPositionQueen;

/**
* ֤ȯί�м�¼��
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Fut_QueryOrderRecords_Answer> CFutOrderQrecordsQueen;

/**
* �ɳ�������
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Fut_QueryCanCancel_Answer> CFutCanCancelQueen;


/**
* �ɽ�����
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Fut_QueryMatch_Answer> CFutMatchQueen;

/**
* �ʲ�����
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Fut_QueryAssets_Answer> CFutAssetsQueen;



#endif //_PTLPUSHQUEEN_FUT_H_