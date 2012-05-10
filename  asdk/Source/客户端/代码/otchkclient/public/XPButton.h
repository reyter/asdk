#if !defined(AFX_XPBUTTON_H__44CD5B2A_756E_4939_9261_E0034E0F2DEF__INCLUDED_)
#define AFX_XPBUTTON_H__44CD5B2A_756E_4939_9261_E0034E0F2DEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XPButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXPButton window
typedef void (*_CheckMenu)(void *,CMenu * c_pMenu);
typedef bool (*_BtnMove)(void *,void *,int,bool);

class CXPButton : public CButton
{
// Construction
public:
	CXPButton();

	// Attributes
	_CheckMenu m_pCheckMenu;
	void * m_pMenuData;
	_BtnMove m_pBtnMove;
	void * m_pBtnMoveData;
protected:
	int m_nMoveType;//0不移动，1上下移动，2左右移动
	bool m_bMoving;//是否在移动
	CPoint m_ptOrg;//移动的原点
	int m_nPopMenuType;//1点击，2鼠标进入,0没有
	int m_nPopMenuID;//菜单
	
	CMenu * m_pPopMenu;
	bool m_bShowed;//已经显示过了
	
	//按钮的外边框
	CPen m_BoundryPen;
	
	//鼠标指针置于按钮之上时按钮的内边框
	CPen m_InsideBoundryPenLeft;
	CPen m_InsideBoundryPenRight;
	CPen m_InsideBoundryPenTop;
	CPen m_InsideBoundryPenBottom;
	
	//按钮获得焦点时按钮的内边框
	CPen m_InsideBoundryPenLeftSel;
	CPen m_InsideBoundryPenRightSel;
	CPen m_InsideBoundryPenTopSel;
	CPen m_InsideBoundryPenBottomSel;
	
	//按钮的底色，包括有效和无效两种状态
	BOOL	m_bNoDraw;//不要绘制
	
	int		m_iBmpPos;//0，全图，1在上方，2在下方, 3在中间
	int		m_iTextPos;//文字位置，0居中，1左边，2右边
	BOOL	m_bBorder;//是否有边框
	BOOL	m_bBMP;//是否是图标按钮
	BOOL	m_bBMPFill;//图形是用来填充的
	unsigned short m_usFillType;// 0 ID,1 HBITMAP
	unsigned short	m_usBMPType;//0 ID,1 HBITMAP,2 BITMAP FILE
	BOOL	m_bBackColor;//是否指定底色
	BOOL	m_bTextColor;
	CBitmap m_Bitmap;//图标按纽
	CBitmap m_BitmapMouseIn;//光标移动到上面
	bool m_BitmapAttached;
	bool m_BitmapMouseInAttached;

	CBitmap m_BitmapFillActive;//
	CBitmap m_BitmapFillInactive;//

	bool	m_BitmapFillActiveAttached;
	bool	m_BitmapFillInactiveAttached;

	COLORREF m_crBtnBackColor;
	COLORREF m_crTextColor;
	
	//按钮的状态
	BOOL m_bOver;	//鼠标位于按钮之上时该值为true，反之为flase
	BOOL m_bTracking;	//在鼠标按下没有释放时该值为true
	BOOL m_bSelected;	//按钮被按下是该值为true
	BOOL m_bFocus;	//按钮为当前焦点所在时该值为true

	BOOL	m_bUnderLine;//下划线

    CToolTipCtrl m_ToolTip;        //提示 tip

	bool m_bTitleInRect;//标题限制在矩形中
	CRect m_rectTitle;//标题矩形

	HCURSOR m_hUserCursor;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXPButton)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void DoGradientFill(CDC *pDC, CRect* rect);
	virtual void DrawInsideBorder(CDC *pDC, CRect* rect);
	virtual void SetBtnBackColor(COLORREF crBk);
	virtual COLORREF GetBtnBackColor();
	virtual void SetTextColor(COLORREF crBk);
	virtual void SetBtnBMP(unsigned int c_UID,unsigned int c_UIDMouseIn);
	virtual void SetBtnBMP(HBITMAP c_hNormal,HBITMAP c_hMouseIn);
	virtual void SetBtnBMP(char * c_pNormalName,char * c_pMouseInName);
	virtual void SetBorder(BOOL c_b);
	virtual BOOL SetNoDraw(BOOL c_bNoDraw);
	virtual BOOL SetBMPFill(BOOL c_bBMPFill,HBITMAP c_hFillActive, HBITMAP c_hFillInactive);
	virtual BOOL SetBMPFill(BOOL c_bFill,unsigned int c_unFillActive,unsigned int c_unFillInactive);
	virtual void SetBmpPos(int c_iPos,int c_iTextPos=0);
	virtual void SetUnderLine(BOOL c_b);
	virtual void SetTitleInRect(bool,CRect);
	virtual ~CXPButton();
	void SetUserCursor(HCURSOR);
	// Generated message map functions
protected:
	//{{AFX_MSG(CXPButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
    
	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void FillRectImage(CBitmap &bitmap,CDC *pDC,CRect &rect);    

protected:
    void InitToolTip();
public:
    void SetToolTipText(CString* spText, BOOL bActivate = TRUE);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetPopMenu(int c_nType,int c_nID);
	void ShowPopMenu();
	void SetMoveType(int c_nMoveType);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XPBUTTON_H__44CD5B2A_756E_4939_9261_E0034E0F2DEF__INCLUDED_)
