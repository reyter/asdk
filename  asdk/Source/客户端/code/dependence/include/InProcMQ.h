#pragma once
#include <boost\noncopyable.hpp>
#include <boost\shared_ptr.hpp>
#include <boost\make_shared.hpp>
#include <boost\thread.hpp>
#include <boost\thread\mutex.hpp>
#include <boost\thread\locks.hpp>
#include <boost\thread\condition.hpp>


struct CMSG
{
	std::wstring	m_strDestination;
	std::wstring	m_strSource;
	unsigned long	m_ulID;	
	unsigned long    m_ThreadID;
	unsigned long*	m_pData;
	unsigned long*	m_pDataLen;
};


class CInProcMQ
{
public:
	CInProcMQ(void);
	~CInProcMQ(void);

public:
	void Put(boost::shared_ptr<CMSG> pMsg);
	boost::shared_ptr<CMSG> Get(void);
	boost::shared_ptr<CMSG> CreateNewMsgObject(void);
	

private:
	boost::ptr_deque<CInProcMQ> m_queMQ;
	boost::mutex m_mtxLock;
	boost::condition_variable m_conVariable;
};
