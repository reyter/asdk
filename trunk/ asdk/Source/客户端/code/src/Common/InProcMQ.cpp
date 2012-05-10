#include "StdAfx.h"
#include "InProcMQ.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

CInProcMQ CInProcMQ::m_Instance;

CInProcMQ::CInProcMQ(void)
:m_CallbackFunc(NULL)
{
}

CInProcMQ::~CInProcMQ(void)
{
}

void CInProcMQ::SyncProcess( DWORD dwCmdID,LONG_PTR pData,DWORD dwLen)
{

}

void CInProcMQ::AsyncProcess( DWORD dwCmdID,LONG_PTR pData,DWORD dwLen)
{
	CMSG msg;
	msg.m_dwCmdId = dwCmdID;
	msg.m_dwSeqId = ::GetTickCount();
	msg.m_pData = pData;
	msg.m_dwLen = dwLen;
	msg.m_bNeedDelete = FALSE;

	{
		CSingleLock gruad(&m_csLock);
		m_queMsgs.push_back(msg);	
		m_evt.SetEvent();
	}
	
}

void CInProcMQ::DispatchMsg( void )
{
	while(true)
	{
		CMSG msg;
		{
			WaitForSingleObject(m_evt,INFINITE);
			CSingleLock gruad(&m_csLock);
			msg = m_queMsgs.front();
			m_queMsgs.pop_front();
			m_evt.ResetEvent();
		}

		if (m_CallbackFunc)
		{
			m_CallbackFunc(msg);
		}
	}
}

void CInProcMQ::RegCallbackFunc( MQCallbackFunc func )
{
	m_CallbackFunc = func;
}


CInProcMQ& CInProcMQ::GetInstance( void )
{
	return m_Instance;
}

void CInProcMQ::Run( void )
{
	for (size_t i = 0; i < 5; i++)
	{
		boost::thread thrd( boost::bind(&CInProcMQ::DispatchMsg,&CInProcMQ::GetInstance())) ;
	}	
}


