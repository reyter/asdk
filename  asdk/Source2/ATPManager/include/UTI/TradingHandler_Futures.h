/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 交易接口类(期货类).
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-8		李伟		 创建
-------------------------------------------------------------
*/

#pragma once
#include "TradingHandler.h"
#include "UTIDefine_Fut.h"
#include "../Include/ATPSetting/ATPErrorDefine.h"

/**
交易处理类(期货).
*/
class AFX_EXT_CLASS CTradingHandler_Futures :
	public CTradingHandler
{
	DECLARE_ERROR_MAP();

public:
	CTradingHandler_Futures(CAlgoSession* pSession);
	virtual ~CTradingHandler_Futures(void);

public:
	/**
	应答数据包头.
	*/
	UTI_Trade_AnsHead m_ansHead;
	/**
	应答数据.
	*/
	char *m_pData[5];
	/**
	应答数据大小.
	*/
	int	m_nDataSize[5];

	/**
	批量委托数据缓存.
	*/
	UTI_FUT_MakeOrderResult *m_pBatchOrder;
	/**
	批量委托应答缓存.
	*/
	BOOL *m_pbBatchOrderGetAns;
	/**
	批量委托数量.
	*/
	int m_nBatchOrderNum;
	/**
	批量委托已应答数量.
	*/
	int m_nBatchOrderAnsNum;
	/**
	批量委托批次ID.
	*/
	int m_nBatchOrderID;

	/**
	批量撤单数据缓存.
	*/
	UTI_FUT_CancelOrderResult *m_pBatchCancel;
	/**
	批量撤单应答缓存.
	*/
	BOOL *m_pbBatchCancelGetAns;
	/**
	批量撤单数量.
	*/
	int m_nBatchCancelNum;
	/**
	批量撤单已应答数量.
	*/
	int m_nBatchCancelAnsNum;
	/**
	批量撤单批次ID.
	*/
	int m_nBatchCancelID;

public:
	/**
	临界区，用于设置应答数据.
	*/
	CRITICAL_SECTION m_csTradeData;
	/**
	临界区，用于设置批量委托数据.
	*/
	CRITICAL_SECTION m_csBatchOrder;
	/**
	临界区，用于设置批量撤单数据.
	*/
	CRITICAL_SECTION m_csBatchCancel;

	/**
	设置返回数据
	@param tagANS_Proc[]	返回包头
	@param char[][]	数据
	@return  返回1.
	*/
	int ResetTradeData(UTI_Trade_AnsHead *pAnsHead, char **pData);

	/**
	创建批量委托
	@param int	委托单数量
	@return  返回1.
	*/
	int CreateBatchOrder(int nItems);

	/**
	设置批量委托结果
	@param int	委托单索引号
	@param tagANS_Proc[]	返回包头
	@param char[]	信息，成功时是委托合同号
	@param int	批次号
	@return  批次号不匹配返回-1，索引号越界返回-2；成功时，若全部委托单都已设置则返回1，不然就返回0.
	*/
	int SetBatchOrderByIndex(int nIndex, UTI_Trade_AnsHead *pAnsHead, char *pszMsg, int nBatchID);

	/**
	等待超时后设置委托单
	@return  若全部委托单都已设置则返回0，否则返回1.
	*/
	int SetBatchOrderTimeout();

	/**
	创建批量撤单
	@param int	待撤单数量
	@return  返回1.
	*/
	int CreateBatchCancel(int nItems);

	/**
	设置批量撤单结果
	@param int	待撤单索引号
	@param tagANS_Proc[]	返回包头
	@param int	批次号
	@return  批次号不匹配返回-1，索引号越界返回-2；成功时，若全部委托单都已设置则返回1，不然就返回0.
	*/
	int SetBatchCancelByIndex(int nIndex, UTI_Trade_AnsHead *pAnsHead, int nBatchID);

	/**
	等待超时后设置待撤单
	@return  若全部待撤单都已设置则返回0，否则返回1.
	*/
	int SetBatchCancelTimeout();

	/**
	拷贝登陆相关信息
	@param CTradingHandler_Security	待拷贝的期货交易处理类
	@return  返回1.
	*/
	int CopyLoginInfo(CTradingHandler_Futures *pOtherTH_Fut);

public:
	
	/**
	登录
	@param UTI_LoginRequest	登录请求
	@param UTI_LoginAnswer	登录应答
	@return  如果登录成功，返回TRUE.否则返回FALSE.
	*/
	bool Login(const UTI_LoginRequest* pLogin,UTI_LoginAnswer& loginAnswer);

	/**
	登出
	*/
	void Logout();

	/**
	@param szCode     代码
	@parma szMarket   市场
	@param nPrice	  价格，放大10000倍	
	@param nVolume    委托量
	@param bsSide     买卖方向 'B' 买，'S' 卖    
	@param szOrderNumber [out]返回合同号
	@param nHedgeFlag 投机套保标志 0 投机, 1 套期保值.
	@param szOrderGroup  带批号下单
	@return 如果下单成功，返回TRUE，否则返回FALSE.
	*/ 
	bool Open(const char* szCode,const char* szMarket,int nPrice,int nVolume,char bsSide,CString& szOrderNumber,int nHedgeFlag=0, const char* szOrderGroup=NULL);


	/**
	@param szCode     代码
	@parma szMarket   市场
	@param nPrice	  价格，放大10000倍	
	@param nVolume    委托量
	@param bsSide     买卖方向 'B' 买，'S' 卖
	@param szOrderNumber [out]返回合同号
	@param nHedgeFlag 投机套保标志 0 投机, 1 套期保值.
	@param szOrderGroup  带批号下单
	@return 如果下单成功，返回TRUE，否则返回FALSE.	
	*/
	bool Close(const char* szCode,const char* szMarket,int nPrice,int nVolume,char bsSide,CString& szOrderNumber,int nHedgeFlag=0,const char* szOrderGroup=NULL);



	/**
	下单
	@param	pOrder	下单内容
	@parma	moResult 下单的结果
	@return 如果下单成功，返回TRUE，否则返回FALSE.
	*/
	bool MakeOrder(const UTI_FUT_Order* pOrder,UTI_FUT_MakeOrderResult& moResult);



	/**
	批量下单
	@param	pOrders	下单内容
	@param  nItems  个数
	@parma	pResults 下单的结果
	@return 如果下单成功，返回TRUE，否则返回FALSE.
	*/
	bool MakeOrder(const UTI_FUT_Order* pOrders,int nItems,UTI_FUT_MakeOrderResult* pResults);


	/**
	撤单
	@param	pRecord		委托记录/可撤单记录
	@param  coResult	撤单结果
	@return	如果已经撤销，或者已经全部成交，返回TRUE,失败反回FALSE。
	*/
	bool CancelOrder(const UTI_FUT_OrderRecord* pRecord,UTI_FUT_CancelOrderResult& coResult);

	/**
	撤单
	@param pszOrderNumber   委托编号
	@param coResult			撤单结果
	@return 如果已经撤销，或者已经全部成交，返回TRUE,失败反回FALSE。
	*/
	bool CancelOrder(const char* pszOrderNumber,UTI_FUT_CancelOrderResult& coResult);

	/**
	批量撤单首地址.
	@param pRecords         批量撤单内容首地址
	@param nRecords			数组记录数
	@param pcoResults		[out]撤单结果首地址, 数组数应大于等于nRecords。	
	*/
	void CancelOrder(const UTI_FUT_OrderRecord* pRecords,int nRecords,UTI_FUT_CancelOrderResult* pcoResults);

	/**
	全撤
	@return 顺利执行返回TRUE，否则，返回FALSE.
	*/
	bool CancelAllOrder();


	/**
	全部持仓查询
	@param pPositions 持仓，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryHoldPositions(UTI_FUT_Position*& pPositions,int& nItems);



	/**
	按市场查询持仓
	@parma szMarket   市场
	@param pPositions 持仓，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryHoldPositions(const char* szMarket, UTI_FUT_Position*& pPositions,int& nItems);

	/**
	查询股指期货市场持仓
	@parma szMarket   市场
	@param pPositions 持仓，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryHoldPositions_CF(const char* szMarket, UTI_FUT_Position*& pPositions,int& nItems);

	/**
	查询上海期货市场持仓
	@parma szMarket   市场
	@param pPositions 持仓，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryHoldPositions_SH(const char* szMarket, UTI_FUT_Position*& pPositions,int& nItems);

	/**
	查询郑州期货市场持仓
	@parma szMarket   市场
	@param pPositions 持仓，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryHoldPositions_ZZ(const char* szMarket, UTI_FUT_Position*& pPositions,int& nItems);

	/**
	查询大连期货市场持仓
	@parma szMarket   市场
	@param pPositions 持仓，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryHoldPositions_DL(const char* szMarket, UTI_FUT_Position*& pPositions,int& nItems);


	/**
	按品种查询
	@param szMarket   市场
	@param szCode	  代码
	@param pPositions 持仓，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryHoldPositions(const char* szCode,const char* szMarket,UTI_FUT_Position*& pPositions,int& nItems);


	/**
	查成交(内部实现需更新定位串)
	@param pMatch 持仓，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryMatch(UTI_FUT_Match*& pMatch,int& nItems);


	/**
	返回自上次查询过后的最新的成交（内部实现需更新定位串）.
	@param pMatch 持仓，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryNewMatch(UTI_FUT_Match*& pMatch,int& nItems);


	/**
	按市场查询成交
	@parma szMarket   市场
	@param pMatch    成交，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryMatchByMarket(const char* szMarket, UTI_FUT_Match*& pMatch,int& nItems);

	/**
	查询股指期货市场成交
	@parma szMarket   市场
	@param pMatch    成交，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryMatchByMarket_CF(const char* szMarket, UTI_FUT_Match*& pMatch,int& nItems);

	/**
	查询上海期货市场成交
	@parma szMarket   市场
	@param pMatch    成交，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryMatchByMarket_SH(const char* szMarket, UTI_FUT_Match*& pMatch,int& nItems);

	/**
	查询郑州期货市场成交
	@parma szMarket   市场
	@param pMatch    成交，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryMatchByMarket_ZZ(const char* szMarket, UTI_FUT_Match*& pMatch,int& nItems);

	/**
	查询大连期货市场成交
	@parma szMarket   市场
	@param pMatch    成交，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryMatchByMarket_DL(const char* szMarket, UTI_FUT_Match*& pMatch,int& nItems);


	/**
	按品种查询
	@param szMarket   市场
	@param szCode	  代码
	@param pMatch    成交，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryMatch(const char* szCode,const char* szMarket,UTI_FUT_Match*& pMatch,int& nItems);



	/**
	按合同号查询
	@param  szOrderNumber   合同号
	@param pMatch    成交，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryMatch(const char* szOrderNumber,UTI_FUT_Match*& pMatch,int& nItems);


	/**
	按委托记录查询
	@param  pRecord   委托记录
	@param pMatch    成交，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryMatch(const UTI_FUT_OrderRecord* pRecord,UTI_FUT_Match*& pMatch,int& nItems);


	/**
	按合同号合并查询
	@param  szOrderNumber   合同号
	@param match    合并后的成交
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryMatch_Merge(const char* szOrderNumber,UTI_FUT_Match& match);


	/**
	按委托记录合并查询
	@param  pRecord   委托记录
	@param match	  合并后的成交
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryMatch_Merge(const UTI_FUT_OrderRecord* pRecord,UTI_FUT_Match& match);


	/**
	订阅成交数据
	@param bSubscribe  TRUE 订阅成交数据，FALSE，取消订阅.
	*/ 
	bool SubscribeMatch(bool bSubscribe);

	/**
	订阅成交数据的通知
	@param pMatch 成交数据
	@param nItmes  记录数
	@see SubscribeMatch
	*/
	virtual void OnNotifyMatch(const UTI_FUT_Match* pMatch,int nItmes){}


	/**
	查委托记录
	@param pRecord	   委托记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryOrderRecords(UTI_FUT_OrderRecord*& pRecord,int& nItems);



	/**
	查指定市场的委托记录
	@param szMarket   市场	
	@param pRecord	   委托记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryOrderRecords(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	查询股指期货市场委托
	@param szMarket   市场	
	@param pRecord	   委托记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryOrderRecords_CF(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	查询上海期货市场委托
	@param szMarket   市场	
	@param pRecord	   委托记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryOrderRecords_SH(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	查询郑州期货市场委托
	@param szMarket   市场	
	@param pRecord	   委托记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryOrderRecords_ZZ(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	查询大连期货市场委托
	@param szMarket   市场	
	@param pRecord	   委托记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryOrderRecords_DL(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	查指定品种的委托记录
	@param szMarket   市场
	@param szCode	  代码
	@param pRecord	   委托记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryOrderRecords(const char* szCode,const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);




	/**
	按合同号查委托
	@param  szOrderNumber 合同号
	@param  orderRecord   委托记录
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryMatch_Merge(const char* szOrderNumber,UTI_FUT_OrderRecord& orderRecord);



	/**
	查可撤委托记录
	@param pRecord	   委托记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryCanCancel(UTI_FUT_OrderRecord*& pRecord,int& nItems);


	/**
	查指定市场的可撤委托记录
	@param szMarket   市场
	@param szCode	  代码
	@param pRecord	   委托记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryCanCancel(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	查询股指期货市场可撤委托
	@param szMarket   市场
	@param szCode	  代码
	@param pRecord	   委托记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryCanCancel_CF(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	查询上海期货市场可撤委托
	@param szMarket   市场
	@param szCode	  代码
	@param pRecord	   委托记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryCanCancel_SH(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	查询郑州期货市场可撤委托
	@param szMarket   市场
	@param szCode	  代码
	@param pRecord	   委托记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryCanCancel_ZZ(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	查询大连期货市场可撤委托
	@param szMarket   市场
	@param szCode	  代码
	@param pRecord	   委托记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryCanCancel_DL(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);


	/**
	查指定品种的可撤委托记录
	@param szMarket   市场
	@param szCode	  代码
	@param pRecord	   委托记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryCanCancel(const char* szCode,const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);


	/**
	按合同号查可撤委托记录
	@param  szOrderNumber 合同号
	@param  orderRecord   委托记录
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryCanCancel(const char* szOrderNumber,UTI_FUT_OrderRecord& orderRecord);



	/**
	查可用资金
	@param dFreeCapital [out]返回可用资金
	@param chCurrencyType 币种, '0' 人民币 , '1' 港币, '2' 美元
	@return 成功返回TRUE，否则返回FALSE.
	*/	
	bool QueryFreeCapital(double& dFreeCapital,char chCurrencyType='0');


	/**
	查资产
	@param pAssets  资产记录，采用new分配，调用者负责delte []。
	@param nItems	  返回记录数.
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryAssets(UTI_FUT_Assets*& pAssets,int& nItems);


	/**
	按币种查资产
	@param chCurrencyType 币种  '0' 人民币 , '1' 港币, '2' 美元
	@param assets  资产记录，	
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryAssets(char chCurrencyType,UTI_FUT_Assets& assets);



	/**
	最大可交易量查询
	@param pReq	 最大可交易量查询请求
	@param iVolume	[out]输出最大可交易量
	@return 成功返回TRUE，否则返回FALSE.
	*/
	bool QueryMaxBSVolume(const UTI_FUT_QueryMaxVolumeReq* pMaxVolReq,INT64& iVolume);



	/**
	合约查询
	*/ 
	bool QueryAgreement(const char* szMarket,const char* szCode,UTI_FUT_Agreement& agreement);


	/**
	结算单确认.
	*/
	bool  ConfirmSettlement();

};
