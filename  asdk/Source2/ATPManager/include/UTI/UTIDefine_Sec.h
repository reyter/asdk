/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 ���׽ӿ���(֤ȯ��Ȩ֤��ETF��).
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-4		��ΰ		 ����
2010-7-12		������		 ������UTI_SEC_MakeOrderResult��UTI_SEC_CancelOrderResult��UTI_SEC_QueryMaxVolumeReq�Ľṹ�嶨��
-------------------------------------------------------------
*/

#pragma once
#ifndef __UTIDEFINE_SEC_H_
#define __UTIDEFINE_SEC_H_
#include "UTIDefine.h"


#pragma pack(push,1)

/**
�µ�����
*/
struct UTI_SEC_Order
{
	/**
	�г�.
	*/
	char szMarket[4];	

	/**
	����.
	*/ 	
	char szCode[12];	

	/**
	����.
	*/ 	
	char szName[16];

	/**
	��������,
	<table border="1">
	<tr><td>'B'</td><td>֤ȯ��ETF��(Buy)</td></tr>
	<tr><td>'S'</td><td>֤ȯ��ETF��(Sell)</td></tr>
	<tr><td>'P'</td><td>�����Ϲ���ETF�깺(Purchase)</td></tr>
	<tr><td>'R'</td><td>������ء�ETF���(Redeem)</td></tr>
	</table>
	*/
	char cBSSide;		

	/**
	�۸�.�Ŵ�һ�򱶣�������ʾ�޼ۣ�������ʾί�з�ʽ���£�
	<table border="1">
	<tr><td>-1</td><td>�Է����ż۸�</td></tr>
	<tr><td>-2</td><td>�������ż۸�</td></tr>
	<tr><td>-3</td><td>��ʱ�ɽ�ʣ�೷��</td></tr>
	<tr><td>-4</td><td>�嵵�ɽ�ʣ�೷��</td></tr>
	<tr><td>-5</td><td>ȫ��ɽ�����</td></tr>
	<tr><td>-6</td><td>�嵵�ɽ�ʣ���ּ�</td></tr>
	</table>
	*/
	int nPrice;	

	/**
	����.
	*/
	unsigned int nVolume;


	/**
	����
	*/
    char szOrderGroup[LEN_ORDERGROUP];
};

/**
�µ����
*/
struct UTI_SEC_MakeOrderResult
{
	/**
	�µ�����
	*/
	UTI_SEC_Order order;

	/**
	�ɹ���־
	*/
	int nSucFlag;

	/**
	* ������Ϣ.
	*/
	char chErrMsg[LEN_ERROR];

	/**
	* ί�����.
	*/
	char chOrderNumber[LEN_ORDERNUMBER];

};


/**
ί�м�¼,ͬʱҲ�ǿɳ�����¼��ʽ�����ͬ.
*/
struct UTI_SEC_OrderRecord
{
	/**
	��������
	*/
	UTI_SEC_Order order;

	/**
	* ��λ��.
	*/
	char chPostStr[LEN_POSTSTR];

	/**
	��ǰ״̬
	<table border="1">
	<tr><td>0</td><td>δ��:ί�гɹ�δ����</td></tr>
	<tr><td>1</td><td>���������ڱ���</td></tr>
	<tr><td>2</td><td>�ѱ������̳ɹ�</td></tr>
	<tr><td>3</td><td>�ѱ��������Ѿ����̣�δ�ɽ����ҷ��˳���ί��ָ��</td></tr>
	<tr><td>4</td><td>�ѳ���δ�ɽ���ȫ���Ѿ������ɹ�</td></tr>
	<tr><td>5</td><td>���ɣ����ֳɽ�</td></tr>
	<tr><td>6</td><td>���ɴ��������ֳɽ����ҷ��˳���ί��ָ��</td></tr>
	<tr><td>7</td><td>���������ֳɽ���ʣ�������Ѿ������ɹ�</td></tr>
	<tr><td>8</td><td>�ѳɣ�ȫ���ɽ�</td></tr>
	<tr><td>9</td><td>�ϵ�</td></tr>
	<tr><td>10</td><td>����</td></tr>
	</table>
	*/
	DWORD    dwStatus;

	/**
	* ί������ ��ʽ��YYYYMMDD.
	*/
	int	 nOrderDate;

	/**
	* ί��ʱ�� ��ʽ��HHMMSS.
	*/
	int	 nOrderTime;	


	/**
	* �ɽ�����.
	*/
	int  nMadeVolume;				
	/**
	* �ɽ����ۣ�������10000��.
	*/
	int  nMadePrice;				
	/**
	* ��������.
	*/
	int  nCancelVolume;				

	/**
	* ί�����.
	*/
	char chOrderNumber[LEN_ORDERNUMBER];


	/**
	* ί�ж�����.
	*/
	double dOrderFrozAmt;	
	/**
	* �ɽ����.
	*/
	double dMadeAmt;


};


/**
�������ؽ��.
*/
struct UTI_SEC_CancelOrderResult
{
	/**
	�ɹ���־
	*/
	int nSucFlag;

	/**
	* ������Ϣ.
	*/
	char chErrMsg[LEN_ERROR];

	/**
	* ί�����.
	*/
	char chOrderNumber[LEN_ORDERNUMBER];
};


/**
�ֲ���Ϣ
*/
struct UTI_SEC_Position
{
	/**
	�г�.
	*/
	char szMarket[4];	

	/**
	����.
	*/ 	
	char szCode[12];

	/**
	֤ȯ����
	*/
	char szName[12];

	/**
	�ɷ����
	*/
	__int64	 i64Balance;				

	/**
	�ɷݿ���
	*/
	__int64  i64Available;				

	/**
	�ɷݶ���
	*/
	__int64  i64Forzen;				

	/**
	����������
	*/
	__int64  i64Buy;					

	/**
	����������
	*/
	__int64  i64Sale;			

	/**
	��ǰӵ����
	*/
	__int64  i64Qty;					

	/**
	����������
	*/
	__int64  i64Diff;	

	/**
	�ɱ��۸�������10000��
	*/
	int  nCostPrice;					

	/**
	��ǰ�ɱ�
	*/
	int  nBuyCost;						
	
	/**
	��ֵ
	*/
	double dMktVal;						

	/**
	ӯ��
	*/
	double dIncome;						

};


/**
�ɽ�
*/
struct UTI_SEC_Match
{
	/**
	��������
	*/
	UTI_SEC_Order order;

	/**
	* ��λ��.
	*/
	char chPostStr[LEN_POSTSTR];

	/**
	�ɽ�״̬ 0-���� 1-���� 2-�ϵ�
	*/
	int nStatus;				

	/**
	ί�����ڣ���ʽ��YYYYMMDD
	*/
	int	 nOrderDate;					

	/**
	ί��ʱ�䣬��ʽ��HHMMSS
	*/
	int	 nOrderTime;								

	/**
	�ɽ�����
	*/
	int  nMadeVolume;					

	/**
	�ɽ��۸�������10000��
	*/
	int  nMadePrice;					
	/**
	��������
	*/
	int  nCancelVolume;										

	/**
	�ɽ�ʱ��
	*/
	int	 nMadeTime;											

	/**
	ί�����
	*/
	char chOrderNumber[LEN_ORDERNUMBER];	
	
	/**
	�ɽ����
	*/
	char chMadeNumber[LEN_MADENUMBER];		

	/**
	˵��
	*/
	char chRemark[LEN_REMARK];			
	/**
	����˵��
	*/
	char chRemark1[LEN_REMARK];			

	/**
	�ɽ����
	*/
	double dMadeAmt;

};


/**
�ʲ���¼
*/
struct UTI_SEC_Assets
{
	/**
	* �������� '0'-����� '1'-�۱� '2'-��Ԫ.
	*/
	char chMoneyType;					
	/**
	* ˵��.
	*/
	char chRemark[LEN_REMARK];			
	/**
	* �ʽ����.
	*/
	double dFundAvl;					
	/**
	* �ʽ����.
	*/
	double dFundBal;				
	/**
	* �ֲ���ֵ�ʲ�.
	*/
	double dStkValue;					
	/**
	* �ʽ��ʲ�.
	*/
	double dFundValue;				
	/**
	* ���ʲ�.
	*/
	double dMarketValue;				
	/**
	* ��ӯ��.
	*/
	double dIncome;					
	/**
	* �����ʽ�.
	*/
	double dFundFroz;				
	/**
	* �����ʽ�.
	*/
	double dOther;						
	/**
	* ����������.
	*/
	double dFundBuy;				
	/**
	* �����������.
	*/
	double dFundSell;	

};

/**
���ɽ�������ѯ�ṹ.
*/
struct UTI_SEC_QueryMaxVolumeReq
{
	/**
	�г�.
	*/
	char szMarket[4];	

	/**
	����.
	*/ 	
	char szCode[12];	
	/**
	��������,
	<table border="1">
	<tr><td>'B'</td><td>֤ȯ��ETF��(Buy)</td></tr>
	<tr><td>'S'</td><td>֤ȯ��ETF��(Sell)</td></tr>
	<tr><td>'P'</td><td>�����Ϲ���ETF�깺(Purchase)</td></tr>
	<tr><td>'R'</td><td>������ء�ETF���(Redeem)</td></tr>
	</table>
	*/
	char cBSSide;		

	/**
	�۸�.�Ŵ�һ�򱶣�������ʾ�޼ۣ�������ʾί�з�ʽ���£�
	<table border="1">
	<tr><td>-1</td><td>�Է����ż۸�</td></tr>
	<tr><td>-2</td><td>�������ż۸�</td></tr>
	<tr><td>-3</td><td>��ʱ�ɽ�ʣ�೷��</td></tr>
	<tr><td>-4</td><td>�嵵�ɽ�ʣ�೷��</td></tr>
	<tr><td>-5</td><td>ȫ��ɽ�����</td></tr>
	<tr><td>-6</td><td>�嵵�ɽ�ʣ���ּ�</td></tr>
	</table>
	*/
	int nPrice;	

};


#pragma pack(pop)
#endif __UTIDEFINE_SEC_H_
