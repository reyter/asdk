//
// @project:atp3
// @author:梁兴其
// @date:2011/7/29
// @description:定义ATPACCEPT与ATPManager之间的通信协议
//
// 

#pragma once
#ifndef __ATPACCEPT_MANAGER_DEFINE_H__
#define __ATPACCEPT_MANAGER_DEFINE_H__

#include "../../include/Protocol/TDProtocolCommon.h"
#include "ATPManagerDataBaseDefine.h"
#pragma pack(push,1)

//
//获取用户信息
//获取用户资金帐号
//获取用户使用算法列表 
//
// 验证用户需要的信息:
// 1.用户名
// 2.密码
// 3.IP
// 4.Mac
// 5.硬盘序列号 
//
#define ID_MSG_ATPACCEPT_MANAGER_VALIDATEUSER					1	//验证用户 
#define ID_MSG_ATPACCEPT_MANAGER_GETFUNDACCOUNT					2	//获取资金账号的信息 
#define ID_MSG_ATPACCEPT_MANAGER_GETALGOINFO					3	//获取用户可以使用的算法及算法使用信息 及算法授权服务器组 
#define	ID_MSG_ATPACCEPT_MANAGER_GETSERVERINFO					4	//获取用户的授权服务器 
#define ID_MSG_ATPACCEPT_MANAGER_GETUSERINFO_WITHFUNDACCOUNT	5	//通过资金帐号获取用户信息 
#define ID_MSG_ATPACCEPT_MANAGER_GETFUNDACCOUNT_SECURITYTYPE	6	//获取资金帐号的证券类型
#define ID_MSG_ATPACCEPT_MANAGER_SET_ALGO_RUNLOG				7	//设置算法运行的日志
#define ID_MSG_ATPACCEPT_MANAGER_UPDATE_ALGO_RUNLOG				8	//用户管理模块 获取最新的算法运行日志
#define	ID_MSG_ATPACCEPT_MANAGER_UPLOADALGO_TACTICS				9	//上载策略

//IP地址结构
//支持IPv6
// struct AtpAccept_Manager_UserIP
// {
// 	int nFiled1;		//字段1
// 	int nFiled2;		//字段2
// 	int nFiled3;		//字段3
// 	int nFiled4;		//字段4 如果为IPv4 前三个字段为0 此字段为IPv4的值  
// };

//	算法运行状态
#define ALGSTATUS_START		0			//开始
#define ALGSTATUS_RUN		1			//正在运行
#define ALGSTATUS_END		2			//结束
#define ALGSTATUS_ABORT		3			//用户中止

/*
 *	消息头
 *	主要是包号 为线程同步
 */
struct AtpAccept_Manager_MsgHead
{
	int nVersion;		//版本
	long lPacketNo;		//包号 
};

/*
 *	验证用户信息 
 */
struct AtpAccept_Manager_ValidateUser{
	char szUserName[16];			//用户帐号
	char szUserPwd[32];				//密码
	char szLoginIpType;				//4:IPv4 6:IPv6
	char szLoginIp[16];				//登录Ip 支持IPv6 
	char szMac[16];					//mac地址
	char szDiskSerialNum[32];		//硬盘序列号 
};

/*
 *	验证用户结果信息 
 */
struct AtpAccept_Manager_ValidateUser_Result
{
	unsigned int nUserId;	//用户ID 
	int nResult;			//0表示登录成功 其他表示失败
	char szError[64];		//失败说明 
};

/*
 *	用户信息
 */
struct AtpAccept_Manager_User
{
	unsigned int nUserId;	//用户ID 
	char szUserName[16];	//用户帐号
};

/*
 * 获取资金帐号信息 
 */
typedef AtpAccept_Manager_User AtpAccept_Manager_GetFoundAccount;

/*
 *	获取资金帐号返回结果 
 */
struct AtpAccept_Manager_GetFoundAccount_Result_Head
{
	int nItems;	//资金账号的数目 
};
/*
 *	获取资金帐号返回结果 
 */
struct AtpAccept_Manager_GetFoundAccount_Result
{
	char szFound[16];		//资金帐号
	char szOrghID[16];		//营业部编号
	short sType;			//证券类型 
	int nCaptialType;		//资金行号类型 1：资金账号 2：信用账号
};


/*
 *	获取可以使用的算法 
 *	一下子把算法参数及算法服务器全取出来
 */
typedef AtpAccept_Manager_User AtpAccept_Manager_GetAlgoInfo;

/*
 *	获取算法返回的头信息 
 */
struct AtpAccept_Manager_GetAlgoInfo_ResultHead
{
	int nAlgoCount;			//算法数目 
};

/*
 *	算法信息 
 */

struct AtpAccept_Manager_GetAlgoInfo_AlgoInfo
{
	UINT32						nSerialNumber;					//	自动增长 唯一
	Atp_Algorithm_Info			algoInfo;						//原来的二期的算法信息结构
	/*
	 *	0:C++ 标准库(C#可由C++标准库载入)
	 *	1:宏汇易编程
	 *	2:Lua脚本
	 *	3:Matlab算法
	 */
	int		nAlgoLangType;			//算法语言类型
	struDataBaseAlgorithmVer	AlgorithVer;					//	算法版本
	char						szAlgoPath[MAX_PATH];			//算法文件的路径
};

/*
 *	算法的头 
 */
// struct AtpAccept_Manager_GetAlgoInfo_AlgoHead
// {
// 	int nAlgoParamCount;	// 算法参数个数
// 	int nAlgServerCount;	// 算法可运行服务器的个数 
// };
// 
// 获取授权服务器的请求信息 
typedef AtpAccept_Manager_User AtpAccept_Manager_GetServerInfo;

/*
 *	请求服务器信息返回的头
 *	
 *
 */
struct  AtpAccept_Manager_GetServerInfo_ResultHead
{
	int nItems;			//记录数目
	int nItemSize;		//记录的大小 
};

/*
 *	算法授权的服务器信息 
 */
struct  AtpAccept_Manager_GetServerInfo_AlgoServer
{
	char cIpType;			//IP类型
	char szServerIp[16];	//服务器IP
	int nPort;				//服务端口 
	UINT32 nServerID;		//服务器记录ID(算法管理模块的记录ID)

	AtpAccept_Manager_GetServerInfo_AlgoServer(){ZeroMemory(this,sizeof(AtpAccept_Manager_GetServerInfo_AlgoServer));}

	AtpAccept_Manager_GetServerInfo_AlgoServer(const AtpAccept_Manager_GetServerInfo_AlgoServer &other)
	{
		memcpy(this,&other,sizeof(AtpAccept_Manager_GetServerInfo_AlgoServer));
	}

	AtpAccept_Manager_GetServerInfo_AlgoServer & operator=(const AtpAccept_Manager_GetServerInfo_AlgoServer &other)
	{
		memcpy(this,&other,sizeof(AtpAccept_Manager_GetServerInfo_AlgoServer));
		return (*this);
	}

};	


/*
 *	通过资金帐号获取用户信息 
 */
struct AtpAccept_Manager_GetUserInfo_WithFundAccout
{	
	ATP_Msg_Login fundAccount;		///>资金帐号
	char szLoginIpType;				///>4:IPv4 6:IPv6
	char szLoginIp[16];				///>登录Ip 支持IPv6 
	char szMac[16];					///>mac地址
	char szDiskSerialNum[32];		///>硬盘序列号 
	int nSecurityType;				///>证券类型 
};

/*
 *	通过资金帐号获取用户信息 
 *	返回的结果 
 */
struct AtpAccept_Manager_GetUserInfo_WithFundAccout_Result
{
	char szUserName[16];			//用户帐号
	char szUserPwd[32];				//密码
	unsigned int nUserId;			//用户ID 
	int nResult;					//0表示登录成功 其他表示失败
	char szError[64];				//失败说明 
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*
 *	获取资金帐号类型
 */
struct AtpAccept_Manager_GetFundAccount_SecurityType
{
	/**
	*	营业部代码.
	*/
	char chOrgID[8];	
	/**
	*	客户号.
	*/
	char chUserID[16];	
};

/*
 *	获取资金帐号类型结果
 */
struct AtpAccept_Manager_GetFundAccount_SecurityType_Result
{
	int nSecurityType;	//-1:不存在该资金帐号，0:没有市场 1股票 2:期货 3:其他
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*
 *	设置算法运行日志
 *	无需回应
 */
struct AtpAccept_Manager_SetAlgoRunLog
{
	GUID		AlgorithmID;					//	算法ID
	char		szUserID[16];					//	用户ID
	INT64		iAlgoInsID;						//	算法运行实例ID		20110916		
	UINT32		nServerID;						//	服务器ID		
	UINT32		nStatus;						//	算法运行状态
	UINT32		nRunBeginDate;					//	运行开始日期
	UINT32		nRunBeginTime;					//	运行开始时间
	UINT32		nRunEndDate;					//	运行结束日期
	UINT32		nRunEndTime;					//	运行结束时间
	UINT64		nVolume;						//	成交量
	UINT64		nTurnover;						//	成交额
	UINT32		nCount[20];						//	交易操作统计，买，卖，持仓，可撤单，市场
	UINT32		nCompletion;					//	算法完成度,百分比
	char		szAlgoRemark[256];				//	算法的描述	
};

/*
 *	更新算法运行日志
 */
typedef AtpAccept_Manager_SetAlgoRunLog AtpAccept_Manager_UpdateAlgoRunLog;

/*
*	上载策略
*/
struct AtpAccept_Manager_UploadTactics
{
	//用户信息
	UINT32		uUserId;						// 用户ID自增ID
	char		szUserId[16];						// 用户ID
	//策略信息
	GUID		guid;							// 策略的GUID(可有客户端或者用户接入端来生成)
	char		szAlgorithmName[16];			//	算法的名称
	UINT32		nAlgoType;						//0 表示读算法的  1-读策略的 2-选股条件的, 3-选股方案的...
	UINT32 		nSecurityType; 					//证劵类型
	UINT32		nLanguageType;					//	语言类型
	char		szExplain[128];					//	算法说明
	UINT32		uContentLength;					//  策略内容
	//此结构后面紧跟策略内容数据
};

/*
*	上载策略结果
*/
struct AtpAccept_Manager_UploadTactics_Result
{
	union
	{
		struct 
		{
			char		szFileName[64];					//	策略的名字
			char		szPath[MAX_PATH];				//	算法使用路径,路径要指定
		}success;
		
		struct 
		{
			int			nResult;						//	错误值
			char		szError[128];					//	错误的说明
		}fail;
	}result;
};

#pragma pack(pop)

#endif	//__ATPACCEPT_MANAGER_DEFINE_H__