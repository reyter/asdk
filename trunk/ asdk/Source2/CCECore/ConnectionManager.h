#pragma once


#include "HHWPConnection.h"
class CConnectionManager
{
public:
	CConnectionManager(void);
	virtual ~CConnectionManager(void);

	static void AddConnection(CHHWPConnection* pConnection);
	static void DeleteConnection(CHHWPConnection* pConnection);
	static void Init();

protected:
	static CPtrList   g_listConnection;
	static CRITICAL_SECTION  g_cslistConnection;
};
