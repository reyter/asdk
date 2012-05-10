#pragma once


#include <string>
#include <vector>
#include <io.h>
#include <boost\checked_delete.hpp>
#include <locale>
#include <atlstr.h>
#include <Windows.h>


	//获取应用程序当前路径
	CString GetAppPath(void);

	//就否存在文件
	BOOL IsFileExists(const wchar_t* pszFile );

	//获取操作系统版本
	CString GetOSVersion(void);

	//获取操作系统语言
	CString GetOSLocale(void);


