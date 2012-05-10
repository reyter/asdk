#pragma once
#include "atltypes.h"

// CBaseDraw 命令目标
class  CPieChartPiece
{
public:
	CPieChartPiece() {;};
	~CPieChartPiece()
	{
	}	
	double		m_dValue;//市值	
	double		m_dPercent;//比例
	double		m_dAngle;//度数
	CPoint		m_pointa;
	CPoint		m_pointb;
	CPoint		m_pointaBottom;
	CPoint		m_pointbBottom;
	COLORREF	m_colorBack;
	COLORREF	m_colorText;	
	int			m_iTitleX;
	int			m_iTitleY;
	CString		m_strTitle;
};

class CBaseDraw// : public CObject
{
public:
	CBaseDraw();
	virtual ~CBaseDraw();
public:
	// 画图DC
	CDC *m_pDC;
public:
	//颜色
	COLORREF	m_colorRef[100];
	COLORREF	m_colorRectBk;
	// 画图区域
	unsigned short	m_uiType;//图形类型,默认为Pie,1是矩形图
	CRect m_rectText;
	int		m_nStartX;
	int		m_nStartY;
	CRect m_rectDraw;
	CRect m_rectDrawTop;//上面的矩形
	CRect m_rectDrawBottom;//下面的矩形
	CPoint m_point0;//0度点坐标
	CPoint m_point180;//180度坐标
	CPoint m_point0Bottom;//下面的0度点坐标
	CPoint m_point180Bottom;//下面的180度点坐标
	CPoint m_pointZero;/*零点,x,y轴*/
	int		m_nMaxStation;//最低点的位置
	int		m_nMinStation;//最高点的位置
	int		m_nAverageStation;//平均线的位置
	CString m_strMax;//最高值
	CString m_strMin;//最低值
	CString m_strAverage;//平均线
	double m_dTotalValue;//总值
	std::vector<CPieChartPiece *> m_vPieChart;
public:
	void	SetRectBkColor(COLORREF c_color);
	unsigned short SetType(unsigned short c_iType);
	unsigned short GetType();
	CPieChartPiece * AddChartPiece(double c_dValue, CString c_strTitle);
public:
	double GetMax();
	double GetMin();
public:
	int Calc(void);
	int CalcPieChart(void);	
public:
	int PaintText(CRect &rect);
	int PaintChart(void);
	int PaintPieChart(void);	
public:
	// 清除所有的数据
	int ClearAllPiece(void);
};


