#pragma once
#include "afxwin.h"


// CDlgWaitData 对话框

class CDlgWaitData : public CDialog
{
	DECLARE_DYNAMIC(CDlgWaitData)

public:
	CDlgWaitData(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWaitData();

// 对话框数据
	enum { IDD = IDD_DLG_WAIT_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	CStatic m_stInfo;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnDataProgress(WPARAM wParam,LPARAM lParam);
	void SetDataInfo(CString c_strInfo);	
	CString m_strInfo;	
	int m_nCycle;
	int m_nTotal;
	int m_nNow;
	CImage m_imgInfo;
protected:
    virtual void PostNcDestroy();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
};
