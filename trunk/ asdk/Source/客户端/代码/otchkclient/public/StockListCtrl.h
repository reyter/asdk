#pragma once
#include "SkinListCtrl.h"

// CStockListCtrl
#ifdef _DEBUG
#define ASSERT_VALID_STRING( str ) ASSERT( !IsBadStringPtr( str, 0xfffff ) )
#else	//	_DEBUG
#define ASSERT_VALID_STRING( str ) ( (void)0 )
#endif	//	_DEBUG


class CStockListCtrl : public CSkinListCtrl
{
	DECLARE_DYNAMIC(CStockListCtrl)

public:
	CStockListCtrl();
	virtual ~CStockListCtrl();
	
    BOOL m_bAsc;//是否顺序排序
    int m_nSortedCol;//当前排序的列
	CFont * m_pFont;
	bool m_bAutoSort;//排序
	bool m_bUnderLine;
	int m_nDiagnoseCol;//个股诊断在的字段

protected:
	WORD m_wHitMask; 
protected:
	 virtual afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult ); 
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
public:
    //static int CALLBACK CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData );
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
    int GetPos(const CString strName);
	CString GetPosName(const int);
	void SetListFont(CFont *c_pFont);
	void SetUnderLine(bool);
	void SetAutoSort(bool);
	void SetSortCol(int c_nCol);
	void ProcSort();
    //afx_msg LRESULT ColumnSort(WPARAM wParam,LPARAM lParam);

    //int m_iNumColumns;
    //int m_iSortColumn;
    //BOOL m_bSortAscending;
//public: 
//    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
protected:
	virtual void PreSubclassWindow();
	virtual int OnToolHitTest(CPoint point, TOOLINFO * pTI) const;
	int CellRectFromPoint(CPoint & point, RECT * cellrect, int * col) const;

public:
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
};


