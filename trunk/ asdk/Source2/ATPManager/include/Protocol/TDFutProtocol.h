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

#ifndef __TDFUTPROTOCOL__H__
#define __TDFUTPROTOCOL__H__
#include "..\\..\\include\\utiapi\\UTIDefine_Fut.h"


#pragma pack(push,1)


typedef  ATP_Msg_Array_Head ATP_Msg_Fut_Array_Head;



//--------------------------普通方式下单----------------------------------------------/
/////////////////////// 发送 ////////////////////////////////////////////////////////// 

/**
消息头信息.
*/
typedef ATP_Msg_Fut_Array_Head			ATP_Msg_Fut_MakeOrder_Head;

/**
期货下单时的内容
*/ 
typedef UTI_FUT_Order				ATP_Msg_Fut_MakeOrder;

/////////////////////////返回///////////////////////////////////////////////////////////

/**
下单返回的头，
*/ 
typedef ATP_Msg_Fut_Array_Head			 ATP_Msg_Fut_MakeOrderAnswer_Head;

/**
期货下单时的应答.
*/ 
typedef UTI_FUT_MakeOrderResult		 ATP_Msg_Fut_MakeOrder_Answer;

//------------------------------------------------------------------------------------/



/**
期货持仓查询.
*/ 
struct ATP_Msg_Fut_QueryParamter
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
			5 CF 
			6 SP SHFE
			7 SP ZCE
			8 SP DCE

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
typedef ATP_Msg_Fut_QueryParamter    ATP_Msg_Fut_QueryHoldPositions;

/////////////////////////返回///////////////////////////////////////////////////////////

/**
期货持仓查询返回头信息
*/
typedef ATP_Msg_Fut_Array_Head			  ATP_Msg_Fut_QueryHoldPositions_Answer_Head;

/**
期货持仓信息.
*/ 
typedef UTI_FUT_Position				ATP_Msg_Fut_HoldPosition;
//---------------------------------------------------------------------------------------/









//--------------------------------委托记录查询----------------------------------------/
/////////////////////// 发送 //////////////////////////////////////////////////////////           
/**
委托记录查询
*/ 
typedef    ATP_Msg_Fut_QueryParamter    ATP_Msg_Fut_QueryOrderRecords;

/////////////////////////返回///////////////////////////////////////////////////////////

/**
委托记录查询,返回头信息
*/
typedef ATP_Msg_Fut_Array_Head			  ATP_Msg_Fut_QueryOrderRecords_Answer_Head;

/**
委托记录.
*/ 
typedef UTI_FUT_OrderRecord			 ATP_Msg_Fut_QueryOrderRecords_Answer;
//---------------------------------------------------------------------------------------/











//--------------------------------可撤单查询----------------------------------------/
/////////////////////// 发送 ////////////////////////////////////////////////////////// 
/**
可撤单查询时，指定的查询方式，同持仓查询时的查询方式相同.
*/
typedef	ATP_Msg_Fut_QueryHoldPositions			ATP_Msg_Fut_QueryCanCancel;


/////////////////////////返回///////////////////////////////////////////////////////////
/**
可撤单查询结果,头信息.
*/
typedef ATP_Msg_Fut_Array_Head						ATP_Msg_Fut_QueryCanCancel_Answer_Head;
	

/**
可撤单查询结果.
*/
typedef UTI_FUT_OrderRecord						ATP_Msg_Fut_QueryCanCancel_Answer;
//---------------------------------------------------------------------------------------/




//----------------------------------------撤单----------------------------------------/
/////////////////////// 发送 ////////////////////////////////////////////////////////// 
/**
可撤单查询结果,头信息.
*/
typedef ATP_Msg_Fut_Array_Head						ATP_Msg_Fut_MakeCancelOrder_Head;

typedef UTI_FUT_OrderRecord ATP_Msg_Fut_MakeCancelOrder;

/*struct ATP_Msg_Fut_MakeCancelOrder
{
	/ **
	委托编号
	* /
	char szOrderNumber[LEN_ORDERNUMBER];
};*/

/////////////////////////返回///////////////////////////////////////////////////////////
/**
可撤单查询结果,头信息.
*/
typedef ATP_Msg_Fut_Array_Head						ATP_Msg_Fut_MakeCancelOrder_Answer_Head;


/**
撤单结果。
*/ 
typedef UTI_FUT_CancelOrderResult				ATP_Msg_Fut_MakeCancelOrder_Answer;
//-------------------------------------------------------------------------------------/








//----------------------------------------成交查询------------------------------------/
/////////////////////// 发送 //////////////////////////////////////////////////////////
/**
成交记录查询
*/ 
typedef    ATP_Msg_Fut_QueryParamter    ATP_Msg_Fut_QueryMatch;

/////////////////////////返回///////////////////////////////////////////////////////////
/**
成交记录结果,头信息.
*/
typedef ATP_Msg_Fut_Array_Head						ATP_Msg_Fut_QueryMatch_Answer_Head;
/**
成交记录结果。
*/ 
typedef UTI_FUT_Match				ATP_Msg_Fut_QueryMatch_Answer;
//-------------------------------------------------------------------------------------/




//----------------------------------------资产查询------------------------------------/
/////////////////////// 发送 //////////////////////////////////////////////////////////
/**
资产查询
*/ 
struct ATP_Msg_Fut_QueryAssets
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
typedef ATP_Msg_Fut_Array_Head						ATP_Msg_Fut_QueryAssets_Answer_Head;
/**
成交记录结果。
*/ 
typedef UTI_FUT_Assets							ATP_Msg_Fut_QueryAssets_Answer;
//-------------------------------------------------------------------------------------/




//---------------------------------最大可交易量查询------------------------------------/
/////////////////////// 发送 //////////////////////////////////////////////////////////
/**
最大可交易量查询
*/ 
typedef UTI_FUT_QueryMaxVolumeReq	ATP_Msg_Fut_QueryMaxVolume;


/////////////////////////返回///////////////////////////////////////////////////////////

struct ATP_Msg_Fut_QueryMaxVolume_Answer{

	ATP_Msg_Fut_QueryMaxVolume query;

    INT64 iMaxVolume;									
};


#pragma pack(pop)

#endif //__TDFUTPROTOCOL__H__
