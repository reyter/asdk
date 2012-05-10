#pragma once

class CResourceLock
{
public:
	CResourceLock(CRITICAL_SECTION* cs)
	{
		pcs = cs;
		EnterCriticalSection(pcs);
	};
	virtual ~CResourceLock(void)
	{
		LeaveCriticalSection(pcs);
	}
protected:
	CRITICAL_SECTION* pcs;
};
