// ATPNetC.h : ATPNetC DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CATPNetCApp
// �йش���ʵ�ֵ���Ϣ������� ATPNetC.cpp
//

class CATPNetCApp : public CWinApp
{
public:
	CATPNetCApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
