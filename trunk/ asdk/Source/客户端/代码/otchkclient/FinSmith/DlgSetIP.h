#pragma once


// CDlgSetIP �Ի���

class CDlgSetIP : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetIP)

public:
	CDlgSetIP(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSetIP();

// �Ի�������
	enum { IDD = IDD_SET_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strIP;
	int m_nPort;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnSearch();
};
