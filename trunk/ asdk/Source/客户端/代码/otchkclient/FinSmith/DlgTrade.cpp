// DlgTrade.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "TopDlg.h"
#include "DlgTrade.h"
#include "../public/ShortSocket.h"
#include "TopDlg.h"
//#include "../public/trade_proto.pb.h"

//protoc -I=. --cpp_out=. Net.proto     //在当前目录下，以cpp方式编译Net.proto

// CDlgTrade 对话框

IMPLEMENT_DYNAMIC(CDlgTrade, CDialog)

CDlgTrade::CDlgTrade(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrade::IDD, pParent)
{
	m_viewmode = MODENULL;
	m_nHeadHeight = 37;
	m_nInvestHeight = 25;
	m_nToolsHeight = 24;

	m_fAmount = 0;
	m_fAmountValid = 0;
	m_fCost = 0;
	m_fValue = 0;
	m_fProfit = 0;

	m_bOwnerSet = false;
	m_pTopDlg = NULL;
	m_nSerialno = 1000;
}

CDlgTrade::~CDlgTrade()
{
	if (m_pTopDlg != NULL)
	{
		m_pTopDlg->DestroyWindow();
		delete m_pTopDlg;
		m_pTopDlg = NULL;
	}
}

void CDlgTrade::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TRADE, m_listTrade);
	DDX_Control(pDX, IDC_EDIT_CODE, m_editCode);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_PRICE, m_editPrice);
	DDX_Control(pDX, IDC_EDIT_AMOUNT_VALID, m_editAmountValid);
	DDX_Control(pDX, IDC_EDIT_VOLUME_VLIAD, m_editVolumeValid);
	DDX_Control(pDX, IDC_EDIT_VOLUME, m_editVolume);
	DDX_Control(pDX, IDC_STATIC_CODE, m_stCode);
	DDX_Control(pDX, IDC_STATIC_NAME, m_stName);
	DDX_Control(pDX, IDC_STATIC_PRICE, m_stPrice);
	DDX_Control(pDX, IDC_STATIC_AMOUNT_VLIAD, m_stAmountValid);
	DDX_Control(pDX, IDC_STATIC_VOLUME_VLIAD, m_stVolumeValid);
	DDX_Control(pDX, IDC_STATIC_VOLUME, m_stVolume);
	DDX_Control(pDX, IDC_BUTTON_CONFIRM, m_btnConfirm);
	DDX_Control(pDX, IDC_LIST_COMBO, m_listCombo);
	DDX_Control(pDX, IDC_BTN_INVEST, m_btnCombo);
	DDX_Control(pDX, IDC_BTN_BUY, m_btnBuyin);
	DDX_Control(pDX, IDC_BTN_SALE, m_btnSaleout);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_BUTTON_CONSIGN, m_btnConsign);
	DDX_Control(pDX, IDC_BUTTON_BARGAIN, m_btnBargain);
	DDX_Control(pDX, IDC_BUTTON_REFRESH, m_btnRefresh);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_btnDoCancel);
	DDX_Control(pDX, IDC_BUTTON_SELALL, m_btnDoSelAll);
	DDX_Control(pDX, IDC_BUTTON_SELNO, m_btnDoSelNone);
	DDX_Control(pDX, IDC_DATE_START, m_dateStart);
	DDX_Control(pDX, IDC_DATE_END, m_dateEnd);
	DDX_Control(pDX, IDC_STATIC_DATE_START, m_stDateStart);
	DDX_Control(pDX, IDC_STATIC_DATE_END, m_stDateEnd);
	DDX_Control(pDX, IDC_BTN_MAKER, m_btnMaker);
	DDX_Control(pDX, IDC_STATIC_PRICE_, m_stPrice_M);
	DDX_Control(pDX, IDC_STATIC_VOLUMME_M, m_stVolume_M);
	DDX_Control(pDX, IDC_STATIC_VOLUME_VLIAD_M, m_stVolumeValid_M);
	DDX_Control(pDX, IDC_EDIT_PRICE_M, m_editPrice_M);
	DDX_Control(pDX, IDC_EDIT_VOLUME_M, m_editVolume_M);
	DDX_Control(pDX, IDC_EDIT_VOLUME_VLIAD_M, m_editVolumeValid_M);
}


BEGIN_MESSAGE_MAP(CDlgTrade, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BARGAIN, &CDlgTrade::OnBnClickedButtonBargain)
	ON_BN_CLICKED(IDC_BUTTON_CONSIGN, &CDlgTrade::OnBnClickedButtonConsign)
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDC_BTN_INVEST, &CDlgTrade::OnBnClickedBtnInvest)
	ON_BN_CLICKED(IDC_BTN_BUY, &CDlgTrade::OnBnClickedBtnBuy)
	ON_BN_CLICKED(IDC_BTN_SALE, &CDlgTrade::OnBnClickedBtnSale)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CDlgTrade::OnBnClickedBtnCancel)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_COMBO, &CDlgTrade::OnNMDblclkListCombo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TRADE, &CDlgTrade::OnNMDblclkListTrade)
	ON_EN_CHANGE(IDC_EDIT_CODE, &CDlgTrade::OnEnChangeEditCode)
	ON_BN_CLICKED(IDC_BUTTON_CONFIRM, &CDlgTrade::OnBnClickedButtonConfirm)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgTrade::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_SELALL, &CDlgTrade::OnBnClickedButtonSelall)
	ON_BN_CLICKED(IDC_BUTTON_SELNO, &CDlgTrade::OnBnClickedButtonSelno)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CDlgTrade::OnBnClickedButtonRefresh)
	ON_EN_CHANGE(IDC_EDIT_VOLUME, &CDlgTrade::OnEnChangeEditVolume)
	ON_BN_CLICKED(IDC_BTN_MAKER, &CDlgTrade::OnBnClickedBtnMaker)
END_MESSAGE_MAP()


// CDlgTrade 消息处理程序

BOOL CDlgTrade::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_listCombo.Init();
	m_listTrade.Init();

	m_btnCombo.SetBorder(FALSE);
	m_btnCombo.SetBtnBMP(IDB_TRADE_HEAD_BTN,IDB_TRADE_HEAD_BTN_SEL);
	m_btnCombo.SetBmpPos(3);
	m_btnCombo.SetTextColor(RGB(0,0,0));

	m_btnBuyin.SetBorder(FALSE);
	m_btnBuyin.SetBtnBMP(IDB_TRADE_HEAD_BTN,IDB_TRADE_HEAD_BTN_SEL);
	m_btnBuyin.SetBmpPos(3);
	m_btnBuyin.SetTextColor(RGB(0,0,0));

	m_btnSaleout.SetBorder(FALSE);
	m_btnSaleout.SetBtnBMP(IDB_TRADE_HEAD_BTN,IDB_TRADE_HEAD_BTN_SEL);
	m_btnSaleout.SetBmpPos(3);
	m_btnSaleout.SetTextColor(RGB(0,0,0));

	m_btnMaker.SetBorder(FALSE);
	m_btnMaker.SetBtnBMP(IDB_TRADE_HEAD_BTN,IDB_TRADE_HEAD_BTN_SEL);
	m_btnMaker.SetBmpPos(3);
	m_btnMaker.SetTextColor(RGB(0,0,0));

	m_btnCancel.SetBorder(FALSE);
	m_btnCancel.SetBtnBMP(IDB_TRADE_HEAD_BTN,IDB_TRADE_HEAD_BTN_SEL);
	m_btnCancel.SetBmpPos(3);
	m_btnCancel.SetTextColor(RGB(0,0,0));

	m_btnConsign.SetBorder(FALSE);
	m_btnConsign.SetBtnBMP(IDB_TRADE_HEAD_BTN,IDB_TRADE_HEAD_BTN_SEL);
	m_btnConsign.SetBmpPos(3);
	m_btnConsign.SetTextColor(RGB(0,0,0));

	m_btnBargain.SetBorder(FALSE);
	m_btnBargain.SetBtnBMP(IDB_TRADE_HEAD_BTN,IDB_TRADE_HEAD_BTN_SEL);
	m_btnBargain.SetBmpPos(3);
	m_btnBargain.SetTextColor(RGB(0,0,0));

	m_listCombo.InsertColumn(0,_T("证券代码"),LVCFMT_CENTER,64);
	m_listCombo.InsertColumn(1,_T("证券名称"),LVCFMT_CENTER,68);
	m_listCombo.InsertColumn(2,_T("库存数量"),LVCFMT_CENTER,64);
	m_listCombo.InsertColumn(3,_T("可卖数量"),LVCFMT_CENTER,64);
	m_listCombo.InsertColumn(4,_T("成本价格"),LVCFMT_CENTER,64);
	m_listCombo.InsertColumn(5,_T("浮动盈亏"),LVCFMT_CENTER,80);
	m_listCombo.InsertColumn(6,_T("盈亏比例"),LVCFMT_CENTER,64);
	m_listCombo.InsertColumn(7,_T("最新市值"),LVCFMT_CENTER,80);
	m_listCombo.InsertColumn(8,_T("成本金额"),LVCFMT_CENTER,80);
	m_listCombo.InsertColumn(9,_T("最新价格"),LVCFMT_CENTER,64);
	m_listCombo.InsertColumn(10,_T("涨跌幅"),LVCFMT_CENTER,64);

	//m_listTrade.SetExtendedStyle( m_listTrade.GetExtendedStyle()|LVS_EX_CHECKBOXES);
	m_listTrade.InsertColumn(0,_T("证券代码"),LVCFMT_CENTER,72);
	m_listTrade.InsertColumn(1,_T("证券名称"),LVCFMT_LEFT,72);
	m_listTrade.InsertColumn(2,_T("买卖标志"),LVCFMT_CENTER,68);
	m_listTrade.InsertColumn(3,_T("委托数量"),LVCFMT_CENTER,80);
	m_listTrade.InsertColumn(4,_T("委托价格"),LVCFMT_RIGHT,80);	
	m_listTrade.InsertColumn(5,_T("成交数量"),LVCFMT_CENTER,80);
	m_listTrade.InsertColumn(6,_T("状态"),LVCFMT_RIGHT,80);	
	m_listTrade.InsertColumn(7,_T("委托时间"),LVCFMT_CENTER,116);
	m_listTrade.InsertColumn(8,_T("委托编号"),LVCFMT_CENTER,80);
	
	m_listTrade.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);// | LVS_EX_GRIDLINES);

	setViewMode(COMBO);

	m_editAmountValid.SetReadOnly();
	m_editVolumeValid.SetReadOnly();

	m_pTopDlg = new CTopDlg();
	m_pTopDlg->Create(IDD_TOP,this);

	CRect rw,r,rect;
	m_editCode.GetWindowRect(&rect);
	m_pTopDlg->GetWindowRect(&rw);
	r.top = rect.top + 20;
	r.left = rect.left + 2;
	r.bottom = r.top + rw.Height();
	r.right = r.left + rect.Width();
	m_pTopDlg->MoveWindow(r);
	m_pTopDlg->SetLinkEdit(&m_editCode,gpData,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgTrade::OnBnClickedButtonBargain()
{
	// TODO: 在此添加控件通知处理程序代码
	clearBargain();
	commitTrade(303);
	setViewMode(BARGAIN);
	getBargain();
	viewBargain();
}

void CDlgTrade::OnBnClickedButtonConsign()
{
	// TODO: 在此添加控件通知处理程序代码	
	clearConsign();
	commitTrade(302);
	setViewMode(CONSIGN);	
	viewConsign();
}

void CDlgTrade::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgTrade::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDCtl == IDC_LIST_TRADE || nIDCtl == IDC_LIST_COMBO)
		lpMeasureItemStruct->itemHeight = 24;
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CDlgTrade::OnBnClickedBtnInvest()
{
	// TODO: 在此添加控件通知处理程序代码		
	if (!getValue())
		return;	
	getMakerStock();
	caclTradeCombo();
	viewTradeCombo();
	setViewMode(COMBO);	
	Invalidate();
}

void CDlgTrade::OnBnClickedBtnBuy()
{
	// TODO: 在此添加控件通知处理程序代码
	commitTrade(309);
	setViewMode(BUYIN);
}

void CDlgTrade::OnBnClickedBtnSale()
{
	// TODO: 在此添加控件通知处理程序代码
	if (commitTrade(310))
	{
		caclTradeCombo();
		viewTradeCombo();
	}
	setViewMode(SALEOUT);
}

void CDlgTrade::OnBnClickedBtnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	clearConsign();
	commitTrade(302);
	setViewMode(CANCEL);	
	viewConsign(0);
}

void CDlgTrade::setViewMode(VIEWMODE c_viewmode)
{
	if (m_viewmode == c_viewmode)
		return;
	m_viewmode = c_viewmode;
	if (m_viewmode == COMBO)
		m_btnCombo.SetBtnBMP(IDB_TRADE_HEAD_BTN_SEL,IDB_TRADE_HEAD_BTN_SEL);
	else
		m_btnCombo.SetBtnBMP(IDB_TRADE_HEAD_BTN,IDB_TRADE_HEAD_BTN_SEL);
	if (m_viewmode == BUYIN)
		m_btnBuyin.SetBtnBMP(IDB_TRADE_HEAD_BTN_SEL,IDB_TRADE_HEAD_BTN_SEL);
	else
		m_btnBuyin.SetBtnBMP(IDB_TRADE_HEAD_BTN,IDB_TRADE_HEAD_BTN_SEL);

	if (m_viewmode == SALEOUT)
		m_btnSaleout.SetBtnBMP(IDB_TRADE_HEAD_BTN_SEL,IDB_TRADE_HEAD_BTN_SEL);
	else
		m_btnSaleout.SetBtnBMP(IDB_TRADE_HEAD_BTN,IDB_TRADE_HEAD_BTN_SEL);

	if (m_viewmode == MAKER)
		m_btnMaker.SetBtnBMP(IDB_TRADE_HEAD_BTN_SEL,IDB_TRADE_HEAD_BTN_SEL);
	else
		m_btnMaker.SetBtnBMP(IDB_TRADE_HEAD_BTN,IDB_TRADE_HEAD_BTN_SEL);

	if (m_viewmode == CANCEL)
		m_btnCancel.SetBtnBMP(IDB_TRADE_HEAD_BTN_SEL,IDB_TRADE_HEAD_BTN_SEL);
	else
		m_btnCancel.SetBtnBMP(IDB_TRADE_HEAD_BTN,IDB_TRADE_HEAD_BTN_SEL);
	if (m_viewmode == CONSIGN)
		m_btnConsign.SetBtnBMP(IDB_TRADE_HEAD_BTN_SEL,IDB_TRADE_HEAD_BTN_SEL);
	else
		m_btnConsign.SetBtnBMP(IDB_TRADE_HEAD_BTN,IDB_TRADE_HEAD_BTN_SEL);
	if (m_viewmode == BARGAIN)
		m_btnBargain.SetBtnBMP(IDB_TRADE_HEAD_BTN_SEL,IDB_TRADE_HEAD_BTN_SEL);
	else
		m_btnBargain.SetBtnBMP(IDB_TRADE_HEAD_BTN,IDB_TRADE_HEAD_BTN_SEL);
	if (m_viewmode == CANCEL)
		m_listTrade.m_bShowCheckBox = true;
	else
		m_listTrade.m_bShowCheckBox = false;

	m_editCode.SetWindowText(_T(""));
	m_editName.SetWindowText(_T(""));
	m_editPrice.SetWindowText(_T(""));
	m_editAmountValid.SetWindowText(_T(""));
	m_editVolume.SetWindowText(_T(""));
	m_editVolumeValid.SetWindowText(_T(""));

	if (m_viewmode == CONSIGN || m_viewmode == CANCEL || m_viewmode == BARGAIN)
	{
		while(m_listTrade.GetHeaderCtrl()->GetItemCount() > 0)
			m_listTrade.DeleteColumn(0);
	}

	if (m_viewmode == CONSIGN || m_viewmode == CANCEL)
	{
		m_listTrade.InsertColumn(0,_T("证券代码"),LVCFMT_CENTER,72);
		m_listTrade.InsertColumn(1,_T("证券名称"),LVCFMT_LEFT,72);
		m_listTrade.InsertColumn(2,_T("买卖标志"),LVCFMT_CENTER,68);
		m_listTrade.InsertColumn(3,_T("委托数量"),LVCFMT_CENTER,80);
		m_listTrade.InsertColumn(4,_T("委托价格"),LVCFMT_RIGHT,80);	
		m_listTrade.InsertColumn(5,_T("成交数量"),LVCFMT_CENTER,80);
		m_listTrade.InsertColumn(6,_T("状态"),LVCFMT_RIGHT,80);	
		m_listTrade.InsertColumn(7,_T("委托时间"),LVCFMT_CENTER,116);
		m_listTrade.InsertColumn(8,_T("委托编号"),LVCFMT_CENTER,80);
	}
	else
	if (m_viewmode == BARGAIN)
	{
		m_listTrade.InsertColumn(0,_T("证券代码"),LVCFMT_CENTER,72);
		m_listTrade.InsertColumn(1,_T("证券名称"),LVCFMT_LEFT,72);
		m_listTrade.InsertColumn(2,_T("买卖标志"),LVCFMT_CENTER,68);
		m_listTrade.InsertColumn(3,_T("数量"),LVCFMT_CENTER,80);
		m_listTrade.InsertColumn(4,_T("价格"),LVCFMT_RIGHT,80);	
		m_listTrade.InsertColumn(5,_T("状态"),LVCFMT_RIGHT,80);	
		m_listTrade.InsertColumn(6,_T("成交时间"),LVCFMT_CENTER,116);
		m_listTrade.InsertColumn(7,_T("委托编号"),LVCFMT_CENTER,80);
	}

	setLayout();
}

void CDlgTrade::setLayout()
{
	bool bShowTrade = false;
	int nLeftSpace = 0;
	int nTopSpace = m_nHeadHeight;
	
	m_rectPriceVol.left = 192;
	m_rectPriceVol.right = m_rectPriceVol.left + 132;
	m_rectPriceVol.top = m_nHeadHeight + 4;
	m_rectPriceVol.bottom = m_rectPriceVol.top + 160;

	m_rectPriceVolMaker = m_rectPriceVol;
	m_rectPriceVolMaker.left = m_rectPriceVolMaker.right + 4;
	m_rectPriceVolMaker.right = m_rectPriceVolMaker.left + m_rectPriceVol.Width();
	if (m_viewmode == BUYIN || m_viewmode == SALEOUT || m_viewmode == MAKER)
	{
		bShowTrade = true;
		m_btnConfirm.SetWindowText(_T("提交委托"));
		if (m_viewmode == BUYIN || m_viewmode == MAKER)
		{
			m_stPrice.SetWindowText(_T("买入价格:"));
			m_stVolumeValid.SetWindowText(_T("可买数量:"));
			m_stVolume.SetWindowText(_T("买入数量:"));			
		}
		else
		{
			m_stPrice.SetWindowText(_T("卖出价格:"));
			m_stVolumeValid.SetWindowText(_T("可卖数量:"));
			m_stVolume.SetWindowText(_T("卖出数量:"));
		}
	}
		
	if (bShowTrade)
	{
		m_editCode.ShowWindow(SW_SHOW);
		m_editName.ShowWindow(SW_SHOW);
		m_editPrice.ShowWindow(SW_SHOW);
		m_editAmountValid.ShowWindow(SW_SHOW);
		m_editVolumeValid.ShowWindow(SW_SHOW);
		m_editVolume.ShowWindow(SW_SHOW);
		m_btnConfirm.ShowWindow(SW_SHOW);

		m_stCode.ShowWindow(SW_SHOW);
		m_stName.ShowWindow(SW_SHOW);
		m_stPrice.ShowWindow(SW_SHOW);
		m_stAmountValid.ShowWindow(SW_SHOW);
		m_stVolumeValid.ShowWindow(SW_SHOW);
		m_stVolume.ShowWindow(SW_SHOW);

		if (m_viewmode == MAKER)
		{
			m_editPrice_M.ShowWindow(SW_SHOW);
			m_editVolumeValid_M.ShowWindow(SW_SHOW);
			m_editVolume_M.ShowWindow(SW_SHOW);
			m_stPrice_M.ShowWindow(SW_SHOW);
			m_stVolumeValid_M.ShowWindow(SW_SHOW);
			m_stVolume_M.ShowWindow(SW_SHOW);
		}
		else
		{
			m_editPrice_M.ShowWindow(SW_HIDE);
			m_editVolumeValid_M.ShowWindow(SW_HIDE);
			m_editVolume_M.ShowWindow(SW_HIDE);
			m_stPrice_M.ShowWindow(SW_HIDE);
			m_stVolumeValid_M.ShowWindow(SW_HIDE);
			m_stVolume_M.ShowWindow(SW_HIDE);
		}
		nLeftSpace = 192 + 140;
		if (m_viewmode == MAKER)
			nLeftSpace += 140;
	}
	else
	{
		m_editCode.ShowWindow(SW_HIDE);
		m_editName.ShowWindow(SW_HIDE);

		m_editPrice.ShowWindow(SW_HIDE);
		m_editAmountValid.ShowWindow(SW_HIDE);
		m_editVolumeValid.ShowWindow(SW_HIDE);
		m_editVolume.ShowWindow(SW_HIDE);
		m_btnConfirm.ShowWindow(SW_HIDE);

		m_stCode.ShowWindow(SW_HIDE);
		m_stName.ShowWindow(SW_HIDE);
		m_stPrice.ShowWindow(SW_HIDE);
		m_stAmountValid.ShowWindow(SW_HIDE);
		m_stVolumeValid.ShowWindow(SW_HIDE);
		m_stVolume.ShowWindow(SW_HIDE);

		m_editPrice_M.ShowWindow(SW_HIDE);
		m_editVolumeValid_M.ShowWindow(SW_HIDE);
		m_editVolume_M.ShowWindow(SW_HIDE);
		m_stPrice_M.ShowWindow(SW_HIDE);
		m_stVolumeValid_M.ShowWindow(SW_HIDE);
		m_stVolume_M.ShowWindow(SW_HIDE);
	}

	CRect rectClient,rect;
	GetClientRect(rectClient);
	rect = rectClient;
	rect.left += 4;
	rect.top += 7;
	rect.bottom = rect.top + 22;
	rect.right = rect.left + 43;
	m_btnCombo.MoveWindow(rect);
	rect.left += 45;
	rect.right += 45;
	m_btnBuyin.MoveWindow(rect);
	rect.left += 45;
	rect.right += 45;
	m_btnSaleout.MoveWindow(rect);

	if(gpData->m_nMemberType == 4)
	{
		rect.left += 45;
		rect.right += 45;
		m_btnMaker.MoveWindow(rect);
		m_btnMaker.ShowWindow(SW_SHOW);
	}
	else
		m_btnMaker.ShowWindow(SW_HIDE);

	rect.left += 45;
	rect.right += 45;
	m_btnCancel.MoveWindow(rect);
	rect.left += 45;
	rect.right += 45;
	m_btnConsign.MoveWindow(rect);
	rect.left += 45;
	rect.right += 45;
	m_btnBargain.MoveWindow(rect);

	rect.top = rectClient.top + m_nHeadHeight + 2;
	rect.bottom = rect.top + m_nToolsHeight - 2;
	rect.right = rectClient.right - 8;
	rect.left = rect.right - 48;
	m_btnRefresh.MoveWindow(rect);

	rect.left -= 52;
	rect.right -= 52;
	m_btnDoSelNone.MoveWindow(rect);
	rect.left -= 52;
	rect.right -= 52;
	m_btnDoSelAll.MoveWindow(rect);
	rect.left -= 52;
	rect.right -= 52;
	m_btnDoCancel.MoveWindow(rect);

	CRect rectStatic;
	m_stDateStart.GetWindowRect(rectStatic);
	rect.left = rectClient.left + 4 + rectStatic.Width();
	rect.right = rect.left + 100;
	m_dateStart.MoveWindow(rect);

	rect.left += 108 + rectStatic.Width();
	rect.right += 108 + rectStatic.Width();
	m_dateEnd.MoveWindow(rect);

	rect.left = rectClient.left + 4;
	rect.right = rect.left + rectStatic.Width();
	rect.top = rect.top + (rect.Height() - rectStatic.Height()) / 2;
	rect.bottom = rect.top + rectStatic.Height();
	m_stDateStart.MoveWindow(rect);
	rect.left += rectStatic.Width() + 108;
	rect.right += rectStatic.Width() + 108;
	m_stDateEnd.MoveWindow(rect);

	if (m_viewmode == BARGAIN)
	{
		rect.top = rectClient.top + m_nHeadHeight + 2;
		rect.bottom = rect.top + m_nToolsHeight - 2;		
		rect.left = rect.right + 112;
		rect.right = rect.left + 48;
		m_btnRefresh.MoveWindow(rect);
	}
	if (m_viewmode == CANCEL)
	{
		m_btnDoSelNone.ShowWindow(SW_SHOW);
		m_btnDoSelAll.ShowWindow(SW_SHOW);
		m_btnDoCancel.ShowWindow(SW_SHOW);
	}
	else
	{
		m_btnDoSelNone.ShowWindow(SW_HIDE);
		m_btnDoSelAll.ShowWindow(SW_HIDE);
		m_btnDoCancel.ShowWindow(SW_HIDE);
	}
	if (m_viewmode == CANCEL || m_viewmode == CONSIGN || m_viewmode == BARGAIN || m_viewmode == COMBO)
	{
		if (m_viewmode == BARGAIN)
			m_btnRefresh.SetWindowText(_T("查询"));	
		else
			m_btnRefresh.SetWindowText(_T("刷新"));	
		m_btnRefresh.ShowWindow(SW_SHOW);
	}
	else
		m_btnRefresh.ShowWindow(SW_HIDE);
	rect = rectClient;
	rect.left += nLeftSpace + 4;
	rect.top += nTopSpace + 4;
	if (m_viewmode == COMBO)
		rect.top += m_nInvestHeight;
	else
	if (m_viewmode == CANCEL || m_viewmode == CONSIGN || m_viewmode == BARGAIN)
		rect.top += m_nToolsHeight;

	rect.bottom -= 4 + 18;
	rect.right -= 4 + 18;
	m_listTrade.MoveWindow(rect);
	m_listCombo.MoveWindow(rect);

	if (m_viewmode == BUYIN || m_viewmode == SALEOUT || m_viewmode == COMBO || m_viewmode == MAKER)
	{
		m_listCombo.ShowWindow(SW_SHOW);
		m_listCombo.ShowScrollBar(true,true);
	}
	else
	{
		m_listCombo.ShowWindow(SW_HIDE);
		m_listCombo.ShowScrollBar(false,false);
	}

	if (m_viewmode == CONSIGN || m_viewmode == BARGAIN || m_viewmode == CANCEL)
	{
		m_listTrade.ShowWindow(SW_SHOW);
		m_listTrade.ShowScrollBar(true,true);
	}
	else
	{
		m_listTrade.ShowWindow(SW_HIDE);
		m_listTrade.ShowScrollBar(false,false);
	}

	if (m_viewmode == BARGAIN)
	{
		m_dateStart.ShowWindow(SW_SHOW);
		m_dateEnd.ShowWindow(SW_SHOW);
		m_stDateStart.ShowWindow(SW_SHOW);
		m_stDateEnd.ShowWindow(SW_SHOW);
	}
	else
	{
		m_dateStart.ShowWindow(SW_HIDE);
		m_dateEnd.ShowWindow(SW_HIDE);
		m_stDateStart.ShowWindow(SW_HIDE);
		m_stDateEnd.ShowWindow(SW_HIDE);
	}
	m_listTrade.Invalidate();
	m_listTrade.PositionScrollBars();

	m_listCombo.Invalidate();
	m_listCombo.PositionScrollBars();

	Invalidate();
}
void CDlgTrade::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_btnConfirm)
	{
		setLayout();

		m_listTrade.Invalidate();
		m_listTrade.PositionScrollBars();

		m_listCombo.Invalidate();
		m_listCombo.PositionScrollBars();
	}
}

BOOL CDlgTrade::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rectClient;
	GetClientRect(rectClient);
	
	CRect rect;
	rect = rectClient;
	rect.bottom = rect.top + m_nHeadHeight;
	gpSkinManager->FillRectImage(IDB_TRADE_HEAD_BACK,pDC,rect);
	CBrush br(0xF7F7F7);
	rect = rectClient;
	rect.top += m_nHeadHeight;
	pDC->FillRect(rect,&br);

	if (m_viewmode == COMBO)
	{
		CString strText;		
		rect = rectClient;
		rect.left += 8;
		rect.top += m_nHeadHeight;
		rect.bottom = rect.top + m_nInvestHeight;
		m_rectValue = rect;
		CFont * pOldFont = pDC->SelectObject(gpSkinManager->m_pFontGraph);
		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		strText.Format(_T("余额:"));
		pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		CSize size = pDC->GetTextExtent(strText);
		rect.left += size.cx + 4;
		strText.Format(_T("%.2f"),m_fAmount);
		pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		size = pDC->GetTextExtent(strText);
		if (size.cx < 60)	size.cx = 60;
		rect.left += size.cx + 8;

		strText.Format(_T("可用:"));
		pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		size = pDC->GetTextExtent(strText);
		rect.left += size.cx + 4;
		strText.Format(_T("%.2f"),m_fAmountValid);
		pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		size = pDC->GetTextExtent(strText);
		if (size.cx < 60) size.cx = 60;
		rect.left += size.cx + 8;

		strText.Format(_T("市值:"));
		pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		size = pDC->GetTextExtent(strText);
		rect.left += size.cx + 4;
		strText.Format(_T("%.2f"),m_fCost);
		pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		size = pDC->GetTextExtent(strText);
		if (size.cx < 60) size.cx = 60;
		rect.left += size.cx + 8;

		strText.Format(_T("资产:"));
		pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		size = pDC->GetTextExtent(strText);
		rect.left += size.cx + 4;
		strText.Format(_T("%.2f"),m_fValue);
		pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		size = pDC->GetTextExtent(strText);
		if (size.cx < 60) size.cx = 60;
		rect.left += size.cx + 8;

		strText.Format(_T("收益:"));
		pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		size = pDC->GetTextExtent(strText);
		rect.left += size.cx + 4;
		strText.Format(_T("%.2f"),m_fProfit);
		if (m_fProfit > 0)
			pDC->SetTextColor(RGB(255,0,0));
		else
			pDC->SetTextColor(RGB(0,255,0));
		pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		size = pDC->GetTextExtent(strText);
		if (size.cx < 60) size.cx = 60;
		rect.left += size.cx + 8;

		pDC->SetTextColor(RGB(0,0,0));
		strText.Format(_T("收益率:"));
		pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		size = pDC->GetTextExtent(strText);
		rect.left += size.cx + 4;
		strText.Format(_T("%.2f%%"),m_fProfit/10000);
		if (m_fProfit > 0)
			pDC->SetTextColor(RGB(255,0,0));
		else
			pDC->SetTextColor(RGB(0,255,0));
		pDC->DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);

		pDC->SelectObject(pOldFont);
		pDC->SetBkMode(nOldMode);
	}
	if (m_viewmode == BUYIN || m_viewmode == SALEOUT || m_viewmode == MAKER)
	{
		SStock * pStock;
		CString strCode;
		m_editCode.GetWindowText(strCode);
		strCode.Trim();
		if (strCode.GetLength() == 6)
		{
			pStock = gpData->GetStock(strCode);			
			drawPriceVol(pDC,m_rectPriceVol,pStock);
			if (m_viewmode == MAKER)
			drawPriceVol(pDC,m_rectPriceVolMaker,pStock,1);
		}
		else
		{
			drawPriceVol(pDC,m_rectPriceVol,NULL);
			if (m_viewmode == MAKER)
			drawPriceVol(pDC,m_rectPriceVolMaker,NULL,1);
		}
	}
	return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}

void CDlgTrade::getTradeCombo()
{
}

void CDlgTrade::viewTradeCombo()
{
	m_listCombo.DeleteAllItems();
	for(int n=0; n<m_vpTradeCombo.size(); n++)
	{
		STradeCombo * pItem = m_vpTradeCombo.at(n);
		int nIndex = m_listCombo.GetItemCount();
		m_listCombo.InsertItem(nIndex,toUnicodeString(pItem->pStock->m_sQuote.szStockCode,strlen(pItem->pStock->m_sQuote.szStockCode)));
		CString strText;
		if (pItem->pStock)
		{
			m_listCombo.SetItemText(nIndex,1,pItem->pStock->m_strName);
			m_listCombo.SetItemData(nIndex,DWORD_PTR(pItem));
		}
	}
}

void CDlgTrade::caclTradeCombo()
{
	char acBuf[64];
	double dCost = 0;
	for(int n=0; n<m_vpTradeCombo.size(); n++)
	{
		STradeCombo * pItem = m_vpTradeCombo.at(n);
		pItem->fCostBase = pItem->fSl * pItem->fPriceBase;
		if (pItem->pStock)
		{
			if (pItem->pStock->m_sQuote.zjjg > 0)
				pItem->fCost = pItem->fSl * pItem->pStock->m_sQuote.zjjg/1000;
			else
				pItem->fCost = pItem->fSl * pItem->pStock->m_sQuote.zrsp/1000;		
			sprintf(acBuf,"%.2f",pItem->fCost);
			pItem->fCost = atof(acBuf);
			dCost += pItem->fCost;
		}
	}
	
	this->m_fCost = dCost;
	m_fValue = m_fCost + m_fAmount;
	if (m_fValue > 0)
	m_fProfit = m_fValue - 1000000;
}

void CDlgTrade::viewConsign(int c_nStatus)
{
	m_listTrade.DeleteAllItems();
	for(int n=0; n<m_vpConsign.size(); n++)
	{
		SVirTrade * pItem = m_vpConsign.at(n);
		
		if (m_viewmode == CANCEL)
		{
			if (pItem->nOperate == 2)
				continue;
			if (pItem->nStatus != 1 && pItem->nStatus != 2)
				continue;
		}
		int nIndex = m_listTrade.GetItemCount();
		CString strCode;
		strCode = pItem->pStock->m_sQuote.szStockCode;
		strCode = strCode.Left(6);
		m_listTrade.InsertItem(nIndex,strCode);
		if (pItem->pStock)
			m_listTrade.SetItemText(nIndex,1,pItem->pStock->m_strName);
		m_listTrade.SetItemText(nIndex,2,pItem->getOperateDesc());
		CString strText;
		strText.Format(_T("%d"),pItem->nVolume);
		m_listTrade.SetItemText(nIndex,3,strText);
		strText.Format(_T("%.3f"),pItem->fPrice);
		m_listTrade.SetItemText(nIndex,4,strText);
		strText.Format(_T("%d"),pItem->nVolumeBargain);
		m_listTrade.SetItemText(nIndex,5,strText);
				
		m_listTrade.SetItemText(nIndex,6,pItem->getStatusDesc());

		m_listTrade.SetItemText(nIndex,7,toUnicodeString(pItem->acDate,strlen(pItem->acDate)));
		strText.Format(_T("%d"),pItem->nId);
		m_listTrade.SetItemText(nIndex,8,strText);
		m_listTrade.SetItemData(nIndex,DWORD_PTR(pItem));
		m_listTrade.SetCheck(nIndex,0);
	}
}

void CDlgTrade::getBargain()
{
}

void CDlgTrade::viewBargain()
{
	m_listTrade.DeleteAllItems();
	for(int n=0; n<m_vpBargain.size(); n++)
	{
		SVirTrade * pItem = m_vpBargain.at(n);
		//if (pItem->nOperate != 0 && pItem->nOperate != 1)
		//	continue;
		//if (pItem->nStatus != 2 || pItem->nStatus != 3 || pItem->nStatus != 4)
		//	continue;
		int nIndex = m_listTrade.GetItemCount();
		CString strCode;
		strCode = pItem->pStock->m_sQuote.szStockCode;
		strCode = strCode.Left(6);

		m_listTrade.InsertItem(nIndex,strCode);
		m_listTrade.SetItemText(nIndex,1,pItem->pStock->m_strName);
		m_listTrade.SetItemText(nIndex,2,pItem->getOperateDesc());
		CString strText;
		strText.Format(_T("%d"),pItem->nVolume);
		m_listTrade.SetItemText(nIndex,3,strText);
		strText.Format(_T("%.3f"),pItem->fPrice);
		m_listTrade.SetItemText(nIndex,4,strText);
				
		m_listTrade.SetItemText(nIndex,5,pItem->getStatusDesc());

		m_listTrade.SetItemText(nIndex,6,toUnicodeString(pItem->acDealDate,strlen(pItem->acDealDate)));
		strText.Format(_T("%d"),pItem->nId);
		m_listTrade.SetItemText(nIndex,7,strText);
		m_listTrade.SetItemData(nIndex,DWORD_PTR(pItem));
	}
}
void CDlgTrade::OnNMDblclkListCombo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if (m_listCombo.GetSelectionMark() == -1)
		return;
	int nSel = m_listCombo.GetSelectionMark();
	STradeCombo * pItem = (STradeCombo *)m_listCombo.GetItemData(nSel);
	if (pItem && pItem->pStock)
	{
		if(m_viewmode == BUYIN || m_viewmode == SALEOUT || m_viewmode == MAKER)
		{
			if (setStockById(pItem->nStockId))
				m_editVolume.SetFocus();
		}
		else
		{
			gpData->m_strStockCode = pItem->pStock->m_sQuote.szStockCode;
			::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,STOCK_FROM_BOTTOM_LIST,DWORD_PTR(pItem->pStock));
		}		
	}
}

void CDlgTrade::OnNMDblclkListTrade(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

bool CDlgTrade::setStockById(int c_nStockId)
{
	SStock * pStock = gpData->GetStock(c_nStockId);
	if (pStock == NULL)
	{
		return false;
	}
	if (pStock->m_bIsMaker == false && m_viewmode == MAKER)
	{
		CString strInfo;
		strInfo.Format(_T("不具有＂%s＂的庄家资格！请检查！"),pStock->m_strName);
		MessageBox(strInfo,_T("提示"));
		return false;
	}
	m_bOwnerSet = true;
	m_editCode.SetWindowText(toUnicodeString(pStock->m_sQuote.szStockCode,6));
	m_bOwnerSet = false;
	m_editName.SetWindowText(pStock->m_strName);
	CString strText;
	int nPrice;
	if (pStock->m_sQuote.zjjg > 0)
	{
		strText.Format(_T("%.2f"),float(pStock->m_sQuote.zjjg)/1000);
		nPrice = pStock->m_sQuote.zjjg;
	}
	else
	{
		strText.Format(_T("%.2f"),float(pStock->m_sQuote.zrsp)/1000);
		nPrice = pStock->m_sQuote.zrsp;
	}
	m_editPrice.SetWindowText(strText);

	strText.Format(_T("%.2f"),m_fAmountValid);
	m_editAmountValid.SetWindowText(strText);
	
	if (m_viewmode == SALEOUT || m_viewmode == MAKER)
	{
		STradeCombo *pItem = getTradeCombo(pStock->m_sQuote.szStockCode);
		if (pItem)
		{
			strText.Format(_T("%d"),int(pItem->fSlValid));
		}
		else
		{
			strText = _T("");
		}
		if (m_viewmode == SALEOUT)
			m_editVolumeValid.SetWindowText(strText);
		else
			m_editVolumeValid_M.SetWindowText(strText);
	}

	if (m_viewmode == BUYIN || m_viewmode == MAKER)
	{
		if (nPrice > 0)
		{
			double fFei = m_fAmountValid * 0.001;
			strText.Format(_T("%d"),int((m_fAmountValid - fFei) / nPrice * 1000) / 100 * 100);
		}
		else
			strText = _T("0");
		m_editVolumeValid.SetWindowText(strText);
	}
	m_strCode = pStock->m_sQuote.szStockCode;
	gpData->m_strStockCode = pStock->m_sQuote.szStockCode;
	//::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,STOCK_FROM_BOTTOM_LIST,DWORD_PTR(pStock));
	Invalidate();
	return true;
}

void CDlgTrade::resetTradeCombo()
{	
	for(int n=0; n<m_listCombo.GetItemCount(); n++)
	{
		m_listCombo.SetItemText(n,5,_T(""));
		m_listCombo.SetItemText(n,6,_T(""));
		m_listCombo.SetItemText(n,7,_T(""));
		m_listCombo.SetItemText(n,9,_T(""));
		m_listCombo.SetItemText(n,10,_T(""));
	}
}

void CDlgTrade::FreshData()
{
	caclTradeCombo();
	if (m_viewmode == COMBO || m_viewmode == BUYIN || m_viewmode == SALEOUT)
	{/*
		if (m_viewmode == COMBO)
			InvalidateRect(m_rectValue);
		resetTradeCombo();*/
	}
	if (m_viewmode == BUYIN || m_viewmode == SALEOUT)
	{
		InvalidateRect(m_rectPriceVol);
	}
}

bool CDlgTrade::getValue()
{
	return commitTrade(322);
}

bool CDlgTrade::getMakerStock()
{
	return commitTrade(350);
}

STradeCombo * CDlgTrade::getTradeCombo(char * c_pCode)
{
	for(int n=0; n<m_vpTradeCombo.size(); n++)
	{
		if (strcmp(m_vpTradeCombo.at(n)->pStock->m_sQuote.szStockCode,c_pCode) == 0)
			return m_vpTradeCombo.at(n);
	}
	return NULL;
}
void CDlgTrade::OnEnChangeEditCode()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_bOwnerSet)
		return;

	CString strCode;
	m_editCode.GetWindowText(strCode);
	strCode.Trim();

	if (strCode.IsEmpty())
	{
		if (m_pTopDlg && m_pTopDlg->IsWindowVisible())
			m_pTopDlg->ShowWindow(SW_HIDE);
		return;
	}
	if (strCode.GetLength() == 9)
		strCode = strCode.Left(6);
	CRect rect,rw,r;
	if(m_pTopDlg->SetByKey(strCode.MakeUpper()) > 0)
	{
		m_editCode.GetWindowRect(&rect);
		m_pTopDlg->GetWindowRect(&rw);
		r.top = rect.top + 20;
		r.left = rect.left + 2;
		r.bottom = r.top + rw.Height();
		r.right = r.left + 200;
		m_pTopDlg->MoveWindow(r);
		m_pTopDlg->ShowWindow(SW_SHOW);
		m_editCode.SetFocus();
	}
	else
	{
		if (m_pTopDlg && m_pTopDlg->IsWindowVisible())
			m_pTopDlg->ShowWindow(SW_HIDE);
	}
	if (strCode.GetLength() != 6)
		return;
	char acCode[8];
	acCode[6] = 0;
	unicodeToAscii(strCode,acCode,8);

	if (m_pTopDlg && m_pTopDlg->IsWindowVisible())
		m_pTopDlg->ShowWindow(SW_HIDE);

	SStock * pStock = gpData->GetStock(acCode);
	if (pStock && setStockById(pStock->m_sQuote.nStockId))
	{		
		m_editVolume.SetFocus();
	}
	else
	{
		if (strlen(acCode) == 6)
		{
			MessageBox(_T("不正确的股票代码！"),_T("提示"));
			m_editCode.SetFocus();
		}
	}
}

BOOL CDlgTrade::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->wParam == VK_RETURN)
	{
		if (pMsg->hwnd == m_editCode.GetSafeHwnd())		
		{							
			m_pTopDlg->OnSelectOver();
		}
		return   TRUE;   
	}

	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;

		if (pMsg->wParam == VK_DOWN)
		{
			if (pMsg->hwnd == m_editCode.GetSafeHwnd())
			{
				if (m_pTopDlg->IsWindowVisible())
				{
					m_pTopDlg->SetFocus();
					if (m_pTopDlg->m_lstCode.GetItemCount() > 0)
					{
						m_pTopDlg->m_lstCode.SetSelectionMark(0);
						m_pTopDlg->m_lstCode.SetItemState(0, LVNI_FOCUSED | LVNI_SELECTED, LVNI_FOCUSED | LVNI_SELECTED); 
					}
					return TRUE;
				}
			}
		}

	if (pMsg->message == WM_CHAR && pMsg->hwnd != m_editCode.GetSafeHwnd() && pMsg->hwnd != m_editPrice.GetSafeHwnd() && pMsg->hwnd != m_editPrice_M.GetSafeHwnd() && pMsg->hwnd != m_editName.GetSafeHwnd()
		&&pMsg->hwnd != m_editVolume.GetSafeHwnd() &&pMsg->hwnd != m_editVolume_M.GetSafeHwnd() && pMsg->hwnd != m_editVolumeValid.GetSafeHwnd() && pMsg->hwnd != m_editAmountValid.GetSafeHwnd())
	{
		if ((pMsg->wParam >='0' && pMsg->wParam <= '9')
			||(pMsg->wParam >='a' && pMsg->wParam <= 'z')
			||(pMsg->wParam >='A' && pMsg->wParam <= 'Z'))
		{
			if (gpTopDlg && gpTopDlg->ActiveByKey(pMsg->wParam))
				return TRUE;
		}

	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgTrade::drawPriceVol(CDC * c_pDC,CRect c_rect,SStock * c_pStock,int c_nType)
{
	SStock * pStock = c_pStock;
	if (c_rect.bottom < c_rect.top)
		return;
	int nHeight = c_rect.Height() / 10;

	c_pDC->MoveTo(c_rect.left,c_rect.top);
	c_pDC->LineTo(c_rect.right,c_rect.top);

	c_pDC->MoveTo(c_rect.left,c_rect.top + nHeight * 5);
	c_pDC->LineTo(c_rect.right,c_rect.top + nHeight * 5);

	c_pDC->MoveTo(c_rect.left,c_rect.top + nHeight * 10);
	c_pDC->LineTo(c_rect.right,c_rect.top + nHeight * 10);

	c_pDC->MoveTo(c_rect.left,c_rect.top);
	c_pDC->LineTo(c_rect.left,c_rect.top + nHeight * 10);
	c_pDC->MoveTo(c_rect.right,c_rect.top);
	c_pDC->LineTo(c_rect.right,c_rect.top + nHeight * 10);
	CString strText;
	CRect rl,rr;

	int nOldBkMode = c_pDC->SetBkMode(TRANSPARENT);
	CFont *pOldFont = c_pDC->SelectObject(gpSkinManager->m_pFontSmall);
	rl = c_rect;	
	rl.bottom = rl.top + nHeight;
	rl.right = rl.left + rl.Width()/2;
	rr = rl;
	rr.left = rl.right;
	rr.right = c_rect.right - 2;
	
	char acBuf[12][5]={"卖⑤","卖④","卖③","卖②","卖①","买①","买②","买③","买④","买⑤"};
	rr.left += 2;
	rl.right -= 2;
	rl.left += 2;
	for(int n=0; n<10; n++)
	{
		CString strText;
		strText = toUnicodeString(acBuf[n],strlen(acBuf[n]));
		c_pDC->SetTextColor(gpSkinManager->getColor(RIGHTTEXTCOLOR));
		c_pDC->DrawText(strText,rl,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		int nPrice,nVol;
		if (pStock)
		{
			if (c_nType == 0)
			{
				if (n == 0){
					nVol = pStock->m_sQuote.SM5;
					nPrice = pStock->m_sQuote.SP5;
				}
				if (n == 1){
					nVol = pStock->m_sQuote.SM4;
					nPrice = pStock->m_sQuote.SP4;
				}
				if (n == 2){
					nVol = pStock->m_sQuote.SM3;
					nPrice = pStock->m_sQuote.SP3;
				}
				if (n == 3){
					nVol = pStock->m_sQuote.SM2;
					nPrice = pStock->m_sQuote.SP2;
				}
				if (n == 4){
					nVol = pStock->m_sQuote.SM1;
					nPrice = pStock->m_sQuote.SP1;
				}
				if (n == 5){
					nVol = pStock->m_sQuote.BM1;
					nPrice = pStock->m_sQuote.BP1;
				}
				if (n == 6){
					nVol = pStock->m_sQuote.BM2;
					nPrice = pStock->m_sQuote.BP2;
				}
				if (n == 7){
					nVol = pStock->m_sQuote.BM3;
					nPrice = pStock->m_sQuote.BP3;
				}
				if (n == 8){
					nVol = pStock->m_sQuote.BM4;
					nPrice = pStock->m_sQuote.BP4;
				}
				if (n == 9){
					nVol = pStock->m_sQuote.BM5;
					nPrice = pStock->m_sQuote.BP5;
				}
			}
			else
			if (c_nType == 1)
			{
				if (n == 0){
					nVol = pStock->m_sQuote.MSM5;
					nPrice = pStock->m_sQuote.MSP5;
				}
				if (n == 1){
					nVol = pStock->m_sQuote.MSM4;
					nPrice = pStock->m_sQuote.MSP4;
				}
				if (n == 2){
					nVol = pStock->m_sQuote.MSM3;
					nPrice = pStock->m_sQuote.MSP3;
				}
				if (n == 3){
					nVol = pStock->m_sQuote.MSM2;
					nPrice = pStock->m_sQuote.MSP2;
				}
				if (n == 4){
					nVol = pStock->m_sQuote.MSM1;
					nPrice = pStock->m_sQuote.MSP1;
				}
				if (n == 5){
					nVol = pStock->m_sQuote.MBM1;
					nPrice = pStock->m_sQuote.MBP1;
				}
				if (n == 6){
					nVol = pStock->m_sQuote.MBM2;
					nPrice = pStock->m_sQuote.MBP2;
				}
				if (n == 7){
					nVol = pStock->m_sQuote.MBM3;
					nPrice = pStock->m_sQuote.MBP3;
				}
				if (n == 8){
					nVol = pStock->m_sQuote.MBM4;
					nPrice = pStock->m_sQuote.MBP4;
				}
				if (n == 9){
					nVol = pStock->m_sQuote.MBM5;
					nPrice = pStock->m_sQuote.MBP5;
				}
			}

			if (nPrice > pStock->m_unPrevClose)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
			else
			if (nPrice < pStock->m_unPrevClose)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
			else
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
			if(nPrice > 0)
			{
				strText.Format(_T("%.2f"),float(nPrice)/1000);
			}
			else
				strText = "";
			c_pDC->DrawText(strText,rl,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);

			c_pDC->SetTextColor(gpSkinManager->getColor(VOLCOLOR));
			if (nVol > 0)
			strText.Format(_T("%d"),nVol/100);
			else
				strText = "";
			c_pDC->DrawText(strText,rr,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
		}
		rr.top += nHeight;
		rr.bottom += nHeight;
		rl.top += nHeight;
		rl.bottom += nHeight;
	}
	c_pDC->SelectObject(pOldFont);
	c_pDC->SetBkMode(nOldBkMode);
}

void CDlgTrade::OnBnClickedButtonConfirm()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText;
	CString strCode,strName,strPrice,strVolume;
	m_editCode.GetWindowText(strCode);
	m_editName.GetWindowText(strName);
	m_editPrice.GetWindowText(strPrice);
	m_editVolume.GetWindowText(strVolume);
	SStock * pStock = gpData->GetStock(strCode);
	if (pStock == NULL)
		return;
	strVolume.Trim();
	if (strVolume.IsEmpty())
	{
		MessageBox(_T("数量不能为空！"),_T("提示"));
		return;
	}
	if (strCode.IsEmpty())
	{
		MessageBox(_T("股票代码不能为空！"),_T("提示"));
		return;
	}

	char acBuf[256];
	unicodeToAscii(strVolume,acBuf,64);
	if (atoi(acBuf) <= 0)
	{
		MessageBox(_T("不正确的股票数量！"),_T("提示"));
		return;
	}
	unicodeToAscii(strPrice,acBuf,64);
	if (atof(acBuf) <= 0 || atof(acBuf) > 999)
	{
		MessageBox(_T("不正确的价格！"),_T("提示"));
		return;
	}
	if(pStock->m_sQuote.zrsp > 0 && atof(acBuf) > pStock->m_sQuote.zrsp/10)
	{
		MessageBox(_T("不正确的价格！"),_T("提示"));
		return;

	}
	if (pStock->m_strName.Find(_T("ST")) == 0
	 || pStock->m_strName.Find(_T("*ST")) == 0		
	 || pStock->m_strName.Find(_T("*SST")) == 0)
	{
		//MessageBox(_T("交易规则不允许买卖ST类股票"),_T("提示"));
		//return;
	}
	if (m_viewmode == BUYIN)
		strText.Format(_T("操作类别:买入\n股票代码:%s\n股票名称:%s\n委托价格:%s\n委托数量:%s\n委托方式:限价委托\n"),strCode,strName,strPrice,strVolume);
	else
	if (m_viewmode == SALEOUT)
		strText.Format(_T("操作类别:卖出\n股票代码:%s\n股票名称:%s\n委托价格:%s\n委托数量:%s\n委托方式:限价委托\n"),strCode,strName,strPrice,strVolume);

	if (MessageBox(strText,_T("委托确认"),MB_OKCANCEL) == IDOK)
	{
		if (commitTrade(301))
		{
			MessageBox(_T("委托已经成功提交！"),_T("提示"));
			commitTrade(322);
			m_editCode.SetWindowText(_T(""));
			m_editName.SetWindowText(_T(""));
			m_editPrice.SetWindowText(_T(""));
			m_editAmountValid.SetWindowText(_T(""));
			m_editVolume.SetWindowText(_T(""));
			m_editVolumeValid.SetWindowText(_T(""));
			//if (commitTrade(310))
			{
				caclTradeCombo();
				viewTradeCombo();
			}
		}
	}
}

bool CDlgTrade::commitTrade(int c_nFuncID)
{
	char acReq[1024];
	char * pRet = (char *)malloc(1024 * 128);
	int nLen = 0;
	if (c_nFuncID == 350)
	{
		nLen = gpData->MakeNormalReq(acReq,3019,(char *)&gpData->m_nUserID,sizeof(int));
	}
	else
	if (c_nFuncID == 322)
	{
		tagPass pass;
		pass.nId = gpData->m_nUserID;
		pass.acCode[0] = 0;
		strcpy(pass.acPass,gpData->m_acPass);
		nLen = gpData->MakeNormalReq(acReq,3013,(char *)&pass,sizeof(pass));
	}
	else
	if (c_nFuncID == 301 && (m_viewmode == BUYIN || m_viewmode == SALEOUT))//交易委托
	{
		char * pMem = new char[sizeof(tagPass) + sizeof(int) + sizeof(tagConsign)];
		tagPass *pPass = (tagPass *)pMem;
		int *pnConsignCount = (int *)(pMem + sizeof(tagPass));
		tagConsign *pConsign = (tagConsign *)(pMem + sizeof(tagPass) + sizeof(int));
		pPass->nId = gpData->m_nUserID;
		pPass->acCode[0] = 0;
		strcpy(pPass->acPass,gpData->m_acPass);

		CString strCode;
		CString strPrice;
		CString strVolume;
		m_editCode.GetWindowText(strCode);
		m_editPrice.GetWindowText(strPrice);
		m_editVolume.GetWindowText(strVolume);
		
		SStock *pStock = gpData->GetStock(strCode);
		if (pStock)
		pConsign->nStockId = pStock->m_sQuote.nStockId;
		char acVolume[32];
		unicodeToAscii(strVolume,acVolume,16);
		pConsign->nAmount = atoi(acVolume);
		char acPrice[32];
		unicodeToAscii(strPrice,acPrice,16);
		pConsign->fPrice = atof(acPrice);
		pConsign->nConsignID = 0;
		if (m_viewmode == BUYIN)
			pConsign->nOperate = 1;
		else
		if (m_viewmode == SALEOUT)
			pConsign->nOperate = 2;
		*pnConsignCount = 1;
		nLen = gpData->MakeNormalReq(acReq,3015,pMem,sizeof(tagPass) + sizeof(int) + sizeof(tagConsign));
		delete [] pMem;
	}
	else
	if (c_nFuncID == 301 && m_viewmode == MAKER)//庄家交易委托
	{
		char * pMem = new char[sizeof(tagPass) + sizeof(int) + sizeof(tagMakerConsignReq)];
		tagPass *pPass = (tagPass *)pMem;
		int *pnConsignCount = (int *)(pMem + sizeof(tagPass));
		tagMakerConsignReq *pConsign = (tagMakerConsignReq *)(pMem + sizeof(tagPass) + sizeof(int));
		pPass->nId = gpData->m_nUserID;
		pPass->acCode[0] = 0;
		strcpy(pPass->acPass,gpData->m_acPass);

		CString strCode;
		CString strPrice;
		CString strVolume;
		m_editCode.GetWindowText(strCode);
		m_editPrice.GetWindowText(strPrice);
		m_editVolume.GetWindowText(strVolume);
		CString strPriceM;
		CString strVolumeM;
		m_editPrice_M.GetWindowText(strPriceM);
		m_editVolume_M.GetWindowText(strVolumeM);
		SStock *pStock = gpData->GetStock(strCode);
		if (pStock)
		pConsign->nStockId = pStock->m_sQuote.nStockId;
		char acVolume[32];
		unicodeToAscii(strVolume,acVolume,16);
		char acVolumeM[32];
		unicodeToAscii(strVolumeM,acVolumeM,16);

		pConsign->nBuyAmount = atoi(acVolume);
		pConsign->nSaleAmount = atoi(acVolumeM);
		char acPrice[32];
		unicodeToAscii(strPrice,acPrice,16);
		char acPriceM[32];
		unicodeToAscii(strPriceM,acPriceM,16);

		pConsign->fBuyPrice = atof(acPrice);
		pConsign->fSalePrice = atof(acPriceM);
		pConsign->nType = 1;
		*pnConsignCount = 1;
		nLen = gpData->MakeNormalReq(acReq,3018,pMem,sizeof(tagPass) + sizeof(int) + sizeof(tagMakerConsignReq));
		delete [] pMem;
	}

	else
	if (c_nFuncID == 302)
	{
		char * pMem = new char[sizeof(tagPass) + sizeof(tagConsignHistoryReq)];
		tagPass * pPass = (tagPass *)(pMem);
		tagConsignHistoryReq *pReq = (tagConsignHistoryReq *)(pMem + sizeof(tagPass));
		pPass->nId = gpData->m_nUserID;		
		pPass->acCode[0] = 0;
		strcpy(pPass->acPass,gpData->m_acPass);

		COleDateTime dt;
		m_dateStart.GetTime(dt);
		sprintf(pReq->acBeginDate,"%d%.2d%.2d",dt.GetYear(),dt.GetMonth(),dt.GetDay());	
		sprintf(pReq->acEndDate,"%d%.2d%.2d",dt.GetYear(),dt.GetMonth(),dt.GetDay());	
		nLen = gpData->MakeNormalReq(acReq,3016,pMem,sizeof(tagPass) + sizeof(tagConsignHistoryReq));
		delete [] pMem;
	}
	else
	if (c_nFuncID == 303)
	{
		char * pMem = new char[sizeof(tagPass) + sizeof(tagBargainReq)];
		tagPass * pPass = (tagPass *)(pMem);
		tagBargainReq *pReq = (tagBargainReq *)(pMem + sizeof(tagPass));
		pPass->nId = gpData->m_nUserID;		
		pPass->acCode[0] = 0;
		strcpy(pPass->acPass,gpData->m_acPass);

		COleDateTime dt;
		m_dateStart.GetTime(dt);
		sprintf(pReq->acBeginDate,"%d%.2d%.2d",dt.GetYear(),dt.GetMonth(),dt.GetDay());	
		sprintf(pReq->acEndDate,"%d%.2d%.2d",dt.GetYear(),dt.GetMonth(),dt.GetDay());	
		nLen = gpData->MakeNormalReq(acReq,3017,pMem,sizeof(tagPass) + sizeof(tagBargainReq));
		delete [] pMem;
	}
	else
	if (c_nFuncID == 305 && m_viewmode == CANCEL)//交易撤单
	{
		char * pMem = new char[sizeof(tagPass) + sizeof(int) + sizeof(tagConsign)];
		tagPass * pPass = (tagPass *)(pMem);
		pPass->nId = gpData->m_nUserID;
		pPass->acCode[0] = 0;
		strcpy(pPass->acPass,gpData->m_acPass);
		int *pnConsignCount = (int *)(pMem + sizeof(tagPass));
		tagConsign *pConsign = (tagConsign *)(pMem + sizeof(tagPass) + sizeof(int));
		int nConsignCount = 0;
		for(int n=0; n<m_listTrade.GetItemCount(); n++)
		{
			if (m_listTrade.GetCheck(n) == FALSE)
				continue;
			pConsign[nConsignCount].nOperate = 3;
			SVirTrade * pT = (SVirTrade *)m_listTrade.GetItemData(n);
			pConsign[nConsignCount].nStockId = pT->pStock->m_sQuote.nStockId;
			pConsign[nConsignCount].fPrice = pT->fPrice;
			pConsign[nConsignCount].nAmount = pT->nVolume;
			pConsign[nConsignCount].nConsignID = pT->nId;
			nConsignCount++;
			if (nConsignCount >= 16)
				break;
		}
		if (nConsignCount > 0)
		{
			*pnConsignCount = nConsignCount;
			nLen = gpData->MakeNormalReq(acReq,3015,pMem,sizeof(tagPass) + sizeof(int) +  sizeof(tagConsign)*nConsignCount);
		}
		delete [] pMem;
	}

	if (nLen > 0)
	{
		nLen = gpCommSocket->SendData(acReq,nLen,true,pRet,1024 * 128);
	}
	/*
	if (nLen > 0 && c_nFuncID == 322)
	{
		FILE * f;
		f = fopen("d:\\cmt.322","wb");
		fwrite(pRet,1,nLen,f);
		fclose(f);
	}*/
	if (*(unsigned short *)(pRet + 12) > 0XFF00)
	{
		MessageBox(toUnicodeString(pRet + 14,strlen(pRet + 14)),_T("错误提示"));
		free(pRet);
		return false;
	}
	if (c_nFuncID == 350 && nLen > 14)
	{
		int nStockCount = *(int *)(pRet + 14);
		for(int n=0; n<nStockCount; n++)
		{
			int nTmp = *(int *)(pRet + 14 + sizeof(int) + n * sizeof(int));
			SStock * pStock = gpData->GetStock(nTmp);
			if (pStock)
			{
				pStock->m_bIsMaker = true;
			}
		}
	}
	else
	if(c_nFuncID == 322 && nLen > 22)
	{

		clearTradeCombo();
		tagAccount * pAccount;
		tagPosition * pItem;
		pAccount = (tagAccount *)(pRet + 14);
	
		m_fAmount = pAccount->fCash;//余额
		m_fAmountValid = pAccount->fCash - pAccount->fFreezeCash;//可用余额
		int nCount = *(int *)(pRet + 14 + sizeof(tagAccount));
		for(int n=0; n<nCount; n++)
		{
			pItem = (tagPosition *)(pRet + 14 + sizeof(tagAccount) + sizeof(int) + n * sizeof(tagPosition));
			PustTradeCombo(pItem->nStockId,pItem->nAmount,pItem->nFreezeAmount,pItem->fCost);
		}
	}
	else
	if (c_nFuncID == 302 && nLen > 18)
	{
		tagConsignHistory * pItem;

		int nCount = *(int *)(pRet + 14);
		for(int n=0; n<nCount; n++)
		{
			pItem = (tagConsignHistory *)(pRet + 18 + n * sizeof(tagConsignHistory));
			PushConsign(pItem);
		}
	}
	else
	if (c_nFuncID == 303 && nLen > 18)
	{
		tagBargain * pItem;

		int nCount = *(int *)(pRet + 14);
		for(int n=0; n<nCount; n++)
		{
			pItem = (tagBargain *)(pRet + 18 + n * sizeof(tagBargain));
			PushBargain(pItem->nStockId,pItem->nAmount,pItem->fPrice,pItem->nOperate,pItem->nState,pItem->acDateTime,pItem->acDateTime,pItem->nConsignID);
		}
		
	}
	free(pRet);
	if (nLen > 0)
		return true;
	else
		return false;
}

void CDlgTrade::PushConsign(tagConsignHistory * c_pItem)
{
	SVirTrade * pItem;
	pItem = new SVirTrade();
	pItem->nStockId = c_pItem->nStockId;
	pItem->fPrice = c_pItem->fPrice;
	pItem->nVolume = c_pItem->nAmount;
	pItem->nOperate = c_pItem->nOperate;
	pItem->nStatus = c_pItem->nState;
	strcpy(pItem->acDate,c_pItem->acDateTime);
	pItem->nId = c_pItem->nConsignID;
	pItem->nVolumeBargain = c_pItem->nBargainAmount;
	pItem->pStock = gpData->GetStock(c_pItem->nStockId);
	m_vpConsign.push_back(pItem);
}

void CDlgTrade::PushBargain(int c_nStockId,int c_nVolume,float c_fPrice,int c_nType,int c_nStatus,char * c_pOrderTime,char * c_pDealTime,int c_nOrderNumber)
{
	SVirTrade * pItem;
	pItem = new SVirTrade();
	pItem->nStockId = c_nStockId;
	pItem->fPrice = c_fPrice;
	pItem->nVolume = c_nVolume;
	pItem->nOperate = c_nType;

	pItem->nStatus = c_nStatus;
	strcpy(pItem->acDate,c_pOrderTime);
	strcpy(pItem->acDealDate,c_pDealTime);
	pItem->nId = c_nOrderNumber;
	pItem->pStock = gpData->GetStock(c_nStockId);
	m_vpBargain.push_back(pItem);
}
void CDlgTrade::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel = 0;
	SVirTrade * pTrade=NULL;
	for(int n=0; n<m_listTrade.GetItemCount(); n++)
	{
		if (m_listTrade.GetCheck(n))
		{
			pTrade = (SVirTrade *)m_listTrade.GetItemData(n);
			nSel ++;
		}
	}
	if (nSel > 0)
	{
		CString strText;
		if (pTrade && nSel == 1)
		{
			
			if (0 == pTrade->nOperate)
				strText.Format(_T("确定撤消以下委托？\n操作类别:买入\n股票代码:%s\n股票名称:%s\n委托价格:%.3f\n委托数量:%d\n委托单号:%d\n"),toUnicodeString(pTrade->pStock->m_sQuote.szStockCode,strlen(pTrade->pStock->m_sQuote.szStockCode)),pTrade->pStock->m_strName,pTrade->fPrice,pTrade->nVolume,pTrade->nId);
			else
			if (1 == pTrade->nOperate)
				strText.Format(_T("确定撤消以下委托？\n操作类别:卖出\n股票代码:%s\n股票名称:%s\n委托价格:%.3f\n委托数量:%d\n委托单号:%d\n确定撤消？"),toUnicodeString(pTrade->pStock->m_sQuote.szStockCode,strlen(pTrade->pStock->m_sQuote.szStockCode)),pTrade->pStock->m_strName,pTrade->fPrice,pTrade->nVolume,pTrade->nId);
		}
		else
			strText = _T("确定撤消所有委托？");
		if (MessageBox(strText,_T("撤单确认"),MB_OKCANCEL) != IDOK)
		{
			return;
		}
		if (commitTrade(305))
			MessageBox(_T("撤单已经提交！"),_T("提示"));
		OnBnClickedBtnCancel();
		commitTrade(322);
	}
	else
	{
		MessageBox(_T("请先选定待撤记录！"),_T("提示"));
	}
}

void CDlgTrade::clearConsign()
{
	while(m_vpConsign.size())
	{
		delete (m_vpConsign.back());
		m_vpConsign.pop_back();
	}
}

void CDlgTrade::clearBargain()
{
	while(m_vpBargain.size())
	{
		delete m_vpBargain.back();
		m_vpBargain.pop_back();
	}
}

void CDlgTrade::clearTradeCombo()
{
	while(m_vpTradeCombo.size())
	{
		delete m_vpTradeCombo.back();
		m_vpTradeCombo.pop_back();
	}
}
void CDlgTrade::PustTradeCombo(int c_nStockId,int c_nHold,int c_nFrozen,float c_fCost)
{
	STradeCombo * pItem = new STradeCombo();
	pItem->pStock = gpData->GetStock(c_nStockId);
	pItem->nStockId = c_nStockId;
	pItem->fPriceBase = c_fCost;
	pItem->fSl = c_nHold;
	pItem->fCostBase = pItem->fPriceBase * pItem->fSl;
	pItem->fSlValid = c_nHold - c_nFrozen;
	m_vpTradeCombo.push_back(pItem);
}
/*
void CDlgTrade::clearTradeCombo()
{
	std::vector<STradeCombo *>::iterator iter;
	while(m_vpTradeCombo.size())
	{
		iter = m_vpTradeCombo.back();
		delete (*iter);
		m_vpTradeCombo.pop_back();
	}
}
*/
void CDlgTrade::OnBnClickedButtonSelall()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int n=0; n<m_listTrade.GetItemCount(); n++)
		m_listTrade.SetCheck(n);
}

void CDlgTrade::OnBnClickedButtonSelno()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int n=0; n<m_listTrade.GetItemCount(); n++)
		m_listTrade.SetCheck(n,0);	
}

void CDlgTrade::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	if (bShow)
	{
		if (getValue())
		{			
			getMakerStock();
			//if (commitTrade(310))
			{
				caclTradeCombo();
				viewTradeCombo();
				setViewMode(COMBO);
				Invalidate();
			}
		}
	}
}

void CDlgTrade::OnBnClickedButtonRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BARGAIN == m_viewmode)
	{
		clearBargain();
		commitTrade(303);
		getBargain();
		viewBargain();
	}
	else
	if (CONSIGN == m_viewmode)
	{
		clearConsign();
		commitTrade(302);
		viewConsign();
	}
	else
	if (CANCEL == m_viewmode)
	{
		clearConsign();
		commitTrade(302);
		viewConsign(0);
	}
	else
	if (COMBO == m_viewmode)
	{
		OnBnClickedBtnInvest();
	}
}

void CDlgTrade::OnEnChangeEditVolume()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CDlgTrade::OnBnClickedBtnMaker()
{
	// TODO: 在此添加控件通知处理程序代码
	if (commitTrade(310))
	{
		caclTradeCombo();
		viewTradeCombo();
	}
	setViewMode(MAKER);
}
