#pragma once
#include "afxcmn.h"


// CDlgOrgTrade �Ի���
class CGridList;
class CTrdGrid;
class CDlgOrgTrade : public CDialog,public IUserWin
{
	DECLARE_DYNAMIC(CDlgOrgTrade)

public:
	CDlgOrgTrade(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgOrgTrade();

// �Ի�������
	enum { IDD = IDD_DLG_ORGTRADE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void DoCommand(int);
	CWnd * GetWnd(){return this;};
	void GetData();
public:
	CListCtrl m_listTrade;
	CTrdGrid *m_pGrid;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkListTrade(NMHDR *pNMHDR, LRESULT *pResult);
};
