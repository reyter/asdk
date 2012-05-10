
/************************************************************************/
/* ����ģ��                                                                     */
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
	double fSl;//����
	double fSlValid;//��������
	double fPriceBase;//�ɱ��۸�
	double fCostBase;
	double fCost;
	int   nBuyToday;//����
	int	  nSaleToday;//����
	SStock * pStock;
};

struct SVirTrade{
	int	nId;	//ί�к�
	int nOperate;//���࣬0�򵥣�1������2����
	double fPrice;//�۸�
	int nVolume;//����
	int nVolumeBargain;//�ɽ�����
	int nStockId;
	char acDate[24];//ί��ʱ��
	char acDealDate[24];//�ɽ�ʱ��
	int nStatus;//
	SStock * pStock;
	CString getOperateDesc()
	{
		if (nOperate == 0) return _T("����");
		if (nOperate == 1) return _T("����");
		if (nOperate == 2) return _T("����");
		return _T("");
	}
	CString getStatusDesc()
	{
		if (nStatus == -1)	
		{
			if (nOperate == 2)
				return _T("ʧ��");
			else
				return _T("����");
		}
		if (nStatus == 1)	return _T("�ȴ�");
		if (nStatus == 2)	return _T("���ֳɽ�");
		if (nStatus == 3)	return _T("���ֳ���");
		if (nStatus == 4)	return _T("���");
		return _T("");
	}
};

// CDlgTrade �Ի���
class CTopDlg;
class CDlgTrade : public CDialog,public IUserWin
{
	DECLARE_DYNAMIC(CDlgTrade)
	typedef enum VIEWMODE{MODENULL=0,COMBO,BUYIN,SALEOUT,MAKER,CANCEL,CONSIGN,BARGAIN};
public:
	CDlgTrade(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTrade();

// �Ի�������
	enum { IDD = IDD_TRADE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	bool m_bOwnerSet;//��������
	int m_nHeadHeight;
	int m_nToolsHeight;//��ť���߶�
	int m_nInvestHeight;
	CRect m_rectPriceVol;
	CRect m_rectPriceVolMaker;
	double m_fAmount;//���
	double m_fAmountValid;//�������
	double m_fCost;//��ֵ
	double m_fValue;//���ʲ�
	double m_fProfit;//ӯ��
	int m_nSerialno;//Request Serialno
	CRect m_rectValue;
	CString m_strCode;
	CTradeListCtrl m_listTrade;	//������ί�е���ʾ�б�
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
	CComboListCtrl m_listCombo;//�ֲ֡����롢������ʾ�б�
	CXPButton m_btnCombo;
	CXPButton m_btnBuyin;
	CXPButton m_btnSaleout;
	CXPButton m_btnCancel;
	CXPButton m_btnConsign;
	CXPButton m_btnBargain;
	CButton m_btnRefresh;
	CTopDlg * m_pTopDlg;
	std::vector<STradeCombo *> m_vpTradeCombo;//�ֲ����
	std::vector<SVirTrade *> m_vpConsign;//ί��
	std::vector<SVirTrade *> m_vpBargain;//�ɽ�
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
