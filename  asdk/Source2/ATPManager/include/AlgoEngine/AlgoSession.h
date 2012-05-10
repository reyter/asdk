/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法会话类.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-4		李伟		 创建
-------------------------------------------------------------
*/

#pragma once
#ifndef   _ALGOSESSION_H_
#define   _ALGOSESSION_H_


//#include "AbstractAlgo.h"
#include "..\include\ATSvr\OpenTDProtocol.h"
#include "AlgoUser.h"
class CAbstractAlgo;
/**
算法交易会话类.
*/
class AFX_EXT_CLASS CAlgoSession
{
public:
	CAlgoSession(CAlgoUser* pUser);
	virtual ~CAlgoSession(void);

	virtual void  OnBuy(const char* szCode,const char* szMarket,int nPrice,int nVolume);

	virtual void  OnSell(const char* szCode,const char* szMarket,int nPrice,int nVolume);

	/**
	返回算法的状态.
	@param pAlgoStatus 返回算法的状态.
	*/
	void GetAlgoStatus(ATP_Msg_Sec_CurrentAlgoStatus* pAlgoStatus);

	CAlgoUser* GetUser();

public:
	
	/**
	取批号,每个对像，取到的批号是唯一的.
	*/
	CString GetGroupNo();

	/**
	取日志名.
	以每个用户的ID，加上日期作为日志名.
	*/ 	
	CString GetLogName();
protected:
	/**
	用户ID.
	*/ 	
	CString m_strUserID;	

	/**
	买的总次数
	*/
	int m_nBuyOrderTimes;


	/**
	卖的总次数
	*/
	int m_nSellOrderTimes;

	/**
	开始时间
	*/
	SYSTEMTIME  m_tmBeignTime;
	
	/**
	跟Session关联的指针.
	*/
	CAbstractAlgo * m_pAlgo;

	/**
	用户.
	*/ 	
	CAlgoUser*    m_pUser;

	friend class CAlgoManager;
};


#endif //_ALGOSESSION_H_