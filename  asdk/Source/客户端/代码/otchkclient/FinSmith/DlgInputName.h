#pragma once
#include "afxwin.h"


// CDlgInputName �Ի���

class CDlgInputName : public CDialog
{
	DECLARE_DYNAMIC(CDlgInputName)

public:
	CDlgInputName(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInputName();

// �Ի�������
	enum { IDD = IDD_DLG_INPUT_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editInput;
	CString m_strInput;
	CString m_strTitle;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
