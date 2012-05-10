// HHUpdateClient.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h”
#endif

#include "resource.h"		// 主符号


// CHHUpdateClientApp:
// 有关此类的实现，请参阅 HHUpdateClient.cpp
//

class CHHUpdateClientApp : public CWinApp
{
public:
	CHHUpdateClientApp();

// 重写
	public:
	virtual BOOL InitInstance();
	BOOL FirstInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CHHUpdateClientApp theApp;
