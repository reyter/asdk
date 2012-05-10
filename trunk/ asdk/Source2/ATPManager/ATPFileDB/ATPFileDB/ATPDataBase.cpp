#include "StdAfx.h"
#include "ATPDataBase.h"


CATPDataBase::CATPDataBase(void)
{

	m_nUsedATPDBSManagerItem = 0;
	m_nATPDBSManagerItem = 0;
	m_pATPDBSManager = NULL;

	m_nUsedATPDBSServerGroupItem = 0;
	m_nATPDBSServerGroupItem = 0;
	m_pATPDBSServerGroup = NULL;

	m_nUsedATPDBSServerItem = 0;
	m_nATPDBSServerItem = 0;
	m_pATPDBSServer = NULL;

	m_nUsedATPDBSPermissionItem = 0;
	m_nATPDBSPermissionItem = 0;
	m_pATPDBSPermission = NULL;

	m_nUsedATPDBSUserGroupItem = 0;
	m_nATPDBSUserGroupItem = 0;
	m_pATPDBSUserGroup = NULL;

	m_nUsedATPDBSUserItem = 0;
	m_nATPDBSUserItem = 0;
	m_pATPDBSUser = NULL;

	m_nUsedATPDBSAlgorithmGroupItem = 0;
	m_nATPDBSAlgorithmGroupItem = 0;
	m_pATPDBSAlgorithmGroup = NULL;

// 	m_nUsedATPDataBaseAlgorithmParamEXItem = 0;
// 	m_nATPDataBaseAlgorithmParamEXItem = 0;
// 	m_pATPDataBaseAlgorithmParamEX = NULL;

	m_nUsedATPDBSAlgorithmItem = 0;
	m_nATPDBSAlgorithmItem = 0;
	m_pATPDBSAlgorithm = NULL;
	InitDBFile("");

}


CATPDataBase::~CATPDataBase(void)
{
	SaveRegistSaveData();//保存数据
}

void*	CATPDataBase::NewRegisterSaveDataStruct(int nID, int nItems)
{
	if (nID == 1)
	{
		m_pATPDBSManager	= new struATPDataBaseManager[nItems];
		return m_pATPDBSManager;
	}
	if (nID == 2)
	{
		m_pATPDBSServerGroup = new struATPDataBaseServerGroup[nItems];
		return m_pATPDBSServerGroup;
	}
	if (nID == 3)
	{
		m_pATPDBSServer = new struATPDataBaseServer[nItems];
		return m_pATPDBSServer;
	}
	if (nID == 4)
	{
		m_pATPDBSPermission = new struATPDataBasePermission[nItems];
		return m_pATPDBSPermission;
	}
	if (nID == 5)
	{
		m_pATPDBSUserGroup = new struATPDataBaseUserGroup[nItems];
		return m_pATPDBSUserGroup;
	}
	if (nID == 6)
	{
		m_pATPDBSUser = new struATPDataBaseUser[nItems];
		return m_pATPDBSUser;
	}
	if (nID == 8)
	{
		m_pATPDBSAlgorithmGroup = new struATPDataBaseAlgorithmGroup[nItems];
		return m_pATPDBSAlgorithmGroup;
	}
	if (nID == 9)
	{
		m_pATPDBSAlgorithm = new struATPDataBaseAlgorithm[nItems];
		return m_pATPDBSAlgorithm;
	}

// 	if (nID == 11)
// 	{
// 		m_pATPDataBaseAlgorithmParamEX = new struATPDataBaseAlgorithmParamEX[nItems];
// 		return m_pATPDataBaseAlgorithmParamEX;
// 	}
	return 0;
}

BOOL	CATPDataBase::DeleteRegisterSaveDataStruct(int nID, int nItems)
{

	if (nID == 1)
	{
		if (m_pATPDBSManager)
		{
			delete m_pATPDBSManager;
		}
	}
	if (nID == 2)
	{
		if (m_pATPDBSServerGroup)
		{
			delete m_pATPDBSServerGroup;
		}
	}
	if (nID == 3)
	{
		if (m_pATPDBSServer)
		{
			delete m_pATPDBSServer;
		}
	}
	if (nID == 4)
	{
		if (m_pATPDBSPermission)
		{
			delete m_pATPDBSPermission;
		}
	}
	if (nID == 5)
	{
		if (m_pATPDBSUserGroup)
		{
			delete m_pATPDBSUserGroup;
		}
	}
	if (nID == 6)
	{
		if (m_pATPDBSUser)
		{
			delete m_pATPDBSUser;
		}
	}
	if (nID == 8)
	{
		if (m_pATPDBSAlgorithmGroup)
		{
			delete m_pATPDBSAlgorithmGroup;
		}
	}
	if (nID == 9)
	{
		if (m_pATPDBSAlgorithm)
		{
			delete m_pATPDBSAlgorithm;
		}
	}

// 	if (nID == 11)
// 	{
// 		if (m_pATPDataBaseAlgorithmParamEX)
// 		{
// 			delete m_pATPDataBaseAlgorithmParamEX;
// 		}
// 	}
	return TRUE;
}



void	CATPDataBase::RegisterData()
{
	CONST UINT32 nUINT8SIZE		= sizeof(UINT8);
	CONST UINT32 nUINT32SIZE	= sizeof(UINT32);
	CONST UINT32 nUINT64SIZE	= sizeof(UINT64);
	CONST UINT32 nATPAUTOID		= sizeof(struATPAutoID);
	CONST UINT32 nATPAUTOALGOID = sizeof(struATPAutoAlgoID);
	mkdir("..\\DB");
	SetSaveDataFileName("..\\DB\\ATP.db");	

	//管理员
	//struATPDataBaseManager			*m_pATPDBSManager;
	struATPDataBaseManager _ATPDBSManager;
	CONST UINT32 nATPDBSMANAGERSIZE = sizeof(struATPDataBaseManager);
	RegisterSaveDataStruct(1, 1, &_ATPDBSManager, nATPDBSMANAGERSIZE,&_ATPDBSManager.nSerialNumber,	nUINT32SIZE);
	RegisterSaveDataStruct(1, 2, &_ATPDBSManager, nATPDBSMANAGERSIZE, _ATPDBSManager.szID,			sizeof(_ATPDBSManager.szID));
	RegisterSaveDataStruct(1, 3, &_ATPDBSManager, nATPDBSMANAGERSIZE, _ATPDBSManager.szName,		sizeof(_ATPDBSManager.szName));
	RegisterSaveDataStruct(1, 4, &_ATPDBSManager, nATPDBSMANAGERSIZE, _ATPDBSManager.szPwd,			sizeof(_ATPDBSManager.szPwd));
	RegisterSaveDataStruct(1, 5, &_ATPDBSManager, nATPDBSMANAGERSIZE,&_ATPDBSManager.nStatus,		nUINT32SIZE);	
	RegisterSaveDataStruct(1, 6, &_ATPDBSManager, nATPDBSMANAGERSIZE, _ATPDBSManager.szExplain,		sizeof(_ATPDBSManager.szExplain));	
	RegisterSaveDataStruct(1, 7, &_ATPDBSManager, nATPDBSMANAGERSIZE, _ATPDBSManager.nPermissionIDs,sizeof(_ATPDBSManager.nPermissionIDs));	
	RegisterSaveDataStruct(1, 8, &_ATPDBSManager, nATPDBSMANAGERSIZE,&_ATPDBSManager.nCreateDate,	nUINT32SIZE);
	RegisterSaveDataStruct(1, 9, &_ATPDBSManager, nATPDBSMANAGERSIZE,&_ATPDBSManager.nCreateTime,	nUINT32SIZE);
	RegisterSaveDataStruct(1, 10,&_ATPDBSManager, nATPDBSMANAGERSIZE,&_ATPDBSManager.nLastDate,		nUINT32SIZE);
	RegisterSaveDataStruct(1, 11,&_ATPDBSManager, nATPDBSMANAGERSIZE,&_ATPDBSManager.nLastTime,		nUINT32SIZE);
	RegisterSaveDataStruct(1, 12,&_ATPDBSManager, nATPDBSMANAGERSIZE,&_ATPDBSManager.nDeleteMark,	nUINT8SIZE);
	RegisterSaveDataStruct(1, 13,&_ATPDBSManager, nATPDBSMANAGERSIZE,&_ATPDBSManager.nServerN,		nUINT32SIZE);
	RegisterSaveDataStruct(1, 14,&_ATPDBSManager, nATPDBSMANAGERSIZE,&_ATPDBSManager.nServerGroupN,	nUINT32SIZE);

	RegisterSaveDataStruct(1, 15,&_ATPDBSManager, nATPDBSMANAGERSIZE,&_ATPDBSManager.pServerIDs,		nATPAUTOID,(int *)&_ATPDBSManager.nServerN);
	RegisterSaveDataStruct(1, 16,&_ATPDBSManager, nATPDBSMANAGERSIZE,&_ATPDBSManager.pServerGroupIDs,	nATPAUTOID,(int *)&_ATPDBSManager.nServerGroupN);

	RegisterSaveDataAddress(1, (void**)&m_pATPDBSManager, nATPDBSMANAGERSIZE, &m_nATPDBSManagerItem, 0, 10240);

	//服务器组
	//struATPDataBaseServerGroup		*m_pATPDBSServerGroup;
	struATPDataBaseServerGroup _ATPDBSServerGroup;
	CONST UINT32 nATPDBSSERVERGROUPSIZE = sizeof(struATPDataBaseServerGroup);
	RegisterSaveDataStruct(2, 1, &_ATPDBSServerGroup, nATPDBSSERVERGROUPSIZE,&_ATPDBSServerGroup.nID,		nUINT32SIZE);
	RegisterSaveDataStruct(2, 2, &_ATPDBSServerGroup, nATPDBSSERVERGROUPSIZE,&_ATPDBSServerGroup.nParentID,	nUINT32SIZE);
	RegisterSaveDataStruct(2, 3, &_ATPDBSServerGroup, nATPDBSSERVERGROUPSIZE, _ATPDBSServerGroup.szName,	sizeof(_ATPDBSServerGroup.szName));
	RegisterSaveDataStruct(2, 4, &_ATPDBSServerGroup, nATPDBSSERVERGROUPSIZE, _ATPDBSServerGroup.szExplain,	sizeof(_ATPDBSServerGroup.szExplain));
	RegisterSaveDataStruct(2, 5, &_ATPDBSServerGroup, nATPDBSSERVERGROUPSIZE,&_ATPDBSServerGroup.nCreateDate,nUINT32SIZE);	
	RegisterSaveDataStruct(2, 6, &_ATPDBSServerGroup, nATPDBSSERVERGROUPSIZE,&_ATPDBSServerGroup.nCreateTime,nUINT32SIZE);	
	RegisterSaveDataStruct(2, 7, &_ATPDBSServerGroup, nATPDBSSERVERGROUPSIZE,&_ATPDBSServerGroup.nDeleteMark,nUINT8SIZE);	

	RegisterSaveDataAddress(2, (void**)&m_pATPDBSServerGroup, nATPDBSSERVERGROUPSIZE, &m_nATPDBSServerGroupItem, 0, 10240);

	//服务器
	//struATPDataBaseServer			*m_pATPDBSServer;
	struATPDataBaseServer _ATPDBSServer;
	CONST UINT32 nATPDBSSERVERSIZE = sizeof(struATPDataBaseServer);
	RegisterSaveDataStruct(3, 1, &_ATPDBSServer, nATPDBSSERVERSIZE,&_ATPDBSServer.nID,			nUINT32SIZE);
	RegisterSaveDataStruct(3, 2, &_ATPDBSServer, nATPDBSSERVERSIZE, _ATPDBSServer.szName,		sizeof(_ATPDBSServer.szName));
	RegisterSaveDataStruct(3, 3, &_ATPDBSServer, nATPDBSSERVERSIZE, _ATPDBSServer.szIP,			sizeof(_ATPDBSServer.szIP));
	RegisterSaveDataStruct(3, 4, &_ATPDBSServer, nATPDBSSERVERSIZE,&_ATPDBSServer.nPort,		nUINT32SIZE);
	RegisterSaveDataStruct(3, 5, &_ATPDBSServer, nATPDBSSERVERSIZE,&_ATPDBSServer.nGroupID,		nUINT32SIZE);
	RegisterSaveDataStruct(3, 6, &_ATPDBSServer, nATPDBSSERVERSIZE,&_ATPDBSServer.nAlloc,		nUINT32SIZE);
	RegisterSaveDataStruct(3, 7, &_ATPDBSServer, nATPDBSSERVERSIZE,&_ATPDBSServer.nCreateDate,	nUINT32SIZE);	
	RegisterSaveDataStruct(3, 8, &_ATPDBSServer, nATPDBSSERVERSIZE,&_ATPDBSServer.nCreateTime,	nUINT32SIZE);	
	RegisterSaveDataStruct(3, 9, &_ATPDBSServer, nATPDBSSERVERSIZE,&_ATPDBSServer.nDeleteMark,	nUINT8SIZE);
	RegisterSaveDataStruct(3, 10, &_ATPDBSServer, nATPDBSSERVERSIZE,&_ATPDBSServer.nIPType,		nUINT32SIZE);	

	RegisterSaveDataAddress(3, (void**)&m_pATPDBSServer, nATPDBSSERVERSIZE, &m_nATPDBSServerItem, 0, 10240);


	//权限
	//struATPDataBasePermission		*m_pATPDBSPermission;
	struATPDataBasePermission _ATPDBSPermission;
	CONST UINT32 nATPDBSPERMISSIONSIZE = sizeof(struATPDataBasePermission);
	RegisterSaveDataStruct(4, 1, &_ATPDBSPermission, nATPDBSPERMISSIONSIZE,&_ATPDBSPermission.nPermissionID,	nUINT32SIZE);
	RegisterSaveDataStruct(4, 2, &_ATPDBSPermission, nATPDBSPERMISSIONSIZE, _ATPDBSPermission.szPermissionName,	sizeof(_ATPDBSPermission.szPermissionName));
	RegisterSaveDataStruct(4, 3, &_ATPDBSPermission, nATPDBSPERMISSIONSIZE,&_ATPDBSPermission.nPermissionType,	nUINT8SIZE);

	RegisterSaveDataAddress(4, (void**)&m_pATPDBSPermission, nATPDBSPERMISSIONSIZE, &m_nATPDBSPermissionItem, 0, 10240);


	//用户组
	//struATPDataBaseUserGroup			*m_pATPDBSUserGroup;
	struATPDataBaseUserGroup _ATPDBSUserGroup;
	CONST UINT32 nATPDBSUSERGROUPSIZE = sizeof(struATPDataBaseUserGroup);
	RegisterSaveDataStruct(5, 1, &_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE,&_ATPDBSUserGroup.nID,				nUINT32SIZE);
	RegisterSaveDataStruct(5, 2, &_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE,&_ATPDBSUserGroup.nParentID,		nUINT32SIZE);
	RegisterSaveDataStruct(5, 3, &_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE, _ATPDBSUserGroup.szName,			sizeof(_ATPDBSUserGroup.szName));
	RegisterSaveDataStruct(5, 4, &_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE, _ATPDBSUserGroup.szExplain,		sizeof(_ATPDBSUserGroup.szExplain));
	RegisterSaveDataStruct(5, 5, &_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE,&_ATPDBSUserGroup.nCreateDate,		nUINT32SIZE);	
	RegisterSaveDataStruct(5, 6, &_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE,&_ATPDBSUserGroup.nCreateTime,		nUINT32SIZE);	
	RegisterSaveDataStruct(5, 7, &_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE,&_ATPDBSUserGroup.nDeleteMark,		nUINT8SIZE);	
	RegisterSaveDataStruct(5, 8, &_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE,&_ATPDBSUserGroup.nAlgorithmN,		nUINT32SIZE);	
	RegisterSaveDataStruct(5, 9, &_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE,&_ATPDBSUserGroup.nAlgorithmGroupN,nUINT32SIZE);	
	RegisterSaveDataStruct(5, 10,&_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE,&_ATPDBSUserGroup.nServerN,		nUINT32SIZE);	
	RegisterSaveDataStruct(5, 11,&_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE,&_ATPDBSUserGroup.nServerGroupN,	nUINT32SIZE);	
	RegisterSaveDataStruct(5, 12,&_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE, _ATPDBSUserGroup.szManagerID,		sizeof(_ATPDBSUserGroup.szManagerID));

	RegisterSaveDataStruct(5, 13,&_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE,&_ATPDBSUserGroup.pAlgorithmIDs,	nATPAUTOALGOID,(int *)&_ATPDBSUserGroup.nAlgorithmN);
	RegisterSaveDataStruct(5, 14,&_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE,&_ATPDBSUserGroup.pAlgorithmGroupIDs,nATPAUTOID,(int *)&_ATPDBSUserGroup.nAlgorithmGroupN);
	RegisterSaveDataStruct(5, 15,&_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE,&_ATPDBSUserGroup.pServerIDs,		nATPAUTOID,(int *)&_ATPDBSUserGroup.nServerN);
	RegisterSaveDataStruct(5, 16,&_ATPDBSUserGroup, nATPDBSUSERGROUPSIZE,&_ATPDBSUserGroup.pServerGroupIDs,	nATPAUTOID,(int *)&_ATPDBSUserGroup.nServerGroupN);

	RegisterSaveDataAddress(5, (void**)&m_pATPDBSUserGroup, nATPDBSUSERGROUPSIZE, &m_nATPDBSUserGroupItem, 0, 10240);

	//用户
	//struATPDataBaseUser				*m_pATPDBSUser;
	struATPDataBaseUser _ATPDBSUser;
	CONST UINT32 nATPDBSUSERSIZE = sizeof(struATPDataBaseUser);
	RegisterSaveDataStruct(6, 1, &_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nSerialNumber,				nUINT32SIZE);
	RegisterSaveDataStruct(6, 2, &_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.szUserID,					sizeof(_ATPDBSUser.szUserID));
	RegisterSaveDataStruct(6, 3, &_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.szPwd,						sizeof(_ATPDBSUser.szPwd));
	RegisterSaveDataStruct(6, 4, &_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.szUserName,					sizeof(_ATPDBSUser.szUserName));
	RegisterSaveDataStruct(6, 5, &_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.szCardID,					sizeof(_ATPDBSUser.szCardID));
	RegisterSaveDataStruct(6, 6, &_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.nGroupIDs,					sizeof( _ATPDBSUser.nGroupIDs));
	RegisterSaveDataStruct(6, 7, &_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.nPermissionIDs,				sizeof(_ATPDBSUser.nPermissionIDs));
	RegisterSaveDataStruct(6, 8, &_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nAuthorizeBeginDate,		nUINT32SIZE);
	RegisterSaveDataStruct(6, 9, &_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nAuthorizeEndDate,			nUINT32SIZE);
	RegisterSaveDataStruct(6, 10,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nStatus,					nUINT32SIZE);
	RegisterSaveDataStruct(6, 11,&_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.szMobiles,					sizeof(_ATPDBSUser.szMobiles));
	RegisterSaveDataStruct(6, 12,&_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.szTelephones,				sizeof(_ATPDBSUser.szTelephones));
	RegisterSaveDataStruct(6, 13,&_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.nQQNumbers,					sizeof(_ATPDBSUser.nQQNumbers));
	RegisterSaveDataStruct(6, 14,&_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.szEmails,					sizeof(_ATPDBSUser.szEmails));
	RegisterSaveDataStruct(6, 15,&_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.szUserExplain,				sizeof(_ATPDBSUser.szUserExplain));
	RegisterSaveDataStruct(6, 16,&_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.szIPs,						sizeof(_ATPDBSUser.szIPs));
	RegisterSaveDataStruct(6, 17,&_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.szMacMark,					sizeof(_ATPDBSUser.szMacMark));
	RegisterSaveDataStruct(6, 18,&_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.szDiskNum,					sizeof(_ATPDBSUser.szDiskNum));
	RegisterSaveDataStruct(6, 19,&_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.nLimitBeginTime,			sizeof(_ATPDBSUser.nLimitBeginTime));
	RegisterSaveDataStruct(6, 20,&_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.nLimitEndTime,				sizeof(_ATPDBSUser.nLimitEndTime));
	RegisterSaveDataStruct(6, 21,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.chLimitWeek,				sizeof(char));
	RegisterSaveDataStruct(6, 22,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nCanAssociateFundsAccount,	nUINT32SIZE);
	RegisterSaveDataStruct(6, 23,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nCanRunAlgorithm,			nUINT32SIZE);
	RegisterSaveDataStruct(6, 24,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nAlgorithmN,				nUINT32SIZE);
	RegisterSaveDataStruct(6, 25,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nAlgorithmGroupN,			nUINT32SIZE);
	RegisterSaveDataStruct(6, 26,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nServerN,					nUINT32SIZE);
	RegisterSaveDataStruct(6, 27,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nServerGroupN,				nUINT32SIZE);
	RegisterSaveDataStruct(6, 28,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nCreateDate,				nUINT32SIZE);
	RegisterSaveDataStruct(6, 29,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nCreateTime,				nUINT32SIZE);
	RegisterSaveDataStruct(6, 30,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nLastDate,					nUINT32SIZE);
	RegisterSaveDataStruct(6, 31,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nLastTime,					nUINT32SIZE);
	RegisterSaveDataStruct(6, 32,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.nDeleteMark,				nUINT8SIZE);
	RegisterSaveDataStruct(6, 33,&_ATPDBSUser, nATPDBSUSERSIZE, _ATPDBSUser.szManagerID,				sizeof(_ATPDBSUser.szManagerID));

	RegisterSaveDataStruct(6, 34,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.pATPFund,			sizeof(struATPDataBaseFund),(int *)&_ATPDBSUser.nCanAssociateFundsAccount);
	RegisterSaveDataStruct(6, 35,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.pAlgorithmIDs,		nATPAUTOALGOID,(int *)&_ATPDBSUser.nAlgorithmN);
	RegisterSaveDataStruct(6, 36,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.pAlgorithmGroupIDs,	nATPAUTOID,(int *)&_ATPDBSUser.nAlgorithmGroupN);
	RegisterSaveDataStruct(6, 37,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.pServerIDs,			nATPAUTOID,(int *)&_ATPDBSUser.nServerN);
	RegisterSaveDataStruct(6, 38,&_ATPDBSUser, nATPDBSUSERSIZE,&_ATPDBSUser.pServerGroupIDs,	nATPAUTOID,(int *)&_ATPDBSUser.nServerGroupN);

	RegisterSaveDataAddress(6, (void**)&m_pATPDBSUser, nATPDBSUSERSIZE, &m_nATPDBSUserItem, 0, 10240);



	//算法组
	//struATPDataBaseAlgorithmGroup	*m_pATPDBSAlgorithmGroup;
	struATPDataBaseAlgorithmGroup _ATPDBSAlgorithmGroup;
	CONST UINT32 nATPDBSALGORITHMGROUPSIZE = sizeof(struATPDataBaseAlgorithmGroup);
	RegisterSaveDataStruct(8, 1, &_ATPDBSAlgorithmGroup, nATPDBSALGORITHMGROUPSIZE,&_ATPDBSAlgorithmGroup.nID,			nUINT32SIZE);
	RegisterSaveDataStruct(8, 2, &_ATPDBSAlgorithmGroup, nATPDBSALGORITHMGROUPSIZE,&_ATPDBSAlgorithmGroup.nParentID,	nUINT32SIZE);
	RegisterSaveDataStruct(8, 3, &_ATPDBSAlgorithmGroup, nATPDBSALGORITHMGROUPSIZE, _ATPDBSAlgorithmGroup.szName,		sizeof(_ATPDBSAlgorithmGroup.szName));
	RegisterSaveDataStruct(8, 4, &_ATPDBSAlgorithmGroup, nATPDBSALGORITHMGROUPSIZE,&_ATPDBSAlgorithmGroup.nCreateDate,	nUINT32SIZE);
	RegisterSaveDataStruct(8, 5, &_ATPDBSAlgorithmGroup, nATPDBSALGORITHMGROUPSIZE,&_ATPDBSAlgorithmGroup.nCreateTime,	nUINT32SIZE);
	RegisterSaveDataStruct(8, 6, &_ATPDBSAlgorithmGroup, nATPDBSALGORITHMGROUPSIZE,&_ATPDBSAlgorithmGroup.nDeleteMark,	nUINT8SIZE);
	RegisterSaveDataStruct(8, 7, &_ATPDBSAlgorithmGroup, nATPDBSALGORITHMGROUPSIZE, _ATPDBSAlgorithmGroup.szManagerID,	sizeof(_ATPDBSAlgorithmGroup.szManagerID));

	RegisterSaveDataAddress(8, (void**)&m_pATPDBSAlgorithmGroup, nATPDBSALGORITHMGROUPSIZE, &m_nATPDBSAlgorithmGroupItem, 0, 10240);

	//算法
	//struATPDataBaseAlgorithm			*m_pATPDBSAlgorithm;
	struATPDataBaseAlgorithm _ATPDBSAlgorithm;
	CONST UINT32 nATPDBSALGORITHMSIZE = sizeof(struATPDataBaseAlgorithm);
	RegisterSaveDataStruct(9, 1,  &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.nSerialNumber,		nUINT32SIZE);
	RegisterSaveDataStruct(9, 2,  &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.AlgorithmID,		sizeof(GUID));
	RegisterSaveDataStruct(9, 3,  &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE, _ATPDBSAlgorithm.szAlgorithmName,	sizeof(_ATPDBSAlgorithm.szAlgorithmName));
	RegisterSaveDataStruct(9, 4,  &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.AlgorithVer,		sizeof(struDataBaseAlgorithmVer));
	RegisterSaveDataStruct(9, 5,  &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.nVersionAttribute,	nUINT8SIZE);
	RegisterSaveDataStruct(9, 6,  &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.nCharge,			nUINT8SIZE);
	RegisterSaveDataStruct(9, 7,  &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.nGroupID,			nUINT32SIZE);
	RegisterSaveDataStruct(9, 8,  &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE, _ATPDBSAlgorithm.szExplain,			sizeof(_ATPDBSAlgorithm.szExplain));
	RegisterSaveDataStruct(9, 9,  &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE, _ATPDBSAlgorithm.szWarning,			sizeof(_ATPDBSAlgorithm.szWarning));
	RegisterSaveDataStruct(9, 10, &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE, _ATPDBSAlgorithm.szKeyword,			sizeof(_ATPDBSAlgorithm.szKeyword));
	RegisterSaveDataStruct(9, 11, &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.nStatus,			nUINT8SIZE);
	RegisterSaveDataStruct(9, 12, &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE, _ATPDBSAlgorithm.szStopReason,		sizeof(_ATPDBSAlgorithm.szStopReason));
	RegisterSaveDataStruct(9, 13, &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.nCreateDate,		nUINT32SIZE);
	RegisterSaveDataStruct(9, 14, &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.nCreateTime,		nUINT32SIZE);
	RegisterSaveDataStruct(9, 15, &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE, _ATPDBSAlgorithm.szPath,				sizeof(_ATPDBSAlgorithm.szPath));
	RegisterSaveDataStruct(9, 16, &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.nParams,			nUINT32SIZE);
	RegisterSaveDataStruct(9, 17, &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.nDeleteMark,		nUINT8SIZE);
	RegisterSaveDataStruct(9, 18, &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE, _ATPDBSAlgorithm.szManagerID,		sizeof(_ATPDBSAlgorithm.szManagerID));
	RegisterSaveDataStruct(9, 19, &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.nParamsEx,			nUINT32SIZE);
	RegisterSaveDataStruct(9, 20, &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.szMainDllName,		sizeof(_ATPDBSAlgorithm.szMainDllName));
	RegisterSaveDataStruct(9, 21, &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.nMarketType,			nUINT32SIZE);
	RegisterSaveDataStruct(9, 22, &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.nLanguageType,			nUINT32SIZE);
	RegisterSaveDataStruct(9, 23, &_ATPDBSAlgorithm, nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.nAlgoType,			nUINT32SIZE);

	RegisterSaveDataStruct(9, 24,&_ATPDBSAlgorithm,  nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.pATPAlgorithmParams,sizeof(struATPDataBaseAlgorithmParam),(int *)&_ATPDBSAlgorithm.nParams);
	RegisterSaveDataStruct(9, 25,&_ATPDBSAlgorithm,  nATPDBSALGORITHMSIZE,&_ATPDBSAlgorithm.pATPAlgorithmParamsEX,sizeof(struATPDataBaseAlgorithmParamEX),(int *)&_ATPDBSAlgorithm.nParamsEx);

	RegisterSaveDataAddress(9, (void**)&m_pATPDBSAlgorithm, nATPDBSALGORITHMSIZE, &m_nATPDBSAlgorithmItem, 0, 10240);


	// 	struATPDataBaseAlgorithmParamEX _struATPDataBaseAlgorithmParamEX;
	// 	CONST UINT32 nATPDATABASEALGORITHMPARAMEXSIZE = sizeof(struATPDataBaseAlgorithmParamEX);
	// 	RegisterSaveDataStruct(11, 1,  &_struATPDataBaseAlgorithmParamEX, nATPDATABASEALGORITHMPARAMEXSIZE,&_struATPDataBaseAlgorithmParamEX.nSerialNumber,		nUINT32SIZE);
	// 	RegisterSaveDataStruct(11, 2,  &_struATPDataBaseAlgorithmParamEX, nATPDATABASEALGORITHMPARAMEXSIZE,&_struATPDataBaseAlgorithmParamEX.nExtraDataLength,	nUINT32SIZE);
	// 	RegisterSaveDataStruct(11, 3,  &_struATPDataBaseAlgorithmParamEX, nATPDATABASEALGORITHMPARAMEXSIZE,&_struATPDataBaseAlgorithmParamEX.ExtraData,	sizeof _struATPDataBaseAlgorithmParamEX.ExtraData);
	// 
	// 	//RegisterSaveDataStruct(11, 3,&_struATPDataBaseAlgorithmParamEX,  nATPDATABASEALGORITHMPARAMEXSIZE,&_struATPDataBaseAlgorithmParamEX.ExtraData,sizeof(char),(int *)&_struATPDataBaseAlgorithmParamEX.nExtraDataLength);
	// 
	// 	RegisterSaveDataAddress(11, (void**)&m_pATPDataBaseAlgorithmParamEX, nATPDATABASEALGORITHMPARAMEXSIZE, &m_nATPDataBaseAlgorithmParamEXItem, 0, 10240);


	RegisterSaveData(21,&m_nUsedATPDBSManagerItem,1);
	RegisterSaveData(22,&m_nUsedATPDBSServerGroupItem,1);
	RegisterSaveData(23,&m_nUsedATPDBSServerItem,1);
	RegisterSaveData(24,&m_nUsedATPDBSPermissionItem,1);
	RegisterSaveData(25,&m_nUsedATPDBSUserGroupItem,1);
	RegisterSaveData(26,&m_nUsedATPDBSUserItem,1);
	RegisterSaveData(28,&m_nUsedATPDBSAlgorithmGroupItem,1);
	RegisterSaveData(29,&m_nUsedATPDBSAlgorithmItem,1);
//	RegisterSaveData(31,&m_nUsedATPDataBaseAlgorithmParamEXItem,1);

	RegisterSaveData(41,&m_nATPDBSManagerItem,1);
	RegisterSaveData(42,&m_nATPDBSServerGroupItem,1);
	RegisterSaveData(43,&m_nATPDBSServerItem,1);
	RegisterSaveData(44,&m_nATPDBSPermissionItem,1);
	RegisterSaveData(45,&m_nATPDBSUserGroupItem,1);
	RegisterSaveData(46,&m_nATPDBSUserItem,1);
	RegisterSaveData(48,&m_nATPDBSAlgorithmGroupItem,1);
	RegisterSaveData(49,&m_nATPDBSAlgorithmItem,1);
	//RegisterSaveData(51,&m_nATPDataBaseAlgorithmParamEXItem,1);

}



int CATPDataBase::InitDBFile(char *pFilename)
{
	RegisterData();
	CFileFind  fileFind;
	mkdir("..\\DB");
	BOOL	bResult=fileFind.FindFile("..\\DB\\ATP.db");
	//RegisterData();
	if(!bResult)
	{

		m_nUsedATPDBSManagerItem	= 0;
		m_nATPDBSManagerItem		= 100;//管理员默认100
		m_pATPDBSManager			= new struATPDataBaseManager[m_nATPDBSManagerItem];
		if (NULL == m_pATPDBSManager)
		{
			return NEWERROR;
		}
		ZeroMemory((char*)m_pATPDBSManager,m_nATPDBSManagerItem*sizeof(struATPDataBaseManager));
		//////////////////////////////////////////////////////////////////////////
		//! 测试数据
		//! 添加管理员
		m_nUsedATPDBSManagerItem = 1;
		int i=0;
		for (;i<22;i++)
		{
			m_pATPDBSManager[0].nPermissionIDs[i] = i+12;
		}
		m_pATPDBSManager[0].nSerialNumber = 1;						//	自动增长 唯一
		strcpy(m_pATPDBSManager[0].szID,"admin");				//	管理员ID
		strcpy(m_pATPDBSManager[0].szName,"ATP");					//	名字
		strcpy(m_pATPDBSManager[0].szPwd,"admin");					//	密码
		m_pATPDBSManager[0].nStatus = 0;							//	管理员状态  0 1 2
		strcpy(m_pATPDBSManager[0].szExplain,"ATP3");		//	说明信息
		//m_pATPDBSManager[0].nPermissionIDs[32];	//	权限ID
		m_pATPDBSManager[0].nCreateDate = 20110822;					//	创建日期
		m_pATPDBSManager[0].nCreateTime = 91356;					//	创建时间
		m_pATPDBSManager[0].nLastDate = 20110823;					//	最后登陆日期
		m_pATPDBSManager[0].nLastTime = 102145;						//	最后登陆时间
		m_pATPDBSManager[0].nDeleteMark = 0;						//	删除标志
		m_pATPDBSManager[0].nServerN = 0;							//	服务器个数
		m_pATPDBSManager[0].pServerIDs = NULL;//new struATPAutoID[2];								//	服务器IDs
		m_pATPDBSManager[0].nServerGroupN = 0;						//	服务器组个数
		m_pATPDBSManager[0].pServerGroupIDs = NULL;//new struATPAutoID[2];					//	服务器组IDs

		//////////////////////////////////////////////////////////////////////////
		m_nUsedATPDBSServerGroupItem	= 0;
		m_nATPDBSServerGroupItem		= 100;//服务器组默认100
		m_pATPDBSServerGroup			= new struATPDataBaseServerGroup[m_nATPDBSServerGroupItem];
		if (NULL == m_pATPDBSServerGroup)
		{
			return NEWERROR;
		}
		ZeroMemory((char*)m_pATPDBSServerGroup,m_nATPDBSServerGroupItem*sizeof(struATPDataBaseServerGroup));
		//////////////////////////////////////////////////////////////////////////
		m_nUsedATPDBSServerItem = 0;
		m_nATPDBSServerItem		= 100;//服务器默认100
		m_pATPDBSServer			= new struATPDataBaseServer[m_nATPDBSServerItem];
		if (NULL == m_pATPDBSServer)
		{
			return NEWERROR;
		}
		ZeroMemory((char*)m_pATPDBSServer,m_nATPDBSServerItem*sizeof(struATPDataBaseServer));
		//////////////////////////////////////////////////////////////////////////
		m_nUsedATPDBSPermissionItem = 0;
		m_nATPDBSPermissionItem		= 100;//权限默认100
		m_pATPDBSPermission			= new struATPDataBasePermission[m_nATPDBSPermissionItem];
		if (NULL == m_pATPDBSPermission)
		{
			return NEWERROR;
		}

		ZeroMemory((char*)m_pATPDBSPermission,m_nATPDBSPermissionItem*sizeof(struATPDataBasePermission));

		//////////////////////////////////////////////////////////////////////////
		//! 
		{
			//初始化权限
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_ADDMANAGER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"添加管理员");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_VIEWMANAGER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"查看管理员");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_MODIFYMANAGER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"修改管理员");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_DISABLEMANAGER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"禁用管理员");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_DELMANAGER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"删除管理员");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_ADDSERVER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"添加服务器");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_VIEWSERVER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"查看服务器");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_MODIFYSERVER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"修改服务器");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_DISABLESERVER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"禁用服务器");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_DELSERVER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"删除服务器");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_VIEWLOG;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"查看算法");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			//////////////////////////////////////////////////////////////////////////

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_ADDALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"添加算法");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_RELALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"发布算法");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_MODIFYALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"修改算法");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_VIEWALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"查看算法");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_DISABLEALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"禁用算法");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_DELALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"删除算法");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_ADDUSER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"添加用户");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_VIEWUSER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"查看用户");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_MODIFYUSER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"修改用户");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_DISABLEUSER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"禁用用户");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_DELUSER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"删除用户");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_VIEWMANAGER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"查看管理员");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_MODIFYMANAGER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"修改管理员");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_VIEWLOG;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"查看日志");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			//////////////////////////////////////////////////////////////////////////

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_ADDALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"添加算法");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_RUN_STOP_ALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"运行算法");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_MODIFYALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"修改算法");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_VIEWALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"查看算法");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_DELALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"删除算法");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_VIEWUSER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"查看用户");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_MODIFYUSER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"修改用户");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_VIEWLOG;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"查看日志");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;
		}

		//////////////////////////////////////////////////////////////////////////
		m_nUsedATPDBSAlgorithmGroupItem = 0;
		m_nATPDBSAlgorithmGroupItem		= 100;//算法组默认100
		m_pATPDBSAlgorithmGroup			= new struATPDataBaseAlgorithmGroup[m_nATPDBSAlgorithmGroupItem];
		if (NULL == m_pATPDBSAlgorithmGroup)
		{
			return NEWERROR;
		}
		ZeroMemory((char*)m_pATPDBSAlgorithmGroup,m_nATPDBSAlgorithmGroupItem*sizeof(struATPDataBaseAlgorithmGroup));
		//////////////////////////////////////////////////////////////////////////
		m_nUsedATPDBSAlgorithmItem	= 0;
		m_nATPDBSAlgorithmItem		= 500;//算法默认500
		m_pATPDBSAlgorithm			= new struATPDataBaseAlgorithm[m_nATPDBSAlgorithmItem];
		if (NULL == m_pATPDBSAlgorithm)
		{
			return NEWERROR;
		}
		ZeroMemory((char*)m_pATPDBSAlgorithm,m_nATPDBSAlgorithmItem*sizeof(struATPDataBaseAlgorithm));
		//////////////////////////////////////////////////////////////////////////
		m_nUsedATPDBSUserGroupItem	= 0;
		m_nATPDBSUserGroupItem		= 100;//用户组默认100
		m_pATPDBSUserGroup			= new struATPDataBaseUserGroup[m_nATPDBSUserGroupItem];
		if (NULL == m_pATPDBSUserGroup)
		{
			return NEWERROR;
		}
		ZeroMemory((char*)m_pATPDBSUserGroup,m_nATPDBSUserGroupItem*sizeof(struATPDataBaseUserGroup));
		//////////////////////////////////////////////////////////////////////////
		m_nUsedATPDBSUserItem	= 0;
		m_nATPDBSUserItem		= 1000;//用户默认1000
		m_pATPDBSUser			= new struATPDataBaseUser[m_nATPDBSUserItem];
		if (NULL == m_pATPDBSUser)
		{
			return NEWERROR;
		}
		ZeroMemory((char*)m_pATPDBSUser,m_nATPDBSUserItem*sizeof(struATPDataBaseUser));
		//////////////////////////////////////////////////////////////////////////
		SaveRegistSaveData();//保存数据
		if (m_pATPDBSManager)
		{
			delete []m_pATPDBSManager;			m_pATPDBSManager		= NULL;
		}
		if (m_pATPDBSServerGroup)
		{
			delete []m_pATPDBSServerGroup;		m_pATPDBSServerGroup	= NULL;
		}
		if (m_pATPDBSServer)
		{
			delete []m_pATPDBSServer;			m_pATPDBSServer			= NULL;
		}
		if (m_pATPDBSPermission)
		{
			delete []m_pATPDBSPermission;		m_pATPDBSPermission		= NULL;
		}
		if (m_pATPDBSUserGroup)
		{
			delete []m_pATPDBSUserGroup;		m_pATPDBSUserGroup		= NULL;
		}
		if (m_pATPDBSUser)
		{
			delete []m_pATPDBSUser;				m_pATPDBSUser			= NULL;
		}
		if (m_pATPDBSAlgorithmGroup)
		{
			delete []m_pATPDBSAlgorithmGroup;	m_pATPDBSAlgorithmGroup = NULL;
		}
		if (m_pATPDBSAlgorithm)
		{
			delete []m_pATPDBSAlgorithm;		m_pATPDBSAlgorithm		= NULL;
		}

	}
	ReadRegistSaveData();
	fileFind.Close();
	return 0;
}


//////////////////////////////////////////////////////////////////////////
int CATPDataBase::AddManager(struATPDataBaseManager *pInATPDBSManager,struATPDataBaseManager *pOutATPDBSManager)
{
	int nRet = 0;
	if (NULL == m_pATPDBSManager)
	{
		nRet = NOTINIT;
		goto END__ADDMANAGER;
	}
	//判断内存是否够用
	//***






	/**
	判断是否已经存在相同数据
	*/
	for (int i=0;i<m_nUsedATPDBSManagerItem;i++)
	{
		//管理员ID
		//管理员ID不能重复
		if (0==strcmp(m_pATPDBSManager[i].szID,pInATPDBSManager->szID))
		{
			//发现重复
			//判断该ID是否被删除了
			if (m_pATPDBSManager[i].nDeleteMark == FALSE)
			{
				nRet = EXISTDATA;
				goto END__ADDMANAGER;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	memcpy((char *)&m_pATPDBSManager[m_nUsedATPDBSManagerItem],(char *)pInATPDBSManager,sizeof struATPDataBaseManager);
	//序号递增
	if (m_nUsedATPDBSManagerItem == 0)
	{
		m_pATPDBSManager[m_nUsedATPDBSManagerItem].nSerialNumber = 1;
	} 
	else
	{
		m_pATPDBSManager[m_nUsedATPDBSManagerItem].nSerialNumber = m_pATPDBSManager[m_nUsedATPDBSManagerItem-1].nSerialNumber + 1;
	}

	//服务器
	m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerIDs = NULL;
	if (pInATPDBSManager->nServerN>0)
	{
		m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerIDs = new struATPAutoID[pInATPDBSManager->nServerN];
		if (NULL == m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerIDs)
		{
			//内存NEW出错，回滚
			ZeroMemory((char *)&m_pATPDBSManager[m_nUsedATPDBSManagerItem],0);
			nRet = NEWERROR;
			goto END__ADDMANAGER;
			
		}
		memcpy(m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerIDs,pInATPDBSManager->pServerIDs,pInATPDBSManager->nServerN*sizeof struATPAutoID);
	}

	//
	//服务器组
	m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerGroupIDs = NULL;
	if (pInATPDBSManager->nServerGroupN>0)
	{
		m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerGroupIDs = new struATPAutoID[pInATPDBSManager->nServerGroupN];
		if (NULL == m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerGroupIDs)
		{
			//内存NEW出错，回滚
			delete m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerIDs;
			ZeroMemory((char *)&m_pATPDBSManager[m_nUsedATPDBSManagerItem],0);
			nRet = NEWERROR;
			goto END__ADDMANAGER;

		}
		memcpy(m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerGroupIDs,pInATPDBSManager->pServerGroupIDs,pInATPDBSManager->nServerGroupN*sizeof struATPAutoID);
	}

	//使用标记+1
	m_nUsedATPDBSManagerItem += 1;


	//成功，返回添加数据
	if (NULL == pOutATPDBSManager)
	{
		nRet = ZERORECORD;
		goto END__ADDMANAGER;
		
	}
	memcpy((char *)pOutATPDBSManager,(char *)&m_pATPDBSManager[m_nUsedATPDBSManagerItem-1],sizeof struATPDataBaseManager);

END__ADDMANAGER:

	SaveRegistSaveData();//保存数据
	return nRet;
}


int CATPDataBase::ModifyManager(struATPDataBaseManager *pATPDBSManager)
{
	int nRet = 0;
	struATPDataBaseManager _ATPDBSManagerTem = {0};
	if (NULL == m_pATPDBSManager)
	{
		nRet = NOTINIT;
		goto END__MODIFYMANAGER;
		
	}

	/**
	判断是否已经存在相同数据
	*/
	for (int i=0;i<m_nUsedATPDBSManagerItem;i++)
	{
		//比较nSerialNumber不相等的管理员ID
		if (m_pATPDBSManager[i].nSerialNumber != pATPDBSManager->nSerialNumber)
		{
			//管理员ID
			//不能存在相同ID
			if (0==strcmp(m_pATPDBSManager[i].szID,pATPDBSManager->szID))
			{
				if (m_pATPDBSManager[i].nDeleteMark == FALSE)
				{
					nRet = EXISTDATA;
					goto END__MODIFYMANAGER;
				}
			}
		}	
	}
	//////////////////////////////////////////////////////////////////////////
	if (1==pATPDBSManager->nSerialNumber)
	{
		strcpy(m_pATPDBSManager[0].szExplain,pATPDBSManager->szExplain);
		strcpy(m_pATPDBSManager[0].szName,pATPDBSManager->szName);
		strcpy(m_pATPDBSManager[0].szID,pATPDBSManager->szID);
		strcpy(m_pATPDBSManager[0].szPwd,pATPDBSManager->szPwd);
		goto END__MODIFYMANAGER;
	} 


	//确保操作的是同一个内存块
	if (m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nSerialNumber == pATPDBSManager->nSerialNumber)
	{
		//把数据copy到临时堆内存
		memcpy((char *)&_ATPDBSManagerTem,(char *)pATPDBSManager,sizeof struATPDataBaseManager);
		_ATPDBSManagerTem.nCreateDate	= m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nCreateDate;
		_ATPDBSManagerTem.nCreateTime	= m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nCreateTime;
		_ATPDBSManagerTem.nLastDate		= m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nLastDate;
		_ATPDBSManagerTem.nLastTime		= m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nLastTime;






		//服务器
		_ATPDBSManagerTem.pServerIDs = NULL;
		if (_ATPDBSManagerTem.nServerN>0)
		{
			_ATPDBSManagerTem.pServerIDs = new struATPAutoID[_ATPDBSManagerTem.nServerN];
			if (NULL == _ATPDBSManagerTem.pServerIDs)
			{
				//NEW出错
				nRet = NEWERROR;
				goto END__MODIFYMANAGER;
			}
			memcpy((char *)_ATPDBSManagerTem.pServerIDs,(char *)pATPDBSManager->pServerIDs,_ATPDBSManagerTem.nServerN*sizeof struATPAutoID);

		}


		//服务器组
		_ATPDBSManagerTem.pServerGroupIDs = NULL;
		if (_ATPDBSManagerTem.nServerGroupN>0)
		{
			_ATPDBSManagerTem.pServerGroupIDs = new struATPAutoID[_ATPDBSManagerTem.nServerGroupN];
			if (NULL == _ATPDBSManagerTem.pServerGroupIDs)
			{
				//NEW出错
				delete _ATPDBSManagerTem.pServerIDs;
				nRet = NEWERROR;
				goto END__MODIFYMANAGER;
			}
			memcpy((char *)_ATPDBSManagerTem.pServerGroupIDs,(char *)pATPDBSManager->pServerGroupIDs,_ATPDBSManagerTem.nServerGroupN*sizeof struATPAutoID);
		}
		//删除之前所指向的指针
		delete []m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].pServerIDs;m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].pServerIDs = NULL;
		delete []m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].pServerGroupIDs;m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].pServerGroupIDs = NULL;
		//
		memcpy((char *)&m_pATPDBSManager[pATPDBSManager->nSerialNumber-1],(char *)&_ATPDBSManagerTem,sizeof struATPDataBaseManager);


	}
	else
	{
		nRet = ZERORECORD;
	}

END__MODIFYMANAGER:

	SaveRegistSaveData();
	return nRet;
}


int CATPDataBase::DelManager(IN struATPDataBaseManager *pATPDBSManager)
{
	int nRet = 0;
	if (NULL == m_pATPDBSManager)
	{
		nRet = NOTINIT;
		goto END__DELMANAGER;

	}
	//确保操作的是同一个内存块
	if (m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nSerialNumber != 1/*不能删除自己*/ && 
		m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nSerialNumber == pATPDBSManager->nSerialNumber &&
		0 == strcmp(m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].szID,pATPDBSManager->szID))
	{
		m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nStatus		= pATPDBSManager->nStatus;
		m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nDeleteMark	= TRUE;
	}
	else
	{
		nRet = ZERORECORD;
		goto END__DELMANAGER;
	}

END__DELMANAGER:

	SaveRegistSaveData();

	return nRet;
}


int CATPDataBase::QueryManager(IN char *pAccount,OUT struATPDataBaseManager **ppATPDBSManager)
{
	int nRet = 0;
	if (NULL == m_pATPDBSManager)
	{
		return NOTINIT;
	}
	if (m_nUsedATPDBSManagerItem<=0)
	{
		return ZERORECORD;
	}

	int i=0;bool bMark=FALSE;
// 	if (0==strcmp("CHHNetFrameProcessor_ATPManagerServer",pAccount))
// 	{
// 		bMark = TRUE;
// 		goto END_QUERYMANAGER;
// 	}

	for (;i<m_nUsedATPDBSManagerItem;i++)
	{
		if (0==strcmp(m_pATPDBSManager[i].szID,pAccount) && 
			FALSE == m_pATPDBSManager[i].nDeleteMark)
		{
			if (1==m_pATPDBSManager[i].nSerialNumber)
			{
				bMark = TRUE;
			}
			
			break;
		}
	}


//END_QUERYMANAGER:

	//超级管理员
	if (bMark)
	{
		*ppATPDBSManager = new struATPDataBaseManager[m_nUsedATPDBSManagerItem];
		if (NULL == *ppATPDBSManager)
		{
			return NEWERROR;
		}
		memcpy((char *)*ppATPDBSManager,(char *)m_pATPDBSManager,m_nUsedATPDBSManagerItem*sizeof struATPDataBaseManager);
		nRet = m_nUsedATPDBSManagerItem;
	}
	else
	{
		*ppATPDBSManager = new struATPDataBaseManager[1];
		if (NULL == *ppATPDBSManager)
		{
			return NEWERROR;
		}
		memcpy((char *)*ppATPDBSManager,(char *)&m_pATPDBSManager[i],sizeof struATPDataBaseManager);
		nRet = 1;
	}
	
	//释放  *ppATPDBSManager  在外面
	return nRet;
}


//////////////////////////////////////////////////////////////////////////
int CATPDataBase::AddServerGroup(IN struATPDataBaseServerGroup *pATPDBSServerGroup,OUT struATPDataBaseServerGroup *pOutData)
{
	int nRet = 0;
	CTime t = CTime::GetCurrentTime();
	if (NULL == m_pATPDBSServerGroup)
	{
		nRet = NOTINIT;
		goto END__ADDSERVERGROUP;
		
	}
	//查看内存使用情况
	//***

	/**
	判断是否已经存在相同数据
	*/
	for (int i=0;i<m_nUsedATPDBSServerGroupItem;i++)
	{
		//服务器组名称
		if (0==strcmp(m_pATPDBSServerGroup[i].szName,pATPDBSServerGroup->szName) && 
			FALSE == m_pATPDBSServerGroup[i].nDeleteMark)
		{
			if (m_pATPDBSServerGroup[i].nDeleteMark == FALSE)
			{
				nRet = EXISTDATA;
				goto END__ADDSERVERGROUP;
			}
			
		}
	}
	//////////////////////////////////////////////////////////////////////////
	memcpy((char *)&m_pATPDBSServerGroup[m_nUsedATPDBSServerGroupItem],(char *)pATPDBSServerGroup,sizeof struATPDataBaseServerGroup);
	
	m_pATPDBSServerGroup[m_nUsedATPDBSServerGroupItem].nCreateDate = t.GetYear()*10000+t.GetMonth()*100+t.GetDay();
	m_pATPDBSServerGroup[m_nUsedATPDBSServerGroupItem].nCreateTime = t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();
	m_pATPDBSServerGroup[m_nUsedATPDBSServerGroupItem].nDeleteMark = 0;
	
	
	
	
	
	//序号递增
	if (m_nUsedATPDBSServerGroupItem == 0)
	{
		m_pATPDBSServerGroup[m_nUsedATPDBSServerGroupItem].nID = 1;
	} 
	else
	{
		m_pATPDBSServerGroup[m_nUsedATPDBSServerGroupItem].nID = m_pATPDBSServerGroup[m_nUsedATPDBSServerGroupItem-1].nID + 1;
	}
	//使用标记+1
	m_nUsedATPDBSServerGroupItem += 1;

// 	if (NULL == pOutData)
// 	{
// 		nRet = ZERORECORD;
// 		goto END__ADDSERVERGROUP;
// 		
// 	}
	memcpy((char *)pOutData,(char *)&m_pATPDBSServerGroup[m_nUsedATPDBSServerGroupItem-1],sizeof struATPDataBaseServerGroup);
	
END__ADDSERVERGROUP:
	
	SaveRegistSaveData();
	return nRet;
}


int CATPDataBase::ModifyServerGroup(IN struATPDataBaseServerGroup *pATPDBSServerGroup)
{
	int nRet = 0;
	if (NULL == m_pATPDBSServerGroup)
	{
		nRet = NOTINIT;
		goto END__MODIFYSERVERGROUP;
	}



	/**
	判断是否已经存在相同数据
	*/
	for (int i=0;i<m_nUsedATPDBSServerGroupItem;i++)
	{
		if (m_pATPDBSServerGroup[i].nID != pATPDBSServerGroup->nID)
		{
			//服务器组名称
			if (0==strcmp(m_pATPDBSServerGroup[i].szName,pATPDBSServerGroup->szName))
			{
				if (m_pATPDBSServerGroup[i].nDeleteMark==FALSE)
				{
					nRet = EXISTDATA;
					goto END__MODIFYSERVERGROUP;
				}
				
			}
		}
		
	}
	//////////////////////////////////////////////////////////////////////////

	//确保操作的是同一个内存块
	if (m_pATPDBSServerGroup[pATPDBSServerGroup->nID-1].nID == pATPDBSServerGroup->nID)
	{
		m_pATPDBSServerGroup[pATPDBSServerGroup->nID-1].nParentID = pATPDBSServerGroup->nParentID;			//	父组ID
		strcpy(m_pATPDBSServerGroup[pATPDBSServerGroup->nID-1].szName,pATPDBSServerGroup->szName);			//	组名
		memcpy(m_pATPDBSServerGroup[pATPDBSServerGroup->nID-1].szExplain,pATPDBSServerGroup->szExplain,128);		//	说明
	}
	else
	{
		nRet = ZERORECORD;
	}
END__MODIFYSERVERGROUP:

	SaveRegistSaveData();
	return nRet;
}


int CATPDataBase::DelServerGroup(IN struATPDataBaseServerGroup *pATPDBSServerGroup)
{
	int nRet = 0;
	if (NULL == m_pATPDBSServerGroup)
	{
		nRet = NOTINIT;
		goto END__DELSERVERGROUP;
		
	}
	//确保操作的是同一个内存块
	if (m_pATPDBSServerGroup[pATPDBSServerGroup->nID-1].nID == pATPDBSServerGroup->nID)
	{
		m_pATPDBSServerGroup[pATPDBSServerGroup->nID-1].nDeleteMark	= TRUE;
	}
	else
	{
		nRet = ZERORECORD;
	}

END__DELSERVERGROUP:


	SaveRegistSaveData();
	return nRet;
}


int CATPDataBase::QueryServerGroup(OUT struATPDataBaseServerGroup **ppATPDBSServerGroup)
{

	if (NULL == m_pATPDBSServerGroup)
	{
		return NOTINIT;
	}
	if (m_nUsedATPDBSServerGroupItem<=0)
	{
		return ZERORECORD;
	}
	*ppATPDBSServerGroup = new struATPDataBaseServerGroup[m_nUsedATPDBSServerGroupItem];
	if (NULL == *ppATPDBSServerGroup)
	{
		return NEWERROR;
	}
	memcpy((char *)*ppATPDBSServerGroup,(char *)m_pATPDBSServerGroup,m_nUsedATPDBSServerGroupItem*sizeof struATPDataBaseServerGroup);
	//释放  *ppATPDBSServerGroup  在外面
	return m_nUsedATPDBSServerGroupItem;
}


//////////////////////////////////////////////////////////////////////////
int CATPDataBase::AddServer(IN struATPDataBaseServer *pATPDBSServer,OUT struATPDataBaseServer *pOutData)
{
	int nRet = 0;
	CTime t = CTime::GetCurrentTime();
	if (NULL == m_pATPDBSServer)
	{
		nRet = NOTINIT;
		goto END__ADDSERVER;
	}
	//查看内存使用情况
	//***
	



	/**
	判断是否已经存在相同数据
	*/

	for (int i=0;i<m_nUsedATPDBSServerItem;i++)
	{
		//IP 或 服务器名字 都不能重复
		if ((0 == strcmp(m_pATPDBSServer[i].szIP,pATPDBSServer->szIP) || 0 == strcmp(m_pATPDBSServer[i].szName,pATPDBSServer->szName)) && 
			FALSE == m_pATPDBSServer[i].nDeleteMark)
		{
			if (m_pATPDBSServer[i].nDeleteMark == FALSE)
			{
				nRet = EXISTDATA;
				goto END__ADDSERVER;
			}
			
		}
	}

	//////////////////////////////////////////////////////////////////////////
	memcpy((char *)&m_pATPDBSServer[m_nUsedATPDBSServerItem],(char *)pATPDBSServer,sizeof struATPDataBaseServer);
	
	m_pATPDBSServer[m_nUsedATPDBSServerItem].nCreateDate = t.GetYear()*10000+t.GetMonth()*100+t.GetDay();
	m_pATPDBSServer[m_nUsedATPDBSServerItem].nCreateTime = t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();
	m_pATPDBSServer[m_nUsedATPDBSServerItem].nDeleteMark = 0;
	m_pATPDBSServer[m_nUsedATPDBSServerItem].nIPType = 4;
	
	//序号递增
	if (m_nUsedATPDBSServerItem == 0)
	{
		m_pATPDBSServer[m_nUsedATPDBSServerItem].nID = 1;
	} 
	else
	{
		m_pATPDBSServer[m_nUsedATPDBSServerItem].nID = m_pATPDBSServer[m_nUsedATPDBSServerItem-1].nID + 1;
	}
	//使用标记+1
	m_nUsedATPDBSServerItem += 1;

// 	if (NULL == pOutData)
// 	{
// 		nRet = ZERORECORD;
// 		goto END__ADDSERVER;
// 		
// 	}
	memcpy((char *)pOutData,(char *)&m_pATPDBSServer[m_nUsedATPDBSServerItem-1],sizeof struATPDataBaseServer);
	
END__ADDSERVER:
	
	SaveRegistSaveData();
	return nRet;
}


int CATPDataBase::ModifyServer(IN struATPDataBaseServer *pATPDBSServer)
{
	int nRet = 0;
	if (NULL == m_pATPDBSServer)
	{
		nRet = NOTINIT;
		goto END__MODIFYSERVER;
		
	}




	/**
	判断是否已经存在相同数据
	*/

	for (int i=0;i<m_nUsedATPDBSServerItem;i++)
	{
		if (m_pATPDBSServer[i].nID != pATPDBSServer->nID)
		{		
			//IP 或 服务器名字 都不能重复
			if (0 == strcmp(m_pATPDBSServer[i].szIP,pATPDBSServer->szIP) || 0 == strcmp(m_pATPDBSServer[i].szName,pATPDBSServer->szName))
			{
				if (m_pATPDBSServer[i].nDeleteMark==FALSE)
				{
					nRet = EXISTDATA;
					goto END__MODIFYSERVER;
				}
				
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//确保操作的是同一个内存块
	if (m_pATPDBSServer[pATPDBSServer->nID-1].nID == pATPDBSServer->nID)
	{
		//memcpy((char *)&m_pATPDBSServer[pATPDBSServer->nID-1],(char *)pATPDBSServer,sizeof struATPDataBaseServer);


		//m_pATPDBSServer[pATPDBSServer->nID-1].nID;						//	服务器ID 自动生成 唯一
		strcpy(m_pATPDBSServer[pATPDBSServer->nID-1].szName,pATPDBSServer->szName);					//	服务器名
		strcpy(m_pATPDBSServer[pATPDBSServer->nID-1].szIP,pATPDBSServer->szIP);					//	服务器IP
		m_pATPDBSServer[pATPDBSServer->nID-1].nIPType		= pATPDBSServer->nIPType;					//	4,6
		m_pATPDBSServer[pATPDBSServer->nID-1].nPort			= pATPDBSServer->nPort;						//	服务器端口号
		m_pATPDBSServer[pATPDBSServer->nID-1].nGroupID		= pATPDBSServer->nGroupID;					//	服务器组
		m_pATPDBSServer[pATPDBSServer->nID-1].nAlloc		= pATPDBSServer->nAlloc;						//	分配原则
		//m_pATPDBSServer[pATPDBSServer->nID-1].nCreateDate	= pATPDBSServer->nCreateDate;				//	创建日期
		//m_pATPDBSServer[pATPDBSServer->nID-1].nCreateTime	= pATPDBSServer->nCreateTime;				//	创建时间
		//m_pATPDBSServer[pATPDBSServer->nID-1].nDeleteMark;				//	删除标记
	}
	else
	{
		nRet = ZERORECORD;
	}
END__MODIFYSERVER:


	SaveRegistSaveData();
	return nRet;
}


int CATPDataBase::DelServer(struATPDataBaseServer *pATPDBSServer)
{
	int nRet = 0;
	if (NULL == m_pATPDBSServer)
	{
		nRet = NEWERROR;
		goto END__DELSERVER;
		
	}
	//确保操作的是同一个内存块
	if (m_pATPDBSServer[pATPDBSServer->nID-1].nID == pATPDBSServer->nID)
	{
		m_pATPDBSServer[pATPDBSServer->nID-1].nDeleteMark	= TRUE;
	}
	else
	{
		nRet = ZERORECORD;
	}


END__DELSERVER:

	SaveRegistSaveData();
	return nRet;
}


int CATPDataBase::QueryServer(struATPDataBaseServer_QUERY *pATPDBSServer_QUERY,OUT struATPDataBaseServer **ppATPDBSServer)
{
	if (NULL == m_pATPDBSServer)
	{
		return NOTINIT;
	}

	if (m_nUsedATPDBSServerItem<=0)
	{
		//没有记录
		return ZERORECORD;
	}

	*ppATPDBSServer = new struATPDataBaseServer[m_nUsedATPDBSServerItem];
	if (NULL == *ppATPDBSServer)
	{
		return NEWERROR;
	}

	//查找
	int i=0,nItems=0/*符合记录条数*/;
	for (;i<m_nUsedATPDBSServerItem;i++)
	{

		if (pATPDBSServer_QUERY->nGroupID == m_pATPDBSServer[i].nGroupID || pATPDBSServer_QUERY->nGroupID == 0)
		{
			memcpy((char *)&(*ppATPDBSServer)[nItems],&m_pATPDBSServer[i],sizeof struATPDataBaseServer);
			nItems++;
		}

	}
	if (nItems==0)
	{
		//没有一条纪录，释放已经分配的内存
		delete *ppATPDBSServer;
		*ppATPDBSServer = NULL;
	}

	//释放  *ppATPDBSServerGroup  在外面
	return nItems;
}

int CATPDataBase::TranslationPermission(int nAccountType,int nPermissionType)
{
	switch(nPermissionType)
	{
	case ID_ATPMANAGE_ADDALGORITHM		:
	case ID_ATPMANAGE_ADDALGORITHMGROUP		://添加算法或算法组
		{
			return MANAGER_ADDALGO;
		}
		break;
	case ID_ATPMANAGE_DELETEALGORITHM		:
	case ID_ATPMANAGE_DELETEALGORITHMGROUP		://删除算法或算法组
		{
			return MANAGER_DELALGO;
		}
		break;
	case ID_ATPMANAGE_MODIFYALGORITHMINFO		:
	case ID_ATPMANAGE_MODIFYALGORITHMGROUP		://修改算法或算法组
		{
			return MANAGER_MODIFYALGO;
		}
		break;
	case ID_ATPMANAGE_QUERYALGORITHMINFO		:
	case ID_ATPMANAGE_QUERYALGORITHMGROUPINFO		://查询算法或算法组
		{
			return MANAGER_VIEWALGO;
		}
		break;
	case ID_ATPMANAGE_ADDUSER		:
	case ID_ATPMANAGE_ADDUSERGROUP		://添加用户或用户组
		{
			return MANAGER_ADDUSER;
		}
		break;
	case ID_ATPMANAGE_DELETEUSER		:
	case ID_ATPMANAGE_DELETEUSERGROUP		://删除用户或用户组
		{
			return MANAGER_DELUSER;
		}
		break;
	case ID_ATPMANAGE_MODIFYUSER		:
	case ID_ATPMANAGE_MODIFYUSERGROUP		://修改用户或用户组
		{
			return MANAGER_MODIFYUSER;
		}
		break;
	case ID_ATPMANAGE_QUERYUSERINFO		:
	case ID_ATPMANAGE_QUERYUSERGROUPINFO		://查询用户或用户组
		{
			return MANAGER_VIEWUSER;
		}
		break;
	default:
		break;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////
int CATPDataBase::IsHavePermission(int nAccountType,const char *pAccountID,int nPermissionType)
{
	int nRet = 0;
	int nMark = 0;
	switch(nAccountType)
	{
	case ATP_ADMINISTRATOR		:
	case ATP_MANAGER:
		{
			int *pPermission = NULL;
			GetManagerPermission(pAccountID,&pPermission);
			if (pPermission)
			{
				int i = 0;
				for (;i<32 && pPermission[i]>0;i++)
				{
					if (pPermission[i] == TranslationPermission(nAccountType,nPermissionType))
					{
						//拥有该权限
						nMark = 1;
						break;
					}
				}
				if (nMark)
				{
					nRet = 0;
				} 
				else
				{
					nRet = -1;
				}

				delete []pPermission;
				return nRet;
			}

		}
		break;
	case ATP_USER:
		{
			int *pPermission = NULL;
			GetUserPermission(pAccountID,&pPermission);
			if (pPermission)
			{
				int i = 0;
				for (;i<32 && pPermission[i]>0;i++)
				{
					if (pPermission[i] == nPermissionType)
					{
						//拥有该权限
						nMark = 1;
						break;
					}
				}
				if (nMark)
				{
					nRet = 0;
				} 
				else
				{
					nRet = -1;
				}

				delete []pPermission;
				return nRet;
			}

		}
		break;
	default:
		return -1;
		break;
	}
	return nRet;
}


int CATPDataBase::GetManagerPermission(const char *AccountID,OUT int **ppPermission)
{
	int i =0;
	for (;i<m_nUsedATPDBSManagerItem;i++)
	{
		if (0 == strcmp(AccountID,m_pATPDBSManager[i].szID) && m_pATPDBSManager[i].nDeleteMark == FALSE)
		{
			*ppPermission = new int[32];
			if (NULL == *ppPermission)
			{
				return -1;
			}

			memcpy(*ppPermission,m_pATPDBSManager[i].nPermissionIDs,sizeof(int)*32);
			break;
		}
	}

	return 0;
}
int CATPDataBase::GetUserPermission(const char *AccountID,OUT int **ppPermission)
{
	int i =0;
	for (;i<m_nUsedATPDBSUserItem;i++)
	{
		if (0 == strcmp(AccountID,m_pATPDBSUser[i].szUserID))
		{
			*ppPermission = new int[32];
			if (NULL == *ppPermission)
			{
				return -1;
			}

			memcpy(*ppPermission,m_pATPDBSUser[i].nPermissionIDs,sizeof(int)*32);
			break;
		}
	}
	return 0;
}

int CATPDataBase::QueryPermission(struATPDataBasePermission **pATPDBSPermission)
{
	if (NULL == m_pATPDBSPermission)
	{
		return NOTINIT;
	}
	if (m_nUsedATPDBSPermissionItem<=0)
	{
		return ZERORECORD;
	}
	*pATPDBSPermission = new struATPDataBasePermission[m_nUsedATPDBSPermissionItem];
	if (NULL == *pATPDBSPermission)
	{
		return NEWERROR;
	}
	memcpy((char *)*pATPDBSPermission,(char *)m_pATPDBSPermission,m_nUsedATPDBSPermissionItem*sizeof struATPDataBasePermission);
	//释放  *ppATPDBSServerGroup  在外面
	return m_nUsedATPDBSPermissionItem;
}


//////////////////////////////////////////////////////////////////////////
int CATPDataBase::AddUserGroup(IN struATPDataBaseUserGroup *pATPDBSUserGroup,OUT struATPDataBaseUserGroup *pOutData)
{
	int nRet = 0;

	if (NULL == m_pATPDBSUserGroup)
	{
		nRet = NOTINIT;
		goto END__ADDUSERGROUP;
		
	}
	//判断内存是否够用
	//***


	/**
	判断是否已经存在相同数据
	*/
	for (int i=0;i<m_nUsedATPDBSUserGroupItem;i++)
	{
		//同一管理员下不能有相同的
		if (0==strcmp(m_pATPDBSUserGroup[i].szManagerID,pATPDBSUserGroup->szManagerID) && 
			0==strcmp(m_pATPDBSUserGroup[i].szName,pATPDBSUserGroup->szName) && 
			FALSE == m_pATPDBSUserGroup[i].nDeleteMark)
		{
			if (m_pATPDBSUserGroup[i].nDeleteMark == FALSE)
			{
				nRet = EXISTDATA;
				goto END__ADDUSERGROUP;
			}
			
		}
	}

	//////////////////////////////////////////////////////////////////////////

	struATPDataBaseUserGroup *pATPDBSUserGroupTemp = NULL;
	pATPDBSUserGroupTemp = &m_pATPDBSUserGroup[m_nUsedATPDBSUserGroupItem];
	memcpy((char *)pATPDBSUserGroupTemp,(char *)pATPDBSUserGroup,sizeof struATPDataBaseUserGroup);
	//序号递增
	if (m_nUsedATPDBSUserGroupItem == 0)
	{
		pATPDBSUserGroupTemp->nID = 1;
	} 
	else
	{
		pATPDBSUserGroupTemp->nID = m_pATPDBSUserGroup[m_nUsedATPDBSUserGroupItem-1].nID + 1;
	}

	//算法
	pATPDBSUserGroupTemp->pAlgorithmIDs = NULL;
	if (pATPDBSUserGroup->nAlgorithmN>0)
	{
		pATPDBSUserGroupTemp->pAlgorithmIDs = new struATPAutoAlgoID[pATPDBSUserGroup->nAlgorithmN];
		if (NULL == pATPDBSUserGroupTemp->pAlgorithmIDs)
		{
			//内存NEW出错，回滚
			ZeroMemory((char *)pATPDBSUserGroupTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSERGROUP;
			
		}
		memcpy(pATPDBSUserGroupTemp->pAlgorithmIDs,pATPDBSUserGroup->pAlgorithmIDs,pATPDBSUserGroup->nAlgorithmN*sizeof struATPAutoAlgoID);

	}
	//
	//算法组
	pATPDBSUserGroupTemp->pAlgorithmGroupIDs = NULL;
	if (pATPDBSUserGroup->nAlgorithmGroupN>0)
	{
		pATPDBSUserGroupTemp->pAlgorithmGroupIDs = new struATPAutoID[pATPDBSUserGroup->nAlgorithmGroupN];
		if (NULL == pATPDBSUserGroupTemp->pAlgorithmGroupIDs)
		{
			//内存NEW出错，回滚
			delete pATPDBSUserGroupTemp->pAlgorithmIDs;
			ZeroMemory((char *)pATPDBSUserGroupTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSERGROUP;
			
		}
		memcpy(pATPDBSUserGroupTemp->pAlgorithmGroupIDs,pATPDBSUserGroup->pAlgorithmGroupIDs,pATPDBSUserGroup->nAlgorithmGroupN*sizeof struATPAutoID);
	}
	//服务器
	pATPDBSUserGroupTemp->pServerIDs = NULL;
	if (pATPDBSUserGroup->nServerN>0)
	{
		pATPDBSUserGroupTemp->pServerIDs = new struATPAutoID[pATPDBSUserGroup->nServerN];
		if (NULL == pATPDBSUserGroupTemp->pServerIDs)
		{
			//内存NEW出错，回滚
			delete pATPDBSUserGroupTemp->pAlgorithmIDs;
			delete pATPDBSUserGroupTemp->pServerIDs;
			ZeroMemory((char *)pATPDBSUserGroupTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSERGROUP;
			
		}
		memcpy(pATPDBSUserGroupTemp->pServerIDs,pATPDBSUserGroup->pServerIDs,pATPDBSUserGroup->nServerN*sizeof struATPAutoID);

	}
	//
	//服务器组
	pATPDBSUserGroupTemp->pServerGroupIDs = NULL;
	if (pATPDBSUserGroup->nServerGroupN>0)
	{
		pATPDBSUserGroupTemp->pServerGroupIDs = new struATPAutoID[pATPDBSUserGroup->nServerGroupN];
		if (NULL == pATPDBSUserGroupTemp->pServerGroupIDs)
		{
			//内存NEW出错，回滚
			delete pATPDBSUserGroupTemp->pAlgorithmIDs;
			delete pATPDBSUserGroupTemp->pServerIDs;
			delete pATPDBSUserGroupTemp->pServerGroupIDs;
			ZeroMemory((char *)pATPDBSUserGroupTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSERGROUP;
			
		}
		memcpy(pATPDBSUserGroupTemp->pServerGroupIDs,pATPDBSUserGroup->pServerGroupIDs,pATPDBSUserGroup->nServerGroupN*sizeof struATPAutoID);

	}
	//使用标记+1
	m_nUsedATPDBSUserGroupItem += 1;

// 	if (NULL == pOutData)
// 	{
// 		nRet = ZERORECORD;
// 		goto END__ADDUSERGROUP;
// 		
// 	}
	memcpy((char *)pOutData,(char *)&m_pATPDBSUserGroup[m_nUsedATPDBSUserGroupItem-1],sizeof struATPDataBaseUserGroup);

END__ADDUSERGROUP:

	SaveRegistSaveData();
	return nRet;
}

int CATPDataBase::ModifyUserGroup(IN struATPDataBaseUserGroup *pATPDBSUserGroup)
{
	int nRet = 0;
	struATPDataBaseUserGroup _ATPDBSUserGroupTemp = {0};
	if (NULL == m_pATPDBSUserGroup)
	{
		nRet = NOTINIT;
		goto END__MODIFYUSERGROUP;
		
	}


	/**
	判断是否已经存在相同数据
	*/
	for (int i=0;i<m_nUsedATPDBSUserGroupItem;i++)
	{
		if (m_pATPDBSUserGroup[i].nID != pATPDBSUserGroup->nID)
		{
			//同一管理员下不能有相同的
			if (0==strcmp(m_pATPDBSUserGroup[i].szManagerID,pATPDBSUserGroup->szManagerID) && 0==strcmp(m_pATPDBSUserGroup[i].szName,pATPDBSUserGroup->szName))
			{
				if (m_pATPDBSUserGroup[i].nDeleteMark == FALSE)
				{
					nRet = EXISTDATA;
					goto END__MODIFYUSERGROUP;
				}
				
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

	//确保操作的是同一个内存块
	if (m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].nID == pATPDBSUserGroup->nID)
	{
		//把数据copy到临时堆内存
		memcpy((char *)&_ATPDBSUserGroupTemp,(char *)pATPDBSUserGroup,sizeof struATPDataBaseUserGroup);
		strcpy(_ATPDBSUserGroupTemp.szManagerID,m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].szManagerID);
		_ATPDBSUserGroupTemp.nCreateDate = m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].nCreateDate;
		_ATPDBSUserGroupTemp.nCreateTime = m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].nCreateTime;
		_ATPDBSUserGroupTemp.nDeleteMark = m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].nDeleteMark;
		



		//算法
		if (pATPDBSUserGroup->nAlgorithmN>0)
		{
			_ATPDBSUserGroupTemp.pAlgorithmIDs = NULL;
			_ATPDBSUserGroupTemp.pAlgorithmIDs = new struATPAutoAlgoID[pATPDBSUserGroup->nAlgorithmN];
			if (NULL == _ATPDBSUserGroupTemp.pAlgorithmIDs)
			{
				//内存NEW出错
				nRet = NEWERROR;
				goto END__MODIFYUSERGROUP;
				
			}
			memcpy(_ATPDBSUserGroupTemp.pAlgorithmIDs,pATPDBSUserGroup->pAlgorithmIDs,pATPDBSUserGroup->nAlgorithmN*sizeof struATPAutoAlgoID);
		}

		if (pATPDBSUserGroup->nAlgorithmGroupN>0)
		{
			//算法组
			_ATPDBSUserGroupTemp.pAlgorithmGroupIDs = NULL;
			_ATPDBSUserGroupTemp.pAlgorithmGroupIDs = new struATPAutoID[pATPDBSUserGroup->nAlgorithmGroupN];
			if (NULL == _ATPDBSUserGroupTemp.pAlgorithmGroupIDs)
			{
				//内存NEW出错
				delete _ATPDBSUserGroupTemp.pAlgorithmIDs;
				nRet = NEWERROR;
				goto END__MODIFYUSERGROUP;
				
			}
			memcpy(_ATPDBSUserGroupTemp.pAlgorithmGroupIDs,pATPDBSUserGroup->pAlgorithmGroupIDs,pATPDBSUserGroup->nAlgorithmGroupN*sizeof struATPAutoID);

		}

		if (_ATPDBSUserGroupTemp.nServerN>0)
		{
			//服务器
			_ATPDBSUserGroupTemp.pServerIDs = NULL;
			_ATPDBSUserGroupTemp.pServerIDs = new struATPAutoID[_ATPDBSUserGroupTemp.nServerN];
			if (NULL == _ATPDBSUserGroupTemp.pServerIDs)
			{
				//NEW出错
				delete _ATPDBSUserGroupTemp.pAlgorithmIDs;
				delete _ATPDBSUserGroupTemp.pAlgorithmGroupIDs;
				nRet = NEWERROR;
				goto END__MODIFYUSERGROUP;
				
			}
			memcpy((char *)_ATPDBSUserGroupTemp.pServerIDs,(char *)pATPDBSUserGroup->pServerIDs,_ATPDBSUserGroupTemp.nServerN*sizeof struATPAutoID);


		}

		if (_ATPDBSUserGroupTemp.nServerGroupN>0)
		{
			//服务器组
			_ATPDBSUserGroupTemp.pServerGroupIDs = NULL;
			_ATPDBSUserGroupTemp.pServerGroupIDs = new struATPAutoID[_ATPDBSUserGroupTemp.nServerGroupN];
			if (NULL == _ATPDBSUserGroupTemp.pServerGroupIDs)
			{
				//NEW出错
				delete _ATPDBSUserGroupTemp.pAlgorithmIDs;
				delete _ATPDBSUserGroupTemp.pAlgorithmGroupIDs;
				delete _ATPDBSUserGroupTemp.pServerGroupIDs;
				nRet = NEWERROR;
				goto END__MODIFYUSERGROUP;
				
			}
			memcpy((char *)_ATPDBSUserGroupTemp.pServerGroupIDs,(char *)pATPDBSUserGroup->pServerGroupIDs,_ATPDBSUserGroupTemp.nServerGroupN*sizeof struATPAutoID);
		}



		//删除之前所指向的指针
		if (m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].pAlgorithmIDs)
		{
			delete []m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].pAlgorithmIDs;m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].pAlgorithmIDs = NULL;
		}
		if (m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].pServerGroupIDs)
		{
			delete []m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].pServerGroupIDs;m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].pServerGroupIDs = NULL;
		}
		if (m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].pServerIDs)
		{
			delete []m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].pServerIDs;m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].pServerIDs = NULL;
		}
		if (m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].pServerGroupIDs)
		{
			delete []m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].pServerGroupIDs;m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].pServerGroupIDs = NULL;
		}



		//
		memcpy((char *)&m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1],(char *)&_ATPDBSUserGroupTemp,sizeof struATPDataBaseUserGroup);


	}
	else
	{
		nRet = ZERORECORD;
	}
	AfxCheckMemory();
END__MODIFYUSERGROUP:

	SaveRegistSaveData();
	return nRet;
}

int CATPDataBase::DelUserGroup(IN struATPDataBaseUserGroup *pATPDBSUserGroup)
{
	int nRet = 0;
	if (NULL == m_pATPDBSUserGroup)
	{
		nRet = NOTINIT;
		goto END__DELUSERGROUP;
		
	}
	//确保操作的是同一个内存块
	if (m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].nID == pATPDBSUserGroup->nID )
	{
		m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].nDeleteMark	= TRUE;
	}
	else
	{
		nRet = ZERORECORD;
		goto END__DELUSERGROUP;
	}

END__DELUSERGROUP:

	SaveRegistSaveData();
	return nRet;
}


int CATPDataBase::QueryUserGroup(IN char *pAccount,OUT struATPDataBaseUserGroup **ppATPDBSUserGroup)
{
	if (m_nUsedATPDBSUserGroupItem<=0)
	{
		return ZERORECORD;
	}
	int i = 0;
	int nCount = 0;
	for (;i<m_nUsedATPDBSUserGroupItem;i++)
	{
		if (0==strcmp(m_pATPDBSUserGroup[i].szManagerID,pAccount))
		{
			nCount++;
		}
	}
	if (0==nCount)
	{
		return 0;
	}
	*ppATPDBSUserGroup = new struATPDataBaseUserGroup[nCount];
	if (NULL == *ppATPDBSUserGroup)
	{
		return NEWERROR;
	}
	int j=0;
	for (i=0;i<m_nUsedATPDBSUserGroupItem;i++)
	{
		if (0==strcmp(m_pATPDBSUserGroup[i].szManagerID,pAccount))
		{
			memcpy((char *)&(*ppATPDBSUserGroup)[j],(char *)&m_pATPDBSUserGroup[i],sizeof struATPDataBaseUserGroup);
			j++;
		}
	}
	
	//释放  *ppATPDBSUserGroup  在外面
	return nCount;
}


//////////////////////////////////////////////////////////////////////////
int CATPDataBase::AddUser(IN struATPDataBaseUser *pATPDBSUser,OUT struATPDataBaseUser *pOutData)
{
	int nRet = 0;
	if (NULL == m_pATPDBSUser)
	{
		nRet = NOTINIT;
		goto END__ADDUSER;
		
	}
	//判断内存是否够用
	//***

	/**
	判断是否已经存在相同数据
	*/
	for (int i=0;i<m_nUsedATPDBSUserItem;i++)
	{
		if (0==strcmp(m_pATPDBSUser[i].szManagerID,pATPDBSUser->szManagerID) && 
			0==strcmp(m_pATPDBSUser[i].szUserID,pATPDBSUser->szUserID) && 
			FALSE == m_pATPDBSUser[i].nDeleteMark)
		{
			if (m_pATPDBSUser[i].nDeleteMark)
			{
				nRet = EXISTDATA;
				goto END__ADDUSER;
			}
			
		}
	}


	//////////////////////////////////////////////////////////////////////////
	struATPDataBaseUser *pATPDBSUserTemp = NULL;
	pATPDBSUserTemp = &m_pATPDBSUser[m_nUsedATPDBSUserItem];
	memcpy((char *)pATPDBSUserTemp,(char *)pATPDBSUser,sizeof struATPDataBaseUser);
	//序号递增
	if (m_nUsedATPDBSUserItem == 0)
	{
		pATPDBSUserTemp->nSerialNumber = 1;
	} 
	else
	{
		pATPDBSUserTemp->nSerialNumber = m_pATPDBSUser[m_nUsedATPDBSUserItem-1].nSerialNumber + 1;
	}
	//资金帐号
	pATPDBSUserTemp->pATPFund = NULL;
	if (pATPDBSUser->nCanAssociateFundsAccount>0)
	{
		pATPDBSUserTemp->pATPFund = new struATPDataBaseFund[pATPDBSUser->nCanAssociateFundsAccount];
		if (NULL == pATPDBSUserTemp->pATPFund)
		{
			//内存NEW出错，回滚
			ZeroMemory((char *)pATPDBSUserTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSER;
			
		}
		memcpy(pATPDBSUserTemp->pATPFund,pATPDBSUser->pATPFund,pATPDBSUser->nCanAssociateFundsAccount*sizeof struATPDataBaseFund);
	}
	//算法
	pATPDBSUserTemp->pAlgorithmIDs = NULL;
	if (pATPDBSUser->nAlgorithmN>0)
	{
		pATPDBSUserTemp->pAlgorithmIDs = new struATPAutoAlgoID[pATPDBSUser->nAlgorithmN];
		if (NULL == pATPDBSUserTemp->pAlgorithmIDs)
		{
			//内存NEW出错，回滚
			delete pATPDBSUserTemp->pATPFund;
			ZeroMemory((char *)pATPDBSUserTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSER;
			
		}
		memcpy(pATPDBSUserTemp->pAlgorithmIDs,pATPDBSUser->pAlgorithmIDs,pATPDBSUser->nAlgorithmN*sizeof struATPAutoAlgoID);

	}
	//
	//算法组
	pATPDBSUserTemp->pAlgorithmGroupIDs = NULL;
	if (pATPDBSUser->nAlgorithmGroupN>0)
	{
		pATPDBSUserTemp->pAlgorithmGroupIDs = new struATPAutoID[pATPDBSUser->nAlgorithmGroupN];
		if (NULL == pATPDBSUserTemp->pAlgorithmGroupIDs)
		{
			//内存NEW出错，回滚
			delete pATPDBSUserTemp->pATPFund;
			delete pATPDBSUserTemp->pAlgorithmIDs;
			ZeroMemory((char *)pATPDBSUserTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSER;
			
		}
		memcpy(pATPDBSUserTemp->pAlgorithmGroupIDs,pATPDBSUser->pAlgorithmGroupIDs,pATPDBSUser->nAlgorithmGroupN*sizeof struATPAutoID);
	}
	//服务器
	pATPDBSUserTemp->pServerIDs = NULL;
	if (pATPDBSUser->nServerN>0)
	{
		pATPDBSUserTemp->pServerIDs = new struATPAutoID[pATPDBSUser->nServerN];
		if (NULL == pATPDBSUserTemp->pServerIDs)
		{
			//内存NEW出错，回滚
			delete pATPDBSUserTemp->pATPFund;
			delete pATPDBSUserTemp->pAlgorithmIDs;
			delete pATPDBSUserTemp->pServerIDs;
			ZeroMemory((char *)pATPDBSUserTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSER;
			
		}
		memcpy(pATPDBSUserTemp->pServerIDs,pATPDBSUser->pServerIDs,pATPDBSUser->nServerN*sizeof struATPAutoID);

	}
	//
	//服务器组
	pATPDBSUserTemp->pServerGroupIDs = NULL;
	if (pATPDBSUser->nServerGroupN>0)
	{
		pATPDBSUserTemp->pServerGroupIDs = new struATPAutoID[pATPDBSUser->nServerGroupN];
		if (NULL == pATPDBSUserTemp->pServerGroupIDs)
		{
			//内存NEW出错，回滚
			delete pATPDBSUserTemp->pATPFund;
			delete pATPDBSUserTemp->pAlgorithmIDs;
			delete pATPDBSUserTemp->pServerIDs;
			delete pATPDBSUserTemp->pServerGroupIDs;
			ZeroMemory((char *)pATPDBSUserTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSER;
		}
		memcpy(pATPDBSUserTemp->pServerGroupIDs,pATPDBSUser->pServerGroupIDs,pATPDBSUser->nServerGroupN*sizeof struATPAutoID);

	}
	//使用标记+1
	m_nUsedATPDBSUserItem += 1;

// 	if (NULL == pOutData)
// 	{
// 		nRet = ZERORECORD;
// 		goto END__ADDUSER;
// 		
// 	}
	memcpy((char *)pOutData,(char *)&m_pATPDBSUser[m_nUsedATPDBSUserItem-1],sizeof struATPDataBaseUser);

END__ADDUSER:

	SaveRegistSaveData();
	return nRet;
}


int CATPDataBase::ModifyUser(IN struATPDataBaseUser *pATPDBSUser)
{
	int nRet = 0;
	struATPDataBaseUser _ATPDBSUserTemp = {0};
	if (NULL == m_pATPDBSUser)
	{
		nRet = NOTINIT;
		goto END__MODIFYUSER;
		
	}


	/**
	判断是否已经存在相同数据
	*/
	for (int i=0;i<m_nUsedATPDBSUserItem;i++)
	{
		if (m_pATPDBSUser[i].nSerialNumber != pATPDBSUser->nSerialNumber)
		{
			if (0==strcmp(m_pATPDBSUser[i].szManagerID,pATPDBSUser->szManagerID) && 0==strcmp(m_pATPDBSUser[i].szUserID,pATPDBSUser->szUserID))
			{
				if (m_pATPDBSUser[i].nDeleteMark == FALSE)
				{
					nRet = EXISTDATA;
					goto END__MODIFYUSER;
				}				
			}
		}
	}


	//////////////////////////////////////////////////////////////////////////
	//确保操作的是同一个内存块
	if (m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nSerialNumber == pATPDBSUser->nSerialNumber)
	{
		//把数据copy到临时堆内存
		memcpy((char *)&_ATPDBSUserTemp,(char *)pATPDBSUser,sizeof struATPDataBaseUser);
		strcpy(_ATPDBSUserTemp.szManagerID,m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].szManagerID);
		_ATPDBSUserTemp.nCreateDate = m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nCreateDate;
		_ATPDBSUserTemp.nCreateTime = m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nCreateTime;
		_ATPDBSUserTemp.nLastDate = m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nLastDate;
		_ATPDBSUserTemp.nLastTime = m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nLastTime;
		_ATPDBSUserTemp.nDeleteMark = m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nDeleteMark;

		//资金帐号
		_ATPDBSUserTemp.pATPFund = NULL;
		if (pATPDBSUser->nCanAssociateFundsAccount>0)
		{
			_ATPDBSUserTemp.pATPFund = new struATPDataBaseFund[pATPDBSUser->nCanAssociateFundsAccount];
			if (NULL == _ATPDBSUserTemp.pATPFund)
			{
				//内存NEW出错
				nRet = NEWERROR;
				goto END__MODIFYUSER;
				
			}
			memcpy(_ATPDBSUserTemp.pATPFund,pATPDBSUser->pATPFund,pATPDBSUser->nCanAssociateFundsAccount*sizeof struATPDataBaseFund);

		}
		//算法
		_ATPDBSUserTemp.pAlgorithmIDs = NULL;
		if (pATPDBSUser->nAlgorithmN>0)
		{
			_ATPDBSUserTemp.pAlgorithmIDs = new struATPAutoAlgoID[pATPDBSUser->nAlgorithmN];
			if (NULL == _ATPDBSUserTemp.pAlgorithmIDs)
			{
				//内存NEW出错
				delete _ATPDBSUserTemp.pATPFund;
				nRet = NEWERROR;
				goto END__MODIFYUSER;
				
			}
			memcpy(_ATPDBSUserTemp.pAlgorithmIDs,pATPDBSUser->pAlgorithmIDs,pATPDBSUser->nAlgorithmN*sizeof struATPAutoAlgoID);

		}
		//
		//算法组
		_ATPDBSUserTemp.pAlgorithmGroupIDs = NULL;
		if (pATPDBSUser->nAlgorithmGroupN>0)
		{
			_ATPDBSUserTemp.pAlgorithmGroupIDs = new struATPAutoID[pATPDBSUser->nAlgorithmGroupN];
			if (NULL == _ATPDBSUserTemp.pAlgorithmGroupIDs)
			{
				//内存NEW出错
				delete _ATPDBSUserTemp.pATPFund;
				delete _ATPDBSUserTemp.pAlgorithmIDs;
				nRet = NEWERROR;
				goto END__MODIFYUSER;
				
			}
			memcpy(_ATPDBSUserTemp.pAlgorithmGroupIDs,pATPDBSUser->pAlgorithmGroupIDs,pATPDBSUser->nAlgorithmGroupN*sizeof struATPAutoID);

		}

		//服务器
		_ATPDBSUserTemp.pServerIDs = NULL;
		if (_ATPDBSUserTemp.nServerN>0)
		{
			_ATPDBSUserTemp.pServerIDs = new struATPAutoID[_ATPDBSUserTemp.nServerN];
			if (NULL == _ATPDBSUserTemp.pServerIDs)
			{
				//NEW出错
				delete _ATPDBSUserTemp.pATPFund;
				delete _ATPDBSUserTemp.pAlgorithmIDs;
				delete _ATPDBSUserTemp.pAlgorithmGroupIDs;
				nRet = NEWERROR;
				goto END__MODIFYUSER;
				
			}
			memcpy((char *)_ATPDBSUserTemp.pServerIDs,(char *)pATPDBSUser->pServerIDs,_ATPDBSUserTemp.nServerN*sizeof struATPAutoID);

		}

		//服务器组
		_ATPDBSUserTemp.pServerGroupIDs = NULL;
		if (_ATPDBSUserTemp.nServerGroupN>0)
		{
			_ATPDBSUserTemp.pServerGroupIDs = new struATPAutoID[_ATPDBSUserTemp.nServerGroupN];
			if (NULL == _ATPDBSUserTemp.pServerGroupIDs)
			{
				//NEW出错
				delete _ATPDBSUserTemp.pATPFund;
				delete _ATPDBSUserTemp.pAlgorithmIDs;
				delete _ATPDBSUserTemp.pAlgorithmGroupIDs;
				delete _ATPDBSUserTemp.pServerGroupIDs;
				nRet = NEWERROR;
				goto END__MODIFYUSER;
			}
			memcpy((char *)_ATPDBSUserTemp.pServerGroupIDs,(char *)pATPDBSUser->pServerGroupIDs,_ATPDBSUserTemp.nServerGroupN*sizeof struATPAutoID);
		}

		//删除之前所指向的指针
		if (m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pATPFund)
		{
			delete []m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pATPFund;m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pATPFund = NULL;
		}
		
		if (m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pAlgorithmIDs)
		{
			delete []m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pAlgorithmIDs;m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pAlgorithmIDs = NULL;
		}
		
		if (m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pAlgorithmGroupIDs)
		{
			delete []m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pAlgorithmGroupIDs;m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pAlgorithmGroupIDs = NULL;
		}
		
		if (m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pServerIDs)
		{
			delete []m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pServerIDs;m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pServerIDs = NULL;
		}
		
		if (m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pServerGroupIDs)
		{
			delete []m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pServerGroupIDs;m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].pServerGroupIDs = NULL;
		}
		
		//
		memcpy((char *)&m_pATPDBSUser[pATPDBSUser->nSerialNumber-1],(char *)&_ATPDBSUserTemp,sizeof struATPDataBaseUser);
		

	}
	else
	{
		nRet = ZERORECORD;
	}

END__MODIFYUSER:

	SaveRegistSaveData();
	return nRet;

}

int CATPDataBase::DelUser(IN struATPDataBaseUser *pATPDBSUser)
{
	int nRet = 0;
	if (NULL == m_pATPDBSUser)
	{
		nRet = NOTINIT;
		goto END__DELUSER;
		
	}
	//确保操作的是同一个内存块
	if (m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nSerialNumber == pATPDBSUser->nSerialNumber &&
		0 == strcmp(m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].szUserID,pATPDBSUser->szUserID))
	{
		m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nStatus		= pATPDBSUser->nStatus;
		m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nDeleteMark	= TRUE;
	}
	else
	{
		return ZERORECORD;//删除失败
	}

END__DELUSER:

	SaveRegistSaveData();
	return nRet;
}


int CATPDataBase::QueryUser(IN struATPDataBaseUser_QUERY *pATPDBSUser_QUERY,IN char *pAccount,OUT struATPDataBaseUser **ppATPDBSUser)
{
	if (NULL == m_pATPDBSUser)
	{
		return NOTINIT;
	}

	if (m_nUsedATPDBSUserItem<=0)
	{
		//没有记录
		return ZERORECORD;
	}

	

	//查找
	int i=0,j=0,nItems=0/*符合记录条数*/;
	for (i=0;i<m_nUsedATPDBSUserItem;i++)
	{

		for (j=0;j<4;j++)
		{
			if (0==strcmp(m_pATPDBSUser[i].szManagerID,pAccount) && (pATPDBSUser_QUERY->nID == m_pATPDBSUser[i].nGroupIDs[j] || pATPDBSUser_QUERY->nID == 0))
			{
				//memcpy((char *)&(*ppATPDBSUser)[nItems],&m_pATPDBSUser[i],sizeof struATPDataBaseUser);
				nItems++;
				break;
			}
		}

	}

	if (0 == nItems)
	{
		return 0;
	}

	*ppATPDBSUser = new struATPDataBaseUser[nItems];
	if (NULL == *ppATPDBSUser)
	{
		return NEWERROR;
	}
	int k=0;
	for (i=0;i<m_nUsedATPDBSUserItem;i++)
	{

		for (j=0;j<4;j++)
		{
			if (0==strcmp(m_pATPDBSUser[i].szManagerID,pAccount) &&(pATPDBSUser_QUERY->nID == m_pATPDBSUser[i].nGroupIDs[j] || pATPDBSUser_QUERY->nID == 0))
			{
				memcpy((char *)&(*ppATPDBSUser)[k],&m_pATPDBSUser[i],sizeof struATPDataBaseUser);
				k++;
				break;
			}
		}

	}

	//释放  *ppATPDBSServerGroup  在外面
	return nItems;
}


//////////////////////////////////////////////////////////////////////////
int CATPDataBase::AddAlgorithmGroup(IN struATPDataBaseAlgorithmGroup *pATPDBSAlgorithmGroup,OUT struATPDataBaseAlgorithmGroup *pOutData)
{
	int nRet = 0;
	CTime t = CTime::GetCurrentTime();
	if (NULL == m_pATPDBSAlgorithmGroup)
	{
		nRet = NOTINIT;
		goto END__ADDALGORITHMGROUP;
		
	}
	//查看内存使用情况
	//***

	/**
	判断是否已经存在相同数据
	*/
	for (int i=0;i<m_nUsedATPDBSAlgorithmGroupItem;i++)
	{
		if (0==strcmp(m_pATPDBSAlgorithmGroup[i].szManagerID,pATPDBSAlgorithmGroup->szManagerID) && 
			0==strcmp(m_pATPDBSAlgorithmGroup[i].szName,pATPDBSAlgorithmGroup->szName) && 
			FALSE == m_pATPDBSAlgorithmGroup[i].nDeleteMark)
		{
			if (m_pATPDBSAlgorithmGroup[i].nDeleteMark =- FALSE)
			{
				nRet = EXISTDATA;
				goto END__ADDALGORITHMGROUP;
			}
			
		}
	}
	//////////////////////////////////////////////////////////////////////////
	memcpy((char *)&m_pATPDBSAlgorithmGroup[m_nUsedATPDBSAlgorithmGroupItem],(char *)pATPDBSAlgorithmGroup,sizeof struATPDataBaseAlgorithmGroup);
	
	m_pATPDBSAlgorithmGroup[m_nUsedATPDBSAlgorithmGroupItem].nCreateDate = t.GetYear()*10000+t.GetMonth()*100+t.GetDay();
	m_pATPDBSAlgorithmGroup[m_nUsedATPDBSAlgorithmGroupItem].nCreateTime = t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();
	m_pATPDBSAlgorithmGroup[m_nUsedATPDBSAlgorithmGroupItem].nDeleteMark = 0;
	//序号递增
	if (m_nUsedATPDBSAlgorithmGroupItem == 0)
	{
		m_pATPDBSAlgorithmGroup[m_nUsedATPDBSAlgorithmGroupItem].nID = 1;
	} 
	else
	{
		m_pATPDBSAlgorithmGroup[m_nUsedATPDBSAlgorithmGroupItem].nID = m_pATPDBSAlgorithmGroup[m_nUsedATPDBSAlgorithmGroupItem-1].nID + 1;
	}
	//使用标记+1
	m_nUsedATPDBSAlgorithmGroupItem += 1;

// 	if (NULL == pOutData)
// 	{
// 		nRet = ZERORECORD;
// 		goto END__ADDALGORITHMGROUP;
// 		
// 	}
	memcpy((char *)pOutData,(char *)&m_pATPDBSAlgorithmGroup[m_nUsedATPDBSAlgorithmGroupItem-1],sizeof struATPDataBaseAlgorithmGroup);
	
END__ADDALGORITHMGROUP:
	
	SaveRegistSaveData();
	return nRet;
}


int CATPDataBase::ModifyAlgorithmGroup(IN struATPDataBaseAlgorithmGroup *pATPDBSAlgorithmGroup)
{
	int nRet = 0;
	if (NULL == m_pATPDBSAlgorithmGroup)
	{
		nRet = NOTINIT;
		goto END__MODIFYALGORITHMGROUP;
		
	}

	/**
	判断是否已经存在相同数据
	*/
	for (int i=0;i<m_nUsedATPDBSAlgorithmGroupItem;i++)
	{
		if (m_pATPDBSAlgorithmGroup[pATPDBSAlgorithmGroup->nID-1].nID != pATPDBSAlgorithmGroup->nID)
		{
		
		if (0==strcmp(m_pATPDBSAlgorithmGroup[i].szManagerID,pATPDBSAlgorithmGroup->szManagerID) && 0==strcmp(m_pATPDBSAlgorithmGroup[i].szName,pATPDBSAlgorithmGroup->szName))
		{
			if (m_pATPDBSAlgorithmGroup[i].nDeleteMark == FALSE)
			{
				nRet = EXISTDATA;
				goto END__MODIFYALGORITHMGROUP;
			}
			
		}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//确保操作的是同一个内存块
	if (m_pATPDBSAlgorithmGroup[pATPDBSAlgorithmGroup->nID-1].nID == pATPDBSAlgorithmGroup->nID)
	{
		m_pATPDBSAlgorithmGroup[pATPDBSAlgorithmGroup->nID-1].nParentID = pATPDBSAlgorithmGroup->nParentID;						//	父组ID
		strcpy(m_pATPDBSAlgorithmGroup[pATPDBSAlgorithmGroup->nID-1].szName,pATPDBSAlgorithmGroup->szName);						//	组名
	}
	else
	{
		nRet = ZERORECORD;
	}

END__MODIFYALGORITHMGROUP:

	SaveRegistSaveData();
	return nRet;
}


int CATPDataBase::DelAlgorithmGroup(IN struATPDataBaseAlgorithmGroup *pATPDBSAlgorithmGroup )
{
	int nRet = 0;
	if (NULL == m_pATPDBSAlgorithmGroup)
	{
		nRet = NOTINIT;
		goto END__DELALGORITHMGROUP;
		
	}
	//确保操作的是同一个内存块
	if (m_pATPDBSAlgorithmGroup[pATPDBSAlgorithmGroup->nID-1].nID == pATPDBSAlgorithmGroup->nID)
	{
		m_pATPDBSAlgorithmGroup[pATPDBSAlgorithmGroup->nID-1].nDeleteMark	= TRUE;
	}
	else
	{
		nRet = ZERORECORD;
	}

END__DELALGORITHMGROUP:

	SaveRegistSaveData();
	return nRet;
}


int CATPDataBase::QueryAlgorithmGroup(IN char *pAccount,OUT struATPDataBaseAlgorithmGroup **ppATPDBSAlgorithmGroup)
{
	if (NULL == m_pATPDBSAlgorithmGroup)
	{
		return NOTINIT;
	}
	if (m_nUsedATPDBSAlgorithmGroupItem<=0)
	{
		return -1;
	}
	int i=0,j=0,nCount=0;
	for (;i<m_nUsedATPDBSAlgorithmGroupItem;i++)
	{
		if (0==strcmp(m_pATPDBSAlgorithmGroup[i].szManagerID,pAccount))
		{
			nCount++;
		}
	}
	if (0==nCount)
	{
		return 0;
	}

	*ppATPDBSAlgorithmGroup = new struATPDataBaseAlgorithmGroup[nCount];
	if (NULL == *ppATPDBSAlgorithmGroup)
	{
		return NEWERROR;
	}
	//int i=0;
	for (i=0,j=0;i<m_nUsedATPDBSAlgorithmGroupItem;i++)
	{
		if (0==strcmp(m_pATPDBSAlgorithmGroup[i].szManagerID,pAccount))
		{
			memcpy((char *)&(*ppATPDBSAlgorithmGroup)[j],(char *)&m_pATPDBSAlgorithmGroup[i],sizeof struATPDataBaseAlgorithmGroup);
			j++;
		}
		
	}

	//释放  *ppATPDBSAlgorithmGroup  在外面
	return nCount;
}


//////////////////////////////////////////////////////////////////////////
//添加算法
int CATPDataBase::AddAlgorithm(IN struATPDataBaseAlgorithm *pATPDBSAlgorithm,OUT struATPDataBaseAlgorithm *pOutData,BOOL bScript)
{
	int nRet = 0;
	CTime t = CTime::GetCurrentTime();
	if (NULL == m_pATPDBSAlgorithm)
	{
		nRet = NOTINIT;
		goto END__ADDALGORITHM;
		
	}
	//判断内存是否够用
	//***


	/**
	判断是否已经存在相同数据
	*/
// 	for (int i=0;i<m_nUsedATPDBSAlgorithmItem;i++)
// 	{
// 		if (0 == strcmp(pATPDBSAlgorithm->szManagerID,m_pATPDBSAlgorithm[i].szManagerID) && 
// 			0 == strcmp(pATPDBSAlgorithm->szAlgorithmName,m_pATPDBSAlgorithm[i].szAlgorithmName) && 
// 			pATPDBSAlgorithm->nAlgoType == m_pATPDBSAlgorithm[i].nAlgoType &&
// 			FALSE == m_pATPDBSAlgorithm[i].nDeleteMark)
// 		{
// 				nRet = EXISTDATA;
// 				goto END__ADDALGORITHM;
// 			
// 		}
// 	}

	//////////////////////////////////////////////////////////////////////////
	//查询该算法ID是否存在
	for (int i=0;i<m_nUsedATPDBSAlgorithmItem;i++)
	{
		if (0 == strcmp(pATPDBSAlgorithm->szManagerID,m_pATPDBSAlgorithm[i].szManagerID) 
			/*&& pATPDBSAlgorithm->nAlgoType == m_pATPDBSAlgorithm[i].nAlgoType */
			&& pATPDBSAlgorithm->AlgorithmID == m_pATPDBSAlgorithm[i].AlgorithmID)
		{
			if (m_pATPDBSAlgorithm[i].nDeleteMark==FALSE)
			{
				nRet = EXISTGUID;
				goto END__ADDALGORITHM;
			} 
			else
			{
				nRet = max(nRet,m_pATPDBSAlgorithm[i].AlgorithVer.Ver[3]);
				nRet += 1;
			}
			
		}
	}
	if (nRet>0)
	{
		pATPDBSAlgorithm->AlgorithVer.Ver[3]=nRet;
	}
	//////////////////////////////////////////////////////////////////////////
	memcpy((char *)&m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem],(char *)pATPDBSAlgorithm,sizeof struATPDataBaseAlgorithm);
	if (!bScript)
	{
		char sz[MAX_PATH]={0};
		sprintf(sz,"\\%d.%d.%d.%d",pATPDBSAlgorithm->AlgorithVer.Ver[0],pATPDBSAlgorithm->AlgorithVer.Ver[1],pATPDBSAlgorithm->AlgorithVer.Ver[2],pATPDBSAlgorithm->AlgorithVer.Ver[3]);

		strcat(m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].szPath,sz);
	}
	
	
	m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].nCreateDate = t.GetYear()*10000+t.GetMonth()*100+t.GetDay();
	m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].nCreateTime = t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();
	m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].nDeleteMark = 0;


	//序号递增
	if (m_nUsedATPDBSAlgorithmItem == 0)
	{
		m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].nSerialNumber = 1;
	} 
	else
	{
		m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].nSerialNumber = m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem-1].nSerialNumber + 1;
	}

	//算法参数
	m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParams = NULL;
	if (pATPDBSAlgorithm->nParams>0)
	{
		m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParams = new struATPDataBaseAlgorithmParam[pATPDBSAlgorithm->nParams];
		if (NULL == m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParams)
		{
			//内存NEW出错，回滚
			ZeroMemory((char *)&m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem],0);
			nRet = NEWERROR;
			goto END__ADDALGORITHM;
		}
		memcpy(m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParams,pATPDBSAlgorithm->pATPAlgorithmParams,pATPDBSAlgorithm->nParams*sizeof struATPDataBaseAlgorithmParam);

	}


	//算法参数附加值
	m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParamsEX = NULL;
	if (pATPDBSAlgorithm->nParamsEx>0)
	{
		m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParamsEX = new struATPDataBaseAlgorithmParamEX[pATPDBSAlgorithm->nParamsEx];
		if (NULL == m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParamsEX)
		{
			//内存NEW出错，回滚
			ZeroMemory((char *)&m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem],0);
			nRet = NEWERROR;
			goto END__ADDALGORITHM;
		}
		memcpy(m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParamsEX,pATPDBSAlgorithm->pATPAlgorithmParamsEX,pATPDBSAlgorithm->nParamsEx*sizeof struATPDataBaseAlgorithmParamEX);
	}
	//使用标记+1
	m_nUsedATPDBSAlgorithmItem += 1;

	if (NULL == pOutData)
	{
		nRet = ZERORECORD;
		goto END__ADDALGORITHM;
	}
	//返回刚刚添加的算法信息
	memcpy((char *)pOutData,(char *)&m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem-1],sizeof struATPDataBaseAlgorithm);

END__ADDALGORITHM:

	SaveRegistSaveData();
	return nRet;
}

int CATPDataBase::ModifyAlgorithm(IN struATPDataBaseAlgorithm *pATPDBSAlgorithm)
{
	int nRet = 0;
	struATPDataBaseAlgorithm _ATPDBSAlgorithmTemp = {0};
	if (NULL == m_pATPDBSAlgorithm)
	{
		nRet = NOTINIT;
		goto END__MODIFYALGORITHM;
	}

	/**
	判断是否已经存在相同数据
	*/
	for (int i=0;i<m_nUsedATPDBSAlgorithmItem;i++)
	{
		if (m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].nSerialNumber != pATPDBSAlgorithm->nSerialNumber)
		{
		
		if (0 == strcmp(pATPDBSAlgorithm->szManagerID,m_pATPDBSAlgorithm[i].szManagerID) && 0 == strcmp(pATPDBSAlgorithm->szAlgorithmName,m_pATPDBSAlgorithm[i].szAlgorithmName))
		{
			if (m_pATPDBSAlgorithm[i].nDeleteMark == FALSE)
			{
				nRet = EXISTDATA;
				goto END__MODIFYALGORITHM;
			}
			
		}
		}
	}
	//确保操作的是同一个内存块
	if (m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].nSerialNumber == pATPDBSAlgorithm->nSerialNumber)
	{
		//把数据copy到临时堆内存
		memcpy((char *)&_ATPDBSAlgorithmTemp,(char *)pATPDBSAlgorithm,sizeof struATPDataBaseAlgorithm);
		/*
		//算法参数
		_ATPDBSAlgorithmTemp.pATPAlgorithmParams = NULL;
		if (_ATPDBSAlgorithmTemp.nParams>0)
		{
			_ATPDBSAlgorithmTemp.pATPAlgorithmParams = new struATPDataBaseAlgorithmParam[_ATPDBSAlgorithmTemp.nParams];
			if (NULL == _ATPDBSAlgorithmTemp.pATPAlgorithmParams)
			{
				//NEW出错

				return NEWERROR;
			}
			memcpy((char *)_ATPDBSAlgorithmTemp.pATPAlgorithmParams,(char *)pATPDBSAlgorithm->pATPAlgorithmParams,_ATPDBSAlgorithmTemp.nParams*sizeof struATPDataBaseAlgorithmParam);
		}
		//算法参数附加值
		_ATPDBSAlgorithmTemp.pATPAlgorithmParamsEX = NULL;
		if (_ATPDBSAlgorithmTemp.nParamsEx>0)
		{
			_ATPDBSAlgorithmTemp.pATPAlgorithmParamsEX = new struATPDataBaseAlgorithmParamEX[_ATPDBSAlgorithmTemp.nParamsEx];
			if (NULL == _ATPDBSAlgorithmTemp.pATPAlgorithmParamsEX)
			{
				//NEW出错

				return NEWERROR;
			}
			memcpy((char *)_ATPDBSAlgorithmTemp.pATPAlgorithmParamsEX,(char *)pATPDBSAlgorithm->pATPAlgorithmParamsEX,_ATPDBSAlgorithmTemp.nParamsEx*sizeof struATPDataBaseAlgorithmParamEX);

		}
		*/

		//删除之前所指向的指针
		//delete []m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].pATPAlgorithmParams;m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].pATPAlgorithmParams = NULL;
		//delete []m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].pATPAlgorithmParamsEX;m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].pATPAlgorithmParamsEX = NULL;

		//
		//memcpy((char *)&m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1],(char *)&_ATPDBSAlgorithmTemp,sizeof struATPDataBaseAlgorithm);

		m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].nCharge = _ATPDBSAlgorithmTemp.nCharge;
		m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].nVersionAttribute = _ATPDBSAlgorithmTemp.nVersionAttribute;
		m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].nGroupID = _ATPDBSAlgorithmTemp.nGroupID;
		strcpy(m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].szExplain,_ATPDBSAlgorithmTemp.szExplain);
		strcpy(m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].szKeyword,_ATPDBSAlgorithmTemp.szKeyword);
		strcpy(m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].szWarning,_ATPDBSAlgorithmTemp.szWarning);
		m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].nAlgoType = _ATPDBSAlgorithmTemp.nAlgoType;
		m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].nLanguageType = _ATPDBSAlgorithmTemp.nLanguageType;


	}
	else
	{
		nRet = ZERORECORD;
	}

END__MODIFYALGORITHM:

	SaveRegistSaveData();
	return nRet;
}

int CATPDataBase::DelAlgorithm(IN struATPDataBaseAlgorithm *pATPDBSAlgorithm)
{
	int nRet = 0;
	if (NULL == m_pATPDBSAlgorithm)
	{
		nRet = NOTINIT;
		goto END__DELALGORITHM;
		
	}
	//确保操作的是同一个内存块
	if (m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].nSerialNumber == pATPDBSAlgorithm->nSerialNumber )
	{
		m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].nStatus		= pATPDBSAlgorithm->nStatus;
		m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].nDeleteMark	= TRUE;
	}
	else
	{
		nRet = -1;
		goto END__DELALGORITHM;
	}

END__DELALGORITHM:

	SaveRegistSaveData();
	return nRet;
}

//查询算法信息
int CATPDataBase::QueryAlgorithm(struATPDataBaseAlgorithm_QUERY *pATPDBSAlgorithm_QUERY,IN char *pAccount,OUT struATPDataBaseAlgorithm **ppATPDBSAlgorithm)
{
	if (NULL == m_pATPDBSAlgorithm)
	{
		return NOTINIT;
	}

	if (m_nUsedATPDBSAlgorithmItem<=0)
	{
		//没有记录
		return ZERORECORD;
	}
	
	//开辟返回值的内存，m_nUsedATPDBSAlgorithmItem个
	*ppATPDBSAlgorithm = new struATPDataBaseAlgorithm[m_nUsedATPDBSAlgorithmItem];
	if (NULL == *ppATPDBSAlgorithm)
	{
		return NEWERROR;
	}
	
	int i=0,nItems=0/*符合记录条数*/;
	for (;i<m_nUsedATPDBSAlgorithmItem;i++)
	{
		//把符合条件的算法信息拷贝到返回值中
		if (0==strcmp(m_pATPDBSAlgorithm[i].szManagerID,pAccount) && (pATPDBSAlgorithm_QUERY->nID == m_pATPDBSAlgorithm[i].nGroupID || pATPDBSAlgorithm_QUERY->nID == 0))
		{
			memcpy((char *)&(*ppATPDBSAlgorithm)[nItems],&m_pATPDBSAlgorithm[i],sizeof struATPDataBaseAlgorithm);
			nItems++;
		}
	}
	if (0==nItems)
	{
		return 0;
	}

	
// 	int j=0;
// 	for (i=0;i<m_nUsedATPDBSAlgorithmItem;i++)
// 	{
// 		//把符合条件的算法信息拷贝到返回值中
// 		if (0==strcmp(m_pATPDBSAlgorithm[i].szManagerID,pAccount) && (pATPDBSAlgorithm_QUERY->nID == m_pATPDBSAlgorithm[i].nGroupID || pATPDBSAlgorithm_QUERY->nID == 0))
// 		{
// 			memcpy((char *)&(*ppATPDBSAlgorithm)[j],&m_pATPDBSAlgorithm[i],sizeof struATPDataBaseAlgorithm);
// 			j++;
// 		}
// 	}



	//释放  *ppATPDBSServerGroup  在外面
	//返回符号条件的个数
	return nItems;
}



//验证用户 
int CATPDataBase::UserLogin(IN const char *pReqData,OUT char **ppAnsData,int *pnLen)
{
	int nAtpAccept_Manager_MsgHeadSize								= sizeof AtpAccept_Manager_MsgHead;
	AtpAccept_Manager_MsgHead *pAtpAccept_Manager_MsgHead			= (AtpAccept_Manager_MsgHead *)pReqData;

	int nAtpAccept_Manager_ValidateUserSize							= sizeof AtpAccept_Manager_ValidateUser;
	AtpAccept_Manager_ValidateUser *pAtpAccept_Manager_ValidateUser = (AtpAccept_Manager_ValidateUser *)&pReqData[nAtpAccept_Manager_MsgHeadSize];
	/************************************************************************/
	/*                      查找用户数据，匹配  ，验证                                              */
	/************************************************************************/

	int nAtpAccept_Manager_ValidateUser_ResultSize					= sizeof AtpAccept_Manager_ValidateUser_Result;
	AtpAccept_Manager_ValidateUser_Result _AtpAccept_Manager_ValidateUser_Result = {0};


	int i=0,nIsExistAccount=0,nIsCorrectPwd=0;
	char *ptr = NULL;
	for (;i<m_nUsedATPDBSUserItem;i++)
	{
		if (m_pATPDBSUser[i].nDeleteMark)
		{
			continue;
		}
		//帐户
		if (0 == strcmp(pAtpAccept_Manager_ValidateUser->szUserName,m_pATPDBSUser[i].szUserID))
		{
			nIsExistAccount = 1;
			//密码
			if (0 == strcmp(pAtpAccept_Manager_ValidateUser->szUserPwd,m_pATPDBSUser[i].szPwd))
			{
				nIsCorrectPwd = 1;
				_AtpAccept_Manager_ValidateUser_Result.nUserId = m_pATPDBSUser[i].nSerialNumber;
				_AtpAccept_Manager_ValidateUser_Result.nResult = 0;
				//有效日期
				CTime t = CTime::GetCurrentTime();
				int nDate = t.GetYear()*10000+t.GetMonth()*100+t.GetDay();
				if (m_pATPDBSUser[i].nAuthorizeBeginDate>nDate || m_pATPDBSUser[i].nAuthorizeEndDate<nDate)
				{
					_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
					strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"有效期已过");
					break;
				}

				//IP v4//IP V6
				if ((int)pAtpAccept_Manager_ValidateUser->szLoginIpType == 4 || (int)pAtpAccept_Manager_ValidateUser->szLoginIpType == 6)
				{
					ptr = strstr(m_pATPDBSUser[i].szIPs,pAtpAccept_Manager_ValidateUser->szLoginIp);
					if (ptr)
					{
						//ip限制登录
						_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"该IP登录受限制");
						break;
					}
				} 
				//mac 地址
				if (strlen(pAtpAccept_Manager_ValidateUser->szMac))
				{
					ptr = strstr(m_pATPDBSUser[i].szMacMark,pAtpAccept_Manager_ValidateUser->szMac);
					if (ptr)
					{
						//mac 地址 限制登录
						_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"该MAC地址登录受限制");
						break;
					}
				}
				//硬盘序列号
				if (strlen(pAtpAccept_Manager_ValidateUser->szDiskSerialNum))
				{
					ptr = strstr(m_pATPDBSUser[i].szDiskNum,pAtpAccept_Manager_ValidateUser->szDiskSerialNum);
					if (ptr)
					{
						//硬盘序列号 限制登录
						_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"该硬盘登录受限制");
						break;
					}
				}


				//CTime t = CTime::GetCurrentTime(); 
				int nTime = t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();//235959

				//时间段
				if (m_pATPDBSUser[i].chLimitTimeMark&128)
				{
					if (m_pATPDBSUser[i].chLimitTimeMark&64)
					{
						if (m_pATPDBSUser[i].nLimitBeginTime[0]<nTime && nTime < m_pATPDBSUser[i].nLimitEndTime[0])
						{
							//登录时间受限制
							_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
							strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"该时间段登录受限制");
							break;
						}
					}
					if (m_pATPDBSUser[i].chLimitTimeMark&32)
					{
						if (m_pATPDBSUser[i].nLimitBeginTime[1]<nTime && nTime < m_pATPDBSUser[i].nLimitEndTime[1])
						{
							//登录时间受限制
							_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
							strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"该时间段登录受限制");
							break;
						}
					}
				}

				//星期
				if (m_pATPDBSUser[i].chLimitWeek&128)
				{
					switch (t.GetDayOfWeek())
					{
					case 1://星期日
						{
							if (m_pATPDBSUser[i].chLimitWeek&64)
							{
								_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
								strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"该星期日登录受限制");
							}
						}
						break;
					case 2://星期一
						{
							if (m_pATPDBSUser[i].chLimitWeek&32)
							{
								_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
								strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"该星期一登录受限制");
							}
						}
						break;
					case 3://二
						{
							if (m_pATPDBSUser[i].chLimitWeek&16)
							{
								_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
								strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"该星期二登录受限制");
							}
						}
						break;
					case 4://三
						{
							if (m_pATPDBSUser[i].chLimitWeek&8)
							{
								_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
								strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"该星期三登录受限制");
							}
						}
						break;
					case 5://四
						{
							if (m_pATPDBSUser[i].chLimitWeek&4)
							{
								_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
								strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"该星期四登录受限制");
							}
						}
						break;
					case 6://五
						{
							if (m_pATPDBSUser[i].chLimitWeek&2)
							{
								_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
								strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"该星期五登录受限制");
							}
						}
						break;
					case 7://六
						{
							if (m_pATPDBSUser[i].chLimitWeek&1)
							{
								_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
								strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"该星期六登录受限制");
							}
						}
						break;
					default:
						break;
					}
				}
			} 
			else
			{
			}
		}
		else
		{

		}
	}
	if (nIsExistAccount==0)
	{
		_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
		strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"帐户不存在");
	}
	else
	{
		if (nIsCorrectPwd == 0)
		{
			_AtpAccept_Manager_ValidateUser_Result.nResult = -1;

			strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"密码错误");
		}
	}

	*ppAnsData = new char[nAtpAccept_Manager_MsgHeadSize+nAtpAccept_Manager_ValidateUser_ResultSize];
	if (*ppAnsData == NULL)
	{
		*pnLen = 0;
		return -1;
	}
	else
	{
		memcpy((char *)*ppAnsData,(char *)pAtpAccept_Manager_MsgHead,nAtpAccept_Manager_MsgHeadSize);
		memcpy((char *)&(*ppAnsData)[nAtpAccept_Manager_MsgHeadSize],(char *)&_AtpAccept_Manager_ValidateUser_Result,nAtpAccept_Manager_ValidateUser_ResultSize);
		*pnLen = nAtpAccept_Manager_MsgHeadSize+nAtpAccept_Manager_ValidateUser_ResultSize;
	}

	return 0;
}
//获取资金账号的信息 
int CATPDataBase::GetFundAccount(IN const char *pReqData,OUT char **ppAnsData,int *pnLen)
{
	int nAtpAccept_Manager_MsgHeadSize = sizeof AtpAccept_Manager_MsgHead;
	AtpAccept_Manager_MsgHead *pAtpAccept_Manager_MsgHead = (AtpAccept_Manager_MsgHead *)pReqData;

	int nAtpAccept_Manager_UserSize = sizeof AtpAccept_Manager_GetFoundAccount;
	AtpAccept_Manager_GetFoundAccount *pAtpAccept_Manager_ValidateUser = (AtpAccept_Manager_GetFoundAccount *)&pReqData[nAtpAccept_Manager_MsgHeadSize];
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	//资金帐户数目
	int nAtpAccept_Manager_GetFoundAccount_Result_HeadSize = sizeof AtpAccept_Manager_GetFoundAccount_Result_Head;
	AtpAccept_Manager_GetFoundAccount_Result_Head _AtpAccept_Manager_GetFoundAccount_Result_Head = {0};
	//资金帐户信息
	int nAtpAccept_Manager_GetFoundAccount_ResultSize = sizeof AtpAccept_Manager_GetFoundAccount_Result;
	AtpAccept_Manager_GetFoundAccount_Result *pAtpAccept_Manager_ValidateUser_Result = NULL;
	int nMark = 0;
	nMark = pAtpAccept_Manager_ValidateUser->nUserId-1;
	if (m_pATPDBSUser[nMark].nDeleteMark == FALSE && pAtpAccept_Manager_ValidateUser->nUserId == m_pATPDBSUser[nMark].nSerialNumber &&
		0 == strcmp(pAtpAccept_Manager_ValidateUser->szUserName,m_pATPDBSUser[nMark].szUserID))
	{
		//资金帐户数目大于0
		if (m_pATPDBSUser[nMark].nCanAssociateFundsAccount>0)
		{
			int nFundAccount = m_pATPDBSUser[nMark].nCanAssociateFundsAccount*12;
			pAtpAccept_Manager_ValidateUser_Result = new AtpAccept_Manager_GetFoundAccount_Result[nFundAccount];
			int i=0;/*帐户和市场个数的循环计数*/
			int j=0;/*帐户个数循计数*/
			int k=0;/*市场个数循环计数*/
			for (;j<m_pATPDBSUser[nMark].nCanAssociateFundsAccount;j++)
			{
				//同一帐户的不同市场类型遍历
				for (k=0;k<12;k++,i++)
				{
					if (m_pATPDBSUser[nMark].pATPFund[j].szMarkets[k] == -1)
					{
						//市场不存在，直接跳出
						break;
					}
					pAtpAccept_Manager_ValidateUser_Result[i].sType = m_pATPDBSUser[nMark].pATPFund[j].szMarkets[k];//帐户类型
					strcpy(pAtpAccept_Manager_ValidateUser_Result[i].szFound,m_pATPDBSUser[nMark].pATPFund[j].szFund);//帐户
					strcpy(pAtpAccept_Manager_ValidateUser_Result[i].szOrghID,m_pATPDBSUser[nMark].pATPFund[j].szOrgID);//营业部ID
				}
			}
			_AtpAccept_Manager_GetFoundAccount_Result_Head.nItems = i;
		}

	} 
	else//为了防止根据nSerialNumber找不到，遍历
	{
		int n=0;
		for (;n<m_nUsedATPDBSUserItem;n++)
		{
			if (m_pATPDBSUser[n].nDeleteMark == FALSE && pAtpAccept_Manager_ValidateUser->nUserId == m_pATPDBSUser[n].nSerialNumber &&
				0 == strcmp(pAtpAccept_Manager_ValidateUser->szUserName,m_pATPDBSUser[n].szUserID))
			{
				//资金帐户数目大于0
				if (m_pATPDBSUser[n].nCanAssociateFundsAccount>0)
				{
					int nFundAccount = m_pATPDBSUser[n].nCanAssociateFundsAccount*12;
					pAtpAccept_Manager_ValidateUser_Result = new AtpAccept_Manager_GetFoundAccount_Result[nFundAccount];
					int i=0;/*帐户和市场个数的循环计数*/
					int j=0;/*帐户个数循计数*/
					int k=0;/*市场个数循环计数*/
					for (;j<m_pATPDBSUser[n].nCanAssociateFundsAccount;j++)
					{
						for (k=0;k<12;k++,i++)
						{
							if (m_pATPDBSUser[n].pATPFund[j].szMarkets[k] == -1)
							{
								//市场不存在，直接跳出
								break;
							}
							pAtpAccept_Manager_ValidateUser_Result[i].sType = m_pATPDBSUser[n].pATPFund[j].szMarkets[k];//帐户类型
							strcpy(pAtpAccept_Manager_ValidateUser_Result[i].szFound,m_pATPDBSUser[n].pATPFund[j].szFund);//帐户
							strcpy(pAtpAccept_Manager_ValidateUser_Result[i].szOrghID,m_pATPDBSUser[n].pATPFund[j].szOrgID);//营业部ID
						}
					}
					_AtpAccept_Manager_GetFoundAccount_Result_Head.nItems = i;
				}
				//找到，处理后，跳出
				break;
			} 
		}
	}

	*pnLen = nAtpAccept_Manager_MsgHeadSize+nAtpAccept_Manager_GetFoundAccount_Result_HeadSize+nAtpAccept_Manager_GetFoundAccount_ResultSize*_AtpAccept_Manager_GetFoundAccount_Result_Head.nItems;
	*ppAnsData = new char[*pnLen];
	if (*ppAnsData == NULL)
	{
		*pnLen = 0;
		return -1;
	}
	else
	{
		int nCount = 0;
		memcpy((char *)&(*ppAnsData)[nCount],(char *)pAtpAccept_Manager_MsgHead,nAtpAccept_Manager_MsgHeadSize);
		nCount += nAtpAccept_Manager_MsgHeadSize;
		memcpy((char *)&(*ppAnsData)[nCount],(char *)&_AtpAccept_Manager_GetFoundAccount_Result_Head,nAtpAccept_Manager_GetFoundAccount_Result_HeadSize);
		nCount += nAtpAccept_Manager_GetFoundAccount_Result_HeadSize;
		if (pAtpAccept_Manager_ValidateUser_Result)
		{
			memcpy((char *)&(*ppAnsData)[nCount],(char *)pAtpAccept_Manager_ValidateUser_Result,nAtpAccept_Manager_GetFoundAccount_ResultSize*_AtpAccept_Manager_GetFoundAccount_Result_Head.nItems);
			delete pAtpAccept_Manager_ValidateUser_Result;
		}
	}

	return 0;
}


//获取用户可以使用的算法及算法使用信息 及算法授权服务器组 
int CATPDataBase::GetAlgoInfo(IN const char *pReqData,OUT char **ppAnsData,int *pnLen)
{
	CString str = "";
	int nAtpAccept_Manager_MsgHeadSize								= sizeof AtpAccept_Manager_MsgHead;
	AtpAccept_Manager_MsgHead *pAtpAccept_Manager_MsgHead			= (AtpAccept_Manager_MsgHead *)pReqData;

	int nAtpAccept_Manager_UserSize									= sizeof AtpAccept_Manager_GetAlgoInfo;
	AtpAccept_Manager_GetAlgoInfo *pAtpAccept_Manager_ValidateUser	= (AtpAccept_Manager_GetAlgoInfo *)&pReqData[nAtpAccept_Manager_MsgHeadSize];
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	//算法个数结构体
	int nAtpAccept_Manager_GetAlgoInfo_ResultHeadSize				= sizeof AtpAccept_Manager_GetAlgoInfo_ResultHead;
	AtpAccept_Manager_GetAlgoInfo_ResultHead _AtpAccept_Manager_GetAlgoInfo_ResultHead = {0};

	//算法信息
	int nAtpAccept_Manager_GetAlgoInfo_AlgoInfoSize					= sizeof AtpAccept_Manager_GetAlgoInfo_AlgoInfo;
	AtpAccept_Manager_GetAlgoInfo_AlgoInfo *pAtpAccept_Manager_GetAlgoInfo_AlgoInfo = new AtpAccept_Manager_GetAlgoInfo_AlgoInfo[1024];
	ASSERT(_CrtCheckMemory());
	//算法参数
	int nAtp_Algoparam_InfoSize										= sizeof Atp_Algoparam_Info;
	Atp_Algoparam_Info *pAtp_Algoparam_Info							= new Atp_Algoparam_Info[1024*20];

	int nAlgoItems				= 0;//算法个数
	int nAllParamItems			= 0;//参数个数
	int nAllExParamLen			= 0;//参数附加数据长度
	int nExistenceMark[1024]	={0};//把存在的放进去保存
	ASSERT(_CrtCheckMemory());
	BOOL bExit=FALSE;
	//int nAtp_Algoparam_InfoSize = sizeof Atp_Algoparam_Info;

	if (pAtpAccept_Manager_ValidateUser->nUserId == m_pATPDBSUser[pAtpAccept_Manager_ValidateUser->nUserId-1].nSerialNumber &&
		0 == strcmp(pAtpAccept_Manager_ValidateUser->szUserName,m_pATPDBSUser[pAtpAccept_Manager_ValidateUser->nUserId-1].szUserID))
	{
		
		int nMark=pAtpAccept_Manager_ValidateUser->nUserId-1;//用户的下标
		//算法组
		int i=0;/*用户的算法组个数循环计数*/
		int j=0;/*算法个数循环计数*/
		int k=0;/*算法参数个数循环计数*/
		
		str.Format("用户下标%d，算法组数%d，算法数%d",nMark,m_pATPDBSUser[nMark].nAlgorithmGroupN,m_nUsedATPDBSAlgorithmItem);
		//AfxMessageBox(str);
		//用户所拥有算法组ID  和  所有算法中所属算法组的ID   进行比较
		for (i=0;i<m_pATPDBSUser[nMark].nAlgorithmGroupN/*该用户拥有算法组个数*/;i++)
		{
			//continue
			for (j=0;j<m_nUsedATPDBSAlgorithmItem/*所有算法个数*/;j++)
			{
				//算法中查找相同算法组的算法
				if (m_pATPDBSAlgorithm[j].nDeleteMark == FALSE/*先判断该算法是否被删除*/ && 
					m_pATPDBSUser[nMark].pAlgorithmGroupIDs[i].nID == m_pATPDBSAlgorithm[j].nGroupID/*该用户所拥有算法组ID==算法所属组ID*/
					)
				{
					//AfxMessageBox("3224");
					bExit=FALSE;
					for (int nM=0;nM<1024;nM++)
					{
						//找到最后一个也没有重复，添加到数组中
						if (nExistenceMark[nM] == 0)
						{
							nExistenceMark[nM]=m_pATPDBSAlgorithm[j].nSerialNumber;
							//bExit = TRUE;
							// 跳出循环1024个
							break;
						}
						//检测是否重复存在
						if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[j].nSerialNumber)
						{
							bExit = TRUE;
							break;
						}
					}
					//重复存在　跳过这次循环　
					if (bExit)
					{
						continue;
					}
					memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[j].AlgorithmID,sizeof GUID);
					pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo = m_pATPDBSAlgorithm[j].nParams;
					sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"说明:%s-关键字:%s-提醒:%s-其他:%s",m_pATPDBSAlgorithm[j].szExplain,m_pATPDBSAlgorithm[j].szKeyword,m_pATPDBSAlgorithm[j].szWarning,m_pATPDBSAlgorithm[j].szStopReason);
					strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[j].szAlgorithmName);

					memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[j].AlgorithVer,sizeof struDataBaseAlgorithmVer);
					pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nAlgoLangType		= m_pATPDBSAlgorithm[j].nLanguageType;
					pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber		= m_pATPDBSAlgorithm[j].nSerialNumber;
					sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[j].szPath,m_pATPDBSAlgorithm[j].szMainDllName);
					//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[j].szPath);
					nAlgoItems++;//算法个数
					//////////////////////////////////////////////////////////////////////////
										//获取参数信息

					for (k=0;k<m_pATPDBSAlgorithm[j].nParams;k++)
					{
						//memcpy((char *)&pAtp_Algoparam_Info[nAllParamItems],(char *)&m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k],nAtp_Algoparam_InfoSize);

						pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength		= m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nExtraDataLength;
						pAtp_Algoparam_Info[nAllParamItems].nType					= m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nType;
						strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamName,m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].szParamName);
						memcpy(&pAtp_Algoparam_Info[nAllParamItems].defaultValue,&m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].defaultValue,sizeof ATP_Msg_MakeOrderByAlgo_ParamValue);
						strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamDescription,m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].szParamDescription);
						int nExMark = m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nExtraDataIndex;
						if (m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nExtraDataLength>0)
						{
							//参数附加数据
							pAtp_Algoparam_Info[nAllParamItems].pExtraData			= new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
							memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[j].pATPAlgorithmParamsEX[nExMark-1].ExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

						}

						nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
						nAllParamItems++;
					}
				}
			}
		}

		//算法
		i = 0;/*用户的算法个数循环计数*/
		j = 0;/*算法个数循环计数*/
		k = 0;/*算法参数个数循环计数*/

		//用户所拥有的算法ID   和  算法中的ID   进行比较
		for (i=0;i<m_pATPDBSUser[nMark].nAlgorithmN;i++)
		{
			for (j=0;j<m_nUsedATPDBSAlgorithmItem/*所有算法个数*/;j++)
			{
				//GUID相等
				if (m_pATPDBSAlgorithm[j].nDeleteMark			== FALSE && 
					m_pATPDBSUser[nMark].pAlgorithmIDs[i].nID	== m_pATPDBSAlgorithm[j].AlgorithmID)
				{

					bExit=FALSE;
					for (int nM=0;nM<1024;nM++)
					{
						//找到最后一个也没有重复
						if (nExistenceMark[nM] == 0)
						{
							nExistenceMark[nM]=m_pATPDBSAlgorithm[j].nSerialNumber;
							//bExit = FALSE;
							// 跳出循环
							break;
						}
						//重复存在
						if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[j].nSerialNumber)
						{
							bExit = TRUE;
							break;
						}
					}
					//重复存在　跳过这次循环　
					if (bExit)
					{
						continue;
					}


					memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[j].AlgorithmID,sizeof GUID);
					pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo		= m_pATPDBSAlgorithm[j].nParams;
					sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"说明:%s-关键字:%s-提醒:%s-其他:%s",m_pATPDBSAlgorithm[j].szExplain,m_pATPDBSAlgorithm[j].szKeyword,m_pATPDBSAlgorithm[j].szWarning,m_pATPDBSAlgorithm[j].szStopReason);
					strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[j].szAlgorithmName);

					memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[j].AlgorithVer,sizeof struDataBaseAlgorithmVer);
					pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber			= m_pATPDBSAlgorithm[j].nSerialNumber;
					sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[j].szPath,m_pATPDBSAlgorithm[j].szMainDllName);
					//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[j].szPath);
					nAlgoItems++;//算法个数

					//获取参数信息

					for (k=0;k<m_pATPDBSAlgorithm[j].nParams;k++)
					{
						pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength					= m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nExtraDataLength;
						pAtp_Algoparam_Info[nAllParamItems].nType								= m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nType;
						strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamName,m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].szParamName);
						memcpy(&pAtp_Algoparam_Info[nAllParamItems].defaultValue,&m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].defaultValue,sizeof ATP_Msg_MakeOrderByAlgo_ParamValue);
						strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamDescription,m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].szParamDescription);
						int nExMark = m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nExtraDataIndex;
						if (m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nExtraDataLength>0)
						{
							//参数附加数据
							pAtp_Algoparam_Info[nAllParamItems].pExtraData						= new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
							memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[j].pATPAlgorithmParamsEX[nExMark-1].ExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

						}

						nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
						nAllParamItems++;
					}
				}
			}
		}

		//查用户组
		i		= 0;//用户的用户组个数循环计数
		j		= 0;//用户组个数循环计数
		k		= 0;
		int x	= 0;// 用户组的算法组个数循环计数
		int y	= 0;//算法个数循环计数
		int z	= 0;//算法参数个数循环计数
		//用户最多只能同时在四个用户组中
		for (i=0;i<4;i++)
		{
			//用户组存在
			if (m_pATPDBSUser[nMark].nGroupIDs[i] > 0)
			{
				//查用户组在哪个位置啦 
				for (j=0;j<m_nUsedATPDBSUserGroupItem;j++)
				{
					//查到用户中的用户组ID在用户组中的位置
					if (m_pATPDBSUserGroup[j].nDeleteMark == FALSE &&
						m_pATPDBSUser[nMark].nGroupIDs[i] == m_pATPDBSUserGroup[j].nID)
					{
						//查找用户组中有哪些算法和算法组，真TMD的麻烦啊
						x = 0;// 用户组的算法组个数循环计数
						y = 0;//算法个数循环计数
						z = 0;//算法参数个数循环计数
						//遍历用户组中的算法组
						for (x=0;x<m_pATPDBSUserGroup[j].nAlgorithmGroupN;x++)
						{
							for (y=0;y<m_nUsedATPDBSAlgorithmItem;y++)
							{
								//算法中查找相同算法组的算法
								if (m_pATPDBSAlgorithm[y].nDeleteMark == FALSE && 
									m_pATPDBSUserGroup[j].pAlgorithmGroupIDs[x].nID == m_pATPDBSAlgorithm[y].nGroupID)
								{
									bExit=FALSE;
									for (int nM=0;nM<1024;nM++)
									{
										//找到最后一个也没有重复
										if (nExistenceMark[nM] == 0)
										{
											nExistenceMark[nM] = m_pATPDBSAlgorithm[y].nSerialNumber;
											//bExit = TRUE;
											// 跳出循环
											break;
										}
										//重复存在
										if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[y].nSerialNumber)
										{
											bExit = TRUE;
											break;
										}
									}
									//重复存在　跳过这次循环　
									if (bExit)
									{
										continue;
									}

									memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[y].AlgorithmID,sizeof GUID);
									pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo		= m_pATPDBSAlgorithm[j].nParams;
									sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"说明:%s-关键字:%s-提醒:%s-其他:%s",m_pATPDBSAlgorithm[y].szExplain,m_pATPDBSAlgorithm[y].szKeyword,m_pATPDBSAlgorithm[y].szWarning,m_pATPDBSAlgorithm[y].szStopReason);
									strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[y].szAlgorithmName);

									memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[y].AlgorithVer,sizeof struDataBaseAlgorithmVer);
									pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber			= m_pATPDBSAlgorithm[y].nSerialNumber;
									sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[y].szPath,m_pATPDBSAlgorithm[y].szMainDllName);
									//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[y].szPath);
									nAlgoItems++;//算法个数

									//获取参数信息

									for (z=0;z<m_pATPDBSAlgorithm[y].nParams;z++)
									{
										//memcpy((char *)&pAtp_Algoparam_Info[nAllParamItems],(char *)&m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k],nAtp_Algoparam_InfoSize);

										pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength					= m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nExtraDataLength;
										pAtp_Algoparam_Info[nAllParamItems].nType								= m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nType;
										strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamName,m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].szParamName);
										memcpy(&pAtp_Algoparam_Info[nAllParamItems].defaultValue,&m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].defaultValue,sizeof ATP_Msg_MakeOrderByAlgo_ParamValue);
										strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamDescription,m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].szParamDescription);
										int nExMark = m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nExtraDataIndex;
										if (m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nExtraDataLength>0)
										{
											//参数附加数据
											pAtp_Algoparam_Info[nAllParamItems].pExtraData = new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
											memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[y].pATPAlgorithmParamsEX[nExMark-1].ExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

										}

										nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
										nAllParamItems++;
									}
								}
							}
						}

						//遍历用户组中的算法
						x = 0;//用户组的算法个数循环计数
						y = 0;//算法个数循环计数
						z = 0;//算法参数个数循环计数
						for (x=0;x<m_pATPDBSUserGroup[j].nAlgorithmN;x++)
						{
							for (y=0;y<m_nUsedATPDBSAlgorithmItem;y++)
							{
								//GUID相等
								if (m_pATPDBSAlgorithm[y].nDeleteMark == FALSE && 
									m_pATPDBSUserGroup[j].nDeleteMark == FALSE &&
									m_pATPDBSUserGroup[j].pAlgorithmIDs[x].nID == m_pATPDBSAlgorithm[y].AlgorithmID)
								{

									bExit=FALSE;
									for (int nM=0;nM<1024;nM++)
									{
										//找到最后一个也没有重复
										if (nExistenceMark[nM] == 0)
										{
											nExistenceMark[nM]=m_pATPDBSAlgorithm[y].nSerialNumber;
											//bExit = TRUE;
											// 跳出循环
											break;
										}
										//重复存在
										if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[y].nSerialNumber)
										{
											bExit = TRUE;
											break;
										}
									}
									//重复存在　跳过这次循环　
									if (bExit)
									{
										continue;
									}


									memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[y].AlgorithmID,sizeof GUID);
									pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo = m_pATPDBSAlgorithm[y].nParams;
									sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"说明:%s-关键字:%s-提醒:%s-其他:%s",m_pATPDBSAlgorithm[y].szExplain,m_pATPDBSAlgorithm[y].szKeyword,m_pATPDBSAlgorithm[y].szWarning,m_pATPDBSAlgorithm[y].szStopReason);
									strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[y].szAlgorithmName);

									memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[y].AlgorithVer,sizeof struDataBaseAlgorithmVer);
									pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber = m_pATPDBSAlgorithm[y].nSerialNumber;
									sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[y].szPath,m_pATPDBSAlgorithm[y].szMainDllName);
									//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[y].szPath);
									nAlgoItems++;//算法个数

									//获取参数信息

									for (z=0;z<m_pATPDBSAlgorithm[y].nParams;z++)
									{
										pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength = m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nExtraDataLength;
										pAtp_Algoparam_Info[nAllParamItems].nType = m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nType;
										strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamName,m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].szParamName);
										memcpy(&pAtp_Algoparam_Info[nAllParamItems].defaultValue,&m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].defaultValue,sizeof ATP_Msg_MakeOrderByAlgo_ParamValue);
										strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamDescription,m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].szParamDescription);
										int nExMark = m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nExtraDataIndex;
										if (m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nExtraDataLength>0)
										{
											//参数附加数据
											pAtp_Algoparam_Info[nAllParamItems].pExtraData = new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
											memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[y].pATPAlgorithmParamsEX[nExMark-1].ExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

										}

										nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
										nAllParamItems++;
									}
								}
							}
						}


					} 
					else
					{
						//找不到再找啦，没什么好沮丧的哦 
					}
				}
			} 
			else
			{
				//用户组都不存在了，还能干嘛呢，走人吧
				break;
			}
		}




	}
	else
	{
		//AfxMessageBox("1");
		int nMark = 0;//用户个数计数，用户的下标
		for (;nMark<m_nUsedATPDBSUserItem;nMark++)
		{
			if (m_pATPDBSUser[nMark].nDeleteMark == FALSE &&//判断该用户是否被删除
				pAtpAccept_Manager_ValidateUser->nUserId == m_pATPDBSUser[nMark].nSerialNumber &&//比较用户ID
				0 == strcmp(pAtpAccept_Manager_ValidateUser->szUserName,m_pATPDBSUser[nMark].szUserID)//比较用户名
				)
			{
				//int nMark=n;//用户的下标
				//算法组
				int i=0,/*用户的算法组个数计数*/
					j=0,/*算法个数计数*/
					k=0;/*算法参数个数计数*/
				for (;i<m_pATPDBSUser[nMark].nAlgorithmGroupN;i++)
				{

					for (j=0;j<m_nUsedATPDBSAlgorithmItem;j++)
					{
						//算法中查找相同算法组的算法
						if (m_pATPDBSAlgorithm[j].nDeleteMark == FALSE && //判断改算法是否被删除
							m_pATPDBSUser[nMark].pAlgorithmGroupIDs[i].nID == m_pATPDBSAlgorithm[j].nGroupID//比较用户的算法组ID 和 算法中所属算法组ID
							)
						{
							bExit=FALSE;
							for (int nM=0;nM<1024;nM++)
							{
								//找到最后一个也没有重复，添加到数组中
								if (nExistenceMark[nM] == 0)
								{
									nExistenceMark[nM]=m_pATPDBSAlgorithm[j].nSerialNumber;
									//bExit = TRUE;
									// 跳出循环1024个
									break;
								}
								//检测是否重复存在
								if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[j].nSerialNumber)
								{
									bExit = TRUE;
									break;//如果已经存在，则没必要再往下找了
								}
							}
							//重复存在　跳过这次循环　
							if (bExit)
							{
								continue;
							}
							memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[j].AlgorithmID,sizeof GUID);
							pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo = m_pATPDBSAlgorithm[j].nParams;
							sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"说明:%s关键字:%s提醒:%s其他:%s",m_pATPDBSAlgorithm[j].szExplain,m_pATPDBSAlgorithm[j].szKeyword,m_pATPDBSAlgorithm[j].szWarning,m_pATPDBSAlgorithm[j].szStopReason);
							strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[j].szAlgorithmName);

							memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[j].AlgorithVer,sizeof struDataBaseAlgorithmVer);
							pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber = m_pATPDBSAlgorithm[j].nSerialNumber;
							sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[j].szPath,m_pATPDBSAlgorithm[j].szMainDllName);
							//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[j].szPath);
							nAlgoItems++;//算法个数

							//获取参数信息

							for (k=0;k<m_pATPDBSAlgorithm[j].nParams;k++)
							{
								//memcpy((char *)&pAtp_Algoparam_Info[nAllParamItems],(char *)&m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k],nAtp_Algoparam_InfoSize);
								//参数附加数据
								//pAtp_Algoparam_Info[nAllParamItems].pExtraData = new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
								//memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].pExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

								//nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
								//nAllParamItems++;
								pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength = m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nExtraDataLength;
								pAtp_Algoparam_Info[nAllParamItems].nType = m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nType;
								strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamName,m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].szParamName);
								memcpy(&pAtp_Algoparam_Info[nAllParamItems].defaultValue,&m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].defaultValue,sizeof ATP_Msg_MakeOrderByAlgo_ParamValue);
								strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamDescription,m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].szParamDescription);
								int nExMark = m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nExtraDataIndex;
								if (m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nExtraDataLength>0)
								{
									//参数附加数据
									pAtp_Algoparam_Info[nAllParamItems].pExtraData = new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
									memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[j].pATPAlgorithmParamsEX[nExMark-1].ExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

								}

								nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
								nAllParamItems++;
							}
						}
					}
				}

				//算法
				//i 用户的算法个数计数
				//j 算法计数
				//k 算法的参数计数
				for (i=0;i<m_pATPDBSUser[nMark].nAlgorithmN;i++)
				{
					for (j=0;j<m_nUsedATPDBSAlgorithmItem;j++)
					{
						//GUID相等
						if (FALSE == m_pATPDBSAlgorithm[j].nDeleteMark && 
							m_pATPDBSUser[nMark].pAlgorithmIDs[i].nID == m_pATPDBSAlgorithm[j].AlgorithmID)
						{
							bExit=FALSE;
							for (int nM=0;nM<1024;nM++)
							{
								//找到最后一个也没有重复，添加到数组中
								if (nExistenceMark[nM] == 0)
								{
									nExistenceMark[nM]=m_pATPDBSAlgorithm[j].nSerialNumber;
									//bExit = TRUE;
									// 跳出循环1024个
									break;
								}
								//检测是否重复存在
								if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[j].nSerialNumber)
								{
									bExit = TRUE;
									break;
								}
							}
							//重复存在　跳过这次循环　
							if (bExit)
							{
								continue;
							}
							memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[j].AlgorithmID,sizeof GUID);
							pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo = m_pATPDBSAlgorithm[j].nParams;
							sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"说明:%s关键字:%s提醒:%s其他:%s",m_pATPDBSAlgorithm[j].szExplain,m_pATPDBSAlgorithm[j].szKeyword,m_pATPDBSAlgorithm[j].szWarning,m_pATPDBSAlgorithm[j].szStopReason);
							strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[j].szAlgorithmName);

							memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[j].AlgorithVer,sizeof struDataBaseAlgorithmVer);
							pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber = m_pATPDBSAlgorithm[j].nSerialNumber;
							sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[j].szPath,m_pATPDBSAlgorithm[j].szMainDllName);
							//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[j].szPath);
							nAlgoItems++;//算法个数

							//获取参数信息

							for (k=0;k<m_pATPDBSAlgorithm[j].nParams;k++)
							{
								//memcpy((char *)&pAtp_Algoparam_Info[nAllParamItems],(char *)&m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k],nAtp_Algoparam_InfoSize);
								//参数附加数据
								//pAtp_Algoparam_Info[nAllParamItems].pExtraData = new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
								//memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].pExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

								//nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
								//nAllParamItems++;
								pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength = m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nExtraDataLength;
								pAtp_Algoparam_Info[nAllParamItems].nType = m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nType;
								strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamName,m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].szParamName);
								memcpy(&pAtp_Algoparam_Info[nAllParamItems].defaultValue,&m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].defaultValue,sizeof ATP_Msg_MakeOrderByAlgo_ParamValue);
								strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamDescription,m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].szParamDescription);
								int nExMark = m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nExtraDataIndex;
								if (m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k].nExtraDataLength>0)
								{
									//参数附加数据
									pAtp_Algoparam_Info[nAllParamItems].pExtraData = new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
									memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[j].pATPAlgorithmParamsEX[nExMark-1].ExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

								}

								nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
								nAllParamItems++;
							}
						}
					}
				}



				//查用户组
				i = 0;//用户的用户组计数
				j = 0;//用户组计数
				k = 0;
				//用户最多只能同时在四个用户组中
				for (i=0;i<4;i++)
				{
					//用户的用户组组存在
					if (m_pATPDBSUser[nMark].nGroupIDs[i] > 0)
					{
						//查用户组在哪个位置啦 
						for (j=0;j<m_nUsedATPDBSUserGroupItem;j++)
						{
							//查到用户中的用户组ID在用户组中的位置
							if (m_pATPDBSUser[nMark].nGroupIDs[i] == m_pATPDBSUserGroup[j].nID)
							{
								//查找用户组中有哪些算法和算法组，真TMD的麻烦啊
								int x = 0,//用户组的算法组计数
									y = 0,//算法个数计数
									z = 0;//
								//遍历用户组中的算法组
								for (x=0;x<m_pATPDBSUserGroup[j].nAlgorithmGroupN;x++)
								{

									for (y=0;y<m_nUsedATPDBSAlgorithmItem;y++)
									{
										//算法中查找相同算法组的算法
										if (FALSE == m_pATPDBSAlgorithm[y].nDeleteMark && 
											m_pATPDBSUserGroup[j].pAlgorithmGroupIDs[x].nID == m_pATPDBSAlgorithm[y].nGroupID)
										{
											bExit=FALSE;
											for (int nM=0;nM<1024;nM++)
											{
												//找到最后一个也没有重复，添加到数组中
												if (nExistenceMark[nM] == 0)
												{
													nExistenceMark[nM]=m_pATPDBSAlgorithm[y].nSerialNumber;
													//bExit = TRUE;
													// 跳出循环1024个
													break;
												}
												//检测是否重复存在
												if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[y].nSerialNumber)
												{
													bExit = TRUE;
													break;
												}
											}
											//重复存在　跳过这次循环　
											if (bExit)
											{
												continue;
											}
											memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[y].AlgorithmID,sizeof GUID);
											pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo = m_pATPDBSAlgorithm[j].nParams;
											sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"说明:%s-关键字:%s-提醒:%s-其他:%s",m_pATPDBSAlgorithm[y].szExplain,m_pATPDBSAlgorithm[y].szKeyword,m_pATPDBSAlgorithm[y].szWarning,m_pATPDBSAlgorithm[y].szStopReason);
											strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[y].szAlgorithmName);

											memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[y].AlgorithVer,sizeof struDataBaseAlgorithmVer);
											pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber = m_pATPDBSAlgorithm[y].nSerialNumber;
											sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[y].szPath,m_pATPDBSAlgorithm[y].szMainDllName);
											//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[y].szPath);
											nAlgoItems++;//算法个数

											//获取参数信息

											for (z=0;z<m_pATPDBSAlgorithm[y].nParams;z++)
											{
												//memcpy((char *)&pAtp_Algoparam_Info[nAllParamItems],(char *)&m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k],nAtp_Algoparam_InfoSize);

												pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength = m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nExtraDataLength;
												pAtp_Algoparam_Info[nAllParamItems].nType = m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nType;
												strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamName,m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].szParamName);
												memcpy(&pAtp_Algoparam_Info[nAllParamItems].defaultValue,&m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].defaultValue,sizeof ATP_Msg_MakeOrderByAlgo_ParamValue);
												strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamDescription,m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].szParamDescription);
												int nExMark = m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nExtraDataIndex;
												if (m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nExtraDataLength>0)
												{
													//参数附加数据
													pAtp_Algoparam_Info[nAllParamItems].pExtraData = new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
													memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[y].pATPAlgorithmParamsEX[nExMark-1].ExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

												}

												nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
												nAllParamItems++;
											}
										}
									}
								}

								//遍历用户组中的算法
								x =0;y = 0;z = 0;
								for (x=0;x<m_pATPDBSUserGroup[j].nAlgorithmN;x++)
								{
									for (y=0;y<m_nUsedATPDBSAlgorithmItem;y++)
									{
										//GUID相等
										if (FALSE == m_pATPDBSAlgorithm[y].nDeleteMark && 
											m_pATPDBSUserGroup[j].pAlgorithmIDs[x].nID == m_pATPDBSAlgorithm[y].AlgorithmID)
										{
											bExit=FALSE;
											for (int nM=0;nM<1024;nM++)
											{
												//找到最后一个也没有重复，添加到数组中
												if (nExistenceMark[nM] == 0)
												{
													nExistenceMark[nM]=m_pATPDBSAlgorithm[y].nSerialNumber;
													//bExit = TRUE;
													// 跳出循环1024个
													break;
												}
												//检测是否重复存在
												if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[y].nSerialNumber)
												{
													bExit = TRUE;
													break;
												}
											}
											//重复存在　跳过这次循环　
											if (bExit)
											{
												continue;
											}
											memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[y].AlgorithmID,sizeof GUID);
											pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo = m_pATPDBSAlgorithm[y].nParams;
											sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"说明:%s-关键字:%s-提醒:%s-其他:%s",m_pATPDBSAlgorithm[y].szExplain,m_pATPDBSAlgorithm[y].szKeyword,m_pATPDBSAlgorithm[y].szWarning,m_pATPDBSAlgorithm[y].szStopReason);
											strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[y].szAlgorithmName);

											memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[y].AlgorithVer,sizeof struDataBaseAlgorithmVer);
											pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber = m_pATPDBSAlgorithm[y].nSerialNumber;
											sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[y].szPath,m_pATPDBSAlgorithm[y].szMainDllName);
											//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[y].szPath);
											nAlgoItems++;//算法个数

											//获取参数信息

											for (z=0;z<m_pATPDBSAlgorithm[y].nParams;z++)
											{
												pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength = m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nExtraDataLength;
												pAtp_Algoparam_Info[nAllParamItems].nType = m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nType;
												strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamName,m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].szParamName);
												memcpy(&pAtp_Algoparam_Info[nAllParamItems].defaultValue,&m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].defaultValue,sizeof ATP_Msg_MakeOrderByAlgo_ParamValue);
												strcpy(pAtp_Algoparam_Info[nAllParamItems].szParamDescription,m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].szParamDescription);
												int nExMark = m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nExtraDataIndex;
												if (m_pATPDBSAlgorithm[y].pATPAlgorithmParams[z].nExtraDataLength>0)
												{
													//参数附加数据
													pAtp_Algoparam_Info[nAllParamItems].pExtraData = new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
													memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[y].pATPAlgorithmParamsEX[nExMark-1].ExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

												}

												nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
												nAllParamItems++;
											}
										}
									}
								}


							} 
							else
							{
								//找不到再找啦，没什么好沮丧的哦 
							}
						}
					} 
					else
					{
						//用户组都不存在了，还能干嘛呢，走人吧
						break;
					}
				}
				//在用户中查找到一个即可，后面就没必要查找，没这么多时间浪费啊
				break;
			}
		}
	}
	ASSERT(_CrtCheckMemory());
	_AtpAccept_Manager_GetAlgoInfo_ResultHead.nAlgoCount = nAlgoItems;
	*pnLen = nAtpAccept_Manager_GetAlgoInfo_ResultHeadSize+nAtpAccept_Manager_MsgHeadSize+
		nAlgoItems*nAtpAccept_Manager_GetAlgoInfo_AlgoInfoSize+nAllParamItems*nAtp_Algoparam_InfoSize+nAllExParamLen;
	*ppAnsData = new char[*pnLen];
	if (*ppAnsData == NULL)
	{
		*pnLen = 0;
		return -1;
	}
	else
	{
		int nCount = 0;
		memcpy((char *)&(*ppAnsData)[nCount],(char *)pAtpAccept_Manager_MsgHead,nAtpAccept_Manager_MsgHeadSize);//标准返回头
		nCount += nAtpAccept_Manager_MsgHeadSize;
		memcpy((char *)&(*ppAnsData)[nCount],(char *)&_AtpAccept_Manager_GetAlgoInfo_ResultHead,nAtpAccept_Manager_GetAlgoInfo_ResultHeadSize);//算法个数
		nCount += nAtpAccept_Manager_GetAlgoInfo_ResultHeadSize;
		int nParamMark = 0;
		int i=0,j=0;
		for (i=0;i<nAlgoItems;i++)
		{
			memcpy((char *)&(*ppAnsData)[nCount],(char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[i],nAtpAccept_Manager_GetAlgoInfo_AlgoInfoSize);//算法
			nCount += nAtpAccept_Manager_GetAlgoInfo_AlgoInfoSize;
			for (j=0;j<pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[i].algoInfo.nParamInfo;j++,nParamMark++)
			{
				memcpy((char *)&(*ppAnsData)[nCount],(char *)&pAtp_Algoparam_Info[nParamMark],nAtp_Algoparam_InfoSize);//参数
				nCount += nAtp_Algoparam_InfoSize;
				if (pAtp_Algoparam_Info[nParamMark].nExtraDataLength>0)
				{
					memcpy((char *)&(*ppAnsData)[nCount],pAtp_Algoparam_Info[nParamMark].pExtraData,pAtp_Algoparam_Info[nParamMark].nExtraDataLength);//参数附加值
					nCount += pAtp_Algoparam_Info[nParamMark].nExtraDataLength;
				}


			}

		}
		str.Format("符合算法数%d",nAlgoItems);
		//AfxMessageBox(str);
		ASSERT(_CrtCheckMemory());
		//释放参数\附加内容
		if (pAtp_Algoparam_Info)
		{
			for (i=0;i<nAllParamItems;i++)
			{
				if (pAtp_Algoparam_Info[i].pExtraData)
				{
					delete pAtp_Algoparam_Info[i].pExtraData;
					pAtp_Algoparam_Info[i].pExtraData = NULL;
				}
			}
			delete []pAtp_Algoparam_Info;
			pAtp_Algoparam_Info = NULL;
		}
		ASSERT(_CrtCheckMemory());
		//释放算法
		if (pAtpAccept_Manager_GetAlgoInfo_AlgoInfo)
		{
			delete pAtpAccept_Manager_GetAlgoInfo_AlgoInfo;
		}
	}

	return 0;
}

int CATPDataBase::GetServerInfo(IN const char *pReqData,OUT char **ppAnsData,int *pnLen)
{
	int nAtpAccept_Manager_MsgHeadSize									= sizeof AtpAccept_Manager_MsgHead;
	AtpAccept_Manager_MsgHead *pAtpAccept_Manager_MsgHead				= (AtpAccept_Manager_MsgHead *)pReqData;

	int nAtpAccept_Manager_UserSize										= sizeof AtpAccept_Manager_GetServerInfo;
	AtpAccept_Manager_GetServerInfo *pAtpAccept_Manager_ValidateUser	= (AtpAccept_Manager_GetServerInfo *)&pReqData[nAtpAccept_Manager_MsgHeadSize];
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	//服务器个数
	int nAtpAccept_Manager_GetServerInfo_ResultHeadSize					= sizeof AtpAccept_Manager_GetServerInfo_ResultHead;
	AtpAccept_Manager_GetServerInfo_ResultHead _AtpAccept_Manager_GetServerInfo_ResultHead = {0};

	int nAtpAccept_Manager_GetServerInfo_AlgoServerSize					= sizeof AtpAccept_Manager_GetServerInfo_AlgoServer;
	AtpAccept_Manager_GetServerInfo_AlgoServer *pAtpAccept_Manager_GetServerInfo_AlgoServer = new AtpAccept_Manager_GetServerInfo_AlgoServer[1024];
	int nAlgoServerItems = 0;//服务器个数
	int nExistenceMark[1024]={0};
	if (pAtpAccept_Manager_ValidateUser->nUserId == m_pATPDBSUser[pAtpAccept_Manager_ValidateUser->nUserId-1].nSerialNumber &&
		0 == strcmp(pAtpAccept_Manager_ValidateUser->szUserName,m_pATPDBSUser[pAtpAccept_Manager_ValidateUser->nUserId-1].szUserID))
	{
		int nMark = pAtpAccept_Manager_ValidateUser->nUserId-1;
		//服务器组
		if (m_pATPDBSUser[nMark].nServerGroupN>0)
		{
			int i=0;
			struATPDataBaseServer_QUERY _ATPDBSServer_QUERY = {0};
			struATPDataBaseServer *pATPDBSServer			= NULL;
			int nItems = 0;
			//查询该用户所有的服务器组
			for (;i<m_pATPDBSUser[nMark].nServerGroupN;i++)
			{
				_ATPDBSServer_QUERY.nGroupID = m_pATPDBSUser[nMark].pServerGroupIDs[i].nID;
				//根据服务器组 ID 查找符合的服务器
				nItems = QueryServer(&_ATPDBSServer_QUERY,&pATPDBSServer);
				int j=0;
				for (j=0;j<nItems;j++)
				{
					//不存在不同服务器组有相同服务器，每个服务器只能所属于一个服务器组
					strcpy(pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].szServerIp,pATPDBSServer[j].szIP);
					pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].cIpType	= pATPDBSServer[j].nIPType;
					pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].nPort		= pATPDBSServer[j].nPort;
					pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].nServerID = pATPDBSServer[j].nID;
					nAlgoServerItems++;
				}
				if (pATPDBSServer)
				{
					delete pATPDBSServer;
					pATPDBSServer = NULL;
				}
			}
		}
		//服务器
		if (m_pATPDBSUser[nMark].nServerN>0)
		{
			//查询该用户所有专属服务器
			int i=0;
			struATPDataBaseServer _ATPDBSServer			= {0};
			for (;i<m_pATPDBSUser[nMark].nServerN;i++)
			{

				//查找i
				int j=0,nItems=0/*符合记录条数*/;
				for (;j<m_nUsedATPDBSServerItem;j++)
				{

					if (m_pATPDBSUser[nMark].pServerIDs[i].nID == m_pATPDBSServer[j].nID)
					{
						ZeroMemory((char *)&_ATPDBSServer,sizeof struATPDataBaseServer);
						memcpy((char *)&_ATPDBSServer,&m_pATPDBSServer[j],sizeof struATPDataBaseServer);
						//查找是否存在
						int k=0,nIsExisit=FALSE;
						for (;k<nAlgoServerItems;k++)
						{
							if (0==strcmp(_ATPDBSServer.szIP,pAtpAccept_Manager_GetServerInfo_AlgoServer[k].szServerIp))
							{
								nIsExisit = TRUE;
								break;
							}
						}

						//
						if (!nIsExisit)
						{
							strcpy(pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].szServerIp,_ATPDBSServer.szIP);
							pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].cIpType	= _ATPDBSServer.nIPType;
							pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].nPort		= _ATPDBSServer.nPort;
							nAlgoServerItems++;
						}

						break;
					}
				}
			}
		}

		//用户组
		int i = 0,j = 0,k = 0;
		for (i=0;i<4;i++)
		{
			//用户组存在
			if (m_pATPDBSUser[nMark].nGroupIDs[i] > 0)
			{
				//查用户组在哪个位置啦 
				for (j=0;j<m_nUsedATPDBSUserGroupItem;j++)
				{
					//查到用户中的用户组ID在用户组中的位置
					if (m_pATPDBSUser[nMark].nGroupIDs[i] == m_pATPDBSUserGroup[j].nID)
					{

						//查找用户组中有哪些服务器和服务器组，真TMD的麻烦啊
						int x = 0,y = 0,z = 0;
						for (x=0;x<m_pATPDBSUserGroup[j].nServerGroupN;x++)
						{

							for (y=0;y<m_nUsedATPDBSServerItem;y++)
							{
								//服务器中查找相同服务器组的服务器
								if (m_pATPDBSUserGroup[j].pServerGroupIDs[x].nID == m_pATPDBSServer[y].nGroupID)
								{

									int nExit = 0;
									for (int nM=0;nM<1024;nM++)
									{
										//找到最后一个也没有重复
										if (nExistenceMark[nM] == 0)
										{
											nExistenceMark[nM]=m_pATPDBSServer[y].nID;
											nExit = 0;
											// 跳出循环
											break;
										}
										//重复存在
										if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSServer[y].nID)
										{
											nExit = 1;
											break;
										}
										//重复存在　跳过这次循环　
										if (nExit == 1)
										{
											continue;
										}
										strcpy(pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].szServerIp,m_pATPDBSServer[y].szIP);
										pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].cIpType	= m_pATPDBSServer[y].nIPType;
										pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].nPort		= m_pATPDBSServer[y].nPort;
										nAlgoServerItems++;

									}
								}
							}
						}

						//遍历用户组中的服务器
						x =0;y = 0;z = 0;
						for (x=0;x<m_pATPDBSUserGroup[j].nServerN;x++)
						{
							for (y=0;y<m_nUsedATPDBSServerItem;y++)
							{
								//ID相等
								if (m_pATPDBSServer[y].nID == m_pATPDBSUserGroup[j].pServerIDs[x].nID)
								{

									int nExit=0;
									for (int nM=0;nM<1024;nM++)
									{
										//找到最后一个也没有重复
										if (nExistenceMark[nM] == 0)
										{
											nExistenceMark[nM]=m_pATPDBSServer[y].nID;
											nExit = 0;
											// 跳出循环
											break;
										}
										//重复存在
										if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSServer[y].nID)
										{
											nExit = 1;
											break;
										}
									}
									//重复存在　跳过这次循环　
									if (nExit == 1)
									{
										continue;
									}
									strcpy(pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].szServerIp,m_pATPDBSServer[y].szIP);
									pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].cIpType	= m_pATPDBSServer[y].nIPType;
									pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].nPort		= m_pATPDBSServer[y].nPort;
									nAlgoServerItems++;

								

									
								}
							}
						}

					}

				}
			}
		}


	}
	else
	{
		int n=0;
		for (;n<m_nUsedATPDBSUserItem;n++)
		{
			int nMark = n;
			//服务器组
			if (m_pATPDBSUser[n].nServerGroupN>0)
			{
				int i=0;
				struATPDataBaseServer_QUERY _ATPDBSServer_QUERY = {0};
				struATPDataBaseServer *pATPDBSServer			= NULL;
				int nItems = 0;
				//查询该用户所有的服务器组
				for (;i<m_pATPDBSUser[n].nServerGroupN;i++)
				{
					_ATPDBSServer_QUERY.nGroupID = m_pATPDBSUser[n].pServerGroupIDs[i].nID;
					//根据服务器组 ID 查找符合的服务器
					nItems = QueryServer(&_ATPDBSServer_QUERY,&pATPDBSServer);
					int j=0;
					for (;j<nItems;j++)
					{
						//不存在不同服务器组有相同服务器，每个服务器只能所属于一个服务器组
						strcpy(pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].szServerIp,pATPDBSServer[j].szIP);
						pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].cIpType	= pATPDBSServer[j].nIPType;
						pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].nPort		= pATPDBSServer[j].nPort;
						nAlgoServerItems++;
					}
					if (pATPDBSServer)
					{
						delete pATPDBSServer;
						pATPDBSServer = NULL;
					}
				}
			}
			//服务器
			if (m_pATPDBSUser[n].nServerN>0)
			{
				//查询该用户所有专属服务器
				int i=0;
				struATPDataBaseServer _ATPDBSServer			= {0};
				for (;i<m_pATPDBSUser[n].nServerN;i++)
				{

					//查找i
					int j=0,nItems=0/*符合记录条数*/;
					for (;j<m_nUsedATPDBSServerItem;j++)
					{

						if (m_pATPDBSUser[n].pServerIDs[i].nID == m_pATPDBSServer[j].nID)
						{
							ZeroMemory((char *)&_ATPDBSServer,sizeof struATPDataBaseServer);
							memcpy((char *)&_ATPDBSServer,&m_pATPDBSServer[j],sizeof struATPDataBaseServer);
							//查找是否存在
							int k=0,nIsExisit=FALSE;
							for (;k<nAlgoServerItems;k++)
							{
								if (0==strcmp(_ATPDBSServer.szIP,pAtpAccept_Manager_GetServerInfo_AlgoServer[k].szServerIp))
								{
									nIsExisit = TRUE;
									break;
								}
							}

							//
							if (!nIsExisit)
							{
								strcpy(pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].szServerIp,_ATPDBSServer.szIP);
								pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].cIpType	= _ATPDBSServer.nIPType;
								pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].nPort		= _ATPDBSServer.nPort;
								nAlgoServerItems++;
							}

							break;
						}
					}
				}
			}

			//用户组
			int i = 0,j = 0,k = 0;
			for (i=0;i<4;i++)
			{
				//用户组存在
				if (m_pATPDBSUser[nMark].nGroupIDs[i] > 0)
				{
					//查用户组在哪个位置啦 
					for (j=0;j<m_nUsedATPDBSUserGroupItem;j++)
					{
						//查到用户中的用户组ID在用户组中的位置
						if (m_pATPDBSUser[nMark].nGroupIDs[i] == m_pATPDBSUserGroup[j].nID)
						{

							//查找用户组中有哪些服务器和服务器组，真TMD的麻烦啊
							int x = 0,y = 0,z = 0;
							for (x=0;x<m_pATPDBSUserGroup[j].nServerGroupN;x++)
							{

								for (y=0;y<m_nUsedATPDBSServerItem;y++)
								{
									//服务器中查找相同服务器组的服务器
									if (m_pATPDBSUserGroup[j].pServerGroupIDs[x].nID == m_pATPDBSServer[y].nGroupID)
									{

										int nExit = 0;
										for (int nM=0;nM<1024;nM++)
										{
											//找到最后一个也没有重复
											if (nExistenceMark[nM] == 0)
											{
												nExistenceMark[nM]=m_pATPDBSServer[y].nID;
												nExit = 0;
												// 跳出循环
												break;
											}
											//重复存在
											if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSServer[y].nID)
											{
												nExit = 1;
												break;
											}
											//重复存在　跳过这次循环　
											if (nExit == 1)
											{
												continue;
											}
											strcpy(pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].szServerIp,m_pATPDBSServer[y].szIP);
											pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].cIpType	= m_pATPDBSServer[y].nIPType;
											pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].nPort		= m_pATPDBSServer[y].nPort;
											nAlgoServerItems++;

										}
									}
								}
							}

							//遍历用户组中的服务器
							x =0;y = 0;z = 0;
							for (x=0;x<m_pATPDBSUserGroup[j].nServerN;x++)
							{
								for (y=0;y<m_nUsedATPDBSServerItem;y++)
								{
									//ID相等
									if (m_pATPDBSServer[y].nID == m_pATPDBSUserGroup[j].pServerIDs[x].nID)
									{

										int nExit=0;
										for (int nM=0;nM<1024;nM++)
										{
											//找到最后一个也没有重复
											if (nExistenceMark[nM] == 0)
											{
												nExistenceMark[nM]=m_pATPDBSServer[y].nID;
												nExit = 0;
												// 跳出循环
												break;
											}
											//重复存在
											if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSServer[y].nID)
											{
												nExit = 1;
												break;
											}
										}
										//重复存在　跳过这次循环　
										if (nExit == 1)
										{
											continue;
										}
										strcpy(pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].szServerIp,m_pATPDBSServer[y].szIP);
										pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].cIpType	= m_pATPDBSServer[y].nIPType;
										pAtpAccept_Manager_GetServerInfo_AlgoServer[nAlgoServerItems].nPort		= m_pATPDBSServer[y].nPort;
										nAlgoServerItems++;




									}
								}
							}

						}

					}
				}
			}

		}
	}
	_AtpAccept_Manager_GetServerInfo_ResultHead.nItems = nAlgoServerItems;
	_AtpAccept_Manager_GetServerInfo_ResultHead.nItemSize = sizeof AtpAccept_Manager_GetServerInfo_AlgoServer;
	*pnLen = nAtpAccept_Manager_MsgHeadSize+nAtpAccept_Manager_GetServerInfo_ResultHeadSize+_AtpAccept_Manager_GetServerInfo_ResultHead.nItems*sizeof AtpAccept_Manager_GetServerInfo_AlgoServer;
	*ppAnsData = new char[*pnLen];
	if (*ppAnsData == NULL)
	{
		*pnLen = 0;
		return -1;
	}
	else
	{
		int nCount = 0;
		memcpy((char *)&(*ppAnsData)[nCount],(char *)pAtpAccept_Manager_MsgHead,nAtpAccept_Manager_MsgHeadSize);
		nCount += nAtpAccept_Manager_MsgHeadSize;
		memcpy((char *)&(*ppAnsData)[nCount],(char *)&_AtpAccept_Manager_GetServerInfo_ResultHead,nAtpAccept_Manager_GetServerInfo_ResultHeadSize);
		nCount += nAtpAccept_Manager_GetServerInfo_ResultHeadSize;
		if (pAtpAccept_Manager_GetServerInfo_AlgoServer)
		{
			memcpy((char *)&(*ppAnsData)[nCount],(char *)pAtpAccept_Manager_GetServerInfo_AlgoServer,_AtpAccept_Manager_GetServerInfo_ResultHead.nItems*sizeof AtpAccept_Manager_GetServerInfo_AlgoServer);
			delete pAtpAccept_Manager_GetServerInfo_AlgoServer;
		}
	}
	return 0;
}

int CATPDataBase::GetAccountByFund(IN const char *pReqData,OUT char **ppAnsData,int *pnLen,BOOL bFlag)
{

	int nAtpAccept_Manager_MsgHeadSize									= sizeof AtpAccept_Manager_MsgHead;
	AtpAccept_Manager_MsgHead *pAtpAccept_Manager_MsgHead				= (AtpAccept_Manager_MsgHead *)pReqData;

	int nAtpAccept_Manager_GetUserInfo_WithFundAccoutSize										= sizeof AtpAccept_Manager_GetUserInfo_WithFundAccout;
	AtpAccept_Manager_GetUserInfo_WithFundAccout *pAtpAccept_Manager_GetUserInfo_WithFundAccout	= (AtpAccept_Manager_GetUserInfo_WithFundAccout *)&pReqData[nAtpAccept_Manager_MsgHeadSize];
	//////////////////////////////////////////////////////////////////////////
	int nAtpAccept_Manager_GetUserInfo_WithFundAccout_ResultSize = sizeof AtpAccept_Manager_GetUserInfo_WithFundAccout_Result;
	AtpAccept_Manager_GetUserInfo_WithFundAccout_Result _AtpAccept_Manager_GetUserInfo_WithFundAccout_Result = {0};


	//////////////////////////////////////////////////////////////////////////
	//此对只查询资金帐号所属市场有效
	int nAtpAccept_Manager_GetFundAccount_SecurityType_ResultSize = sizeof AtpAccept_Manager_GetFundAccount_SecurityType_Result;
	AtpAccept_Manager_GetFundAccount_SecurityType_Result _AtpAccept_Manager_GetFundAccount_SecurityType_Result = {0};
	//////////////////////////////////////////////////////////////////////////
	int i = 0,j = 0,k = 0;
	char szOrgIDTemp[8]={0};
	int nRepeatMark = 0;//重复标记，0则不存在，大于1则互斥
	int nUserMark = 0;//资金帐户匹配成功时候用户的标
	//遍历所有用户
	for (;i<m_nUsedATPDBSUserItem;i++)
	{
		//遍历每个用户的的资金帐户
		for (j=0,k=0;j<m_pATPDBSUser[i].nCanAssociateFundsAccount;j++)
		{
			if (m_pATPDBSUser[i].nDeleteMark)
			{
				continue;
			}
			//营业部代码
			ZeroMemory(szOrgIDTemp,0);
			strncpy(szOrgIDTemp,m_pATPDBSUser[i].pATPFund[j].szOrgID,8);
			//匹配资金帐户
			if (0 == strcmp(m_pATPDBSUser[i].pATPFund[j].szFund,pAtpAccept_Manager_GetUserInfo_WithFundAccout->fundAccount.chUserID) &&
				0 == strcmp(szOrgIDTemp,pAtpAccept_Manager_GetUserInfo_WithFundAccout->fundAccount.chOrgID))
			{
				//只是获取资金帐号的所属市场而已
				if (bFlag)
				{
					int nMark1=0,nMark2=0;
					for (int x=0;x<12;x++)
					{
						if (m_pATPDBSUser[i].pATPFund[j].szMarkets[x] == -1)
						{
							break;
						}
						//股票市场
						if (m_pATPDBSUser[i].pATPFund[j].szMarkets[x]==0 || m_pATPDBSUser[i].pATPFund[j].szMarkets[x]==1 ||
							m_pATPDBSUser[i].pATPFund[j].szMarkets[x]==2 || m_pATPDBSUser[i].pATPFund[j].szMarkets[x]==6)
						{
							nMark1 = 1;
						}
						//期货市场
						if (m_pATPDBSUser[i].pATPFund[j].szMarkets[x]==7 || m_pATPDBSUser[i].pATPFund[j].szMarkets[x]==10)
						{
							nMark2 = 1;
						}
					}
					if (nMark1)
					{
						_AtpAccept_Manager_GetFundAccount_SecurityType_Result.nSecurityType = 1;
					}
					if (nMark2)
					{
						_AtpAccept_Manager_GetFundAccount_SecurityType_Result.nSecurityType = 2;
					}
					if (nMark1 && nMark2)
					{
						_AtpAccept_Manager_GetFundAccount_SecurityType_Result.nSecurityType = 3;
					}
					if (!nMark1 && !nMark2)
					{
						_AtpAccept_Manager_GetFundAccount_SecurityType_Result.nSecurityType = 0;
					}
					
					//查完了资金帐号所属市场立刻走人
					//goto END_GETACCOUNTBYFUND;
				}

				nRepeatMark += 1;
				if (nRepeatMark == 2)
				{
					//没有玩下去的意义了，走人吧
					goto END_SELECTFUND;
				}
				nUserMark = i;//记录用户表中的位置
				//填充返回结果
				_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nUserId = m_pATPDBSUser[i].nSerialNumber;
				strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szUserName,m_pATPDBSUser[i].szUserID);
				strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szUserPwd,m_pATPDBSUser[i].szPwd);
			}			
		}
	}

END_SELECTFUND://结束查找
	if (bFlag)
	{
		if (nRepeatMark == 2 || nRepeatMark == 0)
		{
			//资金帐号不存在
			_AtpAccept_Manager_GetFundAccount_SecurityType_Result.nSecurityType = -1;
			goto END_GETACCOUNTBYFUND;
		}
		else
		{
			goto END_GETACCOUNTBYFUND;
		}
	}

	if (nRepeatMark == 2)
	{
		//没必要做什么了，没结果的，直接返回错误信息吧
		_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nUserId = 0;
		strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szUserName,"");
		strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szUserPwd,"");
		_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
		strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"不支持一个资金帐户对应多个平台帐户");
	}
	else if (nRepeatMark == 0)
	{
		_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nUserId = 0;
		strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szUserName,"");
		strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szUserPwd,"");
		_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
		strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"不存在该资金帐户");
	}
	else if (nRepeatMark == 1)
	{
		char *ptr = NULL;
		if ((int)pAtpAccept_Manager_GetUserInfo_WithFundAccout->szLoginIpType == 4 || (int)pAtpAccept_Manager_GetUserInfo_WithFundAccout->szLoginIpType == 6)
		{
			ptr = strstr(m_pATPDBSUser[nUserMark].szIPs,pAtpAccept_Manager_GetUserInfo_WithFundAccout->szLoginIp);
			if (ptr)
			{
				//ip限制登录
				_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
				strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"该IP登录受限制");
				//break;
				goto END_GETACCOUNTBYFUND;
			}
		} 
		//mac 地址
		if (strlen(pAtpAccept_Manager_GetUserInfo_WithFundAccout->szMac))
		{
			ptr = strstr(m_pATPDBSUser[nUserMark].szMacMark,pAtpAccept_Manager_GetUserInfo_WithFundAccout->szMac);
			if (ptr)
			{
				//mac 地址 限制登录
				_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
				strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"该MAC地址登录受限制");
				//break;
				goto END_GETACCOUNTBYFUND;
			}
		}
		//硬盘序列号
		if (strlen(pAtpAccept_Manager_GetUserInfo_WithFundAccout->szDiskSerialNum))
		{
			ptr = strstr(m_pATPDBSUser[nUserMark].szDiskNum,pAtpAccept_Manager_GetUserInfo_WithFundAccout->szDiskSerialNum);
			if (ptr)
			{
				//硬盘序列号 限制登录
				_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
				strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"该硬盘登录受限制");
				//break;
				goto END_GETACCOUNTBYFUND;
			}
		}


		CTime t = CTime::GetCurrentTime(); 
		int nTime = t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();//235959

		//时间段
		if (m_pATPDBSUser[nUserMark].chLimitTimeMark&128)
		{
			if (m_pATPDBSUser[nUserMark].chLimitTimeMark&64)
			{
				if (m_pATPDBSUser[nUserMark].nLimitBeginTime[0]<nTime && nTime < m_pATPDBSUser[i].nLimitEndTime[0])
				{
					//登录时间受限制
					_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
					strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"该时间段登录受限制");
					//break;
					goto END_GETACCOUNTBYFUND;
				}
			}
			if (m_pATPDBSUser[nUserMark].chLimitTimeMark&32)
			{
				if (m_pATPDBSUser[i].nLimitBeginTime[1]<nTime && nTime < m_pATPDBSUser[i].nLimitEndTime[1])
				{
					//登录时间受限制
					_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
					strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"该时间段登录受限制");
					//break;
					goto END_GETACCOUNTBYFUND;
				}
			}
		}

		//星期
		if (m_pATPDBSUser[nUserMark].chLimitWeek&128)
		{
			switch (t.GetDayOfWeek())
			{
			case 1://星期日
				{
					if (m_pATPDBSUser[nUserMark].chLimitWeek&64)
					{
						_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"该星期日登录受限制");
					}
				}
				break;
			case 2://星期一
				{
					if (m_pATPDBSUser[nUserMark].chLimitWeek&32)
					{
						_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"该星期一登录受限制");
					}
				}
				break;
			case 3://二
				{
					if (m_pATPDBSUser[nUserMark].chLimitWeek&16)
					{
						_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"该星期二登录受限制");
					}
				}
				break;
			case 4://三
				{
					if (m_pATPDBSUser[nUserMark].chLimitWeek&8)
					{
						_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"该星期三登录受限制");
					}
				}
				break;
			case 5://四
				{
					if (m_pATPDBSUser[nUserMark].chLimitWeek&4)
					{
						_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"该星期四登录受限制");
					}
				}
				break;
			case 6://五
				{
					if (m_pATPDBSUser[nUserMark].chLimitWeek&2)
					{
						_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"该星期五登录受限制");
					}
				}
				break;
			case 7://六
				{
					if (m_pATPDBSUser[nUserMark].chLimitWeek&1)
					{
						_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"该星期六登录受限制");
					}
				}
				break;
			default:
				break;
			}
		}
	} 
	else
	{
	}

END_GETACCOUNTBYFUND:


	if (bFlag)
	{
		*ppAnsData = new char[nAtpAccept_Manager_MsgHeadSize+nAtpAccept_Manager_GetFundAccount_SecurityType_ResultSize];
		if (*ppAnsData == NULL)
		{
			*pnLen = 0;
			return -1;
		}
		else
		{
			memcpy((char *)*ppAnsData,(char *)pAtpAccept_Manager_MsgHead,nAtpAccept_Manager_MsgHeadSize);
			memcpy((char *)&(*ppAnsData)[nAtpAccept_Manager_MsgHeadSize],(char *)&_AtpAccept_Manager_GetFundAccount_SecurityType_Result,nAtpAccept_Manager_GetFundAccount_SecurityType_ResultSize);
			*pnLen = nAtpAccept_Manager_MsgHeadSize+nAtpAccept_Manager_GetFundAccount_SecurityType_ResultSize;
		}
	} 
	else
	{
		*ppAnsData = new char[nAtpAccept_Manager_MsgHeadSize+nAtpAccept_Manager_GetUserInfo_WithFundAccout_ResultSize];
		if (*ppAnsData == NULL)
		{
			*pnLen = 0;
			return -1;
		}
		else
		{
			memcpy((char *)*ppAnsData,(char *)pAtpAccept_Manager_MsgHead,nAtpAccept_Manager_MsgHeadSize);
			memcpy((char *)&(*ppAnsData)[nAtpAccept_Manager_MsgHeadSize],(char *)&_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result,nAtpAccept_Manager_GetUserInfo_WithFundAccout_ResultSize);
			*pnLen = nAtpAccept_Manager_MsgHeadSize+nAtpAccept_Manager_GetUserInfo_WithFundAccout_ResultSize;
		}

	}
	
	return 0;

}

int CATPDataBase::GetFundMarket(IN const char *pReqData,OUT char **ppAnsData,int *pnLen)
{

	GetAccountByFund(pReqData,ppAnsData,pnLen,TRUE);


	return 0;
}


int CATPDataBase::ManagerLogin(IN struReq_ATPManageLogin *pInData)
{
	int nRet = 0;
	int nAccountMark = 0;
	int nPwdMark = 0;
	int i=0;
	for (;i<m_nUsedATPDBSManagerItem;i++)
	{
		if (0 == strcmp(pInData->szLoginID,m_pATPDBSManager[i].szID))
		{
			nAccountMark = 1;

			if (0 == strcmp(pInData->szPassword,m_pATPDBSManager[i].szPwd))
			{
				nPwdMark = 1;
				goto END_MANAGERLOGIN;
			}
		}
	}

END_MANAGERLOGIN:

	if (nAccountMark==1 && nPwdMark==1)
	{
		nRet = 0;
		CTime t = CTime::GetCurrentTime();

		m_pATPDBSManager[i].nLastDate = t.GetYear()*10000+t.GetMonth()*100+t.GetDay();
		m_pATPDBSManager[i].nLastTime = t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();

	}
	else if (nAccountMark==1 && nPwdMark==0)
	{
		nRet = -1;//密码错误
	}
	else if (nAccountMark == 0)
	{
		nRet = -2;//帐户不存在
	}
	return nRet;
}

