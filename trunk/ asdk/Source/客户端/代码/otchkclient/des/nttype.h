/*****************************************************************
 *  文件名：	nttype.h
 *  文件功能：	类型定义
 *  编程者：	Wu Qing
 *  初作时间：	2002/5/22
 *  版本: 		1.0
 *  ------------------------------
 *			时间   			 修改者		注释
 *			2002／05／22   	 Wu Qing	创建
*****************************************************************/

#ifndef _NTTYPE_H_
#define _NTTYPE_H_

typedef const char* LPCSTR;
typedef char*       LPSTR;
typedef char        TCHAR;
typedef const TCHAR*   LPCTSTR;
typedef unsigned int SOCKET;
typedef unsigned char* LPBYTE;

typedef unsigned char BYTE, *PBYTE, UCHAR;
typedef unsigned long DWORD;
typedef DWORD BOOL;
typedef unsigned int UINT;
typedef unsigned long ULONG;
typedef unsigned long* ULONG_PTR;

typedef void VOID;

#define TRUE                1
#define FALSE               0

#endif /*_NTTYPE_H_ */

