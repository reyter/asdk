#pragma once
#include "../winunit/IUserWin.h"

// CEmptyWnd

class CEmptyWnd : public CWnd,public IUserWin
{
	DECLARE_DYNAMIC(CEmptyWnd)

public:
	CEmptyWnd();
	virtual ~CEmptyWnd();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CWnd * GetWnd(){return this;};
};


