// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE ��
#include <afxodlgs.h>       // MFC OLE �Ի�����
#include <afxdisp.h>        // MFC �Զ�����
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC ���ݿ���
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO ���ݿ���
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afx.h>
#include <direct.h>

#include "menuxp.h"
#include "hhfc_datatypedefine.h"
#include "HHToolBar.h"
#include "hhdatachannelctrl.h"

#define _ATPFILEDBAPI_



#define NEWERROR		-1			//new ����
#define ZERORECORD		-2			//û�м�¼
#define NOTINIT			-3			//�ڴ��û��ʼ��
#define EXISTDATA		-4			//�Ѿ����ڸ�����
#define EXISTGUID		-5			//�Ѿ����ڸ�GUID
#define NULLHANDLE		-6			//���Ϊ��

#pragma warning(disable :4996 4018)
#include "ATPACCEPT_MANAGER_DEFINE.H"
#include "ATPManagerDefine.h"