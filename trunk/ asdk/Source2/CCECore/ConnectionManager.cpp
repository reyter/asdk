#include "StdAfx.h"
#include ".\connectionmanager.h"

CPtrList  CConnectionManager::g_listConnection;
CRITICAL_SECTION  CConnectionManager::g_cslistConnection;


void CConnectionManager::AddConnection(CHHWPConnection* pConnection)
{
	EnterCriticalSection(&g_cslistConnection);
	g_listConnection.AddTail(pConnection);
	LeaveCriticalSection(&g_cslistConnection);
}
void CConnectionManager::DeleteConnection(CHHWPConnection* pConnection)
{
	EnterCriticalSection(&g_cslistConnection);
	POSITION pos = g_listConnection.Find(pConnection);
	if(pos)
	{
		g_listConnection.RemoveAt(pos);
		delete pConnection;
	}
	LeaveCriticalSection(&g_cslistConnection);
}
void CConnectionManager::Init()
{
	InitializeCriticalSection(&g_cslistConnection);
}


CConnectionManager::CConnectionManager(void)
{
}

CConnectionManager::~CConnectionManager(void)
{
}
