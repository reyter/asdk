// CustomMenu.cpp : implementation file
//

#include "stdafx.h"
#include "CustomMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomMenu

CCustomMenu::CCustomMenu()
{
	m_IconIndex = 0;
	m_Index = 0;
}

CCustomMenu::~CCustomMenu()
{
}

/////////////////////////////////////////////////////////////////////////////
// CCustomMenu message handlers

void CCustomMenu::SetMenuImageList(CImageList *pImageList)
{
	this->pImageList = pImageList;
}

void CCustomMenu::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	if(lpDrawItemStruct->itemData == NULL)
		return;
	CDC *pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	MenuItemInfo *info=(MenuItemInfo*)(lpDrawItemStruct->itemData);
	CFont * pOldFont = pDC->SelectObject(gpSkinManager->GetMenuFont());
	UINT m_MenuID=info->m_MenuID;
	CString m_text=info->m_Text;
	UINT IconIndex=info->m_Icon;
	UINT m_state=lpDrawItemStruct->itemState;
	CRect rect=lpDrawItemStruct->rcItem;
	pDC->SetBkMode(TRANSPARENT);

	switch(m_MenuID)
	{
	case -2://顶层菜单
//		DrawTopMenu(pDC,rect,(m_state& ODS_SELECTED)||
//			(lpDrawItemStruct->itemAction & (ODA_SELECT)));
		DrawTopMenu(pDC,rect,(m_state & ODS_SELECTED)||(m_state & 0x0040));
		//这里也不要用(m_state& ODS_SELECTED)||
//			(lpDrawItemStruct->itemAction & (ODA_SELECT)));
		//(m_state&0x0040)也要加上，否则鼠标移入没反应
		//0x0040 ==ODS_HOTLIGHT
		DrawItemText(pDC,m_text,rect,FALSE,FALSE,TRUE);
		break;
	case -1://弹出菜单
		DrawComMenu(pDC,rect,(m_state & ODS_SELECTED)||(m_state & 0x0040),FALSE);
		DrawItemText(pDC,m_text,rect,FALSE,FALSE,FALSE);
		DrawMenuIcon(pDC,rect,IconIndex + 1);
		break;//记住一定要break，否则，呵呵，后果自负
	case 0:
		DrawSeparate(pDC,rect);
		break;
	default:
		//||(lpDrawItemStruct->itemAction & (ODA_SELECT))
		//这个不要加，加了之后会出现一直处于高亮显示
		if(m_state & ODS_GRAYED) //菜单不可用
		{
			DrawComMenu(pDC,rect,(m_state & ODS_SELECTED),TRUE);
			DrawItemText(pDC,m_text,rect,FALSE,TRUE,FALSE);
		}
		else
		{
			DrawComMenu(pDC,rect,(m_state & ODS_SELECTED),FALSE);
			DrawItemText(pDC,m_text,rect,FALSE,FALSE,FALSE);
		}

		if(m_state & ODS_CHECKED)//被 Check 
			DrawMenuIcon(pDC,rect,0);
		else
			DrawMenuIcon(pDC,rect,IconIndex + 1);

		break;
	}
	pDC->SelectObject(pOldFont);
}

void CCustomMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your code to determine the size of specified item
	int nHeight = gpSkinManager->GetFontHeight(gpSkinManager->GetMenuFont());
	int nWidth = gpSkinManager->GetFontWidth(gpSkinManager->GetMenuFont(),_T("最长的菜单项目是这样"));
	nHeight += 4;
	if(lpMeasureItemStruct->CtlType == ODT_MENU)
	{
		lpMeasureItemStruct->itemHeight = nHeight;
		lpMeasureItemStruct->itemWidth = nWidth;
		MenuItemInfo *info = (MenuItemInfo*)lpMeasureItemStruct->itemData;
		if(lpMeasureItemStruct->itemID == -2)
			lpMeasureItemStruct->itemWidth = info->m_Text.GetLength() * 8;
		else
			lpMeasureItemStruct->itemWidth = gpSkinManager->GetFontWidth(gpSkinManager->GetMenuFont(),info->m_Text) + 32;//nWidth;//info->m_Text.GetLength() * 8 + 32;
		if(info->m_MenuID == 0)
				lpMeasureItemStruct->itemHeight = 1;
	}
}

BOOL CCustomMenu::ChangeMenuItem(CMenu *pMenu, BOOL bTop = FALSE)
{
	if(pMenu != NULL && pMenu->m_hMenu)
	{
		int m_Count = pMenu->GetMenuItemCount();

		for( int i=0 ; i < m_Count ; i++ )
		{
			int m_ID = pMenu->GetMenuItemID(i);

			CMenu *pSubMenu = pMenu->GetSubMenu(i);

			if(m_ID < 0 && bTop)//顶层菜单
			{
				m_MenuInfoList[m_Index].m_MenuID = -2;
			}
			else if(pSubMenu && m_ID != -2 && !bTop)//弹出菜单
			{
				m_MenuInfoList[m_Index].m_MenuID = -1;
				m_MenuInfoList[m_Index].m_Icon = m_IconIndex;
				m_IconIndex++;
			}
			else if(m_ID == 0)//分隔线
				m_MenuInfoList[m_Index].m_MenuID = 0;
			else if(m_ID > 0)//普通菜单
			{
				m_MenuInfoList[m_Index].m_MenuID = m_ID;
				m_MenuInfoList[m_Index].m_Icon = m_IconIndex;
				m_IconIndex++;
			}

			pMenu->GetMenuString(i,m_MenuInfoList[m_Index].m_Text,MF_BYPOSITION);
			pMenu->ModifyMenu(i,MF_BYPOSITION|MF_OWNERDRAW|MF_STRING,
				m_MenuInfoList[m_Index].m_MenuID,(LPCTSTR)(&m_MenuInfoList[m_Index]));

			m_Index++;

			if(pSubMenu)
				ChangeMenuItem(pSubMenu);
		}
	}
	return TRUE;
}

void CCustomMenu::DrawSeparate(CDC *m_dc, CRect m_rect)
{
	m_rect.left = m_rect.left + 30;
	m_dc->Draw3dRect(m_rect,RGB(255,255,255),RGB(255,255,255));
}

void CCustomMenu::DrawComMenu(CDC *m_dc, CRect m_rect, BOOL bSelect,BOOL bGray)
{
	CRect rect(m_rect);
	//rect.DeflateRect(20,1,0,1);

	if(bSelect)
	{
		m_dc->FillSolidRect(rect,RGB(186,211,252));//208,235,255
	}
	else
	{
		if(bGray)
			m_dc->FillSolidRect(rect,RGB(240,238,225));
		else
			m_dc->FillSolidRect(rect,RGB(255,255,255));
	}
}

void CCustomMenu::DrawTopMenu(CDC *m_dc, CRect m_rect, BOOL bSelect)
{
	if(bSelect)
	{
		m_dc->SelectStockObject(BLACK_PEN);
		CRect rect(m_rect);
		m_dc->Rectangle(rect);
		rect.DeflateRect(1,1,1,1);
		m_dc->FillSolidRect(rect,RGB(255,235,181));
	}
	else
	{
		CRect rect;
		AfxGetMainWnd()->GetClientRect(&rect);
		rect.left = 390;
		rect.bottom = m_rect.bottom;
		rect.top = m_rect.top;
		rect.right += 4;
		m_dc->FillSolidRect(m_rect,RGB(186,211,252));
		m_dc->FillSolidRect(rect,RGB(186,211,252));//画出射剩余的部分
	}
}

void CCustomMenu::DrawItemText(CDC *m_dc, CString str, CRect m_rect,BOOL m_Com,
							   BOOL bGray,BOOL bTop)
{
	if(bGray)
		m_dc->SetTextColor(RGB(127,127,127));

	CRect rect(m_rect);

	if(m_Com)
		rect.DeflateRect(36,0,0,0);

	if(bTop)
		m_dc->DrawText(str,rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	else
		m_dc->DrawText(str,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
}

void CCustomMenu::DrawMenuIcon(CDC *m_dc,CRect m_rect, UINT IconIndex)
{
	//pImageList->Draw(m_dc,IconIndex,CPoint(m_rect.left+2,m_rect.top+2),
	//	ILD_TRANSPARENT);
	//ILD_MASK不要加
}
