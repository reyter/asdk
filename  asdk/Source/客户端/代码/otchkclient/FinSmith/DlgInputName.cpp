// DlgInputName.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgInputName.h"


// CDlgInputName 对话框

IMPLEMENT_DYNAMIC(CDlgInputName, CDialog)

CDlgInputName::CDlgInputName(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInputName::IDD, pParent)
	, m_strInput(_T(""))
{

}

CDlgInputName::~CDlgInputName()
{
}

void CDlgInputName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_GROUPNAME, m_editInput);
	DDX_Text(pDX, IDC_EDIT_GROUPNAME, m_strInput);
}


BEGIN_MESSAGE_MAP(CDlgInputName, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgInputName::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgInputName 消息处理程序

BOOL CDlgInputName::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(m_strTitle);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgInputName::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strInput.Trim();

	if(m_strInput.GetLength() > 0)
		OnOK();
	else
	{
		MessageBox(_T("组合不能为空！"),_T("提示"),MB_OK);
	}
}
