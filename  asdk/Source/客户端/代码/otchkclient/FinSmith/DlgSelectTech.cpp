// DlgSelectTech.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "PicWnd.h"
#include "TechManager.h"
#include "DlgSelectTech.h"


// CDlgSelectTech 对话框

IMPLEMENT_DYNAMIC(CDlgSelectTech, CDialog)

CDlgSelectTech::CDlgSelectTech(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectTech::IDD, pParent)
{
	m_bMainPic = false;
	m_bIndex = false;
}

CDlgSelectTech::~CDlgSelectTech()
{
}

void CDlgSelectTech::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TECHS, m_listTechs);
}


BEGIN_MESSAGE_MAP(CDlgSelectTech, CDialog)
	ON_LBN_DBLCLK(IDC_LIST_TECHS, &CDlgSelectTech::OnLbnDblclkListTechs)
	ON_BN_CLICKED(IDOK, &CDlgSelectTech::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSelectTech 消息处理程序

BOOL CDlgSelectTech::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (m_bMainPic)
	{
		m_listTechs.AddString(PIC_BOLL);
		m_listTechs.AddString(PIC_EMA);
		m_listTechs.AddString(PIC_MA);
	}
	else
	{
		m_listTechs.AddString(PIC_MACD);
		m_listTechs.AddString(PIC_KDJ);
		m_listTechs.AddString(PIC_RSI);
		m_listTechs.AddString(PIC_HISK_VOL);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgSelectTech::OnLbnDblclkListTechs()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_listTechs.GetCurSel() == -1)
		return;
	m_listTechs.GetText(m_listTechs.GetCurSel(),m_strSelected);

	OnOK();
}

void CDlgSelectTech::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_listTechs.GetCurSel() == -1)
		return;
	m_listTechs.GetText(m_listTechs.GetCurSel(),m_strSelected);

	OnOK();
}
