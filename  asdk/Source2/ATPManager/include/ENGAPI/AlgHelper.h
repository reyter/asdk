/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨����ƽ̨ �㷨��ؽӿ�
			 
			 �����㷨�ӿ�.
			 �㷨����(ע���㷨����ѯ�㷨��Ϣ������)			 

* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			 ����         �޸�˵��
2010-10-26	 ��ΰ		 ����
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
	* �㷨ִ�к���.
	* �����㷨ѭ��ִ�У�����ѭ������Sleep()���ò���CPU���Ա�������CPUæ��
	* ���㷨���й����У������ ALG_UpdateAlgStatus �����㷨״̬.
	* @param hAlgHandler �㷨�������ͨ���˾����ȡ����־�����׾��.
	* @param  nServiceType �������� 1 ֤ȯ��2 �ڻ� ,������չ
	* @param pValues     ����ֵ��ʼ��ַ.
	* @parma nItem		 ��������
	* @param bStop		 ָʾ�Ƿ�������У�
						 �����������յ�ǿ��ɱ�����㷨ʱ���Ὣ��ָ���ֵ����Ϊtrue.
	* @param  pEndMsg    [out]�������ִ�������Ϣ
	* @param  nLength    ָʾ�������pEndMsg�ĳ���.
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
	* ע���㷨
	* @int nServiceType         �������� 1 ֤ȯ��2 �ڻ� ��������չ
	* @param pAlgoInfo			�㷨��Ϣ
	* @param pParamInfo			�㷨������Ϣ���飬�����С��pAlgoInfo->nParamInfoͬ.
	* @param pExecuteInfo		�㷨ִ����Ϣ.
	* @return 0��ʾע��ɹ�������Ϊ������.
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



