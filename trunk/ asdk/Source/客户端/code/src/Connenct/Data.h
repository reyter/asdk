#pragma once
#include <map>
#include <vector>
#include "data_struct.h"
#include "synch.h"

#define HISK_BEGIN_DATE 20050101

#define	ROLE_YJBG				  0x0001
#define ROLE_YJBG_HZ			  0x0002
#define ROLE_YJBG_FHZ			  0x0004
#define ROLE_HLDXG				  0x0008

typedef enum {FT_INT=0,FT_INTNUM,FT_INT8,FT_DOUBLE,FT_CHAR,FT_VARCHAR,FT_MEMO} FieldDataType;//�ֶ�����

struct SReqHead{
	DWORD m_dwSendTick;
	int m_nLen;
};

struct STrade{
	int	nId;
	int nUserId;
	double dPrice;
	int nAmount;
	char acCode[11];
	char acName[21];
	char acNike[21];
	char acDate[24];
	int nStatus;
};

struct SUserComboStock{
	char acCode[11];//��Ʊ����
	char m_strName;//����
	double dPrice;//�ɱ��۸�
	int	 nAmount;//����
	double	dPriceNow;//�ּ�
	double dCost;//�ɱ�
	double dValue;//��ֵ
	double dPer;//ӯ��
};

typedef struct _K_LINE
{
			unsigned int day;
			unsigned int open;
			unsigned int high;
			unsigned int low;
			unsigned int close;
			unsigned int volume;
			unsigned int amount;
}KLINE,*PKLINE;

struct SUserDefReportItem{
	HWND	hwndFrom;	//��Դ����
	int    nStockId[128];//��Ʊ����,���64ֻ
	int		nCount;//��Ʊ����
};

class CGroupManager;
class CData
{
public:
	CData(void);
	~CData(void);
public:	
	SStock * GetStock(CString c_str);
	SStock * GetStock(char * c_pStockCode);
	SStock * GetStock(unsigned int);
	void SetNotifyHwnd(HWND c_hwnd);
	unsigned short NewSeq();
	CString GetTail(CString c_strText,CString c_strSperate);
public:
	HWND m_hwndMain;
	
	CString m_strStockCode;

	LockSingle m_lockData;//�������ݿ�����
	LockSingle m_lockSeq;

	std::vector<SStock *> m_vpStocks;
	std::map<CString,SStock * > m_mapStocks;
	std::map<unsigned int,SStock *> m_mapUNStocks;	

	HWND  m_hwndNotify;
	unsigned short m_usSeq;
		    
	CWnd	* m_pDlgAlert;

	int m_nProductID;
	int  m_nUserID;
	char m_acPass[128];
	char m_acPassMD5[33];
	int m_nRoleID;
	char m_acLoginCode[64];
	
	char m_acEndDate[9];
	int  m_nLiveDay;//ʣ��ʱ��
	int	 m_nMemberType;//�û�����
	DWORD m_dwRole;//�û�Ȩ��
	DWORD m_dwRoleEx;//�û�Ȩ������	
	char m_acNikeName[64];
	char m_acMail[51];
	char m_acMobile[12];
	char m_acTel[21];
	char m_acMsg[256];
	char m_acAttachData[128];//��Ÿ�����Ϣ

	unsigned int m_unHGID;//�ù��û�id
	
	CString m_strNewsUrl;
	CString m_strHomeUrl;
	CString m_strHelpUrl;
	CString m_strPDFUrl;
	CString m_strF10Url;
	CString m_strSZUrl;
	CString m_strRegUrl;
	CString m_strResetPassUrl;

	char m_acCurPath[MAX_PATH];
	char m_acDataPath[MAX_PATH];
	char m_acIniFile[MAX_PATH];    
	CString m_strShowUrl;	
	void * m_pNewsView;

	std::vector<SQuickKey *> m_vpQuickKey;
	void InitQuickKey();

	unsigned int m_unsCode;
	unsigned int m_uneCode;
	unsigned int m_unTime;

	void PutMin(char * c_pCode,MinUnit * c_pData,int c_nItemCount);
	void PutTick(char * c_pCode,TickUnit * c_pData,int c_nItemCount);	

	int m_nStockSource;//��Ʊ��Դ
	int m_nWorkDay;
	int m_nWorkTime;
	int m_nWorkState;

	int		m_nErrorCode;
	CString m_strErrorMsg;
	bool IsSameWeek(unsigned int,unsigned int);
	bool IsSameMonth(unsigned int,unsigned int);

	CString NumToStr(int c_nNum);
	int GetFileData(char * c_acFile,char * c_pBuf, int c_nMaxLen);
	//For datas
	SStock * GetNextStock(SStock * c_pStock,int c_nWay);
	bool IsStock(CString c_strCode);
	bool IsStock(char * c_pCode);	
	bool IsStock(SStock *);

	CString GetStockValueByName(SStock * c_pStock,CString c_strName);	

	int FormatStockMinKData(unsigned short c_usCycle,SStock * c_pStock,KLINE *c_pK,int c_nCount);

	int WriteToFile(char * c_pFileName,char * c_pData,int c_nLen);
	int GetFromFile(char * c_pFileName,char * c_pData,int c_nMaxLen);
	int GetFromFileTail(char * c_pFileName,char * c_pData,int c_nLen);


	unsigned short m_usWeight;
	
	std::vector<SUserDefReportItem *>	m_vpUserDefReportItems;
	void AddUserDefReportItem(HWND c_hwnd,int * c_pnStockId,int c_nCount);
	void RemoveUserDefReportItem(HWND c_hwnd);
	void CheckUserDefReportItems();
	int GetUserDefReportItems(char * c_pBuf,int &c_nLen,int c_nMaxLen);

	void OnOpenDay(int);
};