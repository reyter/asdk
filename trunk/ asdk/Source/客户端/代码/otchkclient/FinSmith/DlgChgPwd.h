#pragma once
#include "afxwin.h"


// CDlgChgPwd �Ի���

class CDlgChgPwd : public CDialog
{
	DECLARE_DYNAMIC(CDlgChgPwd)

public:
	CDlgChgPwd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgChgPwd();

// �Ի�������
	enum { IDD = IDD_CHGPWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
