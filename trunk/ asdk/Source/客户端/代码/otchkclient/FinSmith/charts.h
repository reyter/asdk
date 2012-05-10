#ifndef CHARTS_H
#define CHARTS_H

#include "chartunit.h"

class CManualDraw;
class Charts
{
public:
    Charts();
	~Charts();
	
public:
	void setSize(CRect c_rect);
	void resizeBody(int c_nHeight,int c_nWay);
	void resetChartsColor();
    void setRects(CRect c_rectBody,CRect c_rectHead,CRect c_rectFoot);
    void getRectBody(CRect &c_rectBody);
    void getRectHead(CRect &c_rectHead);
    void getRectFoot(CRect &c_rectFoot);

    void setTitle(CString c_strTitle);
	void setType(CString c_strTitle,unsigned short c_usCycle);
	CString getType();
	unsigned short getCycle();
	void setTechType(CString c_strType);
	CString getTechType();
	CString getTitle();
    void drawTitles(CDC * c_pDC);
    bool isSelected(int c_nPos,int c_nYValue,CPoint c_pt);
    void addChartUnit(ChartUnit * c_pUnit);
	void removeChartUnit(ChartUnitType c_st);
	bool removeSpecialUnit(SpecialType);
	bool getSpecialUnit(SpecialType);
	void removeTech(bool c_bRemoveFirst);//清除指标

    ChartUnit * getChartUnit(CString c_strChartName);
    ChartUnit * getChartUnitByType(ChartUnitType c_ctType);
    void cleanCharts();
    void getChartsMaxMinValue(int &c_nMax,int &c_nMin,float &c_fMax,float &c_fMin);
    void setChartsMaxMinValue(int c_nMax,int c_nMin,float,float);
    void setChartsDrawRect(CRect c_rect);
    void setChartsViewProperty(int c_nCount,int *c_pnHoriValue,int c_nDataBegin,int c_nDataBeginTime,int c_nDataCount);
    void setChartsCell(int w,int s);
    void setChartsRefer(ReferType c_type,int c_nRefer);    
    void drawCharts(CDC * c_pDC,CString c_strStockCode,bool c_bDrawMainTechLine = true);
    void drawRefer(CDC * c_pDC);

	void setCurPos(int c_nPos,int c_nPosTime);
	ChartUnit * getChartUnit(int c_nIndex);	
	void calcMaxMinValue();
	void calcMaxMinValue(int c_nMax,int c_nMin);
	int setVisible(bool c_bShow);
	bool isPointIn(CPoint c_point);
	bool isMainPic();

	void setMainTech(CString c_strTech,KLINE * c_pBlock,int c_nKItemCount);
	void setTech(CString c_strTech,KLINE * c_pBlock,int c_nKItemCount,KLINE * c_pChgKItem=NULL,int c_nChgKItemCount=0);
	void setEMA(KLINE *c_pBlock,int c_nKItemCount);
	void setBOLL(KLINE *c_pBlock,int c_nKItemCount);
	void addBOLL2(KLINE *c_pBlock,int c_nKItemCount, int c_nBOLL,int c_nMA);
	void setMA(KLINE *c_pBlock,int c_nKItemCount);
	void setMMA(KLINE *c_pBlock,int c_nKItemCount);
	void setVOL(KLINE * c_pBlock,int c_nKItemCount);

	void setMACD(KLINE *c_pBlock,int c_nKItemCount);
	void setKDJ(KLINE *c_pBlock,int c_nKItemCount);
	void setRSI(KLINE *c_pBlock,int c_nKItemCount);	

	void setSelected(bool c_b){m_bSelected = c_b;};
	bool getSelected(){return m_bSelected;};

	void setAixType(AixType);
	AixType getAixType();

	int getTimeByPos(int c_nPos);
	//是否发出买入买出信号
	void CheckBuyOrSell(KLINE * c_pBlock,int c_nPos,bool &c_bBuy,bool &c_bSell);	
	int caclTDREI(KLINE * c_pBlock,int c_nKItemCount,int * c_pfREI);
public:
	CString m_strStockCode;
    CString m_strTitle;
	CString m_strType;//类型
	unsigned short m_usCycle;//周期
	AixType m_atType;//坐标类型
	CString m_strTechType;//技术指标，只有主图此值有效
	bool m_bVisible;//是否可视
	bool m_bSelected;//当前是否被选中
	std::vector<ChartUnit *> m_listCharts;
    CRect m_rectBody;
    CRect m_rectHead;
    CRect m_rectFoot;
};

#endif // CHARTS_H
