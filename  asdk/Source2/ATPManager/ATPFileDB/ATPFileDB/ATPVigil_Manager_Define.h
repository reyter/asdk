//
//@Proejct:ATP3
//@Date:2011/10/12
//@Author:梁兴其
//@Description:算法交易平台管理器服务器端与运维监控服务器端通信定义
//

#pragma once
#ifndef __ATPVIGIL_MANAGER_DEFINE_H__
#define __ATPVIGIL_MANAGER_DEFINE_H__

#pragma pack(push,1)

#define ID_MSG_ATPVIGIL_MANAGER_ADMINLOGIN	1		//登录
#define ID_MSG_ATPVIGIL_MANAGER_UNCONNECT	2		//断开连接 

struct AtpVigil_Manager_UserInfo 
{
	UINT uUserId;		//管理员Id
	int nConnectId;		//连接句柄 用来标识唯一性 
	char chAccount[24];	//管理员账号
	char chStatus[40];  //状态说明
	char chInfo1[48];	//保留
	char chInfo2[48];	//保留
	int  nAppType;		//保留
	int  nAppDate;		//日期
	int nAppTime;		//时间
	int  nLocalPort;   	//服务端口
	int  nRemotePort;	//登录的端口
	int  nRemoteIP;  	//登录的IP
};

#pragma pack(pop)

#endif	//__ATPVIGIL_MANAGER_DEFINE_H__