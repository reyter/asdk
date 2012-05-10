#if !defined(AFX_CUSTOMMENU_H__3AF0EF07_A6CE_47D9_8840_A15350F03607__INCLUDED_)
#define AFX_CUSTOMMENU_H__3AF0EF07_A6CE_47D9_8840_A15350F03607__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomMenu.h : header file
//

#define MAXLIST 1024
#define HEIGHT 28
#define WIDTH  120
/////////////////////////////////////////////////////////////////////////////
// CCustomMenu window

typedef struct
{
	CString m_Text;
	UINT m_MenuID;
	UINT m_Icon;
}MenuItemInfo;
//m_MenuID -2:顶层菜单条 -1:弹出菜单 0:分隔条 >0:一般的菜单
//注意顶层菜单条和弹出菜单的区别

class CCustomMenu : public CMenu
{
// Construction
public:
	CCustomMenu();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomMenu)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetMenuImageList(CImageList *pImageList);
	void DrawMenuIcon(CDC *m_dc,CRect m_rect,UINT IconIndex);
	void DrawItemText(CDC *m_dc,CString str,CRect m_rect,BOOL m_Com,
		BOOL bGray,BOOL bTop);
	void DrawTopMenu(CDC *m_dc,CRect m_rect,BOOL bSelect);
	void DrawComMenu(CDC* m_dc,CRect m_rect,BOOL bSelect,BOOL bGray);
	void DrawSeparate(CDC *m_dc,CRect m_rect);
	MenuItemInfo m_MenuInfoList[MAXLIST];
	UINT m_Index;//用于m_MenuInfoList
	UINT m_IconIndex;
	CImageList *pImageList;
	BOOL ChangeMenuItem(CMenu *m_Menu, BOOL bTop);
	virtual ~CCustomMenu();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCustomMenu)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMMENU_H__3AF0EF07_A6CE_47D9_8840_A15350F03607__INCLUDED_)
