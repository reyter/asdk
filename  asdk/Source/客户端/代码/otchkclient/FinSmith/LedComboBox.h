#pragma once


// CLedComboBox

class CLedComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CLedComboBox)

public:
	CLedComboBox();
	virtual ~CLedComboBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CBrush m_brush;
	int m_nLed[3];
	void ResetSkin();
	void SetEditRect(int,int);
	void SetLeds(int n1,int n2,int n3){m_nLed[0] = n1;m_nLed[1] = n2; m_nLed[2] = n3;};
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
};


