// CommThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinSmith.h"
#include "CommThread.h"
#include "../public/CommSocket.h"

// CCommThread

IMPLEMENT_DYNCREATE(CCommThread, CWinThread)
CCommThread * gpCommThread;

CCommThread::CCommThread()
: m_bExitFlag(false)
{
	m_hwndMain = 0;
	m_pComm = NULL;
	m_bFirst = true;
}

CCommThread::~CCommThread()
{
}

BOOL CCommThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CCommThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CCommThread, CWinThread)
END_MESSAGE_MAP()


// CCommThread ��Ϣ�������

int CCommThread::Run()
{
	// TODO: �ڴ����ר�ô����/����û���
	unsigned short usType;
	while(!m_bExitFlag)
	{
		if (m_pComm == NULL)
		{
			Sleep(50);
			continue;
		}
		if (m_pComm->m_socket != INVALID_SOCKET)
		{
			if (m_pComm->RecvData(usType))
			{
				//if (m_hwndMain != 0)
				//	::PostMessage(m_hwndMain,WM_UPDATE_QUOTEDATA,usType,0);
			}
			Sleep(10);
		}
		else
		{
			if(m_bFirst == false)
			{
				::PostMessage(gpData->m_hwndNotify,WM_CONNECT_SUCCESS,0,100);//��ʾ���Ӵ���
				if( gpCommSocket->ConnectTo(gCfg.m_strQuoteIP,gCfg.GetQuotePort()))
				{
					if (m_pComm->m_socket != INVALID_SOCKET && gpData->m_hwndNotify)
					{
						::PostMessage(gpData->m_hwndNotify,WM_CONNECT_SUCCESS,0,1);

						char acBuf[2048];
						int nLen = gpData->MakeUserOnlineReq(acBuf,gpData->m_nUserID,0);
						gpCommSocket->SendData(acBuf,nLen,false);
					}
				}
			}
			else
				Sleep(10);
		}
	}
	
	PostThreadMessage(WM_QUIT,0,0);
	return CWinThread::Run();
}


void CCommThread::SetCommSocket(CCommSocket * c_pComm)
{
	m_pComm = c_pComm;
}

void CCommThread::SetMainHwnd(HWND c_hwnd)
{
	m_hwndMain = c_hwnd;
}