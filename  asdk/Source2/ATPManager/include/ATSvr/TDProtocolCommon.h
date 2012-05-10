/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 OpenTD 协议.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-1		李伟		 创建
-------------------------------------------------------------
*/

#pragma once

#ifndef __TDPROTOCOLCOMMON__H__
#define __TDPROTOCOLCOMMON__H__


#include "..\\include\\UTI\\UTIDefine.h"
#include "..\\include\\UTI\\UTIDefine_Sec.h"
#include "..\\include\\UTI\\UTIDefine_Fut.h"




//全部一字节方式对齐
#pragma pack(push,1)

//消息头标志.
#define ATP_MSG_FLAG   (0x0716)



//算法服务器消息类型.
enum    ATP_MSG_TYPE
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////系统登录部分//////////////////////////////////////////////////////////////////

	/**
	系统登录
	*/	
	ATP_MSG_LOGIN = 1,

	/**
	系统登录应答.
	*/ 
	ATP_MSG_LOGIN_ANSWER = 2,
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////算法信息查询部分//////////////////////////////////////////////////////////////	


	/**
	查询算法基本信息消息
	*/
	ATP_MSG_QUERY_ALGOINFO=10000,

	/**
	查询算法基本信息消息应答
	*/ 
	ATP_MSG_QUERY_ALGOINFO_ANSWER=10001,


	/**
	查询算法参数信息.
	*/ 	
	ATP_MSG_QUERY_ALGO_PARAMETER_INFO = 10002,


	/**
	查询算法参数信息应答
	*/ 
	ATP_MSG_QUERY_ALGO_PARAMETER_INFO_ANSWER = 10003,


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////证券指令部份//////////////////////////////////////////////////////////////////////	
	
	/**
	普通下单（证券）
	*/ 	
	ATP_MSG_SEC_MAKE_ORDER = 11000,

	/**
	下单应答
	*/ 	
	ATP_MSG_SEC_MAKE_ORDER_ANSWER = 11001,


	/**
	持仓查询（证券）
	*/ 
	ATP_MSG_SEC_QUERYHOLD = 11002,


	/**
	持仓查询应答
	*/ 	
	ATP_MSG_SEC_QUERYHOLD_ANSWER = 11003,


	/**
	当日委托记录查询（证券）
	*/ 
	ATP_MSG_SEC_QUERYORDERRECORD = 11004,


	/**
	当日委托记录查询（证券）应答
	*/
	ATP_MSG_SEC_QUERYORDERRECORD_ANSWER = 11005,


	/**
	可撤单查询（证券）
	*/ 
	ATP_MSG_SEC_QUERYCANCANCEL  =  11006,


	/**
	可撤单查询（证券）应答
	*/ 
	ATP_MSG_SEC_QUERYCANCANCEL_ANSWER  =  11007,


	/**
	资产查询（证券）
	*/ 
	ATP_MSG_SEC_QUERYASSETS	 = 11008,


	/**
	资产查询（证券）应答
	*/ 
	ATP_MSG_SEC_QUERYASSETS_ANSWER	 = 11009,


	/**
	撤单指令(证券)
	*/ 	
	ATP_MSG_SEC_CANCELORDER	 =  11010,


	/**
	撤单指令(证券)应答
	*/ 	
	ATP_MSG_SEC_CANCELORDER_ANSWER	 =  11011,

	/**
	成交查询(证券)
	*/ 	
	ATP_MSG_SEC_QUERYMATCH =11012,


	/**
	成交查询(证券)应答
	*/ 	
	ATP_MSG_SEC_QUERYMATCH_ANSWER =11013,



	/**
	最大可交易量(证券)查询
	*/
	ATP_MSG_SEC_QUERYMAXVOLUME=11014,

	/**
	最大可交易量查询应答.
	*/ 
	ATP_MSG_SEC_QUERYMAXVOLUME_ANSWER=11015,





	/**
	算法下单（证券）
	*/ 	
	ATP_MSG_SEC_MAKE_ORDER_BY_ALGO = 12000,

	/**
	算法下单结果应答.
	*/	
	ATP_MSG_SEC_MAKE_ORDER_BY_ALGO_ANSWER = 12001,

	/**
	当前帐户正在运行的算法状态查询
	*/	
	ATP_MSG_SEC_QUERY_CURRENT_ALGO_STATUS = 12002,

	/**
	当前帐户正在运行的算法状态查询--返回的结果.
	*/ 
	ATP_MSG_SEC_QUERY_CURRENT_ALGO_STATUS_ANSWER = 12003,	
	
	
	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////期货指令部份//////////////////////////////////////////////////////////////////////	
	
	/**
	普通下单（期货）
	*/ 	
	ATP_MSG_FUT_MAKE_ORDER = 13000,

	/**
	下单应答
	*/ 	
	ATP_MSG_FUT_MAKE_ORDER_ANSWER = 13001,


	/**
	持仓查询（期货）
	*/ 
	ATP_MSG_FUT_QUERYHOLD = 13002,


	/**
	持仓查询应答
	*/ 	
	ATP_MSG_FUT_QUERYHOLD_ANSWER = 13003,


	/**
	当日委托记录查询（期货）
	*/ 
	ATP_MSG_FUT_QUERYORDERRECORD = 13004,


	/**
	当日委托记录查询（期货）应答
	*/
	ATP_MSG_FUT_QUERYORDERRECORD_ANSWER = 13005,


	/**
	可撤单查询（期货）
	*/ 
	ATP_MSG_FUT_QUERYCANCANCEL  =  13006,


	/**
	可撤单查询（期货）应答
	*/ 
	ATP_MSG_FUT_QUERYCANCANCEL_ANSWER  =  13007,


	/**
	资产查询（期货）
	*/ 
	ATP_MSG_FUT_QUERYASSETS	 = 13008,


	/**
	资产查询（期货）应答
	*/ 
	ATP_MSG_FUT_QUERYASSETS_ANSWER	 = 13009,


	/**
	撤单指令(期货)
	*/ 	
	ATP_MSG_FUT_CANCELORDER	 =  13010,


	/**
	撤单指令(期货)应答
	*/ 	
	ATP_MSG_FUT_CANCELORDER_ANSWER	 =  13011,

	/**
	成交查询(期货)
	*/ 	
	ATP_MSG_FUT_QUERYMATCH =13012,


	/**
	成交查询(期货)应答
	*/ 	
	ATP_MSG_FUT_QUERYMATCH_ANSWER =13013,



	/**
	最大可交易量(期货)查询
	*/
	ATP_MSG_FUT_QUERYMAXVOLUME=13014,

	/**
	最大可交易量查询应答.
	*/ 
	ATP_MSG_FUT_QUERYMAXVOLUME_ANSWER=13015,





	/**
	算法下单（期货）
	*/ 	
	ATP_MSG_FUT_MAKE_ORDER_BY_ALGO = 14000,

	/**
	算法下单结果应答.
	*/	
	ATP_MSG_FUT_MAKE_ORDER_BY_ALGO_ANSWER = 14001,

	/**
	当前帐户正在运行的算法状态查询
	*/	
	ATP_MSG_FUT_QUERY_CURRENT_ALGO_STATUS = 14002,

	/**
	当前帐户正在运行的算法状态查询--返回的结果.
	*/ 
	ATP_MSG_FUT_QUERY_CURRENT_ALGO_STATUS_ANSWER = 14003,	


	
	
	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	系统消息
	*/ 	
	ATP_MSG_SYSTEM_MESSAGE = 999999,


	ATP_MSG_END
};


//--------------------------消息头------------------------------------------------------/
/**
消息头,每一条消息最前面，均含有此消息头。其对应类型为 ATP_MSG_TYPE. 
@see ATP_MSG_TYPE
*/ 
typedef UTI_MsgHead					ATP_MsgHead;
//-------------------------------------------------------------------------------------/


/**
算法交易服务器系统消息。
*/
struct ATP_Msg_SystemMessage
{
	/**
	消息类型
	0	普通信息
	1	错误信息
	*/ 	
	int nType;	

	/**
	消息.
	*/ 	
	char szMsg[128];
};



/**
数组信息头信息.
*/ 
struct ATP_Msg_Array_Head
{
	/**
	其后跟的记录数
	*/ 	
	int nItems;

	/**
	单个记录大小
	*/ 	
	int nItemSize;
};






/**
算法参数类型
*/
enum ATP_ALGOPARAM_TYPE
{
	/**
	整型.
	*/
	AP_TYPE_INT=0,

	/** 
	浮点数.
	*/
	AP_TYPE_DOUBLE=1,

	/**
	INT64.
	*/
	AP_TYPE_INT64,

	/**
	字符串.
	*/
	AP_TYPE_STRING,
};



//--------------------------服务器支持的算法查询--------------------------------------/
/////////////////////// 发送 ////////////////////////////////////////////////////////// 

//  发送时，仅需指定消息类型为 ATP_MSG_QUERY_ALGOINFO

/////////////////////////返回///////////////////////////////////////////////////////////

/**
查询算法后反回的消息头.
该消息头后，紧跟对应的 ATP_ALGORITHM_INFO 数据.
后面跟指定记录的  ATP_ALGORITHM_INFO 数组.
@see ATP_ALGORITHM_INFO
*/ 
typedef ATP_Msg_Array_Head			ATP_Msg_QueryAlgoInfoAnswer_Head;


/**
算法信息.
*/
struct ATP_ALGORITHM_INFO
{
	/**
	算法的GUID.
	*/ 	
	GUID guidAlgo;

	/**
	算法名称.
	*/ 	
	char szAlgoName[32];

	/**
	算法描述。
	*/ 
	char szAlgoDescription[1024];

	/**
	算法参数个数.
	*/
	int nParamInfo;	
};

//---------------------------------------------------------------------------------------/






//--------------------------算法的参数名细查询----------------------------------------/
/////////////////////// 发送 ////////////////////////////////////////////////////////// 

/**
查询指定算法参数信息.
*/
struct ATP_Msg_QueryAlgoParamterInfo
{
	/**
	算法的GUID.
	*/ 	
	GUID guidAlgo;
};


/////////////////////////返回///////////////////////////////////////////////////////////

/**
返回头信息
*/
struct ATP_Msg_QueryAlgoParamterInfo_Answer_Head
{
	/**
	算法的GUID.
	*/ 	
	GUID guidAlgo;

	/**
	后面跟的参数信息个数.
	*/ 	
	int  nParamter;

	/**
	记录大小，应为sizeof( ATP_ALGOPARAM_INFO )
	*/ 
	int  nItemsize;
};


/**
算法参数详细信息
*/
struct ATP_ALGOPARAM_INFO
{
	/**
	参数类型.
	*/ 	
	int nType;	

	/**
	参数名
	*/ 
	char szParamName[64];

	/**
	描述信息
	*/ 	
	char szParamDescription[512];

};











//--------------------------算法方式下单      ----------------------------------------/
/////////////////////// 发送 ////////////////////////////////////////////////////////// 

/**
算法方式，下单，后面将指定个数的 ATP_ALGOPARAM_VALUE 类型数组。

*/ 
struct ATP_Msg_MakeOrderByAlgo_Head
{
	/**
	算法GUID
	*/ 	
	GUID gudiAlgo;

	/**
	单个参数Item大小。应为 sizeof(ATP_ALGOPARAM_VALUE)
	*/	
	int nParamterItemSize;

	/**
	参数值个数
	*/ 	
    int  nParamterValue;

};

/**
算法参数值.
需要根据nType 来确定Data成员的值.
@see ATP_ALGOPARAM_TYPE
*/ 
struct ATP_Msg_MakeOrderByAlgo_ParamValue
{
	int nType;
	union {
		int			iVal;		
		double		dVal;
		INT64		i64Val;
		char		chVal[256];		
	}data;
};

/////////////////////////返回///////////////////////////////////////////////////////////

struct ATP_Msg_MakeOrderByAlgo_Answer
{
	/**
	0表示成功，其他值表示失败！
	*/ 	
	INT  nResult;			

	/**
	返回时附加的信息
	*/
	char szInfo[128];	
};

//--------------------------------------------------------------------------------------/

typedef    ATP_Msg_MakeOrderByAlgo_Head    ATP_Msg_Sec_MakeOrderByAlgo_Head;
typedef    ATP_Msg_MakeOrderByAlgo_Head    ATP_Msg_Fut_MakeOrderByAlgo_Head;
typedef   ATP_Msg_MakeOrderByAlgo_ParamValue  	ATP_ALGOPARAM_VALUE;
typedef   ATP_Msg_MakeOrderByAlgo_ParamValue 	 ATP_Msg_Sec_MakeOrderByAlgo_ParamValue;
typedef   ATP_Msg_MakeOrderByAlgo_ParamValue  	ATP_Msg_Fut_MakeOrderByAlgo_ParamValue;
typedef   ATP_Msg_MakeOrderByAlgo_Answer       ATP_Msg_Sec_MakeOrderByAlgo_Answer;
typedef   ATP_Msg_MakeOrderByAlgo_Answer       ATP_Msg_Fut_MakeOrderByAlgo_Answer;




//-------------------------该帐号当前正在运行的算法查询---------------------------------/
/////////////////////// 发送 ////////////////////////////////////////////////////////////
//只需标明消息类型

/////////////////////////返回///////////////////////////////////////////////////////////

/**
消息头信息.
*/
typedef ATP_Msg_Array_Head			ATP_Msg_CurrentAlgoStatus_Head;

struct ATP_Msg_CurrentAlgoStatus{
		/**
		算法名称
		*/
		char szName[64];				

		/**
		开始时间,格式, HHMMSSmmm
		*/
		UINT nBeginTime;				

		/**
		下单次数
		*/ 
		UINT nMakeOrderTimes;
		
		/**
		己完成数.
		*/		
		UINT nFinish;

		/**
		总数
		*/ 
		UINT nTotal;

		/**
		状态说明
		*/
        char szStatus[64];				
};

//--------------------------------------------------------------------------------------/

typedef ATP_Msg_CurrentAlgoStatus_Head ATP_Msg_Sec_CurrentAlgoStatus_Head;
typedef ATP_Msg_CurrentAlgoStatus_Head ATP_Msg_Fut_CurrentAlgoStatus_Head;
typedef ATP_Msg_CurrentAlgoStatus ATP_Msg_Sec_CurrentAlgoStatus;
typedef ATP_Msg_CurrentAlgoStatus ATP_Msg_Fut_CurrentAlgoStatus;




//---------------------------------------------------------------------------------------/


#pragma pack(pop)

#endif	//TDPROTOCOLCOMMON

