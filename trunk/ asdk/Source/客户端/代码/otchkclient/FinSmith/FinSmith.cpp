// FinSmith.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "FinSmith.h"
#include "FinSmithDlg.h"
#include "../public/ShortSocket.h"
#include "../public/CommSocket.h"
#include "DlgWaitData.h"
#include "DlgUpdate.h"
#include "DlgSetIP.h"
#include "DlgLogin.h"
#include "CommThread.h"
#include "TechManager.h"
#include "ping.h"
#include "../public/CommSocket.h"
#include "../public/CommFunc.h"
#include "../winunit/IUserWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFinSmithApp

BEGIN_MESSAGE_MAP(CFinSmithApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CFinSmithApp 构造

CFinSmithApp::CFinSmithApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CFinSmithApp 对象

CFinSmithApp theApp;


// CFinSmithApp 初始化

BOOL CFinSmithApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名

#ifndef _DEBUG
	HANDLE   hMutex;
	
	hMutex   =   CreateMutex(NULL,   TRUE,   _T("asdtk_cli"));

	if(GetLastError()   ==   ERROR_ALREADY_EXISTS)   
	{	   
		AfxMessageBox(_T("程序已经运行！"));
		HWND hwnd;
		
		hwnd = FindWindow(NULL,VERNAME);
		ShowWindow(hwnd,SW_RESTORE);
		SetForegroundWindow(hwnd);
		return   FALSE;
	}

#endif
	USES_CONVERSION;
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	//设置工作路径
	WCHAR acPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,acPath);
	
	GetModuleFileName(NULL,acPath,MAX_PATH);
	CString strVer = GetFileVersion((char *)W2A(acPath));
	unicodeToAscii(strVer,gCfg.m_acVer,sizeof(gCfg.m_acVer)-1);
	//strcpy(gCfg.m_acVer,"1.0.0.1");
	//strcpy(gCfg.m_acVer,(char *)W2A(strVer.GetBuffer()));
	//strVer.ReleaseBuffer();
	char aBuf[MAX_PATH];
	
	strcpy(aBuf,(char *)W2A(acPath));
	ExtractDirFromFullPath(aBuf);
	SetCurrentDirectory(toUnicodeString(aBuf,strlen(aBuf)));

	gCfg.m_strMac = GetMac();
	//gpCommThread = NULL;

	gpData = new CDataComm();
	gpSkinManager = new CSkinManager();
	
	sprintf(gpData->m_acCurPath,"%s",aBuf);
	sprintf(gpData->m_acDataPath,"%s\\data",aBuf);
	//mkdir(gpData->m_acDataPath);
	sprintf(gpData->m_acIniFile,"%s\\lcgj.ini",aBuf);   
	gCfg.Load("config.xml");
	gCfg.m_proxyOption.Init(toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
	WCHAR acBuf[32];
	GetPrivateProfileString(_T("SERVER"),_T("port"),_T("0"),acBuf,9,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
	
	gCfg.m_nFixedPort = atoi(W2A(acBuf));

	GetPrivateProfileString(_T("SERVER"),_T("GRPNAME"),_T(""),acBuf,32,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
	gCfg.m_strFixedSvrGrp = acBuf;
	gpData->m_nProductID = gCfg.m_nProduct;
	gpData->m_nRoleID = gCfg.m_nRole;

	CClientDC dc(NULL);
	gpSkinManager->LoadFontConfig();
	gpSkinManager->GetFonts(dc.m_hDC);

	gpSkinManager->SetDefaultFontName(_T("微软雅黑"),_T("Arial"));

	gpSkinManager->InitFont();
	gpSkinManager->CreateFont();

	gpSkinManager->LoadSkin("comm");

	CDlgWaitData * pDlgWait;
	pDlgWait = new CDlgWaitData();
	pDlgWait->Create(IDD_DLG_WAIT_DATA);

	
    //申请服务器	
	
    CDlgLogin logIn;
	bool bGetSvrList = logIn.GetServerListData();
	gSvr.Load("svrlist.xml");
	
/*	if (logIn.GetServer() == false)
	{
		MessageBox(0,_T("连接服务器失败！"),_T("提示"),MB_OK);
		return FALSE;
	}	

	if (gCfg.m_nFixedPort > 0)
	{
		gCfg.m_nQuoteServerPort = gCfg.m_nFixedPort;
		gCfg.m_nQuoteServerPortBAK = gCfg.m_nFixedPort;
		gCfg.m_nNewsServerPort = gCfg.m_nFixedPort;
	}
	
	logIn.CheckVersion();//检查版本	
*/
	
	DeleteTmpFile(gpData->m_acDataPath);
	//登陆开始
	logIn.m_pWait = pDlgWait;
	logIn.m_bToGetSvrList = !bGetSvrList;
	if (logIn.DoModal() != IDOK)
	{
		return FALSE;
	}
	
	gCfg.m_strUser = gpData->m_acLoginCode;
	pDlgWait->ShowWindow(SW_SHOW);

	//申请服务器

	//登陆结束
	//CShortSocket sk;
///-	int nLen;

	gpCommSocket = new CCommSocket();
	gpCommSocket->m_pproxyOption = &gCfg.m_proxyOption;

	//创建线程

	gpCommThread=   new   CCommThread();
	gpCommThread->CreateThread(CREATE_SUSPENDED);   
	gpCommThread->SetThreadPriority(THREAD_PRIORITY_HIGHEST);//THREAD_PRIORITY_NORMAL);   
	gpCommThread->m_bAutoDelete   =   TRUE; //   自动删除线程   
	gpCommThread->SetCommSocket(gpCommSocket);	
	gpCommThread->ResumeThread();	

	//创建到行情服务器的长连接

	if (logIn.CreateConnect(1) == false)
	{/*
		if (gpData->m_nErrorCode == 0xFFFE)
		{
			gpCommSocket->Disconnect();
			MessageBox(0,gpData->m_strErrorMsg,_T("提示"),MB_OK);
			return false;
		}*/
	}
	gpCommThread->m_bFirst = false;
	if (gpCommSocket && gpCommSocket->m_socket != INVALID_SOCKET)
	{
	}
	pDlgWait->ShowWindow(SW_HIDE);

    //added by wangchao 2009-06-26
    //原因：修正运行时等待数据界面退出时的警告
	
    if (pDlgWait)
    {
        pDlgWait->DestroyWindow();  
        pDlgWait = NULL;
        delete pDlgWait;
    }  
	
	CFinSmithDlg dlg;
	m_pMainWnd = &dlg;
	
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此处放置处理何时用“确定”来关闭
		//  对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用“取消”来关闭
		//  对话框的代码
	}
	
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

BOOL CFinSmithApp::ExitInstance()
{
	if (gpCommThread)
	{
		gpCommThread->m_bExitFlag = true;
		gpCommThread->m_pComm->Disconnect();
		::WaitForSingleObject(gpCommThread->m_hThread,INFINITE);
	}
	gpCommThread = NULL;
	delete gpData;
	delete gpSkinManager;
	CTechManager::freeInstance();
    return FALSE;

}
