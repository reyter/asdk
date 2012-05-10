
/************************************************************************/
/*         ���й�Ʊ�б���ʾ                                                             */
/************************************************************************/



#pragma once
#include "afxcmn.h"
#include "../public/stocklistctrl.h"

// CDlgList �Ի���

class CDlgList : public CDialog
{
	DECLARE_DYNAMIC(CDlgList)

public:
	CDlgList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgList();

// �Ի�������
	enum { IDD = IDD_DLG_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nHeadHeight;//ͷ��
	int m_nItemHeight;//�и�			
	//CFont *m_pListFont;
	int m_nCurPage;
	int m_nPageItemBegin;//��ʼ���
	int m_nPageItemCount;//ÿҳ��Ŀ����
	int m_nCurSel;//��ǰѡ����

	int m_nBeginPaintCol;//��ʼ������,Ĭ����3
	int m_nBeginPaintColMax;//��ʼ�����е����
	
	int m_nListCode;//�б����
	int m_nSortedCol;//������
	BOOL m_bAsc;//����
	SStock * m_pStock[100];
	int m_nValid;//��Ч����
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
	//�����б�
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
