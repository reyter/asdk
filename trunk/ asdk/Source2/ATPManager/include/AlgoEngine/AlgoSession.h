/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨�Ự��.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-4		��ΰ		 ����
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
�㷨���׻Ự��.
*/
class AFX_EXT_CLASS CAlgoSession
{
public:
	CAlgoSession(CAlgoUser* pUser);
	virtual ~CAlgoSession(void);

	virtual void  OnBuy(const char* szCode,const char* szMarket,int nPrice,int nVolume);

	virtual void  OnSell(const char* szCode,const char* szMarket,int nPrice,int nVolume);

	/**
	�����㷨��״̬.
	@param pAlgoStatus �����㷨��״̬.
	*/
	void GetAlgoStatus(ATP_Msg_Sec_CurrentAlgoStatus* pAlgoStatus);

	CAlgoUser* GetUser();

public:
	
	/**
	ȡ����,ÿ������ȡ����������Ψһ��.
	*/
	CString GetGroupNo();

	/**
	ȡ��־��.
	��ÿ���û���ID������������Ϊ��־��.
	*/ 	
	CString GetLogName();
protected:
	/**
	�û�ID.
	*/ 	
	CString m_strUserID;	

	/**
	����ܴ���
	*/
	int m_nBuyOrderTimes;


	/**
	�����ܴ���
	*/
	int m_nSellOrderTimes;

	/**
	��ʼʱ��
	*/
	SYSTEMTIME  m_tmBeignTime;
	
	/**
	��Session������ָ��.
	*/
	CAbstractAlgo * m_pAlgo;

	/**
	�û�.
	*/ 	
	CAlgoUser*    m_pUser;

	friend class CAlgoManager;
};


#endif //_ALGOSESSION_H_