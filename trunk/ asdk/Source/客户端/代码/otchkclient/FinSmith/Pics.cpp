// Pics.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "PicWnd.h"
#include "rightWnd.h"
#include "DlgList.h"
#include "TraceWnd.h"
#include "Pics.h"
#include "DlgDiagnose.h"
#include "../public/commsocket.h"

// CPics

IMPLEMENT_DYNAMIC(CPics, CWnd)

CPics::CPics()
{
	m_bInGetReport = false;
	m_nViewType = 1;
	m_nViewMode = 1;
	m_pPicWnd = NULL;
	m_pRightWnd = NULL;	
	m_pList = NULL;
	m_pTrace = NULL;
}

CPics::~CPics()
{	
}


BEGIN_MESSAGE_MAP(CPics, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CPics 消息处理程序



int CPics::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pPicWnd = new CPicWnd(PTTREND,this,(CDlgDiagnose *)GetParent());
	m_pPicWnd->Create(NULL,NULL,0,CRect(),this,0);

	m_pRightWnd = new CRightWnd();
	m_pRightWnd->Create(NULL,NULL,0,CRect(),this,0);

	m_pList = new CDlgList(this);
	m_pList->Create(IDD_DLG_LIST,this);

	m_pTrace = new CTraceWnd(1);
	m_pTrace->Create(NULL,NULL,0,CRect(),this,0);

	SetTimer(101,1000*4,0);
	SetViewType(1);
	return 0;
}

void CPics::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	SetLayout();
}

void CPics::SetLayout()
{
	if (m_nViewType == 0)
	{
		if (m_pPicWnd)
		{
			CRect rect;
			GetClientRect(rect);			
			if (m_nViewMode == 1)
			{
				int nW = m_pRightWnd->GetWidth();
				rect.right -= nW;//186;
				m_pPicWnd->MoveWindow(rect);
				rect.left = rect.right;
				rect.right += nW;
				m_pRightWnd->MoveWindow(rect);			
			}
			else
			if (m_nViewMode == 0)
			{
				m_pPicWnd->MoveWindow(rect);
			}
		}
	}
	else
	if (m_nViewType == 1)
	{
		if (m_pList)
		{
			CRect rect;
			GetClientRect(rect);
			m_pList->MoveWindow(rect);
		}
	}
	else
	if (m_nViewType == 2)
	{
		if (m_pTrace)
		{
			CRect rect;
			GetClientRect(rect);
			m_pTrace->MoveWindow(rect);
		}
	}
}

void CPics::SetViewType(int c_nViewType)
{
	if (c_nViewType == 0)
	{
		m_pList->ShowWindow(SW_HIDE);
		m_pTrace->ShowWindow(SW_HIDE);
		m_nViewType = c_nViewType;
		SetViewMode(m_nViewMode);
	}
	else
	if (c_nViewType == 1)
	{
		m_nViewType = c_nViewType;
		
		m_pTrace->ShowWindow(SW_HIDE);
		m_pPicWnd->ShowWindow(SW_HIDE);
		m_pRightWnd->ShowWindow(SW_HIDE);
		m_pList->ShowWindow(SW_SHOW);
		//SetViewMode(m_nViewMode);
	}
	else//分笔
	if (c_nViewType == 2)
	{
		m_pTrace->ShowWindow(SW_SHOW);
		m_pPicWnd->ShowWindow(SW_HIDE);
		m_pRightWnd->ShowWindow(SW_HIDE);
		m_pList->ShowWindow(SW_HIDE);
		m_nViewType = c_nViewType;
	}
	else//分价
	if (c_nViewType == 3)
	{
		m_pTrace->ShowWindow(SW_HIDE);
		m_nViewType = c_nViewType;
	}
	SetLayout();
}

void CPics::SetViewMode(int c_nViewMode)
{
	if (c_nViewMode == 0)
	{
		m_pPicWnd->ShowWindow(SW_SHOW);
		m_pRightWnd->ShowWindow(SW_HIDE);
	}
	else
	if (c_nViewMode == 1)
	{
		m_pPicWnd->ShowWindow(SW_SHOW);
		m_pRightWnd->ShowWindow(SW_SHOW);
	}
	m_nViewMode = c_nViewMode;
}

void CPics::SetStockCode(CString c_strCode)
{
	SStock * pStock = gpData->GetStock(c_strCode);	
	if (pStock)
	{
		m_strStockCode = pStock->m_sQuote.szStockCode;
	}
	else
		return;
	if (m_pPicWnd)
	{
		m_pPicWnd->setStockCode(m_strStockCode);
		m_pRightWnd->SetStockCode(m_strStockCode);
	}
	SetLayout();
}

void CPics::FreshData(int c_nType)
{
	if (m_pList == NULL)
		return;

	if (m_pList->IsWindowVisible())
	{
		if (c_nType == 100)
			m_pList->FreshHideData();		
		else
			m_pList->FreshData();
	}

	if(m_pPicWnd->IsWindowVisible())
	{
		m_pPicWnd->FreshData();
	}
	if (m_pRightWnd->IsWindowVisible())
	{
		m_pRightWnd->Invalidate();
	}
	if (m_pTrace->IsWindowVisible())
	{
		m_pTrace->FreshData();
	}
}

BOOL CPics::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	return CWnd::OnCommand(wParam, lParam);
}


int CPics::SetWins()
{
	if (m_nViewMode == 0)
	{
		m_nViewMode = 1;
	}
	else
	{
		m_nViewMode = 0;
	}
	SetViewMode(m_nViewMode);
	SetLayout();
	return m_nViewMode;
}

void CPics::GotoStockList(int c_nCode,int c_nSortCol,bool c_bAsc)
{
	if (m_pList)
	{
		if (c_nCode > 0)
		{
			SetViewType(1);
			m_pList->m_nBeginPaintCol = 3;
			m_pList->SetSortCol(c_nSortCol);
			m_pList->m_bAsc = c_bAsc;
			m_pList->SetItems(c_nCode,c_nSortCol,c_bAsc);
			m_pList->SetPage();
			m_pList->SetFocus();
		}
		else
		{
			if (m_pList->m_nListCode == -1)
				return;
			SetViewType(1);
			m_pList->SetFocus();
		}
	}
}

void CPics::GotoTraceWnd()
{
	if (m_pTrace)
	{
		SetViewType(2);
		m_pTrace->SetStockCode(m_strStockCode);
		m_pTrace->SetFocus();
		SetLayout();
	}
}

void CPics::EscapeTraceWnd()
{
	if (m_pTrace)
	{
		SetViewType(0);		
		SetLayout();
	}
}

void CPics::Refresh()
{
	Invalidate();
	if (m_pPicWnd)
		m_pPicWnd->Invalidate();
	if (m_pRightWnd)
		m_pRightWnd->Invalidate();
	if (m_pList)
		m_pList->Invalidate();
	if (m_pTrace)
		m_pTrace->Invalidate();
}
void CPics::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (IsWindowVisible() == false)
		return;

	if (m_bInGetReport == false && nIDEvent == 101 && m_strStockCode.GetLength() > 0)
	{
		m_bInGetReport = true;
		GetReport(false);
		m_bInGetReport = false;
	}
	CWnd::OnTimer(nIDEvent);
}

void CPics::GetReport(bool c_bWait)
{
	int nLen;
	char acReq[1024];
	if (gpData->m_nWorkDay == 0)
	{
		nLen = gpData->MakeLineTestReq(acReq);	
		if (gpCommSocket->SendData(acReq,nLen,true) <= 0)
			return;
	}
	/*
	USES_CONVERSION;
	nLen = gpData->MakePicReq(acReq,(char *)W2A(m_strStockCode.GetBuffer()),1);
	m_strStockCode.ReleaseBuffer();
	if (nLen > 0 && gpCommSocket && gpCommSocket->m_socket != INVALID_SOCKET)
		if (gpCommSocket->SendData(acReq,nLen,c_bWait) <= 0 && c_bWait == false)
		{
			gpCommSocket->Disconnect();
			::PostMessage(gpData->m_hwndMain,WM_CONNECT_SUCCESS,0,0);
		}*/
}
