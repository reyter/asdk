#ifndef CHARTUNIT_H
#define CHARTUNIT_H
#include "atltypes.h"

typedef enum {AIXNORMAL=0,AIXLG} AixType;//坐标类型
typedef enum {CUTrend=0,CUTrendVol,CUKLine,CUVOL,CULink,CUPoint,CUTick,CUTickLine,CUQCT,CUCOMMQCT,CUCOMMQCTATTACH,CUTDBUY,CUTDSELL} ChartUnitType;
typedef enum {RTZERO=0, RTMIN,RTMID,RTMAX} ReferType;//参照
typedef enum {STNULL=0,STMARKETKUANDU,STMARKETGUANGDU,STBOLL,STEMA,STMA,STZLMM,STRSI,STTD,STMMA,STMMC,STTDMA,STBSP,STZF}	SpecialType;//特殊类型

class ChartUnit
{
public:
     ChartUnit();
    ~ChartUnit();

	void setSpecialType(SpecialType);//特殊类型，如市场宽度
	SpecialType getSepcialType();
    void setChartUnitType(ChartUnitType c_cuType);
	ChartUnitType getUnitType();
    void setRefer(ReferType c_rt,int c_nValue);
    void getMaxMinValue(int &c_nBegin,int &c_nMax,int &c_nMin);
    void setMaxMinValue(int c_nMax,int c_nMin,float c_fMax,float c_fMin);
    void setDrawRect(CRect c_rect);    
    void setTitle(CString c_strTitle);
    void setLineColor(COLORREF c_colorRef);
	void setLineWidth(int);
	void setPenStyle(int);
    void setCell(int c_nWidth,int c_nSpace);
    void setData(char * c_pData,int c_nDataLen,bool c_bToFree);
	void setBz(short * c_psBz);
	void setTDPoint(int *,int*);
	void setParam(CString str);
	void setParam(int);
	CString getParamString();
	int  getParamInt();
    void setViewProperty(int c_nCount,int *c_pnHoriValue,int c_nDataBegin,int c_nDataBeginTime,int c_nDataCount);
    void drawChartUnit(CDC * c_pDC);//绘制图形
    void drawLinkLine(CDC * c_pDC,int c_nCount,int *c_pnVertValue,COLORREF c_cl);//绘制连接线
	void drawTick(CDC * c_pDC,int c_nCount,int *c_pnVertValue,COLORREF c_cl,COLORREF);//绘制Tick
    void drawTrend(CDC * c_pDC);//绘制走势力图形
    void drawTrendVol(CDC * c_pDC);//绘制走势图的成交量
    void drawKLine(CDC * c_pDC);//绘制K线	
	void drawTradeArea(CDC * c_pDC,int c_nDays,int c_n5Up,int c_n5Down,int c_n1Up,int c_n1Down);//绘制交易区域
	void drawPrice(CDC * c_pDC,int c_nNowPrice,int c_nPrice,int c_nCreatePrice,CString c_strInfo,CRect &c_rectInfo);
	void drawPriceRight(CDC * c_pDC,int c_nNowPrice,int c_nPrice,CString c_strInfo);
	void drawCutAlert(CDC * c_pDC,int c_nFDown,int c_nFUp);//止损线
	void drawKLineAttach(CDC * c_pDC);//绘制叠加线
    void drawVol(CDC * c_pDC);//绘制成交量
    void drawTitle(CDC * c_pDC,CRect &c_rect);
    void drawRefer(CDC * c_pDC);
	void drawXCoord(CDC * c_pDC,CRect c_rectAxis,int c_nLoopMax);

	int getTimeByPos(int c_nPos);//根据位置取时间
	int getPosByTime(int c_nTime);//根据时间取位置

	//绘制三角形
	void drawSJX(CDC * c_pDC,CPoint c_ptPoint,bool c_bUP,int c_nDis=10);
	
	void calcPerY();
    void calcVertPos(int *c_pnValue,int c_nCount,int *c_pnVert,ReferType c_rtType,int c_nReferValue);
    int getYValueInt(int c_nY);
	int getYValueInt(int &c_nX,int c_nY);
    CString getYValueString(int c_nY,int c_nMax=0);
	CString getYValuePercentString(int c_nY);
    int getValuePos(int c_nValue);
	CString getXValueString(int c_nPos,unsigned short c_usCycle);
	
    bool isSelected(int c_nPos,int c_nValue,CPoint c_pt);
    void setPrecision(int c_nPrecision);
    void setMultiplier(int c_nMultipier);
	void setDiv(int c_nDiv);

	void SetCurPos(int c_nPos,int c_nPosTime);
	void GetValueString(CString &c_strValue);

	int getXByPos(int c_nPos);
	int getPosByX(int c_nX);

	void setIsIndex(bool);
	void setFixedMaxMinValue(int c_nFixedMax,int c_nFixMinValue);
	void setDrawSingle(bool c_bIsSingle);
	bool isDrawSingle();

	void setDrawReferValue(bool);
	void SetAixType(AixType);
	AixType GetAixType();
	void SetPreClose(int);
	void ResetPriceAlertX()
	{
		m_nPriceAlertX = m_rectDraw.left;
	}

	int GetCurPos(){return m_nCurPos;};
	int GetCurPosTime(){return m_nCurPosTime;};
	int GetBeginPos(){return m_nDataBeginPos;};
	int GetBeginPosTime(){return m_nDataBeginPosTime;}
private:
    int m_nDataBeginPos;//数据开始位置
	int m_nDataBeginPosTime;//开始时间
	int m_nCurPos;
	int m_nCurPosTime;//当前位置时间
public:
	SpecialType m_nSpecialType;//特殊类型
    ChartUnitType m_cuType;//图形类型
    CString m_strTitle;//标题
    CRect m_rectTitle;//标题区域
    ReferType m_rtType;//参照
	CString m_strParam;//参数
	bool m_bDrawReferValue;//是否绘制参照值
    int m_nReferValue;//参照值
	int m_nZeroY;//0线
	int m_nPreClose;//昨天收盘
	int m_nBeginValue;//开始值
    int m_nMaxValue;//最大值
    int m_nMinValue;//最小值
    int m_nCellWidth;//单元宽度
    int m_nCellSpace;//单元留空
    int m_nHoriCount;//水平坐标总数

    int m_nDataCount;//有效量
    int *m_pnHoriPoint;//水平点
    char * m_pData;//节点数据
    int m_nDataLen;//数据长度
	short * m_psBz;//标志位
	int *m_pnTDPointHigh;
	int *m_pnTDPointLow;
	bool m_bToFree;//数据是否要释放
    CRect m_rectDraw;//绘制图形区域
    unsigned int m_clLine;//线的颜色
    bool m_bSelected;//选中
    int m_nPrecision;//精度
    int m_nMultiplier;//乘数
	int m_nDiv;//除数
    float m_fPerY;
	int m_nPenStyle;
	int m_nLineWidth;

	int m_nFixedMaxValue;//固定最大值
	int m_nFixedMinValue;//固定最小值
	bool m_bDrawSingle;//单独画，不和其他线发生联系

	bool m_bIsIndex;

	AixType m_atType;//坐标类型

	int m_nPriceAlertX;//价格提示的最近X位置
	ChartUnit * m_pMainUnit;

	int m_nPriceLines[16];//价格点位，0X7FFFFFFF为无效，最多16个价格线
};
#endif // CHARTUNIT_H
