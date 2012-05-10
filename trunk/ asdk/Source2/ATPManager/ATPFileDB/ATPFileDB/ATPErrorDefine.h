#pragma once

#define SUCCESS 0

#define NEWFAIL			17501		//new 失败
#define TIMEOUT			17502		//超时
#define NETWORKBUSY		17503		//网络忙
#define MISSDATACTRL	17504		//数据处理句柄丢失
#define MISSREQDATA		17505		//请求数据丢失


#define NEWERROR		-1			//new 错误
#define ZERORECORD		-2			//没有纪录
#define NOTINIT			-3			//内存块没初始化
#define EXISTDATA		-4			//已经存在该数据
#define EXISTGUID		-5			//已经存在该GUID
#define NULLHANDLE		-6			//句柄为空