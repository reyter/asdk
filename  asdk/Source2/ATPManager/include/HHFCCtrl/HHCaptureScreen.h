#ifndef _CHHCAPTURESCREEN_H_
#define _CHHCAPTURESCREEN_H_
#pragma once
/*//////////////////////////////////////////////////
// 从指定的屏幕区域生成Bitmap
////////////////////////////////////////////////////
// 作者：陈牧
// 
//    2002.08.18  V1.0
// 用法实例：
//void CView::OnDraw(CDC* pDC)
//{
//	//初始化
//	CPalette *pOldPal = pDC->SelectPalette(m_bitmap.GetPalette(),false);
//	pDC->RealizePalette();
//
//	CDC dcComp;
//	dcComp.CreateCompatibleDC(pDC);
//	dcComp.SelectObject(&m_bitmap);
//	pDC->BitBlt(10,10,m_bitmap.m_nWidth,m_bitmap.m_nHeight,&dcComp,0,0,SRCCOPY);
//
//	//必须恢复
//	pDC->SelectPalette(pOldPal,false);
//	m_bCopyOver=false;
//}
//
//void CView::OnGetpic()
//{
//	CRect rect;
//	CWnd *pWnd=GetDesktopWindow();
//	m_bitmap.Capture(m_EndDrawRect);
//	m_bCopyBitmap=true;
//	m_bCopyOver=true;
//	Invalidate();
//}
///////////////////////////////////////////////////*/
// CHHCaptureScreen

class AFX_EXT_CLASS CHHCaptureScreen : public CBitmap
{
	DECLARE_DYNAMIC(CHHCaptureScreen)

public:
	CHHCaptureScreen();
	virtual ~CHHCaptureScreen();

	void Capture(CRect &rect);
	CPalette *GetPalette(){return m_pPalette;};
	CBitmap *Stretch(int nWidth, int nHeight, int nMode);

public:
	int m_nWidth;
	int m_nHeight;

private:
	CPalette *m_pPalette;
};
#endif
