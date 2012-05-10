// DlgSetIP.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinSmith.h"
#include "DlgSetIP.h"
#include "../public/ShortSocket.h"


// CDlgSetIP �Ի���

IMPLEMENT_DYNAMIC(CDlgSetIP, CDialog)

CDlgSetIP::CDlgSetIP(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetIP::IDD, pParent)
	, m_strIP(_T(""))
	, m_nPort(0)
{

}

CDlgSetIP::~CDlgSetIP()
{
}

void CDlgSetIP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
}


BEGIN_MESSAGE_MAP(CDlgSetIP, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgSetIP::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CDlgSetIP::OnBnClickedBtnSearch)
END_MESSAGE_MAP()


// CDlgSetIP ��Ϣ�������

void CDlgSetIP::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (m_strIP.Trim().GetLength() == 0)
		return ;
	if (m_nPort == 0)
		return;
	USES_CONVERSION;
	CShortSocket sk;
	if (sk.TestConnect((char *)W2A(m_strIP.GetBuffer()),m_nPort,&gCfg.m_proxyOption) == false)
	{
		m_strIP.ReleaseBuffer();
		MessageBox(_T("����ָ���˿ڲ��ɹ���"),_T("��ʾ"));
		return;
	}
	m_strIP.ReleaseBuffer();

	gCfg.m_nFixedPort = m_nPort;
	char acBuf[10];
	sprintf(acBuf,"%d",m_nPort);
	WritePrivateProfileString(_T("SERVER"),_T("port"),toUnicodeString(acBuf,strlen(acBuf)),toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));

	OnOK();
}

void CDlgSetIP::OnBnClickedBtnSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CShortSocket sk;
	int nPort[5]={7709,6188,8601,9000};
	USES_CONVERSION;
	for(int n=0; n<4; n++)
	{
		if (sk.TestConnect((char *)W2A(m_strIP.GetBuffer()),nPort[n],&gCfg.m_proxyOption))
		{			
			m_strIP.ReleaseBuffer();			
			m_nPort = nPort[n];
			UpdateData(0);
			return;
		}
		m_strIP.ReleaseBuffer();
	}
	MessageBox(_T("δ���ֿ��ô˶˿ڣ�"),_T("��ʾ"));
}
