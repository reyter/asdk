/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 ʵʱ������.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-1		��ΰ		 ����
-------------------------------------------------------------
*/
#pragma once

#include "OpenTDProtocol.h"

class CAsyncSocket_Svr;
#include "..\Include\AlgoEngine\AlgoManager.h"
#include "..\Include\AlgoEngine\AlgoUser.h"

/**
* �㷨���׷�����������,���ڽ��պ�Ӧ��ͻ��˷����������ݱ���.
*/
class AFX_EXT_CLASS CATSvrProcessor
{
public:
	CATSvrProcessor(void);
	virtual ~CATSvrProcessor(void);

	//�����㷨����ƽ̨�㷨״̬��Ϣ.
	virtual void SendAlgoStatus();

	/**
	ԭʼ�Ľ�������.
	*/
	void OnReceive(char* pData, int nLength);


	void OnReceiveFilter(char* pMsg,int nLength);

	/**
	���յ���Ϣ.�������ش˺�����������������߼��Ĵ���.
	*/
	virtual void OnReceiveMsg(char* pMsg,int nLegnth);


	/**
	��¼��Ϣ
	*/ 	
	virtual bool OnLoginMsg(const UTI_LoginRequest* pLogin,UTI_LoginAnswer& answer)=0;


	/**
	������Ϣ.
	@param nMsgType	��Ϣ����
	@param pMsgBody ��Ϣ�׵�ַ
	@param nBodyLegnth ��Ϣ����
	*/ 
	void SendATPMsg(int nMsgType,void* pMsgBody,int nBodyLength);

	/**
	���ʹ�һ��ͷ����Ϣ.
	@param nMsgType	��Ϣ����
	@param pMsgHead ��Ϣͷ
	@param nHeadLength ��Ϣͷ����.
	@param pMsgBody ��Ϣ�׵�ַ
	@param nBodyLegnth ��Ϣ����	
	*/ 	
	void SendATPMsg(int nMsgType,void* pMsgHead,int nHeadLength,void* pMsgBody,int nBodyLength);

	
	void SendATPSystemMsg(int nType,CString strMsg);


	/**
	������Ϣ��������Ϣ���ͺ󣬹ر�����.
	@param nMsgType	��Ϣ����
	@param pMsgBody ��Ϣ�׵�ַ
	@param nBodyLegnth ��Ϣ����
	*/ 	
	void  SendATPMsgThenClose(int nMsgType,void* pMsgBody,int nBodyLength);

    /**
	�رմ�������������ڴ�
	*/
	//void  Close();

	virtual void GetTradingHandler(CTradingHandler_Security*& pHandlerSec,
		CTradingHandler_Futures*& pHandlerFuture)=0;

protected:
	/**
	��Ϣ˳���.
	*/ 	
	volatile  long    m_lOrder;


	/**
	�Ƿ��Ѿ��ɹ���¼
	*/
	bool			  m_bLoginOk;


	
	/**
	��¼��Ϣ����
	*/ 	
	void OnLoginMsg(char* pMsg,int nLength);

	/**
	��ѯ�㷨��Ϣ.
	*/	
	void OnQueryAlgoInfo();


	/**
	��ѯ�㷨������Ϣ
	*/ 
	void OnQueryAlgoParamter(char* pMsg,int nLength);


	/**
	�㷨��ʽ�µ�.
	������ȥ��д
	*/
	virtual void OnAlgoOrder(char* pMsg,int nLength);


	/**
	�����㷨״̬��ѯ
	*/ 	
	void OnQueryCurrentAlgoStatus(char* pMsg,int nLength);


protected:	
	char*               m_pRealData;
	int					m_nAllocRealDataItem;
	int					m_nRecvOffset;	//���յ����ݵ�����.

	ATP_User_Info		m_UserInfo;


	//������Ϣʱ��������Ϣ��.
	long GetMsgOrder(); 

	//�ڲ���������������ڴ棬�鲢��m_pRealData��.
	void MergeMem(char* pData,int nLength);


	
	//ȡ��ǰʱ��.
	static int GetCurrentMsgTime();

public:
	CAsyncSocket_Svr*	m_pSocket;	
};
