
#ifndef __ATPACCEPT_MAIN_DEFINE_H__
#define __ATPACCEPT_MAIN_DEFINE_H__

#pragma pack(push,1)

/*
 *	消息类型定义 
 */
#define ID_MSG_ATPACCEPT_MAIN_STARTALGO	1	//向主程序发送启动算法指令,回应也用此消息
#define ID_MSG_ATPACCEPT_MAIN_ALGOEND	2	//当算法进程退出时，ATPMain向ATPACCEPT发送此消息 ATPACCEPT无需回应此消息 

#define  ID_ALGMATCHINE_DEBUGWIN32		0
#define  ID_ALGMATCHINE_RELEASEWIN32	1
#define  ID_ALGMATCHINE_DEBUGX64		2
#define  ID_ALGMATCHINE_RELEASEX64		3

/*
*启动算法的必需信息
*/
struct AtpAccept_Main_StartAlgoInfo
{
	/*
	 *	程序类型 
	 *	0:DEBUG Win32
	 *	1:RELEASE	Win32
	 *	2:DEBUG	x64
	 *	3:RELEASE x64
	 */
	int		nMachineType;			//程序类型 

	
	char	szAlgoName[64];			//算法名称
	char	szUserId[16];			//用户ID
	int		nUserConnectId;			//连接句柄
	char	cIpType;				//IP版本类型	4:IPv4 6:IPv6
	char	szUserIp[16];			//用户连接进来的IP IPv4 用串 IPv6 用字节 
	char	szUserMac[16];			//用户的Mac地址
	//int		nAlgSrvCount;		//可以负载该算法的服务器列表

	char	cAlgSvrIpType;			//IP版本类型	4:IPv4 6:IPv6
	char	szAlgSvr[16];			//负载该算法的服务器的IP IPv4 用串 IPv6 用字节 
	int		nAlgSvrServiceId;		//负载算法的服务器主程序的服务ID
};

/*
 *	负载算法的服务器信息
 */
// struct AtpAccept_Main_AlgoSvrInfo
// {
// 	char	cIpType;				//IP版本类型	4:IPv4 6:IPv6
// 	char	szAlgoSvrIp[16];		//服务器Ip地址  IPv4 用串 IPv6 用字节 
// 	unsigned int m_uPort;			//服务器端口号 算法交易主程序的端口
// };

/*
 *启动算法结果
 */
struct AtpAccept_Main_StartAlgoResult
{
	/*
	 *	程序类型 
	 *	0:DEBUG Win32
	 *	1:RELEASE	Win32
	 *	2:DEBUG	x64
	 *	3:RELEASE x64
	 */
	int		nMachineType;			//程序类型 
	char	szAlgoName[64];			//算法名称
	char	szUserId[16];			//用户ID
	int		nUserConnectId;			//连接句柄
	char	cIpType;				//IP版本类型	4:IPv4 6:IPv6
	char	szUserIp[16];			//用户连接进来的IP IPv4 用串 IPv6 用字节 
	char	szUserMac[16];			//用户的Mac地址
	int		nServiceId;				//启动成功的算法ID
	int		nResult;				//成功为0，错误时为错误值
	char	szError[256];			//错误说明
};

/*
 *	算法进程退出时
 *	ATPMain向ATPACCEPT发送此消息
 */
struct AtpAccept_Main_AlgoEnd
{
	int nAlgoServiceId;		//算法服务ID
};

#pragma pack(pop)
#endif	//__ATPACCEPT_MAIN_DEFINE_H__