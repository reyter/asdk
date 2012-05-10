/************************************************************************/
/* Created by MARIUS BANCILA                                            
/*            www.mariusbancila.ro                                      
/* Copyright (C) 2008 MARIUS BANCILA. All rights reserved.              
/*                                                                      
/* Permission is given by the author to freely redistribute and 
/* include this code in any program as long as this credit is 
/* given where due.
/*
/* CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, 
/* WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
/* INCLUDING, WITHOUT LIMITATION, WARRANTIES THAT THE CODE 
/* IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
/* OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND 
/* PERFORMANCE OF THE CODE IS WITH YOU. SHOULD ANY 
/* CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT THE INITIAL 
/* DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY 
/* NECESSARY SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF 
/* WARRANTY CONSTITUTES AN ESSENTIAL PART OF THIS LICENSE. NO USE 
/* OF ANY CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
/* THIS DISCLAIMER.
/*
/************************************************************************/



#pragma once


// CSymbolEdit

class CSymbolEdit : public CEdit
{
	DECLARE_DYNAMIC(CSymbolEdit)

   CFont m_fontPrompt;
   HICON m_hSymbolIcon;
   bool m_bInternalIcon;
   CString m_strPromptText;
   COLORREF m_colorPromptText;
   COLORREF m_colorBack;

   CRect m_rectEdit;
   BOOL m_bBMP;
   CBitmap m_Bitmap;
   CBitmap m_BitmapMouseIn;
   BOOL	m_bFocus;
   void DestroyIcon();

public:
	CSymbolEdit();
	virtual ~CSymbolEdit();

   void SetSymbolIcon(HICON hIcon, BOOL redraw = TRUE);
   void SetSymbolIcon(UINT id, BOOL redraw = TRUE);

   void SetPromptText(CString text, BOOL redraw = TRUE);
   void SetPromptText(LPCTSTR szText, BOOL redraw = TRUE);

   void SetPromptTextColor(COLORREF color, BOOL redraw = TRUE);

   void SetPromptFont(CFont& font, BOOL redraw = TRUE);
   void SetPromptFont(const LOGFONT* lpLogFont, BOOL redraw = TRUE);

   void SetEditRect(CRect c_rect);
   void SetState(BOOL c_bFocus);
   void SetBackColor(COLORREF c_colorBack);
virtual void SetBtnBMP(unsigned int c_UID,unsigned int c_UIDMouseIn);
protected:
   void RecalcLayout();
   virtual void PreSubclassWindow();

   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

public:
   afx_msg void OnPaint();
};


