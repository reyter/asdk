#pragma once
#include "afxwin.h"


// CDlgText �Ի���

class CDlgText : public CDialog
{
	DECLARE_DYNAMIC(CDlgText)

public:
	CDlgText(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgText();

// �Ի�������
	enum { IDD = IDD_DLG_TEXT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
