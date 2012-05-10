#pragma once

//DISCLAIMER:
//The code in this project is Copyright (C) 2006 by Gautam Jain. You have the right to
//use and distribute the code in any way you see fit as long as this paragraph is included
//with the distribution. No warranties or claims are made as to the validity of the
//information and code contained herein, so use it at your own risk.


// CEditWithBack

class CEditWithBack : public CEdit
{
	DECLARE_DYNAMIC(CEditWithBack)

protected:
	BOOL	m_bOver;
	BOOL	m_bTracking;
	HWND	m_hwndNeedEnterKey;
	CBitmap m_bmpEmptyEdit;
	CBitmap m_bmpFilledEdit;
	CRect   m_rectEmptyBitmap;
	CRect   m_rectFilledBitmap;
	CRect	m_rcEditArea;
	CRect	m_rcButtonArea;

public:
	
	BOOL SetBitmaps(UINT iEmptyEdit, UINT iFilledEdit);
	BOOL SetBitmapsRect(CRect c_rectEmpty,CRect c_rectFilled);
	BOOL SetEditArea(CRect rcEditArea);

	CEditWithBack();
	virtual ~CEditWithBack();
	virtual void PreSubclassWindow( );

protected:

	void ResizeWindow();


	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam); // Maps to WM_SETFONT

public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnEnKillfocus();
public:
	afx_msg void OnEnSetfocus();
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


