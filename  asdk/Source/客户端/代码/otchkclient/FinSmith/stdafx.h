// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// �� Windows ͷ���ų�����ʹ�õ�����
#endif

// ���������ʹ��������ָ����ƽ̨֮ǰ��ƽ̨�����޸�����Ķ��塣
// �йز�ͬƽ̨����Ӧֵ��������Ϣ����ο� MSDN�� 
#ifndef WINVER				// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define WINVER 0x0501		// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif

#ifndef _WIN32_WINNT		// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define _WIN32_WINNT 0x0501	// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif						

#ifndef _WIN32_WINDOWS		// ����ʹ���ض��� Windows 98 ����߰汾�Ĺ��ܡ�
//#define _WIN32_WINDOWS 0x0410 // ��������Ϊ�ʺ� Windows Me ����߰汾����Ӧֵ��
#define _WIN32_WINDOWS 0x0501 // ��������Ϊ�ʺ� Windows Me ����߰汾����Ӧֵ��
#endif

#ifndef _WIN32_IE			// ����ʹ���ض��� IE 6.0 ����߰汾�Ĺ��ܡ�
#define _WIN32_IE 0x0600	// ����ֵ����Ϊ��Ӧ��ֵ���������� IE �������汾��ֵ��
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <afxsock.h>		// MFC �׽�����չ
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

#define MAINTITLE	_T("��Ȩ���׿ͻ���")
#define VERNAME		_T("��Ȩ���׿ͻ���")
#define VERSTR		_T("��Ȩ���׿ͻ��� V1.0")
#define EXITMSG		_T("ȷ���˳� ����Ȩ���׿ͻ��ˡ���")

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