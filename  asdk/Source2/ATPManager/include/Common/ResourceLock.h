/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 资源锁
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-17		李伟		 创建
-------------------------------------------------------------
*/

#pragma once
#ifndef _RESOURCE_LOCK_
#define _RESOURCE_LOCK_

/**
资源锁
*/ 
class CResourceLock
{
public:
	CResourceLock(const CRITICAL_SECTION* cs)		
	{	
		m_pcs = (CRITICAL_SECTION*)(cs);
		EnterCriticalSection(m_pcs);
	};
	virtual ~CResourceLock(void)
	{
		LeaveCriticalSection(m_pcs);
	}
protected:
	CRITICAL_SECTION* m_pcs;
};

#endif //_RESOURCE_LOCK_