// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 从 Windows 头中排除极少使用的资料
#endif

// 如果您必须使用下列所指定的平台之前的平台，则修改下面的定义。
// 有关不同平台的相应值的最新信息，请参考 MSDN。 
#ifndef WINVER				// 允许使用特定于 Windows XP 或更高版本的功能。
#define WINVER 0x0501		// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

#ifndef _WIN32_WINNT		// 允许使用特定于 Windows XP 或更高版本的功能。
#define _WIN32_WINNT 0x0501	// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif						

#ifndef _WIN32_WINDOWS		// 允许使用特定于 Windows 98 或更高版本的功能。
//#define _WIN32_WINDOWS 0x0410 // 将它更改为适合 Windows Me 或更高版本的相应值。
#define _WIN32_WINDOWS 0x0501 // 将它更改为适合 Windows Me 或更高版本的相应值。
#endif

#ifndef _WIN32_IE			// 允许使用特定于 IE 6.0 或更高版本的功能。
#define _WIN32_IE 0x0600	// 将此值更改为相应的值，以适用于 IE 的其他版本。值。
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <afxsock.h>		// MFC 套接字扩展
#include <afx.h>
#include <math.h>
#include <afxhtml.h>
#include <atlimage.h>
#pragma warning(disable:4996 4018 4244 4267 4800 4311 4312)


#include "resource.h"
#include "..\\public\\XPButton.h"
#include "..\\public\\SkinManager.h"
#include "..\\public\\EditWithBack.h"
#include "..\\public\\SymbolEdit.h"
#include "..\\public\\TransparentStatic.h"
#include "..\\public\\protocol.h"
#include "..\\public\\Data_struct.h"
#include "..\\public\\rwlock.h"
#include "../public/synch.h"
#include "../public/commfunc.h"
#include "../public/commsocket.h"

//#include "..\\public\TreeCtrlEx\ThemeLib.h"
#include <gdiplus.h>
#include "TransCheckBox.h"
#include "TransRadioBox.h"


#include "..\\public\\Data.h"
#include "..\\public\\DataComm.h"
#include "config.h"
#include "svr.h"

#define WM_TRAYICON		WM_USER + 1

#define DES_KEY		"investzs"

#define MAINTITLE	_T("股权交易客户端")
#define VERNAME		_T("股权交易客户端")
#define VERSTR		_T("股权交易客户端 V1.0")
#define EXITMSG		_T("确定退出 “股权交易客户端”？")

extern CSkinManager g_SkinManager;

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
class CDlgKDetail;
class CTopDlg;
class CDlgContainer;

extern CDataComm * gpData;
extern CSkinManager *gpSkinManager;

extern	CDlgKDetail * gpKDetail;
extern	CTopDlg * gpTopDlg;	
extern	CDlgContainer * gpContainer;	
extern CCommSocket * gpCommSocket;

#define _CRTDBG_MAP_ALLOC 
#include<stdlib.h> 
#include<crtdbg.h>