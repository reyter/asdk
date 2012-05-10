/**
* @Copyright 深圳市创真科技有限公司(www.hh.com.cn)
* @System	 通用通信库(Common Communication Environment Core)
* @Brief	 通用定义
* @Author	 wli
* @Date      2010-10-21
*/

#pragma once

#ifndef __CCEDEFINE_H_
#define __CCEDEFINE_H_

#ifndef _LIST_
#include <list>
using namespace std;
#endif

#ifndef _MAP_
#include <map>
using namespace std;
#endif

#ifndef _BITSET_
#include <bitset>
using namespace std;
#endif

#ifndef _ALGORITHM_
#include <algorithm>
using namespace std;
#endif


/**	
*  代理类型
*/
enum CCE_PROXYTYPE
{
		PROXYTYPE_NOPROXY=0,	//不使用代理
		PROXYTYPE_SOCKS4=1,		//SOCK4
		PROXYTYPE_SOCKS4A=2,	//SOCK4A
		PROXYTYPE_SOCKS5=3,		//SOCK5
		PROXYTYPE_HTTP11=4		//HTTP1.1
};

/**
*	代理数据
*/
struct CCE_PROXYDATA 
{
	CCE_PROXYTYPE  iProxyType;		//使用的代理类型.
	char szProxyHost[32];	//代理地址
	int  iProxyPort;		//代理端口
	char szProxyUser[32];	//代理用户名
	char szProxyPass[32];	//代理密码	
};


/**
*   连接状态 
*/
enum CCE_CONN_STATUS
{
	CCE_CONN_STATUS_OFFLINE=0,	//离线
	CCE_CONN_STATUS_ONLINE=1	//在线
};




#define CCE_CREATE_CONNECTION	(10000)	//创建连接指令.




extern "C"
{
	//CCE库日志记录函数原型.
	typedef void (CALLBACK* CCE_LOG_FUN)(const char *pLog,LPVOID lParam);
}



class CHHWPConnection;

//连接信息
struct CONNECT_INFO
{
	in_addr	addrFromOuter;		//对方外网地址.
	in_addr addrFromInner;		//对方内网地址.
	time_t	connTime;			//连接建立时间.
	__int64	sendBytes;			//发送字节数
	__int64	recvBytes;			//接收字节数
	CHHWPConnection*  pConnection;

};

//用于列表显示的结构.
struct CONNECT_INFO_SHOW
{
	char  clientAddr[64];	//客户区显示地址.
	char  connectTime[24];	//客户登录时间 YYYY-MM-DD HH:MM:SS
	__int64	sendBytes;			//发送字节数
	__int64	recvBytes;			//接收字节数
	CHHWPConnection*  pConnection;

	CONNECT_INFO_SHOW& operator=(CONNECT_INFO& info)
	{
		sprintf(clientAddr,"%d.%d.%d.%d<-%d.%d.%d.%d",
			info.addrFromOuter.S_un.S_un_b.s_b1,
			info.addrFromOuter.S_un.S_un_b.s_b2,
			info.addrFromOuter.S_un.S_un_b.s_b3,
			info.addrFromOuter.S_un.S_un_b.s_b4,
			info.addrFromInner.S_un.S_un_b.s_b1,
			info.addrFromInner.S_un.S_un_b.s_b2,
			info.addrFromInner.S_un.S_un_b.s_b3,
			info.addrFromInner.S_un.S_un_b.s_b4);	//格式化IP地址显示。

		CTime timecc(info.connTime);
		sprintf(connectTime,"%04d-%02d-%02d %02d:%02d:%02d",
			timecc.GetYear(),
			timecc.GetMonth(),
			timecc.GetDay(),
			timecc.GetHour(),
			timecc.GetMinute(),
			timecc.GetSecond());

		this->sendBytes = info.sendBytes;
		this->recvBytes = info.recvBytes;
		this->pConnection = info.pConnection;

		return *this;        
	}

};


#pragma  pack(push,8)

enum __CHANNEL_STATE_
{
	ST_OPENING,				//开启并运行
	ST_CLOSE,				//手动关闭
	ST_CANNOTCONN,			//开启但无法正常运行，需要报警	
	ST_TRYOPEN,
	ST_CANNOTOPEN,			//无法打开
	ST_UNINIT				//尚未初始化
};

struct CHANNEL_INFO_CORE
{
	char szChannelName[32];				//通道名称
	USHORT  nLocalPort;	
	CRuntimeClass* pSvrRunTimeClass;	//运行时支持信息.
	//bool bOpen;						//是否为打开状态，初始化时，是否打开，从文件加载后，是否打开。
	int nChannelStatus;
	LPVOID lParam;						//Add by wli 2010-10-26,wli

	CHANNEL_INFO_CORE()
	{
		nChannelStatus = ST_UNINIT;
	}
};
#pragma  pack(pop)


typedef struct  _tagChannelInfo
{
	int  nChannelStatus;	//状态，开启，关闭，中断(需要报警)？
	char szChanName[32];	//通道名	
	double  client2server;	//客户端到服务器字节数M
	double  server2client;	//服务器到客户端字节数M
	LPVOID	  pChannel;	//指向的数据
	INT_PTR       nConnect;
	INT_PTR		  nMaxConnect;	//最高连接数。
}HHWP_CHANNELINFO;


//CCECore lib 专用.
#ifdef _CCECORE_LIB_
extern CCE_LOG_FUN   g_pCCELogFun;
extern LPVOID		g_pCCELogParam;
extern void AppendLog(const char* pLog);
#endif 

#endif	//__CCEDEFINE_H_