// CEditWithBack.cpp : implementation file
//

//DISCLAIMER:
//The code in this project is Copyright (C) 2006 by Gautam Jain. You have the right to
//use and distribute the code in any way you see fit as long as this paragraph is included
//with the distribution. No warranties or claims are made as to the validity of the
//information and code contained herein, so use it at your own risk.
#include "stdafx.h"
#include "EditWithBack.h"

// CEditWithBack

IMPLEMENT_DYNAMIC(CEditWithBack, CEdit)

CEditWithBack::CEditWithBack()
{
	m_rcEditArea.SetRect(0,0,0,0);
	m_bTracking = false;
	m_bOver = false;
}

CEditWithBack::~CEditWithBack()
{
	m_bmpEmptyEdit.DeleteObject();
	m_bmpFilledEdit.DeleteObject();

}


BEGIN_MESSAGE_MAP(CEditWithBack, CEdit)

	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_CONTROL_REFLECT(EN_KILLFOCUS, &CEditWithBack::OnEnKillfocus)
	ON_CONTROL_REFLECT(EN_SETFOCUS, &CEditWithBack::OnEnSetfocus)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// CEditWithBack message handlers

void CEditWithBack::PreSubclassWindow( )
{	
	// We must have a multiline edit
	// to be able to set the edit rect
	ASSERT( GetStyle() & ES_MULTILINE );

	ResizeWindow();
}


BOOL CEditWithBack::SetBitmaps(UINT iEmptyEdit, UINT iFilledEdit)
{
	BITMAP bmpInfo;

	//delete if already loaded.. just in case
	m_bmpEmptyEdit.DeleteObject();
	m_bmpFilledEdit.DeleteObject();

	m_bmpEmptyEdit.LoadBitmap(iEmptyEdit);
	m_bmpFilledEdit.LoadBitmap(iFilledEdit);

	m_bmpEmptyEdit.GetBitmap(&bmpInfo);
	m_rectEmptyBitmap.SetRect(0,0,bmpInfo.bmWidth,bmpInfo.bmHeight);

	m_bmpFilledEdit.GetBitmap(&bmpInfo);
	m_rectFilledBitmap.SetRect(0,0,bmpInfo.bmWidth,bmpInfo.bmHeight);


	return TRUE;

}
BOOL CEditWithBack::SetBitmapsRect(CRect c_rectEmpty,CRect c_rectFilled)
{
	m_rectEmptyBitmap = c_rectEmpty;
	m_rectFilledBitmap = c_rectFilled;
	return true;
}

void CEditWithBack::ResizeWindow()
{
	if (!::IsWindow(m_hWnd)) return;

	//proceed only if edit area is set
	if (m_rcEditArea == CRect(0,0,0,0)) return;
	/*
	if (GetWindowTextLength() == 0)
	{
		SetWindowPos(&wndTop,0,0,m_sizeEmptyBitmap.cx,m_sizeEmptyBitmap.cy,SWP_NOMOVE|SWP_NOZORDER);
	}else
	{
		SetWindowPos(&wndTop,0,0,m_sizeFilledBitmap.cx,m_sizeFilledBitmap.cy,SWP_NOMOVE|SWP_NOZORDER);
	}
	*/
	SetRect(&m_rcEditArea);

}


//set edit area may be called before creating the edit control
//especially when using the CEdit::Create method
//or after creating the edit control in CEdit::DoDataExchange
//we call ResizeWindow once in SetEditArea and once in PreSubclassWindow
BOOL CEditWithBack::SetEditArea(CRect rcEditArea)
{
	m_rcEditArea = rcEditArea;

	ResizeWindow();

	return TRUE;
}


BOOL CEditWithBack::OnEraseBkgnd(CDC* pDC)
{
	// Get the size of the bitmap
	CDC dcMemory;
	CRect rectBitmap;
	CBitmap* pOldBitmap = NULL;
	int iTextLength = GetWindowTextLength();

	if (iTextLength == 0)
	{
		rectBitmap = m_rectEmptyBitmap;
	}
	else
	{
		rectBitmap = m_rectFilledBitmap;
	}

	// Create an in-memory DC compatible with the
	// display DC we're using to paint
	dcMemory.CreateCompatibleDC(pDC);

	if (iTextLength == 0 && !m_bTracking)
	{
		// Select the bitmap into the in-memory DC
		pOldBitmap = dcMemory.SelectObject(&m_bmpEmptyEdit);
	}else
	{
		// Select the bitmap into the in-memory DC
		pOldBitmap = dcMemory.SelectObject(&m_bmpFilledEdit);
	}

	// Copy the bits from the in-memory DC into the on-
	// screen DC to actually do the painting. Use the centerpoint
	// we computed for the target offset.
	pDC->BitBlt(0,0, rectBitmap.Width(), rectBitmap.Height(), &dcMemory, 
		rectBitmap.left, rectBitmap.top, SRCCOPY);

	dcMemory.SelectObject(pOldBitmap);

	return TRUE;
}

void CEditWithBack::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//this will draw the background again
	//so that the button will be drawn if the text exists
	InvalidateRect(NULL);

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CEditWithBack::OnLButtonUp(UINT nFlags, CPoint point)
{
	//if the button is clicked then send message to the
	//owner.. the owner need not be parent
	//you can set the owner using the CWnd::SetOwner method
	if (m_rcButtonArea.PtInRect(point))
	{
		//it is assumed that when the text is not typed in the
		//edit control, the button will not be visible
		//but you can override this by setting 
		//the m_bButtonExistsAlways to TRUE
	}

	CEdit::OnLButtonUp(nFlags, point);
}


//by default, when the mouse moves over the edit control
//the system shows the I-beam cursor. However we want to
//show the arrow cursor when it is over the Non-Edit area
//where the button and icon is displayed
//here is the code to do this
BOOL CEditWithBack::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CPoint pntCursor;
	GetCursorPos(&pntCursor);
	ScreenToClient(&pntCursor);
	//if mouse is not in the edit area then
	//show arrow cursor
	if (!m_rcEditArea.PtInRect(pntCursor))
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(MAKEINTRESOURCE(IDC_ARROW)));
		return TRUE;
	}

	return CEdit::OnSetCursor(pWnd, nHitTest, message);
}



int CEditWithBack::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	ResizeWindow();

	return 0;
}


LRESULT CEditWithBack::OnSetFont( WPARAM wParam, LPARAM lParam )
{
	DefWindowProc( WM_SETFONT, wParam, lParam );

	ResizeWindow();

	return 0;

}

void CEditWithBack::OnSize( UINT nType, int cx, int cy ) 
{

	CEdit::OnSize( nType, cx, cy );

	ResizeWindow();

}

void CEditWithBack::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*
	if (!m_bTracking)
	{
		m_bTracking = true;
		Invalidate(1);
	}*/
	CEdit::OnMouseMove(nFlags, point);
	
}

LRESULT CEditWithBack::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bOver = FALSE;
	m_bTracking = FALSE;
	InvalidateRect(NULL, FALSE);
	return 0;
}

void CEditWithBack::OnEnKillfocus()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bTracking)
	{
		m_bTracking = false;
		this->Invalidate(1);
	}
}

void CEditWithBack::OnEnSetfocus()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_bTracking)
	{
		m_bTracking = true;
		this->Invalidate(1);
	}
}

void CEditWithBack::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	// TODO: 在此处添加消息处理程序代码
	if (m_bTracking)
	{
		m_bTracking = false;
		this->Invalidate(1);
	}
}

