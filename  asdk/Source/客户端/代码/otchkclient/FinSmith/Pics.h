#pragma once


// CPics
class CPicWnd;
class CRightWnd;
class CDlgList;
class CTraceWnd;
class CPics : public CWnd
{
	DECLARE_DYNAMIC(CPics)

public:
	CPics();
	virtual ~CPics();

protected:
	DECLARE_MESSAGE_MAP()

public:
	void SetViewType(int c_nViewType);
	void SetViewMode(int c_nViewMode);
	void SetLayout();
	void SetStockCode(CString c_strCode);
	void FreshData(int);
	int SetWins();
	void GotoStockList(int c_nCode,int c_nSortCol=3,bool c_bAsc=true);
	void GotoTraceWnd();
	void EscapeTraceWnd();
	void Refresh();
	void GetReport(bool);
public:
	int m_nViewType;//显示类型
	int m_nViewMode;//显示模式
	bool m_bInGetReport;
	CString m_strStockCode;
	CPicWnd * m_pPicWnd;
	CRightWnd * m_pRightWnd;
	CDlgList * m_pList;
	CTraceWnd * m_pTrace;
		
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


