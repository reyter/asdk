// HHUpdateClient.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "HHUpdateClient.h"
#include "HHUpdateClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHHUpdateClientApp

BEGIN_MESSAGE_MAP(CHHUpdateClientApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CHHUpdateClientApp ����

CHHUpdateClientApp::CHHUpdateClientApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CHHUpdateClientApp ����

CHHUpdateClientApp theApp;


// CHHUpdateClientApp ��ʼ��

BOOL CHHUpdateClientApp::InitInstance()
{
	if (!FirstInstance())
	{
		AfxMessageBox("�����Ѿ�����");
		return FALSE;	//�Ѿ���ʵ�������ˣ��˳�
	}
		

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();
	AfxInitRichEdit2();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CHHUpdateClientDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȷ�������ر�
		//�Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//�Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

BOOL CHHUpdateClientApp::FirstInstance()
{
	CWnd *pWndPrev, *pWndChild; 
	//�������������������������ж��Ƿ��Ѿ���ʵ��������
	if (pWndPrev = CWnd::FindWindow(_T("#32770"),"���NSD�Զ���������"))//#32770��Ĭ�ϵĶԻ���������
	{
		//������ھͽ��伤�����ʾ����	  
		pWndChild = pWndPrev->GetLastActivePopup(); 	  
		//�������С���ľͻ�ԭ����
		if (pWndPrev->IsIconic()) 
			pWndPrev->ShowWindow(SW_RESTORE);      	  
		pWndChild->SetForegroundWindow();         	 
		return FALSE;                             
	}
	else
		return TRUE;                             
}
