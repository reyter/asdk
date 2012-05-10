// DlgCommSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinSmith.h"
#include "DlgCommSet.h"
#include "DlgLogin.h"
#include "DlgSetPort.h"
#include "../public/ShortSocket.h"
#include "ping.h"

// CDlgCommSet �Ի���

IMPLEMENT_DYNAMIC(CDlgCommSet, CDialog)

CDlgCommSet::CDlgCommSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCommSet::IDD, pParent)
	, m_bSocket4(0)
	, m_bSocket5(0)
	, m_bHttp(0)
{
}

CDlgCommSet::~CDlgCommSet()
{
}

void CDlgCommSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SERVER, m_listServ);
	DDX_Control(pDX, IDC_EDIT_PROXY_IP, m_editProxyIP);
	DDX_Control(pDX, IDC_EDIT_PROXY_PORT, m_editProxyPort);
	DDX_Control(pDX, IDC_EDIT_PROXY_USER, m_editProxyUser);
	DDX_Control(pDX, IDC_EDIT_PROXY_PASS, m_editProxyPass);
	DDX_Control(pDX, IDC_CHECK_PROXY, m_checkProxy);
	DDX_Control(pDX, IDC_BUTTON_PROXY_TEST, m_btnProxyTest);
	DDX_Control(pDX, IDC_BUTTON_PROXY_SAVE, m_btnProxySave);
	DDX_Control(pDX, IDC_CHECK_HTTP, m_ckUseHttpHead);
}


BEGIN_MESSAGE_MAP(CDlgCommSet, CDialog)
	ON_BN_CLICKED(IDC_BTN_TEST, &CDlgCommSet::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_SET, &CDlgCommSet::OnBnClickedBtnSet)
	ON_BN_CLICKED(IDC_BTN_SET_PORT, &CDlgCommSet::OnBnClickedBtnSetPort)
	ON_BN_CLICKED(IDC_CHECK_PROXY, &CDlgCommSet::OnBnClickedCheckProxy)
	ON_BN_CLICKED(IDCANCEL, &CDlgCommSet::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_PROXY_TEST, &CDlgCommSet::OnBnClickedButtonProxyTest)
	ON_BN_CLICKED(IDC_BUTTON_PROXY_SAVE, &CDlgCommSet::OnBnClickedButtonProxySave)
END_MESSAGE_MAP()


// CDlgCommSet ��Ϣ�������

void CDlgCommSet::OnBnClickedBtnTest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	CDlgLogin log;
	if (log.GetServer() == false)
	{
		MessageBox(_T("���ӷ�����ʧ�ܣ�"),_T("��ʾ"));
		return;
	}*/
	if (gCfg.m_proxyOption.getIsValid())
	{
		MessageBox(_T("��ʹ�ô��������£������ٶȽ����׼ȷ��\r\nֱ��ѡ��Ĭ�Ϸ��������ɣ�"),_T("��ʾ"));
	}
		if (m_listServ.GetItemCount() == 0)
		{
			CDlgLogin logIn;
			logIn.GetServerListData();
			gSvr.Load("svrlist.xml");

			for(int n=0; n<gSvr.m_vpGrp.size(); n++)
			{
				if (gSvr.m_vpGrp.at(n)->m_vpSvrs.size() > 0)
				{
					if (gSvr.m_vpGrp.at(n)->m_strName == gCfg.m_strFixedSvrGrp)
					{
						m_listServ.InsertItem(m_listServ.GetItemCount(),gSvr.m_vpGrp.at(n)->m_strName + _T("(Ĭ��)"));
					}
					else
					m_listServ.InsertItem(m_listServ.GetItemCount(),gSvr.m_vpGrp.at(n)->m_strName);
					m_listServ.SetItemData(m_listServ.GetItemCount()-1,(DWORD_PTR)gSvr.m_vpGrp.at(n));
				}
			}
		}

	if (m_listServ.GetItemCount() == 0)
	{
		MessageBox(_T("���ط������б���ȷ�������������ã�"),_T("��ʾ"));
		return;
	}
	CPing ping;
	CPingReply pr;///-,prBak;
	for(int n=0; n<m_listServ.GetItemCount(); n++)
	{
		SSvrGrp * pGrp = (SSvrGrp *)m_listServ.GetItemData(n);
		if (pGrp)
		{
			SSvr * pSvr = (SSvr *)pGrp->m_vpSvrs.at(0);
			if (pSvr)
			{
				BOOL br = ping.Ping2(pSvr->m_strIP,pr);
				if (br)
				{
					CString str;
					m_listServ.SetItemText(n,1,_T("���ӳɹ�"));
					if (pr.RTT > 140)
						str.Format(_T("����(%d)"),pr.RTT);			
					else
					if (pr.RTT > 100)
						str.Format(_T("��(%d)"),pr.RTT);			
					else
					if (pr.RTT > 40)
						str.Format(_T("һ��(%d)"),pr.RTT);
					else
						str.Format(_T("��(%d)"),pr.RTT);
					m_listServ.SetItemText(n,2,str);
				}
				else
				{
					m_listServ.SetItemText(n,1,_T("����ʧ��"));
				}
			}
		}
	}
}

void CDlgCommSet::OnBnClickedBtnSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_listServ.GetSelectionMark() == -1)
		return;
	
	SSvrGrp *pGrp = NULL;
	for(int n=0; n<m_listServ.GetItemCount(); n++)
	{
		pGrp = (SSvrGrp *)m_listServ.GetItemData(n);
		if (pGrp)
			m_listServ.SetItemText(n,0,pGrp->m_strName);
	}
	
	pGrp = (SSvrGrp *)m_listServ.GetItemData(m_listServ.GetSelectionMark());
	if (!pGrp)
		return;
	gCfg.m_strFixedSvrGrp = pGrp->m_strName;
	CString strText = pGrp->m_strName;
	strText += _T("(Ĭ��)");
	
	m_listServ.SetItemText(m_listServ.GetSelectionMark(),0,strText);

	WritePrivateProfileString(_T("SERVER"),_T("GRPNAME"),pGrp->m_strName,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
}

BOOL CDlgCommSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_listServ.InsertColumn(0,_T("����"),LVCFMT_CENTER,120);
	m_listServ.InsertColumn(1,_T("״̬"),LVCFMT_CENTER,80);
	m_listServ.InsertColumn(2,_T("�ٶ�"),LVCFMT_CENTER,80);

	for(int n=0; n<gSvr.m_vpGrp.size(); n++)
	{
		if (gSvr.m_vpGrp.at(n)->m_vpSvrs.size() > 0)
		{
			//m_listServ.InsertItem(m_listServ.GetItemCount(),gSvr.m_vpGrp.at(n)->m_vpSvrs.at(0)->m_strName);
			if (gSvr.m_vpGrp.at(n)->m_strName == gCfg.m_strFixedSvrGrp)
			{
				m_listServ.InsertItem(m_listServ.GetItemCount(),gSvr.m_vpGrp.at(n)->m_strName + _T("(Ĭ��)"));
			}
			else
			m_listServ.InsertItem(m_listServ.GetItemCount(),gSvr.m_vpGrp.at(n)->m_strName);
			m_listServ.SetItemData(m_listServ.GetItemCount()-1,(DWORD_PTR)gSvr.m_vpGrp.at(n));
		}
	}
	/*
	if (gCfg.m_nFixedHost == -1)
	{
		m_listServ.InsertItem(0,_T("���ŷ�����"));
		m_listServ.InsertItem(1,_T("��ͨ������"));
	}
	else
	if (gCfg.m_nFixedHost == 0)
	{
		m_listServ.InsertItem(0,_T("���ŷ�����(Ĭ��)"));
		m_listServ.InsertItem(1,_T("��ͨ������"));

	}
	else
	if (gCfg.m_nFixedHost == 1)
	{
		m_listServ.InsertItem(0,_T("���ŷ�����"));
		m_listServ.InsertItem(1,_T("��ͨ������(Ĭ��)"));
	}
	*/
	SetProxyOption();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgCommSet::OnBnClickedBtnSetPort()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	CDlgSetPort dlg;
	if (dlg.DoModal() == IDOK)
	{
		if (m_listServ.GetItemCount() == 0)
		{
			CDlgLogin logIn;
			logIn.GetServerListData();
			gSvr.Load("svrlist.xml");

			for(int n=0; n<gSvr.m_vpGrp.size(); n++)
			{
				if (gSvr.m_vpGrp.at(n)->m_vpSvrs.size() > 0)
				{
					if (gSvr.m_vpGrp.at(n)->m_strName == gCfg.m_strFixedSvrGrp)
					{
						m_listServ.InsertItem(m_listServ.GetItemCount(),gSvr.m_vpGrp.at(n)->m_strName + _T("(Ĭ��)"));
					}
					else
					m_listServ.InsertItem(m_listServ.GetItemCount(),gSvr.m_vpGrp.at(n)->m_strName);
					m_listServ.SetItemData(m_listServ.GetItemCount()-1,(DWORD_PTR)gSvr.m_vpGrp.at(n));
				}
			}
		}
	}
}

void CDlgCommSet::OnBnClickedCheckProxy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_checkProxy.GetCheck())
	{
		m_btnProxyTest.EnableWindow();		
		GetDlgItem(IDC_RADIO_SOCKET4)->EnableWindow();
		GetDlgItem(IDC_RADIO_SOCKET5)->EnableWindow();
		GetDlgItem(IDC_RADIO_HTTP)->EnableWindow();
		m_editProxyIP.EnableWindow();
		m_editProxyPort.EnableWindow();
		m_editProxyUser.EnableWindow();
		m_editProxyPass.EnableWindow();
	}
	else
	{
		m_btnProxyTest.EnableWindow(0);		
		GetDlgItem(IDC_RADIO_SOCKET4)->EnableWindow(0);
		GetDlgItem(IDC_RADIO_SOCKET5)->EnableWindow(0);
		GetDlgItem(IDC_RADIO_HTTP)->EnableWindow(0);
		m_editProxyIP.EnableWindow(0);
		m_editProxyPort.EnableWindow(0);
		m_editProxyUser.EnableWindow(0);
		m_editProxyPass.EnableWindow(0);
	}

}

void CDlgCommSet::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CDlgCommSet::OnBnClickedButtonProxyTest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedButtonProxySave();
	CShortSocket sk;
	if (sk.TestConnect((char *)gCfg.m_strDeployIP.c_str(),gCfg.GetDeployPort(),&gCfg.m_proxyOption))
	{
		MessageBox(_T("�������ӳɹ���"),_T("��ʾ"));
	}
	else
	{
		MessageBox(_T("��������ʧ�ܣ�"),_T("��ʾ"));
	}
}

void CDlgCommSet::OnBnClickedButtonProxySave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetProxyOption();
	gCfg.m_proxyOption.Save(toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
}

void CDlgCommSet::SetProxyOption()
{
	if (gCfg.m_proxyOption.m_bUseHttpHead)
		m_ckUseHttpHead.SetCheck(1);
	else
		m_ckUseHttpHead.SetCheck(0);

	if (gCfg.m_proxyOption.getIsValid())
	{
		m_checkProxy.SetCheck(1);		
		
	}
	else
	{
		m_checkProxy.SetCheck(0);
	}
	m_editProxyIP.SetWindowText(gCfg.m_proxyOption.getProxyIP());
	m_editProxyUser.SetWindowText(gCfg.m_proxyOption.getProxyUser());
	m_editProxyPass.SetWindowText(gCfg.m_proxyOption.getProxyPass());
	CString strValue;
	strValue.Format(_T("%d"),gCfg.m_proxyOption.getProxyPort());
	m_editProxyPort.SetWindowText(strValue);
	if (gCfg.m_proxyOption.getProxyType() == 1)
		((CButton *)GetDlgItem(IDC_RADIO_SOCKET4))->SetCheck(1);
	else
	if (gCfg.m_proxyOption.getProxyType() == 2)
		((CButton *)GetDlgItem(IDC_RADIO_SOCKET5))->SetCheck(1);
	else
	if (gCfg.m_proxyOption.getProxyType() == 3)
		((CButton *)GetDlgItem(IDC_RADIO_HTTP))->SetCheck(1);
	OnBnClickedCheckProxy();
}

void CDlgCommSet::GetProxyOption()
{
	if (m_ckUseHttpHead.GetCheck())
		gCfg.m_proxyOption.m_bUseHttpHead = true;
	else
		gCfg.m_proxyOption.m_bUseHttpHead = false;
	if (m_checkProxy.GetCheck())
		gCfg.m_proxyOption.setIsValid(true);
	else
		gCfg.m_proxyOption.setIsValid(false);

	if (((CButton *)GetDlgItem(IDC_RADIO_HTTP))->GetCheck())
		gCfg.m_proxyOption.setProxyType(3);
	else
	if (((CButton *)GetDlgItem(IDC_RADIO_SOCKET5))->GetCheck())
		gCfg.m_proxyOption.setProxyType(2);
	else
	if (((CButton *)GetDlgItem(IDC_RADIO_SOCKET4))->GetCheck())
		gCfg.m_proxyOption.setProxyType(1);

	CString strValue;
	m_editProxyIP.GetWindowText(strValue);
	gCfg.m_proxyOption.setProxyIP(strValue);
	m_editProxyUser.GetWindowText(strValue);
	gCfg.m_proxyOption.setProxyUser(strValue);
	m_editProxyPass.GetWindowText(strValue);
	gCfg.m_proxyOption.setProxyPass(strValue);

	m_editProxyPort.GetWindowText(strValue);
	char acBuf[32];
	unicodeToAscii(strValue,acBuf,32);
	gCfg.m_proxyOption.setProxyPort(atoi(acBuf));

}