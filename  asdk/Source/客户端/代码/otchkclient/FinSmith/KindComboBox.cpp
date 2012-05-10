// KindComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "KindComboBox.h"


// CKindComboBox

IMPLEMENT_DYNAMIC(CKindComboBox, CComboBox)

CKindComboBox::CKindComboBox()
{

}

CKindComboBox::~CKindComboBox()
{
}


BEGIN_MESSAGE_MAP(CKindComboBox, CComboBox)
END_MESSAGE_MAP()



// CKindComboBox 消息处理程序



void CKindComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项
	LPDRAWITEMSTRUCT   lpDIS   =   lpDrawItemStruct;   
	CDC*   pDC   =   CDC::FromHandle(lpDIS->hDC);   
	
///-    BOOL	bShowNews;
	BOOL   bHighlight   =((lpDIS->itemState   &   LVIS_DROPHILITED)||((lpDIS->itemState   &   LVIS_SELECTED)   &&     
	((GetFocus()   ==   this)||   (GetStyle()   &   LVS_SHOWSELALWAYS))));   
    
	if (lpDIS->itemState > 0)
		bHighlight = TRUE;

	//   画文本背景	
	CFont *pOldFont = pDC->SelectObject(gpSkinManager->m_pFontGraph);
	CRect   rcBack   =   lpDIS->rcItem;   
	pDC->SetBkMode(TRANSPARENT);  
	if(   bHighlight   ) 
	{   
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));   
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));       		
		pDC->FillRect(rcBack,   &CBrush(gpSkinManager->getColor(LISTSELBACK)));
	}   
	else   
	{   
		pDC->SetTextColor(RGB(0,0,0));
		
		if   (lpDIS->itemID%2   ==0)   
		{   
				//pDC->SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));
				//pDC->FillRect(rcBack,   &CBrush(DEFAULT_LINE_1_COLOR));
				pDC->FillRect(rcBack,   &CBrush(DEFAULT_LINE_1_COLOR));
		}   
		else   
		{   
				//pDC->SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));
				pDC->FillRect(rcBack,   &CBrush(DEFAULT_LINE_1_COLOR));   
		}
	}   
	
	CString strText;	
	//SIndustry * pItem = (SIndustry *)this->GetItemData(lpDIS->itemID);
	//if (pItem)
	//	strText = pItem->strName;
	//else
	GetLBText(lpDIS->itemID,strText);
	if (strText.IsEmpty())
		strText = _T("全部");
	
	CRect rect;
	rect = lpDIS->rcItem;
	if (strText == _T("公司报告") || strText == _T("行业报告"))
	{
		pDC->SelectObject(gpSkinManager->m_pFontThick);
		pDC->DrawText(strText,rect,DT_CENTER|DT_BOTTOM|DT_SINGLELINE);
	}
	else
		pDC->DrawText(strText,rect,DT_LEFT|DT_BOTTOM|DT_SINGLELINE);
	pDC->SelectObject(pOldFont);
}
