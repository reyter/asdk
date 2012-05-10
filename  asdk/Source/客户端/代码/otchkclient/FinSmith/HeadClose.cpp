// HeadClose.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "HeadClose.h"


// CHeadClose 对话框

IMPLEMENT_DYNAMIC(CHeadClose, CDialog)

CHeadClose::CHeadClose(CWnd* pParent /*=NULL*/)
	: CDialog(CHeadClose::IDD, pParent)
{

}

CHeadClose::~CHeadClose()
{
}

void CHeadClose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnClose);
}


BEGIN_MESSAGE_MAP(CHeadClose, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CHeadClose::OnBnClickedButtonClose)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CHeadClose 消息处理程序

void CHeadClose::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	this->GetParentFrame()->ShowWindow(SW_HIDE);
}

void CHeadClose::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_btnClose)
	{
		CRect rect,rectW,r;
		GetClientRect(rect);
		m_btnClose.GetWindowRect(rectW);
		r.left = rect.left + (rect.Width() - rectW.Width()) / 2;
		r.top = rect.top + (rect.Height() - rectW.Height()) / 2;
		r.right = r.left + rectW.Width();
		r.bottom = r.top + rectW.Height();
		m_btnClose.MoveWindow(r);
	}
}

BOOL CHeadClose::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(rect);
	CBitmap bitmap;
	CBrush brush;
	bitmap.LoadBitmap(IDB_REG_BK);
	brush.CreatePatternBrush(&bitmap);
	pDC->FillRect(rect,&brush);
	brush.DeleteObject();
	bitmap.DeleteObject();
	return true;
	return CDialog::OnEraseBkgnd(pDC);
}
