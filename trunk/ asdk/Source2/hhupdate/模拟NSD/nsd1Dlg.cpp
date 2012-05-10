// nsd1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "nsd1.h"
#include "nsd1Dlg.h"
#include ".\nsd1dlg.h"

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


// Cnsd1Dlg 对话框



Cnsd1Dlg::Cnsd1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cnsd1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void Cnsd1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cnsd1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
END_MESSAGE_MAP()


// Cnsd1Dlg 消息处理程序

BOOL Cnsd1Dlg::OnInitDialog()
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
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void Cnsd1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cnsd1Dlg::OnPaint() 
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
HCURSOR Cnsd1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cnsd1Dlg::OnBnClickedButton1()
{
	m_bForce = FALSE;
	//调用HHUpdateClient

	STARTUPINFO si; //一些必备参数设置
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi; //必备参数设置结束
	if(!CreateProcess("HHUpdateClient.exe",NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
	{
		TRACE("Create Fail!");
		//exit(1);
	}
	else
	{
		TRACE("Success!");
		Sleep(1000);
		OnBnClickedButton2();
	}
}

void Cnsd1Dlg::OnBnClickedButton2()
{//发送窗口句柄、IP等
	CString str="宏汇NSD自动升级服务";
	tagUpgradeInfo *_tagpProcessMsg = new tagUpgradeInfo();
	_tagpProcessMsg->hWnd = this->m_hWnd;
	::GetWindowModuleFileName(this->m_hWnd,_tagpProcessMsg->chAppName,128);
	char *ptr=NULL,c = '\\';
	ptr = strrchr(_tagpProcessMsg->chAppName,c);
	if (strlen(ptr)>1)
	{
		strcpy(_tagpProcessMsg->chAppName,&ptr[1]);
	}
	strcpy(_tagpProcessMsg->szAppID,"001S00000026");
	strcpy(_tagpProcessMsg->szVersion,"");
	strcpy(_tagpProcessMsg->szServerIP,"192.168.10.217");
	strcpy(_tagpProcessMsg->szUserID,"飞天蛇");
	_tagpProcessMsg->nServerPort = 9527;


	_tagpProcessMsg->bForce = (int)m_bForce;//强制升级

	tagCOPYDATASTRUCT sss={0};

	sss.lpData=_tagpProcessMsg;
	sss.cbData=sizeof tagUpgradeInfo;
	CWnd *pWnd=CWnd::FindWindow(NULL,str);//获取目的窗口对象
	while(!pWnd)
	{
		Sleep(500);
	}

	if(pWnd)
	{
		//pWnd->SendMessage(); //发送自定义消息
		//pWnd->SendMessage(WM_MYMESSAGE,0,(LPARAM)_tagpProcessMsg);
		::SendMessage(pWnd->m_hWnd, WM_COPYDATA, NULL, (LPARAM)&sss);
	}
	else
	{
		AfxMessageBox("没有找到MYRECEIVER窗口！");
	}
}

void Cnsd1Dlg::OnBnClickedButton3()
{
	m_bForce = TRUE;
	STARTUPINFO si; //一些必备参数设置
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi; //必备参数设置结束
	if(!CreateProcess("HHUpdateClient.exe",NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
	{
		TRACE("Create Fail!");
		//exit(1);
	}
	else
	{
		TRACE("Success!");
		Sleep(1000);
		OnBnClickedButton2();
	}

}


