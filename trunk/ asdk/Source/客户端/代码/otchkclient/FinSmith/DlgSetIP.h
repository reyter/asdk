#pragma once


// CDlgSetIP 对话框

class CDlgSetIP : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetIP)

public:
	CDlgSetIP(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSetIP();

// 对话框数据
	enum { IDD = IDD_SET_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strIP;
	int m_nPort;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnSearch();
};
