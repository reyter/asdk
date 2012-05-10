// SkinVerticleScrollbar.cpp : implementation file
//

#include "stdafx.h"
#include "SkinVerticleScrollbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinVerticleScrollbar

CSkinVerticleScrollbar::CSkinVerticleScrollbar()
{
	bMouseDown = false;
	bMouseDownArrowUp = false;
	bMouseDownArrowDown = false;
	bDragging = false;

	nThumbTop = 16;
	dbThumbInterval = 0.000000;
	pList = NULL;

}

CSkinVerticleScrollbar::~CSkinVerticleScrollbar()
{
}


BEGIN_MESSAGE_MAP(CSkinVerticleScrollbar, CStatic)
	//{{AFX_MSG_MAP(CSkinVerticleScrollbar)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinVerticleScrollbar message handlers

BOOL CSkinVerticleScrollbar::OnEraseBkgnd(CDC* pDC) 
{
	return CStatic::OnEraseBkgnd(pDC);
}

void CSkinVerticleScrollbar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	CRect clientRect;
	GetClientRect(&clientRect);

	int nHeight = clientRect.Height() - 16;
	

	CRect rectUpArrow(0,0,17,16);
	CRect rectDownArrow(0,nHeight,17,nHeight+16);
	CRect rectThumb(0,nThumbTop,17,nThumbTop+40);

	if(rectThumb.PtInRect(point))
	{
		bMouseDown = true;
	}

	if(rectDownArrow.PtInRect(point))
	{
		bMouseDownArrowDown = true;
		SetTimer(2,250,NULL);
	}

	if(rectUpArrow.PtInRect(point))
	{
		bMouseDownArrowUp = true;
		SetTimer(2,250,NULL);
	}
	
	CStatic::OnLButtonDown(nFlags, point);
}

void CSkinVerticleScrollbar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	UpdateThumbPosition();
	KillTimer(1);
	ReleaseCapture();
	
	bool bInChannel = true;

	CRect clientRect;
	GetClientRect(&clientRect);
	int nHeight = clientRect.Height() - 16;
	CRect rectUpArrow(0,0,17,16);
	CRect rectDownArrow(0,nHeight,17,nHeight+16);
	CRect rectThumb(0,nThumbTop,17,nThumbTop+40);



	if(rectUpArrow.PtInRect(point) && bMouseDownArrowUp)
	{
		ScrollUp();	
		bInChannel = false;
	}

	if(rectDownArrow.PtInRect(point) && bMouseDownArrowDown)
	{
		ScrollDown();
		bInChannel = false;
	}

	if(rectThumb.PtInRect(point))
	{
		bInChannel = false;
	}

	if(bInChannel == true && !bMouseDown)
	{
		if(point.y > nThumbTop)
		{
			PageDown();
		}
		else
		{
			PageUp();
		}
	}

	bMouseDown = false;
	bDragging = false;
	bMouseDownArrowUp = false;
	bMouseDownArrowDown = false;
		
	CStatic::OnLButtonUp(nFlags, point);
}

void CSkinVerticleScrollbar::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect clientRect;
	GetClientRect(&clientRect);

	if(bMouseDown)
	{
		nThumbTop = point.y-20; //-13 so mouse is in middle of thumb
		
		double nMax = pList->GetScrollLimit(SB_VERT);
		int nPos = pList->GetScrollPos(SB_VERT);

		double nHeight = clientRect.Height()-72;
		double nVar = nMax;
		dbThumbInterval = nHeight/nVar;

		//figure out how many times to scroll total from top
		//then minus the current position from it
		int nScrollTimes = (int)((nThumbTop-40)/dbThumbInterval)-nPos;

		//grab the row height dynamically
		//so if the font size or type changes
		//our scroll will still work properly
		CRect itemrect;
		pList->GetItemRect(0,&itemrect, LVIR_BOUNDS);

		CSize size;
		size.cx = 0;
		size.cy = nScrollTimes*itemrect.Height();
		

		pList->Scroll(size);


		LimitThumbPosition();

		Draw();
		
	}
	CStatic::OnMouseMove(nFlags, point);
}

void CSkinVerticleScrollbar::OnPaint() 
{
	CPaintDC dc(this); 
	Draw();
}

void CSkinVerticleScrollbar::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == 1)
	{
		if(bMouseDownArrowDown)
		{
			ScrollDown();
		}
		
		if(bMouseDownArrowUp)
		{
			ScrollUp();
		}
	}
	else if(nIDEvent == 2)
	{
		if(bMouseDownArrowDown)
		{
			KillTimer(2);
			SetTimer(1, 50, NULL);
		}
		
		if(bMouseDownArrowUp)
		{
			KillTimer(2);
			SetTimer(1, 50, NULL);
		}
	}
	CStatic::OnTimer(nIDEvent);
}

void CSkinVerticleScrollbar::PageDown()
{
	pList->SendMessage(WM_VSCROLL, MAKELONG(SB_PAGEDOWN,0),NULL);
	UpdateThumbPosition();
}

void CSkinVerticleScrollbar::PageUp()
{
	pList->SendMessage(WM_VSCROLL, MAKELONG(SB_PAGEUP,0),NULL);
	UpdateThumbPosition();
}

void CSkinVerticleScrollbar::ScrollUp()
{
	pList->SendMessage(WM_VSCROLL, MAKELONG(SB_LINEUP,0),NULL);
	UpdateThumbPosition();
}

void CSkinVerticleScrollbar::ScrollDown()
{
	pList->SendMessage(WM_VSCROLL, MAKELONG(SB_LINEDOWN,0),NULL);
	UpdateThumbPosition();
}

void CSkinVerticleScrollbar::UpdateThumbPosition()
{
	CRect clientRect;
	GetClientRect(&clientRect);

	double nPos = pList->GetScrollPos(SB_VERT);
	double nMax = pList->GetScrollLimit(SB_VERT);
	double nHeight = (clientRect.Height()-72);
	double nVar = nMax;

	dbThumbInterval = nHeight/nVar;

	double nNewdbValue = (dbThumbInterval * nPos);
	int nNewValue = (int)nNewdbValue;


	nThumbTop = 11+nNewValue;

	LimitThumbPosition();
	
	Draw();	
}


void CSkinVerticleScrollbar::Draw()
{

	CClientDC dc(this);
	CRect clientRect;
	GetClientRect(&clientRect);
	CMemDC memDC(&dc, &clientRect);
	memDC.FillSolidRect(&clientRect,  gpSkinManager->getColor(BKCOLOR));
	
	CDC bitmapDC;
	bitmapDC.CreateCompatibleDC(&dc);

	CBitmap bitmap;

	//bitmap.LoadBitmap(IDB_VERTICLE_SCROLLBAR_UPARROW);
	bitmap.Attach(gpSkinManager->GetBitmap(V_UP));
	//bitmap.LoadBitmap(IDB_V_UPARROW);
	CBitmap * pOldBitmap = bitmapDC.SelectObject(&bitmap);
	//memDC.BitBlt(clientRect.left,clientRect.top+11,12,26,&bitmapDC,0,0,SRCCOPY);
	memDC.BitBlt(clientRect.left,clientRect.top,17,16,&bitmapDC,0,0,SRCCOPY);
	bitmapDC.SelectObject(pOldBitmap);
	bitmap.Detach();
	//bitmap.DeleteObject();
	pOldBitmap = NULL;
	
	//draw the background (span)
	//bitmap.LoadBitmap(IDB_VERTICLE_SCROLLBAR_SPAN);
	//bitmap.LoadBitmap(IDB_V_BACK);
	bitmap.Attach(gpSkinManager->GetBitmap(V_BACK));
	pOldBitmap = bitmapDC.SelectObject(&bitmap);
	int nHeight = clientRect.Height() - 16*2;

	memDC.StretchBlt(clientRect.left, clientRect.top+16, 17,nHeight,&bitmapDC, 0,0, 17, 1, SRCCOPY);

	bitmapDC.SelectObject(pOldBitmap);
	//bitmap.DeleteObject();
	bitmap.Detach();
	pOldBitmap = NULL;
	
	//draw the down arrow of the scrollbar
	//bitmap.LoadBitmap(IDB_VERTICLE_SCROLLBAR_DOWNARROW);
	//bitmap.LoadBitmap(IDB_V_DOWNARROW);
	bitmap.Attach(gpSkinManager->GetBitmap(V_DOWN));
	pOldBitmap = bitmapDC.SelectObject(&bitmap);
	memDC.BitBlt(clientRect.left,clientRect.bottom-16,17,16,&bitmapDC,0,0,SRCCOPY);
	bitmapDC.SelectObject(pOldBitmap);
	//bitmap.DeleteObject();
	bitmap.Detach();
	pOldBitmap = NULL;

	//If there is nothing to scroll then don't
	//show the thumb control otherwise show it
	if(pList->GetScrollLimit(SB_VERT) != 0)
	{
		//draw the thumb control
		//bitmap.LoadBitmap(IDB_VERTICLE_SCROLLBAR_THUMB);
		//bitmap.LoadBitmap(IDB_V_MOVEBLOCK);
		bitmap.Attach(gpSkinManager->GetBitmap(V_THUMB));
		pOldBitmap = bitmapDC.SelectObject(&bitmap);
		memDC.BitBlt(clientRect.left,clientRect.top+nThumbTop,17,40,&bitmapDC,0,0,SRCCOPY);
		bitmapDC.SelectObject(pOldBitmap);
		//bitmap.DeleteObject();
		bitmap.Detach();
		pOldBitmap = NULL;
	}


}

void CSkinVerticleScrollbar::LimitThumbPosition()
{
	CRect clientRect;
	GetClientRect(&clientRect);

	if(nThumbTop+40 > (clientRect.Height()-16))
	{
		nThumbTop = clientRect.Height()-56;
	}

	if(nThumbTop < (clientRect.top+16))
	{
		nThumbTop = clientRect.top+16;
	}
}

