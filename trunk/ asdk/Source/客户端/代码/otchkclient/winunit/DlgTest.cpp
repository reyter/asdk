// DlgTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "winunit.h"
#include "DlgTest.h"


// CDlgTest �Ի���

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


// CDlgTest ��Ϣ�������
