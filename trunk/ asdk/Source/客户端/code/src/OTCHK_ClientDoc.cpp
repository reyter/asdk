
// OTCHK_ClientDoc.cpp : COTCHK_ClientDoc ���ʵ��
//

#include "stdafx.h"
#include "OTCHK_Client.h"

#include "OTCHK_ClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COTCHK_ClientDoc

IMPLEMENT_DYNCREATE(COTCHK_ClientDoc, CDocument)

BEGIN_MESSAGE_MAP(COTCHK_ClientDoc, CDocument)
END_MESSAGE_MAP()


// COTCHK_ClientDoc ����/����

COTCHK_ClientDoc::COTCHK_ClientDoc()
{
	// TODO: �ڴ����һ���Թ������

}

COTCHK_ClientDoc::~COTCHK_ClientDoc()
{
}

BOOL COTCHK_ClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// COTCHK_ClientDoc ���л�

void COTCHK_ClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// COTCHK_ClientDoc ���

#ifdef _DEBUG
void COTCHK_ClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COTCHK_ClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COTCHK_ClientDoc ����
