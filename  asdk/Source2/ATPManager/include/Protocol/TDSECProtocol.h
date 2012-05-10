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

#ifndef __TDSECPROTOCOL__H__
#define __TDSECPROTOCOL__H__
#include "..\\..\\include\\utiapi\\UTIDefine_Sec.h"



#pragma pack(push,1)


typedef  ATP_Msg_Array_Head ATP_Msg_Sec_Array_Head;



//--------------------------��ͨ��ʽ�µ�----------------------------------------------/
/////////////////////// ���� ////////////////////////////////////////////////////////// 

/**
��Ϣͷ��Ϣ.
*/
typedef ATP_Msg_Sec_Array_Head			ATP_Msg_Sec_MakeOrder_Head;

/**
֤ȯ�µ�ʱ������
*/ 
typedef UTI_SEC_Order				ATP_Msg_Sec_MakeOrder;

/////////////////////////����///////////////////////////////////////////////////////////

/**
�µ����ص�ͷ��
*/ 
typedef ATP_Msg_Sec_Array_Head			 ATP_Msg_Sec_MakeOrderAnswer_Head;

/**
֤ȯ�µ�ʱ��Ӧ��.
*/ 
typedef UTI_SEC_MakeOrderResult		 ATP_Msg_Sec_MakeOrder_Answer;

//------------------------------------------------------------------------------------/



/**
֤ȯ�ֲֲ�ѯ.
*/ 
struct ATP_Msg_Sec_QueryParamter
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
			<table border="1">
			<tr><td>1</td><td>����A��.</td></tr>
			<tr><td>2</td><td>����B��.</td></tr>
			<tr><td>3</td><td>�Ϻ�A��.</td></tr>
			<tr><td>4</td><td>�Ϻ�B��.</td></tr>
			</table>
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
typedef ATP_Msg_Sec_QueryParamter    ATP_Msg_Sec_QueryHoldPositions;

/////////////////////////����///////////////////////////////////////////////////////////

/**
֤ȯ�ֲֲ�ѯ����ͷ��Ϣ
*/
typedef ATP_Msg_Sec_Array_Head			  ATP_Msg_Sec_QueryHoldPositions_Answer_Head;

/**
֤ȯ�ֲ���Ϣ.
*/ 
typedef UTI_SEC_Position				ATP_Msg_Sec_HoldPosition;
//---------------------------------------------------------------------------------------/









//--------------------------------ί�м�¼��ѯ----------------------------------------/
/////////////////////// ���� //////////////////////////////////////////////////////////           
/**
ί�м�¼��ѯ
*/ 
typedef    ATP_Msg_Sec_QueryParamter    ATP_Msg_Sec_QueryOrderRecords;

/////////////////////////����///////////////////////////////////////////////////////////

/**
ί�м�¼��ѯ,����ͷ��Ϣ
*/
typedef ATP_Msg_Sec_Array_Head			  ATP_Msg_Sec_QueryOrderRecords_Answer_Head;

/**
ί�м�¼.
*/ 
typedef UTI_SEC_OrderRecord			      ATP_Msg_Sec_QueryOrderRecords_Answer;
//---------------------------------------------------------------------------------------/











//--------------------------------�ɳ�����ѯ----------------------------------------/
/////////////////////// ���� ////////////////////////////////////////////////////////// 
/**
�ɳ�����ѯʱ��ָ���Ĳ�ѯ��ʽ��ͬ�ֲֲ�ѯʱ�Ĳ�ѯ��ʽ��ͬ.
*/
typedef	ATP_Msg_Sec_QueryHoldPositions			ATP_Msg_Sec_QueryCanCancel;


/////////////////////////����///////////////////////////////////////////////////////////
/**
�ɳ�����ѯ���,ͷ��Ϣ.
*/
typedef ATP_Msg_Sec_Array_Head						ATP_Msg_Sec_QueryCanCancel_Answer_Head;
	

/**
�ɳ�����ѯ���.
*/
typedef UTI_SEC_OrderRecord						ATP_Msg_Sec_QueryCanCancel_Answer;
//---------------------------------------------------------------------------------------/




//----------------------------------------����----------------------------------------/
/////////////////////// ���� ////////////////////////////////////////////////////////// 
/**
�ɳ�����ѯ���,ͷ��Ϣ.
*/
typedef ATP_Msg_Sec_Array_Head						ATP_Msg_Sec_MakeCancelOrder_Head;

typedef  UTI_SEC_OrderRecord                         ATP_Msg_Sec_MakeCancelOrder;

/////////////////////////����///////////////////////////////////////////////////////////
/**
�ɳ�����ѯ���,ͷ��Ϣ.
*/
typedef ATP_Msg_Sec_Array_Head						ATP_Msg_Sec_MakeCancelOrder_Answer_Head;
/**
���������
*/ 
typedef UTI_SEC_CancelOrderResult				ATP_Msg_Sec_MakeCancelOrder_Answer;
//-------------------------------------------------------------------------------------/








//----------------------------------------�ɽ���ѯ------------------------------------/
/////////////////////// ���� //////////////////////////////////////////////////////////
/**
�ɽ���¼��ѯ
*/ 
typedef    ATP_Msg_Sec_QueryParamter    ATP_Msg_Sec_QueryMatch;

/////////////////////////����///////////////////////////////////////////////////////////
/**
�ɽ���¼���,ͷ��Ϣ.
*/
typedef ATP_Msg_Sec_Array_Head						ATP_Msg_Sec_QueryMatch_Answer_Head;
/**
�ɽ���¼�����
*/ 
typedef UTI_SEC_Match				ATP_Msg_Sec_QueryMatch_Answer;
//-------------------------------------------------------------------------------------/




//----------------------------------------�ʲ���ѯ------------------------------------/
/////////////////////// ���� //////////////////////////////////////////////////////////
/**
�ʲ���ѯ
*/ 
struct ATP_Msg_Sec_QueryAssets
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
typedef ATP_Msg_Sec_Array_Head						ATP_Msg_Sec_QueryAssets_Answer_Head;
/**
�ɽ���¼�����
*/ 
typedef UTI_SEC_Assets							ATP_Msg_Sec_QueryAssets_Answer;
//-------------------------------------------------------------------------------------/




//---------------------------------���ɽ�������ѯ------------------------------------/
/////////////////////// ���� //////////////////////////////////////////////////////////
/**
���ɽ�������ѯ
*/ 
typedef UTI_SEC_QueryMaxVolumeReq	ATP_Msg_Sec_QueryMaxVolume;


/////////////////////////����///////////////////////////////////////////////////////////

struct ATP_Msg_Sec_QueryMaxVolume_Answer{

	ATP_Msg_Sec_QueryMaxVolume query;

    INT64 iMaxVolume;									
};



//-------------------------------------------------------------------------------------/




#pragma pack(pop)

#endif //__TDSECPROTOCOL__H__
