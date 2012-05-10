#pragma once
#include "afxwin.h"

#include "../public/TransparentStatic.h"

const int PICMAX	= 0;	//仅图形
const int PICANDSUB = 1;	//并存
const int SUBMAX	= 2;	//仅仅信息

const int PICPIC	= 100;	//分时和K线
const int PICLIST	= 101;	//列表

class CPics;
class CDlgContainer;
class CPicWnd;
class CRightWnd;
class CFlatSplitterWnd;
class CMyHtmlView;
class CMoveWnd;
class CDlgTrade;
class CEmptyWnd;
class IUserWin;
// CDlgDiagnose 对话框
class CTopDlg;
class CDlgDiagnose : public CDialog
{
	DECLARE_DYNAMIC(CDlgDiagnose)

public:
	CDlgDiagnose(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDiagnose();

// 对话框数据
	enum { IDD = IDD_STOCKDIAGNOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//{{AFX_MSG(CDlgDiagnose)
	afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual int OnToolHitTest(CPoint point, TOOLINFO * pTI) const;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void SetStockCode(CString c_strCode);
	void SetViewType(int c_nViewType);
	void SetSubType(int c_nSubType);
	void SetTopDlg(CTopDlg * c_pTopDlg);
	void SetLayout();
	void ResetSkin();
	void ResetFont();
	void ShowTradeWnd();
	void FreshData(int);
	void Refresh();
	void OnConnectSuccess();
	CWnd * GetWnd(){return this;};
public:	
	int m_nViewType;//显示方式
	int m_nSubType;//下面的类型
	int m_nSizeMode;
	CRect m_rectSize;
	CMoveWnd * m_pMove;
	CDlgContainer * m_pContainer;
	CPics * m_pPics;
	CTopDlg * m_pTopDlg;
	CMyHtmlView * m_pWebPage;
	CDlgTrade * m_pTrade;
	CEmptyWnd * m_pNull;
	CFlatSplitterWnd * m_pSplit;
	CString m_strStockCode;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	afx_msg LRESULT OnContainerMsg(WPARAM wParam,LPARAM lParam);	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
