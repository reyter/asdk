// FinSmith.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFinSmithApp:
// �йش����ʵ�֣������ FinSmith.cpp
//

class CFinSmithApp : public CWinApp
{
public:
	CFinSmithApp();

// ��д
	public:
	virtual BOOL InitInstance();
    virtual BOOL ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:	
};

extern CFinSmithApp theApp;