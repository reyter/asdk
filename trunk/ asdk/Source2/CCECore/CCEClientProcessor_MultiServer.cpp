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
			   int nLevel,				//�������ȼ�.
			   CCE_PROXYTYPE  iProxyType,		//ʹ�õĴ�������.�޴���ʱΪ�� 
			   const char* szProxyHost,	//�����ַ, �޴���ʱΪ""
			   int  iProxyPort,	//����˿�, �޴���ʱΪ0
			   const char* szProxyUser,	//�����û���, �޴���ʱΪ""
			   const char* szProxyPass,	//��������),�޴���ʱΪ"");	
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

	//���û���Ĺ��ܣ����������������.
	if(m_pCurrentServerInfo)
	{
		SetSvrInfoAndConnect(m_pCurrentServerInfo->m_ip,
			m_pCurrentServerInfo->m_port,
			m_pCurrentServerInfo->m_proxy.iProxyType,
			m_pCurrentServerInfo->m_proxy.szProxyHost,	//�����ַ
			m_pCurrentServerInfo->m_proxy.iProxyPort,		//����˿�
			m_pCurrentServerInfo->m_proxy.szProxyUser,	//�����û���
			m_pCurrentServerInfo->m_proxy.szProxyPass	//��������)
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