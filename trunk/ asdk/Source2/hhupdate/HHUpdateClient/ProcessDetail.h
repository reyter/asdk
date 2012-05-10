#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "TransParentButton.h"
#include "ProcessCtrl.h"
// CProcessDetail 对话框

class CProcessDetail : public CDialog
{
	DECLARE_DYNAMIC(CProcessDetail)

public:
	CProcessDetail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProcessDetail();

// 对话框数据
	enum { IDD = IDD_DLG_PROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_ListCtrl_ShowProcess;
	virtual BOOL OnInitDialog();
	void InitList();
	void InitListData();
	bool KillProcess(DWORD dwPid);
	/*CTransParentButton*/CButton m_btnEndProcess;
	/*CTransParentButton*/CButton m_btnEndAllProcess;
	THELSMD m_ListMD;
protected:
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedBtnEndprocess();
	afx_msg void OnBnClickedBtnEndallprocess();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	void SprintfCList();
};
