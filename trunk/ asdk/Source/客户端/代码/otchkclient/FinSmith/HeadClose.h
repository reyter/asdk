#pragma once
#include "resource.h"
#include "afxwin.h"

// CHeadClose 对话框

class CHeadClose : public CDialog
{
	DECLARE_DYNAMIC(CHeadClose)

public:
	CHeadClose(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHeadClose();

// 对话框数据
	enum { IDD = IDD_DIALOG_CLOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonClose();
	CButton m_btnClose;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
