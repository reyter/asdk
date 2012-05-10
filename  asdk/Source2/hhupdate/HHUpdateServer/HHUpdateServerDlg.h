// HHUpdateServerDlg.h : 头文件
//

#pragma once
#include "IOCPServer.h"

// CHHUpdateServerDlg 对话框
class CHHUpdateServerDlg : public CDialog
{
// 构造
public:
	CHHUpdateServerDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CHHUpdateServerDlg();

// 对话框数据
	enum { IDD = IDD_HHUPDATESERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void ShowMsg(CString strMsg,BOOL bClear = FALSE);
	afx_msg void OnBnClickedBtnStart();
	CIOCPServer m_IocpServer;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnSet();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
