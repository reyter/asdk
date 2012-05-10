#pragma once
#include <vector>

struct CServer
{
	CString m_strServerName;
	CString m_strIPAddress;
	DWORD m_dwPort;
};

struct CServerGroup
{
	//服务器组名
	CString m_strGroupName;
	
	//认证服务器
	CServer m_AuthSvr;

	//行情服务器列表
	std::vector<CServer> m_vtPriceSvrs;
};

class CServerMgr
{
public:
	CServerMgr(void);
	~CServerMgr(void);

public:

public:
	CServer m_FixedSvr;//固定主机
	std::vector<CServerGroup> m_vtServerGroups;
};
