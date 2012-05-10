// DlgContainer.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "DlgContainer.h"
#include "MyHtmlView.h"
#include "DlgDiagnose.h"
#include "DlgTrade.h"
#include "TopDlg.h"

// CDlgContainer 对话框

IMPLEMENT_DYNAMIC(CDlgContainer, CDialog)

CDlgContainer::CDlgContainer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgContainer::IDD, pParent)
{
	m_pActiveWnd = NULL;
	m_nViewMode = CONTAINER_MIN;
	m_bNoTitle = false;
	m_bInTimer = false;
	m_nReqSeq = 0;
	m_nAnsSeq = 0;
}

CDlgContainer::~CDlgContainer()
{
}

void CDlgContainer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_MAX, m_btnMax);
	DDX_Control(pDX, IDC_BTN_MIN, m_btnMin);
	DDX_Control(pDX, IDC_BTN_TITLE, m_btnTitle);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btnClose);
}


BEGIN_MESSAGE_MAP(CDlgContainer, CDialog)
	ON_BN_CLICKED(IDC_BTN_MAX, &CDlgContainer::OnBnClickedBtnMax)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_MIN, &CDlgContainer::OnBnClickedBtnMin)
	ON_BN_CLICKED(IDC_BTN_TITLE, &CDlgContainer::OnBnClickedBtnTitle)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CDlgContainer::OnBnClickedBtnClose)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgContainer 消息处理程序

void CDlgContainer::OnBnClickedBtnMax()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nViewMode != CONTAINER_MAX)
	{
		m_nViewMode = CONTAINER_MAX;
		::PostMessage(this->GetParent()->GetSafeHwnd(),WM_CONTAINER,CONTAINER_MAX,0);
		if (m_pActiveWnd)
		{
			m_pActiveWnd->DoCommand(1);
			/*
			if (m_pActiveWnd->IsTitle(SUBDIAGNOSE_TITLE))
			{
				((CDlgGraph *)(m_pActiveWnd->GetWnd()))->SetViewMode(1);
			}*/
		}
	}
}

void CDlgContainer::AddIUserWin(IUserWin * c_iWin)
{
	m_vpIUserWin.push_back(c_iWin);
}

IUserWin * CDlgContainer::GetWndByName(CString c_strName,int &c_nIndex)
{
	std::vector<IUserWin *>::iterator iter;
	int n = 0;
	for(iter = m_vpIUserWin.begin(); iter != m_vpIUserWin.end(); iter++)
	{				
		if ((*iter)->IsTitle(c_strName))
		{
			c_nIndex = n;
			return (*iter);
		}
		n++;
	}
	n = -1;
	std::vector<SButtonWnd *>::iterator iterBtn;
	for(iterBtn = m_vpButtonWnds.begin(); iterBtn != m_vpButtonWnds.end(); iterBtn++)
	{		
		if ((*iterBtn)->m_pWnd->IsTitle(c_strName))
		{
			c_nIndex = n;
			return (*iterBtn)->m_pWnd;
		}
		n--;
	}
	return NULL;
}

IUserWin * CDlgContainer::ActiveWnd(CString c_strName)
{
	int nIndex = -1;
	IUserWin * pWnd = GetWndByName(c_strName,nIndex);
	if (pWnd)
	{
		if (pWnd != m_pActiveWnd)
		{
			if (m_pActiveWnd)
				m_pActiveWnd->GetWnd()->ShowWindow(SW_HIDE);
			m_pActiveWnd = pWnd;
			m_pActiveWnd->GetWnd()->ShowWindow(SW_SHOW);
			if (nIndex >= 0)
			{
				m_btnTitle.SetWindowText(c_strName);
				if (c_strName == SUBNEWS_TITLE)
				{
					m_bNoTitle = true;
					m_btnTitle.ShowWindow(SW_HIDE);
				}
				else
				{
					m_bNoTitle = false;
					m_btnTitle.ShowWindow(SW_SHOW);
					CString str;
					pWnd->GetViewTitle(str);
					m_btnTitle.SetWindowText(str);
				}
				ResetButtonsPos();
				//改变状态				
				m_btnTitle.SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_TITLE_BACK),gpSkinManager->GetBitmap(ID_RB_TITLE_NOSEL_BACK));
				for(int n=0; n<m_vpButtonWnds.size(); n++)
				{
					((CXPButton *)(m_vpButtonWnds.at(n)->m_pButton))->SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_TITLE_NOSEL_BACKC),gpSkinManager->GetBitmap(ID_RB_TITLE_BACKC));
				}
			}
			else//附加
			{
				m_btnTitle.SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_TITLE_NOSEL_BACK),gpSkinManager->GetBitmap(ID_RB_TITLE_BACK));
				nIndex = abs(nIndex);
				nIndex--;
				for(int n=0; n<m_vpButtonWnds.size(); n++)
				{
					if (n == nIndex)
						((CXPButton *)(m_vpButtonWnds.at(n)->m_pButton))->SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_TITLE_BACKC),gpSkinManager->GetBitmap(ID_RB_TITLE_NOSEL_BACKC));
					else
						((CXPButton *)(m_vpButtonWnds.at(n)->m_pButton))->SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_TITLE_NOSEL_BACKC),gpSkinManager->GetBitmap(ID_RB_TITLE_BACKC));
				}
				
			}
		}
		else
		{
			if(nIndex >= 0)
			{
			if (c_strName == SUBNEWS_TITLE)
			{
				m_bNoTitle = true;
				m_btnTitle.ShowWindow(SW_HIDE);
			}
			else
			{
				m_bNoTitle = false;
				CString str;
				pWnd->GetViewTitle(str);					
				m_btnTitle.SetWindowText(str);
				m_btnTitle.ShowWindow(SW_SHOW);
			}
			ResetButtonsPos();
			}
		}
		return pWnd;
	}
	return NULL;
}

IUserWin * CDlgContainer::ActiveWnd(IUserWin * c_pWnd)
{
	if (m_pActiveWnd == c_pWnd)
		return m_pActiveWnd;

	std::vector<IUserWin *>::iterator iter;	
	for(iter = m_vpIUserWin.begin(); iter != m_vpIUserWin.end(); iter++)
	{		
		if ((*iter) == c_pWnd)
		{	
			if (m_pActiveWnd)	
				m_pActiveWnd->GetWnd()->ShowWindow(SW_HIDE);
			m_pActiveWnd = c_pWnd;
			m_pActiveWnd->GetWnd()->ShowWindow(SW_SHOW);
			SetLayout();
			CString strTitle;
			c_pWnd->GetViewTitle(strTitle);
			m_btnTitle.SetWindowText(strTitle);
			m_btnTitle.SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_TITLE_BACK),gpSkinManager->GetBitmap(ID_RB_TITLE_NOSEL_BACK));
			for(int n=0; n<m_vpButtonWnds.size(); n++)
			{
				((CXPButton *)(m_vpButtonWnds.at(n)->m_pButton))->SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_TITLE_NOSEL_BACK),gpSkinManager->GetBitmap(ID_RB_TITLE_BACK));
			}
			return (*iter);
		}		
	}
	std::vector<SButtonWnd *>::iterator iterBtn;
	for(iterBtn = m_vpButtonWnds.begin(); iterBtn != m_vpButtonWnds.end(); iterBtn++)
	{				
		if ((*iterBtn)->m_pWnd == c_pWnd)
		{	
			if (m_pActiveWnd)
				m_pActiveWnd->GetWnd()->ShowWindow(SW_HIDE);
			m_pActiveWnd = (*iterBtn)->m_pWnd;
			CString strTitle;
			m_pActiveWnd->GetViewTitle(strTitle);
			(*iterBtn)->m_pButton->SetWindowText(strTitle);

			m_pActiveWnd->GetWnd()->ShowWindow(SW_SHOW);
			SetLayout();
			m_btnTitle.SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_TITLE_NOSEL_BACK),gpSkinManager->GetBitmap(ID_RB_TITLE_BACK));
			for(int n=0; n<m_vpButtonWnds.size(); n++)
			{				
				((CXPButton *)(m_vpButtonWnds.at(n)->m_pButton))->SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_TITLE_NOSEL_BACKC),gpSkinManager->GetBitmap(ID_RB_TITLE_BACKC));				
			}			
			((CXPButton *)((*iterBtn)->m_pButton))->SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_TITLE_BACKC),gpSkinManager->GetBitmap(ID_RB_TITLE_NOSEL_BACKC));
			return (*iterBtn)->m_pWnd;
		}
	}
	return NULL;	
}

void CDlgContainer::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_btnMax)
	{
		SetLayout();
	}
}

void CDlgContainer::SetLayout()
{
	int nHeight = gpSkinManager->GetFontHeight(gpSkinManager->GetButtonFont());
	m_nBtnHeight = nHeight + 2;
	nHeight += 4;
	if (nHeight < 22)
		nHeight = 22;
	
	int nWidth = gpSkinManager->GetFontWidth(gpSkinManager->GetButtonFont(),_T("智能换股-山河智能"));
	nWidth += 4;
	if(nWidth < 100)
		nWidth = 100;

	m_nHeadHeight = nHeight;
#ifdef CCTV_TV
	//m_nHeadHeight += 16;
#endif
	m_nBtnWidth = nWidth;
	CSize sizeBtnMax = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(ID_MAX_LITTLE));
	CSize sizeBtnMin = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(ID_MIN_LITTLE));
	CSize sizeBtnClose = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(ID_CLOSE_LITTLE));
#ifdef CCTV_TV
	sizeBtnClose.cx += 16;
#endif
	CSize sizeBtnTitle = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(ID_RB_TITLE_BACK));
	CRect rect;
	GetClientRect(rect);
	rect.left += 4;
	rect.bottom = rect.top + m_nHeadHeight;
	rect.top = rect.bottom - m_nBtnHeight;
	rect.right = rect.left + nWidth;
	m_btnTitle.MoveWindow(rect);

	GetClientRect(rect);
	rect.right -= 4;
	rect.left = rect.right - sizeBtnClose.cx;	
#ifdef CCTV_TV
	rect.bottom = rect.top + m_nHeadHeight;	
	//rect.bottom = rect.top + sizeBtnClose.cy;
	rect.left -= sizeBtnClose.cx;
#else
	rect.top += (m_nHeadHeight-sizeBtnClose.cy)/2;
	rect.bottom = rect.top + sizeBtnClose.cy;
#endif
	m_btnClose.MoveWindow(rect);
	
	rect.left -= sizeBtnMax.cx;
	rect.right = rect.left + sizeBtnMax.cx;
	
	m_btnMax.MoveWindow(rect);
	rect.left -= sizeBtnMin.cx;
	rect.right -= sizeBtnMax.cx;
	m_btnMin.MoveWindow(rect);
	if (m_pActiveWnd)
	{
		GetClientRect(rect);
		rect.top += m_nHeadHeight;// + 4;
		m_pActiveWnd->GetWnd()->MoveWindow(rect);
	}	
}

int CDlgContainer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}

BOOL CDlgContainer::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int nHeight = gpSkinManager->GetFontHeight(gpSkinManager->GetButtonFont());
	m_nBtnHeight = nHeight + 2;
	nHeight += 4;
	if (nHeight < 22)
		nHeight = 22;
	
	int nWidth = gpSkinManager->GetFontWidth(gpSkinManager->GetButtonFont(),_T("智能换股-山河智能"));
	nWidth += 4;
	if(nWidth < 100)
		nWidth = 100;

	m_nHeadHeight = nHeight;	
	m_nBtnWidth = nWidth;

	m_btnClose.SetWindowText(_T(""));
	m_btnClose.SetBorder(false);
	m_btnClose.SetBtnBMP(gpSkinManager->GetBitmap(ID_CLOSE_LITTLE),gpSkinManager->GetBitmap(ID_CLOSE_LITTLE_CHG));
	m_btnMax.SetWindowText(_T(""));
	m_btnMax.SetBorder(false);
	m_btnMax.SetBtnBMP(gpSkinManager->GetBitmap(ID_MAX_LITTLE),gpSkinManager->GetBitmap(ID_MAX_LITTLE_CHG));
	m_btnMin.SetWindowText(_T(""));
	m_btnMin.SetBorder(false);
	m_btnMin.SetBtnBMP(gpSkinManager->GetBitmap(ID_MIN_LITTLE),gpSkinManager->GetBitmap(ID_MIN_LITTLE_CHG));

	m_btnTitle.SetWindowText(_T("大盘分析"));
	m_btnTitle.SetBorder(false);
	m_btnTitle.SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_TITLE_BACK),gpSkinManager->GetBitmap(ID_RB_TITLE_NOSEL_BACK));
	m_btnTitle.SetBmpPos(3);

	m_btnTitle.SetFont(gpSkinManager->GetButtonFont());

	SetTimer(100,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CDlgContainer::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(rect);
	pDC->FillRect(rect,&CBrush(gpSkinManager->getColor(BKCOLOR)));
	if (gpSkinManager->GetBitmap(ID_RB_HEAD_BACK))
	{
		rect.bottom = rect.top + m_nHeadHeight;
		gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(ID_RB_HEAD_BACK),pDC,rect);
		GetClientRect(rect);
		rect.top += m_nHeadHeight;
		pDC->FillRect(rect,&CBrush(gpSkinManager->getColor(BKCOLOR)));
	}
	else
	{
	//gpSkinManager->FillRectImage(IDB_ALL_BACK,pDC,rect);
		rect.bottom = rect.top + 25;
		m_nHeadHeight = 25;
		//gpSkinManager->FillRectImage(IDB_BUTTONS_CHANGE_BACK,pDC,rect);
	}
	return true;
	return CDialog::OnEraseBkgnd(pDC);
}

void CDlgContainer::OnBnClickedBtnMin()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nViewMode != CONTAINER_MIN)
	{
		ShowMin();
	}
	else	
	if (m_nViewMode == CONTAINER_MIN)
	{
		m_nViewMode = CONTAINER_HIDE;
		::PostMessage(this->GetParent()->GetSafeHwnd(),WM_CONTAINER,CONTAINER_HIDE,0);		
	}
}

void CDlgContainer::ShowMin()
{
	m_nViewMode = CONTAINER_MIN;
	::PostMessage(this->GetParent()->GetSafeHwnd(),WM_CONTAINER,CONTAINER_MIN,0);
	if (m_pActiveWnd)
	{
		m_pActiveWnd->DoCommand(0);
		/*
		if (m_pActiveWnd->IsKindOf(RUNTIME_CLASS(CDlgGraph)))
		{
			((CDlgGraph *)(m_pActiveWnd))->SetViewMode(0);
			Invalidate();
		}*/
	}
}

//加在头部
CWnd * CDlgContainer::AddButtonWnd(IUserWin * c_pWnd,CString c_strTitle)
{	
	CXPButton * pButton;
	pButton = new CXPButton();
	pButton->Create(c_strTitle,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,CRect(),this,IDC_BTN_TITLE + 1);	
	pButton->SetFont(gpSkinManager->GetButtonFont());
	CString strBtnTitle;
	c_pWnd->GetViewTitle(strBtnTitle);
	pButton->SetWindowText(strBtnTitle);
	pButton->SetBorder(false);
	pButton->SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_TITLE_BACKC),gpSkinManager->GetBitmap(ID_RB_TITLE_NOSEL_BACKC));	
	pButton->SetBmpPos(3,1);	

	CRect r;
	pButton->GetClientRect(r);
	r.left += 20;
	r.right -= 18;
	pButton->SetTitleInRect(true,r);

	SButtonWnd * pItem;
	pItem = new SButtonWnd();
	pItem->m_pWnd = c_pWnd;
	pItem->m_pButton = pButton;	
	c_pWnd->SetTitle(c_strTitle);
	pButton->SetToolTipText(&c_strTitle);
	m_vpButtonWnds.insert(m_vpButtonWnds.begin(),pItem);
	//m_vpButtonWnds.push_back(pItem);


	CXPButton * pClose;
	pClose = new CXPButton();
	pClose->Create(c_strTitle,WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,CRect(),this,IDC_BTN_TITLE + 2);
	pClose->SetBorder(false);
	pClose->SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_ITEM_CLOSE),gpSkinManager->GetBitmap(ID_RB_ITEM_CLOSE_CHANGE));
	
	pClose->BringWindowToTop();
	CString strText(_T("关闭此窗口"));
	pClose->SetToolTipText(&strText);
	pItem->m_pClose = pClose;	
	ResetButtonsPos();
	return pButton;
}

//取新闻窗口
CHtmlView * CDlgContainer::GetNewsWnd()
{
	CMyHtmlView * pWeb;
	int nIndex;
	CString strTitle;
	strTitle = _T("新闻窗口");
	
	pWeb = (CMyHtmlView *)GetWndByName(strTitle,nIndex);
	if (pWeb)
	{
		ActiveWnd(strTitle);
		return pWeb;
	}
	pWeb = new CMyHtmlView();	
	pWeb->Create(NULL, NULL, WS_CHILD |WS_VISIBLE,CRect(), this, 0, NULL);
	
	pWeb->SetWindowText(strTitle);
	AddButtonWnd(pWeb,strTitle);		
	ActiveWnd(pWeb);
	return pWeb;
}

void CDlgContainer::OnBnClickedBtnTitle()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTitle;
	m_btnTitle.GetWindowText(strTitle);
	ActiveWnd(strTitle);
}

BOOL CDlgContainer::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (wParam == IDC_BTN_TITLE + 1)//Active
	{
		if (lParam)
		{
			std::vector<SButtonWnd *>::iterator iter;
			for(iter=m_vpButtonWnds.begin(); iter!=m_vpButtonWnds.end(); iter++)
			{								
				if ((*iter)->m_pButton->m_hWnd == (HWND)lParam)
				{
					CString strTitle;
					(*iter)->m_pWnd->GetTitle(strTitle);
					ActiveWnd(strTitle);
					SetLayout();
				}
			}
		}		
	}
	else
	if (wParam == IDC_BTN_TITLE + 2)//Close
	{
		if (lParam)
		{
			std::vector<SButtonWnd *>::iterator iter;
			for(iter=m_vpButtonWnds.begin(); iter!=m_vpButtonWnds.end(); iter++)
			{								
				if ((*iter)->m_pClose->m_hWnd == (HWND)lParam)
				{
					CString strTitle;
					(*iter)->m_pWnd->GetTitle(strTitle);
					SButtonWnd * pDef = *iter;
					m_vpButtonWnds.erase(iter);
					CloseWnd(pDef);	
					ResetButtonsPos();
					if (m_vpButtonWnds.size() == 0 && m_bNoTitle)
					{
						m_bNoTitle = false;
						::PostMessage(this->GetParent()->GetSafeHwnd(),WM_CONTAINER,CONTAINER_HIDE,0);
					}
					else
					if (m_vpButtonWnds.size() > 0)
					{						
						m_vpButtonWnds.at(0)->m_pWnd->GetTitle(strTitle);				
						ActiveWnd(strTitle);
						SetLayout();
					}
					return true;
				}
			}
		}		
	}

	return CDialog::OnCommand(wParam, lParam);
}

void CDlgContainer::CloseWnd(SButtonWnd * c_p)
{	
	if (c_p)
	{
		if (m_pActiveWnd == c_p->m_pWnd)
			m_pActiveWnd = NULL;
		
		((CXPButton *)c_p->m_pButton)->SetBtnBMP(HBITMAP(0),HBITMAP(0));
		c_p->m_pButton->DestroyWindow();		
		delete c_p->m_pButton;
		((CXPButton *)c_p->m_pClose)->SetBtnBMP(HBITMAP(0),HBITMAP(0));
		c_p->m_pClose->DestroyWindow();
		delete c_p->m_pClose;				
		c_p->m_pWnd->DoCommand(100);
		DeleteUserWin(c_p->m_pWnd);
		//delete c_p->m_pWnd->GetWnd();
		delete c_p;
	}
	CRect rect;
	CString strTitle;
	GetClientRect(rect);
	std::vector<SButtonWnd *>::iterator iter;
	int n=0;
	if (strTitle.IsEmpty())
		m_btnTitle.GetWindowText(strTitle);
	IUserWin * pWnd = ActiveWnd(strTitle);
	if (pWnd)
	{
		SetLayout();
	}		
}

void CDlgContainer::SetStockCode(CString c_strCode)
{
	if (m_strStockCode == c_strCode)
		return;
	m_strStockCode = c_strCode;
	m_nReqSeq++;
}


void CDlgContainer::DoSetStockCodeAction()
{
	char acCode[32];
	acCode[0] = 0;
	unicodeToAscii(m_strStockCode,acCode,24);

	if (m_pActiveWnd)
	{
		m_pActiveWnd->SetStockCode(m_strStockCode);
		if (IsBtnWnd(m_pActiveWnd))
		{
			CString strBtnTitle;
			m_pActiveWnd->GetViewTitle(strBtnTitle);
			m_btnTitle.SetWindowText(strBtnTitle);
		}
	}
	//Invalidate();
}

BOOL CDlgContainer::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
	{		
		return TRUE;
	}
	if (pMsg->message == WM_CHAR)
	{
		if ((pMsg->wParam >='0' && pMsg->wParam <= '9')
			||(pMsg->wParam >='a' && pMsg->wParam <= 'z')
			||(pMsg->wParam >='A' && pMsg->wParam <= 'Z'))
		{
			if (gpTopDlg && gpTopDlg->ActiveByKey(pMsg->wParam))
				return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgContainer::FreshData()
{
	if (m_pActiveWnd)
	{
		m_pActiveWnd->FreshData();
		/*
		if (m_pActiveWnd->IsKindOf(RUNTIME_CLASS(CDlgIndustry)))
		{
		}
		if (m_pActiveWnd->IsKindOf(RUNTIME_CLASS(CDlgChgStk)))
		{
		}
		if (m_pActiveWnd->IsKindOf(RUNTIME_CLASS(CDlgIndustry)))
		{
			((CDlgIndustry *)m_pActiveWnd)->FreshView();
		}
		if (m_pActiveWnd->IsKindOf(RUNTIME_CLASS(CDlgGroupAnaly)))
		{
			((CDlgGroupAnaly *)m_pActiveWnd)->FreshData();
		}
		if (m_pActiveWnd->IsKindOf(RUNTIME_CLASS(CDlgPjSort)))
		{
			((CDlgPjSort *)m_pActiveWnd)->FreshData();
		}
		if (m_pActiveWnd->IsKindOf(RUNTIME_CLASS(CDlgGroupAnaly)))
		{
			((CDlgGroupAnaly *)m_pActiveWnd)->FreshData();
		}
		if (m_pActiveWnd->IsKindOf(RUNTIME_CLASS(CDlgTrade)))
		{
			((CDlgTrade *)m_pActiveWnd)->FreshData();
		}
		if (m_pActiveWnd->IsKindOf(RUNTIME_CLASS(CDlgLedsSelect)))
		{
			((CDlgLedsSelect *)m_pActiveWnd)->FreshData();
		}
		*/
	}
}
void CDlgContainer::OnBnClickedBtnClose()
{
	// TODO: 在此添加控件通知处理程序代码	
	if (true)//(m_nViewMode != CONTAINER_HIDE)
	{
		m_nViewMode = CONTAINER_HIDE;
		::PostMessage(this->GetParent()->GetSafeHwnd(),WM_CONTAINER,CONTAINER_HIDE,0);
		RemoveAttachWnd();
	}
}

void CDlgContainer::ResetButtonsPos()
{	
	CRect rect,rectClient;
	GetClientRect(rect);
	rectClient = rect;
	std::vector<SButtonWnd *>::iterator iter;
	int n=0;
	BOOL bShow = TRUE;
	for(iter=m_vpButtonWnds.begin(); iter!=m_vpButtonWnds.end(); iter++)
	{
		GetClientRect(rect);
		if (m_bNoTitle)
			rect.left += 4 + (n)* (m_nBtnWidth + 2);
		else
			rect.left += 4 + (n + 1)* (m_nBtnWidth + 2);
		rect.right = rect.left + m_nBtnWidth + 2;
		rect.bottom = rect.top + m_nHeadHeight;
		rect.top = rect.bottom-m_nBtnHeight;
		(*iter)->m_pButton->MoveWindow(rect);

		if (rect.right > rectClient.right - 80)
		{
			bShow = FALSE;	
		}
		else
			bShow = TRUE;
		rect.right -= 9;
		rect.left = rect.right - 11;
		rect.top = rect.top + (rect.Height()-10)/2;
		rect.bottom = rect.top + 10;
		(*iter)->m_pClose->MoveWindow(rect);
		n++;
		(*iter)->m_pButton->ShowWindow(bShow);
		(*iter)->m_pClose->ShowWindow(bShow);
	}
}

void CDlgContainer::ResetFont()
{
	m_btnTitle.SetFont(gpSkinManager->GetButtonFont());
	for(int n=0; n<m_vpButtonWnds.size(); n++)
		m_vpButtonWnds.at(n)->m_pButton->SetFont(gpSkinManager->GetButtonFont());
}

void CDlgContainer::ResetSkin()
{
	ResetFont();
	std::vector<IUserWin *>::iterator iter;	
	for(iter = m_vpIUserWin.begin(); iter != m_vpIUserWin.end(); iter++)
	{				
		(*iter)->ResetSkin();
	}

	m_btnClose.SetBtnBMP(gpSkinManager->GetBitmap(ID_CLOSE_LITTLE),gpSkinManager->GetBitmap(ID_CLOSE_LITTLE_CHG));
	m_btnMax.SetBtnBMP(gpSkinManager->GetBitmap(ID_MAX_LITTLE),gpSkinManager->GetBitmap(ID_MAX_LITTLE_CHG));
	m_btnMin.SetBtnBMP(gpSkinManager->GetBitmap(ID_MIN_LITTLE),gpSkinManager->GetBitmap(ID_MIN_LITTLE_CHG));

	m_btnTitle.SetBtnBMP(HBITMAP(0),HBITMAP(0));
	for(int n=0; n<m_vpButtonWnds.size(); n++)
	{
		((CXPButton *)(m_vpButtonWnds.at(n)->m_pButton))->SetBtnBMP(HBITMAP(0),HBITMAP(0));
		((CXPButton *)(m_vpButtonWnds.at(n)->m_pClose))->SetBtnBMP(HBITMAP(0),HBITMAP(0));
	}

	m_btnTitle.SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_TITLE_BACK),gpSkinManager->GetBitmap(ID_RB_TITLE_NOSEL_BACK));
	for(int n=0; n<m_vpButtonWnds.size(); n++)
	{
		((CXPButton *)(m_vpButtonWnds.at(n)->m_pButton))->SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_TITLE_NOSEL_BACK),gpSkinManager->GetBitmap(ID_RB_TITLE_BACK));
		((CXPButton *)(m_vpButtonWnds.at(n)->m_pClose))->SetBtnBMP(gpSkinManager->GetBitmap(ID_RB_ITEM_CLOSE),gpSkinManager->GetBitmap(ID_RB_ITEM_CLOSE_CHANGE));
	}
	for(int n=0; n<m_vpButtonWnds.size(); n++)
	{
		m_vpButtonWnds.at(n)->m_pWnd->ResetSkin();
	}
	SetLayout();
	ResetButtonsPos();
	IUserWin *pA = m_pActiveWnd;
	m_pActiveWnd = NULL;
	ActiveWnd(pA);
	Invalidate();
}

void CDlgContainer::Refresh()
{
	Invalidate();
	if (m_pActiveWnd)
	{		
		m_pActiveWnd->RefreshWin();
	}
}

void CDlgContainer::RemoveAttachWnd()
{	
	SButtonWnd * pBtn;
	while(m_vpButtonWnds.size() > 0)
	{
		pBtn = m_vpButtonWnds.back();
		if (m_pActiveWnd == pBtn->m_pWnd)
			m_pActiveWnd = NULL;

		((CXPButton *)(pBtn)->m_pButton)->SetBtnBMP(HBITMAP(0),HBITMAP(0));
		pBtn->m_pButton->DestroyWindow();
		
		delete pBtn->m_pButton;
		((CXPButton *)(pBtn)->m_pClose)->SetBtnBMP(HBITMAP(0),HBITMAP(0));
		(pBtn)->m_pClose->DestroyWindow();
		delete (pBtn)->m_pClose;
		//c_p->m_pWnd->DestroyWindow();
		//pBtn->m_pWnd->GetWnd()->DestroyWindow();
		pBtn->m_pWnd->DoCommand(100);
		delete (pBtn)->m_pWnd->GetWnd();
		delete (pBtn);

		m_vpButtonWnds.pop_back();
	}
	if (m_bNoTitle == false)
	{
		CString strTitle;
		m_btnTitle.GetWindowText(strTitle);
		ActiveWnd(strTitle);
	}
}

void CDlgContainer::SetViewMode(int c_nMode)
{
	m_nViewMode = c_nMode;
}

bool CDlgContainer::IsBtnWnd(IUserWin * c_pWnd)
{
	std::vector<IUserWin *>::iterator iter;	
	for(iter = m_vpIUserWin.begin(); iter != m_vpIUserWin.end(); iter++)
	{				
		if ((*iter) == c_pWnd)
			return true;
	}
	return false;
}

void CDlgContainer::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bInTimer)
		return;
	m_bInTimer = true;
	if (nIDEvent == 100 && m_nReqSeq != m_nAnsSeq)
	{
		DoSetStockCodeAction();
		m_nAnsSeq = m_nReqSeq;
	}
	m_bInTimer = false;
	CDialog::OnTimer(nIDEvent);
}
