
/************************************************************************/
/*         所有股票列表显示                                                             */
/************************************************************************/



#pragma once
#include "afxcmn.h"
#include "../public/stocklistctrl.h"

// CDlgList 对话框

class CDlgList : public CDialog
{
	DECLARE_DYNAMIC(CDlgList)

public:
	CDlgList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgList();

// 对话框数据
	enum { IDD = IDD_DLG_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nHeadHeight;//头高
	int m_nItemHeight;//行高			
	//CFont *m_pListFont;
	int m_nCurPage;
	int m_nPageItemBegin;//开始序号
	int m_nPageItemCount;//每页项目数量
	int m_nCurSel;//当前选中行

	int m_nBeginPaintCol;//开始绘制列,默认是3
	int m_nBeginPaintColMax;//开始绘制列的最大
	
	int m_nListCode;//列表代码
	int m_nSortedCol;//排序列
	BOOL m_bAsc;//升序
	SStock * m_pStock[100];
	int m_nValid;//有效数量
	void CalcBeginPaintCol(CRect c_rect);
	void SetSortCol(int);
	void ProcSort();
	void SetLayout();
	void SetItems(int c_nCode,int c_nSortCol=3,BOOL c_bAsc=FALSE);
	void SetPage();
	void ResetPage();
	void GetReport(bool,bool c_bAttach);
	void FreshData();
	void FreshHideData();
	void GoPage(int);
	void DrawSelf(CDC * pDC);
	void PaintList(CDC *,CRect);
	//更新列表
	void FreshList();
	int ParseData(char *,int);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void PreSubclassWindow();
public:
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnNMDblclkStocks(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);	
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLvnItemchangedListHide(NMHDR *pNMHDR, LRESULT *pResult);
	CStockListCtrl m_lstHide;
	afx_msg void OnNMDblclkListHide(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	CSpinButtonCtrl m_spin;
	afx_msg void OnDeltaposSpinFields(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
