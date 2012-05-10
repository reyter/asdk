// ATPFileDBApi.cpp : 实现文件
//

#include "stdafx.h"
#include "ATPFileDB.h"
#include "ATPFileDBApi.h"


// CATPFileDBApi

CATPFileDBApi::CATPFileDBApi()
{
	m_pATPDataBase = new CATPDataBase();
	if (NULL == m_pATPDataBase)
	{
		return;
	}
	m_pATPOperateLogBase = new CATPLogBase(OPERATELOG);
	if (NULL == m_pATPOperateLogBase)
	{
		delete m_pATPDataBase;
		return;
	}
	m_pATPAlgoLogBase = new CATPLogBase(ALGOLOG);
	if (NULL == m_pATPAlgoLogBase)
	{
		delete m_pATPDataBase;
		delete m_pATPOperateLogBase;
		return;
	}
}

CATPFileDBApi::~CATPFileDBApi()
{
	if (m_pATPDataBase)
	{
		delete m_pATPDataBase;
	}
	if (m_pATPOperateLogBase)
	{
		delete m_pATPOperateLogBase;
	}
	if (m_pATPAlgoLogBase)
	{
		delete m_pATPAlgoLogBase;
	}
}


// CATPFileDBApi 成员函数

int CATPFileDBApi::IsHavePermission(int nAccountType,const char *pAccountID,int nPermissionType)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->IsHavePermission(nAccountType,pAccountID,nPermissionType);
	}
	else
	{
		return NULLHANDLE;
	}
}


int CATPFileDBApi::AddManager(IN struATPDataBaseManager *pATPDBSManager,OUT struATPDataBaseManager *pOutATPDBSManager)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->AddManager(pATPDBSManager,pOutATPDBSManager);
	} 
	else
	{
		return NULLHANDLE;
	}
}
int CATPFileDBApi::ModifyManager(struATPDataBaseManager *pATPDBSManager)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->ModifyManager(pATPDBSManager);
	} 
	else
	{
		return NULLHANDLE;
	}
}
int CATPFileDBApi::DelManager(struATPDataBaseManager *pATPDBSManager)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->DelManager(pATPDBSManager);
	} 
	else
	{
		return NULLHANDLE;
	}
}
int CATPFileDBApi::QueryManager(IN char *pAccount,OUT struATPDataBaseManager **ppATPDBSManager)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->QueryManager(pAccount,ppATPDBSManager);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::AddServerGroup(struATPDataBaseServerGroup *pATPDBSServerGroup,OUT struATPDataBaseServerGroup *pOutData)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->AddServerGroup(pATPDBSServerGroup,pOutData);
	} 
	else
	{
		return NULLHANDLE;
	}
}
int CATPFileDBApi::ModifyServerGroup(struATPDataBaseServerGroup *pATPDBSServerGroup)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->ModifyServerGroup(pATPDBSServerGroup);
	} 
	else
	{
		return NULLHANDLE;
	}
}
int CATPFileDBApi::DelServerGroup(struATPDataBaseServerGroup *pATPDBSServerGroup)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->DelServerGroup(pATPDBSServerGroup);
	} 
	else
	{
		return NULLHANDLE;
	}
}
int CATPFileDBApi::QueryServerGroup(OUT struATPDataBaseServerGroup **ppATPDBSServerGroup)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->QueryServerGroup(ppATPDBSServerGroup);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::AddServer(struATPDataBaseServer *pATPDBSServer,OUT struATPDataBaseServer *pOutData)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->AddServer(pATPDBSServer,pOutData);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::ModifyServer(struATPDataBaseServer *pATPDBSServer)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->ModifyServer(pATPDBSServer);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::DelServer(struATPDataBaseServer *pATPDBSServer)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->DelServer(pATPDBSServer);
	} 
	else
	{
		return NULLHANDLE;
	}
}


int CATPFileDBApi::QueryServer(struATPDataBaseServer_QUERY *pATPDBSServer_QUERY,OUT struATPDataBaseServer **ppATPDBSServer)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->QueryServer(pATPDBSServer_QUERY,ppATPDBSServer);
	} 
	else
	{
		return NULLHANDLE;
	}
}

//int AddPermission(struATPDataBasePermission *);
//int ModifyPermission(struATPDataBasePermission *);
//int DelPermission(struATPDataBasePermission *);
int CATPFileDBApi::QueryPermission(struATPDataBasePermission **ppATPDBSPermission)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->QueryPermission(ppATPDBSPermission);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::AddUserGroup(struATPDataBaseUserGroup *pATPDBSUserGroup,OUT struATPDataBaseUserGroup *pOutData)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->AddUserGroup(pATPDBSUserGroup,pOutData);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::ModifyUserGroup(struATPDataBaseUserGroup *pATPDBSUserGroup)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->ModifyUserGroup(pATPDBSUserGroup);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::DelUserGroup(struATPDataBaseUserGroup *pATPDBSUserGroup)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->DelUserGroup(pATPDBSUserGroup);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::QueryUserGroup(IN char *pAccount,struATPDataBaseUserGroup **ppATPDBSUserGroup)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->QueryUserGroup(pAccount,ppATPDBSUserGroup);
		/*
		char pData[1024]={0};
		AtpAccept_Manager_MsgHead Head = {0};
		int nHeadSize = sizeof AtpAccept_Manager_MsgHead;

		AtpAccept_Manager_ValidateUser user = {0};
		strcpy(user.szUserName,"123");
		strcpy(user.szUserPwd,"123");

		memcpy(pData,(char *)&Head,sizeof AtpAccept_Manager_MsgHead);
		memcpy(&pData[nHeadSize],(char *)&user,sizeof AtpAccept_Manager_ValidateUser);
		char *pSendData=NULL;
		int nLen = 0;
		UserLogin(( char *)pData,&pSendData,&nLen);

		if (pSendData)
		{
			delete []pSendData;
			pSendData = NULL;
		}
		ZeroMemory(pData,1024);

		//////////////////////////////////////////////////////////////////////////
		AtpAccept_Manager_User _user={0};
		_user.nUserId = 1;
		strcpy(_user.szUserName,"123");

		memcpy(pData,(char *)&Head,sizeof AtpAccept_Manager_MsgHead);
		memcpy(&pData[nHeadSize],(char *)&_user,sizeof AtpAccept_Manager_User);
// 
// 		nLen = 0;
// 		GetFundAccount(( char *)pData,&pSendData,&nLen);
// 
// 		if (pSendData)
// 		{
// 			delete []pSendData;
// 			pSendData = NULL;
// 		}
		nLen = 0;
		GetAlgoInfo(( char *)pData,&pSendData,&nLen);

		if (pSendData)
		{
			delete []pSendData;
			pSendData = NULL;
		}
//		nLen = 0;
// 		GetServerInfo(( char *)pData,&pSendData,&nLen);
// 
// 		if (pSendData)
// 		{
// 			delete []pSendData;
// 			pSendData = NULL;
// 		}
// 
// 		AtpAccept_Manager_GetUserInfo_WithFundAccout  _WithFundAccout = {0};
// 		strcpy(_WithFundAccout.fundAccount.chOrgID,"0001");
// 		strcpy(_WithFundAccout.fundAccount.chUserID,"000100000012");
// 
// 		memcpy(pData,(char *)&Head,sizeof AtpAccept_Manager_MsgHead);
// 		memcpy(&pData[nHeadSize],(char *)&_WithFundAccout,sizeof AtpAccept_Manager_GetUserInfo_WithFundAccout);
// 		nLen = 0;
// 		GetAccountByFund(( char *)pData,&pSendData,&nLen);
// 
// 		if (pSendData)
// 		{
// 			delete []pSendData;
// 			pSendData = NULL;
// 		}
*/
	} 
	else
	{
		return NULLHANDLE;
	}
}


int CATPFileDBApi::AddUser(struATPDataBaseUser *pATPDBSUser,OUT struATPDataBaseUser *pOutData)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->AddUser(pATPDBSUser,pOutData);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::ModifyUser(struATPDataBaseUser *pATPDBSUser)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->ModifyUser(pATPDBSUser);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::DelUser(struATPDataBaseUser *pATPDBSUser)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->DelUser(pATPDBSUser);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::QueryUser(struATPDataBaseUser_QUERY *pATPDBSUser_QUERY,IN char *pAccount,OUT struATPDataBaseUser **ppATPDBSUser)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->QueryUser(pATPDBSUser_QUERY,pAccount,ppATPDBSUser);
	} 
	else
	{
		return NULLHANDLE;
	}
}


int CATPFileDBApi::AddAlgorithmGroup(struATPDataBaseAlgorithmGroup *pATPDBSAlgorithmGroup,OUT struATPDataBaseAlgorithmGroup *pOutData)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->AddAlgorithmGroup(pATPDBSAlgorithmGroup,pOutData);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::ModifyAlgorithmGroup(struATPDataBaseAlgorithmGroup *pATPDBSAlgorithmGroup)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->ModifyAlgorithmGroup(pATPDBSAlgorithmGroup);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::DelAlgorithmGroup(struATPDataBaseAlgorithmGroup *pATPDBSAlgorithmGroup)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->DelAlgorithmGroup(pATPDBSAlgorithmGroup);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::QueryAlgorithmGroup(IN char *pAccount,struATPDataBaseAlgorithmGroup **ppATPDBSAlgorithmGroup)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->QueryAlgorithmGroup(pAccount,ppATPDBSAlgorithmGroup);
	} 
	else
	{
		return NULLHANDLE;
	}
}


int CATPFileDBApi::AddAlgorithm(struATPDataBaseAlgorithm *pATPDBSAlgorithm,OUT struATPDataBaseAlgorithm *pOutData,BOOL bScript)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->AddAlgorithm(pATPDBSAlgorithm,pOutData,bScript);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::ModifyAlgorithm(struATPDataBaseAlgorithm *pATPDBSAlgorithm)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->ModifyAlgorithm(pATPDBSAlgorithm);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::DelAlgorithm(struATPDataBaseAlgorithm *pATPDBSAlgorithm)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->DelAlgorithm(pATPDBSAlgorithm);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::QueryAlgorithm(struATPDataBaseAlgorithm_QUERY *pATPDBSAlgorithm_QUERY,IN char *pAccount,OUT struATPDataBaseAlgorithm **ppATPDBSAlgorithm)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->QueryAlgorithm(pATPDBSAlgorithm_QUERY,pAccount,ppATPDBSAlgorithm);
	} 
	else
	{
		return NULLHANDLE;
	}
}


int	CATPFileDBApi::AddOperateLog(struATPDataBaseOperateLog *pATPDBSOperateLog)
{
	if (m_pATPOperateLogBase)
	{
		return m_pATPOperateLogBase->AddOperateLog(pATPDBSOperateLog);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int	CATPFileDBApi::QueryOperateLog(struATPDataBaseOperateLog_QUERY *pATPDBSOperateLog_QUERY,OUT struATPDataBaseOperateLog **ppATPDBSOperateLog)
{
	int nRet = 0;
	CATPLogBase *pATPOperateLogBase = new CATPLogBase(OPERATELOG,pATPDBSOperateLog_QUERY->nBeginDate);
	if (pATPOperateLogBase)
	{
		nRet = pATPOperateLogBase->QueryOperateLog(pATPDBSOperateLog_QUERY,ppATPDBSOperateLog);


	} 
	else
	{
		nRet = NULLHANDLE;
	}

	if (pATPOperateLogBase)
	{
		delete pATPOperateLogBase;
		pATPOperateLogBase = NULL;
	}
	return nRet;
}


int	CATPFileDBApi::AddAlgorithmLog(struATPDataBaseAlgorithmLog *pATPDBSAlgorithmLog)
{
	if (m_pATPAlgoLogBase)
	{
		return m_pATPAlgoLogBase->AddAlgorithmLog(pATPDBSAlgorithmLog);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int	CATPFileDBApi::QueryAlgorithmLog(struATPDataBaseAlgorithmLog_QUERY *pATPDBSAlgorithmLog_QUERY,OUT struATPDataBaseAlgorithmLog **ppATPDBSAlgorithmLog)
{
	int nRet = 0;
	CATPLogBase *pATPAlgoLogBase = new CATPLogBase(ALGOLOG,pATPDBSAlgorithmLog_QUERY->nRunBeginDate);
	if (pATPAlgoLogBase)
	{
		nRet = pATPAlgoLogBase->QueryAlgorithmLog(pATPDBSAlgorithmLog_QUERY,ppATPDBSAlgorithmLog);
	}
	else
	{
		nRet = NULLHANDLE;
	}
	if (pATPAlgoLogBase)
	{
		delete pATPAlgoLogBase;
		pATPAlgoLogBase = NULL;
	}
	return nRet;
}



//验证用户 
int CATPFileDBApi::UserLogin(IN const char *pReqData,OUT char **ppAnsData,int *pnLen)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->UserLogin(pReqData,ppAnsData,pnLen);
	} 
	else
	{
		return NULLHANDLE;
	}
}
//获取资金账号的信息 
int CATPFileDBApi::GetFundAccount(IN const char *pReqData,OUT char **ppAnsData,int *pnLen)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->GetFundAccount(pReqData,ppAnsData,pnLen);
	} 
	else
	{
		return NULLHANDLE;
	}
}
//获取用户可以使用的算法及算法使用信息 及算法授权服务器组 
int CATPFileDBApi::GetAlgoInfo(IN const char *pReqData,OUT char **ppAnsData,int *pnLen)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->GetAlgoInfo(pReqData,ppAnsData,pnLen);
	} 
	else
	{
		return NULLHANDLE;
	}
}

int CATPFileDBApi::GetServerInfo(IN const char *pReqData,OUT char **ppAnsData,int *pnLen)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->GetServerInfo(pReqData,ppAnsData,pnLen);
	} 
	else
	{
		return NULLHANDLE;
	}
	return 0;
}

int CATPFileDBApi::GetAccountByFund(IN const char *pReqData,OUT char **ppAnsData,int *pnLen,BOOL bFlag)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->GetAccountByFund(pReqData,ppAnsData,pnLen);
	} 
	else
	{
		return NULLHANDLE;
	}
	return 0;
}


int CATPFileDBApi::GetFundMarket(IN const char *pReqData,OUT char **ppAnsData,int *pnLen)
{
	if (m_pATPDataBase)
	{
		return m_pATPDataBase->GetFundMarket(pReqData,ppAnsData,pnLen);
	} 
	else
	{
		return NULLHANDLE;
	}
	return 0;
}

int CATPFileDBApi::SetAlgoParam(int nServiceType,const Atp_Algorithm_Info* pAlgoInfo,const Atp_Algoparam_Info* pParamInfo)
{

	return 0;
}


CList <AtpVigil_Manager_UserInfo,AtpVigil_Manager_UserInfo>* CATPFileDBApi::GetLoginList()
{
	return &m_LoginList;
}

int CATPFileDBApi::ManagerLogin(IN struReq_ATPManageLogin *pInData)
{
	return m_pATPDataBase->ManagerLogin(pInData);
}