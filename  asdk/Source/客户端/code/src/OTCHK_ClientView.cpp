
// OTCHK_ClientView.cpp : COTCHK_ClientView ���ʵ��
//

#include "stdafx.h"
#include "OTCHK_Client.h"

#include "OTCHK_ClientDoc.h"
#include "OTCHK_ClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COTCHK_ClientView

IMPLEMENT_DYNCREATE(COTCHK_ClientView, CFormView)

BEGIN_MESSAGE_MAP(COTCHK_ClientView, CFormView)
END_MESSAGE_MAP()

// COTCHK_ClientView ����/����

COTCHK_ClientView::COTCHK_ClientView()
	: CFormView(COTCHK_ClientView::IDD)
{
	// TODO: �ڴ˴���ӹ������

}

COTCHK_ClientView::~COTCHK_ClientView()
{
}

void COTCHK_ClientView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL COTCHK_ClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void COTCHK_ClientView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}

void COTCHK_ClientView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COTCHK_ClientView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// COTCHK_ClientView ���

#ifdef _DEBUG
void COTCHK_ClientView::AssertValid() const
{
	CFormView::AssertValid();
}

void COTCHK_ClientView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

COTCHK_ClientDoc* COTCHK_ClientView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COTCHK_ClientDoc)));
	return (COTCHK_ClientDoc*)m_pDocument;
}
#endif //_DEBUG


// COTCHK_ClientView ��Ϣ�������
