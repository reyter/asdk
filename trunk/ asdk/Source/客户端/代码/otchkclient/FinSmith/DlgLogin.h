
/************************************************************************/
/* 登录窗口                                                                     */
/************************************************************************/


#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "../public/ShortSocket.h"
#include "..\public\xpbutton.h"

// CDlgLogin 对话框

class CDlgLogin : public CDialog
{
	DECLARE_DYNAMIC(CDlgLogin)

public:
	CDlgLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLogin();

// 对话框数据
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HICON m_hIcon;
	CImage m_imgLogHead;
	CSymbolEdit m_editName;
	CEdit m_editPassword;
	//CTransCheckBox m_ckPassword;
	CButton m_ckPassword;
	CString m_strName;
	CString m_strPassword;	
	BOOL m_bSavePassword;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	//CTransCheckBox m_ckAutoLogin;
	CButton	m_ckAutoLogin;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	int m_nViewType;//0 正常，1忘记密码，2注册
	void SetViewSize();
	afx_msg void OnStnClickedStaticReg();
	afx_msg void OnStnClickedStaticPass();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	int m_nMouseIN;//0 无，1在注册，2在密码
	afx_msg void OnStnClickedStaticReget();
	void DrawVerifyCode(CDC * c_pDC,CRect &rect);
	char m_acVerifyCode[5];

	CBitmap m_loginCheckBK;
	CBitmap m_regBK;
	CBrush m_br;
	CBrush m_brReg;

	CWnd * m_pWait;
	bool m_bDownRet;
	bool m_bInitDataOver;//下载数据完成

	bool m_bToGetSvrList;

	int m_nActiveGG;
	CString m_strUserName;
	CString m_strEMail;
	CString m_strMobile;	

	CShortSocket m_sk;
	void RegAutoRun(BOOL c_bAutoRun);

	bool ChangePass(char *c_pName,char * c_pPass, char * c_pNewPass);
	bool ChangePass(int,char *,char *);
	bool CheckVersion();
	bool GetStockBaseData(CShortSocket &c_sk);
	int GetUpgradeFile(CShortSocket &c_sk,HWND c_hwnd);	
	bool DoUpgrade();
	
	bool ForceQuit();
	bool GetStockInfo(CShortSocket &c_sk);	
	bool GetServerListData();
	bool CreateConnect(int);	

	void PaintMe(CDC * c_pDC);
	bool GetInitData(CShortSocket &c_sk);	
	void DownDataOver(bool);
	
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonActive();
	afx_msg void OnBnClickedButtonLogNow();
	afx_msg void OnEnKillfocusEditName();
	afx_msg void OnEnSetfocusEditName();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedStaticUpgrade();
	CXPButton m_btnNotUser;
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnNotuser();
	CXPButton m_btnClose;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedLogon();
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	virtual INT_PTR DoModal();
	afx_msg void OnBnClickedCheckAutorun();
	CXPButton m_btnLog;
};
