// OTCLoginDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include "OTCHK_Client.h"
#include "OTCLoginDialog.h"
#include "CommonData.h"
#include "Connenct\DataComm.h"
#include "Common\CommonFunc.h"
#include "Common\GlobalMacro.h"
#include "Connenct\ShortSocket.h"
#include "Connenct\CommSocket.h"
#include "Connenct\SocketFactory.h"

#include <vector>
#include <afxsock.h>
#include "AppSetting.h"
#include "Connenct\ServerMg.h"
#include <winsock.h>
#include "Common\RegistryUtil.h"

// COTCLoginDialog 对话框

IMPLEMENT_DYNAMIC(COTCLoginDialog, CDialog)

COTCLoginDialog::COTCLoginDialog(CWnd* pParent /*=NULL*/)
: CDialog(COTCLoginDialog::IDD, pParent)
{
	
}

COTCLoginDialog::~COTCLoginDialog()
{
	
}

void COTCLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SERVER, m_CombServerList);
	DDX_Control(pDX, IDC_EDIT_CUSTOMERID, m_editAccount);
	DDX_Control(pDX, IDC_EDIT_LOGIN_PWD, m_editPassword);
	DDX_Control(pDX, IDC_CHECK_SAVE_ACCOUNT, m_checkSaveAccount);
	DDX_Control(pDX, IDC_CHECK_SAVE_PASSWORD, m_checkSavePassword);
}


BEGIN_MESSAGE_MAP(COTCLoginDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_APPSETTING, &COTCLoginDialog::OnBnClickedButtonAppsetting)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &COTCLoginDialog::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN_CANCEL, &COTCLoginDialog::OnBnClickedButtonLoginCancel)
	ON_BN_CLICKED(IDC_CHECK_SAVE_ACCOUNT, &COTCLoginDialog::OnBnClickedCheckSaveAccount)
	ON_BN_CLICKED(IDC_CHECK_SAVE_PASSWORD, &COTCLoginDialog::OnBnClickedCheckSavePassword)
END_MESSAGE_MAP()


// COTCLoginDialog 消息处理程序

BOOL COTCLoginDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadMultiLanguage();

	//账号最大字符字为16
	m_editAccount.LimitText(USERNAME_MAXLENGTH);


	CServer fixedSvr;
	CAppSetting::GetInstance().GetFixedServer(fixedSvr);

	//是否记住账号
	if (CAppSetting::GetInstance().IsSaveAccount())
	{
		m_checkSaveAccount.SetCheck(TRUE);
		m_editAccount.SetWindowText(CAppSetting::GetInstance().GetAccount());
	}
	else
	{
		m_checkSaveAccount.SetCheck(FALSE);
		m_editAccount.SetWindowText(_T(""));
	}
	
	//是否保存密码
	if (CAppSetting::GetInstance().IsSavePassword())
	{
		m_checkSaveAccount.SetCheck(TRUE);
		m_checkSavePassword.SetCheck(TRUE);
		m_editAccount.SetWindowText(CAppSetting::GetInstance().GetAccount());
		m_editPassword.SetWindowText(CAppSetting::GetInstance().GetPassword());
	}
	else
	{
		m_checkSavePassword.SetCheck(FALSE);
		m_editPassword.SetWindowText(_T(""));
	}

	//添加服务器列表
	m_CombServerList.Clear();
	std::vector<CServerGroup>::iterator iter, itend;
	std::vector<CServerGroup>& vtServerGroups = CServerFactory::GetInstance().GetServerGroup();
	for (iter = vtServerGroups.begin(); iter != vtServerGroups.end();iter++)
	{
		m_CombServerList.AddString(iter->m_strGroupName);
	}
	m_CombServerList.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void COTCLoginDialog::LoadMultiLanguage( void )
{
	DLG_LOADSTRING(IDD_DIALOG_LOGIN);
	CTRL_LOADSTRING(IDC_STATIC_SERVER_ADDRESS);
	CTRL_LOADSTRING(IDC_STATIC_CUSTOMERID);
	CTRL_LOADSTRING(IDC_STATIC_LOGIN_PWD);
	CTRL_LOADSTRING(IDC_BUTTON_APPSETTING);
	CTRL_LOADSTRING(IDC_BUTTON_LOGIN);
	CTRL_LOADSTRING(IDC_BUTTON_LOGIN_CANCEL);
}



void COTCLoginDialog::OnBnClickedButtonAppsetting()
{
	// TODO: 在此添加控件通知处理程序代码
}

void COTCLoginDialog::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码

	//判断用户名与密码是否为空
	CString strAccount;
	m_editAccount.GetWindowText(strAccount);
	strAccount.Trim();
	if (strAccount.IsEmpty())
	{
		AfxMessageBox(_T("账号为空，请输入账号。"));
		m_editAccount.SetFocus();
		return;
	}

	CString strPassword;
	m_editPassword.GetWindowText(strPassword);
	strPassword.Trim();
	if (strPassword.IsEmpty())
	{
		AfxMessageBox(_T("密码为空，请输入密码。"));
		m_editPassword.SetFocus();
		return;
	}
	
	//获取用户选择的服务器地址
	CString strServerGroup;
	CServer AuthSvr;
	m_CombServerList.GetWindowText(strServerGroup);
	std::vector<CServerGroup>::iterator iter, itend;
	std::vector<CServerGroup>& vtServerGroups = CServerFactory::GetInstance().GetServerGroup();
	for (iter = vtServerGroups.begin(); iter != vtServerGroups.end();iter++)
	{
		if (strServerGroup == iter->m_strGroupName)
		{
			AuthSvr = iter->m_AuthSvr;
		}
	}

	if (RETVAL_SUCCESS == theApp.m_Authentication.Login(AuthSvr,strAccount,strPassword))
	{
		AfxMessageBox(_T("认证成功"));
		OnOK();
	}
	else
	{
		AfxMessageBox(_T("认证失败"));
	}
}

void COTCLoginDialog::OnBnClickedButtonLoginCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void COTCLoginDialog::OnBnClickedCheckSaveAccount()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bSave = m_checkSaveAccount.GetCheck();
	CAppSetting::GetInstance().SetSaveAccount(bSave);
}

void COTCLoginDialog::OnBnClickedCheckSavePassword()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bSave = m_checkSavePassword.GetCheck();
	CAppSetting::GetInstance().SetSavePassword(bSave);
}

void COTCLoginDialog::EnableLoginCtrl( BOOL bEnable )
{
	m_checkSaveAccount.EnableWindow(bEnable);
	m_checkSavePassword.EnableWindow(bEnable);
	m_CombServerList.EnableWindow(bEnable);
	m_editAccount.EnableWindow(bEnable);
	m_editPassword.EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_APPSETTING)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_LOGIN)->EnableWindow(bEnable);
}
