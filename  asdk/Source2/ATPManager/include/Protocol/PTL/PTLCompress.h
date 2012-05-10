/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法交易平台 压缩解压函数
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			 作者         修改说明
2010-11-29	 李伟		 创建
-------------------------------------------------------------
*/

#pragma once
#ifndef _PTL_COMPRESS_H_
#define _PTL_COMPRESS_H_

#include "..\\OpenTDProtocol.h"
//压缩功能
#include "..\\..\\hhpfdk\HHNetCompressHelper.h"
#include "..\\..\\hhpfdk\HHNetCompareCompressHelper.h"






/**
* 压缩算法信息
*
*/
extern int ptl_compress(const Atp_Algorithm_Info* pAlgoInfo,
						int nItems,
						char* pData,
						int nLength);


/**
*	解压缩算法信息 
*
*/
extern int ptl_decmpress(char* pData,
						int nLength,
						Atp_Algorithm_Info* pPosition
						,int nItems);



/** 
* 压缩算法参数信息.
* 
*/
extern int ptl_compressAlgoParam(const BYTE* pParaterInfo,
					  int nParaterLength,
					  int nParamter,
					  char* pData,
					  int nLength);



/** 
* 解压缩算法参数信息.
* 
*/
extern int ptl_decompressAlgoParam(char* pData,
							   int nLength,
							   Atp_Algoparam_Info* pParam,
							   int nItems);




#endif	//_PTL_COMPRESS_H_


