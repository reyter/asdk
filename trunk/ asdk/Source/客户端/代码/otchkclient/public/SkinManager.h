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
const int PRICEUP = 3;					///�۸�����.
const int PRICEDOWN = 4;				///�۸��µ�.
const int PRICENORMAL = 5;				///�۸��ƽ.
const int TRENDVOL = 6;					///�ɽ���.
const int KUP = 7;						///K������.
const int KDOWN = 8;					///K���´�.
const int KNORMAL = 9;					///K��������ɫ.
const int BKCOLOR = 10;					///K�߱�����ɫ.
const int SELCOLOR = 11;
const int TRENDLINE = 12;				///������.
const int TRENDMALINE = 13;				///����MA��.
const int VOLCOLOR = 14;				///�ɽ�����ɫ.
const int STOCKNAMECOLOR = 15;			///��Ʊ������ɫ.
const int STOCKCODECOLOR = 16;			///��Ʊ������ɫ.
const int RIGHTTEXTCOLOR = 17;			///�ұ�������ɫ
const int SAFECOLOR	= 18;				///��ȫɫ
const int DANGERCOLOR = 19;				///Σ��ɫ
const int RIGHTSTOCKCODECOLOR = 20;		///�ұߴ���ɫ
const int RIGHTSTOCKNAMECOLOR = 21;		///�ұ�����ɫ
const int TITLECOLOR = 22;				///ָ��������ɫ
const int RIGHTTIMECOLOR = 23;			///�ұ�ʱ����ɫ.
const int LISTNORMALCOLOR = 24;			///�б�������ɫ.
const int LISTBKCOLOR1 = 25;			///�б�����ɫ1.
const int LISTBKCOLOR2 = 26;			///�б�����ɫ2.
const int LISTNAMECOLOR = 27;			///�б�������ɫ.
const int NEWSLISTHILIGHTCOLOR = 28;			
const int NEWSLISTCOLOR = 29;			///�����б���ɫ.
const int NEWSLISTOVERCOLOR = 30;		///�����б�����ɫ.

const int BTNTEXTCOLOR	= 31;			///��ť������ɫ
const int LISTSELBACK	= 32;

const int CHGSTKBACKCOLOR	= 33;
const int GRAPHBACKCOLOR	= 34;
const int CHGSTKBTNTEXTCOLOR = 35;
const int GRAPHBARBACKCOLOR = 36;
const int CHGSTKBTNSELTEXTCOLOR = 37;

const int INDEX_LINE_COLOR = 38;

const int MANUAL_DRAW_LINE_COLOR = 39;
const int MANUAL_DRAW_TEXT_COLOR = 40;

const int BOLL_MIDS	= 41;				///���ֶ����й�
const int BOLL_MIDL = 42;				///���ֳ����й�

const int EDITBKCOLOR = 43;				///�༭���ɫ
const int BTNSHILIGHTCOLOR = 44;		///�س�ɫ
const int EDITTEXTCOLOR = 45;			///�༭������ɫ

const int MAINTITLECOLOR=46;			///������ɫ
// CSkinManager ����Ŀ��

class CSkinManager : public CObject
{
public:
	CSkinManager();
	virtual ~CSkinManager();

	/**
	*	����Ƥ��.
	*	@param c_strSkinName Ƥ������.
	*/
	void SetSkin(CString c_strSkinName);

	/**
	*	����Ƥ������.
	*	@param nSkinType Ƥ������.
	*/
	void SetSkinType(int nSkinType);

	/**
	*	����Ƥ��.
	*	@param c_pSkinName Ƥ������.
	*/
	bool	LoadSkin(char * c_pSkinName);//װ��

	/**
	*	����Ƥ��BmpͼƬ.
	*/
	bool	LoadSkinBmp();
	HBITMAP LoadCommBmp(unsigned int c_unID);


	/**
	*	��ʼ������.
	*/
	void InitFont();

	/**
	*	��������.
	*/
	void CreateFont();
	
	/**
	*	��ȡBitmap.
	*	@param c_unID ID.
	*/
	HBITMAP GetBitmap(unsigned int c_unID);

	/**
	*	��ȡBmp��С.
	*	@param c_hBmp .
	*
	*/
	CSize GetBmpSize(HBITMAP c_hBmp);
	CSize GetBmpSize(int);


	/**
	*	�������ͼ��.
	*	@param c_hBmp .
	*	@param pDC ��ͼ��DC.
	*	@param rect ���������С.
	*/
	CSize FillRectImage(HBITMAP c_hBmp,CDC *pDC,CRect &rect);
	CSize FillRectImage(CBitmap &bitmap,CDC *pDC,CRect &rect);
	CSize FillRectImage(unsigned int c_unDB,CDC *pDC,CRect &rect);


	/**
	*	������������ͼƬ�������.
	*	@param c_hBmp .
	*	@param pDC ��ͼDC.
	*	@param rect ���������.
	*/
	void StretchIntoRectImage(HBITMAP c_hBmp,CDC *pDC,CRect &rect);
	void StretchIntoRectImage(HBITMAP c_hBmp,CDC *pDC,CRect &rectSrc,CRect &rect);
	void StretchIntoRectImage(CBitmap &bitmap,CDC *pDC,CRect &rect);
	void StretchIntoRectImage(CBitmap &bitmap,CDC *pDC,CRect &rectSrc,CRect &rect);


	/**
	*	�����б��(������ɫ).
	*	@param hDC ��ͼDC.
	*	@param rect ��ͼ����.
	*	@param cl1 ��ɫ1
	*	@param cl2 ��ɫ2.
	*/
	void FillGradient(HDC hDC,CRect rect,COLORREF cl1,COLORREF cl2);
	void FillGradient(HDC hDC,CRect rect,COLORREF cl1,COLORREF cl2,COLORREF cl3);

	void drawSJXUP(CDC * c_pDC,CPoint c_ptPoint,int c_nHeight,int c_nWidth,int c_nRectWidth,COLORREF c_cl);
	void drawSJXDOWN(CDC * c_pDC,CPoint c_ptPoint,int c_nHeight,int c_nWidth,int c_nRectWidth,COLORREF c_cl);
	void drawSJXZERO(CDC * c_pDC,CPoint c_ptPoint,int c_nHeight,int c_nWidth,COLORREF c_cl);
	void drawArrowInRect(CDC *,CRect rect,COLORREF c_cl);

	void DrawWeakStrong(CDC * c_pDC,CRect c_rect,float c_f);

	/**
	*	��ȡ�ߵ���ɫ.
	*	@param c_nIndex ����.
	*/
	COLORREF getLineColor(unsigned int c_nIndex);

	/**
	*	��ȡ��ɫ.
	*/
	COLORREF getColor(int c_nDef);
	HBITMAP getCBFCLogo(){return m_hCBFC;};

	/**
	*	��ȡ����.
	*/
	void GetFonts(HDC);


	/**
	*	�Ƿ���ڸ�����.
	*/
	bool ExistsFont(CString);

	/**
	*	��ȡĬ����������.
	*/
	CString GetDefaultFontName();

	/**
	*	����Ĭ����������.
	*	@param c_strFontNameA ��������.
	*	@param c_strDef Ĭ����Ϣ.
	*/
	void SetDefaultFontName(CString c_strFontNameA,CString c_strDef);

	HBITMAP LoadSpecialBmp(int);
	void DrawLeds(CDC * c_pDC,CRect c_rect,char *c_pLeds);

	/**
	*	��ȡ��Ʊ��ֵ(�۸�)��ɫ.
	*	@param c_pStock ��Ʊ����.
	*	@param c_strName ��Ʊ����.
	*	@param strValue ��ֵ.
	*	@param c_clDef Ĭ����ɫ.
	*/
	COLORREF GetStockValueColor(void * c_pStock,CString c_strName,CString strValue,COLORREF c_clDef);

	/**
	*	������������.
	*/
	void LoadFontConfig();

	/**
	*	���������С����.
	*/
	void SaveFontConfig();

	/**
	*	��ȡ����߶�.
	*	@param c_pFont ����.
	*	@returned int.
	*/
	int GetFontHeight(CFont *c_pFont);
	/**
	*	��ȡ������.
	*	@param c_pFont ����.
	*	@param c_strText �ı�.
	*	@returned int.
	*/
	int GetFontWidth(CFont *c_pFont,CString c_strText);


	/**
	*	��ȡ�б������.
	*	@return CFont ����.
	*/
	CFont * GetListFont(){return m_pQuoteListFont;};

	/**
	*	��ȡ��ť������.
	*	@return CFont ����.
	*/
	CFont * GetButtonFont(){return m_pButtonFont;};

	/**
	*	��ȡ�ı�������.
	*	@return CFont ����.
	*/
	CFont * GetTextFont(){return m_pTextFont;};

	/**
	*	��ȡ�˵�������.
	*	@return CFont ����.
	*/
	CFont * GetMenuFont(){return m_pMenuFont;};

	/**
	*	��ȡͼ�ε�����.
	*	@return CFont ����.
	*/
	CFont * GetGraphFont(){return m_pGraphFont;};
private:
	int			m_nSkinType;					///Ƥ������.
	CString		m_strSkinName;					///Ƥ������
	CString		m_strSkinPath;					///Ƥ��·��
	char		m_acFiles[128][64];
	HBITMAP		m_hBmp[128];
	int			m_nBmpCount;					///BmpͼƬ����.

	HBITMAP		m_hCBFC;						///ʱ��logo

	CString		m_strFontNames[MAX_PATH * 2];	///��������
	CString		m_strDefaultFontName;			///Ĭ����������.

	CFont	*	m_pQuoteListFont;				///�����б�����.
	CFont	*	m_pButtonFont;					///��ť����.
	CFont	*	m_pTextFont;					///��������.
	CFont	*	m_pMenuFont;					///�˵�����.
	CFont	*	m_pGraphFont;					///ͼ������.
public:
	CFont	*	m_pFontGraph;					///����ͼ��.
	CFont	*	m_pFontReport;					///���屨��.
	CFont	*	m_pFontTitle;					///�������.
	CFont	*	m_pFontList;					///�����б�.
	CFont	*	m_pFontSmall;					///������С.
	CFont	*	m_pFontSmallHT;
	CFont	*	m_pFontSmallBold;
	CFont	*	m_pFontBig;						///����Ӵ�.
	CFont	*	m_pFontThick;					///����Ӵ�.
	CFont	*	m_pFontTiny;

	int m_nQuoteListFontSize;					///��Ʊ�����б�����	
	int m_nButtonFontSize;						///��ť����
	int m_nMenuFontSize;						///�˵�����
	int m_nGraphFontSize;						///ͼ������
	int m_nTextFontSize;						///ͼ������
};


