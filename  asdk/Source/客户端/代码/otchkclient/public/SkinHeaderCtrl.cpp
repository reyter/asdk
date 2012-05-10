// SkinHeaderCtrl.cpp : implementation file
//

#include "stdafx.h"
//#include "SkinList.h"
#include "SkinHeaderCtrl.h"
#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinHeaderCtrl

CSkinHeaderCtrl::CSkinHeaderCtrl()
{
}

CSkinHeaderCtrl::~CSkinHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CSkinHeaderCtrl, CHeaderCtrl)
	//{{AFX_MSG_MAP(CSkinHeaderCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinHeaderCtrl message handlers

void CSkinHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	
}

void CSkinHeaderCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect, rectItem, clientRect;
	GetClientRect(&rect);
	GetClientRect(&clientRect);
	CMemDC memDC(&dc, rect);
	CDC bitmapDC;
	bitmapDC.CreateCompatibleDC(&dc);
	
	gpSkinManager->FillRectImage(gpSkinManager->GetBitmap(ID_GROUP_HEAD_BACK),&memDC,rect);
	//memDC.FillSolidRect(&rect, RGB(76,85,118));
	memDC.SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));
	int nItems = GetItemCount();
	CPen pen(PS_SOLID,1,RGB(128,128,128));
	CPen * pOldPen;
	for(int i = 0; i <nItems; i++)
	{
		
		TCHAR buf1[256];
		HD_ITEM hditem1;
		
		hditem1.mask = HDI_TEXT | HDI_FORMAT | HDI_ORDER;
		hditem1.pszText = buf1;
		hditem1.cchTextMax = 255;
		GetItem( i, &hditem1 );
		
		GetItemRect(i, &rect);
				
		
		//span the bitmap for the width of the column header item
		int nWidth = rect.Width() - 4;				
				
		//Get all the info for the current
		//item so we can draw the text to it
		//in the desired font and style
		DRAWITEMSTRUCT	DrawItemStruct;
		GetItemRect(i, &rectItem);
		
		
		DrawItemStruct.CtlType		= 100;
		DrawItemStruct.hDC			= dc.GetSafeHdc();
		DrawItemStruct.itemAction	= ODA_DRAWENTIRE; 
		DrawItemStruct.hwndItem 	= GetSafeHwnd(); 
		DrawItemStruct.rcItem	= rectItem;
		DrawItemStruct.itemID	= i;
		DrawItem(&DrawItemStruct);
		
		UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER |DT_CENTER | DT_END_ELLIPSIS ;
		
		//HGDIOBJ hobj = memDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
		CFont *pOldFont = memDC.SelectObject(gpSkinManager->m_pFontSmall);
		
		memDC.SetBkMode(TRANSPARENT);
		rectItem.DeflateRect(2,2,2,2);
		
		TCHAR buf[256];
		HD_ITEM hditem;
		
		hditem.mask = HDI_TEXT | HDI_FORMAT | HDI_ORDER;
		hditem.pszText = buf;
		hditem.cchTextMax = 255;
		GetItem( DrawItemStruct.itemID, &hditem );

		memDC.DrawText(buf, &rectItem, uFormat);
		pOldPen = memDC.SelectObject(&pen);
		int nOld = memDC.SetROP2(R2_NOTXORPEN);//R2_NOT);
		memDC.MoveTo(rectItem.right,rectItem.top);
		memDC.LineTo(rectItem.right,rectItem.bottom);
		memDC.SetROP2(nOld);
		memDC.SelectObject(pOldPen);
		//memDC.SelectObject(hobj);
		memDC.SelectObject(pOldFont);
	}		
}

BOOL CSkinHeaderCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return false;	
}
