// TransRadioBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinSmith.h"
#include "TransRadioBox.h"


// CTransRadioBox

IMPLEMENT_DYNAMIC(CTransRadioBox, CButton)

CTransRadioBox::CTransRadioBox()
{
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);
	m_font.CreateFontIndirect(&m_lf); 
}

CTransRadioBox::~CTransRadioBox()
{
	 m_font.DeleteObject();
}


BEGIN_MESSAGE_MAP(CTransRadioBox, CButton)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CTransRadioBox ��Ϣ�������
//ʵ��RadioBox��͸��������
void CTransRadioBox::OnPaint()
{
 CPaintDC dc(this); // device context for painting
 // TODO: �ڴ˴������Ϣ����������
 // ��Ϊ��ͼ��Ϣ���� CButton::OnPaint()
 CRect rect;
    GetClientRect(&rect);

    CRect BoxRect;
    BoxRect = rect;
    BoxRect.right = BoxRect.left +15;
    //dc.DrawFrameControl(BoxRect,DFC_BUTTON,DFCS_BUTTONRADIOIMAGE|GetCheck()?DFCS_CHECKED :0);
	if (GetCheck())
		dc.DrawFrameControl(BoxRect,DFC_BUTTON,DFCS_BUTTONRADIO | DFCS_CHECKED);
	else
		dc.DrawFrameControl(BoxRect,DFC_BUTTON,DFCS_BUTTONRADIO);

 CFont *pOldFont = (CFont *)dc.SelectObject(&m_font);
    dc.SetBkMode(TRANSPARENT);   
    
    CString StrWndText;
    GetWindowText(StrWndText);

    rect.OffsetRect (20,0);
    dc.DrawText(StrWndText,   rect,   DT_LEFT|DT_VCENTER|DT_SINGLELINE);   
    dc.SelectObject(pOldFont);  
    //Do not call CButton::OnPaint() for painting messages
}


