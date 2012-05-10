// DlgText.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "DlgText.h"


// CDlgText 对话框

IMPLEMENT_DYNAMIC(CDlgText, CDialog)

CDlgText::CDlgText(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgText::IDD, pParent)
	, m_nSize(0)
	, m_strText(_T(""))
{

}

CDlgText::~CDlgText()
{
}

void CDlgText::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_nSize);
	DDV_MinMaxInt(pDX, m_nSize, 5, 12);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strText);
	DDV_MaxChars(pDX, m_strText, 100);
	DDX_Control(pDX, IDC_BUTTON_COLOR, m_btnColor);
}


BEGIN_MESSAGE_MAP(CDlgText, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgText::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CDlgText::OnBnClickedButtonColor)
END_MESSAGE_MAP()


// CDlgText 消息处理程序

void CDlgText::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	OnOK();
}

void CDlgText::OnBnClickedButtonColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_cl = dlg.m_cc.rgbResult;
		m_btnColor.SetBtnBackColor(dlg.m_cc.rgbResult);
		m_btnColor.Invalidate();
	}
}

BOOL CDlgText::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_btnColor.SetBorder(FALSE);
	m_nSize = 6;
	m_cl = gpSkinManager->getColor(MANUAL_DRAW_TEXT_COLOR);
	m_btnColor.SetBtnBackColor(m_cl);
	UpdateData(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
