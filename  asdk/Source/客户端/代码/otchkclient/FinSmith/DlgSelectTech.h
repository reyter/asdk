#pragma once
#include "afxwin.h"


// CDlgSelectTech 对话框

class CDlgSelectTech : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectTech)

public:
	CDlgSelectTech(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSelectTech();

// 对话框数据
	enum { IDD = IDD_DLG_SELECT_TECH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnDblclkListTechs();
	afx_msg void OnBnClickedOk();
	CListBox m_listTechs;
	CString m_strSelected;
	CString m_strStockCode;
	bool m_bMainPic;//主图
	bool m_bIndex;//是否指数
	unsigned short m_usCycle;//周期
};
