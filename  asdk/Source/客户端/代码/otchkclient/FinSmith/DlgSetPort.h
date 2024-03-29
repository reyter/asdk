#pragma once
#include "afxwin.h"


// CDlgSetPort 对话框

class CDlgSetPort : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetPort)

public:
	CDlgSetPort(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSetPort();

// 对话框数据
	enum { IDD = IDD_DLG_SET_PORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_editPort;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSearch();
	afx_msg void OnBnClickedBtnSetPort();
};
