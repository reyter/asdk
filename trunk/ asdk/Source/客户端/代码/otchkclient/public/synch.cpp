#include "stdafx.h"
#include "synch.h"

LockSingle::LockSingle()
{
#ifdef _WIN32
	::InitializeCriticalSection(&m_cs);
#elif defined _POSIX_C_SOURCE
	pthread_mutex_init(&m_cs, NULL);
#endif
}

LockSingle::~LockSingle()
{
#ifdef _WIN32
	::DeleteCriticalSection(&m_cs);
#elif defined _POSIX_C_SOURCE
	pthread_mutex_destroy(&m_cs);
#endif
}

void LockSingle::lock()
{
#ifdef _WIN32
	::EnterCriticalSection(&m_cs);
#elif defined _POSIX_C_SOURCE
	pthread_mutex_lock(&m_cs);
#endif
}

void LockSingle::unlock()
{
#ifdef _WIN32
	::LeaveCriticalSection(&m_cs);
#elif defined _POSIX_C_SOURCE
	pthread_mutex_unlock(&m_cs);
#endif
}
