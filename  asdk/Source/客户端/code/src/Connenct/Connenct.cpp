#include "StdAfx.h"
#include "Connenct.h"
#include "..\Common\StringUtil.h"
#include "..\Common\CommonFunc.h"

CConnenct::CConnenct(void)
{
}

CConnenct::~CConnenct(void)
{
}

void CConnenct::SetConnectTo( const CString& strIpAddress,DWORD dwPort )
{
	m_strIpAddress = strIpAddress;
	m_dwPort = dwPort;
}

void CConnenct::SetConnectTo( const CServer svr )
{
	m_strIpAddress = svr.m_strIPAddress;
	m_dwPort = svr.m_dwPort;
}

int CConnenct::SendAndRecv( const char* pSendBuff,int nSendLen,char* pRecvBuff,int nRecvLen)
{
	CProxyOption m_ProxyOption;
	m_ProxyOption.Init(GetProxyFile());
	return m_ShortSocket.SendAndRecv(m_strIpAddress,m_dwPort,(char*)pSendBuff,nSendLen,pRecvBuff,nRecvLen,NULL,&m_ProxyOption);
}

