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
#ifndef _PTLPUSHQUEEN_SEC_H_
#define _PTLPUSHQUEEN_SEC_H_


#include "PTLPushQueen_Receive.h"

/**
* ֤ȯ�ֱֲ�
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Sec_HoldPosition> CSecHoldPositionQueen;

/**
* ֤ȯί�м�¼��
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Sec_QueryOrderRecords_Answer> CSecOrderQrecordsQueen;

/**
* �ɳ�������
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Sec_QueryCanCancel_Answer> CSecCanCancelQueen;


/**
* �ɽ�����
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Sec_QueryMatch_Answer> CSecMatchQueen;

/**
* �ʲ�����
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Sec_QueryAssets_Answer> CSecAssetsQueen;



#endif //_PTLPUSHQUEEN_SEC_H_