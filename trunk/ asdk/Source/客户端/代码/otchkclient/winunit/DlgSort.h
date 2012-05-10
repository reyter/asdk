#pragma once
#include "afxcmn.h"
#include "../public/StockListCtrl.h"

// CDlgSort 对话框

class CDlgSort : public CDialog,public IUserWin
{
	DECLARE_DYNAMIC(CDlgSort)

public:
	CDlgSort(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSort();

// 对话框数据
	enum { IDD = IDD_DLG_SORT };
	void SetLayout();
	void SetStockList();
	void FreshData();
	void GetData();
	void DoCommand(int);
	void ResetSkin();
public:
	CWnd * GetWnd(){return this;};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	unsigned short	m_usSortType;
	CStockListCtrl m_listA;
	CStockListCtrl m_listB;
	CStockListCtrl m_listBuy;
	CStockListCtrl m_listSell;
	CStockListCtrl m_listTrup;
	CStockListCtrl m_listTrdown;

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnNMDblclkListA(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListB(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMDblclkListBuy(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListSell(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListTradeareaDown(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListTradeareaUp(NMHDR *pNMHDR, LRESULT *pResult);
};
