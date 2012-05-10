/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 OpenTD Э��.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-1		��ΰ		 ����
-------------------------------------------------------------
*/

#pragma once

#ifndef __TDFUTPROTOCOL__H__
#define __TDFUTPROTOCOL__H__
#include "..\\..\\include\\utiapi\\UTIDefine_Fut.h"


#pragma pack(push,1)


typedef  ATP_Msg_Array_Head ATP_Msg_Fut_Array_Head;



//--------------------------��ͨ��ʽ�µ�----------------------------------------------/
/////////////////////// ���� ////////////////////////////////////////////////////////// 

/**
��Ϣͷ��Ϣ.
*/
typedef ATP_Msg_Fut_Array_Head			ATP_Msg_Fut_MakeOrder_Head;

/**
�ڻ��µ�ʱ������
*/ 
typedef UTI_FUT_Order				ATP_Msg_Fut_MakeOrder;

/////////////////////////����///////////////////////////////////////////////////////////

/**
�µ����ص�ͷ��
*/ 
typedef ATP_Msg_Fut_Array_Head			 ATP_Msg_Fut_MakeOrderAnswer_Head;

/**
�ڻ��µ�ʱ��Ӧ��.
*/ 
typedef UTI_FUT_MakeOrderResult		 ATP_Msg_Fut_MakeOrder_Answer;

//------------------------------------------------------------------------------------/



/**
�ڻ��ֲֲ�ѯ.
*/ 
struct ATP_Msg_Fut_QueryParamter
{
	/**
	��ѯ��ʽ��
	0��ȫ���ֲֲ�ѯ��
	1������ָ���г���
	2������ָ���г���ָ��Ʒ�֡�
	3, ����ͬ��Ų�ѯ.
	*/ 	
	int nQueryMethod;

	union
	{
		struct 
		{
			/**
			*   �ɶ�����
			5 CF 
			6 SP SHFE
			7 SP ZCE
			8 SP DCE

			*/
			int nHoldType;


			/**
			ָ���г�.
			*/ 	
			char szMarket[4];

			/**
			ָ������.
			*/ 	
			char szCode[12];
		}ID;

		/**
		��ͬ���
		*/ 		
		char chOrderNumber[LEN_ORDERNUMBER];
	};
};







//--------------------------�ֲֲ�ѯ.-------------------------------------------------/
/////////////////////// ���� //////////////////////////////////////////////////////////  
/**
�ֲֲ�ѯ.
*/
typedef ATP_Msg_Fut_QueryParamter    ATP_Msg_Fut_QueryHoldPositions;

/////////////////////////����///////////////////////////////////////////////////////////

/**
�ڻ��ֲֲ�ѯ����ͷ��Ϣ
*/
typedef ATP_Msg_Fut_Array_Head			  ATP_Msg_Fut_QueryHoldPositions_Answer_Head;

/**
�ڻ��ֲ���Ϣ.
*/ 
typedef UTI_FUT_Position				ATP_Msg_Fut_HoldPosition;
//---------------------------------------------------------------------------------------/









//--------------------------------ί�м�¼��ѯ----------------------------------------/
/////////////////////// ���� //////////////////////////////////////////////////////////           
/**
ί�м�¼��ѯ
*/ 
typedef    ATP_Msg_Fut_QueryParamter    ATP_Msg_Fut_QueryOrderRecords;

/////////////////////////����///////////////////////////////////////////////////////////

/**
ί�м�¼��ѯ,����ͷ��Ϣ
*/
typedef ATP_Msg_Fut_Array_Head			  ATP_Msg_Fut_QueryOrderRecords_Answer_Head;

/**
ί�м�¼.
*/ 
typedef UTI_FUT_OrderRecord			 ATP_Msg_Fut_QueryOrderRecords_Answer;
//---------------------------------------------------------------------------------------/











//--------------------------------�ɳ�����ѯ----------------------------------------/
/////////////////////// ���� ////////////////////////////////////////////////////////// 
/**
�ɳ�����ѯʱ��ָ���Ĳ�ѯ��ʽ��ͬ�ֲֲ�ѯʱ�Ĳ�ѯ��ʽ��ͬ.
*/
typedef	ATP_Msg_Fut_QueryHoldPositions			ATP_Msg_Fut_QueryCanCancel;


/////////////////////////����///////////////////////////////////////////////////////////
/**
�ɳ�����ѯ���,ͷ��Ϣ.
*/
typedef ATP_Msg_Fut_Array_Head						ATP_Msg_Fut_QueryCanCancel_Answer_Head;
	

/**
�ɳ�����ѯ���.
*/
typedef UTI_FUT_OrderRecord						ATP_Msg_Fut_QueryCanCancel_Answer;
//---------------------------------------------------------------------------------------/




//----------------------------------------����----------------------------------------/
/////////////////////// ���� ////////////////////////////////////////////////////////// 
/**
�ɳ�����ѯ���,ͷ��Ϣ.
*/
typedef ATP_Msg_Fut_Array_Head						ATP_Msg_Fut_MakeCancelOrder_Head;

typedef UTI_FUT_OrderRecord ATP_Msg_Fut_MakeCancelOrder;

/*struct ATP_Msg_Fut_MakeCancelOrder
{
	/ **
	ί�б��
	* /
	char szOrderNumber[LEN_ORDERNUMBER];
};*/

/////////////////////////����///////////////////////////////////////////////////////////
/**
�ɳ�����ѯ���,ͷ��Ϣ.
*/
typedef ATP_Msg_Fut_Array_Head						ATP_Msg_Fut_MakeCancelOrder_Answer_Head;


/**
���������
*/ 
typedef UTI_FUT_CancelOrderResult				ATP_Msg_Fut_MakeCancelOrder_Answer;
//-------------------------------------------------------------------------------------/








//----------------------------------------�ɽ���ѯ------------------------------------/
/////////////////////// ���� //////////////////////////////////////////////////////////
/**
�ɽ���¼��ѯ
*/ 
typedef    ATP_Msg_Fut_QueryParamter    ATP_Msg_Fut_QueryMatch;

/////////////////////////����///////////////////////////////////////////////////////////
/**
�ɽ���¼���,ͷ��Ϣ.
*/
typedef ATP_Msg_Fut_Array_Head						ATP_Msg_Fut_QueryMatch_Answer_Head;
/**
�ɽ���¼�����
*/ 
typedef UTI_FUT_Match				ATP_Msg_Fut_QueryMatch_Answer;
//-------------------------------------------------------------------------------------/




//----------------------------------------�ʲ���ѯ------------------------------------/
/////////////////////// ���� //////////////////////////////////////////////////////////
/**
�ʲ���ѯ
*/ 
struct ATP_Msg_Fut_QueryAssets
{
	/**
	��ѯ��ʽ 
	'A'		���б���
	'0'		����� 
	'1'     �۱�
	'2'		��Ԫ
	*/ 	
	char nQueryMethod;
};
/////////////////////////����///////////////////////////////////////////////////////////
/**
�ʲ���ѯ���,ͷ��Ϣ.
*/
typedef ATP_Msg_Fut_Array_Head						ATP_Msg_Fut_QueryAssets_Answer_Head;
/**
�ɽ���¼�����
*/ 
typedef UTI_FUT_Assets							ATP_Msg_Fut_QueryAssets_Answer;
//-------------------------------------------------------------------------------------/




//---------------------------------���ɽ�������ѯ------------------------------------/
/////////////////////// ���� //////////////////////////////////////////////////////////
/**
���ɽ�������ѯ
*/ 
typedef UTI_FUT_QueryMaxVolumeReq	ATP_Msg_Fut_QueryMaxVolume;


/////////////////////////����///////////////////////////////////////////////////////////

struct ATP_Msg_Fut_QueryMaxVolume_Answer{

	ATP_Msg_Fut_QueryMaxVolume query;

    INT64 iMaxVolume;									
};


#pragma pack(pop)

#endif //__TDFUTPROTOCOL__H__
