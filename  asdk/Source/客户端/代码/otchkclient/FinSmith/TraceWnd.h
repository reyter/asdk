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
		unsigned int nVolumeCount;//�ü�λ���ܽ�����
		unsigned int nBuyVolumeCount;	//�ü�λ�Ĺ�������
	}SVolumeStatisticByPrice;

	typedef struct SColumnInfo
	{
		unsigned int nColumnCount;//����
		unsigned int nColumnWidth;//�п�
		unsigned int nRectItemCountOFColumn;//ÿһ�еĵ�Ԫ����Ŀ
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
	CString m_strStockCode;//��Ʊ����
	TickUnit * m_pTick;
	int		m_nMaxTick;
	int		m_nValidTick;
	EDlgViewMode m_eViewMode;//���ڵ���ʾ״̬
	unsigned int m_nDetailStyle;//������ϸ����
	unsigned int m_nYesterdayClosingPrice;//�������̼�
	int m_nMinColumnWidth;//��С�п��	

	MAP_PRICE_VOLUME_STATISTIC m_mapPriceStatistic;//�۸�ͳ����Ϣ��������
	std::vector<unsigned int> m_vMapKey;//����m_mapPriceStatistic�ļ�ֵ
	unsigned int m_nMapKeyVecSize;//m_mapPriceStatistic�ļ�ֵ������
	unsigned int m_nMaxVolumeCount;//�Լ۸����ֵ��������

	/*��ҳ����ʾ*/
	EKeyMessage m_eKeyMessage;//���̵ķ�ҳָ��
	bool m_bFilledFirstPage;//��ҳ�Ƿ��Ѵ���
	unsigned int m_nPageNum;//��ǰҳ��
	unsigned int m_nPageCount;//��ҳ��
	unsigned int m_iBeginPosIndex;//������ʾ����±꣬�տ�
	unsigned int m_iEndPosIndex;//������ʾ�յ��±꣬�տ�
	unsigned int m_nRectItemCount;//ÿҳ�ĵ�Ԫ����Ŀ������ҳ��ʾ��
	
	CString m_cstrPageTitle;//ҳ�����
	CString m_cstrColumnTitle;//�б���
	CString m_cstrTmpString;//���ڽ�����Ϣ���ݸ�ʽת�������ر�����
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


