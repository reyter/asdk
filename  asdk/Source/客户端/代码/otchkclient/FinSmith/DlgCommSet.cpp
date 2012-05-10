// DlgCommSet.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "DlgCommSet.h"
#include "DlgLogin.h"
#include "DlgSetPort.h"
#include "../public/ShortSocket.h"
#include "ping.h"

// CDlgCommSet 对话框

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


// CDlgCommSet 消息处理程序

void CDlgCommSet::OnBnClickedBtnTest()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	CDlgLogin log;
	if (log.GetServer() == false)
	{
		MessageBox(_T("连接服务器失败！"),_T("提示"));
		return;
	}*/
	if (gCfg.m_proxyOption.getIsValid())
	{
		MessageBox(_T("在使用代理的情况下，测试速度结果不准确。\r\n直接选择默认服务器即可！"),_T("提示"));
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
						m_listServ.InsertItem(m_listServ.GetItemCount(),gSvr.m_vpGrp.at(n)->m_strName + _T("(默认)"));
					}
					else
					m_listServ.InsertItem(m_listServ.GetItemCount(),gSvr.m_vpGrp.at(n)->m_strName);
					m_listServ.SetItemData(m_listServ.GetItemCount()-1,(DWORD_PTR)gSvr.m_vpGrp.at(n));
				}
			}
		}

	if (m_listServ.GetItemCount() == 0)
	{
		MessageBox(_T("下载服务器列表不正确，请检查网络设置！"),_T("提示"));
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
					m_listServ.SetItemText(n,1,_T("连接成功"));
					if (pr.RTT > 140)
						str.Format(_T("很慢(%d)"),pr.RTT);			
					else
					if (pr.RTT > 100)
						str.Format(_T("慢(%d)"),pr.RTT);			
					else
					if (pr.RTT > 40)
						str.Format(_T("一般(%d)"),pr.RTT);
					else
						str.Format(_T("快(%d)"),pr.RTT);
					m_listServ.SetItemText(n,2,str);
				}
				else
				{
					m_listServ.SetItemText(n,1,_T("连接失败"));
				}
			}
		}
	}
}

void CDlgCommSet::OnBnClickedBtnSet()
{
	// TODO: 在此添加控件通知处理程序代码
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
	strText += _T("(默认)");
	
	m_listServ.SetItemText(m_listServ.GetSelectionMark(),0,strText);

	WritePrivateProfileString(_T("SERVER"),_T("GRPNAME"),pGrp->m_strName,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
}

BOOL CDlgCommSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_listServ.InsertColumn(0,_T("主机"),LVCFMT_CENTER,120);
	m_listServ.InsertColumn(1,_T("状态"),LVCFMT_CENTER,80);
	m_listServ.InsertColumn(2,_T("速度"),LVCFMT_CENTER,80);

	for(int n=0; n<gSvr.m_vpGrp.size(); n++)
	{
		if (gSvr.m_vpGrp.at(n)->m_vpSvrs.size() > 0)
		{
			//m_listServ.InsertItem(m_listServ.GetItemCount(),gSvr.m_vpGrp.at(n)->m_vpSvrs.at(0)->m_strName);
			if (gSvr.m_vpGrp.at(n)->m_strName == gCfg.m_strFixedSvrGrp)
			{
				m_listServ.InsertItem(m_listServ.GetItemCount(),gSvr.m_vpGrp.at(n)->m_strName + _T("(默认)"));
			}
			else
			m_listServ.InsertItem(m_listServ.GetItemCount(),gSvr.m_vpGrp.at(n)->m_strName);
			m_listServ.SetItemData(m_listServ.GetItemCount()-1,(DWORD_PTR)gSvr.m_vpGrp.at(n));
		}
	}
	/*
	if (gCfg.m_nFixedHost == -1)
	{
		m_listServ.InsertItem(0,_T("电信服务器"));
		m_listServ.InsertItem(1,_T("联通服务器"));
	}
	else
	if (gCfg.m_nFixedHost == 0)
	{
		m_listServ.InsertItem(0,_T("电信服务器(默认)"));
		m_listServ.InsertItem(1,_T("联通服务器"));

	}
	else
	if (gCfg.m_nFixedHost == 1)
	{
		m_listServ.InsertItem(0,_T("电信服务器"));
		m_listServ.InsertItem(1,_T("联通服务器(默认)"));
	}
	*/
	SetProxyOption();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgCommSet::OnBnClickedBtnSetPort()
{
	// TODO: 在此添加控件通知处理程序代码	
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
						m_listServ.InsertItem(m_listServ.GetItemCount(),gSvr.m_vpGrp.at(n)->m_strName + _T("(默认)"));
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CDlgCommSet::OnBnClickedButtonProxyTest()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButtonProxySave();
	CShortSocket sk;
	if (sk.TestConnect((char *)gCfg.m_strDeployIP.c_str(),gCfg.GetDeployPort(),&gCfg.m_proxyOption))
	{
		MessageBox(_T("测试连接成功！"),_T("提示"));
	}
	else
	{
		MessageBox(_T("测试连接失败！"),_T("提示"));
	}
}

void CDlgCommSet::OnBnClickedButtonProxySave()
{
	// TODO: 在此添加控件通知处理程序代码
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