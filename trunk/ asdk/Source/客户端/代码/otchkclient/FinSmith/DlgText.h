#pragma once
#include "afxwin.h"


// CDlgText 对话框

class CDlgText : public CDialog
{
	DECLARE_DYNAMIC(CDlgText)

public:
	CDlgText(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgText();

// 对话框数据
	enum { IDD = IDD_DLG_TEXT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nSize;
	CString m_strText;
	afx_msg void OnBnClickedOk();
	CXPButton m_btnColor;
	COLORREF m_cl;
	afx_msg void OnBnClickedButtonColor();
	virtual BOOL OnInitDialog();
};
