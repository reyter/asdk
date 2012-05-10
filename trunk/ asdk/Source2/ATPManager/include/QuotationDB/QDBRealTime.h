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

#include <vector>
#include <list>
using namespace std;

#include <afxcoll.h>

#include "../Include/tdf/TDFApiDefine.h"
#include "../Include/ATPSetting/ATPErrorDefine.h"
#include "../ATPSetting/ATPSettingHelper.h"

struct AFX_EXT_CLASS DataFeedStatus
{
	_HServer server;				//������.
	INT		 nStatus;				//����״̬
};




enum QUOTATION_TYPE
{
	/**
	�������(֤ȯ)
	*/
	QUOTATION_TYPE_SEC=0,
	/**
	�������(�ڻ�)
	*/
	QUOTATION_TYPE_FUT=1,

	/**
	�������(ָ��)
	*/
	QUOTATION_TYPE_IND=2,

	/**
	�������(��ʳɽ�)
	*/
	QUOTATION_TYPE_TRANSACTION=3,

	/**
	�������(���ί��)
	*/
	QUOTATION_TYPE_ORDER=4,

	/**
	�������(��������)
	*/
	QUOTATION_TYPE_ORDERQUEUE=5,


	QUOTATION_TYPE_MAXCOUNT				//����Ʒ����,����ʹ��.
};


struct AFX_EXT_CLASS SubscribeContent
{
	CString strMarket;
	CString strCode;
	QUOTATION_TYPE   dwType;
	SubscribeContent& operator = (const SubscribeContent& right)
	{
		strMarket = right.strMarket;
		strCode = right.strCode;
		dwType = right.dwType;
		return *this;
	}
	bool operator == (const SubscribeContent& right) const
	{
		return (dwType == right.dwType) && (strMarket == right.strMarket) 
			&&  ( strCode == right.strCode);
	}
	SubscribeContent(const char* szMarket,const char* szCode,DWORD dwType)
	{
		strMarket = szMarket;
		strCode = szCode;
		dwType = dwType;
	}
	SubscribeContent(const SubscribeContent& other)
	{
		strMarket = other.strMarket;
		strCode = other.strCode;
		dwType = other.dwType;
	}
	~SubscribeContent()
	{

	}
};


/**
* ʵʱ������. �ɴӴ���̳г���������ʵ�ֻص������⺯�����Դ�������ĸ���֪ͨ��
* ���Ե��� <a href="#SubscribeQuotation">SubscribeQuotation</a> ������ֻ��ע��Ʒ�֣�
* ��ʵ�֣�ֻ�й�ע��Ʒ�֣���ע���������͸���ʱ����֪ͨ.
* ʵʱ������Ҫ�к��DataFeed����֧��.
* ��ѯ֧�ֲ�������������գ��ڻ�����Ʊ��ָ����
* ���г������Ͷ���
* ȡ������.
*/
class AFX_EXT_CLASS CQDBRealTime
{
	DECLARE_ERROR_MAP();

public:
	/**
	����DataFeed����ʵʱ���ݣ��㷨������øú���.
	��ܻ�������ʱ���øú���.
	*/ 	
	static void BeginDataFeed();


	/**
	����HDBServer����.
	*/ 
	static void EndDataFeed();



	
	/**
	ȡDataFeed����״̬��
	@pStatus , ���ΪNULL,����DataFeed����,�������nItems��״̬.
    @retrun    ����DataFeed����.
	*/	
	//static int GetDataFeedStatus(DataFeedStatus* pStatus,int nItems);


	static bool GetDataFeedStatus();


	static void GetFlow(__int64& iSend,__int64& iRecv);

	/**
	��ѯƷ�ֽ��׹ɶ��������.
	@param 
	-1 
	1 SZ A
	2 SZ B
	3 SH A
	4 SH B
    5 CF 
	6 SP SHFE
	7 SP ZCE
	8 SP DCE
	*/
	static int QueryHolderType(const char* szMarket,const char* szCode);

	
	/**
	����nExid,ȡ��,��0-"SZ"
	*/	
	static CString GetMarket(int nExid);

public:
	CQDBRealTime(void);
	virtual ~CQDBRealTime(void);

 
	/**
		��������֪ͨ,��������仯ʱ�����������⺯��֪ͨ����仯.
		��ε��ã���֧�ֹ�ע���Ʒ�ֵ�����仯.


		@param szMarket			�г�(��:SH)
			<table border="1">
			<tr><td>�г�</td><td>˵��</td></tr>
			<td>SH</td><td>�Ϻ�֤ȯ������</td></tr>
			<td>SZ</td><td>����֤ȯ������</td></tr>
			<td>SP</td><td>��Ʒ�ڻ�</td></tr>
			<td>CF</td><td>�й������ڻ�������</td></tr>
			</table>
		
		@param szCode			����(��:600000)

		@param dwType			�������ͣ������� QUOTATION_TYPE_XXX, Ĭ��ֻ��ע�������
		
		</table>
	*/
	void SubscribeQuotation(const char* szMarket,const char* szCode,QUOTATION_TYPE dwType);

	/**
	ȡ������
	*/ 	
	void UnSubscribeQuotation(const char* szMarket,const char* szCode,QUOTATION_TYPE dwType);

	/**
	ȡ�����еĶ���.
	*/
	void DeleteAllSubscibe();



	/**
		���յ�֤ȯ�������ʱ�Ļص�.		
		@param szMarket			�г�(��:SH)
			<table border="1">
			<tr><td>�г�</td><td>˵��</td></tr>
			<td>SH</td><td>�Ϻ�֤ȯ������</td></tr>
			<td>SZ</td><td>����֤ȯ������</td></tr>	
			</table>
		@param szCode			����(��:600000)
		@param pMarketData	�������
	*/
	virtual void OnReceiveMarketData(const char* szMarket,const char* szCode,const TDFDefine_MarketData* pMarketData){}


	/**
		���յ��ڻ��������ʱ�Ļص�.	
		@param szMarket			�г�(��:CF)
				<table border="1">
				<tr><td>�г�</td><td>˵��</td></tr>
				<td>SP</td><td>��Ʒ�ڻ�</td></tr>
				<td>CF</td><td>�й������ڻ�������</td></tr>
				</table>
		@param szCode			����(��:IF1006)
		@param pMarketData	�������	

	*/
	virtual void OnReceiveMarketData_Futures(const char* szMarket,const char* szCode,const TDFDefine_MarketData_Futures* pMarketData){}




	/**
		���յ�֤ȯ������������ʱ�Ļص�.		
		@param szMarket			�г�(��:SH)
			<table border="1">
			<tr><td>�г�</td><td>˵��</td></tr>
			<td>SH</td><td>�Ϻ�֤ȯ������</td></tr>
			<td>SZ</td><td>����֤ȯ������</td></tr>	
			</table>
		@param szCode			����(��:600000)
		@param pOrderQueue		������������.
	*/
	virtual void OnReceiveOrderQueen(const char* szMarket,const char* szCode,const TDFDefine_OrderQueue* pOrderQueue,int nItems){}




	/**
	���յ�ָ���������ʱ�Ļص�.		
	@param szMarket			�г�(��:SH)
	<table border="1">
	<tr><td>�г�</td><td>˵��</td></tr>
	<td>SH</td><td>�Ϻ�֤ȯ������</td></tr>
	<td>SZ</td><td>����֤ȯ������</td></tr>	
	</table>
	@param szCode			����(��:600000)
	@param pIndex			ָ���������
	*/
	virtual void OnReceiveIndexData(const char* szMarket,const char* szCode,const TDFDefine_IndexData* pIndex){}
	

	/**
		���յ���ʳɽ�����ʱ�Ļص�.		
		@param szMarket			�г�(��:SH)
		<table border="1">
		<tr><td>�г�</td><td>˵��</td></tr>
		<td>SH</td><td>�Ϻ�֤ȯ������</td></tr>
		<td>SZ</td><td>����֤ȯ������</td></tr>	
		</table>
		@param szCode			����(��:600000)
		@param pTransaction		��ʳɽ�����.
		@param nItems           
	*/
	virtual void OnReceiveTransaction(const char* szMarket,const char* szCode,const TDFDefine_Transaction* pTransaction,int nItems){}


	virtual void OnReceiveOrder(const char* szMarket,const char* szCode,const TDFDefine_Order* pOrderQueue,int nItems){}


	/**
	��ѯ����֤ȯ��������
	@param szMarket			�г�(��:SH)
	<table border="1">
	<tr><td>�г�</td><td>˵��</td></tr>
	<td>SH</td><td>�Ϻ�֤ȯ������</td></tr>
	<td>SZ</td><td>����֤ȯ������</td></tr>	
	</table>
	@param marketData	[out] �������µ���������.
	@param szCode			����(��:600000)
    @return           �����ѯ�����ڻ����룬�򷵻�false, ���HDFServer�жϣ�����False��������Ҵ���ʧ�ܣ�����False.
					  ��ʱ������ GetLastError ȡ�ؾ���ԭ��.
    @see GetLastError
	@see GetLastErrorCode
	*/
	bool QueryLastMarketData(const char* szMarket,const char* szCode,TDFDefine_MarketData& marketData);


	/**
	��ѯ�����ڻ���������
	@param szMarket			�г�(��:CF)
	<table border="1">
	<tr><td>�г�</td><td>˵��</td></tr>
	<td>SP</td><td>��Ʒ�ڻ�</td></tr>
	<td>CF</td><td>�й������ڻ�������</td></tr>
	</table>
	@param szCode			����(��:IF1006)
	@param marketDataFutures   [out] �������µ���������
	@return           �����ѯ����֤ȯ���룬�򷵻�false,���HDFServer�жϣ�����False��������Ҵ���ʧ�ܣ�����False.
					  ��ʱ������ GetLastError ȡ�ؾ���ԭ��.
	@see GetLastError
	@see GetLastErrorCode
	*/
	bool  QueryLastMarketData_Futures(const char* szMarket,const char* szCode,TDFDefine_MarketData_Futures& marketDataFutures);



	/**
	��ѯָ����������������
	@param szMarket			�г�(��:SH)
	<table border="1">
	<tr><td>�г�</td><td>˵��</td></tr>
	<td>SP</td><td>��Ʒ�ڻ�</td></tr>
	<td>CF</td><td>�й������ڻ�������</td></tr>
	</table>
	@param szCode			����(��:000300)
	@parma indexData         [out] �������µ���������
	@return           �����ѯ����֤ȯ,�ڻ����룬�򷵻�false�����HDFServer�жϣ�����False��������Ҵ���ʧ�ܣ�����False.
	@see GetLastError
	@see GetLastErrorCode
	*/
	bool QueryLastMarketData_Index(const char* szMarket,const char* szCode,TDFDefine_IndexData& indexData);



protected:
	static CPtrList     s_lsDFSocket;

	friend class CATPDataFeedSocket;
private:

	LPVOID m_pSubscribeThread;


protected:



	vector<SubscribeContent> m_vecSubscribe;

	void Add2Sub(const char* szMarket,const char* szCode,QUOTATION_TYPE dwType);
	
private:
	
	friend class CWinThread_QuotationPush;
	void NotifyBack(QUOTATION_TYPE nType,const char* strMarket,const char* strCode,void* pData,int nItems);
};
