#pragma once

#include "include\\WndBGSManager.h"

// CWndBGS

class CWndATPManagerBGS : public CWndBGSManager
{
	DECLARE_DYNAMIC(CWndATPManagerBGS)

public:
	CWndATPManagerBGS();
	virtual ~CWndATPManagerBGS();
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	int OnRecvData(int nServiceClass, int nServiceID, int nID, void *pData, int nLen, BOOL &bDel);
	afx_msg LRESULT OnMsgActiveMainWindow(WPARAM wParam,LPARAM lParam);
};


