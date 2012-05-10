#pragma once
#include "atltypes.h"

// CBaseDraw ����Ŀ��
class  CPieChartPiece
{
public:
	CPieChartPiece() {;};
	~CPieChartPiece()
	{
	}	
	double		m_dValue;//��ֵ	
	double		m_dPercent;//����
	double		m_dAngle;//����
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
	// ��ͼDC
	CDC *m_pDC;
public:
	//��ɫ
	COLORREF	m_colorRef[100];
	COLORREF	m_colorRectBk;
	// ��ͼ����
	unsigned short	m_uiType;//ͼ������,Ĭ��ΪPie,1�Ǿ���ͼ
	CRect m_rectText;
	int		m_nStartX;
	int		m_nStartY;
	CRect m_rectDraw;
	CRect m_rectDrawTop;//����ľ���
	CRect m_rectDrawBottom;//����ľ���
	CPoint m_point0;//0�ȵ�����
	CPoint m_point180;//180������
	CPoint m_point0Bottom;//�����0�ȵ�����
	CPoint m_point180Bottom;//�����180�ȵ�����
	CPoint m_pointZero;/*���,x,y��*/
	int		m_nMaxStation;//��͵��λ��
	int		m_nMinStation;//��ߵ��λ��
	int		m_nAverageStation;//ƽ���ߵ�λ��
	CString m_strMax;//���ֵ
	CString m_strMin;//���ֵ
	CString m_strAverage;//ƽ����
	double m_dTotalValue;//��ֵ
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
	// ������е�����
	int ClearAllPiece(void);
};


