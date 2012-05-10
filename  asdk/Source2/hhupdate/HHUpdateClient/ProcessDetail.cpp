// ProcessDetail.cpp : 实现文件
//

#include "stdafx.h"
#include "HHUpdateClient.h"
#include "ProcessDetail.h"
#include ".\processdetail.h"



// CProcessDetail 对话框

IMPLEMENT_DYNAMIC(CProcessDetail, CDialog)
CProcessDetail::CProcessDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessDetail::IDD, pParent)
{
	
}

CProcessDetail::~CProcessDetail()
{
}

void CProcessDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl_ShowProcess);
	DDX_Control(pDX, IDC_BTN_ENDPROCESS, m_btnEndProcess);
	DDX_Control(pDX, IDC_BTN_ENDALLPROCESS, m_btnEndAllProcess);
}


BEGIN_MESSAGE_MAP(CProcessDetail, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BTN_ENDPROCESS, OnBnClickedBtnEndprocess)
	ON_BN_CLICKED(IDC_BTN_ENDALLPROCESS, OnBnClickedBtnEndallprocess)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CProcessDetail 消息处理程序

void CProcessDetail::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateWindow();
	*pResult = 0;
}

BOOL CProcessDetail::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	CMenu* pMenu = this->GetSystemMenu(FALSE);//系统菜单
	pMenu->ModifyMenu(SC_CLOSE,MF_BYCOMMAND | MF_GRAYED );//禁用关闭按钮
	InitList();
	if (m_ListMD.GetCount()>0)
	{
		InitListData();
	}
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	SetTimer(11111,1000,NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CProcessDetail::InitList()
{
	LVCOLUMN lv;
	lv.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lv.fmt	= LVCFMT_LEFT;	
	lv.cx	= 100;
	lv.pszText = _T("进程");
	m_ListCtrl_ShowProcess.InsertColumn(0,&lv);//LVM_INSERTCOLUMN 添加列
	lv.cx	= 200;
	lv.pszText = _T("占用路径");	
	m_ListCtrl_ShowProcess.InsertColumn(1,&lv);
	lv.cx	= 80;
	lv.pszText = _T("PID");	
	m_ListCtrl_ShowProcess.InsertColumn(1,&lv);
	lv.cx	= 200;
	lv.pszText = _T("进程路径");	
	m_ListCtrl_ShowProcess.InsertColumn(1,&lv);



	//m_ListCtrl_ShowProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_ListCtrl_ShowProcess.SetExtendedStyle(LVS_EX_INFOTIP|LVS_EX_REGIONAL|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_MULTIWORKAREAS|LVS_EX_CHECKBOXES);
}

void CProcessDetail::InitListData()
{
	
	LVITEM lvItem;
	lvItem.mask		= LVIF_TEXT; 
	lvItem.iItem	= 0;
	lvItem.iSubItem = 0;
	m_ListCtrl_ShowProcess.DeleteAllItems();
	char szProcessName[NOR_SIZE]={0};
	int nPid=0;
	int nItem=0;
	for (int i = 0; i<m_ListMD.GetCount();i++)
	{
		lvItem.iItem = i;

		sprintf(szProcessName,"%s",m_ListMD.GetAt(m_ListMD.FindIndex(i)).ProcessName);
		lvItem.pszText = szProcessName;
		nItem = m_ListCtrl_ShowProcess.InsertItem(&lvItem);


		m_ListCtrl_ShowProcess.SetItemText(nItem,1,m_ListMD.GetAt(m_ListMD.FindIndex(i)).path);
		nPid = m_ListMD.GetAt(m_ListMD.FindIndex(i)).pid;
		sprintf(lvItem.pszText,"%d",nPid);
		m_ListCtrl_ShowProcess.SetItemText(nItem,2,lvItem.pszText);
		m_ListCtrl_ShowProcess.SetItemText(nItem,3,m_ListMD.GetAt(m_ListMD.FindIndex(i)).ProcessPath);
	}
	
	
	for (int i = 0;i<m_ListCtrl_ShowProcess.GetItemCount();i++)
	{
		m_ListCtrl_ShowProcess.SetCheck(i,FALSE);		
	}
}

void CProcessDetail::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
}

bool CProcessDetail::KillProcess(DWORD dwPid)
{

	HANDLE h;
	if( 0==dwPid ) return false;

	h = OpenProcess( PROCESS_ALL_ACCESS,false,dwPid );
	//杀进程
	if (h)
	{
		if( !TerminateProcess(h,0) ) 
		{
			CloseHandle( h );
			return false;
		}
		CloseHandle( h );
	}
	else
	{
		return false;
	}
	
	return true;
}

void CProcessDetail::OnBnClickedBtnEndprocess()
{
	CString strPid="";
// 	int n = m_ListCtrl_ShowProcess.GetSelectedCount();
// 	int nMark = m_ListCtrl_ShowProcess.GetSelectionMark();
// 	if (nMark<0)
// 	{
// 		return;
// 	}
// 
// 	for (int i=0;i<n;i++)
// 	{
// 		m_ListCtrl_ShowProcess.SetCheck(nMark,FALSE);
// 		POSITION pos=m_ListCtrl_ShowProcess.GetFirstSelectedItemPosition();
// 		nMark = m_ListCtrl_ShowProcess.GetNextSelectedItem(pos);
// 	}
// 	do 
// 	{
// 		m_ListCtrl_ShowProcess.GetNextSelectedItem()
// 	} while (m_ListCtrl_ShowProcess.);



	//SprintfCList();
	int n = m_ListCtrl_ShowProcess.GetItemCount();
	for (int i = 0;i<n;)
	{
		if (m_ListCtrl_ShowProcess.GetCheck(i))
		{
			strPid = m_ListCtrl_ShowProcess.GetItemText(i,2);
			if (KillProcess(atoi(strPid)))
			{
				int p = m_ListMD.GetCount();
				for (int j=0;j<p;)
				{
					if (atoi(strPid)==m_ListMD.GetAt(m_ListMD.FindIndex(j)).pid)
					{
						m_ListMD.RemoveAt(m_ListMD.FindIndex(j));
						p--;
						
					}
					else
					{
						j++;
					}
				}
				
			

			}
			else
			{
				i++;
			}
		}
		else
		{
			i++;
		}
		n = m_ListCtrl_ShowProcess.GetItemCount();
	}
	
	//SprintfCList();
	InitListData();
		
}

void CProcessDetail::OnBnClickedBtnEndallprocess()
{
	for (int i = m_ListCtrl_ShowProcess.GetItemCount()-1;i>=0;i--)
	{
		CString strPid = m_ListCtrl_ShowProcess.GetItemText(i,2);
		if (KillProcess(atoi(strPid)))
		{
			//Sleep(1000);
		}
	}
}

void CProcessDetail::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

void CProcessDetail::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent==11111)
	{
		if (m_ListCtrl_ShowProcess.GetItemCount()>0)
		{
			GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
			KillTimer(nIDEvent);
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CProcessDetail::SprintfCList()
{

	for (int i = 0; i<m_ListMD.GetCount();i++)
	{
		TRACE3("%s--%s--%d\n",m_ListMD.GetAt(m_ListMD.FindIndex(i)).ProcessName,
				m_ListMD.GetAt(m_ListMD.FindIndex(i)).path,
				m_ListMD.GetAt(m_ListMD.FindIndex(i)).pid);
	}
	TRACE("------------------------------------------------------------------------");
}
