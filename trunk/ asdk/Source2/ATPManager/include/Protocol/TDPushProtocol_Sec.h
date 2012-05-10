#pragma once
#ifndef _TDPUSHPROTOCOL_SEC_H_
#define _TDPUSHPROTOCOL_SEC_H_

#include "TDPushProtocol.h"

/**
* 证券类 持仓 推送
*/
typedef  CPushItem<ATP_Msg_Sec_HoldPosition>  ATP_Msg_Sec_Push_HoldPosition;

/**
* 证券类 委托记录 推送
*/
typedef CPushItem<ATP_Msg_Sec_QueryOrderRecords_Answer>  ATP_Msg_Sec_Push_OrderRecords;


/**
* 证券类 可撤单推送
*/
typedef  CPushItem<ATP_Msg_Sec_QueryCanCancel_Answer>  ATP_Msg_Sec_Push_CanCancel;


/**
* 证券类 成交推送
*/
typedef  CPushItem<ATP_Msg_Sec_QueryMatch_Answer>  ATP_Msg_Sec_Push_Match;


/**
* 证券类 资产推送
*/
typedef  CPushItem<ATP_Msg_Sec_QueryAssets_Answer>  ATP_Msg_Sec_Push_Assets;



#endif //_TDPUSHPROTOCOL_SEC_H_