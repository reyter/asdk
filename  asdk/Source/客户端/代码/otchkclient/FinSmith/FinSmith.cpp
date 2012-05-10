// FinSmith.cpp : ����Ӧ�ó��������Ϊ��
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

// CFinSmithApp ����

CFinSmithApp::CFinSmithApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CFinSmithApp ����

CFinSmithApp theApp;


// CFinSmithApp ��ʼ��

BOOL CFinSmithApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��

#ifndef _DEBUG
	HANDLE   hMutex;
	
	hMutex   =   CreateMutex(NULL,   TRUE,   _T("asdtk_cli"));

	if(GetLastError()   ==   ERROR_ALREADY_EXISTS)   
	{	   
		AfxMessageBox(_T("�����Ѿ����У�"));
		HWND hwnd;
		
		hwnd = FindWindow(NULL,VERNAME);
		ShowWindow(hwnd,SW_RESTORE);
		SetForegroundWindow(hwnd);
		return   FALSE;
	}

#endif
	USES_CONVERSION;
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	//���ù���·��
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

	gpSkinManager->SetDefaultFontName(_T("΢���ź�"),_T("Arial"));

	gpSkinManager->InitFont();
	gpSkinManager->CreateFont();

	gpSkinManager->LoadSkin("comm");

	CDlgWaitData * pDlgWait;
	pDlgWait = new CDlgWaitData();
	pDlgWait->Create(IDD_DLG_WAIT_DATA);

	
    //���������	
	
    CDlgLogin logIn;
	bool bGetSvrList = logIn.GetServerListData();
	gSvr.Load("svrlist.xml");
	
/*	if (logIn.GetServer() == false)
	{
		MessageBox(0,_T("���ӷ�����ʧ�ܣ�"),_T("��ʾ"),MB_OK);
		return FALSE;
	}	

	if (gCfg.m_nFixedPort > 0)
	{
		gCfg.m_nQuoteServerPort = gCfg.m_nFixedPort;
		gCfg.m_nQuoteServerPortBAK = gCfg.m_nFixedPort;
		gCfg.m_nNewsServerPort = gCfg.m_nFixedPort;
	}
	
	logIn.CheckVersion();//���汾	
*/
	
	DeleteTmpFile(gpData->m_acDataPath);
	//��½��ʼ
	logIn.m_pWait = pDlgWait;
	logIn.m_bToGetSvrList = !bGetSvrList;
	if (logIn.DoModal() != IDOK)
	{
		return FALSE;
	}
	
	gCfg.m_strUser = gpData->m_acLoginCode;
	pDlgWait->ShowWindow(SW_SHOW);

	//���������

	//��½����
	//CShortSocket sk;
///-	int nLen;

	gpCommSocket = new CCommSocket();
	gpCommSocket->m_pproxyOption = &gCfg.m_proxyOption;

	//�����߳�

	gpCommThread=   new   CCommThread();
	gpCommThread->CreateThread(CREATE_SUSPENDED);   
	gpCommThread->SetThreadPriority(THREAD_PRIORITY_HIGHEST);//THREAD_PRIORITY_NORMAL);   
	gpCommThread->m_bAutoDelete   =   TRUE; //   �Զ�ɾ���߳�   
	gpCommThread->SetCommSocket(gpCommSocket);	
	gpCommThread->ResumeThread();	

	//����������������ĳ�����

	if (logIn.CreateConnect(1) == false)
	{/*
		if (gpData->m_nErrorCode == 0xFFFE)
		{
			gpCommSocket->Disconnect();
			MessageBox(0,gpData->m_strErrorMsg,_T("��ʾ"),MB_OK);
			return false;
		}*/
	}
	gpCommThread->m_bFirst = false;
	if (gpCommSocket && gpCommSocket->m_socket != INVALID_SOCKET)
	{
	}
	pDlgWait->ShowWindow(SW_HIDE);

    //added by wangchao 2009-06-26
    //ԭ����������ʱ�ȴ����ݽ����˳�ʱ�ľ���
	
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
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}
	
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
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
