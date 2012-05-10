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

/**
��Դ��
*/ 
class AFX_EXT_CLASS CResourceLock
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
