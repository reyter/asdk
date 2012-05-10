// DlgTechDesc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinSmith.h"
#include "picWnd.h"
#include "DlgTechDesc.h"


// CDlgTechDesc �Ի���

IMPLEMENT_DYNAMIC(CDlgTechDesc, CDialog)

CDlgTechDesc::CDlgTechDesc(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTechDesc::IDD, pParent)
{

}

CDlgTechDesc::~CDlgTechDesc()
{
}

void CDlgTechDesc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DESC, m_editDesc);
}


BEGIN_MESSAGE_MAP(CDlgTechDesc, CDialog)
END_MESSAGE_MAP()


// CDlgTechDesc ��Ϣ�������

void CDlgTechDesc::SetTitle(CString c_strTitle)
{
	m_strTitle = c_strTitle;
}

BOOL CDlgTechDesc::OnInitDialog()
{
	CDialog::OnInitDialog();
	USES_CONVERSION;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_editDesc.SetFont(gpSkinManager->m_pFontGraph);
	SetWindowText(m_strTitle);
	CString strFile;
	if (m_strTitle == PIC_HISK_VOL)
	{
		strFile = "vol.txt";
	}
	else

	if (m_strTitle == PIC_KDJ)
	{
		strFile = "kdj.txt";
	}
	else

	if (m_strTitle == PIC_RSI)
	{
		strFile = "rsi.txt";
	}
	else

	if (m_strTitle == PIC_MACD)
	{
		strFile = "macd.txt";
	}
	else
	if (m_strTitle == PIC_BOLL)
	{
		strFile = "boll.txt";
	}
	else
	if (m_strTitle == _T("���Э��"))
	{
		strFile = "lic.txt";
	}
	else
	if (m_strTitle == _T("��ܰ��ʾ"))
	{
		strFile = "visitor.txt";
	}
	else
	if (m_strTitle == _T("��¼ʧ����ʾ"))	
	{
		strFile = "logfail.txt";
	}
	else
	if (m_strTitle == _T("�ʺ��쳣��ʾ"))
	{
		strFile = "userfail.txt";
	}
	else
	if (m_strTitle == _T("֪ͨ"))
	{
		strFile = "notify.txt";		
	}

	CString strFileName;
	strFileName.Format(_T("%s\\msg\\%s"),toUnicodeString(gpData->m_acCurPath,strlen(gpData->m_acCurPath)),strFile);
	FILE *f;
	f = fopen((char *)W2A(strFileName.GetBuffer()),"r");
	strFileName.ReleaseBuffer();
	CString str;
	if (f)
	{
		char acBuf[4096];
		memset(acBuf,0,4096);
		while(fgets(acBuf,1024,f))
		{
			str += toUnicodeString("\r\n",2);
			str += toUnicodeString(acBuf,strlen(acBuf));
		}
		
		fclose(f);		
	}
	m_editDesc.SetWindowText(str);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
