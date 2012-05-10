/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法信息类
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-2		李伟		 创建
-------------------------------------------------------------
*/

#pragma once

#include "..\\include\\ATSvr\\OpenTDProtocol.h"

/**
算法信息类，用于指示算法的基本信息.
不再导出，仅作内部使用.
*/
class CAlgorithmInfo
{
public:
	CAlgorithmInfo(){}
	CAlgorithmInfo(ATP_ALGORITHM_INFO* pInfoAlgorithm,ATP_ALGOPARAM_INFO* pInfoParamter,CRuntimeClass* pAlgoClass);
	virtual ~CAlgorithmInfo(void);

public:
	

	/**
	算法信息
	*/
	ATP_ALGORITHM_INFO m_infoAlgorithm;


	/**
	参数信息
	*/ 	
	ATP_ALGOPARAM_INFO*  m_pInfoParamter;
	

	/**
	算法类
	*/
	CRuntimeClass* m_pAlgoClass;

private:
	
	friend class CAlgoManager;

};
