#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "../winunit/IUserWin.h"

typedef struct SButtonWnd{
	CWnd * m_pButton;
	CWnd * m_pClose;
	IUserWin * m_pWnd;
}SBUTTIBWND;

struct SIndustry;
// CDlgContainer 对话框
class IUserWin;
class CDlgContainer : public CDialog
{
	DECLARE_DYNAMIC(CDlgContainer)

public:
	CDlgContainer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgContainer();

// 对话框数据
	enum { IDD = IDD_DLG_CONTAINER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:	
	int m_nHeadHeight;
	int m_nBtnHeight;
	int m_nBtnWidth;
	CXPButton m_btnMax;
	CXPButton m_btnMin;
	afx_msg void OnBnClickedBtnMax();
private:
	bool m_bInTimer;
	int	m_nReqSeq;
	int m_nAnsSeq;
public:
	void AddIUserWin(IUserWin *);
	IUserWin * GetWndByName(CString c_strName,int &c_nIndex);
	IUserWin * ActiveWnd(CString c_strName);
	IUserWin * ActiveWnd(IUserWin *);
	void SetLayout();
	void ResetSkin();
	void ResetFont();
	void Refresh();	
	CWnd * AddButtonWnd(IUserWin * c_pWnd,CString c_strTitle);	
	CHtmlView * GetNewsWnd();
	void CloseWnd(SButtonWnd * c_p);
	void SetStockCode(CString c_strCode);
	void DoSetStockCodeAction();
	void FreshData();
	void ResetButtonsPos();

	//
	bool IsBtnWnd(IUserWin * c_pWnd);
	//清除附加窗口
	void RemoveAttachWnd();
	void SetViewMode(int);
	void ShowMin();
public:
	bool m_bNoTitle;//无主题
	CString m_strStockCode;	
	int m_nViewMode;//MAX or Min
	IUserWin * m_pActiveWnd;
	std::vector<IUserWin *> m_vpIUserWin;
	std::vector<SButtonWnd *> m_vpButtonWnds;//附加的窗口，可关闭的窗口

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedBtnMin();
	afx_msg void OnBnClickedBtnTitle();
	CXPButton m_btnTitle;
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CXPButton m_btnClose;
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
