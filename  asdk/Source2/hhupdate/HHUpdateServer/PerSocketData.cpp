#include "StdAfx.h"
#include ".\persocketdata.h"

CPerSocketData::CPerSocketData(void)
{
	m_Socket = INVALID_SOCKET;
	m_AccSocket = INVALID_SOCKET;
}

CPerSocketData::~CPerSocketData(void)
{
}
