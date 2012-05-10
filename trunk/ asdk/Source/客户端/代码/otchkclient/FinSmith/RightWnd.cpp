// RightWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "RightWnd.h"


// CRightWnd

IMPLEMENT_DYNAMIC(CRightWnd, CWnd)

CRightWnd::CRightWnd()
{
	m_rectTraceData.SetRect(0,0,0,0);
}

CRightWnd::~CRightWnd()
{
}


BEGIN_MESSAGE_MAP(CRightWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// CRightWnd 消息处理程序


void CRightWnd::DrawPriceVol(CDC * c_pDC,CRect c_rect)
{
	if (c_rect.bottom < c_rect.top)
		return;
	int nHeight = c_rect.Height() / 16;

	c_pDC->MoveTo(c_rect.left,c_rect.top + nHeight);
	c_pDC->LineTo(c_rect.right,c_rect.top + nHeight);

	c_pDC->MoveTo(c_rect.left,c_rect.top + nHeight * 6);
	c_pDC->LineTo(c_rect.right,c_rect.top + nHeight * 6);

	c_pDC->MoveTo(c_rect.left,c_rect.top + nHeight * 11);
	c_pDC->LineTo(c_rect.right,c_rect.top + nHeight * 11);

	SStock * pStock = gpData->GetStock(m_strStockCode);	
	if (pStock == NULL)
		return;
	CString strText;
	CRect rl,rr;
	rl = c_rect;
	rl.bottom = rl.top + nHeight;
	rl.right = rl.left + rl.Width()/2;
	rr = rl;
	rr.left = rl.right;
	rr.right = c_rect.right - 2;
	strText = _T("委比");
	c_pDC->SetTextColor(gpSkinManager->getColor(RIGHTTEXTCOLOR));
	c_pDC->DrawText(strText,rl,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	if (pStock->m_sQuote.wb > 0)
		c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
	else
	if (pStock->m_sQuote.wb < 0)		
		c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
	else
		c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
	strText.Format(_T("%.2f%%"),float(pStock->m_sQuote.wb) / 100);
	c_pDC->DrawText(strText,rl,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);

	strText = _T("委差");
	c_pDC->SetTextColor(gpSkinManager->getColor(RIGHTTEXTCOLOR));
	c_pDC->DrawText(strText,rr,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	int nWc;
	nWc = pStock->m_sQuote.BM1 + pStock->m_sQuote.BM2 + pStock->m_sQuote.BM3 + pStock->m_sQuote.BM4 + pStock->m_sQuote.BM5;
	nWc -= pStock->m_sQuote.SM1 + pStock->m_sQuote.SM2 + pStock->m_sQuote.SM3 + pStock->m_sQuote.SM4 + pStock->m_sQuote.SM5;
	if (nWc > 0)
		c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
	else
	if (nWc < 0)		
		c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
	else
		c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
	strText.Format(_T("%d"),nWc/100);
	c_pDC->DrawText(strText,rr,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);


	rl = c_rect;
	rl.top += nHeight;
	rl.bottom = rl.top + nHeight;
	rl.right = rl.left + rl.Width()/2;
	rr = rl;
	rr.left = rl.right;
	rr.right = c_rect.right - 2;
	
	//char acBuf[12][5]={"卖五","卖四","卖三","卖二","卖一","买一","买二","买三","买四","买五"};
	char acBuf[12][5]={"卖⑤","卖④","卖③","卖②","卖①","买①","买②","买③","买④","买⑤"};
	rr.left += 2;
	rl.right -= 2;
	for(int n=0; n<10; n++)
	{
		CString strText;
		strText = toUnicodeString(acBuf[n],strlen(acBuf[n]));
		c_pDC->SetTextColor(gpSkinManager->getColor(RIGHTTEXTCOLOR));
		c_pDC->DrawText(strText,rl,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		int nPrice,nVol;
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
		if (nVol >= 100)
		strText.Format(_T("%d"),nVol/100);
		else
			strText = "";
		c_pDC->DrawText(strText,rr,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);

		rr.top += nHeight;
		rr.bottom += nHeight;
		rl.top += nHeight;
		rl.bottom += nHeight;
	}

	char lBuf[5][5] = {"现价","涨跌","涨幅","总量","外盘"};
	char rBuf[5][5] = {"今开","最高","最低","量比","内盘"};
	for(int n=0; n<5; n++)
	{
		CString strText;
		strText = toUnicodeString(lBuf[n],strlen(lBuf[n]));
		c_pDC->SetTextColor(gpSkinManager->getColor(RIGHTTEXTCOLOR));
		c_pDC->DrawText(strText,rl,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		if (n == 0 || n == 1 || n == 2)
		{
			if (n == 0)
			{
				strText.Format(_T("%.2f"),float(pStock->m_sQuote.zjjg)/1000);
			}
			if (n == 1)
			{
				if (pStock->m_sQuote.zjjg > 0 &&  pStock->m_unPrevClose > 0)
				{
					strText.Format(_T("%.2f"),float(int(pStock->m_sQuote.zjjg) - int(pStock->m_unPrevClose))/1000);
				}
				else
					strText = "0";
			}
			if (n == 2)
			{
				strText.Format(_T("%.2f%%"),float(pStock->m_sQuote.zdfd)/100);
			}
			if (pStock->m_sQuote.zjjg > pStock->m_unPrevClose)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
			else
			if (pStock->m_sQuote.zjjg < pStock->m_unPrevClose)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
			else
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
		}

		if (n == 3)
		{
			//strText.Format("%d",pStock->m_sQuote.cjsl);
			strText = gpData->NumToStr(pStock->m_sQuote.cjsl);
			c_pDC->SetTextColor(gpSkinManager->getColor(VOLCOLOR));
		}
		if (n == 4)
		{
			//strText.Format("%d",pStock->m_sQuote.wp);
			strText = gpData->NumToStr(pStock->m_sQuote.wp);
			c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
		}

		c_pDC->DrawText(strText,rl,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);

		strText = toUnicodeString(rBuf[n],strlen(rBuf[n]));
		c_pDC->SetTextColor(gpSkinManager->getColor(RIGHTTEXTCOLOR));
		c_pDC->DrawText(strText,rr,DT_LEFT|DT_VCENTER|DT_SINGLELINE);

		if (n == 0 || n == 1 || n == 2)
		{
			int nValue;
			if (n == 0)
				nValue = pStock->m_sQuote.jrkp;
			if (n == 1)
				nValue = pStock->m_sQuote.zgjg;
			if (n == 2)
				nValue = pStock->m_sQuote.zdjg;
			strText.Format(_T("%.2f"),float(nValue)/1000);
			if (nValue > pStock->m_unPrevClose)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
			else
			if (nValue < pStock->m_unPrevClose)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
			else
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
		}

		if (n == 3)
		{
			strText.Format(_T("%.2f"),float(pStock->m_sQuote.lb)/10000);
			c_pDC->SetTextColor(gpSkinManager->getColor(VOLCOLOR));
		}
		if (n == 4)
		{
			//strText.Format("%d",pStock->m_sQuote.np);
			strText = gpData->NumToStr(pStock->m_sQuote.np);
			c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
		}

		c_pDC->DrawText(strText,rr,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);

		rr.top += nHeight;
		rr.bottom += nHeight;
		rl.top += nHeight;
		rl.bottom += nHeight;

	}
}

void CRightWnd::DrawIndexInfo(CDC * c_pDC,CRect c_rect)
{
	if (c_rect.bottom < c_rect.top)
		return;
	int nHeight = c_rect.Height() / 10;

	SStock * pStock = gpData->GetStock(m_strStockCode);	
	if (pStock == NULL)
		return;
	CString strText;
	CRect r;
	r = c_rect;
	r.bottom = r.top + nHeight;
	r.right -= 4;
	
	CString strBuf[11]={_T("最新指数"),_T("今日开盘"),_T("昨日收盘"),_T("指数涨跌"),_T("指数涨幅"),_T("指数振幅"),_T("总成交量"),_T("总成交额"),_T("最高指数"),_T("最低指数"),_T("换手")};
	for(int n=0; n<10; n++)
	{
		CString strText;
		strText = strBuf[n];
		c_pDC->SetTextColor(gpSkinManager->getColor(RIGHTTEXTCOLOR));
		c_pDC->DrawText(strText,r,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		int nValue = 0;
		if (n == 0)
		{
			strText.Format(_T("%.2f"),float(pStock->m_sQuote.zjjg) / 1000);
			nValue = pStock->m_sQuote.zjjg;
		}
		if (n == 1){
			strText.Format(_T("%.2f"),float(pStock->m_sQuote.jrkp) / 1000);
			nValue = pStock->m_sQuote.jrkp;
		}
		if (n == 2){
			strText.Format(_T("%.2f"),float(pStock->m_unPrevClose) / 1000);
			nValue = pStock->m_unPrevClose;
		}
		if (n == 3){
			strText.Format(_T("%.2f"),float(pStock->m_sQuote.zd) / 1000);
			nValue = pStock->m_sQuote.zd;
		}
		if (n == 4){
			strText.Format(_T("%.2f%%"),float(pStock->m_sQuote.zdfd) / 100);
			nValue = pStock->m_sQuote.zdfd;
		}
		if (n == 5){
			strText.Format(_T("%.2f%%"),float(pStock->m_sQuote.zf) / 100);
			nValue = pStock->m_sQuote.zf;
		}
		if (n == 6){
			strText.Format(_T("%d"),pStock->m_sQuote.cjsl);
			nValue = pStock->m_sQuote.cjsl;
		}
		if (n == 7){
			strText.Format(_T("%d万"),pStock->m_sQuote.cjje/10);
			nValue = pStock->m_sQuote.cjje;
		}
		if (n == 8){
			strText.Format(_T("%.2f"),float(pStock->m_sQuote.zgjg) / 1000);
			nValue = pStock->m_sQuote.zgjg;
		}
		if (n == 9){
			strText.Format(_T("%.2f"),float(pStock->m_sQuote.zdjg) / 1000);
			nValue = pStock->m_sQuote.zdjg;
		}/*
		if (n == 10){
			strText = "";
			//strText.Format("%.2f",float(pStock->m_sQuote.) / 1000);
			//nValue = pStock->m_sQuote.zjjg;
			nValue = 0;
		}*/

		if (n == 0||n==1||n==2||n==8||n==9)
		{
			if (nValue > pStock->m_unPrevClose)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
			else
			if (nValue < pStock->m_unPrevClose)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
			else
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
		}
		if(n==3||n==4)
		{
			if (nValue > 0)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
			else
			if (nValue < 0)
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
			else
				c_pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
		}
		c_pDC->DrawText(strText,r,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);

		r.top += nHeight;
		r.bottom += nHeight;
	}
}

void CRightWnd::DrawStockInfo(CDC *pDC, CRect c_rect)
{
	if (c_rect.bottom < c_rect.top)
		return;
}

void CRightWnd::DrawTraceData(CDC *pDC, CRect c_rect,bool c_bIndex)
{
	if (c_rect.bottom < c_rect.top)
		return;
	SStock * pStock = gpData->GetStock(m_strStockCode);	
	if (pStock == NULL)
		return;
	if (pStock->m_sQuote.jrkp == 0)//未开盘，不显示分笔 2011/5/16
		return;

	char acFile[32];
	sprintf(acFile,"%s.trc.%d",pStock->m_sQuote.szStockCode,gpData->m_nWorkDay);
	char *pData = (char *)malloc(64 * sizeof(TickUnit));
	if (!pData)
		return;
	int nRead = gpData->GetFromFileTail(acFile,pData,64 * sizeof(TickUnit));
	int nSize = sizeof(TickUnit);
	int nTraceItemCount = nRead / nSize;
	if (nTraceItemCount <= 0)
	{
		free(pData);
		return;
	}
	CSize size;
	size = pDC->GetTextExtent(_T("TEXT"));
	int nTextHeight = size.cy + 2;
	CRect rl,rr;
	rl = c_rect;
	rl.bottom = rl.top + nTextHeight;
	rl.right = rl.left + rl.Width()/2;
	rr = rl;
	rr.left = rl.right;
	rr.right = c_rect.right - 2;
	CRect rm;
	rm = rr;
	rm.right -= 30;
	
	if (c_bIndex)
	{
		rl = c_rect;
		rl.bottom = rl.top + nTextHeight;
		rl.right = rl.left + rl.Width()/3 * 2;
		rr = rl;
		rr.left = rl.right;
		rr.right = c_rect.right - 2;
		CRect rm;
		rm = rr;
		rm.right = c_rect.right - 2;
	}
	int nItem = c_rect.Height() / nTextHeight;
	CString strText;
	int nPrice;
	int nCount;
	int nWay;
	if (nItem > nTraceItemCount)
		nItem = nTraceItemCount;
	COLORREF oldColor;
	oldColor = pDC->SetTextColor(gpSkinManager->getColor(RIGHTTEXTCOLOR));
	TickUnit * pUnit;
	for(int n=0; n<nItem; n++)
	{
		pUnit = (TickUnit *)(pData + (nTraceItemCount - nItem + n) * sizeof(TickUnit));
		nPrice = pUnit->Price;
		nWay = pUnit->Way;
		nCount = pUnit->Volume;
		strText.Format(_T("%.2d:%.2d"),pUnit->Time /60,pUnit->Time %60);
		pDC->SetTextColor(gpSkinManager->getColor(RIGHTTIMECOLOR));
		pDC->DrawText(strText,rl,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		
		if (nPrice > pStock->m_unPrevClose)
			pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
		else
		if (nPrice < pStock->m_unPrevClose)
			pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
		else
			pDC->SetTextColor(gpSkinManager->getColor(PRICENORMAL));
		strText.Format(_T("%.2f"),float(nPrice)/1000);
		pDC->DrawText(strText,rl,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);

		strText.Format(_T("%d"),nCount);
		pDC->SetTextColor(gpSkinManager->getColor(VOLCOLOR));		
		if (c_bIndex)
			pDC->DrawText(strText,rr,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
		else
		pDC->DrawText(strText,rm,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
		if (c_bIndex == false)
		{
			if (nWay == 0)
				strText = "";
			else
			if (nWay == 1)
			{
				strText = "B";
				pDC->SetTextColor(gpSkinManager->getColor(PRICEUP));
			}
			else
			{
				strText = "S";
				pDC->SetTextColor(gpSkinManager->getColor(PRICEDOWN));
			}
			pDC->DrawText(strText,rr,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
		}
		rl.top += nTextHeight;
		rl.bottom += nTextHeight;
		rr.top += nTextHeight;
		rr.bottom += nTextHeight;
		rm.top += nTextHeight;
		rm.bottom += nTextHeight;
	}
	pDC->SetTextColor(oldColor);
	free(pData);
}

void CRightWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()

	CRect rect;
	GetClientRect(rect);
	
	CDC SourceDC;
	CBitmap bitmap,*pOldBitmap;
	bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());

	SourceDC.CreateCompatibleDC(NULL);//生成兼容的CDC
	pOldBitmap = SourceDC.SelectObject(&bitmap);

	PaintSelf(SourceDC);
	
	dc.BitBlt(0,0,rect.Width(),rect.Height(),&SourceDC,0,0,SRCCOPY);	
	SourceDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	SourceDC.DeleteDC();	
}
void CRightWnd::PaintSelf(CDC &dc)
{
	int nFoot = gpSkinManager->GetFontHeight(gpSkinManager->GetGraphFont()) + 2;
	if (nFoot < 18)
		nFoot = 18;

	LOGFONT LogFont;
	memset(&LogFont,0,sizeof(LogFont));
	LogFont.lfHeight = gpSkinManager->m_nGraphFontSize;// + 2;//-10
	LogFont.lfCharSet = DEFAULT_CHARSET;
	LogFont.lfWeight = FW_NORMAL;//FW_MEDIUM;
	lstrcpy(LogFont.lfFaceName,gpSkinManager->GetDefaultFontName());
	//lstrcpy(LogFont.lfFaceName,_T("System"));
	CFont * pTextFont = new CFont();
	pTextFont->CreateFontIndirect(&LogFont);
	CFont *pOldFont = dc.SelectObject(pTextFont);

	int nTextHeight;
	CSize size = dc.GetTextExtent(_T("TEST"));
	nTextHeight = size.cy;

	CBrush brush(gpSkinManager->getColor(BKCOLOR));
	
	CRect rect;
	GetClientRect(rect);
	dc.FillRect(rect,&brush);
	dc.SelectObject(&brush);
	
	CPen pen(PS_SOLID,1,gpSkinManager->getColor(AIXLINE));
	CPen *pOldPen;
	CRect rectPriceVol,rectStockInfo,rectTraceData;
	GetClientRect(rect);
	pOldPen = dc.SelectObject(&pen);
	rect.top += 2;
	rect.left += 2;
	rect.right -= 2;
	rect.bottom -= nFoot;
	dc.Rectangle(rect);
	//dc.Rectangle(CRect(rect.left,rect.bottom+2,rect.right,rect.bottom+20));
	dc.Rectangle(CRect(rect.left,rect.bottom,rect.right,rect.bottom+nFoot));
	dc.SetBkMode(TRANSPARENT);
	
	rect.bottom = rect.top + nTextHeight + 4;
	SStock * pStock = gpData->GetStock(m_strStockCode);	
	if (pStock == NULL)
	{
		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldFont);
		pTextFont->DeleteObject();
		delete pTextFont;
		return;
	}
	bool bIndex = false;

	rect.left += 2;
	CString strText;
	dc.SetTextColor(gpSkinManager->getColor(RIGHTSTOCKCODECOLOR));
	strText = pStock->m_sQuote.szStockCode;
	strText = strText.Left(6);
	dc.DrawText(strText,rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	size = dc.GetTextExtent(strText);
	rect.left += size.cx + 4;
	dc.SetTextColor(gpSkinManager->getColor(RIGHTSTOCKNAMECOLOR));
	dc.DrawText(pStock->m_strName,pStock->m_strName.GetLength(),rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);

	GetClientRect(rect);
	rect.top += 2;
	rect.left += 2;
	rect.right -= 2;
	rect.bottom -= nFoot;//24
	if (bIndex)
	{
		rectPriceVol = rect;
		rectPriceVol.top += nTextHeight + 4;
		rectPriceVol.bottom = rectPriceVol.top + 10 * (nTextHeight + 4);
	}
	else
	{
		rectPriceVol = rect;
		rectPriceVol.top += nTextHeight + 4;
		rectPriceVol.bottom = rectPriceVol.top + 16 * (nTextHeight + 4);
	}
	rectStockInfo = rect;
	rectStockInfo.top = rectPriceVol.bottom;	
	rectStockInfo.bottom = rectStockInfo.top;// + 3 * (nTextHeight + 3);
	rectTraceData = rect;
	rectTraceData.top = rectStockInfo.bottom;
	//rectTraceData.bottom -= 4;
	if (rectPriceVol.bottom > rectPriceVol.top  && rectPriceVol.bottom < rect.bottom)
		dc.Rectangle(rectPriceVol);
	if (rectStockInfo.bottom > rectStockInfo.top  && rectStockInfo.bottom < rect.bottom)
		dc.Rectangle(rectStockInfo);
	if (rectTraceData.bottom > rectTraceData.top && rectTraceData.bottom < rect.bottom)
		dc.Rectangle(rectTraceData);

	if (bIndex)
		DrawIndexInfo(&dc,rectPriceVol);
	else
	DrawPriceVol(&dc,rectPriceVol);
	//DrawStockInfo(&dc,rectStockInfo);
	m_rectTraceData = rectTraceData;
	DrawTraceData(&dc,rectTraceData,bIndex);

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldFont);
	pTextFont->DeleteObject();
	delete pTextFont;
}

void CRightWnd::SetStockCode(CString c_strCode)
{
	m_strStockCode = c_strCode;
	Invalidate();
}
void CRightWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if (m_rectTraceData.PtInRect(point))
	//	::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,SHOW_TRACEWND,0);
	CWnd::OnLButtonDblClk(nFlags, point);
}

int CRightWnd::GetWidth()
{
	LOGFONT LogFont;
	memset(&LogFont,0,sizeof(LogFont));
	LogFont.lfHeight = gpSkinManager->m_nGraphFontSize;// + 2;//-10;
	LogFont.lfCharSet = DEFAULT_CHARSET;
	LogFont.lfWeight = FW_NORMAL;//FW_MEDIUM;
	lstrcpy(LogFont.lfFaceName,gpSkinManager->GetDefaultFontName());
	//lstrcpy(LogFont.lfFaceName,_T("System"));
	CFont * pTextFont = new CFont();
	pTextFont->CreateFontIndirect(&LogFont);

	int nRet = gpSkinManager->GetFontWidth(pTextFont,_T("123456.")) * 3;
	delete pTextFont;
	return nRet>186?nRet:186;	
}