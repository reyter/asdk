#pragma once
#include "afxwin.h"


// CDlgTechDesc 对话框

class CDlgTechDesc : public CDialog
{
	DECLARE_DYNAMIC(CDlgTechDesc)

public:
	CDlgTechDesc(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTechDesc();

// 对话框数据
	enum { IDD = IDD_TECH_DESC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editDesc;
	CString m_strTitle;
	void SetTitle(CString c_strTitle);
	virtual BOOL OnInitDialog();
};
