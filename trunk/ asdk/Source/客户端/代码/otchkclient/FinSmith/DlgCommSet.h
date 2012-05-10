#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDlgCommSet �Ի���

class CDlgCommSet : public CDialog
{
	DECLARE_DYNAMIC(CDlgCommSet)

public:
	CDlgCommSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCommSet();

// �Ի�������
	enum { IDD = IDD_DLG_COMM_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listServ;
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedBtnSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSetPort();
	CEdit m_editProxyIP;
	CEdit m_editProxyPort;
	CEdit m_editProxyUser;
	CEdit m_editProxyPass;
	CButton m_checkProxy;
	int m_bSocket4;
	int m_bSocket5;
	int m_bHttp;
	
	afx_msg void OnBnClickedCheckProxy();
	afx_msg void OnBnClickedCancel();
	CButton m_btnProxyTest;
	CButton m_btnProxySave;
	afx_msg void OnBnClickedButtonProxyTest();
	afx_msg void OnBnClickedButtonProxySave();
	void SetProxyOption();
	void GetProxyOption();
	CButton m_ckUseHttpHead;
};
