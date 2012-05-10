/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 ���׽ӿ���.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-4		��ΰ		 ����
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
	֤ȯ����
	*/ 		
	SERVICE_TYPE_SEC=1,

	/**
	�ڻ�����
	*/ 		
	SERVICE_TYPE_FUT=2

};

/**
���״�����
*/
class AFX_EXT_CLASS CTradingHandler
{
	DECLARE_ERROR_MAP();
public:
	CTradingHandler(CAlgoSession* pSession);
	virtual ~CTradingHandler(void);

	/**
	��ʼ��
	*/
	static int Init();

	/**
	���
	*/
	static int Clear();

	/**
	�м������
	@param char[]	dll·��
	@param char[]	ini����·��
	@return  ������óɹ�������0.���򷵻�����ֵ.
	*/
	static int SetMidDrv(char *szDllFilePath,char* szIniFilePath);

	/**
	�õ�����dll����
	@return  1-֤ȯ���ף�2-�ڻ����ף�ʧ���򷵻ظ���.
	*/
	static int GetMidDrvType();

	/**
	��¼
	@param UTI_LoginRequest	��¼����
	@param UTI_LoginAnswer	��¼Ӧ��
	@return  �����¼�ɹ�������TRUE.���򷵻�FALSE.
	*/
	virtual bool Login(const UTI_LoginRequest* pLogin,UTI_LoginAnswer& loginAnswer);

	/**
	�ǳ�
	*/
	virtual void Logout();

	/**
	���Ҹ��г��Ĺɶ��˻�
	@param char[]	�г�
	@param int	���� 1-��A��2-��B��3-��A��4-��B��5-�����ڻ���6-�Ϻ��ڻ���7-֣���ڻ���8-�����ڻ�
	@return  ����ҵ��򷵻������ţ����򷵻�-1.
	*/
	int FindSecuCodeByMarket(int nType);


	virtual int OnDisconnect();

public:
	/**
	ָ��Ӧ���ź���.
	*/
	HANDLE m_hGetAnswer;
	
protected:
	/**
	�ỰID.
	*/
	CAlgoSession* m_pSession;

	/**
	�Ƿ��Ѿ���¼.
	*/
	bool m_bHaveLogined;

	/**
	��½�ɹ�������Ϣ.
	*/
	UTI_AccInfo m_accInfo;

	/**
	�ɶ�����.
	*/
	int m_nSecuNums;

	/**
	�ɶ���Ϣ.
	*/
	UTI_SecuInfo *m_pSecuInfo;

	/**
	������ID.
	*/
	int m_nTradingID;


	/**
	�ɽ�������ѯ��λ��.
	ÿһ�β�ѯʱ������Ҫ���´˴�.
	*/
	CString m_strQueryMatchPosString;


	/**
	���ĵ���������.
	*/
	DWORD m_dwSubscribe;
	

	
};
