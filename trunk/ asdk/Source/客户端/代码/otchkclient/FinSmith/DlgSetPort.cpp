// DlgSetPort.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinSmith.h"
#include "DlgSetPort.h"
#include "../public/ShortSocket.h"

// CDlgSetPort �Ի���

IMPLEMENT_DYNAMIC(CDlgSetPort, CDialog)

CDlgSetPort::CDlgSetPort(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetPort::IDD, pParent)
{

}

CDlgSetPort::~CDlgSetPort()
{
}

void CDlgSetPort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
}


BEGIN_MESSAGE_MAP(CDlgSetPort, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgSetPort::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CDlgSetPort::OnBnClickedBtnSearch)
	ON_BN_CLICKED(IDC_BTN_SET_PORT, &CDlgSetPort::OnBnClickedBtnSetPort)
END_MESSAGE_MAP()


// CDlgSetPort ��Ϣ�������

void CDlgSetPort::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	USES_CONVERSION;
	WCHAR acBuf[11];
	memset(acBuf,0,11);
	m_editPort.GetWindowText(acBuf,10);
	int nPort = atoi(W2A(acBuf));
	if (nPort < 0)
	{
		MessageBox(_T("���벻��ȷ��"),_T("��ʾ"));
		return;
	}
	if (nPort > 0)
	{
		CShortSocket sk;
		if (sk.TestConnect((char *)gCfg.m_strDeployIP.c_str(),nPort,&gCfg.m_proxyOption) == false)
		{
			MessageBox(_T("�˶˿ڲ����ã�"),_T("��ʾ"));
			return;
		}
	}
	gCfg.m_nFixedPort = nPort;
	WritePrivateProfileString(_T("SERVER"),_T("port"),acBuf,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
	OnOK();
}

BOOL CDlgSetPort::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (gCfg.m_nFixedPort > 0)
	{
		CString str;
		str.Format(_T("%d"),gCfg.m_nFixedPort);
		m_editPort.SetWindowText(str);
	}
	else
	{
		CString str;
		str.Format(_T("%d"),gCfg.GetDeployPort());
		m_editPort.SetWindowText(str);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgSetPort::OnBnClickedBtnSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CShortSocket sk;
	int nPort[5]={7709,6188,8601,9000,8099};
	for(int n=0; n<5; n++)
	{
		if (sk.TestConnect((char *)gCfg.m_strDeployIP.c_str(),nPort[n],&gCfg.m_proxyOption) || sk.TestConnect((char *)gCfg.m_strDeployIPBak.c_str(),nPort[n],&gCfg.m_proxyOption))
		{			
			char acBuf[10];
			sprintf(acBuf,"%d",nPort[n]);
			m_editPort.SetWindowText(toUnicodeString(acBuf,strlen(acBuf)));
			return;
		}
	}
	MessageBox(_T("δ���ֿ��ô˶˿ڣ�"),_T("��ʾ"));
}

void CDlgSetPort::OnBnClickedBtnSetPort()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char acIP[32];
	char acIPBak[32];
	strcpy(acIP,gCfg.m_strDeployIP.c_str());
	strcpy(acIP,gCfg.m_strDeployIPBak.c_str());

	USES_CONVERSION;
	WCHAR acBuf[11];
	memset(acBuf,0,11);
	m_editPort.GetWindowText(acBuf,10);
	int nPort = atoi(W2A(acBuf));
	if (nPort < 0)
	{
		MessageBox(_T("���벻��ȷ��"),_T("��ʾ"));
		return;
	}
	if (nPort > 0)
	{
		CShortSocket sk;
		if (sk.TestConnect(acIP,nPort,&gCfg.m_proxyOption) == false && sk.TestConnect(acIPBak,nPort,&gCfg.m_proxyOption) == false)
		{
			MessageBox(_T("�˶˿ڲ����ã�"),_T("��ʾ"));
			return;
		}
	}
	gCfg.m_nFixedPort = nPort;
	WritePrivateProfileString(_T("SERVER"),_T("port"),acBuf,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
	OnOK();

}
