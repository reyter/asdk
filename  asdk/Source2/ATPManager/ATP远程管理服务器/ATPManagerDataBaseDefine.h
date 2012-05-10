#pragma once
#include "ATPACCEPT_MANAGER_DEFINE.H"
#ifndef _ATPMANAGERDATABASEDEFINE_H_
#define _ATPMANAGERDATABASEDEFINE_H_

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

//	算法运行状态
#define ALGSTATUS_START		0			//开始
#define ALGSTATUS_RUN		1			//正在运行
#define ALGSTATUS_END		2			//结束
#define ALGSTATUS_ABORT		3			//用户中止

//按字节对齐
#pragma pack(push, 1)

//版本
struct struDataBaseAlgorithmVer
{
	short Ver[4];
};

//标准返回结果
struct	struAnsOperate
{
	char		szInfo[128];			//	返回信息
	UINT8		nResult;				//	返回结果 TRUE 成功  其他查表
};






//手工输入的ID,
struct	struATID
{
	char	szID[16];
	char	szName[16];
};
//自动生成ID
struct	struATPAutoID
{
	UINT32	nID;
	char	szName[16];
};
//算法
struct	struATPAutoAlgoID
{
	GUID	nID;
	char	szName[16];
};

//	超级管理员
struct struATPDataBaseSuperAdmin
{
	char	szPwd[32];
	UINT32	nPort;		//	服务监听端口
};

//	普通管理员
struct	struATPDataBaseManager
{
	UINT32					nSerialNumber;		//	自动增长 唯一
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
	UINT32					nServerN;			//	服务器个数
	struATPAutoID*			pServerIDs;			//	服务器IDs
	UINT32					nServerGroupN;		//	服务器组个数
	struATPAutoID*			pServerGroupIDs;	//	服务器组IDs
};

//	服务器组
struct struATPDataBaseServerGroup
{
	UINT32			nID;				//	组ID 自动生成  唯一
	UINT32			nParentID;			//	父组ID
	char			szName[16];			//	组名
	char			szExplain[128];		//	说明
	UINT32			nCreateDate;		//	创建日期
	UINT32			nCreateTime;		//	创建时间
	UINT8			nDeleteMark;		//	删除标记
};

//服务器
struct	struATPDataBaseServer
{
	UINT32			nID;						//	服务器ID 自动生成 唯一
	char			szName[16];					//	服务器名
	char			szIP[16];					//	服务器IP
	UINT32			nIPType;					//	4,6
	UINT32			nPort;						//	服务器端口号
	UINT32			nGroupID;					//	服务器组
	UINT32			nAlloc;						//	分配原则
	UINT32			nCreateDate;				//	创建日期
	UINT32			nCreateTime;				//	创建时间
	UINT8			nDeleteMark;				//	删除标记
};

struct	struATPDataBaseServer_QUERY
{
	UINT32			nGroupID;				//	服务器组
};


//权限
struct struATPDataBasePermission
{
	UINT32		nPermissionID;					//	权限ID 自动生成 唯一
	char		szPermissionName[16];			//	权限名
	UINT8		nPermissionType;				//	权限类型
};					

//	用户组
struct	struATPDataBaseUserGroup
{
	UINT32				nID;							//	组ID  自动生成 唯一
	UINT32				nParentID;						//	父组ID
	char				szName[16];						//	组名
	char				szExplain[64];					//	说明信息
	UINT32				nAlgorithmN;					//	算法个数
	struATPAutoAlgoID*	pAlgorithmIDs;					//	算法ID
	UINT32				nAlgorithmGroupN;				//	算法组个数
	struATPAutoID*		pAlgorithmGroupIDs;				//	算法组ID
	UINT32				nServerN;						//	服务器个数
	struATPAutoID*		pServerIDs;						//	服务器ID
	UINT32				nServerGroupN;					//	服务器组个数
	struATPAutoID*		pServerGroupIDs;				//	服务器组ID
	UINT32				nCreateDate;					//	创建日期
	UINT32				nCreateTime;					//	创建时间
	UINT8				nDeleteMark;					//	删除标志
	char				szManagerID[16];				//	管理员ID
};
//	用户帐号与资金帐号关联
struct struATPDataBaseFund
{
	UINT32	nSerialNumber;									//	自动增长 唯一
	char	szFund[16];										//	资金帐号
	char	szOrgID[16];									//	营业部ID
	char	szMarkets[12];									//	市场
};
//用户
struct struATPDataBaseUser
{
	UINT32					nSerialNumber;					//	自动增长 唯一
	char					szUserID[16];					//	用户ID
	char					szPwd[32];						//	用户密码
	char					szUserName[16];					//	用户名
	char					szCardID[18];					//	身份证号码
	UINT32					nGroupIDs[4];					//	用户组ID
	UINT32					nPermissionIDs[32];				//	权限ID
	UINT32					nAuthorizeBeginDate;			//	授权使用开始日期
	UINT32					nAuthorizeEndDate;				//	授权使用截止日期
	UINT32					nStatus;						//	用户使用状态
	char					szMobiles[2][16];				//	手机号码,含区号
	char					szTelephones[2][12];			//	电话号码
	UINT64					nQQNumbers[2];					//	QQ号码
	char					szEmails[2][64];				//	Email号码
	char					szUserExplain[128];				//	用户说明,含禁用理由
	char					szIPs[128];						//	限制IP
	char					szMacMark[40];					//	限制MAC地址
	char					szDiskNum[32];					//	限制硬盘序列号
	char					chLimitTimeMark;				///是否限制登录时间
	UINT32					nLimitBeginTime[4];				//	限制开始时间
	UINT32					nLimitEndTime[4];				//	限制结束时间
	char					chLimitWeek;					//	限制星期,0x80是限制
	UINT32					nCanAssociateFundsAccount;		//	当前资金帐号结构体数,最多10个
	struATPDataBaseFund*	pATPFund;						//	资金帐号结构体
	UINT32					nCanRunAlgorithm;				//	允许同时运行算法个数
	UINT32					nAlgorithmN;					//	算法个数
	struATPAutoAlgoID*		pAlgorithmIDs;					//	算法IDs
	UINT32					nAlgorithmGroupN;				//	算法组个数
	struATPAutoID*			pAlgorithmGroupIDs;				//	算法组IDs
	UINT32					nServerN;
	struATPAutoID*			pServerIDs;						//	专属服务器
	UINT32					nServerGroupN;					//	服务器组个数
	struATPAutoID*			pServerGroupIDs;				//	服务器组IDs
	UINT32					nCreateDate;					//	创建日期
	UINT32					nCreateTime;					//	创建时间
	UINT32					nLastDate;						//	最后登陆日期
	UINT32					nLastTime;						//	最后登陆时间
	UINT8					nDeleteMark;					//	删除标志
	char					szManagerID[16];				//	管理员ID
};									
struct struATPDataBaseUser_QUERY
{
	UINT32				nID;							//	组ID  自动生成
};
//操作日志
struct	struATPDataBaseOperateLog
{
	UINT32		nSerialNumber;					//	自动增长 唯一
	char		szActorID[16];					//	角色ID
	UINT32		nRecords;						//	记录数
	UINT32		nOperateType;					//	操作类型
	UINT32		nOperateDate;					//	操作日期
	UINT32		nOperateTime;					//	操作时间
	char		szInfo[128];					//	记录信息

};

struct	struATPDataBaseOperateLog_QUERY
{
	int		nBeginDate;
	int		nEndDate;
	int		nOperateType;
	char	szUserID[16];					//	用户ID 空则查看全部
};


//	算法组
struct	struATPDataBaseAlgorithmGroup
{
	UINT32			nID;							//	组ID  自动生成 唯一
	UINT32			nParentID;						//	父组ID
	char			szName[16];						//	组名
	int				nCreateDate;					//	创建日期
	int				nCreateTime;					//	创建时间
	UINT8			nDeleteMark;					//	删除标志
	char			szManagerID[16];				//	管理员ID
};

//算法参数
struct struATPDataBaseAlgorithmParam
{
	UINT32				nSerialNumber;						//	自动增长 唯一
	int					nExtraDataLength;					//	附加数据长度	
	ATP_ALGOPARAM_TYPE  nType;								//	参数类型.
	char				szParamName[64];					//	参数名	
	char				szParamDescription[512];			//	描述信息
	ATP_Msg_MakeOrderByAlgo_ParamValue defaultValue;		//	默认值.
	UINT32				nExtraDataIndex;					//	附加数据索引
};

//算法参数附加数据
struct struATPDataBaseAlgorithmParamEX
{
	UINT32	nSerialNumber;									//	自动增长 唯一
	int		nExtraDataLength;								//	附加数据长度	
	BYTE    ExtraData[512];
};


//	算法
struct struATPDataBaseAlgorithm 
{
	UINT32					nSerialNumber;					//	自动增长 唯一
	GUID					AlgorithmID;					//	guid 唯一
	char					szAlgorithmName[16];			//	算法名
	struDataBaseAlgorithmVer AlgorithVer;					//	算法版本
	UINT8					nVersionAttribute;				//	算法版本属性 测试版之类
	UINT8					nCharge;						//	是否收费
	UINT32					nAlgoType;						//0 表示读算法的  1-读策略的 2-选股条件的, 3-选股方案的...
	UINT32					nGroupID;						//	算法组
	UINT32					nMarketType;					//	算法所属的市场类型
	UINT32					nLanguageType;					//	算法编写的语言类型
	char					szExplain[128];					//	算法说明
	char					szWarning[32];					//	算法警告
	char					szKeyword[128];					//	算法关键字
	UINT8					nStatus;						//	算法状态
	char					szStopReason[128];				//	算法禁用原因
	UINT32					nCreateDate;					//	算法发布日期
	UINT32					nCreateTime;					//	算法发布时间
	char					szPath[MAX_PATH];				//	算法使用路径,路径要指定
	char					szMainDllName[32];				//	算法入口dll文件名
	int						nParams;						//	算法参数个数
	struATPDataBaseAlgorithmParam*	pATPAlgorithmParams;	//	算法参数
	int						nParamsEx;
	struATPDataBaseAlgorithmParamEX* pATPAlgorithmParamsEX;
	UINT8					nDeleteMark;					//	删除标记
	char					szManagerID[16];				//	管理员ID
};

struct struATPDataBaseAlgorithm_QUERY
{
	UINT32			nID;									//	组ID  自动生成
};


//	算法日志，每日产生一文件
struct struATPDataBaseAlgorithmLog
{
	UINT32		nSerialNumber;				//	自动增长 唯一
	GUID		AlgorithmID;				//	算法ID
	char		szUserID[16];				//	用户ID
	INT64		iAlgoInsID;					//	算法运行实例ID		20110916		
	UINT32		nUserGroupID;
	UINT32		nServerID	;				//	服务器ID		
	UINT32		nStatus;					//	算法运行状态
	UINT32		nRunBeginDate;				//	运行开始日期
	UINT32		nRunBeginTime;				//	运行开始时间
	UINT32		nRunEndDate;				//	运行结束日期
	UINT32		nRunEndTime;				//	运行结束时间
	UINT64		nVolume;					//	成交量
	UINT64		nTurnover;					//	成交额
	UINT32		nCount[20];					//	交易操作统计，买，卖，撤单，持仓查询，成交查询，委托查询,可撤单查询，资产查询
	UINT32		nCompletion;				//	算法完成度,百分比
	char		szAlgoRemark[256];			// 算法的描述	
};

//算法使用情况汇总，通过算法使用统计，只产生一文件，每日每个算法产生一条纪录
struct struATPDataBaseAlgorithmSummaryByAlgoDaily 
{
	UINT32		nSerialNumber;				//	自动增长 唯一
	GUID		AlgorithmID;				//	算法ID
	UINT32		nDate;
	UINT64		nVolume;					//	成交量
	UINT64		nTurnover;					//	成交额
	UINT32		nCount[20];					//	交易操作统计，买，卖，持仓，可撤单，市场
};

//算法使用情况汇总，通过用户使用统计，只产生一文件，每日每个用户产生一条纪录
struct struATPDataBaseAlgorithmSummaryByAccountDaily 
{
	UINT32		nSerialNumber;				//	自动增长 唯一
	char		szUserID[16];				//	用户ID
	UINT32		nDate;
	UINT64		nVolume;					//	成交量
	UINT64		nTurnover;					//	成交额
	UINT32		nCount[20];					//	交易操作统计，买，卖，持仓，可撤单，市场
};

//算法使用情况汇总，通过算法或用户使用统计，只产生一文件，多日每个算法或每个用户产生一条记录
struct struATPDataBaseAlgorithmSummary 
{
	UINT32		nSerialNumber;				//	自动增长 唯一
	GUID		AlgorithmID;				//	算法ID
	char		szUserID[16];				//	用户ID
	UINT32		nDate;
	UINT64		nVolume;					//	成交量
	UINT64		nTurnover;					//	成交额
	UINT32		nCount[20];					//	交易操作统计，买，卖，持仓，可撤单，市场
};





struct struATPDataBaseAlgorithmLog_QUERY
{
	UINT32				nRunBeginDate;			//	运行开始日期
	UINT32				nRunEndDate;			//	运行结束日期  为空则查询正在运行算法 
	GUID				AlgorithmID;			//	算法ID  为空则全部算法
	char				szUserID[16];			//	用户ID
	UINT32				nServerID;				//	服务器ID		
};
#pragma pack(pop)
#endif	//	_ATPMANAGEDEFINE_H_