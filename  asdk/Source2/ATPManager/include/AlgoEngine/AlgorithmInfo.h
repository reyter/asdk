/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨��Ϣ��
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-2		��ΰ		 ����
-------------------------------------------------------------
*/

#pragma once

#include "..\\include\\ATSvr\\OpenTDProtocol.h"

/**
�㷨��Ϣ�࣬����ָʾ�㷨�Ļ�����Ϣ.
���ٵ����������ڲ�ʹ��.
*/
class CAlgorithmInfo
{
public:
	CAlgorithmInfo(){}
	CAlgorithmInfo(ATP_ALGORITHM_INFO* pInfoAlgorithm,ATP_ALGOPARAM_INFO* pInfoParamter,CRuntimeClass* pAlgoClass);
	virtual ~CAlgorithmInfo(void);

public:
	

	/**
	�㷨��Ϣ
	*/
	ATP_ALGORITHM_INFO m_infoAlgorithm;


	/**
	������Ϣ
	*/ 	
	ATP_ALGOPARAM_INFO*  m_pInfoParamter;
	

	/**
	�㷨��
	*/
	CRuntimeClass* m_pAlgoClass;

private:
	
	friend class CAlgoManager;

};
