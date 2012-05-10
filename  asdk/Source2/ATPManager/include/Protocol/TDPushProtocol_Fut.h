#pragma once
#ifndef _TDPUSHPROTOCOL_FUT_H_
#define _TDPUSHPROTOCOL_FUT_H_

#include "TDPushProtocol.h"

/**
* 期货类 持仓 推送
*/
typedef  CPushItem<ATP_Msg_Fut_HoldPosition>  ATP_Msg_Fut_Push_HoldPosition;

/**
* 期货类 委托记录 推送
*/
typedef CPushItem<ATP_Msg_Fut_QueryOrderRecords_Answer>  ATP_Msg_Fut_Push_OrderRecords;


/**
* 期货类 可撤单推送
*/
typedef  CPushItem<ATP_Msg_Fut_QueryCanCancel_Answer>  ATP_Msg_Fut_Push_CanCancel;


/**
* 期货类 成交推送
*/
typedef  CPushItem<ATP_Msg_Fut_QueryMatch_Answer>  ATP_Msg_Fut_Push_Match;


/**
* 期货类 资产推送
*/
typedef  CPushItem<ATP_Msg_Fut_QueryAssets_Answer>  ATP_Msg_Fut_Push_Assets;



#endif //_TDPUSHPROTOCOL_FUT_H_