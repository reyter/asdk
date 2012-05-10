#pragma once

#ifndef _ATPMANAGERNETDEFINE_H_
#define _ATPMANAGERNETDEFINE_H_

#define	BYTE			unsigned char

#define	UINT8			unsigned char
#define INT8			char						

#define UINT16			unsigned short
#define INT16			short

#define UINT32			unsigned int				
#define INT32			int							

#ifndef _WINDOWS_
#define UINT64		unsigned __int64
#define INT64		__int64					
#else
#define UINT64		unsigned long long
#define INT64		long long
#endif

//	消息定义
#define	ID_ATPMANAGE_LOGIN							50001//	登录
//#define	ID_ATPMANAGE_LOGINANSWER					50002//	登录应答

#define	ID_ATPMANAGE_QUERYOPERATELOG				50010//	查询操作日志(超级管理员,管理员)

/************************************************************************/
/*			超级管理员                                                                     */
/************************************************************************/
//管理员
#define	ID_ATPMANAGE_CREATEMANAGER					50021//	创建管理员(超级管理员)
#define	ID_ATPMANAGE_DELETEMANAGER					50022//	删除管理员(超级管理员)
#define	ID_ATPMANAGE_MODIFYMANAGER					50023//	修改管理员(超级管理员，管理员)
#define	ID_ATPMANAGE_QUERYMANAGERINFO				50024//	查询管理员(超级管理员)

//服务器组
#define	ID_ATPMANAGE_CREATESERVERGROUP				50031//	创建服务器组(超级管理员)
#define	ID_ATPMANAGE_DELETESERVERGROUP				50032//	删除服务器组(超级管理员)
#define	ID_ATPMANAGE_MODIFYSERVERGROUP				50033//	修改服务器组(超级管理员)
#define	ID_ATPMANAGE_QUERYSERVERGROUPINFO			50034//	查询服务器组(超级管理员)

//服务器
#define	ID_ATPMANAGE_CREATESERVER					50041//	创建服务器(超级管理员)
#define	ID_ATPMANAGE_DELETESERVER					50042//	删除服务器(超级管理员)
#define	ID_ATPMANAGE_MODIFYSERVER					50043//	修改服务器(超级管理员)
#define	ID_ATPMANAGE_QUERYSERVERINFO				50044//	查询服务器(超级管理员)

//权限
#define	ID_ATPMANAGE_QUERYPERMISSIONINFO			50051//	查询权限(超级管理员、管理员)

/************************************************************************/
/*                                       管理员                               */
/************************************************************************/

//算法组
#define	ID_ATPMANAGE_ADDALGORITHMGROUP				51011//	添加算法组(管理员)
#define	ID_ATPMANAGE_DELETEALGORITHMGROUP			51012//	删除算法组(管理员)
#define ID_ATPMANAGE_MODIFYALGORITHMGROUP			51013//	修改算法组(管理员)
#define ID_ATPMANAGE_QUERYALGORITHMGROUPINFO		51014//查询算法组(管理员)
													 
//算法
#define	ID_ATPMANAGE_ADDALGORITHM					51021//	添加算法信息(管理员)
#define	ID_ATPMANAGE_DELETEALGORITHM				51022//	删除算法信息(管理员)
#define	ID_ATPMANAGE_MODIFYALGORITHM				51023//	修改算法(管理员)
#define	ID_ATPMANAGE_MODIFYALGORITHMINFO			51024//	修改算法信息(管理员)

//算法属性
#define	ID_ATPMANAGE_QUERYALGORITHMINFO				51025//	查询算法信息(管理员)
#define	ID_ATPMANAGE_QUERYALGORITHMPARAM			51026//	查询算法参数
#define	ID_ATPMANAGE_QUERYALGORITHMVERSION			51027//	查询算法历史版本

//用户组												 
#define	ID_ATPMANAGE_ADDUSERGROUP					51041//	添加用户组(管理员)
#define	ID_ATPMANAGE_DELETEUSERGROUP				51042//	删除用户组(管理员)
#define	ID_ATPMANAGE_MODIFYUSERGROUP				51043//	修改用户组(管理员)
#define	ID_ATPMANAGE_QUERYUSERGROUPINFO				51044//	查询用户组信息(管理员)

//用户
#define	ID_ATPMANAGE_ADDUSER						51051//	添加用户(管理员)
#define	ID_ATPMANAGE_DELETEUSER						51052//	删除用户(管理员)
#define	ID_ATPMANAGE_MODIFYUSER						51053//	修改用户(管理员)
#define	ID_ATPMANAGE_QUERYUSERINFO					51054//	查询用户信息(管理员)

//用户操作日志
#define	ID_ATPMANAGE_QUERYUSEROPERATELOG			51061//	查询用户操作日志(管理员)struReq_ATPManage_ATPManageOperateLog

//算法日志
#define	ID_ATPMANAGE_QUERYUSEDALGORITHM				51071//	查询算法统计信息(管理员)
#define	ID_ATPMANAGE_QUERYUSERALGORITHM				51072//	查询用户使用算法统计信息(管理员)
#define	ID_ATPMANAGE_QUERYSERVERALGORITHM			51073//	查询服务器运行算法统计信息(管理员)




/************************************************************************/
/*                                   用户操作                                   */
/************************************************************************/
#define	ID_ATPMANAGE_USER_QUERYALGORITHM			520001//	查询算法(用户)
#define	ID_ATPMANAGE_USER_ADDALGORITHM				520002//	添加算法(用户)
#define	ID_ATPMANAGE_USER_DELETEALGORITHM			520003//	删除算法(用户)
#define	ID_ATPMANAGE_USER_RUNALGORITHM				520004//	运行算法(用户)
#define	ID_ATPMANAGE_USER_MODIFYINFO				520005//	修改信息(用户)

//////////////////////////////////////////////////////////////////////////




//! 信息包头
struct stru_ATPManageMsgHeadInfo
{	
	UINT16 nHeadSize;				//	
	UINT16 nChannel;				//	数据通道
	UINT32 nMsgType;				//	消息类型
	UINT32 nFlags;					//	
};
const int g_stru_ATPManageMsgHeadInfoSize = sizeof stru_ATPManageMsgHeadInfo;

struct stru_BlockHead
{
	UINT32 nItems;
	UINT32 nItemSize;

};

//版本
struct stru_AlgorithmVer
{
	short Ver[4];
};

//	算法参数
struct stru_ATPAlgorithmParam
{
	
};

//手工输入的ID,
struct	stru_ATPID
{
	char	szID[16];
	char	szName[16];
};
//自动生成ID
struct	stru_ATPAutoID
{
	UINT32	nID;
	char	szName[16];
};

//标准返回结果
struct	struAns_Operate
{
	char	szInfo[128];			//	返回信息
	UINT8	nResult;				//	返回结果 0成功  其他查表
};


//! ***********************************************************************/
//!                    登录                                                
//! ***********************************************************************/


//! 用户登录
struct	struReq_ATPManageLogin
{
	char				szLoginID[16];		//	账号
	char				szIP[32];			//	用户IP
	char				szMAC[16];			//	MAC
	char				szDiskNum[64];		//	硬盘序列号
	char				szPassword[32];		//	密码
	char				chMD5[32];			//	MD5验证码
	char				chProduct[16];		//	产品名
	stru_AlgorithmVer	Ver[4];				//	版本号
};


//! ************************************************************************
//! 超级管理员  
//! ************************************************************************
   
//! ******************
//!    管理员 
//! ******************
struct	stru_ATPManagerInfo
{
	char					szID[16];			//	管理员ID
	char					szName[16];			//	名字
	char					szPwd[32];			//	密码
	UINT32					nStatus;			//	管理员状态  0 1 2
	char					szExplain[64];		//	说明信息
	UINT32					nPermissionIDs[32];	//	权限ID
	UINT32					nCreateDate;		//	创建日期
	UINT32					nCreateTime;		//	创建时间
	UINT32					nLastDate;			//	最后登陆日期
	UINT32					nLastTime;			//	最后登陆时间
	UINT8					nDeleteMark;		//	删除标志
	stru_BlockHead			ServerBlock;		//	服务器个数items	itemsize = sizeof(struATPAutoID)   服务器IDs
	stru_BlockHead			ServerGroupBlock;	//	服务器组个数items   itemsize = sizeof(struATPAutoID)  服务器组IDs
};				
//! 添加管理员
//ID_ATPMANAGE_CREATEMANAGER

//! 修改管理员
//ID_ATPMANAGE_MODIFYMANAGER

//! 删除管理员
//ID_ATPMANAGE_DELETEMANAGER

//! 查看管理员
//ID_ATPMANAGE_QUERYADMIN						-----查看所有管理员，无条件查询


//////////////////////////////////////////////////////////////////////////
//! ******************
//!     服务器组		  *
//! ******************
struct stru_ATPServerGroupInfo
{
	UINT32			nID;				//	组ID 自动生成
	UINT32			nParentID;			//	父组ID
	char			szName[16];			//	组名
	char			szExplain[128];		//	说明
	UINT32			nCreateDate;		//	创建日期
	UINT32			nCreateTime;		//	创建时间
	UINT8			nDeleteMark;		//	删除标记
};
//! 添加服务器组	
//ID_ATPMANAGE_CREATESERVERGROUP

//! 修改服务器组
//ID_ATPMANAGE_MODIFYSERVERGROUP
//! 删除服务器组
//ID_ATPMANAGE_DELETESERVERGROUP

//! 查看服务器组
//ID_ATPMANAGE_QUERYSERVERGROUP		------查看所有服务器，无条件查询


//////////////////////////////////////////////////////////////////////////
//! *****************
//!      服务器       
//! *****************
struct	stru_ATPServerInfo
{
	UINT32			nID;						//	服务器ID 自动生成
	char			szName[16];					//	服务器名
	char			szIP[16];					//	服务器IP
	UINT32			nPort;						//	服务器端口号
	UINT32			nGroupID[16];				//	服务器组
	UINT32			nCreateDate;				//	创建日期
	UINT32			nCreateTime;				//	创建时间
	UINT8			nDeleteMark;				//	删除标记
};
//! 添加服务器
//ID_ATPMANAGE_CREATESERVER

//! 修改服务器
//ID_ATPMANAGE_MODIFYSERVER

//! 删除服务器
//ID_ATPMANAGE_DELETESERVER

//! 查看服务器
//通过组ID查询服务器
//ID_ATPMANAGE_QUERYSERVER						
struct struReq_ATPServerInfo_QUERY
{
	UINT32			nGroupID;						//	  空则查询全部服务器
};


//////////////////////////////////////////////////////////////////////////
//! ******************
//!     权限		  *
//! ******************
struct stru_ATPPermissionInfo
{
	UINT32		nPermissionID;					//	权限ID 自动生成
	char		szPermissionName[16];			//	权限名
	UINT8		nPermissionType;				//	权限类型
};					
//! 查看权限
//通过权限ID查询权限
//ID_ATPMANAGE_QUERYPERMISSION					-----查看所有权限，无其他条件查询


//////////////////////////////////////////////////////////////////////////
/************************************************************************/
//!                      普通管理员                                          
/************************************************************************/
//! *****************
//!       管理员      *
//! ******************
//! 修改管理员(自己)信息
//ID_ATPMANAGE_MODIFYMANAGER
//stru_ATPManagerInfo


//////////////////////////////////////////////////////////////////////////
//! *****************
//!       用户组      *
//! ******************
struct	stru_ATPUserGroupInfo
{
	UINT32				nID;							//	组ID  自动生成
	UINT32				nParentID;						//	父组ID
	char				szName[16];						//	组名
	char				szCreateActor[16];				//	创建角色
	char				szExplain[64];					//	说明信息
	stru_BlockHead		AlgorithmBlock;					//	算法个数 Item ,   itemsize=sizeof(struATPAutoID) 算法IDs
	stru_BlockHead		AlgorithmGroupBlock;			//	算法组个数Item  , itemsize=sizeof(struATPAutoID)  算法组IDs
	stru_BlockHead		ServerBlock;					//	服务器个数Item,	itemsize=sizeof(struATPAutoID) 服务器IDs
	stru_BlockHead		ServerGroupBlock;				//	服务器组个数Item  ,itemsize=sizeof(struATPAutoID)  服务器组IDs
	UINT32				nAlloc;							//	分配原则
	int					nCreateDate;					//	创建日期
	int					nCreateTime;					//	创建时间
	int					nDeleteDate;					//	删除日期
	int					nDeleteTime;					//	删除时间
	UINT8				nDeleteMark;					//	删除标志
};
//! 添加用户组
//ID_ATPMANAGE_ADDUSERGROUP

//! 修改用户组
//ID_ATPMANAGE_MODIFYUSERGROUP

//! 删除用户组
//ID_ATPMANAGE_DELETEUSERGROUP

//! 查看用户组
//ID_ATPMANAGE_QUERYUSERGROUPINFO				----------查看所有用户组，无条件查询


////////////////////////////////////////////////////////////////////////// 
//! *****************
//!     用户      *
//! ******************
//! 用户帐号与资金帐号关联
struct stru_ATPFundInfo
{
	char	szFund[16];										//	资金帐号
	char	szOrgID[16];									//	营业部ID
	char	szMarkets[12];									//	市场
};
//! 用户
struct stru_ATPUserInfo
{
	char					szUserID[16];					//	用户ID
	char					szPwd[32];						//	用户密码
	char					szUserName[16];					//	用户名
	char					szCardID[18];					//	身份证号码
	UINT32					szUserGroupIDs[4][16];			//	用户组ID
	UINT32					nPermissionIDs[32];				//	权限ID
	UINT32					nAuthorizeBeginDate;			//	授权使用开始日期
	UINT32					nAuthorizeEndDate;				//	授权使用截止日期
	UINT32					nUserStatus;					//	用户使用状态
	char					szMobiles[2][16];				//	手机号码,含区号
	char					szTelephones[2][12];			//	电话号码
	UINT64					nQQNumbers[2];					//	QQ号码
	char					szEmails[2][64];				//	Email号码
	char					szUserExplain[128];				//	用户说明,含禁用理由
	char					szIPs[128];						//	限制IP
	char					szMacMark[40];					//	限制MAC地址
	char					szDiskNum[32];					//	限制硬盘序列号
	UINT32					nLimitBeginTime[4];				//	限制开始时间
	UINT32					nLimitEndTime[4];				//	限制结束时间
	char					chLimitWeek;					//	限制星期,0x80是限制
	char					chDeleteMark;					//	删除标记
	stru_BlockHead			FundBlock;						//	当前资金帐号结构体数Items,最多10个         itemsize = sizeof(struATPID)
	UINT32					nCanRunAlgorithm;				//	允许同时运行算法个数
	stru_BlockHead			AlgorithmBlock;					//	算法个数items  ,  itemsize = sizeof(struATPAutoID)
	stru_BlockHead			AlgorithmGroupBlock;			//	算法组个数 items, itemsize = sizeof(struATPAutoID)
	char					szServer[16];
	stru_BlockHead			ServerGroupBlock;
	UINT32					nCreateDate;					//	创建日期
	UINT32					nCreateTime;					//	创建时间
	UINT32					nLastDate;						//	最后登陆日期
	UINT32					nLastTime;						//	最后登陆时间
	UINT8					nDeleteMark;					//	删除标志

};									
//! 添加用户
//ID_ATPMANAGE_ADDUSER

//! 修改用户
//ID_ATPMANAGE_MODIFYUSER

//! 删除用户
//ID_ATPMANAGE_DELETEUSER

//! 查看用户
//ID_ATPMANAGE_QUERYUSER
//通过用户组ID查询用户
struct struReq_ATPUserInfo_QUERY
{
	UINT32 nID;												//空则查询全部用户
};


//////////////////////////////////////////////////////////////////////////
//! ******************
//!     操作日志         *
//! ******************
struct	stru_ATPManageOperateLogInfo
{
	char	szActorID[16];					//	角色ID
	UINT32	nRecords;						//	记录数
	UINT32  nOperateType;					//	操作类型
	UINT32	nOperateDate;					//	操作日期
	UINT32	nOperateTime;					//	操作时间
	char	szInfo[128];					//	记录信息

};
//! 查看用户操作日志
//通过开始结束时间，操作类型、用户ID查询用户操作日志
//ID_ATPMANAGE_QUERYUSEROPERATELOG
struct struReq_ATPManageOperateLog_QUERY
{
	int		nBeginDate;
	int		nEndDate;
	int		nOperateType;
	char	szUserID[16];					//	用户ID 空则查看全部
};


//////////////////////////////////////////////////////////////////////////
//! *****************
//!        算法组     *
//! ******************
struct	stru_ATPAlgorithmGroupInfo
{
	UINT32			nID;							//	组ID  自动生成
	UINT32			nParentID;						//	父组ID
	char			szName[16];						//	组名
	char			szCreateActor[16];				//	创建角色
	int				nCreateDate;					//	创建日期
	int				nCreateTime;					//	创建时间
	int				nDeleteDate;					//	删除日期
	int				nDeleteTime;					//	删除时间
	UINT8			nDeleteMark;					//	删除标志
};
//! 添加算法组
//ID_ATPMANAGE_ADDALGORITHMGROUP

//! 修改算法组
//ID_ATPMANAGE_MODIFYALGORITHMGROUP

//! 删除算法组
//ID_ATPMANAGE_DELETEALGORITHMGROUP

//! 查看算法组
//ID_ATPMANAGE_QUERYALGORITHMGROUP			--------查看所有算法组，无其他条件查询


//////////////////////////////////////////////////////////////////////////
//! ******************
//!        算法            *
//! ******************
struct stru_ATPAlgorithmInfo
{
	GUID					AlgorithmID;					//	guid 唯一
	char					szAlgorithmName[16];			//	算法名
	stru_AlgorithmVer		AlgorithVer;					//	算法版本
	UINT8					nVersionAttribute;				//	算法版本属性 测试版之类
	UINT8					nCharge;						//	是否收费
	UINT32					nGroupID;						//	算法组
	char					szExplain[128];					//	算法说明
	char					szWarning[32];					//	算法警告
	char					szKeyword[128];					//	算法关键字
	UINT8					nStatus;						//	算法状态
	char					szStopReason[128];				//	算法禁用原因
	UINT32					nCreateDate;					//	算法发布日期
	UINT32					nCreateTime;					//	算法发布时间
	char					szPath[128];					//	算法使用路径,路径要指定
	stru_BlockHead			AlgorithmBlock;					//	算法参数个数  算法参数
	UINT8					nDeleteMark;					//	删除标志
};

//! 添加算法
//ID_ATPMANAGE_ADDALGORITHM

//! 修改用户
//ID_ATPMANAGE_MODIFYALGORITHM

//! 删除用户
//ID_ATPMANAGE_DELETEALGORITHM

//! 查看算法.
//通过算法组ID查询
//ID_ATPMANAGE_QUERYALGORITHM
struct struReq_ATPManage_QueryAlgorithm
{
	UINT32			nGroupID;								//	空则查询全部
};

//通过算法ID查询算法版本
//ID_ATPMANAGE_QUERYALGORITHMVERSION
struct struReq_ATPManage_QueryAlgorithmHistoryVersion
{
	GUID			guid;									//	算法ID
};

//通过算法ID、版本，查询算法参数
//ID_ATPMANAGE_QUERYALGORITHMPARAM
struct struReq_ATPManage_QueryAlgorithmParam
{
	GUID				guid;								//	算法ID  
	stru_AlgorithmVer	Ver;								//	算法版本
};

//////////////////////////////////////////////////////////////////////////
//! ******************
//!        算法日志表   *
//! ******************
struct stru_ATPAlgorithmRunLogInfo
{
	GUID					AlgorithmID;					//	算法ID
	char					szUserID[16];					//	用户ID
	UINT32					nUserGroupID;
	UINT32					nServerID	;					//	服务器ID		
	UINT32					nStatus;						//	算法运行状态
	UINT32					nRunBeginDate;					//	运行开始日期
	UINT32					nRunBeginTime;					//	运行开始时间
	UINT32					nRunEndDate;					//	运行结束日期
	UINT32					nRunEndTime;					//	运行结束时间
	UINT64					nVolume;						//	成交量
	UINT64					nTurnover;						//	成交额
	UINT32					nCount[20];						//	交易操作统计，买，卖，持仓，可撤单，市场
	UINT32					nCompletion;					//	算法完成度,百分比
};
//! 查询算日志
//查询算法
//ID_ATPMANAGE_QUERYUSEDALGORITHM
struct struReq_ATPAlgorithmRunLogInfo_QUERY
{
	UINT32					nRunBeginDate;					//	运行开始日期
	UINT32					nRunEndDate;					//	运行结束日期  为空则查询正在运行算法 
	GUID					AlgorithmID;					//	算法ID  为空则全部算法
};
//查询用户使用算法信息
//ID_ATPMANAGE_QUERYUSERALGORITHM
struct struReq_ATPUserRunLogInfo_QUERY
{
	UINT32					nRunBeginDate;					//	运行开始日期
	UINT32					nRunEndDate;					//	运行结束日期  为空查询正在运行算法 
	char					szUserID[16];					//	用户ID 为空则查所有用户
};
//查询服务器使用算法信息
//ID_ATPMANAGE_QUERYSERVERALGORITHM
struct struReq_ATPServerRunLogInfo_QUERY
{
	UINT32					nRunBeginDate;					//	运行开始日期
	UINT32					nRunEndDate;					//	运行结束日期  为空查询正在运行算法 
	UINT32					nServerID	;					//	服务器ID 空则全部服务器
};

#endif	//	_ATPMANAGEDEFINE_H_