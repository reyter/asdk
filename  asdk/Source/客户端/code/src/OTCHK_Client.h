
// OTCHK_Client.h : OTCHK_Client 应用程序的主头文件
//
#pragma once



#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif




#include "resource.h"       // 主符号
#include "Common\Log.h"
#include "Common\MultiLanguage.h"
#include "Authentication.h"
#include "Connenct\DataComm.h"
#include "Common\InProcMQ.h"

// COTCHK_ClientApp:
// 有关此类的实现，请参阅 OTCHK_Client.cpp
//

class COTCHK_ClientApp : public CWinAppEx
{
public:
	COTCHK_ClientApp();


// 重写
public:
	virtual BOOL InitInstance();

// 实现
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


