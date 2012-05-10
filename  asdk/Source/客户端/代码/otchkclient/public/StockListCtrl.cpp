///-#include "StockListCtrl.h"
///-#include "StockListCtrl.h"
// StockListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "StockListCtrl.h"

struct ItemData
{
public:
    ItemData() : arrpsz( NULL ), dwData( NULL ) {}

    LPTSTR* arrpsz;
    DWORD dwData;

private:
    // ban copying.
    ItemData( const ItemData& );
    ItemData& operator=( const ItemData& );
};
// CStockListCtrl 

IMPLEMENT_DYNAMIC(CStockListCtrl, CSkinListCtrl)

CStockListCtrl::CStockListCtrl()
{
    //m_iNumColumns = 0;
    //m_iSortColumn = 1;
    //m_bSortAscending = TRUE;
	m_bAutoSort = true;
    m_bAsc=FALSE;
	m_pFont = NULL;
	m_bUnderLine = false;
	m_nDiagnoseCol = -1;
}

CStockListCtrl::~CStockListCtrl()
{
}


BEGIN_MESSAGE_MAP(CStockListCtrl, CSkinListCtrl)
	ON_WM_MEASUREITEM()
	ON_WM_ERASEBKGND()
    ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
    //ON_MESSAGE(WM_COLUMNSORT, ColumnSort)
    //ON_WM_RBUTTONDOWN()
	 ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
	ON_WM_NCCALCSIZE()
END_MESSAGE_MAP()


//bool IsNumber( LPCTSTR pszText )
//{
//    ASSERT_VALID_STRING( pszText );
//
//    for( int i = 0; i < lstrlen( pszText ); i++ )
//        if( !_istdigit( pszText[ i ] ) )
//            return false;
//
//    return true;
//}
//
//
//int NumberCompare( LPCTSTR pszNumber1, LPCTSTR pszNumber2 )
//{
//    ASSERT_VALID_STRING( pszNumber1 );
//    ASSERT_VALID_STRING( pszNumber2 );
//
//    const int iNumber1 = atoi( pszNumber1 );
//    const int iNumber2 = atoi( pszNumber2 );
//
//    if( iNumber1 < iNumber2 )
//        return -1;
//
//    if( iNumber1 > iNumber2 )
//        return 1;
//
//    return 0;
//}
//
//
static int CALLBACK CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData )
{

    CStockListCtrl* pV=(CStockListCtrl*)lParamData; 
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

    if (strColumnName.Compare(STR_JC) != 0 && strColumnName.Compare(STR_PJ_STR) != 0 && strColumnName.Compare(STR_INDUSTRYNAME) != 0)
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
    if(pV->m_bAsc) 
        return iCompRes;
    else 
        return iCompRes * -1;
}

void CStockListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项
	//得到dc   
	LPDRAWITEMSTRUCT   lpDIS   =   lpDrawItemStruct;   
	CDC*   pDC   =   CDC::FromHandle(lpDIS->hDC);   
	double		f = 0;
	double		dValue = 0;
///-	int		isNagetive;/*1表示上升，0表示没有改变，-1表示下降*/
	LVITEM   lvi   =   {0};   
	lvi.mask   =   LVIF_STATE;//|LVIF_IMAGE;   
	lvi.stateMask   =   LVIS_FOCUSED   |   LVIS_SELECTED   ;   
	lvi.iItem   =   lpDIS->itemID;   
	BOOL   bGet   =   GetItem(&lvi);   
///-    BOOL	bShowNews;
	BOOL   bHighlight   =((lvi.state   &   LVIS_DROPHILITED)||((lvi.state   &   LVIS_SELECTED)   &&     
	((GetFocus()   ==   this)||   (GetStyle()   &   LVS_SHOWSELALWAYS))));   
    
	//   画文本背景
///-	HGDIOBJ hobj;// = pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));	
	CFont * pOldFont = pDC->SelectObject(gpSkinManager->GetListFont());//pDC->SelectObject(gpSkinManager->m_pFontReport);
	CRect   rcBack   =   lpDIS->rcItem;   
	pDC->SetBkMode(TRANSPARENT);   
	if(   bHighlight  || (lvi.state   &   LVIS_SELECTED) )   
	{   
		if (m_bUnderLine == false)
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
					gpSkinManager->FillRectImage(gpSkinManager->GetBitmap(ID_GROUP_LIST_BACK),pDC,rcBack);

				else
					pDC->FillRect(rcBack,   &CBrush(DEFAULT_LINE_1_COLOR));
			}   
			else   
			{   
				pDC->SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));
				if (gpSkinManager->GetBitmap(ID_GROUP_LIST_BACK))
					gpSkinManager->FillRectImage(gpSkinManager->GetBitmap(ID_GROUP_LIST_BACK),pDC,rcBack);
				else
					pDC->FillRect(rcBack,   &CBrush(DEFAULT_LINE_2_COLOR));   
			}   
			CRect r;
			r = rcBack;
			r.top = r.bottom-2;			
			pDC->FillRect(r,   &CBrush(RGB(0,0,255)));
		}
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

	if (m_pFont)
	{
		pOldFont = pDC->SelectObject(m_pFont);
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
		SStock *pRecord = (SStock *)GetItemData(lpDIS->itemID);	
		if(pRecord == NULL)
			return;

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
			CString strFieldName = GetPosName(i);
			if (strFieldName == STR_XH)
				szText.Format(_T("%d"),lpDIS->itemID + 1);
			pDC->SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));   
			if (pRecord)
			{
				if (strFieldName == STR_JC || strFieldName == STR_DM)
					pDC->SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));
				else
				{
					COLORREF clRet = gpSkinManager->GetStockValueColor(pRecord,strFieldName,szText,gpSkinManager->getColor(BTNTEXTCOLOR));
					pDC->SetTextColor(clRet);
				}
			}/*
			if (i == 0)
			{
				DrawFrameControl(lpDrawItemStruct->hDC,&rcItem,DFC_BUTTON,DFCS_CHECKED);
			}
			else*/
			if (strFieldName != STR_DIAGNOSE && strFieldName != STR_WEAKSTRING_YEAR)
			{
				rcItem.bottom -= 2;
				if(szText == "-")
				{
					pDC->DrawText(szText,   lstrlen(szText),   &rcItem,   DT_CENTER|DT_BOTTOM|DT_NOPREFIX|DT_SINGLELINE); 
				}
				else
				{	
					if (strFieldName == STR_INDUSTRYNAME || strFieldName == STR_JC || strFieldName == STR_DM || strFieldName == STR_PJ_STR || strFieldName == STR_INDUSTRY_SORT || strFieldName == STR_CHANGE_STOCK_BTN || strFieldName == STR_DIAGNOSE_QUICK_BTN)
						pDC->DrawText(szText,   lstrlen(szText),   &rcItem,   DT_BOTTOM|DT_CENTER|DT_NOPREFIX|DT_SINGLELINE); 
					else
					if (i > 0)
						pDC->DrawText(szText,   lstrlen(szText),   &rcItem,   DT_BOTTOM|DT_RIGHT|DT_NOPREFIX|DT_SINGLELINE); 					
					else
						pDC->DrawText(szText,   lstrlen(szText),   &rcItem,   DT_BOTTOM|DT_NOPREFIX|DT_SINGLELINE); 
				}
			}
		}   
	}   
	pDC->SelectObject(pOldFont);
	//pDC->SelectObject(hobj);
	if (m_pFont)
		pDC->SelectObject(pOldFont);
}

void CStockListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//lpMeasureItemStruct->itemHeight = 30;
	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

BOOL CStockListCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CSkinListCtrl::OnEraseBkgnd(pDC);
	CRect rect;
	GetClientRect(rect);
	if (gpSkinManager->GetBitmap(ID_GROUP_LIST_BACK))
		gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(ID_GROUP_LIST_BACK),pDC,rect);
	else
		pDC->FillRect(rect,&CBrush(gpSkinManager->getColor(BKCOLOR)));
	return TRUE;
	/*
	COLORREF cl1,cl2;
	GRADIENT_RECT gRct;
	TRIVERTEX gVert[2];

	cl1 = RGB(255,255,255);
	cl2 = RGB(236,239,244);
	gVert[0].x = 0;
	gVert[0].y = 0;
	gVert[0].Red = (GetRValue(cl1)<<8);
	gVert[0].Green = (GetGValue(cl1)<<8);
	gVert[0].Blue = (GetBValue(cl1)<<8);
	gVert[0].Alpha = 0x0000;

	gVert[1].x = rect.Width();
	gVert[1].y = rect.Height();
	gVert[1].Red = (GetRValue(cl2)<<8);
	gVert[1].Green = (GetGValue(cl2)<<8);
	gVert[1].Blue = (GetBValue(cl2)<<8);
	gVert[1].Alpha = 0x0000;

	gRct.UpperLeft = 0;
	gRct.LowerRight = 1;
	::GradientFill( pDC->m_hDC, gVert, 2, &gRct, 1, GRADIENT_FILL_RECT_V );
	return true;*/
	//return CListCtrl::OnEraseBkgnd(pDC);
}


//void CStockListCtrl::OnRButtonDown(UINT nFlags, CPoint point)
//{
//    // TODO: 在此添加消息处理程序代码和/或调用默认值
//    CMenu * pMenu=new CMenu(),*pPop;
//    pMenu->LoadMenu(IDR_MENU_STOCK);
//
//    pPop = pMenu->GetSubMenu(0);
//    GetCursorPos(&point);	
//    pPop->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
//
//
//    pMenu->DestroyMenu();
//    delete pMenu;
//
//    CListCtrl::OnRButtonDown(nFlags, point);
//}

void CStockListCtrl::OnColumnClick( NMHDR* pNMHDR, LRESULT* pResult )
{
	if (m_bAutoSort == false)
		return;

    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    if( pNMListView->iSubItem == m_nSortedCol )
        m_bAsc = !m_bAsc;
    else
    {
        m_bAsc = TRUE;
        m_nSortedCol = pNMListView->iSubItem;
    }
    VERIFY(SortItems( CompareFunction, reinterpret_cast<DWORD>( this )));
    *pResult = 0;
}

void CStockListCtrl::SetSortCol(int c_nCol)
{
	if (m_nSortedCol == c_nCol)
		m_bAsc = !m_bAsc;
	else
		m_nSortedCol = c_nCol;
}
void CStockListCtrl::ProcSort()
{
	VERIFY(SortItems( CompareFunction, reinterpret_cast<DWORD>( this )));
}

int CStockListCtrl::GetPos(const CString strName)
{
    LVCOLUMN lvcol;
    WCHAR   str[128];
///-    int    nColNum;
    CString   strColumnName;

    int index = 0;
    lvcol.mask = LVCF_TEXT;
    lvcol.pszText = str;
    lvcol.cchTextMax = 128;

    while(GetColumn(index, &lvcol))
    {
        strColumnName = lvcol.pszText;            
        if (!strColumnName.Compare(strName))
        {
            break;
        }
        index ++;
    }
    return index;

}

CString CStockListCtrl::GetPosName(const int c_nIndex)
{
    LVCOLUMN lvcol;
    WCHAR   str[128];
///-    int    nColNum;    
    
    lvcol.mask = LVCF_TEXT;
    lvcol.pszText = str;
    lvcol.cchTextMax = 128;

    GetColumn(c_nIndex, &lvcol);
	return lvcol.pszText;
}

//LRESULT CStockListCtrl::ColumnSort(WPARAM wParam,LPARAM lParam)
//{
//    m_fAsc = TRUE;
//    m_nSortedCol = lParam;
//    SortItems( CompareFunction, reinterpret_cast<DWORD>( this ));
//    return 0;
//}


void CStockListCtrl::PreSubclassWindow()
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
int CStockListCtrl::OnToolHitTest(CPoint point, TOOLINFO * pTI) const
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
		row += 3000;
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
int CStockListCtrl::CellRectFromPoint(CPoint & point, RECT * cellrect, int * col) const
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
BOOL CStockListCtrl::OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult )
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
		if (col == 0)
		{
			SStock * pStock = (SStock *)GetItemData(row);
			if (pStock)
			{
				strTipText = pStock->m_sQuote.szStockCode;
			}
			else
				strTipText = GetItemText( row, col );
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

void CStockListCtrl::SetListFont(CFont *c_pFont)
{
	m_pFont = c_pFont;
}

void CStockListCtrl::SetUnderLine(bool c_b)
{
	m_bUnderLine = c_b;
}

void CStockListCtrl::SetAutoSort(bool c_b)
{
	m_bAutoSort = c_b;
}

void CStockListCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CSkinListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
}
