#pragma once

#pragma once

#ifndef _ATPSVRAPI_H_
#define _ATPSVRAPI_H_




#ifdef _ATPSVRAPILIB
#define ATPSVRAPI(type)  type __declspec(dllexport) 
#else
#define ATPSVRAPI(type)  type __declspec(dllimport) 
#endif

#ifdef __cplusplus
extern "C"
{
#endif


typedef void (CALLBACK* ATPSVRAPI_LOG_FUN)(LPCTSTR,LPVOID);

/**
* 设置ATPSvr日志记录
* @param pFun 日志记录函数
* @param lParam 回调给日志记录函数的参数
*/
ATPSVRAPI(void) ATPSVRAPI_SetLogFun(ATPSVRAPI_LOG_FUN pFun,LPVOID lParam);


#ifdef __cplusplus
}
#endif


#endif //_ATPSVRAPI_H_
