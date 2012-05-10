#pragma once
#ifndef _TDPUSHPROTOCOL_SEC_H_
#define _TDPUSHPROTOCOL_SEC_H_

#include "TDPushProtocol.h"

/**
* ֤ȯ�� �ֲ� ����
*/
typedef  CPushItem<ATP_Msg_Sec_HoldPosition>  ATP_Msg_Sec_Push_HoldPosition;

/**
* ֤ȯ�� ί�м�¼ ����
*/
typedef CPushItem<ATP_Msg_Sec_QueryOrderRecords_Answer>  ATP_Msg_Sec_Push_OrderRecords;


/**
* ֤ȯ�� �ɳ�������
*/
typedef  CPushItem<ATP_Msg_Sec_QueryCanCancel_Answer>  ATP_Msg_Sec_Push_CanCancel;


/**
* ֤ȯ�� �ɽ�����
*/
typedef  CPushItem<ATP_Msg_Sec_QueryMatch_Answer>  ATP_Msg_Sec_Push_Match;


/**
* ֤ȯ�� �ʲ�����
*/
typedef  CPushItem<ATP_Msg_Sec_QueryAssets_Answer>  ATP_Msg_Sec_Push_Assets;



#endif //_TDPUSHPROTOCOL_SEC_H_