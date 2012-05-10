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
#ifndef _TDPUSHPROTOCOL_H_
#define _TDPUSHPROTOCOL_H_

//
//消息类型参见 TDProtocolCommon.h
#include "..\\TDProtocolCommon.h"

#pragma pack(push,1)

/**
* 整个包的更新方法.
* 
*/
enum ATP_MSG_PUSH_PACKET_METHOD
{
	/*
	* 全量设置
	*/
	ATP_PUSH_PACKET_ALL_SET = 1,		

	/**
	* 部分修改
	*/
	ATP_PUSH_PACKET_PART_MODIFY=2		
};


/**
* 单条记录的方法
* 
*/
enum ATP_MSG_PUSH_ITEM_METHOD
{
	/**
	* 不适用, 当包为 ATP_PUSH_PACKET_ALL_SET 全量设置时，单条记录更新方法不适用。
	*/
	ATP_PUSH_ITEM_NA = 0,

	/** 
	* 增加
	*/
	ATP_PUSH_ITEM_ADD = 1,			

	/**
	* 删除
	*/
	ATP_PUSH_ITEM_DELETE=2,				

	/**
	* 修改
	*/
	ATP_PUSH_ITEM_UPDATE=3				

};


/**
* 推送包消息头
*/
struct ATP_Msg_PushHead
{
	/**
	* 包使用方法
	*/
	ATP_MSG_PUSH_PACKET_METHOD nPushPacketMethod;

	/**
	* 其后跟的记录数
	*/
    int						   nItems;	

	/**
	* 单条记录的长度.
	*/
	int							nItemSize;
	
};


/**
* 1000 - 10000为保留.
*/
enum ATP_PUSH_MESSAGE
{
	/**
	*请求开始推送
	*/
	ATP_MSG_REQ_BEGIN_PUSH	= 1000,

///////////////////////////////////////////
	/**
	* 证券成交推送
	*/
	ATP_MSG_SEC_PUSH_MATCH = 1001,

	/**
	* 证券资产推送
	*/
	ATP_MSG_SEC_PUSH_ASSETS = 1002,

	/**
	* 证券委托推送
	*/ 
	ATP_MSG_SEC_PUSH_ORDER = 1003,

	/**
	* 证券可撤推送
	*/ 
	ATP_MSG_SEC_PUSH_CANCANCEL = 1004,

	/**
	* 证券持仓推送
	*/ 
	ATP_MSG_SEC_PUSH_HOLDPOSITION = 1005,
	

//////////////////////////////////////////////////////////////////

	/**
	* 期货成交推送
	*/
	ATP_MSG_FUT_PUSH_MATCH = 2001,

	/**
	* 期货资产推送
	*/
	ATP_MSG_FUT_PUSH_ASSETS = 2002,

	/**
	* 期货委托推送
	*/ 
	ATP_MSG_FUT_PUSH_ORDER = 2003,

	/**
	* 期货可撤推送
	*/ 
	ATP_MSG_FUT_PUSH_CANCANCEL = 2004,

	/**
	* 期货持仓推送
	*/ 
	ATP_MSG_FUT_PUSH_HOLDPOSITION = 2005,

/////////////////////////////////////////////////////////////////////////////////

	/**
	* 算法运行状态推送
	*/ 
	ATP_MSG_PUSH_ALGO_STATUS = 3000,	

	/**
	 *	算法日志推送
	 */
	 ATP_MSG_PUSH_ALGO_LOG = 3001

};


#pragma pack(pop)

#endif //_TDPUSHPROTOCOL_H_

