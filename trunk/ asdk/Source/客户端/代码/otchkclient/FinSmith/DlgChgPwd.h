#pragma once
#include "afxwin.h"


// CDlgChgPwd 对话框

class CDlgChgPwd : public CDialog
{
	DECLARE_DYNAMIC(CDlgChgPwd)

public:
	CDlgChgPwd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgChgPwd();

// 对话框数据
	enum { IDD = IDD_CHGPWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editPwd;
	CEdit m_editPwdNew;
	CEdit m_editPwdNew2;
	CString m_strPwd;
	CString m_strPwdNew;
	CString m_strPwdNew2;
	afx_msg void OnBnClickedOk();
};
