// TraceWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "FinSmith.h"
#include "TraceWnd.h"


// CTraceWnd

IMPLEMENT_DYNAMIC(CTraceWnd, CWnd)

CTraceWnd::CTraceWnd(unsigned int nDetailStyle)
{
	m_pTick = (TickUnit *)malloc(sizeof(TickUnit) * 60 * 4 * 24);
	m_nMaxTick = 60 * 4 * 24;
	m_nValidTick = 0;

	m_nDetailStyle = nDetailStyle;
	if (EACH_BARGAIN == m_nDetailStyle)
	{
		m_nMinColumnWidth = 200;	
		m_cstrPageTitle += _T("   交易明细     Up/PageUp:上翻  Down/PageDown:下翻");
		m_cstrColumnTitle = _T("时间       价格    成交量  方向\r\n");
	}
	else if (EACH_PRICE == m_nDetailStyle)
	{
		m_nMinColumnWidth = 240;
		m_cstrPageTitle += _T("   分价表     Up/PageUp:上翻  Down/PageDown:下翻");
		m_cstrColumnTitle = _T("价格    成交量    比例          竞买率%\r\n");
		m_mapPriceStatistic.clear();
		m_vMapKey.clear();
		m_nMapKeyVecSize = 0;
		m_nMaxVolumeCount = 0;
	}
	m_cstrTmpString = _T("");
	//m_cstrFlipNotice = _T("");
	//m_nStandardWidth = (nHor-80)/m_nMaxColumnCount;

	m_eKeyMessage = NONE;
	m_bFilledFirstPage = false;
	m_nPageNum = 1;
	m_nPageCount = 1;	
	m_iBeginPosIndex = 0;
	m_nRectItemCount = 0;	

}

CTraceWnd::~CTraceWnd()
{
}


BEGIN_MESSAGE_MAP(CTraceWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CTraceWnd 消息处理程序



void CTraceWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	m_eViewMode = DLG_SHOW;
	CRect dlgRect;
	GetClientRect(dlgRect);//取得窗口大小（不包括标题栏）
	int nDlgHeight = dlgRect.Height();
	int nDlgWidth = dlgRect.Width();
	if (0 == nDlgWidth)//这是因为宽度为0时，列数为0，会引起除0错误
	{
		return;
	}
	CDC cmemDC;
	cmemDC.CreateCompatibleDC(NULL);
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(&dc,nDlgWidth,nDlgHeight);//创建位图对象
	cmemDC.SelectObject(memBitmap);
	CFont * pOldFont = cmemDC.SelectObject(gpSkinManager->m_pFontReport);
	cmemDC.SetBkMode(TRANSPARENT);//设置背景为透明模式
	cmemDC.FillSolidRect(dlgRect,RGB(255,255,255));//填充位图的背景色
	/*画横线*/
	cmemDC.MoveTo(dlgRect.left,dlgRect.top+29);		
	cmemDC.LineTo(dlgRect.right,dlgRect.top+29);
	cmemDC.MoveTo(dlgRect.left,dlgRect.top+54);		
	cmemDC.LineTo(dlgRect.right,dlgRect.top+54);
	/*画竖线*/
	
	SColumnInfo sColumnInfo;
	sColumnInfo.nColumnCount = nDlgWidth/m_nMinColumnWidth;
	sColumnInfo.nColumnWidth = nDlgWidth/sColumnInfo.nColumnCount;
	sColumnInfo.nRectItemCountOFColumn = (nDlgHeight-54)/HEIGHT_OF_EACH_RECTITEM;
	for(unsigned int j=1 ; j<sColumnInfo.nColumnCount ; j++)
	{
		cmemDC.MoveTo(dlgRect.left+j*sColumnInfo.nColumnWidth,dlgRect.top+29);		
		cmemDC.LineTo(dlgRect.left+j*sColumnInfo.nColumnWidth,dlgRect.bottom);
	}
	/*数据填充*/
	cmemDC.SetTextAlign(TA_LEFT|TA_TOP);//文本以单元格左上顶点为对齐基点
	cmemDC.TextOut(dlgRect.left+10,dlgRect.top+8,m_cstrPageTitle,m_cstrPageTitle.GetLength());//文本输出	
	if (m_nValidTick)
	{
		m_nRectItemCount = sColumnInfo.nRectItemCountOFColumn * sColumnInfo.nColumnCount;	
		if(EACH_BARGAIN == m_nDetailStyle)
		{
			CalcuDataBeginPosIndex(m_nValidTick);
			PaintBargainBillData(cmemDC,dlgRect,sColumnInfo);
		}
		else if (EACH_PRICE == m_nDetailStyle)
		{
			CalcuDataBeginPosIndex(m_nMapKeyVecSize);
			PaintPriceStatisticData(cmemDC,dlgRect,sColumnInfo);
		}
	}

	dc.BitBlt(0,0,nDlgWidth,nDlgHeight,&cmemDC,0,0,SRCCOPY);//将画好的位图显示在窗口中
	cmemDC.SelectObject(pOldFont);
	memBitmap.DeleteObject();
	cmemDC.DeleteDC();
	UpdateWindow();
}

void CTraceWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	::PostMessage(gpData->m_hwndMain,WM_GOTO_STOCK,ESCAPE_TRACEWND,0);
	CWnd::OnLButtonDblClk(nFlags, point);
}

BOOL CTraceWnd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_UP || pMsg->wParam == VK_PRIOR))
	{
		m_eKeyMessage = KEYUP;
		Invalidate(FALSE);
	}
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_DOWN || pMsg->wParam == VK_NEXT))
	{
		m_eKeyMessage = KEYDOWN;
		Invalidate(FALSE);
	}
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
	{
		return TRUE;
	}
	
	return CWnd::PreTranslateMessage(pMsg);
}


void CTraceWnd::CalcuDataBeginPosIndex(const unsigned int& nDataCount)
{
	if (m_nRectItemCount > nDataCount)//交易数据量一页能够显示完毕
	{	
		m_iBeginPosIndex = 0;
		m_iEndPosIndex = nDataCount;
		m_nPageCount = m_nPageNum = 1;
		m_eKeyMessage = NONE;
		m_bFilledFirstPage = false;
		KillTimer(2);//新增
		SetTimer(1,100,NULL);
	}
	else//多页显示
	{
		switch(m_eKeyMessage)
		{
		case NONE://静态、放大、缩小
			if(1 == m_nPageNum)//首页
			{	
				if (m_bFilledFirstPage)//首页数据满页
				{
					m_nPageCount = nDataCount/m_nRectItemCount + (bool)(nDataCount%m_nRectItemCount);
					m_nPageNum = 1;
					m_iBeginPosIndex = nDataCount - m_nRectItemCount;
					m_iEndPosIndex = nDataCount;				
				}
				else//首页数据未满
				{
					m_nPageCount = nDataCount/m_nRectItemCount + (bool)(nDataCount%m_nRectItemCount);
					m_iBeginPosIndex = m_nRectItemCount*(m_nPageCount - m_nPageNum);
					m_iEndPosIndex = nDataCount;
					m_bFilledFirstPage = (m_nRectItemCount == (m_iEndPosIndex - m_iBeginPosIndex));
				}				
			}
			else if (m_nPageNum <= m_nPageCount)
			{
				if (m_nPageNum == m_nPageCount)//末页
				{
					m_nPageCount = nDataCount/m_nRectItemCount + (bool)(nDataCount%m_nRectItemCount);
					m_nPageNum = m_nPageCount;
					m_iBeginPosIndex = 0;
					m_iEndPosIndex = m_nRectItemCount;
				}
				else//其他页面
				{
					m_nPageNum = (nDataCount-m_iEndPosIndex)/m_nRectItemCount + 
						(bool)((nDataCount-m_iEndPosIndex)%m_nRectItemCount)+ 1;
					m_nPageCount = m_iEndPosIndex/m_nRectItemCount + 
						(bool)(m_iEndPosIndex%m_nRectItemCount) + m_nPageNum -1;
					if (m_iEndPosIndex > m_nRectItemCount)
					{
						m_iBeginPosIndex = m_iEndPosIndex - m_nRectItemCount;
					}
					else//当页面停留在倒数第二页时，瞬间放大页面，使得倒数前两页的数据尚且不能填满页面，m_iBeginPosIndex会变为负数。
					{
						m_iBeginPosIndex = 0;
						m_iEndPosIndex = m_nRectItemCount;
					}			
				}				
			}
			break;

		case KEYUP://上翻
			KillTimer(1);//翻页时停止新数据插入
			KillTimer(2);//新增
			//m_cstrFlipNotice = _T("");
			if (1 == m_nPageNum && 2 != m_nPageCount)
			{
				m_iEndPosIndex = m_iBeginPosIndex;
				m_iBeginPosIndex = m_iBeginPosIndex - m_nRectItemCount;
				m_nPageNum += 1;
			}
			else if (m_nPageNum <m_nPageCount - 1)
			{
				m_iEndPosIndex = m_iEndPosIndex - m_nRectItemCount;
				m_iBeginPosIndex = m_iEndPosIndex - m_nRectItemCount;
				m_nPageNum += 1;
			}
			else if (m_nPageNum == m_nPageCount - 1)
			{
				m_iBeginPosIndex = 0;
				m_iEndPosIndex = m_nRectItemCount;
				m_nPageCount = nDataCount/m_nRectItemCount + (bool)(nDataCount%m_nRectItemCount);
				m_nPageNum = m_nPageCount;
			}
			else
			{
				//m_cstrFlipNotice = _T("当前是首页");
				AfxMessageBox(_T("当前是首页"));
			}
			m_eKeyMessage = NONE;
			SetTimer(2,500,NULL);//新增
			break;

		case KEYDOWN://下翻
			KillTimer(1);//翻页时停止新数据插入
			KillTimer(2);//新增
			//m_cstrFlipNotice = _T("");
			if (m_nPageCount == m_nPageNum && 2 != m_nPageCount)
			{
				m_iBeginPosIndex = m_nRectItemCount;
				m_iEndPosIndex = m_iBeginPosIndex + m_nRectItemCount;
				m_nPageNum -= 1;
				SetTimer(2,500,NULL);//新增
			}
			else if (m_nPageNum > 2)
			{
				m_iBeginPosIndex = m_iEndPosIndex;
				m_iEndPosIndex = m_iBeginPosIndex + m_nRectItemCount;		
				m_nPageNum -= 1;
				SetTimer(2,500,NULL);//新增
			}
			else if (2 == m_nPageNum)
			{
			
				m_iBeginPosIndex = nDataCount - m_nRectItemCount;
				m_iEndPosIndex = nDataCount;
				m_nPageCount = nDataCount/m_nRectItemCount + (bool)(nDataCount%m_nRectItemCount);
				m_nPageNum = 1;
				m_bFilledFirstPage = true;
				SetTimer(1,100,NULL);
			}
			else
			{
				//m_cstrFlipNotice = _T("当前是末页");		
				AfxMessageBox(_T("当前是末页"));
				m_bFilledFirstPage = (m_nRectItemCount == (m_iEndPosIndex - m_iBeginPosIndex));
				SetTimer(1,100,NULL);
			}
			m_eKeyMessage = NONE;
			break;

		default:
			break;
		}
	}
}

void CTraceWnd::PaintBargainBillData(CDC& rCDC ,const CRect& rRect,const SColumnInfo& rColumnInfo)
{	
	m_cstrTmpString.Format(_T("页%d/%d  总交易量%d  单页显示量%d"),m_nPageCount-m_nPageNum+1,m_nPageCount,m_nValidTick,m_nRectItemCount);
	rCDC.TextOut(rRect.right-260,rRect.top+8,m_cstrTmpString,m_cstrTmpString.GetLength());

	unsigned int tempIndex = m_iBeginPosIndex;
	int nRectItemLeft;//单元格文本显示左边界
	int nRectItemTop;//单元格文本显示上边界

	/*对列进行数据填充，包括列标题和交易数据*/
	for (unsigned int i=0 ; i<rColumnInfo.nColumnCount && tempIndex<m_nValidTick; i++)
	{
		rCDC.SetTextColor(RGB(0,0,0));//黑色
		nRectItemLeft = rRect.left + 5 + rColumnInfo.nColumnWidth * i;//5为文本偏移量，是文本左界与单元格左界的距离
		rCDC.TextOut(nRectItemLeft,(rRect.top+29+3),m_cstrColumnTitle,m_cstrColumnTitle.GetLength()-2);
		for (unsigned int j=0 ; j<rColumnInfo.nRectItemCountOFColumn && tempIndex<m_nValidTick ; j++)
		{
			nRectItemTop = rRect.top + 54 + 3 + HEIGHT_OF_EACH_RECTITEM * j;//3为文本偏移量，54为数据单元格与对话框上界的基本距离
			/*时间*/
			if (m_pTick[tempIndex].Time%60 < 10)
			{
				m_cstrTmpString.Format(_T("%u:0%u"),m_pTick[tempIndex].Time/60,m_pTick[tempIndex].Time%60);
			}
			else
			{
				m_cstrTmpString.Format(_T("%u:%u"),m_pTick[tempIndex].Time/60,m_pTick[tempIndex].Time%60);
			}
			rCDC.SetTextColor(RGB(0,0,0));
			rCDC.TextOut(nRectItemLeft,nRectItemTop,m_cstrTmpString,m_cstrTmpString.GetLength());

			m_cstrTmpString.Format(_T("%u"),tempIndex+1);
			//rCDC.TextOut(nRectItemLeft+160,nRectItemTop,m_cstrTmpString,m_cstrTmpString.GetLength());
			/*成交量*/
			rCDC.SetTextAlign(TA_RIGHT|TA_TOP);//文本以单元格右上顶点为对齐基点
			m_cstrTmpString.Format(_T("%u"),m_pTick[tempIndex].Volume);
			if (m_pTick[tempIndex].Volume >= 500)
			{
				rCDC.SetTextColor(RGB(255,0,255));//粉色
			}
			rCDC.TextOut(nRectItemLeft+140,nRectItemTop,m_cstrTmpString,m_cstrTmpString.GetLength());
			rCDC.SetTextAlign(TA_LEFT|TA_TOP);
			/*价格*/
			m_cstrTmpString.Format(_T("%.2f"),m_pTick[tempIndex].Price/1000.00);
			if (m_pTick[tempIndex].Price > m_nYesterdayClosingPrice)
			{
				rCDC.SetTextColor(RGB(255,0,0));//红色
			}
			else if (m_pTick[tempIndex].Price == m_nYesterdayClosingPrice)
			{
				rCDC.SetTextColor(RGB(0,0,0));//黑色
			}
			else
			{
				rCDC.SetTextColor(RGB(0,0,255));//蓝色
			}
			rCDC.TextOut(nRectItemLeft+55,nRectItemTop,m_cstrTmpString,m_cstrTmpString.GetLength());
			/*方向*/
			
			if (0 == m_pTick[tempIndex].Way)
			{
				m_cstrTmpString = _T("");
			}
			else if(1 == m_pTick[tempIndex].Way)
			{
				m_cstrTmpString = _T("B");
				rCDC.SetTextColor(RGB(255,0,0));//红色
			}
			else
			{
				m_cstrTmpString = _T("S");
				rCDC.SetTextColor(RGB(0,0,255));//蓝色
			}
			rCDC.TextOut(nRectItemLeft+145,nRectItemTop,m_cstrTmpString,m_cstrTmpString.GetLength());
			tempIndex++;
		}
	}
}

void CTraceWnd::PaintPriceStatisticData(CDC& rCDC ,const CRect& rRect,const SColumnInfo& rColumnInfo)
{
	//unsigned int m_nRectItemCount = rColumnInfo.nRectItemCountOFColumn * rColumnInfo.nColumnCount;//每页的单元格数目，即单页显示量
	//this->CalcuDataBeginPosIndex(m_nRectItemCount,m_nMapKeyVecSize);
	//rCDC.SetTextColor(RGB(255,0,0));//设置文本颜色为红色
	//rCDC.TextOut(rRect.left+420,rRect.top+8,m_cstrFlipNotice,m_cstrFlipNotice.GetLength());
	m_cstrTmpString.Format(_T("页%d/%d  价位数目%d"),m_nPageCount-m_nPageNum+1,m_nPageCount,m_nMapKeyVecSize/*,m_nRectItemCount*/);
	rCDC.TextOut(rRect.right-130,rRect.top+8,m_cstrTmpString,m_cstrTmpString.GetLength());

	unsigned int tempIndex = m_iBeginPosIndex;
	int nRectItemLeft;
	int nRectItemTop;
	COLORREF colFillColor = RGB(255,255,255);
	/*对列进行数据填充，包括列标题和交易数据*/
	for (unsigned int i=0 ; i<rColumnInfo.nColumnCount && tempIndex<m_nMapKeyVecSize; i++)
	{
		rCDC.SetTextColor(RGB(0,0,0));//黑色
		nRectItemLeft = rRect.left + 5 + rColumnInfo.nColumnWidth * i;//5为文本偏移量，是文本左界与单元格左界的距离
		rCDC.TextOut(nRectItemLeft,(rRect.top+29+3),m_cstrColumnTitle,m_cstrColumnTitle.GetLength()-2);
		for (unsigned int j=0 ; j<rColumnInfo.nRectItemCountOFColumn && tempIndex<m_nMapKeyVecSize ; j++)
		{
			nRectItemTop = rRect.top + 54 + 3 + HEIGHT_OF_EACH_RECTITEM * j;//3为文本偏移量，54为数据单元格与对话框上界的基本距离
			/*价格*/
			m_cstrTmpString.Format(_T("%.2f"),m_vMapKey[tempIndex]/1000.00);
			if (m_vMapKey[tempIndex] > m_nYesterdayClosingPrice)
			{
				colFillColor = RGB(255,0,0);//红色
			}
			else if (m_vMapKey[tempIndex] == m_nYesterdayClosingPrice)
			{
				colFillColor = RGB(0,0,0);//黑色
			}
			else
			{
				colFillColor = RGB(0,0,255);//蓝色
			}
			rCDC.SetTextColor(colFillColor);
			rCDC.TextOut(nRectItemLeft,nRectItemTop,m_cstrTmpString,m_cstrTmpString.GetLength());

			/*成交量*/
			rCDC.SetTextAlign(TA_RIGHT|TA_TOP);//文本以单元格右上顶点为对齐基点
			rCDC.SetTextColor(RGB(0,0,0));//黑色
			m_cstrTmpString.Format(_T("%u"),m_mapPriceStatistic[m_vMapKey[tempIndex]].nVolumeCount);
			rCDC.TextOut(nRectItemLeft+85,nRectItemTop,m_cstrTmpString,m_cstrTmpString.GetLength());

			/*竞买率*/
			double dBuyingRate = m_mapPriceStatistic[m_vMapKey[tempIndex]].nBuyVolumeCount*100.0/m_mapPriceStatistic[m_vMapKey[tempIndex]].nVolumeCount;
			m_cstrTmpString.Format(_T("%.2f"),dBuyingRate);
			rCDC.TextOut(nRectItemLeft+235,nRectItemTop,m_cstrTmpString,m_cstrTmpString.GetLength());
			rCDC.SetTextAlign(TA_LEFT|TA_TOP);

			/*比例*/
			int nProportion;
			nProportion = m_mapPriceStatistic[m_vMapKey[tempIndex]].nVolumeCount*100.0/m_nMaxVolumeCount;
			if (m_mapPriceStatistic[m_vMapKey[tempIndex]].nVolumeCount*100%m_nMaxVolumeCount > m_nMaxVolumeCount/2
				|| 0 == nProportion)
			{
				nProportion += 1;
			}
			nRectItemTop = nRectItemTop - 3 + 5;
			if (RGB(0,0,255) == colFillColor)
			{
				colFillColor = RGB(0,255,0);//价格颜色为蓝时，条形柱为绿色
			}
			CRect rect(nRectItemLeft+90,nRectItemTop,nRectItemLeft+90+nProportion,nRectItemTop+10);//条形柱范围
			rCDC.FillSolidRect(rect,colFillColor);
	
			tempIndex++;
		}
	}

}

void CTraceWnd::FreshData()
{
	SStock * pStock = gpData->GetStock(m_strStockCode);	
	if (pStock == NULL)
		return;
	if (pStock->m_sQuote.jrkp == 0)//未开盘，不显示分笔 2011/5/16
		return;
	m_nYesterdayClosingPrice = pStock->m_sQuote.zrsp;
	char acFile[32];
	sprintf(acFile,"data/%s.trc.%d",pStock->m_sQuote.szStockCode,gpData->m_nWorkDay);
	FILE *f;
	f = fopen(acFile,"rb");
	if (f)
	{
		fseek(f,0,SEEK_END);
		int nLen = ftell(f);
		if (nLen / sizeof(TickUnit) == m_nValidTick)
		{
			fclose(f);
			return;
		}
		fseek(f,0,SEEK_SET);
		if (nLen / sizeof(TickUnit) > m_nMaxTick)
		{
			fclose(f);
			return;
		}
		fread(m_pTick,sizeof(TickUnit),nLen / sizeof(TickUnit),f);
		m_nValidTick = nLen / sizeof(TickUnit);
		fclose(f);
		Invalidate();
	}
}

void CTraceWnd::SetStockCode(CString c_strCode)
{
	m_strStockCode = c_strCode;
	FreshData();
}
void CTraceWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetFocus();
	CWnd::OnLButtonDown(nFlags, point);
}
