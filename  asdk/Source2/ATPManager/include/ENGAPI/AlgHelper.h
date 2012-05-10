/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法交易平台 算法相关接口
			 
			 定义算法接口.
			 算法管理(注册算法、查询算法信息及参数)			 

* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			 作者         修改说明
2010-10-26	 李伟		 创建
-------------------------------------------------------------
*/


#pragma once

#ifndef _ALGHELPER_H_
#define _ALGHELPER_H_


#include "AlgTrdHelper.h"
#include "..\\include\\Protocol\\OpenTDProtocol.h"


#ifdef _ENGAPILIB
#define ALGAPI(type)  type __declspec(dllexport) 
#else
#define ALGAPI(type)  type __declspec(dllimport) 
#endif




#ifdef __cplusplus
extern "C"
{
#endif

	/**
	* 算法执行函数.
	* 若此算法循环执行，请在循环调用Sleep()出让部分CPU，以避免引起CPU忙。
	* 在算法进行过程中，请调用 ALG_UpdateAlgStatus 更新算法状态.
	* @param hAlgHandler 算法句柄，可通过此句柄，取得日志及交易句柄.
	* @param  nServiceType 服务类型 1 证券、2 期货 ,其他扩展
	* @param pValues     参数值起始地址.
	* @parma nItem		 参数个数
	* @param bStop		 指示是否继续运行，
						 当服务器接收到强行杀死该算法时，会将其指向的值设置为true.
	* @param  pEndMsg    [out]用于输出执行完成信息
	* @param  nLength    指示输出缓存pEndMsg的长度.
	*/
	typedef int (CALLBACK* ALG_DOALGO_FUN)(HALG /*hAlgHandler*/,
		int nServiceType,
		const ATP_Msg_MakeOrderByAlgo_ParamValue* /*pValues*/
		,int /*nItem*/
		,bool* /*pbStop*/
		,LPTSTR /*pEndMsg*/
		,int    /*nLength*/);


#pragma pack(push,1)
	struct Alg_Execute_Info
	{	
		ALG_DOALGO_FUN		   pfunDoAlgo;
	};
#pragma pack(pop)

	
	/**
	* 注册算法
	* @int nServiceType         服务类型 1 证券，2 期货 其他，扩展
	* @param pAlgoInfo			算法信息
	* @param pParamInfo			算法参数信息数组，数组大小与pAlgoInfo->nParamInfo同.
	* @param pExecuteInfo		算法执行信息.
	* @return 0表示注册成功，其他为错误码.
	*/
	ALGAPI(int)	ALG_RegisterAlgo(
									int nServiceType,
									const Atp_Algorithm_Info* pAlgoInfo,
									const Atp_Algoparam_Info* pParamInfo,		
									const Alg_Execute_Info*   pExecuteInfo
									);


	

///////////////////////////////////////////////////////////////////////////////////////////////////




#ifdef __cplusplus
}
#endif


#endif	//_ALGHELPER_H_



