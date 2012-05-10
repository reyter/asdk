#pragma once


// CMoveWnd

class CMoveWnd : public CWnd
{
	DECLARE_DYNAMIC(CMoveWnd)

public:
	CMoveWnd(int c_nType=0);
	virtual ~CMoveWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void SetControlWnds(CWnd * c_pTop,CWnd * c_pBottom);
	bool ChangePosition(CPoint c_pt);
	void ResetSkin();
	void SetMoveSize(int,int);
public:
	int m_nType;//0Ë®Æ½£¬1´¹Ö±
	bool m_bMoving;
	bool m_bTracking;
	CPoint m_ptOrg;
	CWnd * m_pTop;
	CWnd * m_pBottom;	
	int m_nMinTop;
	int m_nMaxTop;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


