// FinSmithDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "StockWnd.h"
#include "afxcmn.h"
#include "MenuManager.h"
#include "../public/CustomMenu.h"

class CLoopWnd;
class CTopDlg;
class CWebBrowser;
class CMyHtmlView;
class CDlgDiagnose;
class CDlgKDetail;
class IUserWin;

// CFinSmithDlg 对话框
class CFinSmithDlg : public CDialog
{
// 构造
public:
	CFinSmithDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CFinSmithDlg();

// 对话框数据
	enum { IDD = IDD_FINSMITH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
	void SetLayout();//设置布局
protected:
	HICON m_hIcon;
	HICON m_hIconFail;
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnTrayNotify(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnUpdateQuoteData(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnRequestInfo(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnGroupChanged(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnUpdateNewsSet(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnConnectSuccess(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnShowNews(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnGetNewsWnd(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnGotoStock(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnExtraCommand(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSwitchPicType(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnLog(WPARAM wParam,LPARAM lParam);    
    afx_msg LRESULT SetInfoClose(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnForceQuit(WPARAM wParam,LPARAM lParam);
public:
	CMenu m_menuTray;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	NOTIFYICONDATA m_trayIcon;
	bool			m_bIcon;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnSearch();

    bool b_front;
	bool m_bZoom;
	WINDOWPLACEMENT m_WndPlace;
	bool m_bSize;
	int m_nSizeKind;
	CPoint m_ptSize;
	void SizeWindow(UINT nHitTest, CPoint point);
	void ResetSkin();
	void SetViewMode(int c_nMode);
	void FreshUserDefReport();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	
public:
	int m_nEdge;//边距
	int m_nHeadHeight;
    bool  m_bleft;
	bool  m_bFirstShow;
	CMenuManager m_menu;

	CTopDlg * m_pTopDlg;
	CDlgKDetail * m_pKDetail;//K线细节
	CLoopWnd * m_pLoopWnd;	//
	int m_nViewMode;//0正常，1显示右边窗口	
	CRect m_rectSize;
	CDlgDiagnose * m_pDiagnose;//

	int m_nLeftSideWidth;//左边宽度
	int m_nRightSideWidth;//右边宽度	

	afx_msg void OnAbout();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnQuit();
	CWnd * ShowUrl(CString c_strUrl, CWnd *c_pwndCtrl,int c_iLeft,int c_iTop,int c_iWidth,int c_iHeight,BOOL c_bModal,bool c_bTitle);
	CWnd * ShowNews(CString c_strUrl, CWnd *c_pwndCtrl,int c_iLeft,int c_iTop,int c_iWidth,int c_iHeight,BOOL c_bModal,bool c_bTitle);
	int TestWeb(CString c_strDownUrl);
	int InfoSet(int c_nInfoSet);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnClose();    
	bool m_bTryConnecting;
	IUserWin * m_pCollectSort;
	IUserWin * m_pOrgTrade;
	CCustomMenu m_CustomMenu;
public:	
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	CXPButton m_btnMin;
	CXPButton m_btnMax;
	CXPButton m_btnClose;
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnIndustrydown();
	afx_msg void OnBnClickedBtnIndustryup();
	afx_msg void OnBnClickedBtnDiagnose();
	afx_msg void OnBnClickedBtnMarket();
	afx_msg void OnBnClickedBtnMin();
	afx_msg void OnBnClickedBtnMax();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnTech();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnActivateApp(BOOL bActive, DWORD dwThreadID);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnTechRsi();
	afx_msg void OnTechKdj();
	afx_msg void OnTechMacd();
	afx_msg void OnTechBoll();
	afx_msg void OnTechGb();
	afx_msg void OnTechMa();
	afx_msg void OnTechDay();
	afx_msg void OnTechWeek();
	afx_msg void OnTechMonth();
	afx_msg void OnSkinBlack();
	afx_msg void OnSkinWhite();
	afx_msg void OnHomepage();
	afx_msg void OnBoard();
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnChangepassword();
	afx_msg void OnLic();
	afx_msg void OnTechEma();
	afx_msg void OnTechVolume();
	afx_msg void OnCycleMin1();
	afx_msg void OnCycleMin5();
	afx_msg void OnCycleMin15();
	afx_msg void OnCycleMin30();
	afx_msg void OnCycleMin60();	
	afx_msg void OnVirTrade();
	afx_msg void OnManualBook();
	afx_msg void OnRealTrade();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTechCancelAttach();
	afx_msg void OnMenuSetFont();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
};
