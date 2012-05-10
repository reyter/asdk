// KindComboBox.cpp : ʵ���ļ�
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



// CKindComboBox ��Ϣ�������



void CKindComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  ������Ĵ����Ի���ָ����
	LPDRAWITEMSTRUCT   lpDIS   =   lpDrawItemStruct;   
	CDC*   pDC   =   CDC::FromHandle(lpDIS->hDC);   
	
///-    BOOL	bShowNews;
	BOOL   bHighlight   =((lpDIS->itemState   &   LVIS_DROPHILITED)||((lpDIS->itemState   &   LVIS_SELECTED)   &&     
	((GetFocus()   ==   this)||   (GetStyle()   &   LVS_SHOWSELALWAYS))));   
    
	if (lpDIS->itemState > 0)
		bHighlight = TRUE;

	//   ���ı�����	
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
		strText = _T("ȫ��");
	
	CRect rect;
	rect = lpDIS->rcItem;
	if (strText == _T("��˾����") || strText == _T("��ҵ����"))
	{
		pDC->SelectObject(gpSkinManager->m_pFontThick);
		pDC->DrawText(strText,rect,DT_CENTER|DT_BOTTOM|DT_SINGLELINE);
	}
	else
		pDC->DrawText(strText,rect,DT_LEFT|DT_BOTTOM|DT_SINGLELINE);
	pDC->SelectObject(pOldFont);
}
