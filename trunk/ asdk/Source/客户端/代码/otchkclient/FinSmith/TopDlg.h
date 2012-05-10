#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ProListCtrl.h"
// CTopDlg �Ի���
class CData;
class CTopDlg : public CDialog
{
	DECLARE_DYNAMIC(CTopDlg)

public:
	CTopDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTopDlg();

// �Ի�������
	enum { IDD = IDD_TOP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nType;
	bool m_bSelf;
	CString m_strKey;
	CProListCtrl m_lstCode;
public:
	int SetByKey(CString c_strKey);
	bool ActiveByKey(WPARAM wParam);
	void OnSelectOver();
public:
	virtual BOOL OnInitDialog();
public:
	CEdit *m_pEdit;
public:
	int SetLinkEdit(CEdit * c_pWnd,CData * c_pData,int c_nType = 0);//c_nType���ͣ�0��ֱ���Դ����滻��Edit�е����ݣ�1�����������滻,2�Դ����滻�����������3�����������滻,4��6λ����
public:
	afx_msg void OnLvnItemchangedListCode(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual void OnOK();
public:
	CXPButton m_btnHide;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg void OnBnClickedHide();
public:
	afx_msg void OnHdnItemdblclickListCode(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMDblclkListCode(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnEnterKey(WPARAM wParam,LPARAM lParam);
public:
	CData * m_pData;
	int	m_nSortField;//0���룬1ƴ��	
	CEdit m_edit;
	afx_msg void OnEnChangeEditCode();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};
