// XPButton.cpp : implementation file
//

#include "stdafx.h"
#include "XPButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXPButton

CXPButton::CXPButton()
{
	m_BitmapAttached = false;
	m_BitmapMouseInAttached = false;

	m_BitmapFillActiveAttached = false;
	m_BitmapFillInactiveAttached = false;

	m_nMoveType = 0;
	m_pBtnMove = NULL;
	m_pBtnMoveData = NULL;

	m_bMoving = true;
	m_nPopMenuType = 0;
	m_nPopMenuID = 0;
	m_pCheckMenu = NULL;
	m_pMenuData = NULL;
	m_bNoDraw = false;
	m_iBmpPos = 0;
	m_iTextPos = 0;
	m_bBorder = true;
	m_bBMP = false;
	m_bBMPFill = false;
	m_bBackColor = false;
	m_bTextColor = false;
	m_BoundryPen.CreatePen(PS_INSIDEFRAME | PS_SOLID, 1, RGB(0, 0, 0));
	m_InsideBoundryPenLeft.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(153, 198, 252));//RGB(250, 196, 88)); 
	m_InsideBoundryPenRight.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(162, 201, 255));//RGB(251, 202, 106));
	m_InsideBoundryPenTop.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(162, 189, 252));//RGB(252, 210, 121));
	m_InsideBoundryPenBottom.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(162, 201, 255));//RGB(229, 151, 0));
	
	m_crBtnBackColor = RGB(255,255,255);
	
	m_InsideBoundryPenLeftSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(153, 198, 252)); 
	m_InsideBoundryPenTopSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(162, 201, 255));
	m_InsideBoundryPenRightSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(162, 189, 252));
	m_InsideBoundryPenBottomSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(162, 201, 255));
	
	m_bOver = m_bSelected = m_bTracking = m_bFocus = FALSE;
	m_bUnderLine =false;	
	m_bTitleInRect = false;

	m_bShowed = false;
	m_hUserCursor = 0;
}

CXPButton::~CXPButton()
{
	m_BoundryPen.DeleteObject();
	m_InsideBoundryPenLeft.DeleteObject();
	m_InsideBoundryPenRight.DeleteObject();
	m_InsideBoundryPenTop.DeleteObject();
	m_InsideBoundryPenBottom.DeleteObject();
		
	m_InsideBoundryPenLeftSel.DeleteObject();
	m_InsideBoundryPenTopSel.DeleteObject();
	m_InsideBoundryPenRightSel.DeleteObject();
	m_InsideBoundryPenBottomSel.DeleteObject();
	
	if (m_bBMP)
	{
		m_Bitmap.DeleteObject();
		m_BitmapMouseIn.DeleteObject();
	}
}


BEGIN_MESSAGE_MAP(CXPButton, CButton)
	//{{AFX_MSG_MAP(CXPButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXPButton message handlers

//添加Owner Draw属性
void CXPButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);
}

void CXPButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}
	if (m_nMoveType > 0 && m_bMoving)
	{
		CPoint pt;
		GetCursorPos(&pt);
		CRect rect;
		GetWindowRect(rect);
		int h = rect.Height();
		rect.top += pt.y - m_ptOrg.y;
		rect.bottom += pt.y - m_ptOrg.y;
		//MoveWindow(rect);
		if (m_pBtnMove && m_pBtnMoveData)
			m_pBtnMove(m_pBtnMoveData,this,pt.y - m_ptOrg.y,false);
		m_ptOrg = pt;
	}
	CButton::OnMouseMove(nFlags, point);
}


LRESULT CXPButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bOver = FALSE;
	m_bTracking = FALSE;
	//InvalidateRect(NULL, FALSE);
	InvalidateRect(NULL);	
	if (m_pPopMenu)
	{
		//m_pPopMenu->;
	}
	//if (m_bShowed)
	//	m_bShowed = false;
	return 0;
}

LRESULT CXPButton::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	BOOL bOver;
	bOver = m_bOver;
	m_bOver = TRUE;
	InvalidateRect(NULL);
	
	if (bOver == FALSE && m_nPopMenuType == 2 && m_nPopMenuID > 0)
	{
		m_bOver = TRUE;
		ShowPopMenu();
	}
	return 0;
}


void CXPButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//从lpDrawItemStruct获取控件的相关信息
	CRect rect =  lpDrawItemStruct->rcItem;
	CDC *pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	if (m_bNoDraw)
		return ;
	int nSaveDC=pDC->SaveDC();
	UINT state = lpDrawItemStruct->itemState;
	POINT pt ;
	TCHAR strText[MAX_PATH + 1];
	::GetWindowText(m_hWnd, strText, MAX_PATH);
	
	//画按钮的外边框，它是一个半径为5的圆角矩形

	pDC->SetBkMode(TRANSPARENT);
	pt.x = 8;
	pt.y = 8;
	CPen* hOldPen = pDC->SelectObject(&m_BoundryPen);
	if (m_bBorder)
		pDC->RoundRect(&rect, pt);
	
	//获取按钮的状态
	if (state & ODS_FOCUS)
	{
		m_bFocus = TRUE;
		m_bSelected = TRUE;
	}
	else
	{
		m_bFocus = FALSE;
		m_bSelected = FALSE;
	}
	

	if (state & ODS_SELECTED || state & ODS_DEFAULT)
	{
		m_bFocus = TRUE;
	}

	
	pDC->SelectObject(hOldPen);
	
	if (m_bBorder)
		rect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
		
	//根据按钮的状态绘制内边框
	if (m_bOver || m_bSelected)
		DrawInsideBorder(pDC, &rect);
	
	if (m_bBMP)
	{
		BITMAP bm;
		m_Bitmap.GetBitmap(&bm);
		//CRect   r;
		CDC SourceDC;
		CBitmap * pOldBitmap;
		SourceDC.CreateCompatibleDC(NULL);//生成兼容的CDC
		if (m_bOver)
		{
			pOldBitmap = SourceDC.SelectObject(&m_BitmapMouseIn);			
		}
		else
		{
			pOldBitmap = SourceDC.SelectObject(&m_Bitmap);		
		}
        int x = 0;
        if (m_iBmpPos == 3)
        {
            x = rect.left + (rect.Width() - bm.bmWidth) / 2;
        }
		//pDC->BitBlt(x ,rect.top + (rect.Height() - bm.bmHeight) / 2,bm.bmWidth,bm.bmHeight,&SourceDC,0,0,SRCCOPY);
		pDC->StretchBlt(rect.left ,rect.top,rect.Width(),rect.Height(),&SourceDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
		
		SourceDC.SelectObject(pOldBitmap);
		SourceDC.DeleteDC();
	}
	else
	{
		if (m_bBackColor)
			DoGradientFill(pDC,&rect);
	}/*
	CRect rr;
	rr = rect;
	rr.right -= 4;
	rr.left = rect.right - 20;	
	DrawFrameControl(lpDrawItemStruct->hDC,&rr,DFC_CAPTION,DFCS_CAPTIONCLOSE | DFCS_FLAT);*/
	//显示按钮的文本
	if (strText!=NULL)
	{
		CFont* hFont = GetFont();
		CFont _fontNew;
		bool _bCreateFont = false;
		if ( hFont && m_bUnderLine) {
		LOGFONT lf;
		hFont->GetObject(sizeof(lf), &lf);
		lf.lfUnderline = TRUE;		
		_fontNew.CreateFontIndirect(&lf);
		_bCreateFont = true;
		}

		CFont* hOldFont;
		if (_bCreateFont)
			hOldFont = pDC->SelectObject(&_fontNew);
		else
			hOldFont = pDC->SelectObject(hFont);
		CSize szExtent = pDC->GetTextExtent(strText, lstrlen(strText));
		CPoint pt( rect.CenterPoint().x - szExtent.cx / 2,  rect.CenterPoint().y - szExtent.cy / 2);
		if (m_bBMP)
		{
			if (m_iBmpPos == 1)
				pt.y = rect.bottom - szExtent.cy - 1;
			else
			if (m_iBmpPos == 3)
			{
				if (m_bTitleInRect == false)
				{
					pt.x = rect.left + (rect.Width()-szExtent.cx) / 2;
					pt.y = rect.top + (rect.Height() - szExtent.cy) / 2;
				}
			}
			else
			{
				BITMAP bm;
				m_Bitmap.GetBitmap(&bm);
				pt.x = rect.left + bm.bmWidth + 2;
				pt.y = rect.top + (rect.Height() - szExtent.cy) / 2;
			}
		}
		//if (state & ODS_SELECTED) 
		//	pt.Offset(1, 1);
		int nMode = pDC->SetBkMode(TRANSPARENT);
		if (m_bTextColor)
			pDC->SetTextColor(m_crTextColor);
		else
			pDC->SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));
		if (state & ODS_DISABLED)
		{			
			pDC->DrawState(pt, szExtent, strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		}
		else
		{
			if((m_bTitleInRect && szExtent.cx >= m_rectTitle.Width()) || m_iTextPos == 1)
			{
				m_rectTitle = rect;
				m_rectTitle.left += 2;
				m_rectTitle.right -= 32;
				pDC->DrawText(strText,m_rectTitle,DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE|DT_END_ELLIPSIS);
			}
			else
			pDC->DrawState(pt, szExtent, strText, DSS_NORMAL, TRUE, 0, (HBRUSH)NULL);
		}
		pDC->SelectObject(hOldFont);
		pDC->SetBkMode(nMode);
		if (_bCreateFont)
			_fontNew.DeleteObject();
	}
	
	
	pDC->RestoreDC(nSaveDC);
}

//绘制按钮的底色
void CXPButton::DoGradientFill(CDC *pDC, CRect* rect)
{
/*	CBrush brBk[64];
	int nWidth = rect->Width();	
	int nHeight = rect->Height();
	CRect rct;
	
	for (int i = 0; i < 64; i ++)
	{
		if (m_bOver)
		{
			if (m_bFocus)
				brBk[i].CreateSolidBrush(RGB(255 - (i / 4), 255 - (i / 4), 255 - (i / 3)));
			else
				brBk[i].CreateSolidBrush(RGB(255 - (i / 4), 255 - (i / 4), 255 - (i / 5)));
		}
		else
		{
			if (m_bFocus)
				brBk[i].CreateSolidBrush(RGB(255 - (i / 3), 255 - (i / 3), 255 - (i / 4)));
			else
				brBk[i].CreateSolidBrush(RGB(255 - (i / 3), 255 - (i / 3), 255 - (i / 5)));
		}
	}
	
	for (i = rect->top; i <= nHeight + 2; i ++) 
	{
		rct.SetRect(rect->left, i, nWidth + 2, i + 1);
		pDC->FillRect(&rct, &brBk[((i * 63) / nHeight)]);
	}
	
	for (i = 0; i < 64; i ++)
		brBk[i].DeleteObject();*/

	pDC->FillSolidRect(*rect,m_crBtnBackColor);
}

//绘制按钮的内边框
void CXPButton::DrawInsideBorder(CDC *pDC, CRect* rect)
{
	CPen *pLeft, *pRight, *pTop, *pBottom;
	if (!m_bBorder)
		return;
	if (m_bSelected && !m_bOver)
	{
		pLeft = & m_InsideBoundryPenLeftSel;
		pRight = &m_InsideBoundryPenRightSel;
		pTop = &m_InsideBoundryPenTopSel;
		pBottom = &m_InsideBoundryPenBottomSel;
	}
	else
	{
		pLeft = &m_InsideBoundryPenLeft;
		pRight = &m_InsideBoundryPenRight;
		pTop = &m_InsideBoundryPenTop;
		pBottom = &m_InsideBoundryPenBottom;
	}
	
	CPoint oldPoint = pDC->MoveTo(rect->left, rect->bottom - 1);
	CPen* pOldPen = pDC->SelectObject(pLeft);
	pDC->LineTo(rect->left, rect->top + 1);
	pDC->SelectObject(pRight);
	pDC->MoveTo(rect->right - 1, rect->bottom - 1);
	pDC->LineTo(rect->right - 1, rect->top);
	pDC->SelectObject(pTop);
	pDC->MoveTo(rect->left - 1, rect->top);
	pDC->LineTo(rect->right - 1, rect->top);
	pDC->SelectObject(pBottom);
	pDC->MoveTo(rect->left, rect->bottom);
	pDC->LineTo(rect->right - 1, rect->bottom);
	pDC->SelectObject(pOldPen);
	pDC->MoveTo(oldPoint);

	if (m_bSelected && !m_bOver)
		DrawFocusRect(pDC->m_hDC,rect);
}

void CXPButton::SetBtnBackColor(COLORREF crBk)
{
	m_bBackColor = true;
	m_crBtnBackColor = crBk;
}

COLORREF CXPButton::GetBtnBackColor()
{
	
	return m_crBtnBackColor;
}
void CXPButton::SetTextColor(COLORREF crBk)
{
	m_bTextColor = true;
	m_crTextColor = crBk;
}

void CXPButton::SetBtnBMP(unsigned int c_UID,unsigned int c_UIDMouseIn)
{
	if (m_bBMP)
	{
		if (m_usBMPType == 0)
		{
			m_Bitmap.DeleteObject();
			m_BitmapMouseIn.DeleteObject();
		}
		if (m_usBMPType == 1)
		{
			m_Bitmap.Detach();
			m_BitmapMouseIn.Detach();
		}
		if (m_usBMPType == 2)
		{
			m_Bitmap.Detach();
			m_BitmapMouseIn.Detach();
		}
	}
	if (c_UID == 0 && c_UIDMouseIn == 0)
	{
		m_bBMP = false;
		Invalidate(1);
		return;
	}
	m_bBMP = true;
	m_usBMPType = 0;
	m_Bitmap.LoadBitmap(c_UID);
	m_BitmapMouseIn.LoadBitmap(c_UIDMouseIn);
	Invalidate(1);
}

void CXPButton::SetBtnBMP(HBITMAP c_hNormal,HBITMAP c_hMouseIn)
{
	if (m_bBMP)
	{
		if (m_usBMPType == 0)
		{
			m_Bitmap.DeleteObject();
			m_BitmapMouseIn.DeleteObject();
		}
		if (m_usBMPType == 1)
		{
			m_Bitmap.Detach();
			m_BitmapMouseIn.Detach();
		}
		if (m_usBMPType == 2)
		{
			m_Bitmap.Detach();
			m_BitmapMouseIn.Detach();
		}
	}
	m_usBMPType = 1;
	m_BitmapAttached = m_Bitmap.Attach(c_hNormal);
	m_BitmapMouseInAttached = m_BitmapMouseIn.Attach(c_hMouseIn);
	m_bBMP = true;
	Invalidate(1);
}

void CXPButton::SetBtnBMP(char * c_pNormalName,char * c_pMouseInName)
{
	if (m_bBMP)
	{
		if (m_usBMPType == 0)
		{
			m_Bitmap.DeleteObject();
			m_BitmapMouseIn.DeleteObject();
		}
		if (m_usBMPType == 1)
		{
			if (m_BitmapAttached)
			{
				m_Bitmap.Detach();
				m_BitmapAttached = false;
			}
			if (m_BitmapMouseInAttached)
			{
				m_BitmapMouseIn.Detach();
				m_BitmapMouseInAttached = false;
			}
		}
		if (m_usBMPType == 2)
		{
			if (m_BitmapAttached)
			{
				m_Bitmap.Detach();
				m_BitmapAttached = false;
			}
			if (m_BitmapMouseInAttached)
			{
				m_BitmapMouseIn.Detach();
				m_BitmapMouseInAttached = false;
			}
		}
	}

	HBITMAP h;
	h = (HBITMAP)LoadImage(AfxGetInstanceHandle(),toUnicodeString(c_pNormalName,strlen(c_pNormalName)),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	m_BitmapAttached = m_Bitmap.Attach(h);
	h = (HBITMAP)LoadImage(AfxGetInstanceHandle(),toUnicodeString(c_pMouseInName,strlen(c_pMouseInName)),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	m_BitmapMouseInAttached = m_BitmapMouseIn.Attach(h);
	m_bBMP = true;
	m_usBMPType = 2;
	Invalidate(1);
}

void CXPButton::SetBorder(BOOL c_b)
{
	m_bBorder = c_b;
}

void CXPButton::SetBmpPos(int c_iPos,int c_iTextPos)
{
	m_iBmpPos = c_iPos;
	m_iTextPos = c_iTextPos;
}
BOOL CXPButton::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bNoDraw)
		return true;
	
	CRect   rect;   
	GetClientRect(&rect);
	if (m_bBMPFill)
	{/*
		CBrush brush;
		if (m_bOver)
		brush.CreatePatternBrush(&m_BitmapFillActive);
		else
			brush.CreatePatternBrush(&m_BitmapFillInactive);
		pDC->FillRect(&rect,&brush);
		brush.DeleteObject();
		*/
		BITMAP bm;
		m_BitmapFillActive.GetBitmap(&bm);

		CDC SourceDC;
		CBitmap * pOldBitmap;
		SourceDC.CreateCompatibleDC(NULL);//生成兼容的CDC
		if (m_bOver)
		{
			pOldBitmap = SourceDC.SelectObject(&m_BitmapFillActive);			
		}
		else
		{
			pOldBitmap = SourceDC.SelectObject(&m_BitmapFillInactive);		
		}
		pDC->StretchBlt(rect.left ,rect.top,rect.Width(),rect.Height(),&SourceDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
		
		SourceDC.SelectObject(pOldBitmap);
		SourceDC.DeleteDC();

	}
	else
	{
		if (m_bBackColor)
		{
			CBrush brush;
			brush.CreateSolidBrush(m_crBtnBackColor);
			pDC->FillRect(&rect,&brush);
			brush.DeleteObject();
		}
	}
	return true;
	
	return CButton::OnEraseBkgnd(pDC);
}

BOOL CXPButton::SetNoDraw(BOOL c_bNoDraw)
{
	m_bNoDraw = c_bNoDraw;
	return m_bNoDraw;
}

BOOL CXPButton::SetBMPFill(BOOL c_bFill,HBITMAP c_hFillActive,HBITMAP c_bFillInactive)
{
	if (m_bBMPFill)
	{
		if (m_usFillType == 0)
		{
			m_BitmapFillActive.DeleteObject();
			m_BitmapFillInactive.DeleteObject();
		}
		if (m_usFillType == 1)
		{
			m_BitmapFillActive.Detach();
			m_BitmapFillInactive.Detach();
		}
	}
	m_bBMPFill = c_bFill;
	m_usFillType = 1;
	if (m_bBMPFill)
	{
		m_BitmapFillActiveAttached = m_BitmapFillActive.Attach(c_hFillActive);
		m_BitmapFillInactiveAttached = m_BitmapFillInactive.Attach(c_bFillInactive);
	}
	Invalidate(1);
	return m_bBMPFill;
}

BOOL CXPButton::SetBMPFill(BOOL c_bFill,unsigned int c_unFillActive,unsigned int c_unFillInactive)
{
	if (m_bBMPFill)
	{
		if (m_usFillType == 0)
		{
			m_BitmapFillActive.DeleteObject();
			m_BitmapFillInactive.DeleteObject();
		}
		if (m_usFillType == 1)
		{
			if (m_BitmapFillActiveAttached)
			{
				m_BitmapFillActive.Detach();
				m_BitmapFillActiveAttached = false;
			}
			if (m_BitmapFillInactiveAttached)
			{
				m_BitmapFillInactive.Detach();
				m_BitmapFillInactiveAttached = false;
			}
		}
	}
	m_bBMPFill = c_bFill;
	m_usFillType = 0;
	if (m_bBMPFill)
	{
		m_BitmapFillActive.LoadBitmap(c_unFillActive);
		m_BitmapFillInactive.LoadBitmap(c_unFillInactive);
	}
	Invalidate(1);
	return m_bBMPFill;
}

void CXPButton::FillRectImage(CBitmap &bitmap,CDC *pDC,CRect &rect)

{

	CDC MemDC;

	MemDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap *pOldBitmap = (CBitmap *)MemDC.SelectObject(&bmp); 
	CBrush brush;
	brush.CreatePatternBrush(&bitmap);

	// bitmap.GetBitmap(&bm);

	// int li_Width = bm.bmWidth;

	// int li_Height = bm.bmHeight;
	CRect r;
	r.left = 0;
	r.top = 0;
	r.right = rect.right;
	r.bottom = rect.bottom;
	MemDC.FillRect(&r,&brush);
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);    

	MemDC.SelectObject(pOldBitmap);
	brush.DeleteObject();
	bmp.DeleteObject();
	MemDC.DeleteDC();

}

void CXPButton::SetUnderLine(BOOL c_b)
{
	m_bUnderLine = c_b;
}

void CXPButton::InitToolTip()
{
    if (m_ToolTip.m_hWnd == NULL)
    {
        // Create ToolTip control
        m_ToolTip.Create(this);
        // Create active
        m_ToolTip.Activate(TRUE);
    }
}

void CXPButton::SetToolTipText(CString *spText, BOOL bActivate)
{
    // We cannot accept NULL pointer
    if (spText == NULL) return;

    // Initialize ToolTip
    InitToolTip();

    // If there is no tooltip defined then add it
    if (m_ToolTip.GetToolCount() == 0)
    {
        CRect rectBtn; 
        GetClientRect(rectBtn);
        m_ToolTip.AddTool(this, (LPCTSTR)*spText, rectBtn, 1);
    }

    // Set text for tooltip
    m_ToolTip.UpdateTipText((LPCTSTR)*spText, this, 1);
    m_ToolTip.Activate(bActivate);
}
BOOL CXPButton::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类
    InitToolTip();
    m_ToolTip.RelayEvent(pMsg);
    return CButton::PreTranslateMessage(pMsg);
}

void CXPButton::ShowPopMenu()
{
	if(m_bShowed)
		return;
	m_bShowed = true;
	CPoint point;
	CMenu * pMenu=new CMenu(),*pPop;
	pMenu->LoadMenu(m_nPopMenuID);
	if (m_pCheckMenu)
	{
		m_pCheckMenu(m_pMenuData,pMenu);
	}
	pPop = pMenu->GetSubMenu(0);
	GetCursorPos(&point);	
	CRect rect;
	GetWindowRect(rect);
	point.x = rect.left;
	point.y = rect.bottom;
	m_pPopMenu = pPop;
	if (m_nPopMenuType == 2)
		SetTimer(109,500,NULL);
	pPop->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this->GetParent());
	m_pPopMenu = NULL;
	pMenu->DestroyMenu();
	delete pMenu;
	m_bShowed = false;
}

void CXPButton::SetPopMenu(int c_nType,int c_nID)
{
	m_nPopMenuType = c_nType;
	m_nPopMenuID = c_nID;
}
void CXPButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_nMoveType > 0)
	{
		CPoint pt;
		GetCursorPos(&pt);
		m_ptOrg = pt;
		m_bMoving = true;
	}

	if (m_pPopMenu && m_bShowed)// && m_nPopMenuType == 2)
	{
		::SendMessage(this->GetParent()->GetSafeHwnd(),WM_CANCELMODE,0,0);
		m_bShowed = false;
	}

	CButton::OnLButtonDown(nFlags, point);
}

void CXPButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_nMoveType > 0 && m_bMoving)
	{
		CPoint pt;
		GetCursorPos(&pt);
		CRect rect;
		GetWindowRect(rect);
		int h = rect.Height();
		rect.top += pt.y - m_ptOrg.y;
		rect.bottom += pt.y - m_ptOrg.y;
		//MoveWindow(rect);
		if (m_pBtnMove && m_pBtnMoveData)
			m_pBtnMove(m_pBtnMoveData,this,pt.y - m_ptOrg.y,true);
		m_ptOrg = pt;
	}
	if (m_nPopMenuType == 2)
		m_bShowed = false;
	m_bMoving = false;

	if (m_nPopMenuType == 1 && m_nPopMenuID >0)
		ShowPopMenu();

	CButton::OnLButtonUp(nFlags, point);
}

void CXPButton::SetMoveType(int c_nMoveType)
{
	m_nMoveType = c_nMoveType;
	m_bMoving = false;
}
void CXPButton::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_pPopMenu && m_nPopMenuType == 2)
	{
		CRect rect,rectB;
		this->GetWindowRect(rect);
		rectB = rect;
		rectB.top = rect.bottom;
		rectB.bottom += 25 * (m_pPopMenu->GetMenuItemCount()+6);
		rectB.right += 240;
		CPoint point;
		GetCursorPos(&point);
		if (!rect.PtInRect(point) && !rectB.PtInRect(point))
		{
			//int nState = m_pPopMenu->GetMenuState();
			::PostMessage(this->GetParent()->GetSafeHwnd(),WM_CANCELMODE,0,0);
			m_bShowed = false;
		}
		
	}
	else
	{
		if (m_bShowed)
		{
			m_bShowed = false;
			KillTimer(109);
		}
	}
	CButton::OnTimer(nIDEvent);
}

void CXPButton::SetTitleInRect(bool m_b,CRect c_rect)
{
	m_bTitleInRect = m_b;
	m_rectTitle = c_rect;
}

void CXPButton::SetUserCursor(HCURSOR c_h)
{
	m_hUserCursor = c_h;
}
BOOL CXPButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_hUserCursor)
	{
		::SetCursor(m_hUserCursor);
		return TRUE;
	}
	return CButton::OnSetCursor(pWnd, nHitTest, message);
}
