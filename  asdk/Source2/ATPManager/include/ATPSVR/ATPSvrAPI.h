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
* ����ATPSvr��־��¼
* @param pFun ��־��¼����
* @param lParam �ص�����־��¼�����Ĳ���
*/
ATPSVRAPI(void) ATPSVRAPI_SetLogFun(ATPSVRAPI_LOG_FUN pFun,LPVOID lParam);


#ifdef __cplusplus
}
#endif


#endif //_ATPSVRAPI_H_
