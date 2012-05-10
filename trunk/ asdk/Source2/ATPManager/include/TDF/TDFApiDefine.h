///////////////////////////////////////////////////////////////////
// ��� Open DataFeed API ���ݽṹ����
// ���м۸���int��ʾ����ֵΪʵ�ʼ۸�x10000
// ���磺�ɽ���Ϊ 16.80 ��ʾΪ 168000
// @System Transend Open DataFeed API (TDF)
// @Date 2010.4.21
// @Copyright ���ڴ���Ƽ����޹�˾
///////////////////////////////////////////////////////////////////
// @Author wli
// @History 
//     2010-4-21	�����ڻ�����ӿ�
///////////////////////////////////////////////////////////////////

#ifndef _TDFAPIDEFINE_H_
#define _TDFAPIDEFINE_H_

#ifndef _WINDOWS
#define __int64 longlong
#endif

#pragma pack(push,1)

//�������Ͷ���
#define ID_TDFTELE_LOGIN			1		//��¼(Login)
#define ID_TDFTELE_LOGINANSWER		2		//��¼Ӧ��
#define ID_TDFTELE_LOGOUT			3		//�ǳ�(Logout)
#define ID_TDFTELE_CLOSE			4		//�������ر�(Server Close)
#define ID_TDFTELE_COCDETABLE		6		//֤��������(Security Directory)
#define ID_TDFTELE_REQDATA			7		//������������
#define ID_TDFTELE_MARKETCLOSE		8		//������Ϣ	
#define ID_TDFTELE_TRADINGMESSAGE	9		//������Ϣ
#define ID_TDFTELE_TRANSACTION		1101	//�ɽ�(Transaction)
#define ID_TDFTELE_ORDERQUEUE		1102	//ί�ж���(Queue)
#define ID_TDFTELE_ORDER			1103	//���ί��(Order)
#define ID_TDFTELE_ORDERQUEUE_FAST	1104	//ί�ж���(FAST Queue)
#define ID_TDFTELE_MARKETDATA		1012	//��������(Market Data)
#define ID_HDFTELE_MARKETDATA_FUTURES	1016	//�ڻ���������(Futures Market Data)	1016
#define ID_TDFTELE_INDEXDATA		1113	//ָ��(Index)
#define ID_TDFTELE_MARKETOVERVIEW	1115	//�г��ſ�(Market Overview)


#define ID_TDFTELE_ADDCODE			2001	//��Ӵ���.


struct TDFDefine_MsgHead
{
	unsigned short  	sFlags;		//16�ֽ� ��ʶ��(0x5340)
    unsigned short  	sDataType;	//16�ֽ� ��������	          
	int					nDataLen;	//32�ֽ� ���ݳ���
    int					nTime;		//32�ֽ� ʱ�������ȷ������HHMMSSmmmm��
    int     			nOrder;		//32�ֽ� ��ˮ��
};

struct TDFDefine_Login
{
	char chUserName[16];
	char chPassword[32];
	char chID[8];
	char chMD5[32];
};

struct TDFDefine_LoginAnswer
{
	char chInfo[64];			//��Ϣ
	int  nAnswer;				//1:��½�ɹ�
	int  nMarkets;
	char chMarketFlag[32][4];	//�г���־
	int  nDynDate[32];			//��̬��������
};

struct TDFDefine_RequestCodeTable
{
	char chMarketFlag[4];		//�г���־(SZ;SH;HK;CF)
	int  nDate;					//�������ڣ�-1:��ʾ��̬���ݣ�
};

#define ID_HDFDATAFLAGS_RETRANSALTE			0x00000001	//���ݴӿ�ʼ����
#define ID_HDFDATAFLAGS_NOTRANSACTION		0x00000100	//��������ʳɽ�����
#define ID_HDFDATAFLAGS_NOABQUEUE			0x00000200	//������ί�ж�������
#define ID_HDFDATAFLAGS_NOINDEX				0x00000400	//������ָ������
#define ID_HDFDATAFLAGS_NOMARKETOVERVIEW	0x00000800	//������ Market OverView ����
#define ID_HDFDATAFLAGS_NOORDER				0x00001000	//���������ί�����ݣ�SZ-Level2��
#define ID_HDFDATAFLAGS_COMPRESSED			0x00010000	//��������ѹ��
#define ID_HDFDATAFLAGS_ABQUEUE_FAST		0x00020000	//��FAST��ʽ�ṩί�ж�������

struct TDFDefine_RequestMarketData
{
	char chMarketFlag[4];		//�г���־(SZ;SH;HK;CF)
	int  nFlags;				//��ID_HDFDATAFLAGS_����
};

///1.1.1 ֤ȯ������Security Directory��
struct TDFDefine_SecurityCodeHead
{
	int  nSource;	//������ 0:���� 2:�Ϻ�
	int  nDate;		//��������
	int  nCount;	//��������(-1:δ��Ȩ)
	int  nFlags;	//(����)
};

struct TDFDefine_SecurityCode
{
	int  nIdnum;				//���ձ��(���������*100 + ���������)
	int  nType;					//֤ȯ����
	char chSecurityCode[8];		//֤ȯ����
	char chSymbol[16];			//֤ȯ����
};

//1.1.2 ��ʳɽ�(Transaction)
struct TDFDefine_TransactionHead
{
	int 	nIdnum;			//���ձ��
	int     nItems;			//���ݸ���
};

struct TDFDefine_Transaction
{
	int 	nTime;		//�ɽ�ʱ��(HHMMSSmmmm)
	int 	nIndex;		//�ɽ����
	int		nPrice;		//�ɽ��۸�
	int 	nVolume;	//�ɽ�����
	int		nTurnover;	//�ɽ����
};

//1.1.2 ���ί��(Order)
struct TDFDefine_OrderHead
{
	int 	nIdnum;			//���ձ��
	int     nItems;			//���ݸ���
};

struct TDFDefine_Order
{
	int 	nTime;		//ί��ʱ��(HHMMSSmmmm)
	int 	nIndex;		//ί�б��
	int		nPrice;		//ί�м۸�
	int 	nVolume;	//ί������
	char    chType;		//ί�����
	char    chBSFlag;	//ί����������('B','S','C')
	char    chResv[2];	//����
};

//1.1.3 ��������(Queue)
struct TDFDefine_OrderQueueHead
{
	int     nItems;			//���ݸ���
};

struct TDFDefine_OrderQueue
{
	int 	nIdnum;			//���ձ��
	int 	nTime;			//�������(HHMMSSmmmm)
	int     nSide;			//��������('B':Bid 'S':Ask)
	int		nPrice;			//�ɽ��۸�
	int 	nOrders;		//��������
	int 	nABItems;		//��ϸ����
	int 	nABVolume[200];	//������ϸ
};

//1.1.3.1 ��������(�Ϻ�FAST Queue)
struct TDFDefine_OrderQueue_FAST
{
	int  nIdnum;			//���ձ��
	int  nTime;				//����ʱ�䣨HHMMSS��
	int  nSide;				//��������'B':Bid 'A':Ask��
 	int  nImageStatus;		//����״̬��1-Full Image 2-Update��
	int  nNoPriceLevel;		//�����ļ�λ��
}; 

struct TDFDefine_OrderQueue_FAST_Operate
{
	int		nPriceOperate;	// 1.add , 2 Update ,3 Delete  0. absent 
	int     nPrice;			//�۸�
	int		nNumOrders;		//ί�б���
	int		nOqLevel;		//��ǰ��λ��Ҫ�����Ķ�����
};

struct TDFDefine_OrderQueue_FAST_OperateItem
{
	int nOperate;	//������ʽ: 1 Add ,2 Update,3 Delete
	int nEntryID;   //����ID:  Oreder Queue Operator Entry ID
	int nQty;		//��������
};

//1.1.4 ��������(Market Data)
struct TDFDefine_MarketDataHead
{
	int     nItems;			//���ݸ���
};

typedef TDFDefine_MarketDataHead TDFDefine_MarketDataFuturesHead;

struct TDFDefine_MarketData
{
	int		nIdnum;						//���ձ��
	int		nTime;						//ʱ��(HHMMSSmmmm)
	int		nStatus;					//״̬
	unsigned int nPreClose;				//ǰ���̼�
	unsigned int nOpen;					//���̼�
	unsigned int nHigh;					//��߼�
	unsigned int nLow;					//��ͼ�
	unsigned int nMatch;				//���¼�
	unsigned int nAskPrice[10];			//������
	unsigned int nAskVol[10];			//������
	unsigned int nBidPrice[10];			//�����
	unsigned int nBidVol[10];			//������
	unsigned int nNumTrades;			//�ɽ�����
	__int64	iVolume;					//�ɽ�����
	__int64	iTurnover;					//�ɽ��ܽ��
	__int64	nTotalBidVol;				//ί����������
	__int64	nTotalAskVol;				//ί����������
	unsigned int nWeightedAvgBidPrice;	//��Ȩƽ��ί��۸�
	unsigned int nWeightedAvgAskPrice;  //��Ȩƽ��ί���۸�
	int		nIOPV;						//IOPV��ֵ��ֵ
	int		nYieldToMaturity;			//����������
	unsigned int nHighLimited;			//��ͣ��
	unsigned int nLowLimited;			//��ͣ��
	char	chPrefix[4];				//֤ȯ��Ϣǰ׺
};

//1.1.5 ָ��(Index)
struct TDFDefine_IndexDataHead
{
	int     nItems;				//���ݸ���
};

struct TDFDefine_IndexData
{
	int		nIdnum;			//���ձ��
	int     nTime;			//ʱ��(HHMMSSmmmm)
	int		nOpenIndex;		//����ָ��
	int 	nHighIndex;		//���ָ��
	int 	nLowIndex;		//���ָ��
	int 	nLastIndex;		//����ָ��
	__int64	iTotalVolume;	//���������Ӧָ���Ľ�������
	__int64	iTurnover;		//���������Ӧָ���ĳɽ����
	int		nPreCloseIndex;	//ǰ��ָ��
};


//1.1.6 �г��ſ�(Market Overview)
struct TDFDefine_MarketOverview
{
	int		nSource;
	int		nOrigTime;			//ʱ��(HHMMSSmmmm)
	int		nOrigDate;			//����
	char	chEndOfDayMarket;	//������־
};


//f)	����(Close)
struct TDFDefine_MarketClose
{
	int		nSource;
	int		nTime;				//ʱ��(HHMMSSmmmm)
	char	chInfo[64];			//������Ϣ
};

//g)	������Ϣ֪ͨ (Trading Message)
struct TDFDefine_TradingMessage
{
	int		nIdnum;				//���ձ��
	char	chSecurityId[8];	//֤ȯ����
	char	chInfo[128];		//��Ϣ
	int		nTime;				//ʱ��(HHMMSSmmmm)
};


//�ڻ�Markets Data.
struct TDFDefine_MarketData_Futures
{
	int nIdnum;							//���ձ��
	int	nTime;							//ʱ��(HHMMSSmmmm)	
	int		nStatus;					//״̬
	__int64 iPreOpenInterest;			//��ֲ�
	unsigned int nPreClose;				//�����̼�
	unsigned int nPreSettlePrice;		//�����
	unsigned int nOpen;					//���̼�	
	unsigned int nHigh;					//��߼�
	unsigned int nLow;					//��ͼ�
	unsigned int nMatch;				//���¼�
	__int64	iVolume;					//�ɽ�����
	__int64	iTurnover;					//�ɽ��ܽ��
	__int64 iOpenInterest;				//�ֲ�����
	unsigned int nClose;				//������
	unsigned int nSettlePrice;			//�����
	unsigned int nHighLimited;		//��ͣ��
	unsigned int nLowLimited;		//��ͣ��
	int		nPreDelta;			        //����ʵ��
	int     nCurrDelta;                 //����ʵ��
	unsigned int nAskPrice[5];			//������
	unsigned int nAskVol[5];			//������
	unsigned int nBidPrice[5];			//�����
	unsigned int nBidVol[5];			//������
};

#pragma pack(pop)
#endif
