/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 ���׽ӿ���(�ڻ���).
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-4		��ΰ		 ����
-------------------------------------------------------------
*/

#pragma once
#ifndef __UTIDEFINE_FUT_H_
#define __UTIDEFINE_FUT_H_
#include "UTIDefine.h"


#pragma pack(push,1)



/**
*	�µ�����.
*/
struct UTI_FUT_Order
{
	
	/**
	*	�г�.
	*/
	char szMarket[4];	

	/**
	*	���ױ�������.
	<table border="1">
	<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
	<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
	<tr><td>7</td><td>֣���ڻ�.</td></tr>
	<tr><td>8</td><td>�����ڻ�.</td></tr>
	</table>
	*/
	int nHolderType;

	/**
	*	����.
	*/ 	
	char szCode[12];	

	/**
	*	����.
	*/ 	
	char szName[16];

	/**
	*	��������.
	<table border="1">
	<tr><td>'B'</td><td>��(Buy)</td></tr>
	<tr><td>'S'</td><td>��(Sell)</td></tr>
	</table>
	*/
	char cBSSide;	

	/**
	*	��ƽ����.
	<table border="1">
	<tr><td>0</td><td>����</td></tr>
	<tr><td>1</td><td>ƽ��</td></tr>
	<tr><td>2</td><td>ƽ���</td></tr>
	</table>
	*/
	int nKPFlag;

	/**
	*	Ͷ����־.
	<table border="1">
	<tr><td>0</td><td>Ͷ��</td></tr>
	<tr><td>1</td><td>��ֵ</td></tr>
	</table>
	*/
	int nHedgeType;

	/**
	*	�۸񣬷Ŵ�10000��.
	*/
	int nPrice;	

	/**
	*	����.
	*/
	unsigned int nVolume;


	/**
	*	����.
	*/
    char szOrderGroup[LEN_ORDERGROUP];

};

/**
*	�µ����.
*/
struct UTI_FUT_MakeOrderResult
{
	
	/**
	*	�µ�����.
	*/
	UTI_FUT_Order order;

	/**
	*	0��ʾ�ɹ�������ֵ��ʾʧ��.
	*/
	int nErrID;

	/**
	*	������Ϣ.
	*/
	char chErrMsg[LEN_ERROR];

	/**
	*	ί�����.
	*/
	char chOrderNumber[LEN_ORDERNUMBER];

};


/**
*	ί�м�¼,ͬʱҲ�ǿɳ�����¼��ʽ�����ͬ.
*/
struct UTI_FUT_OrderRecord
{
	/**
	* �Ự�е�Ψһ��ʶ�����ڱ�ʶ������¼.
	*/
	INT64     nIdentity;
	
	/**
	*	��������.
	*/
	UTI_FUT_Order order;

	/**
	*	��λ��.
	*/
	char chPostStr[LEN_POSTSTR];

	/**
	*	��ǰ״̬.
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
	</table>
	*/
	DWORD    dwStatus;

	/**
	*	ί������HHMMSS.
	*/
	int	 nOrderDate;

	/**
	*	ί��ʱ��YYYYMMDD.
	*/
	int	 nOrderTime;	

	/**
	*	�ɽ�����.
	*/
	int  nMadeVolume;				
	/**
	*	�ɽ����ۣ�������10000��.
	*/
	int  nMadePrice;				
	/**
	*	��������.
	*/
	int  nCancelVolume;				

	/**
	*	ί�����.
	*/
	char chOrderNumber[LEN_ORDERNUMBER];

	/**
	*	�������ᱣ֤��.
	*/
	double dHoldBal;					

	/**
	*	�����ܷ���.
	*/
	double dFrozFare;		

	/**
	*	������Ϣ.
	*/
	char chNeedInfo[LEN_REMARK];

};


/**
*	�������ؽ��.
*/
struct UTI_FUT_CancelOrderResult
{


	/**
	*	0��ʾ�ɹ�������ֵ��ʾʧ��.
	*/
	int nErrID;

	/**
	*	������Ϣ.
	*/
	char chErrMsg[LEN_ERROR];

	/**
	*	ί�����.
	*/
	char chOrderNumber[LEN_ORDERNUMBER];

};


/**
*	�ֲ���Ϣ.
*/
struct UTI_FUT_Position
{

	/**
	* �Ự�е�Ψһ��ʶ�����ڱ�ʶ������¼.
	*/
	INT64     nIdentity;

	/**
	*	�г�.
	*/
	char szMarket[4];	

	/**
	*	���ױ�������.
	<table border="1">
	<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
	<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
	<tr><td>7</td><td>֣���ڻ�.</td></tr>
	<tr><td>8</td><td>�����ڻ�.</td></tr>
	</table>
	*/
	int nHolderType;

	/**
	*	����.
	*/ 	
	char szCode[12];

	/**
	*	֤ȯ����.
	*/
	char szName[12];

	/**
	*	��������.
	<table border="1">
	<tr><td>'B'</td><td>��(Buy)</td></tr>
	<tr><td>'S'</td><td>��(Sell)</td></tr>
	</table>
	*/
	char cBSSide;

	/**
	*	�ڳ�����.
	*/
	int  nBeginVol;					
	/**
	*	��������.
	*/
	int  nEnableVol;				
	/**
	*	���տ�ƽ������.
	*/
	int	 nRealVol;					

	/**
	*	���տ��ֿ�������.
	*/
	int  nTodayOpenVol;			
	/**
	*	ʵ������ƽ������.
	*/
	int	 nPreDropVol;			
	
	/**
	*	�ɱ��۸�������10000��.
	*/
	int  nCostPrice;				
	/**
	*	���¼۸�.
	*/
	int  nNewPrice;					

	/**
	*	����ӯ��.
	*/
	double dHoldProfit;				
	/**
	*	�ֲָ���ӯ��.
	*/
	double dHoldProfitFloat;		
	/**
	*	�Ͻ����ձ�֤��.
	*/
	double dHoldBal;				

	/**
	*	˵��.
	*/
	char chRemark[LEN_REMARK];		

};


/**
*	�ɽ�.
*/
struct UTI_FUT_Match
{
	/**
	* �Ự�е�Ψһ��ʶ�����ڱ�ʶ������¼.
	*/
	INT64     nIdentity;

	/**
	*	��������.
	*/
	UTI_FUT_Order order;

	/**
	*	��λ��.
	*/
	char chPostStr[LEN_POSTSTR];

	/**
	*	�ɽ�״̬.
	<table border="1">
	<tr><td>0</td><td>����</td></tr>
	<tr><td>1</td><td>����</td></tr>
	<tr><td>2</td><td>�ϵ�</td></tr>
	</table>
	*/
	int nStatus;											

	/**
	*	�ɽ�����.
	*/
	int  nMadeVolume;					

	/**
	*	�ɽ��۸�������10000��.
	*/
	int  nMadePrice;					
	/**
	*	��������.
	*/
	int  nCancelVolume;										

	/**
	*	�ɽ�ʱ��.
	*/
	int	 nMadeTime;											

	/**
	*	ί�����.
	*/
	char chOrderNumber[LEN_ORDERNUMBER];	
	
	/**
	*	�ɽ����.
	*/
	char chMadeNumber[LEN_MADENUMBER];		

	/**
	*	˵��.
	*/
	char chRemark[LEN_REMARK];			
	/**
	*	����˵��.
	*/
	char chRemark1[LEN_REMARK];		

	/**
	*	�����ܷ���.
	*/
	double dFrozFee;					

	/**
	*	ƽ��ӯ��.
	*/
	double dDropProfit;					

	/**
	*	ƽ�ָ���ӯ��.
	*/
	double dDropFrofitFloat;			

};


/**
*	�ʲ���¼.
*/
struct UTI_FUT_Assets
{
	/**
	* �Ự�е�Ψһ��ʶ�����ڱ�ʶ������¼.
	*/
	INT64     nIdentity;

	/**
	*	����.
	<table border="1">
	<tr><td>'0'</td><td>�����.</td></tr>
	<tr><td>'1'</td><td>�۱�.</td></tr>
	<tr><td>'2'</td><td>��Ԫ.</td></tr>
	</table>
	*/
	char chMoneyType;					
	/**
	*	˵��.
	*/
	char chRemark[LEN_REMARK];

	/**
	*	�ʽ����.
	*/
	double dCurrentBal;				
	/**
	*	�����ʽ�.
	*/
	double dEnableBal;				
	/**
	*	��ȡ�ʽ�.
	*/
	double dFetchBal;				
	/**
	*	��Լ��֤��.
	*/
	double dFrozBal;				
	/**
	*	���տ���Ԥ������.
	*/
	double dRealHoldBalA;			
	/**
	*	���տ���Ԥ���ᱣ֤��ͷ���.
	*/
	double dRealHoldBalB;			
	/**
	*	����ӯ��.
	*/
	double dHoldProfit;				
	/**
	*	�ܸ���ӯ��.
	*/
	double dHoldProfitFloat;		
	/**
	*	�ڳ��ͻ�Ȩ��.
	*/
	double dPreRightsBal;			
	/**
	*	�ͻ�Ȩ��.
	*/
	double dRightsBal;				
	/**
	*	�����ͻ�Ȩ��.
	*/
	double dRightsBalFloat;			

	/**
	*	����ƽ��ӯ��.
	*/
	double	dRealDrop;				
	/**
	*	����ƽ��ӯ��.
	*/
	double	dRealDrop_Float;		
	/**
	*	�������.
	*/
	double	dFrozenFare;		
	/**
	*	�ͻ���֤��.
	*/
	double	dBailBalance;			

	/**
	*	���п���ӯ��.
	*/
	double	dRealOpen;				
	/**
	*	��������ӯ��.
	*/
	double	dRealOpen_Float;		
	/**
	*	Ԥ����Ϣ.
	*/
	double dIntrBal;				
};

/**
*	���ɽ�������ѯ�ṹ.
*/
struct UTI_FUT_QueryMaxVolumeReq
{
	
	/**
	*	�г�.
	*/
	char szMarket[4];	

	/**
	*	���ױ�������.
	<table border="1">
	<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
	<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
	<tr><td>7</td><td>֣���ڻ�.</td></tr>
	<tr><td>8</td><td>�����ڻ�.</td></tr>
	</table>
	*/
	int nHolderType;

	/**
	*	����.
	*/ 	
	char szCode[12];	

	/**
	*	����.
	*/ 	
	char szName[16];

	/**
	*	��������.
	<table border="1">
	<tr><td>'B'</td><td>��(Buy)</td></tr>
	<tr><td>'S'</td><td>��(Sell)</td></tr>
	</table>
	*/
	char cBSSide;	

	/**
	*	��ƽ����.
	<table border="1">
	<tr><td>0</td><td>����</td></tr>
	<tr><td>1</td><td>ƽ��</td></tr>
	<tr><td>2</td><td>ƽ���</td></tr>
	</table>
	*/
	int nKPFlag;

	/**
	*	Ͷ����־.
	<table border="1">
	<tr><td>0</td><td>Ͷ��</td></tr>
	<tr><td>1</td><td>��ֵ</td></tr>
	</table>
	*/
	int nHedgeType;

	/**
	*	�۸񣬷Ŵ�10000��.
	*/
	int nPrice;	

};

/**
*	�ڻ���Լ.
*/
struct UTI_FUT_Agreement
{
	/**
	*	�г�.
	*/
	char szMarket[4];	

	/**
	*	���ױ�������.
	<table border="1">
	<tr><td>5</td><td>��ָ�ڻ�.</td></tr>
	<tr><td>6</td><td>�Ϻ��ڻ�.</td></tr>
	<tr><td>7</td><td>֣���ڻ�.</td></tr>
	<tr><td>8</td><td>�����ڻ�.</td></tr>
	</table>
	*/
	int nHolderType;

	/**
	*	����.
	*/ 	
	char szCode[12];	

	/**
	*	����.
	*/ 	
	char szName[16];

	/**
	*	��ŷ�ʽ.
	<table border="1">
	<tr><td>'1'</td><td>���ִ��.</td></tr>
	<tr><td>'2'</td><td>���ִ��.</td></tr>
	</table>
	*/
	char chPriceUnit;				
	/**
	*	��Լ�������.
	*/
	char chFutType;					
	/**
	*	��ʼ���ױ�־.
	<table border="1">
	<tr><td>'0'</td><td>����.</td></tr>
	<tr><td>'1'</td><td>ֹͣ.</td></tr>
	</table>
	*/
	char chStopFlag;				
	/**
	*	�걨��λ.
	*/
	char chReportUnit;				
	/**
	*	ÿ�ֶ���.
	*/
	int nAmountPerHand;				
		
	/**
	*	��С�۲�.
	*/
	double dPriceStep;				
	/**
	*	������С��λ.
	*/
	double dHoldUnit;				
	/**
	*	ƽ����С��λ.
	*/
	double dDropUnit;			
	/**
	*	�м�ί��ÿ������µ�����.
	*/
	double dMarketAmount;			
	/**
	*	�޼�ί��ÿ������µ�����.
	*/
	double dLimitedAmount;			

	/**
	*	���ֱ�֤�����.
	*/
	double	dOpenBailRatio;			
	/**
	*	���ֱ�֤��.
	*/
	double	dOpenBailBalance;		
	/**
	*	ƽ�ֱ�֤�����.
	*/
	double	dDropBailRatio;			
	/**
	*	ƽ�ֱ�֤��.
	*/
	double	dDropBailBalance;		
	/**
	*	���֤�����.
	*/
	double	dDeliverBailRatio;		
	/**
	*	���֤��.
	*/
	double	dDeliverBailBalance;	
	/**
	*	ƽ��ֱ�֤�����.
	*/
	double	dDropcuBailRatio;		
	/**
	*	ƽ��ֱ�֤��.
	*/
	double	dDropcuBailBalance;		

	/**
	*	˵��.
	*/
	char chRemark[LEN_REMARK];		
};

/**
*	�ڻ��ı��˵�.
*/
struct UTI_FUT_Bill
{
	/**
	*	��Ϣ����.
	*/
	int nInfoDate;	
	/**
	*	��Ϣʱ��.
	*/
	int nInfoTime;	

	/**
	*	��Ϣ����.
	*/
	char chInfoMsg[32*1024L];
	/**
	*	��Ϣ����.
	*/
	int nInfoLen;
};

#pragma pack(pop)
#endif __UTIDEFINE_FUT_H_
