// OTCLoginDialog.cpp : ʵ���ļ�
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

// COTCLoginDialog �Ի���

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


// COTCLoginDialog ��Ϣ�������

BOOL COTCLoginDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadMultiLanguage();

	//�˺�����ַ���Ϊ16
	m_editAccount.LimitText(USERNAME_MAXLENGTH);


	CServer fixedSvr;
	CAppSetting::GetInstance().GetFixedServer(fixedSvr);

	//�Ƿ��ס�˺�
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
	
	//�Ƿ񱣴�����
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

	//��ӷ������б�
	m_CombServerList.Clear();
	std::vector<CServerGroup>::iterator iter, itend;
	std::vector<CServerGroup>& vtServerGroups = CServerFactory::GetInstance().GetServerGroup();
	for (iter = vtServerGroups.begin(); iter != vtServerGroups.end();iter++)
	{
		m_CombServerList.AddString(iter->m_strGroupName);
	}
	m_CombServerList.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void COTCLoginDialog::OnBnClickedButtonLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�ж��û����������Ƿ�Ϊ��
	CString strAccount;
	m_editAccount.GetWindowText(strAccount);
	strAccount.Trim();
	if (strAccount.IsEmpty())
	{
		AfxMessageBox(_T("�˺�Ϊ�գ��������˺š�"));
		m_editAccount.SetFocus();
		return;
	}

	CString strPassword;
	m_editPassword.GetWindowText(strPassword);
	strPassword.Trim();
	if (strPassword.IsEmpty())
	{
		AfxMessageBox(_T("����Ϊ�գ����������롣"));
		m_editPassword.SetFocus();
		return;
	}
	
	//��ȡ�û�ѡ��ķ�������ַ
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
		AfxMessageBox(_T("��֤�ɹ�"));
		OnOK();
	}
	else
	{
		AfxMessageBox(_T("��֤ʧ��"));
	}
}

void COTCLoginDialog::OnBnClickedButtonLoginCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}


void COTCLoginDialog::OnBnClickedCheckSaveAccount()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL bSave = m_checkSaveAccount.GetCheck();
	CAppSetting::GetInstance().SetSaveAccount(bSave);
}

void COTCLoginDialog::OnBnClickedCheckSavePassword()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
