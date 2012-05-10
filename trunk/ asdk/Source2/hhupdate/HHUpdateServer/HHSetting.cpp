// HHSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HHUpdateServer.h"
#include "HHSetting.h"
#include "afxdialogex.h"

// CHHSetting �Ի���

IMPLEMENT_DYNAMIC(CHHSetting, CDialog)

CHHSetting::CHHSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CHHSetting::IDD, pParent)
{
	m_bMark = TRUE;
	m_pThread = NULL;
	m_bThreadRun = FALSE;
}

CHHSetting::~CHHSetting()
{
}

void CHHSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHOW, m_listShow);
	DDX_Control(pDX, IDC_CHECK_SELECTALL, m_checkSelectAll);
}

BEGIN_MESSAGE_MAP(CHHSetting, CDialog)
	ON_BN_CLICKED(IDC_BTN_BUILDXML, &CHHSetting::OnBnClickedBtnBuildxml)
	ON_BN_CLICKED(IDC_BTN_COMPRESS, &CHHSetting::OnBnClickedBtnCompress)
	ON_BN_CLICKED(IDC_CHECK_SELECTALL, &CHHSetting::OnBnClickedCheckSelectall)
	ON_BN_CLICKED(IDC_BTN_ONEKEY, &CHHSetting::OnBnClickedBtnOnekey)
END_MESSAGE_MAP()

// CHHSetting ��Ϣ�������

void CHHSetting::OnBnClickedBtnCompress()
{
	//����ͬ��Ŀ¼
	m_pThread =  AfxBeginThread(HHScanLevel1Folder,this);
}
void CHHSetting::OnBnClickedBtnBuildxml()
{
	//����ͬ��Ŀ¼
	AfxBeginThread(HHScanLevel1Folder,this);
}

UINT CHHSetting::HHScanLevel1Folder(LPVOID lParam)
{
	CHHSetting *pThis = (CHHSetting *)lParam;
	
	if (pThis->GetCheckCount()<=0)
	{
		pThis->GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("��ѡ����Ҫ�����İ汾!"));
		pThis->GetDlgItem(IDC_BTN_ONEKEY)->EnableWindow(TRUE);
		pThis->m_bThreadRun = FALSE;
		return FALSE;
	}
	

	
	pThis->m_bThreadRun = TRUE;
	pThis->GetDlgItem(IDC_BTN_COMPRESS)->EnableWindow(FALSE);
	pThis->GetDlgItem(IDC_BTN_BUILDXML)->EnableWindow(FALSE);
	pThis->GetDlgItem(IDC_CHECK_SELECTALL)->EnableWindow(FALSE);
	pThis->GetDlgItem(IDC_LIST_SHOW)->EnableWindow(FALSE);
	
	

	
	HANDLE hFind;
	WIN32_FIND_DATA wfData;
	char szFullPath[MAX_PATH];memset(szFullPath,0,MAX_PATH);
	CString strItemText;
	for (int i = 0;i<pThis->m_listShow.GetItemCount();i++)
	{
		if (pThis->m_listShow.GetCheck(i))
		{
			strItemText = pThis->m_listShow.GetItemText(i,0);
			strcpy(szFullPath,strItemText.GetBuffer());
			
			hFind = FindFirstFile(szFullPath,&wfData);
			if(hFind != INVALID_HANDLE_VALUE)
			{
				strcat(szFullPath,"\\update\\");
				
				pThis->GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("����ѹ��������Ҫ���ļ������Ե�..."));
				pThis->hhCompress.BatchDecompress(szFullPath);
				pThis->GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("��������������Ҫ��XML�ļ������Ե�..."));
				pThis->hhTyXml.HHComposeXML(szFullPath);
				
			}
			strItemText.ReleaseBuffer();
		}
	}

	pThis->GetDlgItem(IDC_BTN_COMPRESS)->EnableWindow(TRUE);	
	pThis->GetDlgItem(IDC_BTN_BUILDXML)->EnableWindow(TRUE);
	pThis->GetDlgItem(IDC_CHECK_SELECTALL)->EnableWindow(TRUE);
	pThis->GetDlgItem(IDC_LIST_SHOW)->EnableWindow(TRUE);

	pThis->GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(_T("ѹ��������XML���!"));
	pThis->GetDlgItem(IDC_BTN_ONEKEY)->EnableWindow(TRUE);
	pThis->m_bThreadRun = FALSE;
	return TRUE;
}

void CHHSetting::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
// 	if (m_pThread)
// 	{
// 		TerminateThread(m_pThread->m_hThread,-1);
// 	}
	if (m_bThreadRun)
	{
		return;
	} 
	
	CDialog::OnCancel();

	
}

BOOL CHHSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitList();
	InitListData();

	GetDlgItem(IDC_BTN_COMPRESS)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_BUILDXML)->ShowWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CHHSetting::InitList()
{
	LVCOLUMN lv;
	lv.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lv.fmt	= LVCFMT_LEFT;	
	lv.cx	= 240;
	lv.pszText = _T("�汾");
	m_listShow.InsertColumn(0,&lv);//LVM_INSERTCOLUMN �����
	lv.cx	= 60;
	lv.pszText = _T("Readme");
	m_listShow.InsertColumn(1,&lv);//LVM_INSERTCOLUMN �����
	lv.cx	= 50;
	lv.pszText = _T("XML");
	m_listShow.InsertColumn(2,&lv);//LVM_INSERTCOLUMN �����
	lv.cx	= 110;
	lv.pszText = _T("ѹ������");
	m_listShow.InsertColumn(3,&lv);//LVM_INSERTCOLUMN �����

	m_listShow.SetExtendedStyle(LVS_EX_INFOTIP|LVS_EX_REGIONAL|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_MULTIWORKAREAS|LVS_EX_CHECKBOXES);
}

void CHHSetting::InitListData()
{
	int nErr=0;
	HANDLE hFind,hFile;
	WIN32_FIND_DATA wfData;
	char szFullPath[MAX_PATH];memset(szFullPath,0,MAX_PATH);
	char szFolderPath[MAX_PATH];memset(szFolderPath,0,MAX_PATH);
	strcat(szFullPath,"*.*");

	hFind = FindFirstFile(szFullPath,&wfData);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		return ;
	}
	m_listShow.DeleteAllItems();
	LVITEM lvItem;
	lvItem.mask		= LVIF_TEXT; 
	lvItem.iItem	= 0;
	lvItem.iSubItem = 0;
	int i = 0,nItem =0;
	char szFileName[MAX_PATH]={0};
	do
	{
		switch(wfData.dwFileAttributes)
		{
		case FILE_ATTRIBUTE_DIRECTORY://Ŀ¼
			{
				if(strcmp(wfData.cFileName,".") && strcmp(wfData.cFileName,".."))//�ų���ǰĿ¼���ϼ�Ŀ¼
				{
					lvItem.iItem = i++;
					lvItem.pszText=wfData.cFileName;
					nItem = m_listShow.InsertItem(&lvItem);

					sprintf(szFileName,"%s%s",wfData.cFileName,"\\readme.txt");
					if (PathFileExists(szFileName))
					{
						m_listShow.SetItemText(nItem,1,"����");
					}else
					{
						m_listShow.SetItemText(nItem,1,"ȱʧ");
					}
					sprintf(szFileName,"%s%s",wfData.cFileName,"\\update.xml");
					if (PathFileExists(szFileName))
					{
						m_listShow.SetItemText(nItem,2,"����");
					}else
					{
						m_listShow.SetItemText(nItem,2,"ȱʧ");
					}

					sprintf(szFileName,"%s%s",wfData.cFileName,"\\update\\*.*");
					hFile = FindFirstFile(szFileName,&wfData);
					if(hFile == INVALID_HANDLE_VALUE)
					{
						goto BreakFile;//
					}

					do
					{
						switch(wfData.dwFileAttributes)
						{
						case FILE_ATTRIBUTE_DIRECTORY://Ŀ¼
							break;
						default://�ļ�
							{
								if (0==strcmpi(&wfData.cFileName[strlen(wfData.cFileName)-3],".hh"))
								{
									ZeroMemory(&szFileName[strlen(szFileName)-3],3);
									strcat(szFileName,wfData.cFileName);
									long lDate=0,lTime=0;char szDate[25]={0},szTime[25]={0};
									GetLocalFileStatus(szFileName,lDate,lTime);
									sprintf(szDate,"%d-%d-%d %d:%d:%d",lDate/10000,lDate%10000/100,lDate%1000%100,lTime/10000,lTime%10000/100,lTime%10000%100);
									m_listShow.SetItemText(nItem,3,szDate);
									goto BreakFile;
								}				
							}
							break;
						}
					}while(FindNextFile(hFile,&wfData));
BreakFile:
					i=i;//������
				}
			}
			break;
		default:
			break;
		}
	}while(FindNextFile(hFind,&wfData));
}

void CHHSetting::OnBnClickedCheckSelectall()
{
	if (m_checkSelectAll.GetCheck())
	{
		for (int i = 0; i<m_listShow.GetItemCount();i++)
		{
			m_listShow.SetCheck(i);
		}
	} 
	else
	{
		for (int i = 0; i<m_listShow.GetItemCount();i++)
		{
			m_listShow.SetCheck(i,FALSE);
		}
	}
}

BOOL CHHSetting::GetLocalFileStatus(char *pFilename,long &lDate, long &lTime)
{
	CTime tFile=CTime::GetCurrentTime();
	lDate=lTime=0;
	CFileFind  fileFind;
	BOOL	bResult=fileFind.FindFile(pFilename);
	if(bResult)
	{
		fileFind.FindNextFile();

		fileFind.GetLastWriteTime(tFile);
		lDate=tFile.GetYear()*10000+tFile.GetMonth()*100+tFile.GetDay();
		lTime=tFile.GetHour()*10000+tFile.GetMinute()*100+tFile.GetSecond();
	}
	fileFind.Close();
	return bResult;
}

int CHHSetting::GetCheckCount()
{
	int i=0,nCount=0;
	for (;i<m_listShow.GetItemCount();i++)
	{
		if (m_listShow.GetCheck(i))
		{
			nCount++;
		}
	}
	return nCount;
}

void CHHSetting::OnBnClickedBtnOnekey()
{
	GetDlgItem(IDC_BTN_ONEKEY)->EnableWindow(FALSE);
	OnBnClickedBtnCompress();
//	OnBnClickedBtnBuildxml();
}
