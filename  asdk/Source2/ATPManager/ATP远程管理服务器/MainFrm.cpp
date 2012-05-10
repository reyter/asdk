
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "ATPManager.h"

#include "MainFrm.h"

#include "HHNsdClientFrame.h"
#include "MenuXP.h"

#include "ATPManagerServer_LinkView.h"
#include "HHNetFrameProcessor_ATPManagerServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

HWND g_hWndMainWnd = NULL;

IMPLEMENT_DYNAMIC(CMainFrame, CHHMainFrame)
IMPLEMENT_MENUXP(CMainFrame, CHHMainFrame)

BEGIN_MESSAGE_MAP(CMainFrame, CHHMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_MENUXP_MESSAGES()
	ON_WM_CLOSE()
//	ON_WM_QUERYOPEN()
ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	g_hWndMainWnd = GetSafeHwnd();
	int nPort = 0;
	nPort =::GetPrivateProfileInt("ATPManagerConfig","port",0,".\\ATPManager.ini");
	if (nPort == 0)
	{
		::WritePrivateProfileString("ATPManagerConfig","port","9088",".\\ATPManager.ini");
		//AfxMessageBox("��������ͨѶ�˿�!");
		//exit(-1);   
	}


	HANDLE   handle;   
	handle   =   ::CreateMutex(NULL, FALSE, "ATPManagerServerMutex");   
	if(GetLastError()   ==   ERROR_ALREADY_EXISTS) 
	{   
		exit(-1);   
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	CHHAppStudioView::SetSystemParamete(0xfffe0100, 0);	//������ϵͳ���ߡ����ԡ��û���Դ������ ����
	CHHAppStudioView::SetApplicationInt(ID_APPINT_HIDEMENU_RMENU, 1);	//���ع������Ҽ��˵�
	CHHAppStudioView::SetSystemParamete(0xfffe0101, 0);	//�ر�ϵͳ�˵�
	CHHAppStudioView::SetSystemParamete(0xfffe0102, 1);	//���ÿ�ܷ��
	CHHAppStudioView::SetSystemParamete(0xfffe0103, 4);	//���ÿ����ɫ���
	CHHAppStudioView::SetSystemParamete(0xfffe0104, 1);	//�������״̬
	//CHHAppStudioView::SetSystemParamete(0xfffe0105, 1);	//����ʾϵͳ����ǩ
	CHHAppStudioView::SetSystemParamete(0xfffe0106, 1);	//�������й�����
	CHHAppStudioView::SetSystemParamete(0xfffe0107, 0);	//��������ʾ(0:��ʾ��ǰ 1:��ʾ�ں� 2:����ʾ
	CHHAppStudioView::SetSystemParamete(0xfffe0108, 0);	//�����ڱ���ʹ��SetWindowText����
	CHHAppStudioView::SetSystemParamete(0xfffe0109, 1);	//�����ڳ�ʼ����Ϊ����
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	m_bSystemStartInformationFlag = FALSE;
	BOOL bDWMEnable = CHHDataChannelCtrl::GetHHNsdSystemInformation(ID_SYSINFO_ISDWM, 0, 0);
	if(bDWMEnable)
		ModifyStyle(0, WS_OVERLAPPEDWINDOW|WS_POPUPWINDOW, 0);
	else
		ModifyStyle(WS_OVERLAPPEDWINDOW|WS_POPUPWINDOW,0/*WS_MINIMIZEBOX|WS_MAXIMIZEBOX*/, 0);
	
	if (CHHMainFrame::OnCreate(lpCreateStruct) == -1)
		return -1;

	InitilizeHHMainFrame();
	SetHHDockMainFrame();

	CHHAppStudioView::ModifyAppStudioStyle(0, ID_APPSTUDIOSTYLE_DISABLEUSERINFO);

	//Start
	char chError[256];
	HHMAINFRAME_USERDOCOUENTLIST m_UserInfo;
	memset(&m_UserInfo, 0, sizeof(m_UserInfo));
	m_UserInfo.m_bLocal = TRUE;
	strcpy_s(m_UserInfo.m_szUserName, sizeof(m_UserInfo.m_szUserName)-1, AfxGetApp()->m_pszExeName);
	CHHNsdClientFrame::CreateLocalUser(&m_UserInfo, chError);
	//CHHResource::SetWindowTranslucence(this->m_hWnd, 236);

	LoadResourceLibrarys(this);
	this->SetActiveWindow();

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	CHHAppStudioView::SetSystemParamete(0xfffe0107, 0);	//��������ʾ(0:��ʾ��ǰ 1:��ʾ�ں� 2:����ʾ
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	//if(g_bAllProcessesTele)
	//	CHHResource::LoadDockView("ͨѶ����"		, "", 0, 1232, NULL, CRect(10, 16, 200, 300), RUNTIME_CLASS(CTeleProcessView), NULL, 5, 0, 0, 0, 0, 0);
	CHHResource::LoadDockView("ͨѶ����"		, "", 0, 1233, NULL, CRect(10, 16, 200, 300), RUNTIME_CLASS(CATPManagerServer_LinkView), NULL, 5, 0, 0, 0, 0, 0);
	//CHHResource::LoadDockView("NsdԶ�̼���û�"	, "", 0, 1231, NULL, CRect(10, 16, 200, 300), RUNTIME_CLASS(CNsdVigilServiceView), NULL, 5, 0, 0, 0, 0, 0);
	//CHHResource::LoadDockView("Nsd�����ػ�"		, "", 0, 1230, NULL, CRect(10, 16, 200, 300), RUNTIME_CLASS(CNsdVigilProcessView), NULL, 5, 0, 0, 0, 0, 0);
	//CHHDataChannelCtrl::ActiveHHView(1230);

	if(OpenUserDocument(this))
	{
		OpenNullUserDocument(this);
	}

	char chInfo[128];
	sprintf(chInfo, "ATPԶ�̹��������");
	this->SetWindowText(chInfo);

	//������ؽ���
	//CHHProgramVigil::StartVigilProcess(NULL, 30);
	////������ؽ���
	//static BOOL StopVigilProcess(LPCSTR szVigilExec);
	//g_hIconNsdVigil_Small = (HICON)::LoadImage(g_hinstanceLib, MAKEINTRESOURCE(IDI_NSDVIGIL_SMALL/*IDI_ICON_APP*/), IMAGE_ICON, 0, 0, 0);
	//g_hIconNsdVigil_Big = (HICON)::LoadImage(g_hinstanceLib, MAKEINTRESOURCE(IDI_NSDVIGIL_BIG/*IDI_ICON_APP*/), IMAGE_ICON, 0, 0, 0);
	//g_hIconNsdVigil_Big	  = AfxGetApp()->LoadIcon(IDI_NSDVIGIL_BIG);
	//CHHResourceApp::SetApplicationInformation(ID_NSDAPP_ICON_SMALL, (WPARAM)g_hIconNsdVigil_Small);
	//CHHResourceApp::SetApplicationInformation(ID_NSDAPP_ICON_BIG, (WPARAM)g_hIconNsdVigil_Big);
	//char chInfo[128];


	//g_hIconNsdVigil_OK = (HICON)::LoadImage(g_hinstanceLib, MAKEINTRESOURCE(IDI_ICON_OK/*IDI_ICON_APP*/), IMAGE_ICON, 0, 0, 0);
	//g_hIconNsdVigil_Sleep = (HICON)::LoadImage(g_hinstanceLib, MAKEINTRESOURCE(IDI_ICON_SLEEP/*IDI_ICON_APP*/), IMAGE_ICON, 0, 0, 0);
	//g_hIconNsdVigil_Error = (HICON)::LoadImage(g_hinstanceLib, MAKEINTRESOURCE(IDI_ICON_ERROR/*IDI_ICON_APP*/), IMAGE_ICON, 0, 0, 0);
	//ActiveHHView(1233);
	//ShowWindow(SW_HIDE);
	return 0;
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{

	if( !CHHMainFrame::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CHHMainFrame::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CHHMainFrame::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// ������ǰ�Ƶ���ͼ����
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{

	// ����ִ��Ĭ�ϴ���
	return CHHMainFrame::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ShowWindow(SW_HIDE);
	//CHHMainFrame::OnClose();
}


//BOOL CMainFrame::OnQueryOpen()
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	return CHHMainFrame::OnQueryOpen();
//}


void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CHHMainFrame::OnSysCommand(nID, lParam);
	if (nID == SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);
	}

}
