/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法交易平台推送协议.


* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			 作者         修改说明
2010-11-25	 李伟		 创建
-------------------------------------------------------------
*/

/**
*  推送消息.
*/

#pragma once
#ifndef _PTLPUSHQUEEN_SEC_H_
#define _PTLPUSHQUEEN_SEC_H_


#include "PTLPushQueen_Receive.h"

/**
* 证券持仓表
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Sec_HoldPosition> CSecHoldPositionQueen;

/**
* 证券委托记录表
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Sec_QueryOrderRecords_Answer> CSecOrderQrecordsQueen;

/**
* 可撤单队列
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Sec_QueryCanCancel_Answer> CSecCanCancelQueen;


/**
* 成交队列
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Sec_QueryMatch_Answer> CSecMatchQueen;

/**
* 资产队列
*/
typedef CPTLPushQueen_Receive<ATP_Msg_Sec_QueryAssets_Answer> CSecAssetsQueen;



#endif //_PTLPUSHQUEEN_SEC_H_