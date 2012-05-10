#ifndef CHARTUNIT_H
#define CHARTUNIT_H
#include "atltypes.h"

typedef enum {AIXNORMAL=0,AIXLG} AixType;//��������
typedef enum {CUTrend=0,CUTrendVol,CUKLine,CUVOL,CULink,CUPoint,CUTick,CUTickLine,CUQCT,CUCOMMQCT,CUCOMMQCTATTACH,CUTDBUY,CUTDSELL} ChartUnitType;
typedef enum {RTZERO=0, RTMIN,RTMID,RTMAX} ReferType;//����
typedef enum {STNULL=0,STMARKETKUANDU,STMARKETGUANGDU,STBOLL,STEMA,STMA,STZLMM,STRSI,STTD,STMMA,STMMC,STTDMA,STBSP,STZF}	SpecialType;//��������

class ChartUnit
{
public:
     ChartUnit();
    ~ChartUnit();

	void setSpecialType(SpecialType);//�������ͣ����г����
	SpecialType getSepcialType();
    void setChartUnitType(ChartUnitType c_cuType);
	ChartUnitType getUnitType();
    void setRefer(ReferType c_rt,int c_nValue);
    void getMaxMinValue(int &c_nBegin,int &c_nMax,int &c_nMin);
    void setMaxMinValue(int c_nMax,int c_nMin,float c_fMax,float c_fMin);
    void setDrawRect(CRect c_rect);    
    void setTitle(CString c_strTitle);
    void setLineColor(COLORREF c_colorRef);
	void setLineWidth(int);
	void setPenStyle(int);
    void setCell(int c_nWidth,int c_nSpace);
    void setData(char * c_pData,int c_nDataLen,bool c_bToFree);
	void setBz(short * c_psBz);
	void setTDPoint(int *,int*);
	void setParam(CString str);
	void setParam(int);
	CString getParamString();
	int  getParamInt();
    void setViewProperty(int c_nCount,int *c_pnHoriValue,int c_nDataBegin,int c_nDataBeginTime,int c_nDataCount);
    void drawChartUnit(CDC * c_pDC);//����ͼ��
    void drawLinkLine(CDC * c_pDC,int c_nCount,int *c_pnVertValue,COLORREF c_cl);//����������
	void drawTick(CDC * c_pDC,int c_nCount,int *c_pnVertValue,COLORREF c_cl,COLORREF);//����Tick
    void drawTrend(CDC * c_pDC);//����������ͼ��
    void drawTrendVol(CDC * c_pDC);//��������ͼ�ĳɽ���
    void drawKLine(CDC * c_pDC);//����K��	
	void drawTradeArea(CDC * c_pDC,int c_nDays,int c_n5Up,int c_n5Down,int c_n1Up,int c_n1Down);//���ƽ�������
	void drawPrice(CDC * c_pDC,int c_nNowPrice,int c_nPrice,int c_nCreatePrice,CString c_strInfo,CRect &c_rectInfo);
	void drawPriceRight(CDC * c_pDC,int c_nNowPrice,int c_nPrice,CString c_strInfo);
	void drawCutAlert(CDC * c_pDC,int c_nFDown,int c_nFUp);//ֹ����
	void drawKLineAttach(CDC * c_pDC);//���Ƶ�����
    void drawVol(CDC * c_pDC);//���Ƴɽ���
    void drawTitle(CDC * c_pDC,CRect &c_rect);
    void drawRefer(CDC * c_pDC);
	void drawXCoord(CDC * c_pDC,CRect c_rectAxis,int c_nLoopMax);

	int getTimeByPos(int c_nPos);//����λ��ȡʱ��
	int getPosByTime(int c_nTime);//����ʱ��ȡλ��

	//����������
	void drawSJX(CDC * c_pDC,CPoint c_ptPoint,bool c_bUP,int c_nDis=10);
	
	void calcPerY();
    void calcVertPos(int *c_pnValue,int c_nCount,int *c_pnVert,ReferType c_rtType,int c_nReferValue);
    int getYValueInt(int c_nY);
	int getYValueInt(int &c_nX,int c_nY);
    CString getYValueString(int c_nY,int c_nMax=0);
	CString getYValuePercentString(int c_nY);
    int getValuePos(int c_nValue);
	CString getXValueString(int c_nPos,unsigned short c_usCycle);
	
    bool isSelected(int c_nPos,int c_nValue,CPoint c_pt);
    void setPrecision(int c_nPrecision);
    void setMultiplier(int c_nMultipier);
	void setDiv(int c_nDiv);

	void SetCurPos(int c_nPos,int c_nPosTime);
	void GetValueString(CString &c_strValue);

	int getXByPos(int c_nPos);
	int getPosByX(int c_nX);

	void setIsIndex(bool);
	void setFixedMaxMinValue(int c_nFixedMax,int c_nFixMinValue);
	void setDrawSingle(bool c_bIsSingle);
	bool isDrawSingle();

	void setDrawReferValue(bool);
	void SetAixType(AixType);
	AixType GetAixType();
	void SetPreClose(int);
	void ResetPriceAlertX()
	{
		m_nPriceAlertX = m_rectDraw.left;
	}

	int GetCurPos(){return m_nCurPos;};
	int GetCurPosTime(){return m_nCurPosTime;};
	int GetBeginPos(){return m_nDataBeginPos;};
	int GetBeginPosTime(){return m_nDataBeginPosTime;}
private:
    int m_nDataBeginPos;//���ݿ�ʼλ��
	int m_nDataBeginPosTime;//��ʼʱ��
	int m_nCurPos;
	int m_nCurPosTime;//��ǰλ��ʱ��
public:
	SpecialType m_nSpecialType;//��������
    ChartUnitType m_cuType;//ͼ������
    CString m_strTitle;//����
    CRect m_rectTitle;//��������
    ReferType m_rtType;//����
	CString m_strParam;//����
	bool m_bDrawReferValue;//�Ƿ���Ʋ���ֵ
    int m_nReferValue;//����ֵ
	int m_nZeroY;//0��
	int m_nPreClose;//��������
	int m_nBeginValue;//��ʼֵ
    int m_nMaxValue;//���ֵ
    int m_nMinValue;//��Сֵ
    int m_nCellWidth;//��Ԫ���
    int m_nCellSpace;//��Ԫ����
    int m_nHoriCount;//ˮƽ��������

    int m_nDataCount;//��Ч��
    int *m_pnHoriPoint;//ˮƽ��
    char * m_pData;//�ڵ�����
    int m_nDataLen;//���ݳ���
	short * m_psBz;//��־λ
	int *m_pnTDPointHigh;
	int *m_pnTDPointLow;
	bool m_bToFree;//�����Ƿ�Ҫ�ͷ�
    CRect m_rectDraw;//����ͼ������
    unsigned int m_clLine;//�ߵ���ɫ
    bool m_bSelected;//ѡ��
    int m_nPrecision;//����
    int m_nMultiplier;//����
	int m_nDiv;//����
    float m_fPerY;
	int m_nPenStyle;
	int m_nLineWidth;

	int m_nFixedMaxValue;//�̶����ֵ
	int m_nFixedMinValue;//�̶���Сֵ
	bool m_bDrawSingle;//�����������������߷�����ϵ

	bool m_bIsIndex;

	AixType m_atType;//��������

	int m_nPriceAlertX;//�۸���ʾ�����Xλ��
	ChartUnit * m_pMainUnit;

	int m_nPriceLines[16];//�۸��λ��0X7FFFFFFFΪ��Ч�����16���۸���
};
#endif // CHARTUNIT_H
