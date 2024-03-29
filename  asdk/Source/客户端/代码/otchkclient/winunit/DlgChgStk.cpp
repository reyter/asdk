// DlgChgStk.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgChgStk.h"

// CDlgChgStk 对话框

IMPLEMENT_DYNAMIC(CDlgChgStk, CDialog)

CDlgChgStk::CDlgChgStk(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChgStk::IDD, pParent)
{
	m_bFixed = false;
	m_strMemo = _T("注：系统帮您选择出同您手中所持有股票市值相当且相对强势的股票");
	m_nTopIndexLast = -1;
	m_nCountPageLast = -1;
}

CDlgChgStk::~CDlgChgStk()
{
}

void CDlgChgStk::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STOCKS, m_listStocks);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);	
	DDX_Control(pDX, IDC_BTN_SAME_VALUE, m_btnValue);
	DDX_Control(pDX, IDC_BTN_SAME_INDUSTRY, m_btnIndu);
	DDX_Control(pDX, IDC_BTN_SAME_PE, m_btnPE);
	DDX_Control(pDX, IDC_BTN_SAME_PRICE, m_btnSamePrice);
	DDX_Control(pDX, IDC_BTN_SAME_AREA, m_btnSameArea);
}


BEGIN_MESSAGE_MAP(CDlgChgStk, CDialog)
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDC_BTN_ADD, &CDlgChgStk::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_SAME_PE, &CDlgChgStk::OnBnClickedBtnSamePe)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_SAME_VALUE, &CDlgChgStk::OnBnClickedBtnSameValue)
	ON_BN_CLICKED(IDC_BTN_SAME_INDUSTRY, &CDlgChgStk::OnBnClickedBtnSameIndustry)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_STOCKS, &CDlgChgStk::OnNMDblclkListStocks)
	ON_BN_CLICKED(IDC_BTN_SAME_PRICE, &CDlgChgStk::OnBnClickedBtnSamePrice)
	ON_BN_CLICKED(IDC_BTN_SAME_AREA, &CDlgChgStk::OnBnClickedBtnSameArea)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgChgStk 娑堟伅澶勭悊绋嬪簭

BOOL CDlgChgStk::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_listStocks.Init();

	m_hBmp = gpSkinManager->LoadSpecialBmp(ID_RB_UNDER_BTN_BACK);
	m_hBmpHead = gpSkinManager->LoadSpecialBmp(ID_RB_UNDER_TITLE_BACK);
	CSize size = gpSkinManager->GetBmpSize(m_hBmpHead);
	m_nHeadHeight = size.cy;
	size = gpSkinManager->GetBmpSize(m_hBmp);
	m_nBtnHeight = size.cy;
	m_nBtnWidth = size.cx;
	if (m_nBtnWidth < 10)
		m_nBtnWidth = 72;

	LONG lStyle;
	lStyle = GetWindowLong(m_listStocks.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle |= LVS_SHOWSELALWAYS;
	SetWindowLong(m_listStocks.m_hWnd, GWL_STYLE, lStyle);//设置style
	(void)m_listStocks.SetExtendedStyle( LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP);// | LVS_EX_CHECKBOXES);

	m_listStocks.InsertColumn(0,STR_DM,LVCFMT_CENTER,60);
	m_listStocks.InsertColumn(1,STR_JC,LVCFMT_CENTER,60);	
	m_listStocks.InsertColumn(2,STR_XJ,LVCFMT_CENTER,55);
	m_listStocks.InsertColumn(3,STR_SYL,LVCFMT_CENTER,80);		
	m_listStocks.InsertColumn(4,STR_SYLYC,LVCFMT_CENTER,80);
	m_listStocks.InsertColumn(5,STR_JGCG,LVCFMT_CENTER,80);
	m_listStocks.InsertColumn(6,STR_ZSZ,LVCFMT_CENTER,80);
	m_listStocks.InsertColumn(7,STR_DIAGNOSE,LVCFMT_CENTER,80);
	m_listStocks.InsertColumn(8,STR_INDUSTRYNAME,LVCFMT_CENTER,120);
	
	m_btnAdd.SetBorder(false);
	m_btnAdd.SetBmpPos(3);
	m_btnAdd.SetUserCursor(LoadCursor(NULL,IDC_HAND));

	m_btnValue.SetBorder(false);
	m_btnValue.SetBmpPos(3);
	m_btnValue.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);

	m_btnIndu.SetBorder(false);
	m_btnIndu.SetBmpPos(3);
	m_btnIndu.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);

	m_btnPE.SetBorder(false);
	m_btnPE.SetBmpPos(3);	
	m_btnPE.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);

	m_btnSamePrice.SetBorder(false);
	m_btnSamePrice.SetBmpPos(3);	
	m_btnSamePrice.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);

	m_btnSameArea.SetBorder(false);
	m_btnSameArea.SetBmpPos(3);	
	m_btnSameArea.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	
	m_btnAdd.SetFont(gpSkinManager->GetButtonFont());
	m_btnValue.SetFont(gpSkinManager->GetButtonFont());
	m_btnIndu.SetFont(gpSkinManager->GetButtonFont());
	m_btnPE.SetFont(gpSkinManager->GetButtonFont());
	m_btnSamePrice.SetFont(gpSkinManager->GetButtonFont());
	m_btnSameArea.SetFont(gpSkinManager->GetButtonFont());
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgChgStk::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加控件通知处理程序代码
	int nHeight = gpSkinManager->GetFontHeight(gpSkinManager->GetListFont());
	if (nIDCtl == IDC_LIST_STOCKS)
		lpMeasureItemStruct->itemHeight = nHeight + 8;

	//if (nIDCtl == IDC_LIST_STOCKS)
	//	lpMeasureItemStruct->itemHeight = LIST_HEIGHT;

	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CDlgChgStk::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_listStocks.GetSelectionMark() == -1)
		return;
	int nSel = m_listStocks.GetSelectionMark();
	SStock * pStock = (SStock *)m_listStocks.GetItemData(nSel);
	if (pStock)
	{
		char acCode[7];
		strncpy(acCode,pStock->m_sQuote.szStockCode,6);
		acCode[6] = 0;
		::PostMessage(gpData->m_hwndMain,WM_ADD_STOCK_TO_GROUP,0,atoi(acCode));//DWORD_PTR(pStock));
	}
}

void CDlgChgStk::OnBnClickedBtnSamePe()
{
	// TODO:: 在此添加控件通知处理程序代码
	m_btnValue.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnIndu.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnPE.SetBMPFill(TRUE,m_hBmp,m_hBmp);
	m_btnSamePrice.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnSameArea.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);

	m_strMemo.Format(_T("注：系统帮您选择出同您手中所持有股票(%s %s)PE相当且相对强势的股票"),m_strStockName,m_strStockCode);
	//m_btnPE.SetToolTipText(&m_strMemo,TRUE);
	SetList(3);
	Invalidate();
}

void CDlgChgStk::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_btnPE)
	{
		SetLayout();
		m_listStocks.PositionScrollBars();
	}
}

BOOL CDlgChgStk::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(rect);
	pDC->FillRect(rect,&CBrush(gpSkinManager->getColor(BKCOLOR)));
	rect.bottom = rect.top + m_nHeadHeight;
	gpSkinManager->StretchIntoRectImage(m_hBmpHead,pDC,rect);
	return true;
	/*
	CRect rect;
	CBrush brush(gpSkinManager->getColor(CHGSTKBACKCOLOR));
	
	GetClientRect(rect);
	pDC->FillRect(rect,&brush);
	
	GetClientRect(rect);
	rect.bottom = rect.top + 30;
	rect.left += 100;
	int nOldMode = pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(gpSkinManager->getColor(BTNTEXTCOLOR));
	CFont * pOldFont = pDC->SelectObject(gpSkinManager->m_pFontGraph);
	pDC->DrawText(m_strMemo,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	pDC->SelectObject(pOldFont);
	pDC->SetBkMode(nOldMode);

	CPen pen(PS_SOLID,1,0x758397);
	CPen * pOldPen = pDC->SelectObject(&pen);
	GetClientRect(rect);
	int n = 1;
	while(n * 39 < 5)//rect.Height())
	{
		pDC->MoveTo(rect.left,rect.top + n*39);
		pDC->LineTo(rect.left + 80,rect.top + n*39);
		n++;
	}
	pDC->SelectObject(pOldPen);
	return true;
	return CDialog::OnEraseBkgnd(pDC);*/
}

void CDlgChgStk::SetLayout()
{
	int nH = gpSkinManager->GetFontHeight(gpSkinManager->GetButtonFont());
	int nW = gpSkinManager->GetFontWidth(gpSkinManager->GetButtonFont(),_T("同行业换股"));
	m_nBtnHeight = nH + 4;
	m_nBtnWidth = nW + 8;
	m_nHeadHeight = nH + 8 + 8;

	CRect rect;
	GetClientRect(rect);
	int nRight = rect.right;
	rect.left += 4;
	rect.bottom = rect.top + (m_nHeadHeight - m_nBtnHeight)/2 + m_nBtnHeight;
	rect.top = rect.bottom - m_nBtnHeight;
	rect.right = rect.left + m_nBtnWidth;
	m_btnIndu.MoveWindow(rect);

	rect.left += m_nBtnWidth;
	rect.right += m_nBtnWidth;
	m_btnSameArea.MoveWindow(rect);

	rect.left += m_nBtnWidth;
	rect.right += m_nBtnWidth;
	m_btnPE.MoveWindow(rect);
	rect.left += m_nBtnWidth;
	rect.right += m_nBtnWidth;
	m_btnValue.MoveWindow(rect);

	rect.left += m_nBtnWidth;
	rect.right += m_nBtnWidth;
	m_btnSamePrice.MoveWindow(rect);

	rect.left = nRight - m_nBtnWidth - 8;
	rect.right = rect.left + m_nBtnWidth;
	rect.bottom = rect.top + (m_nHeadHeight - m_nBtnHeight)/2 + m_nBtnHeight;
	rect.top = rect.bottom - m_nBtnHeight;
	m_btnAdd.MoveWindow(rect);

	GetClientRect(rect);
	rect.top += m_nHeadHeight;
	rect.left += 4;
	rect.right -= 18;
	rect.bottom -= 18 + 2;
	m_listStocks.MoveWindow(rect);

	m_listStocks.SetColumnWidth(0,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("1234567")));
	m_listStocks.SetColumnWidth(1,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("12345678")));
	m_listStocks.SetColumnWidth(2,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("12345678")));
	m_listStocks.SetColumnWidth(3,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("12345678")));
	nW = gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("预测市盈率"));
	if (nW < 80)
		nW = 80;
	m_listStocks.SetColumnWidth(4,nW);
	nW = gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("机构持股"));
	if (nW < 72)
		nW = 72;
	m_listStocks.SetColumnWidth(5,nW);
	m_listStocks.SetColumnWidth(6,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("12345678")));	
	m_listStocks.SetColumnWidth(7,nW);
	m_listStocks.SetColumnWidth(8,gpSkinManager->GetFontWidth(gpSkinManager->GetListFont(),_T("计算机及其附加设备等等")));

	this->Invalidate();
	//Invalidate();
	/*
	rect.top = rect.bottom + 4 + 12 + 4;
	rect.bottom = rect.top + 20;
	rect.right = rect.left + 80;
	m_btnAdd.MoveWindow(rect);*/
}
void CDlgChgStk::OnBnClickedBtnSameValue()
{
	// TODO: 在此处添加消息处理程序代码
	m_btnValue.SetBMPFill(TRUE,m_hBmp,m_hBmp);
	m_btnIndu.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnPE.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnSamePrice.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnSameArea.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);

	m_strMemo.Format(_T("注：系统帮您选择出同您手中所持有股票(%s %s)市值相当且相对强势的股票"),m_strStockName,m_strStockCode);
	//m_btnValue.SetToolTipText(&m_strMemo,TRUE);
	SetList(1);
	Invalidate();
}

void CDlgChgStk::OnBnClickedBtnSameIndustry()
{
	// TODO: 在此添加控件通知处理程序代码
	m_btnValue.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnIndu.SetBMPFill(TRUE,m_hBmp,m_hBmp);
	m_btnPE.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnSamePrice.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnSameArea.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);

	m_strMemo.Format(_T("注：系统帮您选择出同您手中所持有股票(%s %s)同行业且相对强势的股票"),m_strStockName,m_strStockCode);
	//m_btnIndu.SetToolTipText(&m_strMemo,TRUE);
	SetList(2);
	Invalidate();
}

void CDlgChgStk::SetList(int c_nType)
{
	if (m_strStockCode.IsEmpty())
		m_strStockCode = gpData->m_strStockCode;
	if (m_strStockCode.IsEmpty())
		return;

	SStock * pStock;
	pStock = gpData->GetStock(m_strStockCode);	
	if (pStock == NULL)
		return;
	std::vector<SStock *>::iterator iter;
	m_listStocks.DeleteAllItems();
	CString str;
	char acFileName[32];
	char *pData = NULL;
	if (c_nType == 2)
	{
		pData = m_acIndu;
		//sprintf(acFileName,"%.6s.%d",pStock->m_acCode,0x9016);
		/*
		for(iter = pStock->vpIndustry.begin(); iter != pStock->vpIndustry.end(); iter++)
		{
			str = (*iter)->m_acCode;
			m_listStocks.InsertItem(m_listStocks.GetItemCount(),str);
			m_listStocks.SetItemData(m_listStocks.GetItemCount()-1,DWORD_PTR(*iter));
		}*/
	}
	else
	if (c_nType == 1)
	{
		pData = m_acValue;
		//sprintf(acFileName,"%.6s.%d",pStock->m_acCode,0x9017);
		/*
		for(iter = pStock->vpValue.begin(); iter != pStock->vpValue.end(); iter++)
		{
			str = (*iter)->m_acCode;
			m_listStocks.InsertItem(m_listStocks.GetItemCount(),str);
			m_listStocks.SetItemData(m_listStocks.GetItemCount()-1,DWORD_PTR(*iter));
		}*/
	}
	else
	if (c_nType == 3)
	{
		pData = m_acPE;
		//sprintf(acFileName,"%.6s.%d",pStock->m_acCode,0x9018);		
		/*
		for(iter = pStock->vpPE.begin(); iter != pStock->vpPE.end(); iter++)
		{
			str = (*iter)->m_acCode;
			m_listStocks.InsertItem(m_listStocks.GetItemCount(),(str));
			m_listStocks.SetItemData(m_listStocks.GetItemCount()-1,DWORD_PTR(*iter));
		}*/
	}
	else
	if (c_nType == 4)
	{
		pData = m_acPrice;
		//sprintf(acFileName,"%.6s.%d",pStock->m_acCode,0x9019);
		/*
		for(iter = pStock->vpPrice.begin(); iter != pStock->vpPrice.end(); iter++)
		{
			str = (*iter)->m_acCode;
			m_listStocks.InsertItem(m_listStocks.GetItemCount(),(str));
			m_listStocks.SetItemData(m_listStocks.GetItemCount()-1,DWORD_PTR(*iter));
		}*/
	}
	else
	if (c_nType == 5)
	{
		pData = m_acArea;
		//sprintf(acFileName,"%.6s.%d",pStock->m_acCode,0x9020);
		/*
		for(iter = pStock->vpArea.begin(); iter != pStock->vpArea.end(); iter++)
		{
			str = (*iter)->m_acCode;
			m_listStocks.InsertItem(m_listStocks.GetItemCount(),(str));
			m_listStocks.SetItemData(m_listStocks.GetItemCount()-1,DWORD_PTR(*iter));
		}*/
	}
	char acCode[16];
	int nPos = 0;
	char acCodes[1024];
	memset(acCodes,0,sizeof(acCodes));
	while(nPos < strlen(pData))
	{
		strncpy(acCode,pData + nPos,6);	nPos += 7;
		acCode[6] = 0;
		if (strlen(acCodes) > 0)
			strcat(acCodes,",");
		strcat(acCodes,acCode);
		pStock = gpData->GetStock(acCode);
		if (pStock)
		{
			str = pStock->m_sQuote.szStockCode;
			m_listStocks.InsertItem(m_listStocks.GetItemCount(),str);
			m_listStocks.SetItemData(m_listStocks.GetItemCount()-1,DWORD_PTR(pStock));
		}
	}
	if (strlen(pData) >= 6)
		gpGetStockDatasFunc(acCodes,"stockquotebrief.f2510,stockquotebrief.f2547,stockquotebrief.f2509,stockquotebrief.f2531",4);
/*
	char acBuf[1024];
	char acCode[16];
	int nGet = gpData->GetFromFile(acFileName,acBuf,1024);
	for(int n=0; n<nGet/6; n++)
	{
		strncpy(acCode,acBuf + n*6,6);
		acCode[6] = 0;
		pStock = gpData->GetStock(acCode);
		if (pStock)
		{
			str = pStock->m_acCode;
			m_listStocks.InsertItem(m_listStocks.GetItemCount(),str);
			m_listStocks.SetItemData(m_listStocks.GetItemCount()-1,DWORD_PTR(pStock));
		}
	}*/	
	SetUserDefReportItem();
	FreshData();
	CheckTimer();
}

void CDlgChgStk::SetStockCode(CString c_strCode)
{
	if (m_bFixed && m_strStockCode.GetLength())
		return;

	if (m_strStockCode == c_strCode)
		return;
	SStock * pStock = gpData->GetStock(c_strCode);

	if (pStock == NULL)
		return;
	if (gpData->IsStock(c_strCode) == false)
	{		
		return;
	}
	
	m_listStocks.DeleteAllItems();
	
	char acReq[1024];
	char acCode[16];
	unicodeToAscii(c_strCode,acCode,12);
	char *pRecv = (char *)malloc(1024 * 32);
	acCode[6] = 0;
	int nLen = MakeStockChangeReq(acReq,acCode,"stock_change.f01,stock_change.f02,stock_change.f03,stock_change.f04,stock_change.f05");	
	nLen = gpSendFunc(this,acReq,nLen,pRecv,32*1024,true);
	/*
	FILE *f;
	if (nLen > 0)
	{
		f = fopen("c:\\test\\chg","wb");
		if (f)
		{
			fwrite(pRecv,1,nLen,f);
			fclose(f);
		}
	}*/
	memset(m_acIndu,0,sizeof(m_acIndu));
	memset(m_acValue,0,sizeof(m_acValue));
	memset(m_acPE,0,sizeof(m_acPE));
	memset(m_acPrice,0,sizeof(m_acPrice));
	memset(m_acArea,0,sizeof(m_acArea));
	if (nLen > 0)
	{
		nLen -= 18;
		char * p = pRecv + 18;
		int nSize = 0;
		strncpy(acCode,p,6);
		p += 6;
		nSize = *(int *)p;	p += sizeof(int);	nLen -= sizeof(int);	if (nLen<=0) {free(pRecv);return;};
		memcpy(m_acIndu,p,nSize); p += nSize;			nLen -= nSize;	if (nLen<=0) {free(pRecv);return;};
		nSize = *(int *)p;  p += sizeof(int);	nLen -= sizeof(int);	if (nLen<=0) {free(pRecv);return;};
		memcpy(m_acValue,p,nSize); p += nSize;			nLen -= nSize;	if (nLen<=0) {free(pRecv);return;};

		nSize = *(int *)p;  p += sizeof(int);	nLen -= sizeof(int);	if (nLen<=0) {free(pRecv);return;};
		memcpy(m_acPE,p,nSize); p += nSize;			nLen -= nSize;	if (nLen<=0) {free(pRecv);return;};
		nSize = *(int *)p;  p += sizeof(int);	nLen -= sizeof(int);	if (nLen<=0) {free(pRecv);return;};
		memcpy(m_acPrice,p,nSize); p += nSize;			nLen -= nSize;	if (nLen<=0) {free(pRecv);return;};
		nSize = *(int *)p;  p += sizeof(int);	nLen -= sizeof(int);	if (nLen<=0) {free(pRecv);return;};
		memcpy(m_acArea,p,nSize); p += nSize;			nLen -= nSize;	if (nLen<=0) {free(pRecv);return;};
	}
	free(pRecv);
	m_strStockCode = c_strCode;
	if (pStock)
		m_strStockName = pStock->m_strName;
	else
		m_strStockName = "";
	SetTips();
	OnBnClickedBtnSameIndustry();
}

void CDlgChgStk::DoCommand(int c_nCmd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

	if (c_nCmd == 0)
		OnBnClickedBtnSameIndustry();
	if (c_nCmd == 9)//固定股票
		m_bFixed = true;
	if (c_nCmd == 8)
		m_bFixed = false;
	if (c_nCmd == 100)
	{
		m_btnValue.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
		m_btnIndu.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
		m_btnPE.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
		m_btnSamePrice.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
		m_btnSameArea.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	}
}

void CDlgChgStk::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此添加控件通知处理程序代码	
}

void CDlgChgStk::OnNMDblclkListStocks(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_listStocks.GetSelectionMark() == -1)
		return;
	int nSel = m_listStocks.GetSelectionMark();
	SStock * pStock;
	pStock = (SStock *)m_listStocks.GetItemData(nSel);
	if (pStock == NULL)
		return;
	
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;

	int nItem=pNMListView->iItem;
	

	if (pNMListView->iSubItem != 8)
	{		
		::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,STOCK_FROM_CHANGE,DWORD_PTR(pStock));
	}
	*pResult = 0;
}

BOOL CDlgChgStk::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加控件通知处理程序代码
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;
	/*
	if(pMsg->message   ==   WM_KEYDOWN)
	{
		if ((pMsg->wParam >='0' && pMsg->wParam <= '9')
			||(pMsg->wParam >='a' && pMsg->wParam <= 'z')
			||(pMsg->wParam >='A' && pMsg->wParam <= 'Z'))
		{
			if (gpData->m_pTopDlg->ActiveByKey(pMsg->wParam))
				return TRUE;
		}
	}*/
	if (pMsg->message == WM_CHAR)
	{/*
		if ((pMsg->wParam >='0' && pMsg->wParam <= '9')
			||(pMsg->wParam >='a' && pMsg->wParam <= 'z')
			||(pMsg->wParam >='A' && pMsg->wParam <= 'Z'))
		{
			if (gpData->m_pTopDlg->ActiveByKey(pMsg->wParam))
				return TRUE;
		}*/
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgChgStk::OnBnClickedBtnSamePrice()
{
	// TODO: 在此添加控件通知处理程序代码
	m_btnValue.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnIndu.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnPE.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnSamePrice.SetBMPFill(TRUE,m_hBmp,m_hBmp);
	m_btnSameArea.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);

	m_strMemo.Format(_T("注：系统帮您选择出同您手中所持有股票(%s %s)价格相当且相对强势的股票"),m_strStockName,m_strStockCode);
	//m_btnSamePrice.SetToolTipText(&m_strMemo,TRUE);
	SetList(4);
	Invalidate();
}


void CDlgChgStk::FreshData()
{
	for(int n=0; n<m_listStocks.GetItemCount(); n++)
	{
		SStock * pStock = (SStock *)m_listStocks.GetItemData(n);
		if (pStock == NULL)
			continue;

		CString strNew,strOld;
		for(int nSub=0; nSub<m_listStocks.GetHeaderCtrl()->GetItemCount(); nSub++)
		{
			CString strFieldName;
			strFieldName=m_listStocks.GetPosName(nSub);
			strOld = m_listStocks.GetItemText(n,nSub);
			strNew = gpData->GetStockValueByName(pStock,strFieldName);
			if (strOld != strNew)
				m_listStocks.SetItemText(n,nSub,strNew);
		}
	}
}

void CDlgChgStk::OnBnClickedBtnSameArea()
{
	// TODO: 在此添加控件通知处理程序代码
	m_btnValue.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnIndu.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnPE.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnSamePrice.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnSameArea.SetBMPFill(TRUE,m_hBmp,m_hBmp);

	m_strMemo.Format(_T("注：系统帮您选择出同您手中所持有股票(%s %s)相同地域且相对强势的股票"),m_strStockName,m_strStockCode);
	//m_btnSameArea.SetToolTipText(&m_strMemo,TRUE);
	SetList(5);
	Invalidate();
}


void CDlgChgStk::ResetSkin()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

	DeleteObject(m_hBmp);
	DeleteObject(m_hBmpHead);

	m_hBmp = gpSkinManager->LoadSpecialBmp(ID_RB_UNDER_BTN_BACK);
	m_hBmpHead = gpSkinManager->LoadSpecialBmp(ID_RB_UNDER_TITLE_BACK);

	m_btnAdd.SetFont(gpSkinManager->GetButtonFont());
	m_btnValue.SetFont(gpSkinManager->GetButtonFont());
	m_btnIndu.SetFont(gpSkinManager->GetButtonFont());
	m_btnPE.SetFont(gpSkinManager->GetButtonFont());
	m_btnSamePrice.SetFont(gpSkinManager->GetButtonFont());
	m_btnSameArea.SetFont(gpSkinManager->GetButtonFont());

	CSize size = gpSkinManager->GetBmpSize(m_hBmpHead);
	m_nHeadHeight = size.cy;
	size = gpSkinManager->GetBmpSize(m_hBmp);
	m_nBtnHeight = size.cy;
	m_nBtnWidth = size.cx;
	if (m_nBtnWidth < 10)
		m_nBtnWidth = 72;
	SetLayout();
	if (!IsWindowVisible())
		return;
	OnBnClickedBtnSameIndustry();
	Invalidate();
}

void CDlgChgStk::SetTitle(CString c_strIn)
{
	SetWindowText(c_strIn);
}

void CDlgChgStk::GetTitle(CString &c_strIn)
{
	GetWindowText(c_strIn);
}

bool CDlgChgStk::IsTitle(CString c_strIn)
{
	CString strTitle;
	GetWindowText(strTitle);
	if (c_strIn.Find(strTitle) == 0)
	//if (strTitle.Find(c_strIn) == 0)
		return true;
	return false;
}

void CDlgChgStk::GetViewTitle(CString &c_strIn)
{
	GetWindowText(c_strIn);

	c_strIn += "-";
	c_strIn += m_strStockName;
}
/*
int CDlgChgStk::MakeStockChangeReq(char * c_pBuf,char *c_pCode)
{	
	SCommHead * pHead;
	pHead = (SCommHead *)c_pBuf;
	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = gpData->NewSeq();
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = STOCKCHANGEREQ;	
	strcpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short),c_pCode);
	pHead->m_head.SetLength(sizeof(unsigned short) * 3 + 16);
	pHead->m_usFuncNo = STOCKCHANGEREQ;
	return pHead->m_head.GetLength() + 8;
}*/

int CDlgChgStk::MakeStockChangeReq(char * c_pBuf,char * c_pCodes,char * c_pFields)
{
	if (!c_pCodes || !c_pFields)
		return -1;

	SCommHead * pHead;
	pHead = (SCommHead *)c_pBuf;

	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = gpData->NewSeq();
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = STOCKBASEDATA;//功能号
	*(int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = strlen(c_pCodes) + 1;//代码长度，null结尾
	strcpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(int),c_pCodes);//代码
	*(int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(int) + strlen(c_pCodes) + 1) = strlen(c_pFields) + 1;//字段长度
	strcpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(int) + strlen(c_pCodes) + 1 + sizeof(int),c_pFields);//字段
	pHead->m_head.SetLength(sizeof(unsigned short) * 3 + sizeof(int) + strlen(c_pCodes) + 1 + sizeof(int) + strlen(c_pFields) + 1);
	pHead->m_usFuncNo = STOCKBASEDATA;
	return pHead->m_head.GetLength() + 8;
}

void CDlgChgStk::SetTips()
{
	CString str;
	str.Format(_T("注：系统帮您选择出同您手中所持有股票(%s %s)相同地域且相对强势的股票"),m_strStockName,m_strStockCode);
	//m_btnSameArea.SetToolTipText(&(CString(_T("同地域"))),TRUE);
	str.Format(_T("注：系统帮您选择出同您手中所持有股票(%s %s)价格相当且相对强势的股票"),m_strStockName,m_strStockCode);
	//m_btnSamePrice.SetToolTipText(&(CString(_T("同价格"))),TRUE);
	str.Format(_T("注：系统帮您选择出同您手中所持有股票(%s %s)PE相当且相对强势的股票"),m_strStockName,m_strStockCode);
	//m_btnPE.SetToolTipText(&(CString(_T("同PE"))),TRUE);
	str.Format(_T("注：系统帮您选择出同您手中所持有股票(%s %s)同行业且相对强势的股票"),m_strStockName,m_strStockCode);
	//m_btnIndu.SetToolTipText(&(CString(_T("同行业"))),TRUE);
	str.Format(_T("注：系统帮您选择出同您手中所持有股票(%s %s)市值相当且相对强势的股票"),m_strStockName,m_strStockCode);
	//m_btnValue.SetToolTipText(&(CString(_T("同市值"))),TRUE);						
}
BOOL CDlgChgStk::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_btnValue.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnIndu.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnPE.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnSamePrice.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnSameArea.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);

	return __super::DestroyWindow();
}

void CDlgChgStk::OnDestroy()
{
	__super::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	m_btnValue.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnIndu.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnPE.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnSamePrice.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnSameArea.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);

}

void CDlgChgStk::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_btnValue.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnIndu.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnPE.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnSamePrice.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);
	m_btnSameArea.SetBMPFill(FALSE,(unsigned int)0,(unsigned int)0);

	__super::OnClose();
}

void CDlgChgStk::SetUserDefReportItem()
{
	int nId[50];
	int nCount = 0;
	int nTop = m_listStocks.GetTopIndex();
	int nCountPage = m_listStocks.GetCountPerPage();

	for(int n=nTop; n<=nTop + nCountPage && n<m_listStocks.GetItemCount() && nCount<50; n++)
	{
		SStock * pStock;
		pStock = (SStock *)m_listStocks.GetItemData(n);
		if (pStock)
		{
			nId[nCount] = pStock->m_sQuote.nStockId;
			nCount++;
		}
	}
	gpData->m_lockData.lock();
	gpData->AddUserDefReportItem(this->GetSafeHwnd(),nId,nCount);
	gpData->m_lockData.unlock();
}

void CDlgChgStk::CheckTimer()
{
	KillTimer(100);
	
	m_nTopIndexLast = m_listStocks.GetTopIndex();
	m_nCountPageLast = m_listStocks.GetCountPerPage();

	if (m_listStocks.GetItemCount() > m_nCountPageLast)
		SetTimer(100,200,NULL);
	else
	{
		m_nTopIndexLast = -1;
		m_nCountPageLast = -1;
	}
}

void CDlgChgStk::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 100 && m_nTopIndexLast != -1 && m_nCountPageLast != -1)
	{
		int nTop = m_listStocks.GetTopIndex();
		int nCountPage = m_listStocks.GetCountPerPage();
		if (nTop != m_nTopIndexLast || (nTop == m_nTopIndexLast && nCountPage > m_nCountPageLast))
		{
			m_nTopIndexLast = nTop;
			m_nCountPageLast = nCountPage;
			SetUserDefReportItem();
		}
	}

	__super::OnTimer(nIDEvent);
}
