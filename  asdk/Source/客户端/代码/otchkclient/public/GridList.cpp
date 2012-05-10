// GridList.cpp : 实现文件
//

#include "stdafx.h"
#include "GridList.h"
#include <assert.h>

// SCellItem



//SCellItemArray
SCellItemArray::SCellItemArray()
{
	this->Clear();
}

SCellItemArray::SCellItemArray(const std::vector<CString>& vecText)
{
	m_vecArrayData.clear();
	m_nArraySize = 0;
	ARRAY_CELL_ITEM::size_type nSize = vecText.size();	 
	SCellItem sItem;
	for(unsigned int i = 0 ; i < nSize ; i++)
	{
		sItem.cstrText = vecText[i];
		m_vecArrayData.push_back(sItem);
		m_nArraySize++;
	}
}

SCellItemArray::SCellItemArray(const std::map<int,CString> &mapText)
{
	m_vecArrayData.clear();
	m_nArraySize = 0;
	map<int,CString>::const_iterator it = mapText.begin();
	while (mapText.end() != it)
	{
		int nColumnID = it->first;
		SCellItem sItem(it->second);
		this->InsertItem(nColumnID,sItem);
		it++;
	}
}

SCellItemArray::SCellItemArray(const std::ARRAY_CELL_ITEM& vecItem)
{
	m_vecArrayData.clear();	
	m_vecArrayData = vecItem;
	m_nArraySize = vecItem.size();
}

SCellItemArray::SCellItemArray(const SCellItemArray& other)
{
	m_vecArrayData.clear();
	m_vecArrayData = other.GetArrayData();
	m_nArraySize = m_vecArrayData.size();
}

SCellItemArray SCellItemArray::operator =(const SCellItemArray& other)
{
	if (this == &other)
	{
		return *this;
	}
	m_vecArrayData.clear();
	m_vecArrayData = other.GetArrayData();
	m_nArraySize = m_vecArrayData.size();
	return *this;
}

void SCellItemArray::Assign(ITERATOR_ARRAY_VEC beginIt,ITERATOR_ARRAY_VEC endIt)
{
	m_vecArrayData.clear();
	m_vecArrayData.assign(beginIt,endIt);
	m_nArraySize = m_vecArrayData.size();
}

void SCellItemArray::InsertItem(unsigned int nRowOrColumn_ID,const SCellItem& sItem)
{
	if (nRowOrColumn_ID < 0)
	{
		return;
	}
	if (m_nArraySize && nRowOrColumn_ID < m_nArraySize)
	{
		m_vecArrayData.insert(m_vecArrayData.begin()+nRowOrColumn_ID,sItem);
		m_nArraySize++;
	}
	else
	{
		SCellItem tmpItem;
		for (unsigned int i = m_nArraySize ; i < nRowOrColumn_ID ; i++)
		{
			m_vecArrayData.push_back(tmpItem);
			m_nArraySize++;
		}
		m_vecArrayData.push_back(sItem);
		m_nArraySize++;
	}
}

void SCellItemArray::Insert(unsigned int nRowOrColumn_ID,const SCellItem& sItem)
{
	this->InsertItem(nRowOrColumn_ID,sItem);
}

void SCellItemArray::Insert(unsigned int nRowOrColumn_ID, const CString &cstrText, COLORREF colTextColor, COLORREF colBkColor)
{
	SCellItem sItem(cstrText,colTextColor,colBkColor);
	this->InsertItem(nRowOrColumn_ID,sItem);
}

SCellItem& SCellItemArray::operator [](unsigned int nID) const
{
	assert(nID >=0 && nID < m_nArraySize);	
	return m_vecArrayData[nID];	
}

SCellItem& SCellItemArray::At(unsigned int nID) const
{
	assert(nID >=0 && nID < m_nArraySize);
	return m_vecArrayData[nID];	
}

ITERATOR_ARRAY_VEC& SCellItemArray::Find(unsigned int nRowOrColumn_ID) const
{
	if (nRowOrColumn_ID >= 0 && nRowOrColumn_ID < m_nArraySize)
	{
		m_arrayIt = m_vecArrayData.begin()+nRowOrColumn_ID;
	}
	else
	{
		m_arrayIt = m_vecArrayData.end();
	}
	return m_arrayIt;
}

ITERATOR_ARRAY_VEC& SCellItemArray::Begin() const
{
	m_arrayIt = m_vecArrayData.begin(); 
	return m_arrayIt;
}

ITERATOR_ARRAY_VEC& SCellItemArray::End() const
{
	m_arrayIt = m_vecArrayData.end(); 
	return m_arrayIt;
}

ITERATOR_ARRAY_VEC& SCellItemArray::Erase(unsigned int nRowOrColumn_ID)
{
	assert(nRowOrColumn_ID >= 0 && nRowOrColumn_ID < m_nArraySize);
	m_nArraySize--;
	m_arrayIt = m_vecArrayData.begin()+nRowOrColumn_ID;
	m_arrayIt = m_vecArrayData.erase(m_arrayIt);
	return m_arrayIt;
}

ITERATOR_ARRAY_VEC& SCellItemArray::Erase(ITERATOR_ARRAY_VEC iBegIt, ITERATOR_ARRAY_VEC iEndIt)
{
	assert(m_vecArrayData.end() != iBegIt);
	m_arrayIt = m_vecArrayData.erase(iBegIt,iEndIt);
	m_nArraySize = m_vecArrayData.size();
	return m_arrayIt;
}

BOOL SCellItemArray::Empty() const
{
	return m_vecArrayData.empty();
}

int SCellItemArray::Size() const
{
	return m_nArraySize;
}

void SCellItemArray::Clear()
{
	m_vecArrayData.clear();
	m_nArraySize = 0;
}

void SCellItemArray::SetArrayData(const ARRAY_CELL_ITEM& vecData)
{
	m_vecArrayData.clear();
	m_vecArrayData = vecData;
	m_nArraySize = vecData.size();
}

ARRAY_CELL_ITEM& SCellItemArray::GetArrayData() const
{
	return m_vecArrayData;
}

// CGridList

IMPLEMENT_DYNAMIC(CGridList, CWnd)

CGridList::CGridList()
{	
	RegisterWndClass();
	m_pHorScrollBar = m_pVerScrollBar = NULL;
	m_pParentCWnd = NULL;
	m_pFontSystemDefault = NULL;
	m_pFontHeadItem = m_pFontDataItem = NULL;
	
	this->Initial();
}

CGridList::~CGridList()
{
	this->Release();
}


BEGIN_MESSAGE_MAP(CGridList, CWnd)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CGridList 消息处理程序

BOOL CGridList::RegisterWndClass()
{
	WNDCLASS windowclass;
	HINSTANCE hInst = AfxGetInstanceHandle();

	//Check weather the class is registerd already
	if (!(::GetClassInfo(hInst, GRIDLISTCONTROL, &windowclass)))
	{
		//If not then we have to register the new class
		windowclass.style = CS_DBLCLKS;// | CS_HREDRAW | CS_VREDRAW;
		windowclass.lpfnWndProc = ::DefWindowProc;
		windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
		windowclass.hInstance = hInst;
		windowclass.hIcon = NULL;
		windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
		windowclass.lpszMenuName = NULL;
		windowclass.lpszClassName = GRIDLISTCONTROL;

		if (!AfxRegisterClass(&windowclass))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}
	return TRUE;
}

void CGridList::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	if (cx + m_nHorOffSet > m_nSumColumnWidth + m_nVerScrollBarWidth + 1)
	{
		if (m_nSumColumnWidth + m_nVerScrollBarWidth + 1 > cx)
		{
			m_nHorOffSet = m_nSumColumnWidth + m_nVerScrollBarWidth + 1 - cx;
		}
		else
		{
			m_nHorOffSet = 0;
		}
	}
	if (cy + m_nVerOffSet > m_nSumRowHeight + m_nVerScrollBarWidth + 1)
	{
		int sum;
		int i = m_nShowedBeginRowID;
		for( ; i >= m_nFixedRowCount ; i--)
		{
			sum = this->SumRowsHeigth(i,m_nShowedBeginRowID);
			if (cy + m_nVerOffSet - m_nSumRowHeight - m_nVerScrollBarWidth - 1 < sum)
			{
				break;
			}
		}
		if (m_nFixedRowCount - 1 == i)
		{
			m_nVerOffSet = 0;
		}
		else
		{
			m_nVerOffSet = m_nVerOffSet - sum + m_vRowsHeight[i];
		}
		m_nShowedBeginRowID = i + 1;		
	}

	while(FALSE == this->CreateScrollBar(cx,cy));
	Invalidate(FALSE);
}

void CGridList::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	if (m_vRowsHeight.empty() && m_vColumnsWidth.empty())
	{
		return;
	}
	m_mapItemRect.clear();
	m_vecVertLineInfo.clear();
	m_vecGridLine.clear();
	SVertLineInfo sVertLine;
		
	GetClientRect(m_rcCustomRect);
	int rectWidth = m_rcCustomRect.Width();
	int rectHeigth = m_rcCustomRect.Height();
	int nFixColumnsWidth = SumColumnsWidth(0,m_nFixedColumnCount);
	
	this->SetScrollBar(rectWidth,rectHeigth);
	if (0 == m_nVerScrollBarWidth)
	{
		m_nVerOffSet = 0;
		m_nShowedBeginRowID = m_nFixedRowCount;
	}

	CDC cMemoryDc;
	cMemoryDc.CreateCompatibleDC(NULL);
	CBitmap bmGridMap;
	bmGridMap.CreateCompatibleBitmap(&dc,rectWidth-m_nVerScrollBarWidth,rectHeigth-m_nHorScrollBarWidth);
	cMemoryDc.SelectObject(bmGridMap);
	cMemoryDc.SetBkMode(TRANSPARENT);
	cMemoryDc.FillSolidRect(m_rcCustomRect,RGB(255,255,255));	
	/*静止域*/
	EBottLinePos eBottomBoundaryPosition = INSIDE_RECT;
	int nHeadRowHeight = 0;
	if (m_bIsSetUpColumnHead)
	{
		eBottomBoundaryPosition = this->PaintHeadRow(cMemoryDc);
		nHeadRowHeight = m_nHeadRowHeight;
	}
	else
	{
		this->ClearHeadItemRect();
	}
	for (int j=0 , sumRowHeight = nHeadRowHeight ; j < m_nFixedRowCount ; j++)
	{
		if (OUTSIDE_RECT == eBottomBoundaryPosition)
		{
			break;
		}
		eBottomBoundaryPosition = this->PaintDataRow(cMemoryDc,j,sumRowHeight);
	}
	/*滚动域*/
	for (int j = m_nShowedBeginRowID , sumRowHeight = nHeadRowHeight + SumRowsHeigth(0,m_nFixedRowCount); j < m_nRowCount ; j++)
	{
		if (OUTSIDE_RECT == eBottomBoundaryPosition)
		{
			break;
		}
		eBottomBoundaryPosition = this->PaintDataRow(cMemoryDc,j,sumRowHeight);
	}

	for (int i = 0,sum = 0; i < m_nColumnCount ; i++)//竖线
	{
		sum += m_vColumnsWidth[i];
		if (sum-m_nHorOffSet > nFixColumnsWidth)
		{
			CRect rect;
			if (m_bIsShowGridLine)
			{
				rect = CRect(sum-m_nHorOffSet-1,0,sum-m_nHorOffSet+1,m_nSumRowHeight-m_nVerOffSet);
			}
			else
			{
				rect = CRect(sum-m_nHorOffSet-1,0,sum-m_nHorOffSet+1,nHeadRowHeight);
			}
			sVertLine.rcCursorRect = rect;
			sVertLine.iLeftColumnID = i;
			m_vecVertLineInfo.push_back(sVertLine);

			this->SaveGridLineToVec(sum-m_nHorOffSet,0,sum-m_nHorOffSet,m_nSumRowHeight-m_nVerOffSet);
		}
	}

	CRect rcFixColumnsRect = m_rcCustomRect;
	rcFixColumnsRect.right = rcFixColumnsRect.left + nFixColumnsWidth;
	cMemoryDc.FillSolidRect(rcFixColumnsRect,RGB(255,255,255));
	/*静止域*/
	eBottomBoundaryPosition = INSIDE_RECT;
	if (m_bIsSetUpColumnHead)
	{
		eBottomBoundaryPosition = this->PaintHeadRow(cMemoryDc,TRUE);
	}
	for (int j=0 , sumRowHeight = nHeadRowHeight ; j < m_nFixedRowCount ; j++)
	{
		if (OUTSIDE_RECT == eBottomBoundaryPosition)
		{
			break;
		}
		eBottomBoundaryPosition = this->PaintDataRow(cMemoryDc,j,sumRowHeight,TRUE);
	}
	/*滚动域*/
	for (int j = m_nShowedBeginRowID , sumRowHeight = nHeadRowHeight + SumRowsHeigth(0,m_nFixedRowCount); j < m_nRowCount ; j++)
	{
		if (OUTSIDE_RECT == eBottomBoundaryPosition)
		{
			break;
		}
		eBottomBoundaryPosition = this->PaintDataRow(cMemoryDc,j,sumRowHeight,TRUE);
	}

	int iMIN = MIN(m_nFixedColumnCount,m_nColumnCount);
	for (int i = 0,sum = 0; i < iMIN ; i++)
	{
		sum += m_vColumnsWidth[i];
		CRect rect;
		if (m_bIsShowGridLine)
		{
			rect = CRect(sum-1,0,sum+1,m_nSumRowHeight-m_nVerOffSet);
		}
		else
		{
			rect = CRect(sum-1,0,sum+1,nHeadRowHeight);
		}
		sVertLine.rcCursorRect = rect;
		sVertLine.iLeftColumnID = i;
		m_vecVertLineInfo.insert(m_vecVertLineInfo.begin()+i,sVertLine);

		this->SaveGridLineToVec(sum,0,sum,m_nSumRowHeight-m_nVerOffSet);
	}

	this->SaveGridLineToVec(0,0,0,m_nSumRowHeight-m_nVerOffSet);
	this->SaveGridLineToVec(0,0,m_nSumColumnWidth-m_nHorOffSet,0);

	if (m_bIsShowGridLine)//画网格线
	{
		vector<SGridLine>::iterator it = m_vecGridLine.begin();
		while (m_vecGridLine.end() != it)
		{
			cMemoryDc.MoveTo(it->ptStartPoint);
			cMemoryDc.LineTo(it->ptEndPoint);
			it++;
		}
	}
	dc.BitBlt(0,0,rectWidth-m_nVerScrollBarWidth,rectHeigth-m_nHorScrollBarWidth,&cMemoryDc,0,0,SRCCOPY);
	bmGridMap.DeleteObject();
	cMemoryDc.DeleteDC();	

	CWnd::OnPaint();
}

void CGridList::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//nPos:可以设定滚动条的位置
	this->SetFocus();
	SCROLLINFO sHInfo;
	m_pHorScrollBar->GetScrollInfo(&sHInfo);
	if (SB_THUMBTRACK == nSBCode)
	{	
		sHInfo.nPos = nPos;
		Invalidate(FALSE);	
	}
	else if (SB_PAGELEFT == nSBCode)
	{
		if (sHInfo.nPos >= sHInfo.nPage)
		{
			sHInfo.nPos -= sHInfo.nPage;
		}
		else
		{
			sHInfo.nPos = 0;
		}
		Invalidate(FALSE);	
	}
	else if (SB_PAGERIGHT == nSBCode)
	{
		if (sHInfo.nPos+sHInfo.nPage<sHInfo.nMax)
		{
			sHInfo.nPos += sHInfo.nPage;
		}
		else
		{
			sHInfo.nPos = sHInfo.nMax;
		}
		Invalidate(FALSE);	
	}
	else if (SB_LINELEFT == nSBCode)
	{
		if (0 != sHInfo.nPos)
		{
			sHInfo.nPos--;
		}
		Invalidate(FALSE);	
	}
	else if (SB_LINERIGHT == nSBCode)
	{
		if (sHInfo.nPos < sHInfo.nMax)
		{
			sHInfo.nPos++;
		}
		Invalidate(FALSE);	
	}
	m_pHorScrollBar->SetScrollPos(sHInfo.nPos);
	m_nHorOffSet = sHInfo.nPos;
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);	
}

void CGridList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->SetFocus();
	if (m_rcCustomRect.Height() >= m_nSumRowHeight + m_nHorScrollBarWidth + 1)
	{
		return;
	}
	
	SCROLLINFO sVInfo;
	m_pVerScrollBar->GetScrollInfo(&sVInfo);

	if (SB_THUMBTRACK == nSBCode)
	{
		m_nShowedBeginRowID = m_nFixedRowCount + nPos;
		sVInfo.nPos = nPos;
		Invalidate(FALSE);	
	}
	else if (SB_PAGEUP == nSBCode)
	{
		if (m_nShowedBeginRowID >= 3 + m_nFixedRowCount)
		{
			sVInfo.nPos -= 3;
			m_nShowedBeginRowID -= 3;
		}
		else
		{
			sVInfo.nPos = 0;
			m_nShowedBeginRowID = m_nFixedRowCount;
		}
		Invalidate(FALSE);	
	}
	else if (SB_PAGEDOWN == nSBCode)
	{
		if (sVInfo.nPos + 3 < sVInfo.nMax)
		{
			sVInfo.nPos += 3;
			m_nShowedBeginRowID += 3;
		}
		else
		{
			sVInfo.nPos = sVInfo.nMax;
			m_nShowedBeginRowID = m_nFixedRowCount + sVInfo.nMax;
		}
		Invalidate(FALSE);	
	}
	else if (SB_LINEUP == nSBCode)
	{
		if (m_nShowedBeginRowID > m_nFixedRowCount)
		{
			sVInfo.nPos --;
			m_nShowedBeginRowID--;
		}
		Invalidate(FALSE);	
	}
	else if (SB_LINEDOWN == nSBCode)
	{
		if (sVInfo.nPos < sVInfo.nMax)
		{
			sVInfo.nPos ++;
			m_nShowedBeginRowID++;
		}
		Invalidate(FALSE);	
	}
	m_pVerScrollBar->SetScrollPos(sVInfo.nPos);
	m_nVerOffSet = SumRowsHeigth(m_nFixedRowCount,m_nShowedBeginRowID);
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CGridList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rcWindowRect;
	this->GetWindowRect(rcWindowRect);
	CRect rcVerScrollRect = rcWindowRect;
	rcVerScrollRect.bottom = rcWindowRect.bottom - m_nHorScrollBarWidth;
	if (pt.x < rcVerScrollRect.right && pt.x > rcVerScrollRect.left && 
		pt.y < rcVerScrollRect.bottom && pt.y > rcVerScrollRect.top)
	{
		if (NULL == m_pVerScrollBar)
		{
			return FALSE;
		}
		if(zDelta < 0)
		{
			OnVScroll(SB_LINEDOWN, 0, m_pVerScrollBar );
		}
		else if (zDelta > 0)
		{
			OnVScroll(SB_LINEUP, 0, GetScrollBarCtrl(SB_VERT));
		}
	}

	CRect rcHorScrollRect  = rcWindowRect;
	rcHorScrollRect.top = rcWindowRect.bottom - m_nHorScrollBarWidth;
	rcHorScrollRect.right = rcWindowRect.right - m_nVerScrollBarWidth;
	if (pt.x < rcHorScrollRect.right && pt.x > rcHorScrollRect.left && 
		pt.y < rcHorScrollRect.bottom && pt.y > rcHorScrollRect.top)
	{
		if (NULL == m_pHorScrollBar)
		{
			return FALSE;
		}
		if (zDelta < 0)
		{
			OnHScroll(SB_LINERIGHT,GetScrollPos(SB_HORZ),GetScrollBarCtrl(SB_HORZ));
		}
		else if (zDelta > 0)
		{	
			OnHScroll(SB_LINELEFT,m_pHorScrollBar->GetScrollPos(),m_pHorScrollBar);
		}
	}
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CGridList::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Invalidate(FALSE);

	CWnd::OnTimer(nIDEvent);
}

void CGridList::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_vRowsHeight.empty() && m_vColumnsWidth.empty())
	{
		return;
	}
	if (!m_rcCustomRect.PtInRect(point))
	{
		return;
	}

	if (m_bIsSetUpColumnHead)
	{
		this->SetFocusHeadItem(point);
	}	

	if (-1 != this->PtInCursorRects(point))
	{
		//HCURSOR hCur = (HCURSOR)LoadImage(NULL,_T("res\\Cursor.ico"),IMAGE_ICON,20,20,LR_LOADFROMFILE );
		//HCURSOR hCur = AfxGetApp()->LoadCursor(MAKEINTRESOURCE(129));
		HCURSOR hTensileCursor = LoadCursor(NULL,IDC_SIZEWE);
		::SetCursor(hTensileCursor);
	}
	
	if (m_bIsMoveVertLine == TRUE && nFlags != 0)
	{
		this->MoveVertLine(point);
		HCURSOR hTensileCursor = LoadCursor(NULL,IDC_SIZEWE);
		::SetCursor(hTensileCursor);
	}	
	CWnd::OnMouseMove(nFlags, point);
}

void CGridList::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_nVertLineNum = this->PtInCursorRects(point);
	if (m_nVertLineNum != -1)
	{
		m_bIsMoveVertLine = TRUE;
	}
	else
	{
		m_bIsMoveVertLine = FALSE;
	}
	int nFocusColumnID;
	this->GetItemID_Inter(m_nFocusRowID,nFocusColumnID,point);
	m_bIsMouseLButton = TRUE;
	Invalidate(FALSE);
	if (m_rcCustomRect.PtInRect(point))
	{
		this->SetFocus();
	}

	if (m_bIsMoveVertLine)
	{
			HCURSOR hTensileCursor = LoadCursor(NULL,IDC_SIZEWE);
		::SetCursor(hTensileCursor);
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CGridList::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int itemID = 0 ;
	BOOL bIsEmpty = m_vecHeadItemInfo.empty();
	for ( ; !bIsEmpty && itemID < m_nColumnCount ; itemID++)
	{
		if (m_vecHeadItemInfo[itemID].rcItemRect.PtInRect(point) && FALSE == m_bIsMoveVertLine)
		{
			this->OnMHeadItemLClick(itemID);
			break;
		}	
	}
	
	m_bIsMoveVertLine = FALSE;
	m_bIsMouseLButton = FALSE;
	Invalidate(FALSE);
	CWnd::OnLButtonUp(nFlags, point);
}

void CGridList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int rowID,columnID;
	if (this->GetItemID_Inter(rowID,columnID,point))
	{
		this->OnMDataItemLDbClick(rowID,columnID);
		//CString sdt;
		//sdt.Format(_T("%d %d"),rowID , columnID);
		//m_pParentCWnd->SetWindowText(sdt);
	}		
	CWnd::OnLButtonDblClk(nFlags, point);
}
/*********/
/*********/
/*********/
void CGridList::Initial()
{
	m_nHorScrollBarWidth = m_nVerScrollBarWidth = 0;
	m_nRowCount = m_nColumnCount = 0;
	m_nSumRowHeight = m_nSumColumnWidth = 0;
	m_nHorOffSet = 0;
	m_nVerOffSet = 0;
	m_nFixedRowCount = 0;
	m_nFixedColumnCount = 1;
	m_bIsMouseLButton = FALSE;
	m_bIsMoveVertLine = FALSE;
	m_nVertLineNum = -1;
	m_nShowedBeginRowID = m_nFixedRowCount;
	m_nFocusRowID = -1;
	m_nHeadRowHeight = 0;
	m_nDataRowHeight = HEIGHT_ROW_DEFAULT;
	m_nDataColumnWidth = WIDTH_COLUMN_DEFAULT;
	m_nCurrentMaxKey = 0;
}

void CGridList::Release()
{
	m_pParentCWnd = NULL;
	m_pFontHeadItem = NULL;
	m_pFontDataItem = NULL;
	if (m_pHorScrollBar)
	{
		delete m_pHorScrollBar;
		m_pHorScrollBar = NULL;
	}
	if (m_pVerScrollBar)
	{
		delete m_pVerScrollBar;
		m_pVerScrollBar = NULL;
	}
	if (m_pFontSystemDefault)
	{
		m_pFontSystemDefault->DeleteObject();
		delete m_pFontSystemDefault;
		m_pFontSystemDefault = NULL;
	}
	m_vecRowDataKey.clear();
	m_vecRowDataAddr.clear();
	m_mapGirdData.clear();
	m_mapItemRect.clear();
	m_vecHeadItemInfo.clear();
	m_vecVertLineInfo.clear();//
	m_vecGridLine.clear();//
	m_vColumnsWidth.clear();
	m_vRowsHeight.clear();
}

int CGridList::SumRowsHeigth(int nBeginRowID,int nEndRowID)
{
	int sum = 0;
	if (nBeginRowID < 0)
	{
		nBeginRowID = 0;
	}
	if (nEndRowID > m_nRowCount)
	{
		nEndRowID = m_nRowCount;
	}
	if (nBeginRowID >= nEndRowID)
	{
		return 0;
	}
	while(nBeginRowID < nEndRowID)
	{
		sum += m_vRowsHeight[nBeginRowID++];
	}
	return sum;
}

int CGridList::SumColumnsWidth(int nBeginColumnID,int nEndColumnID)
{
	int sum = 0;
	if (nBeginColumnID < 0)
	{
		nBeginColumnID = 0;
	}
	if (nEndColumnID > m_nColumnCount)
	{
		nEndColumnID = m_nColumnCount;
	}
	if (nBeginColumnID >= nEndColumnID)
	{
		return 0;
	}
	while(nBeginColumnID < nEndColumnID)
	{
		sum += m_vColumnsWidth[nBeginColumnID++];
	}
	return sum;
}

BOOL CGridList::CreateScrollBar(int nRectWidth,int nRectHeigth)
{
	if (m_pHorScrollBar)
	{
		delete m_pHorScrollBar;
		m_pHorScrollBar = NULL;
	}
	if (m_pVerScrollBar)
	{
		delete m_pVerScrollBar;
		m_pVerScrollBar = NULL;
	}

	if (m_nHorScrollBarWidth)
	{
		CRect rectHorScrollBar(0,nRectHeigth-m_nHorScrollBarWidth,nRectWidth-m_nVerScrollBarWidth,nRectHeigth);
		m_pHorScrollBar = new CScrollBar();
		if (NULL == m_pHorScrollBar)
		{
			return FALSE;
		}
		if (FALSE == m_pHorScrollBar->Create(SBS_HORZ,rectHorScrollBar,this,0x0001))
		{
			delete m_pHorScrollBar;
			m_pHorScrollBar = NULL;
			return FALSE;
		}
	}

	if (m_nVerScrollBarWidth)
	{
		CRect rectVerScrollBar(nRectWidth-m_nVerScrollBarWidth,0,nRectWidth,nRectHeigth-m_nHorScrollBarWidth);
		m_pVerScrollBar = new CScrollBar();
		if (NULL == m_pVerScrollBar)
		{
			return FALSE;
		}
		if (FALSE == m_pVerScrollBar->Create(SBS_VERT,rectVerScrollBar,this,0x0002))
		{
			delete m_pVerScrollBar;
			m_pVerScrollBar = NULL;
			return FALSE;
		}
	}	
	return TRUE;
}

void CGridList::SetScrollBar(int nRectWidth,int nRectHeigth)
{
	static int staHorScrollBarWidth = 0;
	static int staVerScrollBarWidth = 0;
	if (m_nSumColumnWidth + m_nVerScrollBarWidth < nRectWidth)
	{
		m_nHorScrollBarWidth = 0;
	}
	else
	{
		m_nHorScrollBarWidth = WIDTH_SCROLLBAR;
	}
	if (m_nSumRowHeight + m_nHorScrollBarWidth < nRectHeigth)
	{
		m_nVerScrollBarWidth = 0;
	}
	else
	{
		m_nVerScrollBarWidth = WIDTH_SCROLLBAR;
	}
	if (m_nVerScrollBarWidth != staVerScrollBarWidth || m_nHorScrollBarWidth != staHorScrollBarWidth)
	{
		this->CreateScrollBar(nRectWidth,nRectHeigth);
		staVerScrollBarWidth = m_nVerScrollBarWidth;
		staHorScrollBarWidth = m_nHorScrollBarWidth;
	}
	if (m_pHorScrollBar)
	{
		SCROLLINFO sHorInfo;
		sHorInfo.cbSize = sizeof(sHorInfo);
		sHorInfo.fMask = SIF_ALL;
		sHorInfo.nPage = WIDTH_COLUMN_DEFAULT;
		sHorInfo.nMax = m_nSumColumnWidth - (nRectWidth-m_nVerScrollBarWidth) + WIDTH_COLUMN_DEFAULT;
		sHorInfo.nMin = 0;
		sHorInfo.nPos = m_nHorOffSet;
		sHorInfo.nTrackPos = 0;
		m_pHorScrollBar->SetScrollInfo(&sHorInfo);
		if (m_nRowCount || m_bIsSetUpColumnHead)
		{
			m_pHorScrollBar->ShowScrollBar(TRUE);
		}	
	}
	if (m_pVerScrollBar)
	{
		SCROLLINFO sVerInfo;
		sVerInfo.cbSize = sizeof(sVerInfo);
		sVerInfo.fMask = SIF_ALL;
		sVerInfo.nPage = 1;
		sVerInfo.nMax = this->GetVScroInfoMax();;
		sVerInfo.nMin = 0;
		sVerInfo.nPos = m_nShowedBeginRowID - m_nFixedRowCount;
		sVerInfo.nTrackPos = 0;
		m_pVerScrollBar->SetScrollInfo(&sVerInfo);
		if (m_nColumnCount)
		{
			m_pVerScrollBar->ShowScrollBar(TRUE);
		}	
	}	
}

int CGridList::GetVScroInfoMax()
{
	int nShowingRowCount = 0;
	CRect rcCustomRect;	
	GetClientRect(rcCustomRect);
	if (rcCustomRect.Height() <= m_nHorScrollBarWidth)
	{
		return m_nRowCount + 1 - nShowingRowCount;
	}
	int nSumDataZoneHeigth = rcCustomRect.Height() - m_nHorScrollBarWidth ;
	if (m_bIsSetUpColumnHead)
	{
		if (nSumDataZoneHeigth <= m_nHeadRowHeight)
		{
			return m_nRowCount + 1 - nShowingRowCount;
		}
		nSumDataZoneHeigth -= m_nHeadRowHeight;
	}
	//int nFixedCount;
	int nFixedDataZoneHeigth = SumRowsHeigth(0,m_nFixedRowCount);
	if (nSumDataZoneHeigth < nFixedDataZoneHeigth)
	{
		for (int i = m_nFixedRowCount ; i > 0 ; i--)
		{
			nFixedDataZoneHeigth -= m_vRowsHeight[i-1];
			if (nSumDataZoneHeigth > nFixedDataZoneHeigth)
			{
				nShowingRowCount = i - 1;
				return m_nRowCount + 1 - nShowingRowCount;
			}
		}
	}
	int nMovedDataZoneHeigth = nSumDataZoneHeigth - nFixedDataZoneHeigth;
	for (int i = m_nRowCount -1 ; i >= m_nFixedRowCount ; i--)
	{
		if (SumRowsHeigth(i,m_nRowCount) > nMovedDataZoneHeigth)
		{
			nShowingRowCount = m_nFixedRowCount + m_nRowCount - (i+1);
			return m_nRowCount + 1 - nShowingRowCount;
		}
	}
	nShowingRowCount = m_nRowCount;
	return m_nRowCount + 1 - nShowingRowCount;
}

void CGridList::ClearHeadItemRect()
{
	if (m_vecHeadItemInfo.empty())
	{
		return;
	}
	for (int i = 0 ; i < m_nColumnCount ; i++)
	{
		m_vecHeadItemInfo[i].rcItemRect = CRect(0,0,0,0);
	}
}

EBottLinePos CGridList::PaintHeadRow(CDC &cMemDc,BOOL bIsColumnsFixed /* = FALSE */)
{
	cMemDc.SelectObject(m_pFontHeadItem);
	int nFixColumnsWidth = SumColumnsWidth(0,m_nFixedColumnCount);

	int nColumnCount = m_nColumnCount;
	int nHorOffSet = m_nHorOffSet;
	int nSumColumnWidth = m_nSumColumnWidth;
	if (bIsColumnsFixed)
	{
		nHorOffSet = 0;
		if (m_nColumnCount > m_nFixedColumnCount)
		{
			nColumnCount = m_nFixedColumnCount;
			nSumColumnWidth = nFixColumnsWidth;
		}	
	}

	for (int nColumnID = 0 ,nVertWidth = 0;nColumnID < nColumnCount; nColumnID++)
	{
		nVertWidth += m_vColumnsWidth[nColumnID];
		CRect rcItemRect(nVertWidth-m_vColumnsWidth[nColumnID]-nHorOffSet,0,nVertWidth-nHorOffSet,m_nHeadRowHeight);
		m_vecHeadItemInfo[nColumnID].rcItemRect = rcItemRect;
		this->OnPaintHeadItem(cMemDc,rcItemRect,nColumnID);
	}
	cMemDc.SelectObject(m_pFontSystemDefault);
	
	this->SaveGridLineToVec(0,m_nHeadRowHeight,nSumColumnWidth-nHorOffSet,m_nHeadRowHeight);
	if (m_nHeadRowHeight <= m_rcCustomRect.bottom - m_nHorScrollBarWidth)
	{
		return INSIDE_RECT;
	}
	else
	{
		return OUTSIDE_RECT;
	}
}

EBottLinePos CGridList::PaintDataRow(CDC &cMemDc, int nRowID, int &nRowRectTop ,BOOL bIsColumnsFixed /* = FALSE */)
{
	if (nRowID < 0 || nRowID >= m_nRowCount)
	{
		return INSIDE_RECT;
	}
	cMemDc.SelectObject(m_pFontDataItem);
	int nFixColumnsWidth = SumColumnsWidth(0,m_nFixedColumnCount);
	int nDataColumn = m_mapGirdData[m_vecRowDataKey[nRowID]].Size();

	int nColumnCount = m_nColumnCount;
	int nHorOffSet = m_nHorOffSet;
	int nSumColumnWidth = m_nSumColumnWidth;
	if (bIsColumnsFixed)
	{
		nHorOffSet = 0;
		if (m_nColumnCount > m_nFixedColumnCount)
		{
			nColumnCount = m_nFixedColumnCount;
			nSumColumnWidth = nFixColumnsWidth;
		}	
	}

	CRect rcRowRect(-nHorOffSet,nRowRectTop,nSumColumnWidth-nHorOffSet,nRowRectTop + m_vRowsHeight[nRowID]);
	if (m_nFocusRowID == nRowID)
	{
		cMemDc.FillSolidRect(rcRowRect,COLOR_ROW_FOCUS);
	}

	for (int nColumnID = 0 ,nVertWidth = 0;nColumnID < nColumnCount; nColumnID++)
	{
		nVertWidth += m_vColumnsWidth[nColumnID];
		CRect rcItemRect(nVertWidth-m_vColumnsWidth[nColumnID]-nHorOffSet,nRowRectTop,nVertWidth-nHorOffSet,nRowRectTop + m_vRowsHeight[nRowID]);	
		this->SaveItemRectToMap(nRowID,nColumnID,rcItemRect);
		if (nColumnID < nDataColumn) 
		{
			this->OnPaintDataItem(cMemDc,rcItemRect,nRowID,nColumnID);
		}	
	}	
	cMemDc.SelectObject(m_pFontSystemDefault);

	nRowRectTop += m_vRowsHeight[nRowID];
	this->SaveGridLineToVec(0,nRowRectTop,nSumColumnWidth-nHorOffSet,nRowRectTop);
	if (nRowRectTop <= m_rcCustomRect.bottom - m_nHorScrollBarWidth)
	{
		return INSIDE_RECT;
	}
	else
	{
		return OUTSIDE_RECT;
	}
}

void CGridList::PaintHeadItem(CDC &cMemDc, const CRect &rcDrawOnRect, int nColumnID)
{
	if (rcDrawOnRect.IsRectEmpty() || 1 == rcDrawOnRect.Width() || 1 == rcDrawOnRect.Height())
	{
		return;
	}
	CRect rcFillRect = rcDrawOnRect;
	rcFillRect.right -= 1;
	if (FALSE == m_vecHeadItemInfo[nColumnID].bIsGetFocus || m_bIsMoveVertLine)//标题色
	{
		cMemDc.FillSolidRect(rcFillRect,COLOR_BK_DIALOG/*0xD8E9EC*/);
	}
	else if (FALSE == m_bIsMoveVertLine)
	{
		CRect rcTmpRect = rcDrawOnRect;
		if (m_bIsMouseLButton)
		{
			cMemDc.FillSolidRect(rcTmpRect,RGB(255,205,0));
			rcTmpRect.left +=3 ;
			rcTmpRect.top +=2 ;
			cMemDc.FillSolidRect(rcTmpRect,RGB(236,233,240));
			rcFillRect.OffsetRect(1,1);
		} 
		else
		{
			rcTmpRect.bottom = rcDrawOnRect.bottom-2;
			cMemDc.FillSolidRect(rcTmpRect,RGB(250,250,250));
			rcTmpRect.bottom = rcDrawOnRect.bottom;
			rcTmpRect.top = rcDrawOnRect.bottom-2;
			cMemDc.FillSolidRect(rcTmpRect,RGB(255,205,0));
		}			
	}	

	cMemDc.SetTextColor(m_vecHeadItemInfo[nColumnID].sHeadItem.colTextColor);
	CString cstrTmpText = m_vecHeadItemInfo[nColumnID].sHeadItem.cstrText;
	cMemDc.DrawText(cstrTmpText,&rcFillRect,DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
	cMemDc.SetTextColor(COLOR_ITEM_TEXT_DEFAULT);
}

void CGridList::PaintDataItem(CDC& cMemDc,const CRect& rcDrawOnRect,int nRowID,int nColumnID)
{
	if (rcDrawOnRect.IsRectEmpty() || 1 == rcDrawOnRect.Width() || 1 == rcDrawOnRect.Height())
	{
		return;
	}
	if (nRowID >= m_nRowCount)
	{
		return;
	}
	int nDataRowKey = m_vecRowDataKey[nRowID];
	if (nColumnID >= m_mapGirdData[nDataRowKey].Size())
	{
		return;
	}
	CRect rcFillRect = rcDrawOnRect;
	if(COLOR_BK_DIALOG == m_mapGirdData[nDataRowKey][nColumnID].colBkColor)
	{
		m_mapGirdData[nDataRowKey][nColumnID].colBkColor = COLOR_ITEM_BK_DEFAULT;
	}
	if(COLOR_ITEM_BK_DEFAULT != m_mapGirdData[nDataRowKey][nColumnID].colBkColor)//背景色
	{
		if (nRowID != m_nFocusRowID)
		{
			cMemDc.FillSolidRect(rcFillRect,m_mapGirdData[nDataRowKey][nColumnID].colBkColor);
		}
		else
		{
			cMemDc.FillSolidRect(rcFillRect,m_mapGirdData[nDataRowKey][nColumnID].colBkColor|COLOR_ROW_FOCUS);
		}		
	}

	cMemDc.SetTextColor(m_mapGirdData[nDataRowKey][nColumnID].colTextColor);
	CString cstrTmpText = m_mapGirdData[nDataRowKey][nColumnID].cstrText;
	cMemDc.DrawText(cstrTmpText,&rcFillRect,DT_CENTER | DT_VCENTER | DT_SINGLELINE |DT_WORD_ELLIPSIS);
	cMemDc.SetTextColor(COLOR_ITEM_TEXT_DEFAULT);
}

BOOL CGridList::SaveItemRectToMap(int rowID,int columnID,const CRect& rcItemRect)
{
	if (rowID < 0 || rowID >= m_nRowCount || columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	CRect rcTmpRect = rcItemRect;
	int nFixColumnsWidth = SumColumnsWidth(0,m_nFixedColumnCount);
	if (m_nFixedColumnCount <= columnID)
	{
		if (rcTmpRect.right <= nFixColumnsWidth)
		{
			return FALSE;
		}
		else if (rcTmpRect.left < nFixColumnsWidth)
		{
			rcTmpRect.left = nFixColumnsWidth;
		}
	}

	int nRectRight = m_rcCustomRect.Width() - m_nVerScrollBarWidth;
	if (rcTmpRect.left >= nRectRight)
	{
		return FALSE;
	}
	else if (rcTmpRect.right > nRectRight)
	{
		rcTmpRect.right = nRectRight;
	}

	int nRectBottom = m_rcCustomRect.Height() - m_nHorScrollBarWidth;
	if (rcTmpRect.top >= nRectBottom)
	{
		return FALSE;
	}
	else if (rcTmpRect.bottom > nRectBottom)
	{
		rcTmpRect.bottom = nRectBottom;
	}
	m_mapItemRect[rowID*m_nColumnCount+columnID] = rcTmpRect;
	return TRUE;
}

void CGridList::SaveGridLineToVec(int nStartPointX,int nStartPointY,int nEndPointX,int nEndPointY)
{
	SGridLine line;
	line.ptStartPoint.x = nStartPointX;
	line.ptStartPoint.y = nStartPointY;
	line.ptEndPoint.x = nEndPointX;
	line.ptEndPoint.y = nEndPointY;
	m_vecGridLine.push_back(line);
}

void CGridList::SetFocusHeadItem(const CPoint& point)
{
	static int iFocusRectItem = -1;
	int nColumnID;
	for (nColumnID = 0 ; nColumnID < m_nColumnCount ; nColumnID++)
	{
		if (m_vecHeadItemInfo[nColumnID].rcItemRect.PtInRect(point))
		{
			break;
		}
	}
	if (m_nColumnCount == nColumnID)
	{
		if (-1 != iFocusRectItem)
		{
			m_vecHeadItemInfo[iFocusRectItem].bIsGetFocus = FALSE;
			iFocusRectItem = -1;
			Invalidate(FALSE);
		}
		return;
	}

	if (iFocusRectItem == nColumnID)
	{
		return;
	}
	if(-1 != iFocusRectItem)
	{
		m_vecHeadItemInfo[iFocusRectItem].bIsGetFocus = FALSE;	
	}
	m_vecHeadItemInfo[nColumnID].bIsGetFocus = TRUE;
	iFocusRectItem = nColumnID;
	Invalidate(FALSE);	
}

int CGridList::PtInCursorRects(const CPoint& point)
{
	vector<SVertLineInfo>::size_type nSize = m_vecVertLineInfo.size();
	unsigned int i=0 ;

	for(0 ; i<nSize ; i++)
	{
		if (m_vecVertLineInfo[i].rcCursorRect.PtInRect(point))
		{
			return i;
		}
	}
	return -1;
}

void CGridList::MoveVertLine(CPoint point)
{
	int i = m_nVertLineNum;
	if (0 != i && point.x < m_vecVertLineInfo[i-1].rcCursorRect.right)
	{
		point.x = m_vecVertLineInfo[i-1].rcCursorRect.right;
	}
	if (point.x <= m_vecVertLineInfo[i].rcCursorRect.left)
	{
		m_vColumnsWidth[m_vecVertLineInfo[i].iLeftColumnID] -= m_vecVertLineInfo[i].rcCursorRect.left - point.x;
		m_nSumColumnWidth -= m_vecVertLineInfo[i].rcCursorRect.left - point.x;
	} 
	else if (point.x >= m_vecVertLineInfo[i].rcCursorRect.right)
	{
		if (m_nSumColumnWidth + point.x - m_vecVertLineInfo[i].rcCursorRect.right > WIDTH_COLUMNS_SUM_MAX)
		{
			AfxMessageBox(_T("总列宽已到限值！不能移动！"));
			return;
		}
		m_vColumnsWidth[m_vecVertLineInfo[i].iLeftColumnID] += point.x - m_vecVertLineInfo[i].rcCursorRect.right;
		m_nSumColumnWidth += point.x - m_vecVertLineInfo[i].rcCursorRect.right;
	}
	m_vecVertLineInfo[i].rcCursorRect.left =  point.x - 1;
	m_vecVertLineInfo[i].rcCursorRect.right = point.x + 1;
	Invalidate(FALSE);
}

ECompareResult CGridList::CompareCtring(const CString &fstText, const CString &sndText)
{
	if (fstText == sndText)
	{
		return EQUAL;
	}
	else if (fstText > sndText)
	{
		return BIGER;
	}
	else
	{
		return SMALLER;
	}
}

void CGridList::BubbleSort(int iBaseOnColumnID /* = 0 */,ESortMode eSortMode /* = ASCENDING */)
{
	vector<CString> vecKeyString;
	this->GetColumnText_Inter(iBaseOnColumnID,vecKeyString);
	VEC_ROW_KEY* pKeyVec = &m_vecRowDataKey;
	VEC_ROW_ADDR* pAddrVec = &m_vecRowDataAddr;
	for (int k = m_nRowCount - 1 ; k >= m_nFixedRowCount + 1 ; k--)
	{
		for (int i = m_nFixedRowCount ; i < k ; i++)
		{
			int eCmpResult = this->CompareCtring(vecKeyString[i],vecKeyString[i+1]);
			if (eCmpResult == eSortMode)
			{
				swap(vecKeyString[i],vecKeyString[i+1]);
				swap((*pKeyVec)[i],(*pKeyVec)[i+1]);
				swap((*pAddrVec)[i],(*pAddrVec)[i+1]);
			}
		}
	}
	Invalidate(FALSE);
}

void CGridList::QuickSort(int iBaseOnColumnID /* = 0 */,ESortMode eSortMode /* = ASCENDING */)
{
	vector<CString> vecKeyString;
	this->GetColumnText_Inter(iBaseOnColumnID,vecKeyString);
	this->QSort(vecKeyString,m_nFixedRowCount,m_nRowCount-1,eSortMode);
}

void CGridList::HeapSort(int iBaseOnColumnID /* = 0 */,ESortMode eSortMode /* = ASCENDING */)
{
	vector<CString> vecTmpKey;
	this->GetColumnText_Inter(iBaseOnColumnID,vecTmpKey);
	int nOffset = m_nFixedRowCount;
	int nVecSize = m_nRowCount - nOffset;
	vector<CString> vecKeyString(vecTmpKey.begin()+nOffset,vecTmpKey.end());
	VEC_ROW_KEY* pKeyVec = &m_vecRowDataKey;
	VEC_ROW_ADDR* pAddrVec = &m_vecRowDataAddr;
	for (int i = nVecSize/2 ; i > 0 ; i--)
	{
		HeapAdjust(vecKeyString,i,nVecSize,eSortMode,pKeyVec,pAddrVec);
	}
	for (int j = nVecSize ; j > 1 ; j--)
	{
		swap(vecKeyString[0],vecKeyString[j-1]);
		swap((*pKeyVec)[0+nOffset],(*pKeyVec)[j-1+nOffset]);
		swap((*pAddrVec)[0+nOffset],(*pAddrVec)[j-1+nOffset]);
		HeapAdjust(vecKeyString,1,j-1,eSortMode,pKeyVec,pAddrVec);
	}
	Invalidate(FALSE);
}

int CGridList::Partition(vector<CString>& vecBaseOnText,int nLow,int nHigh,ESortMode eSortMode)
{
	VEC_ROW_KEY* pKeyVec = &m_vecRowDataKey;
	VEC_ROW_ADDR* pAddrVec = &m_vecRowDataAddr;
	int nStandar = nLow;
	int eCmpResult;
	while(nLow < nHigh)
	{
		while(nHigh > nStandar)
		{
			eCmpResult = this->CompareCtring(vecBaseOnText[nStandar],vecBaseOnText[nHigh]);
			if (eCmpResult == eSortMode)
			{
				swap(vecBaseOnText[nStandar],vecBaseOnText[nHigh]);
				swap((*pKeyVec)[nStandar],(*pKeyVec)[nHigh]);
				swap((*pAddrVec)[nStandar],(*pAddrVec)[nHigh]);
				nStandar = nHigh;
				break;
			}
			else
			{
				nHigh--;
			}
		}
		while(nLow < nStandar)
		{
			eCmpResult = this->CompareCtring(vecBaseOnText[nLow],vecBaseOnText[nStandar]);
			if (eCmpResult == eSortMode)
			{
				swap(vecBaseOnText[nLow],vecBaseOnText[nStandar]);
				swap((*pKeyVec)[nLow],(*pKeyVec)[nStandar]);
				swap((*pAddrVec)[nLow],(*pAddrVec)[nStandar]);
				nStandar = nLow;
				break;
			}
			else
			{
				nLow++;
			}
		}	
	}
	return nLow;
}

void CGridList::QSort(vector<CString>& vecBaseOnText,int nLow,int nHigh,ESortMode eSortMode)
{
	if (nLow < nHigh)
	{
		int nStandar = this->Partition(vecBaseOnText,nLow,nHigh,eSortMode);
		this->QSort(vecBaseOnText,nLow,nStandar-1,eSortMode);
		this->QSort(vecBaseOnText,nStandar+1,nHigh,eSortMode);
	}
	Invalidate(FALSE);
}

void CGridList::HeapAdjust(vector<CString>& vecBaseOnText,int nFirst,int nLast,ESortMode eSortMode,VEC_ROW_KEY* pKeyVec,VEC_ROW_ADDR* pAddrVec)
{
	int nOffset = m_nFixedRowCount;
	CString tmpCString = vecBaseOnText[nFirst-1];
	int tmpKey = (*pKeyVec)[nFirst-1+nOffset];
	DWORD_PTR tmpAddr = (*pAddrVec)[nFirst-1+nOffset];
	for (int nChild = 2*nFirst ; nChild <= nLast ; nChild *= 2)
	{
		if (nChild < nLast && -eSortMode == this->CompareCtring(vecBaseOnText[nChild-1],vecBaseOnText[nChild]))
		{
			nChild++;
		}
		if (-eSortMode != this->CompareCtring(tmpCString,vecBaseOnText[nChild-1]))
		{
			break;
		}
		vecBaseOnText[nFirst-1] = vecBaseOnText[nChild-1];
		(*pKeyVec)[nFirst-1+nOffset] = (*pKeyVec)[nChild-1+nOffset];
		(*pAddrVec)[nFirst-1+nOffset] = (*pAddrVec)[nChild-1+nOffset];
		nFirst = nChild;
	}
	vecBaseOnText[nFirst-1] = tmpCString;
	(*pKeyVec)[nFirst-1+nOffset] = tmpKey;
	(*pAddrVec)[nFirst-1+nOffset] = tmpAddr;
}

int CGridList::InitialRowWhichEmpty(int rowID)
{
	int nDataRowKey = m_vecRowDataKey[rowID];
	if (0 == nDataRowKey)
	{
		m_mapGirdData[m_nCurrentMaxKey] = SCellItemArray();
		m_vecRowDataKey[rowID] = m_nCurrentMaxKey;
		nDataRowKey = m_nCurrentMaxKey;
		m_nCurrentMaxKey++;	
	}
	return nDataRowKey;
}

BOOL CGridList::CreateGrid_Inter(int nRowCount,int nColumnCount,CWnd* pParent,const CRect& rcLocateRect /* = 0 */)
{
	if (pParent == NULL || nRowCount < 0 || nColumnCount <= 0)
	{
		return FALSE;
	}
	if (nRowCount > COUNT_ROWS_MAX)
	{
		AfxMessageBox(_T("行数超过限值！请减少行数！"));
		return FALSE;
	}
	if (nColumnCount*WIDTH_COLUMN_DEFAULT > WIDTH_COLUMNS_SUM_MAX)
	{
		AfxMessageBox(_T("总列宽超过限值！请减少列数！"));
		return FALSE;
	}

	this->Release();
	this->Initial();

	LOGFONT logFont;
	HFONT  hSysFont = (HFONT)GetStockObject(SYSTEM_FONT);
	GetObject(hSysFont,sizeof(LOGFONT),&logFont);
	m_pFontSystemDefault = new CFont;
	if (NULL == m_pFontSystemDefault)
	{
		return FALSE;
	}
	m_pFontSystemDefault->CreateFontIndirect(&logFont);
	m_pFontHeadItem = m_pFontSystemDefault;
	m_pFontDataItem = m_pFontSystemDefault;

	m_nRowCount = nRowCount;
	m_nColumnCount = nColumnCount;
	m_pParentCWnd = pParent;
	m_nSumColumnWidth = nColumnCount*WIDTH_COLUMN_DEFAULT;
	m_nSumRowHeight = nRowCount*HEIGHT_ROW_DEFAULT;
	m_vColumnsWidth.assign(nColumnCount,WIDTH_COLUMN_DEFAULT);
	m_vRowsHeight.assign(nRowCount,HEIGHT_ROW_DEFAULT);
		
	m_mapGirdData[0] = SCellItemArray();
	m_nCurrentMaxKey = 1;
	m_vecRowDataKey.assign(nRowCount,0);
	m_vecRowDataAddr.assign(nRowCount,NULL);

	m_bIsShowGridLine = TRUE;
	this->SetUpColumnHead_Inter(TRUE);

	if (FALSE == rcLocateRect.IsRectEmpty())
	{
		MoveWindow(rcLocateRect);
	}

	Invalidate(TRUE);	
	return TRUE;
}

void CGridList::SetUpColumnHead_Inter(BOOL bIsSetUp /* = FALSE */)
{
	if (bIsSetUp == m_bIsSetUpColumnHead)
	{
		return;
	}
	m_bIsSetUpColumnHead = bIsSetUp;
	if (m_bIsSetUpColumnHead)
	{
		if (m_vecHeadItemInfo.empty())
		{
			SHeadItemInfo sHeadItemInfo;
			m_vecHeadItemInfo.assign(m_nColumnCount,sHeadItemInfo);
		}
		if (0 == m_nHeadRowHeight)
		{
			m_nHeadRowHeight = HEIGHT_ROW_DEFAULT;
		}
		m_nSumRowHeight += m_nHeadRowHeight;
	}
	else
	{
		m_nSumRowHeight -= m_nHeadRowHeight;
		CRect rcCustomRect;	
		GetClientRect(rcCustomRect);
		this->OnSize(0,rcCustomRect.Width(),rcCustomRect.Height());
	}
	Invalidate(FALSE);
}

BOOL CGridList::SetHeadRowHeigth_Inter(int nHeigth /* = HEIGHT_ROW_DEFAULT */)
{
	if (nHeigth <= 0)
	{
		return FALSE;
	}
	int nLastHeigth = m_nHeadRowHeight;
	m_nHeadRowHeight = nHeigth;
	if (m_bIsSetUpColumnHead)
	{		
		m_nSumRowHeight -= nLastHeigth;
		m_nSumRowHeight += nHeigth;
		Invalidate(FALSE);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CGridList::SetRowText_Inter(int rowID, const SCellItemArray& sRowData)
{
	if (rowID < 0 || rowID >= m_nRowCount)
	{
		return FALSE;
	}

	int nSize = sRowData.Size();
	if (0 == nSize)
	{
		return FALSE;
	}
	
	int nDataRowKey = this->InitialRowWhichEmpty(rowID);
	SCellItemArray sRowArray = m_mapGirdData[nDataRowKey];
	int iDestDataSize = sRowArray.Size();
	int iSrcDataSize = MIN(nSize,m_nColumnCount);
	for (int i = 0 ; i < iSrcDataSize && i < iDestDataSize;i++)
	{
		sRowArray[i].cstrText = sRowData[i].cstrText;
	}
	if (iSrcDataSize < iDestDataSize)
	{
		for (int k = iSrcDataSize ; k < iDestDataSize ; k++)
		{
			sRowArray[k].cstrText = _T("");
		}
	}
	else
	{
		for (int j = iDestDataSize ; j < iSrcDataSize ; j++)
		{
			sRowArray.Insert(j,sRowData[j].cstrText);
		}
	}
	m_mapGirdData[nDataRowKey] = sRowArray;
	Invalidate(FALSE);
	return TRUE;
}

BOOL CGridList::SetColumnText_Inter(int columnID,const SCellItemArray& sColumnData)
{
	if(columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	int nSize = sColumnData.Size();
	if (0 == nSize)
	{
		return FALSE;
	}
	SCellItemArray tmpColumnData = sColumnData;
	//MAP_ALL_DATA* pDataMap = &m_mapGirdData;

	for(int i=0 ; i<m_nRowCount ;i++)
	{
		int nDataRowKey = this->InitialRowWhichEmpty(i);
		if (columnID < m_mapGirdData[nDataRowKey].Size())
		{
			if (i < nSize)
			{
				m_mapGirdData[nDataRowKey][columnID].cstrText = tmpColumnData[i].cstrText;
			}
			else
			{
				m_mapGirdData[nDataRowKey][columnID].cstrText = _T("");
			}
			
		}
		else
		{
			if (i < nSize)
			{
				m_mapGirdData[nDataRowKey].Insert(columnID,tmpColumnData[i].cstrText);	
			}
			else
			{
				continue;	
			}
		}		
	}

	Invalidate(FALSE);
	return TRUE;
}

void CGridList::GetColumnText_Inter(int columnID,vector<CString>& vecText)
{
	for (int i = 0 ; i < m_nRowCount ; i++)
	{
		SCellItemArray tmpArray = m_mapGirdData[m_vecRowDataKey[i]];
		if (columnID < tmpArray.Size())
		{
			vecText.push_back(tmpArray[columnID].cstrText);
		}
		else
		{
			vecText.push_back(_T(""));
		}
	}
}

BOOL CGridList::IsItemEmpty_Inter(int rowID,int columnID,VEC_ROW_KEY* pKeyVec)
{
	if (rowID < 0 || rowID >= m_nRowCount)
	{
		return TRUE;
	}
	int nDataRowKey = m_vecRowDataKey[rowID];
	if (nDataRowKey)
	{
		int nSize = m_mapGirdData[nDataRowKey].Size();
		if (columnID < nSize)
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CGridList::GetItemID_Inter(int& rRowID,int& rColumnID,const CPoint& point)
{
	static int staRowID = -1;
	rRowID = rColumnID = -1;
	if (m_rcCustomRect.PtInRect(point))
	{
		MAP_ITEM_RECT::iterator it  = m_mapItemRect.begin();
		while (m_mapItemRect.end() != it)
		{
			if(it->second.PtInRect(point))
			{
				break;
			}
			it++;
		}
		if (m_mapItemRect.end() != it)
		{
			int rectID = it->first;
			rRowID = rectID/m_nColumnCount;
			rColumnID = rectID%m_nColumnCount;
			if (rRowID > m_nRowCount)
			{
				return FALSE;
			}
			if (rRowID != staRowID)
			{
				Invalidate(FALSE);
			}
			staRowID = rRowID;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	return FALSE;
}

BOOL CGridList::GetItemRect_Inter(int rowID, int columnID, CRect &rcRect)
{
	if (rowID < 0 || rowID >= m_nRowCount || columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	MAP_ITEM_RECT::iterator it = m_mapItemRect.find(rowID*m_nColumnCount+columnID);
	if (it != m_mapItemRect.end())
	{
		rcRect = it->second;
		return TRUE;
	}
	return FALSE;
}
/*********/
/*********/
/*********/
BOOL CGridList::CreateGrid(int nRowCount,int nColumnCount,CWnd* pParent,const CRect& rcLocateRect /* = 0 */)
{
	return CreateGrid_Inter(nRowCount,nColumnCount,pParent,rcLocateRect);
}

void CGridList::ShowGridLine(BOOL bIsShow)
{
	m_bIsShowGridLine = bIsShow;
	Invalidate(FALSE);
}

void CGridList::SetUpColumnHead(BOOL bIsSetUp /* = FALSE */)
{
	this->SetUpColumnHead_Inter(bIsSetUp);
}

BOOL CGridList::SetFixedRowCount(int nCount /* = 0 */)
{
	if (nCount < 0 || nCount >= m_nRowCount)
	{
		return FALSE;
	}
	m_nFixedRowCount = nCount;
	if (NULL == m_pVerScrollBar)
	{
		m_nShowedBeginRowID = nCount;
		return TRUE;
	}
	if (m_nShowedBeginRowID <= nCount)
	{
		this->OnVScroll(SB_THUMBTRACK, 0, m_pVerScrollBar);
	}
	else
	{
		int iScrollPos = m_nShowedBeginRowID - nCount;
		this->OnVScroll(SB_THUMBTRACK, iScrollPos, m_pVerScrollBar);
	}
	this->OnSize(0,m_rcCustomRect.Width(),m_rcCustomRect.Height());
	return TRUE;
}

BOOL CGridList::SetFixedColumnCount(int nCount /* = 1 */)
{
	if (nCount < 0 || nCount >= m_nColumnCount)
	{
		return FALSE;
	}
	m_nFixedColumnCount = nCount;
	Invalidate(FALSE);
	return TRUE;
}

int CGridList::GetShowingRowCount()
{
	CRect rcCustomRect;	
	GetClientRect(rcCustomRect);
	if (rcCustomRect.Height() <= m_nHorScrollBarWidth)
	{
		return 0;
	}
	int nSumDataZoneHeigth = rcCustomRect.Height() - m_nHorScrollBarWidth ;
	if (m_bIsSetUpColumnHead)
	{
		if (nSumDataZoneHeigth <= m_nHeadRowHeight)
		{
			return 0;
		}
		nSumDataZoneHeigth -= m_nHeadRowHeight;
	}
	//int nFixedCount;
	int nFixedDataZoneHeigth = SumRowsHeigth(0,m_nFixedRowCount);
	if (nSumDataZoneHeigth < nFixedDataZoneHeigth)
	{
		for (int i = m_nFixedRowCount ; i > 0 ; i--)
		{
			nFixedDataZoneHeigth -= m_vRowsHeight[i-1];
			if (nSumDataZoneHeigth >= nFixedDataZoneHeigth)
			{
				return i;
			}
		}
	}
	int nMovedDataZoneHeigth = nSumDataZoneHeigth - nFixedDataZoneHeigth;
	for (int i = m_nShowedBeginRowID ; i < m_nRowCount ; i++)
	{
		if (SumRowsHeigth(m_nShowedBeginRowID,i+1) >= nMovedDataZoneHeigth)
		{
			return m_nFixedRowCount+i+1-m_nShowedBeginRowID;
		}
	}
	return m_nFixedRowCount+m_nRowCount-m_nShowedBeginRowID;
}

int CGridList::GetFocusRowID()
{
	return m_nFocusRowID;
}

void CGridList::SetTableTitle(const CString &cstrTitleText)
{

}

void CGridList::ReSetGrid()
{
	if (m_nColumnCount*WIDTH_COLUMN_DEFAULT > WIDTH_COLUMNS_SUM_MAX)
	{
		AfxMessageBox(_T("总列宽超过限值，请删除列！"));
		return;
	}
	m_nHorOffSet = 0;
	m_nVerOffSet = 0;
	m_nShowedBeginRowID = m_nFixedRowCount;

	m_vRowsHeight.clear();
	m_vColumnsWidth.clear();
	m_vRowsHeight.assign(m_nRowCount,HEIGHT_ROW_DEFAULT);
	m_vColumnsWidth.assign(m_nColumnCount,WIDTH_COLUMN_DEFAULT);
	m_nSumRowHeight = m_nRowCount*HEIGHT_ROW_DEFAULT;
	m_nSumColumnWidth = m_nColumnCount*WIDTH_COLUMN_DEFAULT;
	if (m_bIsSetUpColumnHead)
	{
		m_nSumRowHeight += m_nHeadRowHeight;
	}
	this->SetHeadRowHeigth_Inter(HEIGHT_ROW_DEFAULT);
	Invalidate(FALSE);
}

void CGridList::Clear()
{
	m_vecRowDataKey.clear();
	m_vecRowDataAddr.clear();
	m_mapGirdData.clear();
	m_mapGirdData[0] = SCellItemArray();
	m_nCurrentMaxKey = 1;
	m_vecRowDataKey.assign(m_nRowCount,0);
	m_vecRowDataAddr.assign(m_nRowCount,NULL);
	Invalidate(FALSE);
}

void CGridList::DestoryGrid()
{
	this->Release();
	this->Initial();
	Invalidate(TRUE);
}

ECompareResult CGridList::CompareData(int fstRowID,int fstColumnID,int sndRowID,int sndColumnID)
{
	VEC_ROW_KEY* pKeyVec = &m_vecRowDataKey;
	ECompareResult eResult;
	/*if (fstRowID < 0 || fstRowID >= m_nRowCount || 
		sndRowID < 0 || sndRowID >= m_nRowCount ||
		fstColumnID < 0 || fstColumnID >= m_nColumnCount ||
		sndColumnID < 0 || sndColumnID >= m_nColumnCount)
	{
		eResult = NORESULT;
		return eResult;
	}*/
	assert(fstRowID >= 0 && fstRowID < m_nRowCount); 
	assert(sndRowID >= 0 && sndRowID < m_nRowCount);
	assert(fstColumnID >= 0 && fstColumnID < m_nColumnCount);
	assert(sndColumnID >= 0 && sndColumnID < m_nColumnCount);
	
	BOOL bFirst = IsItemEmpty_Inter(fstRowID,fstColumnID,pKeyVec);
	BOOL bSecond = IsItemEmpty_Inter(sndRowID,sndColumnID,pKeyVec);

	if (FALSE == bFirst && FALSE == bSecond)
	{
		eResult = this->CompareCtring(m_mapGirdData[(*pKeyVec)[fstRowID]][fstColumnID].cstrText,m_mapGirdData[(*pKeyVec)[sndRowID]][sndColumnID].cstrText);
	}
	else if (FALSE == bFirst && TRUE == bSecond)
	{
		eResult = BIGER;
	}
	else if (TRUE == bFirst && FALSE == bSecond)
	{
		eResult = SMALLER;
	}
	else
	{
		//eResult = NORESULT;
		eResult = EQUAL;
	}
	return eResult;
}

BOOL CGridList::ExchangeRow(int fstRowID, int sndRowID)
{
	if (fstRowID < m_nFixedRowCount || fstRowID >= m_nRowCount || sndRowID < m_nFixedRowCount || sndRowID >= m_nRowCount)
	{
		return FALSE;
	}
	if (fstRowID == sndRowID)
	{
		return TRUE;
	}
	swap(m_vecRowDataKey[fstRowID],m_vecRowDataKey[sndRowID]);
	swap(m_vecRowDataAddr[fstRowID],m_vecRowDataAddr[sndRowID]);
	Invalidate(FALSE);
	return TRUE;
}

void CGridList::Sort(int iBaseOnColumnID /* = 0 */,ESortMode eSortMode /* = ASCENDING */)
{
	this->HeapSort(iBaseOnColumnID,eSortMode);
}

void CGridList::SetItemFont(CFont* pFont /* = FONT_SYS_DEFAULT */)
{
	m_pFontDataItem = pFont;
	if (FONT_SYS_DEFAULT == pFont)
	{
		m_pFontDataItem = m_pFontSystemDefault;
	}
	Invalidate(FALSE);
}

void CGridList::SetHeadItemFont(CFont* pFont /* = FONT_SYS_DEFAULT */)
{
	m_pFontHeadItem = pFont;
	if (FONT_SYS_DEFAULT == pFont)
	{
		m_pFontHeadItem = m_pFontSystemDefault;
	}
	Invalidate(FALSE);
}

CFont* CGridList::GetItemFont()
{
	return m_pFontDataItem;
}

CFont* CGridList::GetHeadItemFont()
{
	return m_pFontHeadItem;
}

CFont* CGridList::GetSysDefaultFont()
{
	return m_pFontSystemDefault;
}

BOOL CGridList::SetHeadItemText(int columnID, const CString &cstrText)
{
	if (columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	if (m_vecHeadItemInfo.empty())
	{
		return FALSE;
	}
	m_vecHeadItemInfo[columnID].sHeadItem.cstrText = cstrText;
	Invalidate(FALSE);
	return TRUE;
}

BOOL CGridList::SetHeadItemTextCol(int columnID,const COLORREF& colTextColor /* = COLOR_ITEM_TEXT_DEFAULT */)
{
	if (columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	if (m_vecHeadItemInfo.empty())
	{
		return FALSE;
	}
	m_vecHeadItemInfo[columnID].sHeadItem.colTextColor = colTextColor;
	Invalidate(FALSE);
	return TRUE;
}

BOOL CGridList::SetHeadRowHeigth(int nHeigth /* = HEIGHT_ROW_DEFAULT */)
{
	return this->SetHeadRowHeigth_Inter(nHeigth);
}

int CGridList::GetHeadRowHeigth()
{
	return m_nHeadRowHeight;
}

BOOL CGridList::GetHeadItem(int columnID, SHeadItemInfo &sHeadItemStruct)
{
	if (columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	if (m_vecHeadItemInfo.empty())
	{
		return FALSE;
	}
	sHeadItemStruct = m_vecHeadItemInfo[columnID];
	return TRUE;
}

BOOL CGridList::GetHeadItemRect(int columnID, CRect &rcRect)
{
	if (columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	if (m_vecHeadItemInfo.empty())
	{
		return FALSE;
	}
	rcRect = m_vecHeadItemInfo[columnID].rcItemRect;
	return TRUE;
}

BOOL CGridList::SetRowHeigth(int rowID /* = All_ARRAY */,int nHeigth /* = HEIGHT_ROW_DEFAULT */)
{
	if (nHeigth <= 0)
	{
		return FALSE;
	}
	if (All_ARRAY == rowID)
	{
		m_nDataRowHeight = nHeigth;
		m_vRowsHeight.clear();
		m_vRowsHeight.assign(m_nRowCount,nHeigth);
		m_nSumRowHeight = m_nRowCount * nHeigth;
		if (m_bIsSetUpColumnHead)
		{
			m_nSumRowHeight += m_nHeadRowHeight;
		}
		Invalidate(FALSE);
		return TRUE;
	}
	if (rowID < 0 || rowID >= m_nRowCount)
	{
		return FALSE;
	}
	//m_nDataRowHeight = HEIGHT_ROW_DEFAULT;
	m_nSumRowHeight -= m_vRowsHeight[rowID];
	m_vRowsHeight[rowID] = nHeigth;
	m_nSumRowHeight += nHeigth;
	Invalidate(FALSE);
	return TRUE;
}

int CGridList::GetRowHeigth(int rowID)
{
	if (rowID < 0 || rowID >= m_nRowCount)
	{
		return 0;
	}
	else
	{
		return m_vRowsHeight[rowID];
	}
}

BOOL CGridList::SetColumnWidth(int columnID /* = All_ARRAY */,int nWidth /* = WIDTH_COLUMN_DEFAULT */)
{
	if (nWidth <= 0)
	{
		return FALSE;
	}
	if (All_ARRAY == columnID)
	{
		if (m_nColumnCount * nWidth > WIDTH_COLUMNS_SUM_MAX)
		{
			AfxMessageBox(_T("总列宽超过限值！不能设置！"));
			return FALSE;
		}
		m_nDataColumnWidth = nWidth;
		m_vColumnsWidth.clear();
		m_vColumnsWidth.assign(m_nColumnCount,nWidth);
		m_nSumColumnWidth = m_nColumnCount * nWidth;
		Invalidate(FALSE);
		return TRUE;
	}
	if (columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	if (m_nSumColumnWidth - m_vColumnsWidth[columnID] + nWidth > WIDTH_COLUMNS_SUM_MAX)
	{
		AfxMessageBox(_T("总列宽超过限值！不能设置！"));
		return FALSE;
	}
	m_nSumColumnWidth -= m_vColumnsWidth[columnID];
	m_vColumnsWidth[columnID] = nWidth;
	m_nSumColumnWidth += nWidth;
	Invalidate(FALSE);
	return TRUE;
}

int CGridList::GetColumnWidth(int columnID)
{
	if (columnID < 0 || columnID >= m_nColumnCount)
	{
		return 0;
	}
	else
	{
		return m_vColumnsWidth[columnID];
	}
}

BOOL CGridList::SetRowText(int rowID,const std::vector<CString> &vecText)
{
	SCellItemArray sRowData(vecText);
	return this->SetRowText_Inter(rowID,sRowData);
}

BOOL CGridList::SetRowText(int rowID,const std::map<int,CString> &mapText)
{
	SCellItemArray sRowData(mapText);
	return this->SetRowText_Inter(rowID,sRowData);
}

BOOL CGridList::SetColumnText(int columnID,const std::vector<CString> &vecText)
{
	SCellItemArray sColumnData(vecText);
	return this->SetColumnText_Inter(columnID,sColumnData);
}

BOOL CGridList::SetColumnText(int columnID,const std::map<int,CString> &mapText)
{
	SCellItemArray sColumnData(mapText);
	return this->SetColumnText_Inter(columnID,sColumnData); 
}

BOOL CGridList::InsertRow(int rowID /* = LAST_ARRAY */,int nRowHeigth /* = LENGTH_DEFAULT */)
{
	if (LAST_ARRAY == rowID)
	{
		rowID = m_nRowCount;
	}
	if (LENGTH_DEFAULT == nRowHeigth)
	{
		nRowHeigth = m_nDataRowHeight;
	}
	if (rowID < 0 || rowID > m_nRowCount || nRowHeigth <= 0)
	{
		return FALSE;
	}
	if (COUNT_ROWS_MAX == m_nRowCount)
	{
		AfxMessageBox(_T("行数已到限值，不能插入"));
		return FALSE;
	}
	if (rowID <= m_nFocusRowID)
	{
		m_nFocusRowID++;
	}
	m_vRowsHeight.insert(m_vRowsHeight.begin()+rowID,nRowHeigth);
	m_vecRowDataKey.insert(m_vecRowDataKey.begin()+rowID,0);
	m_vecRowDataAddr.insert(m_vecRowDataAddr.begin()+rowID,NULL);
	m_nSumRowHeight += nRowHeigth;
	m_nRowCount += 1;

	Invalidate(FALSE);
	return TRUE;
}

BOOL CGridList::DeleteRow(int rowID)
{
	if (rowID < 0 || rowID >= m_nRowCount)
	{
		return FALSE;
	}
	if (rowID < m_nFocusRowID)
	{
		m_nFocusRowID--;
	}
	if (1 == m_nRowCount)
	{
		m_nVerOffSet = 0;
		m_nShowedBeginRowID = m_nFixedRowCount;
		m_nFocusRowID = -1;
		//this->Release();
		//this->Initial();
		//Invalidate(TRUE);
		//return TRUE;
	}
	
	int nHeigth = m_vRowsHeight[rowID];
	m_nSumRowHeight -= nHeigth;//
	m_vRowsHeight.erase(m_vRowsHeight.begin() + rowID);//

	int nDataRowKey = m_vecRowDataKey[rowID];
	m_vecRowDataKey.erase(m_vecRowDataKey.begin()+rowID);
	if (nDataRowKey)
	{
		m_mapGirdData.erase(nDataRowKey);
	}
	m_vecRowDataAddr.erase(m_vecRowDataAddr.begin()+rowID);
	
	m_nRowCount -= 1;//

	CRect rcCustomRect;	
	GetClientRect(rcCustomRect);
	if (rowID < m_nFixedRowCount)
	{
		m_nShowedBeginRowID--;
		m_nVerOffSet = this->SumRowsHeigth(m_nFixedRowCount,m_nShowedBeginRowID);
		this->OnSize(0,rcCustomRect.Width(),rcCustomRect.Height());
	}
	else if (rowID >= m_nFixedRowCount && rowID < m_nShowedBeginRowID)
	{
		m_nShowedBeginRowID--;
		m_nVerOffSet -= nHeigth;
	}
	else
	{
		this->OnSize(0,rcCustomRect.Width(),rcCustomRect.Height());
	}
	if (m_nRowCount)
	{
		Invalidate(FALSE);
	}
	else
	{
		Invalidate(TRUE);
	}
	return TRUE;
}

BOOL CGridList::InsertColumn(int columnID /* = LAST_ARRAY */,int nColumnWidth /* = LENGTH_DEFAULT */)
{
	if (LAST_ARRAY == columnID)
	{
		columnID = m_nColumnCount;
	}
	if (LENGTH_DEFAULT == nColumnWidth)
	{
		nColumnWidth = m_nDataColumnWidth;
	}
	if (columnID < 0 || columnID > m_nColumnCount || nColumnWidth <= 0)
	{
		return FALSE;
	}
	if (m_nSumColumnWidth + nColumnWidth > WIDTH_COLUMNS_SUM_MAX)
	{
		AfxMessageBox(_T("总列宽超过限值！请调整列宽！"));
		return FALSE;
	}

	m_vColumnsWidth.insert(m_vColumnsWidth.begin()+columnID,nColumnWidth);
	m_nSumColumnWidth += nColumnWidth;
	m_nColumnCount += 1;
	for (int i = 0 ; i < m_nRowCount ; i++)
	{
		int nDataRowKey = m_vecRowDataKey[i];
		if (nDataRowKey)
		{
			if (columnID < m_mapGirdData[nDataRowKey].Size())
			{
				m_mapGirdData[nDataRowKey].Insert(columnID,_T(""));
			}	
		}
	}
	SHeadItemInfo sHeadItemInfo;
	m_vecHeadItemInfo.insert(m_vecHeadItemInfo.begin()+columnID,sHeadItemInfo);

	Invalidate(FALSE);
	return TRUE;
}

BOOL CGridList::DeleteColumn(int columnID)
{
	if(columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	if (1 == m_nColumnCount)
	{	
		m_nHorOffSet = 0;
		m_nVerOffSet = 0;
		m_nShowedBeginRowID = m_nFixedRowCount;
		m_nFocusRowID = -1;
		//this->Release();
		//this->Initial();
		//Invalidate(TRUE);
		//return TRUE;
	}

	int sum = SumColumnsWidth(m_nFixedColumnCount,columnID);
	if (m_nHorOffSet > sum)
	{
		int nFixColumnsWidth = SumColumnsWidth(0,m_nFixedColumnCount);
		CRect rcRect;
		this->GetItemRect_Inter(0,columnID,rcRect);
		int nHorOffSet = m_vColumnsWidth[columnID];
		if (rcRect.right > nFixColumnsWidth)
		{
			 nHorOffSet = m_vColumnsWidth[columnID] - (rcRect.right - nFixColumnsWidth);
		}
		if (m_nHorOffSet > nHorOffSet)
		{
			m_nHorOffSet -= nHorOffSet;
		}
		else
		{
			m_nHorOffSet = 0;
		}	
	}	

	m_nSumColumnWidth -= m_vColumnsWidth[columnID];
	m_vColumnsWidth.erase(m_vColumnsWidth.begin() + columnID);

	for (int i = 0 ; i < m_nRowCount ; i++)
	{
		int nDataRowKey = m_vecRowDataKey[i];
		if (nDataRowKey)
		{
			if (columnID < m_mapGirdData[nDataRowKey].Size())
			{
				m_mapGirdData[nDataRowKey].Erase(columnID);
			}
		}
	}

	m_nColumnCount -= 1;
	m_vecHeadItemInfo.erase(m_vecHeadItemInfo.begin()+columnID);
	CRect rcCustomRect;	
	GetClientRect(rcCustomRect);
	this->OnSize(0,rcCustomRect.Width(),rcCustomRect.Height());
	if (m_nColumnCount)
	{
		Invalidate(FALSE);
	}
	else
	{
		Invalidate(TRUE);
	}	
	return TRUE;
}

int CGridList::GetRowCount()
{
	return m_nRowCount;
}

int CGridList::GetColumnCount()
{
	return m_nColumnCount;
}

BOOL CGridList::SetItem(int rowID, int columnID, const SCellItem& rItem)
{
	if (rowID < 0 || rowID >= m_nRowCount || columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	int nDataRowKey = this->InitialRowWhichEmpty(rowID);
	if (columnID < m_mapGirdData[nDataRowKey].Size())
	{
		m_mapGirdData[nDataRowKey][columnID] = rItem;
	}
	else
	{
		m_mapGirdData[nDataRowKey].Insert(columnID,rItem);
	}	
	Invalidate(FALSE);
	return TRUE;	
}

BOOL CGridList::GetItem(int rowID, int columnID, SCellItem &rItem)
{
	if (rowID < 0 || rowID >= m_nRowCount || columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	rItem = SCellItem();
	if (FALSE == this->IsItemEmpty_Inter(rowID,columnID,&m_vecRowDataKey))
	{
		rItem = m_mapGirdData[m_vecRowDataKey[rowID]][columnID];
	}
	return TRUE;
}

BOOL CGridList::IsItemEmpty(int rowID,int columnID)
{
	return IsItemEmpty_Inter(rowID,columnID,&m_vecRowDataKey);
}

BOOL CGridList::ClearItem(int rowID, int columnID)
{
	if (rowID < 0 || rowID >= m_nRowCount || columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	if (FALSE == this->IsItemEmpty_Inter(rowID,columnID,&m_vecRowDataKey))
	{
		m_mapGirdData[m_vecRowDataKey[rowID]][columnID] = SCellItem();
	}
	Invalidate(FALSE);
	return TRUE;
}

BOOL CGridList::SetItemText(int rowID, int columnID, const CString& cstrText)
{
	if (rowID < 0 || rowID >= m_nRowCount || columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	int nDataRowKey = this->InitialRowWhichEmpty(rowID);
	if (columnID < m_mapGirdData[nDataRowKey].Size())
	{
		m_mapGirdData[nDataRowKey][columnID].cstrText = cstrText;
	}
	else
	{
		m_mapGirdData[nDataRowKey].Insert(columnID,cstrText);
	}
	Invalidate(FALSE);
	return TRUE;
}

BOOL CGridList::GetItemText(int rowID, int columnID, CString &cstrText)
{
	if (rowID < 0 || rowID >= m_nRowCount || columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	cstrText = _T("");
	if (FALSE == this->IsItemEmpty_Inter(rowID,columnID,&m_vecRowDataKey))
	{
		cstrText = m_mapGirdData[m_vecRowDataKey[rowID]][columnID].cstrText;
	}
	return TRUE;
}

BOOL CGridList::SetItemTextColor(int rowID, int columnID, const COLORREF &colTextColor)
{
	if (rowID < 0 || rowID >= m_nRowCount || columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	int nDataRowKey = this->InitialRowWhichEmpty(rowID);
	if (columnID < m_mapGirdData[nDataRowKey].Size())
	{
		m_mapGirdData[nDataRowKey][columnID].colTextColor = colTextColor;
	}
	else
	{
		m_mapGirdData[nDataRowKey].Insert(columnID,_T(""),colTextColor);
	}
	Invalidate(FALSE);
	return TRUE;
}

BOOL CGridList::GetItemTextColor(int rowID, int columnID, COLORREF &colTextColor)
{
	if (rowID < 0 || rowID >= m_nRowCount || columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	colTextColor = COLOR_ITEM_TEXT_DEFAULT;
	if (FALSE == this->IsItemEmpty_Inter(rowID,columnID,&m_vecRowDataKey))
	{
		colTextColor = m_mapGirdData[m_vecRowDataKey[rowID]][columnID].colTextColor;
	}
	return TRUE;
}

BOOL CGridList::SetItemBkColor(int rowID, int columnID, const COLORREF &colBkColor)
{
	if (rowID < 0 || rowID >= m_nRowCount || columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	int nDataRowKey = this->InitialRowWhichEmpty(rowID);
	if (columnID < m_mapGirdData[nDataRowKey].Size())
	{
		m_mapGirdData[nDataRowKey][columnID].colBkColor = colBkColor;
	}
	else
	{
		m_mapGirdData[nDataRowKey].Insert(columnID,_T(""),COLOR_ITEM_TEXT_DEFAULT,colBkColor);
	}
	Invalidate(FALSE);
	return TRUE;
}

BOOL CGridList::GetItemBkColor(int rowID, int columnID, COLORREF &colBkColor)
{
	if (rowID < 0 || rowID >= m_nRowCount || columnID < 0 || columnID >= m_nColumnCount)
	{
		return FALSE;
	}
	colBkColor = COLOR_ITEM_BK_DEFAULT;
	if (FALSE == this->IsItemEmpty_Inter(rowID,columnID,&m_vecRowDataKey))
	{
		colBkColor = m_mapGirdData[m_vecRowDataKey[rowID]][columnID].colBkColor;
	}
	return TRUE;
}

BOOL CGridList::GetItemID(int& rRowID,int& rColumnID,const CPoint& point)
{
	return this->GetItemID_Inter(rRowID,rColumnID,point);
}

BOOL CGridList::GetItemRect(int rowID,int columnID,CRect& rcRect)
{
	return this->GetItemRect_Inter(rowID,columnID,rcRect);
}

void CGridList::OnMHeadItemLClick(int columnID)
{
	clock_t b,e;
	b = clock();

	ESortMode eNowSortMode = m_vecHeadItemInfo[columnID].eNextSortMode;
	this->HeapSort(columnID,eNowSortMode);
	m_vecHeadItemInfo[columnID].eNextSortMode = ESortMode(-eNowSortMode);

	e = clock();
	int i = e-b;
	CString s;
	s.Format(_T("%d"),i);
	m_pParentCWnd->SetWindowText(s);
}

void CGridList::OnMDataItemLDbClick(int rowID,int columnID)
{

}

void CGridList::OnPaintHeadItem(CDC &cMemDc, const CRect &rcDrawOnRect, int columnID)
{
	this->PaintHeadItem(cMemDc,rcDrawOnRect,columnID);
}

void CGridList::OnPaintDataItem(CDC& cMemDc,const CRect& rcDrawOnRect,int rowID,int columnID)
{
	this->PaintDataItem(cMemDc,rcDrawOnRect,rowID,columnID);//数据
}

BOOL CGridList::SetRowData(int rowID,DWORD_PTR pRowData)
{
	if (rowID < 0 || rowID >= m_nRowCount)
	{
		return FALSE;
	}
	m_vecRowDataAddr[rowID] = pRowData;
	Invalidate(FALSE);
	return TRUE;
}

DWORD_PTR CGridList::GetRowData(int rowID)
{
	if (rowID < 0 || rowID >= m_nRowCount)
	{
		return 0;
	}
	return m_vecRowDataAddr[rowID];
}

