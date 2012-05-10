#include "StdAfx.h"
#include "InProcMQ.h"

CInProcMQ::CInProcMQ(void)
{
}

CInProcMQ::~CInProcMQ(void)
{
}

void CInProcMQ::Put( boost::shared_ptr<CMSG> pMsg )
{
	boost::mutex::scoped_lock guard(m_mtxLock);
	m_queMQ.push_back(pMsg);
	m_conVariable.notify_all();
}

boost::shared_ptr<CMSG> CInProcMQ::Get( void )
{
	boost::mutex::scoped_lock guard(m_mtxLock);
	boost::shared_ptr<CMSG> pTemp = m_queMQ.front();
	m_queMQ.pop_front();
	return pTemp;
}

boost::shared_ptr<CMSG> CInProcMQ::CreateNewMsgObject( void )
{
	return boost::make_shared(CMSG)();
}

