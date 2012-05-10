// BaseDraw.cpp : 实现文件
//

#include "stdafx.h"
#include <math.h>
#include "BaseDraw.h"

#define PIC3D
const double pi = 3.14159265358979323846;
// CBaseDraw
float TransformAngel(CRect rect, float angel)
{
        return angel;
    int nRectWidth = rect.Width();
    int nRectHeight = rect.Height();
    double x = nRectWidth * cos(angel * pi / 180);
    double y = nRectHeight * sin(angel * pi / 180);
    float result = (float)(atan2(y, x) * pi / 3.14);

    if (result < 0)
    {
        result += 360;
    }

//   int iResult = (int)(result+0.5);
    return result;
}

CPoint GetEllipsePoint(CRect rect, float angel)
{
    float a = (float)rect.Width() / 2;
    float b = (float)rect.Height() / 2;

//    angel = angel % 360;
    UINT quant = angel / 90 + 1;

    float fAngel = (float)((float)angel / 360 * 2 * pi);
    float tangent = (float)tan( fAngel );

    double x = sqrt( a*a*b*b / (b*b + a*a*tangent*tangent) );
    double y = sqrt( (a*a*b*b - b*b*x*x) / a / a );

    switch ( quant )
    {
    case 1:
        break;
    case 2:
        x = -x;
        break;
    case 3:
        x = -x;
        y = -y;
        break;
    case 4:
        y = -y;
        break;
    default:
        break;
    }
    x = (int)(x+0.5);
    y = (int)(y+0.5);
    
    int nTempX = (int)(a + 0.5);
    int nTempY = (int)(b + 0.5);

    int iResultX = (int)x + nTempX + rect.left;
    int iResultY = abs((int)y - nTempY - rect.top);
    return CPoint(iResultX, iResultY);
}

long GetDimColor(long lOriginColor)
{
    /**///////////////////////////////////////////////////////////////////////////
    // 取得原颜色的RGB值
    long lRed = GetRValue(lOriginColor);
    long lGreen = GetGValue(lOriginColor);
    long lBlue = GetBValue(lOriginColor);
    /**///////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // 对RGB颜色取半
    long lResultRed = lRed / 2;
    long lResultGreen = lGreen / 2;
    long lResultBlue = lBlue / 2;
    long lResultColor = RGB(lResultRed, lResultGreen, lResultBlue);
    /**///////////////////////////////////////////////////////////////////////////

    return lResultColor;
}
CBaseDraw::CBaseDraw()
: m_pDC(NULL)
{
	m_uiType = 0;
	m_colorRectBk = 0XFFFFFF;
	m_colorRef[0] = RGB(4,2,253);
	m_colorRef[1] = RGB(252,22,148);
	m_colorRef[2] = RGB(93,158,164);
	m_colorRef[3] = RGB(141,42,229);
	m_colorRef[4] = RGB(252,1,252);
	m_colorRef[5] = RGB(215,151,1);
	m_colorRef[6] = RGB(5,250,157);
	m_colorRef[7] = RGB(251,182,210);
	m_colorRef[8] = RGB(108,89,204);
	m_colorRef[9] = RGB(252,170,133);
	m_colorRef[10] = RGB(5,191,252);
	m_colorRef[11] = RGB(132,3,132);
	m_colorRef[12] = RGB(191,227,117);
	m_colorRef[13] = RGB(220,189,220);
	m_colorRef[14] = RGB(4,254,252);
	m_colorRef[15] = RGB(191,185,153);
	m_colorRef[16] = RGB(180,198,220);
	m_colorRef[17] = RGB(223,242,176);
	m_colorRef[18] = RGB(220,115,148);
	m_colorRef[19] = RGB(180,225,228);
	m_colorRef[20] = RGB(149,2,212);
	m_colorRef[21] = RGB(117,137,190);
	m_colorRef[22] = RGB(172,238,236);
	m_colorRef[23] = RGB(253,237,80);
	m_colorRef[24] = RGB(44,78,77);
	m_colorRef[25] = RGB(236,131,236);
	m_colorRef[26] = RGB(4,205,212);
	m_colorRef[27] = RGB(183,8,41);
	m_colorRef[28] = RGB(3,2,132);
	m_colorRef[29] = RGB(0,172,50);
	m_colorRef[30]=0XFF7F00;
	m_colorRef[31]=0X8FBC8F;
	m_colorRef[32]=0XBC8F8F;
	m_colorRef[33]=0X5959AB;
	m_colorRef[34]=0X6F4242;
	m_colorRef[35]=0X238E68;
	m_colorRef[36]=0XFF1CAE;
	m_colorRef[37]=0X236B8E;
	m_colorRef[38]=0X38B0DE;
	m_colorRef[39]=0XCC3299;
		m_colorRef[40]=RGB(180,255,150);
		m_colorRef[41]=RGB(210,255,180);
		m_colorRef[42]=RGB(240,255,210);
		m_colorRef[42]=RGB(240,0,210);
		
		m_colorRef[44]=RGB(30,30,255);
		m_colorRef[45]=RGB(60,60,255);
		m_colorRef[46]=RGB(90,90,255);
		m_colorRef[47]=RGB(120,120,255);
		m_colorRef[48]=RGB(150,150,255);
		m_colorRef[49]=RGB(180,180,255);
		m_colorRef[50]=RGB(210,210,255);
		m_colorRef[51]=RGB(240,240,255);

		m_colorRef[52]=RGB(0,0,255);
		m_colorRef[53]=RGB(30,30,255);
		m_colorRef[54]=RGB(60,60,255);
		m_colorRef[55]=RGB(90,90,255);
		m_colorRef[56]=RGB(120,120,255);
		m_colorRef[57]=RGB(150,150,255);
		m_colorRef[58]=RGB(180,180,255);
		m_colorRef[59]=RGB(210,210,255);
		m_colorRef[60]=RGB(240,240,255);

		m_colorRef[61]=RGB(0,0,30);
		m_colorRef[62]=RGB(0,0,60);
		m_colorRef[63]=RGB(0,0,90);
		m_colorRef[64]=RGB(0,0,120);
		m_colorRef[65]=RGB(0,0,150);
		m_colorRef[66]=RGB(0,0,180);
		m_colorRef[67]=RGB(0,0,210);
		m_colorRef[68]=RGB(0,0,240);

		m_colorRef[69]=RGB(30,0,0);
		m_colorRef[70]=RGB(60,0,0);
		m_colorRef[71]=RGB(90,0,0);
		m_colorRef[72]=RGB(120,0,0);
		m_colorRef[73]=RGB(150,0,0);
		m_colorRef[74]=RGB(180,0,0);
		m_colorRef[75]=RGB(210,0,0);
		m_colorRef[76]=RGB(240,0,0);

		m_colorRef[77]=RGB(60,0,30);
		m_colorRef[78]=RGB(90,0,60);
		m_colorRef[79]=RGB(120,0,90);
		m_colorRef[80]=RGB(150,0,120);
		m_colorRef[81]=RGB(180,0,150);
		m_colorRef[82]=RGB(210,0,180);
		m_colorRef[83]=RGB(240,0,210);

		m_colorRef[84]=RGB(30,30,0);
		m_colorRef[85]=RGB(60,60,0);
		m_colorRef[86]=RGB(90,90,0);
		m_colorRef[87]=RGB(120,120,0);
		m_colorRef[88]=RGB(150,150,0);
		m_colorRef[89]=RGB(180,180,0);
		m_colorRef[90]=RGB(210,210,0);
		m_colorRef[91]=RGB(240,240,0);

		m_colorRef[92]=RGB(30,30,0);
		m_colorRef[93]=RGB(60,60,0);
		m_colorRef[94]=RGB(90,90,0);
		m_colorRef[95]=RGB(120,120,0);
		m_colorRef[96]=RGB(150,150,0);
		m_colorRef[97]=RGB(180,180,0);
		m_colorRef[98]=RGB(210,210,0);
		m_colorRef[99]=RGB(240,240,0);
}

CBaseDraw::~CBaseDraw()
{
	ClearAllPiece();
}


// CBaseDraw 成员函数
unsigned short CBaseDraw::SetType(unsigned short c_uiType)
{
	m_uiType = c_uiType;
	return m_uiType;
}
unsigned short CBaseDraw::GetType()
{
	return m_uiType;
}
CPieChartPiece * CBaseDraw::AddChartPiece(double c_dValue, CString c_strTitle)
{
	CPieChartPiece * p = new CPieChartPiece();		
	p->m_dValue = c_dValue;
	p->m_strTitle = c_strTitle;
	p->m_colorBack = m_colorRef[m_vPieChart.size() % 100];
	p->m_colorText = m_colorRef[m_vPieChart.size() % 100];
	m_vPieChart.push_back(p);
	return p;
}
int CBaseDraw::Calc(void)
{
	return CalcPieChart();
}

int CBaseDraw::CalcPieChart(void)
{
	std::vector<CPieChartPiece *>::iterator iterPiece;
	double dHJ;
	int iTitleBeginX,iTitleBeginY;

	iTitleBeginX = m_rectDraw.left;
	iTitleBeginY = m_rectDraw.top;
	if (m_vPieChart.size() == 0)
		return -1;

	m_rectDrawTop = m_rectDraw;
	m_rectDrawTop.bottom = float(m_rectDraw.Height()) * 0.88 + m_rectDraw.top;
	if (m_rectDrawTop.Width() % 2)
		m_rectDrawTop.right += 1;
	if (m_rectDrawTop.Height() % 2)
		m_rectDrawTop.bottom += 1;
	m_rectDrawBottom = m_rectDrawTop;
	m_rectDrawBottom.OffsetRect(0,float(m_rectDraw.Height()) * 0.1);
	
	m_point0 = GetEllipsePoint(m_rectDrawTop,0);
	m_point180 = GetEllipsePoint(m_rectDrawTop,180);

	m_point0Bottom = GetEllipsePoint(m_rectDrawBottom,0);
	m_point180Bottom = GetEllipsePoint(m_rectDrawBottom,180);

	m_point0.x = m_rectDrawTop.right;
	m_point0.y = m_rectDrawTop.top + m_rectDrawTop.Height() / 2;

	m_point0Bottom.x = m_rectDrawBottom.right;
	m_point0Bottom.y = m_rectDrawBottom.top + m_rectDrawTop.Height() / 2;
	

	dHJ = m_dTotalValue;
	double dAngle = 360;

	int iCount = 0;
	for(iterPiece=m_vPieChart.begin(); iterPiece!=m_vPieChart.end(); iterPiece++)
	{
		(*iterPiece)->m_iTitleX = iTitleBeginX;
		(*iterPiece)->m_iTitleY = iTitleBeginY;
		iTitleBeginY += 20;
		(*iterPiece)->m_dPercent = (*iterPiece)->m_dValue / dHJ;
		(*iterPiece)->m_dAngle = (*iterPiece)->m_dValue * 360/ dHJ;

		(*iterPiece)->m_pointb = GetEllipsePoint(m_rectDrawTop,(float)dAngle);
		(*iterPiece)->m_pointbBottom = GetEllipsePoint(m_rectDrawBottom,(float)dAngle);

		dAngle -= (*iterPiece)->m_dAngle;			

		(*iterPiece)->m_pointa = GetEllipsePoint(m_rectDrawTop,(float)dAngle);
		(*iterPiece)->m_pointaBottom = GetEllipsePoint(m_rectDrawBottom,(float)dAngle);		
		
		iCount++;
	}
	return 0;
}
double CBaseDraw::GetMax()
{
	std::vector <CPieChartPiece *>::iterator iterPiece;
	double dTmp = 0;
	int iCount = 0;
	if (m_vPieChart.size() == 0)
		return 0;
	for(iterPiece=m_vPieChart.begin(); iterPiece!=m_vPieChart.end(); iterPiece++)
	{
		if (iCount == 0)
			dTmp = (*iterPiece)->m_dValue;
		if ((*iterPiece)->m_dValue > dTmp)
			dTmp = (*iterPiece)->m_dValue;
		iCount++;
	}
	return dTmp;
}
double CBaseDraw::GetMin()
{
	std::vector <CPieChartPiece *>::iterator iterPiece;
	double dTmp = 0;
	int iCount;
	if (m_vPieChart.size() == 0)
		return 0;
	iCount = 0;
	for(iterPiece=m_vPieChart.begin(); iterPiece!=m_vPieChart.end(); iterPiece++)
	{
		if (iCount == 0)
			dTmp = (*iterPiece)->m_dValue;
		if ((*iterPiece)->m_dValue < dTmp)
			dTmp = (*iterPiece)->m_dValue;
		iCount++;
	}
	return dTmp;
}
int CBaseDraw::PaintChart()
{
	PaintPieChart();
	return 0;
}
int CBaseDraw::PaintText(CRect &rect)
{
	CRect r;
	double dJE = 0;
	double dCost = 0;
	int iCount = 0;
	int iTitleY = 0;
	///-COLORREF colorOld;
	int   nOldMode;
	CString strText,strTest;
	CSize size;
	CSize sizea,sizeb;
	HGDIOBJ		oldFont;
	strTest = _T("未流通");
	std::vector<CPieChartPiece *>::iterator iterPiece;

	iTitleY = rect.top;
	size = m_pDC->GetTextExtent(strTest);
	for(iterPiece=m_vPieChart.begin(); iterPiece!=m_vPieChart.end(); iterPiece++)
	{
		CSize sizeTmp;
		sizeTmp = m_pDC->GetTextExtent((*iterPiece)->m_strTitle);
		if (size.cx < sizeTmp.cx)
			size.cx = sizeTmp.cx;
	}
	for(iterPiece=m_vPieChart.begin(); iterPiece!=m_vPieChart.end(); iterPiece++)
	{
		nOldMode = m_pDC->SetBkMode(TRANSPARENT);
		oldFont = m_pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));				
		strText = (*iterPiece)->m_strTitle;

		m_pDC->TextOut(rect.left+14,iTitleY + iCount * (size.cy + 2) ,strText,strText.GetLength());

		strText.Format(_T("%.2f%%"),(*iterPiece)->m_dPercent * 100);
		sizea = m_pDC->GetTextExtent(_T("00.12%"));
		sizeb = m_pDC->GetTextExtent(strText);
		m_pDC->TextOut(rect.left + 14 + size.cx + sizea.cx - sizeb.cx,iTitleY + iCount * (size.cy + 2),strText,strText.GetLength());

		m_pDC->SelectObject(oldFont);
		r.left = rect.left + 2;

		r.top = (iCount) * (size.cy + 2) + rect.top;
		r.bottom = size.cy + r.top;
		r.right = r.left + 8;
		m_pDC->FillRect(&r,&(CBrush((*iterPiece)->m_colorBack)));
		m_pDC->SetBkMode(nOldMode);
		iCount++;
	}	
	return 0;
}
#ifdef PIC3D
int CBaseDraw::PaintPieChart(void)
{
	CBitmap *pOldMemDCBitmap = NULL;	
	CDC memDC;
	CBitmap bitmap;
	CRect rect;
	memDC.CreateCompatibleDC(m_pDC);
	rect = m_rectDraw;
	rect.top = 0;
	rect.left = 0;
	rect.bottom = m_rectDraw.Height();
	rect.right = m_rectDraw.Width();
	bitmap.CreateCompatibleBitmap( m_pDC, rect.Width(), rect.Height());
	CBitmap *pOldmemDCBitmap = (CBitmap*)memDC.SelectObject(&bitmap);

	memDC.FillSolidRect(rect, m_colorRectBk);
	
	CPen pen,pen1;
	
	CPen* pOldPen = (CPen*)memDC.SelectStockObject(NULL_PEN);

	CBrush brush,*pPreBrush;
	brush.CreateSolidBrush(m_colorRectBk);
	CBrush* pOldBrush = memDC.SelectObject(&brush);
	
	memDC.Ellipse(rect);	

	std::vector<CPieChartPiece *>::iterator iterPiece;
	CPieChartPiece * p;
	CBrush brushDim;//阴影刷子
	double dAngle = 360;
	int iCount = 0;

	pPreBrush = NULL;
	for(iterPiece=m_vPieChart.begin(); iterPiece!=m_vPieChart.end(); iterPiece++)
	{
		iCount++;
		p = (*iterPiece);
		if (p->m_dValue == 0)
			continue;

		pen.CreatePen(PS_SOLID, 1, GetDimColor(p->m_colorBack));
		memDC.SelectObject(&pen);
		dAngle -= p->m_dAngle;
		memDC.BeginPath();
		if (dAngle+ p->m_dAngle> 180)
		{
			if (dAngle> 180)
			{
				//memDC.Arc(m_rectDrawBottom,p->m_pointaBottom,p->m_pointbBottom);
				//memDC.Chord(m_rectDrawBottom,p->m_pointaBottom,p->m_pointbBottom);
				//memDC.Arc(m_rectDrawTop,p->m_pointa,p->m_pointb);
				memDC.MoveTo(p->m_pointa);
				memDC.LineTo(p->m_pointaBottom);
				memDC.LineTo(p->m_pointbBottom);
				memDC.LineTo(p->m_pointb);
				//memDC.LineTo(p->m_pointa);

			}
			else
			{
				//memDC.Arc(m_rectDrawBottom,m_point180Bottom,p->m_pointbBottom);
				//memDC.Chord(m_rectDrawBottom,m_point180Bottom,p->m_pointbBottom);
				//memDC.Arc(m_rectDrawTop,m_point180,p->m_pointb);
				memDC.MoveTo(m_point180);
				memDC.LineTo(m_point180Bottom);
				memDC.LineTo(p->m_pointbBottom);
				memDC.LineTo(p->m_pointb);
				memDC.LineTo(m_point180);
				
			}
		}
		memDC.CloseFigure();
		memDC.EndPath();
		brushDim.CreateSolidBrush(GetDimColor(p->m_colorBack));
		memDC.SelectObject(&brushDim);
		memDC.FillPath();
		
		if (dAngle+p->m_dAngle > 180)
		{
			if (dAngle > 180)
			{
				memDC.MoveTo(p->m_pointaBottom);
				memDC.LineTo(p->m_pointbBottom);
				memDC.Chord(m_rectDrawBottom,p->m_pointaBottom,p->m_pointbBottom);
			}
			else
			{
				
				CPen pen2;
				pen2.CreatePen(PS_SOLID, 1, GetDimColor(p->m_colorBack));
				memDC.SelectObject(&pen2);
				memDC.Chord(m_rectDrawBottom,m_point180Bottom,p->m_pointbBottom);
				memDC.MoveTo(m_point180Bottom);
				memDC.LineTo(p->m_pointbBottom);
				memDC.LineTo(m_point180Bottom);
				memDC.LineTo(p->m_pointbBottom.x-1,p->m_pointbBottom.y);
				memDC.SelectObject(&pen);
				pen2.DeleteObject();
			}
		}
		brushDim.DeleteObject();
		memDC.SelectObject(pOldPen);
		pen.DeleteObject();
		
		CBrush br(p->m_colorBack);
		memDC.SelectObject(&br);
		memDC.Pie(m_rectDrawTop, p->m_pointa, p->m_pointb);
		/*
		if (dAngle+p->m_dAngle > 180 && dAngle+p->m_dAngle < 270)
		{
			if (pPreBrush)
			{
				memDC.BeginPath();
				memDC.MoveTo(p->m_pointb);
				memDC.LineTo(p->m_pointbBottom);
				memDC.LineTo(m_rectDrawBottom.CenterPoint());
				memDC.LineTo(m_rectDrawTop.CenterPoint());
				memDC.LineTo(p->m_pointb);
				memDC.EndPath();
				memDC.SelectObject(pPreBrush);
				memDC.FillPath();
				memDC.SelectObject(p->m_brushBack);
			}
		}*/
		//pPreBrush = &(p->m_brushBack);
	}

	m_pDC->BitBlt( m_nStartX, m_nStartY, m_rectDraw.Width(), m_rectDraw.Height(), &memDC, 0, 0, SRCCOPY );
	
	memDC.SelectObject(pOldPen);
	memDC.SelectObject(&pOldBrush);
	memDC.SelectObject(pOldmemDCBitmap);
	
	return 0;
}
#else
int CBaseDraw::PaintPieChart(void)
{
	CBitmap *pOldMemDCBitmap = NULL;	
	CDC memDC;
	CBitmap bitmap;
	CRect rect;
	memDC.CreateCompatibleDC(m_pDC);
	rect = m_rectDraw;
	rect.bottom += rect.top;
	rect.right += rect.left;
	bitmap.CreateCompatibleBitmap( m_pDC, rect.Width(), rect.Height());
	CBitmap *pOldmemDCBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
	if (m_rectDraw.Width() == 0)
		return 0;
	memDC.FillSolidRect(rect, m_colorRectBk);
	
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
	CPen* pOldPen = (CPen*)memDC.SelectStockObject(NULL_PEN);

	CBrush brush;
	brush.CreateSolidBrush(m_colorRectBk);
	CBrush* pOldBrush = memDC.SelectObject(&brush);
	memDC.Ellipse(m_rectDraw);	

	vector<CPieChartPiece *>::iterator iterPiece;
	for(iterPiece=m_vPieChart.begin(); iterPiece!=m_vPieChart.end(); iterPiece++)
	{
		memDC.SelectObject(&pen);
		memDC.MoveTo((*iterPiece)->m_pointa);
		memDC.LineTo(m_rectDraw.CenterPoint());
		memDC.LineTo((*iterPiece)->m_pointa);
		//memDC.SelectStockObject(NULL_PEN);
		memDC.SelectObject((*iterPiece)->m_brushBack);
		memDC.Pie(m_rectDraw, (*iterPiece)->m_pointb, (*iterPiece)->m_pointa);
	}
	m_pDC->BitBlt( m_rectDraw.left, m_rectDraw.top, m_rectDraw.Width(), m_rectDraw.Height(), &memDC, m_rectDraw.left, m_rectDraw.top, SRCCOPY );
	
	memDC.SelectObject(pOldPen);
	memDC.SelectObject(&pOldBrush);
	memDC.SelectObject(pOldmemDCBitmap);
	
	return 0;
}
#endif
// 清除所有的数据
int CBaseDraw::ClearAllPiece(void)
{
	std::vector<CPieChartPiece *>::iterator iterPiece;
	while(m_vPieChart.size() > 0)
	{
		iterPiece=m_vPieChart.begin();
		delete *iterPiece;
		m_vPieChart.erase(iterPiece);
	}
	return 0;
}

void CBaseDraw::SetRectBkColor(COLORREF c_color)
{
	m_colorRectBk = c_color;
}