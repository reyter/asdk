//FinanPlugdef.h
#ifndef _FINANPLUGDEF_H_
#define _FINANPLUGDEF_H_
#include <list>
#include "../../public/protocol.h"
#include "FinanPlugExport.h"
/////////////////////////////////////////////////////////////////////////////////
//�ͻ�������

#define PT_STOCKINFO			  3011	//��Ʊ��Ϣ
#define PT_POSITION				  3013	//�ֲ�
#define PT_CONSIGN				  3015  //ί��,��/��/��
#define PT_CONSIGN_HISTORY		  3016  //ί����ʷ
#define PT_BARGAIN				  3017	//�ɽ���ѯ
#define PT_MAKERCONSIGN			  3018	//ׯ��ί��

#define PT_MAKERSTOCK			  3019	//ׯ�ҹ�Ʊ��Ӧ

#define PT_COMMAND				  3010	//��������

#define PT_USER_CHANGEPASSWORD	  3029	//��������
#define PT_VERSION				  3085	//�汾��Ϣ


#define PT_PRIVATE_USER_LOG_DES	  3119  //�û���½������
#define PT_USER_CHANGEPASSWORD_DES	  3129	//�������룬����

//�ṹ��
#pragma pack(push)
#pragma pack(1)
struct tagReturnMsgID
{
	SMsgID    id;
	char*     pBuf;
	int       nBufSize;
};

//��ͷ
struct tagPackHead
{
	CommxHead       comxHead;     //ͨѶ��ͷ 
	unsigned short  nFuncNo;	  //���ܺ�
	unsigned short  nReqCount;	  //�������
};

struct tagVersionInfo
{
	char			szVer[10];
	char			szPatch[10];
	unsigned short	usUpdateType;
	unsigned short	usForce;
	char			szVerUrl[100];
	char			szPatchUrl[100];
	char			szUpdateInfo[1024];
};

struct tagChangePass
{
	int				nUserId;//�û�ID
	char			acCode[16];//����
	char			acPass[32];//������
	char			acNewPass[32];//������
	int				nType;//0��ѯ���룬1��������
};

//�����汾��Ϣ
struct tagUpgradeInfo
{
	unsigned int	nVerID;
	tagVersionInfo	stInfo;
};

struct tagCommandInfo
{
	unsigned short	nCommandID;
	unsigned short	nResult;
};

struct tagUserLogReq
{
	int			nEncrypt;//���ܷ�ʽ
	char		acCode[64];
	char		acPass[64];
};

struct tagUserInfo
{
	int				nMemberType;//��Ա����
	unsigned int    nUserID;          //�û����
	char			szLoginCode[64];	//��½����
	char            szNickName[64];   //�ǳ�
};

struct tagStockInfo
{
	char            szCode[6];
	char			szHy[10];//��ҵ����
	double          nZgb;
	double          nLtg;
	unsigned int    nSyl;
	unsigned int    nPj;
};

struct tagUserPass
{
	int				nId;
	char			acCode[16];
	char			acPass[32];
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
	int		nStockId;//��ƱId
	int		nAmount;//����
	int		nFreezeAmount;//��������
	float	fCost;//�ɱ��۸�
	int		nBuyToday;
	int		nSaleToday;
};

struct tagConsignReq
{
	int		nOperate;//������1ί����2ί����,3����
	int		nStockId;//��ƱId
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
	int		nConsignID;
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

struct tagBargain//�ɽ�
{
	int		nConsignID;
	int		nOperate;
	int		nStockId;
	int		nAmount;
	float	fMoney;
	float	fPrice;
	float	fFee;
	int		nState;
	char	acDateTime[24];
};

struct tagStockDelegate//ί��
{
	int		nStockDelegateId;
	int		nStockId;
	int		nMemberId;
	char	acDelegateDate[24];
	int		nAmount;
	float	fPrice;
	int		nAmountDone;
	int		nAmountLeft;
	int		nStatus;
	int		nBuySale;
	char	acCancelDate[24];
	char	acDoneDate[24];
	int		nCancelId;
	int		nMakerQuoteDetailId;//ׯ��ί��Id����ӦStockQuoteDetail��
};

struct tagStockDetail//�ɽ���ϸ
{
	int		nStockId;
	int		nBuyDelegateId;
	int		nSaleDelegateId;
	float	fDonePrice;
	int		nDoneAmount;
	float	fDoneMoney;
	char	acDoneDate[24];
};

struct tagStockDone//
{
	int		nStockId;
	int		nStockDelegateId;
	float	fDonePrice;
	int		nDoneAmount;
	int		nDoneMoney;
	char	acDoneDate[24];
};

struct tagPriceVol
{
	float	fPrice;
	int		nAmount;
};

#pragma pack(pop)
/////////////////////////////////////////////////////////////////////////////////
#endif