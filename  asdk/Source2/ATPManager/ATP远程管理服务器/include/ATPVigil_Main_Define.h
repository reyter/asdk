//
// @Project:ATP3
// @Author:梁兴其
// @Date:2011-10-19
// @Description:系统监控模块和主程序通信定义
// 

#pragma once

#ifndef __ATPVIGIL_MAIN_DEFINE_H__
#define __ATPVIGIL_MAIN_DEFINE_H__

#pragma pack(push,1)

//
//之前肖总定义消息ID定义了有100和101
// 因此这里从1000开始
// 

#define ID_MSG_ATPVIGIL_MAIN_OPENSERVICE			1001		//打开服务进程
#define ID_MSG_ATPVIGIL_MAIN_TERMINATESERVICE		1002		//终止服务进程
#define ID_MSG_ATPVIGIL_MAIN_RESTARTSERVICE			1003		//重启服务进程
#define ID_MSG_ATPVIGIL_MAIN_SAVEWATCHINFO			1004		//保存服务监控信息 

/*
 *	服务的相关信息
 */
struct AtpVigil_Main_Service
{
	int nServerID;			//服务器标识，用于分布式系统中，0表示主服务器
	int nServiceClass;		//服务类别
	int nServiceID;			//服务ID
};



#pragma pack(pop)


#endif
