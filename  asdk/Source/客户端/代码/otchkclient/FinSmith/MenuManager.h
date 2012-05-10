#pragma once
#include <vector>
#include "atltypes.h"

class CMenuManager
{
public:
	CMenuManager(void);
	~CMenuManager(void);
	// 菜单区域
	CRect m_rectArea;
	// 菜单间距
	int m_nDistance;
	CFont *m_pTextFont;
	COLORREF m_clText;
	std::vector<CString>	m_vpNames;
	std::vector<int>		m_vpMenuIDs;
	std::vector<CRect>		m_vpMenuRects;
	// 设置区域
	void SetArea(CRect c_rect);
	// //设置字体
	void SetTextFont(CFont * c_pFont);
	//设置文字颜色
	void SetTextColor(COLORREF);
	// 设置间隔
	int SetDistance(int c_nDis);
	// 绘制
	void Draw(CDC * c_pDC);
	// 增加菜单项目
	int AddMenu(CString c_strName, int c_nMenuID);
	//检查是否点中菜单
	int CheckMenu(CPoint c_point,CRect &c_rect);
};
