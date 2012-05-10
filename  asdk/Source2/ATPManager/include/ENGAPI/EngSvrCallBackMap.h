#pragma once

#include "EngSvrHelper.h"

#ifndef _MAP_
#include <map>
using namespace std;
#endif

class CEngSvrCallBackMap
	:public map<int,ENG_SVR_CALLBACK*>
{
public:
	CEngSvrCallBackMap(void);
	virtual ~CEngSvrCallBackMap(void);

	static int Register(int nService,
		ENG_SVR_CALLBACK* pCallBakc);

	static ENG_SVR_CALLBACK* GetCallBack(int nSerivceType);
};

extern CEngSvrCallBackMap g_mapEngSvrCallBack;