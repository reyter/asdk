#pragma once
#include "afxwin.h"


// CDlgSetPort �Ի���

class CDlgSetPort : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetPort)

public:
	CDlgSetPort(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSetPort();

// �Ի�������
	enum { IDD = IDD_DLG_SET_PORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_editPort;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSearch();
	afx_msg void OnBnClickedBtnSetPort();
};
