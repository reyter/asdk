// HHUpdateServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CHHUpdateServerApp:
// �йش����ʵ�֣������ HHUpdateServer.cpp
//

class CHHUpdateServerApp : public CWinApp
{
public:
	CHHUpdateServerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHHUpdateServerApp theApp;
