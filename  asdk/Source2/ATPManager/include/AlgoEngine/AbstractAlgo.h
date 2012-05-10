/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法执行类
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-2		李伟		 创建
-------------------------------------------------------------
*/

#pragma once
#ifndef __ABSTRACTALGO_H_
#define __ABSTRACTALGO_H_


#include "..\\include\\ATSvr\\OpenTDProtocol.h"
#include "..\\include\\ATPSetting\\ATPLogger.h"

class CTradingHandler_Futures;
class CTradingHandler_Security;


#include "AlgoSession.h"
/**
	算法执行的接象类
	写义了两个接口
	#See Begin
	#See End
    算法需实现上述函数，以完成实际算法的执行.
*/
class AFX_EXT_CLASS CAbstractAlgo : public CObject
{
	DECLARE_DYNCREATE(CAbstractAlgo);
public:
	/**
	任务总数
	*/
	virtual UINT GetTotal(){ return m_nTotal;}

	/**
	己任务总数
	*/
	virtual UINT GetFinish(){return m_nFinish;}

	/**
	取状态
	*/
	virtual CString GetStatus(){return m_szStatus;}

	/**
	取标识名
	*/
	virtual CString GetRunningAlgoName(){return m_szName;}
public:
		/**
		算法名称
		*/
		char m_szName[64];				

		/**
		开始时间
		*/
		UINT m_nBeginTime;				

		/**
		下单次数
		*/ 
		UINT m_nMakeOrderTimes;
		
		/**
		己完成数.
		*/		
		UINT m_nFinish;

		/**
		总数
		*/ 
		UINT m_nTotal;

		/**
		状态说明
		*/
        char m_szStatus[64];			

public:
	CAbstractAlgo();
	virtual ~CAbstractAlgo();

	
	/**
	算法初始化.
	@param pParamters 算法参数值首地址.
	@param nParams	  参数个数
	@param strReason  如果初始化失败时，或者参数不正确时，返时出错原因。
	@return 返回是否初始化成功，如果初始化成功，算法交易引擎将进一步调用Run函数.
	*/ 
	virtual bool Init(ATP_ALGOPARAM_VALUE* pParamters,int nParams,CString& strReason);



	/**
	具体执行算法，该函数返回后，表示算法退出。算法操作引擎会执行资源的回收工作。
	@return 返回退出代码。
	*/
	virtual int Run(){return 0;}


	/**
	*	强行终止算法下单.
	*	算法应重写此函数，以实现算法的终止运行.结束算法运算，并退出Run函数。
	*	@return 返回退出代码.
		@See Run
	*/
	virtual int Kill(){return 0;}

	
protected:
    CAlgoSession* m_pAlgoSession;

	/*
	交易私有日志.
	*/
	CATPLogger*   m_pPrivateLog;


	/**
	框架在,算法Run之前调用，
	如果是股同时将其值传递到成员变量.
	*/	
	virtual void BeforRun(CAlgoSession* pSession,
		CATPLogger* pPrivateLog,
		CTradingHandler_Security* pHandlerSec,
		CTradingHandler_Futures* pHandlerFut);

	/**
	证券交易指针.
	*/
	CTradingHandler_Security* m_pTradingHeandleSec;	

	/**
	期货交易指针.
	*/
	CTradingHandler_Futures* m_pTradingHeandleFut;

    	
	friend class  CAlgoManager;
	friend class  CWinThread_ExecAlgo;

};

#endif //__ABSTRACTALGO_H_