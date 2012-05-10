#include "StdAfx.h"
#include "TrdGrid.h"

CTrdGrid::CTrdGrid(void)
{
}

CTrdGrid::~CTrdGrid(void)
{
}

void CTrdGrid::OnMDataItemLDbClick(int rowID,int columnID)
{
	SStock * p = (SStock *)GetRowData(rowID);
	if (p)
	{
		::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,0,DWORD_PTR(p));
	}
}

void CTrdGrid::OnPaintDataItem(CDC &cMemDc,const CRect& rcDrawOnRect,int rowID,int columnID)
{
	CString strText;
	CRect rect;
	rect = rcDrawOnRect;
	COLORREF cl = cMemDc.SetTextColor(RGB(0,0,0));
	CFont * pOldFont = cMemDc.SelectObject(gpSkinManager->m_pFontReport);
	GetItemText(rowID,columnID,strText);
	CSize size = cMemDc.GetTextExtent(strText,strText.GetLength());	
	if (columnID == 4)
		cMemDc.DrawText(strText,rect,DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX|DT_END_ELLIPSIS);
	else
		cMemDc.DrawText(strText,rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX|DT_END_ELLIPSIS);
	cMemDc.SetTextColor(cl);
	cMemDc.SelectObject(pOldFont);
}