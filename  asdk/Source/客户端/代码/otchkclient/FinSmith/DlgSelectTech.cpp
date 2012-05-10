// DlgSelectTech.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinSmith.h"
#include "PicWnd.h"
#include "TechManager.h"
#include "DlgSelectTech.h"


// CDlgSelectTech �Ի���

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


// CDlgSelectTech ��Ϣ�������

BOOL CDlgSelectTech::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgSelectTech::OnLbnDblclkListTechs()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_listTechs.GetCurSel() == -1)
		return;
	m_listTechs.GetText(m_listTechs.GetCurSel(),m_strSelected);

	OnOK();
}

void CDlgSelectTech::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_listTechs.GetCurSel() == -1)
		return;
	m_listTechs.GetText(m_listTechs.GetCurSel(),m_strSelected);

	OnOK();
}
