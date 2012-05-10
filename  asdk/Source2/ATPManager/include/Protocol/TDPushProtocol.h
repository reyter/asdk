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
#include "TDProtocolCommon.h"

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
	int							nItemsize;
	
};



template <class PushObject>
struct CPushItem
{	
	/**
	* 该条记录的更新方法
	*/
	ATP_MSG_PUSH_ITEM_METHOD  nMessageHead;

	/**
	* 推送的数据条目.
	*/
    PushObject			       item;  
};


#pragma pack(pop)

#endif //_TDPUSHPROTOCOL_H_

