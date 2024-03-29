// DlgDiagnose.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "picWnd.h"
#include "rightWnd.h"
#include "TraceWnd.h"
#include "DlgDiagnose.h"
#include "../public/commsocket.h"
#include "FlatSplitterWnd.h"
#include "pics.h"
#include "DlgContainer.h"
#include "myhtmlview.h"
#include "MoveWnd.h"
#include "DlgTechDesc.h"
#include "DlgTrade.h"
#include "topdlg.h"
#include "EmptyWnd.h"
#include "..\\WinUnit\\IUserWin.h"
#include "DlgList.h"
#include "DlgKDetail.h"

// CDlgDiagnose 对话框

IMPLEMENT_DYNAMIC(CDlgDiagnose, CDialog)

CDlgDiagnose::CDlgDiagnose(CWnd* pParent /*=NULL*/)
: CDialog(CDlgDiagnose::IDD, pParent)
{
	//m_pF10 = NULL;
	m_nSizeMode = 1;
	m_pPics = NULL;
	m_pSplit = NULL;
	m_pContainer = NULL;
	m_pMove = NULL;
	m_nViewType = PICMAX;
	m_nSubType = 0;//无类型
}

CDlgDiagnose::~CDlgDiagnose()
{
}

void CDlgDiagnose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDiagnose, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)

	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_NCMOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_CONTAINER,OnContainerMsg)
END_MESSAGE_MAP()


// CDlgDiagnose 消息处理程序

BOOL CDlgDiagnose::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(rect);
	pDC->FillRect(rect,&CBrush(gpSkinManager->getColor(BKCOLOR)));

	return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}

BOOL CDlgDiagnose::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化		
	CSize size(100,60);
	//m_pSplit = new CFlatSplitterWnd();
	//m_pSplit->Create(this,3,1,size,NULL,WS_CHILD | WS_VISIBLE);

	m_pMove = new CMoveWnd();
	m_pMove->Create(NULL,NULL,WS_CHILD|WS_VISIBLE,CRect(),this,0);

	m_pPics = new CPics();
	m_pPics->Create(NULL,NULL,0,CRect(),this,0);		

	m_pContainer = new CDlgContainer();
	m_pContainer->Create(IDD_DLG_CONTAINER,this);
	gpContainer = m_pContainer;
	m_pMove->SetControlWnds(m_pPics,m_pContainer);

	m_pTrade = new CDlgTrade();
	m_pTrade->Create(IDD_TRADE,m_pContainer);
	m_pTrade->SetTitle(SUBTRADE_TITLE);
	m_pContainer->AddIUserWin(m_pTrade);

	m_pNull = new CEmptyWnd();
	m_pNull->Create(NULL,NULL,WS_CHILD|WS_VISIBLE,CRect(),this,0);
	m_pNull->SetTitle(SUBNEWS_TITLE);
	m_pContainer->AddIUserWin(m_pNull);

	SetViewType(PICMAX);
	SetLayout();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgDiagnose::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_pPics)
	{
		SetLayout();
		Invalidate();
	}
	else
	{
	}
}
extern void Log(char * c_p);

void CDlgDiagnose::SetStockCode(CString c_strCode)
{	
///-	char acStockSelectFields[16];

	if (c_strCode.IsEmpty())
	{
		m_strStockCode = c_strCode;
		SetViewType(PICMAX);
		SetSubType(0);		
		SetLayout();
		Invalidate();
		return;
	}
	SStock * pStock = gpData->GetStock(c_strCode);
	if (pStock)
	{
		m_strStockCode = pStock->m_sQuote.szStockCode;
	}
	else
		return;
	char acCode[16];
	strncpy(acCode,pStock->m_sQuote.szStockCode,6);
	acCode[6] = 0;

	m_pPics->SetViewType(0);

	if (m_pPics)
	{
		m_pPics->SetStockCode(m_strStockCode);
	}
	if (m_nViewType == SUBMAX)
	{
		SetViewType(PICMAX);
		SetSubType(0);
	}

	if (m_pContainer->IsWindowVisible())
		m_pContainer->SetStockCode(m_strStockCode);
	m_pPics->SetFocus();
	SetLayout();	
	m_pPics->m_pPicWnd->SetFocus();	
}
void CDlgDiagnose::SetViewType(int c_nViewType)
{
	m_nViewType = c_nViewType;
	if (m_nViewType == PICMAX)
	{
		m_pPics->ShowWindow(SW_SHOW);
		if(m_pContainer)
		{
			m_pContainer->ShowWindow(SW_HIDE);
			m_pContainer->SetViewMode(CONTAINER_HIDE);
		}
		m_pMove->ShowWindow(SW_HIDE);
	}
	else
	if (m_nViewType == SUBMAX)
	{
		m_pPics->ShowWindow(SW_HIDE);
		if (m_pContainer)
		{
			m_pContainer->ShowWindow(SW_SHOW);
			m_pContainer->SetViewMode(CONTAINER_MAX);
		}
		m_pMove->ShowWindow(SW_HIDE);
	}
	else
	if (m_nViewType == PICANDSUB)
	{
		m_pPics->ShowWindow(SW_SHOW);
		m_pContainer->SetViewMode(CONTAINER_MIN);
		m_pContainer->ShowWindow(SW_SHOW);	
		m_pMove->ShowWindow(SW_SHOW);
	}
}

void CDlgDiagnose::SetSubType(int c_nSubType)
{
	m_nSubType = c_nSubType;
	if (m_nViewType == PICANDSUB)
		m_pContainer->ShowMin();

	if (m_nSubType == 0)
		return;

		if (m_nSubType == SUBTRADE)
		{
			m_pContainer->ActiveWnd(SUBTRADE_TITLE);
		}

}

BOOL CDlgDiagnose::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->wParam == VK_ESCAPE)
	{		
		if (pMsg->message == WM_KEYUP)
			m_pPics->m_pPicWnd->KeyOperate(pMsg->wParam);
		return TRUE;
	}
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (m_pTopDlg && m_pTopDlg->IsWindowVisible())
			m_pTopDlg->ShowWindow(SW_HIDE);
	}	

	if (pMsg->message == WM_SYSKEYUP && pMsg->wParam == VK_F12)
	{				
		ShowTradeWnd();
		return TRUE;
	}

	if (pMsg->message == WM_KEYDOWN)
	{		
		//if (pMsg->hwnd == m_pPics->m_pTrace->GetSafeHwnd())
		//{
		//	return CDialog::PreTranslateMessage(pMsg);
		//}
		//else
		if (pMsg->hwnd == m_pPics->m_pPicWnd->GetSafeHwnd())
		{
			if (pMsg->wParam == VK_DOWN || pMsg->wParam == VK_UP || pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT || pMsg->wParam == VK_RETURN || pMsg->wParam == VK_TAB)
			{
				m_pPics->m_pPicWnd->KeyOperate(pMsg->wParam);
				if (pMsg->wParam == VK_RETURN)
					return TRUE;
				else
					return TRUE;
			}
			if (pMsg->wParam == VK_PRIOR || pMsg->wParam == VK_NEXT)
			{
				m_pPics->m_pPicWnd->KeyOperate(pMsg->wParam);
				return TRUE;
			}
			if (pMsg->wParam == VK_F3 || pMsg->wParam == VK_F4 || pMsg->wParam == VK_F5 || pMsg->wParam == VK_F8 || pMsg->wParam == VK_F6)
			{
				m_pPics->m_pPicWnd->KeyOperate(pMsg->wParam);
				return TRUE;
			}
		}
		else
		{
			if (pMsg->wParam == VK_RETURN)
			{
				if (m_pPics->m_pPicWnd->IsWindowVisible())
				{
					m_pPics->m_pPicWnd->KeyOperate(pMsg->wParam);	
					m_pPics->m_pPicWnd->SetFocus();
				}
				return TRUE;
			}
		}/*
		 if ((pMsg->wParam >='0' && pMsg->wParam <= '9')
		 ||(pMsg->wParam >='a' && pMsg->wParam <= 'z')
		 ||(pMsg->wParam >='A' && pMsg->wParam <= 'Z'))
		 {
		 if (m_pTopDlg->ActiveByKey(pMsg->wParam))
		 return TRUE;
		 }*/
	}
	if (pMsg->message == WM_CHAR)
	{
		if ((pMsg->wParam >='0' && pMsg->wParam <= '9')
			||(pMsg->wParam >='a' && pMsg->wParam <= 'z')
			||(pMsg->wParam >='A' && pMsg->wParam <= 'Z'))
		{
			if (m_pTopDlg->ActiveByKey(pMsg->wParam))
				return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgDiagnose::SetTopDlg(CTopDlg * c_pTopDlg)
{
	m_pTopDlg = c_pTopDlg;
}

void CDlgDiagnose::SetLayout()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	OnEraseBkgnd(&dc);

	CRect rect;
	GetClientRect(rect);
	CRect rectClient;
	rectClient = rect;

	if (m_nViewType == SUBMAX)
	{
		m_pContainer->MoveWindow(rect);
		m_pPics->m_pPicWnd->SetMouseLineOn(false);
		return;
	}
	if(m_nViewType == PICMAX)
	{
		m_pPics->MoveWindow(rect);
		return;
	}
	int nHeight = rect.Height()/3;
	if (nHeight < 260)
		nHeight = 260;

	rect.bottom -= nHeight + 8;
	m_pPics->MoveWindow(rect);

	rect.top = rect.bottom;
	rect.bottom = rect.top + 8;
	m_pMove->MoveWindow(rect);

	rect.top = rect.bottom;
	rect.bottom = rectClient.bottom;
	m_pContainer->MoveWindow(rect);
	m_pContainer->SetLayout();

	GetClientRect(rect);
	m_pMove->SetMoveSize(rect.top + 220,rect.bottom - 200);

}
void CDlgDiagnose::ShowTradeWnd()
{		
	SetViewType(PICANDSUB);
	SetSubType(SUBTRADE);
	SetLayout();
}


LRESULT CDlgDiagnose::OnContainerMsg(WPARAM wParam, LPARAM lParam)
{
	if (wParam == CONTAINER_HIDE)
	{
		SetViewType(PICMAX);		
	}
	else
		if (wParam == CONTAINER_MAX)
		{
			SetViewType(SUBMAX);
		}
		else
			if (wParam == CONTAINER_MIN)
			{
				SetViewType(PICANDSUB);
			}

			SetLayout();
			return 0;
}

void CDlgDiagnose::FreshData(int c_nType)
{
	m_pPics->FreshData(c_nType);
	if (m_pContainer)
	m_pContainer->FreshData();
}

int CDlgDiagnose::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	EnableToolTips(TRUE);
	return 0;
}

int CDlgDiagnose::OnToolHitTest(CPoint point, TOOLINFO * pTI) const
{
	return -1;
}

BOOL CDlgDiagnose::OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{
	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	CString strTipText;
	UINT nID = pNMHDR->idFrom;

	if( nID == 0 )	  	// Notification in NT from automatically
		return FALSE;   	// created tooltip

	int row = ((nID-1) >> 10) & 0x3fffff ;
	int col = (nID-1) & 0x3ff;

	// Use Item's name as the tool tip. Change this for something different.
	// Like use its file size, etc.
	//strTipText = GetItemText( row, col );

	return TRUE;    // message was handled
}

void CDlgDiagnose::ResetFont()
{
	SetLayout();
}

void CDlgDiagnose::ResetSkin()
{
	ResetFont();
	m_pPics->m_pList->SetLayout();	
	m_pPics->SetLayout();
	/*m_pMove->ResetSkin();
	m_pMarketInformation->ResetSkin();
	m_pFxsInformation->ResetSkin();*/
	m_pContainer->ResetSkin();
	/*m_pPjSort->ResetSkin();
	m_pYcSort->ResetSkin();
	m_pPjtg->ResetSkin();
	m_pYctg->ResetSkin();
	m_pIndustryUp->ResetSkin();
	m_pIndustryDown->ResetSkin();
	m_pIndustryMonitor->ResetSkin();
	m_pGroupAnaly->ResetSkin();
	m_pChg->ResetSkin();
	m_pGraph->ResetSkin();
	m_pDlgResearch->ResetSkin();
	m_pDlgLedsSelect->ResetSkin();*/
	Invalidate();
}
void CDlgDiagnose::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	::PostMessage(gpData->m_hwndMain,WM_CHANGE_VIEWMODE,0,0);
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CDlgDiagnose::OnConnectSuccess()
{
	SetStockCode(m_strStockCode);
}

void CDlgDiagnose::Refresh()
{
	Invalidate();
	if (m_pPics)
	{
		m_pPics->Refresh();		
	}
	if (m_pContainer)
		m_pContainer->Refresh();
}
void CDlgDiagnose::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnTimer(nIDEvent);
}

void CDlgDiagnose::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnNcMouseMove(nHitTest, point);
}

void CDlgDiagnose::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString strTitle;
	if (m_rectSize.PtInRect(point))
	{
		::PostMessage(gpData->m_hwndMain,WM_CHANGE_VIEWMODE,0,0);
		return;
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgDiagnose::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnMouseMove(nFlags, point);
}
/*
LRESULT CDlgDiagnose::OnContainerMsg(WPARAM wParam, LPARAM lParam)
{
	if (wParam == CONTAINER_HIDE)
	{
		SetViewType(PICMAX);		
	}
	else
		if (wParam == CONTAINER_MAX)
		{
			SetViewType(SUBMAX);
		}
		else
			if (wParam == CONTAINER_MIN)
			{
				SetViewType(PICANDSUB);
			}

			SetLayout();
			return 0;
}
*/