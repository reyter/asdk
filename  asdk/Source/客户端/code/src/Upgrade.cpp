#include "StdAfx.h"
#include "Upgrade.h"
#include "AppSetting.h"
#include "Connenct\ShortSocket.h"
#include "Connenct\ProxyOption.h"
#include "Connenct\ServerMg.h"
#include "Connenct\DataComm.h"
#include "Common\CommonFunc.h"
#include "Common\Log.h"

CUpgrade::CUpgrade(void)
{
	
}

CUpgrade::~CUpgrade(void)
{
}

DWORD CUpgrade::DoUpgrade( void )
{
	return 0;

}

DWORD CUpgrade::UpgradeServerGroupData( void )
{
	CProxyOption ProxyOption;
	CShortSocket Socket;
	CDataComm DataComm;
	CServer m_fixedSvr;  

	 CAppSetting::GetInstance().GetFixedServer(m_fixedSvr);
	
	ProxyOption.Init(GetProxyFile());

	char acReq[1024];
	int nLen = DataComm.MakeOnlineInitReq(acReq,0x0018);
	char* pRecv = (char *)malloc(1024 * 1024);
	memset(pRecv,1024*1024,0);

	CStringA strIp(m_fixedSvr.m_strIPAddress);
	DWORD nRet = Socket.SendAndRecv(strIp.GetBuffer(0),m_fixedSvr.m_dwPort,acReq,nLen,pRecv,1024 * 1024,NULL,&ProxyOption);

	if (nRet > 0)
	{
		DataComm.DealData(pRecv,nRet);
	}
	else
	{
		g_Log.LOG_WARNING(L"upgrade server group data failed");
		return RETVAL_ERROR;
	}
}

CString CUpgrade::GetCurrentClientVersion( void )
{
	return NULL;
}

DWORD CUpgrade::CheckClientVersion( CString& strNewVersion,const CString& strCurVersion )
{
	return 0;
}

DWORD CUpgrade::DownLoadUpgradeFile( const CString& strUpgradfFile )
{
	return 0;
}

void CUpgrade::ForceQuit( void )
{

}
