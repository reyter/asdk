//DataQueue.h
#ifndef _DATAQUEUE_H_
#define _DATAQUEUE_H_
#include <deque>
#include "FinanPlugdef.h"
////////////////////////////////////////////////////////////////
class CDataQueue
{
public:
	CDataQueue();
	virtual ~CDataQueue();

	BOOL Init();
	void Release();

	void PushBack(tagReturnMsgID* pData);
	tagReturnMsgID* PopFront();

protected:

private:
	HANDLE             m_hEmptyEvent;    //�ж϶����Ƿ�Ϊ��
	CRITICAL_SECTION   m_csQueue;		 //������

	std::deque<tagReturnMsgID*> m_deque;
	BOOL   m_bRun;  //���б�־
};

////////////////////////////////////////////////////////////////
#endif