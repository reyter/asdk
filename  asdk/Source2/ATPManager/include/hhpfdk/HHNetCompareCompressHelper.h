/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �Ա�ѹ����
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			 ����         �޸�˵��
2010-11-29	 ��ΰ		 ����
-------------------------------------------------------------
*/

#pragma once
#ifndef _HHNETCOMPARECOMPRESS_H_
#define _HHNETCOMPARECOMPRESS_H_

//����ͨ��ѹ����
#include "HHNetCompressHelper.h"


/**
* ����ĳһ��־λ.
*
*/
#define NCH_CCMP_SET_FLAG(n)\
	{\
		_nch_ccmp_flag_data__[(n-1)/8] |= (1<<(7-(n-1)%8));\
	}



/**
* ȡΨһ��־
*/
#define NCH_DCCMP_GET_FLAG(n) (__nch_dcmp_flag_data[(n-1)/8] & (1<<(7-(n-1)%8) ))




/**
* �����ֵ�Ƿ���ͬ,�����ͬ,����ѹ��.
*/
#define NCH_CCMP_CMP_DO(pData,cNew,cOld,fun)\
	++__nch_ccmp_flag_pos_;\
	if(cNew != cOld)\
	{\
		fun(pData,cNew);\
		NCH_CCMP_SET_FLAG(__nch_ccmp_flag_pos_);\
	}




/**
* �����ֵ�Ƿ���ͬ,�����ͬ,����ѹ��.
*/
#define NCH_DCCMP_CMP_DO(pData,cItem,fun)\
	++__nch_dcmp_flag_pos_;\
	if(NCH_DCCMP_GET_FLAG(__nch_dcmp_flag_pos_))\
	{\
		fun(pData,cItem);\
	}



/**
* ��ʼѹ��.
* @param pData ���ڴ洢ѹ�����ݵĵ�ַ.
* @param nLength  pData�ĳ���.
* @param nVersion       0 NCH_CMP_INT_STEP ԭ INTѹ����  ( 1 NCH_CMP_INT_STEP ���ԭ INT64ѹ��.)
* @param nFlag			���ٸ��ֽڵ�λ.
*/
#define NCH_BEGIN_CCMP_VERSION(pData,nLength,nVersion,nFlag)\
	NCH_BEGIN_CMP_VERSION(pData,nLength,nVersion);\
	NCH_CMP_INT_STEP(pData,nFlag);\
	int __nch_ccmp_flag_pos_ =0;\
	char* _nch_ccmp_flag_data__ = pData;\
	memset(pData,0,nFlag);\
	pData += nFlag;


/** 
* ����ѹ��.
* @param pData ���ڴ洢ѹ�����ݵĵ�ַ.
* @param ncmpLength ѹ�������ݵĳ���.
*/
#define NCH_END_CCMP(pData,ncmpLength)\
	NCH_END_CMP(pData,ncmpLength)



/**
*  �Ա�ѹ����������.
*  @param д���ڴ�
*  @param nNew ������
*  @param nOld ������
*/
#define NCH_CCMP_DOUBLE2_STEP(pData,nNew,nOld)	NCH_CCMP_CMP_DO(pData,nNew,nOld,NCH_CMP_DOUBLE2_STEP)



/**
*  �Ա�ѹ����������.
*  @param д���ڴ�
*  @param nNew ������
*  @param nOld ������
*/
#define NCH_CCMP_INT_STEP(pData,nNew,nOld)	NCH_CCMP_CMP_DO(pData,nNew,nOld,NCH_CMP_INT_STEP)


/**
*  �Ա�ѹ����������.
*  @param д���ڴ�
*  @param nNew ������
*  @param nOld ������
*/
#define NCH_CCMP_INT64_STEP(pData,nNew,nOld)	NCH_CCMP_CMP_DO(pData,nNew,nOld,NCH_CMP_INT64_STEP)




/**
*  �Ա�ѹ��˫��������.
*  @param д���ڴ�
*  @param nNew ����
*  @param nOld ����
*/
#define NCH_CCMP_DOUBLE4_STEP(pData,nNew,nOld)	NCH_CCMP_CMP_DO(pData,nNew,nOld,NCH_CMP_DOUBLE4_STEP)
	


/**
*  �Ա�ѹ��˫��������.
*  @param д���ڴ�
*  @param nNew ����
*  @param nOld ����
*/
#define NCH_CCMP_DOUBLE6_STEP(pData,nNew,nOld)	NCH_CCMP_CMP_DO(pData,nNew,nOld,NCH_CMP_DOUBLE6_STEP)



/**
*  �Ա�ѹ���ַ���.
*  @param д���ڴ�
*  @param nNew ����
*  @param nOld ����
*/
#define NCH_CCMP_STRING_STEP(pData,strNew,strOld)\
	++__nch_ccmp_flag_pos_;\
	if(strcmp(strNew,strOld))\
	{\
		NCH_CMP_STRING_STEP(pData,strNew);\
		NCH_CCMP_SET_FLAG(__nch_ccmp_flag_pos_);\
	}




//////////////////////////////////////////////////////////////////////////////////
////��ѹ//////////////////////////////////////////////////////////////////////////



/**
* ��ʼ��ѹ.
* @param pData			Ҫ��ѹ�������ݷ�����ڴ�.
* @param nLength		nLength �ڴ���ܳ���.
* @param nVersion       0 NCH_DCMP_INT_STEP ԭ INT��ѹ��  ( 1 NCH_DCMP_INT_STEP ���ԭ INT64��ѹ.)
*/
#define NCH_BEGIN_DCCMP_VERSION(pData,nLength,nVersion)\
	NCH_BEGIN_DCMP_VERSION(pData,nLength,nVersion);\
	int __nch_dcmp_flag_len=0;\
	NCH_DCMP_INT_STEP(pData,__nch_dcmp_flag_len);\
	int __nch_dcmp_flag_pos_ =0;\
	char* __nch_dcmp_flag_data = pData;\
	pData += __nch_dcmp_flag_len;




/** 
* ������ѹ��.
* @param pData ���ڴ洢ѹ�����ݵĵ�ַ.
* @param ncmpLength ѹ�������ݵĳ���.
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