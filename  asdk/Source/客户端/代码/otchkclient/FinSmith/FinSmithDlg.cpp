// FinSmithDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <AFXINET.H>
#include <tlhelp32.h> //声明快照函数文件
#include "CWebBrowser.h"
#include "FinSmith.h"
#include "FinSmithDlg.h"
#include "../public/CommSocket.h"
#include "TopDlg.h"
#include "../public/ShortSocket.h"
//#include "Log.h"
#include "StockWnd.h"
#include "NewsWnd.h"
#include "DlgLogin.h"
#include "CommThread.h"
#include "DlgTrade.h"
#include "myhtmlview.h"
#include "dlgdiagnose.h"
#include "Pics.h"
#include "picWnd.h"
#include "rightWnd.h"
#include "DlgList.h"
#include "DownThread.h"
#include "DlgChgPwd.h"
#include "DlgKDetail.h"
#include "DlgTechDesc.h"
#include "..//zip//zlib.h"
#include "charts.h"
#include "DlgContainer.h"
#include "afxwin.h"
#include "LoopWnd.h"
#include "DlgSetFont.h"
#include "../public/CustomMenu.h"

#define QFSET(F, B) ((F)[((B)/32)] |= (1 << ((B)%32)))
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	HICON m_hIcon;
	CStatic m_stVer;
	CStatic m_stIcon;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VER, m_stVer);
	DDX_Control(pDX, IDC_STATIC_ICON, m_stIcon);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CFinSmithDlg 对话框

CFinSmithDlg::CFinSmithDlg(CWnd* pParent /*=NULL*/)
: CDialog(CFinSmithDlg::IDD, pParent)
{	
	gpKDetail = NULL;
	gpTopDlg = NULL;
	gpContainer = NULL;

	m_bTryConnecting = false;
	m_bSize = false;
	m_bZoom = false;
	m_nEdge = 0;
	m_nHeadHeight = 24;
	
	m_hIcon = (HICON)::LoadImage(0,_T("logo.ico"),IMAGE_ICON,32,32,LR_LOADFROMFILE);
	m_hIconFail = (HICON)::LoadImage(0,_T("neterror.ico"),IMAGE_ICON,32,32,LR_LOADFROMFILE);
	if (!m_hIcon)
		m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	if (!m_hIconFail)
		m_hIconFail = AfxGetApp()->LoadIcon(IDI_ICON1);

	//HINSTANCE hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDR_MAINFRAME),RT_GROUP_ICON);
	//m_hIcon = (HICON)::LoadImage(hInstResource,MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 32, 32, 0);
	//m_hIcon = LoadImage(0,_T("logo.ico"),IMAGE_ICON,32,32,LR_LOADFROMFILE);

	m_bIcon = true;
	m_bFirstShow = true;
	m_bleft = false;

	b_front = false;
	m_pDiagnose = NULL;
	
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN);   
	int nFullHeight = GetSystemMetrics(SM_CYSCREEN);

	m_nLeftSideWidth = 266;
	m_nRightSideWidth = nFullWidth - m_nLeftSideWidth - 40;
	m_nViewMode = 1;

	m_pCollectSort = NULL;
	m_pOrgTrade = NULL;
/*
	if (gRealTech.LoadDll() == false)
	{
		MessageBox(_T("LoadDll() Fail"));
	}*/
}

CFinSmithDlg::~CFinSmithDlg()
{
	//added by wangchao 2009-07-03
	//原因：修正退出时的内存泄漏
	if (m_pTopDlg != NULL)
	{
		m_pTopDlg->DestroyWindow();
		delete m_pTopDlg;
		m_pTopDlg = NULL;
	}
	//////////////////////////////////////////////////////////////////////////

	//if (m_pLoopWnd)
	//	delete m_pLoopWnd;
}
void CFinSmithDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_MIN, m_btnMin);
	DDX_Control(pDX, IDC_BTN_MAX, m_btnMax);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btnClose);
}

BEGIN_MESSAGE_MAP(CFinSmithDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_TRAYICON,OnTrayNotify)
	ON_MESSAGE(WM_UPDATE_QUOTEDATA,OnUpdateQuoteData)
	ON_MESSAGE(WM_REQUEST_INFO,OnRequestInfo)
	ON_MESSAGE(WM_GROUP_CHANGED,OnGroupChanged)
	ON_MESSAGE(WM_UPDATE_NEWSSET,OnUpdateNewsSet)
	ON_MESSAGE(WM_SET_INFO_CLOSE, SetInfoClose)	
	ON_MESSAGE(WM_CONNECT_SUCCESS,OnConnectSuccess)
	ON_MESSAGE(WM_SHOW_NEWS,OnShowNews)
	ON_MESSAGE(WM_GET_NEWSWND,OnGetNewsWnd)
	ON_MESSAGE(WM_GOTO_STOCK,OnGotoStock)
	ON_MESSAGE(WM_EXTRA_COMMAND,OnExtraCommand)	
	ON_MESSAGE(WM_SWITCH_PIC_TYPE,OnSwitchPicType)
	ON_MESSAGE(WM_LOG,OnLog)
	ON_WM_TIMER()
	ON_WM_DESTROY()	
	ON_COMMAND(ID_ABOUT, &CFinSmithDlg::OnAbout)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZING()
	ON_COMMAND(ID_QUIT, &CFinSmithDlg::OnQuit)
	ON_WM_MOVE()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_FORCE_QUIT,OnForceQuit)
	ON_WM_MOVING()
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CFinSmithDlg::OnBnClickedBtnClose)		
	ON_BN_CLICKED(IDC_BTN_INDUSTRYDOWN, &CFinSmithDlg::OnBnClickedBtnIndustrydown)
	ON_BN_CLICKED(IDC_BTN_INDUSTRYUP, &CFinSmithDlg::OnBnClickedBtnIndustryup)
	ON_BN_CLICKED(IDC_BTN_MARKET, &CFinSmithDlg::OnBnClickedBtnMarket)
	ON_BN_CLICKED(IDC_BTN_MIN, &CFinSmithDlg::OnBnClickedBtnMin)
	ON_BN_CLICKED(IDC_BTN_MAX, &CFinSmithDlg::OnBnClickedBtnMax)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_TECH, &CFinSmithDlg::OnBnClickedBtnTech)
	ON_WM_ACTIVATE()
	ON_WM_ACTIVATEAPP()
	ON_WM_NCACTIVATE()
	ON_COMMAND(ID_TECH_RSI, &CFinSmithDlg::OnTechRsi)
	ON_COMMAND(ID_TECH_KDJ, &CFinSmithDlg::OnTechKdj)
	ON_COMMAND(ID_TECH_MACD, &CFinSmithDlg::OnTechMacd)
	ON_COMMAND(ID_TECH_BOLL, &CFinSmithDlg::OnTechBoll)
	ON_COMMAND(ID_TECH_GB, &CFinSmithDlg::OnTechGb)
	ON_COMMAND(ID_TECH_MA, &CFinSmithDlg::OnTechMa)
	ON_COMMAND(ID_TECH_DAY, &CFinSmithDlg::OnTechDay)
	ON_COMMAND(ID_TECH_WEEK, &CFinSmithDlg::OnTechWeek)
	ON_COMMAND(ID_TECH_MONTH, &CFinSmithDlg::OnTechMonth)
	ON_COMMAND(ID_SKIN_BLACK, &CFinSmithDlg::OnSkinBlack)
	ON_COMMAND(ID_SKIN_WHITE, &CFinSmithDlg::OnSkinWhite)
	ON_COMMAND(ID_HOMEPAGE, &CFinSmithDlg::OnHomepage)
	ON_COMMAND(ID_BOARD, &CFinSmithDlg::OnBoard)
	ON_WM_NCLBUTTONUP()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCRBUTTONUP()
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_CHANGEPASSWORD, &CFinSmithDlg::OnChangepassword)
	ON_COMMAND(ID_LIC, &CFinSmithDlg::OnLic)
	ON_COMMAND(ID_TECH_EMA, &CFinSmithDlg::OnTechEma)
	ON_COMMAND(ID_TECH_VOLUME, &CFinSmithDlg::OnTechVolume)
	ON_COMMAND(ID_CYCLE_MIN_1, &CFinSmithDlg::OnCycleMin1)
	ON_COMMAND(ID_CYCLE_MIN_5, &CFinSmithDlg::OnCycleMin5)
	ON_COMMAND(ID_CYCLE_MIN_15, &CFinSmithDlg::OnCycleMin15)
	ON_COMMAND(ID_CYCLE_MIN_30, &CFinSmithDlg::OnCycleMin30)
	ON_COMMAND(ID_CYCLE_MIN_60, &CFinSmithDlg::OnCycleMin60)
	ON_COMMAND(ID_VIR_TRADE, &CFinSmithDlg::OnVirTrade)
	ON_COMMAND(ID_MANUAL_BOOK, &CFinSmithDlg::OnManualBook)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_MENU_SET_FONT, &CFinSmithDlg::OnMenuSetFont)
	ON_WM_CREATE()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	END_MESSAGE_MAP()


// CFinSmithDlg 消息处理程序

BOOL CFinSmithDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	//ASSERT((IDM_SETTOP & 0xFFF0) == IDM_SETTOP);
	//ASSERT(IDM_SETTOP < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{            
			pSysMenu->AppendMenu(MF_SEPARATOR);  
			//pSysMenu->AppendMenu(MF_STRING, IDM_SETTOP, "始终保持在其他窗口前端");
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);

		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	//消除任务栏显示 
	//LONG style = ::GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE); //获得窗体扩展风格 
	//style &= ~WS_EX_APPWINDOW; //取消WS_EX_APPWINDOW 
	//style |= WS_EX_TOOLWINDOW;
	//::SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, style); //设置窗体扩展风格 
	//MessageBox("2");

	//m_pMove = new CMoveWnd(1);
	//m_pMove->Create(NULL,NULL,WS_CHILD|WS_VISIBLE,CRect(),this,0);

	m_pLoopWnd = new CLoopWnd();
	//m_pLoopWnd->CreateEx(WS_EX_TOPMOST,NULL,_T("网络连接"),WS_OVERLAPPED,CRect(100,100,160,100),NULL,0);
	m_pLoopWnd->Create(NULL,_T("网络连接"),WS_CHILD,CRect(100,100,160,100),this,NULL);
	//m_pLoopWnd->SetParent(this);
	m_pLoopWnd->MoveWindow(100,100,160,100);
	m_pLoopWnd->ShowWindow(SW_HIDE);

	gpData->SetNotifyHwnd(this->GetSafeHwnd());
	
	m_pTopDlg = new CTopDlg();
	m_pTopDlg->Create(IDD_TOP,this);	
	m_pTopDlg->SetLinkEdit(NULL,gpData,0);
	gpTopDlg = m_pTopDlg;

	//m_pWndAlert = NULL;
///- HBITMAP hNormal,hChange;

	SetWindowText(VERNAME);

	m_btnClose.SetWindowText(_T(""));
	m_btnClose.SetBorder(false);	
	m_btnClose.SetBtnBMP(gpSkinManager->GetBitmap(ID_HEAD_CLOSE),gpSkinManager->GetBitmap(ID_HEAD_CLOSE_CHANGE));

	m_btnMax.SetWindowText(_T(""));
	m_btnMax.SetBorder(false);
	m_btnMax.SetBtnBMP(gpSkinManager->GetBitmap(ID_HEAD_MAX),gpSkinManager->GetBitmap(ID_HEAD_MAX_CHANGE));
	m_btnMin.SetWindowText(_T(""));
	m_btnMin.SetBorder(false);	
	m_btnMin.SetBtnBMP(gpSkinManager->GetBitmap(ID_HEAD_MIN),gpSkinManager->GetBitmap(ID_HEAD_MIN_CHANGE));

	m_menu.SetTextFont(gpSkinManager->GetMenuFont());

	m_menu.AddMenu(_T("技术分析"),IDR_MENU_TECH);
		
	m_menu.AddMenu(_T("交易"),IDR_MENU_TRADE);

	m_menu.AddMenu(_T("帮助"),IDR_MENU_HELP);
	
	m_trayIcon.cbSize = sizeof(NOTIFYICONDATA);
	m_trayIcon.hIcon = m_hIcon;
	m_trayIcon.hWnd = m_hWnd;

	m_trayIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	m_trayIcon.uCallbackMessage = WM_TRAYICON;
	CString str;
	str = VERNAME;
	lstrcpy(m_trayIcon.szTip,str.GetBuffer());
	str.ReleaseBuffer();

	str.ReleaseBuffer();
	Shell_NotifyIcon(NIM_ADD, &m_trayIcon);
	str = MAINTITLE;
	lstrcpy(m_trayIcon.szInfo,str.GetBuffer());
	str.ReleaseBuffer();

	str = VERSTR;
	lstrcpy(m_trayIcon.szInfoTitle,str.GetBuffer());
	str.ReleaseBuffer();

	//::AnimateWindow(GetSafeHwnd(),500,AW_HOR_NEGATIVE);	
	
	SetTimer(101,1000 * 10,NULL);//检查心跳
	SetTimer(102,1000 * 10,NULL);//线路检测
	SetTimer(104,1000 * 30,NULL);//取名称
	SetTimer(110,1000 * 6,NULL);//取行情
	SetTimer(111,1000 * 12,NULL);//取行业统计数据

	if (gpData->m_nLiveDay < 10)
		SetTimer(105,1000 * 60 * 10,NULL);

	int nLen;
	if (gpCommSocket == NULL)
	{
		CDlgLogin log;
		log.CreateConnect(1);
		if (gpCommSocket && gpCommSocket->m_socket != INVALID_SOCKET)
		{
			if (gpData->m_vpStocks.size() == 0)
			{
				char acReq[1024];
				nLen = gpData->MakeInitReq(acReq);
				gpCommSocket->SendData(acReq,nLen);
			}
		}
	}
	m_pKDetail = new CDlgKDetail();
	m_pKDetail->Create(IDD_K_DETAIL);
	gpKDetail = m_pKDetail;
	if (gpData->m_dwRole & ROLE_LEDS_HIST)
		m_pKDetail->MoveWindow(0,0,140,16*13);
	else
		m_pKDetail->MoveWindow(0,0,140,16*12);
	m_pKDetail->SetWindowText(_T(""));

	int     nFullWidth;
	int     nFullHeight;
	CRect   rect,rectWin;

	nFullWidth = GetSystemMetrics(SM_CXSCREEN);   
	nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	CRect rcWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcWorkArea,0);

	rect.right = rcWorkArea.right - 4;
	rect.bottom = rcWorkArea.bottom - 4;
	rect.left = rect.right - 240;
	rect.top = rect.bottom - 388;

	m_pDiagnose = new CDlgDiagnose(this);
	m_pDiagnose->Create(IDD_STOCKDIAGNOSE);
	m_pDiagnose->SetTopDlg(m_pTopDlg);
	m_pDiagnose->SetStockCode(_T("000001.SH"));
	
	//m_pDlgGroup->GetStockNews(NULL,0,NULL,0,true);	
	SetViewMode(1);
	::AfxGetApp()->m_pMainWnd = this;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFinSmithDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
		if (nID == SC_MINIMIZE || nID == SC_CLOSE)
		{
			if (nID == SC_MINIMIZE)
				ShowWindow(SW_MINIMIZE);
			else
				ShowWindow(SW_HIDE);
		}
		if (nID == SC_RESTORE)
		{
			//ShowWindow(SW_RESTORE);
		}
		else
		{
			CDialog::OnSysCommand(nID, lParam);
		}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFinSmithDlg::OnPaint()
{
	if (IsIconic())
	{/*
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);*/
	}
	else
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		CRect cRect;
		GetWindowRect(&cRect); 
		/*
		CRgn   wndRgn; 
		CBrush br(RGB(0,0,0));
		wndRgn.CreateRoundRectRgn(0,   0,   cRect.Width(),   cRect.Height(),16,16); 
		dc.FillRgn(&wndRgn,&br); 
		SetWindowRgn(wndRgn,TRUE); 
		wndRgn.DeleteObject();*/
		//OnEraseBkgnd(&dc);
		//CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CFinSmithDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFinSmithDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_btnMax)
	{		
		SetLayout();
		Invalidate(1);
	}
}

void CFinSmithDlg::SetLayout()
{
	CSize size;

	if (!m_pDiagnose)
		return;
	int nMenuHeight = gpSkinManager->GetFontHeight(gpSkinManager->GetMenuFont());

	size = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(ID_HEAD_BACK));
	if (size.cy > 0)
		m_nHeadHeight = size.cy;

	m_nHeadHeight = 24 + nMenuHeight - 17;
	if (m_nHeadHeight < 24)
		m_nHeadHeight = 24;

	m_nLeftSideWidth = gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("123456789012345678901234567890"));
	int nMin = gpSkinManager->GetFontWidth(gpSkinManager->GetButtonFont(),_T("龙虎榜股强势好股")) + 160;
	if (m_nLeftSideWidth < nMin)
		m_nLeftSideWidth = nMin;
	if (m_nLeftSideWidth < 268)
		m_nLeftSideWidth = 268;

	m_nRightSideWidth = GetSystemMetrics(SM_CXSCREEN) - m_nLeftSideWidth - 40;

	CRect rectClient;
	GetClientRect(rectClient);
	CRect rect;
	rect = rectClient;
	rect.right -= 12;
	size = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(ID_HEAD_CLOSE));
	rect.left = rect.right - size.cx;
	rect.top += (m_nHeadHeight - size.cy)/2;
	rect.bottom = rect.top + size.cy;
	m_btnClose.MoveWindow(rect);

	size = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(ID_HEAD_MAX));
	rect.right = rect.left;
	rect.left = rect.right - size.cx;

	m_btnMax.MoveWindow(rect);

	size = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(ID_HEAD_MIN));
	rect.right = rect.left;
	rect.left = rect.right - size.cx;
	m_btnMin.MoveWindow(rect);

	size = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(ID_HEAD_LEFT));
	rect = rectClient;
	rect.left += size.cx;//130;//260;根据图形长度判定
	rect.right = rect.left + 58;
	rect.top = (24 - 16)/2;
	rect.bottom = rect.top + 16;	
		
	GetClientRect(rectClient);

	rect = rectClient;
	rect.top += m_nHeadHeight;		
	if (m_pDiagnose)
	{
		m_pDiagnose->MoveWindow(rect);			
	}

	CRect rw,r;
	
	if (m_pTopDlg)
	{
		m_pTopDlg->GetWindowRect(&rw);
		r.top = rect.top + 20;
		r.left = rect.left + 2;
		r.bottom = r.top + rw.Height();
		r.right = r.left + rect.Width();
		m_pTopDlg->MoveWindow(r);
	}

}
BOOL CFinSmithDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rectClient;
	GetClientRect(rectClient);
	CRect rect = rectClient;

	rect = rectClient;
	gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(ID_DRAG_VERT_BACK),pDC,rect);

	rect.left += m_nEdge;
	rect.top += m_nEdge;
	rect.bottom = m_nHeadHeight + m_nEdge;
	rect.right -= m_nEdge + 1;

	CSize size;
	gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(ID_HEAD_BACK),pDC,CRect(rect.left,rect.top,rect.right,rect.bottom));
	gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(ID_HEAD_RIGHT),pDC,CRect(rect.right-12,rect.top,rect.right,rect.bottom));

	size = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(ID_HEAD_LEFT));

	int nTextW = gpSkinManager->GetFontWidth(gpSkinManager->m_pFontThick,MAINTITLE);
	int nFontHeight = gpSkinManager->GetFontHeight(gpSkinManager->m_pFontThick);
	int nTitleW = size.cx;
	float fW = 1;

	int nIconW = 16;

	if (nFontHeight > 18)
		fW = float(nFontHeight) /17;

	nIconW = int(fW * 16);
		
	if (nIconW > rect.bottom - 6)
		nIconW = rect.bottom - 6;
	nTitleW = nTextW + nIconW + 6 + 4;		

	CDC SourceDC;
	CBitmap bitmap,*pOldBitmap;
	bitmap.CreateCompatibleBitmap(pDC,nTitleW + size.cx - 98,rect.Height());
	SourceDC.CreateCompatibleDC(pDC);//生成兼容的CDC
	pOldBitmap = SourceDC.SelectObject(&bitmap);

	gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(ID_HEAD_LEFT),&SourceDC,CRect(0,0,size.cx-98,size.cy),CRect(0,0,nTitleW,rect.Height()));
	gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(ID_HEAD_LEFT),&SourceDC,CRect(98,0,size.cx,size.cy),CRect(nTitleW,0,nTitleW + size.cx-98,rect.Height()));
	::DrawIconEx(SourceDC.GetSafeHdc(),6,(rect.bottom - nIconW) /2,m_hIcon,nIconW,nIconW,0,0,DI_NORMAL);
	
	int nOldMode = SourceDC.SetBkMode(TRANSPARENT);

	CRect rectText;
	rectText.left = m_nEdge + 6 + 4 + nIconW;
	rectText.right = nTitleW + size.cx - 98;
	rectText.top = m_nEdge;
	rectText.bottom = rect.bottom - m_nEdge;

	COLORREF oldCl = SourceDC.SetTextColor(gpSkinManager->getColor(MAINTITLECOLOR));

	CFont * pFont = SourceDC.SelectObject(gpSkinManager->m_pFontThick);

	SourceDC.DrawText(MAINTITLE,rectText,DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	SourceDC.SetTextColor(oldCl);
	SourceDC.SelectObject(pFont);	

	pDC->StretchBlt(rect.left,rect.top,rect.left+nTitleW + size.cx - 98,rect.bottom,&SourceDC,0,0,nTitleW + size.cx - 98,rect.Height(),SRCCOPY);
	
	SourceDC.SetBkMode(nOldMode);
	SourceDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();	
	SourceDC.DeleteDC();	

	nOldMode = pDC->SetBkMode(TRANSPARENT);

	m_menu.SetArea(CRect(rect.left + nTitleW + size.cx - 98,rect.top,rectClient.right - 106,rect.bottom));
	m_menu.SetDistance(8);
	m_menu.SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));
	m_menu.Draw(pDC);

	rect = rectClient;
	rect.top = rect.bottom - 18;
	pDC->FillRect(rect,&(CBrush(0xBCBCBC)));
	return true;
	return CDialog::OnEraseBkgnd(pDC);
}

void CFinSmithDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect  rect;
	GetClientRect(rect);
	m_ptSize = point;
	/*
	if (point.x < rect.left + 4)
	{
		SetCapture();
		m_bSize = true;
		m_nSizeKind = HTLEFT;
		return;
	}
	if (point.x > rect.right - 4)
	{
		m_bSize = true;
		m_nSizeKind = HTRIGHT;
		SetCapture();
		return;
	}
	if (point.y < rect.top + 4)
	{
		SetCapture();
		m_bSize = true;
		m_nSizeKind = HTTOP;
		return;
	}
	if (point.y > rect.bottom - 4)
	{
		m_bSize = true;
		m_nSizeKind = HTBOTTOM;
		SetCapture();
		return;
	}
	*/
	if (!m_bZoom)
	{
		SendMessage(WM_NCLBUTTONDOWN,   HTCAPTION,   MAKELPARAM(point.x,   point.y));   
		PostMessage(WM_LBUTTONUP,   NULL,   MAKELPARAM(point.x,   point.y));   
	}
	CDialog::OnLButtonDown(nFlags, point);
}


LRESULT CFinSmithDlg::SetInfoClose(WPARAM wParam,LPARAM lParam)
{
	return 0;
}

LRESULT CFinSmithDlg::OnRequestInfo(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CFinSmithDlg::OnUpdateQuoteData(WPARAM wParam, LPARAM lParam)
{
	if (wParam == -1 && lParam == -1)
	{
		MessageBox(_T("文件操作失败！\r\n请检查磁盘空间或请确认在安装目录有写的权限！"),_T("警告"),MB_OK + MB_ICONERROR);
		return 0;
	}
	if (wParam == USERDEFREPORTDATA && lParam == 200)//更新行情数据
	{
		FreshUserDefReport();
		return 0;
	}

	if (wParam == REPORTDATA && lParam == 101)//开盘
	{
		//清除缓存数据
		DeleteTmpFile(gpData->m_acDataPath);
		//下载新闻		
		CDownThread * pThread=   new   CDownThread();		
		pThread->m_pLogin = NULL;
		pThread->CreateThread(CREATE_SUSPENDED);   
		pThread->SetThreadPriority(THREAD_PRIORITY_HIGHEST);//THREAD_PRIORITY_NORMAL);   
		pThread->m_bAutoDelete   =   TRUE; //   自动删除线程   	
		pThread->ResumeThread();

		//交易备忘		
		//下载初始化数据
		return 0;
	}

	if (wParam == REPORTDATA && lParam == 102)//取新闻
	{
		m_pDiagnose->Invalidate();				
	}

	if (wParam == REPORTDATA || wParam == REALMINSDATA || wParam == TRACEDATA || wParam == USERDEFREPORTDATA)
	{
		if (m_pDiagnose)
			m_pDiagnose->FreshData(lParam);
	}
	
	return 0;
}

LRESULT CFinSmithDlg::OnGroupChanged(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CFinSmithDlg::OnUpdateNewsSet(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CFinSmithDlg::OnConnectSuccess(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0 && lParam == 100)
	{
#ifdef CCTV_TV
#else
		if (m_pLoopWnd)
			m_pLoopWnd->Begin(_T("重连服务器 "));
#endif
		return 0;
	}
	if(lParam == 0)
	{
		m_trayIcon.hIcon = m_hIconFail;
		m_bIcon = false;
	}
	else
	{
		m_pLoopWnd->End();
		m_trayIcon.hIcon = m_hIcon;
		m_bIcon = true;
	}
	Shell_NotifyIcon(NIM_MODIFY, &m_trayIcon);
	m_pDiagnose->OnConnectSuccess();
	return 0;
}

LRESULT CFinSmithDlg::OnForceQuit(WPARAM wParam, LPARAM lParam)
{//强制退出
	KillTimer(101);
	KillTimer(102);	
	KillTimer(104);
	gpCommSocket->Disconnect();
	//MessageBox(_T("用户已经在其他地方登录，本程序将退出！"),_T("提示"),MB_OK || MB_ICONWARNING);

	CDlgTechDesc dlg;
	dlg.SetTitle(_T("帐号异常提示"));
	dlg.DoModal();

	Shell_NotifyIcon(NIM_DELETE, &m_trayIcon);
	OnCancel();
	return 0;
}

LRESULT CFinSmithDlg::OnSwitchPicType(WPARAM wParam, LPARAM lParam)
{
	if (m_pDiagnose)
	{
		m_pDiagnose->m_pPics->m_pPicWnd->KeyOperate(VK_F5);
	}
	return 0;
}

LRESULT CFinSmithDlg::OnExtraCommand(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CFinSmithDlg::OnGotoStock(WPARAM wParam, LPARAM lParam)
{
	SStock * pStock = (SStock *)lParam;
	if (wParam != 0)
	{
		bool bReturn = true;
			if (wParam == SHOW_TRADEWND)
			{
				if (m_pDiagnose)
					m_pDiagnose->ShowTradeWnd();
			}
			else
			if (wParam == SHOW_TRACEWND)
			{
				m_pDiagnose->m_pPics->GotoTraceWnd();
				m_pDiagnose->SetLayout();
				return 0;
			}
			else	
			if (wParam == ESCAPE_TRACEWND)
			{
				m_pDiagnose->m_pPics->EscapeTraceWnd();
				m_pDiagnose->SetLayout();
				return 0;
			}
			else	
			if (wParam == SHOW_STOCKS)//显示列表
			{
				
				if (lParam > 0)
				{
					m_pDiagnose->SetStockCode(_T(""));
					m_pDiagnose->m_pPics->GotoStockList(lParam,3,0);
					m_pDiagnose->SetLayout();
				}
				else
				if (gpData->m_nStockSource == STOCK_FROM_LIST)//回到列表
				{
					m_pDiagnose->SetStockCode(_T(""));
					m_pDiagnose->m_pPics->GotoStockList(lParam,3,0);
					m_pDiagnose->SetLayout();
				}
				else
				if (gpData->m_nStockSource == STOCK_FROM_BOTTOM_LIST)//回到下面列表
				{
					m_pDiagnose->SetViewType(PICANDSUB);
					m_pDiagnose->SetLayout();
				}

			}
			else
			if (wParam == STOCK_FROM_GROUP || wParam == STOCK_FROM_LIST || wParam == STOCK_FROM_BOTTOM_LIST || wParam == STOCK_FROM_CHANGE)
			{
				gpData->m_nStockSource = wParam;
				bReturn = false;
			}			
			
		if (bReturn)
			return 0;
	}
	if (wParam == 0)
		gpData->m_nStockSource = 0;

	if (pStock == NULL)
	{
		if (gpData->m_strStockCode.IsEmpty())
			return 0;
		else
		{
			pStock = gpData->GetStock(gpData->m_strStockCode);			
			if (pStock == NULL)
				return 0;
		}
	}	
	gpData->m_strStockCode = pStock->m_sQuote.szStockCode;
	if (pStock)
	{
		gpData->m_strStockCode = pStock->m_sQuote.szStockCode;
		m_pDiagnose->m_strStockCode = pStock->m_sQuote.szStockCode;
		if (m_pDiagnose)
		{
			m_pDiagnose->SetStockCode(gpData->m_strStockCode);
		}
	}

	return 0;
}

LRESULT CFinSmithDlg::OnShowNews(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CFinSmithDlg::OnGetNewsWnd(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CFinSmithDlg::OnLog(WPARAM wParam, LPARAM lParam)
{
	//CLog log;
	//log.DoModal();
	SetTimer(104,1000 * 60,NULL);//测试连接
	return 0;
}

LRESULT CFinSmithDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	//if(wParam != IDR_MAINFRAME)
	//	return 0L;

	if(m_menuTray.m_hMenu == NULL && !m_menuTray.LoadMenu(IDR_MENU1))
		return 0;


	CMenu* pSubMenu = m_menuTray.GetSubMenu(0);
	if (!pSubMenu)
		return 0;
	if (lParam == WM_RBUTTONDOWN)
	{
		::SetMenuDefaultItem(pSubMenu->m_hMenu, 0, TRUE);
		CPoint pos;
		GetCursorPos(&pos);

		//SetForegroundWindow();

		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON
			|TPM_RIGHTBUTTON, pos.x, pos.y, this, NULL);

		//pSubMenu->TrackPopupMenu(TPM_RIGHTALIGN|TPM_LEFTBUTTON
		//|TPM_RIGHTBUTTON, pos.x, pos.y, this, NULL);

	}
	else if(lParam == WM_MOUSEHOVER)//WM_RBUTTONUP)
	{
		//SendMessage(WM_COMMAND, pSubMenu->GetMenuItemID(0), 0);
		m_trayIcon.uFlags = NIF_INFO;
		m_trayIcon.uTimeout = 6000;
		Shell_NotifyIcon(NIM_MODIFY, &m_trayIcon);
	}
	else if(lParam == WM_LBUTTONDBLCLK)
	{
/*
		::KillTimer(this->GetSafeHwnd(),1);
		HICON   hicon   =   AfxGetApp()->LoadIcon(IDR_MAINFRAME);   
		m_trayIcon.hIcon = hicon;
		m_bIcon = true;
		Shell_NotifyIcon(NIM_MODIFY, &m_trayIcon);
*/
		ShowWindow(SW_RESTORE);		
		SetForegroundWindow();
	}
	return 1L;
}


void CFinSmithDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 101)
	{
		if (gpCommSocket->m_socket != INVALID_SOCKET)
		{
			if (!gpCommSocket->SetSocketHeart(1))
			{//超过设定时间没有收到线路检测包
				gpCommSocket->Disconnect();
				PostMessage(WM_CONNECT_SUCCESS,0,0);
			}
		}
		else
			PostMessage(WM_CONNECT_SUCCESS,0,0);
	}
	//发送线路检测包
	if (nIDEvent == 102)
	{
		if (gpCommSocket->m_socket == INVALID_SOCKET)
		{
			//PostMessage(WM_CONNECT_SUCCESS,0,0);
		}
		int nLen;
		char acReq[1024];
		nLen = gpData->MakeLineTestReq(acReq);
		if (nLen > 0 && gpCommSocket && gpCommSocket->m_socket != INVALID_SOCKET)
			if (gpCommSocket->SendData(acReq,nLen,false) <= 0)
			{
				gpCommSocket->Disconnect();
				PostMessage(WM_CONNECT_SUCCESS,0,0);
			}
	}

	if (nIDEvent == 105)
	{
		KillTimer(105);
		CDlgTechDesc dlg;
		dlg.SetTitle(_T("通知"));
		dlg.DoModal();
		SetTimer(105,1000 * 60 * 10,NULL);		
	}
/*
	if (nIDEvent == 110)
	{
		FreshUserDefReport();
	}
*/
	CDialog::OnTimer(nIDEvent);
}

BOOL CFinSmithDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (m_pTopDlg && m_pTopDlg->IsWindowVisible())
			m_pTopDlg->ShowWindow(SW_HIDE);
	}

	if(pMsg->message   ==   WM_KEYDOWN) 
	{   
		if (pMsg->wParam == VK_ESCAPE)
		{
			if (m_pTopDlg->IsWindowVisible())
				m_pTopDlg->ShowWindow(SW_HIDE);
			return 1;
		}
	}   
	/*
	if(pMsg->message   ==   WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
			return TRUE;
		if ((pMsg->wParam >='0' && pMsg->wParam <= '9')
			||(pMsg->wParam >='a' && pMsg->wParam <= 'z')
			||(pMsg->wParam >='A' && pMsg->wParam <= 'Z'))
		{
			if (m_pTopDlg->ActiveByKey(pMsg->wParam))
				return TRUE;
		}
	}*/
	if (pMsg->message == WM_CHAR)
	{
		if ((pMsg->wParam >='0' && pMsg->wParam <= '9')
			||(pMsg->wParam >='a' && pMsg->wParam <= 'z')
			||(pMsg->wParam >='A' && pMsg->wParam <= 'Z'))
		{
			if (m_pTopDlg->ActiveByKey(pMsg->wParam))
				return TRUE;
		}
	}

	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CFinSmithDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	Shell_NotifyIcon(NIM_DELETE, &m_trayIcon);
}

BOOL CFinSmithDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: 在此添加专用代码和/或调用基类


	return CDialog::Create(lpszTemplateName, pParentWnd);
}

void CFinSmithDlg::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	//CLog log;	
	//log.m_strUrl = "http://192.168.12.8:9005/jsp/info/news1.jsp?sbjCode=301010&contentId=307462&type=2 ";
	//log.DoModal();
	//return;
	//CString strUrl = "http://192.168.12.8:9005/jsp/info/news1.jsp?sbjCode=301010&contentId=307462&type=2";
	//ShowUrl(strUrl,this,10,10,600,500,true,true);
	//return;
	//InfoSet(2+8);
	//return;
	CAboutDlg * pDlg;
	pDlg = new CAboutDlg();
	pDlg->DoModal();
	delete pDlg;
}

void CFinSmithDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	if (bShow)
	{				
		if (m_bFirstShow)
		{
			m_bFirstShow = false;
			CRect rectWnd;
			int nFullWidth = GetSystemMetrics(SM_CXSCREEN);   
			int nFullHeight = GetSystemMetrics(SM_CYSCREEN);
			
			rectWnd.top = 10;
			rectWnd.bottom = nFullHeight - 40;
			rectWnd.left = (nFullWidth - m_nLeftSideWidth - m_nRightSideWidth) / 2;
			rectWnd.right = rectWnd.left + m_nLeftSideWidth + m_nRightSideWidth;
			MoveWindow(rectWnd);
						
			OnBnClickedBtnMax();
		}
	}
}

void CFinSmithDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码

	int nMinWidth;
	if (m_nViewMode == 0)
		nMinWidth = 570;//m_nLeftSideWidth;
	else
		nMinWidth = m_nLeftSideWidth + 570;

	if (pRect->right - pRect->left < nMinWidth)
	{
		if (fwSide == WMSZ_LEFT || fwSide== WMSZ_TOPLEFT || fwSide == WMSZ_BOTTOMLEFT )
			pRect->left = pRect->right - nMinWidth;
		if (fwSide == WMSZ_RIGHT || fwSide == WMSZ_BOTTOMRIGHT || fwSide == WMSZ_TOPRIGHT)
			pRect->right = pRect->left + nMinWidth;
	}
	if (pRect->bottom - pRect->top < 500)
	{
		if (fwSide == WMSZ_TOP || fwSide== WMSZ_TOPLEFT || fwSide == WMSZ_TOPRIGHT )
			pRect->top = pRect->bottom - 500;
		if (fwSide == WMSZ_BOTTOM || fwSide == WMSZ_BOTTOMLEFT || fwSide == WMSZ_BOTTOMRIGHT)
			pRect->bottom = pRect->top + 500;
	}
}

void CFinSmithDlg::OnQuit()
{
	// TODO: 在此添加命令处理程序代码

	CRect rect;
	GetWindowRect(rect);
	char acBuf[24];
	sprintf(acBuf,"%d",rect.left);
	if (MessageBox(EXITMSG,_T("提示"),MB_OKCANCEL || MB_ICONQUESTION) == IDOK)
	{
		gpCommSocket->Disconnect();
		Shell_NotifyIcon(NIM_DELETE, &m_trayIcon);
		this->OnCancel();
	}
}

CWnd * CFinSmithDlg::ShowUrl(CString c_strUrl, CWnd *c_pwndCtrl,int c_iLeft,int c_iTop,int c_iWidth,int c_iHeight,BOOL c_bModal,bool c_bTitle)
{
	return NULL;
}
CWnd * CFinSmithDlg::ShowNews(CString c_strUrl, CWnd *c_pwndCtrl,int c_iLeft,int c_iTop,int c_iWidth,int c_iHeight,BOOL c_bModal,bool c_bTitle)
{
	return NULL;
}

int CFinSmithDlg::TestWeb(CString c_strDownUrl)
{
	CString strSentence, strWriteName;;
	CInternetSession sess;
	CHttpFile* fileGet;
	unsigned int	uiTotalLen = 0;
	sess.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000);      // 5秒的连接超时
	sess.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 2000);           // 1秒的发送超时
	sess.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 1000 * 60);        // 60秒的接收超时
	sess.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 2000);     // 2秒的发送超时
	sess.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 1000 * 60);       // 60秒的接收超时
	sess.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);          // 1次重试

	try
	{
		fileGet=(CHttpFile*)sess.OpenURL(c_strDownUrl);
	}
	catch(CException* )
	{
		fileGet = 0;
		return -9;
		//throw;
	}    

	if(fileGet)
	{
		DWORD dwStatus;
		DWORD dwBuffLen = sizeof(dwStatus);
		BOOL bSuccess = fileGet->QueryInfo(HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER, &dwStatus, &dwBuffLen);
		CString strEnter;
		strEnter = "\n";
		if( bSuccess && dwStatus>= 200&& dwStatus<300 ) 
		{ 
			CStdioFile fileWrite;
			char aczBuf[10240 + 1];
			int n;
			while(true)
			{
				n = fileGet->Read(aczBuf,10240);
				if (n<=0)
					break;
				uiTotalLen += n;
			}
		}
		else 
		{
			fileGet->Close();
			delete fileGet;
			sess.Close();
			return -2;
		}
		fileGet->Close();
		delete fileGet;
	}
	else
	{
		sess.Close();
		return -3;
	}

	sess.Close();
	return 0;
}
int CFinSmithDlg::InfoSet(int c_nSet)
{			

	typedef int (_cdecl *UserSet)(int, CRect*, CWnd *);
	HINSTANCE hinstDLL = NULL; 
	int nRet = 0;
	hinstDLL=LoadLibrary(_T("InfoSet.dll"));
	if (hinstDLL != NULL)
	{
		UserSet pSet;
		pSet = (UserSet)GetProcAddress(hinstDLL, "UserSet");
		if (pSet)
		{
			CRect rect;
			GetClientRect(rect);
			rect.left += 36;
			rect.top += 67;
			rect.bottom -= 28;
			rect.right -= 6;

			nRet = pSet(c_nSet, &rect, this);
		}
		//FreeLibrary(hinstDLL);
		return nRet;
	}
	else
	{
		return -1;
	}
	return -1;
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_hIcon = (HICON)::LoadImage(0,_T("logo.ico"),IMAGE_ICON,32,32,LR_LOADFROMFILE);
	if (!m_hIcon)
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	SetWindowText(VERNAME);
	m_stVer.SetWindowText(VERSTR);
	m_stIcon.SetIcon(m_hIcon);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFinSmithDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
}

void CFinSmithDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*
	CRect rect;
	GetWindowRect(rect);
	char acBuf[24];
	sprintf(acBuf,"%d",rect.left);

	if (MessageBox("确定退出 “在线分析师客户端”？","提示",MB_OKCANCEL || MB_ICONQUESTION) == IDOK)
	{
		gpCommSocket->Disconnect();
		Shell_NotifyIcon(NIM_DELETE, &m_trayIcon);		
	}
	else
		return;
*/
	CDialog::OnClose();
}

void CFinSmithDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDialog::OnMoving(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
}

void CFinSmithDlg::OnBnClickedBtnClose()
{
	// TODO: 在此添加控件通知处理程序代码
	OnQuit();
}

void CFinSmithDlg::OnBnClickedBtnIndustrydown()
{
	// TODO: 在此添加控件通知处理程序代码	
}

void CFinSmithDlg::OnBnClickedBtnIndustryup()
{
	// TODO: 在此添加控件通知处理程序代码
	return;
}

void CFinSmithDlg::OnBnClickedBtnDiagnose()
{
	// TODO: 在此添加控件通知处理程序代码
	return;
}

void CFinSmithDlg::OnBnClickedBtnMarket()
{
	// TODO: 在此添加控件通知处理程序代码
	/* forbidden 20100826
	if (m_pDiagnose)
	{
		SStock * pStock = gpData->GetStock("000001.SH");
		if (pStock)
		{
			SendMessage(WM_GOTO_STOCK,0,DWORD_PTR(pStock));		
			m_pDiagnose->ShowMarketAndNews();
		}
	}*/
}

void CFinSmithDlg::OnBnClickedBtnMin()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_MINIMIZE);
}

void CFinSmithDlg::OnBnClickedBtnMax()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!IsZoomed())
	if (m_bZoom == false)
	{
		GetWindowPlacement(&m_WndPlace);
		CRect rcWorkArea;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rcWorkArea,0);
		MoveWindow(&rcWorkArea);
		m_bZoom = true;
		
		//ShowWindow(SW_MAXIMIZE);
	}
	else
	{
		//ShowWindow(SW_RESTORE);		
		m_bZoom = false;

		CRect rect;
		rect = m_WndPlace.rcNormalPosition;
		MoveWindow(rect);
	}
}

void CFinSmithDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_rectSize.PtInRect(point))
	{
		::PostMessage(gpData->m_hwndMain,WM_CHANGE_VIEWMODE,0,0);
		return;
	}
	if (m_bSize)
	{
		SizeWindow(m_nSizeKind,point);
		ReleaseCapture();
		m_bSize = false;
		m_nSizeKind = 0;
		return;
	}

	CRect rect;
	int nID = m_menu.CheckMenu(point,rect);
	if (nID > 0)
	{
		CPoint point;
		CCustomMenu mn;
		mn.LoadMenu(nID);
		mn.ChangeMenuItem(&mn,TRUE);
		CMenu * pPop;
		pPop = mn.GetSubMenu(0);

		//CMenu * pMenu=new CMenu(),*pPop;
		//pMenu->LoadMenu(nID);
		//pPop = pMenu->GetSubMenu(0);
		if (nID == IDR_MENU_TECH)
		{
			CMenu * pSub = pPop->GetSubMenu(6);
			if (pSub)
			{
				if (!(ROLE_JGMM & gpData->m_dwRole))
					//pSub->RemoveMenu(4,MF_BYPOSITION);
					pSub->RemoveMenu(ID_ORG_TRADE,MF_BYCOMMAND);
				if (!(ROLE_CUT_LINE & gpData->m_dwRole))
					//pSub->RemoveMenu(3,MF_BYPOSITION);
					pSub->RemoveMenu(ID_CUT_ALERT,MF_BYCOMMAND);
				if (!(ROLE_TRADE_AREA & gpData->m_dwRole))
					//pSub->RemoveMenu(2,MF_BYPOSITION);
					pSub->RemoveMenu(ID_TRADE_AREA,MF_BYCOMMAND);
				if (!(ROLE_PRICE_ALERT & gpData->m_dwRole))
					//pSub->RemoveMenu(1,MF_BYPOSITION);
					pSub->RemoveMenu(ID_PRICE_ALERT,MF_BYCOMMAND);
				if (!(ROLE_MARKET_RADA & gpData->m_dwRole))
					//pSub->RemoveMenu(0,MF_BYPOSITION);
					pSub->RemoveMenu(ID_MARKET_RADA,MF_BYCOMMAND);
				if (pSub->GetMenuItemCount() == 0)
					pPop->RemoveMenu(6,MF_BYPOSITION);
			}
		}		
		point.x = rect.left;
		point.y = rect.bottom;
		this->ClientToScreen(&point);
		//::ScreenToClient(this->GetSafeHwnd(),&point);			
		pPop->TrackPopupMenu(TPM_RIGHTBUTTON|TPM_LEFTALIGN,point.x,point.y,this);
		//pMenu->DestroyMenu();
		//delete pMenu;
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CFinSmithDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bSize = false;
	if (m_bSize)
	{
		SizeWindow(m_nSizeKind,point);
	}

	CRect rect;
	bool bSize;
	GetClientRect(rect);
	int nSizeKind = 0;
	if (point.x < rect.left + 4 || point.x > rect.right - 4 || point.y < rect.top + 4 || point.y > rect.bottom - 4)
	{
		if (point.x < rect.left + 4)
			nSizeKind = HTLEFT;
		else
		if (point.x > rect.right - 4)
			nSizeKind = HTRIGHT;
		else
		if (point.y < rect.top + 4)
			nSizeKind = HTTOP;
		else
			nSizeKind = HTBOTTOM;
		bSize = true;
	}
	else
		bSize = false;

	HCURSOR hcursor1;
	if (bSize || m_bSize)
	{
		if (nSizeKind == HTLEFT || nSizeKind == HTRIGHT || m_nSizeKind == HTLEFT || m_nSizeKind == HTRIGHT)
			hcursor1 = LoadCursor(NULL,IDC_SIZEWE);
		else
			hcursor1 = LoadCursor(NULL,IDC_SIZENS);
	}
	else
		hcursor1 = LoadCursor(NULL,IDC_ARROW);
	
	SetCursor(hcursor1);

	CDialog::OnMouseMove(nFlags, point);
}

void CFinSmithDlg::SizeWindow(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x == m_ptSize.x)
	{
		return;
	}
	CRect  rect;
	GetWindowRect(rect);
	if (nHitTest == HTLEFT)
		rect.left -= m_ptSize.x - point.x;
	else
	if (nHitTest == HTRIGHT)
		rect.right += point.x - m_ptSize.x;
	else
	if (nHitTest == HTTOP)
		rect.top -= m_ptSize.y - point.y;
	else
	if (nHitTest == HTBOTTOM)
		rect.bottom += point.y - m_ptSize.y;
	MoveWindow(rect);
	m_ptSize = point;
}

void CFinSmithDlg::OnBnClickedBtnTech()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CFinSmithDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码	
	
///-	char acLog[256];
	//if (pWndOther)
	//	sprintf(acLog,"nState = %u,bMinimized = %d,%d\r\n",nState,bMinimized,pWndOther->GetSafeHwnd());
	//else
	//	sprintf(acLog,"nState = %u,bMinimized = %d\r\n",nState,bMinimized);
	//LogFile("c:\\test\\log.log",acLog,strlen(acLog));
	if (nState == WA_ACTIVE && bMinimized)
	{
		ShowWindow(SW_RESTORE);
	}
	else
	if (nState == WA_INACTIVE && !bMinimized)
	{
		if (pWndOther)
		{
			//SetWindowPos(&wndBottom,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE);	
			//SetWindowPos(pWndOther,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE);	
		}
		else
		{
			//SetWindowPos(pWndOther,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE);	
			//if (GetForegroundWindow() != this)
			//	SetWindowPos(&wndBottom,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE);	
		}
	}
}

void CFinSmithDlg::OnActivateApp(BOOL bActive, DWORD dwThreadID)
{
	CDialog::OnActivateApp(bActive, dwThreadID);

	// TODO: 在此处添加消息处理程序代码
	/*
	if (m_bFirstShow == false)
	{
		if (bActive == FALSE)
		{
			//if (dwThreadID != 0)
			//	SetWindowPos(&wndBottom,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE);			
			//if (GetForegroundWindow() == NULL)						
			//	ShowWindow(SW_SHOWMINIMIZED | SW_SHOWMINNOACTIVE);
		}
		else
		if (dwThreadID != 0)
		{
			if (GetForegroundWindow() != this)
				return;
			//SetWindowPos(&wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);
			WINDOWPLACEMENT place;
			GetWindowPlacement(&place);
			if (place.showCmd & SW_SHOWMINIMIZED)
				ShowWindow(SW_RESTORE);
		}
	}*/
}

BOOL CFinSmithDlg::OnNcActivate(BOOL bActive)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CDialog::OnNcActivate(bActive);
}

void CFinSmithDlg::OnTechRsi()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->DoMenuAction(PIC_RSI);
}

void CFinSmithDlg::OnTechKdj()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->DoMenuAction(PIC_KDJ);
}

void CFinSmithDlg::OnTechMacd()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->DoMenuAction(PIC_MACD);
}

void CFinSmithDlg::OnTechBoll()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->DoMenuAction(PIC_BOLL);
}

void CFinSmithDlg::OnTechGb()
{
	// TODO: 在此添加命令处理程序代码	
}

void CFinSmithDlg::OnTechMa()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->DoMenuAction(PIC_MA);
}

void CFinSmithDlg::OnTechDay()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->OnDayk();
}

void CFinSmithDlg::OnTechWeek()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->OnWeekk();
}

void CFinSmithDlg::OnTechMonth()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->OnMonk();
}

void CFinSmithDlg::OnSkinBlack()
{
	// TODO: 在此添加命令处理程序代码
	//gpSkinManager->SetSkin("黑色经典");
	gpSkinManager->SetSkinType(1);
	ResetSkin();
	m_pDiagnose->m_pPics->m_pPicWnd->resetLineColor();
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
	{
		m_pDiagnose->m_pPics->m_pPicWnd->Invalidate();
		m_pDiagnose->m_pPics->m_pRightWnd->Invalidate();
	}
	if (m_pDiagnose->m_pPics->m_pList->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pList->Invalidate();

	if (this->m_pCollectSort)
		m_pCollectSort->ResetSkin();
	WritePrivateProfileString(_T("SKINSET"),_T("style"),_T("black"),toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
	this->SetLayout();
}

void CFinSmithDlg::OnSkinWhite()
{
	// TODO: 在此添加命令处理程序代码
	//gpSkinManager->SetSkin("白色经典");
	gpSkinManager->SetSkinType(0);
	ResetSkin();
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
	{
		m_pDiagnose->m_pPics->m_pPicWnd->Invalidate();
		m_pDiagnose->m_pPics->m_pRightWnd->Invalidate();
	}
	if (this->m_pCollectSort)
		m_pCollectSort->ResetSkin();

	WritePrivateProfileString(_T("SKINSET"),_T("style"),_T("white"),toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
	this->SetLayout();
}

void CFinSmithDlg::OnHomepage()
{		
	// TODO: 在此添加命令处理程序代码
	//::ShellExecute(0,_T("open"),_T("http://www.w5178.com"),NULL,NULL,SW_SHOWNORMAL);
	::ShellExecute(0,_T("open"),gpData->m_strHomeUrl,NULL,NULL,SW_SHOWNORMAL);
}

void CFinSmithDlg::OnBoard()
{
	// TODO: 在此添加命令处理程序代码
	CString strUrl;
	strUrl.Format(_T("http://www.w5178.com/dy.jsp?userId=%d"),gpData->m_nUserID);
	::ShellExecute(0,_T("open"),strUrl,NULL,NULL,SW_SHOWNORMAL);
}

void CFinSmithDlg::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnNcLButtonUp(nHitTest, point);
}

void CFinSmithDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnNcLButtonDown(nHitTest, point);
}

void CFinSmithDlg::OnNcRButtonUp(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnNcRButtonUp(nHitTest, point);
}

void CFinSmithDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	// TODO: 在此处添加消息处理程序代码
}

void CFinSmithDlg::OnChangepassword()
{
	// TODO: 在此添加命令处理程序代码
	CDlgChgPwd dlg;
	dlg.DoModal();	
}

void CFinSmithDlg::ResetSkin()
{
	m_menu.SetTextFont(gpSkinManager->GetMenuFont());
	m_btnClose.SetBtnBMP(gpSkinManager->GetBitmap(ID_HEAD_CLOSE),gpSkinManager->GetBitmap(ID_HEAD_CLOSE_CHANGE));
	m_btnMax.SetBtnBMP(gpSkinManager->GetBitmap(ID_HEAD_MAX),gpSkinManager->GetBitmap(ID_HEAD_MAX_CHANGE));
	m_btnMin.SetBtnBMP(gpSkinManager->GetBitmap(ID_HEAD_MIN),gpSkinManager->GetBitmap(ID_HEAD_MIN_CHANGE));

	Invalidate();
	m_pDiagnose->ResetSkin();
}

void CFinSmithDlg::SetViewMode(int c_nMode)
{
	m_nViewMode = c_nMode;
	m_pDiagnose->m_nSizeMode = m_nViewMode;
	m_pDiagnose->ShowWindow(SW_SHOW);
	SetLayout();
}
void CFinSmithDlg::OnLic()
{
	// TODO: 在此添加命令处理程序代码
	CDlgTechDesc dlg;
	dlg.SetTitle(_T("许可协议"));
	dlg.DoModal();
}


void CFinSmithDlg::OnTechEma()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->DoMenuAction(PIC_EMA);
}

void CFinSmithDlg::OnTechVolume()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->DoMenuAction(PIC_HISK_VOL);	
}

void CFinSmithDlg::OnCycleMin1()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->OnMin1k();
}

void CFinSmithDlg::OnCycleMin5()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->OnMin5k();
}

void CFinSmithDlg::OnCycleMin15()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->OnMin15k();
}

void CFinSmithDlg::OnCycleMin30()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->OnMin30k();
}

void CFinSmithDlg::OnCycleMin60()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose->m_pPics->m_pPicWnd->IsWindowVisible())
		m_pDiagnose->m_pPics->m_pPicWnd->OnMin60k();
}

void CFinSmithDlg::OnVirTrade()
{
	// TODO: 在此添加命令处理程序代码
	m_pDiagnose->ShowTradeWnd();
}

void CFinSmithDlg::OnManualBook()
{
	// TODO: 在此添加命令处理程序代码
	//CString strUrl;
	//strUrl.Format(_T("http://www.w5178.com/jsp/faq/index.jsp"),gpData->m_nUserID);
	::ShellExecute(0,_T("open"),gpData->m_strHelpUrl,NULL,NULL,SW_SHOWNORMAL);	

}

void CFinSmithDlg::OnRealTrade()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pDiagnose)
		m_pDiagnose->ShowTradeWnd();
}

void CFinSmithDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.y < m_nHeadHeight)
		OnBnClickedBtnMax();
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CFinSmithDlg::FreshUserDefReport()
{
	gpData->m_lockData.lock();
	gpData->CheckUserDefReportItems();
	char acReq[4096];
	int nFld[4]={0};
	QFSET(nFld,QFD_STOCKCODE);
	QFSET(nFld,QFD_ZRSP);
	QFSET(nFld,QFD_JRKP);
	QFSET(nFld,QFD_ZDF);
	QFSET(nFld,QFD_ZF);
	QFSET(nFld,QFD_CJSL);
	QFSET(nFld,QFD_CJJE);
	QFSET(nFld,QFD_ZJJG);
	int nLen = 0;
	int nCount = gpData->GetUserDefReportItems(acReq + 96,nLen,4000);
	gpData->m_lockData.unlock();
	int nRet = gpData->MakeUserDefReportReq(acReq,nFld,(int *)(acReq + 96),nCount);
	if (nRet > 0)
	{
		gpCommSocket->SendData(acReq,nRet,false);
	}				
}

void CFinSmithDlg::OnTechCancelAttach()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,SHOW_STOCKS,0);
}

void CFinSmithDlg::OnMenuSetFont()
{
	// TODO: 在此添加命令处理程序代码
	CDlgSetFont dlg;
	if (dlg.DoModal() == IDOK)
	{
		gpSkinManager->CreateFont();
		ResetSkin();
		SetLayout();
	}
}

int CFinSmithDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_CustomMenu.Attach(this->GetMenu()->GetSafeHmenu());
	m_CustomMenu.ChangeMenuItem(&m_CustomMenu,TRUE);

	return 0;
}

void CFinSmithDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (lpDrawItemStruct->CtlType == ODT_MENU)
		m_CustomMenu.DrawItem(lpDrawItemStruct);
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CFinSmithDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (lpMeasureItemStruct->CtlType == ODT_MENU)
		m_CustomMenu.MeasureItem(lpMeasureItemStruct);
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}