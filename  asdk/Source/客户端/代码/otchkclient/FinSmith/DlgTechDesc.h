#pragma once
#include "afxwin.h"


// CDlgTechDesc �Ի���

class CDlgTechDesc : public CDialog
{
	DECLARE_DYNAMIC(CDlgTechDesc)

public:
	CDlgTechDesc(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTechDesc();

// �Ի�������
	enum { IDD = IDD_TECH_DESC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editDesc;
	CString m_strTitle;
	void SetTitle(CString c_strTitle);
	virtual BOOL OnInitDialog();
};
