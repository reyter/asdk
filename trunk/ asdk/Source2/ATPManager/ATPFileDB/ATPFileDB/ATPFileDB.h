// ATPFileDB.h : ATPFileDB DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CATPFileDBApp
// �йش���ʵ�ֵ���Ϣ������� ATPFileDB.cpp
//

class CATPFileDBApp : public CWinApp
{
public:
	CATPFileDBApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
