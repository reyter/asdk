// MoveWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MoveWnd.h"
#include "../public/SKinManager.h"
#include "resource.h"

// CMoveWnd

IMPLEMENT_DYNAMIC(CMoveWnd, CWnd)

CMoveWnd::CMoveWnd(int c_nType)
{
	m_nType = c_nType;
	m_bMoving = false;
	m_pTop = NULL;
	m_pBottom = NULL;
	m_nMinTop = 80;
	m_nMaxTop = 800;
}

CMoveWnd::~CMoveWnd()
{
}


BEGIN_MESSAGE_MAP(CMoveWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CMoveWnd 消息处理程序



void CMoveWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	CRect rect;
	GetClientRect(rect);
	//CSkinManager sk;
	//sk.FillRectImage(IDB_MOVE_BACK,&dc,rect);
	if (m_nType == 0)
		gpSkinManager->FillRectImage(gpSkinManager->GetBitmap(ID_DRAG_BACK),&dc,rect);
	else
		gpSkinManager->FillRectImage(gpSkinManager->GetBitmap(ID_DRAG_VERT_BACK),&dc,rect);
	/*小箭头
	rect.left += (rect.Width() - 17)/2;
	rect.right = rect.left + 17;
	rect.top += (rect.Height() - 8) / 2;
	rect.bottom = rect.top + 8;
	sk.FillRectImage(IDB_MOVE_ARROW_BACK,&dc,rect);*/
}

void CMoveWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GetCursorPos(&m_ptOrg);
	//m_ptOrg = point;
	m_bMoving = true;
	//BringWindowToTop();	
	this->SetCapture();
	CWnd::OnLButtonDown(nFlags, point);
}

void CMoveWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}*/
	if (m_bMoving && (nFlags & MK_LBUTTON))
	{
		ChangePosition(point);
	}
	else
		m_bMoving = false;
	CWnd::OnMouseMove(nFlags, point);
}

void CMoveWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bMoving = false;
	ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}

LRESULT CMoveWnd::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{	
	m_bTracking = FALSE;
	return 0;
}

void CMoveWnd::SetControlWnds(CWnd * c_pTop,CWnd * c_pBottom)
{
	m_pTop = c_pTop;
	m_pBottom = c_pBottom;
}

bool CMoveWnd::ChangePosition(CPoint c_pt)
{
	CPoint pt = c_pt;
	GetCursorPos(&pt);
	CRect rect,rectParent,rectClient;
	this->GetParent()->GetWindowRect(rectParent);
	this->GetParent()->GetClientRect(rectClient);
	int nTop = rectParent.Height() - rectClient.Height();
	int nLeft = rectParent.Width() - rectClient.Width();
	nTop /= 2;
	nLeft /= 2;
	GetWindowRect(rect);
	rect.top -= rectParent.top + nTop;
	rect.bottom -= rectParent.top + nTop;
	rect.left -= rectParent.left + nLeft;
	rect.right -= rectParent.left + nLeft;

	rect.top += pt.y - m_ptOrg.y;
	rect.bottom += pt.y - m_ptOrg.y;
	if (rect.top < m_nMinTop)
		return false;
	if (rect.bottom > m_nMaxTop)
		return false;
	MoveWindow(rect);
	
	if (m_pTop)
	{
		m_pTop->GetWindowRect(rect);	
		rect.top -= rectParent.top + nTop;
		rect.bottom -= rectParent.top + nTop;
		rect.left -= rectParent.left + nLeft;
		rect.right -= rectParent.left + nLeft;
		
		rect.bottom += pt.y - m_ptOrg.y;
		m_pTop->MoveWindow(rect);
		m_pTop->Invalidate();
	}

	if (m_pBottom)
	{
		m_pBottom->GetWindowRect(rect);	
		rect.top -= rectParent.top + nTop;
		rect.bottom -= rectParent.top + nTop;
		rect.left -= rectParent.left + nLeft;
		rect.right -= rectParent.left + nLeft;

		rect.top += pt.y - m_ptOrg.y;
		m_pBottom->MoveWindow(rect);
		m_pBottom->Invalidate();
	}
	
	m_ptOrg = pt;
	return true;
}

void CMoveWnd::ResetSkin()
{
	Invalidate();
}
BOOL CMoveWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCursor(LoadCursor(NULL,IDC_SIZENS));
	return TRUE;
	//return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CMoveWnd::SetMoveSize(int c_nMin,int c_nMax)
{
	m_nMinTop = c_nMin;
	m_nMaxTop = c_nMax;
}