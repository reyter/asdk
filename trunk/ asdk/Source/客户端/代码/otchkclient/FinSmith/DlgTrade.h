
/************************************************************************/
/* 交易模块                                                                     */
/************************************************************************/

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ComboListCtrl.h"
#include "TradeListCtrl.h"
#include "../winunit/IUserWin.h"
#include "afxdtctl.h"

struct STradeCombo{
	int		nStockId;
	double fSl;//数量
	double fSlValid;//可用数量
	double fPriceBase;//成本价格
	double fCostBase;
	double fCost;
	int   nBuyToday;//今买
	int	  nSaleToday;//今卖
	SStock * pStock;
};

struct SVirTrade{
	int	nId;	//委托号
	int nOperate;//种类，0买单，1卖单，2撤单
	double fPrice;//价格
	int nVolume;//数量
	int nVolumeBargain;//成交数量
	int nStockId;
	char acDate[24];//委托时间
	char acDealDate[24];//成交时间
	int nStatus;//
	SStock * pStock;
	CString getOperateDesc()
	{
		if (nOperate == 0) return _T("买入");
		if (nOperate == 1) return _T("卖出");
		if (nOperate == 2) return _T("撤单");
		return _T("");
	}
	CString getStatusDesc()
	{
		if (nStatus == -1)	
		{
			if (nOperate == 2)
				return _T("失败");
			else
				return _T("撤消");
		}
		if (nStatus == 1)	return _T("等待");
		if (nStatus == 2)	return _T("部分成交");
		if (nStatus == 3)	return _T("部分撤销");
		if (nStatus == 4)	return _T("完成");
		return _T("");
	}
};

// CDlgTrade 对话框
class CTopDlg;
class CDlgTrade : public CDialog,public IUserWin
{
	DECLARE_DYNAMIC(CDlgTrade)
	typedef enum VIEWMODE{MODENULL=0,COMBO,BUYIN,SALEOUT,MAKER,CANCEL,CONSIGN,BARGAIN};
public:
	CDlgTrade(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTrade();

// 对话框数据
	enum { IDD = IDD_TRADE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBargain();
	afx_msg void OnBnClickedButtonConsign();
	afx_msg void OnBnClickedButtonSearch();	
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnBnClickedBtnInvest();
	afx_msg void OnBnClickedBtnBuy();
	afx_msg void OnBnClickedBtnSale();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	void setViewMode(VIEWMODE c_viewmode);
	void setLayout();
	bool setStockById(int c_nStockId);
	void getTradeCombo();
	void caclTradeCombo();
	void viewTradeCombo();
	void resetTradeCombo();	
	void viewConsign(int c_nStatus=-1);
	void getBargain();
	void viewBargain();
	void FreshData();
	bool getValue();
	bool getMakerStock();
	CWnd * GetWnd(){return this;};
	STradeCombo * getTradeCombo(char * c_pCode);
	void drawPriceVol(CDC * c_pDC,CRect c_rect,SStock * c_pStock,int c_nType=0);
	void clearConsign();
	void clearBargain();
	void clearTradeCombo();
	bool commitTrade(int c_nFuncID);
	void PushConsign(tagConsignHistory *);
	void PushBargain(int c_nStockId,int c_nVolume,float c_fPrice,int c_nType,int c_nStatus,char *c_pOderTime,char * c_pDealTime,int c_nOrderNumber);
	void PustTradeCombo(int c_nStockId,int c_nHold,int c_nFrozen,float c_fCost);	
public:
	VIEWMODE m_viewmode;
	bool m_bOwnerSet;//主动设置
	int m_nHeadHeight;
	int m_nToolsHeight;//按钮条高度
	int m_nInvestHeight;
	CRect m_rectPriceVol;
	CRect m_rectPriceVolMaker;
	double m_fAmount;//余额
	double m_fAmountValid;//可用余额
	double m_fCost;//市值
	double m_fValue;//总资产
	double m_fProfit;//盈亏
	int m_nSerialno;//Request Serialno
	CRect m_rectValue;
	CString m_strCode;
	CTradeListCtrl m_listTrade;	//撤单、委托的显示列表
	CEdit m_editCode;
	CEdit m_editName;
	CEdit m_editPrice;
	CEdit m_editAmountValid;
	CEdit m_editVolumeValid;
	CEdit m_editVolume;
	CTransparentStatic m_stCode;
	CTransparentStatic m_stName;
	CTransparentStatic m_stPrice;
	CTransparentStatic m_stAmountValid;
	CTransparentStatic m_stVolumeValid;
	CTransparentStatic m_stVolume;
	CButton m_btnConfirm;
	CComboListCtrl m_listCombo;//持仓、买入、卖出显示列表
	CXPButton m_btnCombo;
	CXPButton m_btnBuyin;
	CXPButton m_btnSaleout;
	CXPButton m_btnCancel;
	CXPButton m_btnConsign;
	CXPButton m_btnBargain;
	CButton m_btnRefresh;
	CTopDlg * m_pTopDlg;
	std::vector<STradeCombo *> m_vpTradeCombo;//持仓组合
	std::vector<SVirTrade *> m_vpConsign;//委托
	std::vector<SVirTrade *> m_vpBargain;//成交
	afx_msg void OnNMDblclkListCombo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListTrade(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditCode();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonConfirm();
	CButton m_btnDoCancel;
	CButton m_btnDoSelAll;
	CButton m_btnDoSelNone;
	CDateTimeCtrl m_dateStart;
	CDateTimeCtrl m_dateEnd;
	CTransparentStatic m_stDateStart;
	CTransparentStatic m_stDateEnd;
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonSelall();
	afx_msg void OnBnClickedButtonSelno();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnEnChangeEditVolume();
	CXPButton m_btnMaker;
	afx_msg void OnBnClickedBtnMaker();
	CStatic m_stPrice_M;
	CStatic m_stVolume_M;
	CStatic m_stVolumeValid_M;
	CEdit m_editPrice_M;
	CEdit m_editVolume_M;
	CEdit m_editVolumeValid_M;
};
