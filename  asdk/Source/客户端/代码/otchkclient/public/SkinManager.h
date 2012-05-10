#pragma once
#define DEFAULT_LINE_1_COLOR	0xFFFFFF
#define DEFAULT_LINE_2_COLOR	RGB(240,247,253)
#define DEFAULT_LINE_3_COLOR	RGB(238,240,245)

#define ID_L_R_B_LED			0
#define ID_L_Y_B_LED			1
#define ID_L_G_B_LED			2
#define ID_M_R_B_LED			3
#define ID_M_Y_B_LED			4
#define ID_M_G_B_LED			5
#define ID_R_R_B_LED			6
#define ID_R_Y_B_LED			7
#define ID_R_G_B_LED			8

#define ID_L_R_S_LED			9
#define ID_L_Y_S_LED			10
#define ID_L_G_S_LED			11
#define ID_M_R_S_LED			12
#define ID_M_Y_S_LED			13
#define ID_M_G_S_LED			14
#define ID_R_R_S_LED			15
#define ID_R_Y_S_LED			16
#define ID_R_G_S_LED			17

#define ID_DIAGNOSE_UP_LED		18
#define ID_DIAGNOSE_NORMAL_LED	19
#define ID_DIAGNOSE_DOWN_LED	20
#define ID_DIAGNOSE_LEFT_BACK	21
#define ID_DIAGNOSE_WDJ			22
#define ID_DIAGNOSE_WDJ_RED		23

#define ID_DRAG_BACK			24
#define ID_HEAD_LEFT			25
#define ID_HEAD_BACK			26
#define ID_HEAD_RIGHT			27
#define ID_HEAD_MIN				28
#define ID_HEAD_MIN_CHANGE		29
#define ID_HEAD_MAX				30
#define ID_HEAD_MAX_CHANGE		31
#define ID_HEAD_CLOSE			32
#define ID_HEAD_CLOSE_CHANGE	33
#define ID_INDEX_HEAD_BACK		34
#define ID_INDEX_LIST_BACK		35
#define ID_INDEX_ARROW_UP		36
#define ID_INDEX_ARROW_DOWN		37

#define ID_NEWS_LIST_BACK		38
#define ID_LEFT_HEAD_SEL		40
#define ID_LEFT_HEAD_SEL_CHG	39
#define ID_LEFT_HEAD_UNDERLINE	41
#define ID_MEMO_LIST_BACK		42
#define ID_GROUP_LIST_BACK		43
#define ID_LEFT_GROUP_BACK		44
#define ID_LEFT_SEL_BACK		45
#define ID_ALL_BACK				46
#define ID_GROUP_HEAD_BACK		47
#define ID_RIGHT_HEAD_BACK		48
#define ID_HEAD_STOCK_DIAGNOSE	49
#define ID_HEAD_MARKET_QS		50
#define ID_HEAD_BDL				51
#define ID_RB_HEAD_BACK			52
#define ID_CLOSE_LITTLE			53
#define ID_CLOSE_LITTLE_CHG		54
#define ID_MAX_LITTLE			55
#define ID_MAX_LITTLE_CHG		56
#define ID_MIN_LITTLE			57
#define ID_MIN_LITTLE_CHG		58
#define ID_RB_TITLE_BACK		59
#define ID_RB_TITLE_NOSEL_BACK	60
#define ID_RB_UNDER_TITLE_BACK	61
#define ID_RB_UNDER_BTN_BACK	62
#define ID_SUN					63
#define ID_YIN					64
#define ID_CLOUD				65
#define ID_RAIN					66
#define ID_CHG					67
#define ID_CHG_SELECT			68
#define ID_RB_ITEM_CLOSE		69
#define ID_RB_ITEM_CLOSE_CHANGE	70

#define ID_RB_TITLE_BACKC		71
#define ID_RB_TITLE_NOSEL_BACKC	72

#define ID_PJ_NOW_ARROW			73
#define ID_PJ_LAST_ARROW		74

#define ID_GRAPH_BACK			75
#define ID_ONE_WIN				76
#define ID_TWO_WIN				77

#define ID_GRAPH_JBM			78
#define ID_GRAPH_JG				79
#define ID_GRAPH_JSM			80
#define ID_GRAPH_HEAD_BACK		81
#define ID_GRAPH_WDJ			82
#define ID_GRAPH_WDJ_BACK		83
#define ID_GO_UP				84
#define ID_GO_ZERO				85
#define ID_GO_DOWN				86
#define ID_DRAG_VERT_BACK		87

#define H_THUMB					88
#define H_BACK					89
#define	V_THUMB					90
#define V_BACK					91
#define V_UP					92
#define V_DOWN					93
#define H_RIGHT					94
#define H_LEFT					95

#define ID_SIZE_LEFT			96
#define ID_SIZE_RIGHT			97

#define ID_WATCHLIST			98

#define ID_WAIT_DATA1			129
#define ID_WAIT_DATA2			130
#define ID_WAIT_DATA3			131
#define ID_LOG_HEAD				132
#define ID_LOG_GG				133
#define ID_LOG_BODY				134

#define ID_REG_1				135
#define ID_REG_2				136
#define ID_REG_3				137
#define ID_UPGRADE_BK			138
#define ID_FORGET_PASS			139

const int AIXLINE = 1;
const int AIXTEXT = 2;
const int PRICEUP = 3;					///价格上扬.
const int PRICEDOWN = 4;				///价格下跌.
const int PRICENORMAL = 5;				///价格持平.
const int TRENDVOL = 6;					///成交量.
const int KUP = 7;						///K线上扬.
const int KDOWN = 8;					///K线下挫.
const int KNORMAL = 9;					///K线正常颜色.
const int BKCOLOR = 10;					///K线背景颜色.
const int SELCOLOR = 11;
const int TRENDLINE = 12;				///交易线.
const int TRENDMALINE = 13;				///交易MA线.
const int VOLCOLOR = 14;				///成交量颜色.
const int STOCKNAMECOLOR = 15;			///股票名字颜色.
const int STOCKCODECOLOR = 16;			///股票代码颜色.
const int RIGHTTEXTCOLOR = 17;			///右边文字颜色
const int SAFECOLOR	= 18;				///安全色
const int DANGERCOLOR = 19;				///危险色
const int RIGHTSTOCKCODECOLOR = 20;		///右边代码色
const int RIGHTSTOCKNAMECOLOR = 21;		///右边名称色
const int TITLECOLOR = 22;				///指标名称颜色
const int RIGHTTIMECOLOR = 23;			///右边时间颜色.
const int LISTNORMALCOLOR = 24;			///列表正常颜色.
const int LISTBKCOLOR1 = 25;			///列表背景颜色1.
const int LISTBKCOLOR2 = 26;			///列表背景颜色2.
const int LISTNAMECOLOR = 27;			///列表名称颜色.
const int NEWSLISTHILIGHTCOLOR = 28;			
const int NEWSLISTCOLOR = 29;			///新闻列表颜色.
const int NEWSLISTOVERCOLOR = 30;		///新闻列表覆盖颜色.

const int BTNTEXTCOLOR	= 31;			///按钮字体颜色
const int LISTSELBACK	= 32;

const int CHGSTKBACKCOLOR	= 33;
const int GRAPHBACKCOLOR	= 34;
const int CHGSTKBTNTEXTCOLOR = 35;
const int GRAPHBARBACKCOLOR = 36;
const int CHGSTKBTNSELTEXTCOLOR = 37;

const int INDEX_LINE_COLOR = 38;

const int MANUAL_DRAW_LINE_COLOR = 39;
const int MANUAL_DRAW_TEXT_COLOR = 40;

const int BOLL_MIDS	= 41;				///布林短期中轨
const int BOLL_MIDL = 42;				///不林长期中轨

const int EDITBKCOLOR = 43;				///编辑框底色
const int BTNSHILIGHTCOLOR = 44;		///特出色
const int EDITTEXTCOLOR = 45;			///编辑框字体色

const int MAINTITLECOLOR=46;			///标题字色
// CSkinManager 命令目标

class CSkinManager : public CObject
{
public:
	CSkinManager();
	virtual ~CSkinManager();

	/**
	*	设置皮肤.
	*	@param c_strSkinName 皮肤名称.
	*/
	void SetSkin(CString c_strSkinName);

	/**
	*	设置皮肤类型.
	*	@param nSkinType 皮肤类型.
	*/
	void SetSkinType(int nSkinType);

	/**
	*	加载皮肤.
	*	@param c_pSkinName 皮肤名称.
	*/
	bool	LoadSkin(char * c_pSkinName);//装载

	/**
	*	加载皮肤Bmp图片.
	*/
	bool	LoadSkinBmp();
	HBITMAP LoadCommBmp(unsigned int c_unID);


	/**
	*	初始化字体.
	*/
	void InitFont();

	/**
	*	创建字体.
	*/
	void CreateFont();
	
	/**
	*	获取Bitmap.
	*	@param c_unID ID.
	*/
	HBITMAP GetBitmap(unsigned int c_unID);

	/**
	*	获取Bmp大小.
	*	@param c_hBmp .
	*
	*/
	CSize GetBmpSize(HBITMAP c_hBmp);
	CSize GetBmpSize(int);


	/**
	*	填充区域图像.
	*	@param c_hBmp .
	*	@param pDC 画图的DC.
	*	@param rect 填充的区域大小.
	*/
	CSize FillRectImage(HBITMAP c_hBmp,CDC *pDC,CRect &rect);
	CSize FillRectImage(CBitmap &bitmap,CDC *pDC,CRect &rect);
	CSize FillRectImage(unsigned int c_unDB,CDC *pDC,CRect &rect);


	/**
	*	在区域里拉伸图片进行填充.
	*	@param c_hBmp .
	*	@param pDC 画图DC.
	*	@param rect 拉伸的区域.
	*/
	void StretchIntoRectImage(HBITMAP c_hBmp,CDC *pDC,CRect &rect);
	void StretchIntoRectImage(HBITMAP c_hBmp,CDC *pDC,CRect &rectSrc,CRect &rect);
	void StretchIntoRectImage(CBitmap &bitmap,CDC *pDC,CRect &rect);
	void StretchIntoRectImage(CBitmap &bitmap,CDC *pDC,CRect &rectSrc,CRect &rect);


	/**
	*	填充倾斜度(渐变颜色).
	*	@param hDC 画图DC.
	*	@param rect 画图区域.
	*	@param cl1 颜色1
	*	@param cl2 颜色2.
	*/
	void FillGradient(HDC hDC,CRect rect,COLORREF cl1,COLORREF cl2);
	void FillGradient(HDC hDC,CRect rect,COLORREF cl1,COLORREF cl2,COLORREF cl3);

	void drawSJXUP(CDC * c_pDC,CPoint c_ptPoint,int c_nHeight,int c_nWidth,int c_nRectWidth,COLORREF c_cl);
	void drawSJXDOWN(CDC * c_pDC,CPoint c_ptPoint,int c_nHeight,int c_nWidth,int c_nRectWidth,COLORREF c_cl);
	void drawSJXZERO(CDC * c_pDC,CPoint c_ptPoint,int c_nHeight,int c_nWidth,COLORREF c_cl);
	void drawArrowInRect(CDC *,CRect rect,COLORREF c_cl);

	void DrawWeakStrong(CDC * c_pDC,CRect c_rect,float c_f);

	/**
	*	获取线的颜色.
	*	@param c_nIndex 索引.
	*/
	COLORREF getLineColor(unsigned int c_nIndex);

	/**
	*	获取颜色.
	*/
	COLORREF getColor(int c_nDef);
	HBITMAP getCBFCLogo(){return m_hCBFC;};

	/**
	*	获取字体.
	*/
	void GetFonts(HDC);


	/**
	*	是否存在该字体.
	*/
	bool ExistsFont(CString);

	/**
	*	获取默认字体名称.
	*/
	CString GetDefaultFontName();

	/**
	*	设置默认字体名称.
	*	@param c_strFontNameA 字体名称.
	*	@param c_strDef 默认信息.
	*/
	void SetDefaultFontName(CString c_strFontNameA,CString c_strDef);

	HBITMAP LoadSpecialBmp(int);
	void DrawLeds(CDC * c_pDC,CRect c_rect,char *c_pLeds);

	/**
	*	获取股票价值(价格)颜色.
	*	@param c_pStock 股票代码.
	*	@param c_strName 股票名称.
	*	@param strValue 价值.
	*	@param c_clDef 默认颜色.
	*/
	COLORREF GetStockValueColor(void * c_pStock,CString c_strName,CString strValue,COLORREF c_clDef);

	/**
	*	加载字体设置.
	*/
	void LoadFontConfig();

	/**
	*	保存字体大小设置.
	*/
	void SaveFontConfig();

	/**
	*	获取字体高度.
	*	@param c_pFont 字体.
	*	@returned int.
	*/
	int GetFontHeight(CFont *c_pFont);
	/**
	*	获取字体宽度.
	*	@param c_pFont 字体.
	*	@param c_strText 文本.
	*	@returned int.
	*/
	int GetFontWidth(CFont *c_pFont,CString c_strText);


	/**
	*	获取列表的字体.
	*	@return CFont 字体.
	*/
	CFont * GetListFont(){return m_pQuoteListFont;};

	/**
	*	获取按钮的字体.
	*	@return CFont 字体.
	*/
	CFont * GetButtonFont(){return m_pButtonFont;};

	/**
	*	获取文本的字体.
	*	@return CFont 字体.
	*/
	CFont * GetTextFont(){return m_pTextFont;};

	/**
	*	获取菜单的字体.
	*	@return CFont 字体.
	*/
	CFont * GetMenuFont(){return m_pMenuFont;};

	/**
	*	获取图形的字体.
	*	@return CFont 字体.
	*/
	CFont * GetGraphFont(){return m_pGraphFont;};
private:
	int			m_nSkinType;					///皮肤类型.
	CString		m_strSkinName;					///皮肤名称
	CString		m_strSkinPath;					///皮肤路径
	char		m_acFiles[128][64];
	HBITMAP		m_hBmp[128];
	int			m_nBmpCount;					///Bmp图片计数.

	HBITMAP		m_hCBFC;						///时报logo

	CString		m_strFontNames[MAX_PATH * 2];	///字体名称
	CString		m_strDefaultFontName;			///默认字体名称.

	CFont	*	m_pQuoteListFont;				///报价列表字体.
	CFont	*	m_pButtonFont;					///按钮字体.
	CFont	*	m_pTextFont;					///文字字体.
	CFont	*	m_pMenuFont;					///菜单字体.
	CFont	*	m_pGraphFont;					///图形字体.
public:
	CFont	*	m_pFontGraph;					///字体图形.
	CFont	*	m_pFontReport;					///字体报告.
	CFont	*	m_pFontTitle;					///字体标题.
	CFont	*	m_pFontList;					///字体列表.
	CFont	*	m_pFontSmall;					///字体缩小.
	CFont	*	m_pFontSmallHT;
	CFont	*	m_pFontSmallBold;
	CFont	*	m_pFontBig;						///字体加大.
	CFont	*	m_pFontThick;					///字体加粗.
	CFont	*	m_pFontTiny;

	int m_nQuoteListFontSize;					///股票行情列表字体	
	int m_nButtonFontSize;						///按钮字体
	int m_nMenuFontSize;						///菜单字体
	int m_nGraphFontSize;						///图形字体
	int m_nTextFontSize;						///图形字体
};


