#pragma once

#include "UTIDefine_Sec.h"
#include "UTIApiHelper.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
*	UTI֤ȯ���׾��.
*/
typedef void*  HUTI_SEC;

/**
*	�ص�����Ϣ����(֤ȯ)
*/
enum UTI_SEC_UPDATE_TYPE
{
	/**
	*	�ֲ���Ϣ
	*/
	UTI_SEC_UPDATE_POSITION = 0,	
	/**
	*	�ɽ���Ϣ
	*/
	UTI_SEC_UPDATE_MATCH = 1,
	/**
	*	ί����Ϣ
	*/
	UTI_SEC_UPDATE_ORDER = 2,
	/**
	*	�ʽ���Ϣ
	*/
	UTI_SEC_UPDATE_ASSETS = 3,
	/**
	*	�ɳ�����Ϣ
	*/
	UTI_SEC_UPDATE_CANCANCEL = 4
};

/**
*	��Ϣ���»ص�����(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param nType ��Ϣ����.
*	@param lParam ������Ϣ��ԭֵ����.
*/
typedef void (CALLBACK* LP_UTI_SEC_UPDATE_CALLBACK_FUN)(HUTI_SEC /*handler*/,UTI_SEC_UPDATE_TYPE /*nType*/,LPVOID /*lParam*/);

/**
*	����֤ȯ���׾��.
*	@return ������������֤ȯ���׾��.
*/
UTIAPI(HUTI_SEC) UTI_SEC_CreateHandler();

/**
*	����֤ȯ���׾��.
*	@param handler Ҫ���ٵ�֤ȯ���׾��.
*	@return ���ٳɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_DestroyHandler(HUTI_SEC handler);

/**
*	������Ϣ���»ص�����(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param nType ��Ϣ����.
*	@param lParam ������Ϣ��ԭֵ����.
*	@return ���óɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_SetUpdateCallBackFun(HUTI_SEC handler,LP_UTI_SEC_UPDATE_CALLBACK_FUN pFun,LPVOID lParam);

/**
*	������½�˺���Ϣ(֤ȯ).
*	@param handlerTo ��д���֤ȯ���׾��.
*	@param handlerFrom ��������֤ȯ���׾��.
*	@return �����ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_CopyHandler(HUTI_SEC handlerTo, HUTI_SEC handlerFrom);

/**
*	��¼(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param pLogin ��¼����.
*	@param pLoginAnswer [out]��¼Ӧ��.
*	@return ��¼�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_Login(HUTI_SEC handler, const UTI_LoginRequest* pLogin,UTI_LoginAnswer* pLoginAnswer);

/**
*	�ǳ�(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@return �ǳ��ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_Logout(HUTI_SEC handler);

/**
*	֤ȯ����.
*	@param handler ֤ȯ���׾��.
*	@param lpszCode ����.
*	@param lpszMarket �г�.
*	@param nHolderType �ɶ�����.
<table border="1">
<tr><td>1</td><td>����A��.</td></tr>
<tr><td>2</td><td>����B��.</td></tr>
<tr><td>3</td><td>�Ϻ�A��.</td></tr>
<tr><td>4</td><td>�Ϻ�B��.</td></tr>
</table>
*	@param nPrice �۸񣬷Ŵ�10000����������ʾ�޼ۣ�������ʾ�м�ί�з�ʽ.
<table border="1">
<tr><td>-1</td><td>�Է����ż۸�.</td></tr>
<tr><td>-2</td><td>�������ż۸�.</td></tr>
<tr><td>-3</td><td>��ʱ�ɽ�ʣ�೷��.</td></tr>
<tr><td>-4</td><td>�嵵�ɽ�ʣ�೷��.</td></tr>
<tr><td>-5</td><td>ȫ��ɽ�����.</td></tr>
<tr><td>-6</td><td>�嵵�ɽ�ʣ���ּ�.</td></tr>
</table>
*	@param nVolume ί����.
*	@param szOrderNumber [out]���غ�ͬ��.
*	@param nLenOrderNumber szOrderNumber�ĳ��ȣ���������28λ.
*	@param lpszOrderGroup �������µ�.
*	@return �µ��ɹ��򷵻�0�����򷵻�����ֵ.
*/ 
UTIAPI(int) UTI_SEC_Buy(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,int nPrice,int nVolume,char* szOrderNumber,int nLenOrderNumber,LPCSTR lpszOrderGroup);

/**
*	֤ȯ����.
*	@param handler ֤ȯ���׾��.
*	@param lpszCode ����.
*	@param lpszMarket �г�.
*	@param nHolderType �ɶ�����.
<table border="1">
<tr><td>1</td><td>����A��.</td></tr>
<tr><td>2</td><td>����B��.</td></tr>
<tr><td>3</td><td>�Ϻ�A��.</td></tr>
<tr><td>4</td><td>�Ϻ�B��.</td></tr>
</table>
*	@param nPrice �۸񣬷Ŵ�10000����������ʾ�޼ۣ�������ʾ�м�ί�з�ʽ.
<table border="1">
<tr><td>-1</td><td>�Է����ż۸�.</td></tr>
<tr><td>-2</td><td>�������ż۸�.</td></tr>
<tr><td>-3</td><td>��ʱ�ɽ�ʣ�೷��.</td></tr>
<tr><td>-4</td><td>�嵵�ɽ�ʣ�೷��.</td></tr>
<tr><td>-5</td><td>ȫ��ɽ�����.</td></tr>
<tr><td>-6</td><td>�嵵�ɽ�ʣ���ּ�.</td></tr>
</table>
*	@param nVolume ί����.
*	@param szOrderNumber [out]���غ�ͬ��.
*	@param nLenOrderNumber szOrderNumber�ĳ��ȣ���������28λ.
*	@param lpszOrderGroup �������µ�.
*	@return �µ��ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_Sell(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,int nPrice,int nVolume,char* szOrderNumber,int nLenOrderNumber,LPCSTR lpszOrderGroup);

/**
*	�깺.
*	@param handler ֤ȯ���׾��.
*	@param lpszCode ����.
*	@param lpszMarket �г�.
*	@param nHolderType �ɶ�����.
<table border="1">
<tr><td>1</td><td>����A��.</td></tr>
<tr><td>2</td><td>����B��.</td></tr>
<tr><td>3</td><td>�Ϻ�A��.</td></tr>
<tr><td>4</td><td>�Ϻ�B��.</td></tr>
</table>
*	@param nVolume ί����.
*	@param szOrderNumber [out]���غ�ͬ��.
*	@param nLenOrderNumber szOrderNumber�ĳ��ȣ���������28λ.
*	@return �µ��ɹ��򷵻�0�����򷵻�����ֵ.
*/ 
UTIAPI(int) UTI_SEC_ETFPurchase(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,int nVolume,char* szOrderNumber,int nLenOrderNumber);

/**
*	���.
*	@param handler ֤ȯ���׾��.
*	@param lpszCode ����.
*	@param lpszMarket �г�.
*	@param nHolderType �ɶ�����.
<table border="1">
<tr><td>1</td><td>����A��.</td></tr>
<tr><td>2</td><td>����B��.</td></tr>
<tr><td>3</td><td>�Ϻ�A��.</td></tr>
<tr><td>4</td><td>�Ϻ�B��.</td></tr>
</table>
*	@param nVolume ί����.
*	@param szOrderNumber [out]���غ�ͬ��.	
*	@param nLenOrderNumber szOrderNumber�ĳ��ȣ���������28λ.
*	@return �µ��ɹ��򷵻�0�����򷵻�����ֵ.
*/ 
UTIAPI(int) UTI_SEC_ETFRedeem(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,int nVolume,char* szOrderNumber,int nLenOrderNumber);

/**
*	�µ�(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param pOrder �µ�����.
*	@param pMoResult [out]�µ����.
*	@return �µ��ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_MakeOrder(HUTI_SEC handler, const UTI_SEC_Order* pOrder,UTI_SEC_MakeOrderResult* pMoResult);

/**
*	�����µ�(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param pOrders �µ����ݣ�����������С��nItems.
*	@param nItems �µ�����.
*	@param pMoResults [out]�µ���������µ�����һһ��Ӧ������������С��nItems.
*	@return �����µ��ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_MakeBatchOrder(HUTI_SEC handler, const UTI_SEC_Order* pOrders,int nItems,UTI_SEC_MakeOrderResult* pMoResults);

/**
*	����(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param pRecord ί�м�¼/�ɳ�����¼.
*	@param pCoResult [out]�������.
*	@return	�����ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_CancelOrder(HUTI_SEC handler, const UTI_SEC_OrderRecord* pRecord,UTI_SEC_CancelOrderResult* pCoResult);

/**
*	ͨ����ͬ�Ž��г���(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param lpszOrderNumber ί�б��.
*	@param pCoResult [out]�������.
*	@return	�����ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_CancelOrderByOrderNumber(HUTI_SEC handler, LPCSTR lpszOrderNumber,UTI_SEC_CancelOrderResult* pCoResult);

/**
*	��������(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param pRecords �������ݣ�����������С��nRecords.
*	@param nRecords	��������.
*	@param pCoResults [out]����������볷������һһ��Ӧ������������С��nRecords.
*	@return ���������ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_CancelBatchOrder(HUTI_SEC handler, const UTI_SEC_OrderRecord* pRecords,int nRecords,UTI_SEC_CancelOrderResult* pCoResults);

/**
*	ȫ��(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@return ȫ���ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_CancelAllOrder(HUTI_SEC handler);

/**
*	��ѯȫ���ֲ�(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param ppPositions [out]�ֲ֣�����new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryHoldPositions(HUTI_SEC handler, UTI_SEC_Position** ppPositions,int* pnItems);

/**
*	���г���ѯ�ֲ�(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param lpszMarket �г�.
*	@param nHolderType �ɶ�����.
<table border="1">
<tr><td>1</td><td>����A��.</td></tr>
<tr><td>2</td><td>����B��.</td></tr>
<tr><td>3</td><td>�Ϻ�A��.</td></tr>
<tr><td>4</td><td>�Ϻ�B��.</td></tr>
</table>
*	@param ppPositions [out]�ֲ֣�����new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryHoldPositionsByMarket(HUTI_SEC handler, LPCSTR lpszMarket,int nHolderType, UTI_SEC_Position** ppPositions,int* pnItems);

/**
*	��Ʒ�ֲ�ѯ�ֲ�(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param lpszCode ����.
*	@param lpszMarket �г�.
*	@param nHolderType �ɶ�����.
<table border="1">
<tr><td>1</td><td>����A��.</td></tr>
<tr><td>2</td><td>����B��.</td></tr>
<tr><td>3</td><td>�Ϻ�A��.</td></tr>
<tr><td>4</td><td>�Ϻ�B��.</td></tr>
</table>
*	@param ppPositions [out]�ֲ֣�����new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryHoldPositionsByCode(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_SEC_Position** ppPositions,int* pnItems);

/**
*	��ѯȫ���ɽ�(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param ppMatch [out]�ɽ�������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryMatch(HUTI_SEC handler, UTI_SEC_Match** ppMatch,int* pnItems);

/**
*	��ѯ���µĳɽ�(֤ȯ)��ÿ�β�ѯ�ɹ�����¶�λ��.
*	@param handler ֤ȯ���׾��.
*	@param ppMatch [out]�ɽ�������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryNewMatch(HUTI_SEC handler, UTI_SEC_Match** ppMatch,int* pnItems);

/**
*	����λ����ѯ�ɽ�(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param lpszPostStr ��λ��.
*	@param ppMatch [out]�ɽ�������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryMatchByPostStr(HUTI_SEC handler, LPCSTR lpszPostStr, UTI_SEC_Match** ppMatch,int* pnItems);

/**
*	���г���ѯ�ɽ�(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param lpszMarket �г�.
*	@param nHolderType �ɶ�����.
<table border="1">
<tr><td>1</td><td>����A��.</td></tr>
<tr><td>2</td><td>����B��.</td></tr>
<tr><td>3</td><td>�Ϻ�A��.</td></tr>
<tr><td>4</td><td>�Ϻ�B��.</td></tr>
</table>
*	@param ppMatch [out]�ɽ�������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryMatchByMarket(HUTI_SEC handler, LPCSTR lpszMarket,int nHolderType, UTI_SEC_Match** ppMatch,int* pnItems);

/**
*	��Ʒ�ֲ�ѯ�ɽ�(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param lpszCode	����.
*	@param lpszMarket �г�.
*	@param nHolderType �ɶ�����.
<table border="1">
<tr><td>1</td><td>����A��.</td></tr>
<tr><td>2</td><td>����B��.</td></tr>
<tr><td>3</td><td>�Ϻ�A��.</td></tr>
<tr><td>4</td><td>�Ϻ�B��.</td></tr>
</table>
*	@param ppMatch [out]�ɽ�������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryMatchByCode(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_SEC_Match** ppMatch,int* pnItems);

/**
*	����ͬ�Ų�ѯ�ɽ�(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param lpszOrderNumber ��ͬ��.
*	@param ppMatch [out]�ɽ�������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryMatchByOrderNumber(HUTI_SEC handler, LPCSTR lpszOrderNumber,UTI_SEC_Match** ppMatch,int* pnItems);

/**
*	��ί�м�¼��ѯ�ɽ�(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param pRecord ί�м�¼.
*	@param ppMatch [out]�ɽ�������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryMatchByOrder(HUTI_SEC handler, const UTI_SEC_OrderRecord* pRecord,UTI_SEC_Match** ppMatch,int* pnItems);

/**
*	����ͬ�źϲ���ѯ�ɽ�(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param lpszOrderNumber ��ͬ��.
*	@param pMatch [out]�ϲ���ĳɽ�.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryMatch_Merge(HUTI_SEC handler, LPCSTR lpszOrderNumber,UTI_SEC_Match* pMatch);

/**
*	��ί�м�¼�ϲ���ѯ(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param pRecord ί�м�¼.
*	@param pMatch [out]�ϲ���ĳɽ�.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryMatchByOrder_Merge(HUTI_SEC handler, const UTI_SEC_OrderRecord* pRecord,UTI_SEC_Match* pMatch);

/**
*	��ѯȫ��ί��(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param ppRecord	[out]ί�м�¼������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryOrderRecords(HUTI_SEC handler, UTI_SEC_OrderRecord** ppRecord,int* pnItems);

/**
*	��ָ���г���ί��(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param lpszMarket �г�.	
*	@param nHolderType �ɶ�����.
<table border="1">
<tr><td>1</td><td>����A��.</td></tr>
<tr><td>2</td><td>����B��.</td></tr>
<tr><td>3</td><td>�Ϻ�A��.</td></tr>
<tr><td>4</td><td>�Ϻ�B��.</td></tr>
</table>
*	@param ppRecord	[out]ί�м�¼������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryOrderRecordsByMarket(HUTI_SEC handler, LPCSTR lpszMarket,int nHolderType,UTI_SEC_OrderRecord** ppRecord,int* pnItems);

/**
*	��ָ��Ʒ�ֵ�ί��(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param lpszCode ����.
*	@param lpszMarket �г�.
*	@param nHolderType �ɶ�����.
<table border="1">
<tr><td>1</td><td>����A��.</td></tr>
<tr><td>2</td><td>����B��.</td></tr>
<tr><td>3</td><td>�Ϻ�A��.</td></tr>
<tr><td>4</td><td>�Ϻ�B��.</td></tr>
</table>
*	@param ppRecord	[out]ί�м�¼������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryOrderRecordsByCode(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_SEC_OrderRecord** ppRecord,int* pnItems);

/**
*	����ͬ�Ų�ί��(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param lpszOrderNumber ��ͬ��.
*	@param pOrderRecord [out]ί�м�¼.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryOrderByNumber(HUTI_SEC handler, LPCSTR lpszOrderNumber,UTI_SEC_OrderRecord* pOrderRecord);

/**
*	��ѯȫ���ɳ�ί��(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param ppRecord [out]ί�м�¼������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryCanCancel(HUTI_SEC handler, UTI_SEC_OrderRecord** ppRecord,int* pnItems);

/**
*	��ָ���г��Ŀɳ�ί��(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param lpszMarket �г�.
*	@param nHolderType �ɶ�����.
<table border="1">
<tr><td>1</td><td>����A��.</td></tr>
<tr><td>2</td><td>����B��.</td></tr>
<tr><td>3</td><td>�Ϻ�A��.</td></tr>
<tr><td>4</td><td>�Ϻ�B��.</td></tr>
</table>
*	@param ppRecord [out]ί�м�¼������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryCanCancelByMarket(HUTI_SEC handler, LPCSTR lpszMarket,int nHolderType,UTI_SEC_OrderRecord** ppRecord,int* pnItems);

/**
*	��ָ��Ʒ�ֵĿɳ�ί��(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param lpszCode ����.
*	@param lpszMarket �г�.
*	@param nHolderType �ɶ�����.
<table border="1">
<tr><td>1</td><td>����A��.</td></tr>
<tr><td>2</td><td>����B��.</td></tr>
<tr><td>3</td><td>�Ϻ�A��.</td></tr>
<tr><td>4</td><td>�Ϻ�B��.</td></tr>
</table>
*	@param ppRecord [out]ί�м�¼������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryCanCancelByCode(HUTI_SEC handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_SEC_OrderRecord** ppRecord,int* pnItems);

/**
*	����ͬ�Ų�ɳ�ί��(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param lpszOrderNumber ��ͬ��.
*	@param pOrderRecord [out]ί�м�¼.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryCanCancelByNumber(HUTI_SEC handler, LPCSTR lpszOrderNumber,UTI_SEC_OrderRecord* pOrderRecord);

/**
*	������ʽ�(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param pdFreeCapital [out]�����ʽ�.
*	@param chCurrencyType ����.
<table border="1">
<tr><td>'0'</td><td>�����.</td></tr>
<tr><td>'1'</td><td>�۱�.</td></tr>
<tr><td>'2'</td><td>��Ԫ.</td></tr>
</table>
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/	
UTIAPI(int) UTI_SEC_QueryFreeCapital(HUTI_SEC handler, double* pdFreeCapital,char chCurrencyType);

/**
*	��ѯȫ���ʽ���Ϣ(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param ppAssets [out]�ʲ���¼������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryAssets(HUTI_SEC handler, UTI_SEC_Assets** ppAssets,int* pnItems);

/**
*	�����ֲ��ʽ���Ϣ(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param chCurrencyType ����.
<table border="1">
<tr><td>'0'</td><td>�����.</td></tr>
<tr><td>'1'</td><td>�۱�.</td></tr>
<tr><td>'2'</td><td>��Ԫ.</td></tr>
</table>
*	@param ppAssets [out]�ʲ���¼.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryAssetsByCurrency(HUTI_SEC handler, char chCurrencyType,UTI_SEC_Assets* pAssets);

/**
*	��ѯ���ɽ�����(֤ȯ).
*	@param handler ֤ȯ���׾��.
*	@param pMaxVolReq ��ѯ���ɽ���������.
*	@param piVolume [out]������ɽ�����.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SEC_QueryMaxBSVolume(HUTI_SEC handler, const UTI_SEC_QueryMaxVolumeReq* pMaxVolReq,INT64* piVolume);


/**
*	��ȡ�����ַ���.
*	@param	nErrorCode	����ֵ.
*   @param  pszError    ���ش���ֵ
*   @param  nLength     ���ش���ֵ���ڴ�ĳ���
*	@return             0����֪����1����̬����-1 δ֪����
*   @remark ����ĳЩ�����ɹ�̨������
*	@���ǹ�̨�����Ĵ�����Ҫʹ��handlerȡ,����ȡ�����һ�δ���.
*/
UTIAPI(int) UTI_SEC_GetError(int nErrorCode,HUTI_SEC handler,char* pszError,int nLength);


#ifdef __cplusplus
}
#endif