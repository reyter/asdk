
#ifndef __SYNCH_H__
#define __SYNCH_H__

#ifdef _WIN32
#include <windows.h>
#elif defined _POSIX_C_SOURCE
#include <pthread.h>
#endif

class LockNone
{
public:
	void lock() {};
	void unlock() {};
};

class LockSingle
{
public:
	LockSingle();
	~LockSingle();
	void lock();
	void unlock();

private:
#ifdef _WIN32
	CRITICAL_SECTION m_cs;
#elif defined _POSIX_C_SOURCE
	pthread_mutex_t m_cs;
#endif
};

#endif
