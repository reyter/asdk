/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 实时行情类.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-4		李伟		 创建
-------------------------------------------------------------
*/


#pragma once

#ifndef __UTIDEFINE_H_
#define __UTIDEFINE_H_
#pragma pack(push,1)

//#include "TradeHead.h"
//#include "nsdprocapi.h"

#ifndef INFINITE
#define INFINITE 0xFFFFFFFF
#endif

#ifndef __NSDPROCAPI_H__

//市场类型
#define MARKET_SZ        0   //  深圳
#define MARKET_SH        1   //  上海
#define MARKET_STZ       2   //  深圳特
#define MARKET_HK		 6	 //  港股
#define MARKET_SP		 7	 //	 商品期货
#define MARKET_CF		 10	 //	 股指期货



#define LEN_ERROR		64		//出错内容
#define LEN_SESSION		64		//会话回填
#define LEN_MARKETNAME	16		//市场名称
#define LEN_BROKER		16		//经纪人
#define LEN_CUSTOM		16		//客户号
#define LEN_ACCOUNT		16		//资金账号
#define LEN_USERCODE	16		//股东代码
#define LEN_USERNAME	24		//股东姓名	--长文件名
#define LEN_USERADDR	96		//客户地址
#define LEN_POSTCODE	8		//邮政编码
#define LEN_TELN0		16		//电话号码
#define LEN_EMAIL		36		//EMAIL
#define LEN_IDNO		36		//证件号码
#define LEN_PASSWORD	24		//股东密码
#define LEN_STOCKCODE	8		//证券代码
#define LEN_STOCKENCODE	16		//证券内码
#define LEN_STOCKNAME	16		//证券名称
#define LEN_MADENUMBER  16      //成交编号
#define LEN_ORDERNUMBER	28		//委托序号
#define LEN_CHANNELCODE	144		//渠道代码

#define LEN_ORDERGROUP	12		//委托批号
#define LEN_SEAT		8		//席位号
#define LEN_FIRMIT		12		//代理商号
#define LEN_ORGID		8		//营业部代码
#define LEN_ORGNAME		32		//营业部名称
#define LEN_BANKCODE	8		//银行代码
#define LEN_BANKNAME	24		//银行名称
#define LEN_BANKACCOUNT 24		//银行帐号
#define LEN_INFOCODE	8		//信息编号
#define LEN_POSTSTR		32		//查询定位串
#define LEN_REMARK		16		//简要说明
#define LEN_RATION		32		//配号代码
#define LEN_BOARD		8		//板块

#define LEN_TACODE		8		//基金公司
#define LEN_TANAME		24		//基金公司名称
#define LEN_OFCODE		8		//基金代码
#define LEN_OFENCODE	16		//基金内码
#define LEN_OFNAME		24		//基金代码名称
#define LEN_TAACCOUNT	16		//基金账号
#define LEN_TRANSACCOUNT	24  //交易账号
#define LEN_EXTINST			16	//外部机构
#define LEN_APPLYNUMBER		36	//申请编号
#define LEN_PACTCODE		36	//协议代码
#define LEN_BRANCHID		16	//分支机构代码
#define LEN_TITLE			64	//风险评估大标题
#define LEN_RISKNAME		32	//风险评估名称

#define LEN_COMBCODE	16		//组合代码
#define LEN_COMBNAME	24		//组合名称

#define LEN_FUTCODE	16		//期货品种代码
#define LEN_FUTNAME	23		//期货品种名称

#define LEN_IPOSTOCKNAME	64	//IPO股票名称

#endif


/////////////////////////////////////////////////////////////////////////////////////
/// OpenTD 通信协议
/////////////////////////////////////////////////////////////////////////////////////


enum UTI_TradeFunID
{
	/**
	账号登陆.
	*/
	ID_TRADE_XYGD	= 1,
	/**
	查询股东代码或交易编码.
	*/
	ID_TRADE_GDCX	= 2,
	/**
	账号退出.
	*/
	ID_TRADE_EXIT	= 3,

	/**
	买卖委托(证券).
	*/
	ID_SEC_MMWT		= 100,
	/**
	撤销委托(证券).
	*/
	ID_SEC_CXWT		= 101,
	/**
	最大交易数量(证券).
	*/
	ID_SEC_MAXVOL	= 102,
	/**
	资金查询(证券).
	*/
	ID_SEC_ZJCX		= 103,
	/**
	持仓查询(证券).
	*/
	ID_SEC_CCCX		= 104,
	/**
	委托查询(证券).
	*/
	ID_SEC_WTCX		= 105,
	/**
	可撤单查询(证券).
	*/
	ID_SEC_KCDCX	= 106,
	/**
	成交查询(证券).
	*/
	ID_SEC_CJCX		= 107,
	/**
	增量成交查询(证券).
	*/
	ID_SEC_SUMZLCJCX= 108,

	/**
	买卖委托(期货).
	*/
	ID_FUT_MMWT		= 200,
	/**
	撤销委托(期货).
	*/
	ID_FUT_CXWT		= 201,
	/**
	最大交易数量(期货).
	*/
	ID_FUT_MAXVOL	= 202,
	/**
	资金查询(期货).
	*/
	ID_FUT_ZJCX		= 203,
	/**
	持仓查询(期货).
	*/
	ID_FUT_CCCX		= 204,
	/**
	委托查询(期货).
	*/
	ID_FUT_WTCX		= 205,
	/**
	可撤单查询(期货).
	*/
	ID_FUT_KCDCX	= 206,
	/**
	成交查询(期货).
	*/
	ID_FUT_CJCX		= 207,
	/**
	增量成交查询(期货).
	*/
	ID_FUT_SUMZLCJCX= 208,
};

/**
账户信息，用于各个请求指令
*/
struct UTI_AccInfo
{
	/**
	所属营业部
	*/
	char chOrgID[LEN_ORGID];		
	/**
	客户号
	*/
	char chCustomer[LEN_CUSTOM];		
	/**
	资金账号
	*/
	char chAccountCode[LEN_ACCOUNT];	
	/**
	所属经纪人
	*/
	char chBroker[LEN_BROKER];			
	/**
	托管银行
	*/
	char chBankCode[LEN_BANKCODE];		
	/**
	会话特别段，以后的请求完整回填,也可当作扩展保留段
	*/
	char chSession[LEN_SESSION];		
	/**
	客户密码
	*/
	char chPassword[LEN_PASSWORD];		
};

/**
股东信息或交易编码信息
*/
struct UTI_SecuInfo
{
	/**
	市场类型. 
	1 SZ A
	2 SZ B
	3 SH A
	4 SH B
    5 CF 
	6 SP SHFE
	7 SP ZCE
	8 SP DCE
	*/
	int	 nHolderType;
	/**
	所属营业部
	*/
	char chOrgID[LEN_ORGID];		
	/**
	客户号
	*/
	char chCustomer[LEN_CUSTOM];		
	/**
	资金账号
	*/
	char chAccountCode[LEN_ACCOUNT];	
	/**
	股东代码
	*/
	char chUserCode[LEN_USERCODE];		
	/**
	席位号
	*/
	char chSeat[LEN_SEAT];			
};

/**
查询信息
*/
struct UTI_QueryInfo
{
	/**
	查询模式,
	<table border="1">
	<tr><td>0</td><td>查询所有</td></tr>
	<tr><td>1</td><td>指定股东代码或交易编码</td></tr>
	<tr><td>2</td><td>指定证券代码或合约代码</td></tr>
	<tr><td>3</td><td>指定合同号</td></tr>
	<tr><td>4</td><td>指定币种</td></tr>
	</table>
	*/
	int nQryType;				
	/**
	股东代码或交易编码
	*/
	char chUserCode[LEN_USERCODE];		
	/**
	市场类型. 
	1 SZ A
	2 SZ B
	3 SH A
	4 SH B
    5 CF 
	6 SP SHFE
	7 SP ZCE
	8 SP DCE
	*/
	int	 nHolderType;
	/**
	证券代码或是合约代码
	*/
	char chStockCode[LEN_STOCKCODE];	
	/**
	合同号
	*/
	char chOrderNumber[LEN_ORDERNUMBER];

	/**
	查询方向，0-向前，1-向后
	*/
	int	 nQryFlag;						
	/**
	请求行数
	*/
	int	 nCount;						
	/**
	* 定位串.
	*/
	char chPostStr[LEN_POSTSTR];
};

/**
交易指令请求包头
*/
struct UTI_Trade_ReqHead
{
	/**
	包头长度
	*/
	int  				nHeadSize;

	/**
	16字节 功能号
	*/
	UTI_TradeFunID  	sFunID;	

	/**
	记录数
	*/
	int  				nItems;	

	/**
	记录大小
	*/
	int  				nItemSize;

	/**
	包顺列号
	*/
	int  				nPackOrder;

	/**
	请求日期YYYYMMDD
	*/
	int  				nReqDate;

	/**
	请求时间HHMMSS
	*/
	int  				nReqTime;

	/**
	IP地址 用16进制表示  外网+内网+连接
	*/
	char				chIPV4[12];	

	/**
	网卡地址
	*/
	char				chMacAddr[13];	

	/**
	账户信息
	*/
	UTI_AccInfo			accInfo;

};

/**
交易指令应答包头
*/
struct UTI_Trade_AnsHead
{
	/**
	16字节 功能号
	*/
	UTI_TradeFunID  	sFunID;		
	/**
	包顺列号
	*/
	int  				nPackOrder;
	/**
	应答表示，0表示成功，其它失败
	*/
	int					nAnsStatus;
	/**
	出错信息
	*/
	char				chErrMsg[64];		
	/**
	返回结果表数量
	*/
	int					nResultQrys;		
	/**
	返回结果数
	*/
	int					nItems[5];
	/**
	返回结果大小
	*/
	int					nItemSize[5];
};


//数据包识别头
struct UTI_MsgHead
{
	/**
	16字节 标识符         0x5348
	*/
	unsigned short  	sFlags;		

	/**
	16字节 数据类型
	*/
	unsigned short  	sDataType;		          

	/**
	32字节 数据长度（不含本识别头）
	*/
	int					nDataLen;	

	/**
	32字节 时间戳（精确到毫秒,格式HHMMSSmmm）
	*/
	int					nTime;		

	/**
	32字节 流水号（当返回数据太大时有效，每个请求顺序编码）
	*/
	int     			nOrder;
};

/**
登陆
*/
typedef struct UTI_LoginRequest
{
	/**
	营业部代码
	*/
	char chOrgID[8];	
	/**
	客户号
	*/
	char chUserID[16];	

	/**
	用户密码
	*/
	char chPassword[32];	

	/**
	保留
	*/
	char chID[8];			

	/**
	保留
	*/
	char chMD5[32];			
}UTI_SEC_LoginRequest,UTI_FUT_LoginRequest;


/**
登陆应答
*/
typedef struct UTI_LoginAnswer
{
	/**
	0=登陆成功，其他失败
	*/ 	
	int  nAnswer;	
	/**
	失败信息
	*/
	char chInfo[64];			//信息
}UTI_SEC_LoginAnswer,UTI_FUT_LoginAnswer;



#pragma pack(pop)
#endif //__UTIDEFINE_H_
