#pragma once
#include <vector>
#include "atltypes.h"

class CMenuManager
{
public:
	CMenuManager(void);
	~CMenuManager(void);
	// �˵�����
	CRect m_rectArea;
	// �˵����
	int m_nDistance;
	CFont *m_pTextFont;
	COLORREF m_clText;
	std::vector<CString>	m_vpNames;
	std::vector<int>		m_vpMenuIDs;
	std::vector<CRect>		m_vpMenuRects;
	// ��������
	void SetArea(CRect c_rect);
	// //��������
	void SetTextFont(CFont * c_pFont);
	//����������ɫ
	void SetTextColor(COLORREF);
	// ���ü��
	int SetDistance(int c_nDis);
	// ����
	void Draw(CDC * c_pDC);
	// ���Ӳ˵���Ŀ
	int AddMenu(CString c_strName, int c_nMenuID);
	//����Ƿ���в˵�
	int CheckMenu(CPoint c_point,CRect &c_rect);
};
