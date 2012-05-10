/************************************************************************/
/* 画图窗口                                                                     */
/************************************************************************/



#pragma once
#include "chartunit.h"
#include "../public/CustomMenu.h"

#define MAX_TIPS_LEN 2048

#define PIC_TREND	_T("分时走势")
#define PIC_KLINE	_T("K线")
#define PIC_HISKDAY	_T("日线")
#define PIC_HISKWEK	_T("周线")
#define PIC_HISKMTH	_T("月线")
#define PIC_TREN_VOL	_T("VOLUME")
#define PIC_HISK_VOL	_T("VOLUME")
#define PIC_MACD			_T("MACD")
#define PIC_KDJ				_T("KDJ")
#define PIC_RSI				_T("RSI")
#define PIC_BOLL			_T("BOLL")
#define PIC_EMA				_T("EMA")
#define PIC_MA				_T("MA")
#define PIC_MMA				_T("MMA")
#define PIC_TDMA			_T("TDMA")

#define PRICE_MBJ			1
#define PRICE_HL			2
#define PRICE_IPO			3
#define PRICE_JZC			4
#define PRICE_ZFJ			5
#define PRICE_PGJ			6
#define PRICE_NBJYJ			7

class Charts;
typedef enum {PTTREND=0,PTHISK} PicType;
class CPics;
class CDlgDiagnose;
class CPicWnd : public CWnd
{
	DECLARE_DYNAMIC(CPicWnd)

public:
	CPicWnd(PicType c_ptType,CPics * c_pPics,CDlgDiagnose *);
	virtual ~CPicWnd();

protected:
	//{{AFX_MSG(CPicWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void setPicType(PicType c_ptType);
	PicType getPicType();
	void getZoom(int c_nZoom,int &c_nWidth,int &c_nSpace);	
	void setStockCode(CString c_strStockCode);
	void setMousePos(int c_x, int c_y);
	void getMousePos(int &c_x, int &c_y);
	void setCursorAway();
	int getXPos(int c_nX);
	void paintMe(CDC * c_pDC);
	void drawTitle(CDC * c_pDC);
	void drawRefer(CDC * c_pDC);
	void drawMouseLine(CDC * c_pDC);
	void drawMoveRect(CDC * c_pDC);
	void drawDetail(CDC * c_pDC);
	void drawKLineDetail(CDC *,KLINE *);
	void drawMinUnitDetail(CDC *,MinUnit *,int,bool c_bIndex);
	void resetSize();
	void onSizeChange(int c_nPointBegin=0);
	void resetViewTrendPoints();
	void resetViewHiskPoints(int c_nPointBegin=0);
	void setChartsViewPoints();
	void setBeginEndPos(int c_nWay,int c_nStep);
	void calcChartsMaxMinValue();
	void setZoom(int c_nZoom,int c_nPointBegin=-1);
	void resetZoom();
	void goUp(int c_nPointBegin=-1);
	void goDown();
	void goLeft();
	void goRight();
	Charts * isMouseInCharts(CPoint c_point);
	Charts * setChartsSelected(CPoint c_point);
	Charts * getChartsSelected();
	CString GetPointInChartsTitle(CPoint c_point);
	//隐藏或者显示图形
	void HideOrShowCharts(int c_nIndex);
	//显示或者隐藏细节窗口
	void SetMouseLineOn(bool);

	//void setKLines(int c_nCount, int *c_pParams,Charts * c_pCharts=NULL);
	void setKLines(Charts * c_pCharts=NULL);


	/**
	*	@设置MACD指标.
	*	@param c_nCount 计数.
	*	@param c_pParams 参数.
	*/
	void setMACD(int c_nCount, int * c_pParams);

	/**
	*	@设置KDJ指标.
	*	@param c_nCount 计数.
	*	@param c_pParams 参数.
	*/
	void setKDJ(int c_nCount, int * c_pParams);
	
	/**
	*	@设置RSI指标.
	*	@param c_nCount 计数.
	*	@param c_pParams 参数.
	*/
	void setRSI(int c_nCount, int * c_pParams);
	
	/**
	*	@设置BOLL指标.
	*	@param c_nCount 计数.
	*	@param c_pParams 参数.
	*/
	void setBOLL(int c_nCount, int * c_pParams);
	
	/**
	*	@添加BOLL指标.
	*	@param c_nCount 计数.
	*	@param c_pParams 参数.
	*/
	void addBOLL(int c_nCount, int * c_pParams);
	
	/**
	*	@
	*	@param
	*/
	void addBOLL2(Charts *);
	
	/**
	*	@添加EMA指标.
	*	@param c_nCount 计数.
	*	@param c_pParams 参数.
	*/
	void addEMA(int c_nCount, int * c_pParams);
	
	/**
	*	@设置成交量线.
	*	@param c_nCount 计数.
	*	@param c_pParams 参数.
	*/
	void setVolLines(int c_nCount, int *c_pParams);
	
	/**
	*	@设置趋势线.
	*	@param c_pCharts
	*/
	void setTrendLine(Charts * c_pCharts = NULL);
	
	/**
	*	@设置交易量.
	*	@param c_pCharts 
	*/
	void setTrendVol(Charts * c_pCharts = NULL);
	
	/**
	*	@创建图.
	*/
	void createPic();
	
	/**
	*	@创建最小图.
	*	@param
	*/
	void createMinPic();	
	
	/**
	*	@
	*	@param
	*/
	void createHiskPic();
	
	/**
	*	@获取报告.
	*	@param c_bWait 是否等待.
	*/
	void GetReport(bool c_bWait);

	/**
	*	@刷新数据.
	*/
	void FreshData();

	/**
	*	@获取图片数据.
	*/
	void getPicData();		
	void createFutureKLine();//创建后续的K线

	/**
	*	@改变图像.
	*	@param c_ptType 
	*	@param c_usCycle
	*/
	void changePic(PicType c_ptType,unsigned short c_usCycle);
	void resetPic();//重新设置图形，数据发生了变化
	void KeyOperate(UINT nChar);

	void setCurPos(int c_nPos,int c_nPosTime);


	void getMouseString(CPoint);
	void resetMouseString();


	Charts * GetChartsByUnitType(ChartUnitType c_type);
	ChartUnitType GetChartsUnitType();
	Charts * GetChartsByTitle(CString c_strTitle);
	int GetSizeCharts(CPoint c_point);
	void DrawSizeLine(CRect,CPoint);
	void SizeRects(CPoint c_point);
	void InitMinData();
	void SetMinData(char * c_pBuf,int c_nLen);
	bool RemoveTechPic(CString);
	void DoMenuAction(CString c_strTech);
	void OnKdj();
	void OnRsi();
	void OnBoll();
	void OnAddBoll();
	void OnAddEMA();

	void resetLineColor();

	void InitStaticData(SStock *);
	//更换指标
	void ChangeTech(Charts * c_pCharts,CString c_strTech);
	//保存当前指标设置
	void SaveCurTechSet();
	bool IsExistsTech(CString c_strTech);

	//格式化分钟线
	void FormatMinKData();	
	//
	void LogA(char * c_pBuf);

	int GetNextMinute(unsigned short m_usCycle,int c_nMinute);//取下一个分钟
	int	GetNextDay(int c_nDay);//取下一个交易日
	int	GetNextWeek(int c_nDay);//取下一个交易周
	int	GetNextMonth(int c_nDay);//取下一个交易月

	void ResetFutrueItem(int c_nWay);//放大或者缩小右边的空白
public:
	PicType m_ptType;//图形类型
	
	unsigned short m_usCycle;
	int m_nCurPos;//定位
	int m_nCurPosTime;//定位时间
	int m_nMousePos;//鼠标位置
	int m_nMouseX,m_nMouseY;
	CPics * m_pPics;
	CDlgDiagnose * m_pDiagnose;//诊断窗口
	
	int m_nStockId;
	CString m_strStockCode;
	CString m_strStockName;

	CString m_strAddStockCode;

	CRect m_rectDraw;
    CRect m_rectAix;
	CRect m_rectMainPic;//主图区域

	CRect m_rectTech;
	int m_nTechButtonCount;

    int m_nLeftDis,m_nRightDis,m_nTopDis,m_nBottomDis;

	RWLock m_lockPics;
	std::vector<Charts *> m_listPics;

    int *m_pnHoriPoint;
    int m_nHoriPointCount;
	int m_nMaxViewPointCount;//最多显示点
    int m_nPointBegin;//开始点	
	int m_nPointBeginTime;//开始点时间
	int m_nLockPointEnd;//锁定结束点	
    int m_nPointViewCount;//显示点数量
    int m_nZoom;//
	bool m_bDrawMouseLine;

	int m_nTailSpaceItems;//右侧留白单元
	int m_nFutrueItems;//右恻后续时间单元
	bool m_bDrawMainTechLine;//显示主图指标
	CFont *m_pTextFont;

	CString m_strMouseX;
	CString m_strMouseY;
	
	int m_nMinMaxItem;
	MinUnit * m_pMinData;
	int m_nMinItemCount;

	int  m_nKDataMaxLen;//K线最大长度
	char * m_pKData;//K线数据
	int	   m_nKItemCount;//K线数量
	int		m_nMinFreshBegin;//开始更新位置

	bool	m_bHISKEMA;//均线
	bool	m_bHISKBOLL;//boll通道

	//CXPButton * m_pSetWin;
	CRect m_rectSetWin;
	CRect m_rectPriceAlert;
	CRect m_rectCutLine;
	CRect m_rectTradeArea;
	CRect m_rectTools;
	bool m_bSizeRect;//改变
	int m_nSizeRect;//改变的图形
	CPoint m_pointSizeBegin;//开始点
	CPoint m_pointSizeLast;//上一个点
	
	CPoint m_pointMoveSet;//鼠标移动起点
	CPoint m_pointMoveSeek;//鼠标移动点

	bool m_bInGetReport;		
		
	WCHAR m_wcTips[MAX_TIPS_LEN + 1];

	AixType m_atCur;//当前坐标
	CCustomMenu m_menu;	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnMonk();
	afx_msg void OnWeekk();
	afx_msg void OnDayk();
	afx_msg void OnRealmin();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAddStock();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTechDesc();
public:
	afx_msg void OnMacd();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnParamSet();
	afx_msg void OnSelectTech();
	afx_msg void OnSetTechParam();
	afx_msg void OnMin1k();
	afx_msg void OnMin5k();
	afx_msg void OnMin15k();
	afx_msg void OnMin30k();
	afx_msg void OnMin60k();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);	
	afx_msg void OnShowHideMainTech();
	afx_msg void OnAixNormal();
	afx_msg void OnAixLg();
	afx_msg void OnWeightFront();
	afx_msg void OnWeightNone();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
};


