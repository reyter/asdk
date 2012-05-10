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
	//����������
	CString m_strGroupName;
	
	//��֤������
	CServer m_AuthSvr;

	//����������б�
	std::vector<CServer> m_vtPriceSvrs;
};

class CServerMgr
{
public:
	CServerMgr(void);
	~CServerMgr(void);

public:

public:
	CServer m_FixedSvr;//�̶�����
	std::vector<CServerGroup> m_vtServerGroups;
};
