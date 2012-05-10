// HHUpdateServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HHUpdateServer.h"
#include "HHUpdateServerDlg.h"

#include "..\\include\\compress\\HHCompress.h"
#include "..\\include\\HHXml\\HHTyXml.h"
#include "HHSetting.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CHHUpdateServerDlg �Ի���

CHHUpdateServerDlg::CHHUpdateServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHHUpdateServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CHHUpdateServerDlg::~CHHUpdateServerDlg()
{
	int i;
	i=9;
}
void CHHUpdateServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHHUpdateServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_START, &CHHUpdateServerDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CHHUpdateServerDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_SET, &CHHUpdateServerDlg::OnBnClickedBtnSet)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CHHUpdateServerDlg ��Ϣ�������

BOOL CHHUpdateServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	SetTimer(12001,1000,NULL);
	SetTimer(12002,1000*60,NULL);
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CHHUpdateServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHHUpdateServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CHHUpdateServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CHHUpdateServerDlg::ShowMsg(CString strMsg,BOOL bClear)
{
	CRichEditCtrl *pEditShow = (CRichEditCtrl *)GetDlgItem(IDC_RICHEDIT2_SHOW);
	//CRichEditCtrl
	if (NULL != pEditShow)
	{
		if (bClear)
		{
			pEditShow->Clear();
		}
		pEditShow->SetSel(-1, -1);
		if (strMsg.GetLength()>0)
		{
			pEditShow->ReplaceSel(strMsg+_T("\r\n"));
		}
		
	}
	
}

LRESULT CHHUpdateServerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (message == WM_SHOW_MSG) {
		ShowMsg((TCHAR *)lParam);
		return TRUE;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CHHUpdateServerDlg::OnBnClickedBtnStart()
{
	m_IocpServer.AssociateWnd(this);//���ݱ�����ָ��
	if (m_IocpServer.StartServer(9527))
	{
		GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
	}
}

void CHHUpdateServerDlg::OnBnClickedBtnStop()
{
	m_IocpServer.StopServer();
	GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SET)->EnableWindow(TRUE);
}

void CHHUpdateServerDlg::OnBnClickedBtnSet()
{
	//GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	CHHSetting seting;
	seting.DoModal();
}

void CHHUpdateServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (12001==nIDEvent)
	{
		UpdateWindow();
	}
	if (12002==nIDEvent)
	{
		ShowMsg("",TRUE);
	}
	CDialog::OnTimer(nIDEvent);
}
