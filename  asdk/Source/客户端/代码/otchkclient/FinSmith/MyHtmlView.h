#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CHtmlView��"
#endif 
#include "../winunit/IUserWin.h"

// CMyHtmlView Html ��ͼ
class CMyHtmlView : public CHtmlView,public IUserWin
{
	DECLARE_DYNCREATE(CMyHtmlView)

public:
	CMyHtmlView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMyHtmlView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
public:
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
public:
	afx_msg void OnViewStock();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	virtual void OnDownloadBegin();
public:
	virtual void OnDownloadComplete();
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
public:
	virtual void OnNavigateError(LPCTSTR lpszURL, LPCTSTR lpszFrame, DWORD dwError, BOOL *pbCancel);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	virtual void OnDocumentComplete(LPCTSTR lpszURL);

	void	SetNotifyHwnd(HWND c_hwnd);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnCommandStateChange(long nCommand, BOOL bEnable);
	void RefreshWin();
	void ResetSkin();
	CWnd * GetWnd(){return this;};
	void SetStockCode(CString c_strCode);
	bool m_bGotoStock;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnInitialUpdate();
//	WNDPROC   wpOrigIEProc;   //   ��ö�������Ա 
};


