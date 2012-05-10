/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 实时行情类.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-1		李伟		 创建
-------------------------------------------------------------
*/

#pragma once

#include <vector>
#include <list>
using namespace std;

#include <afxcoll.h>

#include "../Include/tdf/TDFApiDefine.h"
#include "../Include/ATPSetting/ATPErrorDefine.h"
#include "../ATPSetting/ATPSettingHelper.h"

struct AFX_EXT_CLASS DataFeedStatus
{
	_HServer server;				//服务器.
	INT		 nStatus;				//在线状态
};




enum QUOTATION_TYPE
{
	/**
	行情快照(证券)
	*/
	QUOTATION_TYPE_SEC=0,
	/**
	行情快照(期货)
	*/
	QUOTATION_TYPE_FUT=1,

	/**
	行情快照(指数)
	*/
	QUOTATION_TYPE_IND=2,

	/**
	行情快照(逐笔成交)
	*/
	QUOTATION_TYPE_TRANSACTION=3,

	/**
	行情快照(逐笔委托)
	*/
	QUOTATION_TYPE_ORDER=4,

	/**
	行情快照(订单队列)
	*/
	QUOTATION_TYPE_ORDERQUEUE=5,


	QUOTATION_TYPE_MAXCOUNT				//最大的品种数,不可使用.
};


struct AFX_EXT_CLASS SubscribeContent
{
	CString strMarket;
	CString strCode;
	QUOTATION_TYPE   dwType;
	SubscribeContent& operator = (const SubscribeContent& right)
	{
		strMarket = right.strMarket;
		strCode = right.strCode;
		dwType = right.dwType;
		return *this;
	}
	bool operator == (const SubscribeContent& right) const
	{
		return (dwType == right.dwType) && (strMarket == right.strMarket) 
			&&  ( strCode == right.strCode);
	}
	SubscribeContent(const char* szMarket,const char* szCode,DWORD dwType)
	{
		strMarket = szMarket;
		strCode = szCode;
		dwType = dwType;
	}
	SubscribeContent(const SubscribeContent& other)
	{
		strMarket = other.strMarket;
		strCode = other.strCode;
		dwType = other.dwType;
	}
	~SubscribeContent()
	{

	}
};


/**
* 实时行情类. 可从此类继承出来，自行实现回调的虚拟函数，以处理行情的更新通知。
* 可以调用 <a href="#SubscribeQuotation">SubscribeQuotation</a> 来订阅只关注的品种，
* 以实现，只有关注的品种，关注的数据类型更新时，才通知.
* 实时行情需要有宏汇DataFeed服务支持.
* 查询支持查代码表、查行情快照（期货、股票、指数）
* 按市场、类型订阅
* 取消订阅.
*/
class AFX_EXT_CLASS CQDBRealTime
{
	DECLARE_ERROR_MAP();

public:
	/**
	开启DataFeed接收实时数据，算法无需调用该函数.
	框架会在启动时调用该函数.
	*/ 	
	static void BeginDataFeed();


	/**
	结束HDBServer连结.
	*/ 
	static void EndDataFeed();



	
	/**
	取DataFeed在线状态。
	@pStatus , 如果为NULL,返回DataFeed数量,否则，填充nItems个状态.
    @retrun    返回DataFeed数量.
	*/	
	//static int GetDataFeedStatus(DataFeedStatus* pStatus,int nItems);


	static bool GetDataFeedStatus();


	static void GetFlow(__int64& iSend,__int64& iRecv);

	/**
	查询品种交易股东代码类别.
	@param 
	-1 
	1 SZ A
	2 SZ B
	3 SH A
	4 SH B
    5 CF 
	6 SP SHFE
	7 SP ZCE
	8 SP DCE
	*/
	static int QueryHolderType(const char* szMarket,const char* szCode);

	
	/**
	根据nExid,取串,如0-"SZ"
	*/	
	static CString GetMarket(int nExid);

public:
	CQDBRealTime(void);
	virtual ~CQDBRealTime(void);

 
	/**
		订阅行情通知,当有行情变化时，将调用虚拟函数通知行情变化.
		多次调用，以支持关注多个品种的行情变化.


		@param szMarket			市场(如:SH)
			<table border="1">
			<tr><td>市场</td><td>说明</td></tr>
			<td>SH</td><td>上海证券交易所</td></tr>
			<td>SZ</td><td>深圳证券交易所</td></tr>
			<td>SP</td><td>商品期货</td></tr>
			<td>CF</td><td>中国金融期货交易所</td></tr>
			</table>
		
		@param szCode			代码(如:600000)

		@param dwType			数据类型，可以是 QUOTATION_TYPE_XXX, 默认只关注行情快照
		
		</table>
	*/
	void SubscribeQuotation(const char* szMarket,const char* szCode,QUOTATION_TYPE dwType);

	/**
	取消订阅
	*/ 	
	void UnSubscribeQuotation(const char* szMarket,const char* szCode,QUOTATION_TYPE dwType);

	/**
	取消所有的订阅.
	*/
	void DeleteAllSubscibe();



	/**
		接收到证券行情快照时的回调.		
		@param szMarket			市场(如:SH)
			<table border="1">
			<tr><td>市场</td><td>说明</td></tr>
			<td>SH</td><td>上海证券交易所</td></tr>
			<td>SZ</td><td>深圳证券交易所</td></tr>	
			</table>
		@param szCode			代码(如:600000)
		@param pMarketData	行情快照
	*/
	virtual void OnReceiveMarketData(const char* szMarket,const char* szCode,const TDFDefine_MarketData* pMarketData){}


	/**
		接收到期货行情快照时的回调.	
		@param szMarket			市场(如:CF)
				<table border="1">
				<tr><td>市场</td><td>说明</td></tr>
				<td>SP</td><td>商品期货</td></tr>
				<td>CF</td><td>中国金融期货交易所</td></tr>
				</table>
		@param szCode			代码(如:IF1006)
		@param pMarketData	行情快照	

	*/
	virtual void OnReceiveMarketData_Futures(const char* szMarket,const char* szCode,const TDFDefine_MarketData_Futures* pMarketData){}




	/**
		接收到证券订单队列数据时的回调.		
		@param szMarket			市场(如:SH)
			<table border="1">
			<tr><td>市场</td><td>说明</td></tr>
			<td>SH</td><td>上海证券交易所</td></tr>
			<td>SZ</td><td>深圳证券交易所</td></tr>	
			</table>
		@param szCode			代码(如:600000)
		@param pOrderQueue		订单队列数据.
	*/
	virtual void OnReceiveOrderQueen(const char* szMarket,const char* szCode,const TDFDefine_OrderQueue* pOrderQueue,int nItems){}




	/**
	接收到指数行情快照时的回调.		
	@param szMarket			市场(如:SH)
	<table border="1">
	<tr><td>市场</td><td>说明</td></tr>
	<td>SH</td><td>上海证券交易所</td></tr>
	<td>SZ</td><td>深圳证券交易所</td></tr>	
	</table>
	@param szCode			代码(如:600000)
	@param pIndex			指数行情快照
	*/
	virtual void OnReceiveIndexData(const char* szMarket,const char* szCode,const TDFDefine_IndexData* pIndex){}
	

	/**
		接收到逐笔成交数据时的回调.		
		@param szMarket			市场(如:SH)
		<table border="1">
		<tr><td>市场</td><td>说明</td></tr>
		<td>SH</td><td>上海证券交易所</td></tr>
		<td>SZ</td><td>深圳证券交易所</td></tr>	
		</table>
		@param szCode			代码(如:600000)
		@param pTransaction		逐笔成交数据.
		@param nItems           
	*/
	virtual void OnReceiveTransaction(const char* szMarket,const char* szCode,const TDFDefine_Transaction* pTransaction,int nItems){}


	virtual void OnReceiveOrder(const char* szMarket,const char* szCode,const TDFDefine_Order* pOrderQueue,int nItems){}


	/**
	查询最新证券行情数据
	@param szMarket			市场(如:SH)
	<table border="1">
	<tr><td>市场</td><td>说明</td></tr>
	<td>SH</td><td>上海证券交易所</td></tr>
	<td>SZ</td><td>深圳证券交易所</td></tr>	
	</table>
	@param marketData	[out] 返回最新的行情数据.
	@param szCode			代码(如:600000)
    @return           如果查询的是期货代码，则返回false, 如果HDFServer中断，返回False，如果查找代码失败，返回False.
					  此时，可用 GetLastError 取回具体原因.
    @see GetLastError
	@see GetLastErrorCode
	*/
	bool QueryLastMarketData(const char* szMarket,const char* szCode,TDFDefine_MarketData& marketData);


	/**
	查询最新期货行情数据
	@param szMarket			市场(如:CF)
	<table border="1">
	<tr><td>市场</td><td>说明</td></tr>
	<td>SP</td><td>商品期货</td></tr>
	<td>CF</td><td>中国金融期货交易所</td></tr>
	</table>
	@param szCode			代码(如:IF1006)
	@param marketDataFutures   [out] 返回最新的行情数据
	@return           如果查询的是证券代码，则返回false,如果HDFServer中断，返回False，如果查找代码失败，返回False.
					  此时，可用 GetLastError 取回具体原因.
	@see GetLastError
	@see GetLastErrorCode
	*/
	bool  QueryLastMarketData_Futures(const char* szMarket,const char* szCode,TDFDefine_MarketData_Futures& marketDataFutures);



	/**
	查询指数的最新行情数据
	@param szMarket			市场(如:SH)
	<table border="1">
	<tr><td>市场</td><td>说明</td></tr>
	<td>SP</td><td>商品期货</td></tr>
	<td>CF</td><td>中国金融期货交易所</td></tr>
	</table>
	@param szCode			代码(如:000300)
	@parma indexData         [out] 返回最新的行情数据
	@return           如果查询的是证券,期货代码，则返回false。如果HDFServer中断，返回False，如果查找代码失败，返回False.
	@see GetLastError
	@see GetLastErrorCode
	*/
	bool QueryLastMarketData_Index(const char* szMarket,const char* szCode,TDFDefine_IndexData& indexData);



protected:
	static CPtrList     s_lsDFSocket;

	friend class CATPDataFeedSocket;
private:

	LPVOID m_pSubscribeThread;


protected:



	vector<SubscribeContent> m_vecSubscribe;

	void Add2Sub(const char* szMarket,const char* szCode,QUOTATION_TYPE dwType);
	
private:
	
	friend class CWinThread_QuotationPush;
	void NotifyBack(QUOTATION_TYPE nType,const char* strMarket,const char* strCode,void* pData,int nItems);
};
