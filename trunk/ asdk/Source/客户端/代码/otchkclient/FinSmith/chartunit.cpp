#include "StdAfx.h"
#include "math.h"
#include "../public/data_struct.h"
#include "chartunit.h"
#include "../public/skinmanager.h"

ChartUnit::ChartUnit()
{
	m_bDrawReferValue = true;
	m_bDrawSingle = false;
	m_nSpecialType = STNULL;
	m_nFixedMaxValue = 0x7FFFFFFF;
	m_nFixedMinValue = 0x7FFFFFFF;
    m_nHoriCount = 0;
    m_pnHoriPoint = NULL;
    m_pData = NULL;
    m_nDataBeginPos = 0;
    m_nDataCount = 0;
    m_nCellWidth = 1;
    m_nCellSpace = 1;
    m_rtType = RTZERO;
    m_nReferValue = 0;
    m_nMaxValue = -1;
    m_nMinValue = 0X7FFFFFFF;
    m_bSelected =  false;
    m_nMultiplier = 1;
	m_nDiv = 1;
    m_nPrecision = 0;
	m_nCurPos = -1;
	m_psBz = NULL;
	m_bToFree = true;
	m_bIsIndex = false;//是否指数
	m_nPenStyle = PS_SOLID;
#ifdef CCTV_TV
	m_nLineWidth = 2;
#else
	m_nLineWidth = 1;
#endif
	m_atType = AIXNORMAL;
	m_pMainUnit = NULL;
	m_pnTDPointHigh = NULL;
	m_pnTDPointLow = NULL;

	for(int n=0; n<16; n++)
	{
		m_nPriceLines[n] = 0X7FFFFFFF;
	}
}

ChartUnit::~ChartUnit()
{
    if(m_bToFree)
    {
        if (m_pData)
			free(m_pData);
    }
	if (m_psBz)
		free(m_psBz);
	if (m_pnTDPointHigh)
		free(m_pnTDPointHigh);
	if (m_pnTDPointLow)
		free(m_pnTDPointLow);
}

void ChartUnit::setChartUnitType(ChartUnitType c_cuType)
{
    m_cuType = c_cuType;
}

void ChartUnit::setRefer(ReferType c_rt, int c_nValue)
{
    m_rtType = c_rt;
    m_nReferValue = c_nValue;
}

void ChartUnit::setMaxMinValue(int c_nMax, int c_nMin,float c_fMax,float c_fMin)
{
	if (m_nFixedMaxValue != 0x7FFFFFFF && m_nFixedMinValue != 0x7FFFFFFF)
		return;

	if (m_bDrawSingle)
		return;

		if (m_cuType == CUTrend || m_cuType == CUTrendVol)
		{
			m_nMaxValue = float(c_nMax) * 1.001;
			m_nMinValue = float(c_nMin * 0.999);
		}
		else
		{
			m_nMaxValue = c_nMax;
			m_nMinValue = c_nMin;
			if (m_rtType == RTMIN)
				m_nReferValue = m_nMinValue;
			else
			if (m_rtType == RTMID)
			{
				if (m_nMinValue < m_nReferValue && m_nMaxValue < m_nReferValue)
					m_nMaxValue = m_nReferValue;
				else
				if (m_nMinValue > m_nReferValue && m_nMaxValue > m_nReferValue)
					m_nMinValue = m_nReferValue;
			}
		}
}

void ChartUnit::getMaxMinValue(int &c_nBegin,int &c_nInMax, int &c_nInMin)
{
	if (m_nFixedMaxValue != 0x7FFFFFFF && m_nFixedMinValue != 0x7FFFFFFF)
	{
		c_nInMax = m_nFixedMaxValue;
		c_nInMin = m_nFixedMinValue;
		return;
	}
	int nRetMax,nRetMin;
	nRetMax = -1;
	nRetMin = 0x7FFFFFFF;
	
	if (m_nSpecialType == STRSI)
	{
		c_nInMax = 100 * 1000;
		c_nInMin = 0;
	}
	if (m_cuType == CUTDBUY || m_cuType == CUTDSELL)
	{
		return;
	}
    if(m_cuType == CULink)
    {
        int *pnValue;
        pnValue = (int *)m_pData;
		if (pnValue == NULL)
			return;
        for(int n=0; n<m_nDataCount; n++)
        {
            if (pnValue[n + m_nDataBeginPos] == 0X7FFFFFFF)
                continue;
            if (pnValue[n + m_nDataBeginPos] > nRetMax)
                nRetMax = pnValue[n + m_nDataBeginPos];
            if (pnValue[n + m_nDataBeginPos] < nRetMin)
                nRetMin = pnValue[n + m_nDataBeginPos];
        }
    }
    else
    if(m_cuType == CUQCT)
    {
        KLINE *pK;
        pK = (KLINE *)m_pData;
		if (pK == NULL)
			return;
		int nBegin = m_nDataBeginPos - 32;
		if (nBegin < 0)
			nBegin = 0;
        for(int n=nBegin; n<m_nDataLen/sizeof(KLINE); n++)
        {
            if (pK[n].close == 0X7FFFFFFF)
                continue;
            if (pK[n].high > nRetMax || nRetMax == 0xFFFFFFFF)
                nRetMax = pK[n].high;
            if (pK[n].low < nRetMin)
                nRetMin = pK[n].low;
        }
    }
	else
    if (m_cuType == CUTrend)
    {
        MinUnit * pBlock = (MinUnit *)m_pData;
		int nMinItemCount = m_nDataLen / sizeof(MinUnit);
        if (pBlock)
        {
			if (m_nDataCount > 0)
			{
            for(int n=0; n<m_nDataCount; n++)
            {				
				if (int(pBlock[n + m_nDataBeginPos].NewPrice) > 0)
				{
					if (int(pBlock[n + m_nDataBeginPos].NewPrice) > nRetMax)
						nRetMax = pBlock[n + m_nDataBeginPos].NewPrice;
					if (int(pBlock[n + m_nDataBeginPos].NewPrice) < nRetMin)
						nRetMin = pBlock[n + m_nDataBeginPos].NewPrice;
				}
				if (int(pBlock[n + m_nDataBeginPos].MaxPrice) > 0)
				{
					if (int(pBlock[n + m_nDataBeginPos].MaxPrice) > nRetMax)
						nRetMax = pBlock[n + m_nDataBeginPos].MaxPrice;
				}
				if (int(pBlock[n + m_nDataBeginPos].MinPrice) > 0)
				{
					if (int(pBlock[n + m_nDataBeginPos].MinPrice) < nRetMin)
						nRetMin = pBlock[n + m_nDataBeginPos].MinPrice;
				}
				if (m_bIsIndex == false)
				{
					if (pBlock[n + m_nDataBeginPos].AvgPrice > 0)
					{
						if (int(pBlock[n + m_nDataBeginPos].AvgPrice) > nRetMax)
							nRetMax = pBlock[n + m_nDataBeginPos].AvgPrice;
						if (int(pBlock[n + m_nDataBeginPos].AvgPrice) < nRetMin)
							nRetMin = pBlock[n + m_nDataBeginPos].AvgPrice;
					}
				}
            }
			}
			else
			{
				nRetMax = m_nReferValue * 1.1;
				nRetMin = m_nReferValue * 0.9;
			}
        }
		if (m_nReferValue > 0)
		{
			int nMax = (m_nReferValue * 0.01);
			if (m_nReferValue < 10000)
				nMax = (m_nReferValue * 0.02);
			if (abs(nRetMax - m_nReferValue) < nMax && abs(nRetMin - m_nReferValue) < nMax)
			{
				nRetMax = m_nReferValue + nMax;
				nRetMin = m_nReferValue - nMax;
			}
		}
    }
    else
    if (m_cuType == CUTrendVol)
    {
        MinUnit * pBlock = (MinUnit *)m_pData;
		int nMinItemCount = m_nDataLen / sizeof(MinUnit);
        if (pBlock)
        {
            for(int n=m_nDataBeginPos; n<m_nDataCount; n++)
            {
				if(m_bIsIndex)
				{
					if (int(pBlock[n].Volume) > nRetMax)
						nRetMax = pBlock[n].Volume;
					if (int(pBlock[n].Volume) < nRetMin)
						nRetMin = pBlock[n].Volume;
				}
				else
				{
					if (int(pBlock[n].Volume) > nRetMax)
						nRetMax = pBlock[n].Volume;
					if (int(pBlock[n].Volume) < nRetMin)
						nRetMin = pBlock[n].Volume;
				}
            }
        }
    }
    else
    if (m_cuType == CUKLine)
    {
        KLINE * pBlock = (KLINE *)m_pData;
		int nBlockItemCount = m_nDataLen / sizeof(KLINE);
        if (pBlock)
        {
            for(int n=0; n<m_nDataCount; n++)
            {   
				if((n + m_nDataBeginPos) >= nBlockItemCount)
					break;
				if (c_nBegin == 0)
				{
					if (pBlock[n + m_nDataBeginPos].close != 0x7FFFFFFF)
						c_nBegin = pBlock[n + m_nDataBeginPos].close;
				}
				if (pBlock[n + m_nDataBeginPos].low == 0x7FFFFFFF 
					||pBlock[n + m_nDataBeginPos].high == 0x7FFFFFFF)
					continue;

                if (int(pBlock[n + m_nDataBeginPos].high) > nRetMax)
                    nRetMax = pBlock[n + m_nDataBeginPos].high;
                if (pBlock[n + m_nDataBeginPos].low > 0 && int(pBlock[n + m_nDataBeginPos].low) < nRetMin)
                    nRetMin = pBlock[n + m_nDataBeginPos].low;
            }
			m_nBeginValue = c_nBegin;
			m_nMaxValue = nRetMax;
			m_nMinValue = nRetMin;
        }
    }
    else
    if (m_cuType == CUVOL)
    {
        KLINE * pBlock = (KLINE *)m_pData;
		int nBlockItemCount = m_nDataLen / sizeof(KLINE);
        if (pBlock)
        {
            for(int n=0; n<m_nDataCount; n++)
            {
                if (int(pBlock[n + m_nDataBeginPos].volume/m_nDiv) > nRetMax)
                    nRetMax = pBlock[n + m_nDataBeginPos].volume/m_nDiv;
                if (int(pBlock[n + m_nDataBeginPos].volume/m_nDiv) < nRetMin)
                    nRetMin = pBlock[n + m_nDataBeginPos].volume/m_nDiv;
            }
        }
    }
    else
    {
        int *pnValue;
        pnValue = (int *)m_pData;
		if (pnValue == NULL)
			return;
        for(int n=0; n<m_nDataCount; n++)
        {
            if (pnValue[n + m_nDataBeginPos] == 0X7FFFFFFF)
                continue;

            if (pnValue[n + m_nDataBeginPos] > nRetMax)
                nRetMax = pnValue[n + m_nDataBeginPos];
            if (pnValue[n + m_nDataBeginPos] < nRetMin)
                nRetMin = pnValue[n + m_nDataBeginPos];
        }
    }
	if (m_bDrawSingle)//单独画的图形在此就完成最大和最小值的设置
	{
		m_nMaxValue = nRetMax;
		m_nMinValue = nRetMin;
		if (m_rtType == RTMIN)
			m_nReferValue = m_nMinValue;
	}
	else
	{
		if (nRetMax > c_nInMax)
			c_nInMax = nRetMax;
		if (nRetMin < c_nInMin)
			c_nInMin = nRetMin;
	}
}

void ChartUnit::setDrawRect(CRect c_rect)
{
    m_rectDraw = c_rect;
}

void ChartUnit::setLineColor(COLORREF c_color)
{
    m_clLine = c_color;
}

void ChartUnit::setLineWidth(int c_n)
{
#ifdef CCTV_TV
	m_nLineWidth = c_n;
	if (c_n < 2)
		m_nLineWidth = 2;
#else
    m_nLineWidth = c_n;
#endif
}

void ChartUnit::setPenStyle(int c_n)
{
	m_nPenStyle = c_n;
}

void ChartUnit::setCell(int c_nWidth, int c_nSpace)
{
    m_nCellWidth = c_nWidth;
    m_nCellSpace = c_nSpace;
}

void ChartUnit::setData(char * c_pData,int c_nDataLen,bool c_bToFree)
{
    if(m_bToFree)
    {
        if (m_pData)
			free(m_pData);
		if (m_pnTDPointHigh)
		{
			free(m_pnTDPointHigh);
			m_pnTDPointHigh = NULL;
		}
		if (m_pnTDPointLow)
		{
			free(m_pnTDPointLow);
			m_pnTDPointLow = NULL;
		}
    }
    m_pData = c_pData;
    m_nDataLen = c_nDataLen;
	m_bToFree = c_bToFree;
}

void ChartUnit::setTDPoint(int *c_pnH,int *c_pnL)
{
	if (m_pnTDPointHigh)
		free(m_pnTDPointHigh);
	m_pnTDPointHigh = c_pnH;
	if (m_pnTDPointLow)
		free(m_pnTDPointLow);
	m_pnTDPointLow = c_pnL;
}

void ChartUnit::setBz(short * c_psBz)
{
	if (m_psBz)
		free(m_psBz);
	m_psBz = c_psBz;
}
void ChartUnit::setViewProperty(int c_nCount, int *c_pnHoriValue, int c_nDataBegin,int c_nDataBeginTime, int c_nDataCount)
{
    m_nHoriCount = c_nCount;
    m_pnHoriPoint = c_pnHoriValue;  
    m_nDataBeginPos = c_nDataBegin;
	m_nDataBeginPosTime = c_nDataBeginTime;
    m_nDataCount = c_nDataCount;
}

void ChartUnit::drawChartUnit(CDC * c_pDC)
{
	//c_pDC->Rectangle(m_rectDraw);
    if (m_cuType == CULink)
    {
		int nCount = m_nDataLen/sizeof(int);
		int nV = m_nDataCount;
		if (nCount - m_nDataBeginPos > m_nDataCount);
		{
			if (m_nSpecialType == STMMA)
			{
				nV = nCount - m_nDataBeginPos;
				if (nV > m_nHoriCount)
					nV = m_nHoriCount;
			}
		}
		if (nCount > 0 && m_nDataBeginPos<nCount)
		{
			int * pnVert = new int[nV];
			for(int n=0; n<nV; n++)
				pnVert[n] = INVALID_INT;
			if (m_nDataBeginPos + nV <= nCount)
				calcVertPos((int *)m_pData + m_nDataBeginPos,nV,pnVert,m_rtType,m_nReferValue);
			else
				calcVertPos((int *)m_pData + m_nDataBeginPos,nCount-m_nDataBeginPos,pnVert,m_rtType,m_nReferValue);
			drawLinkLine(c_pDC,nV,pnVert,gpSkinManager->getLineColor(m_clLine));
			delete [] pnVert;
		}
    }
    else
    if (m_cuType == CUTrend)
        drawTrend(c_pDC);
    else
    if (m_cuType == CUTrendVol)
        drawTrendVol(c_pDC);
    else
    if (m_cuType == CUKLine)
	{
        drawKLine(c_pDC);		
	}
    else
    if (m_cuType == CUVOL)
        drawVol(c_pDC);
	else
	if (m_cuType == CUTick || m_cuType == CUTickLine)
	{
		if (m_pData == NULL)
			return;
		int nCount = m_nDataLen/sizeof(int);        
		if (nCount > 0 && m_nDataBeginPos<nCount)
		{
			int * pnVert = new int[m_nDataCount];
			for(int n=0; n<m_nDataCount; n++)
				pnVert[n] = INVALID_INT;
			if (m_nDataBeginPos + m_nDataCount <= nCount)
				calcVertPos((int *)m_pData + m_nDataBeginPos,m_nDataCount,pnVert,m_rtType,m_nReferValue);
			else
				calcVertPos((int *)m_pData + m_nDataBeginPos,nCount - m_nDataBeginPos ,pnVert,m_rtType,m_nReferValue);
			drawTick(c_pDC,m_nDataCount,pnVert,RGB(255,0,0),RGB(0,255,0));
			delete [] pnVert;
		}
	}
}

void ChartUnit::drawLinkLine(CDC * c_pDC,int c_nCount,int *c_pnVertValue,COLORREF c_cl)
{
    if (m_nDataCount == 0 || c_nCount == 0)
        return;

	if (m_nSpecialType == STRSI )//RSI
	{
		CRect r = m_rectDraw;
		r.top = getValuePos(100 * 1000);
		r.bottom = getValuePos(80 * 1000);
		c_pDC->FillRect(r,&CBrush(gpSkinManager->getColor(DANGERCOLOR)));

		r.top = getValuePos(20 * 1000);
		r.bottom = getValuePos(0);
		c_pDC->FillRect(r,&CBrush(gpSkinManager->getColor(SAFECOLOR)));

		CPen pen30(PS_SOLID,1,gpSkinManager->getColor(SAFECOLOR));
		CPen pen70(PS_SOLID,1,gpSkinManager->getColor(DANGERCOLOR));
		CPen *pOld = c_pDC->SelectObject(&pen70);
		c_pDC->MoveTo(r.left,getValuePos(70 * 1000));
		c_pDC->LineTo(r.right,getValuePos(70 * 1000));
		c_pDC->SelectObject(&pen30);
		c_pDC->MoveTo(r.left,getValuePos(30 * 1000));
		c_pDC->LineTo(r.right,getValuePos(30 * 1000));
		c_pDC->SelectObject(pOld);
	}
	
	for(int n=0; n<16; n++)
	{
		if (m_nPriceLines[n] == 0X7FFFFFFF)
			break;
		CRect r = m_rectDraw;
		CPen pen30(PS_DOT,1,gpSkinManager->getColor(AIXLINE));		
		CPen *pOld = c_pDC->SelectObject(&pen30);
		c_pDC->MoveTo(r.left,getValuePos(m_nPriceLines[n]));
		c_pDC->LineTo(r.right,getValuePos(m_nPriceLines[n]));
		c_pDC->SelectObject(pOld);
	}

	CPen penLine(m_nPenStyle,m_nLineWidth,c_cl);
	CPen penSel(PS_SOLID,1,gpSkinManager->getColor(SELCOLOR));
	
    POINT p1,p2;
	
    int nBegin = 0;
    for(nBegin=0; nBegin<c_nCount; nBegin++)
    {
        if (c_pnVertValue[nBegin] == 0x7FFFFFFF)
            continue;
        break;
    }
	
	if (c_nCount - nBegin <= 0)
		return;

	POINT *ppDot = new POINT[c_nCount - nBegin];

    p1.x = (m_pnHoriPoint[nBegin] + m_rectDraw.left + (m_nCellWidth) / 2);
    p1.y = (c_pnVertValue[nBegin]);

	ppDot[0].x = p1.x;
	ppDot[0].y = p1.y;
    int nX = 0;
	int nValidCount = 0;
    for(int n=nBegin; n<c_nCount; n++)
    {
        if (n == c_nCount)
            break;
        if (c_pnVertValue[n] == 0x7FFFFFFF)
		{
			if (nValidCount > 0)
			{
				c_pDC->SelectObject(penLine);
				c_pDC->Polyline(ppDot,nValidCount);
				if (m_nSpecialType == STTDMA || m_nSpecialType == STZF )
				{
					CRect r;
					r.SetRect(ppDot[0].x-2,ppDot[0].y-2,ppDot[0].x + 2,ppDot[0].y + 2);
                
					c_pDC->SelectObject(penSel);
					c_pDC->Rectangle(r);
				}

			}
			nValidCount = 0;
            continue;
		}
        p2.x = (m_pnHoriPoint[n] + m_rectDraw.left + (m_nCellWidth )/ 2);
        p2.y = (c_pnVertValue[n]);
		ppDot[nValidCount].x = p2.x;
		ppDot[nValidCount].y = p2.y;
		nValidCount++;

        //c_pDC->SelectObject(penLine);
		//c_pDC->MoveTo(p1);
		//c_pDC->LineTo(p2);
        
		if (m_psBz)
		{
			if (m_psBz[this->m_nDataBeginPos + n] == -1)
			{
				//红三角
				CBrush br(RGB(255,0,0));
				CPen tpen(PS_SOLID,1,RGB(255,0,0));
				POINT *pp = new POINT[4];
				pp[0].x = p2.x;		pp[0].y = p2.y;
				pp[1].x = p2.x - 5; pp[1].y = p2.y + 12;
				pp[2].x = p2.x + 5; pp[2].y = p2.y + 12;
				pp[3].x = p2.x;		pp[3].y = p2.y;
				CBrush *old = c_pDC->SelectObject(&br);
				CPen *oldt = c_pDC->SelectObject(&tpen);
				c_pDC->Polygon(pp,4);
				c_pDC->SelectObject(old);
				c_pDC->SelectObject(oldt);
				delete [] pp;
			}
			else
			if (m_psBz[this->m_nDataBeginPos + n] == 1)
			{
				//绿三角
				CBrush br(RGB(0,255,0));
				CPen tpen(PS_SOLID,1,RGB(0,255,0));
				POINT *pp = new POINT[4];
				pp[0].x = p2.x;		pp[0].y = p2.y;
				pp[1].x = p2.x - 5; pp[1].y = p2.y - 12;
				pp[2].x = p2.x + 5; pp[2].y = p2.y - 12;
				pp[3].x = p2.x;		pp[3].y = p2.y;
				CBrush *old = c_pDC->SelectObject(&br);
				CPen *oldt = c_pDC->SelectObject(&tpen);
				c_pDC->Polygon(pp,4);
				c_pDC->SelectObject(old);
				c_pDC->SelectObject(oldt);
				delete [] pp;
			}
		}
        p1 = p2;
        if (m_bSelected)
        {
            if ((m_pnHoriPoint[n] - nX) > 30)
            {
                //绘制选中点
                CRect r;
				r.SetRect(p2.x-2,p2.y-2,p2.x + 2,p2.y + 2);
                
                c_pDC->SelectObject(penSel);
				c_pDC->Rectangle(r);                
                nX = m_pnHoriPoint[n];
            }
        }
    }    
	if (nValidCount > 0)
	{
		c_pDC->SelectObject(penLine);
		c_pDC->Polyline(ppDot,nValidCount);
		if (m_nSpecialType == STTDMA || m_nSpecialType == STZF)
		{
			CRect r;
			r.SetRect(ppDot[0].x-2,ppDot[0].y-2,ppDot[0].x + 2,ppDot[0].y + 2);
                
			c_pDC->SelectObject(penSel);
			c_pDC->Rectangle(r);
		}
	}
	delete [] ppDot;
}


void ChartUnit::drawTick(CDC * c_pDC,int c_nCount,int *c_pnVertValue,COLORREF c_clUp,COLORREF c_clDown)
{
    if (m_nDataCount == 0 || c_nCount == 0)
        return;
	if (m_nMaxValue == 0XFFFFFFFF)
		return;
	if (m_nMinValue == 0X7FFFFFFF)
		return;

	if (m_nSpecialType == STMARKETGUANGDU)//市场广度不画线
	{
		CRect r = m_rectDraw;
		r.top = getValuePos(100 * 10000);
		r.bottom = getValuePos(88 * 10000);
		c_pDC->FillRect(r,&CBrush(gpSkinManager->getColor(DANGERCOLOR)));

		r.top = getValuePos(38 * 10000);
		r.bottom = getValuePos(0);
		c_pDC->FillRect(r,&CBrush(gpSkinManager->getColor(SAFECOLOR)));
		return;
	}

	if (m_nSpecialType == STMARKETKUANDU)//市场广度不画线
	{
		CRect r = m_rectDraw;
		r.top = getValuePos(100 * 10);
		r.bottom = getValuePos(70 * 10);
		c_pDC->FillRect(r,&CBrush(gpSkinManager->getColor(DANGERCOLOR)));

		r.top = getValuePos(18 * 10);
		r.bottom = getValuePos(0);
		c_pDC->FillRect(r,&CBrush(gpSkinManager->getColor(SAFECOLOR)));
		return;
	}

	CBrush brUp(c_clUp);
	CBrush brDown(c_clDown);
	CPen penUp(PS_SOLID,1,c_clUp);
	CPen penDown(PS_SOLID,1,c_clDown);
    CRect rect;
	
    int nBegin = 0;
    for(nBegin=0; nBegin<c_nCount; nBegin++)
    {
        if (c_pnVertValue[nBegin] == 0x7FFFFFFF)
            continue;
        break;
    }
	
    int nX = 0;
    for(int n=nBegin; n<c_nCount; n++)
    {
        if (n == c_nCount)
            break;
        if (c_pnVertValue[n] == 0x7FFFFFFF)
            continue;
		rect.left = m_pnHoriPoint[n] + m_rectDraw.left;// + (m_nCellWidth+m_nCellSpace) ;
		rect.top = c_pnVertValue[n];
		rect.right = rect.left + m_nCellWidth+m_nCellSpace;
		rect.bottom = m_nZeroY;
		if (m_cuType == CUTick)
		{
			if (rect.top < rect.bottom)
				c_pDC->FillRect(rect,&brUp);
			else
			{			
				rect.bottom = rect.top;
				rect.top = m_nZeroY;
				c_pDC->FillRect(rect,&brDown);
			}
		}
		else
		{
			if (rect.top < rect.bottom)
				c_pDC->SelectObject(penUp);
			else
				c_pDC->SelectObject(penDown);
			c_pDC->MoveTo(rect.left + rect.Width()/2,rect.top);
			c_pDC->LineTo(rect.left + rect.Width()/2,rect.bottom);
		}
    }    
}

void ChartUnit::drawTrend(CDC * c_pDC)
{
    if (m_nDataCount == 0)
        return;

    MinUnit * pBlock = (MinUnit *)m_pData;
	int nMinItemCount = m_nDataLen / sizeof(MinUnit);
    if (!pBlock)
        return;
    if (nMinItemCount == 0)
        return;

    if (m_nDataCount > nMinItemCount)
        return;

    int * pnVert = new int[m_nDataCount];
    for(int n=0; n<m_nDataCount; n++)
        pnVert[n] = pBlock[n + m_nDataBeginPos].NewPrice;

    calcVertPos(pnVert,m_nDataCount,pnVert,RTMID,m_nReferValue);
    drawLinkLine(c_pDC,m_nDataCount,pnVert,gpSkinManager->getColor(TRENDLINE));

	if (m_bIsIndex == false)
	{
		for(int n=0; n<m_nDataCount;n++ )
			pnVert[n] = pBlock[n + m_nDataBeginPos].AvgPrice;

		calcVertPos(pnVert,m_nDataCount,pnVert,RTMID,m_nReferValue);
		drawLinkLine(c_pDC,m_nDataCount,pnVert,gpSkinManager->getColor(TRENDMALINE));
	}
    delete [] pnVert;    
}

void ChartUnit::drawTrendVol(CDC * c_pDC)
{
    if (m_nDataCount == 0)
        return;

    MinUnit * pBlock = (MinUnit *)m_pData;
	int nMinItemCount = m_nDataLen / sizeof(MinUnit);
    if (!pBlock)
        return;
    if (nMinItemCount == 0)
        return;

    if (m_nDataCount > nMinItemCount)
        return;

    if (m_nHoriCount < m_nDataCount)
        return;

    int * pnVert = new int[m_nDataCount];
    for(int n=0; n<m_nDataCount; n++)
        pnVert[n] = pBlock[n + m_nDataBeginPos].Volume;

    calcVertPos(pnVert,m_nDataCount,pnVert,RTZERO,0);
	CPen pen(PS_SOLID,1,gpSkinManager->getColor(TRENDVOL));
	CPen *pOldPen = c_pDC->SelectObject(&pen);
    POINT p1,p2;
    for(int n=0; n<m_nDataCount; n++)
    {
        p1.x = (m_pnHoriPoint[n] + m_rectDraw.left);
        p1.y = (pnVert[n]);
        p2.x = (m_pnHoriPoint[n] + m_rectDraw.left);
        p2.y = (m_rectDraw.bottom);
		c_pDC->MoveTo(p1);
		c_pDC->LineTo(p2);
    }
	c_pDC->SelectObject(pOldPen);
    delete [] pnVert;
}

void ChartUnit::drawTradeArea(CDC * c_pDC,int c_nDays,int c_n5Up,int c_n5Down,int c_n1Up,int c_n1Down)
{
    KLINE * pBlock = (KLINE *)m_pData;
	int nBlockItemCount = m_nDataLen / sizeof(KLINE);
    if (pBlock == NULL)
        return;
    if (nBlockItemCount <= c_nDays + 2)
        return;

	int nTime = pBlock[nBlockItemCount - c_nDays - 1].day;
	int n[2];

	n[1] = c_n1Down;
	n[0] = c_n1Up;
	calcVertPos(n,2,n,RTMIN,m_nMinValue);

	int nPos = getPosByTime(nTime);
	int nX =   getXByPos(nPos);
	nX = m_rectDraw.left;
	CBrush br(RGB(128,128,255));
	if (n[0] > m_rectDraw.top && n[0] < m_rectDraw.bottom && n[1] > m_rectDraw.top && n[1] < m_rectDraw.bottom)
	{
		if (n[0] == n[1])
			c_pDC->FillRect(CRect(nX,n[0]-1,m_rectDraw.right,n[1]+1),&br);
		else
		c_pDC->FillRect(CRect(nX,n[0],m_rectDraw.right,n[1]),&br);
	}

	nTime = pBlock[nBlockItemCount - 1].day;

	n[1] = c_n5Down;
	n[0] = c_n5Up;
	calcVertPos(n,2,n,RTMIN,m_nMinValue);

	nPos = getPosByTime(nTime);
	nX =   getXByPos(nPos);
	nX = m_rectDraw.left;

	CPen pen3(PS_SOLID,2,gpSkinManager->getColor(PRICEUP));
	CPen pen4(PS_SOLID,2,RGB(0,212,0));
	CPen * pPenOld = c_pDC->SelectObject(&pen3);
	if (n[0] > m_rectDraw.top && n[0] < m_rectDraw.bottom)
	{
		c_pDC->MoveTo(nX,n[0]);
		c_pDC->LineTo(m_rectDraw.right,n[0]);
	}
	c_pDC->SelectObject(&pen4);
	if (n[1] > m_rectDraw.top && n[1] < m_rectDraw.bottom)
	{
		c_pDC->MoveTo(nX,n[1]);
		c_pDC->LineTo(m_rectDraw.right,n[1]);
	}
	c_pDC->SelectObject(pPenOld);

}

void ChartUnit::drawPrice(CDC * c_pDC,int c_nNowPrice,int c_nPrice,int c_nCreatePrice,CString c_strInfo,CRect &c_rectInfo)
{
	c_rectInfo.SetRect(0,0,0,0);
	if (c_nNowPrice > 0)
	{/*
		if (c_nPrice < c_nNowPrice * 90 / 100 || c_nPrice > c_nNowPrice * 110 / 100)
			return;*/
		if (c_nNowPrice < c_nPrice * 90 / 100 || c_nNowPrice > c_nPrice * 110 / 100)
			return;
	}
	int n[2];
	n[0] = c_nPrice;
	calcVertPos(n,1,n,RTMIN,m_nMinValue);
	if (n[0] < m_rectDraw.top)
		return;
	if (n[0] > m_rectDraw.bottom)
		return;

	CBrush br(RGB(34,136,255));
	CBrush * pOldBrush = c_pDC->SelectObject(&br);
	CPen pen(PS_SOLID,2,RGB(34,136,255));//gpSkinManager->getLineColor(0));
	CPen * pPenOld = c_pDC->SelectObject(&pen);
	c_pDC->MoveTo(m_rectDraw.left,n[0]);
	c_pDC->LineTo(m_rectDraw.right,n[0]);

	CRect rect;
	CFont * pFont = c_pDC->SelectObject(gpSkinManager->m_pFontSmall);
	COLORREF cl = c_pDC->SetTextColor(RGB(255,255,255));//gpSkinManager->getColor(RIGHTTEXTCOLOR));
	int nMode = c_pDC->SetBkMode(TRANSPARENT);
	CString strText;
	if (c_nPrice == c_nCreatePrice || c_nCreatePrice == 0)
		strText.Format(_T(" %.2f"),float(c_nPrice) / 1000);
	else
		strText.Format(_T("%.2f 复权价%.2f"),float(c_nCreatePrice) / 1000,float(c_nPrice) / 1000);
	strText = c_strInfo + strText;
	CSize size = c_pDC->GetTextExtent(strText);
	rect.SetRect(m_nPriceAlertX+2,n[0] - size.cy,m_nPriceAlertX + 2 + size.cx,n[0]);
	c_pDC->Rectangle(rect);
	c_pDC->SelectObject(pPenOld);

	c_rectInfo = rect;
	c_pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	m_nPriceAlertX += 2 + size.cx;
	c_pDC->SelectObject(pOldBrush);
	c_pDC->SelectObject(pFont);
	c_pDC->SetTextColor(cl);
	c_pDC->SetBkMode(nMode);
}

void ChartUnit::drawPriceRight(CDC * c_pDC,int c_nNowPrice,int c_nPrice,CString c_strInfo)
{
	if (c_nNowPrice > 0)
	{/*
		if (c_nPrice < c_nNowPrice * 90 / 100 || c_nPrice > c_nNowPrice * 110 / 100)
			return;*/
		if (c_nNowPrice < c_nPrice * 90 / 100 || c_nNowPrice > c_nPrice * 110 / 100)
			return;
	}
	int n[2];
	n[0] = c_nPrice;
	calcVertPos(n,1,n,RTMIN,m_nMinValue);
	if (n[0] < m_rectDraw.top)
		return;
	if (n[0] > m_rectDraw.bottom)
		return;

	CBrush br(RGB(34,136,255));
	CBrush * pOldBrush = c_pDC->SelectObject(&br);
	CPen pen(PS_SOLID,2,RGB(34,136,255));//gpSkinManager->getLineColor(0));
	CPen * pPenOld = c_pDC->SelectObject(&pen);
	c_pDC->MoveTo(m_rectDraw.left,n[0]);
	c_pDC->LineTo(m_rectDraw.right,n[0]);

	CSize si = c_pDC->GetTextExtent(_T("123456."));
	CRect rect;
	rect.left = m_rectDraw.right + 2;
	rect.right = rect.left + si.cx;
	rect.bottom = n[0];
	rect.top = rect.bottom - 24;
	CFont * pFont = c_pDC->SelectObject(gpSkinManager->m_pFontSmall);
	COLORREF cl = c_pDC->SetTextColor(RGB(255,255,255));//gpSkinManager->getColor(RIGHTTEXTCOLOR));
	int nMode = c_pDC->SetBkMode(TRANSPARENT);
	CSize size = c_pDC->GetTextExtent(c_strInfo);
	c_pDC->Rectangle(CRect(rect.left - 2,rect.bottom - size.cy - 1,rect.left + size.cx + 1,rect.bottom + size.cy + 1));
	c_pDC->SelectObject(pPenOld);

	c_pDC->DrawText(c_strInfo,rect,DT_LEFT|DT_BOTTOM|DT_SINGLELINE);
	CString strText;
	strText.Format(_T("%.2f"),float(c_nPrice) / 1000);
	rect.top = rect.bottom;
	rect.bottom = rect.top + 24;
	c_pDC->DrawText(strText,rect,DT_LEFT|DT_TOP|DT_SINGLELINE);
	c_pDC->SelectObject(pOldBrush);
	c_pDC->SelectObject(pFont);
	c_pDC->SetTextColor(cl);
	c_pDC->SetBkMode(nMode);
}

void ChartUnit::drawCutAlert(CDC * c_pDC,int c_nFDown,int c_nFUp)
{
    KLINE * pBlock = (KLINE *)m_pData;
	int nBlockItemCount = m_nDataLen / sizeof(KLINE);
    if (pBlock == NULL)
        return;
    if (nBlockItemCount < 5)
        return;

	int c;
	c = pBlock[nBlockItemCount-1].close;

	int nTime = pBlock[nBlockItemCount - 1].day;
	int n5Time = nTime;
	if (nBlockItemCount > 5)
		n5Time = pBlock[nBlockItemCount - 6].day;
	int n[4];
	n[0] = pBlock[nBlockItemCount - 1].high;
	n[1] = pBlock[nBlockItemCount - 1].low;
	n[2] = c_nFDown;
	n[3] = c_nFUp;

	calcVertPos(n,4,n,RTMIN,m_nMinValue);

	if (n[2] > m_rectDraw.bottom - 16 || n[2] < m_rectDraw.top)
		return;

	int nPos = getPosByTime(nTime);
	int nX = getXByPos(nPos);
	nPos = getPosByTime(n5Time);
	int n5X = getXByPos(nPos);

	CPen pen(PS_SOLID,2,gpSkinManager->getColor(PRICEDOWN));
	CPen * pOldPen = c_pDC->SelectObject(&pen);
	c_pDC->MoveTo(n5X,n[2]);
	c_pDC->LineTo(m_rectDraw.right,n[2]);
	c_pDC->SelectObject(pOldPen);
	CFont *pFont = c_pDC->SelectObject(gpSkinManager->m_pFontSmall);
	int nMode = c_pDC->SetBkMode(TRANSPARENT);
	COLORREF cl = c_pDC->SetTextColor(RGB(255,255,255));
	CBrush br(RGB(0,0,255));
	CBrush * pOldBr = c_pDC->SelectObject(&br);
	CSize size = c_pDC->GetTextExtent(_T("止损线"));
	c_pDC->Rectangle(CRect(m_rectDraw.right-size.cx-2,n[2]-size.cy-2,m_rectDraw.right-2,n[2]-2));
	c_pDC->DrawText(_T("止损线"),CRect(nX,n[2]-size.cy-2,m_rectDraw.right-2,n[2]-2),DT_RIGHT|DT_BOTTOM|DT_SINGLELINE);
	c_pDC->SelectObject(pOldBr);
	c_pDC->SetTextColor(cl);
	c_pDC->SetBkMode(nMode);
	c_pDC->SelectObject(pFont);
	if (true)
	{
		CPoint pt;
		if (c_nFDown > c)//止损卖出
		{
			pt.x = nX;
			pt.y = n[0] - 4;
			gpSkinManager->drawSJXDOWN(c_pDC,pt,12,6,2,RGB(0,255,0));
		}/*
		else
		if (fUp < c)//止损买入
		{
			pt.x = nX;
			pt.y = n[1]  + 16;
			gpSkinManager->drawSJXUP(c_pDC,pt,12,6,2,RGB(255,0,0));
		}*/
	}
}

void ChartUnit::drawKLine(CDC * c_pDC)
{
    KLINE * pBlock = (KLINE *)m_pData;
	int nBlockItemCount = m_nDataLen / sizeof(KLINE);
    if (pBlock == NULL)
        return;
    if (nBlockItemCount <= 0)
        return;

	CPoint ptMax(-1,-1);
	CPoint ptMin(0x7FFFFFFF,0x7FFFFFFF);
	int nMax,nMin,nMaxIndex,nMinIndex;
	nMax = -1;
	nMin = 0x7FFFFFFF;
	nMaxIndex = -1;
	nMinIndex = -1;
    int *pnOpen,*pnClose,*pnHigh,*pnLow;
    pnOpen = new int[m_nDataCount];
    pnClose = new int[m_nDataCount];
    pnHigh = new int[m_nDataCount];
    pnLow = new int[m_nDataCount];
    for(int n=0; n<m_nDataCount; n++)
    {
        pnOpen[n] = pBlock[n + m_nDataBeginPos].open;
        pnClose[n] = pBlock[n + m_nDataBeginPos].close;
        pnHigh[n] = pBlock[n + m_nDataBeginPos].high;
        pnLow[n] = pBlock[n + m_nDataBeginPos].low;
		if (pnHigh[n] > nMax)
		{
			nMax = pnHigh[n];
			nMaxIndex = n;
		}
		if (pnLow[n] < nMin)
		{
			nMin = pnLow[n];
			nMinIndex = n;
		}
    }
    calcVertPos(pnOpen,m_nDataCount,pnOpen,RTMIN,m_nMinValue);
    calcVertPos(pnClose,m_nDataCount,pnClose,RTMIN,m_nMinValue);
    calcVertPos(pnHigh,m_nDataCount,pnHigh,RTMIN,m_nMinValue);
    calcVertPos(pnLow,m_nDataCount,pnLow,RTMIN,m_nMinValue);
    if (m_nCellWidth > 0)
	{
		if (nMaxIndex >= 0 && nMinIndex >= 0)
		{
			ptMax.x = m_rectDraw.left + m_pnHoriPoint[nMaxIndex] + m_nCellWidth / 2;
			ptMax.y = pnHigh[nMaxIndex];
			ptMin.x = m_rectDraw.left + m_pnHoriPoint[nMinIndex] + m_nCellWidth / 2;
			ptMin.y = pnLow[nMinIndex];
		}
	}
	else
	{
		if (nMaxIndex >= 0 && nMinIndex >= 0)
		{
			ptMax.x = m_rectDraw.left + m_pnHoriPoint[nMaxIndex];
			ptMax.y = pnHigh[nMaxIndex];
			ptMin.x = m_rectDraw.left + m_pnHoriPoint[nMinIndex];
			ptMin.y = pnLow[nMinIndex];
		}
	}
    CBrush brushUp(gpSkinManager->getColor(KUP));
    CBrush brushDown(gpSkinManager->getColor(KDOWN));
	CBrush brushNormal(gpSkinManager->getColor(KNORMAL));

    POINT pHigh,pLow;
    POINT pOpen,pClose;

	CPen LinePenSolidUp(PS_SOLID,1,gpSkinManager->getColor(KUP));
	CPen LinePenSolidDown(PS_SOLID,1,gpSkinManager->getColor(KDOWN));
	CPen LinePenSolidNormal(PS_SOLID,1,gpSkinManager->getColor(KNORMAL));
	
	bool bSel = false;
	bool bBuy = false;
	bool bSell = false;
	bool bZLMM = false;
	bool bJumpBuy = false;
	if (m_psBz != NULL)
		bZLMM = true;
    CRect rectBox;
    int x1,y1,x2,y2;
    int nX = 0;
    for(int n=0; n<m_nDataCount; n++)
    {
		bSel = false;
		bBuy = false;
		bSell = false;
		bJumpBuy = false;/*
		if (n>4 && pBlock[n+m_nDataBeginPos].close > pBlock[n+m_nDataBeginPos-2].close
		&& pBlock[n+m_nDataBeginPos-1].close > pBlock[n+m_nDataBeginPos-3].close)
			bSel = true;*/
/*demark call buy
(OP >= CL1) AND (HI1 > (CL2 + 1.618*(HI2-LO2))) AND (HI1 > HI4) AND (HI1 > HI5) AND (CL1 > CL2) AND (CL1 > CL3) AND (CL1 > CL4) AND (CL1 > CL5)
*/
		
		if (n+m_nDataBeginPos>6 
		&& (pBlock[n+m_nDataBeginPos].open >= pBlock[n+m_nDataBeginPos-1].close) 
		&& (pBlock[n+m_nDataBeginPos-1].high > pBlock[n+m_nDataBeginPos-2].close + (int(pBlock[n+m_nDataBeginPos-2].high)-int(pBlock[n+m_nDataBeginPos-2].low)))
		//&& (pBlock[n+m_nDataBeginPos-1].high > pBlock[n+m_nDataBeginPos-2].close + 1.382*(int(pBlock[n+m_nDataBeginPos-2].high)-int(pBlock[n+m_nDataBeginPos-2].low)))
		//&& (pBlock[n+m_nDataBeginPos-1].high > pBlock[n+m_nDataBeginPos-2].close + 1.618*(int(pBlock[n+m_nDataBeginPos-2].high)-int(pBlock[n+m_nDataBeginPos-2].low)))
		&& (pBlock[n+m_nDataBeginPos-1].high > pBlock[n+m_nDataBeginPos-4].high) 
		&& (pBlock[n+m_nDataBeginPos-1].high > pBlock[n+m_nDataBeginPos-5].high) 
		&& (pBlock[n+m_nDataBeginPos-1].close > pBlock[n+m_nDataBeginPos-2].close)
		&& (pBlock[n+m_nDataBeginPos-1].close > pBlock[n+m_nDataBeginPos-3].close) 
		&& (pBlock[n+m_nDataBeginPos-1].close > pBlock[n+m_nDataBeginPos-4].close) 
		&& (pBlock[n+m_nDataBeginPos-1].close > pBlock[n+m_nDataBeginPos-5].close))
			bSell = true;

		if (n+m_nDataBeginPos>6 
		&& (pBlock[n+m_nDataBeginPos].open <= pBlock[n+m_nDataBeginPos-1].close) 
		&& (pBlock[n+m_nDataBeginPos-1].low > pBlock[n+m_nDataBeginPos-2].close - 1.318*(int(pBlock[n+m_nDataBeginPos-2].high)-int(pBlock[n+m_nDataBeginPos-2].low)))
		//&& (pBlock[n+m_nDataBeginPos-1].high > pBlock[n+m_nDataBeginPos-2].close + 1.618*(int(pBlock[n+m_nDataBeginPos-2].high)-int(pBlock[n+m_nDataBeginPos-2].low)))
		&& (pBlock[n+m_nDataBeginPos-2].high > pBlock[n+m_nDataBeginPos-3].low) 
		&& (pBlock[n+m_nDataBeginPos-1].high > pBlock[n+m_nDataBeginPos-2].low) 
		&& (pBlock[n+m_nDataBeginPos-1].low < pBlock[n+m_nDataBeginPos-4].low) 
		&& (pBlock[n+m_nDataBeginPos-1].low < pBlock[n+m_nDataBeginPos-5].low) 
		&& (pBlock[n+m_nDataBeginPos-1].close < pBlock[n+m_nDataBeginPos-2].close)
		&& (pBlock[n+m_nDataBeginPos-1].close < pBlock[n+m_nDataBeginPos-3].close) 
		&& (pBlock[n+m_nDataBeginPos-1].close < pBlock[n+m_nDataBeginPos-4].close) 
		&& (pBlock[n+m_nDataBeginPos-1].close < pBlock[n+m_nDataBeginPos-5].close))
			bBuy = true;

		if (n+m_nDataBeginPos > 10)
		{
			//短线指标
			//bJumpBuy = IsJumpDownBuy(pBlock,n+m_nDataBeginPos);
		}
		if (bZLMM)
		{
			if (m_psBz[n+m_nDataBeginPos] > 0)
				c_pDC->SelectObject(LinePenSolidDown);
			else
				c_pDC->SelectObject(LinePenSolidUp);
		}
		else
		{
			if (pBlock[n+m_nDataBeginPos].close > pBlock[n+m_nDataBeginPos].open)
				c_pDC->SelectObject(LinePenSolidUp);
			else
			if (pBlock[n+m_nDataBeginPos].close < pBlock[n+m_nDataBeginPos].open)
				c_pDC->SelectObject(LinePenSolidDown);
			else
				c_pDC->SelectObject(LinePenSolidNormal);
		}
		
		if (m_nCellWidth > 0)
			x1 = m_rectDraw.left + m_pnHoriPoint[n] + m_nCellWidth / 2;
		else
			x1 = m_rectDraw.left + m_pnHoriPoint[n];
        y1 = pnHigh[n];
        pHigh.x = (x1);
        pHigh.y = (y1);
        x2 = x1;
        y2 = pnLow[n];
        pLow.x = (x2);
        pLow.y = (y2);
        pOpen.x = (x1);
        pOpen.y = (pnOpen[n]);
        pClose.x = (x1);
        pClose.y = (pnClose[n]);
        if (pnOpen[n] > pnClose[n])
        {			
			c_pDC->MoveTo(pHigh);
			c_pDC->LineTo(pClose);
            c_pDC->MoveTo(pLow);
			c_pDC->LineTo(pOpen);            
        }
        else
        if (pnOpen[n] < pnClose[n])
        {
			c_pDC->MoveTo(pHigh);
			c_pDC->LineTo(pOpen);
            c_pDC->MoveTo(pClose);
			c_pDC->LineTo(pLow);            
        }
		else
		{
			c_pDC->MoveTo(pHigh);
			c_pDC->LineTo(pLow);            
		}
		if (bZLMM)
		{
			if (m_psBz[n+m_nDataBeginPos] == -1)
				drawSJX(c_pDC,pLow,true);
			else
			if (m_psBz[n+m_nDataBeginPos] == 1)
				drawSJX(c_pDC,pHigh,false);
		}

		x1 = m_rectDraw.left + m_pnHoriPoint[n];
        y1 = pnOpen[n];
        x2 = m_rectDraw.left + m_pnHoriPoint[n];
        y2 = pnClose[n];
		if (m_nCellWidth > 0)
		{
			if (y2 > y1)
				rectBox.SetRect(x1,y1,x1 + m_nCellWidth,y2);            
			else
				rectBox.SetRect(x1,y2,x1 + m_nCellWidth,y1);
		}
		else
		{
			if (y2 > y1)
				rectBox.SetRect(x1,y1,x1,y2);
			else
				rectBox.SetRect(x1,y2,x1,y1);
		}
		if (bZLMM)
		{
			if (m_psBz[n+m_nDataBeginPos] > 0)
				c_pDC->SelectObject(brushDown);
			else
				c_pDC->SelectObject(brushUp);
		}
		else
		{
			if (pBlock[n+m_nDataBeginPos].close > pBlock[n+m_nDataBeginPos].open)		
				c_pDC->SelectObject(brushUp);
			else
			if (pBlock[n+m_nDataBeginPos].close < pBlock[n+m_nDataBeginPos].open)		
				c_pDC->SelectObject(brushDown);
			else
				c_pDC->SelectObject(brushNormal);
		}
				
		if (pBlock[n+m_nDataBeginPos].close != pBlock[n+m_nDataBeginPos].open && rectBox.Height() > 0)
		{			
			c_pDC->Rectangle(rectBox);
		}
		else
		{
			c_pDC->MoveTo(rectBox.left,rectBox.top);
			c_pDC->LineTo(rectBox.right,rectBox.bottom);
		}

        
        if (m_bSelected)
        {
            if ((m_pnHoriPoint[n] - nX) > 30)
            {
                //绘制选中点
                CRect r;
                r.SetRect(rectBox.left,rectBox.top-2,rectBox.left+4,rectBox.top+2);
                c_pDC->SelectObject(LinePenSolidNormal);
				c_pDC->Rectangle(r);                
                nX = m_pnHoriPoint[n];
            }
        }
    }

		//绘制最高最低点
	if (nMaxIndex >= 0 && nMinIndex >= 0)
	{
		CFont * pOldFont = c_pDC->SelectObject(gpSkinManager->m_pFontSmall);
		c_pDC->SelectObject(&LinePenSolidNormal);
		COLORREF cl = c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
		CString strText;
		strText.Format(_T("%.2f"),float(nMax)/1000);
		CSize size = c_pDC->GetTextExtent(strText);
		if (ptMax.x + 10 + size.cx > m_rectDraw.right)
		{
			c_pDC->MoveTo(ptMax);
			c_pDC->LineTo(ptMax.x - 10,ptMax.y + size.cy/2);
			c_pDC->TextOut(ptMax.x - 10 - size.cx,ptMax.y - 2,strText);
		}
		else
		{
			c_pDC->MoveTo(ptMax);
			c_pDC->LineTo(ptMax.x + 10,ptMax.y + size.cy/2);
			c_pDC->TextOut(ptMax.x + 10,ptMax.y - 2,strText);
		}
		strText.Format(_T("%.2f"),float(nMin)/1000);
		size = c_pDC->GetTextExtent(strText);
		if (ptMin.x + 10 + size.cx > m_rectDraw.right)
		{
			c_pDC->MoveTo(ptMin);
			c_pDC->LineTo(ptMin.x - 10,ptMin.y - size.cy/2);
			c_pDC->TextOut(ptMin.x - 10 - size.cx,ptMin.y - size.cy,strText);
		}
		else
		{
			c_pDC->MoveTo(ptMin);
			c_pDC->LineTo(ptMin.x + 10,ptMin.y - size.cy/2);
			c_pDC->TextOut(ptMin.x + 10,ptMin.y - size.cy,strText);
		}
		c_pDC->SelectObject(pOldFont);
		c_pDC->SetTextColor(cl);
	}

    delete [] pnOpen;
    delete [] pnClose;
    delete [] pnHigh;
    delete [] pnLow;
}

void ChartUnit::drawKLineAttach(CDC * c_pDC)
{
    KLINE * pBlock = (KLINE *)m_pData;
	int nBlockItemCount = m_nDataLen / sizeof(KLINE);
    if (pBlock == NULL)
        return;
    if (nBlockItemCount <= 0)
        return;

    int *pnOpen,*pnClose,*pnHigh,*pnLow;
    pnOpen = new int[m_nDataCount];
    pnClose = new int[m_nDataCount];
    pnHigh = new int[m_nDataCount];
    pnLow = new int[m_nDataCount];
	for(int n=0; n<m_nDataCount; n++)
	{
		pnOpen[n] = 0x7FFFFFFF;
		pnClose[n] = 0x7FFFFFFF;
		pnHigh[n] = 0x7FFFFFFF;
		pnLow[n] = 0x7FFFFFFF;
	}
    for(int n=0; n<m_nDataCount; n++)
    {
		if ((n + m_nDataBeginPos) >= nBlockItemCount)
			break;
        pnOpen[n] = pBlock[n + m_nDataBeginPos].open;
        pnClose[n] = pBlock[n + m_nDataBeginPos].close;
        pnHigh[n] = pBlock[n + m_nDataBeginPos].high;
        pnLow[n] = pBlock[n + m_nDataBeginPos].low;
    }
    calcVertPos(pnOpen,m_nDataCount,pnOpen,RTMIN,m_nMinValue);
    calcVertPos(pnClose,m_nDataCount,pnClose,RTMIN,m_nMinValue);
    calcVertPos(pnHigh,m_nDataCount,pnHigh,RTMIN,m_nMinValue);
    calcVertPos(pnLow,m_nDataCount,pnLow,RTMIN,m_nMinValue);
    
    CBrush brushUp(gpSkinManager->getColor(AIXTEXT));
    CBrush brushDown(gpSkinManager->getColor(AIXTEXT));
	CBrush brushNormal(gpSkinManager->getColor(AIXTEXT));

    POINT pHigh,pLow;
    POINT pOpen,pClose;

	CPen LinePenSolidUp(PS_SOLID,1,gpSkinManager->getColor(AIXTEXT));
	CPen LinePenSolidDown(PS_SOLID,1,gpSkinManager->getColor(AIXTEXT));
	CPen LinePenSolidNormal(PS_SOLID,1,gpSkinManager->getColor(AIXTEXT));

    CRect rectBox;
    int x1,y1,x2,y2;
    int nX = 0;
    for(int n=0; n<m_nDataCount; n++)
    {
		if ((n+m_nDataBeginPos) >= nBlockItemCount)
			break;
        if (pBlock[n+m_nDataBeginPos].close > pBlock[n+m_nDataBeginPos].open)
            c_pDC->SelectObject(LinePenSolidUp);
        else
        if (pBlock[n+m_nDataBeginPos].close < pBlock[n+m_nDataBeginPos].open)
            c_pDC->SelectObject(LinePenSolidDown);
        else
            c_pDC->SelectObject(LinePenSolidNormal);

        x1 = m_rectDraw.left + (m_nCellWidth + m_nCellSpace) * n + m_nCellWidth / 2;
        y1 = pnHigh[n];
        pHigh.x = (x1);
        pHigh.y = (y1);
        x2 = x1;
        y2 = pnLow[n];
        pLow.x = (x2);
        pLow.y = (y2);
        pOpen.x = (x1);
        pOpen.y = (pnOpen[n]);
        pClose.x = (x1);
        pClose.y = (pnClose[n]);
        if (pnOpen[n] > pnClose[n])
        {			
			c_pDC->MoveTo(pHigh);
			c_pDC->LineTo(pClose);
            c_pDC->MoveTo(pLow);
			c_pDC->LineTo(pOpen);            
        }
        else
        if (pnOpen[n] < pnClose[n])
        {
			c_pDC->MoveTo(pHigh);
			c_pDC->LineTo(pOpen);
            c_pDC->MoveTo(pClose);
			c_pDC->LineTo(pLow);            
        }
		else
		{
			c_pDC->MoveTo(pHigh);
			c_pDC->LineTo(pLow);            
		}
        x1 = m_rectDraw.left + (m_nCellWidth+ m_nCellSpace) * n;
        y1 = pnOpen[n];
        x2 = m_rectDraw.left + (m_nCellWidth+ m_nCellSpace) * n;
        y2 = pnClose[n];
        if (y2 > y1)
			rectBox.SetRect(x1,y1,x1 + m_nCellWidth,y2);            
        else
            rectBox.SetRect(x1,y2,x1 + m_nCellWidth,y1);

        if (pBlock[n+m_nDataBeginPos].close > pBlock[n+m_nDataBeginPos].open)		
            c_pDC->SelectObject(brushUp);
        else
        if (pBlock[n+m_nDataBeginPos].close < pBlock[n+m_nDataBeginPos].open)		
            c_pDC->SelectObject(brushDown);
        else
            c_pDC->SelectObject(brushNormal);
		if (pBlock[n+m_nDataBeginPos].close != pBlock[n+m_nDataBeginPos].open && rectBox.Height() > 0)
			c_pDC->Rectangle(rectBox);
		else
		{
			c_pDC->MoveTo(rectBox.left,rectBox.top);
			c_pDC->LineTo(rectBox.right,rectBox.bottom);
		}
        
        if (m_bSelected)
        {
            if ((m_pnHoriPoint[n] - nX) > 30)
            {
                //绘制选中点
                CRect r;
                r.SetRect(rectBox.left-2,rectBox.top-2,rectBox.left+2,rectBox.top+2);
                c_pDC->SelectObject(LinePenSolidNormal);
				c_pDC->Rectangle(r);                
                nX = m_pnHoriPoint[n];
            }
        }

    }
    delete [] pnOpen;
    delete [] pnClose;
    delete [] pnHigh;
    delete [] pnLow;
}

void ChartUnit::drawVol(CDC * c_pDC)
{
    if (m_nDataCount == 0)
        return;

    KLINE * pBlock = (KLINE *)m_pData;
	int nBlockItemCount = m_nDataLen / sizeof(KLINE);
    if (!pBlock)
        return;
    if (nBlockItemCount == 0)
        return;

    int * pnVert = new int[m_nDataCount];
    for(int n=0; n<m_nDataCount; n++)
        pnVert[n] = pBlock[n + m_nDataBeginPos].volume/m_nDiv;

    calcVertPos(pnVert,m_nDataCount,pnVert,RTZERO,0);

	CPen LinePenSolidUp(PS_SOLID,1,gpSkinManager->getColor(KUP));
	CPen LinePenSolidDown(PS_SOLID,1,gpSkinManager->getColor(KDOWN));
	CPen LinePenSolidNormal(PS_SOLID,1,gpSkinManager->getColor(KNORMAL));

	CBrush brushDown(gpSkinManager->getColor(KDOWN));
	CBrush brushUp(gpSkinManager->getColor(KUP));
	//CBrush brushUp(gpSkinManager->getColor(99));
    CRect rect;
    int nX = 0;
    for(int n=0; n<m_nDataCount; n++)
    {
        rect.SetRect(m_pnHoriPoint[n] + m_rectDraw.left,pnVert[n],m_pnHoriPoint[n] + m_rectDraw.left + m_nCellWidth ,pnVert[n] + m_rectDraw.bottom-pnVert[n]);

        if (pBlock[n + m_nDataBeginPos].close >= pBlock[n + m_nDataBeginPos].open)
        {
            c_pDC->SelectObject(LinePenSolidUp);
			c_pDC->SelectObject(brushUp);
			c_pDC->Rectangle(rect);
        }
        else
        {
			c_pDC->SelectObject(LinePenSolidDown);			
			c_pDC->FillRect(rect,&brushDown);
        }

        if (m_bSelected)
        {
            if ((m_pnHoriPoint[n] - nX) > 30)
            {
                //绘制选中点
                CRect r;
                r.SetRect(rect.left-2,rect.top-2,rect.left + 2,rect.top + 2);
				c_pDC->SelectObject(LinePenSolidNormal);
				c_pDC->Rectangle(r);                
                nX = m_pnHoriPoint[n];
            }
        }

    }
    delete [] pnVert;
}

void ChartUnit::calcVertPos(int *c_pnValue, int c_nCount, int *c_pnVert, ReferType c_rtType, int c_nReferValue)
{
    if (m_nMaxValue == -1)
        return;
    if (m_nMinValue == 0X7FFFFFFF)
        return;

    //if (m_nMaxValue == m_nMinValue)
    //    return;

    float fPerY = m_rectDraw.Height();
    if (c_rtType == RTZERO)
    {
        fPerY /= (m_nMaxValue);
    }
    else
    if (c_rtType == RTMIN)
    {
		if (m_nMaxValue == m_nMinValue)
			return;
		if (m_atType == AIXLG)
		{
			float f = m_nMaxValue;
			f = log10(f/m_nMinValue);
			fPerY /= f;
		}
		else
        fPerY /= (m_nMaxValue - m_nMinValue);
    }
    else
    if (c_rtType == RTMID)
    {        
        if (abs(m_nMaxValue - c_nReferValue) > abs(m_nMinValue - c_nReferValue))
            fPerY /= abs(m_nMaxValue - c_nReferValue) * 2;
        else           
            fPerY /= abs(m_nMinValue - c_nReferValue) * 2;
    }

    for(int n=0; n<c_nCount; n++)
    {
        if (c_pnValue[n] == 0X7FFFFFFF)
        {
            c_pnVert[n] = 0X7FFFFFFF;
            continue;
        }

        float fValue;
        if (c_rtType == RTZERO)
        {
            fValue = c_pnValue[n] - c_nReferValue;
			m_nZeroY = m_rectDraw.bottom;
            c_pnVert[n] = m_rectDraw.bottom - fValue * fPerY;
        }
        else
        if (c_rtType == RTMIN)
        {
            fValue = c_pnValue[n];
			if (m_atType == AIXLG)
			{
				if (fValue <= 0)
					fValue = 0;
				fValue = log10(fValue/c_nReferValue);
			}
			else
				fValue -= c_nReferValue;
			m_nZeroY = m_rectDraw.bottom;
            c_pnVert[n] = m_rectDraw.bottom - fValue * fPerY;
        }
        else
        if (c_rtType == RTMID)
        {
            fValue = c_pnValue[n];
            fValue -= c_nReferValue;
			m_nZeroY = m_rectDraw.top + m_rectDraw.Height()/2;
            c_pnVert[n] = float(m_rectDraw.top + m_rectDraw.Height()/2) - fValue * fPerY;
        }
    }
    m_fPerY = fPerY;
}

void ChartUnit::calcPerY()
{
    if (m_nMaxValue == -1)
        return;
    if (m_nMinValue == 0X7FFFFFFF)
        return;

    if (m_nMaxValue == m_nMinValue)
        return;

    float fPerY = m_rectDraw.Height();
    if (m_rtType == RTZERO)
    {
        fPerY /= (m_nMaxValue);
		m_nZeroY = m_rectDraw.bottom;
    }
    else
    if (m_rtType == RTMIN)
    {
		if (m_atType == AIXLG)//对数坐标
		{
			float f = m_nMaxValue;
			f = log10(f/m_nMinValue);
			fPerY /= f;
		}
		else
			fPerY /= (m_nMaxValue - m_nMinValue);
		m_nZeroY = m_rectDraw.bottom;
    }
    else
    if (m_rtType == RTMID)
    {        
        if (abs(m_nMaxValue - m_nReferValue) > abs(m_nMinValue - m_nReferValue))
            fPerY /= abs(m_nMaxValue - m_nReferValue) * 2;
        else           
            fPerY /= abs(m_nMinValue - m_nReferValue) * 2;
		m_nZeroY = m_rectDraw.top + m_rectDraw.Height()/2;
    }
    m_fPerY = fPerY;
}

//根据值取Y轴的位置
int ChartUnit::getValuePos(int c_nValue)
{
    if (m_fPerY == 0)
        return 0;

    int nRet = 0;
    float fValue = c_nValue;
	if (m_cuType == CUTick || m_cuType == CUTickLine || m_cuType == CULink)
	{
        fValue -= m_nReferValue;
        fValue *= m_fPerY;
        fValue = m_nZeroY - fValue;//m_rectDraw.top + m_rectDraw.Height()/2 - fValue;
        nRet = fValue;
	}
	else
    if (m_cuType == CUTrend)
    {                
        fValue -= m_nReferValue;
        fValue *= m_fPerY;
        fValue = m_rectDraw.top + m_rectDraw.Height()/2 - fValue;
        nRet = fValue;
    }
    else
    if (m_cuType == CUTrendVol)
    {
        fValue *= m_fPerY;
        fValue = m_rectDraw.bottom - fValue;
        nRet = fValue;
    }
    else
    if (m_cuType == CUQCT)
    {        
		if (m_atType == AIXLG)
		{
			fValue = log10(fValue/m_nReferValue);
		}
		else
			fValue -= m_nReferValue;
        fValue *= m_fPerY;
        fValue = m_rectDraw.bottom - fValue;
        nRet = fValue;
    }
    else
    if (m_cuType == CUKLine)
    {        
		if (m_atType == AIXLG)
		{
			if (fValue <= 0)
				return INVALID_INT;
			fValue = log10(fValue/m_nReferValue);
		}
		else
			fValue -= m_nReferValue;
        fValue *= m_fPerY;
        fValue = m_rectDraw.bottom - fValue;
        nRet = fValue;
    }
    else
    if (m_cuType == CUVOL)
    {
        fValue *= m_fPerY;
        fValue = m_rectDraw.bottom - fValue;
        nRet = fValue;
    }

    return nRet;
}
CString ChartUnit::getXValueString(int c_nXPos,unsigned short c_usCycle)
{
	CString strRet;
	if (m_cuType == CUTrend)
	{
        MinUnit * pBlock = (MinUnit *)m_pData;
        if (pBlock && c_nXPos >=0 && c_nXPos < m_nHoriCount)//m_nDataCount)
        {
			strRet.Format(_T("%02d:%02d"),pBlock[c_nXPos + m_nDataBeginPos].Time/60,pBlock[c_nXPos + m_nDataBeginPos].Time%60);
			return strRet;
		}
	}
	else
	if (m_cuType == CUKLine)
	{
        KLINE * pBlock = (KLINE *)m_pData;
		if (pBlock && c_nXPos >=0 && c_nXPos < this->m_nHoriCount)//m_nDataCount)
		{
			int nDay = pBlock[c_nXPos + m_nDataBeginPos].day;
			if (c_usCycle == 5 || c_usCycle == 6 || c_usCycle == 7)
				strRet.Format(_T("%d"),nDay);
			else
				strRet.Format(_T("%d/%d %d:%.2d"),nDay / 1000000 % 100,nDay / 10000 % 100,(nDay % 10000)/60,(nDay % 10000) % 60);
			return strRet;
		}

	}
	return strRet;
}

CString ChartUnit::getYValueString(int c_nY,int c_nMaxLen)
{
    int nValue;
    nValue = getYValueInt(c_nY);
    if (nValue == 0X7FFFFFFF)
        return _T("");

    CString strRet;
    float fValue = nValue;
    if (m_nPrecision == 0)
    {		
		if (m_bIsIndex && int(fValue/m_nMultiplier)>10000)
			strRet.Format(_T("%d万"),int(fValue/m_nMultiplier)/10000);
		else
		{
			//if (int(fValue/m_nMultiplier)>10000)
			//	strRet.Format(_T("%d万"),int(fValue/m_nMultiplier)/10000);
			//else
				strRet.Format(_T("%d"),int(fValue/m_nMultiplier));
		}
    }
    else
    {
        CString strFormat;
        strFormat.Format(_T("%%.%df"),m_nPrecision);
        strRet.Format(strFormat,fValue / m_nMultiplier);

		if (c_nMaxLen > 0)
		{
			int nPoint = strRet.Find('.');
			if (nPoint >= c_nMaxLen)
				strRet = strRet.Left(nPoint);
		}
    }
    return strRet;
}

CString ChartUnit::getYValuePercentString(int c_nY)
{
    int nValue;
    nValue = getYValueInt(c_nY);
    if (nValue == 0X7FFFFFFF)
        return _T("");

    CString strRet;
    float fValue = nValue;
	if (m_nReferValue > 0)
    strRet.Format(_T("%.2f%%"),(fValue-m_nReferValue)/m_nReferValue * 100);
    return strRet;
}
//取周围最近的点
int ChartUnit::getYValueInt(int &c_nX,int c_nY)
{
	int nValue = getYValueInt(c_nY);
	if (nValue == 0x7FFFFFFF)
		return nValue;
	if (m_cuType != CUKLine)
		return nValue;

	if (m_nDataLen <= 0)
		return nValue;

	if (c_nX < 0)
		return nValue;
	int nCount = m_nDataLen/sizeof(KLINE);
	KLINE * pK = (KLINE *)m_pData;
	if (c_nX >= nCount)
		return nValue;

	int nMaxHigh=0,nMaxIndex=-1;
	int nMinLow=0x7FFFFFFF,nMinIndex=-1;

	int nDis = 3;
	if (m_nCellWidth + m_nCellSpace> 5)
		nDis = 0;
	else
	if (m_nCellWidth+ m_nCellSpace > 3)
		nDis = 1;
	else
	if (m_nCellWidth+ m_nCellSpace > 1)
		nDis = 3;
	else
		nDis = 5;
	for(int n=c_nX-nDis; n<=c_nX+nDis; n++)
	{		
		if (n<0 || n>=nCount)
			continue;
		if (pK[n].high > nMaxHigh)
		{
			nMaxHigh = pK[n].high;
			nMaxIndex = n;
		}
		if (pK[n].low < nMinLow)
		{
			nMinLow = pK[n].low;
			nMinIndex = n;
		}
	}
	if (nValue < nMinLow)
	{
		c_nX = nMinIndex;
		return nMinLow;
	}
	if (nValue > pK[c_nX].high)
	{
		c_nX = nMaxIndex;
		return nMaxHigh;
	}
	if (nMaxHigh - nValue > nValue - nMinLow)
	{
		nValue = nMinLow;
		c_nX = nMinIndex;
	}
	else
	{
		nValue = nMaxHigh;
		c_nX = nMaxIndex;
	}
	return nValue;
}

int ChartUnit::getYValueInt(int c_nY)
{
    int nValue = 0X7FFFFFFF;
    if (m_fPerY == 0)
        return nValue;

    float fValue;
    if (m_cuType == CUTrend)
    {
        fValue =  m_rectDraw.top + m_rectDraw.Height()/2 - c_nY;
        fValue /= m_fPerY;
        fValue += m_nReferValue;
        return int(fValue);
    }
    else
    if (m_cuType == CUTrendVol)
    {
        fValue = m_rectDraw.bottom - c_nY;
        fValue /= m_fPerY;
		if (fValue < 0)
			fValue = 0;
        return int(fValue);
    }
    else
	if (m_cuType == CUQCT)
	{
		fValue = m_rectDraw.bottom - c_nY;
		fValue /= m_fPerY;
		if (m_atType == AIXLG)
		{
			fValue = pow(10,fValue) * m_nReferValue;
		}
		else
			fValue += m_nReferValue;
		return int(fValue);
	}
	else
    if (m_cuType == CUKLine)
    {
        //if (c_nY > m_rectDraw.top && c_nY < m_rectDraw.bottom)
        {
            fValue = m_rectDraw.bottom - c_nY;
            fValue /= m_fPerY;
			if (m_atType == AIXLG)
			{
				fValue = pow(10,fValue) * m_nReferValue;
			}
			else
				fValue += m_nReferValue;
            return int(fValue);
        }
    }
    else
    if (m_cuType == CUVOL)
    {
        //if (c_nY >= m_rectDraw.top && c_nY <= m_rectDraw.bottom)
        {
            fValue = m_rectDraw.bottom - c_nY;
            fValue /= m_fPerY;
			if (fValue < 0)
				fValue = 0;
            return int(fValue);
        }
    }
    else
    {
        //if (c_nY > m_rectDraw.top && c_nY < m_rectDraw.bottom)
        {			
			if (this->m_rtType == RTMID)
			{
				fValue = m_nZeroY - c_nY;
				fValue /= m_fPerY;            
				return int(fValue) + m_nReferValue;
			}
			else
			{
				fValue = m_rectDraw.bottom - c_nY;
				fValue /= m_fPerY;            
				return int(fValue) + m_nReferValue;
			}
        }
    }
    return nValue;
}

void ChartUnit::setTitle(CString c_strTitle)
{
    m_strTitle = c_strTitle;
}

void ChartUnit::drawTitle(CDC *c_pDC,CRect &c_rect)
{
	c_pDC->SetBkMode(TRANSPARENT);
    if (m_cuType == CUTrend)
    {		
        CSize size = c_pDC->GetTextExtent(_T("分时 均线"));
        m_rectTitle.SetRect(c_rect.left,c_rect.top,c_rect.left + size.cx,c_rect.top + size.cy);
        c_rect = m_rectTitle;

		c_pDC->SetTextColor(gpSkinManager->getColor(TRENDLINE));
		c_pDC->DrawText(_T("分时"),m_rectTitle,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		if (m_bIsIndex == false)
		{
			c_pDC->SetTextColor(gpSkinManager->getColor(TRENDMALINE));
			c_pDC->DrawText(_T("均线"),m_rectTitle,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);        
		}
        return;
    }
	if (m_nSpecialType == STMARKETGUANGDU)//市场广度
	{
        CSize size = c_pDC->GetTextExtent(_T("安全区 风险区"));
        m_rectTitle.SetRect(c_rect.left,c_rect.top,c_rect.left + size.cx,c_rect.top + size.cy);
        c_rect = m_rectTitle;

		c_pDC->SetTextColor(gpSkinManager->getColor(SAFECOLOR));
		c_pDC->DrawText(_T("安全区"),m_rectTitle,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		c_pDC->SetTextColor(gpSkinManager->getColor(DANGERCOLOR));
		c_pDC->DrawText(_T("风险区"),m_rectTitle,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
        return;

	}

	if (m_nSpecialType == STMARKETKUANDU)//市场宽度
	{
        CSize size = c_pDC->GetTextExtent(_T("安全区 风险区"));
        m_rectTitle.SetRect(c_rect.left,c_rect.top,c_rect.left + size.cx,c_rect.top + size.cy);
        c_rect = m_rectTitle;

		c_pDC->SetTextColor(gpSkinManager->getColor(SAFECOLOR));
		c_pDC->DrawText(_T("安全区"),m_rectTitle,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		c_pDC->SetTextColor(gpSkinManager->getColor(DANGERCOLOR));
		c_pDC->DrawText(_T("风险区"),m_rectTitle,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
        return;

	}
	c_pDC->SetTextColor(gpSkinManager->getLineColor(m_clLine));
	CString strValue;
	GetValueString(strValue);
	strValue = m_strTitle + strValue;
    CSize size = c_pDC->GetTextExtent(strValue);
    m_rectTitle.SetRect(c_rect.left,c_rect.top,c_rect.left+size.cx,c_rect.top + size.cy);
    
	if (m_rectTitle.right < c_rect.right)
		c_pDC->DrawText(strValue,m_rectTitle,DT_LEFT|DT_VCENTER|DT_SINGLELINE);    
	c_rect = m_rectTitle;
}

bool ChartUnit::isSelected(int c_nPos, int c_nValue,CPoint c_pt)
{
    m_bSelected = false;
    if (c_nPos == -1)
        return m_bSelected;

    if (c_nPos >= m_nDataCount)
        return m_bSelected;

	
    if (m_rectTitle.PtInRect(c_pt))
    {
        m_bSelected = true;
        return true;
    }
    if (m_cuType == CUKLine)
    {
        KLINE * p = (KLINE *)m_pData;
        if (p)
        {
            if (int(p[c_nPos + m_nDataBeginPos].high) > c_nValue && int(p[c_nPos + m_nDataBeginPos].low) < c_nValue)
            {
                m_bSelected = true;
                return true;
            }
        }
    }
    else
    if (m_cuType == CUVOL)    
    {
        KLINE * p = (KLINE *)m_pData;
        if (p)
        {
            if (int(p[c_nPos + m_nDataBeginPos].volume) > c_nValue)
            {
                m_bSelected = true;
                return true;
            }
        }
    }
    else
    if (m_cuType == CUTrend || m_cuType == CUTrendVol)
    {
        m_bSelected = false;
    }
    else
    {
        int * pInt = (int *)m_pData;
		if (pInt == NULL)
			return false;
        if ((pInt[c_nPos + m_nDataBeginPos]) >= float(c_nValue) * 0.99 && float(pInt[c_nPos + m_nDataBeginPos]) <= float(c_nValue) * 1.01)
        {
            m_bSelected = true;
            return true;
        }
    }
    return m_bSelected;
}

void ChartUnit::drawRefer(CDC * c_pDC)
{
    CPoint p1,p2;
    float fH,fW;
	CPen LinePenDot(PS_DOT,1,gpSkinManager->getColor(AIXLINE));
	CPen LinePenSolid(PS_SOLID,1,gpSkinManager->getColor(AIXLINE));
	CPen LinePen2Solid(PS_SOLID,2,gpSkinManager->getColor(AIXLINE));
    CPen *pOldPen = c_pDC->SelectObject(&LinePenDot);
	c_pDC->SetBkMode(TRANSPARENT);
    fH = m_rectDraw.Height();
	fW = m_rectDraw.Width();
	int nTextWidth = 50;
	int nMinRowHeight = 50;//每行最低行高
	int nMinRowValue = 0;//每行最低值，50的倍数
    CString strText;
	CSize size;
	size = c_pDC->GetTextExtent(_T("123456."));
	nTextWidth = size.cx;
    if (m_cuType == CUKLine)
    {
		nTextWidth = size.cx;//50;
		//计算最小单元50,然后是50的倍数
		CString strFormat;
		nMinRowValue = nMinRowHeight / m_fPerY;
		int k = 50;
		if (nMinRowValue > 100000)
			k = 100000;			
		if (nMinRowValue > 50000)
			k = 50000;
		else
		if (nMinRowValue > 10000)
			k = 10000;
		else
		if (nMinRowValue > 5000)
			k = 5000;
		else
		if (nMinRowValue > 1000)
			k = 1000;
		else
		if (nMinRowValue > 500)
			k = 500;
		else
		if (nMinRowValue > 100)
			k = 100;
			
		if (m_nMaxValue > 1000 * 10000 && k < 1000)
			k = 1000;
			
		nMinRowValue = (nMinRowValue / k + 1) * k;
		bool bFloat = false;
		if (k > 1000)
		{
			if (m_nMaxValue > 1000 * 1000)
				strFormat = _T("%d");
			else
			{
				strFormat = _T("%.2f");
				bFloat = true;
			}
		}
		else
		{
			strFormat = _T("%.2f");
			bFloat = true;
		}

		int nBeginValue = (m_nMinValue / nMinRowValue) * nMinRowValue;
        
		if (m_atType == AIXNORMAL)
		{
			int nLoopValue = nBeginValue;
			while(true)
			{
				nLoopValue += nMinRowValue;
				if (nLoopValue > m_nMaxValue)
					break;
				p1.x = (m_rectDraw.left);
				p1.y = getValuePos(nLoopValue);
				p2.x = (m_rectDraw.right);
				p2.y = p1.y;
				c_pDC->SelectObject(&LinePenDot);
				c_pDC->MoveTo(p1);
				c_pDC->LineTo(p2);            
				c_pDC->SelectObject(&LinePenSolid);
				c_pDC->MoveTo(p2);
				c_pDC->LineTo(p2.x+4,p2.y);
				if (m_nDataCount > 0)
				{
					if (!bFloat)
						strText.Format(strFormat,nLoopValue/1000);
					else
						strText.Format(strFormat,float(nLoopValue)/1000);
					if (strText.GetLength() > 6)
						strText = strText.Left(6);
					c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
					size = c_pDC->GetTextExtent(strText);
					c_pDC->DrawText(strText,CRect(p2.x,p2.y-size.cy/2,p2.x + nTextWidth,p2.y+size.cy/2),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);            
				}
			}
		}
		else
		if (m_atType == AIXLG)
		{
			KLINE * p = (KLINE *)m_pData;
			float fPreClose;//昨天收盘价格
			if (p)
			{
				if(m_nDataCount + m_nDataBeginPos > 1)
					fPreClose = p[m_nDataCount + m_nDataBeginPos - 2].close;
				else
				if(m_nDataCount + m_nDataBeginPos > 0)
					fPreClose = p[m_nDataCount + m_nDataBeginPos - 1].close;
				else
					fPreClose = m_nPreClose;

				p1.x = (m_rectDraw.left);
				p1.y = getValuePos(fPreClose);
				p2.x = (m_rectDraw.right);
				p2.y = p1.y;
				c_pDC->SelectObject(&LinePenDot);
				c_pDC->MoveTo(p1);
				c_pDC->LineTo(p2);            
				c_pDC->SelectObject(&LinePenSolid);
				c_pDC->MoveTo(p2);
				c_pDC->LineTo(p2.x+4,p2.y);

				strText = getYValueString(p2.y,5);
				if (strText.GetLength() > 6)
					strText = strText.Left(6);
				c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
				size = c_pDC->GetTextExtent(strText);
				c_pDC->DrawText(strText,CRect(p2.x,p2.y-size.cy/2,p2.x + nTextWidth,p2.y+size.cy/2),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
				
				int nLastTopY = p2.y-size.cy/2;
				int nLastBottomY = p2.y + size.cy/2;
				int nMultCount = 0;
				float fMult = 1.1f;
				float fValue = fPreClose;
				while(true)
				{					
					fValue *= fMult;
					nMultCount++;
					if (fValue > m_nMaxValue)
						break;
					p1.y = getValuePos(fValue);
					p2.y = p1.y;
					c_pDC->SelectObject(&LinePenDot);
					c_pDC->MoveTo(p1);
					c_pDC->LineTo(p2);            
					if (nLastTopY > p2.y + size.cy/2 + size.cy)
					{
						c_pDC->SelectObject(&LinePenSolid);
						c_pDC->MoveTo(p2);
						c_pDC->LineTo(p2.x+4,p2.y);
					}
					strText = getYValueString(p2.y,5);
					if (strText.GetLength() > 6)
						strText = strText.Left(6);
					c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
					size = c_pDC->GetTextExtent(strText);
					if (nLastTopY > p2.y + size.cy/2 + size.cy)
					{
						c_pDC->DrawText(strText,CRect(p2.x,p2.y-size.cy/2,p2.x + nTextWidth,p2.y+size.cy/2),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);	
					}
					strText.Format(_T("%d%%"),nMultCount * 10);
					if (nLastTopY > p2.y + size.cy/2 + size.cy)
					{
						c_pDC->DrawText(strText,CRect(p2.x,p2.y+size.cy/2,p2.x + nTextWidth,p2.y+size.cy/2 + size.cy),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
						nLastTopY = p2.y - size.cy/2;
					}
				}

				nMultCount = 0;
				fMult = 0.9f;
				fValue = fPreClose;
				while(true)
				{					
					fValue *= fMult;
					nMultCount++;
					if (fValue < m_nMinValue || (fValue <= 1 && m_nMinValue <= 0))
						break;
					p1.y = getValuePos(fValue);
					p2.y = p1.y;
					c_pDC->SelectObject(&LinePenDot);
					c_pDC->MoveTo(p1);
					c_pDC->LineTo(p2);            
					if (nLastBottomY < p2.y - size.cy/2)
					{
						c_pDC->SelectObject(&LinePenSolid);
						c_pDC->MoveTo(p2);
						c_pDC->LineTo(p2.x+4,p2.y);
					}
					strText = getYValueString(p2.y,5);
					if (strText.GetLength() > 6)
						strText = strText.Left(6);
					c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
					size = c_pDC->GetTextExtent(strText);
					if (nLastBottomY < p2.y - size.cy/2)
					c_pDC->DrawText(strText,CRect(p2.x,p2.y-size.cy/2,p2.x + nTextWidth,p2.y+size.cy/2),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
					
					strText.Format(_T("%d%%"),nMultCount * -10);
					if (nLastBottomY < p2.y - size.cy/2)
					{
						c_pDC->DrawText(strText,CRect(p2.x,p2.y+size.cy/2,p2.x + nTextWidth,p2.y+size.cy/2 + size.cy),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
						nLastBottomY = p2.y + size.cy/2 + size.cy;
					}
				}

			}
		}
    }
    if (m_cuType == CUVOL)
    {
		//nTextWidth = 50;
		int nFg = 4;
        
		if (fH/4 > 30)
			nFg = 4;
		else
		if (fH/3 > 30)
			nFg = 3;
		else
			nFg = 2;
		fH /= nFg;

        for(int n=0; n<(nFg); n++)
        {
            p1.x = (m_rectDraw.left);
            p1.y = (m_rectDraw.top + fH * n);
            p2.x = (m_rectDraw.right);
            p2.y = (m_rectDraw.top + fH * n);
			c_pDC->SelectObject(&LinePenDot);
			c_pDC->MoveTo(p1);
			c_pDC->LineTo(p2);
			c_pDC->SelectObject(&LinePenSolid);
			c_pDC->MoveTo(p2);
			c_pDC->LineTo(p2.x+4,p2.y);
            if (m_nDataCount > 0)
			{
				strText = getYValueString(p2.y,5);			

				c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
				CSize size = c_pDC->GetTextExtent(strText);
				c_pDC->DrawText(strText,CRect(p2.x,p2.y-size.cy/2,p2.x+nTextWidth,p2.y + size.cy/2),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);            
			}
        }
		if (m_nDiv > 1)
		{
			strText.Format(_T("X%d"),m_nDiv);
			size = c_pDC->GetTextExtent(strText);
			c_pDC->DrawText(strText,CRect(m_rectDraw.right,m_rectDraw.bottom-size.cy,m_rectDraw.right + 50,m_rectDraw.bottom),DT_LEFT|DT_VCENTER|DT_SINGLELINE);            
		}
    }   
	if (m_cuType == CUTrend)
	{		
        fH /= 16;
        for(int n=0; n<=16; n++)
        {
            p1.x = (m_rectDraw.left);
            p1.y = (m_rectDraw.top + fH * n);
            p2.x = (m_rectDraw.right);
            p2.y = (m_rectDraw.top + fH * n);
			if (n == 8)
				c_pDC->SelectObject(&LinePen2Solid);
			else
				c_pDC->SelectObject(&LinePenSolid);
			c_pDC->MoveTo(p1);
			c_pDC->LineTo(p2);
            
			if (n<16 && m_nDataCount > 0)
			{
				strText = getYValueString(p2.y,5);
				if (n == 8)
					c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
				else
				if (n > 8)
					c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
				else
					c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
				CSize size = c_pDC->GetTextExtent(strText);
				//c_pDC->DrawText(strText,CRect(m_rectDraw.left - nTextWidth ,p2.y-size.cy/2,m_rectDraw.left - 2,p2.y + size.cy/2),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
				c_pDC->DrawText(strText,CRect(m_rectDraw.left - nTextWidth ,p2.y-size.cy/2,m_rectDraw.left - 2,p2.y + size.cy/2),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
				strText = getYValuePercentString(p2.y);
				if (n > 8)
					strText = strText.Right(strText.GetLength() - 1);
				c_pDC->DrawText(strText,CRect(p2.x,p2.y-size.cy/2,p2.x+nTextWidth,p2.y + size.cy/2),DT_LEFT|DT_VCENTER|DT_SINGLELINE);								
			}
        }
		if (m_nDataCount > 0)
		{
			c_pDC->SelectObject(&LinePenDot);
		
			for(int n=1; n<239; n++)
			{
				if ((n <= 120 && n % 30 == 0) || (n > 121 && (n-1) % 30 == 0))
				{
					p1.x = this->m_pnHoriPoint[n] + m_rectDraw.left;
					p1.y = m_rectDraw.top;
					p2 = p1;
					p2.y = m_rectDraw.bottom;
					c_pDC->MoveTo(p1);
					c_pDC->LineTo(p2);            
				}
			}
		}
		/*
		fW /= 8;
        for(int n=1; n<=8; n++)
        {
            p1.x = (m_rectDraw.left + fW * n);
            p1.y = (m_rectDraw.top);
            p2.x = (m_rectDraw.left + fW * n);
            p2.y = (m_rectDraw.bottom);
			c_pDC->MoveTo(p1);
			c_pDC->LineTo(p2);            
        }
		*/
	}
	if (m_cuType == CUTrendVol)
	{		
		c_pDC->SelectObject(&LinePenSolid);
        fH /= 8;
        for(int n=0; n<=8; n++)
        {
            p1.x = (m_rectDraw.left);
            p1.y = (m_rectDraw.top + fH * n);
            p2.x = (m_rectDraw.right);
            p2.y = (m_rectDraw.top + fH * n);
			c_pDC->MoveTo(p1);
			c_pDC->LineTo(p2);
            
			if (n < 8 && m_nDataCount > 0)
			{
				strText = getYValueString(p2.y,5);			
				c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
				size = c_pDC->GetTextExtent(strText);
				c_pDC->DrawText(strText,CRect(p2.x + 2,p2.y-size.cy/2,p2.x+nTextWidth,p2.y + size.cy/2),DT_LEFT|DT_VCENTER|DT_SINGLELINE);
				c_pDC->DrawText(strText,CRect(m_rectDraw.left - nTextWidth,p2.y-size.cy/2,m_rectDraw.left - 2,p2.y + size.cy/2),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
			}
        }
		if (m_nDataCount > 0)
		{
			c_pDC->SelectObject(&LinePenDot);
		
			for(int n=1; n<239; n++)		
			{
				if ((n <= 120 && n % 30 == 0) || (n > 121 && (n-1) % 30 == 0))
				{
					p1.x = this->m_pnHoriPoint[n] + m_rectDraw.left;
					p1.y = m_rectDraw.top;
					p2 = p1;
					p2.y = m_rectDraw.bottom;
					c_pDC->MoveTo(p1);
					c_pDC->LineTo(p2);            
				}
			}
		}
	}
	//nTextWidth = 50;
	if (m_cuType == CUTick || m_cuType == CUTickLine || m_cuType == CULink || m_cuType == CUQCT)
	{			
		c_pDC->SelectObject(&LinePenDot);
		p1.x = (m_rectDraw.left);
		p1.y = m_nZeroY;
		p2.x = m_rectDraw.right;
		p2.y = m_nZeroY;		
		c_pDC->MoveTo(p1);
		c_pDC->LineTo(p2);
		c_pDC->SelectObject(&LinePenSolid);
		c_pDC->MoveTo(p2);
		c_pDC->LineTo(p2.x+4,p2.y);
		if (m_nDataCount > 0)
		{
			c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
			strText.Format(_T("%.2f"),float(m_nReferValue)/m_nMultiplier);
			//strText = "0.00";
			if (m_bDrawReferValue)
			{
				size = c_pDC->GetTextExtent(strText);
				c_pDC->DrawText(strText,CRect(p2.x,p2.y-size.cy/2,p2.x+nTextWidth,p2.y + size.cy/2),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
			}

			p1.y = getValuePos(m_nMaxValue);
			p2.y = p1.y;
			if (abs(p2.y - m_nZeroY) > 20)
			{
				c_pDC->SelectObject(&LinePenDot);
				c_pDC->MoveTo(p1);
				c_pDC->LineTo(p2);
				c_pDC->SelectObject(&LinePenSolid);
				c_pDC->MoveTo(p2);
				c_pDC->LineTo(p2.x+4,p2.y);
				if (m_bDrawReferValue)
				{
					strText.Format(_T("%.2f"),float(m_nMaxValue) / m_nMultiplier);
					c_pDC->DrawText(strText,CRect(p2.x,p2.y-size.cy/2,p2.x+nTextWidth,p2.y + size.cy/2),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
				}
			}
			p1.y = getValuePos(m_nMinValue);
			p2.y = p1.y;
			if (abs(p2.y - m_nZeroY) > 20)
			{
				c_pDC->SelectObject(&LinePenDot);
				c_pDC->MoveTo(p1);
				c_pDC->LineTo(p2);
				c_pDC->SelectObject(&LinePenSolid);
				c_pDC->MoveTo(p2);
				c_pDC->LineTo(p2.x+4,p2.y);		
				if (m_bDrawReferValue)
				{
					strText.Format(_T("%.2f"),float(m_nMinValue) / m_nMultiplier);
					c_pDC->DrawText(strText,CRect(p2.x,p2.y-size.cy/2,p2.x+nTextWidth,p2.y + size.cy/2),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
				}
			}
			if (m_nSpecialType == STRSI)
			{
				p1.y = getValuePos(20 * 1000);
				p2.y = p1.y;
				if (true)
				{
					c_pDC->SelectObject(&LinePenDot);
					c_pDC->MoveTo(p1);
					c_pDC->LineTo(p2);
					c_pDC->SelectObject(&LinePenSolid);
					c_pDC->MoveTo(p2);
					c_pDC->LineTo(p2.x+4,p2.y);		
					if (m_bDrawReferValue)
					{
						strText.Format(_T("%d"),20);
						c_pDC->DrawText(strText,CRect(p2.x,p2.y-size.cy/2,p2.x+nTextWidth,p2.y + size.cy/2),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
					}
				}

				p1.y = getValuePos(50 * 1000);
				p2.y = p1.y;
				if (true)
				{
					c_pDC->SelectObject(&LinePenDot);
					c_pDC->MoveTo(p1);
					c_pDC->LineTo(p2);
					c_pDC->SelectObject(&LinePenSolid);
					c_pDC->MoveTo(p2);
					c_pDC->LineTo(p2.x+4,p2.y);		
					if (m_bDrawReferValue)
					{
						strText.Format(_T("%d"),50);
						c_pDC->DrawText(strText,CRect(p2.x,p2.y-size.cy/2,p2.x+nTextWidth,p2.y + size.cy/2),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
					}
				}

				p1.y = getValuePos(80 * 1000);
				p2.y = p1.y;
				if (true)
				{
					c_pDC->SelectObject(&LinePenDot);
					c_pDC->MoveTo(p1);
					c_pDC->LineTo(p2);
					c_pDC->SelectObject(&LinePenSolid);
					c_pDC->MoveTo(p2);
					c_pDC->LineTo(p2.x+4,p2.y);		
					if (m_bDrawReferValue)
					{
						strText.Format(_T("%d"),80);
						c_pDC->DrawText(strText,CRect(p2.x,p2.y-size.cy/2,p2.x+nTextWidth,p2.y + size.cy/2),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
					}
				}

			}
		}
	}
	c_pDC->SelectObject(pOldPen);
}

void ChartUnit::setPrecision(int c_nPrecision)
{
    m_nPrecision = c_nPrecision;
}

void ChartUnit::setMultiplier(int c_nMultiplier)
{
    m_nMultiplier = c_nMultiplier;
}

void ChartUnit::setDiv(int c_nDiv)
{
	m_nDiv = c_nDiv;
}
void ChartUnit::GetValueString(CString &c_strValue)
{	
//CUTrend=0,CUTrendVol,CUKLine,CUVOL,
	int nPos = m_nCurPos;
	if (m_nCurPos >= m_nDataCount)
		nPos = m_nDataCount - 1;

	if (m_nDataCount == 0)
		return;
	if (nPos < 0)
		nPos = m_nDataCount-1;
	
	if (nPos >= m_nDataCount)
		return;

	CString strFormat;
	if (m_cuType == CUKLine)
	{
		KLINE * pBlock = (KLINE *)m_pData;
		int nKItemCount = m_nDataLen / sizeof(KLINE);
		if (nKItemCount > m_nDataBeginPos + nPos)
		{
			if (m_nPrecision > 0)
			{
				strFormat.Format(_T(":%%.%df"),m_nPrecision);
				c_strValue.Format(strFormat,float(pBlock[m_nDataBeginPos + nPos].close)/m_nMultiplier);

			}
			else
			{
				strFormat.Format(_T(":%%%dd"),m_nPrecision);
				c_strValue.Format(strFormat,pBlock[m_nDataBeginPos + nPos].close/m_nMultiplier);
			}
		}	
		return;
	}
	if (m_cuType == CUVOL)
	{
		KLINE * pBlock = (KLINE *)m_pData;
		int nKItemCount = m_nDataLen / sizeof(KLINE);
		if (nKItemCount > m_nDataBeginPos + nPos)
		{
			c_strValue.Format(_T(":%d"),pBlock[m_nDataBeginPos + nPos].volume/m_nDiv);
		}	
		return;
	}

	if (m_cuType != CULink && m_cuType != CUTick && m_cuType != CUTickLine && m_cuType != CUQCT)
		return;
	if (m_nDataCount == 0)
		return;
	if (nPos == -1)
		nPos = m_nDataCount-1;
	
	if (nPos >= m_nDataCount)
		return;

	int *pnData = (int *)m_pData;
	if (pnData == NULL)
		return;
	if (pnData[m_nDataBeginPos + nPos] == 0X7FFFFFFF)
		return;
	if (m_nPrecision > 0)
	{
		strFormat.Format(_T(":%%.%df"),m_nPrecision);
		c_strValue.Format(strFormat,float(pnData[m_nDataBeginPos + nPos])/m_nMultiplier);
	}
	else
	{
		strFormat.Format(_T(":%%%dd"),m_nPrecision);
		c_strValue.Format(strFormat,pnData[m_nDataBeginPos + nPos]/m_nMultiplier);
	}	
	
}

void ChartUnit::SetCurPos(int c_nPos,int c_nPosTime)
{
	m_nCurPos = c_nPos;
	m_nCurPosTime = c_nPosTime;
}

ChartUnitType ChartUnit::getUnitType()
{
	return m_cuType;
}

void ChartUnit::drawXCoord(CDC * c_pDC,CRect c_rectAxis,int c_nLoopMax)
{
    CPoint p1,p2;
	CPen LinePenSolid(PS_SOLID,1,gpSkinManager->getColor(AIXLINE));	
	if (m_nDataCount == 0)
		return;
    CPen *pOldPen = c_pDC->SelectObject(&LinePenSolid);
	c_pDC->SetBkMode(TRANSPARENT);
	c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
	int nTextWidth = 50;
    CString strText;	
    if (m_cuType == CUKLine)
    {
		KLINE * pKLine = (KLINE *)m_pData;
		int nKLineItemCount = m_nDataLen / sizeof(KLINE);		
		int nCurYear,nCurMonth,nCurDay;
		int nNewYear,nNewMonth,nNewDay;
		int nLastX = m_rectDraw.left;
		nCurYear = 0;
		nCurMonth = 0;
		nCurDay = 0;
		for(int n=0; n<m_nHoriCount; n++)
        {
			if((n + m_nDataBeginPos) >= c_nLoopMax)//nKLineItemCount)//画出后面有效的日期
			{
				break;
			}
			int nDay = pKLine[m_nDataBeginPos + n].day;
			
			nNewYear = nDay / 10000;
			nNewMonth = nDay / 100 %100;
			nNewDay = nDay %100;
			if (nNewYear > 10000)
			{
				nDay /= 10000;
				nNewYear = nDay / 10000;
				nNewYear += 2000;
				nNewMonth = nDay / 100 % 100;
				nNewDay = nDay % 100;				
				if (nCurDay == nNewDay && nNewMonth == nCurMonth)
				{
					continue;
				}
				strText.Format(_T("%d/%d"),nNewMonth,nNewDay);
			}
			else
			{
				if (nCurMonth == nNewMonth)
				{
					continue;
				}
				strText.Format(_T("%.2d"),nNewMonth);
			}
			nCurYear = nNewYear;
			nCurMonth = nNewMonth;
			nCurDay = nNewDay;
			p1.x = m_pnHoriPoint[n] + m_rectDraw.left;
			p1.y = c_rectAxis.bottom;
			p2 = p1;
			p2.y = p1.y + 4;
			if (p1.x > m_rectDraw.right)
				break;

			c_pDC->MoveTo(p1);
			c_pDC->LineTo(p2);						
			
			CSize size = c_pDC->GetTextExtent(strText);	
			if ((p2.x-size.cx/2) > (nLastX + 4))
			{
				c_pDC->DrawText(strText,CRect(p2.x-size.cx/2,p2.y,p2.x + size.cx/2,p2.y + size.cy),DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				nLastX = p2.x + size.cx/2;
			}
        }
    }
	if (m_cuType == CUTrend)
	{		
		MinUnit * pMin = (MinUnit *)m_pData;
		int nMinItemCount = m_nDataLen / sizeof(MinUnit);
		for(int n=0; n<242; n++)
		{
			if ((n <= 120 && n % 30 == 0) || (n > 121 && (n-1) % 30 == 0))
			{
				p1.x = m_pnHoriPoint[n] + m_rectDraw.left;
				if(n > 240)
					p1.x = m_rectDraw.right;
				p1.y = c_rectAxis.bottom;
				p2 = p1;
				p2.y = p1.y + 4;
				c_pDC->MoveTo(p1);
				c_pDC->LineTo(p2);	
				strText.Format(_T("%d:%.2d"),pMin[n].Time/60,pMin[n].Time%60);
				CSize size = c_pDC->GetTextExtent(strText);
				c_pDC->DrawText(strText,CRect(p2.x-size.cx/2,p2.y,p2.x + size.cx/2,p2.y + size.cy),DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			}
		}
	}
	c_pDC->SelectObject(pOldPen);
}

void ChartUnit::setParam(int c_n)
{
	m_strParam.Format(_T("%d"),c_n);
}

void ChartUnit::setParam(CString c_str)
{
	m_strParam = c_str;
}

CString ChartUnit::getParamString()
{
	return m_strParam;
}

int ChartUnit::getParamInt()
{
	USES_CONVERSION;
	char * pBuf;
	pBuf = (char *)W2A(m_strParam.GetBuffer());
	int n = atoi(pBuf);
	m_strParam.ReleaseBuffer();
	return n;
}

void ChartUnit::setIsIndex(bool c_b)
{
	m_bIsIndex = c_b;
}

void ChartUnit::setFixedMaxMinValue(int c_nFixedMax,int c_nFixedMin)
{
	m_nFixedMaxValue = c_nFixedMax;
	m_nFixedMinValue = c_nFixedMin;
	m_nMaxValue = c_nFixedMax;
	m_nMinValue = c_nFixedMin;
}

void ChartUnit::setSpecialType(SpecialType c_nSp)
{
	m_nSpecialType = c_nSp;
}
SpecialType ChartUnit::getSepcialType()
{
	return m_nSpecialType;
}
void ChartUnit::setDrawSingle(bool c_bIsSingle)
{
	m_bDrawSingle = c_bIsSingle;
}

bool ChartUnit::isDrawSingle()
{
	return m_bDrawSingle;
}

void ChartUnit::setDrawReferValue(bool c_b)
{
	m_bDrawReferValue = c_b;
}

int ChartUnit::getXByPos(int c_nPos)
{
	if (this->m_cuType == CUTrend)
	{
		if (c_nPos < 0 || c_nPos > this->m_nHoriCount)
			return INVALID_INT;
		return m_pnHoriPoint[c_nPos] + m_rectDraw.left;
	}
	int nIndex = c_nPos - m_nDataBeginPos;
	if (nIndex >= m_nHoriCount)
		return INVALID_INT;
	if (nIndex >= 0)
		return m_pnHoriPoint[nIndex] + m_nCellWidth/2 + m_rectDraw.left;
	return m_pnHoriPoint[0] + nIndex * (m_nCellWidth + m_nCellSpace)+ m_nCellWidth/2 + m_rectDraw.left;
}

int ChartUnit::getPosByX(int c_nX)
{	
	if (m_nHoriCount == 0)
		return INVALID_INT;
	if (c_nX <= m_pnHoriPoint[0] + m_rectDraw.left)
		return m_nDataBeginPos;

	if (c_nX >= m_pnHoriPoint[m_nHoriCount-1] + m_rectDraw.left)
		return m_nDataBeginPos + m_nHoriCount - 1;

	for(int n=1; n<m_nHoriCount; n++)
	{
		if (c_nX >= m_pnHoriPoint[n] +  m_rectDraw.left && c_nX <= m_pnHoriPoint[n+1] +  m_rectDraw.left)
			return n + m_nDataBeginPos;
	}
	return m_nDataBeginPos;	
}

void ChartUnit::drawSJX(CDC * c_pDC,CPoint c_ptPoint,bool c_bUP,int c_nDis)
{
	if (c_bUP)
	{
		//红三角
		CBrush br(RGB(255,0,0));
		CPen tpen(PS_SOLID,1,RGB(255,0,0));
		POINT *pp = new POINT[4];
		pp[0].x = c_ptPoint.x;		pp[0].y = c_ptPoint.y + c_nDis;
		pp[1].x = c_ptPoint.x - 5; pp[1].y = c_ptPoint.y + c_nDis + 12;
		pp[2].x = c_ptPoint.x + 5; pp[2].y = c_ptPoint.y + c_nDis + 12;
		pp[3].x = c_ptPoint.x;		pp[3].y = c_ptPoint.y + c_nDis;
		CBrush *old = c_pDC->SelectObject(&br);
		CPen *oldt = c_pDC->SelectObject(&tpen);
		c_pDC->Polygon(pp,4);
		c_pDC->SelectObject(old);
		c_pDC->SelectObject(oldt);
		delete [] pp;
	}
	else
	{
		//绿三角
		CBrush br(RGB(0,255,0));
		CPen tpen(PS_SOLID,1,RGB(0,255,0));
		POINT *pp = new POINT[4];
		pp[0].x = c_ptPoint.x;		pp[0].y = c_ptPoint.y - c_nDis;
		pp[1].x = c_ptPoint.x - 5; pp[1].y = c_ptPoint.y - c_nDis - 12;
		pp[2].x = c_ptPoint.x + 5; pp[2].y = c_ptPoint.y - c_nDis - 12;
		pp[3].x = c_ptPoint.x;		pp[3].y = c_ptPoint.y - c_nDis;
		CBrush *old = c_pDC->SelectObject(&br);
		CPen *oldt = c_pDC->SelectObject(&tpen);
		c_pDC->Polygon(pp,4);
		c_pDC->SelectObject(old);
		c_pDC->SelectObject(oldt);
		delete [] pp;
	}
}

void ChartUnit::SetAixType(AixType c_atType)
{
	m_atType = c_atType;
}

AixType ChartUnit::GetAixType()
{
	return m_atType;
}

void ChartUnit::SetPreClose(int c_nPreClose)
{
	m_nPreClose = c_nPreClose;
}

int ChartUnit::getTimeByPos(int c_nPos)
{
	if (c_nPos < 0)
		return INVALID_INT;
    if (m_cuType == CUKLine)
    {
		KLINE * pKLine = (KLINE *)m_pData;
		int nKLineItemCount = m_nDataLen / sizeof(KLINE);
		if (c_nPos < nKLineItemCount)
			return pKLine[c_nPos].day;
    }
	if (m_cuType == CUTrend)
	{		
		MinUnit * pMin = (MinUnit *)m_pData;
		int nMinItemCount = m_nDataLen / sizeof(MinUnit);
		if (c_nPos < nMinItemCount)
			return pMin[c_nPos].Time;
	}
	return INVALID_INT;
}

int ChartUnit::getPosByTime(int c_nTime)
{
	if (c_nTime < 0)
		return INVALID_INT;
	if (m_cuType == CUKLine)
	{
		KLINE * pKLine = (KLINE *)m_pData;
		int nKLineItemCount = m_nDataLen / sizeof(KLINE);
		for(int n=0; n<nKLineItemCount; n++)
		{
			if (pKLine[n].day >= c_nTime)
				return n;
		}
	}
	else
	if (m_cuType == CUTrend)
	{
		MinUnit * pMin = (MinUnit *)m_pData;
		int nMinItemCount = m_nDataLen / sizeof(MinUnit);
		for(int n=0; n<nMinItemCount; n++)
		{
			if (pMin[n].Time >= c_nTime)
				return n;
		}
	}
	return INVALID_INT;
}