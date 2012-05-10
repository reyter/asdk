
// OTCHK_Client.h : OTCHK_Client Ӧ�ó������ͷ�ļ�
//
#pragma once



#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif




#include "resource.h"       // ������
#include "Common\Log.h"
#include "Common\MultiLanguage.h"
#include "Authentication.h"
#include "Connenct\DataComm.h"
#include "Common\InProcMQ.h"

// COTCHK_ClientApp:
// �йش����ʵ�֣������ OTCHK_Client.cpp
//

class COTCHK_ClientApp : public CWinAppEx
{
public:
	COTCHK_ClientApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:	
	CAuthentication m_Authentication;
	CDataComm m_DataComm;

};

extern COTCHK_ClientApp theApp;


