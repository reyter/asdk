// MyWebView.cpp : ʵ���ļ�
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


// CMyWebView ��ͼ

void CMyWebView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CMyWebView ���

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


// CMyWebView ��Ϣ�������
