// winunit.h : winunit DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CwinunitApp
// �йش���ʵ�ֵ���Ϣ������� winunit.cpp
//

class CwinunitApp : public CWinApp
{
public:
	CwinunitApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual void OnFinalRelease();
};
