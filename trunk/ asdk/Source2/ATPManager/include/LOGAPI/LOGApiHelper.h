#pragma once
#ifndef _LOGAPIHELPER_H_
#define _LOGAPIHELPER_H_

/*
1、调用LOG_CreateHandler创建处理器
2、调用LOG_SetDeveloper、LOG_SetFileVersion设置开发者，版本号
3、调用LOG_OpenFile打开或者创建索引、日志文件
4、调用LOG_SetLogTimer定时把缓冲区内容写入文件
5、调用LOG_AppendLogInfoToBuffer追加到缓冲区
6、在程序退出之前调用LOG_LogProcStart把缓冲区内容写入文件(平时可以不用)

不使用时，调用LOG_KillLogTimer、LOG_CloseFile、LOG_DestroyHandler
关闭定时器、关闭文件、销毁处理器对象
*/

#include "LOGApiDefine.h"

#ifdef _LOGAPILIB
	#define LOGAPI(type) type __declspec(dllexport)
#else
	#define LOGAPI(type) type __declspec(dllimport)
#endif

#pragma  pack(push,1)

#ifdef __cplusplus
extern "C"
{
#endif


/**
*	LOG处理器句柄
*/
typedef void* HLOG;

/**
*	创建一个处理器句柄
*	@param szLogName  日志名称
*   @param pHLog	  [0ut] 输出打开的句柄.
*	@return 返回所创建的处理器
*/
LOGAPI(int) LOG_OpenLog(LPCTSTR szLogName,HLOG* pHLog);

/**
*  是否记录某一类日志.缺省不记录所有类别日志.
*  @param hLogger 日志记录句柄.
*  @param nClass  日志类别.
*  @param bEnable 是否启用.
*/
LOGAPI(int) LOG_EnableLogClass(HLOG hLogger,int nClass,bool bEnable);

/**
*  写入日志（字符串）
*  @param hLogger 日志记录句柄.
*  @param nClass  日志类别.
*  @param lpszLog 要记录日志字符串.
*/
LOGAPI(int) LOG_LogString(HLOG hLogger,int nClass,LPCTSTR lpszLog);

/**
*  写入日志（原始二进制）
*  @param hLogger 日志记录句柄.
*  @param nClass  日志类别.
*  @param pLog	  数据首地址
*  @param nLength 数据长度
*/
LOGAPI(int) LOG_LogRaw(HLOG hLogger,int nClass,const void* pLog,int nLength);


/**
*  设置写入日志缓冲大小（日志采取定时（缺省1分种）、缓冲(缺省64k)机制保存，）
*  @param hLogger 日志记录句柄.
*  @param nLogBufferSize 新缓冲大小
*  @return 返回原来的缓冲大小.
*/
LOGAPI(size_t) LOG_SetLogBufferSize(HLOG hLogger,size_t nLogBufferSize);

/**
*  设置写入日志缓冲写入间隔（日志采取定时（缺省1分种）、缓冲(缺省64k)机制保存，）
*  @param hLogger		 日志记录句柄.
*  @param dwMillSeconds  新间隔
*  @return 返回原来的间隔
*/
LOGAPI(DWORD) LOG_SetLogTimer(HLOG hLogger,DWORD dwMilliseconds);

/**
*  强制将该句柄上的缓冲写入磁盘文件。
*  @param hLogger		 日志记录句柄.
*/
LOGAPI(int) LOG_Commit(HLOG hLogger);

/**
*  关闭日志
*  @param hLogger		 日志记录句柄.
*/
LOGAPI(int) LOG_CloseLog(HLOG hLogger);

/**
* 返回错误描述.
*/
LOGAPI(LPCTSTR) LOG_GetError(int nErrorCode);

/**
* 设置字串日志观察窗口
*  WPARAM  本句柄上最大的日志序号。
*  LPARAM  NULL.
*  @param hLogger		 日志记录句柄.
*  @param hWnd			 窗口保存柄
*  @param nMessageID     消息ID.
*  @param bEnable        是否观察.
*/
LOGAPI(int)    LOG_EnableWatchWindow(HLOG hLogger,HWND hWnd,int nMessageID,bool bEnable);

/**
* 获取指定句柄上的日志记录数.
* @param hLogger 日志记录句柄.
* @param pnCount [out] 输出日志数
* @return        0 函数正常，其他为错误码.可用 LOG_GetError() 格式化.
*/
LOGAPI(int)    LOG_GetLogCount(HLOG hLogger,size_t* pnCount);

/**
* 获取指定句柄上的指定序号的日志* .
* @param hLogger 日志记录句柄.
* @param nSN 序号(从1开始).
* @param pHead [out] 输出日志相关信息.
* @param ppLog  [out] 输出日志内容， 需调用 LOG_Release(*ppLog) 释放相应的内存
* @return        0 函数正常，其他为错误码.可用 LOG_GetError() 格式化.
*/
LOGAPI(int)    LOG_GetLog(HLOG hLogger,int nSN,LogRecordHead* pHead,void** ppLog);

/**
* 释放内存
*/
LOGAPI(void)    LOG_Release(void* pData);



enum LOG_DATA_TYPE
{
	LDT_STRING =1,		//字符串char*
	LDT_BINARAY = 2		//二进字数据
};

/**
* 写日志回调原型.
*/
typedef void (CALLBACK* LOGHOOK_FUN)(HLOG /*hLogger*/,
	LOG_DATA_TYPE /*nType*/,
	int /*nClass*/,
	const void* /*pData*/,
	int /*nLength*/);

/**
* 设置写日志钩子
*/
LOGAPI(void)	LOG_SetLogHook(HLOG hLogger,LOGHOOK_FUN pHook);


#ifdef __cplusplus
}
#endif


#pragma  pack(pop)

#endif //_LOGAPIHELPER_H_