#pragma once

#include "CWebBrowser.h"
// CMyWebView ��ͼ

class CMyWebView : public CView
{
	DECLARE_DYNCREATE(CMyWebView)

protected:
	CMyWebView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMyWebView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	CWebBrowser m_Browser;
};


