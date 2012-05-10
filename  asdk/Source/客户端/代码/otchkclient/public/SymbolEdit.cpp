// AeroEdit.cpp : implementation file
//

#include "stdafx.h"
#include "SymbolEdit.h"

// CSymbolEdit

IMPLEMENT_DYNAMIC(CSymbolEdit, CEdit)

CSymbolEdit::CSymbolEdit():
m_hSymbolIcon(NULL),
m_bInternalIcon(false),
m_bBMP(FALSE),
m_bFocus(FALSE),
m_colorPromptText(RGB(127,127,127))
{
	m_fontPrompt.CreateFont(
		12,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                      // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		DEFAULT_CHARSET,           // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("ËÎÌו"));

	m_colorBack = GetSysColor(COLOR_WINDOW);
}

CSymbolEdit::~CSymbolEdit()
{
	DestroyIcon();
	if (m_bBMP)
	{
		m_Bitmap.DeleteObject();;
		m_BitmapMouseIn.DeleteObject();
	}
}


BEGIN_MESSAGE_MAP(CSymbolEdit, CEdit)
	ON_WM_PAINT()
	ON_MESSAGE(WM_SETFONT, OnSetFont)
END_MESSAGE_MAP()

void CSymbolEdit::DestroyIcon()
{
	// if icon was loaded internally, destroy it
	if(m_bInternalIcon || m_hSymbolIcon != NULL)
		::DestroyIcon(m_hSymbolIcon);
}

void CSymbolEdit::PreSubclassWindow() 
{
	RecalcLayout();
}

void CSymbolEdit::SetSymbolIcon(HICON hIcon, BOOL redraw)
{
	DestroyIcon();

	m_hSymbolIcon = hIcon;

	// icon was not loaded internally
	m_bInternalIcon = false;

	RecalcLayout();

	if(redraw)
		Invalidate(TRUE);
}

void CSymbolEdit::SetSymbolIcon(UINT id, BOOL redraw)
{
	DestroyIcon();

	m_hSymbolIcon = (HICON)::LoadImage(
		AfxGetResourceHandle(),
		MAKEINTRESOURCE(id),
		IMAGE_ICON,
		16,
		16,
		LR_DEFAULTCOLOR|LR_LOADTRANSPARENT);

	ASSERT(m_hSymbolIcon != NULL);

	// icon was loaded internally
	m_bInternalIcon = true;

	RecalcLayout();

	if(redraw)
		Invalidate(TRUE);
}

void CSymbolEdit::SetPromptText(CString text, BOOL redraw)
{
	m_strPromptText = text;

	if(redraw)
		Invalidate(TRUE);
}

void CSymbolEdit::SetPromptText(LPCTSTR szText, BOOL redraw)
{
	m_strPromptText = szText;

	if(redraw)
		Invalidate(TRUE);
}

void CSymbolEdit::SetPromptTextColor(COLORREF color, BOOL redraw)
{
	m_colorPromptText = color;

	if(redraw)
		Invalidate(TRUE);
}

void CSymbolEdit::SetPromptFont(CFont& font, BOOL redraw)
{
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));

	font.GetLogFont(&lf);
	SetPromptFont(&lf);

	if(redraw)
		Invalidate(TRUE);
}

void CSymbolEdit::SetPromptFont(const LOGFONT* lpLogFont, BOOL redraw)
{
	m_fontPrompt.DeleteObject();	
	m_fontPrompt.CreateFontIndirect(lpLogFont);

	if(redraw)
		Invalidate(TRUE);
}

void CSymbolEdit::RecalcLayout()
{
	int width = GetSystemMetrics( SM_CXSMICON );

	if(m_hSymbolIcon)
	{
		DWORD dwMargins = GetMargins();
		SetMargins(LOWORD(dwMargins), width + 6);
	}
}

// CSymbolEdit message handlers

void CSymbolEdit::OnPaint()
{
	CPaintDC dc(this);
	CString text;
	GetWindowText(text);

	CRect rect;
	GetClientRect( &rect );
	
	//Clearing the background
	dc.FillSolidRect( rect, m_colorBack);

	if (m_bBMP)
	{
		CBrush brush;
		brush.CreatePatternBrush(&m_Bitmap);
		dc.FillRect(rect,&brush);
		brush.DeleteObject();
		if(text.GetLength() == 0 && m_bFocus == FALSE)
		{
			BITMAP bmp;
			m_BitmapMouseIn.GetBitmap(&bmp);
			brush.CreatePatternBrush(&m_BitmapMouseIn);
			CRect r;
			r = rect;
			r.right = r.left + bmp.bmWidth;
			dc.FillRect(r,&brush);
			brush.DeleteObject();
		}
	}
	DWORD dwMargins = GetMargins();

	if( m_hSymbolIcon )
	{
		// Drawing the icon
		int width = GetSystemMetrics( SM_CXSMICON );
		int height = GetSystemMetrics( SM_CYSMICON );
		
		::DrawIconEx( 
			dc.m_hDC, 
			rect.right - width - 1, 
			1,
			m_hSymbolIcon, 
			width, 
			height, 
			0, 
			NULL, 
			DI_NORMAL);
		
		rect.left += LOWORD(dwMargins) + 1;
		rect.right -= (width + 7);
	}
	else
	{
		rect.left += (LOWORD(dwMargins) + 1);
		rect.right -= (HIWORD(dwMargins) + 1);
	}

	CFont* oldFont = NULL;

	rect.top += 1;

	if(text.GetLength() == 0)
	{		
		if(this != GetFocus() && m_strPromptText.GetLength() > 0 || (text.GetLength() == 0))
		{
			oldFont = dc.SelectObject(&m_fontPrompt);
			COLORREF color = dc.GetTextColor();
			dc.SetTextColor(m_colorPromptText);
			dc.DrawText(m_strPromptText, rect, DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_EDITCONTROL);
			dc.SetTextColor(color);
			dc.SelectObject(oldFont);
		}
	}
	else
	{
		oldFont = dc.SelectObject(GetFont());
		dc.DrawText(text, m_rectEdit, DT_SINGLELINE|DT_INTERNAL|DT_EDITCONTROL);
		dc.SelectObject(oldFont);
	}
}

void CSymbolEdit::OnSize(UINT nType, int cx, int cy)
{
	CEdit::OnSize(nType, cx, cy);

	RecalcLayout();
}

LRESULT CSymbolEdit::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	DefWindowProc(WM_SETFONT, wParam, lParam);

	RecalcLayout();

	return 0;
}

void CSymbolEdit::SetEditRect(CRect c_rect)
{
	m_rectEdit = c_rect;
	SetRect(c_rect);
}

void CSymbolEdit::SetBtnBMP(unsigned int c_UID,unsigned int c_UIDMouseIn)
{
	if (m_bBMP)
	{
		m_Bitmap.DeleteObject();
		m_BitmapMouseIn.DeleteObject();
	}
	m_bBMP = true;
	m_Bitmap.LoadBitmap(c_UID);
	m_BitmapMouseIn.LoadBitmap(c_UIDMouseIn);
	Invalidate(1);
}

void CSymbolEdit::SetState(BOOL c_bFocus)
{
	m_bFocus = c_bFocus;
	Invalidate(1);
}

void CSymbolEdit::SetBackColor(COLORREF c_colorBack)
{
	m_colorBack = c_colorBack;
}