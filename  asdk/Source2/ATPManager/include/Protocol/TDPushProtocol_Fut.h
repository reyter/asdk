#pragma once
#ifndef _TDPUSHPROTOCOL_FUT_H_
#define _TDPUSHPROTOCOL_FUT_H_

#include "TDPushProtocol.h"

/**
* �ڻ��� �ֲ� ����
*/
typedef  CPushItem<ATP_Msg_Fut_HoldPosition>  ATP_Msg_Fut_Push_HoldPosition;

/**
* �ڻ��� ί�м�¼ ����
*/
typedef CPushItem<ATP_Msg_Fut_QueryOrderRecords_Answer>  ATP_Msg_Fut_Push_OrderRecords;


/**
* �ڻ��� �ɳ�������
*/
typedef  CPushItem<ATP_Msg_Fut_QueryCanCancel_Answer>  ATP_Msg_Fut_Push_CanCancel;


/**
* �ڻ��� �ɽ�����
*/
typedef  CPushItem<ATP_Msg_Fut_QueryMatch_Answer>  ATP_Msg_Fut_Push_Match;


/**
* �ڻ��� �ʲ�����
*/
typedef  CPushItem<ATP_Msg_Fut_QueryAssets_Answer>  ATP_Msg_Fut_Push_Assets;



#endif //_TDPUSHPROTOCOL_FUT_H_