
// ATPManager.h : ATPManager Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CATPManagerApp:
// �йش����ʵ�֣������ ATPManager.cpp
//

class CATPManagerApp : public CWinApp
{
public:
	CATPManagerApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CATPManagerApp theApp;
