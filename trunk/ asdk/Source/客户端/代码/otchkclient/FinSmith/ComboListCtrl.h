#pragma once
#include "../public/SkinListCtrl.h"
#define DEFAULT_LINE_1_COLOR	0xFFFFFF
#define DEFAULT_LINE_2_COLOR	RGB(240,247,253)
#define DEFAULT_LINE_3_COLOR	RGB(238,240,245)

// CComboListCtrl

class CComboListCtrl : public CSkinListCtrl
{
	DECLARE_DYNAMIC(CComboListCtrl)

public:
	CComboListCtrl();
	virtual ~CComboListCtrl();

	BOOL m_fAsc;//是否顺序排序
    int m_nSortedCol;//当前排序的列
	int m_nDiagnoseCol;
protected:
	//{{AFX_MSG(CIndustryListCtrl)
	afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
protected:
	virtual void PreSubclassWindow();
	virtual int OnToolHitTest(CPoint point, TOOLINFO * pTI) const;
	int CellRectFromPoint(CPoint & point, RECT * cellrect, int * col) const;
public:
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
};


