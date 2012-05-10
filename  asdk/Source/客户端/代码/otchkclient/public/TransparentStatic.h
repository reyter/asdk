#pragma once


// CTransparentStatic

class CTransparentStatic : public CStatic
{
	DECLARE_DYNAMIC(CTransparentStatic)

public:
	CTransparentStatic();
	virtual ~CTransparentStatic();

protected:
   afx_msg LRESULT OnSetText(WPARAM,LPARAM);
   afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
   DECLARE_MESSAGE_MAP()

public:
	void SetTextColor(COLORREF c_clText);
public:
	COLORREF m_clText;
};


