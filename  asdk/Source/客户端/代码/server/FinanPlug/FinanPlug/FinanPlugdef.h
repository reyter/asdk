//FinanPlugdef.h
#ifndef _FINANPLUGDEF_H_
#define _FINANPLUGDEF_H_
#include <list>
#include "../../public/protocol.h"
#include "FinanPlugExport.h"
/////////////////////////////////////////////////////////////////////////////////
//客户端请求

#define PT_STOCKINFO			  3011	//股票信息
#define PT_POSITION				  3013	//持仓
#define PT_CONSIGN				  3015  //委托,买/卖/撤
#define PT_CONSIGN_HISTORY		  3016  //委托历史
#define PT_BARGAIN				  3017	//成交查询
#define PT_MAKERCONSIGN			  3018	//庄家委托

#define PT_MAKERSTOCK			  3019	//庄家股票对应

#define PT_COMMAND				  3010	//管理命令

#define PT_USER_CHANGEPASSWORD	  3029	//更改密码
#define PT_VERSION				  3085	//版本信息


#define PT_PRIVATE_USER_LOG_DES	  3119  //用户登陆，加密
#define PT_USER_CHANGEPASSWORD_DES	  3129	//更改密码，加密

//结构体
#pragma pack(push)
#pragma pack(1)
struct tagReturnMsgID
{
	SMsgID    id;
	char*     pBuf;
	int       nBufSize;
};

//包头
struct tagPackHead
{
	CommxHead       comxHead;     //通讯包头 
	unsigned short  nFuncNo;	  //功能号
	unsigned short  nReqCount;	  //请求个数
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
	int				nUserId;//用户ID
	char			acCode[16];//代码
	char			acPass[32];//现密码
	char			acNewPass[32];//新密码
	int				nType;//0查询密码，1交易密码
};

//升级版本信息
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
	int			nEncrypt;//加密方式
	char		acCode[64];
	char		acPass[64];
};

struct tagUserInfo
{
	int				nMemberType;//会员类型
	unsigned int    nUserID;          //用户编号
	char			szLoginCode[64];	//登陆名称
	char            szNickName[64];   //昵称
};

struct tagStockInfo
{
	char            szCode[6];
	char			szHy[10];//行业代码
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

struct tagAccount//帐户信息
{
	float		fAssets;//总资产
	float		fCash;//现金总额
	float		fFreezeCash;//冻结现金
	float		fProfit;//盈亏
};

struct tagPosition//持仓
{
	int		nStockId;//股票Id
	int		nAmount;//数量
	int		nFreezeAmount;//冻结数量
	float	fCost;//成本价格
	int		nBuyToday;
	int		nSaleToday;
};

struct tagConsignReq
{
	int		nOperate;//操作，1委托买，2委托卖,3撤单
	int		nStockId;//股票Id
	int		nAmount;//数量
	float	fPrice;//价格
	int		nConsignID;//对于撤单此值为待撤单的委托号
};

struct tagMakerConsignReq//庄家委托
{
	int		nStockId;//股票Id
	int		nBuyAmount;//买入数量
	float	fBuyPrice;//买入价格
	int		nSaleAmount;//卖出数量
	float	fSalePrice;//卖出价格
	int		nType;//0追加，1撤销先前的委托
};

struct tagConsignHistoryReq
{
	char	acBeginDate[24];
	char	acEndDate[24];
};

struct tagConsignHistory//委托历史
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

struct tagBargain//成交
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

struct tagStockDelegate//委托
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
	int		nMakerQuoteDetailId;//庄家委托Id，对应StockQuoteDetail表
};

struct tagStockDetail//成交明细
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