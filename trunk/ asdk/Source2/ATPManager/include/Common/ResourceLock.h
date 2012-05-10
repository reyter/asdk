/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 ��Դ��
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-17		��ΰ		 ����
-------------------------------------------------------------
*/

#pragma once
#ifndef _RESOURCE_LOCK_
#define _RESOURCE_LOCK_

/**
��Դ��
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