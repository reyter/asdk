#include "StdAfx.h"
#include ".\overlappedex.h"

COverLappedEx::COverLappedEx(void)
{
}

COverLappedEx::~COverLappedEx(void)
{
}

COverLappedEx::COverLappedEx(IO_TYPE ioType)
{
	ZeroMemory(&m_OLap, sizeof(OVERLAPPED));
	m_IOType = ioType;
	ZeroMemory(&m_AnswerBuff,sizeof m_AnswerBuff);
}