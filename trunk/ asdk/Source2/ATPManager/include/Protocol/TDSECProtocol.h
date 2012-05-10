/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 OpenTD 协议.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-1		李伟		 创建
-------------------------------------------------------------
*/
#pragma once

#ifndef __TDSECPROTOCOL__H__
#define __TDSECPROTOCOL__H__
#include "..\\..\\include\\utiapi\\UTIDefine_Sec.h"



#pragma pack(push,1)


typedef  ATP_Msg_Array_Head ATP_Msg_Sec_Array_Head;



//--------------------------普通方式下单----------------------------------------------/
/////////////////////// 发送 ////////////////////////////////////////////////////////// 

/**
消息头信息.
*/
typedef ATP_Msg_Sec_Array_Head			ATP_Msg_Sec_MakeOrder_Head;

/**
证券下单时的内容
*/ 
typedef UTI_SEC_Order				ATP_Msg_Sec_MakeOrder;

/////////////////////////返回///////////////////////////////////////////////////////////

/**
下单返回的头，
*/ 
typedef ATP_Msg_Sec_Array_Head			 ATP_Msg_Sec_MakeOrderAnswer_Head;

/**
证券下单时的应答.
*/ 
typedef UTI_SEC_MakeOrderResult		 ATP_Msg_Sec_MakeOrder_Answer;

//------------------------------------------------------------------------------------/



/**
证券持仓查询.
*/ 
struct ATP_Msg_Sec_QueryParamter
{
	/**
	查询方式，
	0，全部持仓查询，
	1，仅查指定市场，
	2，仅查指定市场，指定品种。
	3, 按合同序号查询.
	*/ 	
	int nQueryMethod;

	union
	{
		struct 
		{
			/**
			*   股东类型
			<table border="1">
			<tr><td>1</td><td>深圳A股.</td></tr>
			<tr><td>2</td><td>深圳B股.</td></tr>
			<tr><td>3</td><td>上海A股.</td></tr>
			<tr><td>4</td><td>上海B股.</td></tr>
			</table>
			*/
			int nHoldType;

			/**
			指定市场.
			*/ 	
			char szMarket[4];

			/**
			指定代码.
			*/ 	
			char szCode[12];
		}ID;

		/**
		合同序号
		*/ 		
		char chOrderNumber[LEN_ORDERNUMBER];
	};
};







//--------------------------持仓查询.-------------------------------------------------/
/////////////////////// 发送 //////////////////////////////////////////////////////////  
/**
持仓查询.
*/
typedef ATP_Msg_Sec_QueryParamter    ATP_Msg_Sec_QueryHoldPositions;

/////////////////////////返回///////////////////////////////////////////////////////////

/**
证券持仓查询返回头信息
*/
typedef ATP_Msg_Sec_Array_Head			  ATP_Msg_Sec_QueryHoldPositions_Answer_Head;

/**
证券持仓信息.
*/ 
typedef UTI_SEC_Position				ATP_Msg_Sec_HoldPosition;
//---------------------------------------------------------------------------------------/









//--------------------------------委托记录查询----------------------------------------/
/////////////////////// 发送 //////////////////////////////////////////////////////////           
/**
委托记录查询
*/ 
typedef    ATP_Msg_Sec_QueryParamter    ATP_Msg_Sec_QueryOrderRecords;

/////////////////////////返回///////////////////////////////////////////////////////////

/**
委托记录查询,返回头信息
*/
typedef ATP_Msg_Sec_Array_Head			  ATP_Msg_Sec_QueryOrderRecords_Answer_Head;

/**
委托记录.
*/ 
typedef UTI_SEC_OrderRecord			      ATP_Msg_Sec_QueryOrderRecords_Answer;
//---------------------------------------------------------------------------------------/











//--------------------------------可撤单查询----------------------------------------/
/////////////////////// 发送 ////////////////////////////////////////////////////////// 
/**
可撤单查询时，指定的查询方式，同持仓查询时的查询方式相同.
*/
typedef	ATP_Msg_Sec_QueryHoldPositions			ATP_Msg_Sec_QueryCanCancel;


/////////////////////////返回///////////////////////////////////////////////////////////
/**
可撤单查询结果,头信息.
*/
typedef ATP_Msg_Sec_Array_Head						ATP_Msg_Sec_QueryCanCancel_Answer_Head;
	

/**
可撤单查询结果.
*/
typedef UTI_SEC_OrderRecord						ATP_Msg_Sec_QueryCanCancel_Answer;
//---------------------------------------------------------------------------------------/




//----------------------------------------撤单----------------------------------------/
/////////////////////// 发送 ////////////////////////////////////////////////////////// 
/**
可撤单查询结果,头信息.
*/
typedef ATP_Msg_Sec_Array_Head						ATP_Msg_Sec_MakeCancelOrder_Head;

typedef  UTI_SEC_OrderRecord                         ATP_Msg_Sec_MakeCancelOrder;

/////////////////////////返回///////////////////////////////////////////////////////////
/**
可撤单查询结果,头信息.
*/
typedef ATP_Msg_Sec_Array_Head						ATP_Msg_Sec_MakeCancelOrder_Answer_Head;
/**
撤单结果。
*/ 
typedef UTI_SEC_CancelOrderResult				ATP_Msg_Sec_MakeCancelOrder_Answer;
//-------------------------------------------------------------------------------------/








//----------------------------------------成交查询------------------------------------/
/////////////////////// 发送 //////////////////////////////////////////////////////////
/**
成交记录查询
*/ 
typedef    ATP_Msg_Sec_QueryParamter    ATP_Msg_Sec_QueryMatch;

/////////////////////////返回///////////////////////////////////////////////////////////
/**
成交记录结果,头信息.
*/
typedef ATP_Msg_Sec_Array_Head						ATP_Msg_Sec_QueryMatch_Answer_Head;
/**
成交记录结果。
*/ 
typedef UTI_SEC_Match				ATP_Msg_Sec_QueryMatch_Answer;
//-------------------------------------------------------------------------------------/




//----------------------------------------资产查询------------------------------------/
/////////////////////// 发送 //////////////////////////////////////////////////////////
/**
资产查询
*/ 
struct ATP_Msg_Sec_QueryAssets
{
	/**
	查询方式 
	'A'		所有币种
	'0'		人民币 
	'1'     港币
	'2'		美元
	*/ 	
	char nQueryMethod;
};
/////////////////////////返回///////////////////////////////////////////////////////////
/**
资产查询结果,头信息.
*/
typedef ATP_Msg_Sec_Array_Head						ATP_Msg_Sec_QueryAssets_Answer_Head;
/**
成交记录结果。
*/ 
typedef UTI_SEC_Assets							ATP_Msg_Sec_QueryAssets_Answer;
//-------------------------------------------------------------------------------------/




//---------------------------------最大可交易量查询------------------------------------/
/////////////////////// 发送 //////////////////////////////////////////////////////////
/**
最大可交易量查询
*/ 
typedef UTI_SEC_QueryMaxVolumeReq	ATP_Msg_Sec_QueryMaxVolume;


/////////////////////////返回///////////////////////////////////////////////////////////

struct ATP_Msg_Sec_QueryMaxVolume_Answer{

	ATP_Msg_Sec_QueryMaxVolume query;

    INT64 iMaxVolume;									
};



//-------------------------------------------------------------------------------------/




#pragma pack(pop)

#endif //__TDSECPROTOCOL__H__
