// DlgSort.cpp : 实现文件
//

#include "stdafx.h"
#include "winunit.h"
#include "DlgSort.h"


// CDlgSort 对话框

IMPLEMENT_DYNAMIC(CDlgSort, CDialog)

CDlgSort::CDlgSort(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSort::IDD, pParent)
{
	m_usSortType = 81;
}

CDlgSort::~CDlgSort()
{
}

void CDlgSort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_A, m_listA);
	DDX_Control(pDX, IDC_LIST_B, m_listB);
	DDX_Control(pDX, IDC_LIST_BUY, m_listBuy);
	DDX_Control(pDX, IDC_LIST_SELL, m_listSell);
	DDX_Control(pDX, IDC_LIST_TRADEAREA_UP, m_listTrup);
	DDX_Control(pDX, IDC_LIST_TRADEAREA_DOWN, m_listTrdown);
}


BEGIN_MESSAGE_MAP(CDlgSort, CDialog)
	ON_WM_SIZE()
	ON_WM_MEASUREITEM()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_A, &CDlgSort::OnNMDblclkListA)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_B, &CDlgSort::OnNMDblclkListB)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BUY, &CDlgSort::OnNMDblclkListBuy)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SELL, &CDlgSort::OnNMDblclkListSell)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TRADEAREA_DOWN, &CDlgSort::OnNMDblclkListTradeareaDown)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TRADEAREA_UP, &CDlgSort::OnNMDblclkListTradeareaUp)
END_MESSAGE_MAP()


// CDlgSort 消息处理程序

BOOL CDlgSort::OnInitDialog()
{
	__super::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_listA.Init();
	m_listB.Init();
	m_listBuy.Init();
	m_listSell.Init();
	m_listTrup.Init();
	m_listTrdown.Init();
	m_listA.InsertColumn(0,STR_JC,LVCFMT_CENTER,60 + 2);
	m_listA.InsertColumn(1,STR_XJ,LVCFMT_CENTER,50 + 2);
	m_listA.InsertColumn(2,STR_ZDF,LVCFMT_CENTER,50 + 2);		
	m_listA.InsertColumn(3,STR_HSL,LVCFMT_CENTER,50 + 2);
	m_listA.InsertColumn(4,STR_LB,LVCFMT_CENTER,46 + 2);
	m_listA.InsertColumn(5,STR_ZHANGSU,LVCFMT_CENTER,50 + 2);

	m_listB.InsertColumn(0,STR_JC,LVCFMT_CENTER,60 + 2);
	m_listB.InsertColumn(1,STR_XJ,LVCFMT_CENTER,50 + 2);		
	m_listB.InsertColumn(2,STR_ZDF,LVCFMT_CENTER,50 + 2);		
	m_listB.InsertColumn(3,STR_HSL,LVCFMT_CENTER,50 + 2);
	m_listB.InsertColumn(4,STR_LB,LVCFMT_CENTER,46 + 2);
	m_listB.InsertColumn(5,STR_ZHANGSU,LVCFMT_CENTER,50 + 2);

	m_listBuy.InsertColumn(0,STR_JC,LVCFMT_CENTER,60 + 2);
	m_listBuy.InsertColumn(1,STR_XJ,LVCFMT_CENTER,55 + 2);
	m_listBuy.InsertColumn(2,STR_ZDF,LVCFMT_CENTER,50 + 2);		
	m_listBuy.InsertColumn(3,STR_HSL,LVCFMT_CENTER,70 + 2);
	m_listBuy.InsertColumn(4,STR_LB,LVCFMT_CENTER,70 + 2);

	m_listSell.InsertColumn(0,STR_JC,LVCFMT_CENTER,60 + 2);
	m_listSell.InsertColumn(1,STR_XJ,LVCFMT_CENTER,55 + 2);
	m_listSell.InsertColumn(2,STR_ZDF,LVCFMT_CENTER,50 + 2);		
	m_listSell.InsertColumn(3,STR_HSL,LVCFMT_CENTER,70 + 2);
	m_listSell.InsertColumn(4,STR_LB,LVCFMT_CENTER,70 + 2);

	m_listTrup.InsertColumn(0,STR_JC,LVCFMT_CENTER,60 + 2);
	m_listTrup.InsertColumn(1,STR_XJ,LVCFMT_CENTER,50 + 2);
	m_listTrup.InsertColumn(2,STR_ZDF,LVCFMT_CENTER,50 + 2);		
	m_listTrup.InsertColumn(3,STR_HSL,LVCFMT_CENTER,50 + 2);
	m_listTrup.InsertColumn(4,STR_LB,LVCFMT_CENTER,46 + 2);
	m_listTrup.InsertColumn(5,STR_ZHANGSU,LVCFMT_CENTER,50 + 2);

	m_listTrdown.InsertColumn(0,STR_JC,LVCFMT_CENTER,60 + 2);
	m_listTrdown.InsertColumn(1,STR_XJ,LVCFMT_CENTER,50 + 2);		
	m_listTrdown.InsertColumn(2,STR_ZDF,LVCFMT_CENTER,50 + 2);		
	m_listTrdown.InsertColumn(3,STR_HSL,LVCFMT_CENTER,50 + 2);
	m_listTrdown.InsertColumn(4,STR_LB,LVCFMT_CENTER,46 + 2);
	m_listTrdown.InsertColumn(5,STR_ZHANGSU,LVCFMT_CENTER,50 + 2);

	SetLayout();
	m_listA.PositionScrollBars();
	m_listB.PositionScrollBars();
	m_listBuy.PositionScrollBars();
	m_listSell.PositionScrollBars();
	m_listTrup.PositionScrollBars();
	m_listTrdown.PositionScrollBars();

	SetStockList();

	SetTimer(101,1000*25,NULL);
	//FreshData();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CDlgSort::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	return __super::PreTranslateMessage(pMsg);
}

void CDlgSort::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_listA)
	{
		SetLayout();
		m_listA.PositionScrollBars();
		m_listB.PositionScrollBars();
		m_listBuy.PositionScrollBars();
		m_listSell.PositionScrollBars();
		m_listTrup.PositionScrollBars();
		m_listTrdown.PositionScrollBars();
	}
}

void CDlgSort::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDCtl == IDC_LIST_A || nIDCtl == IDC_LIST_B || nIDCtl == IDC_LIST_BUY || nIDCtl == IDC_LIST_SELL || nIDCtl == IDC_LIST_TRADEAREA_UP || nIDCtl == IDC_LIST_TRADEAREA_DOWN)
		lpMeasureItemStruct->itemHeight = 24;
	__super::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CDlgSort::OnNMDblclkListA(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	if (m_listA.GetSelectionMark() == -1)
		return;
	int nSel = m_listA.GetSelectionMark();
	SStock * pStock;
	pStock = (SStock *)m_listA.GetItemData(nSel);
	if (pStock == NULL)
		return;
	
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;

	int nItem=pNMListView->iItem;
	
	if (pStock)
	{
		::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,0,DWORD_PTR(pStock));
	}
}

void CDlgSort::OnNMDblclkListB(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if (m_listB.GetSelectionMark() == -1)
		return;
	int nSel = m_listB.GetSelectionMark();
	SStock * pStock;
	pStock = (SStock *)m_listB.GetItemData(nSel);
	if (pStock == NULL)
		return;
	
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;

	int nItem=pNMListView->iItem;
	
	if (pStock)
	{
		::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,0,DWORD_PTR(pStock));
	}

}

void CDlgSort::SetLayout()
{
	CRect rectClient;
	GetClientRect(rectClient);

	CRect rect;
	rect = rectClient;
	rect.bottom = rectClient.Height()/3 - 18;
	rect.top += 24;	
	rect.left += 4;
	rect.right = rect.left + (rectClient.Width() - 24 * 2 - 4 * 2)/2;
	m_listA.MoveWindow(rect);

	rect.left = rectClient.Width()/2 + 4;
	rect.right = rectClient.right - 24;
	m_listB.MoveWindow(rect);

	rect = rectClient;
	rect.top = rectClient.Height()/3;
	rect.bottom = rect.top + rectClient.Height()/3 - 18;
	rect.top += 24;	
	rect.left += 4;
	rect.right = rect.left + (rectClient.Width() - 24 * 2 - 4 * 2)/2;
	m_listBuy.MoveWindow(rect);

	rect.left = rectClient.Width()/2 + 4;
	rect.right = rectClient.right - 18;
	m_listSell.MoveWindow(rect);

	rect = rectClient;
	rect.top = rectClient.Height()*2/3;	
	rect.bottom -= 24;
	rect.top += 24;	
	rect.left += 4;
	rect.right = rect.left + (rectClient.Width() - 24 * 2 - 4 * 2)/2;
	m_listTrup.MoveWindow(rect);

	rect.left = rectClient.Width()/2 + 4;
	rect.right = rectClient.right - 24;
	m_listTrdown.MoveWindow(rect);

}
void CDlgSort::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 __super::OnPaint()

	CFont * pOldFont = dc.SelectObject(gpSkinManager->m_pFontBig);
	
	int nOldMode = dc.SetBkMode(TRANSPARENT);
	CRect rectClient;
	GetClientRect(rectClient);
	rectClient.bottom = rectClient.top + 24;
	rectClient.right = rectClient.Width()/2;
	dc.DrawText(_T("价量异动"),rectClient,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	
	GetClientRect(rectClient);
	rectClient.bottom = rectClient.top + 24;
	rectClient.left = rectClient.Width()/2;
	dc.DrawText(_T("牛栏马圈"),rectClient,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	GetClientRect(rectClient);
	rectClient.top = rectClient.top + rectClient.Height()/3;
	rectClient.bottom = rectClient.top + 24;	
	rectClient.right = rectClient.Width()/2;
	dc.DrawText(_T("主力买入"),rectClient,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	
	GetClientRect(rectClient);
	rectClient.top = rectClient.top + rectClient.Height()/3;
	rectClient.bottom = rectClient.top + 24;
	rectClient.left = rectClient.Width()/2;
	dc.DrawText(_T("主力卖出"),rectClient,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	GetClientRect(rectClient);
	rectClient.top = rectClient.top + rectClient.Height() * 2/3;
	rectClient.bottom = rectClient.top + 24;	
	rectClient.right = rectClient.Width()/2;
	dc.DrawText(_T("多头能量"),rectClient,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	
	GetClientRect(rectClient);
	rectClient.top = rectClient.top + rectClient.Height() * 2/3;
	rectClient.bottom = rectClient.top + 24;
	rectClient.left = rectClient.Width()/2;
	dc.DrawText(_T("空头能量"),rectClient,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	dc.SetBkMode(nOldMode);
	dc.SelectObject(pOldFont);
}

void CDlgSort::SetStockList()
{
	FILE * f;
	char acFile[256];
	int nCount;
	unsigned short usType;
	char acBuf[256];
	SStock * pStock;

	m_listA.DeleteAllItems();
	m_listB.DeleteAllItems();
	m_listBuy.DeleteAllItems();
	m_listSell.DeleteAllItems();
	m_listTrup.DeleteAllItems();
	m_listTrdown.DeleteAllItems();

	sprintf(acFile,"%s\\collectsort.%d",gpData->m_acDataPath,m_usSortType);
	f = fopen(acFile,"rb");
	if (!f)
		return;
	nCount = 0;
	while(true)
	{
		if (fread(&usType,1,sizeof(short),f) != sizeof(short))
		{
			fclose(f);
			return;
		}
		if (fread(&nCount,1,sizeof(int),f) != sizeof(int))
		{
			fclose(f);
			return;
		}
		int nZs;
		CString strText;
		for(int n=0; n<nCount; n++)
		{
			if (fread(acBuf,1,9,f) != 9)
			{
				fclose(f);
				return;
			}
			acBuf[9] = 0;
			pStock = gpData->GetStock(acBuf);

			if (fread(acBuf,1,sizeof(int) * 5,f) != sizeof(int) * 5)
			{
				fclose(f);
				return;
			}

			if (pStock)
			{
				if (usType == 1)
				{
					m_listA.InsertItem(m_listA.GetItemCount(),gpData->GetStockValueByName(pStock,STR_JC));
					m_listA.SetItemData(m_listA.GetItemCount()-1,DWORD_PTR(pStock));
					pStock->m_sQuote.zjjg = *(int *)(acBuf);
					pStock->m_sQuote.zdfd = *(int *)(acBuf + sizeof(int));
					pStock->m_sQuote.lb = *(int *)(acBuf + sizeof(int) * 2);
					pStock->m_sQuote.cjsl = *(int *)(acBuf + sizeof(int) * 3);
					nZs = *(int *)(acBuf + sizeof(int)*4);
				}
				else
				if (usType == 2)
				{
					m_listB.InsertItem(m_listB.GetItemCount(),gpData->GetStockValueByName(pStock,STR_JC));
					m_listB.SetItemData(m_listB.GetItemCount()-1,DWORD_PTR(pStock));
					pStock->m_sQuote.zjjg = *(int *)(acBuf);
					pStock->m_sQuote.zdfd = *(int *)(acBuf + sizeof(int));
					pStock->m_sQuote.lb = *(int *)(acBuf + sizeof(int) * 2);
					pStock->m_sQuote.cjsl = *(int *)(acBuf + sizeof(int) * 3);
					nZs = *(int *)(acBuf + sizeof(int)*4);
				}
				else
				if (usType == 3)
				{
					m_listBuy.InsertItem(m_listBuy.GetItemCount(),gpData->GetStockValueByName(pStock,STR_JC));
					m_listBuy.SetItemData(m_listBuy.GetItemCount()-1,DWORD_PTR(pStock));
					pStock->m_sQuote.zjjg = *(int *)(acBuf);
					pStock->m_sQuote.zdfd = *(int *)(acBuf + sizeof(int));
					pStock->m_sQuote.lb = *(int *)(acBuf + sizeof(int) * 2);
					pStock->m_sQuote.cjsl = *(int *)(acBuf + sizeof(int) * 3);
				}
				else
				if (usType == 4)
				{
					m_listSell.InsertItem(m_listSell.GetItemCount(),gpData->GetStockValueByName(pStock,STR_JC));
					m_listSell.SetItemData(m_listSell.GetItemCount()-1,DWORD_PTR(pStock));
					pStock->m_sQuote.zjjg = *(int *)(acBuf);
					pStock->m_sQuote.zdfd = *(int *)(acBuf + sizeof(int));
					pStock->m_sQuote.lb = *(int *)(acBuf + sizeof(int) * 2);
					pStock->m_sQuote.cjsl = *(int *)(acBuf + sizeof(int) * 3);
				}

				else
				if (usType == 5)
				{
					m_listTrup.InsertItem(m_listTrup.GetItemCount(),gpData->GetStockValueByName(pStock,STR_JC));
					m_listTrup.SetItemData(m_listTrup.GetItemCount()-1,DWORD_PTR(pStock));
					pStock->m_sQuote.zjjg = *(int *)(acBuf);
					pStock->m_sQuote.zdfd = *(int *)(acBuf + sizeof(int));
					pStock->m_sQuote.lb = *(int *)(acBuf + sizeof(int) * 2);
					pStock->m_sQuote.cjsl = *(int *)(acBuf + sizeof(int) * 3);
					nZs = *(int *)(acBuf + sizeof(int)*4);
				}

			}
		}
	}			
}

void CDlgSort::FreshData()
{
	SetStockList();

	SStock * pItem;
	for(int n=0; n<m_listA.GetItemCount(); n++)
	{
		pItem = (SStock *)m_listA.GetItemData(n);
		if (!pItem)
			continue;
		CString str;
		
		str = gpData->GetStockValueByName(pItem,STR_XJ);
		m_listA.SetItemText(n,1,str);
	
		str = gpData->GetStockValueByName(pItem,STR_ZDF);
		if (str != _T("-"))
			str += "%";
		m_listA.SetItemText(n,2,str);
	
		str = gpData->GetStockValueByName(pItem,STR_HSL);
		m_listA.SetItemText(n,3,str);

		str = gpData->GetStockValueByName(pItem,STR_LB);
		m_listA.SetItemText(n,4,str);

		str = gpData->GetStockValueByName(pItem,STR_ZHANGSU);
		m_listA.SetItemText(n,5,str);
	}	

	for(int n=0; n<m_listB.GetItemCount(); n++)
	{
		pItem = (SStock *)m_listB.GetItemData(n);
		if (!pItem)
			continue;
		CString str;
		
		str = gpData->GetStockValueByName(pItem,STR_XJ);
		m_listB.SetItemText(n,1,str);
	
		str = gpData->GetStockValueByName(pItem,STR_ZDF);
		if (str != _T("-"))
			str += "%";
		m_listB.SetItemText(n,2,str);
	
		str = gpData->GetStockValueByName(pItem,STR_HSL);
		m_listB.SetItemText(n,3,str);

		str = gpData->GetStockValueByName(pItem,STR_LB);
		m_listB.SetItemText(n,4,str);

		str = gpData->GetStockValueByName(pItem,STR_ZHANGSU);
		m_listB.SetItemText(n,5,str);
	}	

	for(int n=0; n<m_listBuy.GetItemCount(); n++)
	{
		pItem = (SStock *)m_listBuy.GetItemData(n);
		if (!pItem)
			continue;
		CString str;
		
		str = gpData->GetStockValueByName(pItem,STR_XJ);
		m_listBuy.SetItemText(n,1,str);
	
		str = gpData->GetStockValueByName(pItem,STR_ZDF);
		if (str != _T("-"))
			str += "%";
		m_listBuy.SetItemText(n,2,str);
	
		str = gpData->GetStockValueByName(pItem,STR_HSL);
		m_listBuy.SetItemText(n,3,str);

		str = gpData->GetStockValueByName(pItem,STR_LB);
		m_listBuy.SetItemText(n,4,str);
	}	

	for(int n=0; n<m_listSell.GetItemCount(); n++)
	{
		pItem = (SStock *)m_listSell.GetItemData(n);
		if (!pItem)
			continue;
		CString str;
		
		str = gpData->GetStockValueByName(pItem,STR_XJ);
		m_listSell.SetItemText(n,1,str);
	
		str = gpData->GetStockValueByName(pItem,STR_ZDF);
		if (str != _T("-"))
			str += "%";
		m_listSell.SetItemText(n,2,str);
	
		str = gpData->GetStockValueByName(pItem,STR_HSL);
		m_listSell.SetItemText(n,3,str);

		str = gpData->GetStockValueByName(pItem,STR_LB);
		m_listSell.SetItemText(n,4,str);
	}	

	for(int n=0; n<m_listTrup.GetItemCount(); n++)
	{
		pItem = (SStock *)m_listTrup.GetItemData(n);
		if (!pItem)
			continue;
		CString str;
		
		str = gpData->GetStockValueByName(pItem,STR_XJ);
		m_listTrup.SetItemText(n,1,str);
	
		str = gpData->GetStockValueByName(pItem,STR_ZDF);
		if (str != _T("-"))
			str += "%";
		m_listTrup.SetItemText(n,2,str);
	
		str = gpData->GetStockValueByName(pItem,STR_HSL);
		m_listTrup.SetItemText(n,3,str);

		str = gpData->GetStockValueByName(pItem,STR_LB);
		m_listTrup.SetItemText(n,4,str);

		str = gpData->GetStockValueByName(pItem,STR_ZHANGSU);
		m_listTrup.SetItemText(n,5,str);
	}	

	for(int n=0; n<m_listTrdown.GetItemCount(); n++)
	{
		pItem = (SStock *)m_listTrdown.GetItemData(n);
		if (!pItem)
			continue;
		CString str;
		
		str = gpData->GetStockValueByName(pItem,STR_XJ);
		m_listTrdown.SetItemText(n,1,str);
	
		str = gpData->GetStockValueByName(pItem,STR_ZDF);
		if (str != _T("-"))
			str += "%";
		m_listTrdown.SetItemText(n,2,str);
	
		str = gpData->GetStockValueByName(pItem,STR_HSL);
		m_listTrdown.SetItemText(n,3,str);

		str = gpData->GetStockValueByName(pItem,STR_LB);
		m_listTrdown.SetItemText(n,4,str);

		str = gpData->GetStockValueByName(pItem,STR_ZHANGSU);
		m_listTrdown.SetItemText(n,5,str);
	}	

}
void CDlgSort::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 101)
	{
		if (IsWindowVisible())
		{
			//if (gpData->m_nDateClose < gpData->m_nDateOpen)
			//	GetData();
		}
	}
	__super::OnTimer(nIDEvent);
}

void CDlgSort::GetData()
{
	char acReq[256];
	SCommHead * pHead;
	pHead = (SCommHead *)acReq;

	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = gpData->NewSeq();
	pHead->m_usReqCount = 1;
	*(unsigned short *)(acReq + sizeof(SCommHead)) = COLLECTSORT;	//综合排行
	*(unsigned short *)(acReq + sizeof(SCommHead) + sizeof(unsigned short)) = m_usSortType;//类型,81,上海深圳A,82,上海A,83,深圳A
	pHead->m_head.SetLength(sizeof(unsigned short) * 4);
	pHead->m_usFuncNo = COLLECTSORT;
	int nLen = pHead->m_head.GetLength() + 8;

	gpSendFunc(this,acReq,nLen,NULL,0,false);
}

void CDlgSort::DoCommand(int c_nCmd)
{
	if (c_nCmd == 81)
	{
		m_usSortType = c_nCmd;
		GetData();
	}
}

void CDlgSort::ResetSkin()
{
	m_listA.Invalidate();
	m_listB.Invalidate();
	m_listTrup.Invalidate();
	m_listTrdown.Invalidate();
	this->m_listBuy.Invalidate();
	m_listSell.Invalidate();
	Invalidate();
}
void CDlgSort::OnNMDblclkListBuy(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	if (m_listBuy.GetSelectionMark() == -1)
		return;
	int nSel = m_listBuy.GetSelectionMark();
	SStock * pStock;
	pStock = (SStock *)m_listBuy.GetItemData(nSel);
	if (pStock == NULL)
		return;
	
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;

	int nItem=pNMListView->iItem;
	
	if (pStock)
	{
		::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,0,DWORD_PTR(pStock));
	}

}

void CDlgSort::OnNMDblclkListSell(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	if (m_listSell.GetSelectionMark() == -1)
		return;
	int nSel = m_listSell.GetSelectionMark();
	SStock * pStock;
	pStock = (SStock *)m_listSell.GetItemData(nSel);
	if (pStock == NULL)
		return;
	
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;

	int nItem=pNMListView->iItem;
	
	if (pStock)
	{
		::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,0,DWORD_PTR(pStock));
	}
}

void CDlgSort::OnNMDblclkListTradeareaDown(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if (m_listTrdown.GetSelectionMark() == -1)
		return;
	int nSel = m_listTrdown.GetSelectionMark();
	SStock * pStock;
	pStock = (SStock *)m_listTrdown.GetItemData(nSel);
	if (pStock == NULL)
		return;
	
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;

	int nItem=pNMListView->iItem;
	
	if (pStock)
	{
		::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,0,DWORD_PTR(pStock));
	}

}

void CDlgSort::OnNMDblclkListTradeareaUp(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	if (m_listTrup.GetSelectionMark() == -1)
		return;
	int nSel = m_listTrup.GetSelectionMark();
	SStock * pStock;
	pStock = (SStock *)m_listTrup.GetItemData(nSel);
	if (pStock == NULL)
		return;
	
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;

	int nItem=pNMListView->iItem;
	
	if (pStock)
	{
		::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,0,DWORD_PTR(pStock));
	}

}
