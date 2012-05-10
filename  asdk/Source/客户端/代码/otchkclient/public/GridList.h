#pragma once
#include <vector>
#include <map>
#include <list>

#define GRIDLISTCONTROL _T("CGridListControl")
#define WIDTH_SCROLLBAR 18
#define HEIGHT_ROW_DEFAULT 18
#define WIDTH_COLUMN_DEFAULT 80
#define COLOR_ITEM_TEXT_DEFAULT 0x000000
#define COLOR_ITEM_BK_DEFAULT 0xFFFFFF
#define COLOR_ROW_FOCUS 0xE0E0E0
#define COUNT_ROWS_MAX (32768-2)//滚动条滚动块的位置决定
#define WIDTH_COLUMNS_SUM_MAX (32768-98)//滚动条滚动块的位置决定
#define All_ARRAY -1
#define LAST_ARRAY -1
#define LENGTH_DEFAULT -1
#define FONT_SYS_DEFAULT 0
#define MIN(iA,iB) (iA)<(iB)?(iA):(iB)
#define ARRAY_CELL_ITEM vector<SCellItem>
#define ITERATOR_ARRAY_VEC vector<SCellItem>::iterator
//#define  IDC_TENSILE MAKEINTRESOURCE(129)

const COLORREF COLOR_BK_DIALOG = ::GetSysColor(COLOR_BTNFACE);

using namespace std;

enum ECompareResult
{
	NORESULT = -2, 
	SMALLER, 
	EQUAL, 
	BIGER
};

enum ESortMode
{
	ASCENDING = 1, 
	DESCENDING = -1
};

typedef enum EBottomBoundaryPosition
{
	INSIDE_RECT = 0,	
	OUTSIDE_RECT
}EBottLinePos;

struct SCellItem
{
	CString cstrText;
	COLORREF colTextColor;
	COLORREF colBkColor;
	SCellItem()
	{
		this->cstrText = _T("");
		this->colTextColor = COLOR_ITEM_TEXT_DEFAULT;
		this->colBkColor = COLOR_ITEM_BK_DEFAULT; 
	};
	SCellItem(const CString &cstrText,
		COLORREF colTextColor = COLOR_ITEM_TEXT_DEFAULT,
		COLORREF colBkColor = COLOR_ITEM_BK_DEFAULT)
	{
		this->cstrText = cstrText;
		this->colTextColor = colTextColor;
		this->colBkColor = colBkColor; 
	};
};

struct SHeadItemInfo
{
	BOOL bIsGetFocus;
	ESortMode eNextSortMode;
	CRect rcItemRect;
	SCellItem sHeadItem;	

	SHeadItemInfo()
	{
		this->bIsGetFocus = FALSE;
		this->eNextSortMode = ASCENDING;
		this->rcItemRect = CRect(0,0,0,0);
		this->sHeadItem.colBkColor = COLOR_BK_DIALOG;
	};
};

struct SGridLine
{
	CPoint ptStartPoint;
	CPoint ptEndPoint;
	SGridLine()
	{
		ptStartPoint.x = 0;
		ptStartPoint.y = 0;
		ptEndPoint.x = 0;
		ptEndPoint.y = 0;
	};
};

struct SVertLineInfo
{
	CRect rcCursorRect;
	int iLeftColumnID;
};

struct SCellItemArray
{
private:
	mutable ARRAY_CELL_ITEM m_vecArrayData;/*********************/
	mutable ARRAY_CELL_ITEM::size_type m_nArraySize;
	mutable ITERATOR_ARRAY_VEC m_arrayIt;
protected:
	void InsertItem(unsigned int nRowOrColumn_ID,const SCellItem& sItem);
public:
	SCellItemArray();
	SCellItemArray(const vector<CString>& vecText);
	SCellItemArray(const map<int,CString>& mapText);
	SCellItemArray(const ARRAY_CELL_ITEM& vecItem);
	SCellItemArray(const SCellItemArray& other);
	SCellItemArray operator = (const SCellItemArray& other);
	void Assign(ITERATOR_ARRAY_VEC beginIt,ITERATOR_ARRAY_VEC endIt);
	void Insert(unsigned int nRowOrColumn_ID,const SCellItem& sItem);
	void Insert(unsigned int nRowOrColumn_ID,const CString& cstrText,
		COLORREF colTextColor = COLOR_ITEM_TEXT_DEFAULT,
		COLORREF colBkColor = COLOR_ITEM_BK_DEFAULT);

	SCellItem& operator[] (unsigned int nID) const;
	SCellItem& At(unsigned int nID) const;
	ITERATOR_ARRAY_VEC& Find(unsigned int nRowOrColumn_ID) const;
	ITERATOR_ARRAY_VEC& Begin() const;
	ITERATOR_ARRAY_VEC& End() const;
	ITERATOR_ARRAY_VEC& Erase(unsigned int nRowOrColumn_ID);
	ITERATOR_ARRAY_VEC& Erase(ITERATOR_ARRAY_VEC iBegIt,ITERATOR_ARRAY_VEC iEndIt);//
	BOOL Empty() const;
	int Size() const;
	void Clear();

	void SetArrayData(const ARRAY_CELL_ITEM& vecData);
	ARRAY_CELL_ITEM& GetArrayData() const;	
};

// CGridList

class CGridList : public CWnd
{
	DECLARE_DYNAMIC(CGridList)
typedef vector<int> VEC_ROW_KEY;
typedef vector<DWORD_PTR> VEC_ROW_ADDR;
typedef map<unsigned long,SCellItemArray> MAP_ALL_DATA;
typedef map<long,CRect> MAP_ITEM_RECT;

public:
	CGridList();
	virtual ~CGridList();
	
protected:
	DECLARE_MESSAGE_MAP()

protected:
	BOOL RegisterWndClass();

public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);	
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);//
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

private:
	CRect m_rcCustomRect;
	CWnd * m_pParentCWnd;
	CScrollBar* m_pHorScrollBar;
	CScrollBar* m_pVerScrollBar;
	int m_nHorScrollBarWidth;
	int m_nVerScrollBarWidth;
	int m_nRowCount;
	int m_nColumnCount;
	vector<int> m_vRowsHeight;
	vector<int> m_vColumnsWidth;
	int m_nSumRowHeight;
	int m_nSumColumnWidth;
	int m_nHorOffSet;//Be Setted in OnHScroll
	int m_nVerOffSet;//Be Setted in OnVScroll
	int m_nFixedRowCount;
	int m_nFixedColumnCount;
	int m_nHeadRowHeight;
	int m_nDataRowHeight;
	int m_nDataColumnWidth;
	
	BOOL m_bIsShowGridLine;	
	BOOL m_bIsSetUpColumnHead;//Be Setted in SetUpColumnHead
	BOOL m_bIsMouseLButton;
	BOOL m_bIsMoveVertLine;
	int m_nVertLineNum;
	int m_nShowedBeginRowID;
	int m_nFocusRowID;

	int m_nCurrentMaxKey;
	MAP_ALL_DATA m_mapGirdData;
	VEC_ROW_KEY m_vecRowDataKey;
	VEC_ROW_ADDR m_vecRowDataAddr;

	MAP_ITEM_RECT m_mapItemRect;
	vector<SVertLineInfo> m_vecVertLineInfo;
	vector<SHeadItemInfo> m_vecHeadItemInfo;
	vector<SGridLine> m_vecGridLine;

	CFont* m_pFontSystemDefault;
	CFont* m_pFontHeadItem;
	CFont* m_pFontDataItem;	

protected:
	void Initial();
	void Release();
	int SumRowsHeigth(int nBeginRowID,int nEndRowID);
	int SumColumnsWidth(int nBeginColumnID,int nEndColumnID);
	BOOL CreateScrollBar(int nRectWidth,int nRectHeigth);//
	void SetScrollBar(int nRectWidth,int nRectHeigth);//
	int GetVScroInfoMax();//
	void ClearHeadItemRect();
	EBottLinePos PaintHeadRow(CDC &cMemDc,BOOL bIsColumnsFixed = FALSE );//*
	EBottLinePos PaintDataRow(CDC &cMemDc, int nRowID, int &nRowRectTop ,BOOL bIsColumnsFixed = FALSE);//*
	void PaintHeadItem(CDC& cMemDc,const CRect& rcDrawOnRect,int nColumnID);
	void PaintDataItem(CDC& cMemDc,const CRect& rcDrawOnRect,int nRowID,int nColumnID);	
	BOOL SaveItemRectToMap(int rowID,int columnID,const CRect& rcRect);//*
	void SaveGridLineToVec(int nStartPointX,int nStartPointY,int nEndPointX,int nEndPointY);
	void SetFocusHeadItem(const CPoint& point);
	int PtInCursorRects(const CPoint& point);
	void MoveVertLine(CPoint point);	
	ECompareResult CompareCtring(const CString& fstText,const CString& sndText);
	void BubbleSort(int iBaseOnColumnID = 0,ESortMode eSortMode = ASCENDING);
	void QuickSort(int iBaseOnColumnID = 0,ESortMode eSortMode = ASCENDING);
	void HeapSort(int iBaseOnColumnID = 0,ESortMode eSortMode = ASCENDING);
	int Partition(vector<CString>& vecBaseOnText,int nLow,int nHigh,ESortMode eSortMode);
	void QSort(vector<CString>& vecBaseOnText,int nLow,int nHigh,ESortMode eSortMode);
	void HeapAdjust(vector<CString>& vecBaseOnText,int nFirst,int nLast,ESortMode eSortMode,VEC_ROW_KEY* pKeyVec,VEC_ROW_ADDR* pAddrVec);
	int InitialRowWhichEmpty(int rowID);
	BOOL CreateGrid_Inter(int nRowCount,int nColumnCount,CWnd* pParent,const CRect& rcLocateRect = 0);
	void SetUpColumnHead_Inter(BOOL bIsSetUp = FALSE);
	BOOL SetHeadRowHeigth_Inter(int nHeigth = HEIGHT_ROW_DEFAULT);
	BOOL SetRowText_Inter(int rowID,const SCellItemArray& sRowData);
	BOOL SetColumnText_Inter(int columnID,const SCellItemArray& sColumnData);
	void GetColumnText_Inter(int columnID,vector<CString>& vecText);
	BOOL IsItemEmpty_Inter(int rowID,int columnID,VEC_ROW_KEY* pKeyVec);
	BOOL GetItemID_Inter(int& rRowID,int& rColumnID,const CPoint& point);
	BOOL GetItemRect_Inter(int rowID,int columnID,CRect& rcRect);
	
	
public:
	virtual BOOL CreateGrid(int nRowCount,int nColumnCount,CWnd* pParent,const CRect& rcLocateRect = 0);	
	virtual void ShowGridLine(BOOL bIsShow = FALSE);	
	virtual void SetUpColumnHead(BOOL bIsSetUp = FALSE);
	virtual BOOL SetFixedRowCount(int nCount = 0);
	virtual BOOL SetFixedColumnCount(int nCount = 1);
	virtual int GetShowingRowCount();//获得当前显示的行的数目 //
	virtual int GetFocusRowID();
	virtual void SetTableTitle(const CString& cstrTitleText);
	virtual void ReSetGrid();
	virtual void Clear();
	virtual void DestoryGrid();
	ECompareResult CompareData(int fstRowID,int fstColumnID,int sndRowID,int sndColumnID);
	virtual BOOL ExchangeRow(int fstRowID,int sndRowID);
	virtual void Sort(int iBaseOnColumnID = 0,ESortMode eSortMode = ASCENDING);
	virtual void SetItemFont(CFont* pFont = FONT_SYS_DEFAULT);
	virtual void SetHeadItemFont(CFont* pFont = FONT_SYS_DEFAULT);
	virtual CFont* GetItemFont();
	virtual CFont* GetHeadItemFont();
	virtual CFont* GetSysDefaultFont();

	/*标题行操作*/
	virtual BOOL SetHeadItemText(int columnID,const CString& cstrText);
	virtual BOOL SetHeadItemTextCol(int columnID,const COLORREF& colTextColor = COLOR_ITEM_TEXT_DEFAULT);
	virtual BOOL SetHeadRowHeigth(int nHeigth = HEIGHT_ROW_DEFAULT);
	virtual int GetHeadRowHeigth();
	virtual BOOL GetHeadItem(int columnID,SHeadItemInfo& sHeadItemStruct);
	virtual BOOL GetHeadItemRect(int columnID,CRect& rcRect);
	

	/*行、列操作*/
	virtual BOOL SetRowHeigth(int rowID = All_ARRAY,int nHeigth = HEIGHT_ROW_DEFAULT);
	virtual int GetRowHeigth(int rowID);

	virtual BOOL SetColumnWidth(int columnID = All_ARRAY,int nWidth = WIDTH_COLUMN_DEFAULT);
	virtual int GetColumnWidth(int columnID);

	virtual BOOL SetRowText(int rowID,const std::vector<CString> &vecText);
	virtual BOOL SetRowText(int rowID,const std::map<int,CString> &mapText);

	virtual BOOL SetColumnText(int columnID,const std::vector<CString> &vecText);
	virtual BOOL SetColumnText(int columnID,const std::map<int,CString> &mapText);

	virtual BOOL InsertRow(int rowID = LAST_ARRAY,int nRowHeigth = LENGTH_DEFAULT);
	virtual BOOL DeleteRow(int rowID);
	virtual BOOL InsertColumn(int columnID = LAST_ARRAY,int nColumnWidth = LENGTH_DEFAULT);
	virtual BOOL DeleteColumn(int columnID);

	virtual int GetColumnCount();
	virtual int GetRowCount();	


	/*单元格操作*/
	virtual BOOL SetItem(int rowID,int columnID,const SCellItem& rItem);
	virtual BOOL GetItem(int rowID,int columnID,SCellItem& rItem);
	virtual BOOL IsItemEmpty(int rowID,int columnID);
	virtual BOOL ClearItem(int rowID,int columnID);

	virtual BOOL SetItemText(int rowID,int columnID,const CString& cstrText);
	virtual BOOL GetItemText(int rowID,int columnID,CString& cstrText);

	virtual BOOL SetItemTextColor(int rowID,int columnID,const COLORREF& colTextColor = COLOR_ITEM_TEXT_DEFAULT);
	virtual BOOL GetItemTextColor(int rowID,int columnID,COLORREF& colTextColor);

	virtual BOOL SetItemBkColor(int rowID,int columnID,const COLORREF& colBkColor = COLOR_ITEM_BK_DEFAULT);
	virtual BOOL GetItemBkColor(int rowID,int columnID,COLORREF& colBkColor);

	virtual BOOL GetItemID(int& rRowID,int& rColumnID,const CPoint& point);
	virtual BOOL GetItemRect(int rowID,int columnID,CRect& rcRect);


	/*用户自定义扩展操作*/
	virtual BOOL SetRowData(int rowID,DWORD_PTR pRowData);
	virtual DWORD_PTR GetRowData(int rowID);

	virtual void OnMHeadItemLClick(int columnID);
	virtual void OnMDataItemLDbClick(int rowID,int columnID);
	virtual void OnPaintHeadItem(CDC& cMemDc,const CRect& rcDrawOnRect,int columnID);
	virtual void OnPaintDataItem(CDC& cMemDc,const CRect& rcDrawOnRect,int rowID,int columnID);	
};


