
// OTCHK_ClientDoc.cpp : COTCHK_ClientDoc 类的实现
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


// COTCHK_ClientDoc 构造/析构

COTCHK_ClientDoc::COTCHK_ClientDoc()
{
	// TODO: 在此添加一次性构造代码

}

COTCHK_ClientDoc::~COTCHK_ClientDoc()
{
}

BOOL COTCHK_ClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// COTCHK_ClientDoc 序列化

void COTCHK_ClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// COTCHK_ClientDoc 诊断

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


// COTCHK_ClientDoc 命令
