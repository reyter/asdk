// DlgList.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "topDlg.h"
#include "../public/commsocket.h"
#include "DlgList.h"


// CDlgList 对话框

IMPLEMENT_DYNAMIC(CDlgList, CDialog)

CDlgList::CDlgList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgList::IDD, pParent)
{
	m_nListCode = -1;
	m_nCurPage = 0;
	m_nPageItemBegin = 0;
	m_nPageItemCount = 0;
//	m_pListFont = NULL;
	m_nItemHeight = 20;
	m_nHeadHeight = 26;
	m_nCurSel = 0;
	m_nValid = 0;
	m_nSortedCol = 3;
	m_nListCode = 61;
	m_bAsc = true;
	m_nBeginPaintCol = 3;
	m_nBeginPaintColMax = 3;
}

CDlgList::~CDlgList()
{/*
	if (m_pListFont)
	{
		m_pListFont->DeleteObject();
		delete m_pListFont;
	}*/
}

void CDlgList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);	
	DDX_Control(pDX, IDC_LIST_HIDE, m_lstHide);
	DDX_Control(pDX, IDC_SPIN_FIELDS, m_spin);
}


BEGIN_MESSAGE_MAP(CDlgList, CDialog)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_MEASUREITEM()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_HIDE, &CDlgList::OnLvnItemchangedListHide)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_HIDE, &CDlgList::OnNMDblclkListHide)
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FIELDS, &CDlgList::OnDeltaposSpinFields)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CDlgList 消息处理程序

void CDlgList::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_lstHide)
	{
		SetLayout();
		m_lstHide.PositionScrollBars();
	}
}


BOOL CDlgList::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(rect);	
	CDC SourceDC;
	CBitmap bitmap,*pOldBitmap;
	bitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());	
	
	SourceDC.CreateCompatibleDC(NULL);//生成兼容的CDC
	pOldBitmap = SourceDC.SelectObject(&bitmap);

	DrawSelf(&SourceDC);
	
	GetClientRect(rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&SourceDC,0,0,SRCCOPY);	
	SourceDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();	
	SourceDC.DeleteDC();	
	return TRUE;

}

void CDlgList::DrawSelf(CDC * pDC)
{
	CBrush brush;
	CRect rect,rectClient;
	GetClientRect(rect);
	rect.bottom = rect.top + m_nHeadHeight;
	gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(ID_GROUP_HEAD_BACK),pDC,rect);

	GetClientRect(rectClient);
	GetClientRect(rect);
	rect.bottom = rect.top + m_nHeadHeight - 8;
	
	//CFont *pOldFont = pDC->SelectObject(gpSkinManager->m_pFontList);	
	CFont *pOldFont = pDC->SelectObject(gpSkinManager->GetListFont());

	int nOldMode = pDC->SetBkMode(TRANSPARENT);	
	CString strText;
	pDC->SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));
	for(int n=0; n<m_lstHide.GetHeaderCtrl()->GetItemCount(); n++)
	{
		if (n>2 && n<m_nBeginPaintCol)
			continue;

		rect.right = rect.left + m_lstHide.GetColumnWidth(n);
		if (rect.right > rectClient.right)
			break;

		strText = m_lstHide.GetPosName(n);
		if (n == m_nSortedCol)
		{
			pDC->DrawText(strText,rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}
		else
		{
			if (n == 0 || n == 1 || n == 2)
				pDC->DrawText(strText,rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			else
				pDC->DrawText(strText,rect,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
		}
		if (n == m_nSortedCol)
		{
			CRect r;
			r = rect;
			CSize size = pDC->GetTextExtent(strText);
			CPoint pt1;
			pt1.x = rect.left + (rect.Width() - size.cx)/2 + size.cx + 4;
			pt1.y = rect.top + (rect.Height() - size.cy)/2 + size.cy - 4;
			
			CPoint ptA,ptB;
			if (m_bAsc)
			{
				gpSkinManager->drawSJXUP(pDC,pt1,12,6,2,RGB(255,0,255));
			}
			else
			{	
				gpSkinManager->drawSJXDOWN(pDC,pt1,12,6,2,RGB(255,0,255));	
				
			}
		}
		rect.left = rect.right;
	}
	
	pDC->SelectObject(gpSkinManager->GetListFont());
	GetClientRect(rect);
	rect.top += m_nHeadHeight;	
	PaintList(pDC,rect);
	pDC->SetBkMode(nOldMode);
	pDC->SelectObject(pOldFont);
}

BOOL CDlgList::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  在此添加额外的初始化
	m_lstHide.Init();

	m_lstHide.ShowWindow(SW_HIDE);
	m_lstHide.ShowScrollBar(false,false);
	m_lstHide.InsertColumn(0,STR_XH,LVCFMT_CENTER,40);
	m_lstHide.InsertColumn(1,STR_DM,LVCFMT_CENTER,60);
	m_lstHide.InsertColumn(2,STR_JC,LVCFMT_CENTER,75);
	m_lstHide.InsertColumn(3,STR_ZDF,LVCFMT_CENTER,50);
	
	m_lstHide.InsertColumn(4,STR_XJ,LVCFMT_CENTER,55);		
	m_lstHide.InsertColumn(5,STR_LB,LVCFMT_CENTER,50);		

	m_lstHide.InsertColumn(6,STR_QHSL,LVCFMT_CENTER,50);

	m_lstHide.InsertColumn(7,STR_CJL,LVCFMT_CENTER,65);
	m_lstHide.InsertColumn(8,STR_CJJE,LVCFMT_CENTER,65);
	m_lstHide.InsertColumn(9,STR_ZD,LVCFMT_CENTER,55);
	m_lstHide.InsertColumn(10,STR_ZF,LVCFMT_CENTER,55);
	
	
	m_lstHide.InsertColumn(11,STR_ZRSP,LVCFMT_CENTER,55);
	m_lstHide.InsertColumn(12,STR_ZGJG,LVCFMT_CENTER,55);
	m_lstHide.InsertColumn(13,STR_ZDJG,LVCFMT_CENTER,55);	
	
	SetTimer(110,4 * 1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CDlgList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
	{
		if (gpTopDlg && gpTopDlg->IsWindowVisible())
			gpTopDlg->ShowWindow(SW_HIDE);
		if (pMsg->message == WM_KEYUP && pMsg->wParam == VK_RETURN)// && pMsg->hwnd == this->GetSafeHwnd())
		{
			if (m_nCurSel >= 0 && m_nCurSel<m_nValid)
			{
				SStock * pStock = m_pStock[m_nCurSel];
				if (pStock)
					::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,STOCK_FROM_LIST,DWORD_PTR(pStock));
			}
		}
		return TRUE;
	}

	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (gpTopDlg && gpTopDlg->IsWindowVisible())
			gpTopDlg->ShowWindow(SW_HIDE);
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
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_PRIOR || pMsg->wParam == VK_NEXT)
		{
			if (pMsg->wParam == VK_PRIOR)
				GoPage(-1);
			else
				GoPage(1);
			return TRUE;
		}
		if (pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN)
		{
			if (pMsg->wParam == VK_UP)
				m_nCurSel--;
			else
				m_nCurSel++;
			if (m_nCurSel < 0)
			{
				m_nCurSel = 0;
				return TRUE;
			}
			else
			if (m_nCurSel >= m_nPageItemCount)
			{
				m_nCurSel = m_nPageItemCount-1;
				return TRUE;
			}
			Invalidate();
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgList::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::PreSubclassWindow();
}

void CDlgList::SetLayout()
{
	int nFontHeight = gpSkinManager->GetFontHeight(gpSkinManager->GetListFont());
	m_nItemHeight = nFontHeight + 4;
	m_nHeadHeight = nFontHeight + 8;

	CRect  rect;
	GetClientRect(rect);
	CalcBeginPaintCol(rect);
	rect.top += m_nHeadHeight;
	if (m_spin.IsWindowVisible())
		rect.bottom -= 16;
	m_nPageItemCount = (rect.Height())/m_nItemHeight;
	GetClientRect(rect);
	//if (m_spin.IsWindowVisible())
	{
		rect.top = rect.bottom - 16;
		rect.left = rect.right  - 30;
		m_spin.MoveWindow(rect);
	}
	m_lstHide.SetColumnWidth(0,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("12345")));
	m_lstHide.SetColumnWidth(1,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("1234567")));
	m_lstHide.SetColumnWidth(2,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("股票名称7")));
	m_lstHide.SetColumnWidth(3,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("123.45")));
	m_lstHide.SetColumnWidth(4,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("1234.56")));
	m_lstHide.SetColumnWidth(5,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("1234.45")));
	m_lstHide.SetColumnWidth(6,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("1234.45")));
	m_lstHide.SetColumnWidth(7,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("1234567890")));
	m_lstHide.SetColumnWidth(8,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("1234567890")));
	m_lstHide.SetColumnWidth(9,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("1234.45")));
	m_lstHide.SetColumnWidth(10,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("1234.45")));
	m_lstHide.SetColumnWidth(11,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("1234.45")));
	m_lstHide.SetColumnWidth(12,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("1234.56")));
	m_lstHide.SetColumnWidth(13,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("1234.56")));
	ResetPage();
}

void CDlgList::SetItems(int c_nCode,int c_nSortCol,BOOL c_bAsc)
{
	m_nPageItemBegin = 0;
	m_nListCode = c_nCode;
	m_nSortedCol = c_nSortCol;
	m_bAsc = c_bAsc;

	FreshList();
}

void CDlgList::SetPage()
{
	GetReport(true,true);
	FreshList();
	Invalidate();
}

void CDlgList::ResetPage()
{
	GetReport(true,false);
	FreshList();
	Invalidate();
}

void CDlgList::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CDlgList::OnNMDblclkStocks(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	if (m_nCurSel  >= 0 && m_nCurSel<m_nValid)
	{
		SStock * pStock = m_pStock[m_nCurSel];
		if (pStock == NULL)
			return;
		::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,0,DWORD_PTR(pStock));
	}
}

void CDlgList::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (IsWindowVisible() == false)
		return;

	if (nIDEvent == 110)
	{
		if (gpData->m_nWorkState != 0 && gpData->m_nWorkState != 7 && gpData->m_nWorkState != 5)
		{
			FreshList();
			GetReport(false,false);
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlgList::GetReport(bool c_bWaitReturn,bool c_bAttach)
{
	if (m_nCurSel < 0)
		return;

	if (m_nCurSel>= m_nValid)
		return;

	int nLen;
	int *pnCodes = new int[100];
	int nCodeCount = 0;
	char acReq[1024];
	for(int n=0; n<m_nValid && n<m_nPageItemCount; n++)
	{
		SStock * pStock = m_pStock[n];
		if (pStock)
		{
			pnCodes[nCodeCount] = pStock->m_sQuote.nStockId;
			nCodeCount++;
			if (nCodeCount > 50)
				break;
		}
	}
	if (nCodeCount > 0)
	{
		nLen = gpData->MakeReportOnceReq(acReq,pnCodes,nCodeCount);
	
		if (nLen > 8 && gpCommSocket && gpCommSocket->m_socket != INVALID_SOCKET)
		if (gpCommSocket->SendData(acReq,nLen,c_bWaitReturn) <= 0)
		{
			gpCommSocket->Disconnect();
			::PostMessage(gpData->m_hwndMain,WM_CONNECT_SUCCESS,0,0);
		}
	}
}

void CDlgList::FreshHideData()
{
	ProcSort();
	SetPage();
}

void CDlgList::SetSortCol(int c_nCol)
{
	if (m_nSortedCol == c_nCol)
		m_bAsc = !m_bAsc;
	else
		m_nSortedCol = c_nCol;
}

void CDlgList::FreshData()
{	
	Invalidate();
}

void CDlgList::GoPage(int c_n)
{
	int nBegin = m_nPageItemBegin;
	if (c_n == 1)
	{
		if (m_nValid < m_nPageItemCount)
			return;
		nBegin += m_nPageItemCount;
		m_nPageItemBegin = nBegin;
		m_nCurSel = 0;
		SetPage();
	}
	else
	{
		if (nBegin == 0)
			return;
		nBegin -= m_nPageItemCount;
		if (nBegin < 0)
			nBegin = 0;
		m_nPageItemBegin = nBegin;
		m_nCurSel = 0;
		SetPage();
	}
}


void CDlgList::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	rect.SetRect(0,0,0,0);
	int nIndex = -1;
	rect.bottom = rect.top + m_nHeadHeight;
	for(int n=0; n<m_lstHide.GetHeaderCtrl()->GetItemCount(); n++)
	{
		if (n>2 && n<m_nBeginPaintCol)
			continue;
		rect.right = rect.left + m_lstHide.GetColumnWidth(n);
		if (rect.PtInRect(point))
		{
			nIndex = n;
			break;
		}
		rect.left = rect.right;
	}
	if (nIndex > 0 && (nIndex == 0 || nIndex==1 || nIndex==2 || nIndex==3||nIndex==4||nIndex==5||nIndex==6||nIndex==7||nIndex==8||nIndex==9||nIndex==10||nIndex==11||nIndex==12||nIndex==13||nIndex==14||nIndex==15||nIndex==16))
	{
		SetSortCol(nIndex);
		ProcSort();
		m_nPageItemBegin = 0;
		SetPage();
		Invalidate();
		return;
	}
	int nItem = (point.y - m_nHeadHeight) / m_nItemHeight;
	if (nItem < m_nPageItemCount && nItem<m_nValid)
	{
		m_nCurSel = nItem;
		Invalidate();
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgList::PaintList(CDC * c_pDC,CRect c_rect)
{
	CRect rcItem;
	rcItem = c_rect;
	rcItem.bottom = rcItem.top + m_nItemHeight;
	CString strName;
	SStock * pStock;	
	int k = 0;
	for(int n=0; n<m_nPageItemCount && n<m_nValid; n++)
	{		
		pStock = m_pStock[n];
		if (pStock == NULL)
			continue;
		c_pDC->SetTextColor(gpSkinManager->getColor(LISTNORMALCOLOR));   
		if  (n%2   ==0)   			 
			c_pDC->FillRect(rcItem,   &CBrush(gpSkinManager->getColor(LISTBKCOLOR1)));
		else   			
			c_pDC->FillRect(rcItem,   &CBrush(gpSkinManager->getColor(LISTBKCOLOR2)));
		if (n == m_nCurSel)
		{
			CRect r=rcItem;
			r.top = r.bottom - 2;
			c_pDC->FillRect(r,   &CBrush(RGB(0,0,255)));//底线
		}
		CRect rc = rcItem;
		CString strText;

		for(int nSub=0; nSub<m_lstHide.GetHeaderCtrl()->GetItemCount(); nSub ++)
		{
			if (nSub>2 && nSub<m_nBeginPaintCol)
				continue;

			strName = m_lstHide.GetPosName(nSub);
			if (nSub == 0)
				strText.Format(_T("%d"),m_nPageItemBegin + n+1);
			else
				strText = gpData->GetStockValueByName(pStock,strName);
				//strText = m_lstHide.GetItemText(n,nSub);			
			rc.right = rc.left + m_lstHide.GetColumnWidth(nSub);
			if (rc.right > c_rect.right)
				break;

			if (nSub > 0)
			{
				COLORREF cl = gpSkinManager->GetStockValueColor(pStock,strName,strText,gpSkinManager->getColor(LISTNORMALCOLOR));
				c_pDC->SetTextColor(cl);
			}
			if (nSub == 0 || nSub == 1 || nSub == 2)
				c_pDC->DrawText(strText,rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			else
				c_pDC->DrawText(strText,rc,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);

			rc.left = rc.right;
		}
		rcItem.top += m_nItemHeight;
		rcItem.bottom += m_nItemHeight;
		k++;
	}
	while(rcItem.top < c_rect.bottom)
	{
		//c_pDC->FillRect(rcItem,&CBrush(gpSkinManager->getColor(BKCOLOR)));
		
		if  (k % 2 == 0)
			c_pDC->FillRect(rcItem,   &CBrush(gpSkinManager->getColor(LISTBKCOLOR1)));   
		else   
			c_pDC->FillRect(rcItem,   &CBrush(gpSkinManager->getColor(LISTBKCOLOR2)));   
		k++;
		rcItem.top += m_nItemHeight;
		rcItem.bottom += m_nItemHeight;
	}
	
}

void CDlgList::ProcSort()
{
	///-SStock * pA, *pB;
	if (m_nSortedCol == 1)
	for(int n=0; n<m_nValid-1; n++)
	{
		for(int k=n+1; k<m_nValid; k++)
		{
			if (((m_bAsc && strcmp(m_pStock[n]->m_sQuote.szStockCode , m_pStock[k]->m_sQuote.szStockCode) > 0))
				||
				((!m_bAsc && strcmp(m_pStock[n]->m_sQuote.szStockCode , m_pStock[k]->m_sQuote.szStockCode) < 0)))
			{
				SStock * pTmp = m_pStock[k];
				m_pStock[k] = m_pStock[n];
				m_pStock[n] = pTmp;
			}
		}
	}
	if (m_nSortedCol == 2)
	for(int n=0; n<m_nValid-1; n++)
	{
		for(int k=n+1; k<m_nValid; k++)
		{
			if (((m_bAsc && m_pStock[n]->m_strName.Compare(m_pStock[k]->m_strName) > 0))
				||
				((!m_bAsc && m_pStock[n]->m_strName.Compare(m_pStock[k]->m_strName) < 0)))
			{
				SStock * pTmp = m_pStock[k];
				m_pStock[k] = m_pStock[n];
				m_pStock[n] = pTmp;
			}
		}
	}

	if (m_nSortedCol == 3)
	for(int n=0; n<m_nValid-1; n++)
	{
		for(int k=n+1; k<m_nValid; k++)
		{
			if (((m_bAsc && m_pStock[n]->m_sQuote.zdfd > m_pStock[k]->m_sQuote.zdfd))
				||
			((!m_bAsc && m_pStock[n]->m_sQuote.zdfd < m_pStock[k]->m_sQuote.zdfd)))
			{
				SStock * pTmp = m_pStock[k];
				m_pStock[k] = m_pStock[n];
				m_pStock[n] = pTmp;
			}
		}
	}

	if (m_nSortedCol == 4)
	for(int n=0; n<m_nValid-1; n++)
	{
		for(int k=n+1; k<m_nValid; k++)
		{
			if (((m_bAsc && m_pStock[n]->m_sQuote.zjjg > m_pStock[k]->m_sQuote.zjjg))
				||
			((!m_bAsc && m_pStock[n]->m_sQuote.zjjg < m_pStock[k]->m_sQuote.zjjg)))
			{
				SStock * pTmp = m_pStock[k];
				m_pStock[k] = m_pStock[n];
				m_pStock[n] = pTmp;
			}
		}
	}

	if (m_nSortedCol == 9)
	for(int n=0; n<m_nValid-1; n++)
	{
		for(int k=n+1; k<m_nValid; k++)
		{
			if (((m_bAsc && m_pStock[n]->m_sQuote.zd > m_pStock[k]->m_sQuote.zd))
				||
			((!m_bAsc && m_pStock[n]->m_sQuote.zd < m_pStock[k]->m_sQuote.zd)))
			{
				SStock * pTmp = m_pStock[k];
				m_pStock[k] = m_pStock[n];
				m_pStock[n] = pTmp;
			}
		}
	}

	if (m_nSortedCol == 600)
	for(int n=0; n<m_nValid-1; n++)
	{
		for(int k=n+1; k<m_nValid; k++)
		{
			if (((m_bAsc && m_pStock[n]->m_sQuote.BP1 > m_pStock[k]->m_sQuote.BP1))
				||
			((!m_bAsc && m_pStock[n]->m_sQuote.BP1 < m_pStock[k]->m_sQuote.BP1)))
			{
				SStock * pTmp = m_pStock[k];
				m_pStock[k] = m_pStock[n];
				m_pStock[n] = pTmp;
			}
		}
	}

	if (m_nSortedCol == 7)
	for(int n=0; n<m_nValid-1; n++)
	{
		for(int k=n+1; k<m_nValid; k++)
		{
			if (((m_bAsc && m_pStock[n]->m_sQuote.cjsl > m_pStock[k]->m_sQuote.cjsl))
				||
			((!m_bAsc && m_pStock[n]->m_sQuote.cjsl < m_pStock[k]->m_sQuote.cjsl)))
			{
				SStock * pTmp = m_pStock[k];
				m_pStock[k] = m_pStock[n];
				m_pStock[n] = pTmp;
			}
		}
	}
	if (m_nSortedCol == 8)
	for(int n=0; n<m_nValid-1; n++)
	{
		for(int k=n+1; k<m_nValid; k++)
		{
			if (((m_bAsc && m_pStock[n]->m_sQuote.cjje > m_pStock[k]->m_sQuote.cjje))
				||
			((!m_bAsc && m_pStock[n]->m_sQuote.cjje < m_pStock[k]->m_sQuote.cjje)))
			{
				SStock * pTmp = m_pStock[k];
				m_pStock[k] = m_pStock[n];
				m_pStock[n] = pTmp;
			}
		}
	}

	if (m_nSortedCol == 6)//换手
	for(int n=0; n<m_nValid-1; n++)
	{
		for(int k=n+1; k<m_nValid; k++)
		{
			float hsa,hsb;
			if (m_pStock[n]->m_dLtg > 0)
				hsa = m_pStock[n]->m_sQuote.cjsl / m_pStock[n]->m_dLtg;
			else
				hsa = 0;
			if (m_pStock[k]->m_dLtg > 0)
				hsb = m_pStock[k]->m_sQuote.cjsl / m_pStock[k]->m_dLtg;
			else
				hsb = 0;

			if (((m_bAsc && hsa > hsb))
				||
			((!m_bAsc && hsa < hsb)))
			{
				SStock * pTmp = m_pStock[k];
				m_pStock[k] = m_pStock[n];
				m_pStock[n] = pTmp;
			}
		}
	}
	if (m_nSortedCol == 1100)
	for(int n=0; n<m_nValid-1; n++)
	{
		for(int k=n+1; k<m_nValid; k++)
		{
			if (((m_bAsc && m_pStock[n]->m_sQuote.jrkp > m_pStock[k]->m_sQuote.jrkp))
				||
				((!m_bAsc && m_pStock[n]->m_sQuote.jrkp < m_pStock[k]->m_sQuote.jrkp)))
			{
				SStock * pTmp = m_pStock[k];
				m_pStock[k] = m_pStock[n];
				m_pStock[n] = pTmp;
			}
		}
	}

	if (m_nSortedCol == 11)
	for(int n=0; n<m_nValid-1; n++)
	{
		for(int k=n+1; k<m_nValid; k++)
		{
			if (((m_bAsc && m_pStock[n]->m_sQuote.zrsp > m_pStock[k]->m_sQuote.zrsp))
				||
				((!m_bAsc && m_pStock[n]->m_sQuote.zrsp < m_pStock[k]->m_sQuote.zrsp)))
			{
				SStock * pTmp = m_pStock[k];
				m_pStock[k] = m_pStock[n];
				m_pStock[n] = pTmp;
			}
		}
	}
	if (m_nSortedCol == 12)
	for(int n=0; n<m_nValid-1; n++)
	{
		for(int k=n+1; k<m_nValid; k++)
		{
			if (((m_bAsc && m_pStock[n]->m_sQuote.zgjg > m_pStock[k]->m_sQuote.zgjg))
				||
				((!m_bAsc && m_pStock[n]->m_sQuote.zgjg < m_pStock[k]->m_sQuote.zgjg)))
			{
				SStock * pTmp = m_pStock[k];
				m_pStock[k] = m_pStock[n];
				m_pStock[n] = pTmp;
			}
		}
	}

	if (m_nSortedCol == 13)
	for(int n=0; n<m_nValid-1; n++)
	{
		for(int k=n+1; k<m_nValid; k++)
		{
			if (((m_bAsc && m_pStock[n]->m_sQuote.zdjg > m_pStock[k]->m_sQuote.zdjg))
				||
				((!m_bAsc && m_pStock[n]->m_sQuote.zdjg < m_pStock[k]->m_sQuote.zdjg)))
			{
				SStock * pTmp = m_pStock[k];
				m_pStock[k] = m_pStock[n];
				m_pStock[n] = pTmp;
			}
		}
	}
	if (m_nSortedCol == 5)
	for(int n=0; n<m_nValid-1; n++)
	{
		for(int k=n+1; k<m_nValid; k++)
		{
			if (((m_bAsc && m_pStock[n]->m_sQuote.lb > m_pStock[k]->m_sQuote.lb))
				||
				((!m_bAsc && m_pStock[n]->m_sQuote.lb < m_pStock[k]->m_sQuote.lb)))
			{
				SStock * pTmp = m_pStock[k];
				m_pStock[k] = m_pStock[n];
				m_pStock[n] = pTmp;
			}
		}
	}
}
void CDlgList::OnLvnItemchangedListHide(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CDlgList::OnNMDblclkListHide(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CDlgList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.y < m_nHeadHeight)
		return;

	if (m_nCurSel  >= 0 && m_nCurSel<m_nValid)
	{
		SStock * pStock = m_pStock[m_nCurSel];
		if (pStock == NULL)
			return;		
		::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,STOCK_FROM_LIST,DWORD_PTR(pStock));
	}

	CDialog::OnLButtonDblClk(nFlags, point);
}

void CDlgList::OnDeltaposSpinFields(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nBeginPaintCol -= pNMUpDown->iDelta;
	if (m_nBeginPaintCol < 3)
	{
		m_nBeginPaintCol = 3;
	}
	else
	if (m_nBeginPaintCol > m_nBeginPaintColMax)
		m_nBeginPaintCol = m_nBeginPaintColMax;
	else
		Invalidate();
	*pResult = 0;
}

void CDlgList::CalcBeginPaintCol(CRect c_rect)
{
	int nX = 0;
	int nX3 = 0;
	bool bViewSpin = false;
	for(int n=0; n<m_lstHide.GetHeaderCtrl()->GetItemCount(); n++)
	{
		nX += m_lstHide.GetColumnWidth(n);
		if (nX > c_rect.Width())
		{
			bViewSpin = true;
			break;
		}
	}
	m_nBeginPaintColMax = 3;
	if (bViewSpin)
	{
		nX3 = m_lstHide.GetColumnWidth(0) + m_lstHide.GetColumnWidth(1) + m_lstHide.GetColumnWidth(2);
		for(int n=m_lstHide.GetHeaderCtrl()->GetItemCount()-1; n>=3; n--)
		{
			nX3 += m_lstHide.GetColumnWidth(n);
			if (nX3 > c_rect.Width())
			{
				m_nBeginPaintColMax = n+1;
				break;
			}
		}
	}
	if (bViewSpin)
	{
		m_nBeginPaintCol = 3;
		m_spin.ShowWindow(SW_SHOW);
	}
	else
	{
		m_nBeginPaintCol = 3;
		m_spin.ShowWindow(SW_HIDE);
	}
}
void CDlgList::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetFocus();
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgList::FreshList()
{
	for(int n=0; n<gpData->m_vpStocks.size();n++)
	m_pStock[n] = gpData->m_vpStocks.at(n);
	m_nValid = gpData->m_vpStocks.size();
	/*
	unsigned short usIndex = 2;
	char acKinds[32] = {0};
	if (m_nListCode == 60)	strcpy(acKinds,"md_szag|md_shag");		
	if (m_nListCode == 61)	strcpy(acKinds,"md_shag");
	if (m_nListCode == 62)	strcpy(acKinds,"md_shbg");
	if (m_nListCode == 63)	strcpy(acKinds,"md_szag|md_cyb");
	if (m_nListCode == 64)	strcpy(acKinds,"md_szbg");
						
	//code|name|zdf|zjjg|lb4|zrsp5|jrkp6|zjcj7|cjsl8|cjje9|zf10|zgjg11|zdjg|BP1|SP1|zd|hsl|syl
	if (m_nSortedCol == 1)	usIndex = 0;
	if (m_nSortedCol == 2)	usIndex = 1;
	if (m_nSortedCol == 3)	usIndex = 2;
	if (m_nSortedCol == 4)	usIndex = 3;

	if (m_nSortedCol == 9)	usIndex = 15;//涨跌
	if (m_nSortedCol == 7)	usIndex = 8;
	if (m_nSortedCol == 8)	usIndex = 9;
	if (m_nSortedCol == 6)	usIndex = 16;//换手
	if (m_nSortedCol == 1100) usIndex = 6;
	if (m_nSortedCol == 10)	usIndex = 10;
	if (m_nSortedCol == 11)	usIndex = 5;
	if (m_nSortedCol == 12)	usIndex = 11;
	if (m_nSortedCol == 13)	usIndex = 12;
	if (m_nSortedCol == 5)	usIndex = 4;
	if (m_nSortedCol == 14)	usIndex = 17;//PE
	if (m_nSortedCol == 15)	usIndex = 18;//YLYC
	if (m_nSortedCol == 16)	usIndex = 19;//PJ

	if (strlen(acKinds) == 0)
		return;
	char * pData = (char *)malloc(10240);
	int nRet = gpData->MakeQuoteSortReq(pData,acKinds,"code|name|zdf|zjjg|lb|zrsp|jrkp|zjcj|cjsl|cjje|zf|zgjg|zdjg|BP1|SP1|zd|hsl|PE|YLYC|PJ",usIndex,m_bAsc,m_nPageItemBegin,m_nPageItemCount);
	if (nRet > 0)
	{
		nRet = gpCommSocket->SendData(pData,nRet,true,pData,8096);
		if (nRet > 0)
		{
			ParseData(pData,nRet);
		}
	}
	free(pData);*/
}

int CDlgList::ParseData(char * c_pData,int c_nLen)
{
	unsigned short usKindLen = 0;
	unsigned short usColLen = 0;//
	unsigned short usIndex = 0;//排序列
	unsigned short usSortType = 0;//排序方式
	unsigned short usBeginNo = 0;//开始行
	unsigned short usCount = 0;//指定行数	
	unsigned short usLineCount = 0;//返回行数
	int	nDataLen = 0;
	char * p = (c_pData + 14);//跳过头
	int nOffset = 14;//开始位置

	usKindLen = *(unsigned short *)p;		p += sizeof(unsigned short);		nOffset += sizeof(unsigned short);
											p += usKindLen;						nOffset += usKindLen;
	usColLen = *(unsigned short *)p;		p += sizeof(unsigned short);		nOffset += sizeof(unsigned short);
											p += usColLen;						nOffset += usColLen;
	usIndex = *(unsigned short *)p;			p += sizeof(unsigned short);		nOffset += sizeof(unsigned short);
	usSortType = *(unsigned short *)p;		p += sizeof(unsigned short);		nOffset += sizeof(unsigned short);
	usBeginNo = *(unsigned short *)p;		p += sizeof(unsigned short);		nOffset += sizeof(unsigned short);
	usCount = *(unsigned short *)p;			p += sizeof(unsigned short);		nOffset += sizeof(unsigned short);
	usLineCount = *(unsigned short *)p;		p += sizeof(unsigned short);		nOffset += sizeof(unsigned short);

	nDataLen = *(int *)p;					p += sizeof(int);					nOffset += sizeof(int);

	char acCode[32];
	char acName[32];
	//zdf|zjjg|lb|zrsp|jrkp|zjcj|cjsl|cjje|zf|zgjg|zdjg|BP1|SP1|zd|hsl|PE|PE|YLYC;
	int nValue[18];
	int nValidLine = 0;
	while(nOffset < c_nLen)
	{
		strncpy(acCode,p,16);		p += 16;				nOffset += 16;
		strncpy(acName,p,16);		p += 16;				nOffset += 16;
		nValue[0] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[1] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[2] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[3] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[4] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[5] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[6] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[7] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[8] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[9] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[10] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[11] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[12] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[13] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[14] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[15] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[16] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);
		nValue[17] = *(int *)p;		p += sizeof(int);		nOffset += sizeof(int);

		SStock * pStock = gpData->GetStock(acCode);
		if (pStock)
		{
			pStock->m_sQuote.zdfd	= nValue[0];
			pStock->m_sQuote.zjjg	= nValue[1];
			pStock->m_sQuote.lb		= nValue[2];
			pStock->m_sQuote.zrsp	= nValue[3];
			pStock->m_sQuote.jrkp	= nValue[4];
			pStock->m_sQuote.zjcj	= nValue[5];
			pStock->m_sQuote.cjsl	= nValue[6];
			pStock->m_sQuote.cjje	= nValue[7];
			pStock->m_sQuote.zf		= nValue[8];
			pStock->m_sQuote.zgjg	= nValue[9];
			pStock->m_sQuote.zdjg	= nValue[10];
			pStock->m_sQuote.BP1	= nValue[11];
			pStock->m_sQuote.SP1	= nValue[12];
			pStock->m_sQuote.zd		= nValue[13];
			pStock->m_sQuote.hsl	= nValue[14];

			if (pStock->m_sQuote.zdjg == 99999999)
				pStock->m_sQuote.zdjg = 0;

			m_pStock[nValidLine] = pStock;
			nValidLine++;
		}
	}
	m_nPageItemBegin = usBeginNo;
	m_nValid = nValidLine;
	return nValidLine;
}