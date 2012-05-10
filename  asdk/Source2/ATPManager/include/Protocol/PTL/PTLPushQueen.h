/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法交易平台 推送模板库.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			 作者         修改说明
2010-11-29	 李伟		 创建
-------------------------------------------------------------
*/

#pragma once
#ifndef _PTLPUSHQUEEN_H_
#define _PTLPUSHQUEEN_H_

#include "TDPushProtocol.h"
#include "..\\TDSECProtocol.h"
#include "..\\TDFutProtocol.h"





#include "atlcore.h"
#include <map>
#include <algorithm>
using namespace std;


#pragma pack(push,1)

struct PARTCOMPRESS_HEAD
{
	UINT_PTR  nId;
	ATP_MSG_PUSH_ITEM_METHOD nMethod;
};

#pragma pack(pop)

//压缩功能
#include "..\\..\\hhpfdk\HHNetCompressHelper.h"
#include "..\\..\\hhpfdk\HHNetCompareCompressHelper.h"

/**
* 压缩持仓信息到指定的内存中
* @param pPosition  持仓信息　
* @param pData      指写的内存
* @param nLength 内存长度
*/
extern int ptl_compress(const ATP_Msg_Sec_HoldPosition* pPosition,
						char* pData,
						int nLength);


/**
* 从指定的内存中解压缩持仓信息
* @param pData      指写的内存
* @param nBufferLen 内存长度
* @param pPosition  持仓信息　
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Sec_HoldPosition* pPosition);



/**
* 对比压缩持仓信息到指定的内存中
* @param pNew		新的持仓信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的持仓信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
extern int ptl_comparecmpress(const ATP_Msg_Sec_HoldPosition* New,
							  const ATP_Msg_Sec_HoldPosition* Old,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Sec_HoldPosition* pPosition);


////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
* 压缩委托记录信息到指定的内存中
* @param pOrderRecord  委托记录
* @param pData      指写的内存
* @param nLength 内存长度
*/
extern int ptl_compress(const ATP_Msg_Sec_QueryOrderRecords_Answer* pOrderRecord,
						char* pData,
						int nLength);


/**
* 从指定的内存中解压缩持仓信息
* @param pData      指写的内存
* @param nBufferLen 内存长度
* @param pOrderRecord  委托记录　
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Sec_QueryOrderRecords_Answer* pOrderRecord);



/**
* 对比压缩持仓信息到指定的内存中
* @param pNew		新的委托信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的委托信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
extern int ptl_comparecmpress(const ATP_Msg_Sec_QueryOrderRecords_Answer* pNew,
							  const ATP_Msg_Sec_QueryOrderRecords_Answer* pOld,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Sec_QueryOrderRecords_Answer* pOrderRecord);

////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
* 压缩成交记录信息到指定的内存中
* @param pMatch  成交记录
* @param pData   指写的内存
* @param nLength 内存长度
*/
extern int ptl_compress(const ATP_Msg_Sec_QueryMatch_Answer* pMatch,
						char* pData,
						int nLength);


/**
* 从指定的内存中解压缩成交信息
* @param pData      指写的内存
* @param nBufferLen 内存长度
* @param pMatch  成交记录
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Sec_QueryMatch_Answer* pMatch);



/**
* 对比压缩成交信息到指定的内存中
* @param pNew		新的委托信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的委托信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
extern int ptl_comparecmpress(const ATP_Msg_Sec_QueryMatch_Answer* pNew,
							  const ATP_Msg_Sec_QueryMatch_Answer* pOld,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Sec_QueryMatch_Answer* pMatch);


//资产
///////////////////////////////////////////////////////////////////////////////////////////////////////


/**
* 压缩资产记录信息到指定的内存中
* @param pAssets 资产记录
* @param pData   指写的内存
* @param nLength 内存长度
*/
extern int ptl_compress(const ATP_Msg_Sec_QueryAssets_Answer* pAssets,
						char* pData,
						int nLength);


/**
* 从指定的内存中解压缩资产信息
* @param pData      指写的内存
* @param nBufferLen 内存长度
* @param pAssets  资产记录
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Sec_QueryAssets_Answer* pAssets);



/**
* 对比压缩资产到指定的内存中
* @param pNew		新的资产信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的资产信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
extern int ptl_comparecmpress(const ATP_Msg_Sec_QueryAssets_Answer* pNew,
							  const ATP_Msg_Sec_QueryAssets_Answer* pOld,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Sec_QueryAssets_Answer* pStatus);

//////////////////////////////////////////////////////////////////////////
/**
* 压缩下单信息到指定的内存中
* @param pPosition  持仓信息　
* @param pData      指写的内存
* @param nLength 内存长度
*/
extern int ptl_compress(const ATP_Msg_Sec_MakeOrder* pMakeOrder,
	char* pData,
	int nLength);


/**
* 从指定的内存中解压下单信息
* @param pData      指写的内存
* @param nBufferLen 内存长度
* @param pPosition  持仓信息　
*/
extern int ptl_decmpress(char* pData,
	int nLength,
	ATP_Msg_Sec_MakeOrder* pMakeOrder);



/**
* 对比压缩下单信息到指定的内存中
* @param pNew		新的持仓信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的持仓信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
extern int ptl_comparecmpress(const ATP_Msg_Sec_MakeOrder* New,
	const ATP_Msg_Sec_MakeOrder* Old,
	char* pData,
	int nLength);

//************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////

//期货部分

/**
* 压缩持仓信息到指定的内存中
* @param pPosition  持仓信息　
* @param pData      指写的内存
* @param nLength 内存长度
*/
extern int ptl_compress(const ATP_Msg_Fut_HoldPosition* pPosition,
						char* pData,
						int nLength);


/**
* 从指定的内存中解压缩持仓信息
* @param pData      指写的内存
* @param nBufferLen 内存长度
* @param pPosition  持仓信息　
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Fut_HoldPosition* pPosition);



/**
* 对比压缩持仓信息到指定的内存中
* @param pNew		新的持仓信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的持仓信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
extern int ptl_comparecmpress(const ATP_Msg_Fut_HoldPosition* New,
							  const ATP_Msg_Fut_HoldPosition* Old,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Fut_HoldPosition* pPosition);


////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
* 压缩委托记录信息到指定的内存中
* @param pOrderRecord  委托记录
* @param pData      指写的内存
* @param nLength 内存长度
*/
extern int ptl_compress(const ATP_Msg_Fut_QueryOrderRecords_Answer* pOrderRecord,
						char* pData,
						int nLength);


/**
* 从指定的内存中解压缩持仓信息
* @param pData      指写的内存
* @param nBufferLen 内存长度
* @param pOrderRecord  委托记录　
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Fut_QueryOrderRecords_Answer* pOrderRecord);



/**
* 对比压缩持仓信息到指定的内存中
* @param pNew		新的委托信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的委托信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
extern int ptl_comparecmpress(const ATP_Msg_Fut_QueryOrderRecords_Answer* pNew,
							  const ATP_Msg_Fut_QueryOrderRecords_Answer* pOld,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Fut_QueryOrderRecords_Answer* pOrderRecord);

////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
* 压缩成交记录信息到指定的内存中
* @param pMatch  成交记录
* @param pData   指写的内存
* @param nLength 内存长度
*/
extern int ptl_compress(const ATP_Msg_Fut_QueryMatch_Answer* pMatch,
						char* pData,
						int nLength);


/**
* 从指定的内存中解压缩成交信息
* @param pData      指写的内存
* @param nBufferLen 内存长度
* @param pMatch  成交记录
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Fut_QueryMatch_Answer* pMatch);



/**
* 对比压缩成交信息到指定的内存中
* @param pNew		新的委托信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的委托信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
extern int ptl_comparecmpress(const ATP_Msg_Fut_QueryMatch_Answer* pNew,
							  const ATP_Msg_Fut_QueryMatch_Answer* pOld,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Fut_QueryMatch_Answer* pMatch);


//资产
///////////////////////////////////////////////////////////////////////////////////////////////////////


/**
* 压缩资产记录信息到指定的内存中
* @param pAssets 资产记录
* @param pData   指写的内存
* @param nLength 内存长度
*/
extern int ptl_compress(const ATP_Msg_Fut_QueryAssets_Answer* pAssets,
						char* pData,
						int nLength);


/**
* 从指定的内存中解压缩资产信息
* @param pData      指写的内存
* @param nBufferLen 内存长度
* @param pAssets  资产记录
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Fut_QueryAssets_Answer* pAssets);



/**
* 对比压缩算法状态信息到指定的内存中
* @param pNew		新的资产信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的资产信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
extern int ptl_comparecmpress(const ATP_Msg_Fut_QueryAssets_Answer* pNew,
							  const ATP_Msg_Fut_QueryAssets_Answer* pOld,
							  char* pData,
							  int nLength);


extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_Fut_QueryAssets_Answer* pStatus);

//////////////////////////////////////////////////////////////////////////
/**
* 压缩下单信息到指定的内存中
* @param pPosition  持仓信息　
* @param pData      指写的内存
* @param nLength 内存长度
*/
extern int ptl_compress(const ATP_Msg_Fut_MakeOrder* pMakeOrder,
	char* pData,
	int nLength);


/**
* 从指定的内存中解压下单信息
* @param pData      指写的内存
* @param nBufferLen 内存长度
* @param pPosition  持仓信息　
*/
extern int ptl_decmpress(char* pData,
	int nLength,
	ATP_Msg_Fut_MakeOrder* pMakeOrder);



/**
* 对比压缩下单信息到指定的内存中
* @param pNew		新的持仓信息,如果为NULL,则表示要删除旧持仓信息.　
* @param pOld		旧的持仓信息,如果为NULL,表示要新增持仓信息.
* @param pData      指写的内存
* @param nBufferLen 内存长度
*/
extern int ptl_comparecmpress(const ATP_Msg_Fut_MakeOrder* New,
	const ATP_Msg_Fut_MakeOrder* Old,
	char* pData,
	int nLength);

//////////////////////////////////////////////////////////////////////////


extern int ptl_compress(const ATP_Msg_CurrentAlgoStatus* pStatus,
						char* pData,
						int nLength);


extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_CurrentAlgoStatus* pStatus);

extern int ptl_comparedecmpress(char* pData,
								int nLength,
								ATP_Msg_CurrentAlgoStatus* pStatus);


extern int ptl_comparecmpress(const ATP_Msg_CurrentAlgoStatus* pNew,
					   const ATP_Msg_CurrentAlgoStatus* pOld,
					   char* pData,
					   int nLength);

//////////////////////////////////////////////////////////////////////////
//推送日志压缩
extern int ptl_compress(const ATP_Msg_AlgoLog* pLog,
						char* pData,
						int nLength);


extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_AlgoLog* pLog);

//////////////////////////////////////////////////////////////////////////
//日志类别
extern int ptl_compress(const ATP_Msg_Algo_LogCategory* pCate,
						char* pData,
						int nLength);


extern int ptl_decmpress(char* pData,
						 int nLength,
						 ATP_Msg_Algo_LogCategory* pCate);

#endif //_PTLPUSHQUEEN_H_
