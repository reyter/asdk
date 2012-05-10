
// MainFrm.cpp : CMainFrame 类的实现
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


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
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
		//AfxMessageBox("请先设置通讯端口!");
		//exit(-1);   
	}


	HANDLE   handle;   
	handle   =   ::CreateMutex(NULL, FALSE, "ATPManagerServerMutex");   
	if(GetLastError()   ==   ERROR_ALREADY_EXISTS) 
	{   
		exit(-1);   
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	CHHAppStudioView::SetSystemParamete(0xfffe0100, 0);	//不加载系统工具、属性、用户资源管理器 窗口
	CHHAppStudioView::SetApplicationInt(ID_APPINT_HIDEMENU_RMENU, 1);	//隐藏工具栏右键菜单
	CHHAppStudioView::SetSystemParamete(0xfffe0101, 0);	//关闭系统菜单
	CHHAppStudioView::SetSystemParamete(0xfffe0102, 1);	//设置框架风格
	CHHAppStudioView::SetSystemParamete(0xfffe0103, 4);	//设置框架颜色风格
	CHHAppStudioView::SetSystemParamete(0xfffe0104, 1);	//锁定框架状态
	//CHHAppStudioView::SetSystemParamete(0xfffe0105, 1);	//不显示系统主标签
	CHHAppStudioView::SetSystemParamete(0xfffe0106, 1);	//隐藏所有工具栏
	CHHAppStudioView::SetSystemParamete(0xfffe0107, 0);	//主标题显示(0:显示在前 1:显示在后 2:不显示
	CHHAppStudioView::SetSystemParamete(0xfffe0108, 0);	//主窗口标题使用SetWindowText设置
	CHHAppStudioView::SetSystemParamete(0xfffe0109, 1);	//主窗口初始设置为隐藏
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
	CHHAppStudioView::SetSystemParamete(0xfffe0107, 0);	//主标题显示(0:显示在前 1:显示在后 2:不显示
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	//if(g_bAllProcessesTele)
	//	CHHResource::LoadDockView("通讯进程"		, "", 0, 1232, NULL, CRect(10, 16, 200, 300), RUNTIME_CLASS(CTeleProcessView), NULL, 5, 0, 0, 0, 0, 0);
	CHHResource::LoadDockView("通讯连接"		, "", 0, 1233, NULL, CRect(10, 16, 200, 300), RUNTIME_CLASS(CATPManagerServer_LinkView), NULL, 5, 0, 0, 0, 0, 0);
	//CHHResource::LoadDockView("Nsd远程监控用户"	, "", 0, 1231, NULL, CRect(10, 16, 200, 300), RUNTIME_CLASS(CNsdVigilServiceView), NULL, 5, 0, 0, 0, 0, 0);
	//CHHResource::LoadDockView("Nsd进程守护"		, "", 0, 1230, NULL, CRect(10, 16, 200, 300), RUNTIME_CLASS(CNsdVigilProcessView), NULL, 5, 0, 0, 0, 0, 0);
	//CHHDataChannelCtrl::ActiveHHView(1230);

	if(OpenUserDocument(this))
	{
		OpenNullUserDocument(this);
	}

	char chInfo[128];
	sprintf(chInfo, "ATP远程管理服务器");
	this->SetWindowText(chInfo);

	//启动监控进程
	//CHHProgramVigil::StartVigilProcess(NULL, 30);
	////结束监控进程
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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 将焦点前移到视图窗口
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{

	// 否则，执行默认处理
	return CHHMainFrame::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ShowWindow(SW_HIDE);
	//CHHMainFrame::OnClose();
}


//BOOL CMainFrame::OnQueryOpen()
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	return CHHMainFrame::OnQueryOpen();
//}


void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CHHMainFrame::OnSysCommand(nID, lParam);
	if (nID == SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);
	}

}
