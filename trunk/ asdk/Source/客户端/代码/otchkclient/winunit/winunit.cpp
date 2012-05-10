// winunit.cpp : ���� DLL �ĳ�ʼ�����̡�
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
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//


// CwinunitApp

BEGIN_MESSAGE_MAP(CwinunitApp, CWinApp)
END_MESSAGE_MAP()


// CwinunitApp ����

CwinunitApp::CwinunitApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CwinunitApp ����

CwinunitApp theApp;


// CwinunitApp ��ʼ��

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
	// TODO: �ڴ����ר�ô����/����û���
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