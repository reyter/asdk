#pragma once
#include "afxwin.h"


// CDlgInputName 对话框

class CDlgInputName : public CDialog
{
	DECLARE_DYNAMIC(CDlgInputName)

public:
	CDlgInputName(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInputName();

// 对话框数据
	enum { IDD = IDD_DLG_INPUT_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editInput;
	CString m_strInput;
	CString m_strTitle;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
