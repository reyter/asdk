/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 对比压缩宏
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			 作者         修改说明
2010-11-29	 李伟		 创建
-------------------------------------------------------------
*/

#pragma once
#ifndef _HHNETCOMPARECOMPRESS_H_
#define _HHNETCOMPARECOMPRESS_H_

//引入通用压缩类
#include "HHNetCompressHelper.h"


/**
* 设置某一标志位.
*
*/
#define NCH_CCMP_SET_FLAG(n)\
	{\
		_nch_ccmp_flag_data__[(n-1)/8] |= (1<<(7-(n-1)%8));\
	}



/**
* 取唯一标志
*/
#define NCH_DCCMP_GET_FLAG(n) (__nch_dcmp_flag_data[(n-1)/8] & (1<<(7-(n-1)%8) ))




/**
* 检查其值是否相同,如果不同,则将其压缩.
*/
#define NCH_CCMP_CMP_DO(pData,cNew,cOld,fun)\
	++__nch_ccmp_flag_pos_;\
	if(cNew != cOld)\
	{\
		fun(pData,cNew);\
		NCH_CCMP_SET_FLAG(__nch_ccmp_flag_pos_);\
	}




/**
* 检查其值是否相同,如果不同,则将其压缩.
*/
#define NCH_DCCMP_CMP_DO(pData,cItem,fun)\
	++__nch_dcmp_flag_pos_;\
	if(NCH_DCCMP_GET_FLAG(__nch_dcmp_flag_pos_))\
	{\
		fun(pData,cItem);\
	}



/**
* 开始压缩.
* @param pData 用于存储压缩数据的地址.
* @param nLength  pData的长度.
* @param nVersion       0 NCH_CMP_INT_STEP 原 INT压缩，  ( 1 NCH_CMP_INT_STEP 变成原 INT64压缩.)
* @param nFlag			多少个字节的位.
*/
#define NCH_BEGIN_CCMP_VERSION(pData,nLength,nVersion,nFlag)\
	NCH_BEGIN_CMP_VERSION(pData,nLength,nVersion);\
	NCH_CMP_INT_STEP(pData,nFlag);\
	int __nch_ccmp_flag_pos_ =0;\
	char* _nch_ccmp_flag_data__ = pData;\
	memset(pData,0,nFlag);\
	pData += nFlag;


/** 
* 结束压缩.
* @param pData 用于存储压缩数据的地址.
* @param ncmpLength 压缩后数据的长度.
*/
#define NCH_END_CCMP(pData,ncmpLength)\
	NCH_END_CMP(pData,ncmpLength)



/**
*  对比压缩整形数据.
*  @param 写入内存
*  @param nNew 新整数
*  @param nOld 旧整数
*/
#define NCH_CCMP_DOUBLE2_STEP(pData,nNew,nOld)	NCH_CCMP_CMP_DO(pData,nNew,nOld,NCH_CMP_DOUBLE2_STEP)



/**
*  对比压缩整形数据.
*  @param 写入内存
*  @param nNew 新整数
*  @param nOld 旧整数
*/
#define NCH_CCMP_INT_STEP(pData,nNew,nOld)	NCH_CCMP_CMP_DO(pData,nNew,nOld,NCH_CMP_INT_STEP)


/**
*  对比压缩整形数据.
*  @param 写入内存
*  @param nNew 新整数
*  @param nOld 旧整数
*/
#define NCH_CCMP_INT64_STEP(pData,nNew,nOld)	NCH_CCMP_CMP_DO(pData,nNew,nOld,NCH_CMP_INT64_STEP)




/**
*  对比压缩双精度数据.
*  @param 写入内存
*  @param nNew 新数
*  @param nOld 旧数
*/
#define NCH_CCMP_DOUBLE4_STEP(pData,nNew,nOld)	NCH_CCMP_CMP_DO(pData,nNew,nOld,NCH_CMP_DOUBLE4_STEP)
	


/**
*  对比压缩双精度数据.
*  @param 写入内存
*  @param nNew 新数
*  @param nOld 旧数
*/
#define NCH_CCMP_DOUBLE6_STEP(pData,nNew,nOld)	NCH_CCMP_CMP_DO(pData,nNew,nOld,NCH_CMP_DOUBLE6_STEP)



/**
*  对比压缩字符串.
*  @param 写入内存
*  @param nNew 新数
*  @param nOld 旧数
*/
#define NCH_CCMP_STRING_STEP(pData,strNew,strOld)\
	++__nch_ccmp_flag_pos_;\
	if(strcmp(strNew,strOld))\
	{\
		NCH_CMP_STRING_STEP(pData,strNew);\
		NCH_CCMP_SET_FLAG(__nch_ccmp_flag_pos_);\
	}




//////////////////////////////////////////////////////////////////////////////////
////解压//////////////////////////////////////////////////////////////////////////



/**
* 开始解压.
* @param pData			要将压缩后数据放入的内存.
* @param nLength		nLength 内存的总长度.
* @param nVersion       0 NCH_DCMP_INT_STEP 原 INT解压，  ( 1 NCH_DCMP_INT_STEP 变成原 INT64解压.)
*/
#define NCH_BEGIN_DCCMP_VERSION(pData,nLength,nVersion)\
	NCH_BEGIN_DCMP_VERSION(pData,nLength,nVersion);\
	int __nch_dcmp_flag_len=0;\
	NCH_DCMP_INT_STEP(pData,__nch_dcmp_flag_len);\
	int __nch_dcmp_flag_pos_ =0;\
	char* __nch_dcmp_flag_data = pData;\
	pData += __nch_dcmp_flag_len;




/** 
* 结束解压缩.
* @param pData 用于存储压缩数据的地址.
* @param ncmpLength 压缩后数据的长度.
*/
#define NCH_END_DCCMP(pData,ndcmpLength)\
	NCH_END_DCMP(pData,ndcmpLength)


#define NCH_DCCMP_INT_STEP(pData,item)	NCH_DCCMP_CMP_DO(pData,item,NCH_DCMP_INT_STEP)

#define NCH_DCCMP_INT64_STEP(pData,item)	NCH_DCCMP_CMP_DO(pData,item,NCH_DCMP_INT64_STEP)

#define NCH_DCCMP_DOUBLE2_STEP(pData,item)	NCH_DCCMP_CMP_DO(pData,item,NCH_DCMP_DOUBLE2_STEP)


#define NCH_DCCMP_DOUBLE4_STEP(pData,item)	NCH_DCCMP_CMP_DO(pData,item,NCH_DCMP_DOUBLE4_STEP)


#define NCH_DCCMP_DOUBLE6_STEP(pData,item)	NCH_DCCMP_CMP_DO(pData,item,NCH_DCMP_DOUBLE6_STEP)


#define NCH_DCCMP_STRING_STEP(pData,str,nlen)\
	++__nch_dcmp_flag_pos_;\
	if(NCH_DCCMP_GET_FLAG(__nch_dcmp_flag_pos_))\
	{\
		ZeroMemory(str,nlen);\
		NCH_DCMP_STRING_STEP(pData,str,nlen);\
	}


#endif //_HHNETCOMPARECOMPRESS_H_