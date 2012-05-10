#pragma once
#include <vector>

#define EACH_BARGAIN 1
#define EACH_PRICE   2

#define  HEIGHT_OF_EACH_RECTITEM 20
const int MIN_BARGAINBILL_DIALOG_WIDTH_BARGAIN = 800;
const int MIN_BARGAINBILL_DIALOG_WIDTH_PRICE = 650;
const int MIN_BARGAINBILL_DIALOG_HEIGTH_BARGAIN = (34+460);
const int MIN_BARGAINBILL_DIALOG_HEIGTH_PRICE = (34+300);

enum EDlgViewMode{DLG_HIDE,DLG_SHOW};
enum EKeyMessage{NONE,KEYUP,KEYDOWN};
	typedef struct SVolumeStatisticByPrice
	{
		unsigned int nVolumeCount;//该价位的总交易量
		unsigned int nBuyVolumeCount;	//该价位的购买交易量
	}SVolumeStatisticByPrice;

	typedef struct SColumnInfo
	{
		unsigned int nColumnCount;//列数
		unsigned int nColumnWidth;//列宽
		unsigned int nRectItemCountOFColumn;//每一列的单元格数目
	}SColumnInfo;

	typedef std::map<unsigned int,SVolumeStatisticByPrice> MAP_PRICE_VOLUME_STATISTIC;

// CTraceWnd

class CTraceWnd : public CWnd
{
	DECLARE_DYNAMIC(CTraceWnd)

public:
	CTraceWnd(unsigned int);
	virtual ~CTraceWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void SetStockCode(CString m_strStockCode);
	void FreshData();
	void CalcuDataBeginPosIndex(const unsigned int& nDataCount);
	void PaintBargainBillData(CDC& rCDC ,const CRect& rRect,const SColumnInfo& rColumnInfo);
	void PaintPriceStatisticData(CDC& rCDC ,const CRect& rRect,const SColumnInfo& rColumnInfo);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

private:
	CString m_strStockCode;//股票代码
	TickUnit * m_pTick;
	int		m_nMaxTick;
	int		m_nValidTick;
	EDlgViewMode m_eViewMode;//窗口的显示状态
	unsigned int m_nDetailStyle;//保存明细类型
	unsigned int m_nYesterdayClosingPrice;//昨日收盘价
	int m_nMinColumnWidth;//最小列宽度	

	MAP_PRICE_VOLUME_STATISTIC m_mapPriceStatistic;//价格统计信息保存容器
	std::vector<unsigned int> m_vMapKey;//保存m_mapPriceStatistic的键值
	unsigned int m_nMapKeyVecSize;//m_mapPriceStatistic的键值的数量
	unsigned int m_nMaxVolumeCount;//以价格区分的最大交易量

	/*翻页和显示*/
	EKeyMessage m_eKeyMessage;//键盘的翻页指令
	bool m_bFilledFirstPage;//首页是否已存满
	unsigned int m_nPageNum;//当前页码
	unsigned int m_nPageCount;//总页数
	unsigned int m_iBeginPosIndex;//数据显示起点下标，闭开
	unsigned int m_iEndPosIndex;//数据显示终点下标，闭开
	unsigned int m_nRectItemCount;//每页的单元格数目，即单页显示量
	
	CString m_cstrPageTitle;//页面标题
	CString m_cstrColumnTitle;//列标题
	CString m_cstrTmpString;//用于交易信息数据格式转换，无特别意义
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


