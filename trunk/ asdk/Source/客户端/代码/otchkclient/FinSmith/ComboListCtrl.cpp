// ComboListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ComboListCtrl.h"
#include "DlgTrade.h"
#include "resource.h"

// CComboListCtrl

IMPLEMENT_DYNAMIC(CComboListCtrl, CSkinListCtrl)
static int CALLBACK CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData )
{
    CComboListCtrl* pV=(CComboListCtrl*)lParamData; 
    CString strItem1, strItem2; 
    LVFINDINFO info; 
    int nIndex; 
    info.flags = LVFI_PARAM;                       //设置为LVFI_PARAM，后面的FindItem才能有效，详情参考MSDN的LVFINDINFO 
    info.lParam = lParam1;                         //由item data(lParam1)得到对应的item text 
    if ( (nIndex=pV->FindItem(&info)) != -1) 
        strItem1 = pV->GetItemText(nIndex, pV->m_nSortedCol); 
    info.lParam = lParam2;                         //由item data(lParam2)得到对应的item text 
    if ( (nIndex=pV->FindItem(&info)) != -1)
        strItem2 = pV->GetItemText(nIndex, pV->m_nSortedCol); 
    int iCompRes ;
    //iCompRes = strcmp(strItem1, strItem2);     //根据当前的排序方式进行调整 

    LVCOLUMN lvcol;
    WCHAR  str[128];

    CString  strColumnName;

	USES_CONVERSION;

    lvcol.mask = LVCF_TEXT;
    lvcol.pszText = str;
    lvcol.cchTextMax = 128;

    pV->GetColumn(pV->m_nSortedCol, &lvcol);
    strColumnName = lvcol.pszText;

	if (!strColumnName.Compare(_T("序号")))
		return 0;

    if (strColumnName.Compare(_T("证券名称")))
    {
		float   f1   =   atof((char *)W2A(strItem1.GetBuffer()));
		strItem1.ReleaseBuffer();
		float   f2   =   atof((char *)W2A(strItem2.GetBuffer()));
		strItem2.ReleaseBuffer();
        if (f1 > f2)
        {
            iCompRes = 1;
        }
        else if (f1 < f2)
        {
            iCompRes = -1;
        }
        else
        {
            iCompRes = 0;
        }
    }

    else

    {
		iCompRes = strcmp((char *)W2A(strItem1.GetBuffer()), (char *)W2A(strItem2.GetBuffer()));     //根据当前的排序方式进行调整
		strItem1.ReleaseBuffer();
		strItem2.ReleaseBuffer();
    }
    if(pV->m_fAsc) 
        return iCompRes;
    else 
        return iCompRes * -1;
}

CComboListCtrl::CComboListCtrl()
{
	m_fAsc=TRUE;
	m_nSortedCol = 0;
	m_nDiagnoseCol = -1;
}

CComboListCtrl::~CComboListCtrl()
{
}


BEGIN_MESSAGE_MAP(CComboListCtrl, CSkinListCtrl)
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
	
	ON_WM_NCCALCSIZE()
END_MESSAGE_MAP()

void CComboListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	//得到dc   
	LPDRAWITEMSTRUCT   lpDIS   =   lpDrawItemStruct;   
	CDC*   pDC   =   CDC::FromHandle(lpDIS->hDC);   
	double		f = 0;
	double		dValue = 0;
	LVITEM   lvi   =   {0};   
	lvi.mask   =   LVIF_STATE;//|LVIF_IMAGE;   
	lvi.stateMask   =   LVIS_FOCUSED   |   LVIS_SELECTED   ;   
	lvi.iItem   =   lpDIS->itemID;   
	BOOL   bGet   =   GetItem(&lvi);   
	BOOL   bHighlight   =((lvi.state   &   LVIS_DROPHILITED)||((lvi.state   &   LVIS_SELECTED)   &&     
	((GetFocus()   ==   this)||   (GetStyle()   &   LVS_SHOWSELALWAYS))));   
    
	//   画文本背景
///-	HGDIOBJ hobj;// = pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	CFont *pOldFont = pDC->SelectObject(gpSkinManager->m_pFontSmall);
	CRect   rcBack   =   lpDIS->rcItem;   
	pDC->SetBkMode(TRANSPARENT);   
	if(   bHighlight   )   
	{   
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));   
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));       
		//pDC->FillRect(rcBack,   &CBrush(0xC4DFFD));
		pDC->FillRect(rcBack,   &CBrush(gpSkinManager->getColor(LISTSELBACK)));
	}   
	else   
	{   
		if   (lpDIS->itemID%2   ==0)   
		{   
				pDC->SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));
				if (gpSkinManager->GetBitmap(ID_GROUP_LIST_BACK))
					gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(ID_GROUP_LIST_BACK),pDC,rcBack);
				else
					pDC->FillRect(rcBack,   &CBrush(DEFAULT_LINE_1_COLOR));
		}   
		else   
		{   
				pDC->SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));
				if (gpSkinManager->GetBitmap(ID_GROUP_LIST_BACK))
					gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(ID_GROUP_LIST_BACK),pDC,rcBack);
				else
					pDC->FillRect(rcBack,   &CBrush(DEFAULT_LINE_2_COLOR));   
		}   
	}   

	//设置字体颜色   
	CString   str;   
    
	//得到焦点大小   
	CRect   rcFocus   =   lpDIS->rcItem;   
	rcFocus.DeflateRect(1,1,1,1);   
	   
	if   (lpDIS->itemAction   &   ODA_DRAWENTIRE)   
	{   
		//写文本   
		CString   szText;   
		STradeCombo *pItem = (STradeCombo *)GetItemData(lpDIS->itemID);	
		for   (int   i   =   0;   i   <   GetHeaderCtrl()->GetItemCount();   i++) 
		{   //循环得到文本   
			CRect   rcItem;   
			if   (   !GetSubItemRect(lpDIS->itemID,   i,   LVIR_LABEL,   rcItem   ))   
				continue;   
			szText   =   GetItemText(   lpDIS->itemID,   i   );  
			if (i > 0)//
			{
				rcItem.right -= 2;
			}
			pDC->SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));   
			if (pItem)
			{
				if (i == 0)
				{
					szText = pItem->pStock->m_sQuote.szStockCode;
					szText = szText.Left(6);
				}
				else
				if (i == 1)
					szText = pItem->pStock->m_strName;
				else
				if (i == 2)
					szText.Format(_T("%.2f"),pItem->fSl);
				else
				if (i == 3)
					szText.Format(_T("%.2f"),pItem->fSlValid);
				else
				if (i == 4)
					szText.Format(_T("%.3f"),pItem->fPriceBase);
				else
				if (i == 5)//浮动盈亏
				{
					szText.Format(_T("%.2f"),pItem->fCost - pItem->fCostBase);
					float f = pItem->fCost - pItem->fCostBase;
					if (f < 0)
						pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
					else
						if (f > 0)
						pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
				}
				else
				if (i == 6)//盈亏比例
				{
					if (pItem->fCostBase > 0)
					{
						szText.Format(_T("%.2f%%"),(pItem->fCost-pItem->fCostBase)/pItem->fCostBase * 100);
						float f = pItem->fCost - pItem->fCostBase;
						if (f < 0)
							pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
						else
						if (f > 0)
							pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
					}
					else
						szText = _T("-");
				}
				else
				if (i == 7)//最新市值
				{
					szText.Format(_T("%.2f"),pItem->fCost);
				}
				else
				if (i == 8)//成本金额
				{
					szText.Format(_T("%.2f"),pItem->fCostBase);
				}
				else
				if (i == 9)
				{
					szText.Format(_T("%.2f"),float(pItem->pStock->m_sQuote.zjjg) / 1000);
					if (pItem->pStock->m_sQuote.zdfd < 0)
						pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
					else
						if (pItem->pStock->m_sQuote.zdfd > 0)
						pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
				}
				else
				if (i == 10)
				{
					szText.Format(_T("%.2f%%"),float(pItem->pStock->m_sQuote.zdfd)/100);
					if (pItem->pStock->m_sQuote.zdfd < 0)
						pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
					else
						if (pItem->pStock->m_sQuote.zdfd > 0)
						pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
				}
			}
			if (i != 11)
			{
				rcItem.bottom -= 2;
				if(szText == "-")
				{
					pDC->DrawText(szText,   lstrlen(szText),   &rcItem,   DT_CENTER|DT_BOTTOM|DT_NOPREFIX|DT_SINGLELINE); 
				}
				else
				{
					if(i== 0 || i == 1)
						pDC->DrawText(szText,   lstrlen(szText),   &rcItem,   DT_BOTTOM|DT_CENTER|DT_NOPREFIX|DT_SINGLELINE); 
					else
						pDC->DrawText(szText,   lstrlen(szText),   &rcItem,   DT_RIGHT|DT_BOTTOM|DT_NOPREFIX|DT_SINGLELINE); 
				}
			}
		}   
	}   
	//pDC->SelectObject(hobj);
	pDC->SelectObject(pOldFont);
}

BOOL CComboListCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(rect);
	gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(ID_GROUP_LIST_BACK),pDC,rect);

	m_SkinVerticleScrollbar.UpdateThumbPosition();
	m_SkinHorizontalScrollbar.UpdateThumbPosition();

	return TRUE;
	return CListCtrl::OnEraseBkgnd(pDC);
	//return CListCtrl::OnEraseBkgnd(pDC);
}

void CComboListCtrl::OnColumnClick( NMHDR* pNMHDR, LRESULT* pResult )
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    if( pNMListView->iSubItem == m_nSortedCol )
        m_fAsc = !m_fAsc;
    else
    {
        m_fAsc = TRUE;
        m_nSortedCol = pNMListView->iSubItem;
    }
    VERIFY(SortItems( CompareFunction, reinterpret_cast<DWORD>( this )));

    *pResult = 0;
}

void CComboListCtrl::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	CSkinListCtrl::PreSubclassWindow();
	EnableToolTips(TRUE);
}
////////////////////////////////////////////
// Tool Tip Text Functions                //
// Modified algorithm from codeguru.com   //
// by Kory Becker, kory@dummysoftware.com //
////////////////////////////////////////////
int CComboListCtrl::OnToolHitTest(CPoint point, TOOLINFO * pTI) const
{
	int row, col;
	RECT cellrect;
	row = CellRectFromPoint(point, &cellrect, &col );

	if ( row == -1 ) 
	{
		return -1;
	}

	if (col == m_nDiagnoseCol)
	{
		int nLeft = cellrect.left + (cellrect.right - cellrect.left - 60) / 2;
		if (point.x > nLeft && point.x < nLeft+20)
			col = 1;
		else
		if (point.x > nLeft+20 && point.x < nLeft+40)
			col = 2;
		else
		if (point.x > nLeft+40 && point.x < nLeft+60)
			col = 3;
		else
			return -1;
		row += 300;
	}

	pTI->hwnd = m_hWnd;
	pTI->uId = (UINT)((row<<10)+(col&0x3ff)+1);
	pTI->lpszText = LPSTR_TEXTCALLBACK;

	pTI->rect = cellrect;

	return pTI->uId;
}

// CellRectFromPoint	- Determine the row, col and bounding rect of a cell
// Returns		- row index on success, -1 otherwise
// point		- point to be tested.
// cellrect		- to hold the bounding rect
// col			- to hold the column index
int CComboListCtrl::CellRectFromPoint(CPoint & point, RECT * cellrect, int * col) const
{
	int colnum;
	CHeaderCtrl* pHeader;
	int nColumnCount;

	// If not REPORT style for the list, then use 1 column
	// Otherwise, find the column in the report style view.
	if( (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT )
	{
		// Window is not Report style, so no headers. Deal with it!
		nColumnCount = 1;
	}
	else
	{
		// Get the number of columns in Report style.
		pHeader = (CHeaderCtrl*)GetDlgItem(0);
		nColumnCount = pHeader->GetItemCount();
	}
	
	// Get the top and bottom row visible
	int row = GetTopIndex();
	int bottom = row + GetCountPerPage();
	if( bottom > GetItemCount() )
		bottom = GetItemCount();
	
	// Loop through the visible rows
	for( ;row <=bottom;row++)
	{
		// Get bounding rect of item and check whether point falls in it.
		CRect rect, rectLabel;
		if( (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT )
		{
			// If not Report style, get label / icon boundaries.
			GetItemRect( row, &rect, LVIR_ICON );
			GetItemRect( row, &rectLabel, LVIR_LABEL );
		}
		else
		{
			// If Report style, get bounds of cell.
			GetItemRect( row, &rect, LVIR_BOUNDS );
		}

		if( rect.PtInRect(point) ||
			rectLabel.PtInRect(point))
		{
			bool InLabel = false;

			// Store which part user clicked on if in ICON view,
			// clicked the Label or the Icon?
			if (rect.PtInRect(point))
			{
				InLabel = false;
			}
			else if (rectLabel.PtInRect(point))
			{
				InLabel = true;
			}

			// Now find the column
			for( colnum = 0; colnum < nColumnCount; colnum++ )
			{
				// Getting column width
				int colwidth;
				if( (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT )
				{
					colwidth = 100000; // don't count colwidth.
				}
				else
				{
					// If REPORT, check inside column width.
					colwidth = GetColumnWidth(colnum);
				}

				if( (point.x >= rect.left 
					&& point.x <= (rect.left + colwidth )) ||
					(point.x >= rectLabel.left
					&& point.x <= (rectLabel.left + colwidth )))
				{
					RECT rectClient;
					GetClientRect( &rectClient );
					if( col ) *col = colnum;
					rect.right = rect.left + colwidth;
					rectLabel.right = rectLabel.left + colwidth;

					// Make sure that the right extent does not exceed
					// the client area
					if ( rect.right > rectClient.right ) 
						rect.right = rectClient.right;
					if ( rectLabel.right > rectClient.right )
						rectLabel.right = rectClient.right;

					if (!InLabel)
					{
						*cellrect = rect;
					}
					else
					{
						*cellrect = rectLabel;
					}

					return row;
				}
				rect.left += colwidth;
				rectLabel.left += colwidth;
			}
		}
	}
	return -1;
}

//////////////////////////////////////////////////
// OnToolTipText()                              //
// Modify this function to change the text      //
// displayed in the Tool Tip.                   //
// Currently, it uses GetItemText() to just     //
// show the item's name. But you should change  //
// it to show other info like file size, etc.   //
//////////////////////////////////////////////////
BOOL CComboListCtrl::OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult )
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

	if (row >= 300)
	{
	}
	else
		strTipText = GetItemText( row, col );

#ifndef _UNICODE
	if (pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, strTipText, 80);
	else
		_mbstowcsz(pTTTW->szText, strTipText, 80);
#else
	if (pNMHDR->code == TTN_NEEDTEXTA)
		_wcstombsz(pTTTA->szText, strTipText, 80);
	else
		lstrcpyn(pTTTW->szText, strTipText, 80);
#endif
	*pResult = 0;

	return TRUE;    // message was handled
}


void CComboListCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CSkinListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
}
