// CommThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinSmith.h"
#include "DlgLogin.h"
#include "../public/ShortSocket.h"
#include "DownThread.h"

// CCommThread

IMPLEMENT_DYNCREATE(CDownThread, CWinThread)

CDownThread::CDownThread()
: m_bExitFlag(false)
{
	m_hwndMain = 0;
	m_sk.SetKeepLive(true);
}

CDownThread::~CDownThread()
{
}

BOOL CDownThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CDownThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDownThread, CWinThread)
END_MESSAGE_MAP()


// CCommThread ��Ϣ�������

int CDownThread::Run()
{
	// TODO: �ڴ����ר�ô����/����û���	
	if (m_pLogin)//��¼������Ч
	{
		bool bRet = m_pLogin->GetInitData(m_sk);
		m_sk.Disconnect();
		m_pLogin->m_bDownRet = true;		
	}
	else//û�е�¼���ڣ�����Ϊ�ǵ�½���̸�������
	{
		CDlgLogin dlg;		
		dlg.GetStockInfo(m_sk);
		::PostMessage(gpData->m_hwndNotify,WM_UPDATE_QUOTEDATA,REPORTDATA,102);
		m_sk.Disconnect();
	}
	PostThreadMessage(WM_QUIT,0,0);
	return CWinThread::Run();
}

void CDownThread::SetMainHwnd(HWND c_hwnd)
{
	m_hwndMain = c_hwnd;
}