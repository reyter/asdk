//
// @project:atp3
// @author:梁兴其
// @date:2011/9/8
// @description:定义ATPACCEPT与监控系统之间的通信协议
//
// 

#pragma once
#ifndef __ATPACCEPT_MC_DEFINE_H__
#define __ATPACCEPT_MC_DEFINE_H__

#pragma pack(push,1)

#define ID_MSG_ATPACCEPT_MC_USERLOGIN	1		//用户登录
#define ID_MSG_ATPACCEPT_MC_UNCONNECT	2		//断开连接 

struct AtpAccept_Mc_UserInfo 
{
	UINT uUserId;		//用户Id
	int nConnectId;		//连接句柄 用来标识唯一性 
	char chAccount[24];//账号
	char chStatus[40];  //状态
	char chInfo1[48];
	char chInfo2[48];
	int  nAppType;
	int  nAppDate;
	int  nAppTime;
	//下面三个必须在一起, 要排序
	int  nLocalPort;   //本地端口
	int  nRemotePort;//远程端口
	int  nRemoteIP;  //远程IP

	__int64 GetId()
	{
		return nConnectId;		//为了泛型 
	}
};

#pragma pack(pop)

#endif	//__ATPACCEPT_MC_DEFINE_H__