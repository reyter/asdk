#pragma once


// CSkinComboBox

class CSkinComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CSkinComboBox)

public:
	CSkinComboBox();
	virtual ~CSkinComboBox();

protected:
	DECLARE_MESSAGE_MAP()
public:		
	CBrush m_brush;
	void ResetSkin();
	void SetEditRect(int,int);	
	void DrawBorder(CDC * c_pDC,CRect c_rect);
	void DrawDownButton(CDC * c_pDC,CRect c_rectBk);
	void DrawItemBk(CDC * c_pDC,CRect c_itemRect,int c_nItem);
	void DrawEditItemBk(CDC * c_pDC,CRect c_itemRect);
	void DrawItemBkHot(CDC * c_pDC,CRect c_itemRect,int c_nItem);
	void DrawItemImage(CDC * c_pDC,CRect c_itemRect,int nItem);
	void DrawItemText(CDC * c_pDC,CRect c_itemRect,int c_nItem,bool c_bHot = false);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


