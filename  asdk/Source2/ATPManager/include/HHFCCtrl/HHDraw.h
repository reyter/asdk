#pragma once

#define DFCS_CAPTIONBUTTON	5
#define DFCS_MOUSEMOVE     0x0800
#define DFCS_COLORGRAY     0x8000

class AFX_EXT_CLASS CHHDraw
{
public:
	CHHDraw(void);
	~CHHDraw(void);
private:
	//Memory DC ���
	CWnd *m_pWnd;
	CDC *m_pDC,m_MemDC;
	CRect m_rectMem;
	CBitmap m_MemBmp, *m_pOldBmp;
public:
	CHHDraw(CWnd *pWnd, CDC *pDC, RECT rect);
	CDC *GetMemoryDC();
	void SetMemoryDC(RECT rect);
public:
	//�жϵ�point�Ƿ�������rect��
	static BOOL isInRectangle(POINT point, RECT rect);
	//�жϵ�point�Ƿ�������rect�ı߿���
	static BOOL isOnRectangle(POINT point, RECT rect, int nWidth=0);
	//�жϵ�point�Ƿ���Բ��
	static BOOL isInEllipse(POINT point, RECT rect);
	//�жϵ�point�Ƿ���Բ��
	static BOOL isOnEllipse(POINT point, RECT rect, int nWidth=0);
	//�жϵ��Ƿ�������
	static BOOL isOnLine(POINT point, int x1, int y1, int x2, int y2, int linewidth=1);
	//�жϵ��Ƿ��ڵ���
	static BOOL isOnDot(POINT point, POINT pointDot, int size=5);
	//�ж�rect�Ƿ�������rectBorder��
	static BOOL isInRectangle(RECT rect, RECT rectBorder);
	static BOOL isOnRoundRect(POINT point, RECT rect, POINT ptRound, int nWidth=0);
	static BOOL isInRoundRect(POINT point, RECT rect, POINT ptRound);
public:
	static COLORREF HLS_Transform(COLORREF rgb, int percent_L, int percent_S);
	static COLORREF GetSystemMenuBarColor();
public:
	//��ʾλͼ
	//x,y,size: ���λ�ú������С  
	//hBmp: λͼ
	//xb,yb,size: λͼλ�úʹ�С
	//bStretch:   λͼ����
	static void draw_Bitmap(CWnd *pWnd, CDC *pDC, RECT rect, HBITMAP hBmp, RECT rectBmp, BOOL bStretch=FALSE);
	//
	static void draw_BitmapButton(CWnd *pWnd, CDC *pDC, RECT rectBar, HBITMAP hBmp, RECT rectBmp, int nLeft=4);
	//System Tray �ı���
	static void draw_SystemTrayBackground(CWnd *pWnd, CDC *pDC, RECT rect);

public:
	//�����α߿�
	static void draw_RectangleBorder(CDC *pDC, RECT *prc, COLORREF cr, int type=0, int width=1);
	//��ɫ�������
	static void draw_GradientFillWE(CDC* pDC, RECT* prc, int nSegs, COLORREF crStart, COLORREF crEnd, BOOL bSemiFormat, RECT* prcFull);
	static void draw_GradientFillNS(CDC* pDC, RECT* prc, int nSegs, COLORREF crStart, COLORREF crEnd, BOOL bSemiFormat, RECT* prcFull);
	//ˮ��Bar
	static void draw_CrystalBar(CDC *pDC, RECT rectBar, COLORREF colorStart, COLORREF colorEnd, COLORREF colorBox, int nRound);
	//SpinButton
	static int  draw_SpinButton(CDC *pDC, RECT rect, COLORREF clrBtn1, COLORREF clrBtn2, COLORREF clrArrow, COLORREF clrDown, COLORREF clrBox, CPoint point, int nFlags); //nFlags: 0x01:��갴�£�0x02:��갴��
	//��ɫ����Bar
	static void draw_3DBarWE(CDC* pDC, RECT *prc, int nSegs, COLORREF crStart, COLORREF crProc, COLORREF crEnd);
	static void draw_3DBarNS(CDC* pDC, RECT *prc, int nSegs, COLORREF crStart, COLORREF crProc, COLORREF crEnd);
	//��ɫ����Box
	static RECT draw_3DBox(CDC *pDC, RECT *prc, int nBoxWidth, int nSegs, COLORREF crStart, COLORREF crProc, COLORREF crEnd, int nTopHight=-1);
	//��ɫ����Rect
	static void draw_GradientRect(CDC *pDC, RECT *prc, int nWidth, COLORREF crStart, COLORREF crProc, COLORREF crEnd, BOOL bReverse=FALSE);
	//��ɫ����Rect�߽�(1-Left, 2-Top, 3-Right, 4-Top)
	static void draw_GradientBorderLine(CDC *pDC, RECT *prc, int nType, COLORREF crStart, COLORREF crProc, COLORREF crEnd, BOOL bReverse=FALSE);
	//��ɫ����Tab
	static RECT draw_GradientTab(CDC *pDC, RECT *prc, int nWidth, int nTabX, int nTabHeigh, int nTabWidth, COLORREF crStart, COLORREF crProc, COLORREF crEnd);
	//��ܴ��ڱ߿�
	static void DrawHHFrameRect(CDC *pDC, RECT *pRect, int nFlag, int nOrder);
	//��ܴ��ڱ���
	static void DrawHHFrameTitle(CDC *pDC, RECT *pRect, HICON hIcon, CString strTitle, int nFontSize, CString strFont, int nFlag, COLORREF &colorBk1, COLORREF &colorBk2);
	//���
	static void DrawHHFrame(CWnd *pWnd, CDC *pDC, RECT rectWindow, HBITMAP hBmpFace, RECT rectBmpFrame, RECT rectBmpClient);
	//��ܰ�ť
	static void DrawHHFrameControl(CWnd *pWnd, CDC *pDC, RECT *pRect, int nType, int nStatus, COLORREF color);
	//�˵��߿�
	static void DrawHHMenuFrame(CDC *pDC, RECT *pRect, POINT ptMenu=CPoint(-100,-100));	
	//��ά����
	static void DrawHH3DRect(CDC *pDC, RECT *pRect, COLORREF colorBx1, COLORREF colorBx2, COLORREF colorBx3, COLORREF colorBx4);
public:
	//����
	static void draw_Diamond(CDC *pDC, RECT rect, COLORREF color, BOOL bFill);	
	//������
	static void draw_Triangle(CDC *pDC, RECT rect, COLORREF color, BOOL bFill);
	//ʮ��
	static void draw_Cross(CDC *pDC, RECT rect, COLORREF color, int nPix);
	//��������
	static void DrawSortTriangle(CDC* pDC, COLORREF color, int x, int y, int nSize, bool bDown);
	//�����¼�ͷ
	static void draw_ArrowDown(CDC *pDC,int x,int y,int width,int height,COLORREF color);
	//�����ϼ�ͷ
	static void draw_ArrowUp(CDC *pDC,int x,int y,int width,int height, COLORREF color);
	//ͼ����ť
	static void draw_PinButton(CDC *pDC, RECT *pRect, COLORREF color, int nStatus=0, COLORREF color1=GetSysColor(COLOR_3DHILIGHT), COLORREF color2=::GetSysColor(COLOR_3DDKSHADOW));
	//ͼ����ť
	static void draw_PinedButton(CDC *pDC, RECT *pRect, COLORREF color, int nStatus=0, COLORREF color1=GetSysColor(COLOR_3DHILIGHT), COLORREF color2=::GetSysColor(COLOR_3DDKSHADOW));
	//�رհ�ť
	static void draw_CloseButton(CDC *pDC, RECT *pRect, COLORREF color, int nStatus=0, COLORREF color1=GetSysColor(COLOR_3DHILIGHT), COLORREF color2=::GetSysColor(COLOR_3DDKSHADOW));
	//�رհ�ť2
	static void draw_CloseButton2(CDC *pDC, RECT *pRect, COLORREF color, int nStatus=0, COLORREF color1=GetSysColor(COLOR_3DHILIGHT), COLORREF color2=::GetSysColor(COLOR_3DDKSHADOW));
	static void draw_RestoreButton2(CDC *pDC, RECT *pRect, COLORREF color, int nStatus, COLORREF color1=GetSysColor(COLOR_3DHILIGHT), COLORREF color2=::GetSysColor(COLOR_3DDKSHADOW));
	//�����˵���ť1(Left)
	static void draw_LeftMenuButton(CDC *pDC, RECT *pRect, COLORREF color, int nStatus=0, COLORREF color1=GetSysColor(COLOR_3DHILIGHT), COLORREF color2=::GetSysColor(COLOR_3DDKSHADOW));
	//�����˵���ť2(Down)
	static void draw_DownMenuButton(CDC *pDC, RECT *pRect, COLORREF color, int nStatus=0, COLORREF color1=GetSysColor(COLOR_3DHILIGHT), COLORREF color2=::GetSysColor(COLOR_3DDKSHADOW));
	//�����
	static void draw_Fork(CDC *pDC, int x, int y, int nSize, COLORREF color);
	//X���
	static void draw_CrossX(CDC *pDC, int x, int y, int nSize, COLORREF color);
	//��������
	static void draw_TriangleFlag(CDC *pDC, int x, int y, int nSize, COLORREF color);
	//���ױ��
	static void draw_Mine(CDC *pDC, int x, int y, int nSize, COLORREF color);
	//��
	static void draw_Ball(CDC *pDC, int x, int y, int nSize, COLORREF color);
	//����
	static void draw_Rectangle(CDC *pDC, int x, int y, int width, int hight, COLORREF color, BOOL bFill);
	//Բ��
	static void draw_Circularity(CDC *pDC, int x, int y, int width, int hight, COLORREF color, BOOL bFill);
	//С��
	static void draw_Flag(CDC *pDC, int x, int y, int size, COLORREF color);
	//��
	static void draw_Star(CDC *pDC, int x, int y, int size, COLORREF color);
	//�����Ǳ��
	static void draw_TriangleUp(CDC *pDC, int x, int y, int nSize, COLORREF color);
	//�����Ǳ��
	static void draw_TriangleDown(CDC *pDC, int x, int y, int nSize, COLORREF color);
	//�����Ǳ��
	static void draw_TriangleLeft(CDC *pDC, int x, int y, int nSize, COLORREF color);
	//�����Ǳ��
	static void draw_TriangleRight(CDC *pDC, int x, int y, int nSize, COLORREF color);
	//
	static void draw_FrameTitleBar(CDC *pDC, RECT *prc, COLORREF crBack1, COLORREF crBack2);
	//������ͷ
	static void draw_ArrowEast(CDC *pDC,int x,int y,int nSize, COLORREF color);
	//���ϼ�ͷ
	static void draw_ArrowSouth(CDC *pDC,int x,int y,int nSize, COLORREF color);
	//������ͷ
	static void draw_ArrowWest(CDC *pDC,int x,int y,int nSize, COLORREF color);
	//������ͷ
	static void draw_ArrowNorth(CDC *pDC,int x,int y,int nSize, COLORREF color);
	//������ͷ
	static void draw_ArrowNorthEast(CDC *pDC,int x,int y,int nSize, COLORREF color);
	//���ϼ�ͷ
	static void draw_ArrowSouthEast(CDC *pDC,int x,int y,int nSize, COLORREF color);
	//���ϼ�ͷ
	static void draw_ArrowSouthWest(CDC *pDC,int x,int y,int nSize, COLORREF color);
	//������ͷ
	static void draw_ArrowNorthWest(CDC *pDC,int x,int y,int nSize, COLORREF color);
	//ֱ�߼�ͷ
	static void draw_LineArrow(CDC * pDC, CPoint pbeg, CPoint pend, COLORREF color, int nLineWidth, int nArrowSize, int nStyle);
	static BOOL isOnLineArrow(CPoint point, CPoint pbeg, CPoint pend, int nLineWidth, int nArrowSize, int nStyle);
public:
	static HBITMAP GetScreenBitmap(LPCRECT pRect);
	//////////////
	static void DrawMenuBarShade(CWnd *pWnd, CDC *pDC, RECT rect, BOOL bMenu=FALSE);
	//
	static void DrawFocusRect(RECT rect, BOOL bRemoveRect);
	//
	static HBITMAP PasteBitmapFromClipboard();
	static BOOL CopyBitmapToClipboard(HBITMAP hBitmap);
	static HBITMAP CopyHBITMAP(HBITMAP hBitmap);
};
