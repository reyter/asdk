// DlgSetFont.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "DlgSetFont.h"


// CDlgSetFont 对话框

IMPLEMENT_DYNAMIC(CDlgSetFont, CDialog)

CDlgSetFont::CDlgSetFont(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetFont::IDD, pParent)
{

}

CDlgSetFont::~CDlgSetFont()
{
}

void CDlgSetFont::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MENU, m_cbMenu);
	DDX_Control(pDX, IDC_COMBO_BUTTON, m_cbButton);
	DDX_Control(pDX, IDC_COMBO_LIST, m_cbList);
	DDX_Control(pDX, IDC_COMBO_TEXT, m_cbText);
	DDX_Control(pDX, IDC_COMBO_GRAPH, m_cbGraph);
}


BEGIN_MESSAGE_MAP(CDlgSetFont, CDialog)
	ON_BN_CLICKED(IDC_BTN_DEFAULT, &CDlgSetFont::OnBnClickedBtnDefault)
	ON_BN_CLICKED(IDOK, &CDlgSetFont::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSetFont 消息处理程序

BOOL CDlgSetFont::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_cbMenu.InsertString(0,_T("10"));
	m_cbMenu.InsertString(1,_T("12"));
	m_cbMenu.InsertString(2,_T("14"));
	m_cbMenu.InsertString(3,_T("16"));
	m_cbMenu.InsertString(4,_T("18"));
	m_cbMenu.InsertString(5,_T("20"));
	m_cbMenu.InsertString(6,_T("22"));
	m_cbMenu.InsertString(7,_T("24"));
	m_cbMenu.InsertString(8,_T("26"));

	m_cbButton.InsertString(0,_T("10"));
	m_cbButton.InsertString(1,_T("12"));
	m_cbButton.InsertString(2,_T("14"));
	m_cbButton.InsertString(3,_T("16"));
	m_cbButton.InsertString(4,_T("18"));
	m_cbButton.InsertString(5,_T("20"));
	m_cbButton.InsertString(6,_T("22"));
	m_cbButton.InsertString(7,_T("24"));
	m_cbButton.InsertString(8,_T("26"));

	m_cbText.InsertString(0,_T("10"));
	m_cbText.InsertString(1,_T("12"));
	m_cbText.InsertString(2,_T("14"));
	m_cbText.InsertString(3,_T("16"));
	m_cbText.InsertString(4,_T("18"));
	m_cbText.InsertString(5,_T("20"));
	m_cbText.InsertString(6,_T("22"));
	m_cbText.InsertString(7,_T("24"));
	m_cbText.InsertString(8,_T("26"));

	m_cbList.InsertString(0,_T("10"));
	m_cbList.InsertString(1,_T("12"));
	m_cbList.InsertString(2,_T("14"));
	m_cbList.InsertString(3,_T("16"));
	m_cbList.InsertString(4,_T("18"));
	m_cbList.InsertString(5,_T("20"));
	m_cbList.InsertString(6,_T("22"));
	m_cbList.InsertString(7,_T("24"));
	m_cbList.InsertString(8,_T("26"));

	m_cbGraph.InsertString(0,_T("10"));
	m_cbGraph.InsertString(1,_T("12"));
	m_cbGraph.InsertString(2,_T("14"));
	m_cbGraph.InsertString(3,_T("16"));
	m_cbGraph.InsertString(4,_T("18"));
	m_cbGraph.InsertString(5,_T("20"));
	m_cbGraph.InsertString(6,_T("22"));
	m_cbGraph.InsertString(7,_T("24"));
	m_cbGraph.InsertString(8,_T("26"));

	CString strText;
	strText.Format(_T("%d"),abs(gpSkinManager->m_nTextFontSize));
	m_cbText.SetWindowText(strText);

	strText.Format(_T("%d"),abs(gpSkinManager->m_nQuoteListFontSize));
	m_cbList.SetWindowText(strText);

	strText.Format(_T("%d"),abs(gpSkinManager->m_nGraphFontSize));
	m_cbGraph.SetWindowText(strText);

	strText.Format(_T("%d"),abs(gpSkinManager->m_nButtonFontSize));
	m_cbButton.SetWindowText(strText);

	strText.Format(_T("%d"),abs(gpSkinManager->m_nMenuFontSize));
	m_cbMenu.SetWindowText(strText);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgSetFont::OnBnClickedBtnDefault()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText;
#ifdef CCTV_TV
	m_cbText.SetWindowText(_T("18"));

	m_cbList.SetWindowText(_T("18"));

	m_cbGraph.SetWindowText(_T("12"));

	m_cbButton.SetWindowText(_T("18"));
	
	m_cbMenu.SetWindowText(_T("18"));

#else
	m_cbText.SetWindowText(_T("12"));

	m_cbList.SetWindowText(_T("12"));

	m_cbGraph.SetWindowText(_T("12"));

	m_cbButton.SetWindowText(_T("12"));
	
	m_cbMenu.SetWindowText(_T("12"));
#endif
}

void CDlgSetFont::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	char acBuf[16];
	CString strText;
	m_cbText.GetWindowText(strText);
	unicodeToAscii(strText,acBuf,16);
	gpSkinManager->m_nTextFontSize = atoi(acBuf) * -1;
	m_cbMenu.GetWindowText(strText);
	unicodeToAscii(strText,acBuf,16);
	gpSkinManager->m_nMenuFontSize = atoi(acBuf) * -1;
	m_cbButton.GetWindowText(strText);
	unicodeToAscii(strText,acBuf,16);
	gpSkinManager->m_nButtonFontSize = atoi(acBuf) * -1;
	m_cbGraph.GetWindowText(strText);
	unicodeToAscii(strText,acBuf,16);
	gpSkinManager->m_nGraphFontSize = atoi(acBuf) * -1;
	m_cbList.GetWindowText(strText);
	unicodeToAscii(strText,acBuf,16);
	gpSkinManager->m_nQuoteListFontSize = atoi(acBuf) * -1;
	gpSkinManager->SaveFontConfig();
	OnOK();
}
