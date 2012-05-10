#pragma once
#define IDC_FILEPROGRESS				10015
/*************************************************
* Copyright (c) 2005,���ڴ���Ƽ����޹�˾������
* All rights reserved
*
* �ļ����ƣ�TextProgressCtrl.h
* ժ    Ҫ���������ֵĽ�����
*
* ��ǰ�汾��1.1
* ��    �ߣ�����
* ������ڣ�2004��4��12��
**************************************************/

class AFX_EXT_CLASS CTextProgressCtrl : public CProgressCtrl
{
public:
    CTextProgressCtrl();
	virtual ~CTextProgressCtrl();

public:
    int SetPos(int nPos);
    int StepIt();
	int OffsetPos(int nPos);
    int SetStep(int nStep);

    void SetRange(int nLower, int nUpper);
    void SetForeColour(COLORREF col);
    void SetBkColour(COLORREF col);
    void SetTextForeColour(COLORREF col);
    void SetTextBkColour(COLORREF col);
	void SetShowText(BOOL bShow);

    COLORREF GetForeColour();
    COLORREF GetBkColour();
    COLORREF GetTextForeColour();
    COLORREF GetTextBkColour();

public:
	LRESULT OnSetText(CString strType, LPCTSTR szText);
    LRESULT OnGetText(UINT cchTextMax, LPTSTR szText);

protected:
    int m_nPos; 
	int m_nStepSize;
    int m_nMax;
	int m_nMin;

	int m_nBarWidth;

    CString m_strText;
	CString m_strType;
    BOOL m_bShowText;
    
	COLORREF m_colFore;
    COLORREF m_colBk;
	COLORREF m_colTextFore;
	COLORREF m_colTextBk;

	CFont m_Font;

    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);

    DECLARE_MESSAGE_MAP()
};
