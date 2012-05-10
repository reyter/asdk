#pragma once
#include "atsvrprocessor.h"
class CTradingHandler_Futures;

class AFX_EXT_CLASS CATSvrProcessor_Fut :
	public CATSvrProcessor
{
public:
	CATSvrProcessor_Fut(void);
	virtual ~CATSvrProcessor_Fut(void);

	virtual void SendAlgoStatus();

	/**
	接收到消息.了类重载此函数，以完成其自有逻辑的处理.
	*/
	virtual void OnReceiveMsg(char* pMsg,int nLength);


	virtual bool OnLoginMsg(const UTI_LoginRequest* pLogin,UTI_LoginAnswer& answer);

	virtual void CATSvrProcessor_Fut::GetTradingHandler(CTradingHandler_Security*& pHandlerSec,
		CTradingHandler_Futures*& pHandlerFuture);


public:

	/**
	处理下单消息
	*/ 	
	void OnMakeOrder(char* pMsg,int nLength);


	/**
	处理持仓查询
	*/ 
	void OnQueryHoldPostion(char* pMsg,int nLength);


	/**
	可撤单查询.
	*/ 
	void OnQueryCanCancel(char* pMsg,int nLength);



	/**
	委托查询
	*/
	void OnQueryOrderRecord(char* pMsg,int nLength);


	/**
	资产查询
	*/
	void OnQueryAssets(char* pMsg,int nLength);

	/**
	成交查询
	*/
	void OnQueryMatch(char* pMsg,int nLength);


	/**
	最大可交易量查询.
	*/ 	
	void OnQueryMaxVolume(char* pMsg,int nLength);



	/**
	撤单
	*/	
	void OnCancelOrder(char* pMsg,int nLength);	


	/**
	算法下单指令.
	*/	
	//virtual void OnAlgoOrder(char* pMsg,int nLength);


protected:

	/**
	交易助手.
	*/ 	
	CTradingHandler_Futures* m_pTradingHandler;
};
