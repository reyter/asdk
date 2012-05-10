// DlgInputName.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgInputName.h"


// CDlgInputName �Ի���

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


// CDlgInputName ��Ϣ�������

BOOL CDlgInputName::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(m_strTitle);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgInputName::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	m_strInput.Trim();

	if(m_strInput.GetLength() > 0)
		OnOK();
	else
	{
		MessageBox(_T("��ϲ���Ϊ�գ�"),_T("��ʾ"),MB_OK);
	}
}
