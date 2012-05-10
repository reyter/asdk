// MyWebView.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "MyWebView.h"


// CMyWebView

IMPLEMENT_DYNCREATE(CMyWebView, CView)

CMyWebView::CMyWebView()
{

}

CMyWebView::~CMyWebView()
{
}

BEGIN_MESSAGE_MAP(CMyWebView, CView)
END_MESSAGE_MAP()


// CMyWebView 绘图

void CMyWebView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CMyWebView 诊断

#ifdef _DEBUG
void CMyWebView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyWebView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyWebView 消息处理程序
