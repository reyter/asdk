///////////////////////////////////////////////////////////////////
// ��� ��Ƶ���� API ���ݽṹ����
// 2009.12.8
// ���ڴ���Ƽ����޹�˾
///////////////////////////////////////////////////////////////////
// ���м۸�ʹ��int,����С��4λ, ����:10.75��ʾΪ107500
// IOPV����ϢҲʹ��int,����С��4λ
///////////////////////////////////////////////////////////////////

#ifndef _HDBAPIDEFINE_H_
#define _HDBAPIDEFINE_H_

#ifndef _WINDOWS
#define __int64 longlong
#endif

#pragma pack(push,1)

//�������Ͷ���
#define ID_HDBTELE_LOGIN			1		//��¼��Login��
#define ID_HDBTELE_LOGINANSWER		2		//��¼Ӧ��
#define ID_HDBTELE_LOGOUT			3		//�ǳ���Logout��

//��������
#define ID_HDBTELE_REQCODETABLE		100		//��������
#define ID_HDBTELE_REQKDATA			101		//����K������
#define ID_HDBTELE_REQTICKDATA		102		//����Tick����
#define ID_HDBTELE_REQSAVEDATA		103		//����L2����
#define ID_HDBTELE_REQBASEDATA		120		//�����������
#define ID_HDBTELE_REQHZB			130		//����������ϻ��ܱ�
#define ID_HDBTELE_REQMARKETDATA	200		//������ʷ��������
#define ID_HDBTELE_CANCEL			300		//�жϴ���

//����Ӧ��
#define ID_HDBTELE_COCDETABLE		1000	//֤��������(Security Directory)
#define ID_HDBTELE_DAYKDATA			1010	//K������
#define ID_HDBTELE_DAYKDATA_INDEX	1011	//K������
#define ID_HDBTELE_TICKKDATA		1020	//Tick����
#define ID_HDBTELE_TICKKDATA_AB		1022	//Tick����
#define ID_HDBTELE_TICKKDATA_INDEX	1023	//Tick����
#define ID_HDBTELE_TICKKDATA_ACC		1024	//Tick����(���ۼƳɽ������ۼƳɽ���)
#define ID_HDBTELE_TICKKDATA_AB_ACC		1025	//Tick����(���ۼƳɽ������ۼƳɽ���)
#define ID_HDBTELE_TICKKDATA_INDEX_ACC	1026	//Tick����(���ۼƳɽ������ۼƳɽ���)



#define ID_HDBTELE_TRANSACTION		1030	//��ʳɽ�(Transaction)
#define ID_HDBTELE_ORDERQUEUE		1031	//ί�ж���(Queue)
#define ID_HDBTELE_ORDER			1035	//���ί��(Order)
#define ID_HDBTELE_BROKERQUEUE		1036	//���Ͷ���(�۹�)
#define ID_HDBTELE_BASEDATA_FP		1200	//��������-���䷽��
#define ID_HDBTELE_HZB_BASE			1300	//�������ϻ��ܱ�-������Ϣ
#define ID_HDBTELE_MARKETDATA		2000	//��ʷ����

//֤ȯ���Ͷ���/////////////////////////////////////////////////////////////////////////
//֤ȯ�������ඨ��
#define ID_BASECLASS_INDEX		0x00	//ָ��
#define ID_BASECLASS_SHARES		0x10	//��Ʊ
#define ID_BASECLASS_FUND		0x20	//����
#define ID_BASECLASS_BOND		0x30	//ծȯ & ��תծ
#define ID_BASECLASS_REPO		0x40	//�ع�
#define ID_BASECLASS_QZ			0x60	//Ȩ֤
#define ID_BASECLASS_FUTURES	0x70	//�ڻ�
#define ID_BASECLASS_FOREX		0x80	//���
#define ID_BASECLASS_BANKRATE	0xd0	//��������
#define ID_BASECLASS_NMETAL		0xe0	//�����(noble metal)
#define ID_BASECLASS_OTHER		0xf0	//����

//֤ȯ��չ���ඨ��
#define ID_BTEX_HASWARRANT		0x80000000	//����(��Ȩ֤�Ĺ�Ʊ)
//֤ȯ�������ඨ��(ϸ��)
#define ID_BT_INDEX				0x01	//������ָ��
#define ID_BT_INDEX_ASIA		0x03	//����ָ��
#define ID_BT_INDEX_FOREIGN		0x04	//����ָ��
#define ID_BT_INDEX_HH			0x05	//ϵͳ����ָ��
#define ID_BT_INDEX_USER		0x06	//�û�����ָ��
#define ID_BT_INDEX_MD			0x08	//ָ���ֻ�
#define ID_BT_SHARES_A			0x10	//A��
#define ID_BT_SHARES_S			0x11	//��С���
#define ID_BT_SHARES_G			0x12	//��ҵ���
#define ID_BT_SHARES_B			0x16	//B��
#define ID_BT_SHARES_H			0x17	//H��(��������е�A�ɣ�2008.12.4Ϊ�Ϻ�Level2����H������)
#define ID_BT_SHARES_US			0x1a	//US
#define ID_BT_SHARES_USADR		0x1b	//US ADR
#define ID_BT_SHARES_E			0x1e	//��չ����Ʊ(��)
#define ID_BT_FUND				0x20	//����
#define ID_BT_FUND_OPEN			0x21	//δ���п��Ż���
#define ID_BT_FUND_LOF			0x22	//���п��Ż���
#define ID_BT_FUND_ETF			0x23	//�����Ϳ���ʽָ������
#define ID_BT_FUND_ETS			0x25	//��չ������(��)
#define ID_BT_BOND_NA			0x30	//����ծȯ
#define ID_BT_BOND_CORP			0x31	//��ҵծȯ
#define ID_BT_BOND_FIN			0x32	//����ծȯ
#define ID_BT_BOND_CON			0x33	//��תծȯ
#define ID_BT_REPO_NA			0x40	//��ծ�ع�
#define ID_BT_REPO_CORP			0x41	//��ծ�ع�
#define ID_BT_QZ				0x60	//Ȩ֤
#define ID_BT_QZ_C				0x61	//�Ϲ�Ȩ֤
#define ID_BT_QZ_P				0x62	//�Ϲ�Ȩ֤
#define ID_BT_QZ_C_B			0x64	//�Ϲ�Ȩ֤(B��)
#define ID_BT_QZ_P_B			0x65	//�Ϲ�Ȩ֤(B��)
#define ID_BT_QZ_M				0x66	//ţ֤��moo-cow��
#define ID_BT_QZ_B				0x67	//��֤��bear��

#define ID_BT_FUTURES_IDX		0x70	//ָ���ڻ�
#define ID_BT_FUTURES			0x71	//��Ʒ�ڻ�
#define ID_BT_FUTURES_SHA		0x72	//��Ʊ�ڻ�
#define ID_BT_FUTURES_IBOR		0x73	//ͬҵ��������ڻ�
#define ID_BT_FUTURES_EFN		0x74	//Exchange Fund Note Futures
#define ID_BT_FUTURES_CX_IDX	0x78	//ָ���ڻ�����CX
#define ID_BT_FUTURES_CC_IDX	0x79	//ָ���ڻ�����CC
#define ID_BT_FUTURES_CX		0x7a	//��Ʒ�ڻ�����CX
#define ID_BT_FUTURES_CC		0x7b	//��Ʒ�ڻ�����CC
#define ID_BT_FUTURES_CX_SHA	0x7c	//��Ʊ�ڻ�����CX
#define ID_BT_FUTURES_CC_SHA	0x7d	//��Ʊ�ڻ�����CC

#define ID_BT_FOREX_BASE		0x80	//��������
#define ID_BT_FOREX_CROSE		0x81	//�������
#define ID_BT_FOREX_REVERSE		0x82	//�������
#define ID_BT_BANKRATE			0xd0	//��������
#define ID_BT_BANKRATE_HK		0xd1	//��������(HK)
#define ID_BT_BANKRATE_WORLD	0xd2	//��������(Interal)
#define ID_BT_NMETAL			0xe0	//�����(noble metal)
#define ID_BT_OTHERS			0xf0	//����
#define ID_BT_OTHER_SHARES_SG_A	0xf1	//A���¹��깺
#define ID_BT_OTHER_SHARES_ZF_A	0xf2	//A������
//end of ֤ȯ���Ͷ���/////////////////////////////////////////////////////////

//���ݰ�ʶ��ͷ
struct HDBDefine_MsgHead
{
	unsigned short  	sFlags;		//16�ֽ� ��ʶ��         0x5348
    unsigned short  	sDataType;	//16�ֽ� ��������	          
	int					nDataLen;	//32�ֽ� ���ݳ��ȣ�������ʶ��ͷ��
    int					nTime;		//32�ֽ� ʱ�������ȷ������HHMMSSmmmm��
    int     			nOrder;		//32�ֽ� ��ˮ�ţ�����������̫��ʱ��Ч��ÿ������˳����룩
	int					nChannel;	//ͨ���� �����ݰ�ͨ�����ͣ�ͨ�������ɶ��壩
};

//��½
struct HDBDefine_Login
{
	char chUserName[16];	//�û�����
	char chPassword[32];	//�û�����
	char chID[8];			//����
	char chMD5[32];			//����
};

//��½Ӧ��
struct HDBDefine_LoginAnswer
{
	char chInfo[64];			//��Ϣ
	int  nAnswer;				//1=��½�ɹ�������ʧ��
	int  nMarkets;				//֧���г�����
	char chMarketFlag[32][4];	//�г���־
	int  nDynDate[32];			//��̬��������
	//��Ȩ��Ϣ��������
	struct CertifucationInfo
	{
		int  nBeginDate;		//������Ȩ��ʼ����
		int  nEndDate;			//������Ȩ��ֹ����
	}CertiDate[12];
};

///1.1 ֤ȯ������
//�����г�����(���д��룬����ͣ��Ʒ��)
struct HDBDefine_RequestCodeTable
{
	char chMarketFlag[4];		//�г���־
};

//Ӧ�����ݰ�
struct HDBDefine_SecurityCode_Head
{
	char chMarket[4];
	int  nTotalItems;	//��������
	int  nItemSize;		//ÿ����¼��С
};

//�����
struct HDBDefine_SecurityCode
{
	char chSecurityCode[8];		//֤ȯ����
	char chSymbol[16];			//֤ȯ����
	int  nType;					//֤ȯ����
};


//1.2 ����K������
struct HDBDefine_RequestKData
{
	char chCode[8];		//֤ȯ����
	char chMarket[4];	//֤ȯ�г�(SZ,SH,PT)
	int  nFlags;		
	int  nCQFlag;		//��Ȩ��־(0:ԭʼ���� 1:��Ȩ���� 2:��Ȩ����)
	int  nCQDate;		//��Ȩ����(-1:ȫ�̸�Ȩ)
	int  nQJFlag;		//ȫ�۱�־(ծȯ)(0:���� 1:ȫ��)
	int  nCyc;			//��������(0:���� 1:���� 2:���� 3:���� 4:���� 5:������ 6:���� 7:�Զ������� 8:�Զ������� 9:�Զ�������)
	int  nCycUserDef;	//�Զ�������(nCyc=0ʱ��nCycUserDefΪ���Ӷ��壬nCyc=7ʱnCycUserDef=3��ʾ3���ߣ�nCyc=8ʱnCycUserDef=3��ʾ3���ߣ�nCyc=9ʱnCycUserDef=3��ʾ3����)
	int  nBeginDate;	//��ʼ����(-1:���������ڿ�ʼ)
	int  nEndDate;		//��������(-1:��ǰ����)
	int  nResv1;		//����
	int  nResv2;		//����
};

//K�����ݰ�ͷ
struct HDBDefine_KData_Head
{
	char chCode[8];
	char chMarket[4];
	int  nFlags;		
	int  nCQFlag;		//��Ȩ��־(0:ԭʼ���� 1:��Ȩ���� 2:��Ȩ����)
	int  nCQDate;		//��Ȩ����(-1:ȫ�̸�Ȩ)
	int  nQJFlag;		//ȫ�۱�־(ծȯ)(0:���� 1:ȫ��)
	int  nCyc;			//��������(0:���� 1:���� 2:���� 3:���� 4:���� 5:������ 6:���� 7:�Զ������� 8:�Զ������� 9:�Զ�������)
	int  nCycUserDef;	//�Զ�������(nCyc=0ʱ��nCycUserDefΪ���Ӷ��壬nCyc=7ʱnCycUserDef=3��ʾ3���ߣ�nCyc=8ʱnCycUserDef=3��ʾ3���ߣ�nCyc=9ʱnCycUserDef=3��ʾ3����)
	int  nItemSize;		//ÿ����¼��С
	int  nItems;		//������������
	int  nResv;			//����
	int  nOverFlag;		//������־(1:������ϣ�0:������һ�����ݰ�, -1:��ʾû����Ȩ���߲�����Ȩ����)
};
//K�����ݽṹ
struct HDBDefine_KData
{
	int     nDate;		//����
	int     nTime;		//ʱ��
	int		nOpen;		//����
	int		nHigh;		//���
	int		nLow;		//���
	int		nClose;		//����
	__int64 iVolume;	//�ɽ���
	__int64	iTurover;	//�ɽ���(Ԫ)
	int	  	nMatchItems;//�ɽ�����
	int   	nInterest;	//�ֲ���(�ڻ�)��IOPV(����)����Ϣ(ծȯ)
};

struct HDBDefine_KData_Index
{
	int     nDate;		//����
	int     nTime;		//ʱ��
	int		nOpen;		//����
	int		nHigh;		//���
	int		nLow;		//���
	int		nClose;		//����
	__int64 iVolume;	//�ɽ���
	__int64	iTurover;	//�ɽ���(Ԫ)
	int	  	nMatchItems;//�ɽ�����
	int   	nStocks;	//Ʒ������
	int   	nUps;		//����Ʒ����
	int   	nDowns;		//�µ�Ʒ����
	int   	nHoldLines;	//��ƽƷ����
};

//1.3 ��ʷtick����
struct HDBDefine_RequestTickData
{
	char chCode[8];
	char chMarket[4];
	int  nFlags;		//0x01:��������������
	int  nDate;			//��������
	int  nBeginItem;	//��ʼλ��
	int  nEndItem;		//����λ��(-1: ���λ��)
	int  nResv1;		//����
	int  nResv2;		//����
};

struct HDBDefine_TickData_Head
{
	char chCode[8];
	char chMarket[4];
	int  nFlags;		//0x01:��������������
	int  nDate;			//��������
	int  nTotalItems;
	int  nItemSize;		//ÿ����¼��С
	int  nBeginItem;	//���ο�ʼλ��
	int  nItems;		//������������
	int  nOverFlag;		//������־(1:������ϣ�0:������һ�����ݰ�, -1:��ʾû����Ȩ���߲�����Ȩ����)
};

struct HDBDefine_TickData
{
	int   	nTime;		//ʱ��
	int	  	nPrice;		//�ɽ���
	__int64 iVolume;	//�ɽ���
	__int64	iTurover;	//�ɽ���(Ԫ)
	int   	nMatchItems;//�ɽ�����
	int   	nInterest;	//�ֲ���(�ڻ�)��IOPV(����)����Ϣ(ծȯ)
	char   	chTradeFlag;//�ɽ���־
	char   	chBSFlag;	//BS��־
};


//���������̡����ۼƳɽ������ۼƳɽ����Tick����.
struct HDBDefine_TickData_ACC
{
	int   	nTime;		//ʱ��
	int	  	nPrice;		//�ɽ���
	__int64 iVolume;	//�ɽ���
	__int64	iTurover;	//�ɽ���(Ԫ)
	int   	nMatchItems;//�ɽ�����
	int   	nInterest;	//�ֲ���(�ڻ�)��IOPV(����)����Ϣ(ծȯ)
	char   	chTradeFlag;//�ɽ���־
	char   	chBSFlag;	//BS��־
	__int64 iAccVolume;	//�����ۼƳɽ���
	__int64	iAccTurover;//���ճɽ���(Ԫ)
};



struct HDBDefine_TickData_AB
{
	int   	 nTime;				//ʱ��
	int	 	 nPrice;			//�ɽ���
	__int64	 iVolume;			//�ɽ���
	__int64	 iTurover;			//�ɽ���
	int   	 nMatchItems;		//�ɽ�����
	int   	 nInterest;			//�ֲ���(�ڻ�)��IOPV(����)����Ϣ(ծȯ)
	char   	 chTradeFlag;		//�ɽ���־
	char   	 chBSFlag;	 		//BS��־
	int		 nAskPrice[10];		//������
	unsigned nAskVolume[10];	//������
	int		 nBidPrice[10];		//�����
	unsigned nBidVolume[10];	//������
	int		 nAskAvPrice;		//��Ȩƽ��������(�Ϻ�L2)
	int		 nBidAvPrice;		//��Ȩƽ�������(�Ϻ�L2)
	__int64  iTotalAskVolume;	//��������(�Ϻ�L2)
	__int64  iTotalBidVolume;	//��������(�Ϻ�L2)
};


//�������̡����ۼƳɽ�����Tick����.
struct HDBDefine_TickData_AB_ACC
{
	int   	 nTime;				//ʱ��
	int	 	 nPrice;			//�ɽ���
	__int64	 iVolume;			//�ɽ���
	__int64	 iTurover;			//�ɽ���
	int   	 nMatchItems;		//�ɽ�����
	int   	 nInterest;			//�ֲ���(�ڻ�)��IOPV(����)����Ϣ(ծȯ)
	char   	 chTradeFlag;		//�ɽ���־
	char   	 chBSFlag;	 		//BS��־
	__int64 iAccVolume;			//�����ۼƳɽ���
	__int64	iAccTurover;		//���ճɽ���(Ԫ)
	int		 nAskPrice[10];		//������
	unsigned nAskVolume[10];	//������
	int		 nBidPrice[10];		//�����
	unsigned nBidVolume[10];	//������
	int		 nAskAvPrice;		//��Ȩƽ��������(�Ϻ�L2)
	int		 nBidAvPrice;		//��Ȩƽ�������(�Ϻ�L2)
	__int64  iTotalAskVolume;	//��������(�Ϻ�L2)
	__int64  iTotalBidVolume;	//��������(�Ϻ�L2)
};



struct HDBDefine_TickData_Index
{
	int   	 nTime;				//ʱ��
	int	 	 nPrice;			//�ɽ���
	__int64	 iVolume;			//�ɽ���
	__int64	 iTurover;			//�ɽ���
	int   	 nMatchItems;		//�ɽ�����
	int   	 nIndex;			//����Ȩָ��
	int   	 nStocks;			//Ʒ������
	int   	 nUps;				//����Ʒ����
	int   	 nDowns;			//�µ�Ʒ����
	int   	 nHoldLines;		//��ƽƷ����
};


struct HDBDefine_TickData_Index_ACC
{
	int   	 nTime;				//ʱ��
	int	 	 nPrice;			//�ɽ���
	__int64	 iVolume;			//�ɽ���
	__int64	 iTurover;			//�ɽ���
	int   	 nMatchItems;		//�ɽ�����
	int   	 nIndex;			//����Ȩָ��
	int   	 nStocks;			//Ʒ������
	int   	 nUps;				//����Ʒ����
	int   	 nDowns;			//�µ�Ʒ����
	int   	 nHoldLines;		//��ƽƷ����
	__int64 iAccVolume;			//�����ۼƳɽ���
	__int64	iAccTurover;		//���ճɽ���(Ԫ)
};


//1.3 ��ʷLevel2����
struct HDBDefine_RequestSaveData
{
	char chCode[8];
	char chMarket[4];
	int  nFlags;
	int  nDate;			//��������
	int  nType;			//0:��ʳɽ�(�L2�۹�) 1:ί�ж���(�L2) 2:���ί��(����L2) 3:���Ͷ���(�۹�)
	int  nBeginItem;	//��ʼλ��
	int  nEndItem;		//����λ��(-1: ���λ��)
	int  nResv1;		//����
	int  nResv2;		//����
};


struct HDBDefine_SaveData_Head
{
	char chCode[8];
	char chMarket[4];
	int  nFlags;
	int  nDate;			//��������
	int  nType;			//0:��ʳɽ�(�L2�۹�) 1:ί�ж���(�L2) 2:���ί��(����L2) 3:���Ͷ���(�۹�)
	int  nTotalItems;
	int  nItemSize;		//ÿ����¼��С
	int  nBeginItem;	//��ʼλ��
	int  nItems;		//���δ��ͼ�¼��
	int  nOverFlag;		//������־(1:������ϣ�0:������һ�����ݰ�, -1:��ʾû����Ȩ���߲�����Ȩ����)
};

//1.4 �������
struct HDBDefine_Transaction
{
	int 	nTradeRef;		//�ɽ����
	int 	nTradeTime;		//�ɽ�ʱ��
	char    chTradeFlag;	//�ɽ���־
	char    chBSFlag;		//BS��־
	int		nTradePrice;	//�ɽ��۸�
	int 	nTradeVolume;	//�ɽ�����
};

//1.5 ���ί��
struct HDBDefine_Order
{
	int 	nOrderRef;		//ί�б��
	int 	nOrderTime;		//ί��ʱ��
	char    chOrderFlag;	//ί�����
	char    chBSFlag;		//ί����������
	int		nOrderPrice;	//ί�м۸�
	int 	nOrderVolume;	//ί������
};

//1.6 ��������(Queue)
struct HDBDefine_OrderQueue
{
	int 	nTime;			//�������(HHMMSS)
	int     nSide;			//��������('B':Bid 'A':Ask)
	int		nPrice;			//�ɽ��۸�
	int 	nOrderItems;	//��������
	int 	nABItems;		//��ϸ����
	int 	nABVolume[50];	//������ϸ
};

//1.7 ��ʷ��������
struct HDBDefine_RequestMarketData
{
	char chMarket[4];
	int  nFlags;
	int  nDate;			//��������
	int  nClassType;	//�������ID(����չ)
	GUID guidType;		//�������guid(����չ)
	int  nHotType;		//��������(����չ)
	int  nHotOrder;		//���з�ʽ(����չ)
	int  nResv1;		//����1
	int  nResv2;		//����2
};

struct HDBDefine_MarketData_Head
{
	char chMarket[4];
	int  nFlags;
	int  nDate;			//��������
	int  nTotalItems;	//��������
	int  nItemSize;		//ÿ����¼��С
	int  nBeginItem;	//���ο�ʼλ��
	int  nItems;		//������������
	int  nClassType;	//�������ID(����չ)
	GUID guidType;		//�������guid(����չ)
	int  nHotType;		//��������(����չ)
	int  nHotOrder;		//���з�ʽ(����չ)
	int  nResv1;		//����
	int  nResv2;		//����
	int  nResv3;		//����
	int  nOverFlag;		//������־(1:������ϣ�0:������һ�����ݰ�, -1:��ʾû����Ȩ���߲�����Ȩ����)
};

struct HDBDefine_MarketData
{
	char	chCode[8];	//֤ȯ����
	char	chName[16];	//֤ȯ����
	int   	nType;		//֤ȯ����
	int	  	nPreClose;	//ǰ����
	int	  	nOpen;		//���̼�
	int	  	nHigh;		//��߼�
	int	  	nLow;		//��ͼ�
	int	  	nPrice;		//���ɽ���
	__int64 iVolume;	//�ɽ���
	__int64	iTurover;	//�ɽ���(Ԫ)
	int   	nMatchItems;//�ɽ�����
	int   	nInterest;	//�ֲ���(�ڻ�)��IOPV(����)����Ϣ(ծȯ)
};

//��Ȩ��������(2010.1.25����)
struct HDBDefine_RequestBaseData
{
	char chCode[8];
	char chMarket[4];
	int  nFlags;
	int  nType;			//=0:��Ȩ���䷽��
	int  nBeginItem;	//��ʼλ��
	int  nEndItem;		//����λ��(-1: ���λ��)
	int  nResv1;		//����
	int  nResv2;		//����
};

struct HDBDefine_BaseData_Head
{
	char chCode[8];
	char chMarket[4];
	int  nFlags;
	int  nType;			//=0:��Ȩ���䷽��
	int  nTotalItems;
	int  nItemSize;		//ÿ����¼��С
	int  nBeginItem;	//��ʼλ��
	int  nItems;		//���δ��ͼ�¼��
	int  nOverFlag;		//������־(1:������ϣ�0:������һ�����ݰ�, -1:��ʾû����Ȩ���߲�����Ȩ����)
};

struct HDBDefine_BaseData_FP
{
	int 	nDateDJ;	//�Ǽ�����, ��Ҫ������ҵծȯ�������´μ�Ϣ����Ϣ����
	int 	nDateCQ;	//��Ȩ����
	int 	nZGB;		//������ܹɱ�(���)
	int 	nFXL;		//���������(���)
	int 	nKLT;		//��������ͨ�ɱ�(���)
	int 	nLTG;		//�������ͨ�ɱ�(���)
	int 	nYearFP;	//�������
	int  	nCQJG;		//��Ȩ�۸�
	int  	nPGJG;		//��ɼ۸�
	int		nZFJG;		//�����۸�
	float	fPXS;		//��Ϣ����
	float	fSGS;		//�͹�����
	float	fPGS;		//�������
	float	fZZGS;		//ת������
	float	fZFGS;		//��������
	char	chFPFA[64];	//���䷽��
};

//�������ϻ��ܱ�

//����������ϻ��ܱ�
struct HDBDefine_RequestHZB
{
	char chMarketFlag[4];		//�г���־
	int  nFlags;				//����
	int  nType;					//0:������Ϣ���ܱ�
};

struct HDBDefine_HZB_Head
{
	char chMarket[4];
	int  nFlags;		//����
	int	 nType;			//��������
	int  nTotalItems;	//��������
	int  nItemSize;		//ÿ����¼��С
	int  nBegin;		//��ʼ����λ��
	int  nItems;		//���δ��͸���
	int  nOverFlag;		//������־(1:������ϣ�0:������һ�����ݰ�, -1:��ʾû����Ȩ���߲�����Ȩ����)
};

struct HDBDefine_HZB_BaseInfo
{
	char	chCode[8];		//֤ȯ����
	char    chStkName[16];	//֤ȯ���
	char    chCompany[36];	//֤ȯȫ��
	char    chClass[4];		//֤�����ҵ����
	char	chExitFlag;		//���б�־
	int		nIssDate;		//��������
	int		nIssVolume;		//������
	int		nIssPrice;		////���м�
	int		nIssValue;		//������ֵ
	float	fIssProfit;		//������ӯ	//��ծȯΪ��Ϣ��
	char	chIssNote;		//���з�ʽ
	int		nListDate;		//��������	
	int		nEndDate;		//��������	//ծȯΪ������

	int		nGBFXL;			//������
	int		nGBKLT;			//����ͨ��
	int		nGBLTG;			//��ͨ��
};

#pragma pack(pop)
#endif
