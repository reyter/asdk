// PicWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "../public/data.h"
#include "float.h"
#include "FinSmith.h"
#include "PicWnd.h"
#include "charts.h"
#include "Pics.h"
#include "DlgDiagnose.h"
#include "../public/skinmanager.h"
#include "DlgTechDesc.h"
#include "../public/commsocket.h"
#include "DlgContainer.h"
#include "Calc.h"
#include "TopDlg.h"
#include "DlgKDetail.h"
#include "DlgSelectTech.h"
#include "DlgParamSet.h"
#include "../public/CustomMenu.h"

// CPicWnd

IMPLEMENT_DYNAMIC(CPicWnd, CWnd)
void LogB(char * c_p,int nLen=0)
{/*
 FILE *f = fopen("c:\\test\\log","ab");
 if (f)
 {
 DWORD d = GetTickCount();
 char acBuf[16];		
 sprintf(acBuf,"%d:%d ",d,nLen);
 fseek(f,0,SEEK_END);
 fwrite(acBuf,1,strlen(acBuf),f);
 fwrite(c_p,1,strlen(c_p),f);
 fclose(f);
 }*/
}

CPicWnd::CPicWnd(PicType c_ptType,CPics * c_pPics,CDlgDiagnose * c_pDiagnose)
{	
	//m_atCur = AIXNORMAL;
	m_nCurPos = -1;
	m_atCur = (AixType)CTechManager::getInstance()->getAix();
	m_pPics = c_pPics;
	m_pDiagnose = c_pDiagnose;
	m_bHISKEMA = true;
	m_bHISKBOLL = false;
	m_nLockPointEnd = -1;
	m_bSizeRect = false;
	m_nSizeRect = -1;

	m_bDrawMainTechLine = true;
	m_nMinMaxItem = 243;
	m_pMinData = (MinUnit *)malloc(256 * sizeof(MinUnit));;
	m_nMinItemCount = 0;
	InitMinData();

	m_nKDataMaxLen = 4096 * sizeof(KLINE);
	m_pKData = (char *)malloc(m_nKDataMaxLen);
	m_usCycle = 5;//日线，6周线，7月线
	m_nZoom = 3;
	m_bDrawMouseLine = false;

	m_nHoriPointCount = 0;
	m_pnHoriPoint = NULL;
	m_nPointBegin = 0;
	m_nPointViewCount = 0;

	m_nLeftDis = 8;
	m_nRightDis = 54;
	m_nTopDis = 4;
	m_nBottomDis = 18;    

	m_nMouseX = -1;
	m_nMouseY = -1;

	m_ptType = c_ptType;
	if (m_ptType == PTTREND)
		m_usCycle = 0;
	//右侧留白单元

	m_nTailSpaceItems = 10;
	m_nFutrueItems = 0;
	/*
	LOGFONT LogFont;
	memset(&LogFont,0,sizeof(LogFont));
	LogFont.lfHeight = -12;
	LogFont.lfWeight = FW_NORMAL;//FW_MEDIUM;
	//LogFont.lfWeight = 400;
	//LogFont.lfWidth = 7;
	LogFont.lfCharSet = DEFAULT_CHARSET;
	LogFont.lfQuality = PROOF_QUALITY ;
	lstrcpy(LogFont.lfFaceName,gpSkinManager->GetDefaultFontName());
	//lstrcpy(LogFont.lfFaceName,_T("Arial"));
	m_pTextFont = new CFont();
	m_pTextFont->CreateFontIndirect(&LogFont);
	*/
	m_bInGetReport = false;
	gpKDetail->m_pPicWnd = this;	
}

CPicWnd::~CPicWnd()
{
	while(m_listPics.size())
	{
		delete *(m_listPics.begin());
		m_listPics.erase(m_listPics.begin());
	}
	if (m_pKData)
		free(m_pKData);
}


BEGIN_MESSAGE_MAP(CPicWnd, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MONK, &CPicWnd::OnMonk)
	ON_COMMAND(ID_WEEKK, &CPicWnd::OnWeekk)
	ON_COMMAND(ID_DAYK, &CPicWnd::OnDayk)
	ON_COMMAND(ID_REALMIN, &CPicWnd::OnRealmin)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_COMMAND(ID_ADD_STOCK, &CPicWnd::OnAddStock)
	ON_WM_CHAR()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_TECH_DESC, &CPicWnd::OnTechDesc)
	ON_COMMAND(ID_MACD, &CPicWnd::OnMacd)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_SELECT_TECH, &CPicWnd::OnSelectTech)
	ON_COMMAND(ID_SET_TECH_PARAM, &CPicWnd::OnSetTechParam)
	ON_COMMAND(ID_MIN1K, &CPicWnd::OnMin1k)
	ON_COMMAND(ID_MIN5K, &CPicWnd::OnMin5k)
	ON_COMMAND(ID_MIN15K, &CPicWnd::OnMin15k)
	ON_COMMAND(ID_MIN30K, &CPicWnd::OnMin30k)
	ON_COMMAND(ID_MIN60K, &CPicWnd::OnMin60k)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_SHOW_HIDE_MAIN_TECH, &CPicWnd::OnShowHideMainTech)
	ON_COMMAND(ID_AIX_NORMAL, &CPicWnd::OnAixNormal)
	ON_COMMAND(ID_AIX_LG, &CPicWnd::OnAixLg)
	ON_COMMAND(ID_WEIGHT_FRONT, &CPicWnd::OnWeightFront)
	ON_COMMAND(ID_WEIGHT_NONE, &CPicWnd::OnWeightNone)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()



// CPicWnd 消息处理程序

void CPicWnd::setPicType(PicType c_ptType)
{
	m_ptType = c_ptType;
}

PicType CPicWnd::getPicType()
{
	return m_ptType;
}
BOOL CPicWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CRect rect;
	GetClientRect(rect);
	calcChartsMaxMinValue();

	CDC SourceDC;
	CBitmap bitmap,*pOldBitmap;
	bitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CFont *pOldFont;	

	SourceDC.CreateCompatibleDC(NULL);//生成兼容的CDC
	pOldBitmap = SourceDC.SelectObject(&bitmap);

	pOldFont = SourceDC.SelectObject(gpSkinManager->GetGraphFont());//m_pTextFont);
	CBrush br(RGB(255,255,255));
	CBrush * pOldBrush = SourceDC.SelectObject(&br);

	m_lockPics.WaitRead();

	paintMe(&SourceDC);	
	drawMoveRect(&SourceDC);
	drawMouseLine(&SourceDC);
	if (((CPics *)this->GetParent())->m_nViewMode)
		gpSkinManager->FillRectImage(gpSkinManager->GetBitmap(ID_TWO_WIN),&SourceDC,m_rectSetWin);
	else
		gpSkinManager->FillRectImage(gpSkinManager->GetBitmap(ID_ONE_WIN),&SourceDC,m_rectSetWin);

	//CImage img;
	//img.Load(_T("d:\\16g.png"));	
	//img.Draw(SourceDC.GetSafeHdc(),m_rectPriceAlert.left,m_rectPriceAlert.top);
	if(m_ptType == PTHISK)
	{
		if (ROLE_PRICE_ALERT & gpData->m_dwRole)
			gpSkinManager->FillRectImage(IDB_LIGHT,&SourceDC,m_rectPriceAlert);
		if (ROLE_TRADE_AREA & gpData->m_dwRole)
			gpSkinManager->FillRectImage(IDB_TRADEAREA,&SourceDC,m_rectTradeArea);
		if (ROLE_CUT_LINE & gpData->m_dwRole)
			gpSkinManager->FillRectImage(IDB_CUTLINE,&SourceDC,m_rectCutLine);
	}
	if (m_bDrawMouseLine)
	{		
		drawDetail(&SourceDC);
	}
	SourceDC.SelectObject(pOldBrush);
	rect.top = rect.bottom - m_nBottomDis/2;
	GetClientRect(rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&SourceDC,0,0,SRCCOPY);	
	SourceDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	SourceDC.SelectObject(pOldFont);
	SourceDC.DeleteDC();	

	m_lockPics.EndRead();
	return TRUE;
	return CWnd::OnEraseBkgnd(pDC);
}

void CPicWnd::getZoom(int c_nZoom, int &c_nWidth, int &c_nSpace)
{
	if (m_ptType == PTTREND)
	{
		c_nWidth = 1;
		c_nSpace = 0;
		return;
	}
	if(c_nZoom < 0)
	{
		c_nWidth = c_nZoom - 1;
		c_nSpace = 0;
	}
	else
		if (c_nZoom == 0)
		{
			c_nWidth = 1;
			c_nSpace = 0;
		}
		else
			if (c_nZoom == 1)
			{
				c_nWidth = 1;
				c_nSpace = 1;
			}
			else
				if (c_nZoom == 2)
				{
					c_nWidth = 1;
					c_nSpace = 2;
				}
				else
					if (c_nZoom == 3)
					{
						c_nWidth = 3;
						c_nSpace = 2;
					}
					else
						if (c_nZoom == 4)
						{
							c_nWidth = 5;
							c_nSpace = 2;
						}
						else
							if (c_nZoom == 5)
							{
								c_nWidth = 7;
								c_nSpace = 3;
							}
							else
								if (c_nZoom == 6)
								{
									c_nWidth = 17;
									c_nSpace = 7;
								}
								else
									if (c_nZoom == 7)
									{
										c_nWidth = 33;
										c_nSpace = 11;
									}
									else
										if (c_nZoom == 8)
										{
											c_nWidth = 59;
											c_nSpace = 19;
										}
										else
											if (c_nZoom == 9)
											{
												c_nWidth = 95;
												c_nSpace = 32;
											}

}

void CPicWnd::setStockCode(CString c_strStockCode)
{	
	//Log("A\n");
	SStock *p = gpData->GetStock(c_strStockCode);	

	if (!p)
		return;
	m_nStockId = p->m_sQuote.nStockId;
	char acCode[16];
	strcpy(acCode,p->m_sQuote.szStockCode);
	acCode[6] = 0;

	resetMouseString();

	gpKDetail->SetSSTOCK(p);	

	m_strStockCode = c_strStockCode;
	GetReport(true);
	m_strStockName = p->m_strName;
	m_nHoriPointCount = 0;
	m_nPointViewCount = 0;

	//Log("H\n");
	getPicData();
	createFutureKLine();

	m_lockPics.WaitWrite();
	createPic();
	//resetZoom();
	//resetSize();
	//onSizeChange();	

	resetZoom();
	resetSize();
	onSizeChange();		
	m_lockPics.EndWrite();
	//Log("OVER\n");
}

void CPicWnd::paintMe(CDC * c_pDC)
{        
	CBrush brush(gpSkinManager->getColor(BKCOLOR));

	CRect rect;
	GetClientRect(rect);
	c_pDC->FillRect(rect,&brush);

	if (m_strStockCode.IsEmpty())
		return;

	CPen penUp(PS_SOLID,1,gpSkinManager->getColor(AIXLINE));
	CPen penUp2(PS_SOLID,3,gpSkinManager->getColor(AIXLINE));	

	CBrush * pOldBrush = c_pDC->SelectObject(&brush);
	c_pDC->Rectangle(m_rectAix);	

	for(int n=0; n<m_listPics.size(); n++)
	{
		CRect rectHead,rectBody,rectFoot;
		m_listPics.at(n)->getRectBody(rectBody);
		m_listPics.at(n)->getRectHead(rectHead);
		m_listPics.at(n)->getRectFoot(rectFoot);
		c_pDC->SelectObject(brush);
		CPen *pOldPen;
		if (m_listPics.at(n)->getSelected())
			pOldPen = c_pDC->SelectObject(&penUp2);
		else
			pOldPen = c_pDC->SelectObject(&penUp);
		if (m_listPics.at(n)->m_bVisible)
			c_pDC->Rectangle(CRect(rectHead.left,rectHead.top,rectHead.left + rectHead.Width(),rectHead.top + rectHead.Height() + rectBody.Height() + rectFoot.Height()));        
		c_pDC->SelectObject(pOldPen);
	}
	c_pDC->SelectObject(pOldBrush);

	drawTitle(c_pDC);
	drawRefer(c_pDC);

	for(int n=0; n<m_listPics.size(); n++)
	{
		if (n == 0)
		{
			if (m_listPics.size() && m_listPics.at(0)->m_listCharts.size())
				m_listPics.at(n)->m_listCharts.at(0)->ResetPriceAlertX();
			SStock * pStock = gpData->GetStock(m_strStockCode);
			m_listPics.at(n)->drawCharts(c_pDC,m_strStockCode,m_bDrawMainTechLine);
		}
		else
		{
			if (m_listPics.at(n)->m_bVisible)
				m_listPics.at(n)->drawCharts(c_pDC,m_strStockCode);
		}
	}


	if (m_nHoriPointCount == 0)
		return;
	if (m_nPointViewCount == 0)
		return;

	if (m_listPics.size() > 0)
	{
		if (m_nKItemCount + m_nFutrueItems < 4096)
			m_listPics.at(0)->getChartUnit(0)->drawXCoord(c_pDC,m_rectAix,m_nKItemCount + m_nFutrueItems);
		else
			m_listPics.at(0)->getChartUnit(0)->drawXCoord(c_pDC,m_rectAix,4096);
	}

	/*
	for(int n=0; n<m_listCharts.size(); n++)
	{
	m_pManualDraw->Draw(c_pDC,m_listCharts.at(n));        
	}
	*/
}

void CPicWnd::drawTitle(CDC * c_pDC)
{

}

void CPicWnd::drawRefer(CDC * c_pDC)
{
	for(int n=0; n<m_listPics.size(); n++)
	{
		if (m_listPics.at(n)->m_bVisible)
			m_listPics.at(n)->drawRefer(c_pDC);
	}
}

Charts * CPicWnd::isMouseInCharts(CPoint c_point)
{
	for(int n=0; n<m_listPics.size(); n++)
	{
		CRect rect,rectH,rectB;
		m_listPics.at(n)->getRectBody(rect);
		m_listPics.at(n)->getRectHead(rectH);
		m_listPics.at(n)->getRectFoot(rectB);
		rect.left -= 1;
		rect.top -= 1;
		rect.bottom += 1;
		rect.right += 1;
		if (rect.PtInRect(c_point) || rectH.PtInRect(c_point) || rectB.PtInRect(c_point))
			return m_listPics.at(n);
	}
	return NULL;
}

Charts * CPicWnd::getChartsSelected()
{
	for(int n=0; n<m_listPics.size(); n++)
	{
		if (m_listPics.at(n)->getSelected())
			return m_listPics.at(n);
	}
	return NULL;
}

Charts * CPicWnd::setChartsSelected(CPoint c_point)
{
	Charts * pSel = NULL;
	for(int n=0; n<m_listPics.size(); n++)
	{
		CRect rect,rectH,rectB;
		m_listPics.at(n)->getRectBody(rect);
		m_listPics.at(n)->getRectHead(rectH);
		m_listPics.at(n)->getRectFoot(rectB);
		rect.left -= 1;
		rect.top -= 1;
		rect.bottom += 1;
		rect.right += 1;
		if (rect.PtInRect(c_point) || rectH.PtInRect(c_point) || rectB.PtInRect(c_point))
		{
			pSel =  m_listPics.at(n);
			if (pSel->m_bVisible)
				pSel->setSelected(true);
			else
				pSel->setSelected(false);
		}
		else
			m_listPics.at(n)->setSelected(false);
	}
	return pSel;
}

void CPicWnd::resetMouseString()
{
	m_strMouseX = "";
	m_strMouseY = "";
}

void CPicWnd::getMouseString(CPoint c_point)
{
	m_strMouseX = "";
	m_strMouseY = "";
	if (m_listPics.size() == 0)
		return;
	if (m_listPics.at(0)->m_listCharts.size() == 0)
		return;

	int nXPos = getXPos(c_point.x);
	if (nXPos >= 0)
		m_strMouseX = m_listPics.at(0)->getChartUnit(0)->getXValueString(nXPos,m_usCycle);
	else
		m_strMouseX = "";
	for(int n=0; n<m_listPics.size(); n++)
	{
		if (m_listPics.at(n)->m_listCharts.size() == 0)
			continue;
		CRect rect;
		m_listPics.at(n)->getRectBody(rect);
		if (rect.PtInRect(c_point))
		{
			m_strMouseY = m_listPics.at(n)->getChartUnit(0)->getYValueString(c_point.y);			
		}
	}
}

void CPicWnd::resetSize()
{
	int nFontW = gpSkinManager->GetFontWidth(gpSkinManager->GetGraphFont(),_T("123456."));
	if (nFontW < 56)
		nFontW = 56;
	m_nRightDis = nFontW + 4;
	int nFontH = gpSkinManager->GetFontHeight(gpSkinManager->GetGraphFont());
	nFontH += 2;
	if (nFontH < 18)
		nFontH = 18;
	if (m_ptType == PTTREND)
	{
		m_nLeftDis = nFontW + 4;
		m_nBottomDis = nFontH;
	}
	else
	{
		m_nLeftDis = 8;
		m_nBottomDis = nFontH + nFontH;
	}
	CRect rect;
	GetClientRect(rect);

	m_rectAix.SetRect(m_nLeftDis,m_nTopDis,rect.Width() - m_nRightDis,rect.Height() - m_nBottomDis);
	m_rectDraw = m_rectAix;

	if (m_listPics.size() == 0)
		return;

	int nPerH;
	if (m_listPics.size() == 2)
		nPerH = (rect.Height() - m_nTopDis - m_nBottomDis) / (4);
	else
		if (m_listPics.size() == 3)
			nPerH = (rect.Height() - m_nTopDis - m_nBottomDis) / (5);
		else
			return;		

	CRect rectBody,rectHead,rectFoot;    
	rectBody.SetRect(m_rectDraw.left ,m_rectDraw.top ,m_rectDraw.right, m_rectDraw.bottom - nPerH * (m_listPics.size()-1));
	m_listPics.at(0)->setSize(rectBody);
	m_rectMainPic = rectBody;
	rectBody.SetRect(m_rectDraw.left ,m_rectDraw.bottom  - nPerH * (m_listPics.size()-1) ,m_rectDraw.right, m_rectDraw.bottom - nPerH * (m_listPics.size()-2));
	m_listPics.at(1)->setSize(rectBody);

	if (m_listPics.size() < 3)
		return;

	CRect rectOne,rectTwo;
	rectOne = rectBody;
	rectBody.SetRect(m_rectDraw.left ,m_rectDraw.bottom - nPerH,m_rectDraw.right, m_rectDraw.bottom);
	m_listPics.at(2)->setSize(rectBody);
	rectTwo = rectBody;
	if (m_listPics.at(1)->m_bVisible == false)
	{
		rectTwo.top = rectOne.top;
		m_listPics.at(2)->setSize(rectTwo);
	}
	else
		if (m_listPics.at(2)->m_bVisible == false)
		{
			rectOne.bottom = rectTwo.bottom;
			m_listPics.at(1)->setSize(rectOne);
		}
}

void CPicWnd::setBeginEndPos(int c_nWay,int c_nStep)
{
	if (m_nPointViewCount <= 0)
		return;
	int nTotalPoint;
	if (m_ptType == PTTREND)
		nTotalPoint = m_nMinItemCount;
	else
		nTotalPoint = m_nKItemCount;

	if (nTotalPoint <= 0)
		return;
	if(c_nWay == 1)//往左移动
	{
		m_nPointBegin -= c_nStep;
		if (m_nPointBegin < 0)
			m_nPointBegin = 0;
		m_nPointViewCount += c_nStep;

		//m_nPointViewCount = nTotalPoint - m_nPointBegin - 1;
		if (m_nPointViewCount > m_nMaxViewPointCount)
			m_nPointViewCount = m_nMaxViewPointCount;
		if (m_nPointViewCount < 0)
		{
			m_nPointViewCount = 0;
		}
	}
	else
		if (c_nWay == 2 || c_nWay == 3)//向右移动
		{		
			if (m_nPointViewCount + m_nPointBegin == nTotalPoint - 1)//已经是最终点
				return;
			if (m_nPointViewCount == m_nMaxViewPointCount)//相等，后移动
			{
				m_nPointBegin += c_nStep;//移动单位
			}
			else
				if (c_nWay == 3)
					m_nPointBegin += c_nStep;

			m_nPointViewCount = nTotalPoint - m_nPointBegin;
			if (m_nPointViewCount > m_nMaxViewPointCount)
				m_nPointViewCount = m_nMaxViewPointCount;

		}
		else
			if (c_nWay != 0)
			{		
				m_nPointViewCount = nTotalPoint - m_nPointBegin - 1;
				if (m_nPointViewCount > m_nMaxViewPointCount)
					m_nPointViewCount = m_nMaxViewPointCount;
			}
			m_nPointBeginTime = m_listPics.at(0)->getTimeByPos(m_nPointBegin);
			for(int n=0; n<m_listPics.size(); n++)
			{
				if (n == 2)
					m_listPics.at(n)->setChartsViewProperty(m_nHoriPointCount,m_pnHoriPoint,m_nPointBegin,m_nPointBeginTime,m_nPointViewCount);
				else
					m_listPics.at(n)->setChartsViewProperty(m_nHoriPointCount,m_pnHoriPoint,m_nPointBegin,m_nPointBeginTime,m_nPointViewCount);
			}

			calcChartsMaxMinValue();	
}

void CPicWnd::onSizeChange(int c_nPointBegin)
{    
	int w,s;
	getZoom(m_nZoom,w,s);

	if (m_strStockCode.IsEmpty())
		return;

	SStock * pStock = gpData->GetStock(m_strStockCode);
	if (pStock == NULL)
		return;

	int nItemCount = 0;
	int nPreClose = 0;
	if (m_ptType == PTTREND)
	{
		m_nPointBegin = 0;
		if (m_nMinItemCount == 0)
			return;

		MinUnit * pBlock = (MinUnit *)m_pMinData;				
		if (pBlock == NULL)
			return;
		nItemCount = m_nMinItemCount;
		nPreClose = pStock->m_unPrevClose;
	}
	else
	{
		KLINE * pBlock = (KLINE *)m_pKData;		
		if (pBlock == NULL)
			return;
		if (m_nKItemCount <= 0)
			return;
		nItemCount = m_nKItemCount;
	}


	int nMaxPoint = 0;
	if (m_ptType == PTTREND)
	{
		nMaxPoint = 242;
		if (m_nHoriPointCount > nMaxPoint)
			m_nHoriPointCount = 242;
	}
	else
	{
		if (w > 0)
			nMaxPoint = m_rectAix.Width() / (w + s);//最大显示点数
		else
			nMaxPoint = (m_rectAix.Width() - 1) * abs(w);
	}
	if (nMaxPoint < 0)
		nMaxPoint = 0;
	m_nMaxViewPointCount = nMaxPoint;
	if (m_nHoriPointCount < nMaxPoint)//设置水平坐标
	{
		if (m_nHoriPointCount > 0)
			delete [] m_pnHoriPoint;
		m_nHoriPointCount = nMaxPoint;
		ASSERT(m_nHoriPointCount<1024*1024);
		m_pnHoriPoint = new int[m_nHoriPointCount];
	}

	if (m_ptType == PTTREND)
	{
		float f;
		f = float(m_rectAix.Width()) / m_nHoriPointCount;
		for(int n=0; n<m_nHoriPointCount; n++)
			m_pnHoriPoint[n] = f * n;
	}
	else
	{
		if(w > 0)
		{
			for(int n=0; n<m_nHoriPointCount; n++)
				m_pnHoriPoint[n] = (w + s) * n;
		}
		else
		{
			for(int n=0; n<m_nHoriPointCount; n++)
			{
				m_pnHoriPoint[n] = n/abs(w);
			}
		}
	}
	if (m_ptType == PTHISK)
		resetViewHiskPoints(c_nPointBegin);
	else
		if (m_ptType == PTTREND)
			resetViewTrendPoints();
	/*
	if (nMaxPoint >= nItemCount + m_nSpaceItems)//可以全部显示
	{
	m_nPointBegin = 0;
	m_nPointViewCount = nItemCount;
	}
	else
	{		
	if (m_nPointViewCount == 0)//remember this,first time,show tail
	{
	m_nPointViewCount = nMaxPoint - m_nSpaceItems;
	m_nPointBegin = nItemCount - m_nPointViewCount;
	}
	else
	{
	m_nPointViewCount = nMaxPoint;
	if (nItemCount < nMaxPoint)
	m_nPointViewCount = nItemCount;

	if (m_nLockPointEnd > 0)//锁定结束位置
	{
	//m_nPointCount -= m_nSpcaeItems;
	m_nPointBegin = m_nLockPointEnd - m_nPointViewCount + 1;
	}
	}
	if (m_nPointBegin < 0)
	m_nPointBegin = 0;
	if (m_nPointBegin > nItemCount)
	m_nPointBegin = 0;
	if (m_nPointBegin + m_nPointViewCount >= nItemCount)
	m_nPointViewCount = nItemCount - m_nPointBegin;
	}

	if (m_nHoriPointCount <= 0 || !m_pnHoriPoint || m_nPointViewCount <= 0 || m_nHoriPointCount>10000)
	{
	m_nHoriPointCount = 0;
	m_nPointViewCount = 0;
	return;
	}
	for(int n=0; n<m_listPics.size(); n++)
	{
	if (n == 2)
	m_listPics.at(n)->setChartsViewProperty(m_nHoriPointCount,m_pnHoriPoint,m_nPointBegin,m_nPointViewCount);
	else
	m_listPics.at(n)->setChartsViewProperty(m_nHoriPointCount,m_pnHoriPoint,m_nPointBegin,m_nPointViewCount);
	}
	calcChartsMaxMinValue();
	*/
	Invalidate();
}

void CPicWnd::resetViewTrendPoints()
{    
	int w,s;
	getZoom(m_nZoom,w,s);

	if (m_strStockCode.IsEmpty())
		return;

	if (m_ptType != PTTREND)
		return;

	SStock * pStock = gpData->GetStock(m_strStockCode);
	if (pStock == NULL)
		return;

	int nItemCount = 0;
	int nPreClose = 0;

	m_nPointBegin = 0;
	m_nPointViewCount = m_nMinItemCount;	
	if (m_nMinItemCount == 0)
		return;

	MinUnit * pBlock = (MinUnit *)m_pMinData;				
	if (pBlock == NULL)
		return;
	nItemCount = m_nMinItemCount;
	nPreClose = pStock->m_unPrevClose;

	m_nMaxViewPointCount = 242;

	if (m_nHoriPointCount < 242)
	{
		delete [] m_pnHoriPoint;
		m_nHoriPointCount = 242;
		ASSERT(m_nHoriPointCount<1024*1024);
		m_pnHoriPoint = new int[m_nHoriPointCount];
	}
	float f;
	f = float(m_rectAix.Width()) / m_nHoriPointCount;
	for(int n=0; n<m_nHoriPointCount; n++)
		m_pnHoriPoint[n] = f * n;

	if (m_listPics.size())
		m_nPointBeginTime = m_listPics.at(0)->getTimeByPos(m_nPointBegin);
	for(int n=0; n<m_listPics.size(); n++)
	{
		if (n == 2)
			m_listPics.at(n)->setChartsViewProperty(m_nHoriPointCount,m_pnHoriPoint,m_nPointBegin,m_nPointBeginTime,m_nPointViewCount);
		else
			m_listPics.at(n)->setChartsViewProperty(m_nHoriPointCount,m_pnHoriPoint,m_nPointBegin,m_nPointBeginTime,m_nPointViewCount);
	}

	calcChartsMaxMinValue();
}

void CPicWnd::resetViewHiskPoints(int c_nPointBegin)
{    
	m_nPointBegin = c_nPointBegin;
	m_nPointViewCount = 0;

	if (c_nPointBegin > 0)
		m_nLockPointEnd = -1;
	if (m_ptType != PTHISK)
		return;

	int w,s;
	getZoom(m_nZoom,w,s);

	if (m_strStockCode.IsEmpty())
		return;

	SStock * pStock = gpData->GetStock(m_strStockCode);
	if (pStock == NULL)
		return;

	int nItemCount = 0;
	int nPreClose = 0;

	KLINE * pBlock = (KLINE *)m_pKData;		
	if (pBlock == NULL)
		return;
	if (m_nKItemCount <= 0)
		return;
	nItemCount = m_nKItemCount;


	int nMaxPoint = 0;

	if (w > 0)
		nMaxPoint = m_rectAix.Width() / (w + s);//最大显示点数
	else
		nMaxPoint = (m_rectAix.Width() - 1) * abs(w);

	if (nMaxPoint < 0)
	{
		nMaxPoint = 0;
		return;
	}
	m_nMaxViewPointCount = nMaxPoint;
	if (m_nHoriPointCount < nMaxPoint)//设置水平坐标
	{
		if (m_nHoriPointCount > 0)
			delete [] m_pnHoriPoint;
		m_nHoriPointCount = nMaxPoint;
		ASSERT(m_nHoriPointCount<1024*1024);
		m_pnHoriPoint = new int[m_nHoriPointCount];
	}
	m_nHoriPointCount = nMaxPoint;

	if(w > 0)
	{
		for(int n=0; n<m_nHoriPointCount; n++)
			m_pnHoriPoint[n] = (w + s) * n;
	}
	else
	{
		for(int n=0; n<m_nHoriPointCount; n++)
		{
			m_pnHoriPoint[n] = n/abs(w);
		}
	}

	if (nMaxPoint >= nItemCount + m_nTailSpaceItems + m_nFutrueItems)//可以全部显示
	{
		m_nPointBegin = 0;
		m_nPointViewCount = nItemCount;
	}
	else
		if (nMaxPoint > nItemCount)//可以全部显示
		{
			m_nPointBegin = m_nTailSpaceItems + m_nFutrueItems - nMaxPoint;
			if (m_nPointBegin < 0)
				m_nPointBegin = 0;
			m_nPointViewCount = nItemCount - m_nPointBegin;
		}
		else
		{		
			if (m_nPointViewCount == 0 && m_nLockPointEnd <= 0)//remember this,first time,show tail
			{				
				if(c_nPointBegin == 0)
					m_nPointViewCount = nMaxPoint - m_nTailSpaceItems - m_nFutrueItems;
				else
					m_nPointViewCount = nMaxPoint - m_nFutrueItems;

				if (m_nPointViewCount <= 0)
					m_nPointViewCount = 1;
				if(c_nPointBegin == 0)
					m_nPointBegin = nItemCount - m_nPointViewCount;
				else
				{
					if (nItemCount - m_nPointBegin < m_nPointViewCount)
						m_nPointViewCount = nItemCount - m_nPointBegin;
				}
			}
			else
			{
				m_nPointViewCount = nMaxPoint - m_nFutrueItems;
				if (m_nPointViewCount < 0)
					m_nPointViewCount = 1;
				//if (nItemCount < nMaxPoint)
				//	m_nPointViewCount = nItemCount;

				if (m_nLockPointEnd > 0)//锁定结束位置
				{				
					m_nPointBegin = m_nLockPointEnd - m_nPointViewCount + 1;
					if (m_nLockPointEnd == nItemCount-1)//最后一个
					{
						if (m_nPointViewCount > m_nTailSpaceItems)
						{
							m_nPointBegin += m_nTailSpaceItems;
							m_nPointViewCount -= m_nTailSpaceItems;
						}
					}
				}
			}
			if (m_nPointBegin < 0)
				m_nPointBegin = 0;
			if (m_nPointBegin > nItemCount)
				m_nPointBegin = 0;						
		}

		if (m_nHoriPointCount <= 0 || m_pnHoriPoint <= 0 || m_nPointViewCount <= 0 || m_nHoriPointCount>10000)
		{
			m_nHoriPointCount = 0;
			m_nPointViewCount = 0;
			return;
		}
		setChartsViewPoints();
}

void CPicWnd::setChartsViewPoints()
{
	if (m_listPics.size() == 0)
		return;
	m_nPointBeginTime = m_listPics.at(0)->getTimeByPos(m_nPointBegin);
	for(int n=0; n<m_listPics.size(); n++)
	{
		m_listPics.at(n)->setChartsViewProperty(m_nHoriPointCount,m_pnHoriPoint,m_nPointBegin,m_nPointBeginTime,m_nPointViewCount);
	}

	calcChartsMaxMinValue();
}

void CPicWnd::setZoom(int c_nZoom,int c_nPointBegin)
{
	if (c_nZoom < 9 && c_nZoom > 0)
	{
		m_nZoom = c_nZoom;
		int w,s;
		getZoom(m_nZoom,w,s);
		for(int n=0; n<m_listPics.size(); n++)
			m_listPics.at(n)->setChartsCell(w,s);
		if (this->m_ptType == PTHISK)
		{
			if (m_nKItemCount < c_nPointBegin)
				m_nPointBegin = 0;
			else
				m_nPointBegin = c_nPointBegin;
		}
		else
		{
			m_nPointBegin = 0;
		}		

		onSizeChange();
		calcChartsMaxMinValue();
	}
}

void CPicWnd::resetZoom()
{
	int w,s;
	getZoom(m_nZoom,w,s);
	for(int n=0; n<m_listPics.size(); n++)
		m_listPics.at(n)->setChartsCell(w,s);
}

void CPicWnd::goUp(int c_nPointBegin)
{
	if (m_nZoom < 9)
	{
		m_nZoom++;
		int w,s;
		getZoom(m_nZoom,w,s);
		for(int n=0; n<m_listPics.size(); n++)
			m_listPics.at(n)->setChartsCell(w,s);
		onSizeChange(c_nPointBegin);
	}
}

void CPicWnd::goDown()
{
	if (m_nZoom > -4)
	{
		m_nZoom--;
		int w,s;
		getZoom(m_nZoom,w,s);
		for(int n=0; n<m_listPics.size(); n++)
			m_listPics.at(n)->setChartsCell(w,s);
		m_nPointBegin = -1;		
		onSizeChange();
	}
}

void CPicWnd::goLeft()
{
	int x,y;
	int nPos = 0;
	getMousePos(x,y);
	if (m_nCurPos >=0 && m_nCurPos < m_nPointViewCount)
		nPos = m_nCurPos;
	else
		nPos = getXPos(x);
	if (m_bDrawMouseLine)
	{		
		nPos--;
	}
	else
	{
		if (m_nPointViewCount > 0)
			nPos = m_nPointViewCount-1;
	}
	if (nPos < 0)
	{
		nPos = 0;
		if (m_nPointBegin > 0)
		{
			setBeginEndPos(1,1);
			//m_nSpaceItems = 0;
			getMouseString(CPoint(m_nMouseX,m_nMouseY));
			m_nCurPos = nPos;
			//onSizeChange();
		}
	}
	else
	{
		if (m_ptType == PTHISK)
		{
			KLINE * pBlock = (KLINE *)m_pKData;		
			if (pBlock && m_nKItemCount > 0)
			{				
				y = m_listPics.at(0)->getChartUnit(_T(""))->getValuePos(pBlock[nPos + m_nPointBegin].close);
			}
		}
		else
			if (m_ptType == PTTREND)
			{
				SStock * pStock = gpData->GetStock(m_strStockCode);
				if (pStock)
				{
					MinUnit * pBlock = (MinUnit *)m_pMinData;
					if (m_nMinItemCount > nPos + m_nPointBegin)
						y = m_listPics.at(0)->getChartUnit(0)->getValuePos(pBlock[nPos + m_nPointBegin].NewPrice);					
				}
			}
			setCursorAway();
			int nW,nS;
			getZoom(m_nZoom,nW,nS);

			if (nW > 0)
				setMousePos(m_pnHoriPoint[nPos] + m_rectDraw.left + nW/2,y);
			else
				setMousePos(m_pnHoriPoint[nPos] + m_rectDraw.left,y);
			m_nCurPos = nPos;
	}
	if (m_bDrawMouseLine == false)
		SetMouseLineOn(true);
	Invalidate();
}

void CPicWnd::goRight()
{
	int x,y;
	int nPos = 0;
	getMousePos(x,y);
	if (m_nCurPos >=0 && m_nCurPos < m_nPointViewCount)
		nPos = m_nCurPos;
	else
		nPos = getXPos(x);

	if (nPos < 0)
		return;

	if (m_bDrawMouseLine == false)
		nPos = 0;
	else
		if (nPos < m_nPointViewCount)
		{
			nPos++;
		}
		if (nPos == m_nPointViewCount)
		{		
			if (m_ptType == PTHISK && (nPos + m_nPointBegin)== m_nKItemCount)
				return;
			m_nPointBegin++;
			getMouseString(CPoint(m_nMouseX,m_nMouseY));
			m_nCurPos = nPos;
			onSizeChange();
		}
		else
		{
			if (m_ptType == PTHISK)
			{
				KLINE * pBlock = (KLINE *)m_pKData;
				if (pBlock && m_nKItemCount)
				{
					y = m_listPics.at(0)->getChartUnit(_T(""))->getValuePos(pBlock[nPos + m_nPointBegin].close);
				}
			}
			else
				if (m_ptType == PTTREND)
				{
					SStock * pStock = gpData->GetStock(m_strStockCode);			
					if (pStock)
					{
						MinUnit * pBlock = (MinUnit *)m_pMinData;
						if (m_nMinItemCount > nPos + m_nPointBegin)
							y = m_listPics.at(0)->getChartUnit(0)->getValuePos(pBlock[nPos + m_nPointBegin].NewPrice);
					}
				}
				setCursorAway();
				int nW,nS;
				getZoom(m_nZoom,nW,nS);
				if (nW > 0)
					setMousePos(m_pnHoriPoint[nPos] + m_rectDraw.left + nW/2,y);
				else
					setMousePos(m_pnHoriPoint[nPos] + m_rectDraw.left,y);
				m_nCurPos = nPos;
				//onSizeChange();
		}
		if (m_bDrawMouseLine == false)
			SetMouseLineOn(true);
		Invalidate();
}

void CPicWnd::setMousePos(int c_x, int c_y)
{
	if (isMouseInCharts(CPoint(c_x,c_y)) != NULL)
	{
		m_nMouseX = c_x;
		m_nMouseY = c_y;

		m_nMousePos = getXPos(m_nMouseX);
		if (this->m_bDrawMouseLine)
		{
			m_nCurPos = getXPos(m_nMouseX);
			if (m_nCurPos == -1)
				setCurPos(m_nCurPos,m_nCurPosTime);
			else
				setCurPos(m_nCurPos,m_nCurPosTime);
		}
		getMouseString(CPoint(m_nMouseX,m_nMouseY));
	}
}

void CPicWnd::getMousePos(int &c_x, int &c_y)
{
	c_x = m_nMouseX;
	c_y = m_nMouseY;
}

int CPicWnd::getXPos(int c_nX)
{
	if (c_nX > m_rectDraw.right || c_nX < m_rectDraw.left)
		return -1;

	if (m_nHoriPointCount == 0)
		return -1;
	if (m_nPointViewCount == 0)
		return -1;

	int nSel;
	for(nSel=1; nSel<m_nHoriPointCount; nSel++)
	{
		if (m_pnHoriPoint[nSel] > (c_nX - m_rectDraw.left))
		{
			nSel--;
			break;
		}
	}

	//if (nSel >= m_nPointViewCount)
	//    nSel = m_nPointViewCount - 1;

	return nSel;
}

void CPicWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_nLockPointEnd = m_nPointBegin + m_nPointViewCount - 1;
	if (true)
	{
		CSize size = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(ID_TWO_WIN));
		CRect rect;
		GetClientRect(rect);
		rect.right -= 4 + m_nRightDis;
		rect.top += 6;
		rect.left = rect.right - size.cx;//12;
		rect.bottom = rect.top + size.cy;//12;		
		m_rectSetWin = rect;

		size = gpSkinManager->GetBmpSize(IDB_LIGHT);
		rect.left = rect.right + 4 + 4;
		rect.right = rect.left + size.cx;		
		//rect.top += 2;
		rect.bottom = rect.top + size.cy;
		if (ROLE_PRICE_ALERT & gpData->m_dwRole)
			m_rectPriceAlert = rect;
		else
			m_rectPriceAlert.SetRect(0,0,0,0);

		size = gpSkinManager->GetBmpSize(IDB_CUTLINE);
		rect.left = rect.right + 1;
		rect.right = rect.left + size.cx;		
		//rect.top += 2;
		rect.bottom = rect.top + size.cy;
		if (ROLE_CUT_LINE & gpData->m_dwRole)
			m_rectCutLine = rect;
		else
			m_rectCutLine.SetRect(0,0,0,0);

		size = gpSkinManager->GetBmpSize(IDB_TRADEAREA);
		rect.left = rect.right + 1;
		rect.right = rect.left + size.cx;
		rect.bottom = rect.top + size.cy;
		if (ROLE_TRADE_AREA & gpData->m_dwRole)
			m_rectTradeArea = rect;
		else
			m_rectTradeArea.SetRect(0,0,0,0);

		size = gpSkinManager->GetBmpSize(IDB_TOOLS);
		rect.left = rect.right + 1;
		rect.right = rect.left + size.cx;
		rect.bottom = rect.top + size.cy;
		m_rectTools = rect;
	}
	m_lockPics.WaitRead();
	resetSize();
	calcChartsMaxMinValue();
	onSizeChange();
	m_lockPics.EndRead();
	Invalidate();
}

void CPicWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值	
	//if (gpData->m_pTopDlg->IsWindowVisible() == false)
	//	SetFocus();
	m_lockPics.WaitRead();
	if (m_bSizeRect && m_nSizeRect >= 0)
	{
		CRect rect;
		m_listPics.at(m_nSizeRect)->getRectFoot(rect);
		DrawSizeLine(rect,point);
		CWnd::OnMouseMove(nFlags, point);
		SetCursor(LoadCursor(NULL,IDC_SIZENS));
		m_lockPics.EndRead();
		return;
	}
	else
	{			
		//if (m_bDrawMouseLine || m_pManualDraw->InDrawing() || m_pManualDraw->InMoving())
		//	Invalidate();
		setMousePos(point.x,point.y);	
		Invalidate();		

		CWnd::OnMouseMove(nFlags, point);
		if (m_ptType != PTHISK)
		{
			m_lockPics.EndRead();
			return;
		}
		if (m_listPics.size() <= 1)
		{
			m_lockPics.EndRead();
			return;
		}

		int nSizeRect = GetSizeCharts(point);
		HCURSOR hcursor1;
		if (nSizeRect >= 0)
		{
			hcursor1 = LoadCursor(NULL,IDC_SIZENS);		
			SetCursor(hcursor1);
		}
		else
		{
			hcursor1 = LoadCursor(NULL,IDC_ARROW);
			SetCursor(hcursor1);
		}
		//SetCursor(hcursor1);
	}
	if (m_ptType == PTHISK && m_listPics.size())
	{
		if (m_pointMoveSet.x > 0 && m_pointMoveSet.y > 0)
		{
			m_pointMoveSeek = point;
			Invalidate();
			m_lockPics.EndRead();
			return;
		}
	}
	m_lockPics.EndRead();
}
/*
void CPicWnd::setKLines(int c_nCount, int *c_pParams)
{
if (c_nCount == 0)
return;
if (c_pParams == NULL)
return;

Charts * pKLine;
pKLine = new Charts();
SStock * pStock = gpData->GetStock(m_strStockCode.GetBuffer());
if (pStock)
pKLine->setTitle(pStock->m_acName);
else
pKLine->setTitle(m_strStockCode);
m_listCharts.push_back(pKLine);

ChartUnit * pLine;
int w,s;
getZoom(m_nZoom,w,s);
KLINE * pBlock = (KLINE *)m_pKData;

if (!pBlock || m_nKItemCount == 0)
return;
pKLine->cleanCharts();

pLine = new ChartUnit();
pLine->setChartUnitType(CUKLine);
pLine->setCell(w,s);
pLine->setLineColor(gpSkinManager->getColor(AIXLINE));
if (m_usCycle == 5)
pLine->setTitle(_T("日线"));
else
if (m_usCycle == 6)
pLine->setTitle(_T("周线"));
else
if (m_usCycle == 7)
pLine->setTitle(_T("月线"));

pLine->setData((char *)pBlock,m_nKItemCount * sizeof(KLINE),false);
pLine->setPrecision(2);
pLine->setMultiplier(1000);
pLine->setRefer(RTMIN,0);
pKLine->addChartUnit(pLine);

for(int n=0; n<c_nCount; n++)
{
if (c_pParams[n] >= m_nKItemCount)
continue;
pLine = new ChartUnit();
pLine->setChartUnitType(CULink);
pLine->setCell(w,s);
pLine->setLineColor(gpSkinManager->getLineColor(n));
CString strInfo;
strInfo.Format(_T("MA%d"),c_pParams[n]);
pLine->setTitle(strInfo);
pLine->setRefer(RTMIN,0);

int *pn = (int *)malloc(m_nKItemCount * sizeof(int));

for(int k=0; k<c_pParams[n]-1 && k<m_nKItemCount; k++)
pn[k] = 0X7FFFFFFF;
for(int k=c_pParams[n]-1; k<m_nKItemCount; k++)
pn[k] = 0;
//
for(int k=c_pParams[n]-1; k<m_nKItemCount; k++)
{
for(int j=k-c_pParams[n]+1; j<=k; j++)
pn[k] += pBlock[j].close;
}
for(int k=c_pParams[n]-1; k<m_nKItemCount; k++)
{
pn[k] /= c_pParams[n];
}
pLine->setData((char *)pn,sizeof(int) * m_nKItemCount,true);
pLine->setPrecision(2);
pLine->setMultiplier(1000);
pKLine->addChartUnit(pLine);
}
}
*/
//void CPicWnd::setKLines(int c_nCount, int *c_pParams,Charts *c_pCharts)
void CPicWnd::setKLines(Charts *c_pCharts)
{
	//if (c_nCount == 0)
	//    return;
	//if (c_pParams == NULL)
	//    return;

	Charts * pKLine;
	if (c_pCharts == NULL)
	{
		pKLine = new Charts();
		m_listPics.push_back(pKLine);
	}
	else
		pKLine = c_pCharts;

	SStock * pStock = gpData->GetStock(m_strStockCode);
	if (pStock)
		pKLine->setTitle(m_strStockCode.Left(6) + _T(" ") + pStock->m_strName);
	else
		pKLine->setTitle(m_strStockCode);
	pKLine->setType(PIC_KLINE,m_usCycle);    

	ChartUnit * pLine;
	int w,s;
	getZoom(m_nZoom,w,s);
	KLINE * pBlock = (KLINE *)m_pKData;

	if (!pBlock || m_nKItemCount <= 0)
		return;
	pKLine->cleanCharts();

	pLine = new ChartUnit();
	pLine->setChartUnitType(CUKLine);
	pLine->setCell(w,s);
	pLine->setLineColor(gpSkinManager->getColor(TITLECOLOR));
	if (m_usCycle == 5)
	{
		if (gpData->m_usWeight == 2)
			pLine->setTitle(_T("日线 前复权"));
		else
			pLine->setTitle(_T("日线 不复权"));
	}
	else
		if (m_usCycle == 6)
		{
			if (gpData->m_usWeight == 2)
				pLine->setTitle(_T("周线 前复权"));
			else
				pLine->setTitle(_T("周线 不复权"));
		}
		else
			if (m_usCycle == 7)
			{
				if (gpData->m_usWeight == 2)
					pLine->setTitle(_T("月线 前复权"));
				else
					pLine->setTitle(_T("月线 不复权"));
			}
			else
				if (m_usCycle == HISKMINDATA)
					pLine->setTitle(_T("1分钟线"));
				else
					if (m_usCycle == HISKMIN5DATA)
						pLine->setTitle(_T("5分钟线"));
					else
						if (m_usCycle == HISKMIN15DATA)
							pLine->setTitle(_T("15分钟线"));
						else
							if (m_usCycle == HISKMIN30DATA)
								pLine->setTitle(_T("30分钟线"));
							else
								if (m_usCycle == HISKMIN60DATA)
									pLine->setTitle(_T("60分钟线"));

	pLine->SetPreClose(pStock->m_unPrevClose);

	pLine->setData((char *)pBlock,m_nKItemCount * sizeof(KLINE),false);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	pLine->setRefer(RTMIN,0);
	pKLine->addChartUnit(pLine);

	return;
}

void CPicWnd::setVolLines(int c_nCount, int *c_pParams)
{
	if (c_nCount == 0)
		return;
	if (c_pParams == NULL)
		return;
	Charts *pVol;
	pVol = new Charts();
	m_listPics.push_back(pVol);

	ChartUnit * pLine;
	int w,s;
	getZoom(m_nZoom,w,s);
	KLINE * pBlock = (KLINE *)m_pKData;
	if (!pBlock || m_nKItemCount <= 0)
		return;    

	unsigned int unMax = 0;
	for(int n=0; n<m_nKItemCount; n++)
	{
		if (unMax < pBlock[n].volume)
			unMax = pBlock[n].volume;
	}
	int nToDiv = 1;
	if (unMax > 10000*10)
		nToDiv =10;

	if (unMax > 10000*100)
		nToDiv = 100;

	if (unMax > 10000*1000)
		nToDiv = 1000;

	if (unMax > 10000*10000)
		nToDiv = 10000;
	pLine = new ChartUnit();
	pLine->setChartUnitType(CUVOL);
	pLine->setCell(w,s);
	pLine->setLineColor(gpSkinManager->getColor(TITLECOLOR));
	pLine->setTitle(_T("VOLUME"));
	pLine->setData((char *)pBlock,m_nKItemCount * sizeof(KLINE),false);
	pLine->setPrecision(0);
	pLine->setDiv(nToDiv);
	pLine->setRefer(RTZERO,0);
	pLine->setMultiplier(1);

	pVol->addChartUnit(pLine);

	for(int n=0; n<c_nCount; n++)
	{
		pLine = new ChartUnit();
		pLine->setChartUnitType(CULink);
		pLine->setCell(w,s);
		pLine->setLineColor(n);
		CString strInfo;
		strInfo.Format(_T("MA%d"),c_pParams[n]);
		pLine->setTitle(strInfo);
		pLine->setRefer(RTZERO,0);

		int *pn = (int *)malloc(sizeof(int) *m_nKItemCount);

		for(int k=0; k<c_pParams[n]-1 && k<m_nKItemCount; k++)
			pn[k] = 0X7FFFFFFF;
		for(int k=c_pParams[n]-1; k<m_nKItemCount; k++)
			pn[k] = 0;
		//
		for(int k=c_pParams[n]-1; k<m_nKItemCount; k++)
		{
			for(int j=k-c_pParams[n]+1; j<=k; j++)
				pn[k] += pBlock[j].volume/nToDiv;
		}
		for(int k=c_pParams[n]-1; k<m_nKItemCount; k++)
		{
			pn[k] /= c_pParams[n];
		}
		pLine->setData((char *)pn,sizeof(int) * m_nKItemCount,true);
		pLine->setPrecision(0);
		pLine->setMultiplier(1);
		pVol->addChartUnit(pLine);
	}
}

void CPicWnd::setTrendLine(Charts * c_pCharts)
{
	Charts * pKLine;
	if (c_pCharts == NULL)
	{
		pKLine = new Charts();
		m_listPics.push_back(pKLine);
	}
	else
		pKLine = c_pCharts;
	SStock * pStock = gpData->GetStock(m_strStockCode);

	if (pStock)
		pKLine->setTitle(m_strStockCode.Left(6) + _T(" ") + pStock->m_strName);
	else
		pKLine->setTitle(m_strStockCode);

	pKLine->setType(PIC_TREND,m_usCycle);


	ChartUnit * pLine;
	int w,s;
	getZoom(m_nZoom,w,s);
	MinUnit * pBlock = (MinUnit *)m_pMinData;
	//if (m_nMinItemCount == 0)
	//	return;

	if (!pBlock)
		return;
	pKLine->cleanCharts();

	pLine = new ChartUnit();
	pLine->setChartUnitType(CUTrend);
	if (m_strStockCode == "000001.SH" ||  m_strStockCode == "399001.SZ" || gpData->IsStock(m_strStockCode))
		pLine->setIsIndex(false);//!gpData->IsStock(m_strStockCode));
	else
		pLine->setIsIndex(true);
	pLine->setCell(w,s);
	pLine->setLineColor(gpSkinManager->getColor(AIXTEXT));
	pLine->setTitle(_T("分时"));
	if (pStock->m_sQuote.jrkp == 0 || m_nMinItemCount == 0)
	{
		m_nMinItemCount = 242;
		for(int n=0; n<m_nMinItemCount; n++)
		{
			pBlock[n].AvgPrice = pStock->m_unPrevClose;
			pBlock[n].MaxPrice = pStock->m_unPrevClose;
			pBlock[n].MinPrice = pStock->m_unPrevClose;
			pBlock[n].OpenPrice = pStock->m_unPrevClose;
			pBlock[n].Volume = 0;
			pBlock[n].NewPrice = pStock->m_unPrevClose;
		}
	}
	pLine->setData((char *)pBlock,m_nMinItemCount * sizeof(MinUnit),false);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);    
	pKLine->addChartUnit(pLine);
	pLine->setRefer(RTMID,pStock->m_unPrevClose);
}

void CPicWnd::setTrendVol(Charts * c_pCharts)
{
	SStock * pStock = gpData->GetStock(m_strStockCode);
	if (pStock == NULL)
		return;

	Charts *pVol;
	pVol = new Charts();	
	if (c_pCharts == NULL)
	{
		pVol = new Charts();
		m_listPics.push_back(pVol);
	}
	else
		pVol = c_pCharts;

	ChartUnit * pLine;
	int w,s;
	getZoom(m_nZoom,w,s);
	MinUnit * pBlock = m_pMinData;

	if (!pBlock)
		return;    

	pLine = new ChartUnit();
	pLine->setIsIndex(!gpData->IsStock(pStock->m_sQuote.szStockCode));
	pLine->setChartUnitType(CUTrendVol);
	pLine->setCell(w,s);
	pLine->setLineColor(gpSkinManager->getColor(AIXTEXT));    
	pLine->setTitle(_T(""));
	pLine->setData((char *)pBlock,sizeof(MinUnit) * m_nMinItemCount,false);
	pLine->setPrecision(0);
	pLine->setMultiplier(1);
	pLine->setRefer(RTZERO,0);
	pVol->addChartUnit(pLine);
}

void CPicWnd::createPic()
{
	if(m_ptType == PTTREND)
	{		
		//m_nSpaceItems = 0;
		createMinPic();
	}
	else
	{
		m_nLockPointEnd = -1;		
		//m_nSpaceItems = 10;
		createHiskPic();
	}
}

void CPicWnd::createHiskPic()
{
	KLINE * pBlock = (KLINE *)m_pKData;
	//清除现有的图形
	for(int n=0; n<m_listPics.size(); n++)
	{
		m_listPics.at(n)->cleanCharts();
		m_listPics.at(n)->m_usCycle = m_usCycle;
		m_listPics.at(n)->m_strStockCode = m_strStockCode;
	}
	int nChartsCount = m_listPics.size();
	for (int n=nChartsCount; n<3; n++)
	{
		Charts * pCharts = new Charts();
		pCharts->m_usCycle = m_usCycle;
		m_listPics.push_back(pCharts);
		pCharts->m_strStockCode = m_strStockCode;
	}
	//清除结束
	if (pBlock == NULL)
		return;
	if (m_nKItemCount == 0)
		return;

	if (m_nKItemCount > 1)
		gpKDetail->SetKLINE(&pBlock[m_nKItemCount-1],pBlock[m_nKItemCount-2].close,m_usCycle);
	else
		gpKDetail->SetKLINE(&pBlock[m_nKItemCount-1],0,m_usCycle);

	setKLines(m_listPics.at(0));

	CString strTech;
	bool bIsStock = gpData->IsStock(m_strStockCode);
	for(int n=0; n<m_listPics.size(); n++)
	{
		strTech = CTechManager::getInstance()->getTechByIndex(n,bIsStock,m_usCycle,m_strStockCode);

		if (!strTech.IsEmpty())
		{
			ChangeTech(m_listPics.at(n),strTech);
		}
		else
		{
			//MessageBox(_T("技术指标为空！"),_T("提示"));
		}
	}

	m_listPics.at(0)->setAixType(m_atCur);
}
/*
void CPicWnd::createHiskPic()
{
KLINE * pBlock = (KLINE *)m_pKData;
//清除现有的图形
while(m_listCharts.size())
{
m_listCharts.at(0)->cleanCharts();

delete *(m_listCharts.begin());
m_listCharts.erase(m_listCharts.begin());
}   
//清除结束
if (pBlock == NULL)
return;
if (m_nKItemCount == 0)
return;

if (m_nKItemCount > 1)
gpData->m_pKDetail->SetKLINE(&pBlock[m_nKItemCount-1],pBlock[m_nKItemCount-2].close);
else
gpData->m_pKDetail->SetKLINE(&pBlock[m_nKItemCount-1],0);
int *pn = new int[10];
//pn[0] = 3;
//pn[1] = 5;
//pn[2] = 8;
//pn[3] = 10;
pn[0] = 12;
//pn[5] = 35;
//pn[6] = 40;
//pn[7] = 45;
//pn[8] = 50;
pn[1] = 60;
if (m_usCycle == 7)
setKLines(2,pn);
else
if (m_usCycle == 6)
setKLines(2,pn);
else
setKLines(2,pn);
if (m_bHISKEMA)
addEMA(2,pn);
if (m_bHISKBOLL)
{
pn[0] = 26;
addBOLL(1,pn);
}
pn[0] = 12;
pn[2] = 12;
pn[3] = 24;	
setVolLines(1,pn);
delete [] pn;
resetSize();
onSizeChange();
}
*/
void CPicWnd::createMinPic()
{
	SStock * pStock = gpData->GetStock(m_strStockCode);
	if (pStock == NULL)
		return;
	InitMinData();

	if (pStock->m_nMinItemCount > 0)
	{
		SetMinData(pStock->m_pMinData,pStock->m_nMinItemCount*sizeof(MinUnit));
	}		

	//清除现有的图形

	while(m_listPics.size() > 2)
	{
		m_listPics.back()->cleanCharts();
		delete m_listPics.back();
		m_listPics.pop_back();
	}
	//清除结束

	for(int n=0; n<m_listPics.size(); n++)
	{
		m_listPics.at(n)->cleanCharts();
		m_listPics.at(n)->m_usCycle = m_usCycle;
		m_listPics.at(n)->m_strStockCode = m_strStockCode;
	}

	int nChartsCount = m_listPics.size();
	for (int n=nChartsCount; n<2; n++)
	{
		Charts * pCharts = new Charts();
		pCharts->m_usCycle = m_usCycle;
		pCharts->m_strStockCode = m_strStockCode;
		m_listPics.push_back(pCharts);
	}

	setTrendLine(m_listPics.at(0));
	setTrendVol(m_listPics.at(1));
	resetZoom();
	resetSize();
	onSizeChange();
	Invalidate();
}

void CPicWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bSizeRect = false;
	m_nSizeRect = -1;

	m_lockPics.WaitRead();
	int nInRect = -1;
	for(int n=0; n<m_listPics.size(); n++)
	{
		if (m_listPics.at(n)->isPointIn(point))
		{
			nInRect = n;
			break;
		}
	}
	if (nInRect != 0)
	{
		if (m_listPics.size() > 2)
		{
			HideOrShowCharts(nInRect);
			CWnd::OnLButtonDblClk(nFlags, point);
			m_lockPics.EndRead();
			return;
		}
	}
	SetMouseLineOn(!m_bDrawMouseLine);
	CWnd::OnLButtonDblClk(nFlags, point);

	if (m_bDrawMouseLine == false)
	{
		if (m_listPics.size() > 0)
		{
			CRect rect;
			m_listPics.at(0)->getRectBody(rect);
			setMousePos(rect.right-1,rect.bottom-10);
		}
		this->m_nCurPos = -1;
		this->setCurPos(m_nCurPos,m_nCurPosTime);
	}
	Invalidate();
	m_lockPics.EndRead();
	SetFocus();
	BringWindowToTop();	
}

void CPicWnd::drawMouseLine(CDC * c_pDC)
{
	CRect rect;

	if (m_nMouseX == -1 && m_nMouseY == -1)
		return;
	CPen pen(PS_SOLID,1,gpSkinManager->getColor(AIXLINE));
	CPen * pOldPen = c_pDC->SelectObject(&pen);	
	CBrush br(RGB(0,0,255));
	CBrush * pOldBrush = c_pDC->SelectObject(&br);
	int oldMode = c_pDC->SetBkMode(TRANSPARENT);
	COLORREF clOld = c_pDC->SetTextColor(RGB(255,255,255));
	CRect r;
	for(int n=0; n<m_listPics.size(); n++)
	{
		m_listPics.at(n)->getRectBody(rect);
		if (rect.PtInRect(CPoint(m_nMouseX,m_nMouseY)))
		{
			if (m_bDrawMouseLine)
			{
				c_pDC->MoveTo(rect.left,m_nMouseY);
				c_pDC->LineTo(rect.right,m_nMouseY);
				c_pDC->MoveTo(m_nMouseX,rect.bottom);
				c_pDC->LineTo(m_nMouseX,rect.top);
			}
			CSize size = c_pDC->GetTextExtent(m_strMouseY);
			r = CRect(rect.right,m_nMouseY-size.cy/2 - 2,rect.right + size.cx,m_nMouseY+size.cy/2 + 2);			
			c_pDC->Rectangle(r);
			c_pDC->DrawText(m_strMouseY,CRect(rect.right,m_nMouseY-size.cy/2,rect.right + m_nRightDis,m_nMouseY+size.cy/2),DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		}
		else
		{
			if (m_bDrawMouseLine)
			{
				c_pDC->MoveTo(m_nMouseX,rect.top);
				c_pDC->LineTo(m_nMouseX,rect.bottom);
			}
			CSize size = c_pDC->GetTextExtent(m_strMouseX);
			if (n == m_listPics.size() - 1)
			{
				CRect rectFoot;
				m_listPics.at(n)->getRectFoot(rectFoot);
				r = CRect(m_nMouseX,rectFoot.bottom,m_nMouseX+size.cx,rectFoot.bottom+size.cy + 2);				
				c_pDC->Rectangle(r);
				c_pDC->DrawText(m_strMouseX,CRect(m_nMouseX,rectFoot.bottom+2,m_nMouseX+size.cx,rectFoot.bottom+size.cy),DT_LEFT|DT_VCENTER|DT_SINGLELINE);
			}
		}
	}
	c_pDC->SetTextColor(clOld);
	c_pDC->SetBkMode(oldMode);
	c_pDC->SelectObject(pOldPen);
	c_pDC->SelectObject(pOldBrush);
}

void CPicWnd::drawMoveRect(CDC * c_pDC)
{
	CRect rect;

	if (m_pointMoveSet.x == 0 && m_pointMoveSet.y == 0)
		return;
	CPen pen(PS_SOLID,1,gpSkinManager->getColor(AIXLINE));
	CPen * pOldPen = c_pDC->SelectObject(&pen);					

	c_pDC->MoveTo(m_pointMoveSet.x,m_pointMoveSet.y);
	c_pDC->LineTo(m_pointMoveSet.x,m_pointMoveSeek.y);
	c_pDC->LineTo(m_pointMoveSeek.x,m_pointMoveSeek.y);
	c_pDC->LineTo(m_pointMoveSeek.x,m_pointMoveSet.y);
	c_pDC->LineTo(m_pointMoveSet.x,m_pointMoveSet.y);

	c_pDC->SelectObject(pOldPen);
}

void CPicWnd::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	this->m_bSizeRect = false;
	this->m_nSizeRect = -1;
	SStock * pStock = gpData->GetStock(m_strStockCode);
	if (pStock == NULL)
		return;
	bool bIsIndex = false;
	if (gpData->IsStock(m_strStockCode))
		bIsIndex = false;
	else
		bIsIndex = true;

	CCustomMenu pop;
	pop.LoadMenu(IDR_MENUPIC);
	//mn.ChangeMenuItem(&mn,TRUE);
	CMenu * pPop;
	pPop = pop.GetSubMenu(0);

	//CMenu * pMenu=new CMenu(),*pPop;
	//pMenu->LoadMenu(IDR_MENUPIC);
	//pPop = pMenu->GetSubMenu(0);	

	bool bZbsm = false;
	CPoint pt;
	GetCursorPos(&pt);
	pt.x = m_nMouseX;
	pt.y = m_nMouseY;
	pt = point;
	CString strTitle = GetPointInChartsTitle(pt);
	if(m_ptType != PTTREND
		&& (strTitle == PIC_BOLL
		|| strTitle == PIC_HISK_VOL
		|| strTitle == PIC_MACD
		|| strTitle == PIC_RSI
		|| strTitle == PIC_KDJ))
	{
		bZbsm = true;
	}
	else
	{
		pPop->RemoveMenu(ID_TECH_DESC,MF_BYCOMMAND);
	}

	bool bQxdj = true;
	if (!bQxdj && !bZbsm)
	{
		pPop->RemoveMenu(8,MF_BYPOSITION);
	}
	if (bIsIndex)
	{
		pPop->RemoveMenu(ID_ADD_STOCK,MF_BYCOMMAND);
		pPop->RemoveMenu(6,MF_BYPOSITION);
	}
	if (m_ptType == PTTREND)
	{
		pPop->RemoveMenu(5,MF_BYPOSITION);
		pPop->RemoveMenu(4,MF_BYPOSITION);
		pPop->RemoveMenu(3,MF_BYPOSITION);
		pPop->RemoveMenu(1,MF_BYPOSITION);
	}
	if (m_listPics.at(0)->m_atType == AIXNORMAL)
	{
		pPop->GetSubMenu(1)->CheckMenuItem(ID_AIX_NORMAL,MF_CHECKED);
		pPop->GetSubMenu(1)->CheckMenuItem(ID_AIX_LG,MF_UNCHECKED);
	}
	else
		if (m_listPics.at(0)->m_atType == AIXLG)
		{
			pPop->GetSubMenu(1)->CheckMenuItem(ID_AIX_NORMAL,MF_UNCHECKED);
			pPop->GetSubMenu(1)->CheckMenuItem(ID_AIX_LG,MF_CHECKED);
		}
		if (gpData->m_usWeight == 2)
		{
			if (pPop->GetSubMenu(4))
			{
				pPop->GetSubMenu(4)->CheckMenuItem(ID_WEIGHT_FRONT,MF_CHECKED);
				pPop->GetSubMenu(4)->CheckMenuItem(ID_WEIGHT_NONE,MF_UNCHECKED);
			}
		}
		else
		{
			if (pPop->GetSubMenu(4))
			{
				pPop->GetSubMenu(4)->CheckMenuItem(ID_WEIGHT_FRONT,MF_UNCHECKED);
				pPop->GetSubMenu(4)->CheckMenuItem(ID_WEIGHT_NONE,MF_CHECKED);
			}
		}
		pop.ChangeMenuItem(&pop,TRUE);
		pPop->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
		//pMenu->DestroyMenu();
		//delete pMenu;

}

void CPicWnd::OnMonk()
{
	// TODO: 在此添加命令处理程序代码
	m_lockPics.WaitWrite();
	changePic(PTHISK,7);
	m_lockPics.EndWrite();
}

void CPicWnd::OnWeekk()
{
	// TODO: 在此添加命令处理程序代码
	m_lockPics.WaitWrite();
	changePic(PTHISK,6);
	m_lockPics.EndWrite();
}

void CPicWnd::OnDayk()
{
	// TODO: 在此添加命令处理程序代码
	m_lockPics.WaitWrite();
	changePic(PTHISK,5);
	m_lockPics.EndWrite();
}

void CPicWnd::OnRealmin()
{
	// TODO: 在此添加命令处理程序代码
	m_lockPics.WaitWrite();
	changePic(PTTREND,0);
	m_lockPics.EndWrite();
}

void CPicWnd::changePic(PicType c_ptType,unsigned short c_usCycle)
{
	m_nLockPointEnd = -1;
	m_ptType = c_ptType;
	m_usCycle = c_usCycle;
	m_nPointViewCount = 0;
	m_nPointBegin = 0;
	getPicData();
	createFutureKLine();
	createPic();

	resetZoom();
	resetSize();
	onSizeChange();
	Invalidate();
}

void CPicWnd::resetPic()
{
	SStock * pStock = gpData->GetStock(m_strStockCode);
	if (pStock == NULL)
		return;

	if (m_ptType == PTTREND)
	{
		if (m_listPics.size() < 2)
			return;
		if (pStock->m_nMinItemCount > 0)
		{
			SetMinData(pStock->m_pMinData,pStock->m_nMinItemCount*sizeof(MinUnit));
		}		

		m_listPics.at(0)->removeTech(true);
		setTrendLine(m_listPics.at(0));
		m_listPics.at(1)->removeTech(true);
		setTrendVol(m_listPics.at(1));
	}
	else
	{
		KLINE * pBlock = (KLINE *)m_pKData;
		//清除现有的图形
		CString strMainTech;
		strMainTech = m_listPics.at(0)->m_strTechType;
		for(int n=0; n<m_listPics.size(); n++)
		{
			m_listPics.at(n)->cleanCharts();
			m_listPics.at(n)->m_usCycle = m_usCycle;
		}
		int nChartsCount = m_listPics.size();
		for (int n=nChartsCount; n<3; n++)
		{
			Charts * pCharts = new Charts();
			pCharts->m_usCycle = m_usCycle;
			m_listPics.push_back(pCharts);
		}
		//清除结束
		if (pBlock == NULL)
			return;
		if (m_nKItemCount == 0)
			return;

		setKLines(m_listPics.at(0));
		m_listPics.at(0)->setMainTech(strMainTech,pBlock,m_nKItemCount);

		CString strTech;
		for(int n=1; n<m_listPics.size(); n++)
		{				
			strTech = m_listPics.at(n)->m_strType;
			if (!strTech.IsEmpty())
			{
				ChangeTech(m_listPics.at(n),strTech);
			}		
		}
		m_listPics.at(0)->setAixType(m_atCur);
		for(int n=0; n<m_listPics.size(); n++)
		{
			m_listPics.at(n)->setRects(m_listPics.at(n)->m_rectBody,m_listPics.at(n)->m_rectHead,m_listPics.at(n)->m_rectFoot);
		}
	}
}

void CPicWnd::getPicData()
{
	char acBuf[1024];
	int nRet;
	USES_CONVERSION;
	if (m_ptType == PTTREND)
	{
		nRet = gpData->MakeRealMinReq(acBuf,(char *)W2A(m_strStockCode.GetBuffer()),1);
		m_strStockCode.ReleaseBuffer();
		if (nRet > 0)
		{
			if (gpCommSocket)
			{
				gpCommSocket->SendData(acBuf,nRet,true);
			}
			
		}
			
	}
	else if (m_ptType == PTHISK && (m_usCycle == HISKMINDATA || m_usCycle == HISKMIN5DATA || m_usCycle == HISKMIN15DATA || m_usCycle == HISKMIN30DATA || m_usCycle == HISKMIN60DATA))	
	{//分钟线
		nRet = gpData->GetMinHisKData((char *)W2A(m_strStockCode.GetBuffer()),m_usCycle,0,m_pKData,m_nKDataMaxLen);
		m_strStockCode.ReleaseBuffer();
		if (nRet > 0)
		{
			m_nKItemCount = nRet / sizeof(KLINE);
		}
		else
			m_nKItemCount = 0;

		m_nMinFreshBegin = m_nKItemCount;
		FormatMinKData();//格式化K线
		/*
		for(int n=0; n<m_nKItemCount; n++)//去除交易额0
		{
		if (((KLINE *)m_pKData)[n].amount == 0)
		((KLINE *)m_pKData)[n].amount = ((KLINE *)m_pKData)[n].volume * ((KLINE *)m_pKData)[n].low / 100000;
		}*/
	}
	else if (m_ptType == PTHISK && (m_usCycle == HISKDAYDATA || m_usCycle == HISKWEEKDATA || m_usCycle == HISKMONTHDATA))
	{//日线
		DWORD d1,d2;
		d1 = GetTickCount();
		nRet = gpData->GetHisKData((char *)W2A(m_strStockCode.GetBuffer()),m_usCycle,gpData->m_usWeight,m_pKData,m_nKDataMaxLen,gpData->m_nWorkDay);
		m_strStockCode.ReleaseBuffer();

		if (nRet > 0)
		{
			m_nKItemCount = nRet / sizeof(KLINE);
		}
		else
		{
			m_nKItemCount = 0;

		}
		d2 = GetTickCount();
#ifdef _DEBUG
		FILE *f;
		f = fopen("c:\\rec.his","ab");
		if (f)
		{
			char acBuf[256];
			sprintf(acBuf,"%s %d\n",(char *)W2A(m_strStockCode.GetBuffer()),d2-d1);
			m_strStockCode.ReleaseBuffer();
			fseek(f,0,SEEK_END);
			fwrite(acBuf,1,strlen(acBuf),f);
			fclose(f);
		}
#endif
	}
}

void CPicWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_lockPics.WaitRead();
	KeyOperate(nChar);
	m_lockPics.EndRead();
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);		
}

void CPicWnd::KeyOperate(UINT nChar)
{
	if(nChar == VK_ESCAPE)
	{
		if (m_bDrawMouseLine)
		{
			SetMouseLineOn(false);
			Invalidate();
		}
		else
		{
			::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,SHOW_STOCKS,0);
		}
		return;
	}
	else
		if(nChar == VK_UP)
		{
			if (m_ptType == PTHISK)
			{
				if (m_nLockPointEnd <= 0)
					m_nLockPointEnd = m_nPointBegin + m_nPointViewCount - 1;
				goUp();
			}
		}
		else
			if (nChar == VK_DOWN)
			{
				if (m_ptType == PTHISK)
				{
					if (m_nLockPointEnd <= 0)
						m_nLockPointEnd = m_nPointBegin + m_nPointViewCount - 1;
					goDown();
				}
			}
			else
				if (nChar == VK_LEFT)
				{
					short stL = GetAsyncKeyState(VK_LCONTROL);
					short stR = GetAsyncKeyState(VK_RCONTROL);
					if (stL || stR)
					{
						ResetFutrueItem(0);
					}
					else
					{
						m_nLockPointEnd = -1;			
						goLeft();
					}
				}
				else
					if (nChar == VK_RIGHT)
					{
						short stL = GetAsyncKeyState(VK_LCONTROL);
						short stR = GetAsyncKeyState(VK_RCONTROL);
						if (stL || stR)
						{
							ResetFutrueItem(1);
						}
						else
						{
							m_nLockPointEnd = -1;
							goRight();
						}
					}
					else
						if (nChar == VK_RETURN || nChar == VK_F5)
						{
							if (m_ptType == PTTREND)
								changePic(PTHISK,5);
							else
							{
								if (gpContainer && gpContainer->IsWindowVisible())
									gpContainer->OnBnClickedBtnClose();
								changePic(PTTREND,0);
							}
						}
						else
							if (nChar == VK_NEXT)
							{
								//ResetSpaceItem(1);
								m_nLockPointEnd = -1;
								SStock * pStock = gpData->GetStock(m_strStockCode);
								::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,1,DWORD_PTR(pStock));
							}
							else
								if (nChar == VK_PRIOR)
								{
									//ResetSpaceItem(0);

									m_nLockPointEnd = -1;
									SStock * pStock = gpData->GetStock(m_strStockCode);
									::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,-1,DWORD_PTR(pStock));
								}
								else
									if (nChar == VK_F3)
									{
										SStock * pStock = gpData->GetStock("000001.SH");		
										//pStock = gpData->GetNextStock(pStock,-1);		
										if (pStock)
											::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,0,DWORD_PTR(pStock));
									}
									else
										if (nChar == VK_F4)
										{
											SStock * pStock = gpData->GetStock("399001.SZ");		
											if (pStock)
												::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,0,DWORD_PTR(pStock));
										}
										else
											if (nChar == VK_F8)
											{
												if (m_ptType == PTHISK)
												{
													if (m_usCycle == 5)
														this->changePic(PTHISK,6);
													else
														if (m_usCycle == 6)
															this->changePic(PTHISK,7);
														else
															if (m_usCycle == 7)
																changePic(PTHISK,HISKMINDATA);
															else
																if (m_usCycle == HISKMINDATA)
																	changePic(PTHISK,HISKMIN5DATA);
																else
																	if (m_usCycle == HISKMIN5DATA)
																		changePic(PTHISK,HISKMIN15DATA);
																	else
																		if (m_usCycle == HISKMIN15DATA)
																			changePic(PTHISK,HISKMIN30DATA);
																		else
																			if (m_usCycle == HISKMIN30DATA)
																				changePic(PTHISK,HISKMIN60DATA);
																			else
																				if (m_usCycle == HISKMIN60DATA)
																					changePic(PTHISK,5);


												}
											}
											else
												if (nChar == VK_F6)
												{
													::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,SHOW_STOCKS,61);
												}
												else
													if (nChar == VK_F10)
													{
														SStock *pStock = gpData->GetStock(m_strStockCode);
														if (pStock)
															::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,SHOW_F10,DWORD_PTR(pStock));
													}
													else
														if (nChar == VK_F12)
														{
															::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,SHOW_TRADEWND,0);
														}
														else
															if (nChar == VK_TAB)
															{
																if (m_ptType == PTHISK)
																{
																	if (m_listPics.size() > 0)
																	{
																		m_bDrawMainTechLine = !m_bDrawMainTechLine;
																		Invalidate();
																	}
																}
															}
															SetFocus();
}

void CPicWnd::setCurPos(int c_nPos,int c_nPosTime)
{
	if (m_listPics.size() == 0)
		return;

	m_nCurPos = c_nPos;
	m_nCurPosTime = m_listPics.at(0)->getTimeByPos(c_nPos + m_nPointBegin);
	for(int n=0; n<m_listPics.size(); n++)
		m_listPics.at(n)->setCurPos(c_nPos,m_nCurPosTime);	
}

void CPicWnd::drawDetail(CDC * c_pDC)
{
	SStock * pStock = gpData->GetStock(m_strStockCode);
	if (pStock == NULL)
		return;

	if(PTTREND == m_ptType)
	{
		if (m_nMinItemCount == 0)
			return;

		MinUnit * pBlock = (MinUnit *)m_pMinData;

		if (!pBlock)
			return;
		if (m_nPointBegin + m_nCurPos >= 0 && m_nPointBegin + m_nCurPos < m_nMinItemCount)
			drawMinUnitDetail(c_pDC,&(pBlock[m_nPointBegin + m_nCurPos]),pStock->m_unPrevClose,!gpData->IsStock(pStock->m_sQuote.szStockCode));
	}
	else
	{
		KLINE * pBlock = (KLINE *)m_pKData;

		if (!pBlock || m_nKItemCount <= 0)
			return;
		if (gpKDetail && m_nPointBegin + m_nCurPos-1 >= 0)
			gpKDetail->SetKLINE(&(pBlock[m_nPointBegin + m_nCurPos]),pBlock[m_nPointBegin + m_nCurPos-1].close,m_usCycle);
		else
			gpKDetail->SetKLINE(&(pBlock[m_nPointBegin + m_nCurPos]),0,m_usCycle);
		/*
		if (m_nPointBegin + m_nCurPos >= 0 && m_nPointBegin + m_nCurPos < m_nKItemCount)
		drawKLineDetail(c_pDC,&(pBlock[m_nPointBegin + m_nCurPos]));*/
	}
}

void CPicWnd::drawMinUnitDetail(CDC * c_pDC,MinUnit * c_pUnit,int c_nPreClose,bool c_bIndex)
{
	CRect r;
	int nHeight = gpSkinManager->GetFontHeight(gpSkinManager->GetGraphFont());
	nHeight += 2;

	r = m_rectAix;
	if (c_bIndex)
		r.bottom = r.top + nHeight * 12;
	else
		r.bottom = r.top + nHeight * 14;
	r.left -= m_nLeftDis - 4;
	//r.left -=58;
	r.right = r.left + m_nLeftDis - 4;
	CBrush br(gpSkinManager->getColor(BKCOLOR));
	CBrush * brOld = c_pDC->SelectObject(&br);
	c_pDC->Rectangle(r);
	c_pDC->SelectObject(brOld);

	r = m_rectAix;
	r.bottom = r.top + nHeight;
	r.left -=m_nLeftDis - 4;
	r.right = r.left + m_nLeftDis - 4;
	CSize size;
	CString strText;
	strText.Format(_T("时间:"));
	c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
	c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.bottom += nHeight;
	r.top += nHeight;

	strText.Format(_T("%02d:%02d"),c_pUnit->Time/60,c_pUnit->Time%60);
	c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
	c_pDC->DrawText(strText,r,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.bottom += nHeight;
	r.top += nHeight;	

	strText.Format(_T("价格:"));
	c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
	c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.bottom += nHeight;
	r.top += nHeight;

	strText.Format(_T("%.2f"),float(c_pUnit->NewPrice)/1000);
	if (c_pUnit->NewPrice > c_nPreClose)
		c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
	else
		if (c_pUnit->NewPrice < c_nPreClose)
			c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
		else
			c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
	c_pDC->DrawText(strText,r,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.bottom += nHeight;
	r.top += nHeight;

	strText.Format(_T("均价:"));
	c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
	c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.bottom += nHeight;
	r.top += nHeight;

	strText.Format(_T("%.2f"),float(c_pUnit->AvgPrice)/1000);
	if (c_pUnit->AvgPrice> c_nPreClose)
		c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
	else
		if (c_pUnit->AvgPrice < c_nPreClose)
			c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
		else
			c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
	c_pDC->DrawText(strText,r,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.bottom += nHeight;
	r.top += nHeight;

	strText.Format(_T("涨跌:"));
	c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
	c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.bottom += nHeight;
	r.top += nHeight;	

	strText.Format(_T("%.2f"),float((int)c_pUnit->NewPrice - c_nPreClose)/1000);
	if (c_pUnit->NewPrice> c_nPreClose)
		c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
	else
		if (c_pUnit->NewPrice < c_nPreClose)
			c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
		else
			c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
	c_pDC->DrawText(strText,r,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.bottom += nHeight;
	r.top += nHeight;


	strText.Format(_T("涨跌幅:"));
	c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
	c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.bottom += nHeight;
	r.top += nHeight;

	if (c_nPreClose > 0)
		strText.Format(_T("%.2f%%"),float(int(c_pUnit->NewPrice) - c_nPreClose) * 100/c_nPreClose);
	else
		strText = "0";
	if (c_pUnit->NewPrice> c_nPreClose)
		c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
	else
		if (c_pUnit->NewPrice < c_nPreClose)
			c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
		else
			c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
	c_pDC->DrawText(strText,r,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.bottom += nHeight;
	r.top += nHeight;

	strText.Format(_T("成交量"));
	c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
	c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.bottom += nHeight;
	r.top += nHeight;

	strText.Format(_T("%d"),c_pUnit->Volume);
	c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
	c_pDC->DrawText(strText,r,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.bottom += nHeight;
	r.top += nHeight;

	if (c_bIndex == false)
	{
		strText.Format(_T("成交额:"));
		c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
		c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		size = c_pDC->GetTextExtent(strText);
		r.bottom += nHeight;
		r.top += nHeight;

		strText.Format(_T("%.2f万"),float(c_pUnit->Volume * c_pUnit->AvgPrice) / 10000);
		c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
		c_pDC->DrawText(strText,r,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
		size = c_pDC->GetTextExtent(strText);
		r.bottom += nHeight;
		r.top += nHeight;
	}
}

void CPicWnd::drawKLineDetail(CDC * c_pDC,KLINE * c_pKLine)
{
	SStock * pStock = gpData->GetStock(m_strStockCode);

	CRect r;
	m_listPics.at(0)->getRectHead(r);

	r.top = r.bottom - 16;	
	r.left += 4;

	CString strText;
	CSize size;

	strText.Format(_T("%d"),c_pKLine->day);
	c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
	c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.left += size.cx + 4;

	if (c_pKLine->open < c_pKLine->close)
		c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
	else
		if (c_pKLine->open > c_pKLine->close)
			c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
		else
			c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
	strText.Format(_T("开:%.2f"),float(c_pKLine->open)/1000);
	c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.left += size.cx + 4;

	strText.Format(_T("收:%.2f"),float(c_pKLine->close)/1000);
	c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.left += size.cx + 4;

	strText.Format(_T("高:%.2f"),float(c_pKLine->high)/1000);
	c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.left += size.cx + 4;

	strText.Format(_T("低:%.2f"),float(c_pKLine->low)/1000);
	c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.left += size.cx + 4;

	strText.Format(_T("量:%d"),c_pKLine->volume);
	c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
	c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.left += size.cx + 4;

	strText.Format(_T("额:%d"),c_pKLine->amount);
	c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
	c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	size = c_pDC->GetTextExtent(strText);
	r.left += size.cx + 4;

	if (pStock->m_dLtg > 0)
	{
		strText.Format(_T("换:%.2f%%"),float(c_pKLine->volume) * 100 * 100/pStock->m_dLtg);
		c_pDC->SetTextColor(gpSkinManager->getColor(AIXTEXT));
		c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		size = c_pDC->GetTextExtent(strText);
		r.left += size.cx + 4;
	}
}

void CPicWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetFocus();
	m_lockPics.WaitRead();
	int nSizeRect = GetSizeCharts(point);
	if (nSizeRect >= 0)
	{
		m_bSizeRect = true;
		m_nSizeRect = nSizeRect;
		m_pointSizeBegin = point;
		m_pointSizeLast = CPoint(0,0);
		CRect rect;
		m_listPics.at(0)->getRectFoot(rect);
		DrawSizeLine(rect,point);
	}
	else
	{		
		Charts * pCharts = setChartsSelected(point);
		if (pCharts)
		{						
			m_pointMoveSet = point;
			m_pointMoveSeek = point;
		}
	}
	m_lockPics.EndRead();
	CWnd::OnLButtonDown(nFlags, point);
}

Charts * CPicWnd::GetChartsByUnitType(ChartUnitType c_type)
{
	for(int n=0; n<m_listPics.size(); n++)
	{
		if (m_listPics.at(n)->getChartUnitByType(c_type))
			return m_listPics.at(n);
	}
	return NULL;
}

Charts * CPicWnd::GetChartsByTitle(CString c_strTitle)
{
	for(int n=0; n<m_listPics.size(); n++)
	{
		if (m_listPics.at(n)->getTitle() == c_strTitle)
			return m_listPics.at(n);
	}
	return NULL;
}

ChartUnitType CPicWnd::GetChartsUnitType()
{
	return m_listPics.at(0)->getChartUnit(0)->getUnitType();
}
void CPicWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (IsWindowVisible() == false)
		return;

	if (m_bInGetReport == false && nIDEvent == 101 && m_strStockCode.GetLength() > 0)
	{
		m_bInGetReport = true;
		if (gpData->m_nWorkState == 1 || gpData->m_nWorkState == 2 || gpData->m_nWorkState == 3 || gpData->m_nWorkState == 4 )
		{			
			GetReport(false);
		}
		m_bInGetReport = false;
	}
	CWnd::OnTimer(nIDEvent);
}

int CPicWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_menu.Attach(GetMenu()->GetSafeHmenu());
	m_menu.ChangeMenuItem(&m_menu,TRUE);

	SetTimer(101,4 * 1000,NULL);
	return 0;
}

void CPicWnd::OnAddStock()
{
	// TODO: 在此添加命令处理程序代码	
	if (m_strStockCode.IsEmpty())
		return;

	SStock * pStock = gpData->GetStock(m_strStockCode);
	/*
	pStock = gpData->GetStock("600036.sh");
	if (pStock)
	addStockHisK(pStock);
	return;*/
	if (pStock)
	{		
		int nCode;
		char acBuf[7];
		strncpy(acBuf,pStock->m_sQuote.szStockCode,6);
		acBuf[6] = 0;
		nCode = atoi(acBuf);
		::PostMessage(gpData->m_hwndMain,WM_ADD_STOCK_TO_GROUP,0,nCode);
	}

}

void CPicWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == VK_RETURN)
	{
		m_lockPics.WaitWrite();
		if (m_ptType == PTTREND)
			changePic(PTHISK,5);
		else
			changePic(PTTREND,0);
		m_lockPics.EndWrite();
	}

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CPicWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

BOOL CPicWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (wParam == 201)
	{
		/*
		int nRet = ((CPics *)this->GetParent())->SetWins();
		if (nRet == 0)
		m_pSetWin->SetBtnBMP(gpSkinManager->GetBitmap(ID_TWO_WIN),gpSkinManager->GetBitmap(ID_ONE_WIN));
		else
		m_pSetWin->SetBtnBMP(gpSkinManager->GetBitmap(ID_ONE_WIN),gpSkinManager->GetBitmap(ID_TWO_WIN));*/
	}

	return CWnd::OnCommand(wParam, lParam);
}

int CPicWnd::GetSizeCharts(CPoint c_point)
{
	if (m_listPics.size() <= 1)
	{
		return -1;
	}
	/*
	for(int n=0; n<m_listPics.size(); n++)
	{
	if (m_listPics.at(n)->m_bVisible == false)//隐藏的图形
	return -1;
	}*/
	for(int n=0; n<m_listPics.size()-1; n++)
	{
		if (m_listPics.at(n)->m_bVisible == false)
			continue;
		CRect rect;
		m_listPics.at(n)->getRectFoot(rect);
		if (c_point.y > rect.bottom - 4 && c_point.y < rect.bottom + 4)
		{
			return n;			
		}
	}
	return -1;
}
void CPicWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_lockPics.WaitRead();
	if (m_bSizeRect && m_nSizeRect >=0 )
	{
		SizeRects(point);
		m_bSizeRect = false;
		m_nSizeRect = -1;
		m_lockPics.EndRead();
		Invalidate();
		CWnd::OnLButtonUp(nFlags, point);
		return;
	}
	m_pointSizeLast = CPoint(0,0);
	m_pointSizeBegin = CPoint(0,0);
	m_bSizeRect = false;
	m_nSizeRect = -1;

	m_lockPics.EndRead();
	if (m_rectSetWin.PtInRect(point))
	{
		((CPics *)this->GetParent())->SetWins();
	}
	if (m_rectTradeArea.PtInRect(point) && ROLE_TRADE_AREA & gpData->m_dwRole)
	{
		::PostMessage(gpData->m_hwndMain,WM_COMMAND,ID_TRADE_AREA,0);
	}

	if (m_rectCutLine.PtInRect(point) && ROLE_CUT_LINE & gpData->m_dwRole)
	{
		::PostMessage(gpData->m_hwndMain,WM_COMMAND,ID_CUT_ALERT,0);
	}

	if (m_rectTools.PtInRect(point))
	{
		::PostMessage(gpData->m_hwndMain,WM_COMMAND,ID_DRAW_TOOLS,0);
	}

	if (m_pointMoveSet.x > 0 && m_pointMoveSet.y > 0 && m_pointMoveSeek.x > m_pointMoveSet.x+128 && m_pointMoveSeek.y > m_pointMoveSet.y+128)
	{
		goUp(getXPos(m_pointMoveSet.x) + m_nPointBegin);
	}
	else
		if (m_pointMoveSet.x > 0 && m_pointMoveSet.y > 0 && m_pointMoveSeek.x < m_pointMoveSet.x-128 && m_pointMoveSeek.y < m_pointMoveSet.y-128)
		{
			goDown();
		}
		m_pointMoveSet.SetPoint(0,0);
		m_pointMoveSeek.SetPoint(0,0);
		Invalidate();
		CWnd::OnLButtonUp(nFlags, point);
}


void CPicWnd::DrawSizeLine(CRect c_rect,CPoint c_point)
{
	CPen pen(PS_SOLID,1,RGB(0,0,0));	
	CDC * pDC = GetDC();
	CPen *pPenOld = pDC->SelectObject(&pen);
	//int nOld = pDC->SetROP2(R2_XORPEN);
	//int nOld = pDC->SetROP2(R2_MASKPENNOT);
	int nOld = pDC->SetROP2(R2_NOT);

	if (m_pointSizeLast.x != 0 && m_pointSizeLast.y != 0)
	{
		pDC->MoveTo(c_rect.left,m_pointSizeLast.y);
		pDC->LineTo(c_rect.right,m_pointSizeLast.y);
	}
	pDC->MoveTo(c_rect.left,c_point.y);
	pDC->LineTo(c_rect.right,c_point.y);
	pDC->SetROP2(nOld);
	pDC->SelectObject(pPenOld);
	this->ReleaseDC(pDC);
	m_pointSizeLast = c_point;
}

void CPicWnd::SizeRects(CPoint c_point)
{
	if (m_nSizeRect < 0 || m_nSizeRect > (m_listPics.size()-2))
		return;

	int nChange = c_point.y - m_pointSizeBegin.y;
	CRect rectHead1,rectBody1,rectFoot1;
	m_listPics.at(m_nSizeRect)->getRectBody(rectBody1);
	m_listPics.at(m_nSizeRect)->getRectHead(rectHead1);
	m_listPics.at(m_nSizeRect)->getRectFoot(rectFoot1);
	rectBody1.bottom += nChange;
	rectFoot1.top += nChange;
	rectFoot1.bottom += nChange;	

	CRect rectHead2,rectBody2,rectFoot2,rectHead3,rectBody3,rectFoot3;;
	if (m_listPics.at(m_nSizeRect+1)->m_bVisible == false)
	{
		m_listPics.at(m_nSizeRect+1)->getRectBody(rectBody2);
		m_listPics.at(m_nSizeRect+1)->getRectHead(rectHead2);
		m_listPics.at(m_nSizeRect+1)->getRectFoot(rectFoot2);

		if (m_nSizeRect == 0)
		{
			m_listPics.at(m_nSizeRect+2)->getRectBody(rectBody3);
			m_listPics.at(m_nSizeRect+2)->getRectHead(rectHead3);
			m_listPics.at(m_nSizeRect+2)->getRectFoot(rectFoot3);
		}
		rectHead2.top += nChange;
		rectHead2.bottom += nChange;	
		rectBody2.top += nChange;

		rectHead3.top += nChange;
		rectHead3.bottom += nChange;	
		rectBody3.top += nChange;

	}
	else
	{
		m_listPics.at(m_nSizeRect+1)->getRectBody(rectBody2);
		m_listPics.at(m_nSizeRect+1)->getRectHead(rectHead2);
		m_listPics.at(m_nSizeRect+1)->getRectFoot(rectFoot2);
		rectHead2.top += nChange;
		rectHead2.bottom += nChange;	
		rectBody2.top += nChange;
		if (m_nSizeRect == 0 && m_listPics.size() > 2)
		{
			m_listPics.at(m_nSizeRect+2)->getRectBody(rectBody3);
			m_listPics.at(m_nSizeRect+2)->getRectHead(rectHead3);
			m_listPics.at(m_nSizeRect+2)->getRectFoot(rectFoot3);

			if (rectHead3.top - rectHead2.top < 40)
				return;
		}
	}

	if (rectBody1.bottom  - rectBody1.top < 40
		|| rectBody2.bottom  - rectBody2.top < 20)
		return;

	m_listPics.at(m_nSizeRect)->setRects(rectBody1,rectHead1,rectFoot1);
	if (m_listPics.at(m_nSizeRect+1)->m_bVisible == false)
	{
		m_listPics.at(m_nSizeRect+1)->setRects(rectBody2,rectHead2,rectFoot2);
		if (m_nSizeRect == 0)
			m_listPics.at(m_nSizeRect+2)->setRects(rectBody3,rectHead3,rectFoot3);
	}
	else
	{
		m_listPics.at(m_nSizeRect+1)->setRects(rectBody2,rectHead2,rectFoot2);
	}

	//onSizeChange();
}

void CPicWnd::InitMinData()
{
	m_nMinItemCount = 0;
	if (m_pMinData)
	{
		//初始化分时
		for(int n=0; n<121; n++)
		{
			m_pMinData[n].Time = 570 + n;
			m_pMinData[n].NewPrice = 0X7FFFFFFF;
		}
		for(int n=0; n<121; n++)
		{
			m_pMinData[121 + n].Time = 780 + n;
			m_pMinData[121 + n].NewPrice = 0X7FFFFFFF;
		}
	}

}

void CPicWnd::SetMinData(char * c_pBuf,int c_nLen)
{
	int nItemCount = c_nLen/sizeof(MinUnit);
	MinUnit * pSrc = (MinUnit *)c_pBuf;
	MinUnit * pMin = m_pMinData;
	int k=0;
	for(int n=0; n<nItemCount; n++)
	{
		while(true)
		{			
			if (pMin[k].Time == pSrc[n].Time)
			{
				pMin[k].AvgPrice = pSrc[n].AvgPrice;
				pMin[k].MaxPrice = pSrc[n].MaxPrice;
				pMin[k].MinPrice = pSrc[n].MinPrice;
				pMin[k].NewPrice = pSrc[n].NewPrice;
				pMin[k].OpenPrice = pSrc[n].OpenPrice;
				pMin[k].Volume = pSrc[n].Volume;
				k++;
				break;
			}
			else
			{
				if (k > 242)
					break;
				pMin[k].AvgPrice = pSrc[n].AvgPrice;
				pMin[k].MaxPrice = pSrc[n].MaxPrice;
				pMin[k].MinPrice = pSrc[n].MinPrice;
				pMin[k].NewPrice = pSrc[n].NewPrice;
				pMin[k].OpenPrice = pSrc[n].OpenPrice;
				pMin[k].Volume = 0;
				k++;
			}
		}
		if (k > 242)
			break;
	}
	m_nMinItemCount = k;
}

bool CPicWnd::RemoveTechPic(CString c_strName)
{
	bool bRet = false;
	Charts * pCharts = NULL;
	pCharts = GetChartsByTitle(c_strName);
	if (pCharts)//已经存在了
		return true;
	//bRet = true;
	if(pCharts == NULL)
		pCharts = GetChartsByTitle(PIC_MACD);
	if(pCharts == NULL)
		pCharts = GetChartsByTitle(PIC_KDJ);
	if(pCharts == NULL)
		pCharts = GetChartsByTitle(PIC_RSI);
	if(pCharts == NULL)
		pCharts = GetChartsByTitle(PIC_BOLL);

	if (pCharts)
	{
		std::vector<Charts *>::iterator iter;
		for(iter=m_listPics.begin(); iter!=m_listPics.end(); iter++)		
		{
			if ((*iter) == pCharts)
			{
				(*iter)->cleanCharts();
				delete (*iter);
				m_listPics.erase(iter);
				//resetSize();
				//onSizeChange();
				break;
			}
		}   
	}
	return bRet;
}


void CPicWnd::DoMenuAction(CString c_strTech)
{
	bool bIndex = false;
	bool bMainPic = false;

	if (c_strTech == PIC_EMA || c_strTech == PIC_MA || c_strTech == PIC_MMA || c_strTech == PIC_TDMA || c_strTech == PIC_BOLL)
		bMainPic = true;

	m_lockPics.WaitWrite();
	if (IsExistsTech(c_strTech) == false)
	{
		int nIndex = m_listPics.size() - 1;
		if (nIndex > 0)
		{
			if (bMainPic)
				ChangeTech(m_listPics.at(0),c_strTech);
			else
			{
				for(int n=1; n<m_listPics.size(); n++)
				{
					if (m_listPics.at(n)->getSelected())
					{
						nIndex = n;
						break;
					}
				}
				ChangeTech(m_listPics.at(nIndex),c_strTech);
			}
		}				
		SaveCurTechSet();
	}
	resetZoom();
	resetSize();
	setBeginEndPos(0,0);
	m_lockPics.EndWrite();
}

void CPicWnd::OnTechDesc()
{
	// TODO: 在此添加命令处理程序代码
	CDlgTechDesc dlg;
	CPoint pt;
	//GetCursorPos(&pt);
	//pt.x = m_nMouseX;
	//pt.y = m_nMouseY;
	CString strTitle = GetPointInChartsTitle(pt);
	dlg.SetTitle(strTitle);
	dlg.DoModal();
}

CString CPicWnd::GetPointInChartsTitle(CPoint c_point)
{
	for(int n=0; n<m_listPics.size(); n++)
	{
		CRect rect;		
		m_listPics.at(n)->getRectBody(rect);
		if (m_listPics.at(n)->getSelected())
			//if (rect.PtInRect(c_point))
		{
			if (n == 0)
				return m_listPics.at(n)->m_strTechType;
			else
				return m_listPics.at(n)->m_strTitle;
		}
	}
	return _T("");
}

void CPicWnd::FreshData()
{
	SStock * pStock = gpData->GetStock(m_strStockCode);
	if (pStock == NULL)
		return;

	m_lockPics.WaitWrite();
	if (m_ptType == PTTREND)
	{
		resetPic();
		resetZoom();
		resetSize();
		resetViewTrendPoints();
		setCurPos(m_nCurPos,m_nCurPosTime);
		Invalidate();
		m_lockPics.EndWrite();
		return;
	}

	//处理K线图
	if (pStock->m_sQuote.jrkp == 0)//没有开盘不处理
	{
		m_lockPics.EndWrite();
		return;
	}
	/*
	if (gpData->m_nDateOpen == gpData->m_nDateClose)//已经收盘了
	{
	m_lockPics.EndWrite();
	return;
	}
	*/
	if (m_ptType == PTHISK && (m_usCycle == HISKMINDATA || m_usCycle == HISKMIN5DATA || m_usCycle == HISKMIN15DATA || m_usCycle == HISKMIN30DATA || m_usCycle == HISKMIN60DATA))
	{
		int nOldKCount = m_nKItemCount;
		int nOldPointEnd = m_nPointBegin + m_nPointViewCount - 1;
		int nOldCurPos = m_nCurPos;
		FormatMinKData();
		if (nOldKCount < m_nKItemCount)
		{
			//changePic(PTHISK,m_usCycle);

			resetPic();
			resetZoom();
			//resetSize();
			resetViewHiskPoints();		
			m_nCurPos = -1;
			setCurPos(m_nCurPos,m_nCurPosTime);
			Invalidate();
		}
		else
		{
			Invalidate();
		}
		m_lockPics.EndWrite();
		return;
	}
	USES_CONVERSION;
	//取当前K线的最后日期
	KLINE * pK = (KLINE *)m_pKData;

	int nOldCurPos = m_nCurPos;
	int nOldCurPosTime = m_nCurPosTime;
	if (pStock->m_sQuote.cjsl>0 && (m_nKItemCount==0 || pK[m_nKItemCount-1].day < gpData->m_nWorkDay || pK[m_nKItemCount-1].day > gpData->m_nWorkDay))//最后日期小于开盘日期，大于开盘日期出错了
	{		
		int nReadLen = gpData->GetHisKData((char *)W2A(m_strStockCode.GetBuffer()),m_usCycle,gpData->m_usWeight,m_pKData,m_nKDataMaxLen,gpData->m_nWorkDay);
		if (nReadLen > 0)
		{
			m_nKItemCount = nReadLen / sizeof(KLINE);
		}
		else
			m_nKItemCount = 0;		
		m_strStockCode.ReleaseBuffer();

		//changePic(PTHISK,m_usCycle);
		m_nLockPointEnd = -1;		
		m_nPointViewCount = 0;
		m_nPointBegin = 0;
		resetPic();
		resetZoom();
		//resetSize();
		onSizeChange();	
		Invalidate();

		m_lockPics.EndWrite();
		return;
	}

	int nIndexDiv = 1;
	if (m_usCycle == 6 || m_usCycle == 7)
		if ((m_usCycle == 5 || m_usCycle == 6 || m_usCycle == 7) && pStock->m_sQuote.cjsl>0 )//日线

		{
			pK[m_nKItemCount-1].close = pStock->m_sQuote.zjjg;
			if(m_usCycle == 5)
				pK[m_nKItemCount-1].open = pStock->m_sQuote.jrkp;
			else
				if (pK[m_nKItemCount-1].open == 0)
					pK[m_nKItemCount-1].open = pStock->m_sQuote.jrkp;

			if (m_usCycle == 5)
			{
				pK[m_nKItemCount-1].amount = pStock->m_sQuote.cjje;
				pK[m_nKItemCount-1].volume = pStock->m_sQuote.cjsl;
			}
			else
			{
				char acFile[32];
				sprintf(acFile,"%s.%d",pStock->m_sQuote.szStockCode,m_usCycle);
				KLINE kTail;
				int nRead = gpData->GetFromFileTail(acFile,(char *)&kTail,sizeof(KLINE));
				if (nRead == sizeof(KLINE))
				{			
					pK[m_nKItemCount-1].amount = pStock->m_sQuote.cjje  / nIndexDiv + kTail.amount;
					pK[m_nKItemCount-1].volume = pStock->m_sQuote.cjsl  / nIndexDiv + kTail.volume;
				}
			}
			if (pStock->m_sQuote.zgjg > pK[m_nKItemCount-1].high)
				pK[m_nKItemCount-1].high = pStock->m_sQuote.zgjg;
			if (pK[m_nKItemCount-1].low == 0)
				pK[m_nKItemCount-1].low = pStock->m_sQuote.zdjg;
			if (pStock->m_sQuote.zdjg < pK[m_nKItemCount-1].low)
				pK[m_nKItemCount-1].low = pStock->m_sQuote.zdjg;
			int nn = m_nCurPos;
			resetPic();
			resetZoom();
			//resetSize();		
			setChartsViewPoints();
			//设置回位置
			m_nCurPos = nOldCurPos;
			setCurPos(nOldCurPos,nOldCurPosTime);
			Invalidate();				
		}
		m_lockPics.EndWrite();
}

/*
void CPicWnd::FreshData()
{
SStock * pStock = gpData->GetStock(m_strStockCode);
if (pStock == NULL)
return;

if (m_ptType == PTTREND)
{
createPic();
return;
}
//处理K线图
if (pStock->m_sQuote.jrkp == 0)//没有开盘不处理
return;

//取当前K线的最后日期
KLINE * pK = (KLINE *)m_pKData;
if (m_nKItemCount==0 || pK[m_nKItemCount-1].day < gpData->m_nDateOpen || pK[m_nKItemCount-1].day > gpData->m_nDateOpen)//最后日期小于开盘日期，大于开盘日期出错了
{
//if ((m_usCycle == 6 && gpData->IsSameWeek(pK[m_nKItemCount-1].day,gpData->m_nDateOpen))
//	|| (m_usCycle == 7 && gpData->IsSameMonth(pK[m_nKItemCount-1].day,gpData->m_nDateOpen)))
//{
//}
//else
{
int nReadLen = gpData->GetHisKData(m_strStockCode.GetBuffer(),m_usCycle,m_pKData,m_nKDataMaxLen);
if (nReadLen > 0)
{
m_nKItemCount = nReadLen / sizeof(KLINE);
}
else
m_nKItemCount = 0;

m_strStockCode.ReleaseBuffer();
createPic();//重新建图
return;
}
}
if (gpData->m_nDateOpen == gpData->m_nDateClose)//已经收盘了
return;

if (m_usCycle == 5 || m_usCycle == 6 || m_usCycle == 7)//日线
{
pK[m_nKItemCount-1].close = pStock->m_sQuote.zjjg;
pK[m_nKItemCount-1].open = pStock->m_sQuote.jrkp;
if (m_usCycle == 5)
{
pK[m_nKItemCount-1].amount = pStock->m_sQuote.cjje;
pK[m_nKItemCount-1].volume = pStock->m_sQuote.cjsl;
}
else
{
//pK[m_nKItemCount-1].amount += pStock->m_cjjeChg;
//pK[m_nKItemCount-1].volume += pStock->m_cjslChg;
}
if (pStock->m_sQuote.zjjg > pK[m_nKItemCount-1].high)
pK[m_nKItemCount-1].high = pStock->m_sQuote.zjjg;
if (pK[m_nKItemCount-1].low == 0)
pK[m_nKItemCount-1].low = pStock->m_sQuote.zdjg;
if (pStock->m_sQuote.zdjg < pK[m_nKItemCount-1].low)
pK[m_nKItemCount-1].low = pStock->m_sQuote.zdjg;
updateKLines();
Invalidate();		
//createPic();
}
}
*/
void CPicWnd::GetReport(bool c_bWait)
{
	int nLen;
	char acReq[1024];
	if (gpData->m_nWorkDay == 0)
	{
		nLen = gpData->MakeLineTestReq(acReq);	
		if (gpCommSocket->SendData(acReq,nLen,true) <= 0)
			return;
	}
	nLen = gpData->MakePicReq(acReq,&m_nStockId,1);
	if (nLen > 0 && gpCommSocket && gpCommSocket->m_socket != INVALID_SOCKET)
		if (gpCommSocket->SendData(acReq,nLen,c_bWait) <= 0 && c_bWait == false)
		{
			gpCommSocket->Disconnect();
			::PostMessage(gpData->m_hwndMain,WM_CONNECT_SUCCESS,0,0);
		}
}

void CPicWnd::calcChartsMaxMinValue()
{
	for(int n=0; n<m_listPics.size(); n++)
	{		
		m_listPics.at(n)->calcMaxMinValue();
	}
}

void CPicWnd::setMACD(int c_nCount, int *c_pParams)
{
	if (c_nCount == 0)
		return;
	if (c_pParams == NULL)
		return;

	SStock * pStock = gpData->GetStock(m_strStockCode);

	ChartUnit * pLine;
	int w,s;
	getZoom(m_nZoom,w,s);
	KLINE * pBlock = (KLINE *)m_pKData;

	if (!pBlock || m_nKItemCount <= 0)
		return;

	Charts * pKLine;
	pKLine = new Charts();
	pKLine->setTitle(PIC_MACD);
	pKLine->setType(PIC_MACD,m_usCycle);
	m_listPics.push_back(pKLine);

	pKLine->cleanCharts();

	float *pfData = new float[m_nKItemCount];
	for(int n=0; n<m_nKItemCount; n++)
		pfData[n] = pBlock[n].close;

	int nShort,nLong,nMid;
	nShort = c_pParams[0];
	nLong = c_pParams[1];
	nMid = c_pParams[2];

	float *pfRetShort = new float[m_nKItemCount];
	float *pfRetLong = new float[m_nKItemCount];
	float *pfDiff = new float[m_nKItemCount];
	float *pfRetDea = new float[m_nKItemCount];
	float *pfMacd = new float[m_nKItemCount];

	Calc_Ema(pfRetShort,pfData,m_nKItemCount,nShort);//快线
	for(int n=0; n<m_nKItemCount; n++)
		pfData[n] = pBlock[n].close;

	Calc_Ema(pfRetLong,pfData,m_nKItemCount,nLong);//慢线
	for(int n=0; n<m_nKItemCount; n++)
	{
		if (InValid(pfRetShort[n]) || InValid(pfRetLong[n]))
		{
			SetInValid(pfDiff[n]);
		}
		else
			pfDiff[n] = pfRetShort[n] - pfRetLong[n];
	}
	Calc_Ema(pfRetDea,pfDiff,m_nKItemCount,nMid);//中间

	for(int n=0; n<m_nKItemCount; n++)
	{
		if (InValid(pfDiff[n]) || InValid(pfRetDea[n]))
		{
			SetInValid(pfMacd[n]);
		}
		else
			pfMacd[n] = 2 *(pfDiff[n] - pfRetDea[n]);
	}

	int * pnMacd = (int *)malloc(m_nKItemCount * sizeof(int));
	int * pnDea = (int *)malloc(m_nKItemCount * sizeof(int));
	int * pnDiff = (int *)malloc(m_nKItemCount * sizeof(int));
	for(int n=0; n<m_nKItemCount; n++)
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
	delete [] pfDiff;
	delete [] pfRetDea;
	delete [] pfRetShort;
	delete [] pfRetLong;
	delete [] pfMacd;

	pLine = new ChartUnit();
	pLine->setChartUnitType(CUTickLine);
	pLine->setCell(w,s);
	pLine->setLineColor(0);
	CString strInfo;
	strInfo.Format(_T("MACD(%d,%d,%d)"),nShort,nLong,nMid);
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMID,0);
	pLine->setData((char *)pnMacd,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(100*1000);
	pKLine->addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	pLine->setLineColor(0);

	strInfo = "DIF";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMID,0);
	pLine->setData((char *)pnDiff,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(100*1000);
	pKLine->addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	pLine->setLineColor(1);

	strInfo= "DEA";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMID,0);
	pLine->setData((char *)pnDea,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(100*1000);
	pKLine->addChartUnit(pLine);

}

void CPicWnd::OnMacd()
{
	// TODO: 在此添加命令处理程序代码
	m_lockPics.WaitWrite();
	bool bSelf = RemoveTechPic(PIC_MACD);
	if (bSelf)
	{
		m_lockPics.EndWrite();
		return;
	}
	int *pn = new int[3];
	pn[0] = 12;
	pn[1] = 26;
	pn[2] = 9;
	setMACD(3,pn);
	delete [] pn;
	resetSize();
	//calcChartsMaxMinValue();
	setBeginEndPos(0,0);
	//onSizeChange();
	Invalidate();
	m_lockPics.EndWrite();
}

void CPicWnd::OnKdj()
{
	// TODO: 在此添加命令处理程序代码
	m_lockPics.WaitWrite();
	bool bSelf = RemoveTechPic(PIC_KDJ);
	if (bSelf)
	{
		m_lockPics.EndWrite();
		return;
	}
	int *pn = new int[3];
	pn[0] = 9;
	pn[1] = 3;
	pn[2] = 3;
	setKDJ(3,pn);
	delete [] pn;
	resetSize();
	setBeginEndPos(0,0);
	//onSizeChange();
	m_lockPics.EndWrite();
}

void CPicWnd::OnRsi()
{
	// TODO: 在此添加命令处理程序代码
	m_lockPics.WaitWrite();
	bool bSelf = RemoveTechPic(PIC_RSI);
	if (bSelf)
	{
		m_lockPics.EndWrite();
		return;
	}
	int *pn = new int[3];
	pn[0] = 6;
	pn[1] = 12;
	pn[2] = 24;
	setRSI(3,pn);
	delete [] pn;
	resetSize();
	setBeginEndPos(0,0);
	//calcChartsMaxMinValue();
	//onSizeChange();
	m_lockPics.EndWrite();
	Invalidate();
}

void CPicWnd::OnBoll()
{
	// TODO: 在此添加命令处理程序代码
	if (m_listPics.at(0)->getSpecialUnit(STBOLL))
	{
		m_listPics.at(0)->removeSpecialUnit(STBOLL);
		OnAddEMA();
	}
	else
		if (m_listPics.at(0)->getSpecialUnit(STEMA))
		{
			m_listPics.at(0)->removeSpecialUnit(STEMA);
			OnAddBoll();
		}
		else
		{
			OnAddBoll();
		}
		resetLineColor();
		return;
		/*
		int *pn = new int[3];
		pn[0] = 20;
		setBOLL(1,pn);
		setCurTech(PIC_BOLL);
		delete [] pn;
		resetSize();
		calcChartsMaxMinValue();
		onSizeChange();
		Invalidate();*/
}

void CPicWnd::OnAddBoll()
{
	// TODO: 在此添加命令处理程序代码
	int *pn = new int[3];
	pn[0] = 26;
	addBOLL(1,pn);	
	delete [] pn;
	resetSize();
	//calcChartsMaxMinValue();
	setBeginEndPos(0,0);
	//onSizeChange();
	Invalidate();
}

void CPicWnd::OnAddEMA()
{
	// TODO: 在此添加命令处理程序代码
	int *pn = new int[3];
	pn[0] = 12;
	pn[1] = 60;
	addEMA(2,pn);	
	delete [] pn;
	resetSize();
	calcChartsMaxMinValue();
	//onSizeChange();
	setBeginEndPos(0,0);
	resetLineColor();
	Invalidate();
}

void CPicWnd::setKDJ(int c_nCount, int *c_pParams)
{
	if (c_nCount == 0)
		return;
	if (c_pParams == NULL)
		return;

	SStock * pStock = gpData->GetStock(m_strStockCode);

	ChartUnit * pLine;
	int w,s;
	getZoom(m_nZoom,w,s);
	KLINE * pBlock = (KLINE *)m_pKData;

	if (!pBlock || m_nKItemCount <= 0)
		return;

	Charts * pKLine;	
	pKLine = new Charts();
	pKLine->setTitle(PIC_KDJ);
	pKLine->setType(PIC_KDJ,m_usCycle);
	m_listPics.push_back(pKLine);


	int N,M1,M2;
	N = c_pParams[0];
	M1 = c_pParams[1];
	M2 = c_pParams[2];

	float *pfLow = new float[m_nKItemCount];
	float *pfHigh = new float[m_nKItemCount];
	float *pfRSV = new float[m_nKItemCount];
	float *pfK = new float[m_nKItemCount];
	float *pfD = new float[m_nKItemCount];
	float *pfJ = new float[m_nKItemCount];
	float *pfData = new float[m_nKItemCount];
	for(int n=0; n<m_nKItemCount; n++)
		pfData[n] = pBlock[n].low;

	Calc_LLV(pfLow,pfData,m_nKItemCount,N);//取N日最低
	for(int n=0; n<m_nKItemCount; n++)
		pfData[n] = pBlock[n].high;
	Calc_HHV(pfHigh,pfData,m_nKItemCount,N);//取N日最高

	for(int n=0; n<m_nKItemCount; n++)//HHV-LLV
	{
		pfHigh[n] -= pfLow[n];
	}

	for(int n=0; n<m_nKItemCount; n++)//CLOSE-LLV
	{
		pfLow[n] = float(pBlock[n].close) - pfLow[n];
	}

	for(int n=0; n<m_nKItemCount; n++)//RSV
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
	Calc_Sma(pfK,pfRSV,m_nKItemCount,M1,1);
	Calc_Sma(pfD,pfK,m_nKItemCount,M2,1);

	for(int n=0; n<m_nKItemCount; n++)
	{
		if (InValid(pfK[n]) || InValid(pfD[n]))
		{
			SetInValid(pfJ[n]);
		}
		else
			pfJ[n] = 3 * pfK[n] - 2 * pfD[n];
	}

	int * pnK = (int *)malloc(m_nKItemCount * sizeof(int));
	int * pnD = (int *)malloc(m_nKItemCount * sizeof(int));
	int * pnJ = (int *)malloc(m_nKItemCount * sizeof(int));
	for(int n=0; n<m_nKItemCount; n++)
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
	pLine->setCell(w,s);
	pLine->setLineColor(0);
	CString strInfo;
	strInfo.Format(_T("KDJ(%d,%d,%d) K"),N,M1,M2);
	pLine->setTitle(strInfo);
	pLine->setRefer(RTZERO,0);
	pLine->setData((char *)pnK,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	pKLine->addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	pLine->setLineColor(1);

	strInfo = "D";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTZERO,0);
	pLine->setData((char *)pnD,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	pKLine->addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	pLine->setLineColor(2);

	strInfo= "J";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTZERO,0);
	pLine->setData((char *)pnJ,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	pKLine->addChartUnit(pLine);

}

void CPicWnd::setRSI(int c_nCount, int *c_pParams)
{
	if (c_nCount == 0)
		return;
	if (c_pParams == NULL)
		return;

	SStock * pStock = gpData->GetStock(m_strStockCode);


	ChartUnit * pLine;
	int w,s;
	getZoom(m_nZoom,w,s);
	KLINE * pBlock = (KLINE *)m_pKData;

	if (!pBlock || m_nKItemCount <= 0)
		return;

	Charts * pKLine;
	pKLine = new Charts();
	pKLine->setTitle(PIC_RSI);
	pKLine->setType(PIC_RSI,m_usCycle);
	m_listPics.push_back(pKLine);

	pKLine->cleanCharts();


	int N1,N2,N3;
	N1 = c_pParams[0];
	N2 = c_pParams[1];
	N3 = c_pParams[2];

	float *pfMax = new float[m_nKItemCount];
	float *pfAbs = new float[m_nKItemCount];
	float *pfRSI1 = new float[m_nKItemCount];
	float *pfRSI2 = new float[m_nKItemCount];
	float *pfRSI3 = new float[m_nKItemCount];
	float *pfRetMax = new float[m_nKItemCount];
	float *pfRetAbs = new float[m_nKItemCount];

	SetInValid(pfMax[0]);
	SetInValid(pfAbs[0]);

	for(int n=1; n<m_nKItemCount; n++)
	{
		pfMax[n] = float(pBlock[n].close) - float(pBlock[n-1].close);
		if (pfMax[n] < 0)
			pfMax[n] = 0;
		pfAbs[n] = abs(float(pBlock[n].close) - float(pBlock[n-1].close));
	}
	Calc_Sma(pfRetMax,pfMax,m_nKItemCount,N1,1);
	Calc_Sma(pfRetAbs,pfAbs,m_nKItemCount,N1,1);
	for(int n=0; n<m_nKItemCount; n++)
	{
		if (InValid(pfRetMax[n]) || InValid(pfRetAbs[n]))
		{
			SetInValid(pfRSI1[n]);
		}
		else
			pfRSI1[n] = pfRetMax[n] / pfRetAbs[n] * 100;
	}

	Calc_Sma(pfRetMax,pfMax,m_nKItemCount,N2,1);
	Calc_Sma(pfRetAbs,pfAbs,m_nKItemCount,N2,1);
	for(int n=0; n<m_nKItemCount; n++)
	{
		if (InValid(pfRetMax[n]) || InValid(pfRetAbs[n]))
		{
			SetInValid(pfRSI1[n]);
		}
		else
			pfRSI2[n] = pfRetMax[n] / pfRetAbs[n] * 100;
	}

	Calc_Sma(pfRetMax,pfMax,m_nKItemCount,N3,1);
	Calc_Sma(pfRetAbs,pfAbs,m_nKItemCount,N3,1);
	for(int n=0; n<m_nKItemCount; n++)
	{
		if (InValid(pfRetMax[n]) || InValid(pfRetAbs[n]))
		{
			SetInValid(pfRSI3[n]);
		}
		else
			pfRSI3[n] = pfRetMax[n] / pfRetAbs[n] * 100;
	}

	int * pnRSI1 = (int *)malloc(m_nKItemCount * sizeof(int));
	int * pnRSI2 = (int *)malloc(m_nKItemCount * sizeof(int));
	int * pnRSI3 = (int *)malloc(m_nKItemCount * sizeof(int));
	for(int n=0; n<m_nKItemCount; n++)
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
	delete [] pfMax;
	delete [] pfAbs;
	delete [] pfRSI1;
	delete [] pfRSI2;
	delete [] pfRSI3;
	delete [] pfRetMax;
	delete [] pfRetAbs;

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	pLine->setLineColor(0);
	CString strInfo;
	strInfo.Format(_T("RSI(%d,%d,%d) RSI1"),N1,N2,N3);
	pLine->setTitle(strInfo);
	pLine->setRefer(RTZERO,0);
	pLine->setData((char *)pnRSI1,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	pKLine->addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	pLine->setLineColor(1);

	strInfo = "RSI2";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTZERO,0);
	pLine->setData((char *)pnRSI2,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	pKLine->addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	pLine->setLineColor(2);

	strInfo= "RSI3";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTZERO,0);
	pLine->setData((char *)pnRSI3,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	pKLine->addChartUnit(pLine);

}

void CPicWnd::setBOLL(int c_nCount, int *c_pParams)
{
	if (c_nCount == 0)
		return;
	if (c_pParams == NULL)
		return;

	Charts * pKLine;    
	SStock * pStock = gpData->GetStock(m_strStockCode);
	if(pStock == NULL)
		return;

	ChartUnit * pLine;
	int w,s;
	getZoom(m_nZoom,w,s);
	KLINE * pBlock = (KLINE *)m_pKData;

	if (!pBlock || m_nKItemCount <= 0)
		return;    
	pKLine = new Charts();
	pKLine->setTitle(PIC_BOLL);
	pKLine->setType(PIC_BOLL,m_usCycle);
	m_listPics.push_back(pKLine);

	float *pfData = new float[m_nKItemCount];
	for(int n=0; n<m_nKItemCount; n++)
		pfData[n] = float(pBlock[n].close);

	int N;
	N = c_pParams[0];

	float *pfBoll = new float[m_nKItemCount];
	float *pfStd = new float[m_nKItemCount];
	float *pfUpper = new float[m_nKItemCount];
	float *pfLower = new float[m_nKItemCount];

	Calc_Ma(pfBoll,pfData,m_nKItemCount,N);//N日MA	
	Calc_Std(pfStd,pfData,m_nKItemCount,N);//Boll

	for(int n=0; n<m_nKItemCount; n++)
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

	int * pnBoll = (int *)malloc(m_nKItemCount * sizeof(int));
	int * pnUpper = (int *)malloc(m_nKItemCount * sizeof(int));
	int * pnLower = (int *)malloc(m_nKItemCount * sizeof(int));
	for(int n=0; n<m_nKItemCount; n++)
	{
		if (InValid(pfBoll[n]))
			pnBoll[n] = 0X7FFFFFFF;
		else
			pnBoll[n] = int(pfBoll[n] * 100);
		if (InValid(pfUpper[n]))
			pnUpper[n] = 0X7FFFFFFF;
		else
			pnUpper[n] = int(pfUpper[n] * 100);
		if (InValid(pfLower[n]))
			pnLower[n] = 0X7FFFFFFF;
		else
			pnLower[n] = int(pfLower[n] * 100);
	}

	delete [] pfBoll;
	delete [] pfStd;
	delete [] pfUpper;
	delete [] pfLower;

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	pLine->setLineColor(0);
	CString strInfo;
	strInfo.Format(_T("BOLL(%d) BOLL"),N);
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setData((char *)pnBoll,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(100*1000);	
	pKLine->addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	pLine->setLineColor(0);

	strInfo = "UPPER";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setData((char *)pnUpper,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(100*1000);
	pKLine->addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	pLine->setLineColor(2);

	strInfo= "LOWER";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setData((char *)pnLower,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(100*1000);	
	pKLine->addChartUnit(pLine);

}

void CPicWnd::HideOrShowCharts(int c_nIndex)
{
	if (m_listPics.size() < 3)
		return;

	int nShow;
	int nWay;
	int nHeight= 0;
	if (c_nIndex == 2)
	{
		nShow = 1;
		nWay = -1;
	}
	else
		if (c_nIndex == 1)
		{
			nShow = 2;
			nWay = 1;
		}
		else
			return;

	if (m_listPics.at(nShow)->m_bVisible)//上一个图显示中
	{
		nHeight = m_listPics.at(nShow)->setVisible(false);//隐藏它
	}
	else
	{
		nHeight = m_listPics.at(nShow)->setVisible(true);//显示它
		nHeight *= -1;
	}

	m_listPics.at(c_nIndex)->resizeBody(nHeight,nWay);

	setBeginEndPos(0,0);
	//onSizeChange();
	Invalidate();
}

void CPicWnd::addBOLL(int c_nCount, int *c_pParams)
{
	//if (m_bHISKBOLL)
	//	return;

	if (m_ptType != PTHISK)
		return;

	if (c_nCount == 0)
		return;
	if (c_pParams == NULL)
		return;

	Charts * pKLine;    
	SStock * pStock = gpData->GetStock(m_strStockCode);
	if(pStock == NULL)
		return;

	pKLine = m_listPics.at(0);	
	pKLine->removeSpecialUnit(STEMA);
	pKLine->setTechType(PIC_BOLL);
	if (pKLine->getSpecialUnit(STBOLL))
		return;

	if (pKLine->removeSpecialUnit(STBOLL) == true)
	{
		m_bHISKBOLL = false;
		return;
	}

	m_bHISKBOLL = true;
	int nLineColor = pKLine->m_listCharts.size() - 1;	
	ChartUnit * pLine;
	int w,s;
	getZoom(m_nZoom,w,s);
	KLINE * pBlock = (KLINE *)m_pKData;

	if (!pBlock || m_nKItemCount <= 0)
		return;    

	float *pfData = new float[m_nKItemCount];
	for(int n=0; n<m_nKItemCount; n++)
		pfData[n] = float(pBlock[n].close);

	int N;
	N = c_pParams[0];

	float *pfBoll56 = new float[m_nKItemCount];

	float *pfBoll = new float[m_nKItemCount];
	float *pfStd = new float[m_nKItemCount];
	float *pfUpper = new float[m_nKItemCount];
	float *pfLower = new float[m_nKItemCount];

	Calc_Ma(pfBoll56,pfData,m_nKItemCount,56);//N日MA	
	Calc_Ma(pfBoll,pfData,m_nKItemCount,N);//N日MA	
	Calc_Std(pfStd,pfData,m_nKItemCount,N);//Boll

	for(int n=0; n<m_nKItemCount; n++)
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

	int * pnBoll56 = (int *)malloc(m_nKItemCount * sizeof(int));
	int * pnBoll = (int *)malloc(m_nKItemCount * sizeof(int));
	int * pnUpper = (int *)malloc(m_nKItemCount * sizeof(int));
	int * pnLower = (int *)malloc(m_nKItemCount * sizeof(int));
	for(int n=0; n<m_nKItemCount; n++)
	{
		if (InValid(pfBoll[n]))
			pnBoll[n] = 0X7FFFFFFF;
		else
			pnBoll[n] = int(pfBoll[n]);
		if (InValid(pfUpper[n]))
			pnUpper[n] = 0X7FFFFFFF;
		else
			pnUpper[n] = int(pfUpper[n]);
		if (InValid(pfLower[n]))
			pnLower[n] = 0X7FFFFFFF;
		else
			pnLower[n] = int(pfLower[n]);

		if (InValid(pfBoll56[n]))
			pnBoll56[n] = 0X7FFFFFFF;
		else
			pnBoll56[n] = int(pfBoll56[n]);
	}

	delete [] pfBoll56;
	delete [] pfBoll;
	delete [] pfStd;
	delete [] pfUpper;
	delete [] pfLower;

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	//pLine->setLineColor(gpSkinManager->getLineColor(nLineColor));
	pLine->setLineColor(0xFFFF33);	
	pLine->setLineWidth(2);
	CString strInfo;
	strInfo = "MA(56)";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setData((char *)pnBoll56,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	pLine->setSpecialType(STBOLL);
	pKLine->addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	pLine->setLineColor(nLineColor);
	pLine->setPenStyle(PS_DASHDOT);
	strInfo.Format(_T("B(%d)"),N);
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setData((char *)pnBoll,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);	
	pLine->setSpecialType(STBOLL);
	pKLine->addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	//pLine->setLineColor(gpSkinManager->getLineColor(nLineColor + 1));
	pLine->setLineColor(0x9900FF);
	//pLine->setLineWidth(3);

	strInfo = "U";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setData((char *)pnUpper,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	pLine->setSpecialType(STBOLL);
	pKLine->addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	//pLine->setLineColor(gpSkinManager->getLineColor(nLineColor + 2));
	pLine->setLineColor(0x0000FF);
	//pLine->setLineWidth(3);

	strInfo= "L";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setData((char *)pnLower,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);	
	pLine->setSpecialType(STBOLL);
	pKLine->addChartUnit(pLine);

	addBOLL2(pKLine);
}

void CPicWnd::addBOLL2(Charts * c_pCharts)
{

	Charts * pKLine = c_pCharts;

	SStock * pStock = gpData->GetStock(m_strStockCode);


	m_bHISKBOLL = true;
	int nLineColor = pKLine->m_listCharts.size() - 1;	
	ChartUnit * pLine;
	int w,s;
	getZoom(m_nZoom,w,s);
	KLINE * pBlock = (KLINE *)m_pKData;

	if (!pBlock || m_nKItemCount <= 0)
		return;    

	float *pfData = new float[m_nKItemCount];
	for(int n=0; n<m_nKItemCount; n++)
		pfData[n] = float(pBlock[n].close);

	int N;
	N = 55;

	float *pfBoll = new float[m_nKItemCount];
	float *pfStd = new float[m_nKItemCount];
	float *pfUpper = new float[m_nKItemCount];
	float *pfLower = new float[m_nKItemCount];

	Calc_Ma(pfBoll,pfData,m_nKItemCount,N);//N日MA	
	Calc_Std(pfStd,pfData,m_nKItemCount,N);//Boll

	Calc_Ma(pfBoll,pfData,m_nKItemCount,26);//26日MA	换成26日
	for(int n=0; n<m_nKItemCount; n++)
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

	int * pnBoll = (int *)malloc(m_nKItemCount * sizeof(int));
	int * pnUpper = (int *)malloc(m_nKItemCount * sizeof(int));
	int * pnLower = (int *)malloc(m_nKItemCount * sizeof(int));
	for(int n=0; n<m_nKItemCount; n++)
	{
		if (InValid(pfBoll[n]))
			pnBoll[n] = 0X7FFFFFFF;
		else
			pnBoll[n] = int(pfBoll[n]);
		if (InValid(pfUpper[n]))
			pnUpper[n] = 0X7FFFFFFF;
		else
			pnUpper[n] = int(pfUpper[n]);
		if (InValid(pfLower[n]))
			pnLower[n] = 0X7FFFFFFF;
		else
			pnLower[n] = int(pfLower[n]);
	}

	delete [] pfBoll;
	delete [] pfStd;
	delete [] pfUpper;
	delete [] pfLower;


	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	//pLine->setLineColor(gpSkinManager->getLineColor(nLineColor + 1));
	pLine->setLineColor(RGB(255,0,0));
	pLine->setLineWidth(4);

	CString strInfo(_T("U55"));
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setData((char *)pnUpper,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);
	pLine->setSpecialType(STBOLL);
	pKLine->addChartUnit(pLine);

	pLine = new ChartUnit();
	pLine->setChartUnitType(CULink);
	pLine->setCell(w,s);
	//pLine->setLineColor(gpSkinManager->getLineColor(nLineColor + 2));
	pLine->setLineColor(RGB(0,255,0));
	pLine->setLineWidth(4);

	strInfo= "L55";
	pLine->setTitle(strInfo);
	pLine->setRefer(RTMIN,0);
	pLine->setData((char *)pnLower,sizeof(int) * m_nKItemCount,true);
	pLine->setPrecision(2);
	pLine->setMultiplier(1000);	
	pLine->setSpecialType(STBOLL);
	pKLine->addChartUnit(pLine);
}

void CPicWnd::addEMA(int c_nCount, int *c_pParams)
{
	if (c_nCount == 0)
		return;
	if (c_pParams == NULL)
		return;

	if (m_ptType != PTHISK)
		return;
	if (m_listPics.size() == 0)
		return;
	//if (m_bHISKEMA)
	//	return;

	Charts * pKLine = m_listPics.at(0);
	pKLine->removeSpecialUnit(STBOLL);
	if (pKLine->getSpecialUnit(STEMA))
		return;

	pKLine->setTechType(PIC_EMA);
	/*
	if (pKLine->removeSpecialUnit(STEMA))
	{
	m_bHISKEMA = false;
	return;
	}*/

	m_bHISKEMA = true;
	SStock * pStock = gpData->GetStock(m_strStockCode);    

	ChartUnit * pLine;
	int w,s;
	getZoom(m_nZoom,w,s);
	KLINE * pBlock = (KLINE *)m_pKData;

	if (!pBlock || m_nKItemCount <= 0)
		return;

	float *pfData = new float[m_nKItemCount];
	for(int n=0; n<m_nKItemCount; n++)
		pfData[n] = pBlock[n].close;

	float *pfRet = new float[m_nKItemCount];
	for(int n=0; n<c_nCount; n++)
	{
		int *pn = (int *)malloc(m_nKItemCount * sizeof(int));
		Calc_Ema(pfRet,pfData,m_nKItemCount,c_pParams[n]);
		for(int k=0; k<m_nKItemCount; k++)
		{
			if (InValid(pfRet[k]))
				pn[k] = 0X7FFFFFFF;
			else
				pn[k] = int(pfRet[k]);
		}
		pLine = new ChartUnit();
		pLine->setChartUnitType(CULink);
		pLine->setCell(w,s);
		pLine->setLineColor(n);
		CString strInfo;
		strInfo.Format(_T("EMA%d"),c_pParams[n]);
		pLine->setParam(c_pParams[n]);
		pLine->setTitle(strInfo);
		pLine->setRefer(RTMIN,0);		        
		pLine->setData((char *)pn,sizeof(int) * m_nKItemCount,true);
		pLine->setPrecision(2);
		pLine->setMultiplier(1000);
		pLine->setSpecialType(STEMA);
		pKLine->addChartUnit(pLine);
	}
	delete [] pfRet;
	delete [] pfData;
}

void CPicWnd::resetLineColor()
{
	for(int n=0; n<m_listPics.size(); n++)
	{
		m_listPics.at(n)->resetChartsColor();
	}
}

void CPicWnd::SetMouseLineOn(bool c_bOn)
{
	m_bDrawMouseLine = c_bOn;
	if (c_bOn && m_ptType == PTHISK)
	{
		CRect rect,rectMain;
		GetWindowRect(rectMain);

		gpKDetail->GetWindowRect(rect);
		int nFontHeight = gpSkinManager->GetFontHeight(gpSkinManager->GetGraphFont());
		nFontHeight += 2;
		int nFontWidth = gpSkinManager->GetFontWidth(gpSkinManager->GetGraphFont(),_T("当前时间：20011231"));
		nFontWidth += 16;
		if (nFontWidth < 120)
			nFontWidth = 120;
		rect.right = rect.left + nFontWidth;
		rect.bottom = rect.top + nFontHeight * 11 + 24;
		if (gpKDetail->IsDefaultRect(rect))
		{			
			CPoint pt;
			::GetCursorPos(&pt);
			CRect r;
			r.left = rectMain.left + 4;//;
			//r.top = pt.y + 20;// rectMain.top + 20;// + 10;
			r.top = rectMain.top + (m_rectMainPic.Height()-rect.Height())/2;
			if (r.top < 0)
				r.top = 0;
			r.right = r.left + rect.Width();
			r.bottom = r.top + rect.Height();
			gpKDetail->SetDefaultRect(r);
			gpKDetail->MoveWindow(r);
		}
		else
		{
			gpKDetail->MoveWindow(rect);
		}
		gpKDetail->ShowWindow(SW_SHOW);
	}
	else
	{
		gpKDetail->ShowWindow(SW_HIDE);
		m_nCurPos = -1;
		m_nCurPosTime = -1;
		setCurPos(m_nCurPos,m_nCurPosTime);
	}
}
void CPicWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	if (bShow == false)
		SetMouseLineOn(false);
}

void CPicWnd::InitStaticData(SStock * c_pStock)
{
}

void CPicWnd::setCursorAway()
{
	CPoint pt(0,0);	
	ClientToScreen(&pt);
	SetCursorPos(pt.x,pt.y);
}

void CPicWnd::OnSelectTech()
{
	// TODO: 在此添加命令处理程序代码
	bool bIndex;
	bool bMain;
	if (gpData->IsStock(m_strStockCode))
		bIndex = false;
	else
		bIndex = true;

	CPoint pt;
	pt.x = m_nMouseX;
	pt.y = m_nMouseY;
	Charts * pCharts = getChartsSelected();//isMouseInCharts(pt);
	if (pCharts == NULL)
		return;

	bMain = pCharts->isMainPic();

	CDlgSelectTech dlg;
	dlg.m_bIndex = bIndex;
	dlg.m_strStockCode = m_strStockCode;
	dlg.m_bMainPic = bMain;
	dlg.m_usCycle = m_usCycle;
	if (dlg.DoModal() == IDOK)
	{
		if (CTechManager::getInstance()->isValid(dlg.m_strSelected,!bIndex,m_usCycle,m_strStockCode) == false)
		{
			MessageBox(_T("目前不提供当前周期的所选指标！"),_T("提示"));
			return;
		}
		pCharts->m_usCycle = m_usCycle;
		if (IsExistsTech(dlg.m_strSelected) == false)
		{
			ChangeTech(pCharts,dlg.m_strSelected);
			SaveCurTechSet();
		}
	}
	resetZoom();
	resetSize();
	setBeginEndPos(0,0);
	//onSizeChange();
}

void CPicWnd::ChangeTech(Charts * c_pCharts,CString c_strTech)
{
	if (c_pCharts->isMainPic())
	{
		c_pCharts->setMainTech(c_strTech,(KLINE *)m_pKData,m_nKItemCount);
	}
	else
	{
		c_pCharts->setTech(c_strTech,(KLINE *)m_pKData,m_nKItemCount,NULL,0);
	}
}
void CPicWnd::OnSetTechParam()
{
	// TODO: 在此添加命令处理程序代码
	bool bIndex;
	bool bMain;
	if (gpData->IsStock(m_strStockCode))
		bIndex = false;
	else
		bIndex = true;

	CPoint pt;
	pt.x = m_nMouseX;
	pt.y = m_nMouseY;
	Charts * pCharts = getChartsSelected();//isMouseInCharts(pt);
	if (pCharts == NULL)
		return;

	bMain = pCharts->isMainPic();

	CDlgParamSet dlg;
	dlg.m_bMainPic = bMain;
	dlg.m_strTech = pCharts->getType();
	dlg.m_usCycle = m_usCycle;

	if (bMain)
	{
		dlg.m_strTech = pCharts->getTechType();
	}
	if (dlg.DoModal() == IDOK)
	{
		ChangeTech(pCharts,dlg.m_strTech);
		resetZoom();
		resetSize();
		setBeginEndPos(0,0);
		//onSizeChange();
	}
}

void CPicWnd::SaveCurTechSet()
{
	bool bIndex = false;
	if(gpData->IsStock(m_strStockCode))
		bIndex = false;
	for(int n=0; n<m_listPics.size(); n++)
	{
		CString strTech;
		if (n == 0)
			strTech = m_listPics.at(n)->getTechType();
		else
			strTech = m_listPics.at(n)->getType();
		CTechManager::getInstance()->setTechByIndex(n,1,strTech,m_usCycle);
	}
}

bool CPicWnd::IsExistsTech(CString c_strTech)
{
	for(int n=0; n<m_listPics.size(); n++)
	{
		if (m_listPics.at(n)->getType() == c_strTech)
			return true;
	}
	return false;
}
void CPicWnd::OnMin1k()
{
	// TODO: 在此添加命令处理程序代码
	m_lockPics.WaitWrite();
	changePic(PTHISK,HISKMINDATA);
	m_lockPics.EndWrite();
}

void CPicWnd::OnMin5k()
{
	// TODO: 在此添加命令处理程序代码
	m_lockPics.WaitWrite();
	changePic(PTHISK,HISKMIN5DATA);
	m_lockPics.EndWrite();
}

void CPicWnd::OnMin15k()
{
	// TODO: 在此添加命令处理程序代码
	m_lockPics.WaitWrite();
	changePic(PTHISK,HISKMIN15DATA);
	m_lockPics.EndWrite();
}

void CPicWnd::OnMin30k()
{
	// TODO: 在此添加命令处理程序代码
	m_lockPics.WaitWrite();
	changePic(PTHISK,HISKMIN30DATA);
	m_lockPics.EndWrite();
}

void CPicWnd::OnMin60k()
{
	// TODO: 在此添加命令处理程序代码
	m_lockPics.WaitWrite();
	changePic(PTHISK,HISKMIN60DATA);
	m_lockPics.EndWrite();
}
void CPicWnd::FormatMinKData()
{
	if (m_strStockCode.IsEmpty())
		return;

	SStock * pStock;
	pStock = gpData->GetStock(m_strStockCode);
	if (pStock == NULL)
		return;

	if (pStock->m_nMinItemCount == 0)
		return;	

	if (m_nMinFreshBegin > 0)//检查是否已经存在了
	{
		int nKTime = 0;
		_K_LINE * pk = (_K_LINE *)(m_pKData + (m_nMinFreshBegin-1)*sizeof(KLINE));	
		nKTime = pk->day;
		nKTime /= 10000;
		if (nKTime == gpData->m_nWorkDay%1000000)//YYMMDD
			return;
	}
	int nUnitTime = 1;
	if (m_usCycle == HISKMINDATA)
		nUnitTime = 1;
	else
		if (m_usCycle == HISKMIN5DATA)
			nUnitTime = 5;
		else
			if (m_usCycle == HISKMIN15DATA)
				nUnitTime = 15;
			else
				if (m_usCycle == HISKMIN30DATA)
					nUnitTime = 30;
				else
					if (m_usCycle == HISKMIN60DATA)
						nUnitTime = 60;

	int nKCount = 0;
	MinUnit * pMinUnit = (MinUnit *)pStock->m_pMinData;	
	_K_LINE * pKUnit = (_K_LINE *)(m_pKData + m_nMinFreshBegin*sizeof(KLINE));	

	int nTime = 570;
	if (nUnitTime == 1)
	{
		for(int n=0; n<pStock->m_nMinItemCount; n++)
		{
			pKUnit[n].day = pMinUnit[n].Time + gpData->m_nWorkDay % 1000000 * 10000;
			pKUnit[n].open = pMinUnit[n].OpenPrice;
			pKUnit[n].close = pMinUnit[n].NewPrice;
			pKUnit[n].high = pMinUnit[n].MaxPrice;
			pKUnit[n].low = pMinUnit[n].MinPrice;
			pKUnit[n].volume = pMinUnit[n].Volume;
			pKUnit[n].amount = pMinUnit[n].Volume * pMinUnit[n].AvgPrice;
			if (pKUnit[n].open == 0)
				pKUnit[n].open = pKUnit[n].close;			
			if (pKUnit[n].high == 0)
				pKUnit[n].high = pKUnit[n].close;
			if (pKUnit[n].low == 0)
				pKUnit[n].low = pKUnit[n].close;

		}
		m_nKItemCount = m_nMinFreshBegin + pStock->m_nMinItemCount;
	}
	else
	{
		pKUnit[nKCount].day = pMinUnit[0].Time + gpData->m_nWorkDay % 1000000 * 10000;
		pKUnit[nKCount].open = pMinUnit[0].OpenPrice;
		pKUnit[nKCount].close = pMinUnit[0].NewPrice;
		pKUnit[nKCount].high = pMinUnit[0].MaxPrice;
		pKUnit[nKCount].low = pMinUnit[0].MinPrice;
		pKUnit[nKCount].volume = pMinUnit[0].Volume;
		pKUnit[nKCount].amount = pMinUnit[0].Volume * pMinUnit[0].AvgPrice;

		for(int n=1; n<pStock->m_nMinItemCount; n++)
		{	
			nTime = n;
			if (nTime > 120)
				nTime--;
			//if (pMinUnit[n].Time % nUnitTime == 1 && pMinUnit[n].Time != 570 && pMinUnit[n].Time != 571)
			if (nTime % nUnitTime == 1 && nTime != 1)
			{
				nKCount++;
				pKUnit[nKCount].day = pMinUnit[n].Time + gpData->m_nWorkDay % 1000000 * 10000;
				pKUnit[nKCount].open = pMinUnit[n].OpenPrice;
				pKUnit[nKCount].close = pMinUnit[n].NewPrice;
				pKUnit[nKCount].high = pMinUnit[n].MaxPrice;
				pKUnit[nKCount].low = pMinUnit[n].MinPrice;
				pKUnit[nKCount].volume = pMinUnit[n].Volume;
				pKUnit[nKCount].amount = pMinUnit[n].Volume * pMinUnit[n].AvgPrice;
			}
			else
			{
				pKUnit[nKCount].day = pMinUnit[n].Time + gpData->m_nWorkDay % 1000000 * 10000;
				pKUnit[nKCount].close = pMinUnit[n].NewPrice;
				if (pMinUnit[n].MaxPrice > pKUnit[nKCount].high)
					pKUnit[nKCount].high = pMinUnit[n].MaxPrice;
				if (pMinUnit[n].MinPrice < pKUnit[nKCount].low)
					pKUnit[nKCount].low = pMinUnit[n].MinPrice;
				pKUnit[nKCount].volume += pMinUnit[n].Volume;
				pKUnit[nKCount].amount += pMinUnit[n].Volume * pMinUnit[n].AvgPrice;
			}
		}
		m_nKItemCount = m_nMinFreshBegin + nKCount + 1;
	}
}		

void CPicWnd::LogA(char * c_pBuf)
{			
#ifdef _DEBUG
	FILE * f;
	f = fopen(".\\pic.log","ab");
	if (f)
	{
		fseek(f,0,SEEK_END);
		fwrite(c_pBuf,1,strlen(c_pBuf),f);
		fclose(f);
	}
#endif
}
BOOL CPicWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	//	if (cs.lpszClass == NULL)
	//		cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS);

	return CWnd::PreCreateWindow(cs);
}

void CPicWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	setChartsSelected(point);
	Invalidate();
	CWnd::OnRButtonDown(nFlags, point);
}

void CPicWnd::OnShowHideMainTech()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptType == PTHISK)
	{
		if (m_listPics.size() > 0)
		{
			m_bDrawMainTechLine = !m_bDrawMainTechLine;
			Invalidate();
		}
	}
}

void CPicWnd::OnAixNormal()
{
	// TODO: 在此添加命令处理程序代码
	if(m_ptType != PTHISK)
		return;
	if (m_listPics.size() == 0)
		return;
	m_atCur = AIXNORMAL;
	m_listPics.at(0)->setAixType(AIXNORMAL);
	Invalidate();
	CTechManager::getInstance()->setAix(AIXNORMAL);
}

void CPicWnd::OnAixLg()
{
	// TODO: 在此添加命令处理程序代码
	if(m_ptType != PTHISK)
		return;
	if (m_listPics.size() == 0)
		return;
	m_atCur = AIXLG;
	m_listPics.at(0)->setAixType(AIXLG);
	Invalidate();
	CTechManager::getInstance()->setAix(AIXLG);
}

void CPicWnd::createFutureKLine()
{
	if (m_ptType != PTHISK)
		return;
	if (m_nKItemCount <= 0)
		return;
	int nDay = gpData->m_nWorkDay;
	KLINE * pK = (KLINE *)m_pKData;
	if (m_nKItemCount > 0)
	{
		if (pK[m_nKItemCount - 1].day > nDay)
			nDay = pK[m_nKItemCount - 1].day;
	}


	for(int n=m_nKItemCount; n<4096; n++)
	{
		if (m_usCycle == HISKMINDATA || m_usCycle == HISKMIN5DATA || m_usCycle == HISKMIN15DATA || m_usCycle == HISKMIN30DATA || m_usCycle == HISKMIN60DATA)
		{///分线
			nDay = GetNextMinute(m_usCycle,nDay);
			pK[n].day = nDay;
		}
		else if (m_usCycle == 5)
		{///日线
			nDay = GetNextDay(nDay);
			pK[n].day = nDay;
		}
		else if (m_usCycle == 6)
		{///周线
			nDay = GetNextWeek(nDay);
			pK[n].day = nDay;
		}
		else if (m_usCycle == 7)
		{//月线
			nDay = GetNextMonth(nDay);
			pK[n].day = nDay;
		}
	}	
}

int CPicWnd::GetNextMinute(unsigned short c_usCycle,int c_nMinute)
{
	int nMins[242] = {570,571,572,573,574,575,576,577,578,579,580,581,582,583,584,585,586,587,588,589,590,591,592,593,594,595,596,597,598,599,600,\
		601,602,603,604,605,606,607,608,609,610,611,612,613,614,615,616,617,618,619,620,621,622,623,624,625,626,627,628,629,630,\
		631,632,633,634,635,636,637,638,639,640,641,642,643,644,645,646,647,648,649,650,651,652,653,654,655,656,657,658,659,660,\
		661,662,663,664,665,666,667,668,669,670,671,672,673,674,675,676,677,678,679,680,681,682,683,684,685,686,687,688,689,690,\
		780,781,782,783,784,785,786,787,788,789,790,791,792,793,794,795,796,797,798,799,800,801,802,803,804,805,806,807,808,809,810,\
		811,812,813,814,815,816,817,818,819,820,821,822,823,824,825,826,827,828,829,830,831,832,833,834,835,836,837,838,839,840,\
		841,842,843,844,845,846,847,848,849,850,851,852,853,854,855,856,857.858,859,860,861,662,863,864,865,866,867,868.869,870,\
		871,872,873,874,875,876,877,878,879,880,881,882,883,884,885,886,887,888,889,890,891,892,893,894,895,896,897,898,899,900};
	int nMin5s[48] =     {575,580,585,590,595,600,605,610,615,620,625,630,635,640,645,650,655,660,665,670,675,680,685,690,785,790,795,800,805,810,815,820,825,830,835,840,845,850,855,860,865,870,875,880,885,890,895,900};
	int nMin15s[16] = {585,600,615,630,645,660,675,690,795,810,825,840,855,870,885,900};
	int nMin30s[8] = {600,630,660,690,810,840,870,900};
	int nMin60s[4] = {630,690,840,900};
	int *pn = NULL;
	int nCount = 0;
	int nDay = c_nMinute/10000;
	int nMinute = c_nMinute % 10000;
	switch(c_usCycle)
	{
	case HISKMINDATA:///1分线
		{
			pn = nMins;
			nCount = 242;
		}
		break;
	case HISKMIN5DATA:///5分线
		pn = nMin5s;
		nCount = 48;
		break;
	case HISKMIN15DATA:///15分线
		pn = nMin15s;
		nCount = 16;
		break;
	case HISKMIN30DATA:///30分线
		pn = nMin30s;
		nCount = 8;
		break;
	case HISKMIN60DATA://60分线
		pn = nMin60s;
		nCount = 4;
		break;
	default:
		return 0;
	}
	if (pn == NULL)
		return c_nMinute;
	int nIndex = -1;
	for(int n=0; n<nCount; n++)
	{
		if (pn[n] > nMinute)
		{
			nIndex = n;
			break;
		}
	}
	if (nIndex >= 0 && nIndex < nCount)
	{
		return nDay * 10000 + pn[nIndex];
	}
	nDay = GetNextDay(nDay + 20000000);
	return pn[0] + nDay % 1000000 * 10000;
}

int	CPicWnd::GetNextDay(int c_nDay)
{
	///c_nDay，如20120203 星期五.

	COleDateTime dt;
	///年，月，日，时，分，秒.
	dt.SetDateTime(c_nDay/10000,c_nDay % 10000 / 100,c_nDay % 100,0,0,0);	

	COleDateTimeSpan dtSpan;
	//设置时间跨度.日，时，分，秒.
	dtSpan.SetDateTimeSpan(1,0,0,0);

	while(true)
	{
		dt += dtSpan;
		///星期六、日，非交易日.
		if (dt.GetDayOfWeek() == 1 || dt.GetDayOfWeek() == 7)
		{
			continue;
		}

		///返回日期，如20120206 星期一.
		return dt.GetDay() + dt.GetMonth() * 100 + dt.GetYear() * 10000;
	}
}

int	CPicWnd::GetNextWeek(int c_nDay)
{
	///c_nDay，如20120131.星期二.


	int nDay = c_nDay;
	while(true)
	{
		nDay = GetNextDay(nDay);///c_nDay，如20120201.

		///如果这一天(nDay)，是否和上一天(c_nDay)同在一周之内.
		if (!IsSameWeek(nDay,c_nDay))
			break;
	}///知道nDay和c_nDay不在同一周.根据星期日是一周的开始，那么nDay是星期日.


	int nNewDay = nDay;
	while(true)
	{
		nNewDay = GetNextDay(nDay);
		if (!IsSameWeek(nDay,nNewDay))
		{
			//返回下一周的星期五，20120210.
			return nDay;
		}
		nDay = nNewDay;
	}
}

int	CPicWnd::GetNextMonth(int c_nDay)
{
	int nDay = c_nDay;
	while(true)
	{
		nDay = GetNextDay(nDay);
		if (!IsSameMonth(nDay,c_nDay))
			break;
	}
	int nNewDay = nDay;
	while(true)
	{
		nNewDay = GetNextDay(nDay);
		if (!IsSameMonth(nDay,nNewDay))
			return nDay;
		nDay = nNewDay;
	}
}

void CPicWnd::ResetFutrueItem(int c_nWay)
{
	if (m_ptType != PTHISK)
		return;

	m_lockPics.WaitWrite();	
	m_nLockPointEnd = -1;
	if (c_nWay == 1)		
		m_nFutrueItems += 20;
	else
		m_nFutrueItems -= 20;
	if (m_nFutrueItems > 200)
		m_nFutrueItems = 200;
	if (m_nFutrueItems < 0)
		m_nFutrueItems = 0;
	m_nPointViewCount = 0;
	onSizeChange();		
	m_lockPics.EndWrite();

}
void CPicWnd::OnWeightFront()
{
	// TODO: 在此添加命令处理程序代码
	if (gpData->m_usWeight != 2)
	{
		gpData->m_usWeight = 2;
		if (m_ptType == PTHISK && (m_usCycle == 5 || m_usCycle == 6 || m_usCycle == 7))
		{
			setStockCode(m_strStockCode);
		}
	}
}

void CPicWnd::OnWeightNone()
{
	// TODO: 在此添加命令处理程序代码
	if (gpData->m_usWeight != 3)
	{
		gpData->m_usWeight = 3;
		if (m_ptType == PTHISK && (m_usCycle == 5 || m_usCycle == 6 || m_usCycle == 7))
		{
			setStockCode(m_strStockCode);
		}
	}
}

void CPicWnd::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (lpDrawItemStruct->CtlType == ODT_MENU)
		m_menu.DrawItem(lpDrawItemStruct);
	CWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CPicWnd::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (lpMeasureItemStruct->CtlType == ODT_MENU)
		m_menu.MeasureItem(lpMeasureItemStruct);
	CWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}