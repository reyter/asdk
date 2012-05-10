// TransCheckBox.cpp : 实现文件
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



// CTransCheckBox 消息处理程序
//实现CheckBox的透明的类型
void CTransCheckBox::OnPaint()
{
 CPaintDC dc(this); // device context for painting
 // TODO: 在此处添加消息处理程序代码
 // 不为绘图消息调用 CButton::OnPaint()
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


