#pragma once
#include "TechManager.h"

// CDlgParamSet 对话框

class CDlgParamSet : public CDialog
{
	DECLARE_DYNAMIC(CDlgParamSet)

public:
	CDlgParamSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgParamSet();

// 对话框数据
	enum { IDD = IDD_DLG_PARAM_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void InitData();
	void SetViewItems();
public:
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedOk();	
public:
	unsigned int m_unEditID[8];// = (IDC_EDIT_1,IDC_EDIT_2,IDC_EDIT_3,IDC_EDIT_4,IDC_EDIT_5,IDC_EDIT_6,IDC_EDIT_7,IDC_EDIT_8);
	unsigned int m_unStaticID[8];// = (IDC_STATIC_1,IDC_STATIC_2,IDC_STATIC_3,IDC_STATIC_4,IDC_STATIC_5,IDC_STATIC_6,IDC_STATIC_7,IDC_STATIC_8);
	bool m_bMainPic;
	CString m_strTech;
	unsigned short m_usCycle;
	STECH m_stTech;
	bool m_bChanged;
	int	m_nParamCount;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
};
