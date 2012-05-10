// DlgOrgTrade.cpp : 实现文件
//

#include "stdafx.h"
#include "winunit.h"
#include "../public/GridList.h"
#include "TrdGrid.h"
#include "DlgOrgTrade.h"


// CDlgOrgTrade 对话框

IMPLEMENT_DYNAMIC(CDlgOrgTrade, CDialog)

CDlgOrgTrade::CDlgOrgTrade(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOrgTrade::IDD, pParent)
{
	
}

CDlgOrgTrade::~CDlgOrgTrade()
{
}

void CDlgOrgTrade::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TRADE, m_listTrade);
}


BEGIN_MESSAGE_MAP(CDlgOrgTrade, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TRADE, &CDlgOrgTrade::OnNMDblclkListTrade)
END_MESSAGE_MAP()


// CDlgOrgTrade 消息处理程序

BOOL CDlgOrgTrade::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化	
	m_listTrade.InsertColumn(0,_T("代码"),LVCFMT_CENTER,60 + 2);
	m_listTrade.InsertColumn(1,_T("名称"),LVCFMT_CENTER,60 + 2);
	m_listTrade.InsertColumn(2,_T("日期"),LVCFMT_CENTER,60 + 2);		
	m_listTrade.InsertColumn(3,_T("买/卖"),LVCFMT_CENTER,60 + 2);
	m_listTrade.InsertColumn(4,_T("数量(千万)"),LVCFMT_RIGHT,100 + 2);

	m_listTrade.ShowWindow(SW_HIDE);
	CRect rect;
	m_pGrid = new CTrdGrid();		
	m_pGrid->Create(NULL,NULL,WS_CHILD|WS_VISIBLE,CRect(),this,0);
	GetClientRect(rect);
	rect.top += 32;
	m_pGrid->CreateGrid(0,5,this,rect);	
	m_pGrid->SetHeadItemText(0,_T("代码"));
	m_pGrid->SetHeadItemText(1,_T("名称"));
	m_pGrid->SetHeadItemText(2,_T("日期"));
	m_pGrid->SetHeadItemText(3,_T("买/卖"));
	m_pGrid->SetHeadItemText(4,_T("数量(千万)"));	
	
	m_pGrid->SetRowHeigth(-1,24);
	m_pGrid->SetColumnWidth(0,60);
	m_pGrid->SetColumnWidth(1,60);
	m_pGrid->SetColumnWidth(2,60);
	m_pGrid->SetColumnWidth(3,60);
	m_pGrid->SetColumnWidth(4,120);
	m_pGrid->SetHeadRowHeigth(32);
	m_pGrid->SetFixedColumnCount(2);
	m_pGrid->SetItemFont(gpSkinManager->m_pFontReport);
	m_pGrid->SetHeadItemFont(gpSkinManager->m_pFontBig);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgOrgTrade::OnNMDblclkListTrade(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	if (m_listTrade.GetSelectionMark() == -1)
		return;
	int nSel = m_listTrade.GetSelectionMark();
	SStock * pStock;
	pStock = (SStock *)m_listTrade.GetItemData(nSel);
	if (pStock == NULL)
		return;
	
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;

	int nItem=pNMListView->iItem;
	
	if (pStock)
	{
		::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,0,DWORD_PTR(pStock));
	}

}

void CDlgOrgTrade::DoCommand(int c_nCmd)
{
	if (c_nCmd == 81)
	{
		GetData();
	}
}

void CDlgOrgTrade::GetData()
{
	char acFile[MAX_PATH];
	int nReadLen = 0;	
	sprintf(acFile,"%s\\0.0.0.%d.%d",gpData->m_acDataPath,MACRODATA,11);
	FILE * f;
	f = fopen(acFile,"rb");
	if (f)	
	{
		m_listTrade.DeleteAllItems();
		char *p = (char *)malloc(1024 * 128);
		int nLen = fread(p,1,1024*128,f);
		fclose(f);
		int nOffset = 24;
		char acCode[16];
		char chType;
		int nDay = 0;
		double dSl = 0;
		while(nOffset  < nLen)
		{
			strncpy(acCode,p + nOffset,6);		nOffset += 6;
			acCode[6] = 0;
			nDay = *(int *)(p + nOffset);		nOffset += sizeof(int);
			chType = *(p + nOffset);			nOffset += 1;
			dSl = *(double *)(p + nOffset);		nOffset += sizeof(double);
			SStock * pStock = gpData->GetStock(acCode);
			CString str;			
			if (pStock)
			{				
				m_pGrid->InsertRow();
				m_pGrid->SetItemText(m_pGrid->GetRowCount()-1,0,toUnicodeString(acCode,strlen(acCode)));
				m_pGrid->SetRowData(m_pGrid->GetRowCount()-1,(DWORD_PTR)pStock);				
				m_pGrid->SetItemText(m_pGrid->GetRowCount()-1,1,pStock->m_strName);
				str.Format(_T("%d"),nDay);				
				m_pGrid->SetItemText(m_pGrid->GetRowCount()-1,2,str);
				if (chType == 'S')
				{					
					m_pGrid->SetItemText(m_pGrid->GetRowCount()-1,3,_T("卖出"));
				}
				else
				{					
					m_pGrid->SetItemText(m_pGrid->GetRowCount()-1,3,_T("买入"));
				}
				str.Format(_T("%.3f"),dSl/10000);
				m_pGrid->SetItemText(m_pGrid->GetRowCount()-1,4,str);
			}
		}
		free(p);
	}
}