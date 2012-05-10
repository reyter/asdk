#pragma once
#include "atsvrprocessor.h"
class CTradingHandler_Security;

class AFX_EXT_CLASS CATSvrProcessor_Sec :
	public CATSvrProcessor
{
public:
	CATSvrProcessor_Sec(void);
	virtual ~CATSvrProcessor_Sec(void);

	virtual void SendAlgoStatus();

	/**
	���յ���Ϣ.�������ش˺�����������������߼��Ĵ���.
	*/
	virtual void OnReceiveMsg(char* pMsg,int nLength);

	
	virtual bool OnLoginMsg(const UTI_LoginRequest* pLogin,UTI_LoginAnswer& answer);


	virtual void GetTradingHandler(CTradingHandler_Security*& pHandlerSec,
		CTradingHandler_Futures*& pHandlerFuture);

public:
    
	/**
	�����µ���Ϣ
	*/ 	
	void OnMakeOrder(char* pMsg,int nLength);


	/**
	����ֲֲ�ѯ
	*/ 
	void OnQueryHoldPostion(char* pMsg,int nLength);


	/**
	�ɳ�����ѯ.
	*/ 
	void OnQueryCanCancel(char* pMsg,int nLength);



	/**
	ί�в�ѯ
	*/
	void OnQueryOrderRecord(char* pMsg,int nLength);


	/**
	�ʲ���ѯ
	*/
	void OnQueryAssets(char* pMsg,int nLength);

	/**
	�ɽ���ѯ
	*/
	void OnQueryMatch(char* pMsg,int nLength);


	/**
	���ɽ�������ѯ.
	*/ 	
	void OnQueryMaxVolume(char* pMsg,int nLength);


	
	/**
	����
	*/	
	void OnCancelOrder(char* pMsg,int nLength);	


	/**
	�㷨�µ�ָ��.
	*/	
	//virtual void OnAlgoOrder(char* pMsg,int nLength);


protected:
	
	/**
	��������.
	*/ 	
	CTradingHandler_Security* m_pTradingHandler;
};
