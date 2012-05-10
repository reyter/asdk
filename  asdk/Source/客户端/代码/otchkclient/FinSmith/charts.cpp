#include "Stdafx.h"

#include "charts.h"
#include "../finsmith/TechManager.h"
#include "../finsmith/Calc.h"
#include "../finsmith/PicWnd.h"
#include "../public/data_struct.h"
#include "../public/skinmanager.h"

Charts::Charts()
{
	m_bVisible = true;
	m_bSelected = false;
	m_atType = AIXNORMAL;
}


Charts::~Charts()
{

}

int Charts::setVisible(bool c_bShow)
{
	m_bVisible = c_bShow;
	int nHeight = m_rectHead.Height();
	nHeight += m_rectBody.Height();
	nHeight += m_rectFoot.Height();
	return nHeight;
}

void Charts::setSize(CRect c_rect)
{
	int nDis = 16;
	int nH = gpSkinManager->GetFontHeight(gpSkinManager->GetGraphFont());
	nDis = nH;
	if (nDis < 16)
		nDis = 16;
	if (m_listCharts.size() == 0)
		return;

	CRect rH,rB,rF;
	if(getChartUnit(0)->m_cuType == CUTrend)
	{
		rH = c_rect;
		rH.bottom = rH.top + nDis;
		rF = c_rect;
		rF.top = rF.bottom;
		rB = c_rect;
		rB.top = rH.bottom;
		rB.bottom = rF.top;
	}
	else
		if(getChartUnit(0)->m_cuType == CUKLine)	
		{
			rH = c_rect;
			rH.bottom = rH.top + nDis + 16;
			rF = c_rect;
			rF.top = rF.bottom - nDis;
			rB = c_rect;
			rB.top = rH.bottom;
			rB.bottom = rF.top;
		}
		else
			if(getChartUnit(0)->m_cuType == CUTrendVol)
			{
				rH = c_rect;
				rH.bottom = rH.top;
				rF = c_rect;
				rF.top = rF.bottom;
				rB = c_rect;
				rB.top = rH.bottom;
				rB.bottom = rF.top;
			}
			else
				if(getChartUnit(0)->m_cuType == CUVOL)
				{
					rH = c_rect;
					rH.bottom = rH.top + nDis;
					rF = c_rect;
					rF.top = rF.bottom;
					rB = c_rect;
					rB.top = rH.bottom;
					rB.bottom = rF.top;
				}
				else
				{
					rH = c_rect;
					rH.bottom = rH.top + nDis;
					rF = c_rect;
					rF.top = rF.bottom - nDis;
					rB = c_rect;
					rB.top = rH.bottom;
					rB.bottom = rF.top;
				}

				setRects(rB,rH,rF);
}
void Charts::resizeBody(int c_nHeight,int c_nWay)
{
	if (c_nWay == -1)//向上
	{
		m_rectHead.top -= c_nHeight;
		m_rectHead.bottom -= c_nHeight;
		m_rectBody.top -= c_nHeight;
	}
	else//向下
	{
		m_rectFoot.top += c_nHeight;
		m_rectFoot.bottom += c_nHeight;
		m_rectBody.bottom += c_nHeight;
	}
	setRects(m_rectBody,m_rectHead,m_rectFoot);
}
void Charts::setRects(CRect c_rectBody, CRect c_rectHead, CRect c_rectFoot)
{
	m_rectBody = c_rectBody;
	m_rectHead = c_rectHead;
	m_rectFoot = c_rectFoot;
	for(int n=0; n<m_listCharts.size(); n++)
	{
		m_listCharts.at(n)->setDrawRect(m_rectBody);
	}
}

void Charts::getRectBody(CRect &c_rectBody)
{
	c_rectBody = m_rectBody;
}

void Charts::getRectFoot(CRect &c_rectFoot)
{
	c_rectFoot = m_rectFoot;
}

void Charts::getRectHead(CRect &c_rectHead)
{
	c_rectHead = m_rectHead;
}

void Charts::getChartsMaxMinValue(int &c_nMax,int &c_nMin,float &c_fMax,float &c_fMin)
{
	int nBegin=0;
///-	int nMax,nMin;
///-	int nBaseMax,nBaseMin;
	float fBaseMax,fBaseMin;
	int nBaseBegin;
	nBaseBegin = 0;
	fBaseMax = 0;
	fBaseMin = 0;
	for(int n=0; n<m_listCharts.size(); n++)
	{
		nBegin = 0;
		m_listCharts.at(n)->getMaxMinValue(nBegin,c_nMax,c_nMin);
	}
	if (m_listCharts.size())
		if (m_listCharts.at(0)->getUnitType() == CUKLine && c_nMin < 0)
		{
			c_nMin = 100;
		}
}

void Charts::setTitle(CString c_strTitle)
{
	m_strTitle = c_strTitle;
}

void Charts::setType(CString c_strType,unsigned short c_usType)
{
	m_strType = c_strType;
	m_usCycle = c_usType;
}

CString Charts::getType()
{
	return m_strType;
}

unsigned short Charts::getCycle()
{
	return m_usCycle;
}
void Charts::drawTitles(CDC * c_pDC)
{
	if (m_bVisible == false)
		return;

	CRect rectTitle;    
	rectTitle = m_rectHead;

	c_pDC->SetBkMode(TRANSPARENT);
	if (!m_strTitle.IsEmpty())
	{
		CSize size = c_pDC->GetTextExtent(m_strTitle);
#ifdef CCTV_TV
		c_pDC->SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));
#else
		c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
#endif
		c_pDC->DrawText(m_strTitle,rectTitle,DT_LEFT|DT_VCENTER);
		rectTitle.left += size.cx + 10;        
	}

	for(int n=0; n<m_listCharts.size(); n++)
	{
		m_listCharts.at(n)->drawTitle(c_pDC,rectTitle);
		rectTitle.left = rectTitle.right + 10;
		if (rectTitle.left > m_rectBody.right || rectTitle.right > m_rectBody.right)
			//if (rectTitle.left > (m_rectHead.right-60) || rectTitle.right > (m_rectHead.right-60))
		{
			return;
			rectTitle.left = m_rectHead.left + 8;			
			rectTitle.top += 16;
		}
		rectTitle.right = m_rectHead.right - 60;
	}    
}

bool Charts::isSelected(int c_nPos, int c_nYValue,CPoint c_pt)
{
	int xPos;
	int yValue;
	xPos = c_nPos;
	yValue = c_nYValue;
	if (m_rectHead.PtInRect(c_pt) || m_rectBody.PtInRect(c_pt))
	{
		bool bRet = false;
		for(int n=0; n<m_listCharts.size(); n++)
		{
			if (m_listCharts.at(n)->isSelected(xPos,yValue,c_pt))
			{
				bRet = true;
				xPos = -1;
			}
		}
		return bRet;
	}
	return false;
}

void Charts::addChartUnit(ChartUnit * c_pUnit)
{
	m_listCharts.push_back(c_pUnit);
}

void Charts::removeChartUnit(ChartUnitType c_st)
{
}
ChartUnit * Charts::getChartUnit(CString c_strChartName)
{
	for(int n=0; n<m_listCharts.size(); n++)
	{
		if (c_strChartName.IsEmpty())
			return m_listCharts.at(n);
		if (m_listCharts.at(n)->m_strTitle == c_strChartName)
			return m_listCharts.at(n);
	}
	return NULL;
}

ChartUnit * Charts::getChartUnitByType(ChartUnitType c_cut)
{
	for(int n=0; n<m_listCharts.size(); n++)
	{
		if (m_listCharts.at(n)->m_cuType == c_cut)
			return m_listCharts.at(n);
	}
	return NULL;
}

void Charts::setChartsDrawRect(CRect c_rect)
{
	for(int n=0; n<m_listCharts.size(); n++)
	{
		m_listCharts.at(n)->setDrawRect(c_rect);
	}
}

void Charts::setChartsMaxMinValue(int c_nMax, int c_nMin,float c_fMax,float c_fMin)
{
	for(int n=0; n<m_listCharts.size(); n++)
	{
		m_listCharts.at(n)->setMaxMinValue(c_nMax,c_nMin,c_fMax,c_fMin);
	}
}

void Charts::setChartsViewProperty(int c_nCount, int *c_pnHoriValue, int c_nDataBegin,int c_nDataBeginTime, int c_nDataCount)
{
	for(int n=0; n<m_listCharts.size(); n++)
		m_listCharts.at(n)->setViewProperty(c_nCount,c_pnHoriValue,c_nDataBegin,c_nDataBeginTime,c_nDataCount);
}

void Charts::setChartsCell(int w, int s)
{
	for(int n=0; n<m_listCharts.size(); n++)
		m_listCharts.at(n)->setCell(w,s);
}

void Charts::drawCharts(CDC * c_pDC,CString c_strStockCode,bool c_bDrawMainTechLine)
{
	if (m_bVisible == false)
		return;

	CDC SourceDC;
	CBitmap bitmap,*pOldBitmap;
	CFont *pOldFont;
	CRect rectBody = m_rectBody;
	if(m_rectHead.Height() > 10)
		rectBody.top -= 10;
	if(m_rectFoot.Height() > 10)
		rectBody.bottom += 10;
	bitmap.CreateCompatibleBitmap(c_pDC,rectBody.right,rectBody.bottom);
	SourceDC.CreateCompatibleDC(NULL);//生成兼容的CDC
	pOldBitmap = SourceDC.SelectObject(&bitmap);
	SourceDC.BitBlt(rectBody.left,rectBody.top,rectBody.Width(),rectBody.Height(),c_pDC,rectBody.left,rectBody.top,SRCCOPY);
	pOldFont = SourceDC.SelectObject(gpSkinManager->m_pFontGraph);
	SourceDC.SetBkMode(TRANSPARENT);
	for(int n=0; n<m_listCharts.size(); n++)
	{
		if (n == 0 || c_bDrawMainTechLine)
			m_listCharts.at(n)->drawChartUnit(&SourceDC);		
	}
	//for(int n=0; n<m_listCharts.size(); n++)
	//    m_listCharts.at(n)->drawChartUnit(c_pDC);
	c_pDC->BitBlt(rectBody.left,rectBody.top,rectBody.Width(),rectBody.Height(),&SourceDC,rectBody.left,rectBody.top,SRCCOPY);

	SourceDC.SelectObject(pOldBitmap);
	SourceDC.SelectObject(pOldFont);
	bitmap.DeleteObject();	
	SourceDC.DeleteDC();

	drawTitles(c_pDC);
}

void Charts::setChartsRefer(ReferType c_type, int c_nRefer)
{
	if (m_listCharts.at(0)->getUnitType() == CUTickLine || m_listCharts.at(0)->getUnitType() == CUTick)
		return;
	for(int n=0; n<m_listCharts.size(); n++)
	{
		m_listCharts.at(n)->setRefer(c_type,c_nRefer);
		//m_listCharts.at(n)->calcPerY(c_type,c_nRefer);
	}
}

void Charts::cleanCharts()
{
	while(m_listCharts.size() > 0)
	{		
		delete *(m_listCharts.begin());
		m_listCharts.erase(m_listCharts.begin());
	}
}

void Charts::drawRefer(CDC * c_pDC)
{
	if (m_bVisible == false)
		return;

	if (m_listCharts.size() > 0)
		m_listCharts.at(0)->drawRefer(c_pDC);
}

void Charts::setCurPos(int c_nPos,int c_nPosTime)
{
	for(int n=0; n<m_listCharts.size(); n++)
	{
		m_listCharts.at(n)->SetCurPos(c_nPos,c_nPosTime);
	}
}

ChartUnit * Charts::getChartUnit(int c_nIndex)
{
	if (m_listCharts.size() == 0 || m_listCharts.size() < c_nIndex)
		return NULL;

	return m_listCharts.at(c_nIndex);
}

CString Charts::getTitle()
{
	return m_strTitle;
}

void Charts::calcMaxMinValue()
{
	int nMax,nMin;///-,nRefer;
	nMax = -1;
	nMin = 0X7FFFFFFF;
	float fMax,fMin;
	getChartsMaxMinValue(nMax,nMin,fMax,fMin);
	setChartsMaxMinValue(nMax,nMin,fMax,fMin);
	for(int n=0; n<m_listCharts.size(); n++)
	{
		m_listCharts.at(n)->calcPerY();//计算Y值
	}
}

void Charts::calcMaxMinValue(int c_nMax,int c_nMin)
{
	int nMax,nMin;///-,nRefer;
	nMax = c_nMax;
	nMin = c_nMin;
	float fMax,fMin;
	getChartsMaxMinValue(nMax,nMin,fMax,fMin);
	setChartsMaxMinValue(nMax,nMin,fMax,fMin);
	for(int n=0; n<m_listCharts.size(); n++)
	{
		m_listCharts.at(n)->calcPerY();//计算Y值
	}
}

bool Charts::isPointIn(CPoint c_point)
{
	if (m_bVisible == false)
		return false;

	if (m_rectHead.PtInRect(c_point) || m_rectBody.PtInRect(c_point) || m_rectFoot.PtInRect(c_point))
		return true;

	return false;
}
void Charts::removeTech(bool c_bRemoveFirst)
{
	std::vector<ChartUnit *>::iterator iter;
	iter = m_listCharts.begin();
	if (iter == m_listCharts.end())
		return;

	if ((*iter)->m_psBz)
	{
		free((*iter)->m_psBz);
		(*iter)->m_psBz = NULL;
	}
	if (c_bRemoveFirst == false)
		iter++;
	while(iter != m_listCharts.end())
	{
		delete *iter;
		iter = m_listCharts.erase(iter);
	}
}
bool Charts::removeSpecialUnit(SpecialType c_spt)
{
	bool bRet = false;
	std::vector<ChartUnit *>::iterator iter;
	iter = m_listCharts.begin();
	while(iter != m_listCharts.end())
	{
		if ((*iter)->m_nSpecialType == c_spt)
		{
			delete *iter;
			iter = m_listCharts.erase(iter);
			bRet = true;
		}
		else
			iter++;
	}
	return bRet;
}

bool Charts::getSpecialUnit(SpecialType c_spt)
{
	bool bRet = false;
	std::vector<ChartUnit *>::iterator iter;
	iter = m_listCharts.begin();
	while(iter != m_listCharts.end())
	{
		if ((*iter)->m_nSpecialType == c_spt)
		{
			return true;
		}
		else
			iter++;
	}
	return false;
}

void Charts::resetChartsColor()
{	
	int nColor = 0;
	for(int n=0; n<m_listCharts.size(); n++)
	{
		if (m_listCharts.at(n)->m_clLine < 20)
		{
			m_listCharts.at(n)->setLineColor(nColor);
			nColor++;
		}
	}
}

bool Charts::isMainPic()
{
	if (m_strType == PIC_KLINE)
		return true;
	return false;
}

void Charts::setTech(CString c_strTech,KLINE * c_pBlock,int c_nKItemCount,KLINE * c_pChgK,int c_nChgKCount)
{
	removeTech(true);
	if (c_strTech == PIC_RSI)
		setRSI(c_pBlock,c_nKItemCount);
	else
		if (c_strTech == PIC_MACD)
			setMACD(c_pBlock,c_nKItemCount);
		else
			if (c_strTech == PIC_KDJ)
				setKDJ(c_pBlock,c_nKItemCount);
			else
				if (c_strTech == PIC_HISK_VOL)
					setVOL(c_pBlock,c_nKItemCount);
}

void Charts::setMainTech(CString c_strTech,KLINE * c_pBlock,int c_nKItemCount)
{
	removeTech(false);
	if (c_strTech == PIC_EMA)
		setEMA(c_pBlock,c_nKItemCount);
	else
		if (c_strTech == PIC_BOLL)
			setBOLL(c_pBlock,c_nKItemCount);
		else
			if (c_strTech == PIC_MA)
				setMA(c_pBlock,c_nKItemCount);
			else
			if (c_strTech == PIC_MMA)
				setMMA(c_pBlock,c_nKItemCount);
	setTechType(c_strTech);
}
void Charts::setEMA(KLINE *c_pBlock,int c_nKItemCount)
{
	STECH tech;
	tech.m_strName = PIC_EMA;
	tech.m_usCycle = m_usCycle;
	CTechManager::getInstance()->getTech(&tech);

	int nCount = tech.m_nParamCount;
	int *pParams = new int[tech.m_nParamCount];
	for(int n=0; n<nCount; n++)
		pParams[n] = atoi(tech.m_acParams[n]);
	/*
	int nCount = 2;
	int *pParams = new int[2];
	pParams[0] = 12;
	pParams[1] = 60;
	*/
	ChartUnit * pLine;	

	float *pfData = new float[c_nKItemCount];
	for(int n=0; n<c_nKItemCount; n++)
		pfData[n] = c_pBlock[n].close;

	float *pfRet = new float[c_nKItemCount];
	for(int n=0; n<nCount; n++)
	{
		int *pn = (int *)malloc(c_nKItemCount * sizeof(int));
		Calc_Ema(pfRet,pfData,c_nKItemCount,pParams[n]);
		for(int k=0; k<c_nKItemCount; k++)
		{
			if (InValid(pfRet[k]))
				pn[k] = 0X7FFFFFFF;
			else
				pn[k] = int(pfRet[k]);
		}
		pLine = new ChartUnit();
		pLine->setChartUnitType(CULink);
		//pLine->setCell(w,s);
		pLine->setLineColor(n);
		CString strInfo;
		strInfo.Format(_T("EMA%d"),pParams[n]);
		pLine->setParam(pParams[n]);
		pLine->setTitle(strInfo);
		pLine->setRefer(RTMIN,0);		        
		pLine->setData((char *)pn,sizeof(int) * c_nKItemCount,true);
		pLine->setPrecision(2);
		pLine->setMultiplier(1000);
		pLine->setSpecialType(STEMA);
		addChartUnit(pLine);
	}
	delete [] pfRet;
	delete [] pfData;
	delete [] pParams;
	setTechType(PIC_EMA);
}

void Charts::setBOLL(KLINE *c_pBlock,int c_nKItemCount)
{
	STECH tech;
	tech.m_strName = PIC_BOLL;
	tech.m_usCycle = m_usCycle;
	CTechManager::getInstance()->getTech(&tech);

	int nCount = tech.m_nParamCount;
	int *pParams = new int[tech.m_nParamCount];
	for(int n=0; n<nCount; n++)
		pParams[n] = atoi(tech.m_acParams[n]);

	int nMA = pParams[0];
	int nOLL = pParams[1];
	int nBOLL2 = pParams[2];
	/*
	int nCount = 1;
	int *pParams = new int[2];
	pParams[0] = 26;
	pParams[1] = 60;
	*/    
	int nLineColor = m_listCharts.size() - 1;
	ChartUnit * pLine;    	

	float *pfData = new float[c_nKItemCount];
	for(int n=0; n<c_nKItemCount; n++)
		pfData[n] = float(c_pBlock[n].close);

	int N;
	N = pParams[1];

	float *pfBoll56 = new float[c_nKItemCount];

	float *pfBoll = new float[c_nKItemCount];
	float *pfStd = new float[c_nKItemCount];
	float *pfUpper = new float[c_nKItemCount];
	float *pfLower = new float[c_nKItemCount];

	Calc_Ma(pfBoll56,pfData,c_nKItemCount,nMA);//N日MA	
	Calc_Ma(pfBoll,pfData,c_nKItemCount,N);//N日MA	
	Calc_Std(pfStd,pfData,c_nKItemCount,N);//Boll

	for(int n=0; n<c_nKItemCount; n++)
	{
		if (InValid(pfBoll[n]) || InValid(pfStd[n]))
		{
			SetInValid(pfUpper[n]);
			SetInValid(pfLower[n]);
		}
		else
		{
			pfUpper[n] = pfBoll[n] + 2 *pfStd[n];
			pfLower[n] = pfBoll[n] - 2 *pfStd[n];
		}
	}

	int * pnBoll56 = (int *)malloc(c_nKItemCount * sizeof(int));
	int * pnBoll = (int *)malloc(c_nKItemCount * sizeof(int));
	int * pnUpper = (int *)malloc(c_nKItemCount * sizeof(int));
	int * pnLower = (int *)malloc(c_nKItemCount * sizeof(int));
	for(int n=0; n<c_nKItemCount; n++)
	{
		if (InValid(pfBoll[n]) || pfBoll[n] < 0)
			pnBoll[n] = 0X7FFFFFFF;
		else
			pnBoll[n] = int(pfBoll[n]);
		if (InValid(pfUpper[n]) || pfUpper[n] < 0)
			pnUpper[n] = 0X7FFFFFFF;
		else
			pnUpper[n] = int(pfUpper[n]);
		if (InValid(pfLower[n]) || pfLower[n] < 0)
			pnLower[n] = 0X7FFFFFFF;
		else
			pnLower[n] = int(pfLower[n]);

		if (InValid(pfBoll56[n]) || pfBoll56[n] < 0)
			pnBoll56[n] = 0X7FFFFFFF;
		else
			pnBoll56[n] = int(pfBoll56[n]);
	}
	delete [] pfData;
	delete [] pfBoll56;
	delete [] pfBoll;
	delete [] pfStd;
	delete [] pfUpper;
	delete [] pfLower;

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	//pLine->setCell(w,s);	

	pLine->setLineColor(gpSkinManager->getColor(BOLL_MIDS));

	CString strInfo;
	//strInfo = "ZLBOLL(26,56,2,55) MIDL";
	strInfo = "ZLBOLL MIDS";
	//strInfo = "MA(56)";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setPenStyle(PS_DASHDOT);
	pLine->setData((char *)pnBoll,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	pLine->setSpecialType(STBOLL);
	addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	//pLine->setCell(w,s);
	//pLine->setLineColor(gpSkinManager->getLineColor(nLineColor + 1));
	pLine->setLineColor(RGB(255,128,255));
	//pLine->setLineWidth(3);

	strInfo = "UPPS";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setData((char *)pnUpper,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	pLine->setSpecialType(STBOLL);
	addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	//pLine->setCell(w,s);
	//pLine->setLineColor(gpSkinManager->getLineColor(nLineColor + 2));
	pLine->setLineColor(RGB(128,0,255));
	//pLine->setLineWidth(3);

	strInfo= "LOWS";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setData((char *)pnLower,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);	
	pLine->setSpecialType(STBOLL);
	addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	//pLine->setCell(w,s);
	pLine->setLineColor(gpSkinManager->getColor(BOLL_MIDL));
	pLine->setLineWidth(2);
	//pLine->setPenStyle(PS_DASHDOT);
	strInfo = "MIDL";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setData((char *)pnBoll56,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);	
	pLine->setSpecialType(STBOLL);
	addChartUnit(pLine);

	delete [] pParams;
	setTechType(PIC_BOLL);
	addBOLL2(c_pBlock,c_nKItemCount,nBOLL2,nMA);		
}

void Charts::addBOLL2(KLINE *c_pBlock,int c_nKItemCount, int c_nBOLL,int c_nMA)
{    
	ChartUnit * pLine;

	float *pfData = new float[c_nKItemCount];
	for(int n=0; n<c_nKItemCount; n++)
		pfData[n] = float(c_pBlock[n].close);

	int N;
	N = c_nBOLL;

	float *pfBoll = new float[c_nKItemCount];
	float *pfStd = new float[c_nKItemCount];
	float *pfUpper = new float[c_nKItemCount];
	float *pfLower = new float[c_nKItemCount];

	Calc_Ma(pfBoll,pfData,c_nKItemCount,N);//N日MA	
	Calc_Std(pfStd,pfData,c_nKItemCount,N);//Boll

	Calc_Ma(pfBoll,pfData,c_nKItemCount,c_nMA);//26);//26日MA	换成26日
	for(int n=0; n<c_nKItemCount; n++)
	{
		if (InValid(pfBoll[n]) || InValid(pfStd[n]))
		{
			SetInValid(pfUpper[n]);
			SetInValid(pfLower[n]);
		}
		else
		{
			pfUpper[n] = pfBoll[n] + 2 *pfStd[n];
			pfLower[n] = pfBoll[n] - 2 *pfStd[n];
		}
	}

	//int * pnBoll = (int *)malloc(c_nKItemCount * sizeof(int));
	int * pnUpper = (int *)malloc(c_nKItemCount * sizeof(int));
	int * pnLower = (int *)malloc(c_nKItemCount * sizeof(int));
	for(int n=0; n<c_nKItemCount; n++)
	{
		//if (InValid(pfBoll[n]))
		//	pnBoll[n] = 0X7FFFFFFF;
		//else
		//	pnBoll[n] = int(pfBoll[n]);
		if (InValid(pfUpper[n]) || pfUpper[n] <= 0)
			pnUpper[n] = 0X7FFFFFFF;
		else
			pnUpper[n] = int(pfUpper[n]);
		if (InValid(pfLower[n]) || pfLower[n] <= 0)
			pnLower[n] = 0X7FFFFFFF;
		else
			pnLower[n] = int(pfLower[n]);
	}

	delete [] pfData;
	delete [] pfBoll;
	delete [] pfStd;
	delete [] pfUpper;
	delete [] pfLower;


	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);    
	//pLine->setLineColor(gpSkinManager->getLineColor(nLineColor + 1));
	pLine->setLineColor(RGB(255,0,0));
	pLine->setLineWidth(4);

	CString strInfo;
	strInfo = "UPPL";// = "U55";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setData((char *)pnUpper,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	pLine->setSpecialType(STBOLL);	
	addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	//pLine->setLineColor(gpSkinManager->getLineColor(nLineColor + 2));
	pLine->setLineColor(RGB(0,255,0));
	pLine->setLineWidth(4);

	strInfo = "LOWL";//= "L55";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setData((char *)pnLower,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);	
	pLine->setSpecialType(STBOLL);
	addChartUnit(pLine);
}

void Charts::setMA(KLINE *c_pBlock,int c_nKItemCount)
{
	STECH tech;
	tech.m_strName = PIC_MA;
	tech.m_usCycle = m_usCycle;
	CTechManager::getInstance()->getTech(&tech);

	int nCount = tech.m_nParamCount;
	int *pParams = new int[tech.m_nParamCount];
	for(int n=0; n<nCount; n++)
		pParams[n] = atoi(tech.m_acParams[n]);

	ChartUnit * pLine;	

	float *pfData = new float[c_nKItemCount];
	for(int n=0; n<c_nKItemCount; n++)
		pfData[n] = c_pBlock[n].close;

	float *pfRet = new float[c_nKItemCount];
	for(int n=0; n<nCount; n++)
	{
		int *pn = (int *)malloc(c_nKItemCount * sizeof(int));
		Calc_Ma(pfRet,pfData,c_nKItemCount,pParams[n]);
		for(int k=0; k<c_nKItemCount; k++)
		{
			if (InValid(pfRet[k]))
				pn[k] = 0X7FFFFFFF;
			else
				pn[k] = int(pfRet[k]);
		}
		pLine = new ChartUnit();
		pLine->setChartUnitType(CULink);
		//pLine->setCell(w,s);
		pLine->setLineColor(n);
		CString strInfo;
		strInfo.Format(_T("MA%d"),pParams[n]);
		pLine->setParam(pParams[n]);
		pLine->setTitle(strInfo);
		pLine->setRefer(RTMIN,0);		        
		pLine->setData((char *)pn,sizeof(int) * c_nKItemCount,true);
		pLine->setPrecision(2);
		pLine->setMultiplier(1000);
		pLine->setSpecialType(STMA);
		addChartUnit(pLine);
	}
	delete [] pfRet;
	delete [] pfData;
	delete [] pParams;
	setTechType(PIC_MA);
}

void Charts::setMMA(KLINE *c_pBlock,int c_nKItemCount)
{
	int nMove[3]={3,5,5};
	STECH tech;
	tech.m_strName = PIC_MMA;
	tech.m_usCycle = m_usCycle;
	CTechManager::getInstance()->getTech(&tech);

	int nCount = tech.m_nParamCount;
	int *pParams = new int[tech.m_nParamCount];
	for(int n=0; n<nCount; n++)
		pParams[n] = atoi(tech.m_acParams[n]);

	ChartUnit * pLine;	

	float *pfData = new float[c_nKItemCount];
	for(int n=0; n<c_nKItemCount; n++)
		pfData[n] = c_pBlock[n].close;

	float *pfRet = new float[c_nKItemCount];
	for(int n=0; n<nCount/2; n++)
	{
		nMove[n] = pParams[nCount/2 + n];
	}
	for(int n=0; n<nCount/2; n++)
	{
		int *pn = (int *)malloc((c_nKItemCount+nMove[n]) * sizeof(int));
		Calc_Ma(pfRet,pfData,c_nKItemCount,pParams[n]);
		for(int k=0; k<nMove[n]; k++)
		{
			pn[k] = 0X7FFFFFFF;
		}
/*		
		for(int k=0; k<c_nKItemCount-nMove[n]; k++)
		{
			if (InValid(pfRet[k]))
				pn[k+nMove[n]] = 0X7FFFFFFF;
			else
				pn[k+nMove[n]] = int(pfRet[k]);
		}*/

		for(int k=0; k<c_nKItemCount; k++)
		{
			if (InValid(pfRet[k]))
				pn[k+nMove[n]] = 0X7FFFFFFF;
			else
				pn[k+nMove[n]] = int(pfRet[k]);
		}

		pLine = new ChartUnit();
		pLine->setChartUnitType(CULink);
		//pLine->setCell(w,s);
		pLine->setLineColor(n);
		CString strInfo;
		strInfo.Format(_T("MMA%d"),pParams[n]);
		pLine->setParam(pParams[n]);
		pLine->setTitle(strInfo);
		pLine->setRefer(RTMIN,0);		        
		pLine->setData((char *)pn,sizeof(int) * (c_nKItemCount+nMove[n]),true);
		pLine->setPrecision(2);
		pLine->setMultiplier(1000);
		pLine->setSpecialType(STMMA);
		addChartUnit(pLine);
	}
	delete [] pfRet;
	delete [] pfData;
	delete [] pParams;
	setTechType(PIC_MA);
}

void Charts::setMACD(KLINE * c_pBlock,int c_nKItemCount)
{
	STECH tech;
	tech.m_strName = PIC_MACD;
	tech.m_usCycle = m_usCycle;
	CTechManager::getInstance()->getTech(&tech);

	int nCount = tech.m_nParamCount;
	int *pParams = new int[tech.m_nParamCount];
	pParams[0] = atoi(tech.m_acParams[0]);//12;
	pParams[1] = atoi(tech.m_acParams[1]);//26;
	pParams[2] = atoi(tech.m_acParams[2]);//9;

	ChartUnit * pLine;

	setTitle(PIC_MACD);
	setType(PIC_MACD,m_usCycle);	

	float *pfData = new float[c_nKItemCount];
	for(int n=0; n<c_nKItemCount; n++)
		pfData[n] = c_pBlock[n].close;

	int nShort,nLong,nMid;
	nShort = pParams[0];
	nLong = pParams[1];
	nMid = pParams[2];

	float *pfRetShort = new float[c_nKItemCount];
	float *pfRetLong = new float[c_nKItemCount];
	float *pfDiff = new float[c_nKItemCount];
	float *pfRetDea = new float[c_nKItemCount];
	float *pfMacd = new float[c_nKItemCount];

	Calc_Ema(pfRetShort,pfData,c_nKItemCount,nShort);//快线
	for(int n=0; n<c_nKItemCount; n++)
		pfData[n] = c_pBlock[n].close;

	Calc_Ema(pfRetLong,pfData,c_nKItemCount,nLong);//慢线
	for(int n=0; n<c_nKItemCount; n++)
	{
		if (InValid(pfRetShort[n]) || InValid(pfRetLong[n]))
		{
			SetInValid(pfDiff[n]);
		}
		else
			pfDiff[n] = pfRetShort[n] - pfRetLong[n];
	}
	Calc_Ema(pfRetDea,pfDiff,c_nKItemCount,nMid);//中间

	for(int n=0; n<c_nKItemCount; n++)
	{
		if (InValid(pfDiff[n]) || InValid(pfRetDea[n]))
		{
			SetInValid(pfMacd[n]);
		}
		else
			pfMacd[n] = 2 *(pfDiff[n] - pfRetDea[n]);
	}

	int * pnMacd = (int *)malloc(c_nKItemCount * sizeof(int));
	int * pnDea = (int *)malloc(c_nKItemCount * sizeof(int));
	int * pnDiff = (int *)malloc(c_nKItemCount * sizeof(int));
	for(int n=0; n<c_nKItemCount; n++)
	{
		if (InValid(pfMacd[n]))
			pnMacd[n] = 0X7FFFFFFF;
		else
			pnMacd[n] = int(pfMacd[n] * 100);
		if (InValid(pfDiff[n]))
			pnDiff[n] = 0X7FFFFFFF;
		else
			pnDiff[n] = int(pfDiff[n] * 100);
		if (InValid(pfRetDea[n]))
			pnDea[n] = 0X7FFFFFFF;
		else
			pnDea[n] = int(pfRetDea[n] * 100);
	}

	delete [] pfData;
	delete [] pfDiff;
	delete [] pfRetDea;
	delete [] pfRetShort;
	delete [] pfRetLong;
	delete [] pfMacd;

	pLine = new ChartUnit();
	pLine->setChartUnitType(CUTickLine);    
	pLine->setLineColor(0);
	CString strInfo;
	strInfo.Format(_T("MACD(%d,%d,%d)"),nShort,nLong,nMid);
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMID,0);
	pLine->setData((char *)pnMacd,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(100*1000);
	addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);    
	pLine->setLineColor(0);

	strInfo = "DIF";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMID,0);
	pLine->setData((char *)pnDiff,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(100*1000);
	addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setLineColor(1);

	strInfo= "DEA";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMID,0);
	pLine->setData((char *)pnDea,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(100*1000);
	addChartUnit(pLine);

	delete [] pParams;
}

void Charts::setKDJ(KLINE * c_pBlock,int c_nKItemCount)
{
	STECH tech;
	tech.m_strName = PIC_KDJ;
	tech.m_usCycle = m_usCycle;
	CTechManager::getInstance()->getTech(&tech);

	int nCount = tech.m_nParamCount;
	int *pParams = new int[tech.m_nParamCount];
	for(int n=0; n<nCount; n++)
		pParams[n] = atoi(tech.m_acParams[n]);

	setTitle(PIC_KDJ);
	setType(PIC_KDJ,m_usCycle);    

	ChartUnit * pLine;

	int N,M1,M2;
	N = pParams[0];
	M1 = pParams[1];
	M2 = pParams[2];

	float *pfLow = new float[c_nKItemCount];
	float *pfHigh = new float[c_nKItemCount];
	float *pfRSV = new float[c_nKItemCount];
	float *pfK = new float[c_nKItemCount];
	float *pfD = new float[c_nKItemCount];
	float *pfJ = new float[c_nKItemCount];
	float *pfData = new float[c_nKItemCount];
	for(int n=0; n<c_nKItemCount; n++)
		pfData[n] = c_pBlock[n].low;

	Calc_LLV(pfLow,pfData,c_nKItemCount,N);//取N日最低
	for(int n=0; n<c_nKItemCount; n++)
		pfData[n] = c_pBlock[n].high;
	Calc_HHV(pfHigh,pfData,c_nKItemCount,N);//取N日最高

	for(int n=0; n<c_nKItemCount; n++)//HHV-LLV
	{
		pfHigh[n] -= pfLow[n];
	}

	for(int n=0; n<c_nKItemCount; n++)//CLOSE-LLV
	{
		pfLow[n] = float(c_pBlock[n].close) - pfLow[n];
	}

	for(int n=0; n<c_nKItemCount; n++)//RSV
	{
		if (pfHigh[n] == 0)
		{
			SetInValid(pfRSV[n]);
		}
		else
		{
			pfRSV[n] = pfLow[n] / pfHigh[n] * 100;
		}
	}
	Calc_Sma(pfK,pfRSV,c_nKItemCount,M1,1);
	Calc_Sma(pfD,pfK,c_nKItemCount,M2,1);

	for(int n=0; n<c_nKItemCount; n++)
	{
		if (InValid(pfK[n]) || InValid(pfD[n]))
		{
			SetInValid(pfJ[n]);
		}
		else
			pfJ[n] = 3 * pfK[n] - 2 * pfD[n];
	}

	int * pnK = (int *)malloc(c_nKItemCount * sizeof(int));
	int * pnD = (int *)malloc(c_nKItemCount * sizeof(int));
	int * pnJ = (int *)malloc(c_nKItemCount * sizeof(int));
	for(int n=0; n<c_nKItemCount; n++)
	{
		if (InValid(pfK[n]))
			pnK[n] = 0X7FFFFFFF;
		else
			pnK[n] = int(pfK[n] * 1000);
		if (InValid(pfD[n]))
			pnD[n] = 0X7FFFFFFF;
		else
			pnD[n] = int(pfD[n] * 1000);
		if (InValid(pfJ[n]))
			pnJ[n] = 0X7FFFFFFF;
		else
			pnJ[n] = int(pfJ[n] * 1000);
	}	
	delete [] pfLow;
	delete [] pfHigh;
	delete [] pfRSV;
	delete [] pfK;
	delete [] pfD;
	delete [] pfJ;
	delete [] pfData;

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);    
	pLine->setLineColor(0);
	CString strInfo;
	strInfo.Format(_T("KDJ(%d,%d,%d) K"),N,M1,M2);
	pLine->setTitle(strInfo);
	pLine->setRefer(RTZERO,0);
	pLine->setData((char *)pnK,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);    
	pLine->setLineColor(1);

	strInfo = "D";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTZERO,0);
	pLine->setData((char *)pnD,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);    
	pLine->setLineColor(2);

	strInfo= "J";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTZERO,0);
	pLine->setData((char *)pnJ,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	addChartUnit(pLine);

	delete pParams;
}

void Charts::setRSI(KLINE * c_pBlock,int c_nKItemCount)
{
	STECH tech;
	tech.m_strName = PIC_RSI;
	tech.m_usCycle = m_usCycle;
	CTechManager::getInstance()->getTech(&tech);

	int nCount = tech.m_nParamCount;
	int *pParams = new int[tech.m_nParamCount];
	for(int n=0; n<nCount; n++)
		pParams[n] = atoi(tech.m_acParams[n]);

	setTitle(PIC_RSI);
	setType(PIC_RSI,m_usCycle);    

	ChartUnit * pLine;

	setTitle(PIC_RSI);
	setType(PIC_RSI,m_usCycle);    

	int N1,N2,N3;
	N1 = pParams[0];
	N2 = pParams[1];
	N3 = pParams[2];

	float *pfMax = new float[c_nKItemCount];
	float *pfAbs = new float[c_nKItemCount];
	float *pfRSI1 = new float[c_nKItemCount];
	float *pfRSI2 = new float[c_nKItemCount];
	float *pfRSI3 = new float[c_nKItemCount];
	float *pfRetMax = new float[c_nKItemCount];
	float *pfRetAbs = new float[c_nKItemCount];

	SetInValid(pfMax[0]);
	SetInValid(pfAbs[0]);

	for(int n=1; n<c_nKItemCount; n++)
	{
		pfMax[n] = float(c_pBlock[n].close) - float(c_pBlock[n-1].close);
		if (pfMax[n] < 0)
			pfMax[n] = 0;
		pfAbs[n] = abs(float(c_pBlock[n].close) - float(c_pBlock[n-1].close));
	}
	Calc_Sma(pfRetMax,pfMax,c_nKItemCount,N1,1);
	Calc_Sma(pfRetAbs,pfAbs,c_nKItemCount,N1,1);
	for(int n=0; n<c_nKItemCount; n++)
	{
		if (InValid(pfRetMax[n]) || InValid(pfRetAbs[n]) || pfRetAbs[n] == 0.0)
		{
			SetInValid(pfRSI1[n]);
		}
		else
			pfRSI1[n] = pfRetMax[n] / pfRetAbs[n] * 100;
	}

	Calc_Sma(pfRetMax,pfMax,c_nKItemCount,N2,1);
	Calc_Sma(pfRetAbs,pfAbs,c_nKItemCount,N2,1);
	for(int n=0; n<c_nKItemCount; n++)
	{
		if (InValid(pfRetMax[n]) || InValid(pfRetAbs[n]) || pfRetAbs[n] == 0.0)
		{
			SetInValid(pfRSI2[n]);
		}
		else
			pfRSI2[n] = pfRetMax[n] / pfRetAbs[n] * 100;
	}

	Calc_Sma(pfRetMax,pfMax,c_nKItemCount,N3,1);
	Calc_Sma(pfRetAbs,pfAbs,c_nKItemCount,N3,1);
	for(int n=0; n<c_nKItemCount; n++)
	{
		if (InValid(pfRetMax[n]) || InValid(pfRetAbs[n]))
		{
			SetInValid(pfRSI3[n]);
		}
		else
			pfRSI3[n] = pfRetMax[n] / pfRetAbs[n] * 100;
	}

	int * pnRSI1 = (int *)malloc(c_nKItemCount * sizeof(int));
	int * pnRSI2 = (int *)malloc(c_nKItemCount * sizeof(int));
	int * pnRSI3 = (int *)malloc(c_nKItemCount * sizeof(int));
	for(int n=0; n<c_nKItemCount; n++)
	{
		if (InValid(pfRSI1[n]))
			pnRSI1[n] = 0X7FFFFFFF;
		else
			pnRSI1[n] = int(pfRSI1[n] * 1000);
		if (InValid(pfRSI2[n]))
			pnRSI2[n] = 0X7FFFFFFF;
		else
			pnRSI2[n] = int(pfRSI2[n] * 1000);
		if (InValid(pfRSI3[n]))
			pnRSI3[n] = 0X7FFFFFFF;
		else
			pnRSI3[n] = int(pfRSI3[n] * 1000);
	}	
	delete pfMax;
	delete pfAbs;
	delete pfRSI1;
	delete pfRSI2;
	delete pfRSI3;
	delete pfRetMax;
	delete pfRetAbs;

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);    
	pLine->setLineColor(0);
	pLine->setSpecialType(STRSI);	

	CString strInfo;
	strInfo.Format(_T("RSI(%d,%d,%d) RSI1"),N1,N2,N3);
	pLine->setTitle(strInfo);
	pLine->setRefer(RTZERO,0);
	pLine->setData((char *)pnRSI1,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);    
	pLine->setLineColor(1);

	strInfo = "RSI2";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTZERO,0);
	pLine->setData((char *)pnRSI2,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);    
	pLine->setLineColor(2);

	strInfo= "RSI3";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTZERO,0);
	pLine->setData((char *)pnRSI3,sizeof(int) * c_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	addChartUnit(pLine);

	delete pParams;
}

void Charts::setVOL(KLINE * c_pBlock,int c_nKItemCount)
{
	STECH tech;
	tech.m_strName = PIC_HISK_VOL;
	tech.m_usCycle = m_usCycle;
	CTechManager::getInstance()->getTech(&tech);

	int nCount = tech.m_nParamCount;
	int *pParams = new int[tech.m_nParamCount];
	for(int n=0; n<nCount; n++)
		pParams[n] = atoi(tech.m_acParams[n]);

	setTitle(PIC_HISK_VOL);
	setType(PIC_HISK_VOL,m_usCycle);

	unsigned int unMax = 0;
	for(int n=0; n<c_nKItemCount; n++)
	{
		if (unMax < c_pBlock[n].volume)
			unMax = c_pBlock[n].volume;
	}
	int nToDiv = 1;
	if (unMax > 100000)//10万
		nToDiv =10;

	if (unMax > 1000000)//100万
		nToDiv = 100;

	if (unMax > 10000000)//1000万
		nToDiv = 1000;

	if (unMax > 10000*10000)//亿
		nToDiv = 10000;
	ChartUnit * pLine;

	pLine = new ChartUnit();
	pLine->setChartUnitType(CUVOL);    
	pLine->setLineColor(gpSkinManager->getColor(TITLECOLOR));
	pLine->setTitle(_T("VOLUME"));
	pLine->setData((char *)c_pBlock,c_nKItemCount * sizeof(KLINE),false);
	pLine->setPrecision(0);
	pLine->setDiv(nToDiv);
	pLine->setRefer(RTZERO,0);
	pLine->setMultiplier(1);

	addChartUnit(pLine);

	for(int n=0; n<nCount; n++)
	{
		pLine = new ChartUnit();
		pLine->setChartUnitType(CULink);        
		pLine->setLineColor(n);
		CString strInfo;
		strInfo.Format(_T("MA%d"),pParams[n]);
		pLine->setTitle(strInfo);
		pLine->setRefer(RTZERO,0);

		int *pn = (int *)malloc(sizeof(int) *c_nKItemCount);

		for(int k=0; k<pParams[n]-1 && k<c_nKItemCount; k++)
			pn[k] = 0X7FFFFFFF;
		for(int k=pParams[n]-1; k<c_nKItemCount; k++)
			pn[k] = 0;
		//
		for(int k=pParams[n]-1; k<c_nKItemCount; k++)
		{
			for(int j=k-pParams[n]+1; j<=k; j++)
				pn[k] += c_pBlock[j].volume/nToDiv;
		}
		for(int k=pParams[n]-1; k<c_nKItemCount; k++)
		{
			pn[k] /= pParams[n];
		}
		pLine->setData((char *)pn,sizeof(int) * c_nKItemCount,true);
		pLine->setPrecision(0);
		pLine->setMultiplier(1);
		addChartUnit(pLine);
	}

	delete pParams;
}


void Charts::setTechType(CString c_strType)
{
	m_strTechType = c_strType;
}

CString Charts::getTechType()
{
	return m_strTechType;
}

void Charts::setAixType(AixType c_at)
{
	m_atType = c_at;
	for(int n=0; n<m_listCharts.size(); n++)
		m_listCharts.at(n)->SetAixType(c_at);
}

AixType Charts::getAixType()
{
	return m_atType;
}

int Charts::getTimeByPos(int c_nPos)
{
	if (m_listCharts.size() == 0)
		return -1;

	return m_listCharts.at(0)->getTimeByPos(c_nPos);
}
