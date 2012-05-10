// DlgUpdate.cpp : 实现文件
//

#include "stdafx.h"
#include "shlwapi.h"
#include "DlgLogin.h"
#include "../public/ShortSocket.h"
#include "DlgUpdate.h"
 

// CDlgUpdate 对话框

IMPLEMENT_DYNAMIC(CDlgUpdate, CDialog)

CDlgUpdate::CDlgUpdate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUpdate::IDD, pParent)
	, m_strInfo(_T(""))
{
	m_bFirstShow = true;
}

CDlgUpdate::~CDlgUpdate()
{
}

void CDlgUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Text(pDX, IDC_INFO, m_strInfo);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_BTN_START, m_btnStart);
	DDX_Control(pDX, IDC_CLOSE, m_btnCancel);
	DDX_Control(pDX, IDC_INFO, m_edit);
}


BEGIN_MESSAGE_MAP(CDlgUpdate, CDialog)
	ON_MESSAGE(WM_DOWNLOAD_LEN,OnDownloadSize)
	ON_BN_CLICKED(IDCANCEL, &CDlgUpdate::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CLOSE, &CDlgUpdate::OnBnClickedClose)
	ON_BN_CLICKED(IDC_BTN_START, &CDlgUpdate::OnBnClickedBtnStart)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CDlgUpdate::OnBnClickedBtnClose)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CDlgUpdate 消息处理程序

BOOL CDlgUpdate::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_btnClose.SetWindowText(_T(""));
	m_btnClose.SetBorder(false);
	m_btnClose.SetBtnBMP(IDB_BTN_MIN_CLOSE,IDB_BTN_MIN_CLOSE);

	m_btnStart.SetWindowText(_T(""));
	m_btnStart.SetBorder(false);
	m_btnStart.SetBtnBMP(IDB_BTN_CONFIRM,IDB_BTN_CONFIRM);

	m_btnCancel.SetWindowText(_T(""));
	m_btnCancel.SetBorder(false);
	m_btnCancel.SetBtnBMP(IDB_BTN_CANCEL,IDB_BTN_CANCEL);

	m_edit.SetFont(gpSkinManager->m_pFontSmall);
	//m_edit.ShowWindow(SW_HIDE);
	//m_progress.ShowWindow(SW_SHOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

bool CDlgUpdate::DownFileDirect()
{
	CShortSocket sk;

	SetInfoRect(false);
	m_progress.ShowWindow(SW_SHOW);
	SetLayout();
	m_progress.SetRange32(0,1024 * 1024 * 3);

	CDlgLogin dlg;
	sk.SetKeepLive(true);
	int nRet;
	while(m_nCancel != 1)
	{
		nRet = dlg.GetUpgradeFile(sk,this->GetSafeHwnd());
		if (nRet != 0)
			break;
	}
	sk.Disconnect();
	if (nRet == 1)
	{
		char acFile[MAX_PATH];
		sprintf(acFile,"%s\\%s.exe",gpData->m_acCurPath,gCfg.m_acVer);
		m_strFile = toUnicodeString(acFile,strlen(acFile));
		return true;
	}
	else
		return false;
}
bool CDlgUpdate::DownFile()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet;
	SetInfoRect(false);
	m_progress.ShowWindow(SW_SHOW);
	SetLayout();
	m_progress.SetRange32(0,1024 * 1024 * 3);

	COleDateTime dtCur;
	CString strTime;
	dtCur =  COleDateTime::GetCurrentTime();
	strTime.Format(_T("%02d%02d%02d%02d%02d%02d"),dtCur.GetYear(),dtCur.GetMonth(),dtCur.GetDay(),dtCur.GetHour(),dtCur.GetMinute(),dtCur.GetSecond());
	m_strUrl += "?NOWTIME=";
	m_strUrl += strTime;
	m_nCancel = 0;
	iRet = DownLoadData(m_strUrl,m_strFile,GetSafeHwnd(),&m_nCancel);
	if (iRet != 0 && iRet != -999)
	{
		MessageBox(_T("下载失败！"),_T("提示"),MB_OK +MB_ICONWARNING);
		m_progress.ShowWindow(SW_HIDE);
		SetLayout();
		return false;
	}

	m_progress.ShowWindow(SW_HIDE);
	SetLayout();
	if (iRet == -999)
		return false;
	else
	return true;
}

LRESULT CDlgUpdate::OnDownloadSize(WPARAM wParam,LPARAM lParam)
{
	m_progress.SetPos((unsigned int)wParam);
	return 0;
}
void CDlgUpdate::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nCancel = 1;
	EndDialog(IDCANCEL);
	//OnCancel();
}

void CDlgUpdate::OnBnClickedClose()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nCancel = 1;
	EndDialog(IDCANCEL);
}

void CDlgUpdate::OnBnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	//if (DownFile())
	if (DownFileDirect())
	{
		if(m_nCancel == 1)
			EndDialog(IDCANCEL);
		else
			this->OnOK();
	}
	else
	{
		MessageBox(_T("下载升级文件失败！"),_T("提示"),MB_OK);
	}
}

BOOL CDlgUpdate::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(rect);	
	HBITMAP h = gpSkinManager->LoadCommBmp(ID_UPGRADE_BK);
	if (h)
	{
		gpSkinManager->FillRectImage(h,pDC,rect);		
		DeleteObject(h);
	}
	pDC->SetBkMode(TRANSPARENT);
	//HGDIOBJ hobj = pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	//CFont * pOldFont = pDC->SelectObject(gpSkinManager->m_pFontSmall);
	//pDC->DrawText(m_strInfo,m_rectInfo,DT_TOP|DT_LEFT|DT_WORDBREAK);
	//pDC->SelectObject(hobj);
	//pDC->SelectObject(pOldFont);
	return true;
	return CDialog::OnEraseBkgnd(pDC);
}

HBRUSH CDlgUpdate::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	
	if (pWnd->GetSafeHwnd() == GetDlgItem(IDC_INFO)->GetSafeHwnd())
	{
		CBrush brush;
		pDC->SetBkMode(TRANSPARENT);
		brush.CreateSolidBrush(RGB(255,255,255));
		return brush; 
		//return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CDlgUpdate::SetInfoRect(bool c_bMax)
{/*
	CRect rect,rectClient;
	GetClientRect(rectClient);
	rect = rectClient;
	rect.left += 8;
	rect.right -= 8;
	rect.top += 4;
	rect.bottom -= 28;
	CRect rectProgress;
	m_progress.GetWindowRect(rectProgress);
	if (c_bMax == false)
		rect.bottom -= rectProgress.Height() + 4;
	this->GetDlgItem(IDC_INFO)->MoveWindow(rect);*/
}

void CDlgUpdate::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_btnClose)
	{
		SetLayout();
	}
}

void CDlgUpdate::SetLayout()
{
	CRect rect;
	GetClientRect(rect);
	rect.right -= 4;
	rect.left =rect.right - 16;
	rect.top += 4 + 2;
	rect.bottom = rect.top + 16;
	m_btnClose.MoveWindow(rect);

	GetClientRect(rect);
	rect.bottom -= 2;
	rect.top = rect.bottom - 25;
	rect.right = rect.left + rect.Width()/2;
	rect.right -= 8;
	rect.left = rect.right - 77;
	m_btnStart.MoveWindow(rect);

	GetClientRect(rect);
	rect.bottom -= 2;
	rect.top = rect.bottom - 25;
	rect.left += rect.Width()/2;
	rect.right += 8;
	rect.right = rect.left + 77;
	m_btnCancel.MoveWindow(rect);

	GetClientRect(rect);
	rect.left += 2;//150;
	rect.right -= 2;
	rect.top += 28;
	if (m_progress.IsWindowVisible())
		rect.bottom -= 32+22;
	else
		rect.bottom -= 32;
	m_edit.MoveWindow(rect);
	m_rectInfo = rect;

	GetClientRect(rect);
	rect.left += 2;
	rect.right -= 2;
	rect.bottom -= 32;
	rect.top = rect.bottom - 20;
	m_progress.MoveWindow(rect);
}
void CDlgUpdate::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	if (m_bFirstShow)
	{
		m_bFirstShow = false;
		CRect rect;
		this->GetWindowRect(rect);
		rect.right = rect.left + 400;
		rect.bottom = rect.top + 300;
		this->MoveWindow(rect);
		this->CenterWindow();
	}
}

void CDlgUpdate::OnBnClickedBtnClose()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nCancel = 1;
	EndDialog(IDCANCEL);
}

void CDlgUpdate::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_NCLBUTTONDOWN,   HTCAPTION,   MAKELPARAM(point.x,   point.y));   
	PostMessage(WM_LBUTTONUP,   NULL,   MAKELPARAM(point.x,   point.y));   

	CDialog::OnLButtonDown(nFlags, point);
}
