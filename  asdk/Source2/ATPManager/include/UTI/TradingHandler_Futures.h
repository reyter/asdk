/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 ���׽ӿ���(�ڻ���).
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-8		��ΰ		 ����
-------------------------------------------------------------
*/

#pragma once
#include "TradingHandler.h"
#include "UTIDefine_Fut.h"
#include "../Include/ATPSetting/ATPErrorDefine.h"

/**
���״�����(�ڻ�).
*/
class AFX_EXT_CLASS CTradingHandler_Futures :
	public CTradingHandler
{
	DECLARE_ERROR_MAP();

public:
	CTradingHandler_Futures(CAlgoSession* pSession);
	virtual ~CTradingHandler_Futures(void);

public:
	/**
	Ӧ�����ݰ�ͷ.
	*/
	UTI_Trade_AnsHead m_ansHead;
	/**
	Ӧ������.
	*/
	char *m_pData[5];
	/**
	Ӧ�����ݴ�С.
	*/
	int	m_nDataSize[5];

	/**
	����ί�����ݻ���.
	*/
	UTI_FUT_MakeOrderResult *m_pBatchOrder;
	/**
	����ί��Ӧ�𻺴�.
	*/
	BOOL *m_pbBatchOrderGetAns;
	/**
	����ί������.
	*/
	int m_nBatchOrderNum;
	/**
	����ί����Ӧ������.
	*/
	int m_nBatchOrderAnsNum;
	/**
	����ί������ID.
	*/
	int m_nBatchOrderID;

	/**
	�����������ݻ���.
	*/
	UTI_FUT_CancelOrderResult *m_pBatchCancel;
	/**
	��������Ӧ�𻺴�.
	*/
	BOOL *m_pbBatchCancelGetAns;
	/**
	������������.
	*/
	int m_nBatchCancelNum;
	/**
	����������Ӧ������.
	*/
	int m_nBatchCancelAnsNum;
	/**
	������������ID.
	*/
	int m_nBatchCancelID;

public:
	/**
	�ٽ�������������Ӧ������.
	*/
	CRITICAL_SECTION m_csTradeData;
	/**
	�ٽ�����������������ί������.
	*/
	CRITICAL_SECTION m_csBatchOrder;
	/**
	�ٽ�������������������������.
	*/
	CRITICAL_SECTION m_csBatchCancel;

	/**
	���÷�������
	@param tagANS_Proc[]	���ذ�ͷ
	@param char[][]	����
	@return  ����1.
	*/
	int ResetTradeData(UTI_Trade_AnsHead *pAnsHead, char **pData);

	/**
	��������ί��
	@param int	ί�е�����
	@return  ����1.
	*/
	int CreateBatchOrder(int nItems);

	/**
	��������ί�н��
	@param int	ί�е�������
	@param tagANS_Proc[]	���ذ�ͷ
	@param char[]	��Ϣ���ɹ�ʱ��ί�к�ͬ��
	@param int	���κ�
	@return  ���κŲ�ƥ�䷵��-1��������Խ�緵��-2���ɹ�ʱ����ȫ��ί�е����������򷵻�1����Ȼ�ͷ���0.
	*/
	int SetBatchOrderByIndex(int nIndex, UTI_Trade_AnsHead *pAnsHead, char *pszMsg, int nBatchID);

	/**
	�ȴ���ʱ������ί�е�
	@return  ��ȫ��ί�е����������򷵻�0�����򷵻�1.
	*/
	int SetBatchOrderTimeout();

	/**
	������������
	@param int	����������
	@return  ����1.
	*/
	int CreateBatchCancel(int nItems);

	/**
	���������������
	@param int	������������
	@param tagANS_Proc[]	���ذ�ͷ
	@param int	���κ�
	@return  ���κŲ�ƥ�䷵��-1��������Խ�緵��-2���ɹ�ʱ����ȫ��ί�е����������򷵻�1����Ȼ�ͷ���0.
	*/
	int SetBatchCancelByIndex(int nIndex, UTI_Trade_AnsHead *pAnsHead, int nBatchID);

	/**
	�ȴ���ʱ�����ô�����
	@return  ��ȫ�����������������򷵻�0�����򷵻�1.
	*/
	int SetBatchCancelTimeout();

	/**
	������½�����Ϣ
	@param CTradingHandler_Security	���������ڻ����״�����
	@return  ����1.
	*/
	int CopyLoginInfo(CTradingHandler_Futures *pOtherTH_Fut);

public:
	
	/**
	��¼
	@param UTI_LoginRequest	��¼����
	@param UTI_LoginAnswer	��¼Ӧ��
	@return  �����¼�ɹ�������TRUE.���򷵻�FALSE.
	*/
	bool Login(const UTI_LoginRequest* pLogin,UTI_LoginAnswer& loginAnswer);

	/**
	�ǳ�
	*/
	void Logout();

	/**
	@param szCode     ����
	@parma szMarket   �г�
	@param nPrice	  �۸񣬷Ŵ�10000��	
	@param nVolume    ί����
	@param bsSide     �������� 'B' ��'S' ��    
	@param szOrderNumber [out]���غ�ͬ��
	@param nHedgeFlag Ͷ���ױ���־ 0 Ͷ��, 1 ���ڱ�ֵ.
	@param szOrderGroup  �������µ�
	@return ����µ��ɹ�������TRUE�����򷵻�FALSE.
	*/ 
	bool Open(const char* szCode,const char* szMarket,int nPrice,int nVolume,char bsSide,CString& szOrderNumber,int nHedgeFlag=0, const char* szOrderGroup=NULL);


	/**
	@param szCode     ����
	@parma szMarket   �г�
	@param nPrice	  �۸񣬷Ŵ�10000��	
	@param nVolume    ί����
	@param bsSide     �������� 'B' ��'S' ��
	@param szOrderNumber [out]���غ�ͬ��
	@param nHedgeFlag Ͷ���ױ���־ 0 Ͷ��, 1 ���ڱ�ֵ.
	@param szOrderGroup  �������µ�
	@return ����µ��ɹ�������TRUE�����򷵻�FALSE.	
	*/
	bool Close(const char* szCode,const char* szMarket,int nPrice,int nVolume,char bsSide,CString& szOrderNumber,int nHedgeFlag=0,const char* szOrderGroup=NULL);



	/**
	�µ�
	@param	pOrder	�µ�����
	@parma	moResult �µ��Ľ��
	@return ����µ��ɹ�������TRUE�����򷵻�FALSE.
	*/
	bool MakeOrder(const UTI_FUT_Order* pOrder,UTI_FUT_MakeOrderResult& moResult);



	/**
	�����µ�
	@param	pOrders	�µ�����
	@param  nItems  ����
	@parma	pResults �µ��Ľ��
	@return ����µ��ɹ�������TRUE�����򷵻�FALSE.
	*/
	bool MakeOrder(const UTI_FUT_Order* pOrders,int nItems,UTI_FUT_MakeOrderResult* pResults);


	/**
	����
	@param	pRecord		ί�м�¼/�ɳ�����¼
	@param  coResult	�������
	@return	����Ѿ������������Ѿ�ȫ���ɽ�������TRUE,ʧ�ܷ���FALSE��
	*/
	bool CancelOrder(const UTI_FUT_OrderRecord* pRecord,UTI_FUT_CancelOrderResult& coResult);

	/**
	����
	@param pszOrderNumber   ί�б��
	@param coResult			�������
	@return ����Ѿ������������Ѿ�ȫ���ɽ�������TRUE,ʧ�ܷ���FALSE��
	*/
	bool CancelOrder(const char* pszOrderNumber,UTI_FUT_CancelOrderResult& coResult);

	/**
	���������׵�ַ.
	@param pRecords         �������������׵�ַ
	@param nRecords			�����¼��
	@param pcoResults		[out]��������׵�ַ, ������Ӧ���ڵ���nRecords��	
	*/
	void CancelOrder(const UTI_FUT_OrderRecord* pRecords,int nRecords,UTI_FUT_CancelOrderResult* pcoResults);

	/**
	ȫ��
	@return ˳��ִ�з���TRUE�����򣬷���FALSE.
	*/
	bool CancelAllOrder();


	/**
	ȫ���ֲֲ�ѯ
	@param pPositions �ֲ֣�����new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryHoldPositions(UTI_FUT_Position*& pPositions,int& nItems);



	/**
	���г���ѯ�ֲ�
	@parma szMarket   �г�
	@param pPositions �ֲ֣�����new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryHoldPositions(const char* szMarket, UTI_FUT_Position*& pPositions,int& nItems);

	/**
	��ѯ��ָ�ڻ��г��ֲ�
	@parma szMarket   �г�
	@param pPositions �ֲ֣�����new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryHoldPositions_CF(const char* szMarket, UTI_FUT_Position*& pPositions,int& nItems);

	/**
	��ѯ�Ϻ��ڻ��г��ֲ�
	@parma szMarket   �г�
	@param pPositions �ֲ֣�����new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryHoldPositions_SH(const char* szMarket, UTI_FUT_Position*& pPositions,int& nItems);

	/**
	��ѯ֣���ڻ��г��ֲ�
	@parma szMarket   �г�
	@param pPositions �ֲ֣�����new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryHoldPositions_ZZ(const char* szMarket, UTI_FUT_Position*& pPositions,int& nItems);

	/**
	��ѯ�����ڻ��г��ֲ�
	@parma szMarket   �г�
	@param pPositions �ֲ֣�����new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryHoldPositions_DL(const char* szMarket, UTI_FUT_Position*& pPositions,int& nItems);


	/**
	��Ʒ�ֲ�ѯ
	@param szMarket   �г�
	@param szCode	  ����
	@param pPositions �ֲ֣�����new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryHoldPositions(const char* szCode,const char* szMarket,UTI_FUT_Position*& pPositions,int& nItems);


	/**
	��ɽ�(�ڲ�ʵ������¶�λ��)
	@param pMatch �ֲ֣�����new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryMatch(UTI_FUT_Match*& pMatch,int& nItems);


	/**
	�������ϴβ�ѯ��������µĳɽ����ڲ�ʵ������¶�λ����.
	@param pMatch �ֲ֣�����new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryNewMatch(UTI_FUT_Match*& pMatch,int& nItems);


	/**
	���г���ѯ�ɽ�
	@parma szMarket   �г�
	@param pMatch    �ɽ�������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryMatchByMarket(const char* szMarket, UTI_FUT_Match*& pMatch,int& nItems);

	/**
	��ѯ��ָ�ڻ��г��ɽ�
	@parma szMarket   �г�
	@param pMatch    �ɽ�������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryMatchByMarket_CF(const char* szMarket, UTI_FUT_Match*& pMatch,int& nItems);

	/**
	��ѯ�Ϻ��ڻ��г��ɽ�
	@parma szMarket   �г�
	@param pMatch    �ɽ�������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryMatchByMarket_SH(const char* szMarket, UTI_FUT_Match*& pMatch,int& nItems);

	/**
	��ѯ֣���ڻ��г��ɽ�
	@parma szMarket   �г�
	@param pMatch    �ɽ�������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryMatchByMarket_ZZ(const char* szMarket, UTI_FUT_Match*& pMatch,int& nItems);

	/**
	��ѯ�����ڻ��г��ɽ�
	@parma szMarket   �г�
	@param pMatch    �ɽ�������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryMatchByMarket_DL(const char* szMarket, UTI_FUT_Match*& pMatch,int& nItems);


	/**
	��Ʒ�ֲ�ѯ
	@param szMarket   �г�
	@param szCode	  ����
	@param pMatch    �ɽ�������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryMatch(const char* szCode,const char* szMarket,UTI_FUT_Match*& pMatch,int& nItems);



	/**
	����ͬ�Ų�ѯ
	@param  szOrderNumber   ��ͬ��
	@param pMatch    �ɽ�������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryMatch(const char* szOrderNumber,UTI_FUT_Match*& pMatch,int& nItems);


	/**
	��ί�м�¼��ѯ
	@param  pRecord   ί�м�¼
	@param pMatch    �ɽ�������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryMatch(const UTI_FUT_OrderRecord* pRecord,UTI_FUT_Match*& pMatch,int& nItems);


	/**
	����ͬ�źϲ���ѯ
	@param  szOrderNumber   ��ͬ��
	@param match    �ϲ���ĳɽ�
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryMatch_Merge(const char* szOrderNumber,UTI_FUT_Match& match);


	/**
	��ί�м�¼�ϲ���ѯ
	@param  pRecord   ί�м�¼
	@param match	  �ϲ���ĳɽ�
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryMatch_Merge(const UTI_FUT_OrderRecord* pRecord,UTI_FUT_Match& match);


	/**
	���ĳɽ�����
	@param bSubscribe  TRUE ���ĳɽ����ݣ�FALSE��ȡ������.
	*/ 
	bool SubscribeMatch(bool bSubscribe);

	/**
	���ĳɽ����ݵ�֪ͨ
	@param pMatch �ɽ�����
	@param nItmes  ��¼��
	@see SubscribeMatch
	*/
	virtual void OnNotifyMatch(const UTI_FUT_Match* pMatch,int nItmes){}


	/**
	��ί�м�¼
	@param pRecord	   ί�м�¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryOrderRecords(UTI_FUT_OrderRecord*& pRecord,int& nItems);



	/**
	��ָ���г���ί�м�¼
	@param szMarket   �г�	
	@param pRecord	   ί�м�¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryOrderRecords(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	��ѯ��ָ�ڻ��г�ί��
	@param szMarket   �г�	
	@param pRecord	   ί�м�¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryOrderRecords_CF(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	��ѯ�Ϻ��ڻ��г�ί��
	@param szMarket   �г�	
	@param pRecord	   ί�м�¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryOrderRecords_SH(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	��ѯ֣���ڻ��г�ί��
	@param szMarket   �г�	
	@param pRecord	   ί�м�¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryOrderRecords_ZZ(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	��ѯ�����ڻ��г�ί��
	@param szMarket   �г�	
	@param pRecord	   ί�м�¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryOrderRecords_DL(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	��ָ��Ʒ�ֵ�ί�м�¼
	@param szMarket   �г�
	@param szCode	  ����
	@param pRecord	   ί�м�¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryOrderRecords(const char* szCode,const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);




	/**
	����ͬ�Ų�ί��
	@param  szOrderNumber ��ͬ��
	@param  orderRecord   ί�м�¼
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryMatch_Merge(const char* szOrderNumber,UTI_FUT_OrderRecord& orderRecord);



	/**
	��ɳ�ί�м�¼
	@param pRecord	   ί�м�¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryCanCancel(UTI_FUT_OrderRecord*& pRecord,int& nItems);


	/**
	��ָ���г��Ŀɳ�ί�м�¼
	@param szMarket   �г�
	@param szCode	  ����
	@param pRecord	   ί�м�¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryCanCancel(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	��ѯ��ָ�ڻ��г��ɳ�ί��
	@param szMarket   �г�
	@param szCode	  ����
	@param pRecord	   ί�м�¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryCanCancel_CF(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	��ѯ�Ϻ��ڻ��г��ɳ�ί��
	@param szMarket   �г�
	@param szCode	  ����
	@param pRecord	   ί�м�¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryCanCancel_SH(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	��ѯ֣���ڻ��г��ɳ�ί��
	@param szMarket   �г�
	@param szCode	  ����
	@param pRecord	   ί�м�¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryCanCancel_ZZ(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);

	/**
	��ѯ�����ڻ��г��ɳ�ί��
	@param szMarket   �г�
	@param szCode	  ����
	@param pRecord	   ί�м�¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryCanCancel_DL(const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);


	/**
	��ָ��Ʒ�ֵĿɳ�ί�м�¼
	@param szMarket   �г�
	@param szCode	  ����
	@param pRecord	   ί�м�¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryCanCancel(const char* szCode,const char* szMarket,UTI_FUT_OrderRecord*& pRecord,int& nItems);


	/**
	����ͬ�Ų�ɳ�ί�м�¼
	@param  szOrderNumber ��ͬ��
	@param  orderRecord   ί�м�¼
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryCanCancel(const char* szOrderNumber,UTI_FUT_OrderRecord& orderRecord);



	/**
	������ʽ�
	@param dFreeCapital [out]���ؿ����ʽ�
	@param chCurrencyType ����, '0' ����� , '1' �۱�, '2' ��Ԫ
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/	
	bool QueryFreeCapital(double& dFreeCapital,char chCurrencyType='0');


	/**
	���ʲ�
	@param pAssets  �ʲ���¼������new���䣬�����߸���delte []��
	@param nItems	  ���ؼ�¼��.
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryAssets(UTI_FUT_Assets*& pAssets,int& nItems);


	/**
	�����ֲ��ʲ�
	@param chCurrencyType ����  '0' ����� , '1' �۱�, '2' ��Ԫ
	@param assets  �ʲ���¼��	
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryAssets(char chCurrencyType,UTI_FUT_Assets& assets);



	/**
	���ɽ�������ѯ
	@param pReq	 ���ɽ�������ѯ����
	@param iVolume	[out]������ɽ�����
	@return �ɹ�����TRUE�����򷵻�FALSE.
	*/
	bool QueryMaxBSVolume(const UTI_FUT_QueryMaxVolumeReq* pMaxVolReq,INT64& iVolume);



	/**
	��Լ��ѯ
	*/ 
	bool QueryAgreement(const char* szMarket,const char* szCode,UTI_FUT_Agreement& agreement);


	/**
	���㵥ȷ��.
	*/
	bool  ConfirmSettlement();

};
