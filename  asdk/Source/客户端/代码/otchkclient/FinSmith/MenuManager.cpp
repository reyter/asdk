#include "StdAfx.h"
#include "MenuManager.h"

CMenuManager::CMenuManager(void)
: m_nDistance(0)
, m_pTextFont(NULL)
{
	m_clText = RGB(255,255,255);
}

CMenuManager::~CMenuManager(void)
{
}

// ��������
void CMenuManager::SetArea(CRect c_rect)
{
	m_rectArea = c_rect;
}

// //��������
void CMenuManager::SetTextFont(CFont * c_pFont)
{
	m_pTextFont = c_pFont;
}

//����������ɫ
void CMenuManager::SetTextColor(COLORREF c_cl)
{
	m_clText = c_cl;
}

// ���ü��
int CMenuManager::SetDistance(int c_nDis)
{
	m_nDistance = c_nDis;
	return 0;
}

// ����
void CMenuManager::Draw(CDC * c_pDC)
{
	CFont * pFont = NULL;
	if (m_pTextFont)
		pFont = c_pDC->SelectObject(gpSkinManager->GetMenuFont());
	c_pDC->SetTextColor(m_clText);
	int nMode = c_pDC->SetBkMode(TRANSPARENT);
	CRect r = m_rectArea;
	CSize  size;
	int nLastButtonWidth = 0;
	size = c_pDC->GetTextExtent(m_vpNames.at(m_vpNames.size()-1));
	nLastButtonWidth = size.cx + m_nDistance;//���һ����ť�Ŀ�ȣ���֤���һ����ť��ʾ��
	for(int n=0; n<m_vpNames.size(); n++)
	{
		size = c_pDC->GetTextExtent(m_vpNames.at(n));
		if (r.left + size.cx > r.right)
			break;
		if (n != m_vpNames.size()-1 && r.left + size.cx + nLastButtonWidth + m_nDistance > r.right)//�Ѿ��Ų������һ����ť������ʾ�ΰ�ť
		{
			m_vpMenuRects.at(n).SetRect(0,0,0,0);
			continue;
		}
		c_pDC->DrawText(m_vpNames.at(n),r,DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		m_vpMenuRects.at(n).SetRect(r.left,r.top,r.left + size.cx,r.bottom);
		r.left += size.cx + m_nDistance;
	}
	c_pDC->SetBkMode(nMode);
	if (m_pTextFont)
		c_pDC->SelectObject(pFont);
}

// ���Ӳ˵���Ŀ
int CMenuManager::AddMenu(CString c_strName, int c_nMenuID)
{
	m_vpNames.push_back(c_strName);
	m_vpMenuIDs.push_back(c_nMenuID);
	m_vpMenuRects.push_back(CRect(0,0,0,0));
	return m_vpNames.size();
}

int CMenuManager::CheckMenu(CPoint c_point,CRect &c_rect)
{
	for(int n=0; n<m_vpMenuRects.size(); n++)
	{
		if (m_vpMenuRects.at(n).PtInRect(c_point))
		{
			c_rect = m_vpMenuRects.at(n);
			return m_vpMenuIDs.at(n);
		}
	}
	return -1;
}
