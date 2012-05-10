#pragma once
#include "OTCBaseObject.h"
#include "afxwin.h"


#define  USERNAME_MAXLENGTH  16 //用户名称最大长度为16位

// COTCLoginDialog 对话框

class COTCLoginDialog : public CDialog,COTCBaseObject
{
	DECLARE_DYNAMIC(COTCLoginDialog)

public:
	COTCLoginDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COTCLoginDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

protected:
	//加载多国语言
	virtual void LoadMultiLanguage(void);

public:
	afx_msg void OnBnClickedButtonAppsetting();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonLoginCancel();

	//进行认证时，禁用或启用登录界面的控件
	void EnableLoginCtrl(BOOL bEnable);

private:
	// 接入地址列表
	CComboBox m_CombServerList;
	//客户名
	CEdit m_editAccount;
	//登录密码
	CEdit m_editPassword;

public:
	CButton m_checkSaveAccount;
	CButton m_checkSavePassword;
	afx_msg void OnBnClickedCheckSaveAccount();
	afx_msg void OnBnClickedCheckSavePassword();
};
