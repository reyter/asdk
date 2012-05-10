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


#include "..\\UTIAPI\\UTIDefine.h"
#include "..\\UTIAPI\\UTIDefine_Sec.h"
#include "..\\UTIAPI\\UTIDefine_Fut.h"




//全部一字节方式对齐
#pragma pack(push,1)

//消息头标志.
#define ATP_MSG_MAGICNUMBER   (0x2010)


//算法服务器消息类型.
enum    ATP_MSG_TYPE
{

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	系统消息
	*/ 	
	ATP_MSG_SYSTEM_MESSAGE = 0,


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


	/**
	* 设置地址信息.
	*/ 
	ATP_MSG_SET_ADDR_INFO=3,

	
	/**
	* 服务器发送动态口令
	* 一登录，服务器便会发动态口令，此口令用于算法交易服务器3DES登录，同时将登录消息头的nCryptCompressMethod的高位，设置为2.
	*/
	ATP_MSG_SET_DYNAMIC_PASSWORD=4,


	

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
	//当前帐户正在运行的算法状态查询
	*/	
	ATP_MSG_SEC_QUERY_CURRENT_ALGO_STATUS = 12002,

	/**
	当前帐户正在运行的算法状态查询--返回的结果.
	*/ 
	ATP_MSG_SEC_QUERY_CURRENT_ALGO_STATUS_ANSWER = 12003,	

	
	
	/**
	* 指示算法完成
	*/
	ATP_MSG_SEC_ALGO_FINISH	= 12004,
	
	

	/**
	* 终止正在运行的算法.
	*/
	ATP_MSG_SEC_KILL_ALGO  = 12005,

	/**
	 *	算法当天日志历史请求
	 */
	ATP_MSG_SEC_ALGO_TODAY_LOGHISTORY_QUERY = 12006,

	 /**
	 *	算法当天日志历史回应
	 */

	 ATP_MSG_SEC_ALGO_TODAY_LOGHISTORY_ANSWER = 12007,

	 /**
	 *	算法日志历史请求
	 */
	 ATP_MSG_SEC_ALGO_LOGHISTORY_QUERY = 12008,

	 /**
	 *	算法日志历史回应
	 */
	 ATP_MSG_SEC_ALGO_LOGHISTORY_ANSWER = 12009,

	 /*
	*	推送日志
	*/
	ATP_MSG_SEC_PUSH_ALGO_LOG = 12010,

	/*
	 *	日志类别请求
	 */
	 ATP_MSG_SEC_ALGO_LOGCATEGORY_QUERY = 12011,

	 /*
	  *	日志类别回应
	  */
	 ATP_MSG_SEC_ALGO_LOGCATEGORY_ANSWER = 12012,

	 /*
	  *	订阅日志请求
	  */
	 ATP_MSG_SEC_SUBSCRIBE_ALOGLOG_QUERY = 12013,

	 /*
	  *	订阅日志回应
	  */
	ATP_MSG_SEC_SUBSCRIBE_ALOGLOG_ANSWER = 12014, 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///上传文件，客服端上传文件，以便查阅.

	/**
	* 上传文件
	* 
	*/
	ATP_MSG_UPLOAD_FILE  =  12901,
	

	/**
	* 上传文件结果
	*/
	ATP_MSG_UPLOAD_FILE_RESULT = 12902,




	
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
	* 推送期货结算单.
	*/
	ATP_MSG_FUT_PUSH_SETTLEMENT = 13016,

	/**
	* 确认期货结算单
	*/
	ATP_MSG_FUT_CONFIRMSETTLEMENT = 13017,




	/**
	算法下单（期货）
	*/ 	
	ATP_MSG_FUT_MAKE_ORDER_BY_ALGO = 14000,

//////////////////////////////////////////////////////////////////////////////////////////

	/**
	* 算法下单结果应答.
	*/	
	ATP_MSG_FUT_MAKE_ORDER_BY_ALGO_ANSWER = 14001,

	/**
	* 当前帐户正在运行的算法状态查询
	*/	
	ATP_MSG_FUT_QUERY_CURRENT_ALGO_STATUS = 14002,

	/**
	当前帐户正在运行的算法状态查询--返回的结果.
	*/ 
	ATP_MSG_FUT_QUERY_CURRENT_ALGO_STATUS_ANSWER = 14003,	


	/**
	* 指示算法完成
	*/
	ATP_MSG_FUT_ALGO_FINISH	= 14004,


	/**
	* 终止正在运行的算法.
	*/
	ATP_MSG_FUT_KILL_ALGO  = 14005,
	

    


	ATP_MSG_END
};




#define TTD_HH_COMPRESS_METHOD		0x01  //宏汇压缩方式

//--------------------------消息头------------------------------------------------------/
/**
消息头,每一条消息最前面，均含有此消息头。其对应类型为 ATP_MSG_TYPE. 
@see ATP_MSG_TYPE
*/ 
//数据包识别头
struct ATP_MsgHead
{
	USHORT                nMagicNum; //魔法数字  ATP_MSG_MAGICNUMBER

	/**
	*					  整个包，除了 nMagicNum 和 nCRC 外 的CRC检验值.
	*/
	int					  nCRC;

	/**
	*   该消息头长度
	*/
	USHORT                nHeadLen;

	/**
	*	数据长度（不含本识别头）
	*/
	UINT32				  nDataLen;

	/**
	*	使用的协议版本号,当前版本为 1  
	*/
	USHORT  			  sVersion;

	/**
	*	加密压缩方式,先压缩再加密.(先解密再解压)
	*	LOBYTE        压缩方法  0、无压缩, 1、宏汇压缩 
	*       HIBYTE        加密方法. 0、无加密、1、3DES固定密文,2、3DES 动态密文, 4、变形算法
	*/
	USHORT				  nCryptCompressMethod;

	/**
	* 数据类型
	*/
	USHORT  			  sDataType;

	/**
	* 数据生成时间戳（精确到毫秒,格式HHMMSSmmm）
	*/
	UINT				  nTime;

	/**
	* 请求编号，如果是回应客户端的请求，
	* 则该编号为客户端发送来的请求编号。
	* 服务器推送的非应答类包，请求号恒为0xFFFFFFFF
	*/
	UINT                  nReqOrder;

	/**
	32字节 流水号（当返回数据太大时有效，每个请求顺序编码）
	*/
	int     			  nOrder;
	
};
//-------------------------------------------------------------------------------------/



typedef UTI_LoginRequest  ATP_Msg_Login;	//登录请求.

typedef UTI_LoginAnswer   ATP_Msg_Login_Answer;	//登录应答.



/**
* 地址信息
*/
struct ATP_Msg_Addr_Info
{
	/**
	* IPV4地址,IPv6暂不考虑，以后升级
	*/
	char szIP[16];			
	
	/**
	* mac 地址.
	*/
	char szMAC[18];
};

/**
* 动态口令
*/
struct ATP_Msg_Dynamic_Password
{
	char szDynPassword[24];
};




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
	AP_TYPE_INT64=2,

	/**
	字符串.
	*/
	AP_TYPE_STRING=3,

	/**
	* 日期
	*/
	AP_TYPE_DATE=4,

	/**
	* 时间
	*/
	AP_TYPE_TIME=5,
    
	/**
	* 列表
	*/
	AP_TYPE_LIST=6

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
struct Atp_Algorithm_Info
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
算法参数值.
需要根据nType 来确定Data成员的值.
@see ATP_ALGOPARAM_TYPE
*/ 
struct ATP_Msg_MakeOrderByAlgo_ParamValue
{
	ATP_ALGOPARAM_TYPE  nType;			//ATP_ALGOPARAM_TYPE
	union {
		int			iVal;				//AP_TYPE_LIST index.
		double		dVal;
		INT64		i64Val;
		char		chVal[64];			//AP_TYPE_STRING
	}data;
};



/**
* 算法参数详细信息
* 变长.
*/
struct Atp_Algoparam_Info
{
	/**
	* 附加数据长度	
	*/ 
	int		nExtraDataLength;	

	/**
	参数类型.
	*/ 	
	ATP_ALGOPARAM_TYPE  nType;	

	/**
	参数名
	*/ 
	char     szParamName[64];
	
	/**
	描述信息
	*/ 	
	char	szParamDescription[512];

	//默认值.
	ATP_Msg_MakeOrderByAlgo_ParamValue defaultValue;	

	/**
	* 附加数据
	*/	
	BYTE    *pExtraData;

	////////////////////helper functions/////////
	
	Atp_Algoparam_Info()
	{
		memset(this,0,sizeof(*this));
	}
	Atp_Algoparam_Info(const Atp_Algoparam_Info& other)
	{
		memset(this,0,sizeof(*this));
		*this = other;
	}
	~Atp_Algoparam_Info()
	{
		if(pExtraData && nExtraDataLength>0)
			delete []pExtraData;
	}
	void SetExtraData(BYTE* pData,int nLength)
	{
		if(pExtraData && nExtraDataLength>0)
		{			
			delete []pExtraData;
			pExtraData  = NULL;
		}
		nExtraDataLength = nLength; 
		if(pData && nLength>0)
		{
			pExtraData = new BYTE[nLength+1];
			memset(pExtraData,0,nLength+1);
			memcpy(pExtraData,pData,nLength);
		}
	}
	int FromByte(const char* pData,int nDataLen)
	{
		if(pExtraData && nExtraDataLength>0)
		{			
			delete []pExtraData;
			pExtraData  = NULL;

		}
		memset(this,0,sizeof(*this));	//先清空.
		
		//从宏汇传输的二进制流上恢复.
		//先用整形放一长，再传用数据。
		int* pItemLen = (int*)pData;
		pData += sizeof(int);
		memcpy(this,pData,offsetof(Atp_Algoparam_Info,pExtraData));
		pExtraData = new BYTE[nExtraDataLength+1];
		pExtraData[nExtraDataLength] = 0;
		memcpy(pExtraData,pData+offsetof(Atp_Algoparam_Info,pExtraData),nExtraDataLength);
		return *pItemLen + sizeof(int);
	}
	Atp_Algoparam_Info& operator=(const Atp_Algoparam_Info& other)
	{
		memcpy(this,&other,offsetof(Atp_Algoparam_Info,pExtraData));	
		SetExtraData(other.pExtraData,other.nExtraDataLength);
		return *this;
	}	
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
		* 标识符。
		*/
		INT64	nIdentity;

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
       	char szStatus[256];				
};

//--------------------------------------------------------------------------------------/

typedef ATP_Msg_CurrentAlgoStatus_Head ATP_Msg_Sec_CurrentAlgoStatus_Head;
typedef ATP_Msg_CurrentAlgoStatus_Head ATP_Msg_Fut_CurrentAlgoStatus_Head;
typedef ATP_Msg_CurrentAlgoStatus ATP_Msg_Sec_CurrentAlgoStatus;
typedef ATP_Msg_CurrentAlgoStatus ATP_Msg_Fut_CurrentAlgoStatus;




//---------------------------------------------------------------------------------------/



/**
* 算法完成结果。
*/ 
struct ATP_Msg_AlgoFinish
{
	/**
	* 标识符。
	*/
	INT64	nIdentity;

	/**
	* 退出代码.
	*/
	int         nRetCode;


	/**
	* 退出信息.
	*/
	char        szMsg[256];

};



/**
* 可用于杀死指示的算法.
*/
struct ATP_Msg_Run_Algo_Info
{
	/**
	* 标识符。
	*/
	INT64	nIdentity;
};


typedef ATP_Msg_AlgoFinish ATP_Msg_SEC_AlgoFinish;
typedef ATP_Msg_AlgoFinish ATP_Msg_Fut_AlgoFinish;

typedef ATP_Msg_Run_Algo_Info ATP_Msg_SEC_Run_Algo_Info;
typedef ATP_Msg_Run_Algo_Info ATP_Msg_FUT_Run_Algo_Info;


/**
算法交易服务器上传文件结果
*/
struct ATP_Msg_UploadFileResult
{
	/**
	消息类型
	0	上传文件成功
	其他，错误码
	*/ 	
	int nType;	

	/**
	*消息.
	*/ 	
	char szResultMsg[128];
};

/**
 *	推送日志结构
 *
 */
#define PER_LOG_MAX_LENGTH 256
struct ATP_Msg_AlgoLog
{
	int nId;							//自动编号
	INT64 iSrcIdentity;					//来源的表示 即算法的标识
	int nType;							//类型
	int nCategory;						//类别
	int nGrade;							//级别
	int nTime;							//时间
	int nDataLen;						//数据长度
	char *pData;						//数据
	
	ATP_Msg_AlgoLog()
	{
		nId = 0;
		nType = 0;
		nCategory = 0;
		nGrade = 0;
		nTime = 0;
		nDataLen = 0;
		pData = 0;
	}

	~ATP_Msg_AlgoLog()
	{
		if (pData)
		{
			delete []pData;
		}
	}
};

/**
 *	日志类别结构
 *
 */
struct ATP_Msg_Algo_LogCategory
{
	int nCate;					//类别
	char szDescription[16];		//类别说明
};

/**
 *	日志订阅头结构
 *
 */
struct ATP_Msg_Algo_LogSubscribe_Head
{
	GUID guidAlgo;
	ATP_Msg_Array_Head arrHead;
};

/**
 *	日志订阅结构
 *
 */
struct ATP_Msg_Algo_LogSubscribe
{
	int nCate;		//类别
};

/**
 *	日志订阅结构
 *
 */
struct ATP_Msg_Algo_LogSubscribe_Result
{
	int nResult;		//返回结果 0表示成功其他表示失败
};


#pragma pack(pop)

#endif	//TDPROTOCOLCOMMON

