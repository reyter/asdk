#pragma once

#include "UTIDefine_Fut.h"
#include "UTIApiHelper.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
*	UTI�ڻ����׾��.
*/
typedef void*  HUTI_FUT;

/**
*	�ص�����Ϣ����(�ڻ�)
*/
enum UTI_FUT_UPDATE_TYPE
{
	/**
	*	�ֲ���Ϣ
	*/
	UTI_FUT_UPDATE_POSITION = 0,	
	/**
	*	�ɽ���Ϣ
	*/
	UTI_FUT_UPDATE_MATCH = 1,
	/**
	*	ί����Ϣ
	*/
	UTI_FUT_UPDATE_ORDER = 2,
	/**
	*	�ʽ���Ϣ
	*/
	UTI_FUT_UPDATE_ASSETS = 3,
	/**
	*	�ɳ�����Ϣ
	*/
	UTI_FUT_UPDATE_CANCANCEL = 4
};

/**
*	��Ϣ���»ص�����(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param nType ��Ϣ����.
*	@param lParam ������Ϣ��ԭֵ����.
*/
typedef void (CALLBACK* LP_UTI_FUT_UPDATE_CALLBACK_FUN)(HUTI_FUT /*handler*/,UTI_FUT_UPDATE_TYPE /*nType*/,LPVOID /*lParam*/);

/**
*	����һ���ڻ����׾��.
*	@return �������������ڻ����׾��.
*/
UTIAPI(HUTI_FUT) UTI_FUT_CreateHandler();

/**
*	����һ���ڻ����׾��.
*	@param handler Ҫ���ٵ��ڻ����׾��.
*	@return ���ٳɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_DestroyHandler(HUTI_FUT handler);

/**
*	������Ϣ���»ص�����(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param nType ��Ϣ����.
*	@param lParam ������Ϣ��ԭֵ����.
*	@return ���óɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_SetUpdateCallBackFun(HUTI_FUT handler,LP_UTI_FUT_UPDATE_CALLBACK_FUN pFun,LPVOID lParam);

/**
*	������½�˺���Ϣ(�ڻ�).
*	@param handlerTo ��д���֤ȯ���׾��.
*	@param handlerFrom ��������֤ȯ���׾��.
*	@return �����ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_CopyHandler(HUTI_FUT handlerTo, HUTI_FUT handlerFrom);

/**
*	��¼(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param pLogin ��¼����.
*	@param pLoginAnswer [out]��¼Ӧ��.
*	@return ��¼�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_Login(HUTI_FUT handler, const UTI_LoginRequest* pLogin,UTI_LoginAnswer* pLoginAnswer);

/**
*	�ǳ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@return �ǳ��ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_Logout(HUTI_FUT handler);

/**
*	�ڻ�����.
*	@param handler �ڻ����׾��.
*	@param lpszCode ����.
*	@param lpszMarket �г�.
*	@param nHolderType ���ױ�������.
<table border="1">
<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
<tr><td>7</td><td>֣���ڻ�.</td></tr>
<tr><td>8</td><td>�����ڻ�.</td></tr>
</table>
*	@param nPrice �۸񣬷Ŵ�10000��.	
*	@param nVolume ί����.
*	@param chBsSide ��������.
<table border="1">
<tr><td>'B'</td><td>��.</td></tr>
<tr><td>'S'</td><td>��.</td></tr>
</table>
*	@param szOrderNumber [out]���غ�ͬ��.
*	@param nLenOrderNumber szOrderNumber�ĳ��ȣ���������28λ.
*	@param nHedgeFlag Ͷ���ױ���־.
<table border="1">
<tr><td>0</td><td>Ͷ��.</td></tr>
<tr><td>1</td><td>���ڱ�ֵ.</td></tr>
</table>
*	@param lpszOrderGroup �������µ�.
*	@return �µ��ɹ��򷵻�0�����򷵻�����ֵ.
*/ 
UTIAPI(int) UTI_FUT_Open(HUTI_FUT handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,int nPrice,int nVolume,char chBsSide,char* szOrderNumber,int nLenOrderNumber,int nHedgeFlag, LPCSTR lpszOrderGroup);

/**
*	�ڻ�ƽ��.
*	@param handler �ڻ����׾��.
*	@param lpszCode ����.
*	@param lpszMarket �г�.
*	@param nHolderType ���ױ�������.
<table border="1">
<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
<tr><td>7</td><td>֣���ڻ�.</td></tr>
<tr><td>8</td><td>�����ڻ�.</td></tr>
</table>
*	@param nPrice �۸񣬷Ŵ�10000��.	
*	@param nVolume ί����.
*	@param chBsSide ��������.
<table border="1">
<tr><td>'B'</td><td>��.</td></tr>
<tr><td>'S'</td><td>��.</td></tr>
</table>
*	@param szOrderNumber [out]���غ�ͬ��.
*	@param nLenOrderNumber szOrderNumber�ĳ��ȣ���������28λ.
*	@param nHedgeFlag Ͷ���ױ���־.
<table border="1">
<tr><td>0</td><td>Ͷ��.</td></tr>
<tr><td>1</td><td>���ڱ�ֵ.</td></tr>
</table>
*	@param lpszOrderGroup �������µ�.
*	@return �µ��ɹ��򷵻�0�����򷵻�����ֵ.	
*/
UTIAPI(int) UTI_FUT_Close(HUTI_FUT handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,int nPrice,int nVolume,char chBsSide,char* szOrderNumber,int nLenOrderNumber,int nHedgeFlag, LPCSTR lpszOrderGroup);

/**
*	�µ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param pOrder �µ�����.
*	@param pMoResult [out]�µ����.
*	@return �µ��ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_MakeOrder(HUTI_FUT handler, const UTI_FUT_Order* pOrder,UTI_FUT_MakeOrderResult* pMoResult);

/**
*	�����µ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param pOrders �µ����ݣ�����������С��nItems.
*	@param nItems �µ�����.
*	@param pMoResults [out]�µ���������µ�����һһ��Ӧ������������С��nItems.
*	@return �����µ��ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_MakeBatchOrder(HUTI_FUT handler, const UTI_FUT_Order* pOrders,int nItems,UTI_FUT_MakeOrderResult* pMoResults);

/**
*	����(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param pRecord ί�м�¼/�ɳ�����¼.
*	@param pCoResult [out]�������.
*	@return �����ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_CancelOrder(HUTI_FUT handler, const UTI_FUT_OrderRecord* pRecord,UTI_FUT_CancelOrderResult* pCoResult);

/**
*	ͨ����ͬ�Ž��г���(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszOrderNumber ί�б��.
*	@param pCoResult �������.
*	@return �����ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_CancelOrderByOrderNumber(HUTI_FUT handler, LPCSTR lpszOrderNumber,UTI_FUT_CancelOrderResult* pCoResult);

/**
*	��������(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param pRecords �������ݣ�����������С��nRecords.
*	@param nRecords ��������.
*	@param pcoResults [out]����������볷������һһ��Ӧ������������С��nRecords.
*	@return ���������ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_CancelBatchOrder(HUTI_FUT handler, const UTI_FUT_OrderRecord* pRecords,int nRecords,UTI_FUT_CancelOrderResult* pCoResults);

/**
*	ȫ��(�ڻ�).
*	@param handler �ڻ����׾��.
*	@return ȫ���ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_CancelAllOrder(HUTI_FUT handler);

/**
*	��ѯȫ���ֲ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param ppPositions [out]�ֲ֣�����new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryHoldPositions(HUTI_FUT handler, UTI_FUT_Position** ppPositions,int* pnItems);

/**
*	���г���ѯ�ֲ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszMarket �г�.
*	@param nHolderType ���ױ�������.
<table border="1">
<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
<tr><td>7</td><td>֣���ڻ�.</td></tr>
<tr><td>8</td><td>�����ڻ�.</td></tr>
</table>
*	@param ppPositions [out]�ֲ֣�����new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryHoldPositionsByMarket(HUTI_FUT handler, LPCSTR lpszMarket,int nHolderType, UTI_FUT_Position** ppPositions,int* pnItems);

/**
*	��Ʒ�ֲ�ѯ�ֲ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszCode ����.
*	@param lpszMarket �г�.
*	@param nHolderType ���ױ�������.
<table border="1">
<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
<tr><td>7</td><td>֣���ڻ�.</td></tr>
<tr><td>8</td><td>�����ڻ�.</td></tr>
</table>
*	@param ppPositions [out]�ֲ֣�����new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryHoldPositionsByCode(HUTI_FUT handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_FUT_Position** ppPositions,int* pnItems);

/**
*	��ѯȫ���ɽ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param ppMatch [out]�ɽ�������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryMatch(HUTI_FUT handler, UTI_FUT_Match** ppMatch,int* pnItems);

/**
*	��ѯ���µĳɽ�(�ڻ�)��ÿ�β�ѯ�ɹ�����¶�λ��.
*	@param handler �ڻ����׾��.
*	@param ppMatch [out]�ɽ�������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryNewMatch(HUTI_FUT handler, UTI_FUT_Match** ppMatch,int* pnItems);

/**
*	����λ����ѯ�ɽ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszPostStr ��λ��.
*	@param ppMatch [out]�ɽ�������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryMatchByPostStr(HUTI_FUT handler, LPCSTR lpszPostStr, UTI_FUT_Match** ppMatch,int* pnItems);

/**
*	���г���ѯ�ɽ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszMarket �г�.
*	@param nHolderType ���ױ�������.
<table border="1">
<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
<tr><td>7</td><td>֣���ڻ�.</td></tr>
<tr><td>8</td><td>�����ڻ�.</td></tr>
</table>
*	@param ppMatch [out]�ɽ�������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryMatchByMarket(HUTI_FUT handler, LPCSTR lpszMarket,int nHolderType, UTI_FUT_Match** ppMatch,int* pnItems);

/**
*	��Ʒ�ֲ�ѯ�ɽ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszCode ����.
*	@param lpszMarket �г�.
*	@param nHolderType ���ױ�������.
<table border="1">
<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
<tr><td>7</td><td>֣���ڻ�.</td></tr>
<tr><td>8</td><td>�����ڻ�.</td></tr>
</table>
*	@param ppMatch [out]�ɽ�������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryMatchByCode(HUTI_FUT handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_FUT_Match** ppMatch,int* pnItems);

/**
*	����ͬ�Ų�ѯ�ɽ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszOrderNumber ��ͬ��.
*	@param ppMatch [out]�ɽ�������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryMatchByOrderNumber(HUTI_FUT handler, LPCSTR lpszOrderNumber,UTI_FUT_Match** ppMatch,int* pnItems);

/**
*	��ί�м�¼��ѯ�ɽ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param pRecord ί�м�¼.
*	@param ppMatch [out]�ɽ�������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryMatchByOrder(HUTI_FUT handler, const UTI_FUT_OrderRecord* pRecord,UTI_FUT_Match** ppMatch,int* pnItems);

/**
*	����ͬ�źϲ���ѯ�ɽ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszOrderNumber ��ͬ��.
*	@param pMatch [out]�ϲ���ĳɽ�.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryMatch_Merge(HUTI_FUT handler, LPCSTR lpszOrderNumber,UTI_FUT_Match* pMatch);

/**
*	��ί�м�¼�ϲ���ѯ�ɽ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param pRecord ί�м�¼.
*	@param pMatch [out]�ϲ���ĳɽ�.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryMatchByOrder_Merge(HUTI_FUT handler, const UTI_FUT_OrderRecord* pRecord,UTI_FUT_Match* pMatch);

/**
*	��ѯȫ��ί��(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param ppRecord [out]ί�У�����new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryOrderRecords(HUTI_FUT handler, UTI_FUT_OrderRecord** ppRecord,int* pnItems);

/**
*	��ָ���г���ί��(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszMarket �г�.
*	@param nHolderType ���ױ�������.
<table border="1">
<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
<tr><td>7</td><td>֣���ڻ�.</td></tr>
<tr><td>8</td><td>�����ڻ�.</td></tr>
</table>
*	@param ppRecord [out]ί�У�����new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryOrderRecordsByMarket(HUTI_FUT handler, LPCSTR lpszMarket,int nHolderType,UTI_FUT_OrderRecord** ppRecord,int* pnItems);

/**
*	��ָ��Ʒ�ֵ�ί��(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszCode ����.
*	@param lpszMarket �г�.
*	@param nHolderType ���ױ�������.
<table border="1">
<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
<tr><td>7</td><td>֣���ڻ�.</td></tr>
<tr><td>8</td><td>�����ڻ�.</td></tr>
</table>
*	@param ppRecord [out]ί�У�����new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryOrderRecordsByCode(HUTI_FUT handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_FUT_OrderRecord** ppRecord,int* pnItems);

/**
*	����ͬ�Ų�ί��(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszOrderNumber ��ͬ��.
*	@param pOrderRecord [out]ί�м�¼.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryOrderByNumber(HUTI_FUT handler, LPCSTR lpszOrderNumber,UTI_FUT_OrderRecord* pOrderRecord);

/**
*	��ѯȫ���ɳ�ί��(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param ppRecord [out]ί�У�����new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryCanCancel(HUTI_FUT handler, UTI_FUT_OrderRecord** ppRecord,int* pnItems);

/**
*	��ָ���г��Ŀɳ�ί��(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszMarket �г�.
*	@param nHolderType ���ױ�������.
<table border="1">
<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
<tr><td>7</td><td>֣���ڻ�.</td></tr>
<tr><td>8</td><td>�����ڻ�.</td></tr>
</table>
*	@param ppRecord [out]ί�У�����new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryCanCancelByMarket(HUTI_FUT handler, LPCSTR lpszMarket,int nHolderType,UTI_FUT_OrderRecord** ppRecord,int* pnItems);

/**
*	��ָ��Ʒ�ֵĿɳ�ί��(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszCode ����.
*	@param lpszMarket �г�.
*	@param nHolderType ���ױ�������.
<table border="1">
<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
<tr><td>7</td><td>֣���ڻ�.</td></tr>
<tr><td>8</td><td>�����ڻ�.</td></tr>
</table>
*	@param ppRecord [out]ί�У�����new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryCanCancelByCode(HUTI_FUT handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_FUT_OrderRecord** ppRecord,int* pnItems);

/**
*	����ͬ�Ų�ɳ�ί��(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszOrderNumber ��ͬ��.
*	@param pOrderRecord [out]ί�м�¼.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryCanCancelByNumber(HUTI_FUT handler, LPCSTR lpszOrderNumber,UTI_FUT_OrderRecord* pOrderRecord);

/**
*	������ʽ�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param pdFreeCapital [out]�����ʽ�.
*	@param chCurrencyType ����.
<table border="1">
<tr><td>'0'</td><td>�����.</td></tr>
<tr><td>'1'</td><td>�۱�.</td></tr>
<tr><td>'2'</td><td>��Ԫ.</td></tr>
</table>
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/	
UTIAPI(int) UTI_FUT_QueryFreeCapital(HUTI_FUT handler, double* pdFreeCapital,char chCurrencyType);

/**
*	��ѯȫ���ʽ���Ϣ(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param ppAssets [out]�ʲ���¼������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryAssets(HUTI_FUT handler, UTI_FUT_Assets** ppAssets,int* pnItems);

/**
*	�����ֲ��ʽ���Ϣ(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param chCurrencyType ����.
<table border="1">
<tr><td>'0'</td><td>�����.</td></tr>
<tr><td>'1'</td><td>�۱�.</td></tr>
<tr><td>'2'</td><td>��Ԫ.</td></tr>
</table>
*	@param pAssets [out]�ʲ���¼.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryAssetsByCurrency(HUTI_FUT handler, char chCurrencyType,UTI_FUT_Assets* pAssets);

/**
*	��ѯ���ɽ�����(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param pMaxVolReq ��ѯ���ɽ���������.
*	@param piVolume [out]������ɽ�����.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_QueryMaxBSVolume(HUTI_FUT handler, const UTI_FUT_QueryMaxVolumeReq* pMaxVolReq,INT64* piVolume);

/**
*	��ѯȫ����Լ(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param ppAgreement [out]��Լ��Ϣ������new���䣬�������UTI_Release����ɾ��.
*	@param pnItems [out]���ؼ�¼��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/ 
UTIAPI(int) UTI_FUT_QueryAgreement(HUTI_FUT handler, UTI_FUT_Agreement** ppAgreement,int* pnItems);

/**
*	��Ʒ�ֲ�ѯ��Լ(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param lpszCode ����.
*	@param lpszMarket �г�.
*	@param nHolderType ���ױ�������.
<table border="1">
<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
<tr><td>7</td><td>֣���ڻ�.</td></tr>
<tr><td>8</td><td>�����ڻ�.</td></tr>
</table>
*	@param pAgreement [out]��Լ��Ϣ.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/ 
UTIAPI(int) UTI_FUT_QueryAgreementByCode(HUTI_FUT handler, LPCSTR lpszCode,LPCSTR lpszMarket,int nHolderType,UTI_FUT_Agreement* pAgreement);

/**
*	��ѯ�ı��˵�(�ڻ�).
*	@param handler �ڻ����׾��.
*	@param nDate �˵�����.
*	@param ppBill [out]�ı��˵���Ϣ������new���䣬�������UTI_Release����ɾ��.
*	@param pnInfoLen [out]�����ı���Ϣ����.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/ 
UTIAPI(int) UTI_FUT_QueryBill(HUTI_FUT handler, int nDate , char** ppBill,int* pnInfoLen);

/**
*	���㵥ȷ��(�ڻ�).
*	@param handler �ڻ����׾��.
*	@return ��ѯ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_FUT_ConfirmSettlement(HUTI_FUT handler);


/**
*	��ȡ�����ַ���.
*	@param	nErrorCode	����ֵ.
*   @param  pszError    ���ش���ֵ
*   @param  nLength     ���ش���ֵ���ڴ�ĳ���
*	@return             0����֪����1����̬����-1 δ֪����
*   @remark ����ĳЩ�����ɹ�̨������
*	@���ǹ�̨�����Ĵ�����Ҫʹ��handlerȡ,����ȡ�����һ�δ���.
*/
UTIAPI(int) UTI_FUT_GetError(int nErrorCode,HUTI_FUT handler,char* pszError,int nLength);

#ifdef __cplusplus
}
#endif