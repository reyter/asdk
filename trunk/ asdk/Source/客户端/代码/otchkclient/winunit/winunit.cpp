// winunit.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "winunit.h"
#include "WinF10.h"
#include "DlgChgStk.h"
#include "DlgSort.h"
#include "DlgOrgTrade.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//


// CwinunitApp

BEGIN_MESSAGE_MAP(CwinunitApp, CWinApp)
END_MESSAGE_MAP()


// CwinunitApp 构造

CwinunitApp::CwinunitApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CwinunitApp 对象

CwinunitApp theApp;


// CwinunitApp 初始化

BOOL CwinunitApp::InitInstance()
{
	CWinApp::InitInstance();
	AfxEnableControlContainer();
	/*
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}*/
	::CoInitialize(NULL);
	return TRUE;
}

void CwinunitApp::OnFinalRelease()
{
	// TODO: 在此添加专用代码和/或调用基类
	::CoUninitialize();
	CWinApp::OnFinalRelease();
}

IUserWin  * CreateUserWin(int c_nKind,CWnd * c_pParent)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
/*
	if (c_nKind == SUBF10)
	{
		CWinF10 * pWin = new CWinF10();
		pWin->CreateSelf(CWnd::FromHandle(c_pParent->m_hWnd));
		pWin->SetTitle(SUBF10_TITLE);
		return pWin;
	}
	else
	if (c_nKind == SUBCHANGESTOCK)
	{
		CDlgChgStk * pChg = new CDlgChgStk();
		pChg->Create(IDD_DLG_CHANGE_STOCK,c_pParent);
		pChg->SetTitle(SUBCHANGESTOCK_TITLE);	
		return pChg;
	}
	else
	if (c_nKind == SUBCOLLECTSORT)
	{
		CDlgSort * pSort = new CDlgSort();
		pSort->Create(IDD_DLG_SORT,c_pParent);
		pSort->SetTitle(SUBCOLLECTSORT_TITLE);
		return pSort;
	}
	else
	if (c_nKind = SUBORGTRADE)
	{
		CDlgOrgTrade * pDlg = new CDlgOrgTrade();
		pDlg->Create(IDD_DLG_ORGTRADE,c_pParent);
		pDlg->SetTitle(SUBORGTRADE_TITLE);
		return pDlg;
	}*/
	return NULL;
}

void DeleteUserWin(IUserWin * c_i)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	delete c_i->GetWnd();
}

void UserWinSetData(CData * c_pData,CGroupManager *c_pGroupManager,CSkinManager * c_pSkinManager)
{
	gpData = c_pData;
	gpGroupManager = c_pGroupManager;
	gpSkinManager = c_pSkinManager;
}

void SetAppFunc(_SendFunc c_pFunc,_GetStockDatasFunc c_pGetStockDatasFunc)
{
	gpSendFunc = c_pFunc;
	gpGetStockDatasFunc = c_pGetStockDatasFunc;
}