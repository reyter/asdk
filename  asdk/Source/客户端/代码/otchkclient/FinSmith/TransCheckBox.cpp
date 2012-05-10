// TransCheckBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinSmith.h"
#include "TransCheckBox.h"


// CTransCheckBox

IMPLEMENT_DYNAMIC(CTransCheckBox, CButton)

CTransCheckBox::CTransCheckBox()
{
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);
	m_font.CreateFontIndirect(&m_lf); 
}

CTransCheckBox::~CTransCheckBox()
{
	 m_font.DeleteObject();
}


BEGIN_MESSAGE_MAP(CTransCheckBox, CButton)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CTransCheckBox ��Ϣ�������
//ʵ��CheckBox��͸��������
void CTransCheckBox::OnPaint()
{
 CPaintDC dc(this); // device context for painting
 // TODO: �ڴ˴������Ϣ����������
 // ��Ϊ��ͼ��Ϣ���� CButton::OnPaint()
 CRect rect;
    GetClientRect(&rect);

    CRect BoxRect;
    BoxRect = rect;
    BoxRect.right = BoxRect.left +15;
    dc.DrawFrameControl(BoxRect,DFC_BUTTON,DFCS_BUTTONCHECK|GetCheck()?DFCS_CHECKED :0);

 CFont *pOldFont = (CFont *)dc.SelectObject(&m_font);
    dc.SetBkMode(TRANSPARENT);   
    
    CString StrWndText;
    GetWindowText(StrWndText);

    rect.OffsetRect (20,0);
	COLORREF cl = dc.SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));
    dc.DrawText(StrWndText,   rect,   DT_LEFT|DT_VCENTER|DT_SINGLELINE);   
	dc.SetTextColor(cl);
    dc.SelectObject(pOldFont);  
    //Do not call CButton::OnPaint() for painting messages
}


