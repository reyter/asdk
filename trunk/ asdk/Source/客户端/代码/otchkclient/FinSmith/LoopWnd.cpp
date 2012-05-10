// LoopWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "LoopWnd.h"


// CLoopWnd

IMPLEMENT_DYNAMIC(CLoopWnd, CFrameWnd)

CLoopWnd::CLoopWnd()
: m_nTime(0)
{	
}

CLoopWnd::~CLoopWnd()
{
}


BEGIN_MESSAGE_MAP(CLoopWnd, CFrameWnd)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CLoopWnd 消息处理程序



void CLoopWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_nTime++;
	if (m_nTime == 10)
		m_nTime = 0;
	BringWindowToTop();
	Invalidate();
	CFrameWnd::OnTimer(nIDEvent);
}

void CLoopWnd::Begin(CString c_strInfo)
{
	m_strInfo = c_strInfo;
	m_nTime = 0;
	ShowWindow(SW_SHOW);
	CenterWindow();
	BringWindowToTop();
	SetTimer(100,1000,NULL);
}

void CLoopWnd::End(void)
{
	KillTimer(100);
	ShowWindow(SW_HIDE);
}

void CLoopWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	CString strText;
	CRect rect;
	GetClientRect(rect);
	strText += m_strInfo;
	for(int n=0; n<m_nTime; n++)
	{
		strText += _T(".");
	}
	CBrush brush(RGB(255,255,225));
	dc.FillRect(rect,&brush);
	CFont * pOldFont = dc.SelectObject(gpSkinManager->m_pFontSmall);
	int nMode = dc.SetBkMode(TRANSPARENT);
	int cl = dc.SetTextColor(RGB(0,0,0));
	dc.DrawText(strText,rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	dc.SetTextColor(cl);
	dc.SetBkMode(nMode);
	dc.SelectObject(pOldFont);
}

int CLoopWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}

BOOL CLoopWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	cs.dwExStyle |= WS_EX_TOOLWINDOW;
	cs.style &= WS_BORDER;
	cs.style &= WS_DLGFRAME;

	return CFrameWnd::PreCreateWindow(cs);
}
