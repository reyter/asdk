// LedComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "SkinComboBox.h"


// CSkinComboBox

IMPLEMENT_DYNAMIC(CSkinComboBox, CComboBox)

CSkinComboBox::CSkinComboBox()
{
	m_brush.CreateSolidBrush(gpSkinManager->getColor(BKCOLOR));
}

CSkinComboBox::~CSkinComboBox()
{
	m_brush.DeleteObject();
}


BEGIN_MESSAGE_MAP(CSkinComboBox, CComboBox)
	ON_WM_MEASUREITEM()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CSkinComboBox 消息处理程序



void CSkinComboBox::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值	
	CComboBox::OnMeasureItem(nIDCtl, lpMeasureItemStruct);	
}

void CSkinComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	CDC *pDC=CDC::FromHandle(lpDrawItemStruct->hDC); 
	int nSaveDC=pDC->SaveDC(); 
	CRect itemRect = lpDrawItemStruct->rcItem; 
	int nItem = lpDrawItemStruct->itemID; 
      
	if(lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) 
	{ 
		DrawItemBk(pDC,itemRect,nItem); //画正常状态item的背景 
		//DrawItemImage(pDC,itemRect,nItem); 
		DrawItemText(pDC,itemRect,nItem);//画正常状态item文 
	} 

	if((lpDrawItemStruct->itemState & ODS_SELECTED) && 
		(lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)) ) 
	{ 
		DrawItemBkHot(pDC,itemRect,nItem); 
		//DrawItemImage(pDC,itemRect,nItem); 
		DrawItemText(pDC,itemRect,nItem,true); 
	} 

	if(!(lpDrawItemStruct->itemState & ODS_SELECTED) && 
		(lpDrawItemStruct->itemAction & ODA_SELECT ) ) 
	{ 
		DrawItemBk(pDC,itemRect,nItem); 
		//DrawItemImage(pDC,itemRect,nItem); 
		DrawItemText(pDC,itemRect,nItem); 
	} 

	pDC->RestoreDC(nSaveDC); 

}

void CSkinComboBox::SetEditRect(int c_nLeft,int c_nRight)
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

void CSkinComboBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CComboBox::OnPaint()
	CRect rectBk; 
	GetClientRect(rectBk); 

	//DrawBorder(&dc,rectBk);
	CRect rb;
	rb = rectBk;
	rb.top += 1;
	rb.left += 1;
	rb.right -= 1;
	rb.bottom -= 1;
	DrawEditItemBk(&dc,rectBk); 
	DrawDownButton(&dc,rectBk); //与按钮一样,有正常,HOT,按下和非激活状态 		

	if ( CComboBox::GetCount() >0 && CComboBox::GetCurSel() >= 0 ) 
	{ 
		//int nState = CS_NORMAL; 
		CSize sz(0,0);
		int nItem = CComboBox::GetCurSel(); 
		//GetComboState()== CS_SELECT ? nState = CS_DISABLED : nState = CS_NORMAL ; 

		//CString strItemText(_T("")); 
		//GetLBText(nItem,strItemText);
		//rectBk.left += sz.cx + 4;
		//dc.DrawText(strItemText,rectBk,DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		int nBX = GetSystemMetrics(SM_CXVSCROLL); 
		rectBk.right -= nBX + 4;
		DrawItemText(&dc,rectBk,nItem); 		
		//DrawItemImage(&dc,rectBk,nItem,GetItemImage(nItem),nState); 
	} 	
}

void CSkinComboBox::DrawItemBk(CDC * c_pDC,CRect c_itemRect,int c_nItem)
{
	CBrush brush(gpSkinManager->getColor(EDITBKCOLOR));
	c_pDC->FillRect(c_itemRect,&brush);
}

void CSkinComboBox::DrawEditItemBk(CDC * c_pDC,CRect c_itemRect)
{
	CBrush brush(gpSkinManager->getColor(EDITBKCOLOR));
	c_pDC->FillRect(c_itemRect,&brush);
}

void CSkinComboBox::DrawItemBkHot(CDC * c_pDC,CRect c_itemRect,int c_nItem)
{
	c_pDC->FillRect(c_itemRect,   &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
}

void CSkinComboBox::DrawItemImage(CDC * c_pDC,CRect c_itemRect,int nItem)
{
	if (nItem > 2 && nItem < 0)
		return;
/*
	CRect r;
	r = c_itemRect;
	CSize sz = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(unLed));
	r.right = r.left + sz.cx;
	r.top += (r.Height() - sz.cy)/2;
	gpSkinManager->FillRectImage(gpSkinManager->GetBitmap(unLed),c_pDC,r);	*/
}

void CSkinComboBox::DrawItemText(CDC * c_pDC,CRect c_itemRect,int c_nItem,bool c_bHot)
{
	int nOld = c_pDC->SetBkMode(TRANSPARENT);
	CFont *pOldFont = c_pDC->SelectObject(gpSkinManager->m_pFontGraph);
	COLORREF cl;
	if (c_bHot)
		cl = c_pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	else
		cl = c_pDC->SetTextColor(gpSkinManager->getColor(EDITTEXTCOLOR));
	CRect rect = c_itemRect;
	rect.left += 4;
	CString strText;
	GetLBText(c_nItem,strText);
	if (strText.IsEmpty())
		strText = _T("全部");
	if (strText == _T("公司报告") || strText == _T("行业报告"))
	{
		c_pDC->SelectObject(gpSkinManager->m_pFontThick);
		c_pDC->DrawText(strText,rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_WORDBREAK);
	}
	else
		c_pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_WORDBREAK);
	
	c_pDC->SelectObject(pOldFont);	
	c_pDC->SetTextColor(cl);
	c_pDC->SetBkMode(nOld);
}

void CSkinComboBox::DrawBorder(CDC * c_pDC,CRect c_rect)
{
	CPen pen(PS_SOLID,1,RGB(0,0,255));

	CPen * pOld = c_pDC->SelectObject(&pen);	
	c_pDC->Rectangle(c_rect);
	c_pDC->SelectObject(pOld);
}

void CSkinComboBox::DrawDownButton(CDC * c_pDC,CRect c_rectBk)
{	
	int nW = GetSystemMetrics(SM_CXVSCROLL); 
	nW = GetSystemMetrics(SM_CYHSCROLL); 
	int nBX = GetSystemMetrics(SM_CXBORDER); 
	int nBY = GetSystemMetrics(SM_CYBORDER); 

	CRect r;
	r = c_rectBk;
	r.left = r.right - nW - nBX;
	r.right = r.left + nW;
	r.top = r.top + nBY + (r.Height() - nBY * 2 - nW)/2;
	r.bottom = r.top + nW;
	
	gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(V_DOWN),c_pDC,r);	
}
HBRUSH CSkinComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	//COMBOBOXINFO cbinfo;
	//GetComboBoxInfo(&cbinfo);
	if( nCtlColor == CTLCOLOR_LISTBOX || nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_MSGBOX )	
	{
		pDC->SetBkColor(gpSkinManager->getColor(EDITBKCOLOR));
		pDC->SetTextColor(gpSkinManager->getColor(EDITTEXTCOLOR));
		hbr = m_brush;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CSkinComboBox::ResetSkin()
{
	m_brush.DeleteObject();
	m_brush.CreateSolidBrush(gpSkinManager->getColor(EDITBKCOLOR));
}
BOOL CSkinComboBox::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (HIWORD(wParam) == WM_KEYUP && LOWORD(wParam) == VK_RETURN)
	{
		ShowDropDown(FALSE);
		return TRUE;
	}
	if ( HIWORD(wParam) == EN_CHANGE )
	{
		//show drop menu
/*		ShowDropDown(TRUE); //使用这个鼠标会不见
		::SetCursor(::LoadCursor(NULL,IDC_ARROW)); //重新显示鼠标
*/
		// Save	the state of the edit control
		CString windowtext;
		GetWindowText(windowtext);

		//if no text,return
		if ( windowtext.GetLength()==0)
		{
			SetCurSel(-1);
			return true;
		}

		// Currently selected range
		DWORD dwCurSel = GetEditSel();
		WORD start = LOWORD(dwCurSel);
		WORD end = HIWORD(dwCurSel);

		// Perform actual completion 
		CString ItemText;
		CString TempWindowText; //use for MakeUpper(); 
		int FindItem;

		int bestindex = -1;
		int bestfrom = INT_MAX;
		for ( int x = 0; x < GetCount(); x++ )
		{
			GetLBText(x,ItemText);

			FindItem = ItemText.Find(windowtext);

			//搜索结果不区分大小写，若搜索结构需要区分大小写，请去掉这一段
			if(FindItem==-1)
			{
				ItemText.MakeUpper(); 
				TempWindowText=windowtext;
				TempWindowText.MakeUpper();
				FindItem = ItemText.Find(TempWindowText);
			}

			if ( FindItem != -1 && FindItem < bestfrom )
			{
				bestindex = x;
				bestfrom = FindItem;
			}
		}

		if ( bestindex==-1) //no match item,so select none
			SetCurSel(-1); 
		else if (GetCurSel() != bestindex)
		{
			// Select the matching entry in the list
			SetCurSel(bestindex);
		}
		if (bestindex != -1)
		{
		ShowDropDown(TRUE); //使用这个鼠标会不见
		::SetCursor(::LoadCursor(NULL,IDC_ARROW)); //重新显示鼠标
		}
		else
		{
		ShowDropDown(FALSE); //使用这个鼠标会不见
		::SetCursor(::LoadCursor(NULL,IDC_ARROW)); //重新显示鼠标
		}
		// Restore the edit control
		SetWindowText(windowtext);
		SetEditSel(start,end);

		return true;
	} 

	return CComboBox::OnCommand(wParam, lParam);
}

BOOL CSkinComboBox::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->wParam == VK_RETURN)
	{		
		ShowDropDown(FALSE);
		return   TRUE;   
	}

	return CComboBox::PreTranslateMessage(pMsg);
}
