// HHUpdateClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CHHUpdateClientApp:
// �йش����ʵ�֣������ HHUpdateClient.cpp
//

class CHHUpdateClientApp : public CWinApp
{
public:
	CHHUpdateClientApp();

// ��д
	public:
	virtual BOOL InitInstance();
	BOOL FirstInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHHUpdateClientApp theApp;
