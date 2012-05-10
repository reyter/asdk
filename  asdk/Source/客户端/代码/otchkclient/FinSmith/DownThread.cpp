// CommThread.cpp : 实现文件
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
	// TODO: 在此执行任意逐线程初始化
	return TRUE;
}

int CDownThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDownThread, CWinThread)
END_MESSAGE_MAP()


// CCommThread 消息处理程序

int CDownThread::Run()
{
	// TODO: 在此添加专用代码和/或调用基类	
	if (m_pLogin)//登录窗口有效
	{
		bool bRet = m_pLogin->GetInitData(m_sk);
		m_sk.Disconnect();
		m_pLogin->m_bDownRet = true;		
	}
	else//没有登录窗口，则认为是登陆后开盘更新数据
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