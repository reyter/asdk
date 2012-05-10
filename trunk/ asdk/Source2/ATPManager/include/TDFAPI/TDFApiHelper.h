/**
* @Copyright �����д���Ƽ����޹�˾(www.hh.com.cn)
* @System	 ���TDFϵͳ(Transend Data Feed System)
* @Brief	 ���������ϵͳAPI�����ӿ�.
* @Author	 ���� ������
* @Date      2010-10-8
*
*	֧�ֶ���ͬʱ���ӡ����������ַ��
* ʹ�÷���, 
*   ���ȣ����� TDF_CreateHandler ���������
*   Ȼ�󣬵��� TDF_AddServer    ���������÷�����������Ϣ.
*   ������Ҫ  TDF_SetRequestDate��TDF_SetRequestMarkets,
*   ���� TDF_SetOnTDFRecvDataHandler ���ûص��¼������� ��
*	���� TDF_SaveSnapshot ָʾ�Ƿ�Ҫ�������
*	���� TDF_Begin ��ʼ
*	API ���ûص���֪ͨ���ݵ��
*	���� TDF_End ����
*	���� TDF_DestroyHandler ���پ�����ͷ���Դ.
*/
#pragma once

#ifndef _TDFAPIHELPER_H_
#define _TDFAPIHELPER_H_

#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif

#include "TDFApiDefine.h"
//#include "..\\Include\\Common\\CommLogger.h"


#ifdef _TDFAPILIB
#define TDFAPI(type)  type __declspec(dllexport) 
#else
#define TDFAPI(type)  type __declspec(dllimport) 
#endif

#ifdef __cplusplus
extern "C"
{
#endif



#pragma pack(push,1)

struct TDF_API_ReqMarkets
{
	/**
	*	Ҫ������г�����"SZ","SH","CF"��.
	*/ 
	char chMarket[4];

	/**
	*   ������г���־,�������������ݵ����.(ϵͳĬ�ϻ���ѹ����ʽ����)
	*   ID_HDFDATAFLAGS_RETRANSALTE		 ���ݴ�ͷ���ͣ��������������տ���ǰ���ͣ����������ʱ�㴫������.��
	*	ID_HDFDATAFLAGS_NOTRANSACTION    ��������ʳɽ�����
	*   ID_HDFDATAFLAGS_NOABQUEUE        ������ί�ж�������
	*	ID_HDFDATAFLAGS_NOINDEX          ������ָ������
	*/
	DWORD dwFlag;
};

/**
*	��ȡ��������ṹ��.
*/
typedef struct tagTDF_GetBacthMarketData
{
	/**
	*	Ҫ������г�����"SZ","SH","CF"��.
	*/ 
	char szMarket[4];
	/**
	*	����,��:600000.
	*/ 
	char szCode[8];

	/**
	*	��������.���ص�����.
	*/
	TDFDefine_MarketData marketData;

	/**
	* �������,�ɹ�Ϊ0;
	*/
	int nError;
}TDF_GetBacthMarketData;

/**
*	��ȡ������ָ�ڻ�����ṹ��.
*/
typedef struct tagTDF_GetBacthMarketDataFutures
{
	/**
	*	Ҫ������г�����"SZ","SH","CF"��.
	*/ 
	char szMarket[4];
	/**
	*	����,��:600000.
	*/ 
	char szCode[8];

	/**
	*	��������.���ص�����.
	*/
	TDFDefine_MarketData_Futures marketData;

	/**
	* �������,�ɹ�Ϊ0;
	*/
	int nError;
}TDF_GetBacthMarketDataFutures;

/**
*	��ȡ����ָ������ṹ��.
*/
typedef struct tagTDF_GetBacthMarketDataIndex
{
	/**
	*	Ҫ������г�����"SZ","SH","CF"��.
	*/ 
	char szMarket[4];
	/**
	*	����,��:600000.
	*/ 
	char szCode[8];

	/**
	*	��������.���ص�����.
	*/
	TDFDefine_IndexData marketData;

	/**
	* �������,�ɹ�Ϊ0;
	*/
	int nError;
}TDF_GetBacthMarketDataIndex;

#pragma pack(pop)


/**
*	TDF���������.
*/
typedef void*  HTDF;

/**
*	����һ�����������.
*	@return �����������Ĵ�����.
*/
TDFAPI(HTDF) TDF_CreateHandler();

/**
*	����һ��������.
*	@param handler Ҫ���ٵĴ�����.
*/
TDFAPI(int) TDF_DestroyHandler(HTDF hTdf);

/**
*	���TDF��������ַ.	������Ӷ��TDF��������ַ����ʵ�ֶ������֧��.
*	������������һ��������ʧ��ʱ��
*	���Զ����ӵ���һ��������
*	��������˳������ӵ�˳����ͬ.
*	@param handler  ������.
*	@param chServer ��������ַ��������IP������������
*   @param nPort	�������˿�.
*	@param nLevel   �������������ȼ�,nLevelֵԽ����Խ�����������ӣ�
*					�ɽ�Level2�������������ȼ����ô�һЩ,��Level1��������ȼ�����Ϊ���.
*	@param iProxyType ʹ�õĴ�������<br>	
<li>0			��ʹ�ô���.
<li>1			SOCK4
<li>2			SOCK4A
<li>3			SOCK5
<li>4			HTTP1.1
*	@param szProxyHost	�����������ַ. 
*   @param iProxyPort	����������˿�. 
*	@param szProxyUser  �û��� ���û�������ʱ��Ϊ�㳤���ַ���"" .
*	@param lpUserName ���Ӹ÷�����ʱ����ʹ�õ��û���.
*	@param lpPassword ���Ӹ÷�����ʱ����ʹ�õ����롣
*	
*/
TDFAPI(int) TDF_AddServer(HTDF hTdf,
						   LPCSTR lpServer,
						   int nPort,
						   int nLevel,
							int  iProxyType,		//ʹ�õĴ�������.�޴���ʱΪ�� 
							char* szProxyHost,	//�����ַ, �޴���ʱΪ""
							int  iProxyPort,	//����˿�, �޴���ʱΪ0
							char* szProxyUser,	//�����û���, �޴���ʱΪ""
							char* szProxyPass,	//��������),�޴���ʱΪ""
						    LPCSTR lpUserName,
						   LPCSTR lpPassword
						   );

/**
*	�����������������,�������øú�������Ĭ������������յ�����.
*	@param handler  ������.
*	��ΪTDF����֧�����ݻ��ݣ����øù��ܣ������ɶ���ʷ���ݵĻ���.
*	@param nDate	Ҫ���ʵ���������, ��ʽ��YYYYMMDD ,�� 20101008
*	@param dSpeed   �ط�ʱ�ı���.��СΪ1����С��1ʱ��ϵͳ���Զ���Ϊ1����ϵͳ��IO���������㣬������
*					֧�ֵı���ʱ����ϵͳ������ٶȲ��š�
*/
TDFAPI(int) TDF_SetRequestDate(HTDF hTdf,int nDate,double dSpeed);

/**
*	����Ҫ�������ݵ��г�.
*	@param handler  ������.
*	@param pMarkets �������ݵ��г�����־,������.
*	@param nItems   ��¼��.
*	@remark �ܷ��ʵ��г����ݣ������ܷ������ϵ��������ݣ�����ʹ�õ��ʺŵ����Ȩ�޵�����.
*			��������ô˺�������Ĭ��������ʺ�֧�ֵ������г���
*/ 
TDFAPI(int) TDF_SetRequestMarkets(
	HTDF hTdf,
	TDF_API_ReqMarkets* pMarkets,
	int nItems
	);

/**
*	 ���ö���,ϵͳĬ������������Ĳ�����Ȩ�޵��г���ȫ��Ʒ�ֵ�����.
*	 �����ö��ĺ�ϵͳֻ����������Ʒ�ֵ����ݣ��Խ�ʡ�������.
*	 @param handler  ������.
*	 @param nSubscriptionType	���ķ�ʽ: 0������  1:����  2:ɾ��  3: ��ԭ.
*	 @param pData  �����������ݵ���ʼ��ַ.
*	 @param nItems ��������.
*	 @remark  �� nSubscriptionType = 3 ʱ����ȡ��Ϣ���ж��ģ��ָ�Ϊ������������. 
*/
TDFAPI(int) TDF_SetSubscription(
								HTDF hTdf,
								int nSubscriptionType,
								TDFDefine_SubscriptionData* pData,
								int nItems
								);


//---------------------------------------------------------------------
//�¼��ص�

/**
*	TDF״̬�ı�ʱ�Ļص�����.
*	@param	nStatus  ����״̬.
*					 0  ��δ����
*					 1  �Ѿ���������
*					 2  �Ѿ���¼�ɹ�
*					 3  ���մ��������
*					 4  ���ڽ�������.
*/
typedef bool (CALLBACK *ON_TDF_STATUS_CHANGED)(HTDF hTdf,int nStatus);

/**
*	TDF�ж�ʱ�ص�����ԭ��.
*	@return �������TRUE����API���µ�¼����.
*			�������FALSE��API���ٽ�����������.
*/
typedef bool (CALLBACK* ON_TDF_DISCONNECT_HANDLER)(HTDF /*handler*/);

/**
*	TDF��¼����ص�����ԭ��.
*/
typedef void (CALLBACK* ON_TDF_LOGINRESULT_HANDLER)(HTDF /*handler*/,const TDFDefine_LoginAnswer* /*pAnswer*/);

/**
*	���յ�����TDF�����������ݻص�֪ͨ����.
*	@param handler ������.
*	@param pHead ��Ϣͷ.
*	@param pApplicationHead Ӧ��ͷ��ͨ��ָ���������ݵ�����\��ʶ\��¼���ȡ�ĳ����Ϣ�޴�Ӧ��ͷ���ʴ˲�������ΪNULL.
*	@param nApplicationHeadSize Ӧ��ͷ����,����Ϊ��.
*	@param pData ��ѹ������ݵ���ʼλ��.�������ͣ������ pHead �� sDataType ��ֵ������ת��.
*				����sDataType����������Ϣ��ʽ���ɲμ� �ӿ�pdf �� ʾ������.
*	@param nItemSize ÿһ����¼�Ĵ�С.
*	@param nItems ��¼��.
*/
typedef void (CALLBACK* ON_TDF_RECV_DATA_HANDLER)(
												  HTDF /*handler*/,
												  const TDFDefine_MsgHead* /*pHead*/,//��Ϣͷ�г��õ����ݳ�ԱsDataType��nTime.sDataTypeָ����������.����Ĳ���,����sDataType��ǿ��ת��Ϊ��Ӧ�Ľṹ.nTimeΪ�������������ݵĻ���ʱ��,��ʽΪHHMMSSmmm.
												  const void* /*pApplicationHead*/,
												  int /*nApplicationHeadSize*/,
												  const void* /*pData*/,
												  int /*nItemSize*/,
												  int /*nItems*/
												  );

/**
*	����TDF״̬�ı�Ĵ�����.
*	@param HTDF  ������.
*/
TDFAPI(ON_TDF_STATUS_CHANGED) TDF_SetOnStatusChanged(HTDF hTdf,ON_TDF_STATUS_CHANGED pHandler);

/**
*	���������ж�ʱ�Ĵ�����.
*	����֮ǰ���жϴ�����.Ĭ���жϺ��������κδ�������TRUE���Ա�������һ������.
*	@param HTDF  ������.
*	@param pHandler	   �ж��¼�������	.
*/
TDFAPI(ON_TDF_DISCONNECT_HANDLER)  TDF_SetOnTDFDisconnectHandler(HTDF hTdf,ON_TDF_DISCONNECT_HANDLER pHandler);
/**
*	���õ�¼����Ĵ�����.
*	����֮ǰ�ĵ�¼���������,ϵͳĬ��ΪNULL,������.
*	@param HTDF  ������.
*	@param pHandler	   ��¼Ӧ���¼�������	.
*/
TDFAPI(ON_TDF_LOGINRESULT_HANDLER)  TDF_SetOnTDFLoginResultHandler(HTDF hTdf,ON_TDF_LOGINRESULT_HANDLER pHandler);
/**
*	���ý��յ������ݴ�����.
*	����֮ǰ�����ݴ�����. ϵͳĬ��ΪNULL��������.
*	@param HTDF  ������.
*	@param pHandler	   ���յ����ݵĴ�����	.
*/
TDFAPI(ON_TDF_RECV_DATA_HANDLER)  TDF_SetOnTDFRecvDataHandler(HTDF hTdf,ON_TDF_RECV_DATA_HANDLER pHandler);
//------------------------------------------------------------------------

/**
*	��ʼ
*	����ʼ�������ݣ�����������.
*	 @param handler  ������.
*/
TDFAPI(int) TDF_Begin(HTDF hTdf);

/**
*	�����Ͽ�������������ӡ������Ͽ��󣬲����Զ��������ӷ�������
*   �����Ҫ�������ӣ����ٴε���<a href="#TDF_Begin">TDF_Begin</a>
*	 @param handler  ������.
*/
TDFAPI(int) TDF_End(HTDF hTdf);

/**
*	�Ƿ�Ҫ����������ա��˺������� ���е� TDF_Begin ֮ǰ���á�
*	����������պ󣬿�ʹ�� 
*	TDF_GetLastMarketData ��TDF_GetLastMarketData_Index �� TDF_GetLastMarketData_Futures ��ѯ���µ�������ա�
*	@param bSave �Ƿ���API����ÿ��Ʒ�ֵ���������������ڴ��С�
*/
TDFAPI(int) TDF_SaveSnapshot(bool bSave);


/**
* �������������������״̬
* �����ڻ���ʱ������ĳ����ɺ���øú���,Ȼ���������һ�յ�����.
*
*/
TDFAPI(void) TDF_Clear();



/**
*	��ѯ���µ���������.
*	@param  lpMarket �г�
*	@param  lpCode   ����
*	@param  pMarketData  [out]�������µ����顣
*	@return �����ȡ�ɹ����򷵻�0,���򣬷��ط��㡣
*/
TDFAPI(int) TDF_GetLastMarketData(
		LPCSTR lpMarket,
		LPCSTR lpCode,
		TDFDefine_MarketData *pMarketData
		);

/**
*	��ѯָ�����µ���������.
*	@param  lpMarket �г�
*	@param  lpCode   ����
*	@param  pMarketData  [out]�������µ����顣
*	@return �����ȡ�ɹ����򷵻�0,���򣬷��ط��㡣
*/
TDFAPI(int) TDF_GetLastMarketData_Index(
		LPCSTR lpMarket,
		LPCSTR lpCode,
		TDFDefine_IndexData *pMarketData
		);

/**
*	��ѯ�ڻ�Ʒ�����µ���������.
*	@param  lpMarket �г�
*	@param  lpCode   ����
*	@param  pMarketData  [out]�������µ����顣
*	@return �����ȡ�ɹ����򷵻�0,���򣬷��ط��㡣
*/
TDFAPI(int) TDF_GetLastMarketData_Futures(
	LPCSTR lpMarket,
	LPCSTR lpCode,
	TDFDefine_MarketData_Futures *pMarketData
	);

/**
*	������ѯ���µ���������.
*	@param  pTdfGetBatchMarketData ��������.
*	@param	nItems				����.
*/
TDFAPI(int) TDF_GetBatchLastMarketData(
	TDF_GetBacthMarketData *pTdfGetBatchMarketData,
	int nItems
	);

/**
*	������ѯ��ָ�ڻ����µ���������.
*	@param  pTdfGetBatchMarketData ��������.
*	@param	nItems				����.
*/
TDFAPI(int) TDF_GetBatchLastMarketDataFutures(
	TDF_GetBacthMarketDataFutures *pTdfGetBatchMarketData,
	int nItems
);

/**
*	������ѯָ�����µ���������.
*	@param  pTdfGetBatchMarketData ��������.
*	@param	nItems				����.
*/
TDFAPI(int) TDF_GetBatchLastMarketDataIndex(
	TDF_GetBacthMarketDataIndex *pTdfGetBatchMarketData,
	int nItems
	);

/**
*	��ȡ�����.
*	@param  lpMarket �г�
*	@param nItems ��������.
*	@param pRetData ��������.
*
**/
TDFAPI(int) TDF_GetCodeTable(
	LPCSTR lpMarket,
	int *pnItems,
	TDFDefine_SecurityCode **pRetData
	);

/**
*	ȡ������������״̬.
*	@param handler ������.
*	@param pI64Send  [out]�����ֽ���
*	@param pI64Recv  [out]�����ֽ���
*	@Return          ���ص�ǰ״̬
*					 0  ��δ����
*					 1  �Ѿ���������
*					 2  �Ѿ���¼�ɹ�
*					 3  ���մ��������
*					 4  ���ڽ�������..
*/
TDFAPI(int)	TDF_GetStatus(HTDF hTdf,__int64 *pI64Send = NULL,__int64 *pI64Recv = NULL);

/**
*	ȡ�Է���ַ
*	@param handler ������.
*	@param pPeerAddr [out]���δ���ӣ������㡣����Է���ַ.
*	@Return  �����Ƿ�ɹ���ȡ�����ַ.

*/
TDFAPI(int)	TDF_GetPeerAddr(HTDF hTdf,sockaddr_in *pPeerAddr);
/**
*	ȡ�Է���ַ
*	@param hTdf ������.
*	@param pszAddr [out]���Ի����������ӵĶԷ�Ŀ���ַ.
*	@Return  �����Ƿ��Ѿ�����

*/
TDFAPI(int)	TDF_GetConnectingAddrString(HTDF hTdf,LPTSTR pszAddr,int nLength);

/**
*	�ͷ��ڴ�.
*/
TDFAPI(int)	TDF_Release(void *pData);

/**
*	��ȡ�����ַ���.
*	@param	nErrorCode	����ֵ.
*	@return ���ش���˵�����ַ���.
*/
TDFAPI(LPCTSTR) TDF_GetError(int nErrorCode);

/**
*	��ȡ�ɶ�����.
*	@param lpszMarket	�г����� SZ SH
*	@param lpszSecCode	֤ȯ���� 600000 000001
*	@return ���عɶ�����.1:����A��,2:����B��,3:�Ϻ�A��,4:�Ϻ�B��. 5:��ָ�ڻ� 6 �Ϻ��ڻ� 7 ֣���ڻ� 8 �����ڻ�
*    �Ҳ����򷵻�-1
*   @remark ����TDF���յ��Ĵ����������жϡ�
*/
TDFAPI(int) TDF_GetHolderType(LPCTSTR lpszMarket,LPCSTR lpszSecCode); 

/**
*	��ȡ֤ȯ����.
*	@param lpszMarket	�г����� SZ SH
*	@param lpszSecCode	֤ȯ���� 600000 000001
*	@return ����֤ȯ����.
*	֤ȯ����
*	�������ࣨλ���жϣ�
*	0x80000000 ����(��Ȩ֤�Ĺ�Ʊ)
*	0x00 ָ��
*	0x10 ��Ʊ
*	0x20 ����
*	0x30 ծȯ & ��תծ
*	0x40 �ع�
*	0x60 Ȩ֤
*	0x70 �ڻ�
*	0x80 ���
*	0xd0 ��������
*	0xe0 ���
*/
TDFAPI(int) TDF_GetSecurityType(LPCTSTR lpszMarket,LPCSTR lpszSecCode,int *pnType); 

/**
*	�����г���������������������ʱ��.
*	@param lpszMarket	�г����� SZ SH
*	@return ����ʱ�� ��ʽΪ:HHMMSS.
*/
TDFAPI(int) TDF_GetLastMarketTime(LPCTSTR lpszMarket);


/**
*	�����г��ο�ʱ��.
*	@param lpszMarket	�г����� SZ SH
*	@return ����ʱ�� ��ʽΪ:HHMMSS.
*   @remark ע����ʱ��������ʱ���뱾��ʱ���ϼ��㡣�����ܱ�֤��ʱ�����ȫ��ȷ.����ʹ��.
*			������������ʱ�䣬δ�ﵽ���뼶ʱ���ο�ʱ�����Ƶ�ʣ��Ը��� TDF_GetLastMarketTime �ĸ���Ƶ��.
*   ע�⣬���ط��ٶ�С��1λ��ʱ���벻Ҫʹ�øú���.
*/
TDFAPI(int) TDF_GetMarketReferenceTime(LPCTSTR lpszMarket);



/**
*	������������
*/
TDFAPI(int) TDF_GetLastMarketDate(LPCTSTR lpszMarket);

/**
* ������־��¼����.
*/
//DECLARE_COMMON_LOG_FUN(TDF,TDFAPI);

typedef void (CALLBACK* TDF_LOG_FUN)(LPCTSTR,LPVOID);

/**
* ����TDF��־��¼
* @param pFun ��־��¼����
* @param lParam �ص�����־��¼�����Ĳ���
*/
TDFAPI(void) TDF_SetLogFun(TDF_LOG_FUN pFun,LPVOID lParam);



#ifdef __cplusplus
}
#endif


#endif //_TDFAPIHELPER_H_