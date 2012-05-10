/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨ִ����
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-2		��ΰ		 ����
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
	�㷨ִ�еĽ�����
	д���������ӿ�
	#See Begin
	#See End
    �㷨��ʵ�����������������ʵ���㷨��ִ��.
*/
class AFX_EXT_CLASS CAbstractAlgo : public CObject
{
	DECLARE_DYNCREATE(CAbstractAlgo);
public:
	/**
	��������
	*/
	virtual UINT GetTotal(){ return m_nTotal;}

	/**
	����������
	*/
	virtual UINT GetFinish(){return m_nFinish;}

	/**
	ȡ״̬
	*/
	virtual CString GetStatus(){return m_szStatus;}

	/**
	ȡ��ʶ��
	*/
	virtual CString GetRunningAlgoName(){return m_szName;}
public:
		/**
		�㷨����
		*/
		char m_szName[64];				

		/**
		��ʼʱ��
		*/
		UINT m_nBeginTime;				

		/**
		�µ�����
		*/ 
		UINT m_nMakeOrderTimes;
		
		/**
		�������.
		*/		
		UINT m_nFinish;

		/**
		����
		*/ 
		UINT m_nTotal;

		/**
		״̬˵��
		*/
        char m_szStatus[64];			

public:
	CAbstractAlgo();
	virtual ~CAbstractAlgo();

	
	/**
	�㷨��ʼ��.
	@param pParamters �㷨����ֵ�׵�ַ.
	@param nParams	  ��������
	@param strReason  �����ʼ��ʧ��ʱ�����߲�������ȷʱ����ʱ����ԭ��
	@return �����Ƿ��ʼ���ɹ��������ʼ���ɹ����㷨�������潫��һ������Run����.
	*/ 
	virtual bool Init(ATP_ALGOPARAM_VALUE* pParamters,int nParams,CString& strReason);



	/**
	����ִ���㷨���ú������غ󣬱�ʾ�㷨�˳����㷨���������ִ����Դ�Ļ��չ�����
	@return �����˳����롣
	*/
	virtual int Run(){return 0;}


	/**
	*	ǿ����ֹ�㷨�µ�.
	*	�㷨Ӧ��д�˺�������ʵ���㷨����ֹ����.�����㷨���㣬���˳�Run������
	*	@return �����˳�����.
		@See Run
	*/
	virtual int Kill(){return 0;}

	
protected:
    CAlgoSession* m_pAlgoSession;

	/*
	����˽����־.
	*/
	CATPLogger*   m_pPrivateLog;


	/**
	�����,�㷨Run֮ǰ���ã�
	����ǹ�ͬʱ����ֵ���ݵ���Ա����.
	*/	
	virtual void BeforRun(CAlgoSession* pSession,
		CATPLogger* pPrivateLog,
		CTradingHandler_Security* pHandlerSec,
		CTradingHandler_Futures* pHandlerFut);

	/**
	֤ȯ����ָ��.
	*/
	CTradingHandler_Security* m_pTradingHeandleSec;	

	/**
	�ڻ�����ָ��.
	*/
	CTradingHandler_Futures* m_pTradingHeandleFut;

    	
	friend class  CAlgoManager;
	friend class  CWinThread_ExecAlgo;

};

#endif //__ABSTRACTALGO_H_