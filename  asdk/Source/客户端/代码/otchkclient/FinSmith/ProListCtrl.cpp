// CProListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ProListCtrl.h"
#include "resource.h"


// CIndexListCtrl

IMPLEMENT_DYNAMIC(CProListCtrl, CListCtrl)

CProListCtrl::CProListCtrl()
{
	for(int i=0; i<30; i++)
	{
		m_lFieldFormat[i] = 0;
		m_lFieldNegative[i] = false;
	}
}

CProListCtrl::~CProListCtrl()
{
}


BEGIN_MESSAGE_MAP(CProListCtrl, CListCtrl)
	ON_WM_MEASUREITEM()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CProListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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
	//HGDIOBJ hobj;// = pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	CFont *pOldFont = pDC->SelectObject(gpSkinManager->m_pFontSmall);
	CRect   rcBack   =   lpDIS->rcItem;  
    rcBack.right += 4;
	pDC->SetBkMode(TRANSPARENT);   

	COLORREF clNormal = RGB(0,0,0);
	int nSel = this->GetSelectionMark();

	if(   bHighlight || (nSel == -1 && lpDIS->itemID==0) || lpDIS->itemID==nSel)
	{   
		//pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT)); 
		//pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));       
		pDC->FillRect(rcBack,   &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));  
		clNormal = RGB(255,255,0);	
	}   
	else   
	{   
		if   (lpDIS->itemID%2   ==0)   
		{   
			pDC->FillRect(rcBack,   &CBrush(DEFAULT_LINE_1_COLOR));   
		}   
		else   
		{   
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

		for   (int   i   =   0;   i   <   GetHeaderCtrl()->GetItemCount();   i++) 
		{   //循环得到文本   
			CRect   rcItem;   
			if   (   !GetSubItemRect(lpDIS->itemID,   i,   LVIR_LABEL,   rcItem   ))   
				continue; 
			szText   =   GetItemText(   lpDIS->itemID,   i   );  

			pDC->SetTextColor(clNormal);

			rcItem.bottom -= 2;
			if (GetFieldFormat(i) & DT_RIGHT)
				rcItem.right -= 4;
			if(szText == "-")
			{
				pDC->DrawText(szText,   lstrlen(szText),   &rcItem,   DT_CENTER|DT_BOTTOM|DT_NOPREFIX|DT_SINGLELINE|DT_END_ELLIPSIS); 
			}
			else
			{
				DrawColorText(pDC,rcItem,szText,DT_LEFT|DT_BOTTOM|DT_NOPREFIX|DT_SINGLELINE|DT_END_ELLIPSIS,clNormal);
			}
				
		}   
	}   
	//pDC->SelectObject(hobj);
	pDC->SelectObject(pOldFont);
}

void CProListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

BOOL CProListCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return CListCtrl::OnEraseBkgnd(pDC);
	int i;	
	CRect rect,r,rw;
	//CString strInfo;
	
	GetClientRect(&rect);
	CBrush brush1,brush2;
	brush1.CreateSolidBrush(DEFAULT_LINE_1_COLOR);
	brush2.CreateSolidBrush(DEFAULT_LINE_2_COLOR);
	this->GetHeaderCtrl()->GetWindowRect(&rw);
	r = rect;
	r.top += 1 + rw.Height();
	r.bottom = r.top + LIST_HEIGHT;
	i = 0;
	
	while(r.top < rect.bottom)
	{
		
		if (this->GetHeaderCtrl()->IsWindowVisible())
		{
			if (i % 2 != 0)
				pDC->FillRect(r,&brush2);
			else
				pDC->FillRect(r,&brush1);
		}
		else
		{
			if (i % 2 != 0)
				pDC->FillRect(r,&brush1);
			else
				pDC->FillRect(r,&brush2);
		}
		r.bottom += LIST_HEIGHT;
		r.top += LIST_HEIGHT;
		i++;
	}
	
	brush1.DeleteObject();
	brush2.DeleteObject();
	return true;
	//return CListCtrl::OnEraseBkgnd(pDC);
}

void CProListCtrl::DrawColorText(CDC * c_pDC,CRect c_rect,CString c_strText,long c_lFormat,COLORREF c_clDef)
{
	CRect rectDraw;
	rectDraw = c_rect;

	CString strDraw;
	strDraw = c_strText;
	int nFind,nFindEnd;
	nFind = strDraw.Find(_T("A_"));
	nFindEnd = strDraw.Find(_T("_A"));
	while(nFind >= 0 && nFindEnd >= 0)
	{
		CString strLeft,strRight,strMid;
		strLeft = strDraw.Left(nFind);
		strRight = strDraw.Right(strDraw.GetLength() - nFindEnd - 2);
		strMid = strDraw.Right(strDraw.GetLength() - nFind - 2);
		strMid = strMid.Left(nFindEnd - nFind - 2);
		strDraw= strRight;
		nFind = strDraw.Find(_T("A_"));
		nFindEnd = strDraw.Find(_T("_A"));
		c_pDC->SetTextColor(c_clDef);
		c_pDC->DrawText(strLeft,strLeft.GetLength(),rectDraw,c_lFormat);//DT_LEFT|DT_NOPREFIX|DT_SINGLELINE|DT_END_ELLIPSIS);		
		CSize size = c_pDC->GetTextExtent(strLeft,strLeft.GetLength());
		rectDraw.left += size.cx;
		if (rectDraw.left > rectDraw.right)
			return;
		c_pDC->SetTextColor(RGB(0,0,255));
		c_pDC->DrawText(strMid,strMid.GetLength(),rectDraw,c_lFormat);//DT_LEFT|DT_NOPREFIX|DT_SINGLELINE|DT_END_ELLIPSIS);
		size = c_pDC->GetTextExtent(strMid,strMid.GetLength());
		rectDraw.left += size.cx;
		if (rectDraw.left > rectDraw.right)
			return;
	}
	c_pDC->SetTextColor(c_clDef);
	c_pDC->DrawText(strDraw,strDraw.GetLength(),rectDraw,c_lFormat);//DT_LEFT|DT_NOPREFIX|DT_SINGLELINE|DT_END_ELLIPSIS);
}

void CProListCtrl::SetFieldFormat(int c_nField,long c_lFormat)
{
	if (c_nField > 29)
		return;
	m_lFieldFormat[c_nField] = c_lFormat;
}
long CProListCtrl::GetFieldFormat(int c_nField)
{
	if (c_nField > 29)
		return 0;
	else
		return m_lFieldFormat[c_nField];
}

void CProListCtrl::SetFieldNegative(int c_nField,bool c_b)
{
	if (c_nField > 29)
		return;
	m_lFieldNegative[c_nField] = c_b;
}
bool CProListCtrl::GetFieldNegative(int c_nField)
{
	if (c_nField > 29)
		return 0;
	else
		return m_lFieldNegative[c_nField];
}
