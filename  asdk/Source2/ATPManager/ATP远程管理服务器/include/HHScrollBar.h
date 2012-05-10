#pragma once

#define WM_HHHSCROLL	WM_USER+480
#define WM_HHVSCROLL	WM_USER+481

struct HHFC_HHSCROLLCOLORSET
{
	int      nScrollType;
	COLORREF colorBorder;
	COLORREF colorArrow[2];
	COLORREF colorScroll[2];
	COLORREF colorPosBar[3][2];
	int		 nSize;
	void Init()
	{
		nScrollType=-1;
		colorBorder=RGB(96,96,96);
		colorArrow[0]=colorArrow[1]=RGB(0,0,0);
		colorScroll[0]=RGB(200,200,200);
		colorScroll[1]=RGB(255,255,255);
		colorPosBar[0][0]=RGB(200,200,200); colorPosBar[0][1]=RGB(255,255,255);
		colorPosBar[1][0]=RGB(140,140,140); colorPosBar[1][1]=RGB(190,190,190);
		colorPosBar[2][0]=RGB(160,160,160);	colorPosBar[2][1]=RGB(255,255,255);
		nSize=17;
	}
};

// CHHScrollBar
class AFX_EXT_CLASS CHHScrollBar : public CWnd
{
	DECLARE_DYNCREATE(CHHScrollBar)
public:
	int m_dwStyle;
	int m_nID;
	SCROLLINFO m_ScrollInfo;

	RECT m_rectArrow[2];
	RECT m_rectPosBar;
	RECT m_rectScroll;

	HHFC_HHSCROLLCOLORSET m_colorSet;

	int m_nSelectButton;
	int m_nOperateButton;
	BOOL m_bRButtonDown;
	POINT m_ptOffset;
	int   m_nPosOffset;
// Constructors
public:
	CHHScrollBar();
	virtual ~CHHScrollBar();
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

// Attributes
	int GetScrollPos();
	int SetScrollPos(int nPos, BOOL bRedraw = TRUE);
	void GetScrollRange(LPINT lpMinPos, LPINT lpMaxPos);
	void SetScrollRange(int nMinPos, int nMaxPos, BOOL bRedraw = TRUE);
	void ShowScrollBar(BOOL bShow = TRUE);

	BOOL EnableScrollBar(UINT nArrowFlags = ESB_ENABLE_BOTH);

	BOOL SetScrollInfo(LPSCROLLINFO lpScrollInfo, BOOL bRedraw = TRUE);
	BOOL GetScrollInfo(LPSCROLLINFO lpScrollInfo, UINT nMask = SIF_ALL);
	int  GetScrollLimit();

	void SetHHScrollDrawStyle(int nDrawStyle);
	void SetHHScrollColorSet(HHFC_HHSCROLLCOLORSET *pcolorSet);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnTimer(UINT nIDEvent);

	void TrackScroll(int nOperateButton);

protected:
	void CalcPos();
	void DrawHHScrollBar(CDC *pDC);
	void DrawHHScrollBarDraw(CDC *pDC);
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDoHHScrollCommand(UINT nID);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void Print(CDC *pDC, int nOffsetX=-9999, int nOffsetY=-9999);
};
