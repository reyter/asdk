#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ProListCtrl.h"
// CTopDlg 对话框
class CData;
class CTopDlg : public CDialog
{
	DECLARE_DYNAMIC(CTopDlg)

public:
	CTopDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTopDlg();

// 对话框数据
	enum { IDD = IDD_TOP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nType;
	bool m_bSelf;
	CString m_strKey;
	CProListCtrl m_lstCode;
public:
	int SetByKey(CString c_strKey);
	bool ActiveByKey(WPARAM wParam);
	void OnSelectOver();
public:
	virtual BOOL OnInitDialog();
public:
	CEdit *m_pEdit;
public:
	int SetLinkEdit(CEdit * c_pWnd,CData * c_pData,int c_nType = 0);//c_nType类型，0，直接以代码替换此Edit中的内容，1以中文名称替换,2以代码替换最后搜索串，3以中文名称替换,4以6位代码
public:
	afx_msg void OnLvnItemchangedListCode(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual void OnOK();
public:
	CXPButton m_btnHide;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg void OnBnClickedHide();
public:
	afx_msg void OnHdnItemdblclickListCode(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMDblclkListCode(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnEnterKey(WPARAM wParam,LPARAM lParam);
public:
	CData * m_pData;
	int	m_nSortField;//0编码，1拼音	
	CEdit m_edit;
	afx_msg void OnEnChangeEditCode();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};
