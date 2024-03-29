
// DlgLogin.cpp : 实现文件
//

#include "stdafx.h"
#include <atlbase.h>
#include "math.h"
#include "FinSmith.h"
#include "DlgLogin.h"
#include "../public/ShortSocket.h"
#include "../public/CommSocket.h"
#include "DlgUpdate.h"
#include "DlgSetIP.h"
#include "Downthread.h"
#include "ping.h"
#include "DlgWaitData.h"
#include "DlgTechDesc.h"
#include "DlgCommSet.h"
#include "DlgTEchDesc.h"
#include "..\\public\\md5.h"
#include "..\\public\\deslib.h"
#include "Calc.h"

// CDlgLogin 对话框

IMPLEMENT_DYNAMIC(CDlgLogin, CDialog)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
: CDialog(CDlgLogin::IDD, pParent)
, m_strName(_T(""))
, m_strPassword(_T(""))
, m_bSavePassword(FALSE)
{
	m_pWait = NULL;
	m_nViewType = 0;
	m_nMouseIN = 0;
	m_nActiveGG = 0;
	m_strUserName = "wuqing";
	m_strEMail = "WuQ@investoday.com.cn";
	m_strMobile = "13825200850";

	m_loginCheckBK.LoadBitmap(IDB_LOGIN_CHECK_BK);
	m_br.CreatePatternBrush(&m_loginCheckBK);	
	m_regBK.LoadBitmap(IDB_REG_BK);
	m_brReg.CreatePatternBrush(&m_regBK);	
	m_bToGetSvrList = false;
	m_imgLogHead.Load(_T("./Skin/comm/loggg.jpg"));	
}

CDlgLogin::~CDlgLogin()
{
	m_loginCheckBK.DeleteObject();
	m_regBK.DeleteObject();
	m_br.DeleteObject();
	m_brReg.DeleteObject();
	if(!m_imgLogHead.IsNull())
	m_imgLogHead.Detach();
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPassword);
	DDX_Control(pDX, IDC_CHECK_PASSWORD, m_ckPassword);
	DDX_Control(pDX, IDC_CHECK_AUTOLOGIN, m_ckAutoLogin);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Check(pDX, IDC_CHECK_PASSWORD, m_bSavePassword);
	DDX_Control(pDX, IDC_CHECK_AUTOLOGIN, m_ckAutoLogin);
	DDX_Control(pDX, IDC_BTN_NOTUSER, m_btnNotUser);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btnClose);
	DDX_Control(pDX, IDOK, m_btnLog);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgLogin::OnBnClickedOk)
	ON_WM_ERASEBKGND()
	ON_STN_CLICKED(IDC_STATIC_REG, &CDlgLogin::OnStnClickedStaticReg)
	ON_STN_CLICKED(IDC_STATIC_PASS, &CDlgLogin::OnStnClickedStaticPass)
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STATIC_REGET, &CDlgLogin::OnStnClickedStaticReget)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_ACTIVE, &CDlgLogin::OnBnClickedButtonActive)
	ON_BN_CLICKED(IDC_BUTTON_LOG_NOW, &CDlgLogin::OnBnClickedButtonLogNow)
	ON_EN_KILLFOCUS(IDC_EDIT_NAME, &CDlgLogin::OnEnKillfocusEditName)
	ON_EN_SETFOCUS(IDC_EDIT_NAME, &CDlgLogin::OnEnSetfocusEditName)
	ON_STN_CLICKED(IDC_STATIC_UPGRADE, &CDlgLogin::OnStnClickedStaticUpgrade)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CDlgLogin::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_NOTUSER, &CDlgLogin::OnBnClickedBtnNotuser)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_LOGON, &CDlgLogin::OnBnClickedLogon)
	ON_BN_CLICKED(IDC_CHECK_AUTORUN, &CDlgLogin::OnBnClickedCheckAutorun)
END_MESSAGE_MAP()


// CDlgLogin 消息处理程序

void CDlgLogin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	KillTimer(102);	
/*
	CShortSocket ska;
	char acData[1024];
	char * pRet = (char *)malloc(1024 * 512);

	sprintf(acData,"<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\"><s:Body><sendMessage xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\"><mobile>15118110052</mobile><message>test你好</message></sendMessage></s:Body></s:Envelope>");

	int nRetLen = ska.HttpSMGSendAndRecv("192.168.11.24",8100,acData,strlen(acData),(char *)pRet,1024*512,0,&gCfg.m_proxyOption);
	if (nRetLen)
	{
		FILE *f;
		f = fopen("c:\\test\\ret.d","wb");
		if (f)
		{
			fwrite(pRet,1,nRetLen,f);
			fclose(f);
		}
	}
	free(pRet);
	return;*/
	/*
	if (GetServer() == false)
	{
	MessageBox(_T("连接服务器失败！"),_T("提示"));
	return;
	}*/
	/*
	this->m_sk.SetKeepLive(true);
	while(true)
	{
	if (GetUpgradeFile(m_sk) != 0)
	break;
	}
	m_sk.Disconnect();
	m_sk.SetKeepLive(false);*/
	//生成授权文件
	//gpData->MakeQuoteServerLic(500,gCfg.m_acDesKey);
#ifdef CCTV_TV
#else
	CheckVersion();//检查版本	
#endif

	if (gCfg.m_usUpdateType > 0 && gCfg.m_usForce == 1)
	{
		MessageBox(_T("必须升级到新版本才能使用！"),_T("提示"));
		return;
	}
	/*
	if (gCfg.m_nFixedPort == 0)
	{
	if (GetServer() == false)
	{
	CDlgTechDesc dlg;
	dlg.SetTitle(_T("登录失败提示"));
	dlg.DoModal();
	return;
	}
	}*/
	//
	m_strName.Trim();
	m_strPassword.Trim();
	if (m_strName.IsEmpty())
	{
		MessageBox(_T("用户名称不能为空！"),_T("提示"));
		return;
	}
	//USES_CONVERSION;
	char acName[20];
	memset(acName,0,sizeof(acName));
	unicodeToAscii(m_strName,acName,18);
	char acPass[32];
	char acMD5[128];
	memset(acMD5,0,sizeof(acMD5));
	acPass[16] = 0;
	unicodeToAscii(m_strPassword,acPass,17);
	strncpy(acMD5,acPass,16);	
	MD5_Sig_Get((unsigned char *)acPass,strlen(acPass),acMD5 + 16,60);	
	gCfg.m_strPass = acMD5;
	gCfg.m_strPassMD5 = acMD5 + 16;

	int nPort = 0;
	bool bGet = gSvr.GetQuoteServer(gCfg.m_strQuoteIP,nPort,gCfg.m_strFixedSvrGrp,gpData->m_nUserID);
	if (bGet == false)
	{
		MessageBox(_T("未能取到可用服务器！"),_T("提示"));
		return;
	}
	gCfg.SetQuotePort(nPort);
	SSvrGrp * pGrp = gSvr.GetSvrGrpByName(gCfg.m_strFixedSvrGrp);
	gCfg.m_strUserIP = pGrp->m_svrUserInfo.m_strIP;
	gCfg.SetUserPort(pGrp->m_svrUserInfo.m_nPort);
	gCfg.m_strTeacherIP = pGrp->m_svrTeaching.m_strIP;//取可用的服务器配置，培训、交易等
	gCfg.SetTeacherPort(pGrp->m_svrTeaching.m_nPort);
	gCfg.m_strTradeIP = pGrp->m_svrTrade.m_strIP;
	gCfg.SetTradePort(pGrp->m_svrTrade.m_nPort);

	CShortSocket sk;
	char *pRecv = (char *)malloc(1024 * 1024);
	char *pSend = (char *)malloc(1024);
	gpData->m_lockData.lock();
	gpData->m_nUserID = 0;
	gCfg.m_strUser = "";
	char acIP[32];
	unicodeToAscii(gCfg.m_strUserIP,acIP,32);
	//用本地配置的服务器进行用户验证
	char acDes[64];
	Encrypt(acMD5,48,acDes,gCfg.m_acDesKey);
	tagUserLogReq req;
	req.nEncrypt = 0;
	strcpy(req.acCode,acName);
	strcpy(req.acPass,acPass);
	int nLen = gpData->MakeNormalReq(pSend,3119,(char *)&req,sizeof(tagUserLogReq));
	int nRet = sk.SendAndRecv(acIP,gCfg.GetUserPort(),pSend,nLen,pRecv,10240,GetSafeHwnd(),&gCfg.m_proxyOption);
	if (nRet > 0)
	{
		gpData->DealData(pRecv,nRet);
	}
	gpData->m_lockData.unlock();
	free(pRecv);
	free(pSend);

	bGet = gSvr.GetQuoteServer(gCfg.m_strQuoteIP,nPort,gCfg.m_strFixedSvrGrp,gpData->m_nUserID);
	if (bGet)
	{
		pGrp = gSvr.GetSvrGrpByName(gCfg.m_strFixedSvrGrp);
		gCfg.m_strUserIP = pGrp->m_svrUserInfo.m_strIP;
		gCfg.SetUserPort(pGrp->m_svrUserInfo.m_nPort);
		gCfg.m_strTeacherIP = pGrp->m_svrTeaching.m_strIP;//取可用的服务器配置，培训、交易等
		gCfg.SetTeacherPort(pGrp->m_svrTeaching.m_nPort);
		gCfg.m_strTradeIP = pGrp->m_svrTrade.m_strIP;
		gCfg.SetTradePort(pGrp->m_svrTrade.m_nPort);
	}
	if (gpData->m_nUserID == 0)
	{		
		if (nRet > 0)
			MessageBox(_T("登陆失败！请检查用户名及密码！"),_T("提示"));
		else
		{
			CDlgTechDesc dlg;
			dlg.SetTitle(_T("登录失败提示"));
			dlg.DoModal();			
		}
		return;
	}
	if (gpData->m_nUserID > 0)
	{		
		memset(gpData->m_acPass,0,sizeof(gpData->m_acPass));
		strncpy(gpData->m_acPass,acPass,16);

		memset(gpData->m_acPassMD5,0,sizeof(gpData->m_acPassMD5));
		strncpy(gpData->m_acPassMD5,acMD5,32);
		WritePrivateProfileString(_T("LOGINSET"),_T("name"),m_strName,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));

		if (m_pWait)
		{
			m_pWait->ShowWindow(SW_SHOW);
			this->ShowWindow(SW_HIDE);
		}
		//启动下载数据线程
		m_bDownRet = false;

		CDownThread * pThread=   new   CDownThread();
		m_bInitDataOver = false;
		pThread->m_pLogin = this;
		pThread->CreateThread(CREATE_SUSPENDED);   
		pThread->SetThreadPriority(THREAD_PRIORITY_HIGHEST);//THREAD_PRIORITY_NORMAL);   
		pThread->m_bAutoDelete   =   TRUE; //   自动删除线程   	
		pThread->ResumeThread();

		//::WaitForSingleObject(pThread->m_hThread,INFINITE);

		//下载数据线程结束
		while(m_bDownRet != true)
		{
			OnTimer(103);
		}
		//GetInitData();

		if (m_bInitDataOver)
			OnOK();
		else
		{
			this->ShowWindow(SW_SHOW);
			if (m_pWait)
				m_pWait->ShowWindow(SW_HIDE);
			MessageBox(_T("数据下载失败！可能原因：\r\n1、网络断开\r\n2、网速过慢\r\n请检查网络后再试！"),_T("提示"),MB_OK);
		}
	}
	else
	{
		CDlgTechDesc dlg;
		dlg.SetTitle(_T("登录失败提示"));
		dlg.DoModal();
		/*
		if (nRet > 0)
		MessageBox("登陆失败！请检查用户名及密码！","提示");
		else
		MessageBox("连接服务器失败，请检查网络！","提示");*/
		return;
	}
}

void CDlgLogin::DownDataOver(bool bOK)
{
	if (bOK)
	{
		EndDialog(IDOK);
		//OnOK();
	}
	else
	{
		ShowWindow(SW_SHOW);
		if (m_pWait)
			m_pWait->ShowWindow(SW_HIDE);
		MessageBox(_T("数据下载失败！可能原因：\r\n1、网络断开\r\n2、网速过慢\r\n请检查网络后再试！"),_T("提示"),MB_OK);
	}
}

BOOL CDlgLogin::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(VERNAME);

	m_hIcon = (HICON)::LoadImage(0,_T("logo.ico"),IMAGE_ICON,32,32,LR_LOADFROMFILE);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

///-	char acFile[MAX_PATH];
	USES_CONVERSION;
	WCHAR acBuf[31];

	memset(acBuf,0,sizeof(acBuf));
	GetPrivateProfileString(_T("LOGINSET"),_T("name"),_T(""),acBuf,30,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));	

	if (lstrlen(acBuf) > 0)
	{
		m_strName = acBuf;
	}
	GetPrivateProfileString(_T("LOGINSET"),_T("pass"),_T(""),acBuf,30,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
	if (lstrlen(acBuf) > 0)
	{
		m_strPassword = acBuf;
		m_bSavePassword = true;
	}

	this->UpdateData(0);

	GetPrivateProfileString(_T("SKINSET"),_T("style"),_T("black"),acBuf,30,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
	if (strcmp(W2A(acBuf),"black") == 0)
		gpSkinManager->SetSkinType(1);
	else
		gpSkinManager->SetSkinType(0);

	m_btnClose.SetWindowText(_T(""));
	m_btnClose.SetBorder(false);
	m_btnClose.SetBtnBMP(IDB_LOG_HEAD_CLOSE,IDB_LOG_HEAD_CLOSE_CHANGE);

	//m_editName.SetPromptText("按右边注册按纽可获得帐号", FALSE);
	m_editName.SetPromptText(_T("在此输入帐号"), FALSE);
	m_editName.SetPromptTextColor(RGB(208, 208, 208));
	//m_editName.SetBtnBMP(IDB_EDITING,IDB_WAIT_EDIT);

	CRect rect,rectClient;
	GetWindowRect(rect);
	GetClientRect(rectClient);

	m_btnLog.SetBorder(false);
	m_btnLog.SetBtnBMP(IDB_BTN_LOG,IDB_BTN_LOG);
	m_btnLog.SetWindowText(_T("用户登录"));
	m_btnLog.SetTextColor(RGB(0,0,0));
	m_btnLog.SetBmpPos(3);
	rect.left = 20;
	rect.top = 20;
	rect.right = rect.left + 76;
	rect.bottom = rect.top + 27;
	m_btnLog.MoveWindow(rect);


	m_btnNotUser.SetBorder(false);
	m_btnNotUser.SetBtnBMP(IDB_LOG_NOTUSER,IDB_LOG_NOTUSER);
	m_btnNotUser.SetWindowText(_T("网络测试"));
	m_btnNotUser.SetTextColor(RGB(0,0,0));
	m_btnNotUser.SetBmpPos(3);
	rect.left = 20;
	rect.top = 20;
	rect.right = rect.left + 76;
	rect.bottom = rect.top + 27;
	m_btnNotUser.MoveWindow(rect);

	m_editName.GetWindowRect(rectClient);//用户名输入
	rect= rectClient;
	rect.top = 114;
	rect.bottom = rect.top + 20;
	rect.left  = 74;
	rect.right = rect.left + 180;
	m_editName.MoveWindow(rect);

	rect.top = 2;
	rect.bottom = 18;
	rect.left = 2;
	rect.right = rect.right-2;
	m_editName.SetEditRect(rect);
	m_editName.Invalidate(1);

	m_editPassword.GetWindowRect(rectClient);//密码输入
	rect= rectClient;
	rect.top = 144;
	rect.bottom = rect.top + 20;
	rect.left  = 74;
	rect.right = rect.left + 180;
	m_editPassword.MoveWindow(rect);

	m_ckPassword.GetWindowRect(rectClient);
	rect= rectClient;
	rect.top = 170;
	rect.bottom = rect.top + rectClient.Height();
	rect.left  = 74;
	rect.right = rect.left + rectClient.Width();
	m_ckPassword.MoveWindow(rect);

	m_ckAutoLogin.GetWindowRect(rectClient);
	rect= rectClient;
	rect.top = 170;
	rect.bottom = rect.top + rectClient.Height();
	rect.left  = 152;
	rect.right = rect.left + rectClient.Width();
	m_ckAutoLogin.MoveWindow(rect);

	m_btnLog.GetWindowRect(rectClient);
	rect= rectClient;
	rect.top = 200;
	rect.bottom = rect.top + rectClient.Height();
	rect.left  = 247;
	rect.right = rect.left + rectClient.Width();
	m_btnLog.MoveWindow(rect);

	m_btnNotUser.GetWindowRect(rectClient);
	rect= rectClient;
	rect.top = 200;
	rect.bottom = rect.top + rectClient.Height();
	rect.left  = 160;
	rect.right = rect.left + rectClient.Width();
	m_btnNotUser.MoveWindow(rect);

	rect = rectClient;
	rect.left = 16;
	rect.right = 100;
	rect.top = 158 + 22;
	rect.bottom = rect.top + 13;

	m_nViewType = 0;

	int width= GetSystemMetrics(SM_CXFULLSCREEN); 
	int high= GetSystemMetrics(SM_CYFULLSCREEN); 

	GetClientRect(rect);
	rect.left = (width - 363) / 2;
	rect.right = rect.left + 363;
	rect.top = 100;
	rect.bottom = 100 + 206;
	MoveWindow(rect);
	SetViewSize();
	//SetTimer(101,1000 * 2,NULL);//检查心跳
	SetTimer(102,1000 * 5,NULL);//自动登陆

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CDlgLogin::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(rect);

	CDC SourceDC;
	CBitmap bitmap,*pOldBitmap;
	bitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());	

	SourceDC.CreateCompatibleDC(NULL);//生成兼容的CDC
	pOldBitmap = SourceDC.SelectObject(&bitmap);

	PaintMe(&SourceDC);

	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&SourceDC,0,0,SRCCOPY);	
	SourceDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	SourceDC.DeleteDC();	
	return TRUE;
	return CWnd::OnEraseBkgnd(pDC);

}
void CDlgLogin::PaintMe(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	CBitmap bitmap;
///-	HBITMAP hBitmap;
	CBrush brush;	
	gpSkinManager->FillRectImage(IDB_LOG_BIG_BACK,pDC,rect);
	rect.top = rect.bottom - 4;
	CBrush br(RGB(75,91,126));
	pDC->FillRect(rect,&br);
	GetClientRect(rect);
	rect.bottom = rect.top + 22;

	HBITMAP h = gpSkinManager->LoadCommBmp(ID_LOG_HEAD);
	if (h)
	{
		gpSkinManager->FillRectImage(h,pDC,rect);
		DeleteObject(h);
	}

	::DrawIconEx(pDC->GetSafeHdc(),6,rect.top + (rect.Height() - 16) /2,m_hIcon,16,16,0,0,DI_NORMAL);
	CRect rectText;
	rectText = rect;
	rectText.left += 6 + 16 + 4;
	int nOldMode = pDC->SetBkMode(TRANSPARENT);
	COLORREF oldCl = pDC->SetTextColor(gpSkinManager->getColor(MAINTITLECOLOR));

	CFont * pFont = pDC->SelectObject(gpSkinManager->m_pFontSmallHT);

	pDC->DrawText(MAINTITLE,rectText,DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	pDC->SetTextColor(oldCl);
	pDC->SelectObject(pFont);
	pDC->SetBkMode(nOldMode);

	rect.top = rect.bottom;
	rect.bottom = rect.top + 79;
	rect.left += 4;
	rect.right = rect.left + 355;
	/*
	h = gpSkinManager->LoadCommBmp(ID_LOG_GG);
	if (h)
	{
		gpSkinManager->FillRectImage(h,pDC,rect);
		DeleteObject(h);
	}*/
	if(!m_imgLogHead.IsNull())
	m_imgLogHead.Draw(pDC->GetSafeHdc(),rect);
	rect.top = rect.bottom;
	rect.bottom = 236;
	h = gpSkinManager->LoadCommBmp(ID_LOG_BODY);
	if (h)
	{
		gpSkinManager->FillRectImage(h,pDC,rect);
		DeleteObject(h);
	}
	//gpSkinManager->FillRectImage(IDB_LOG_BODY,pDC,rect);

	if (m_nViewType == 1)
	{
		GetClientRect(rect);
		rect.left = rect.left + (363 - 317) / 2;
		rect.right = rect.left + 317;
		rect.top = rect.top + 236 + 4;
		rect.bottom = rect.top + 139;
		HBITMAP h = gpSkinManager->LoadCommBmp(ID_FORGET_PASS);
		if (h)
		{
			gpSkinManager->FillRectImage(h,pDC,rect);
			DeleteObject(h);
		}
		rect.left = 204;
		rect.top = 336;
		DrawVerifyCode(pDC,rect);
	}
	else
		if (m_nViewType == 2)
		{
			//GetClientRect(rect);
			//rect.top = rect.bottom - 247;
			//bitmap.LoadBitmap(IDB_REG_1);
			//gpSkinManager->FillRectImage(bitmap,pDC,rect);
			//bitmap.DeleteObject();
		}
		else
			if (m_nViewType == 3)
			{
				GetClientRect(rect);
				rect.top = rect.top + 236 + 4;
				rect.bottom = rect.top + 305;
				rect.left = rect.left + (363 - 315)/2;
				rect.right = rect.left + 315;
				gpSkinManager->FillRectImage(gpSkinManager->GetBitmap(ID_REG_2),pDC,rect);
			}
			else
				if (m_nViewType == 4)
				{
					GetClientRect(rect);
					rect.top = rect.top + 236 + 4;
					rect.bottom = rect.top + 158;
					rect.left = rect.left + (363-315)/2;
					rect.right = rect.left + 315;
					gpSkinManager->FillRectImage(gpSkinManager->GetBitmap(ID_REG_3),pDC,rect);
					pDC->SetBkMode(TRANSPARENT);
					rect.left = 127;
					rect.top = 319;
					rect.right = 318;
					rect.bottom = rect.top + 20;
					pDC->DrawText(m_strUserName,m_strUserName.GetLength(),rect,DT_LEFT);

					rect.left = 127;
					rect.top = 352;
					rect.right = 318;
					rect.bottom = rect.top + 20;
					//m_strPassword = m_strUserName;
					pDC->DrawText(m_strPassword,m_strPassword.GetLength(),rect,DT_LEFT);
				}
}

void CDlgLogin::SetViewSize()
{
	int nWidth = 363;
	int nHeight = 236;
	CRect rect,rectClient;
	GetClientRect(rect);	
	rect.right -= 4;
	rect.left = rect.right - 20;
	rect.top += 2;
	rect.bottom = rect.top + 19;
	m_btnClose.MoveWindow(rect);

	if (m_nViewType == 0)
	{
		nHeight = 236;

	}
	else
					if (m_nViewType == 4)
					{
						nHeight = 236 + 158 + 8;
					}


					GetWindowRect(rect);
					GetClientRect(rectClient);
					rect.right = rect.left + nWidth + rect.Width() - rectClient.Width();
					rect.bottom = rect.top + nHeight + rect.Height() - rectClient.Height();
					MoveWindow(rect);
}
void CDlgLogin::OnStnClickedStaticReg()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox("此版本不支持此功能！","提示",MB_OK);
	//return;
#ifndef TRADEON
	::ShellExecute(0,_T("open"),gpData->m_strRegUrl,NULL,NULL,SW_SHOWNORMAL);
	return;
#endif
	/*
	m_nViewType = 2;
	SetViewSize();
	this->Invalidate();*/
}

void CDlgLogin::OnStnClickedStaticPass()
{
	// TODO: 在此添加控件通知处理程序代码
	/*	if (ChangePass("ABC123456","888888","123456"))
	MessageBox("密码修改成功！","提示",MB_OK);
	else
	MessageBox("用户名或密码错误！","提示",MB_OK);
	*/
	if (gpData->m_strResetPassUrl.IsEmpty())
	{
		MessageBox(_T("对不起，此功能暂未提供！"),_T("提示"),MB_OK +MB_ICONWARNING);// MB_ICONERROR);
		return;
	}
	::ShellExecute(0,_T("open"),gpData->m_strResetPassUrl,NULL,NULL,SW_SHOWNORMAL);
	return;
	m_nViewType = 1;
	SetViewSize();
	CRect rect;
	DrawVerifyCode(NULL,rect);
	this->Invalidate();
}

HBRUSH CDlgLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	if (pWnd->GetSafeHwnd() == GetDlgItem(IDC_CHECK_PASSWORD)->GetSafeHwnd()
		||pWnd->GetSafeHwnd() == GetDlgItem(IDC_CHECK_AUTOLOGIN)->GetSafeHwnd()
		||pWnd->GetSafeHwnd() == GetDlgItem(IDC_CHECK_AUTORUN)->GetSafeHwnd())
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_br; 
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

BOOL CDlgLogin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgLogin::OnStnClickedStaticReget()
{
	// TODO: 在此添加控件通知处理程序代码
	CRect rect;
	DrawVerifyCode(NULL,rect);
	rect.left = 92 + 90;
	rect.top = 317 + 2;
	rect.bottom = rect.top + 16;
	rect.right = 92 + 130;
	this->InvalidateRect(rect);
}


void CDlgLogin::DrawVerifyCode(CDC * c_pDC,CRect &rect)
{
}

void CDlgLogin::RegAutoRun(BOOL c_bAutoRun)
{
	CRegKey		key;
	HRESULT hr;
	CString    sPath;   
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
	sPath.ReleaseBuffer();   
	hr = key.Open(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\MicroSoft\\Windows\\CurrentVersion\\Run"));
	if (hr == ERROR_SUCCESS )
	{
		if (c_bAutoRun)
		{
			key.SetValue(sPath,_T("ehome"));
		}
		else
		{
			key.DeleteValue(_T("ehome"));
		}
	}
	key.Close();
}

int CDlgLogin::GetUpgradeFile(CShortSocket &c_sk,HWND c_hwnd)
{	
	char * pRecv;
	int nRet;
	char acReq[1024];
	char acVer[11];
	sprintf(acVer,gCfg.m_acVer);

	int nVerID = 1;
#ifdef TRADEON//投顾版本
	nVerID = 2;	
#endif

#ifdef INVEST_AND_ZS//中山版本
	nVerID = 3;
#endif

#ifdef CCTV_BJ	//CCTV财经频道合作
	nVerID = 4;
#endif
	int nFileLen = 0;
	int nLen = gpData->MakeUpgradeFileReq(acReq,nVerID,acVer,nFileLen);//请求升级文件

	int nDealResult = -999;
	pRecv = (char *)malloc(1024 * 64);
	nRet = c_sk.SendAndRecv((char *)gCfg.m_strDeployIP.c_str(),gCfg.GetDeployPort(),acReq,nLen,pRecv,48 * 1024,0,&gCfg.m_proxyOption);
	if (nRet <= 0)
		nRet = c_sk.SendAndRecv((char *)gCfg.m_strDeployIPBak.c_str(),gCfg.GetDeployPort(),acReq,nLen,pRecv,10 * 1024,0,&gCfg.m_proxyOption);
	if (nRet > 0)
	{
		nDealResult = gpData->DealData(pRecv,nRet);

		if (c_hwnd > 0)
		{
			::SendMessage(c_hwnd,WM_DOWNLOAD_LEN,nFileLen,nDealResult);
			MSG   Message; 
			while (::PeekMessage(&Message,   NULL,   0,   0,   PM_REMOVE))     
			{ 
				::TranslateMessage(&Message); 
				::DispatchMessage(&Message); 
			}
		}
	}
	free(pRecv);
	return nDealResult;
}

bool CDlgLogin::CheckVersion()
{
	bool bRet = false;
	CShortSocket sk;
	char * pRecv;
	int nRet;
	char acReq[1024];

	int nVerID = 1;
#ifdef TRADEON//投顾版本
	nVerID = 2;	
#endif

#ifdef INVEST_AND_ZS//中山版本
	nVerID = 3;
#endif

#ifdef CCTV_BJ	//CCTV财经频道合作
	nVerID = 4;
#endif
	int nLen = gpData->MakeVersionReq(acReq,nVerID,gCfg.m_acVer,gCfg.m_acPatch);//请求版本信息

	gCfg.m_usUpdateType = 0;

	pRecv = (char *)malloc(1024 * 10);
	nRet = sk.SendAndRecv((char *)gCfg.m_strDeployIP.c_str(),gCfg.GetDeployPort(),acReq,nLen,pRecv,10 * 1024,0,&gCfg.m_proxyOption);
	if (nRet <= 0)
		nRet = sk.SendAndRecv((char *)gCfg.m_strDeployIPBak.c_str(),gCfg.GetDeployPort(),acReq,nLen,pRecv,10 * 1024,0,&gCfg.m_proxyOption);
	if (nRet > 0)
	{
		gpData->DealData(pRecv,nRet);
	}
	free(pRecv);
	//gCfg.m_usUpdateType = 1;
	//gCfg.m_usForce = 1;
	//版本
	if (gCfg.m_usUpdateType == 1 || gCfg.m_usUpdateType == 2)
	{
		CDlgUpdate dlg;
		if (gCfg.m_usUpdateType == 1)
		{
			dlg.m_strUrl = gCfg.m_acVerUrl;
			dlg.m_strFile = "Setup";
			dlg.m_strFile += gCfg.m_acVer;
			dlg.m_strFile += ".exe";
		}
		else
		{
			dlg.m_strUrl = gCfg.m_acPatchUrl;
			dlg.m_strFile = "Setup";
			dlg.m_strFile += gCfg.m_acVer;
			dlg.m_strFile += ".";
			dlg.m_strFile += gCfg.m_acPatch;
			dlg.m_strFile += ".cab";

		}
		dlg.m_strInfo = gCfg.m_acUpdateInfo;

		if (dlg.DoModal() != IDOK)
		{
			if (gCfg.m_usForce == 1)
				::PostQuitMessage(0);
		}
		else
		{
			USES_CONVERSION;
			if (gCfg.m_usUpdateType == 1)
			{//安装包
				CString strRun;
				strRun = dlg.m_strFile;
				strRun += " /SILENT";
				char acRun[MAX_PATH];
				unicodeToAscii(strRun,acRun,MAX_PATH-1);
				::WinExec(acRun,SW_SHOW);
				//::WinExec((char *)W2A(strRun.GetBuffer()),SW_SHOW);
				//strRun.ReleaseBuffer();
				::PostQuitMessage(0);				
				//::terminate();
				return false;
			}
			else
			{//补丁包
				CString strRun;
				strRun = "expand ";
				strRun += dlg.m_strFile;
				strRun += " -F:* .";
				char acRun[MAX_PATH];
				unicodeToAscii(strRun,acRun,MAX_PATH-1);
				::WinExec(acRun,SW_SHOW);
				//::WinExec((char *)W2A(strRun.GetBuffer()),SW_SHOW);
				//strRun.ReleaseBuffer();
			}
		}
	}

	return bRet;
}

bool CDlgLogin::ChangePass(char * c_pName,char * c_pPass,char * c_pNewPass)
{
	bool bRet = false;
	CShortSocket sk;
	char * pRecv;
	int nRet;
	char acReq[1024];
	int nLen = gpData->MakeUserChangePasswordReq(acReq,gCfg.m_nProduct,c_pName,c_pPass,c_pNewPass);
	pRecv = (char *)malloc(1024 * 10);
	char acIP[32];
	unicodeToAscii(gCfg.m_strUserIP,acIP,32);
	nRet = sk.SendAndRecv(acIP,gCfg.GetUserPort(),acReq,nLen,pRecv,10 * 1024,0,&gCfg.m_proxyOption);
	if (nRet > 4)
	{
		//gpData->DealData(pRecv,nRet);
		if (*(int *)(pRecv + nRet - sizeof(int)) == 1)
			bRet = true;
	}
	free(pRecv);

	return bRet;
}

bool CDlgLogin::ChangePass(int c_nUserId,char * c_pPass,char * c_pNewPass)
{
	bool bRet = false;
	CShortSocket sk;
	char * pRecv;
	int nRet;
	char acReq[1024];
	tagChangePass chg;
	chg.nType = 0;
	chg.nUserId = gpData->m_nUserID;
	strncpy(chg.acPass,c_pPass,16);
	strncpy(chg.acNewPass,c_pNewPass,16);
	int nLen = gpData->MakeNormalReq(acReq,3129,(char *)&chg,sizeof(tagChangePass));
	pRecv = (char *)malloc(1024 * 10);
	char acIP[32];
	unicodeToAscii(gCfg.m_strUserIP,acIP,32);
	nRet = sk.SendAndRecv(acIP,gCfg.GetUserPort(),acReq,nLen,pRecv,10 * 1024,0,&gCfg.m_proxyOption);
	if (nRet > 4)
	{
		//gpData->DealData(pRecv,nRet);
		if (*(int *)(pRecv + nRet - sizeof(int)) == 1)
			bRet = true;
	}
	free(pRecv);

	return bRet;
}

bool CDlgLogin::DoUpgrade()
{
	bool bRet = false;

	//版本
	if (gCfg.m_usUpdateType != 0)
	{
		CDlgUpdate dlg;
		if (gCfg.m_usUpdateType == 1)
		{
			dlg.m_strUrl = gCfg.m_acVerUrl;
			dlg.m_strFile = "Setup";
			dlg.m_strFile += gCfg.m_acVer;
			dlg.m_strFile += ".exe";
		}
		else
		{
			dlg.m_strUrl = gCfg.m_acPatchUrl;
			dlg.m_strFile = "Setup";
			dlg.m_strFile += gCfg.m_acVer;
			dlg.m_strFile += ".";
			dlg.m_strFile += gCfg.m_acPatch;
			dlg.m_strFile += ".cab";

		}
		dlg.m_strInfo = toUnicodeString(gCfg.m_acUpdateInfo,strlen(gCfg.m_acUpdateInfo));

		if (dlg.DoModal() == IDOK)
		{
			USES_CONVERSION;
			if (gCfg.m_usUpdateType == 1)
			{//安装包
				CString strRun;
				strRun = dlg.m_strFile;
				strRun += " /SILENT";
				char acRun[MAX_PATH];
				unicodeToAscii(strRun,acRun,MAX_PATH-1);
				::WinExec(acRun,SW_SHOW);
				//::WinExec((char *)W2A(strRun.GetBuffer()),SW_SHOW);
				//strRun.ReleaseBuffer();
				::PostQuitMessage(0);
				return false;
			}
			else
			{//补丁包
				CString strRun;
				strRun = "expand ";
				strRun += dlg.m_strFile;
				strRun += " -F:* .";
				char acRun[MAX_PATH];
				unicodeToAscii(strRun,acRun,MAX_PATH-1);
				::WinExec(acRun,SW_SHOW);

				//::WinExec((char *)W2A(strRun.GetBuffer()),SW_SHOW);
				//strRun.ReleaseBuffer();
			}
		}
	}

	return bRet;
}

bool CDlgLogin::ForceQuit()
{
	CShortSocket sk;
	char * pRecv;
	int nRet;
	int nLen;

	if (strlen(gCfg.m_acPreServIP) > 0 && gCfg.m_nPrePort > 0)//有登陆记录，清除
	{
		pRecv = (char *)malloc(1024);
		char acReq[1024];
		gpData->m_lockData.lock();
		nLen = gpData->MakeUserForceQuitReq(acReq,gpData->m_nUserID);
		nRet = sk.SendAndRecv((char *)gCfg.m_acPreServIP,gCfg.m_nPrePort,acReq,nLen,pRecv,1024,0,&gCfg.m_proxyOption);
		if (nRet > 0)
		{
			//gpData->DealData(pRecv);
		}
		gpData->m_lockData.unlock();
		free(pRecv);
	}
	return true;
}

bool CDlgLogin::GetStockInfo(CShortSocket &c_sk)
{	
	char * pRecv;
	int nRet;
	int nLen;

	gpData->m_lockData.lock();
	char acReq[1024];
	nLen = gpData->MakeInitReq(acReq);
	//nLen = gpData->MakeInitReq(acReq);
/*
	 FILE *f;
	 f = fopen("c:\\test\\initnew.req","wb");
	 if (f)
	 {
	 fwrite(acReq,1,nLen,f);
	 fclose(f);
	 }
*/
	pRecv = (char *)malloc(1024 * 1024);
	nRet = c_sk.SendAndRecv(gCfg.m_strQuoteIP,gCfg.GetQuotePort(),acReq,nLen,pRecv,1024 * 1024,m_pWait->GetSafeHwnd(),&gCfg.m_proxyOption);
	if (nRet > 0)
	{/*
	 FILE *f;
	 f = fopen("c:\\test\\initnew","wb");
	 if (f)
	 {
	 fwrite(pRecv,1,nRet,f);
	 fclose(f);
	 }*/
		if (gpData->DealData(pRecv,nRet) < 0)
		{
			gpData->m_lockData.unlock();
			free(pRecv);
			return false;
		}
	}
	gpData->m_lockData.unlock();
	free(pRecv);
	if (gpData->m_vpStocks.size() <= 0)
		return false;
	else
		return true;
}

bool CDlgLogin::GetServerListData()
{
	CShortSocket sk;
	char * pRecv;
	int nRet;
	int nLen;

	gpData->m_lockData.lock();
	char acReq[1024];
	nLen = gpData->MakeOnlineInitReq(acReq,0x0018);

	pRecv = (char *)malloc(1024 * 1024);
	nRet = sk.SendAndRecv((char *)gCfg.m_strDeployIP.c_str(),gCfg.GetDeployPort(),acReq,nLen,pRecv,1024 * 1024,m_pWait->GetSafeHwnd(),&gCfg.m_proxyOption);
	if (nRet <= 0)
		nRet = sk.SendAndRecv((char *)gCfg.m_strDeployIPBak.c_str(),gCfg.GetDeployPort(),acReq,nLen,pRecv,1024 * 1024,m_pWait->GetSafeHwnd(),&gCfg.m_proxyOption);
	if (nRet > 0)
	{
		gpData->DealData(pRecv,nRet);
	}
	gpData->m_lockData.unlock();
	free(pRecv);
	if (nRet > 0)
		return true;
	else
		return false;
}

bool CDlgLogin::CreateConnect(int c_nFirst)
{
	bool bRet = false;
	//gpCommSocket->m_lockSocket.lock();
	if (gpCommSocket->ConnectTo(gCfg.m_strQuoteIP,gCfg.GetQuotePort()))
		if (gpCommSocket->m_socket != INVALID_SOCKET)
		{		
			char acBuf[2048];
			int nLen = gpData->MakeUserOnlineReq(acBuf,gpData->m_nUserID,c_nFirst);		
			nLen = gpCommSocket->SendData(acBuf,nLen,true,acBuf,2048);
			if (nLen > 0)
			{
				int nRet = gpData->DealData(acBuf,nLen);
				if (nRet >= 0)
					bRet = true;
				if (gpData->m_hwndNotify)
					::PostMessage(gpData->m_hwndNotify,WM_CONNECT_SUCCESS,0,1);
			}
		}
		//gpCommSocket->m_lockSocket.unlock();
		return bRet;
}

void CDlgLogin::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	/*
	CBrush br;
	dc.SetBkMode(TRANSPARENT);
	br.CreatePatternBrush(&m_loginCheckBK);
	CRect rect;
	GetClientRect(rect);
	dc.FillRect(rect,&br);
	br.DeleteObject();*/
}

void CDlgLogin::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	if (bShow)
	{
		m_editName.SetFocus();
		CString str;
		m_editName.GetWindowText(str);
		m_editName.SetSel(str.GetLength(),-1);
	}
}

void CDlgLogin::OnBnClickedButtonActive()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("对不起，此功能暂未提供！"),_T("提示"),MB_OK + MB_ICONWARNING);
}

void CDlgLogin::OnBnClickedButtonLogNow()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedOk();
}

void CDlgLogin::OnEnKillfocusEditName()
{
	// TODO: 在此添加控件通知处理程序代码
	m_editName.SetState(FALSE);
}

void CDlgLogin::OnEnSetfocusEditName()
{
	// TODO: 在此添加控件通知处理程序代码
	m_editName.SetState(TRUE);
}

void CDlgLogin::OnStnClickedStaticUpgrade()
{
	// TODO: 在此添加控件通知处理程序代码
	//if (gCfg.m_usUpdateType == 0)
	//	return;

	DoUpgrade();
}

void CDlgLogin::OnBnClickedBtnClose()
{
	// TODO: 在此添加控件通知处理程序代码
	this->OnCancel();	
}

void CDlgLogin::OnBnClickedBtnNotuser()
{
	// TODO: 在此添加控件通知处理程序代码	
	CDlgCommSet dlg;
	dlg.DoModal();
}

void CDlgLogin::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_NCLBUTTONDOWN,   HTCAPTION,   MAKELPARAM(point.x,   point.y));
	PostMessage(WM_LBUTTONUP,   NULL,   MAKELPARAM(point.x,   point.y));

	CDialog::OnLButtonDown(nFlags, point);
}


bool CDlgLogin::GetInitData(CShortSocket &c_sk)
{		
	bool bRet;
	int nRetryTime = 0;
	int nStep = 0;
	while(true)
	{
		//OnTimer(103);
		if (nStep == 0)		
		{
			if (m_pWait)
				((CDlgWaitData *)m_pWait)->SetDataInfo(_T("基础数据"));
			gpData->m_nErrorCode = 0;
			bRet = GetStockInfo(c_sk);
			if (bRet == false && gpData->m_nErrorCode == 0xFFFE)
			{
				MessageBox(gpData->m_strErrorMsg,_T("提示"));
				return false;
			}
		}
		else
			if (nStep == 1)
			{
				if (m_pWait)
					((CDlgWaitData *)m_pWait)->SetDataInfo(_T("行情数据"));
				bRet = true;//GetReportInitData(c_sk);
			}
			else
				if (nStep == 2)
				{
					bRet = true;
				}
				else
					if (nStep == 3)
					{
						bRet = true;
					}
					else
						if (nStep == 4)
						{
						}
						else
							if (nStep == 6)
							{
								bRet = true;
							}
							if (bRet)
							{
								nStep++;
								nRetryTime = 0;
								if (nStep == 7)
									break;
							}
							else
							{
								nRetryTime++;
								if (nRetryTime == 3)
									break;
							}
	}
	m_bInitDataOver = bRet;
	return bRet;
}
void CDlgLogin::OnTimer(UINT_PTR nIDEvent)
{	
	if (nIDEvent == 102)
	{
		UpdateData();
	}
	if (nIDEvent == 103)
	{
		//this->m_pWait->Invalidate();
		MSG   Message; 
		while (::PeekMessage(&Message,   NULL,   0,   0,   PM_REMOVE))     
		{ 
			::TranslateMessage(&Message); 
			::DispatchMessage(&Message); 
		} 
	}
}
void CDlgLogin::OnBnClickedLogon()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedOk();
}

BOOL CDlgLogin::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialog::OnWndMsg(message, wParam, lParam, pResult);
}

LRESULT CDlgLogin::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialog::WindowProc(message, wParam, lParam);
}

INT_PTR CDlgLogin::DoModal()
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialog::DoModal();
}

void CDlgLogin::OnBnClickedCheckAutorun()
{
	// TODO: 在此添加控件通知处理程序代码
}
