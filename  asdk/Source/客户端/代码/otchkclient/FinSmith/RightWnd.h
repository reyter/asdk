/************************************************************************/
/* ÓÒ±ß±¨¼Û°å´°¿Ú                                                                     */
/************************************************************************/


#pragma once


// CRightWnd

class CRightWnd : public CWnd
{
	DECLARE_DYNAMIC(CRightWnd)

public:
	CRightWnd();
	virtual ~CRightWnd();

protected:
	DECLARE_MESSAGE_MAP()

public:
	void PaintSelfIndex(CDC &dc);
	void PaintSelf(CDC &dc);
	void DrawPriceVol(CDC * pDC,CRect c_rect);
	void DrawIndexInfo(CDC * pDC,CRect c_rect);
	void DrawStockInfo(CDC * pDC,CRect c_rect);
	void DrawTraceData(CDC * pDC,CRect c_rect,bool);
	int GetWidth();
public:
	void SetStockCode(CString c_strCode);
public:
	CString m_strStockCode;
	CRect m_rectTraceData;
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


