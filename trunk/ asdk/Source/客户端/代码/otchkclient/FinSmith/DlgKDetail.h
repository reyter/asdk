/************************************************************************/
/* 浮动K线详情板                                                                     */
/************************************************************************/


#pragma once


// CDlgKDetail 对话框
class CPicWnd;
class CDlgKDetail : public CDialog
{
	DECLARE_DYNAMIC(CDlgKDetail)

public:
	CDlgKDetail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgKDetail();

// 对话框数据
	enum { IDD = IDD_K_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void PaintMe(CDC * c_pDC);
	void SetSSTOCK(SStock * c_pStock);
	void SetKLINE(KLINE * c_pKLine,int c_nZrsp,int c_nCycle);	
	void SetDefaultRect(CRect);
	bool IsDefaultRect(CRect);
	KLINE m_kline;
	SStock *m_pStock;
	int m_nZrsp;
	int m_nCycle;
	CPicWnd * m_pPicWnd;
	CRect m_rectDefault;//默认位置
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
