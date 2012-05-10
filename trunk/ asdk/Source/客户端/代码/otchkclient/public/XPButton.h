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
	int m_nMoveType;//0���ƶ���1�����ƶ���2�����ƶ�
	bool m_bMoving;//�Ƿ����ƶ�
	CPoint m_ptOrg;//�ƶ���ԭ��
	int m_nPopMenuType;//1�����2������,0û��
	int m_nPopMenuID;//�˵�
	
	CMenu * m_pPopMenu;
	bool m_bShowed;//�Ѿ���ʾ����
	
	//��ť����߿�
	CPen m_BoundryPen;
	
	//���ָ�����ڰ�ť֮��ʱ��ť���ڱ߿�
	CPen m_InsideBoundryPenLeft;
	CPen m_InsideBoundryPenRight;
	CPen m_InsideBoundryPenTop;
	CPen m_InsideBoundryPenBottom;
	
	//��ť��ý���ʱ��ť���ڱ߿�
	CPen m_InsideBoundryPenLeftSel;
	CPen m_InsideBoundryPenRightSel;
	CPen m_InsideBoundryPenTopSel;
	CPen m_InsideBoundryPenBottomSel;
	
	//��ť�ĵ�ɫ��������Ч����Ч����״̬
	BOOL	m_bNoDraw;//��Ҫ����
	
	int		m_iBmpPos;//0��ȫͼ��1���Ϸ���2���·�, 3���м�
	int		m_iTextPos;//����λ�ã�0���У�1��ߣ�2�ұ�
	BOOL	m_bBorder;//�Ƿ��б߿�
	BOOL	m_bBMP;//�Ƿ���ͼ�갴ť
	BOOL	m_bBMPFill;//ͼ������������
	unsigned short m_usFillType;// 0 ID,1 HBITMAP
	unsigned short	m_usBMPType;//0 ID,1 HBITMAP,2 BITMAP FILE
	BOOL	m_bBackColor;//�Ƿ�ָ����ɫ
	BOOL	m_bTextColor;
	CBitmap m_Bitmap;//ͼ�갴Ŧ
	CBitmap m_BitmapMouseIn;//����ƶ�������
	bool m_BitmapAttached;
	bool m_BitmapMouseInAttached;

	CBitmap m_BitmapFillActive;//
	CBitmap m_BitmapFillInactive;//

	bool	m_BitmapFillActiveAttached;
	bool	m_BitmapFillInactiveAttached;

	COLORREF m_crBtnBackColor;
	COLORREF m_crTextColor;
	
	//��ť��״̬
	BOOL m_bOver;	//���λ�ڰ�ť֮��ʱ��ֵΪtrue����֮Ϊflase
	BOOL m_bTracking;	//����갴��û���ͷ�ʱ��ֵΪtrue
	BOOL m_bSelected;	//��ť�������Ǹ�ֵΪtrue
	BOOL m_bFocus;	//��ťΪ��ǰ��������ʱ��ֵΪtrue

	BOOL	m_bUnderLine;//�»���

    CToolTipCtrl m_ToolTip;        //��ʾ tip

	bool m_bTitleInRect;//���������ھ�����
	CRect m_rectTitle;//�������

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
