
#ifndef __QUOTE_DATA_STRUCT_H__
#define __QUOTE_DATA_STRUCT_H__
#include <vector>

#define STR_XH	_T("���")
#define STR_DM	_T("����")
#define STR_JC    _T("���")
#define STR_ZS		_T("����")
#define STR_XJ    _T("�ּ�")
#define STR_CJL   _T("�ɽ���")
#define STR_ZDF   _T("�Ƿ�")
#define STR_ZD		_T("�ǵ�")
#define STR_W_ZDF	_T("���Ƿ�")
#define STR_M_ZDF   _T("���Ƿ�")
#define STR_PJ    _T("����")
#define STR_YLYC    _T("ӯ��Ԥ��")
#define STR_M3_YLYC	_T("����ǰԤ��")
#define STR_ZRSP    _T("����")
#define STR_JRKP    _T("��")
#define STR_ZGJG   _T("���")
#define STR_ZDJG   _T("���")
#define STR_HSL    _T("����%")
#define STR_QHSL    _T("������")
#define STR_LB		_T("����")
#define STR_ZHANGSU		_T("����")
#define STR_ZF		_T("���%")
#define STR_SYL    _T("��ӯ��")
#define STR_SYLYC    _T("Ԥ����ӯ��")
#define STR_CJJE    _T("�ɽ���")
#define STR_BUY   _T("����")
#define STR_SELL   _T("����")
//#define STR_MGSY    "ÿ������"
#define STR_LTSZ    _T("��ͨ��ֵ")
#define STR_PB		_T("PB")
#define STR_PE		_T("PE")
#define STR_ZSZ    _T("����ֵ")
#define STR_JGCG	_T("�����ֹ�")
#define STR_DIAGNOSE _T("�������")
#define STR_INDUSTRYNAME	_T("��ҵ")
#define STR_WEAKSTRING_YEAR	_T("52��ǿ��")
#define STR_PJ_JG		_T("��������")
#define STR_PJ_RQ		_T("��������")
#define STR_PJ_THIS			_T("��������")
#define STR_PJ_LAST		_T("�ϴ�����")
#define STR_YC_JG		_T("Ԥ�����")
#define STR_YC_RQ		_T("Ԥ������")
#define STR_YC_THIS		_T("����Ԥ��")
#define STR_YC_LAST		_T("�ϴ�Ԥ��")
#define STR_YC_YEAR		_T("Ԥ�����")
#define STR_MBJ			_T("Ŀ���")
#define STR_MBJ_JCFD	_T("���ǿռ�")
#define STR_PJ_STR		_T("��ǰ����")
#define STR_SRZZ		_T("��������")
#define STR_YLZZ		_T("ӯ������")

#define STR_LX12YLZZ	_T("����12��ӯ������")
#define STR_WL12YLZZ	_T("δ��12��ӯ������")
#define STR_ZXJDYLZZ	_T("���¼���ӯ������")
#define STR_LX12SRZZ	_T("����12����������")
#define STR_LX12ROE		_T("����12��ROE")

#define STR_M3_ZDF		_T("�����ǵ���")
#define STR_M6_ZDF		_T("�����ǵ���")
#define STR_M12_ZDF		_T("һ���ǵ���")
#define STR_WZJLR		_T("һ���ʽ�����(����)")
#define STR_WZJLRZB		_T("һ���ʽ�����ռ��")

#define STR_JGCGBL		_T("�����ֹɱ���")
#define STR_JGCGBL_LAST		_T("���ڳֹɱ���")
#define STR_SZKJ		_T("���ǿռ�")
#define STR_FXSQXZS		_T("����ʦ����ָ��")

#define STR_INDUSTRY_WEAKSTRONG	_T("��ҵǿ��")
#define STR_INDUSTRY_SORT		_T("��ҵ��������")

#define STR_DIAGNOSE_QUICK_BTN	_T("���ժҪ")
#define STR_CHANGE_STOCK_BTN	_T("����")

#define STR_GROUP_STOCK_VOLUME				_T("����")
#define STR_GROUP_STOCK_AVGPRICE			_T("����")
#define STR_GROUP_STOCK_VALUE			_T("��ֵ")
#define STR_GROUP_STOCK_INCOME			_T("ӯ��")
#define STR_GROUP_STOCK_INCOME_PER			_T("ӯ����")

#define LIST_HEIGHT		24		//����и�

#define STOCK_CODE_LEN	16
#define STOCK_NAME_LEN	64
#define STOCK_SPELL_LEN 4
#define STOCK_KIND_LEN	16
#define STOCK_PYDM_LEN	6
#define TICK_PERBLOCK	120
#define MINK_PERBLOCK	60
#define QUOTEHEAD		(STOCK_CODE_LEN+STOCK_NAME_LEN)
#define QUOTETAIL		(STOCK_KIND_LEN+sizeof(unsigned int)*4)

#define DIALOG_BNK_COLOR        RGB(230, 240, 255)
#define BORDER_COLOR            RGB(150, 166, 192)//�߿�ɫ

#define WM_REQUEST_INFO			WM_USER + 50	//��ȡ��ǰ�û�ID����ʱͨѶ���������˿�

#define WM_UPDATE_QUOTEDATA		WM_USER + 101//�������ݸ���

#define WM_CONNECT_SUCCESS		WM_USER + 102//���ӳɹ�
#define WM_UPDATE_NEWSSET		WM_USER + 103//������Ѷ����

#define WM_ENTER_KEY				WM_USER + 127//���˻س���

#define WM_EXTRA_COMMAND		WM_USER + 200	//���͸����������

#define WM_ALERT_INFO			WM_USER + 201	//��Ϣ��ʾ����
#define WM_UPDATE_RUN_INFO		WM_USER + 202	//�����
#define WM_PERSONAL_SET			WM_USER + 203	//���Ի�����
#define WM_SHORT_START          WM_USER + 205
#define WM_CREATE_LISTCTRL_INI  WM_USER + 206
#define WM_CANCEL_ALERT         WM_USER + 207
#define WM_SET_INFO_CLOSE       WM_USER + 208
#define WM_SET_INFO_STOCK       WM_USER + 209
//#define WM_COLUMNSORT           WM_USER + 207


#define WM_LOG_SUCCESS			WM_USER + 210	//��½�ɹ�
#define WM_LOG					WM_USER + 212	//���µ�½
#define WM_DATA_PROGRESS		WM_USER + 213	//���ݽ���
#define WM_SHOW_NEWS			WM_USER + 214	//��ʾ����
#define WM_GOTO_STOCK			WM_USER + 217
#define	WM_SWITCH_PIC_TYPE		WM_USER + 218	//�л�Trend->Hisk,Hisk->Trend

#define WM_FORCE_QUIT			WM_USER + 215	//ǿ���˳�

#define WM_ADD_STOCK_TO_GROUP	WM_USER + 216	//���ӹ�Ʊ����ѡ�����

#define WM_CONTAINER			WM_USER + 219

#define WM_ADD_STOCK_TO_PIC		WM_USER + 220	//����K��

#define WM_GET_NEWSWND			WM_USER + 221	//ȡһ�����Ŵ���

#define WM_GROUP_CHANGED		WM_USER + 222	//������ݸ�����

#define WM_CHANGE_VIEWMODE		WM_USER + 223	//�л���ʾģʽ

#define WM_OPEN_TECH_FILE		WM_USER + 224	//�򿪼���ͼ���ļ�
#define CONTAINER_MIN			1
#define CONTAINER_MAX			2
#define CONTAINER_HIDE			3

const unsigned int		CREATE_GROUP_COMMAND = 101;	//�������
const unsigned int		ADD_STOCK_COMMAND = 102;		//������ѡ��
const unsigned int		INFO_SET_SUCCESS = 103;	//�����Լ�ѡ���
const unsigned int		PERSONAL_SET_COMMAND = 104;		//���Ƹ��Ի�
const unsigned int      CREATE_INI = 105;
const unsigned int      GROUP_OPERATE = 106;
const unsigned int      NEWS_OPERATE = 107;
const unsigned int		BUY_STOCK = 108;		//�����Ʊ
const unsigned int		SALE_STOCK = 109;		//������Ʊ
const unsigned int		PIC_2_STOCK = 110;		//ͼ�αȽ�


const unsigned int		VIEW_GROUP_NEWS = 122;	//��ʾ�������
const unsigned int		VIEW_INDUSTRY_NEWS	= 123;//��ʾ��ҵ����
const unsigned int		VIEW_STOCK_NEWS	= 124;//��ʾ��������
const unsigned int		GOTO_NEXT_STOCK = 125;//ȥ��һ֧��Ʊ
const unsigned int		GOTO_LAST_STOCK = 126;//ȥ��һ֧��Ʊ


//const unsigned int      SET_NEW_OPEN = 109;
//const unsigned int      SET_INFO_CLOSE = 110;

const unsigned int		SHOW_GROUP_WINDOW = 120;	//��ʾ��ϴ���
const unsigned int		SHOW_INFO_WINDOW = 121;		//��ʾ��Ѷ����
const unsigned int		SHOW_F10		= 127;		//��ʾF10��Ϣ
const unsigned int		SHOW_STOCKS		= 128;		//����
const unsigned int	    SHOW_GORUP		= 129;		//��ʾ���

const unsigned int		SHOW_SENDMSG	= 130;		//������Ϣ
const unsigned int		SHOW_TRADEWND	= 131;		//��ʾ���״���
const unsigned int		SHOW_TRACEWND	= 132;		//�ֱʴ���
const unsigned int		SHOW_TRACEPRICEWND = 133;	//�ֱʼ۸񴰿�
const unsigned int		ESCAPE_TRACEWND	= 134;		//�����ֱʴ���
const unsigned int		ESCAPE_TRACEPRICEWND	= 135;		//�����ֱʼ۸񴰿�

const unsigned int		STOCK_FROM_GROUP = 150;		//�����
const unsigned int		STOCK_FROM_LIST	= 151;		//���б�
const unsigned int		STOCK_FROM_BOTTOM_LIST = 152;		//�������б�
const unsigned int		STOCK_FROM_CHANGE = 153;	//�ӻ�������

const unsigned int		VIEW_INDUSTRY_STOCKS	= 154;//��ʾ��ҵ�й�Ʊ�б�
const unsigned int		VIEW_CHANGE_STOCKS		= 155;//��ʾ���ɴ���

const unsigned int      RUN_HEIGHT = 23;
const unsigned int      ALERT_HEIGHT = 199;
const unsigned int      ALERT_WIDTH = 338;

const unsigned int      LOG_WIDTH = 500;
const unsigned int      LOG_HEIGHT = 400;

const unsigned int      TITILE_BUTTON_HEIGHT = 25;

const	unsigned short	INITDATA=0x0001;		//�г���ʼ��
const	unsigned short	INITDATANEW=0x000A;		//�г���ʼ��
const	unsigned short	TRACEDATA=0x0002;	//�ɽ���ϸ
const	unsigned short	REPORTDATA=0x0003;	//��ѡ�ɱ���
const	unsigned short	REALMINSDATA=0x0004;	//��������
const	unsigned short	HISKDAYDATA=0x0005;		//��ʷK����
const	unsigned short	HISKWEEKDATA=0x0006;		//��ʷK����
const	unsigned short	HISKMONTHDATA=0x0007;		//��ʷK����
const	unsigned short	HISKMINDATA=0x0101;			//1������
const	unsigned short	HISKMIN5DATA=0x0105;			//5������
const	unsigned short	HISKMIN15DATA=0x010F;			//15
const	unsigned short	HISKMIN30DATA=0x011E;			//30
const	unsigned short	HISKMIN60DATA=0x013C;			//60������
const	unsigned short	REALMINSDATA2=0x0008;			//���շ�ʱ
const	unsigned short	ONLINEINITDATA=0x0009;			//���߷���ʦ��ʼ��

const	unsigned short	ONLINEINITDATA_A=0x0013;			//���߷���ʦ��ʼ��A
const	unsigned short	ONLINEINITDATA_B=0x0014;			//���߷���ʦ��ʼ��B
const	unsigned short	ONLINEINITDATA_C=0x0015;			//���߷���ʦ��ʼ��C
const	unsigned short	ONLINEINITDATA_D=0x0016;			//���߷���ʦ��ʼ��D
const	unsigned short	ONLINEINITDATA_E=0x0017;			//���߷���ʦ��ʼ��E
const	unsigned short	ONLINEINITDATA_F=0x001E;			//���߷���ʦ��ʼ��F

const	unsigned short	SERVERLIST		=0x0018;			//�������б�
const	unsigned short	SENDMSG=0x0011;				//������Ϣ

const	unsigned short	ONLINEINITREQ=3011;//���߷���ʦ��ʼ��
const	unsigned short  STOCKCHANGEREQ=3014;//����
const	unsigned short  TRADEMEMOREQ=3015;//���ױ���
const	unsigned short  MARKETTECHREQ=3016;//����ָ���ʽ�
const	unsigned short  RPSTECHREQ=3017;//RPSָ��
const	unsigned short  WEAKSTRONGTECHREQ=3018;//����ָ��ǿ��
const	unsigned short	STOCKPBPEREQ = 3019;//���ɵ�PBPE��ʷ

const	unsigned short	STOCKTECHREQ = 3030;//��������,�Ժ���ɵ������ɴ˹������,�����е���������

const	unsigned short  STOCKDIAGNOSEREQ=3013;//������� 
const	unsigned short  STOCKDIAGNOSEREQNEW=3051;//������� 
const	unsigned short	STOCKBLOCKREQ=3048;//���

const	unsigned short  REPORTPARAMS=3115;	//�о��������
const	unsigned short	ANALYSTREQ=3116;	//�о�Ա

const	unsigned short	STOCKDIVIDEDREQ = 3120;//���ɷֺ���Ϣ

const	unsigned short	LINETESTREQ=0x0000;//��·���������
const	unsigned short	LINETESTREP=0x0100;//��·����Ӧ���

const	unsigned short	LISTOFUSER=0x0019;			//�����û��б�
const	unsigned short	OFFLINEUSER=0x001A;			//���û�����
const	unsigned short	ISUSERONLINE=0x001B;		//�û��Ƿ�����
const	unsigned short	REPORTURL=0x001C;			//�о�����URL
const	unsigned short	UPGRADEFILE=0x001D;			//���������ļ�

const	unsigned short	STOCKBASEDATA=0x0021;		//��Ʊ��������
const	unsigned short	COLLECTSORT=0x0022;			//�ۺ�����
const	unsigned short	USERDEFREPORTDATA=0x0023;	//�Զ��屨�۱�
const	unsigned short	QUOTESORTDATA=0x0024;		//��׼���а�
const	unsigned short	INVEST66SORT=0x0025;		//66����
const	unsigned short	INVESTINDUTOTAL=0x0026;		//��ҵͳ��
const	unsigned short	BESTSTOCKS=0x0027;			//������

const	unsigned short	MACRODATA=0x0028;			//�������
const	unsigned short	STOCKTRADEDATA=0x0029;			//��Ʊ��������
const	unsigned short	STOCKSELECTDATA=0x0030;		//��Ʊ��ѡ����
const	unsigned short	TABLEDATA=0x0031;			//�Զ����ֶ�����,MACRODATAָ���������ͣ��ڷ����ת�����ֶ�
const	unsigned short	BUYSALELIST=0x0032;			//��������
const	unsigned short	REALPUSHREQ=0x1000;	//��������

#define REAL_PUSH_REQ					4096	//��������

#define ID_URL_PERSONAL_SET				101	//���Ի�����
#define ID_URL_NEWS_SET					102 //��Ѷ����
#define ID_URL_STOCK					103 //����
#define ID_URL_NEWS						104 //��Ѷ
#define ID_URL_SERVICE					105 //����
#define ID_URL_INDEX					106 //ָ��

//Ȩ��
#define	ROLE_YJBG						0x0001		//�о�����
#define ROLE_YJBG_HZ					0x0002		//��������
#define ROLE_YJBG_FHZ					0x0004		//�Ǻ�������
#define ROLE_HLDXG						0x0008		//���̵�ѡ��
#define ROLE_LEDS_HIST					0x0010		//���̵���ʷ
#define ROLE_LEDS_CHANGE				0x0020		//���̵Ʊ仯
#define ROLE_ALERT						0x0040		//����Ԥ��
#define ROLE_PRICE_ALERT				0x0080		//�۸���ʾ
#define ROLE_MARKET_RADA				0x0100		//�г��״�
#define ROLE_TRADE_AREA					0x0200		//��������
#define ROLE_CUT_LINE					0x0400		//ֹ����
#define ROLE_MACRO_DATA					0x0800		//�������
#define ROLE_NBJY						0x1000		//�ڲ�����
#define	ROLE_JGMM						0x2000		//��������



/// ��������Դ���͹��������ݵ��б�־
#define  FD_ZRSP                 1
#define  FD_JRKP                 2
#define  FD_ZJCJ                 3
#define  FD_CJSL                 4
#define  FD_CJJE                 5
#define  FD_CJBS                 6
#define  FD_ZGCJ                 7
#define  FD_ZDCJ                 8
#define  FD_SYL1                 9
#define  FD_SYL2                10
#define  FD_JSD1                11
#define  FD_JSD2                12
#define  FD_HYCC                13
#define  FD_SJW5                14
#define  FD_SSL5                15
#define  FD_SJW4                16
#define  FD_SSL4                17
#define  FD_SJW3                18
#define  FD_SSL3                19
#define  FD_SJW2                20
#define  FD_SSL2                21
#define  FD_SJW1                22
#define  FD_SSL1                23
#define  FD_BJW1                24
#define  FD_BSL1                25
#define  FD_BJW2                26
#define  FD_BSL2                27
#define  FD_BJW3                28
#define  FD_BSL3                29
#define  FD_BJW4                30
#define  FD_BSL4                31
#define  FD_BJW5                32
#define  FD_BSL5                33
#define  FD_XXJYDW				34
#define  FD_XXMGMZ				35
#define  FD_XXZFXL				36
#define  FD_XXLTGS				37
#define  FD_XXSNLR				38
#define  FD_XXBNLR				39
#define  FD_XXJSFL				40
#define  FD_XXYHSL				41
#define  FD_XXGHFL				42
#define  FD_XXMBXL				43
#define  FD_XXBLDW				44
#define  FD_XXSLDW				45
#define  FD_XXJGDW				46
#define  FD_XXJHCS				47
#define  FD_XXLXCS				48
#define  FD_XXXJXZ				49
#define  FD_XXZTJG				50
#define  FD_XXDTJG				51
#define  FD_XXZHBL				52


#define QFD_STOCKCODE	1
#define QFD_STOCKNAME	2
#define QFD_ZRSP		3
#define QFD_JRKP		4
#define QFD_ZTJG		5
#define QFD_DTJG		6
#define QFD_SYL1		7
#define QFD_SYL2		8
#define QFD_ZGJG		9
#define QFD_ZDJG		10
#define QFD_ZJJG		11
#define QFD_ZJCJ		12				
#define QFD_CJSL		13
#define QFD_CJJE		14
#define QFD_CJBS		15
#define QFD_BP1			16
#define QFD_BM1			17
#define QFD_BP2			18
#define QFD_BM2			19
#define QFD_BP3			20
#define QFD_BM3			21
#define QFD_BP4			22
#define QFD_BM4			23
#define QFD_BP5			24
#define QFD_BM5			25
#define QFD_SP1			26
#define QFD_SM1			27
#define QFD_SP2			28
#define QFD_SM2			29
#define QFD_SP3			30
#define QFD_SM3			31
#define QFD_SP4			32
#define QFD_SM4			33
#define QFD_SP5			34
#define QFD_SM5			35
#define QFD_5RPJZS		36
#define QFD_PJJG		37
#define QFD_WB			38
#define QFD_LB			39
#define QFD_NP			40
#define QFD_WP			41
#define QFD_ZDF			42
#define QFD_ZF			43

#pragma pack(1)
//����ṹ
struct Quote
{
	int	nStockId;						//Id
	char szStockCode[STOCK_CODE_LEN];	//Ʒ�ִ���
	char szStockName[STOCK_NAME_LEN];	//��Ʊ���
	unsigned int zrsp;					//����
	unsigned int jrkp;					//��
	unsigned int ztjg;					//��ͣ��
	unsigned int dtjg;					//��ͣ��
	unsigned int syl1;					//��ӯ��1
	unsigned int syl2;					//��ӯ��2
	unsigned int zgjg;					//��߼۸�
	unsigned int zdjg;					//��ͼ۸�
	unsigned int zjjg;					//����ɽ���
	unsigned int zjcj;					//����ɽ���
	unsigned int cjsl;					//�ܳɽ���
	unsigned int cjje;					//�ɽ����
	unsigned int cjbs;					//�ɽ�����
	unsigned int BP1;
	unsigned int BM1;
	unsigned int BP2;
	unsigned int BM2;
	unsigned int BP3;
	unsigned int BM3;
	unsigned int BP4;
	unsigned int BM4;
	unsigned int BP5;
	unsigned int BM5;
	unsigned int SP1;
	unsigned int SM1;
	unsigned int SP2;
	unsigned int SM2;
	unsigned int SP3;
	unsigned int SM3;
	unsigned int SP4;
	unsigned int SM4;
	unsigned int SP5;
	unsigned int SM5;

	unsigned int MBP1;
	unsigned int MBM1;
	unsigned int MBP2;
	unsigned int MBM2;
	unsigned int MBP3;
	unsigned int MBM3;
	unsigned int MBP4;
	unsigned int MBM4;
	unsigned int MBP5;
	unsigned int MBM5;
	unsigned int MSP1;
	unsigned int MSM1;
	unsigned int MSP2;
	unsigned int MSM2;
	unsigned int MSP3;
	unsigned int MSM3;
	unsigned int MSP4;
	unsigned int MSM4;
	unsigned int MSP5;
	unsigned int MSM5;

	unsigned int day5pjzs;				//5��ƽ������
	unsigned int pjjg;					//����
	int wb;								//ί��
	unsigned int lb;					//����
	unsigned int np;					//����
	unsigned int wp;					//����
	int zd;
	int zdfd;							//�ǵ���
	int zf;								//���
	//����
	int hsl;							//������
};

//�ֱʳɽ��ṹ
struct TickUnit
{
	unsigned int Time;					//ʱ�䣬��ʽ��HHMM
	unsigned int Price;					//�ɽ���
	unsigned int Volume;				//�ɽ���
	unsigned char Way;					//�ɽ�����0-δ֪��1-���̣�2-����
};

struct TickBlock
{
	TickUnit unit[TICK_PERBLOCK];
	unsigned int next;
};

//�ڴ����K�߽ṹ
struct MinUnit
{
	unsigned int Time;					//ʱ�䣬��ʽ��HHMM
	unsigned int OpenPrice;
	unsigned int MaxPrice;
	unsigned int MinPrice;
	unsigned int NewPrice;
	unsigned int Volume;
	unsigned int AvgPrice;				//����
};

struct MinBlock
{
	MinUnit unit[MINK_PERBLOCK];
	unsigned int next;
};

struct RINDEX
{
	int idxQuote;				//��������
	int idxTick;				//�ֱʳɽ�����
	int cntTick;				//�ֱʳɽ�����
	int idxMinK;				//����K������
	int cntMinK;				//����K�߸���
};

//����
struct SStock
{
	CString m_strName;	
	char m_acKind[STOCK_KIND_LEN + 1];
	char m_acSpell[STOCK_SPELL_LEN + 1];
	unsigned int m_unPrevClose;
	Quote m_sQuote;
	double m_dZgb;//�ܹɱ�
	double m_dLtg;//��ͨ��
	float	m_fRJCG;//�˾��ֹ�

	double	m_dValue;//����ֵ
	double  m_dLtValue;//��ͨ��ֵ

	int m_nMinItemCount;
	char * m_pMinData;//����
	int m_nLastMinTime;//������
	bool m_bIsMaker;//�Ƿ���ׯ��

	void init()
	{
		memset(&m_sQuote,0,sizeof(Quote));
		m_nMinItemCount = 0;
		m_pMinData = NULL;//����
		m_nLastMinTime = 0;
		m_bIsMaker = false;
	}
};

//ͨѶ��ͷ��
struct SCommHead{
	CommxHead	m_head;//��׼ͷ
	unsigned short	m_usFuncNo;//���ܱ��
	unsigned short m_usReqCount;//�����������
};
struct tagUserLogReq
{
	int			nEncrypt;
	char		acCode[64];
	char		acPass[64];
};

struct tagUserInfo
{
	int				nMemberType;//��Ա����
	unsigned int    nUserId;          //�û����
	char			szLoginCode[64];	//��½����
	char            szNickName[64];   //�ǳ�
};

struct tagChangePass
{
	int				nUserId;//�û�ID
	char			acCode[16];//����
	char			acPass[32];//������
	char			acNewPass[32];//������
	int				nType;//0��ѯ���룬1��������
};

struct tagPass
{
	int			nId;
	char		acCode[16];
	char		acPass[32];
};

struct tagAccount//�ʻ���Ϣ
{
	float		fAssets;//���ʲ�
	float		fCash;//�ֽ��ܶ�
	float		fFreezeCash;//�����ֽ�
	float		fProfit;//ӯ��
};

struct tagPosition//�ֲ�
{
	int		nStockId;
	int		nAmount;//����
	int		nFreezeAmount;//��������
	float	fCost;//�ɱ��۸�
	int		nBuyToDay;
	int		nSellToday;
};

struct tagConsign
{
	int		nOperate;//������1ί����2ί������3����
	int		nStockId;	
	int		nAmount;//����
	float	fPrice;//�۸�
	int		nConsignID;//���ڳ�����ֵΪ��������ί�к�
};

struct tagMakerConsignReq//ׯ��ί��
{
	int		nStockId;//��ƱId
	int		nBuyAmount;//��������
	float	fBuyPrice;//����۸�
	int		nSaleAmount;//��������
	float	fSalePrice;//�����۸�
	int		nType;//0׷�ӣ�1������ǰ��ί��
};

struct tagConsignHistoryReq
{
	char	acBeginDate[24];
	char	acEndDate[24];
};

struct tagConsignHistory//ί����ʷ
{
	int		nConsignID;//ί�к�
	int		nOperate;
	int		nStockId;
	int		nAmount;
	float	fPrice;
	int		nBargainAmount;
	int		nState;
	char	acDateTime[24];
};

struct tagBargainReq
{
	char	acBeginDate[24];
	char	acEndDate[24];
};

struct tagBargain
{
	int		nConsignID;//ί�к�
	int		nOperate;
	int		nStockId;
	int		nAmount;
	float	fMoney;
	float	fPrice;
	float	fFee;
	int		nState;
	char	acDateTime[24];
};

//��������
class CData;
typedef void (*_SetData)(CData * c_pData);
typedef CWnd *(*_CreateWnd)(char *,CRect *,CWnd *,unsigned short c_usID);
typedef int  (*_DoCmd)(CWnd *,char *);
//��������,���ݰ���seq��λΪc_usID,����λΪ���������
typedef int (*_SendData)(CWnd * c_pWnd,char * c_pData,int c_nLen,bool c_bWaitReturn);
//�����յ�������
typedef int (*_OnRecvData)(char * c_pWndName,CWnd * c_pWnd,char * c_pData,int c_nLen);
//
typedef void (*_OnMessage)(char * c_pWndName,CWnd * c_pWnd,MSG * c_pMsg);
//����SendData����
typedef void (*_SetSendData)(_SendData c_p);
//Wnd dll�ӿ�
struct SWndDllInterface
{
	_CreateWnd	m_pCreateWnd;//��������
	_DoCmd		m_pDoCmd;//ִ������
	_SendData	m_pSendData;//��������
	_OnRecvData	m_pOnRecvData;//������յ�������
	_OnMessage  m_pOnMessage;
};
struct SDllDef
{
	HMODULE	m_hHandle;
	char m_acDllFile[MAX_PATH];
	SWndDllInterface m_interFace;
};

struct SQuickKey
{
	char m_acKeyDesc[20];
	char m_acKey[8];
};

#pragma pack()

#endif
