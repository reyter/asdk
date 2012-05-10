// DlgParamSet.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "TechManager.h"
#include "DlgParamSet.h"


// CDlgParamSet 对话框
CTechManager * CTechManager::m_instance = NULL;

IMPLEMENT_DYNAMIC(CDlgParamSet, CDialog)

CDlgParamSet::CDlgParamSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParamSet::IDD, pParent)
{
	m_unEditID[0] = IDC_EDIT_1;
	m_unEditID[1] = IDC_EDIT_2;
	m_unEditID[2] = IDC_EDIT_3;
	m_unEditID[3] = IDC_EDIT_4;
	m_unEditID[4] = IDC_EDIT_5;
	m_unEditID[5] = IDC_EDIT_6;
	m_unEditID[6] = IDC_EDIT_7;
	m_unEditID[7] = IDC_EDIT_8;		
	
	m_unStaticID[0] = IDC_STATIC_1;
	m_unStaticID[1] = IDC_STATIC_2;
	m_unStaticID[2] = IDC_STATIC_3;
	m_unStaticID[3] = IDC_STATIC_4;
	m_unStaticID[4] = IDC_STATIC_5;
	m_unStaticID[5] = IDC_STATIC_6;
	m_unStaticID[6] = IDC_STATIC_7;
	m_unStaticID[7] = IDC_STATIC_8;	

	m_bChanged = false;
	m_stTech.Init();
}

CDlgParamSet::~CDlgParamSet()
{
}

void CDlgParamSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgParamSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDlgParamSet::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDOK, &CDlgParamSet::OnBnClickedOk)	
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgParamSet::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgParamSet::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CDlgParamSet 消息处理程序

void CDlgParamSet::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_stTech.m_bDefault = true;
	InitData();
	SetViewItems();
}

void CDlgParamSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	WCHAR acBuf[16];
	USES_CONVERSION;
	bool bChange = false;
	for(int n=0; n<m_stTech.m_nParamCount; n++)
	{
		memset(acBuf,0,sizeof(acBuf));
		GetDlgItemText(m_unEditID[n],acBuf,15);
		if (strcmp(W2A(acBuf),m_stTech.m_acParams[n]) != 0)
		{
			strcpy(m_stTech.m_acParams[n],W2A(acBuf));
			bChange = true;
		}
	}
	if (m_nParamCount != m_stTech.m_nParamCount)
		bChange = true;

	if (bChange)
	{
		m_stTech.m_bDefault = false;		
		CTechManager::getInstance()->setTech(&m_stTech);
		m_bChanged = bChange;
	}
	OnOK();
}

void CDlgParamSet::InitData()
{
	m_stTech.m_strName = m_strTech;
	m_stTech.m_bMainPic = m_bMainPic;
	m_stTech.m_usCycle = m_usCycle;
	CTechManager::getInstance()->getTech(&m_stTech);
	m_nParamCount = m_stTech.m_nParamCount;
}

void CDlgParamSet::SetViewItems()
{	
	int m_nBegin;
	if (m_stTech.m_nParamCount <= 0)
	{
		m_nBegin = 0;
	}
	else
		m_nBegin = m_stTech.m_nParamCount;
	
	for(int n=m_nBegin; n<8; n++)
	{
		GetDlgItem(m_unEditID[n])->ShowWindow(SW_HIDE);
		GetDlgItem(m_unStaticID[n])->ShowWindow(SW_HIDE);
	}

///-	char acBuf[64];
	for(int n=0; n<m_nBegin; n++)
	{
		GetDlgItem(m_unEditID[n])->SetWindowText(toUnicodeString(m_stTech.m_acParams[n],strlen(m_stTech.m_acParams[n])));
		GetDlgItem(m_unStaticID[n])->SetWindowText(toUnicodeString(m_stTech.m_acDescs[n],strlen(m_stTech.m_acDescs[n])));
	}

	if (m_stTech.m_bCanAdd)
	{
		GetDlgItem(IDC_BUTTON_ADD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_DELETE)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_ADD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_DELETE)->ShowWindow(SW_HIDE);
	}
}
BOOL CDlgParamSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strTitle;
	strTitle = _T("[");
	strTitle += m_strTech;
	strTitle += _T("]指标参数调整");
	SetWindowText(strTitle);
	InitData();
	SetViewItems();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgParamSet::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	m_stTech.m_nParamCount++;
	if (m_stTech.m_nParamCount > 8)
	{
		m_stTech.m_nParamCount = 8;	
	}
	else
	{
		GetDlgItem(m_unEditID[m_stTech.m_nParamCount-1])->ShowWindow(SW_SHOW);
		GetDlgItem(m_unStaticID[m_stTech.m_nParamCount-1])->ShowWindow(SW_SHOW);
		strcpy(m_stTech.m_acDescs[m_stTech.m_nParamCount-1],m_stTech.m_acDescs[m_stTech.m_nParamCount-2]);

		GetDlgItem(m_unEditID[m_stTech.m_nParamCount-1])->SetWindowText(toUnicodeString(m_stTech.m_acParams[m_stTech.m_nParamCount-1],strlen(m_stTech.m_acParams[m_stTech.m_nParamCount-1])));
		GetDlgItem(m_unStaticID[m_stTech.m_nParamCount-1])->SetWindowText(toUnicodeString(m_stTech.m_acDescs[m_stTech.m_nParamCount-1],strlen(m_stTech.m_acDescs[m_stTech.m_nParamCount-1])));
	}
}

void CDlgParamSet::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	m_stTech.m_nParamCount--;
	if (m_stTech.m_nParamCount < 1)
		m_stTech.m_nParamCount = 1;
	else
	{
		GetDlgItem(m_unEditID[m_stTech.m_nParamCount])->ShowWindow(SW_HIDE);
		GetDlgItem(m_unStaticID[m_stTech.m_nParamCount])->ShowWindow(SW_HIDE);
	}
	
}
