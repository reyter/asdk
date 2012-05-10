#include "StdAfx.h"
#include "SocketFactory.h"
#include "..\Common\GlobalMacro.h"
#include "CommSocket.h"
#include "..\Common\CommonFunc.h"
#include "..\AppSetting.h"
#include "..\OTCHK_Client.h"
#include "..\CommonData.h"




CServerFactory CServerFactory::m_instance;

CServerFactory::CServerFactory(void)
{
}

CServerFactory::~CServerFactory(void)
{

}


BOOL CServerFactory::Init( void )
{
	//初始化socket运行环境
	WSADATA wsaData;
	int  nResult = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
	if ( nResult != 0 ) 
	{
		return RETVAL_ERROR;
	}

	CAppSetting asConfig;
	asConfig.GetFixedServer(m_FixedSvr);
	asConfig.GetServerGroup(m_vtServerGroups);

	m_strProxyFlie = GetProxyFile();
	if (CheckFileExist(m_strProxyFlie.GetBuffer(0)))
	{
		g_Log.LOG_WARNING(L"%s is not exist",m_strProxyFlie);
	}

	return  RETVAL_SUCCESS;
}

CShortSocket* CServerFactory::CreateFixedConnect(void)
{
	m_ProxyOption.Init(m_strProxyFlie);



	return NULL;
}



BOOL CServerFactory::CreateAuthConnect( CShortSocket* pSocket )
{
	return RETVAL_SUCCESS;
}

BOOL CServerFactory::CreateMarketConnect( CShortSocket* pSocket )
{
	return RETVAL_SUCCESS;
}

void CServerFactory::Disconnect( CShortSocket* pSocket )
{
	if (NULL != pSocket)
	{
		pSocket->Disconnect();
	}

	__DELETE_OBJECT(pSocket);
}

CServerFactory& CServerFactory::GetInstance( void )
{
	return m_instance;
}

std::vector<CServerGroup>& CServerFactory::GetServerGroup( void )
{
	return m_vtServerGroups;
}

CProxyOption& CServerFactory::GetProxyOptionObject( void )
{
	m_ProxyOption.Init(m_strProxyFlie);
	return m_ProxyOption;
}

