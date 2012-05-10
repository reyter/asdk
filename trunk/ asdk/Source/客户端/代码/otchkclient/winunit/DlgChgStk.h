#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "../public/XPButton.h"
#include "../public/StockListCtrl.h"
#include "IUserWin.h"
#include "Resource.h"

// CDlgChgStk 对话框

class CDlgChgStk : public CDialog,public IUserWin
{
	DECLARE_DYNAMIC(CDlgChgStk)

public:
	CDlgChgStk(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgChgStk();

// 对话框数据
	enum { IDD = IDD_DLG_CHANGE_STOCK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	bool m_bFixed;
	CString m_strStockCode;
	CString m_strStockName;	
	CString m_strMemo;
	CStockListCtrl m_listStocks;
	CXPButton m_btnAdd;	
	char m_acIndu[1024];
	char m_acValue[1024];
	char m_acPE[1024];
	char m_acPrice[1024];
	char m_acArea[1024];

	int m_nHeadHeight;
	int m_nBtnHeight;
	int m_nBtnWidth;

	int m_nTopIndexLast;
	int m_nCountPageLast;

	void CheckTimer();
	virtual BOOL OnInitDialog();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnBnClickedBtnAdd();
	CXPButton m_btnValue;
	CXPButton m_btnIndu;
	afx_msg void OnBnClickedBtnSamePe();
	CXPButton m_btnPE;
	HBITMAP m_hBmp;
	HBITMAP m_hBmpHead;
	void SetLayout();
	void ResetSkin();
	void SetTitle(CString);
	void GetTitle(CString &c_strIn);
	bool IsTitle(CString c_strIn);
	void GetViewTitle(CString &c_strIn);
	void SetList(int c_nType);
	void SetStockCode(CString c_str);
	void FreshData();
	void DoCommand(int);
	int MakeStockChangeReq(char * c_pBuf,char *c_pCode,char * c_pFields);
	void SetTips();
	CWnd * GetWnd(){return this;};
	void SetUserDefReportItem();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedBtnSameValue();
	afx_msg void OnBnClickedBtnSameIndustry();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnNMDblclkListStocks(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnSamePrice();
	CXPButton m_btnSamePrice;
	afx_msg void OnBnClickedBtnSameArea();
	CXPButton m_btnSameArea;
	virtual BOOL DestroyWindow();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
