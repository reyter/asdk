/**
* @Copyright �����д���Ƽ����޹�˾(www.hh.com.cn)
* @System	 (TDBHelper)
* @Brief	 TDB-API�����ӿ�.
* @Author	 ����
* @Date      2010-8-17
* @Usage 
	����  TDB_CreateHanler ����һ�����
	Ȼ��  ����  TDB_AddServer �����м����������ַ��
	����  TDB_Begin           ��ʼ�������Ӻ͵�¼��
	����  TDB_GetStatus       �������״̬��
	����  TDB_GetKData		  �ȴ�TDB�������Ͻ������ݡ�
	---ʹ�����ݡ�
	����  TDB_Release         �ͷŷ��ص������ڴ�(���룬���������ڴ�й©)
	����  TDB_End			  �ж�������������ӡ�
	����  TDB_DestroyHandler  ���پ��

* @History   
*	wli            2010-10-26             Modify.( �޸Ĵ����޸���ʳɽ�����������ע�� )
*/

#pragma once
#ifndef __TDBAPI_H__
#define __TDBAPI_H__

#ifndef _WINSOCK2API_
#include <winsock2.h>
#endif

#include "HDBApiDefine.h"
//#include "..\\include\\Common\\commlogger.h"


#ifdef _TDBHELPERLIB_
#define TDBAPI(type) _declspec(dllexport) type
#else	
#define TDBAPI(type) _declspec(dllimport) type
#endif


#ifdef __cplusplus
extern "C"
{
#endif


	/**
	*	TDB���������.
	*/
	typedef void*  HTDB;

	/**
	*	����һ�����������.
	*	@return �����������Ĵ�����.
	*/
	TDBAPI(HTDB) TDB_CreateHandler();

	/**
	*	����һ��������.
	*	@param handler Ҫ���ٵĴ�����.
	*/
	TDBAPI(void) TDB_DestroyHandler(HTDB hTdb);

	/**
	*	���TDB��������ַ.	������Ӷ��TDB��������ַ����ʵ�ֶ������֧��.
	*	������������һ��������ʧ��ʱ�����Զ����ӵ���һ��������
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
	*	@param szProxyPass	����. 
	*	@param lpUserName ���Ӹ÷�����ʱ����ʹ�õ��û���.
	*	@param lpPassword ���Ӹ÷�����ʱ����ʹ�õ����롣
	*	
	*/
	TDBAPI(int) TDB_AddServer(HTDB hTdb,
		LPCSTR lpServer,
		int nPort,				
		int nLevel,				//�������ȼ�.
		int  iProxyType,		//ʹ�õĴ�������.�޴���ʱΪ�� 
		char* szProxyHost,	//�����ַ, �޴���ʱΪ""
		int  iProxyPort,	//����˿�, �޴���ʱΪ0
		char* szProxyUser,	//�����û���, �޴���ʱΪ""
		char* szProxyPass,	//��������),�޴���ʱΪ""
		LPCSTR lpUserName,	//HDB�û���
		LPCSTR lpPassword	//HDB����
		);

	/**
	*	ȡ������������״̬.
	*	@param handler ������.
	*	@param pI64Send  [out]�����ֽ���
	*	@param pI64Recv  [out]�����ֽ���
	*	@Return          ״̬
	*					 0 δ����
	*					 1 ���ӽ���
	*					 2 ��½�ɹ�.
	*					 3 ���մ����������.
	*/
	TDBAPI(int)	TDB_GetStatus(HTDB hTdb,
		__int64 *pI64Send,
		__int64 *pI64Recv);

	/**
	*	ȡ�Է���ַ
	*	@param handler ������.
	*	@param pPeerAddr [out]���δ���ӣ������㡣����Է���ַ.
	*	@Return  �����Ƿ��Ѿ�����

	*/
	TDBAPI(int)	TDB_GetPeerAddr(HTDB hTdb,sockaddr_in *pPeerAddr);



	/**
	*	ȡ�Է���ַ
	*	@param handler ������.
	*	@param pszAddr [out]���Ի����������ӵĶԷ�Ŀ���ַ.
	*	@Return  �����Ƿ��Ѿ�����

	*/
	TDBAPI(int)	TDB_GetConnectingAddrString(HTDB hTdb,LPTSTR pszAddr,int nLength);


	/**
	*	��ʼ.
	*	����ʼ�������ݣ�����������.
	*	 @param handler  ������.
	*/
	TDBAPI(int) TDB_Begin(HTDB hTdb);

	/**
	*	�����Ͽ�������������ӡ������Ͽ��󣬲����Զ��������ӷ�������
	*   �����Ҫ�������ӣ����ٴε���<a href="#TDB_Begin">TDB_Begin</a>
	*	 @param handler  ������.
	*/
	TDBAPI(int) TDB_End(HTDB hTdb);



	/**
	*	��鵱ǰ����Ƿ���ָ���г�������.
	*	@param pszMarket �г�."SZ","SH","CF","SP"
	*/
	TDBAPI(int) TDB_BeSupportedMarket(HTDB hTdb,const char *pszMarket);

	/**
	*	��ȡK������.
	*	@param handler  ������.
	*	@param pRequestKData	��������.
	*	@param nItems			������������.
	*	@param pRetData			��������. (������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*	@param dwTimeOut			��ʱ.���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return					���ش�����. 0 ��ʾ�ɹ�������Ϊ������.
	*/
	TDBAPI(int) TDB_GetKData(HTDB hTdb,const HDBDefine_RequestKData *pRequestKData,
		int *pnItems,
		HDBDefine_KData **ppRetData,DWORD dwTimeOut);

	
	/**
	*	��ȡָ��K������.
	*	@param handler  ������.
	*	@param pRequestKData_Index	��������.
	*	@param nItems				[out]��������.
	*	@param pRetData				[out]��������.(������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*	@param dwTimeOut				��ʱ.���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return						���ش�����. 0 ��ʾ�ɹ�������Ϊ������.
	*/
	TDBAPI(int) TDB_GetKDataIndex(HTDB hTdb,const HDBDefine_RequestKData *pRequestKData_Index,
		int *pnItems,
		HDBDefine_KData_Index **ppRetData,DWORD dwTimeOut);

	
	/**
	*	��ȡTick����.
	*	@param handler  ������.
	*	@param pRequestTickData	��������.
	*	@param pnItems			[out]��������.
	*	@param pRetData			[out]��������.(������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*   @param dwTimeOut			��ʱ. ���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return					���ش�����. 0 ��ʾ�ɹ�������Ϊ������.
	*/
	TDBAPI(int) TDB_GetTickData(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickData,
		int *pnItems,
		HDBDefine_TickData **ppRetData,DWORD dwTimeOut);//Tick
	/**
	*	��ȡTick����������.
	*	@param handler  ������.
	*	@param pRequestTickABData	��������.
	*	@param pnItems				[out]��������.
	*	@param pRetData				[out]��������.(������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*   @param dwTimeOut				��ʱ.���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return ���ش�����. 0 ��ʾ�ɹ�������Ϊ������.
	*/
	TDBAPI(int) TDB_GetTickData_AB(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickABData,
		int *pnItems,
		HDBDefine_TickData_AB **ppRetData,DWORD dwTimeOut);//Tick
	/**
	*	��ȡTick�ۼƳɽ�������.
	*	@param handler  ������.
	*	@param pRequestTickACCData	��������.
	*	@param nItems				[out]��������.
	*	@param pRetData				[out]��������.(������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*   @param dwTimeOut				��ʱ.��ʱ.���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return						���ش�����.0 ��ʾ�ɹ�������Ϊ������.
	*/
	TDBAPI(int) TDB_GetTickData_ACC(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickACCData,
		int *pnItems,
		HDBDefine_TickData_ACC **ppRetData,DWORD dwTimeOut);//Tick
	/**
	*	��ȡTick�����̺��ۼƳɽ�������.
	*	@param handler  ������.
	*	@param pRequestTickABACCData	��������.
	*	@param pnItems					[out]��������.
	*	@param pRetData					[out]��������. (������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*   @param dwTimeOut					��ʱ.���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return ���ش�����.0 ��ʾ�ɹ�������Ϊ������.
	*/
	TDBAPI(int) TDB_GetTickData_ABACC(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickABACCData,
		int *pnItems,
		HDBDefine_TickData_AB_ACC **ppRetData,DWORD dwTimeOut);//Tick
	/**
	*	��ȡTickָ������.
	*	@param handler  ������.
	*	@param pRequestTickData_Index	��������.
	*	@param pnItems					[out]��������.
	*	@param pRetData					[out]��������.(������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*   @param dwTimeOut					��ʱ.���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return							���ش�����.0 ��ʾ�ɹ�������Ϊ������.
	*/
	TDBAPI(int) TDB_GetTickData_Index(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickData_Index,
		int *pnItems,
		HDBDefine_TickData_Index **ppRetData,DWORD dwTimeOut);//Tick
	/**
	*	��ȡTick����������ָ������.
	*	@param handler  ������.
	*	@param pRequestTickABData_Index	��������.
	*	@param pnItems					[out]��������.
	*	@param pRetData					[out]��������. (������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*   @param dwTimeOut					��ʱ.
	*	@Return							���ش�����.
	*/
	TDBAPI(int) TDB_GetTickABData_Index(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickABData_Index,
		int *pnItems,
		HDBDefine_TickData_Index **ppRetData,DWORD dwTimeOut);//Tick
	/**
	*	��ȡTick�ۼƳɽ���ָ������.
	*	@param handler  ������.
	*	@param pRequestTickACCData_Index	��������.
	*	@param pnItems						[out]��������.
	*	@param pRetData						[out]��������. (������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*   @param dwTimeOut						��ʱ.���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return								���ش�����.0 ��ʾ�ɹ�������Ϊ������.
	*/
	TDBAPI(int) TDB_GetTickACCData_Index(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickACCData_Index,
		int *pnItems,
		HDBDefine_TickData_Index_ACC **ppRetData,DWORD dwTimeOut);//Tick
	/**
	*	��ȡTick�����̺��ۼƳɽ���ָ������.
	*	@param handler  ������.
	*	@param pRequestTickABACCData_Index	��������.
	*	@param pnItems						[out]��������.
	*	@param pRetData						[out]��������. (������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*   @param dwTimeOut						��ʱ.���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return								���ش�����.0 ��ʾ�ɹ�������Ϊ������.
	*/
	TDBAPI(int) TDB_GetTickABACCData_Index(HTDB hTdb,const HDBDefine_RequestTickData *pRequestTickABACCData_Index,
		int *pnItems,
		HDBDefine_TickData_Index_ACC **ppRetData,DWORD dwTimeOut);//Tick
	
	
	
	
	
	/**
	*	��ȡ��ʳɽ�.
	*	@param handler  ������.
	*	@param pRequestSaveData	��������.
	*	@param pnItems			[out]��������.
	*	@param pRetData			[out]��������. (������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*   @param dwTimeOut			��ʱ.���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return ���ش�����.0 ��ʾ�ɹ�������Ϊ������.
	*/	
	TDBAPI(int) TDB_GetTransaction(HTDB hTdb,const HDBDefine_RequestSaveData *pRequestSaveData,
		int *pnItems,
		HDBDefine_Transaction **ppRetData,DWORD dwTimeOut);
	/**
	*	ί�ж�������.
	*	@param handler  ������.
	*	@param pRequestOrderQueue	��������.
	*	@param pnItems			[out]��������.
	*	@param pRetData			[out]��������. (������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*   @param dwTimeOut			��ʱ.���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return ���ش�����.0 ��ʾ�ɹ�������Ϊ������.
	*/	
	TDBAPI(int) TDB_GetOrderQueue(HTDB hTdb,const HDBDefine_RequestSaveData *pRequestOrderQueue,
		int *pnItems,
		HDBDefine_OrderQueue **ppRetData,DWORD dwTimeOut);
	/**
	*	���ί������.
	*	@param handler  ������.
	*	@param pRequestOrder	��������.
	*	@param pnItems			[out]��������.
	*	@param pRetData			[out]��������.(������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*   @param dwTimeOut			��ʱ.���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return ���ش�����.0 ��ʾ�ɹ�������Ϊ������.
	*/	
	TDBAPI(int) TDB_GetOrder(HTDB hTdb,const HDBDefine_RequestSaveData *pRequestOrder,
		int *pnItems,
		HDBDefine_Order **ppRetData,DWORD dwTimeOut);
	
	/**
	*	��ȡ��ʷ��������.
	*	@param handler  ������.
	*	@param pRequestMarketData	��������.
	*	@param pnItems				[out]��������.
	*	@param pRetData				[out]��������. (������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*   @param dwTimeOut				��ʱ.���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return						���ش�����.0 ��ʾ�ɹ�������Ϊ������.
	*/	
	TDBAPI(int) TDB_GetMarketData(HTDB hTdb,const HDBDefine_RequestMarketData *pRequestMarketData,
		int *pnItems,
		HDBDefine_MarketData **ppRetData,DWORD dwTimeOut);
	/**  
	*	��ȡ��Ȩ���䷽������.
	*	@param handler  ������.
	*	@param pRequestBaseData	��������.
	*	@param pnItems			[out]��������.
	*	@param pRetData			[out]��������. (������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*   @param dwTimeOut			��ʱ.���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return					���ش�����.0 ��ʾ�ɹ�������Ϊ������.
	*/	
	TDBAPI(int) TDB_GetBaseData_FP(HTDB hTdb,const HDBDefine_RequestBaseData *pRequestBaseData,
		int *pnItems,
		HDBDefine_BaseData_FP **ppRetData,DWORD dwTimeOut);
	/**
	*	��ȡ������Ϣ���ܱ�����.
	*	@param handler  ������.
	*	@param pRequestHZB		��������.
	*	@param pnItems			[out]��������.
	*	@param pRetData			[out]��������.    (������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*   @param dwTimeOut			��ʱ.���룬INFINITE ��ʾһֱ�ȴ���
	*	@Return					���ش�����.0 ��ʾ�ɹ�������Ϊ������.
	*/
	TDBAPI(int) TDB_GetHZB_BaseInfo(HTDB hTdb,const HDBDefine_RequestHZB *pRequestHZB,
		int *pnItems,
		HDBDefine_HZB_BaseInfo **ppRetData,DWORD dwTimeOut);

	/**
	*	��ȡ�����.
	*	@param handler  ������.
	*	@param pnItems			[out]��������.
	*	@param pRetData			[out]��������.    (������� ����� TDB_Release(*pRetData) �ͷ��ڴ� )
	*	@Return					���ش�����.0 ��ʾ�ɹ�������Ϊ������.
	*
	**/
	TDBAPI(int) TDB_GetCodeTable(HTDB hTdb,int *pnItems,
		HDBDefine_SecurityCode **ppRetData);

	/**
	 *	��ȡ�����Ϣ
	 *	@param	hTdb			[IN]TDB���������
	 *	@param	ppSectorArr		[OUT]�����Ϣ.
	 *	@param	pnItems			[OUT]��¼��Ŀ.
	 *	@return �ɹ�����0,���󷵻ش������.
	 */
	TDBAPI(int) TDB_GetSector(HTDB hTdb,HDBDefine_Sector **ppSectorArr,int *pnItems);

	/**
	 *	��ȡ���Ĵ����
	 *	@param	hTdb		[IN]TDB���������
	 *	@param	pRequest	[IN]����.  
	 *	@param	ppCodeArr	[OUT]�����.
	 *	@param	pnItems		[OUT]��¼��Ŀ.
	 *	@return �ɹ�����0,���󷵻ش������.
	 */
	TDBAPI(int) TDB_GetSectorCodeTable(HTDB hTdb,HDBDefine_RequestSectorCodeTable *pRequest,HDBDefine_SecurityCode **ppCodeArr,int *pnItems);

	/**
	 *	�ϴ�ָ��
	 *	@param	hTdb		[IN]TDB���������
	 *	@param	lpszEZFName			ָ������
	 *	@param	lpszEZFContent		ָ������
	 *	@return �ɹ�����0.
	 */
	TDBAPI(int) TDB_AddEZFormula(HTDB hTdb,LPCTSTR lpszEZFName,LPCTSTR lpszEZFContent);

	/**
	 *	ɾ��ָ��
	 *	@param	hTdb		[IN]TDB���������
	 *	@param	lpszEZFName			ָ������
	 *	@return �ɹ�����0.
	 */
	TDBAPI(int) TDB_DeleteEZFormula(HTDB hTdb,LPCTSTR lpszEZFName);


	/**
	 *	��ȡ�������ϵ�ָ��
	 *	?@param	hTdb		[IN]TDB���������
	 *	@param	lpszEZFName			ָ������(��ָ�����������)
	 *	@return �ɹ�����0.
	 */
	TDBAPI(int) TDB_GetEZFormula(HTDB hTdb,LPCTSTR lpszEZFName,HDBDefine_EZFormula_Item **ppEZF,int *pnItems);

	/**
	 *	��ȡָ�����Ľ��
	 *	?@param	hTdb			[IN]TDB���������
	 *	@param	pEZFCalc		Ҫ�����ָ��������Ϣ
	 *	@param	pCalcResult		ָ�����еĽ�� ��������ʹ�ú�ǵ���TDB_ClearEZFResult������
	 *	@return �ɹ�����0.
	 */
	TDBAPI(int) TDB_GetCalcEZFormulaResult(HTDB hTdb,HDBDefine_EZFormula_Calc *pEZFCalc,HDBDefine_EZFormula_ResultData *pCalcResult);

	/**
	 *	���ָ������
	 *	@param	hTdb		[IN]TDB���������
	 *	@param	pEZFResult Ҫ�����ָ�����н������
	 */
	TDBAPI(int) TDB_ClearEZFResult(HTDB hTdb,HDBDefine_EZFormula_ResultData *pEZFResult);

	//////////////////////////////////////////////////////////////////////////
	//�¼��ص�

	/**
	*	TDB�ж�ʱ�ص�����ԭ��.
	*	@return �������TRUE����API���µ�¼����.
	*			�������FALSE��API���ٽ�����������.
	*/
	typedef bool (CALLBACK* ON_TDB_DISCONNECT_HANDLER)(HTDB /*hTdb*/);

	/**
	*	TDB��¼����ص�����ԭ��.
	*/
	typedef void (CALLBACK* ON_TDB_LOGINRESULT_HANDLER)(HTDB /*hTdb*/,const HDBDefine_LoginAnswer * /*pAnswer*/);
	
	/**
	*	���������ж�ʱ�Ĵ�����.
	*	����֮ǰ���жϴ�����.Ĭ���жϺ��������κδ�������TRUE���Ա�������һ������.
	*	@param tdfHandler  ������.
	*	@param pHandler	   �ж��¼�������	.
	*/
	TDBAPI(ON_TDB_DISCONNECT_HANDLER)  TDB_SetOnTDBDisconnectHandler(HTDB hTdb,
		ON_TDB_DISCONNECT_HANDLER pHandler);

	/**
	*	���õ�¼����Ĵ�����.
	*	����֮ǰ�ĵ�¼���������,ϵͳĬ��ΪNULL,������.
	*	@param tdfHandler  ������.
	*	@param pHandler	   ��¼Ӧ���¼�������	.
	*/
	TDBAPI(ON_TDB_LOGINRESULT_HANDLER)  TDB_SetOnTDBLoginResultHandler(HTDB hTdb,
		ON_TDB_LOGINRESULT_HANDLER pHandler);

	/**
	*	�ͷ��ڴ�.
	*	@param pRetData Ҫ�ͷŵ��ڴ�ָ��
	*/
	TDBAPI(int) TDB_Release(void *pRetData);


	

	/**
	*	��ȡ��������Ϣ.
	*	@param nErrorCode �������.
	*/
	TDBAPI(LPCTSTR) TDB_GetError(int nErrorCode);


	
	/**
	* TDB ��־��¼
	*/
	//DECLARE_COMMON_LOG_FUN(TDB,TDBAPI);

	/**
	* ������־��¼����.
	*/
	//DECLARE_COMMON_LOG_FUN(TDF,TDFAPI);
	typedef void (CALLBACK* TDB_LOG_FUN)(LPCTSTR,LPVOID);

	/**
	* ����TDB��־��¼
	* @param pFun ��־��¼����
	* @param lParam �ص�����־��¼�����Ĳ���
	*/
	TDBAPI(void) TDB_SetLogFun(TDB_LOG_FUN pFun,LPVOID lParam);


#ifdef __cplusplus
}
#endif
#endif //__TDBAPI_H__