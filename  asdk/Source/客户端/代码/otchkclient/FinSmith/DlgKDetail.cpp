// DlgKDetail.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "PicWnd.h"
#include "DlgKDetail.h"


// CDlgKDetail 对话框

IMPLEMENT_DYNAMIC(CDlgKDetail, CDialog)

CDlgKDetail::CDlgKDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKDetail::IDD, pParent)
{
	m_pPicWnd = NULL;
	m_rectDefault.SetRect(0,0,0,0);
}

CDlgKDetail::~CDlgKDetail()
{
}

void CDlgKDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgKDetail, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CDlgKDetail 消息处理程序

BOOL CDlgKDetail::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(rect);

	CDC SourceDC;
	CBitmap bitmap,*pOldBitmap;
	bitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	//CFont *pOldFont;
	
	SourceDC.CreateCompatibleDC(NULL);//生成兼容的CDC
	pOldBitmap = SourceDC.SelectObject(&bitmap);
	
	CFont * pOldFont = SourceDC.SelectObject(gpSkinManager->GetGraphFont());
	CBrush br(RGB(255,255,255));
	CBrush * pOldBrush = SourceDC.SelectObject(&br);
	PaintMe(&SourceDC);
	SourceDC.SelectObject(pOldBrush);
	GetClientRect(rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&SourceDC,0,0,SRCCOPY);	
	SourceDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	SourceDC.SelectObject(pOldFont);	
	SourceDC.DeleteDC();	
	
	return true;
	return CDialog::OnEraseBkgnd(pDC);
}

void CDlgKDetail::PaintMe(CDC * c_pDC)
{
	CBrush brush(gpSkinManager->getColor(BKCOLOR));
	//2010/08/25
	CRect rect;
	GetClientRect(rect);
	int nH = rect.Height() / 11;
	c_pDC->FillRect(rect,&brush);
	bool bIndex = true;
	if (gpData->IsStock(m_pStock->m_sQuote.szStockCode))
		bIndex = false;
	char acTitle[11][10] = {"时间：","现价：","开盘：","最高：","最低：","收盘：","成交量：","成交额：","涨跌幅：","换手率：","红绿灯："};
	c_pDC->SetBkMode(TRANSPARENT);
	CString strText;

	int unA,unB,unC;
	unA = INVALID_INT;
	unB = INVALID_INT;
	unC = INVALID_INT;
	int nDataLen = 0;
	char * pLeds = NULL;
	if (nDataLen && (m_nCycle == 5 || m_nCycle == 6 || m_nCycle == 7))
	{
		for(int n=0; n<nDataLen/(sizeof(int) + 3); n++)
		{
			if (m_kline.day >= *(int *)(pLeds + n * (sizeof(int) + 3)))
			{
				if(*(pLeds + n * (sizeof(int) + 3) + sizeof(int)) == 'G')
					unA = ID_L_G_S_LED;
				else
				if(*(pLeds + n * (sizeof(int) + 3) + sizeof(int)) == 'Y')
					unA = ID_L_Y_S_LED;
				else
				if(*(pLeds + n * (sizeof(int) + 3) + sizeof(int)) == 'R')
					unA = ID_L_R_S_LED;

				if(*(pLeds + n * (sizeof(int) + 3) + sizeof(int) + 1) == 'G')
					unC = ID_R_G_S_LED;
				else
				if(*(pLeds + n * (sizeof(int) + 3) + sizeof(int) + 1) == 'Y')
					unC = ID_R_Y_S_LED;
				else
				if(*(pLeds + n * (sizeof(int) + 3) + sizeof(int) + 1) == 'R')
					unC = ID_R_R_S_LED;

				if(*(pLeds + n * (sizeof(int) + 3) + sizeof(int) + 2) == 'G')
					unB = ID_M_G_S_LED;
				else
				if(*(pLeds + n * (sizeof(int) + 3) + sizeof(int) + 2) == 'Y')
					unB = ID_M_Y_S_LED;
				else
				if(*(pLeds + n * (sizeof(int) + 3) + sizeof(int) + 2) == 'R')
					unB = ID_M_R_S_LED;
			}
		}
	}
	else
		acTitle[10][0] = 0;
	
	for(int n=0; n<11; n++)
	{
		c_pDC->SetTextColor(gpSkinManager->getColor(RIGHTTEXTCOLOR));
		c_pDC->DrawText(toUnicodeString(acTitle[n],strlen(acTitle[n])),CRect(rect.left+2,rect.top+n*nH,rect.right,rect.top+(n+1)*nH),DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		if (m_pStock == NULL)
			continue;
		
		strText = "";
		if (n == 0)
		{
			c_pDC->SetTextColor(gpSkinManager->getColor(RIGHTTEXTCOLOR));
			if (m_nCycle == 5 || m_nCycle == 6 || m_nCycle == 7)
				strText.Format(_T("%d/%.2d/%.2d"),m_kline.day/10000,m_kline.day/100%100,m_kline.day % 100);
			else
				//strText.Format("%d/%.2d/%.2d",m_kline.day/10000,m_kline.day/100%100,m_kline.day % 100);
				strText.Format(_T("%d/%d/%d:%.2d"),m_kline.day / 1000000 % 100,m_kline.day / 10000 % 100,(m_kline.day % 10000)/60,(m_kline.day % 10000) % 60);
		}
		else
		if (n == 1)
		{
			strText.Format(_T("%.2f"),float(m_pStock->m_sQuote.zjjg)/1000);
			c_pDC->SetTextColor(gpSkinManager->GetStockValueColor(m_pStock,STR_XJ,_T(""),RGB(192,192,192)));
		}
		else
		if ( n == 2)
		{
			if (m_kline.open > m_nZrsp)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
			else
			if (m_kline.open < m_nZrsp)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
			else
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
			strText.Format(_T("%.2f"),float(m_kline.open)/1000);			
		}
		else
		if ( n == 3)
		{
			if (m_kline.high > m_nZrsp)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
			else
			if (m_kline.high < m_nZrsp)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
			else
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
			strText.Format(_T("%.2f"),float(m_kline.high)/1000);			
		}
		else
		if ( n == 4)
		{
			if (m_kline.low > m_nZrsp)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
			else
			if (m_kline.low < m_nZrsp)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
			else
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
			strText.Format(_T("%.2f"),float(m_kline.low)/1000);
		}
		else
		if ( n == 5)
		{
			if (m_kline.close > m_nZrsp)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
			else
			if (m_kline.close < m_nZrsp)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
			else
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
			strText.Format(_T("%.2f"),float(m_kline.close)/1000);
		}
		else
		if ( n == 6)
		{
			c_pDC->SetTextColor(gpSkinManager->getColor(RIGHTTEXTCOLOR));
			strText.Format(_T("%d"),m_kline.volume);
		}
		else
		if ( n == 7)
		{
			c_pDC->SetTextColor(gpSkinManager->getColor(RIGHTTEXTCOLOR));
			if ((bIndex && (m_nCycle == 5 || m_nCycle == 6 || m_nCycle == 7)) || !bIndex)
				strText.Format(_T("%d"),m_kline.amount);
			else
				strText = "-";
		}
		else
		if ( n == 8)
		{
			if (m_nZrsp > 0)
			{
				if (m_kline.close > m_nZrsp)
					c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
				else
				if (m_kline.close < m_nZrsp)
					c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
				else
					c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
				strText.Format(_T("%.2f%%"),(float(m_kline.close) - float(m_nZrsp))/m_nZrsp * 100);
			}
		}
		else
		if (n == 9)
		{
			if (m_pStock->m_dLtg > 0)
			{
				c_pDC->SetTextColor(gpSkinManager->getColor(RIGHTTEXTCOLOR));
				strText.Format(_T("%.2f%%"),float(m_kline.volume) * 100 * 100/m_pStock->m_dLtg);
			}
		}
		else
		if (n == 10 && unA != INVALID_INT && unB != INVALID_INT && unC != INVALID_INT)
		{
			int nFH = gpSkinManager->GetFontHeight(gpSkinManager->GetGraphFont());
			if (nFH < 17)
				nFH = 17;
			CRect r;
			r.SetRect(rect.left+2,rect.top+n*nH,rect.right-2,rect.top+(n+1)*nH);
			

			CSize szA = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(unA));
			CSize szB = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(unB));
			CSize szC = gpSkinManager->GetBmpSize(gpSkinManager->GetBitmap(unC));
			
			r.left = r.right - (szA.cx + szB.cx + szC.cx) * nFH/17 - 2;
			r.top += (r.Height() - szA.cy * nFH/17) / 2 + 1;
			r.bottom = r.top + szA.cy * nFH/17;

			r.right = r.left + szA.cx * nFH / 17;
			gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(unA),c_pDC,r);
			r.left = r.right;
			
			r.right = r.left + szB.cx * nFH / 17;
			gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(unB),c_pDC,r);
			r.left = r.right;

			r.right = r.left + szC.cx * nFH / 17;
			gpSkinManager->StretchIntoRectImage(gpSkinManager->GetBitmap(unC),c_pDC,r);
		}
		if (n != 10)
			c_pDC->DrawText(strText,CRect(rect.left+2,rect.top+n*nH,rect.right-2,rect.top+(n+1)*nH),DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	}
}

void CDlgKDetail::SetSSTOCK(SStock * c_pStock)
{
	m_pStock = c_pStock;
	if (m_pStock)
		SetWindowText(m_pStock->m_strName);
}

void CDlgKDetail::SetKLINE(KLINE * c_pKLine,int c_nZrsp,int c_nCycle)
{	
	memcpy(&m_kline,c_pKLine,sizeof(KLINE));
	m_nZrsp = c_nZrsp;
	m_nCycle = c_nCycle;
	if (IsWindowVisible())
		Invalidate();
}

void CDlgKDetail::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
}

void CDlgKDetail::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nID == SC_CLOSE)
	{
		if(m_pPicWnd)
		{
			m_pPicWnd->SetMouseLineOn(false);
			m_pPicWnd->Invalidate();
		}
	}

	CDialog::OnSysCommand(nID, lParam);
}

BOOL CDlgKDetail::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgKDetail::SetDefaultRect(CRect c_r)
{
	m_rectDefault = c_r;
}

bool CDlgKDetail::IsDefaultRect(CRect c_r)
{
	if (m_rectDefault.top == 0 && m_rectDefault.bottom == 0 && m_rectDefault.left == 0)
		return true;
	if ((c_r.top + c_r.Height()/2 == m_rectDefault.top+m_rectDefault.Height()/2) && c_r.left == m_rectDefault.left)
		return true;
	return false;
}
