#pragma once
#include "afxwin.h"


// CDlgSetFont �Ի���

class CDlgSetFont : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetFont)

public:
	CDlgSetFont(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSetFont();

// �Ի�������
	enum { IDD = IDD_DLG_SET_FONT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbMenu;
	CComboBox m_cbButton;
	CComboBox m_cbList;
	CComboBox m_cbText;
	CComboBox m_cbGraph;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnDefault();
	afx_msg void OnBnClickedOk();
};
