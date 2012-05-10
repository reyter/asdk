/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨����ƽ̨ ѹ����ѹ����
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			 ����         �޸�˵��
2010-11-29	 ��ΰ		 ����
-------------------------------------------------------------
*/

#pragma once
#ifndef _PTL_COMPRESS_H_
#define _PTL_COMPRESS_H_

#include "..\\OpenTDProtocol.h"
//ѹ������
#include "..\\..\\hhpfdk\HHNetCompressHelper.h"
#include "..\\..\\hhpfdk\HHNetCompareCompressHelper.h"






/**
* ѹ���㷨��Ϣ
*
*/
extern int ptl_compress(const Atp_Algorithm_Info* pAlgoInfo,
						int nItems,
						char* pData,
						int nLength);


/**
*	��ѹ���㷨��Ϣ 
*
*/
extern int ptl_decmpress(char* pData,
						int nLength,
						Atp_Algorithm_Info* pPosition
						,int nItems);



/** 
* ѹ���㷨������Ϣ.
* 
*/
extern int ptl_compressAlgoParam(const BYTE* pParaterInfo,
					  int nParaterLength,
					  int nParamter,
					  char* pData,
					  int nLength);



/** 
* ��ѹ���㷨������Ϣ.
* 
*/
extern int ptl_decompressAlgoParam(char* pData,
							   int nLength,
							   Atp_Algoparam_Info* pParam,
							   int nItems);




#endif	//_PTL_COMPRESS_H_


