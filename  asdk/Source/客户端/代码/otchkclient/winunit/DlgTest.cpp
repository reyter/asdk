// DlgTest.cpp : 实现文件
//

#include "stdafx.h"
#include "winunit.h"
#include "DlgTest.h"


// CDlgTest 对话框

IMPLEMENT_DYNAMIC(CDlgTest, CDialog)

CDlgTest::CDlgTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTest::IDD, pParent)
{

}

CDlgTest::~CDlgTest()
{
}

void CDlgTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTest, CDialog)
END_MESSAGE_MAP()


// CDlgTest 消息处理程序
