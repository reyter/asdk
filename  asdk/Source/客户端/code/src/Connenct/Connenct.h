#pragma once
#include "ProxyOption.h"
#include "ShortSocket.h"
#include "DataComm.h"
#include "ServerMg.h"

class CConnenct
{
public:
	CConnenct(void);
	~CConnenct(void);

public:
	void SetConnectTo(const CString& strIpAddress,DWORD dwPort);
	void SetConnectTo(const CServer svr);
	int SendAndRecv(const char* pSendBuff,int nSendLen,char* pRecvBuff,int nRecvLen);

private:
	CString m_strIpAddress;
	DWORD m_dwPort;
	CShortSocket m_ShortSocket;
	
};
