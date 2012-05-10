#pragma once

#include <list>
using namespace std;

template <
	class Type, 
	class Allocator=allocator<Type> 
>
class CLockList :
	public list<Type,Allocator>
{
public:
	CLockList<Type, 
		Allocator>(void):list<Type,Allocator>
	{
		InitializeCriticalSection(&m_cs);		
	}

	virtual ~CLockList(void)
	{
		DeleteCriticalSection(&m_cs);		
	}
	
	void EnterLock()
	{
		EnterCriticalSection(&m_cs);
	}
	void LeaveLock()
	{
		LeaveCriticalSection(&m_cs);
	}
protected:
	CRITICAL_SECTION m_cs;
};
