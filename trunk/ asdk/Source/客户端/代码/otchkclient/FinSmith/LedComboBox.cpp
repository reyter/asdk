// LedComboBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinSmith.h"
#include "LedComboBox.h"


// CLedComboBox

IMPLEMENT_DYNAMIC(CLedComboBox, CComboBox)

CLedComboBox::CLedComboBox()
{
	m_brush.CreateSolidBrush(gpSkinManager->getColor(BKCOLOR));
}

CLedComboBox::~CLedComboBox()
{
}


BEGIN_MESSAGE_MAP(CLedComboBox, CComboBox)
	ON_WM_MEASUREITEM()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CLedComboBox ��Ϣ�������



void CLedComboBox::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ	
	//lpMeasureItemStruct->itemHeight = 24;
	CComboBox::OnMeasureItem(nIDCtl, lpMeasureItemStruct);	
}

void CLedComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  ������Ĵ����Ի���ָ����
	CDC *pDC=CDC::FromHandle(lpDrawItemStruct->hDC); 
	int nSaveDC=pDC->SaveDC(); 
	CRect itemRect = lpDrawItemStruct->rcItem; 
	int nItem = lpDrawItemStruct->itemID; 
      
	if(lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) 
	{ 
		DrawItemBk(pDC,itemRect,nItem); //������״̬item�ı��� 
		DrawItemImage(pDC,itemRect,nItem); 
		DrawItemText(pDC,itemRect,nItem);//������״̬item�� 
	} 

	if((lpDrawItemStruct->itemState & ODS_SELECTED) && 
		(lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)) ) 
	{ 
		DrawItemBkHot(pDC,itemRect,nItem); 
		DrawItemImage(pDC,itemRect,nItem); 
		DrawItemText(pDC,itemRect,nItem,true); 
	} 

	if(!(lpDrawItemStruct->itemState & ODS_SELECTED) && 
		(lpDrawItemStruct->itemAction & ODA_SELECT ) ) 
	{ 
		DrawItemBk(pDC,itemRect,nItem); 
		DrawItemImage(pDC,itemRect,nItem); 
		DrawItemText(pDC,itemRect,nItem); 
	} 

	pDC->RestoreDC(nSaveDC); 

}

void CLedComboBox::SetEditRect(int c_nLeft,int c_nRight)
{
	CRect rect;
	GetClientRect(rect);
	rect.left += c_nLeft;
	
	CEdit *pEdit = (CEdit *)GetWindow(GW_CHILD);
	int nW = GetSystemMetrics(SM_CXVSCROLL); 
	nW = GetSystemMetrics(SM_CYHSCROLL); 
	rect.right -= nW;
	if (pEdit)
	{
		CRect rW;
		pEdit->GetWindowRect(rW);
		rect.top += (rect.Height() - rW.Height()) / 2;
		rect.bottom = rect.top + rW.Height();
			
		//pEdit->SetRect(rect);
		pEdit->MoveWindow(rect);		
	}
}

void CLedComboBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CComboBox::OnPaint()
	CRect rectBk; 
	GetClientRect(rectBk); 

	DrawBorder(&dc,rectBk); 
	DrawEditItemBk(&dc,rectBk); 
	DrawDownButton(&dc,rectBk); //�밴ťһ��,������,HOT,���ºͷǼ���״̬ 

	if ( CComboBox::GetCount() >0 && CComboBox::GetCurSel() >= 0 ) 
	{ 
		//int nState = CS_NORMAL; 
		CSize sz(0,0);
		int nItem = CComboBox::GetCurSel(); 
		//GetComboState()== CS_SELECT ? nState = CS_DISABLED : nState = CS_NORMAL ; 
		if (nItem >= 0 && nItem <= 2)
		{
			int unLed = m_nLed[nItem];

			CRect r;
			r = rectBk;
			//sz = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(unLed));
			sz = gpSkinManager->GetBmpSize(unLed);
			r.right = r.left + sz.cx;
			r.top += (r.Height() - sz.cy)/2;
			//gpSkinManager->FillRectImage(gpSkinManager->GetBitmap(unLed),&dc,r);
			gpSkinManager->FillRectImage(unLed,&dc,r);
		}
		
		CString strItemText(_T("")); 
		//GetLBText(nItem,strItemText);
		rectBk.left += sz.cx + 2;
		//dc.SetBkMode(TRANSPARENT);
		//COLORREF cl = dc.SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));
		dc.DrawText(strItemText,rectBk,DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		//dc.SetTextColor(cl);
		//DrawItemText(&dc,rectBk,nItem,strItemText,nState); 
		//DrawItemImage(&dc,rectBk,nItem,GetItemImage(nItem),nState); 
	} 
}

void CLedComboBox::DrawItemBk(CDC * c_pDC,CRect c_itemRect,int c_nItem)
{
	CBrush brush(gpSkinManager->getColor(EDITBKCOLOR));
	c_pDC->FillRect(c_itemRect,&brush);
}

void CLedComboBox::DrawEditItemBk(CDC * c_pDC,CRect c_itemRect)
{
	CBrush brush(gpSkinManager->getColor(EDITBKCOLOR));
	c_pDC->FillRect(c_itemRect,&brush);
}

void CLedComboBox::DrawItemBkHot(CDC * c_pDC,CRect c_itemRect,int c_nItem)
{
	//COLORREF cl1 = c_pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	//COLORREF cl2 = c_pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
	c_pDC->FillRect(c_itemRect,   &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
}

void CLedComboBox::DrawItemImage(CDC * c_pDC,CRect c_itemRect,int nItem)
{
	if (nItem > 2 && nItem < 0)
		return;
	int unLed = m_nLed[nItem];

	CRect r;
	r = c_itemRect;
	//CSize sz = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(unLed));
	CSize sz = gpSkinManager->GetBmpSize(unLed);

	r.right = r.left + sz.cx;
	r.top += (r.Height() - sz.cy)/2;
	//gpSkinManager->FillRectImage(gpSkinManager->GetBitmap(unLed),c_pDC,r);	
	gpSkinManager->FillRectImage(unLed,c_pDC,r);	
}

void CLedComboBox::DrawItemText(CDC * c_pDC,CRect c_itemRect,int c_nItem,bool c_bHot)
{
	CSize sz = gpSkinManager->GetBmpSize(m_nLed[0]);
	int nOld = c_pDC->SetBkMode(TRANSPARENT);
	COLORREF cl;
	if (c_bHot)
		cl = c_pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	else
		cl = c_pDC->SetTextColor(gpSkinManager->getColor(EDITTEXTCOLOR));
	
	CRect rect = c_itemRect;
	rect.left += sz.cx + 4;
	CString strText;
	GetLBText(c_nItem,strText);
	c_pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	c_pDC->SetTextColor(cl);
	c_pDC->SetBkMode(nOld);
}

void CLedComboBox::DrawBorder(CDC * c_pDC,CRect c_rect)
{
	CPen pen(PS_SOLID,1,RGB(0,0,255));

	CPen * pOld = c_pDC->SelectObject(&pen);
	c_pDC->Rectangle(c_rect);
	c_pDC->SelectObject(pOld);
}

void CLedComboBox::DrawDownButton(CDC * c_pDC,CRect c_rectBk)
{	
	int nW = GetSystemMetrics(SM_CXVSCROLL); 
	nW = GetSystemMetrics(SM_CYHSCROLL); 
	
	CRect r;
	r = c_rectBk;
	r.left = r.right - nW;
	
	r.top = r.top + (r.Height() - nW)/2;
	r.bottom = r.top + nW;

	gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(V_DOWN),c_pDC,r);	
}
HBRUSH CLedComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if( nCtlColor == CTLCOLOR_LISTBOX || nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_MSGBOX )	
	{
		pDC->SetBkColor(gpSkinManager->getColor(EDITBKCOLOR));
		pDC->SetTextColor(gpSkinManager->getColor(EDITTEXTCOLOR));
		hbr = m_brush;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CLedComboBox::ResetSkin()
{
	m_brush.DeleteObject();
	m_brush.CreateSolidBrush(gpSkinManager->getColor(EDITBKCOLOR));
}