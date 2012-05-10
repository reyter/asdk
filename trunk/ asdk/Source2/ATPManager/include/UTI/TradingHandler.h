/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 交易接口类.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-4		李伟		 创建
-------------------------------------------------------------
*/
#pragma once

#include "../Include/AlgoEngine/AlgoSession.h"
#include "UTIDefine.h"
#include "../Include/ATPSetting/ATPErrorDefine.h"
#include "../Include/QuotationDB/QDBRealTime.h"
#include "../Include/ATPSetting/ATPSettingHelper.h"


enum SERVICE_TYPE
{
	/**
	证券服务
	*/ 		
	SERVICE_TYPE_SEC=1,

	/**
	期货服务
	*/ 		
	SERVICE_TYPE_FUT=2

};

/**
交易处理类
*/
class AFX_EXT_CLASS CTradingHandler
{
	DECLARE_ERROR_MAP();
public:
	CTradingHandler(CAlgoSession* pSession);
	virtual ~CTradingHandler(void);

	/**
	初始化
	*/
	static int Init();

	/**
	清除
	*/
	static int Clear();

	/**
	中间件设置
	@param char[]	dll路径
	@param char[]	ini配置路径
	@return  如果设置成功，返回0.否则返回其它值.
	*/
	static int SetMidDrv(char *szDllFilePath,char* szIniFilePath);

	/**
	得到交易dll类型
	@return  1-证券交易，2-期货交易，失败则返回负数.
	*/
	static int GetMidDrvType();

	/**
	登录
	@param UTI_LoginRequest	登录请求
	@param UTI_LoginAnswer	登录应答
	@return  如果登录成功，返回TRUE.否则返回FALSE.
	*/
	virtual bool Login(const UTI_LoginRequest* pLogin,UTI_LoginAnswer& loginAnswer);

	/**
	登出
	*/
	virtual void Logout();

	/**
	查找该市场的股东账户
	@param char[]	市场
	@param int	类型 1-深A，2-深B，3-沪A，4-沪B，5-金融期货，6-上海期货，7-郑州期货，8-大连期货
	@return  如果找到则返回索引号，否则返回-1.
	*/
	int FindSecuCodeByMarket(int nType);


	virtual int OnDisconnect();

public:
	/**
	指令应答信号量.
	*/
	HANDLE m_hGetAnswer;
	
protected:
	/**
	会话ID.
	*/
	CAlgoSession* m_pSession;

	/**
	是否已经登录.
	*/
	bool m_bHaveLogined;

	/**
	登陆成功返回信息.
	*/
	UTI_AccInfo m_accInfo;

	/**
	股东数量.
	*/
	int m_nSecuNums;

	/**
	股东信息.
	*/
	UTI_SecuInfo *m_pSecuInfo;

	/**
	交易类ID.
	*/
	int m_nTradingID;


	/**
	成交增量查询定位串.
	每一次查询时，都需要更新此串.
	*/
	CString m_strQueryMatchPosString;


	/**
	订阅的数据类型.
	*/
	DWORD m_dwSubscribe;
	

	
};
