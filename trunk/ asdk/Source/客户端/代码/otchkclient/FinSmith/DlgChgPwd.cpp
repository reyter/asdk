// DlgChgPwd.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "DlgLogin.h"
#include "..\\public\\md5.h"
#include "..\\public\\deslib.h"
#include "DlgChgPwd.h"


// CDlgChgPwd 对话框

IMPLEMENT_DYNAMIC(CDlgChgPwd, CDialog)

CDlgChgPwd::CDlgChgPwd(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChgPwd::IDD, pParent)
	, m_strPwd(_T(""))
	, m_strPwdNew(_T(""))
	, m_strPwdNew2(_T(""))
{

}

CDlgChgPwd::~CDlgChgPwd()
{
}

void CDlgChgPwd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPwd);
	DDX_Control(pDX, IDC_EDIT_PWD_NEW, m_editPwdNew);
	DDX_Control(pDX, IDC_EDIT_PWD_NEW_2, m_editPwdNew2);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	DDX_Text(pDX, IDC_EDIT_PWD_NEW, m_strPwdNew);
	DDX_Text(pDX, IDC_EDIT_PWD_NEW_2, m_strPwdNew2);
}


BEGIN_MESSAGE_MAP(CDlgChgPwd, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgChgPwd::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgChgPwd 消息处理程序

void CDlgChgPwd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strPwd.Trim();
	m_strPwdNew.Trim();
	m_strPwdNew2.Trim();
	if (m_strPwd.IsEmpty())
	{
		MessageBox(_T("当前密码不能为空!"),_T("提示"),MB_OK);
		return;
	}
	if (m_strPwdNew.IsEmpty())
	{
		MessageBox(_T("新密码不能为空!"),_T("提示"),MB_OK);
		return;
	}
	if (m_strPwdNew.GetLength() > 16)
	{
		MessageBox(_T("新密码长度超过16位!"),_T("提示"),MB_OK);
		return;
	}

	if (m_strPwdNew != m_strPwdNew2)
	{
		MessageBox(_T("两次输入密码不一致!"),_T("提示"),MB_OK);
		return;
	}
	CDlgLogin log;
	char acPass[64],acPassNew[64];
	memset(acPass,0,sizeof(acPass));
	memset(acPassNew,0,sizeof(acPassNew));
	unicodeToAscii(m_strPwd,acPass,31);
	unicodeToAscii(m_strPwdNew,acPassNew,31);
	
	MD5_Sig_Get((unsigned char *)(acPass),strlen(acPass),acPass + 16,32);	
	MD5_Sig_Get((unsigned char *)(acPassNew),strlen(acPassNew),acPassNew + 16,32);	

	//USES_CONVERSION;
	char acPassDes[64];
	char acPassNewDes[64];
	Encrypt(acPass,48,acPassDes,gCfg.m_acDesKey);
	Encrypt(acPassNew,48,acPassNewDes,gCfg.m_acDesKey);
	//bool bSucc = log.ChangePass((char *)gCfg.m_strUser.c_str(),acPassDes,acPassNewDes);
	bool bSucc = log.ChangePass(gpData->m_nUserID,acPass,acPassNew);
	//bool bSucc = log.ChangePass((char *)gCfg.m_strUser.c_str(),(char *)W2A(m_strPwd.GetBuffer()),(char *)W2A(m_strPwdNew.GetBuffer()));
	//m_strPwd.ReleaseBuffer();
	//m_strPwdNew.ReleaseBuffer();
	if (bSucc)
	{
		MessageBox(_T("密码修改成功！"),_T("提示"),MB_OK);
		WCHAR wcRet[17];
		wcRet[16] = 0;
		GetPrivateProfileString(_T("LOGINSET"),_T("pass"),_T(""),wcRet,16,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
		if (lstrlen(wcRet) > 0)
			WritePrivateProfileString(_T("LOGINSET"),_T("pass"),m_strPwdNew,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
	}
	else
	{
		MessageBox(_T("用户名或密码错误！"),_T("提示"),MB_OK);
		return;
	}
	OnOK();
}
