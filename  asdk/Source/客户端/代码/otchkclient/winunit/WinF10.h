#pragma once

#include "IUserWin.h"
// CWinF10

class CMyHtmlView;
class CWinF10 : public CWnd, public IUserWin
{
	DECLARE_DYNAMIC(CWinF10)

public:
	CWinF10();
	virtual ~CWinF10();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void ShowUrl();
	void SetViewPage(int);
public:
	CMyHtmlView * m_pWeb;
	CString m_strStockCode;
	int m_nViewPage;//œ‘ æ“≥√Ê
	void CreateSelf(CWnd * c_pParent);
	void SetStockCode(CString c_strCode);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void SetLayout(void);
	void SetNoFlash();
	CWnd * GetWnd();
	void GetViewTitle(CString &);
	bool IsTitle(CString c_strIn);
	void ResetSkin();
	void DoCommand(int c_nCommand);
	virtual BOOL DestroyWindow();
};

