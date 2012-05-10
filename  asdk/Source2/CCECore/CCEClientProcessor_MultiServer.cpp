#include "stdafx.h"
#include "CCEClientProcessor_MultiServer.h"


IMPLEMENT_DYNCREATE(CCCEClientProcessor_MultiServer,CCCEClientProcessor)

CCCEClientProcessor_MultiServer::CCCEClientProcessor_MultiServer(void)
:m_pCurrentServerInfo(NULL)
{
}

CCCEClientProcessor_MultiServer::~CCCEClientProcessor_MultiServer(void)
{
}


void CCCEClientProcessor_MultiServer::OnConnectResult(bool bRet)
{
	if(bRet)
	{
		NULL;
	}else
	{
		TryConnectNextServer();
	}
}

bool CCCEClientProcessor_MultiServer::AddServer(const CCCETCPServerInfo* pInfo)
{	
	if( m_nCurrentStatus == CCE_CONN_STATUS_OFFLINE )
	{
		m_lsServer.AddServer(pInfo);
		return true;
	}else
	{
		return false;
	}

}

bool CCCEClientProcessor_MultiServer::AddServer(LPCSTR lpServer,
			   int nPort,				
			   int nLevel,				//连接优先级.
			   CCE_PROXYTYPE  iProxyType,		//使用的代理类型.无代理时为零 
			   const char* szProxyHost,	//代理地址, 无代理时为""
			   int  iProxyPort,	//代理端口, 无代理时为0
			   const char* szProxyUser,	//代理用户名, 无代理时为""
			   const char* szProxyPass,	//代理密码),无代理时为"");	
			   const BYTE* pExtraData,
			   int   nExtraDataLength)
{
	CCE_PROXYDATA proxy;
	memset(&proxy,0,sizeof(proxy));

	proxy.iProxyType = iProxyType;
	proxy.iProxyPort = iProxyPort;

	if(szProxyHost)
		strncpy(proxy.szProxyHost,szProxyHost,sizeof(proxy.szProxyHost)-1);

	if(szProxyUser)
		strncpy(proxy.szProxyUser,szProxyUser,sizeof(proxy.szProxyUser)-1);

	if(szProxyPass)
		strncpy(proxy.szProxyPass,szProxyPass,sizeof(proxy.szProxyPass)-1);


	CCCETCPServerInfo info(lpServer,nPort,nLevel,&proxy,pExtraData,nExtraDataLength);

	return AddServer(&info);
}


void CCCEClientProcessor_MultiServer::Begin()
{
	if(m_nCurrentStatus == CCE_CONN_STATUS_OFFLINE)
	{
		TryConnectServer();	//Try Connected Server.
	}
}

const CCCETCPServerInfo* CCCEClientProcessor_MultiServer::GetCurrentConnectionInfo()
{
	return m_pCurrentServerInfo;
}


void CCCEClientProcessor_MultiServer::TryConnectServer()
{
	m_pCurrentServerInfo = m_lsServer.GetFirstServer();
	DoConnect();
}

void CCCEClientProcessor_MultiServer::TryConnectNextServer()
{
	m_pCurrentServerInfo = m_lsServer.GetNextServer(m_pCurrentServerInfo);
	DoConnect();
}
void CCCEClientProcessor_MultiServer::DoConnect()
{

	ASSERT(m_pCurrentServerInfo);

	m_bMannualEnd = false;

	//调用基类的功能，向服务器发起连接.
	if(m_pCurrentServerInfo)
	{
		SetSvrInfoAndConnect(m_pCurrentServerInfo->m_ip,
			m_pCurrentServerInfo->m_port,
			m_pCurrentServerInfo->m_proxy.iProxyType,
			m_pCurrentServerInfo->m_proxy.szProxyHost,	//代理地址
			m_pCurrentServerInfo->m_proxy.iProxyPort,		//代理端口
			m_pCurrentServerInfo->m_proxy.szProxyUser,	//代理用户名
			m_pCurrentServerInfo->m_proxy.szProxyPass	//代理密码)
			);
	}
}

bool CCCEClientProcessor_MultiServer::OnClose()
{
	if(m_bMannualEnd)
	{
		m_pCurrentServerInfo = NULL;
		return true;
	}else
	{
		TryConnectServer();
		return false;
	}
}

void CCCEClientProcessor_MultiServer::End()
{
	Disconnect();
}