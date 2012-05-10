#include "StdAfx.h"
#include "Authentication.h"
#include "Common\Log.h"
#include "Connenct\ProxyOption.h"
#include "Connenct\ShortSocket.h"
#include "Connenct\DataComm.h"
#include "Common\CommonFunc.h"
#include "Connenct\data_struct.h"
#include "Common\StringUtil.h"
#include "CommonData.h"
#include "Connenct\SocketFactory.h"
#include "Connenct\Connenct.h"
#include "OTCHK_Client.h"


CAuthentication::CAuthentication(void)
{
}

CAuthentication::~CAuthentication(void)
{
}

DWORD CAuthentication::Login( const CServer authsvr,const CString& strAccount,const CString& strPwd )
{
	if (authsvr.m_strIPAddress.IsEmpty()||
		strAccount.IsEmpty()||
		strPwd.IsEmpty())
	{
		g_Log.LOG_WARNING(L"auth param error");
		return RETVAL_ERROR;
	}

	g_Log.LOG_INFO(L"begin connect to auth server ip:%s,port:%d",authsvr.m_strIPAddress,authsvr.m_dwPort);

	char *pSend = (char *)malloc(1024);
	char *pRecv = (char *)malloc(1024);	
	if (NULL == pRecv || NULL == pSend)
	{
		__FREE_OBJECT(pSend);
		__FREE_OBJECT(pRecv);
		return RETVAL_ERROR;
	}

	//构造登录请求报文
	tagUserLogReq reqUserLoginData;
	reqUserLoginData.nEncrypt = 0;
	strncpy(reqUserLoginData.acCode,ToCStringA(strAccount).GetBuffer(0),64);
	strncpy(reqUserLoginData.acPass,ToCStringA(strPwd).GetBuffer(0),64);

	int nLen = theApp.m_DataComm.MakeNormalReq(pSend,REQID_LOGIN,(char *)&reqUserLoginData,sizeof(tagUserLogReq));

	//发送报文 
	CConnenct socket;
	socket.SetConnectTo(authsvr);
	int nRet = socket.SendAndRecv(pSend,nLen,pRecv,1024);

	//解析报文
	if (nRet > 0)
	{
		theApp.m_DataComm.DealData(pRecv,nRet);
	}

	__FREE_OBJECT(pRecv);
	__FREE_OBJECT(pSend);


	if (nRet > 0 && theApp.m_DataComm.m_nUserID > 0)
	{
		return RETVAL_SUCCESS;
	}

	return RETVAL_ERROR;
}

DWORD CAuthentication::Logout( void )
{
	return RETVAL_SUCCESS;
}