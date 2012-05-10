// DlgWaitData.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "DlgWaitData.h"


// CDlgWaitData 对话框

IMPLEMENT_DYNAMIC(CDlgWaitData, CDialog)

CDlgWaitData::CDlgWaitData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWaitData::IDD, pParent)
{
	m_nCycle = 0;
	m_strInfo = _T(" ");
	m_nTotal = 0;
	m_nNow = 0;
	m_imgInfo.Load(_T("./Skin/comm/logWait.jpg"));	
}

CDlgWaitData::~CDlgWaitData()
{
	if (!m_imgInfo.IsNull())
	m_imgInfo.Detach();
}

void CDlgWaitData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_A, m_stInfo);
}


BEGIN_MESSAGE_MAP(CDlgWaitData, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_MESSAGE(WM_DATA_PROGRESS,OnDataProgress)
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgWaitData 消息处理程序

BOOL CDlgWaitData::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*
	HBITMAP h;
	if (m_nCycle % 3 == 0)
		h = gpSkinManager->LoadCommBmp(ID_WAIT_DATA1);
	else
	if (m_nCycle % 3 == 1)
		h = gpSkinManager->LoadCommBmp(ID_WAIT_DATA2);
	else
		h = gpSkinManager->LoadCommBmp(ID_WAIT_DATA3);
	*/
	
	CRect rectClient;
	GetClientRect(rectClient);
	if (!m_imgInfo.IsNull())
	m_imgInfo.Draw(pDC->GetSafeHdc(),rectClient);
	/*
	if (h)
	{
		gpSkinManager->FillRectImage(h,pDC,rectClient);
		DeleteObject(h);
	}*/
	CRect rect;
	GetClientRect(rect);
	rect.top = rect.bottom - 20;
	CFont *pFont = pDC->SelectObject(gpSkinManager->m_pFontSmall);
	int nOldMode = pDC->SetBkMode(TRANSPARENT);
	COLORREF cl = pDC->SetTextColor(RGB(0,0,160));
	CString str;
	
	
	if (m_nTotal > 0)
	{				
		str.Format(_T("%s %d / %d"),m_strInfo,m_nNow,m_nTotal);
		//str = m_strInfo + str;
	}
	else
		str = m_strInfo;

	pDC->DrawText(str,rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	pDC->SetBkMode(nOldMode);
	pDC->SelectObject(pFont);
	return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}

BOOL CDlgWaitData::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//HBITMAP h = gpSkinManager->LoadCommBmp(ID_WAIT_DATA1);
	//if (h)
	if(!m_imgInfo.IsNull())
	{
		//CBitmap bitmap;
		//BITMAP bm;
		//bitmap.Attach(h);
		//bitmap.GetBitmap(&bm);
		//bitmap.Detach();
		CRect rect;
		GetWindowRect(rect);
		
		int with= GetSystemMetrics(SM_CXFULLSCREEN); 
		int height= GetSystemMetrics(SM_CYFULLSCREEN); 

		rect.left = (with - m_imgInfo.GetWidth()) / 2;
		rect.right = rect.left + m_imgInfo.GetWidth();
		rect.top = (height - m_imgInfo.GetHeight()) / 2;
		rect.bottom = rect.top + m_imgInfo.GetHeight();// + 20;
		MoveWindow(rect);
		//DeleteObject(h);
	}
	m_stInfo.ShowWindow(SW_HIDE);
	//m_stInfo.ShowWindow(SW_SHOW);
	SetTimer(101,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgWaitData::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_stInfo)
	{
		CRect rect;
		GetClientRect(rect);
		rect.top = rect.bottom - 20;
		//m_stInfo.MoveWindow(rect);
	}
}

void CDlgWaitData::SetDataInfo(CString c_strInfo)
{
	m_strInfo = c_strInfo;
	m_nTotal = 0;
	m_nNow = 0;
	m_stInfo.SetWindowText(c_strInfo);
}

LRESULT CDlgWaitData::OnDataProgress(WPARAM wParam, LPARAM lParam)
{	
	m_nTotal = lParam;
	m_nNow = wParam;
	Invalidate();
	return 0;
}

void CDlgWaitData::PostNcDestroy()
{
    // TODO: 在此添加专用代码和/或调用基类

    CDialog::PostNcDestroy();
    DestroyWindow();
    delete this;
}

void CDlgWaitData::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 101)
	{
		if (IsWindowVisible())
		{
			m_nCycle++;
			Invalidate();
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgWaitData::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	/*
	HBITMAP h;
	if (m_nCycle % 3 == 0)
		h = gpSkinManager->LoadCommBmp(ID_WAIT_DATA1);
	else
	if (m_nCycle % 3 == 1)
		h = gpSkinManager->LoadCommBmp(ID_WAIT_DATA2);
	else
		h = gpSkinManager->LoadCommBmp(ID_WAIT_DATA3);
	CRect rectClient;
	GetClientRect(rectClient);
	if (h)
	{
		gpSkinManager->FillRectImage(h,&dc,rectClient);
		DeleteObject(h);
	}		
	*/
}
