// HHUpdateServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HHUpdateServer.h"
#include "HHUpdateServerDlg.h"

#include "..\\include\\compress\\HHCompress.h"
#include "..\\include\\HHXml\\HHTyXml.h"
#include "HHSetting.h"
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
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CHHUpdateServerDlg 对话框

CHHUpdateServerDlg::CHHUpdateServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHHUpdateServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CHHUpdateServerDlg::~CHHUpdateServerDlg()
{
	int i;
	i=9;
}
void CHHUpdateServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHHUpdateServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_START, &CHHUpdateServerDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CHHUpdateServerDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_SET, &CHHUpdateServerDlg::OnBnClickedBtnSet)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CHHUpdateServerDlg 消息处理程序

BOOL CHHUpdateServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	SetTimer(12001,1000,NULL);
	SetTimer(12002,1000*60,NULL);
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CHHUpdateServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHHUpdateServerDlg::OnPaint() 
{
	if (IsIconic())
	{
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
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CHHUpdateServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CHHUpdateServerDlg::ShowMsg(CString strMsg,BOOL bClear)
{
	CRichEditCtrl *pEditShow = (CRichEditCtrl *)GetDlgItem(IDC_RICHEDIT2_SHOW);
	//CRichEditCtrl
	if (NULL != pEditShow)
	{
		if (bClear)
		{
			pEditShow->Clear();
		}
		pEditShow->SetSel(-1, -1);
		if (strMsg.GetLength()>0)
		{
			pEditShow->ReplaceSel(strMsg+_T("\r\n"));
		}
		
	}
	
}

LRESULT CHHUpdateServerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (message == WM_SHOW_MSG) {
		ShowMsg((TCHAR *)lParam);
		return TRUE;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CHHUpdateServerDlg::OnBnClickedBtnStart()
{
	m_IocpServer.AssociateWnd(this);//传递本窗口指针
	if (m_IocpServer.StartServer(9527))
	{
		GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
	}
}

void CHHUpdateServerDlg::OnBnClickedBtnStop()
{
	m_IocpServer.StopServer();
	GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SET)->EnableWindow(TRUE);
}

void CHHUpdateServerDlg::OnBnClickedBtnSet()
{
	//GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	CHHSetting seting;
	seting.DoModal();
}

void CHHUpdateServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (12001==nIDEvent)
	{
		UpdateWindow();
	}
	if (12002==nIDEvent)
	{
		ShowMsg("",TRUE);
	}
	CDialog::OnTimer(nIDEvent);
}
