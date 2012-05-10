// nsd1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "nsd1.h"
#include "nsd1Dlg.h"
#include ".\nsd1dlg.h"

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


// Cnsd1Dlg �Ի���



Cnsd1Dlg::Cnsd1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cnsd1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void Cnsd1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cnsd1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
END_MESSAGE_MAP()


// Cnsd1Dlg ��Ϣ�������

BOOL Cnsd1Dlg::OnInitDialog()
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
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void Cnsd1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cnsd1Dlg::OnPaint() 
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
HCURSOR Cnsd1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cnsd1Dlg::OnBnClickedButton1()
{
	m_bForce = FALSE;
	//����HHUpdateClient

	STARTUPINFO si; //һЩ�ر���������
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi; //�ر��������ý���
	if(!CreateProcess("HHUpdateClient.exe",NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
	{
		TRACE("Create Fail!");
		//exit(1);
	}
	else
	{
		TRACE("Success!");
		Sleep(1000);
		OnBnClickedButton2();
	}
}

void Cnsd1Dlg::OnBnClickedButton2()
{//���ʹ��ھ����IP��
	CString str="���NSD�Զ���������";
	tagUpgradeInfo *_tagpProcessMsg = new tagUpgradeInfo();
	_tagpProcessMsg->hWnd = this->m_hWnd;
	::GetWindowModuleFileName(this->m_hWnd,_tagpProcessMsg->chAppName,128);
	char *ptr=NULL,c = '\\';
	ptr = strrchr(_tagpProcessMsg->chAppName,c);
	if (strlen(ptr)>1)
	{
		strcpy(_tagpProcessMsg->chAppName,&ptr[1]);
	}
	strcpy(_tagpProcessMsg->szAppID,"001S00000026");
	strcpy(_tagpProcessMsg->szVersion,"");
	strcpy(_tagpProcessMsg->szServerIP,"192.168.10.217");
	strcpy(_tagpProcessMsg->szUserID,"������");
	_tagpProcessMsg->nServerPort = 9527;


	_tagpProcessMsg->bForce = (int)m_bForce;//ǿ������

	tagCOPYDATASTRUCT sss={0};

	sss.lpData=_tagpProcessMsg;
	sss.cbData=sizeof tagUpgradeInfo;
	CWnd *pWnd=CWnd::FindWindow(NULL,str);//��ȡĿ�Ĵ��ڶ���
	while(!pWnd)
	{
		Sleep(500);
	}

	if(pWnd)
	{
		//pWnd->SendMessage(); //�����Զ�����Ϣ
		//pWnd->SendMessage(WM_MYMESSAGE,0,(LPARAM)_tagpProcessMsg);
		::SendMessage(pWnd->m_hWnd, WM_COPYDATA, NULL, (LPARAM)&sss);
	}
	else
	{
		AfxMessageBox("û���ҵ�MYRECEIVER���ڣ�");
	}
}

void Cnsd1Dlg::OnBnClickedButton3()
{
	m_bForce = TRUE;
	STARTUPINFO si; //һЩ�ر���������
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi; //�ر��������ý���
	if(!CreateProcess("HHUpdateClient.exe",NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
	{
		TRACE("Create Fail!");
		//exit(1);
	}
	else
	{
		TRACE("Success!");
		Sleep(1000);
		OnBnClickedButton2();
	}

}


