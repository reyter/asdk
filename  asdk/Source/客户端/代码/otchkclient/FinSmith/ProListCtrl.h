#pragma once
#define DEFAULT_LINE_1_COLOR	0xFFFFFF
//#define DEFAULT_LINE_2_COLOR	RGB(240,247,255)
//#define DEFAULT_LINE_2_COLOR	RGB(0,0,0)

// CProListCtrl

class CProListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CProListCtrl)

public:
	CProListCtrl();
	virtual ~CProListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
public:
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	void DrawColorText(CDC * c_pDC,CRect c_rect,CString c_strText,long c_lFieldFormat,COLORREF c_clDef=RGB(0,0,0));
	long m_lFieldFormat[30];
	bool m_lFieldNegative[30];
	void SetFieldFormat(int c_nField,long c_lFormat);
	long GetFieldFormat(int c_nField);
	void SetFieldNegative(int c_nField,bool c_b);
	bool GetFieldNegative(int c_nField);

};


