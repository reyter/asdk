// TopDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProListCtrl.h"
#include "../public/data_struct.h"
#include "TopDlg.h"


// CTopDlg 对话框

IMPLEMENT_DYNAMIC(CTopDlg, CDialog)
int CALLBACK ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
CTopDlg::CTopDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTopDlg::IDD, pParent)
	, m_pEdit(NULL)
{
	m_bSelf = false;
}

CTopDlg::~CTopDlg()
{
}

void CTopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CODE, m_lstCode);
	DDX_Control(pDX, IDC_HIDE, m_btnHide);
	DDX_Control(pDX, IDC_EDIT_CODE, m_edit);
}


BEGIN_MESSAGE_MAP(CTopDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CODE, &CTopDlg::OnLvnItemchangedListCode)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_HIDE, &CTopDlg::OnBnClickedHide)
	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &CTopDlg::OnHdnItemdblclickListCode)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CODE, &CTopDlg::OnNMDblclkListCode)
	ON_WM_CTLCOLOR()
	ON_WM_MEASUREITEM()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_MESSAGE(WM_ENTER_KEY,OnEnterKey)
	ON_EN_CHANGE(IDC_EDIT_CODE, &CTopDlg::OnEnChangeEditCode)
	ON_WM_ERASEBKGND()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


// CTopDlg 消息处理程序

int CTopDlg::SetByKey(CString c_strKey)
{
	unsigned int iLen;
	SStock *pCode;
	CString strValue;
	CString strName;
	int iType;
	if (c_strKey.GetAt(0) >= '0' && c_strKey.GetAt(0) <= '9')
		iType = 0;
	else iType = 1;
	m_strKey = c_strKey;
	m_nSortField = iType;
	iLen = c_strKey.GetLength();
	m_lstCode.DeleteAllItems();

	USES_CONVERSION;
	if (m_bSelf)
	{
	std::vector<SQuickKey *>::iterator iterKey;
	char acKey[10];
	strncpy(acKey,(char *)W2A(c_strKey.GetBuffer()),10);
	c_strKey.ReleaseBuffer();
	acKey[9] = 0;
	for(iterKey=gpData->m_vpQuickKey.begin(); iterKey!=gpData->m_vpQuickKey.end(); iterKey++)
	{
		SQuickKey * pKey = *iterKey;
		if (strncmp(acKey,pKey->m_acKey,strlen(acKey)) == 0)
		{
			m_lstCode.InsertItem(m_lstCode.GetItemCount(),toUnicodeString((*iterKey)->m_acKey,strlen((*iterKey)->m_acKey)));
			m_lstCode.SetItemText(m_lstCode.GetItemCount() - 1,1,toUnicodeString((*iterKey)->m_acKeyDesc,strlen((*iterKey)->m_acKeyDesc)));
		}
	}
	}
	//std::vector<SStock *>::iterator iter;
	std::map<CString,SStock * >::iterator iter;
	//for(iter = m_pData->m_vpStocks.begin(); iter != m_pData->m_vpStocks.end(); iter++)	
	for(iter = m_pData->m_mapStocks.begin(); iter != m_pData->m_mapStocks.end(); iter++)	
	{		;
		pCode = (*iter).second;
		/*
		if ((strncmp(pCode->m_acCode,"09",2) == 0) 
			||(strncmp(pCode->m_acCode,"39",2) == 0) 
			|| (strncmp(pCode->m_acCode + 6,".S",2) == 0))
			continue;
		*/
		if (m_bSelf)
		{
		if (strcmp(pCode->m_acKind,"md_szag") != 0
		  &&strcmp(pCode->m_acKind,"md_szbg") != 0
		  &&strcmp(pCode->m_acKind,"md_cyb") != 0
		  &&strcmp(pCode->m_acKind,"md_szwa") != 0
		   &&strcmp(pCode->m_acKind,"md_szzs") != 0
		  &&strcmp(pCode->m_acKind,"md_shag") != 0
		  &&strcmp(pCode->m_acKind,"md_shbg") != 0
		  &&strcmp(pCode->m_acKind,"md_shwa") != 0
		   &&strcmp(pCode->m_acKind,"md_shzs") != 0
		   &&strcmp(pCode->m_acKind,"md_shetf") != 0
		   &&strcmp(pCode->m_acKind,"md_shlof") != 0
		   &&strcmp(pCode->m_acKind,"md_szlof") != 0
		   &&strcmp(pCode->m_acKind,"md_shjj") != 0
		   &&strcmp(pCode->m_acKind,"md_szjj") != 0
		   &&strcmp(pCode->m_acKind,"md_szetf") != 0)
		   continue;
		}
		else
		if (strcmp(pCode->m_acKind,"md_szag") != 0
		  &&strcmp(pCode->m_acKind,"md_szbg") != 0
		  &&strcmp(pCode->m_acKind,"md_cyb") != 0
		  &&strcmp(pCode->m_acKind,"md_szwa") != 0
		  &&strcmp(pCode->m_acKind,"md_shag") != 0
		  &&strcmp(pCode->m_acKind,"md_shbg") != 0
		  &&strcmp(pCode->m_acKind,"md_shwa") != 0
		   &&strcmp(pCode->m_acKind,"md_shetf") != 0
		   &&strcmp(pCode->m_acKind,"md_shlof") != 0
		   &&strcmp(pCode->m_acKind,"md_szlof") != 0
		   &&strcmp(pCode->m_acKind,"md_shjj") != 0
		   &&strcmp(pCode->m_acKind,"md_szjj") != 0
		   &&strcmp(pCode->m_acKind,"md_szetf") != 0)
		  continue;
		  
		if (iType == 1)
			strValue = pCode->m_acSpell;
		else
		{
			strValue = pCode->m_sQuote.szStockCode;
			strValue = strValue.Left(6);
		}
		if (strValue.Left(iLen) == c_strKey || (iLen >= 2 && strValue.Find(c_strKey) > 0) )
		{
			m_lstCode.InsertItem(m_lstCode.GetItemCount(),strValue);
			strName = pCode->m_strName;
			m_lstCode.SetItemText(m_lstCode.GetItemCount() - 1,1,strName);
			m_lstCode.SetItemData(m_lstCode.GetItemCount() - 1,(DWORD_PTR)pCode);
		}
		if (m_lstCode.GetItemCount() > 30)
			break;
	}
	if (m_lstCode.GetItemCount() > 1)
		m_lstCode.SortItems(ListCompare,(DWORD)this);
	if (m_lstCode.GetItemCount() > 0)
	{
		//m_lstCode.SetFocus();
		m_lstCode.SetSelectionMark(0);
	}
	CRect rect;
	if (m_lstCode.GetItemCount() == 0 && m_bSelf == false)
	{
		this->ShowWindow(SW_HIDE);
		return 0;
	}
	else
	{
		CRect rw;
		GetWindowRect(&rw);
		GetClientRect(&rect);
		rect.top = 0;
		if (m_bSelf)
		{
			rect.top += 20;
		}
		if (m_lstCode.GetItemCount() < 15 && m_bSelf == false)
		{
			if (m_bSelf)
				rect.bottom = m_lstCode.GetItemCount() * 18 + 10 + 20;
			//else
			//	rect.bottom = m_lstCode.GetItemCount() * 18 + 10;
		}
		else
		{
			//if (m_bSelf)
			//	rect.bottom = 15 * 18 + 10 + 20;
			//else
			//	rect.bottom = 15 * 18 + 10;
		}
		
		if (m_bSelf)
		{
			
		}
		else
		{
			//MoveWindow(rw);
			//m_lstCode.MoveWindow(rect);
			//rw.bottom = rw.top + rect.Height() + 20;
		}
		m_btnHide.SetForegroundWindow();
	}
	return 1;
}

BOOL CTopDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
//	m_btnHide.SetBtnBMP(IDB_CLOSE,IDB_CLOSE);
	m_btnHide.SetBorder(false);
	m_btnHide.ShowWindow(SW_HIDE);
	CRect r,rect;
	GetClientRect(&rect);
	r.right = rect.Width() - 1;
	r.left = rect.right - 11;
	r.top = 1;
	r.bottom = 12;
	m_btnHide.MoveWindow(&r);
	m_lstCode.InsertColumn(0,_T("拼音"));
	m_lstCode.SetColumnWidth(0,60);
	m_lstCode.InsertColumn(1,_T("名称"));
	m_lstCode.SetColumnWidth(1,80);
	m_lstCode.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL);
	//m_lstCode.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES);
	m_lstCode.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

int CTopDlg::SetLinkEdit(CEdit * c_pWnd,CData * c_pData,int c_nType)
{
	m_pData = c_pData;
	if (c_pWnd == NULL)
	{
		m_pEdit = &m_edit;
		m_bSelf = true;
		m_edit.ShowWindow(SW_SHOW);
	}
	else
	{
		m_pEdit = c_pWnd;
		m_bSelf = false;
		m_edit.ShowWindow(SW_HIDE);
	}
	
	m_nType = c_nType;
	return 0;
}

void CTopDlg::OnLvnItemchangedListCode(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CTopDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	OnSelectOver();
	CDialog::OnOK();
	if (m_pEdit)
		m_pEdit->SetFocus();
}

void CTopDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect,rw,r;
	GetClientRect(&rect);
	
	if (m_bSelf)
	{
		rect.top += 4;
		
		rect.left += 4;
		rect.right -= 4;
		if (m_edit)
		{
			m_edit.GetWindowRect(rw);
			rect.bottom = rect.top + rw.Height();
			m_edit.MoveWindow(rect);
			GetClientRect(&rect);
			rect.top += 4 + rw.Height();
			rect.left += 4;
			rect.bottom -= 4;
			rect.right -= 4;
			m_lstCode.MoveWindow(rect);
		}
	}
	else
	{
		if (m_edit)
		{
			m_edit.ShowWindow(SW_HIDE);
			m_lstCode.MoveWindow(rect);
		}
	}
}

void CTopDlg::OnBnClickedHide()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}

void CTopDlg::OnHdnItemdblclickListCode(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CTopDlg::OnNMDblclkListCode(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
	CString strSel;
	SStock * pCode;
	if (m_pEdit)
	{
		strSel = m_lstCode.GetItemText(pNMLV->iItem,0);
		pCode = (SStock *)m_lstCode.GetItemData(pNMLV->iItem);
		if (pCode)
		{
			OnSelectOver();
		}
		else
		{
			OnSelectOver();
		}
	}
}

HBRUSH CTopDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CTopDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDCtl == IDC_LIST_CODE)
		lpMeasureItemStruct->itemHeight = 18;

	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CTopDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if (nChar == 13)
	//{
		//OnSelectOver();
	//}
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTopDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if (nChar == 13)
	//{
	//	OnSelectOver();
	//}
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTopDlg::OnSelectOver()
{
	USES_CONVERSION;
	if (true)
	{
		CString strSel;
		m_edit.GetWindowText(strSel);

		SStock * pCode;
		int iSel;
		if (m_pEdit && (m_lstCode.GetItemCount() > 0))
		{
			iSel = m_lstCode.GetSelectionMark();
			if (iSel == -1)
				iSel = 0;
			if (m_nType == 0 || m_nType == 2)
				strSel = m_lstCode.GetItemText(iSel,0);
			else
			if (m_nType == 1 || m_nType == 3)
				strSel = m_lstCode.GetItemText(iSel,1);
			pCode = (SStock *)m_lstCode.GetItemData(iSel);
			if (pCode == NULL && m_bSelf)
			{
				ShowWindow(SW_HIDE);
				CString str = m_lstCode.GetItemText(iSel,0);
				if (str == "06")
				{										
					::PostMessage(m_pData->m_hwndMain,WM_GOTO_STOCK,SHOW_GROUP_WINDOW,0);
				}				
				else
				if (str == "60" || str == "61" || str == "62" || str == "63" || str == "64")
				{					
					int nCode = 0;
					nCode = atoi((char *)W2A(str.GetBuffer()));
					str.ReleaseBuffer();					
					::PostMessage(m_pData->m_hwndMain,WM_GOTO_STOCK,SHOW_STOCKS,nCode);
				}				
				else
				if (str == "KDJ")
				{
					::PostMessage(m_pData->m_hwndMain,WM_COMMAND,ID_TECH_KDJ,0);
				}
				else
				if (str == "RSI")
				{
					::PostMessage(m_pData->m_hwndMain,WM_COMMAND,ID_TECH_RSI,0);
				}
				else
				if (str == "MACD")
				{
					::PostMessage(m_pData->m_hwndMain,WM_COMMAND,ID_TECH_MACD,0);
				}
				else
				if (str == "EMA")
				{
					::PostMessage(m_pData->m_hwndMain,WM_COMMAND,ID_TECH_EMA,0);
				}
				else
				if (str == "MA")
				{
					::PostMessage(m_pData->m_hwndMain,WM_COMMAND,ID_TECH_MA,0);
				}
				else
				if (str == "BOLL")
				{
					::PostMessage(m_pData->m_hwndMain,WM_COMMAND,ID_TECH_BOLL,0);
				}
				else
				if (str == "VOLUME")
				{
					::PostMessage(m_pData->m_hwndMain,WM_COMMAND,ID_TECH_VOLUME,0);
				}
				return;
			}
			
			strSel = pCode->m_sQuote.szStockCode;
			if (m_bSelf)
			{
				ShowWindow(SW_HIDE);
				m_pData->m_strStockCode = pCode->m_sQuote.szStockCode;
				gpData->m_nStockSource = 0;
				::PostMessage(m_pData->m_hwndMain,WM_GOTO_STOCK,0,(DWORD_PTR)pCode);				
				return;
			}
			if (m_nType == 1 || m_nType == 3)
				strSel = pCode->m_strName;
			if(m_nType == 0 || m_nType == 1)
				m_pEdit->SetWindowText(strSel);
			else
			{
				CString strChg;
				m_pEdit->GetWindowText(strChg);
				strChg.MakeUpper();
				//strChg.Replace(m_strKey,strSel);
				strChg = strChg.Left(strChg.GetLength()-m_strKey.GetLength());
				strChg += strSel;
				m_pEdit->SetWindowText(strChg);
				m_pEdit->SetSel(strChg.GetLength(),strChg.GetLength(),FALSE);
			}
			
			ShowWindow(SW_HIDE);
			if (m_bSelf == false)
			{
				m_pEdit->SetFocus();
				if (m_nType == 0 || m_nType == 1)
					::PostMessage(this->GetParent()->GetSafeHwnd(),WM_ENTER_KEY,13,0);
			}
		}
		else
		{
			ShowWindow(SW_HIDE);
		}
		
	}	
}

LRESULT CTopDlg::OnEnterKey(WPARAM wParam,LPARAM lParam)
{
	CString strSel;
	SStock * pCode;
	int iSel;
	if (m_pEdit && (m_lstCode.GetItemCount() > 0))
	{
		iSel = m_lstCode.GetSelectionMark();
		if (iSel == -1)
			iSel = 0;
		strSel = m_lstCode.GetItemText(iSel,0);
		if (wParam == 13)
		{
			pCode = (SStock *)m_lstCode.GetItemData(iSel);
			strSel = pCode->m_sQuote.szStockCode;
			m_pEdit->SetWindowText(strSel);
			m_pEdit->SetFocus();
			ShowWindow(SW_HIDE);		
		}
		if (wParam == 40)
		{
			//m_lstCode.SetFocus();
			if (iSel == 0)
			{
				m_lstCode.SetSelectionMark(0);
				m_lstCode.SetItemState(0, LVNI_FOCUSED | LVNI_SELECTED, LVNI_FOCUSED | LVNI_SELECTED); 
			}
		}
	}
	return 0;
}

bool CTopDlg::ActiveByKey(WPARAM wParam)
{
	CString strKey;
	strKey = char(wParam);
	

	int     nFullWidth;
	int     nFullHeight;
	CRect   rect;

	nFullWidth = GetSystemMetrics(SM_CXSCREEN);   
	nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	CRect rcWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcWorkArea,0);

	rect.left = nFullWidth - 184;
	rect.top = rcWorkArea.bottom - 230;
	rect.right = nFullWidth - 4;
	rect.bottom = rcWorkArea.bottom;
	MoveWindow(rect);
	SetByKey(strKey);
	ShowWindow(SW_SHOW);
	m_edit.SetFocus();
	m_edit.SetWindowText(strKey);
	m_edit.SetSel(-1);
	//m_lstCode.SetFocus();
	return true;
}
int CALLBACK ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CTopDlg* pV=(CTopDlg *)lParamSort;
	SStock * pRecord1,*pRecord2;

	CString strValue1,strValue2;
	
	pRecord1 = (SStock *)lParam1;
	pRecord2 = (SStock *)lParam2;
	if (pRecord1 == NULL)
		return -1;
	if (pRecord2 == NULL)
		return 1;
	if (pV->m_nSortField == 1)
	{
		if (strlen(pRecord1->m_acSpell) < strlen(pRecord2->m_acSpell))
			return -1;
		else
		if (strlen(pRecord1->m_acSpell) > strlen(pRecord2->m_acSpell))
			return 1;
		else
		return strcmp(pRecord1->m_acSpell,pRecord2->m_acSpell);
	}
	else
	{
		if (strncmp(pRecord1->m_sQuote.szStockCode,pRecord2->m_sQuote.szStockCode,6) == 0)
		{
			int nCmp = strcmp(pRecord1->m_sQuote.szStockCode,pRecord2->m_sQuote.szStockCode);
			if (nCmp < 0)
				return 1;
			else
			if (nCmp > 0)
				return -1;
			return nCmp;
		}
		else
		{			
			return strcmp(pRecord1->m_sQuote.szStockCode,pRecord2->m_sQuote.szStockCode);
		}
	}
}

void CTopDlg::OnEnChangeEditCode()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strKey;
	m_edit.GetWindowText(strKey);
	if (strKey.IsEmpty())
		ShowWindow(SW_HIDE);
	else
	{
		if (strKey.GetAt(0) < '0' || strKey.GetAt(0) > '9')		
			strKey.MakeUpper();
		SetByKey(strKey);
	}
}

BOOL CTopDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->hwnd == m_edit.GetSafeHwnd() || pMsg->hwnd == m_lstCode.GetSafeHwnd())
	{
		if (pMsg->wParam == VK_RETURN && pMsg->message == WM_KEYUP)
		{
			OnSelectOver();
			return  TRUE;
		}
		if (pMsg->message == WM_KEYDOWN)
		{
			if ((pMsg->wParam >='0' && pMsg->wParam <= '9')
				||(pMsg->wParam >='a' && pMsg->wParam <= 'z')
				||(pMsg->wParam >='A' && pMsg->wParam <= 'Z')
				|| pMsg->wParam == VK_BACK)
			{
				if (pMsg->hwnd != m_edit.GetSafeHwnd())
				{
					CString strKey;
					m_edit.GetWindowText(strKey);
					if (pMsg->wParam == VK_BACK)
					{
						strKey = strKey.Left(strKey.GetLength() - 1);
					}
					else
					{
						strKey += char(pMsg->wParam);						
					}
					m_edit.SetWindowText(strKey);
					//SetByKey(strKey);
					return TRUE;
				}
			}
			if (pMsg->wParam == VK_DOWN && pMsg->hwnd == m_edit.GetSafeHwnd())
			{
				if (m_lstCode.GetItemCount() > 0)
				{
					int nSel = m_lstCode.GetSelectionMark();
					nSel++;
					if (nSel < m_lstCode.GetItemCount())
					{
						m_lstCode.SetSelectionMark(nSel);
						m_lstCode.EnsureVisible(nSel,true);
						m_lstCode.Invalidate();
					}
				}

				return TRUE;
			}
			if (pMsg->wParam == VK_UP && pMsg->hwnd == m_edit.GetSafeHwnd())
			{
				if (m_lstCode.GetItemCount() > 0)
				{
					int nSel = m_lstCode.GetSelectionMark();
					nSel--;
					if (nSel >= 0)
					{
						m_lstCode.SetSelectionMark(nSel);
						m_lstCode.EnsureVisible(nSel,true);
						m_lstCode.Invalidate();
					}
				}
				
				return TRUE;
			}
		}
	}
	if (pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CTopDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(rect);
	pDC->FillRect(rect,   &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
	return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}

void CTopDlg::OnKillFocus(CWnd* pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);

	// TODO: 在此处添加消息处理程序代码
}
