#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"

// CDlgUpdate 对话框

class CDlgUpdate : public CDialog
{
	DECLARE_DYNAMIC(CDlgUpdate)

public:
	CDlgUpdate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUpdate();

// 对话框数据
	enum { IDD = IDD_UPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	bool m_bFirstShow;
	int m_nCancel;
	CString m_strUrl;//文件下载
	CString m_strFile;//文件名称
	CString m_strInfo;//包信息
	CRect m_rectInfo;
	virtual BOOL OnInitDialog();
	void SetLayout();
	bool DownFile();
	bool DownFileDirect();
	void SetInfoRect(bool c_bMax);
	afx_msg LRESULT OnDownloadSize(WPARAM wParam,LPARAM lParam);

	CProgressCtrl m_progress;
	
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedBtnStart();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CXPButton m_btnClose;
	CXPButton m_btnStart;
	CXPButton m_btnCancel;
	CEdit m_edit;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
