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
	SaveRegistSaveData();//��������
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

	//����Ա
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

	//��������
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

	//������
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


	//Ȩ��
	//struATPDataBasePermission		*m_pATPDBSPermission;
	struATPDataBasePermission _ATPDBSPermission;
	CONST UINT32 nATPDBSPERMISSIONSIZE = sizeof(struATPDataBasePermission);
	RegisterSaveDataStruct(4, 1, &_ATPDBSPermission, nATPDBSPERMISSIONSIZE,&_ATPDBSPermission.nPermissionID,	nUINT32SIZE);
	RegisterSaveDataStruct(4, 2, &_ATPDBSPermission, nATPDBSPERMISSIONSIZE, _ATPDBSPermission.szPermissionName,	sizeof(_ATPDBSPermission.szPermissionName));
	RegisterSaveDataStruct(4, 3, &_ATPDBSPermission, nATPDBSPERMISSIONSIZE,&_ATPDBSPermission.nPermissionType,	nUINT8SIZE);

	RegisterSaveDataAddress(4, (void**)&m_pATPDBSPermission, nATPDBSPERMISSIONSIZE, &m_nATPDBSPermissionItem, 0, 10240);


	//�û���
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

	//�û�
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



	//�㷨��
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

	//�㷨
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
		m_nATPDBSManagerItem		= 100;//����ԱĬ��100
		m_pATPDBSManager			= new struATPDataBaseManager[m_nATPDBSManagerItem];
		if (NULL == m_pATPDBSManager)
		{
			return NEWERROR;
		}
		ZeroMemory((char*)m_pATPDBSManager,m_nATPDBSManagerItem*sizeof(struATPDataBaseManager));
		//////////////////////////////////////////////////////////////////////////
		//! ��������
		//! ��ӹ���Ա
		m_nUsedATPDBSManagerItem = 1;
		int i=0;
		for (;i<22;i++)
		{
			m_pATPDBSManager[0].nPermissionIDs[i] = i+12;
		}
		m_pATPDBSManager[0].nSerialNumber = 1;						//	�Զ����� Ψһ
		strcpy(m_pATPDBSManager[0].szID,"admin");				//	����ԱID
		strcpy(m_pATPDBSManager[0].szName,"ATP");					//	����
		strcpy(m_pATPDBSManager[0].szPwd,"admin");					//	����
		m_pATPDBSManager[0].nStatus = 0;							//	����Ա״̬  0 1 2
		strcpy(m_pATPDBSManager[0].szExplain,"ATP3");		//	˵����Ϣ
		//m_pATPDBSManager[0].nPermissionIDs[32];	//	Ȩ��ID
		m_pATPDBSManager[0].nCreateDate = 20110822;					//	��������
		m_pATPDBSManager[0].nCreateTime = 91356;					//	����ʱ��
		m_pATPDBSManager[0].nLastDate = 20110823;					//	����½����
		m_pATPDBSManager[0].nLastTime = 102145;						//	����½ʱ��
		m_pATPDBSManager[0].nDeleteMark = 0;						//	ɾ����־
		m_pATPDBSManager[0].nServerN = 0;							//	����������
		m_pATPDBSManager[0].pServerIDs = NULL;//new struATPAutoID[2];								//	������IDs
		m_pATPDBSManager[0].nServerGroupN = 0;						//	�����������
		m_pATPDBSManager[0].pServerGroupIDs = NULL;//new struATPAutoID[2];					//	��������IDs

		//////////////////////////////////////////////////////////////////////////
		m_nUsedATPDBSServerGroupItem	= 0;
		m_nATPDBSServerGroupItem		= 100;//��������Ĭ��100
		m_pATPDBSServerGroup			= new struATPDataBaseServerGroup[m_nATPDBSServerGroupItem];
		if (NULL == m_pATPDBSServerGroup)
		{
			return NEWERROR;
		}
		ZeroMemory((char*)m_pATPDBSServerGroup,m_nATPDBSServerGroupItem*sizeof(struATPDataBaseServerGroup));
		//////////////////////////////////////////////////////////////////////////
		m_nUsedATPDBSServerItem = 0;
		m_nATPDBSServerItem		= 100;//������Ĭ��100
		m_pATPDBSServer			= new struATPDataBaseServer[m_nATPDBSServerItem];
		if (NULL == m_pATPDBSServer)
		{
			return NEWERROR;
		}
		ZeroMemory((char*)m_pATPDBSServer,m_nATPDBSServerItem*sizeof(struATPDataBaseServer));
		//////////////////////////////////////////////////////////////////////////
		m_nUsedATPDBSPermissionItem = 0;
		m_nATPDBSPermissionItem		= 100;//Ȩ��Ĭ��100
		m_pATPDBSPermission			= new struATPDataBasePermission[m_nATPDBSPermissionItem];
		if (NULL == m_pATPDBSPermission)
		{
			return NEWERROR;
		}

		ZeroMemory((char*)m_pATPDBSPermission,m_nATPDBSPermissionItem*sizeof(struATPDataBasePermission));

		//////////////////////////////////////////////////////////////////////////
		//! 
		{
			//��ʼ��Ȩ��
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_ADDMANAGER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"��ӹ���Ա");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_VIEWMANAGER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�鿴����Ա");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_MODIFYMANAGER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�޸Ĺ���Ա");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_DISABLEMANAGER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"���ù���Ա");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_DELMANAGER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"ɾ������Ա");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_ADDSERVER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"��ӷ�����");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_VIEWSERVER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�鿴������");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_MODIFYSERVER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�޸ķ�����");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_DISABLESERVER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"���÷�����");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_DELSERVER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"ɾ��������");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = ADMIN_VIEWLOG;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�鿴�㷨");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_ADMINISTRATOR;

			//////////////////////////////////////////////////////////////////////////

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_ADDALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"����㷨");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_RELALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�����㷨");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_MODIFYALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�޸��㷨");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_VIEWALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�鿴�㷨");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_DISABLEALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�����㷨");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_DELALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"ɾ���㷨");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_ADDUSER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"����û�");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_VIEWUSER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�鿴�û�");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_MODIFYUSER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�޸��û�");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_DISABLEUSER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�����û�");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_DELUSER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"ɾ���û�");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_VIEWMANAGER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�鿴����Ա");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_MODIFYMANAGER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�޸Ĺ���Ա");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = MANAGER_VIEWLOG;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�鿴��־");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_MANAGER;

			//////////////////////////////////////////////////////////////////////////

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_ADDALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"����㷨");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_RUN_STOP_ALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�����㷨");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_MODIFYALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�޸��㷨");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_VIEWALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�鿴�㷨");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_DELALGO;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"ɾ���㷨");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_VIEWUSER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�鿴�û�");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_MODIFYUSER;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�޸��û�");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;

			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].nPermissionID = USER_VIEWLOG;
			strcpy(m_pATPDBSPermission[m_nUsedATPDBSPermissionItem].szPermissionName,"�鿴��־");
			m_pATPDBSPermission[m_nUsedATPDBSPermissionItem++].nPermissionType=ATP_USER;
		}

		//////////////////////////////////////////////////////////////////////////
		m_nUsedATPDBSAlgorithmGroupItem = 0;
		m_nATPDBSAlgorithmGroupItem		= 100;//�㷨��Ĭ��100
		m_pATPDBSAlgorithmGroup			= new struATPDataBaseAlgorithmGroup[m_nATPDBSAlgorithmGroupItem];
		if (NULL == m_pATPDBSAlgorithmGroup)
		{
			return NEWERROR;
		}
		ZeroMemory((char*)m_pATPDBSAlgorithmGroup,m_nATPDBSAlgorithmGroupItem*sizeof(struATPDataBaseAlgorithmGroup));
		//////////////////////////////////////////////////////////////////////////
		m_nUsedATPDBSAlgorithmItem	= 0;
		m_nATPDBSAlgorithmItem		= 500;//�㷨Ĭ��500
		m_pATPDBSAlgorithm			= new struATPDataBaseAlgorithm[m_nATPDBSAlgorithmItem];
		if (NULL == m_pATPDBSAlgorithm)
		{
			return NEWERROR;
		}
		ZeroMemory((char*)m_pATPDBSAlgorithm,m_nATPDBSAlgorithmItem*sizeof(struATPDataBaseAlgorithm));
		//////////////////////////////////////////////////////////////////////////
		m_nUsedATPDBSUserGroupItem	= 0;
		m_nATPDBSUserGroupItem		= 100;//�û���Ĭ��100
		m_pATPDBSUserGroup			= new struATPDataBaseUserGroup[m_nATPDBSUserGroupItem];
		if (NULL == m_pATPDBSUserGroup)
		{
			return NEWERROR;
		}
		ZeroMemory((char*)m_pATPDBSUserGroup,m_nATPDBSUserGroupItem*sizeof(struATPDataBaseUserGroup));
		//////////////////////////////////////////////////////////////////////////
		m_nUsedATPDBSUserItem	= 0;
		m_nATPDBSUserItem		= 1000;//�û�Ĭ��1000
		m_pATPDBSUser			= new struATPDataBaseUser[m_nATPDBSUserItem];
		if (NULL == m_pATPDBSUser)
		{
			return NEWERROR;
		}
		ZeroMemory((char*)m_pATPDBSUser,m_nATPDBSUserItem*sizeof(struATPDataBaseUser));
		//////////////////////////////////////////////////////////////////////////
		SaveRegistSaveData();//��������
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
	//�ж��ڴ��Ƿ���
	//***






	/**
	�ж��Ƿ��Ѿ�������ͬ����
	*/
	for (int i=0;i<m_nUsedATPDBSManagerItem;i++)
	{
		//����ԱID
		//����ԱID�����ظ�
		if (0==strcmp(m_pATPDBSManager[i].szID,pInATPDBSManager->szID))
		{
			//�����ظ�
			//�жϸ�ID�Ƿ�ɾ����
			if (m_pATPDBSManager[i].nDeleteMark == FALSE)
			{
				nRet = EXISTDATA;
				goto END__ADDMANAGER;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	memcpy((char *)&m_pATPDBSManager[m_nUsedATPDBSManagerItem],(char *)pInATPDBSManager,sizeof struATPDataBaseManager);
	//��ŵ���
	if (m_nUsedATPDBSManagerItem == 0)
	{
		m_pATPDBSManager[m_nUsedATPDBSManagerItem].nSerialNumber = 1;
	} 
	else
	{
		m_pATPDBSManager[m_nUsedATPDBSManagerItem].nSerialNumber = m_pATPDBSManager[m_nUsedATPDBSManagerItem-1].nSerialNumber + 1;
	}

	//������
	m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerIDs = NULL;
	if (pInATPDBSManager->nServerN>0)
	{
		m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerIDs = new struATPAutoID[pInATPDBSManager->nServerN];
		if (NULL == m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerIDs)
		{
			//�ڴ�NEW�����ع�
			ZeroMemory((char *)&m_pATPDBSManager[m_nUsedATPDBSManagerItem],0);
			nRet = NEWERROR;
			goto END__ADDMANAGER;
			
		}
		memcpy(m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerIDs,pInATPDBSManager->pServerIDs,pInATPDBSManager->nServerN*sizeof struATPAutoID);
	}

	//
	//��������
	m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerGroupIDs = NULL;
	if (pInATPDBSManager->nServerGroupN>0)
	{
		m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerGroupIDs = new struATPAutoID[pInATPDBSManager->nServerGroupN];
		if (NULL == m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerGroupIDs)
		{
			//�ڴ�NEW�����ع�
			delete m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerIDs;
			ZeroMemory((char *)&m_pATPDBSManager[m_nUsedATPDBSManagerItem],0);
			nRet = NEWERROR;
			goto END__ADDMANAGER;

		}
		memcpy(m_pATPDBSManager[m_nUsedATPDBSManagerItem].pServerGroupIDs,pInATPDBSManager->pServerGroupIDs,pInATPDBSManager->nServerGroupN*sizeof struATPAutoID);
	}

	//ʹ�ñ��+1
	m_nUsedATPDBSManagerItem += 1;


	//�ɹ��������������
	if (NULL == pOutATPDBSManager)
	{
		nRet = ZERORECORD;
		goto END__ADDMANAGER;
		
	}
	memcpy((char *)pOutATPDBSManager,(char *)&m_pATPDBSManager[m_nUsedATPDBSManagerItem-1],sizeof struATPDataBaseManager);

END__ADDMANAGER:

	SaveRegistSaveData();//��������
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
	�ж��Ƿ��Ѿ�������ͬ����
	*/
	for (int i=0;i<m_nUsedATPDBSManagerItem;i++)
	{
		//�Ƚ�nSerialNumber����ȵĹ���ԱID
		if (m_pATPDBSManager[i].nSerialNumber != pATPDBSManager->nSerialNumber)
		{
			//����ԱID
			//���ܴ�����ͬID
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


	//ȷ����������ͬһ���ڴ��
	if (m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nSerialNumber == pATPDBSManager->nSerialNumber)
	{
		//������copy����ʱ���ڴ�
		memcpy((char *)&_ATPDBSManagerTem,(char *)pATPDBSManager,sizeof struATPDataBaseManager);
		_ATPDBSManagerTem.nCreateDate	= m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nCreateDate;
		_ATPDBSManagerTem.nCreateTime	= m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nCreateTime;
		_ATPDBSManagerTem.nLastDate		= m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nLastDate;
		_ATPDBSManagerTem.nLastTime		= m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nLastTime;






		//������
		_ATPDBSManagerTem.pServerIDs = NULL;
		if (_ATPDBSManagerTem.nServerN>0)
		{
			_ATPDBSManagerTem.pServerIDs = new struATPAutoID[_ATPDBSManagerTem.nServerN];
			if (NULL == _ATPDBSManagerTem.pServerIDs)
			{
				//NEW����
				nRet = NEWERROR;
				goto END__MODIFYMANAGER;
			}
			memcpy((char *)_ATPDBSManagerTem.pServerIDs,(char *)pATPDBSManager->pServerIDs,_ATPDBSManagerTem.nServerN*sizeof struATPAutoID);

		}


		//��������
		_ATPDBSManagerTem.pServerGroupIDs = NULL;
		if (_ATPDBSManagerTem.nServerGroupN>0)
		{
			_ATPDBSManagerTem.pServerGroupIDs = new struATPAutoID[_ATPDBSManagerTem.nServerGroupN];
			if (NULL == _ATPDBSManagerTem.pServerGroupIDs)
			{
				//NEW����
				delete _ATPDBSManagerTem.pServerIDs;
				nRet = NEWERROR;
				goto END__MODIFYMANAGER;
			}
			memcpy((char *)_ATPDBSManagerTem.pServerGroupIDs,(char *)pATPDBSManager->pServerGroupIDs,_ATPDBSManagerTem.nServerGroupN*sizeof struATPAutoID);
		}
		//ɾ��֮ǰ��ָ���ָ��
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
	//ȷ����������ͬһ���ڴ��
	if (m_pATPDBSManager[pATPDBSManager->nSerialNumber-1].nSerialNumber != 1/*����ɾ���Լ�*/ && 
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

	//��������Ա
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
	
	//�ͷ�  *ppATPDBSManager  ������
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
	//�鿴�ڴ�ʹ�����
	//***

	/**
	�ж��Ƿ��Ѿ�������ͬ����
	*/
	for (int i=0;i<m_nUsedATPDBSServerGroupItem;i++)
	{
		//������������
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
	
	
	
	
	
	//��ŵ���
	if (m_nUsedATPDBSServerGroupItem == 0)
	{
		m_pATPDBSServerGroup[m_nUsedATPDBSServerGroupItem].nID = 1;
	} 
	else
	{
		m_pATPDBSServerGroup[m_nUsedATPDBSServerGroupItem].nID = m_pATPDBSServerGroup[m_nUsedATPDBSServerGroupItem-1].nID + 1;
	}
	//ʹ�ñ��+1
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
	�ж��Ƿ��Ѿ�������ͬ����
	*/
	for (int i=0;i<m_nUsedATPDBSServerGroupItem;i++)
	{
		if (m_pATPDBSServerGroup[i].nID != pATPDBSServerGroup->nID)
		{
			//������������
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

	//ȷ����������ͬһ���ڴ��
	if (m_pATPDBSServerGroup[pATPDBSServerGroup->nID-1].nID == pATPDBSServerGroup->nID)
	{
		m_pATPDBSServerGroup[pATPDBSServerGroup->nID-1].nParentID = pATPDBSServerGroup->nParentID;			//	����ID
		strcpy(m_pATPDBSServerGroup[pATPDBSServerGroup->nID-1].szName,pATPDBSServerGroup->szName);			//	����
		memcpy(m_pATPDBSServerGroup[pATPDBSServerGroup->nID-1].szExplain,pATPDBSServerGroup->szExplain,128);		//	˵��
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
	//ȷ����������ͬһ���ڴ��
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
	//�ͷ�  *ppATPDBSServerGroup  ������
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
	//�鿴�ڴ�ʹ�����
	//***
	



	/**
	�ж��Ƿ��Ѿ�������ͬ����
	*/

	for (int i=0;i<m_nUsedATPDBSServerItem;i++)
	{
		//IP �� ���������� �������ظ�
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
	
	//��ŵ���
	if (m_nUsedATPDBSServerItem == 0)
	{
		m_pATPDBSServer[m_nUsedATPDBSServerItem].nID = 1;
	} 
	else
	{
		m_pATPDBSServer[m_nUsedATPDBSServerItem].nID = m_pATPDBSServer[m_nUsedATPDBSServerItem-1].nID + 1;
	}
	//ʹ�ñ��+1
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
	�ж��Ƿ��Ѿ�������ͬ����
	*/

	for (int i=0;i<m_nUsedATPDBSServerItem;i++)
	{
		if (m_pATPDBSServer[i].nID != pATPDBSServer->nID)
		{		
			//IP �� ���������� �������ظ�
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
	//ȷ����������ͬһ���ڴ��
	if (m_pATPDBSServer[pATPDBSServer->nID-1].nID == pATPDBSServer->nID)
	{
		//memcpy((char *)&m_pATPDBSServer[pATPDBSServer->nID-1],(char *)pATPDBSServer,sizeof struATPDataBaseServer);


		//m_pATPDBSServer[pATPDBSServer->nID-1].nID;						//	������ID �Զ����� Ψһ
		strcpy(m_pATPDBSServer[pATPDBSServer->nID-1].szName,pATPDBSServer->szName);					//	��������
		strcpy(m_pATPDBSServer[pATPDBSServer->nID-1].szIP,pATPDBSServer->szIP);					//	������IP
		m_pATPDBSServer[pATPDBSServer->nID-1].nIPType		= pATPDBSServer->nIPType;					//	4,6
		m_pATPDBSServer[pATPDBSServer->nID-1].nPort			= pATPDBSServer->nPort;						//	�������˿ں�
		m_pATPDBSServer[pATPDBSServer->nID-1].nGroupID		= pATPDBSServer->nGroupID;					//	��������
		m_pATPDBSServer[pATPDBSServer->nID-1].nAlloc		= pATPDBSServer->nAlloc;						//	����ԭ��
		//m_pATPDBSServer[pATPDBSServer->nID-1].nCreateDate	= pATPDBSServer->nCreateDate;				//	��������
		//m_pATPDBSServer[pATPDBSServer->nID-1].nCreateTime	= pATPDBSServer->nCreateTime;				//	����ʱ��
		//m_pATPDBSServer[pATPDBSServer->nID-1].nDeleteMark;				//	ɾ�����
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
	//ȷ����������ͬһ���ڴ��
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
		//û�м�¼
		return ZERORECORD;
	}

	*ppATPDBSServer = new struATPDataBaseServer[m_nUsedATPDBSServerItem];
	if (NULL == *ppATPDBSServer)
	{
		return NEWERROR;
	}

	//����
	int i=0,nItems=0/*���ϼ�¼����*/;
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
		//û��һ����¼���ͷ��Ѿ�������ڴ�
		delete *ppATPDBSServer;
		*ppATPDBSServer = NULL;
	}

	//�ͷ�  *ppATPDBSServerGroup  ������
	return nItems;
}

int CATPDataBase::TranslationPermission(int nAccountType,int nPermissionType)
{
	switch(nPermissionType)
	{
	case ID_ATPMANAGE_ADDALGORITHM		:
	case ID_ATPMANAGE_ADDALGORITHMGROUP		://����㷨���㷨��
		{
			return MANAGER_ADDALGO;
		}
		break;
	case ID_ATPMANAGE_DELETEALGORITHM		:
	case ID_ATPMANAGE_DELETEALGORITHMGROUP		://ɾ���㷨���㷨��
		{
			return MANAGER_DELALGO;
		}
		break;
	case ID_ATPMANAGE_MODIFYALGORITHMINFO		:
	case ID_ATPMANAGE_MODIFYALGORITHMGROUP		://�޸��㷨���㷨��
		{
			return MANAGER_MODIFYALGO;
		}
		break;
	case ID_ATPMANAGE_QUERYALGORITHMINFO		:
	case ID_ATPMANAGE_QUERYALGORITHMGROUPINFO		://��ѯ�㷨���㷨��
		{
			return MANAGER_VIEWALGO;
		}
		break;
	case ID_ATPMANAGE_ADDUSER		:
	case ID_ATPMANAGE_ADDUSERGROUP		://����û����û���
		{
			return MANAGER_ADDUSER;
		}
		break;
	case ID_ATPMANAGE_DELETEUSER		:
	case ID_ATPMANAGE_DELETEUSERGROUP		://ɾ���û����û���
		{
			return MANAGER_DELUSER;
		}
		break;
	case ID_ATPMANAGE_MODIFYUSER		:
	case ID_ATPMANAGE_MODIFYUSERGROUP		://�޸��û����û���
		{
			return MANAGER_MODIFYUSER;
		}
		break;
	case ID_ATPMANAGE_QUERYUSERINFO		:
	case ID_ATPMANAGE_QUERYUSERGROUPINFO		://��ѯ�û����û���
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
						//ӵ�и�Ȩ��
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
						//ӵ�и�Ȩ��
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
	//�ͷ�  *ppATPDBSServerGroup  ������
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
	//�ж��ڴ��Ƿ���
	//***


	/**
	�ж��Ƿ��Ѿ�������ͬ����
	*/
	for (int i=0;i<m_nUsedATPDBSUserGroupItem;i++)
	{
		//ͬһ����Ա�²�������ͬ��
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
	//��ŵ���
	if (m_nUsedATPDBSUserGroupItem == 0)
	{
		pATPDBSUserGroupTemp->nID = 1;
	} 
	else
	{
		pATPDBSUserGroupTemp->nID = m_pATPDBSUserGroup[m_nUsedATPDBSUserGroupItem-1].nID + 1;
	}

	//�㷨
	pATPDBSUserGroupTemp->pAlgorithmIDs = NULL;
	if (pATPDBSUserGroup->nAlgorithmN>0)
	{
		pATPDBSUserGroupTemp->pAlgorithmIDs = new struATPAutoAlgoID[pATPDBSUserGroup->nAlgorithmN];
		if (NULL == pATPDBSUserGroupTemp->pAlgorithmIDs)
		{
			//�ڴ�NEW�����ع�
			ZeroMemory((char *)pATPDBSUserGroupTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSERGROUP;
			
		}
		memcpy(pATPDBSUserGroupTemp->pAlgorithmIDs,pATPDBSUserGroup->pAlgorithmIDs,pATPDBSUserGroup->nAlgorithmN*sizeof struATPAutoAlgoID);

	}
	//
	//�㷨��
	pATPDBSUserGroupTemp->pAlgorithmGroupIDs = NULL;
	if (pATPDBSUserGroup->nAlgorithmGroupN>0)
	{
		pATPDBSUserGroupTemp->pAlgorithmGroupIDs = new struATPAutoID[pATPDBSUserGroup->nAlgorithmGroupN];
		if (NULL == pATPDBSUserGroupTemp->pAlgorithmGroupIDs)
		{
			//�ڴ�NEW�����ع�
			delete pATPDBSUserGroupTemp->pAlgorithmIDs;
			ZeroMemory((char *)pATPDBSUserGroupTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSERGROUP;
			
		}
		memcpy(pATPDBSUserGroupTemp->pAlgorithmGroupIDs,pATPDBSUserGroup->pAlgorithmGroupIDs,pATPDBSUserGroup->nAlgorithmGroupN*sizeof struATPAutoID);
	}
	//������
	pATPDBSUserGroupTemp->pServerIDs = NULL;
	if (pATPDBSUserGroup->nServerN>0)
	{
		pATPDBSUserGroupTemp->pServerIDs = new struATPAutoID[pATPDBSUserGroup->nServerN];
		if (NULL == pATPDBSUserGroupTemp->pServerIDs)
		{
			//�ڴ�NEW�����ع�
			delete pATPDBSUserGroupTemp->pAlgorithmIDs;
			delete pATPDBSUserGroupTemp->pServerIDs;
			ZeroMemory((char *)pATPDBSUserGroupTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSERGROUP;
			
		}
		memcpy(pATPDBSUserGroupTemp->pServerIDs,pATPDBSUserGroup->pServerIDs,pATPDBSUserGroup->nServerN*sizeof struATPAutoID);

	}
	//
	//��������
	pATPDBSUserGroupTemp->pServerGroupIDs = NULL;
	if (pATPDBSUserGroup->nServerGroupN>0)
	{
		pATPDBSUserGroupTemp->pServerGroupIDs = new struATPAutoID[pATPDBSUserGroup->nServerGroupN];
		if (NULL == pATPDBSUserGroupTemp->pServerGroupIDs)
		{
			//�ڴ�NEW�����ع�
			delete pATPDBSUserGroupTemp->pAlgorithmIDs;
			delete pATPDBSUserGroupTemp->pServerIDs;
			delete pATPDBSUserGroupTemp->pServerGroupIDs;
			ZeroMemory((char *)pATPDBSUserGroupTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSERGROUP;
			
		}
		memcpy(pATPDBSUserGroupTemp->pServerGroupIDs,pATPDBSUserGroup->pServerGroupIDs,pATPDBSUserGroup->nServerGroupN*sizeof struATPAutoID);

	}
	//ʹ�ñ��+1
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
	�ж��Ƿ��Ѿ�������ͬ����
	*/
	for (int i=0;i<m_nUsedATPDBSUserGroupItem;i++)
	{
		if (m_pATPDBSUserGroup[i].nID != pATPDBSUserGroup->nID)
		{
			//ͬһ����Ա�²�������ͬ��
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

	//ȷ����������ͬһ���ڴ��
	if (m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].nID == pATPDBSUserGroup->nID)
	{
		//������copy����ʱ���ڴ�
		memcpy((char *)&_ATPDBSUserGroupTemp,(char *)pATPDBSUserGroup,sizeof struATPDataBaseUserGroup);
		strcpy(_ATPDBSUserGroupTemp.szManagerID,m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].szManagerID);
		_ATPDBSUserGroupTemp.nCreateDate = m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].nCreateDate;
		_ATPDBSUserGroupTemp.nCreateTime = m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].nCreateTime;
		_ATPDBSUserGroupTemp.nDeleteMark = m_pATPDBSUserGroup[pATPDBSUserGroup->nID-1].nDeleteMark;
		



		//�㷨
		if (pATPDBSUserGroup->nAlgorithmN>0)
		{
			_ATPDBSUserGroupTemp.pAlgorithmIDs = NULL;
			_ATPDBSUserGroupTemp.pAlgorithmIDs = new struATPAutoAlgoID[pATPDBSUserGroup->nAlgorithmN];
			if (NULL == _ATPDBSUserGroupTemp.pAlgorithmIDs)
			{
				//�ڴ�NEW����
				nRet = NEWERROR;
				goto END__MODIFYUSERGROUP;
				
			}
			memcpy(_ATPDBSUserGroupTemp.pAlgorithmIDs,pATPDBSUserGroup->pAlgorithmIDs,pATPDBSUserGroup->nAlgorithmN*sizeof struATPAutoAlgoID);
		}

		if (pATPDBSUserGroup->nAlgorithmGroupN>0)
		{
			//�㷨��
			_ATPDBSUserGroupTemp.pAlgorithmGroupIDs = NULL;
			_ATPDBSUserGroupTemp.pAlgorithmGroupIDs = new struATPAutoID[pATPDBSUserGroup->nAlgorithmGroupN];
			if (NULL == _ATPDBSUserGroupTemp.pAlgorithmGroupIDs)
			{
				//�ڴ�NEW����
				delete _ATPDBSUserGroupTemp.pAlgorithmIDs;
				nRet = NEWERROR;
				goto END__MODIFYUSERGROUP;
				
			}
			memcpy(_ATPDBSUserGroupTemp.pAlgorithmGroupIDs,pATPDBSUserGroup->pAlgorithmGroupIDs,pATPDBSUserGroup->nAlgorithmGroupN*sizeof struATPAutoID);

		}

		if (_ATPDBSUserGroupTemp.nServerN>0)
		{
			//������
			_ATPDBSUserGroupTemp.pServerIDs = NULL;
			_ATPDBSUserGroupTemp.pServerIDs = new struATPAutoID[_ATPDBSUserGroupTemp.nServerN];
			if (NULL == _ATPDBSUserGroupTemp.pServerIDs)
			{
				//NEW����
				delete _ATPDBSUserGroupTemp.pAlgorithmIDs;
				delete _ATPDBSUserGroupTemp.pAlgorithmGroupIDs;
				nRet = NEWERROR;
				goto END__MODIFYUSERGROUP;
				
			}
			memcpy((char *)_ATPDBSUserGroupTemp.pServerIDs,(char *)pATPDBSUserGroup->pServerIDs,_ATPDBSUserGroupTemp.nServerN*sizeof struATPAutoID);


		}

		if (_ATPDBSUserGroupTemp.nServerGroupN>0)
		{
			//��������
			_ATPDBSUserGroupTemp.pServerGroupIDs = NULL;
			_ATPDBSUserGroupTemp.pServerGroupIDs = new struATPAutoID[_ATPDBSUserGroupTemp.nServerGroupN];
			if (NULL == _ATPDBSUserGroupTemp.pServerGroupIDs)
			{
				//NEW����
				delete _ATPDBSUserGroupTemp.pAlgorithmIDs;
				delete _ATPDBSUserGroupTemp.pAlgorithmGroupIDs;
				delete _ATPDBSUserGroupTemp.pServerGroupIDs;
				nRet = NEWERROR;
				goto END__MODIFYUSERGROUP;
				
			}
			memcpy((char *)_ATPDBSUserGroupTemp.pServerGroupIDs,(char *)pATPDBSUserGroup->pServerGroupIDs,_ATPDBSUserGroupTemp.nServerGroupN*sizeof struATPAutoID);
		}



		//ɾ��֮ǰ��ָ���ָ��
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
	//ȷ����������ͬһ���ڴ��
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
	
	//�ͷ�  *ppATPDBSUserGroup  ������
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
	//�ж��ڴ��Ƿ���
	//***

	/**
	�ж��Ƿ��Ѿ�������ͬ����
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
	//��ŵ���
	if (m_nUsedATPDBSUserItem == 0)
	{
		pATPDBSUserTemp->nSerialNumber = 1;
	} 
	else
	{
		pATPDBSUserTemp->nSerialNumber = m_pATPDBSUser[m_nUsedATPDBSUserItem-1].nSerialNumber + 1;
	}
	//�ʽ��ʺ�
	pATPDBSUserTemp->pATPFund = NULL;
	if (pATPDBSUser->nCanAssociateFundsAccount>0)
	{
		pATPDBSUserTemp->pATPFund = new struATPDataBaseFund[pATPDBSUser->nCanAssociateFundsAccount];
		if (NULL == pATPDBSUserTemp->pATPFund)
		{
			//�ڴ�NEW�����ع�
			ZeroMemory((char *)pATPDBSUserTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSER;
			
		}
		memcpy(pATPDBSUserTemp->pATPFund,pATPDBSUser->pATPFund,pATPDBSUser->nCanAssociateFundsAccount*sizeof struATPDataBaseFund);
	}
	//�㷨
	pATPDBSUserTemp->pAlgorithmIDs = NULL;
	if (pATPDBSUser->nAlgorithmN>0)
	{
		pATPDBSUserTemp->pAlgorithmIDs = new struATPAutoAlgoID[pATPDBSUser->nAlgorithmN];
		if (NULL == pATPDBSUserTemp->pAlgorithmIDs)
		{
			//�ڴ�NEW�����ع�
			delete pATPDBSUserTemp->pATPFund;
			ZeroMemory((char *)pATPDBSUserTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSER;
			
		}
		memcpy(pATPDBSUserTemp->pAlgorithmIDs,pATPDBSUser->pAlgorithmIDs,pATPDBSUser->nAlgorithmN*sizeof struATPAutoAlgoID);

	}
	//
	//�㷨��
	pATPDBSUserTemp->pAlgorithmGroupIDs = NULL;
	if (pATPDBSUser->nAlgorithmGroupN>0)
	{
		pATPDBSUserTemp->pAlgorithmGroupIDs = new struATPAutoID[pATPDBSUser->nAlgorithmGroupN];
		if (NULL == pATPDBSUserTemp->pAlgorithmGroupIDs)
		{
			//�ڴ�NEW�����ع�
			delete pATPDBSUserTemp->pATPFund;
			delete pATPDBSUserTemp->pAlgorithmIDs;
			ZeroMemory((char *)pATPDBSUserTemp,0);
			nRet = NEWERROR;
			goto END__ADDUSER;
			
		}
		memcpy(pATPDBSUserTemp->pAlgorithmGroupIDs,pATPDBSUser->pAlgorithmGroupIDs,pATPDBSUser->nAlgorithmGroupN*sizeof struATPAutoID);
	}
	//������
	pATPDBSUserTemp->pServerIDs = NULL;
	if (pATPDBSUser->nServerN>0)
	{
		pATPDBSUserTemp->pServerIDs = new struATPAutoID[pATPDBSUser->nServerN];
		if (NULL == pATPDBSUserTemp->pServerIDs)
		{
			//�ڴ�NEW�����ع�
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
	//��������
	pATPDBSUserTemp->pServerGroupIDs = NULL;
	if (pATPDBSUser->nServerGroupN>0)
	{
		pATPDBSUserTemp->pServerGroupIDs = new struATPAutoID[pATPDBSUser->nServerGroupN];
		if (NULL == pATPDBSUserTemp->pServerGroupIDs)
		{
			//�ڴ�NEW�����ع�
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
	//ʹ�ñ��+1
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
	�ж��Ƿ��Ѿ�������ͬ����
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
	//ȷ����������ͬһ���ڴ��
	if (m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nSerialNumber == pATPDBSUser->nSerialNumber)
	{
		//������copy����ʱ���ڴ�
		memcpy((char *)&_ATPDBSUserTemp,(char *)pATPDBSUser,sizeof struATPDataBaseUser);
		strcpy(_ATPDBSUserTemp.szManagerID,m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].szManagerID);
		_ATPDBSUserTemp.nCreateDate = m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nCreateDate;
		_ATPDBSUserTemp.nCreateTime = m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nCreateTime;
		_ATPDBSUserTemp.nLastDate = m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nLastDate;
		_ATPDBSUserTemp.nLastTime = m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nLastTime;
		_ATPDBSUserTemp.nDeleteMark = m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nDeleteMark;

		//�ʽ��ʺ�
		_ATPDBSUserTemp.pATPFund = NULL;
		if (pATPDBSUser->nCanAssociateFundsAccount>0)
		{
			_ATPDBSUserTemp.pATPFund = new struATPDataBaseFund[pATPDBSUser->nCanAssociateFundsAccount];
			if (NULL == _ATPDBSUserTemp.pATPFund)
			{
				//�ڴ�NEW����
				nRet = NEWERROR;
				goto END__MODIFYUSER;
				
			}
			memcpy(_ATPDBSUserTemp.pATPFund,pATPDBSUser->pATPFund,pATPDBSUser->nCanAssociateFundsAccount*sizeof struATPDataBaseFund);

		}
		//�㷨
		_ATPDBSUserTemp.pAlgorithmIDs = NULL;
		if (pATPDBSUser->nAlgorithmN>0)
		{
			_ATPDBSUserTemp.pAlgorithmIDs = new struATPAutoAlgoID[pATPDBSUser->nAlgorithmN];
			if (NULL == _ATPDBSUserTemp.pAlgorithmIDs)
			{
				//�ڴ�NEW����
				delete _ATPDBSUserTemp.pATPFund;
				nRet = NEWERROR;
				goto END__MODIFYUSER;
				
			}
			memcpy(_ATPDBSUserTemp.pAlgorithmIDs,pATPDBSUser->pAlgorithmIDs,pATPDBSUser->nAlgorithmN*sizeof struATPAutoAlgoID);

		}
		//
		//�㷨��
		_ATPDBSUserTemp.pAlgorithmGroupIDs = NULL;
		if (pATPDBSUser->nAlgorithmGroupN>0)
		{
			_ATPDBSUserTemp.pAlgorithmGroupIDs = new struATPAutoID[pATPDBSUser->nAlgorithmGroupN];
			if (NULL == _ATPDBSUserTemp.pAlgorithmGroupIDs)
			{
				//�ڴ�NEW����
				delete _ATPDBSUserTemp.pATPFund;
				delete _ATPDBSUserTemp.pAlgorithmIDs;
				nRet = NEWERROR;
				goto END__MODIFYUSER;
				
			}
			memcpy(_ATPDBSUserTemp.pAlgorithmGroupIDs,pATPDBSUser->pAlgorithmGroupIDs,pATPDBSUser->nAlgorithmGroupN*sizeof struATPAutoID);

		}

		//������
		_ATPDBSUserTemp.pServerIDs = NULL;
		if (_ATPDBSUserTemp.nServerN>0)
		{
			_ATPDBSUserTemp.pServerIDs = new struATPAutoID[_ATPDBSUserTemp.nServerN];
			if (NULL == _ATPDBSUserTemp.pServerIDs)
			{
				//NEW����
				delete _ATPDBSUserTemp.pATPFund;
				delete _ATPDBSUserTemp.pAlgorithmIDs;
				delete _ATPDBSUserTemp.pAlgorithmGroupIDs;
				nRet = NEWERROR;
				goto END__MODIFYUSER;
				
			}
			memcpy((char *)_ATPDBSUserTemp.pServerIDs,(char *)pATPDBSUser->pServerIDs,_ATPDBSUserTemp.nServerN*sizeof struATPAutoID);

		}

		//��������
		_ATPDBSUserTemp.pServerGroupIDs = NULL;
		if (_ATPDBSUserTemp.nServerGroupN>0)
		{
			_ATPDBSUserTemp.pServerGroupIDs = new struATPAutoID[_ATPDBSUserTemp.nServerGroupN];
			if (NULL == _ATPDBSUserTemp.pServerGroupIDs)
			{
				//NEW����
				delete _ATPDBSUserTemp.pATPFund;
				delete _ATPDBSUserTemp.pAlgorithmIDs;
				delete _ATPDBSUserTemp.pAlgorithmGroupIDs;
				delete _ATPDBSUserTemp.pServerGroupIDs;
				nRet = NEWERROR;
				goto END__MODIFYUSER;
			}
			memcpy((char *)_ATPDBSUserTemp.pServerGroupIDs,(char *)pATPDBSUser->pServerGroupIDs,_ATPDBSUserTemp.nServerGroupN*sizeof struATPAutoID);
		}

		//ɾ��֮ǰ��ָ���ָ��
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
	//ȷ����������ͬһ���ڴ��
	if (m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nSerialNumber == pATPDBSUser->nSerialNumber &&
		0 == strcmp(m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].szUserID,pATPDBSUser->szUserID))
	{
		m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nStatus		= pATPDBSUser->nStatus;
		m_pATPDBSUser[pATPDBSUser->nSerialNumber-1].nDeleteMark	= TRUE;
	}
	else
	{
		return ZERORECORD;//ɾ��ʧ��
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
		//û�м�¼
		return ZERORECORD;
	}

	

	//����
	int i=0,j=0,nItems=0/*���ϼ�¼����*/;
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

	//�ͷ�  *ppATPDBSServerGroup  ������
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
	//�鿴�ڴ�ʹ�����
	//***

	/**
	�ж��Ƿ��Ѿ�������ͬ����
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
	//��ŵ���
	if (m_nUsedATPDBSAlgorithmGroupItem == 0)
	{
		m_pATPDBSAlgorithmGroup[m_nUsedATPDBSAlgorithmGroupItem].nID = 1;
	} 
	else
	{
		m_pATPDBSAlgorithmGroup[m_nUsedATPDBSAlgorithmGroupItem].nID = m_pATPDBSAlgorithmGroup[m_nUsedATPDBSAlgorithmGroupItem-1].nID + 1;
	}
	//ʹ�ñ��+1
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
	�ж��Ƿ��Ѿ�������ͬ����
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
	//ȷ����������ͬһ���ڴ��
	if (m_pATPDBSAlgorithmGroup[pATPDBSAlgorithmGroup->nID-1].nID == pATPDBSAlgorithmGroup->nID)
	{
		m_pATPDBSAlgorithmGroup[pATPDBSAlgorithmGroup->nID-1].nParentID = pATPDBSAlgorithmGroup->nParentID;						//	����ID
		strcpy(m_pATPDBSAlgorithmGroup[pATPDBSAlgorithmGroup->nID-1].szName,pATPDBSAlgorithmGroup->szName);						//	����
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
	//ȷ����������ͬһ���ڴ��
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

	//�ͷ�  *ppATPDBSAlgorithmGroup  ������
	return nCount;
}


//////////////////////////////////////////////////////////////////////////
//����㷨
int CATPDataBase::AddAlgorithm(IN struATPDataBaseAlgorithm *pATPDBSAlgorithm,OUT struATPDataBaseAlgorithm *pOutData,BOOL bScript)
{
	int nRet = 0;
	CTime t = CTime::GetCurrentTime();
	if (NULL == m_pATPDBSAlgorithm)
	{
		nRet = NOTINIT;
		goto END__ADDALGORITHM;
		
	}
	//�ж��ڴ��Ƿ���
	//***


	/**
	�ж��Ƿ��Ѿ�������ͬ����
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
	//��ѯ���㷨ID�Ƿ����
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


	//��ŵ���
	if (m_nUsedATPDBSAlgorithmItem == 0)
	{
		m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].nSerialNumber = 1;
	} 
	else
	{
		m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].nSerialNumber = m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem-1].nSerialNumber + 1;
	}

	//�㷨����
	m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParams = NULL;
	if (pATPDBSAlgorithm->nParams>0)
	{
		m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParams = new struATPDataBaseAlgorithmParam[pATPDBSAlgorithm->nParams];
		if (NULL == m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParams)
		{
			//�ڴ�NEW�����ع�
			ZeroMemory((char *)&m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem],0);
			nRet = NEWERROR;
			goto END__ADDALGORITHM;
		}
		memcpy(m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParams,pATPDBSAlgorithm->pATPAlgorithmParams,pATPDBSAlgorithm->nParams*sizeof struATPDataBaseAlgorithmParam);

	}


	//�㷨��������ֵ
	m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParamsEX = NULL;
	if (pATPDBSAlgorithm->nParamsEx>0)
	{
		m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParamsEX = new struATPDataBaseAlgorithmParamEX[pATPDBSAlgorithm->nParamsEx];
		if (NULL == m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParamsEX)
		{
			//�ڴ�NEW�����ع�
			ZeroMemory((char *)&m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem],0);
			nRet = NEWERROR;
			goto END__ADDALGORITHM;
		}
		memcpy(m_pATPDBSAlgorithm[m_nUsedATPDBSAlgorithmItem].pATPAlgorithmParamsEX,pATPDBSAlgorithm->pATPAlgorithmParamsEX,pATPDBSAlgorithm->nParamsEx*sizeof struATPDataBaseAlgorithmParamEX);
	}
	//ʹ�ñ��+1
	m_nUsedATPDBSAlgorithmItem += 1;

	if (NULL == pOutData)
	{
		nRet = ZERORECORD;
		goto END__ADDALGORITHM;
	}
	//���ظո���ӵ��㷨��Ϣ
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
	�ж��Ƿ��Ѿ�������ͬ����
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
	//ȷ����������ͬһ���ڴ��
	if (m_pATPDBSAlgorithm[pATPDBSAlgorithm->nSerialNumber-1].nSerialNumber == pATPDBSAlgorithm->nSerialNumber)
	{
		//������copy����ʱ���ڴ�
		memcpy((char *)&_ATPDBSAlgorithmTemp,(char *)pATPDBSAlgorithm,sizeof struATPDataBaseAlgorithm);
		/*
		//�㷨����
		_ATPDBSAlgorithmTemp.pATPAlgorithmParams = NULL;
		if (_ATPDBSAlgorithmTemp.nParams>0)
		{
			_ATPDBSAlgorithmTemp.pATPAlgorithmParams = new struATPDataBaseAlgorithmParam[_ATPDBSAlgorithmTemp.nParams];
			if (NULL == _ATPDBSAlgorithmTemp.pATPAlgorithmParams)
			{
				//NEW����

				return NEWERROR;
			}
			memcpy((char *)_ATPDBSAlgorithmTemp.pATPAlgorithmParams,(char *)pATPDBSAlgorithm->pATPAlgorithmParams,_ATPDBSAlgorithmTemp.nParams*sizeof struATPDataBaseAlgorithmParam);
		}
		//�㷨��������ֵ
		_ATPDBSAlgorithmTemp.pATPAlgorithmParamsEX = NULL;
		if (_ATPDBSAlgorithmTemp.nParamsEx>0)
		{
			_ATPDBSAlgorithmTemp.pATPAlgorithmParamsEX = new struATPDataBaseAlgorithmParamEX[_ATPDBSAlgorithmTemp.nParamsEx];
			if (NULL == _ATPDBSAlgorithmTemp.pATPAlgorithmParamsEX)
			{
				//NEW����

				return NEWERROR;
			}
			memcpy((char *)_ATPDBSAlgorithmTemp.pATPAlgorithmParamsEX,(char *)pATPDBSAlgorithm->pATPAlgorithmParamsEX,_ATPDBSAlgorithmTemp.nParamsEx*sizeof struATPDataBaseAlgorithmParamEX);

		}
		*/

		//ɾ��֮ǰ��ָ���ָ��
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
	//ȷ����������ͬһ���ڴ��
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

//��ѯ�㷨��Ϣ
int CATPDataBase::QueryAlgorithm(struATPDataBaseAlgorithm_QUERY *pATPDBSAlgorithm_QUERY,IN char *pAccount,OUT struATPDataBaseAlgorithm **ppATPDBSAlgorithm)
{
	if (NULL == m_pATPDBSAlgorithm)
	{
		return NOTINIT;
	}

	if (m_nUsedATPDBSAlgorithmItem<=0)
	{
		//û�м�¼
		return ZERORECORD;
	}
	
	//���ٷ���ֵ���ڴ棬m_nUsedATPDBSAlgorithmItem��
	*ppATPDBSAlgorithm = new struATPDataBaseAlgorithm[m_nUsedATPDBSAlgorithmItem];
	if (NULL == *ppATPDBSAlgorithm)
	{
		return NEWERROR;
	}
	
	int i=0,nItems=0/*���ϼ�¼����*/;
	for (;i<m_nUsedATPDBSAlgorithmItem;i++)
	{
		//�ѷ����������㷨��Ϣ����������ֵ��
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
// 		//�ѷ����������㷨��Ϣ����������ֵ��
// 		if (0==strcmp(m_pATPDBSAlgorithm[i].szManagerID,pAccount) && (pATPDBSAlgorithm_QUERY->nID == m_pATPDBSAlgorithm[i].nGroupID || pATPDBSAlgorithm_QUERY->nID == 0))
// 		{
// 			memcpy((char *)&(*ppATPDBSAlgorithm)[j],&m_pATPDBSAlgorithm[i],sizeof struATPDataBaseAlgorithm);
// 			j++;
// 		}
// 	}



	//�ͷ�  *ppATPDBSServerGroup  ������
	//���ط��������ĸ���
	return nItems;
}



//��֤�û� 
int CATPDataBase::UserLogin(IN const char *pReqData,OUT char **ppAnsData,int *pnLen)
{
	int nAtpAccept_Manager_MsgHeadSize								= sizeof AtpAccept_Manager_MsgHead;
	AtpAccept_Manager_MsgHead *pAtpAccept_Manager_MsgHead			= (AtpAccept_Manager_MsgHead *)pReqData;

	int nAtpAccept_Manager_ValidateUserSize							= sizeof AtpAccept_Manager_ValidateUser;
	AtpAccept_Manager_ValidateUser *pAtpAccept_Manager_ValidateUser = (AtpAccept_Manager_ValidateUser *)&pReqData[nAtpAccept_Manager_MsgHeadSize];
	/************************************************************************/
	/*                      �����û����ݣ�ƥ��  ����֤                                              */
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
		//�ʻ�
		if (0 == strcmp(pAtpAccept_Manager_ValidateUser->szUserName,m_pATPDBSUser[i].szUserID))
		{
			nIsExistAccount = 1;
			//����
			if (0 == strcmp(pAtpAccept_Manager_ValidateUser->szUserPwd,m_pATPDBSUser[i].szPwd))
			{
				nIsCorrectPwd = 1;
				_AtpAccept_Manager_ValidateUser_Result.nUserId = m_pATPDBSUser[i].nSerialNumber;
				_AtpAccept_Manager_ValidateUser_Result.nResult = 0;
				//��Ч����
				CTime t = CTime::GetCurrentTime();
				int nDate = t.GetYear()*10000+t.GetMonth()*100+t.GetDay();
				if (m_pATPDBSUser[i].nAuthorizeBeginDate>nDate || m_pATPDBSUser[i].nAuthorizeEndDate<nDate)
				{
					_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
					strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"��Ч���ѹ�");
					break;
				}

				//IP v4//IP V6
				if ((int)pAtpAccept_Manager_ValidateUser->szLoginIpType == 4 || (int)pAtpAccept_Manager_ValidateUser->szLoginIpType == 6)
				{
					ptr = strstr(m_pATPDBSUser[i].szIPs,pAtpAccept_Manager_ValidateUser->szLoginIp);
					if (ptr)
					{
						//ip���Ƶ�¼
						_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"��IP��¼������");
						break;
					}
				} 
				//mac ��ַ
				if (strlen(pAtpAccept_Manager_ValidateUser->szMac))
				{
					ptr = strstr(m_pATPDBSUser[i].szMacMark,pAtpAccept_Manager_ValidateUser->szMac);
					if (ptr)
					{
						//mac ��ַ ���Ƶ�¼
						_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"��MAC��ַ��¼������");
						break;
					}
				}
				//Ӳ�����к�
				if (strlen(pAtpAccept_Manager_ValidateUser->szDiskSerialNum))
				{
					ptr = strstr(m_pATPDBSUser[i].szDiskNum,pAtpAccept_Manager_ValidateUser->szDiskSerialNum);
					if (ptr)
					{
						//Ӳ�����к� ���Ƶ�¼
						_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"��Ӳ�̵�¼������");
						break;
					}
				}


				//CTime t = CTime::GetCurrentTime(); 
				int nTime = t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();//235959

				//ʱ���
				if (m_pATPDBSUser[i].chLimitTimeMark&128)
				{
					if (m_pATPDBSUser[i].chLimitTimeMark&64)
					{
						if (m_pATPDBSUser[i].nLimitBeginTime[0]<nTime && nTime < m_pATPDBSUser[i].nLimitEndTime[0])
						{
							//��¼ʱ��������
							_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
							strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"��ʱ��ε�¼������");
							break;
						}
					}
					if (m_pATPDBSUser[i].chLimitTimeMark&32)
					{
						if (m_pATPDBSUser[i].nLimitBeginTime[1]<nTime && nTime < m_pATPDBSUser[i].nLimitEndTime[1])
						{
							//��¼ʱ��������
							_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
							strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"��ʱ��ε�¼������");
							break;
						}
					}
				}

				//����
				if (m_pATPDBSUser[i].chLimitWeek&128)
				{
					switch (t.GetDayOfWeek())
					{
					case 1://������
						{
							if (m_pATPDBSUser[i].chLimitWeek&64)
							{
								_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
								strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"�������յ�¼������");
							}
						}
						break;
					case 2://����һ
						{
							if (m_pATPDBSUser[i].chLimitWeek&32)
							{
								_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
								strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"������һ��¼������");
							}
						}
						break;
					case 3://��
						{
							if (m_pATPDBSUser[i].chLimitWeek&16)
							{
								_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
								strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"�����ڶ���¼������");
							}
						}
						break;
					case 4://��
						{
							if (m_pATPDBSUser[i].chLimitWeek&8)
							{
								_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
								strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"����������¼������");
							}
						}
						break;
					case 5://��
						{
							if (m_pATPDBSUser[i].chLimitWeek&4)
							{
								_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
								strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"�������ĵ�¼������");
							}
						}
						break;
					case 6://��
						{
							if (m_pATPDBSUser[i].chLimitWeek&2)
							{
								_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
								strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"���������¼������");
							}
						}
						break;
					case 7://��
						{
							if (m_pATPDBSUser[i].chLimitWeek&1)
							{
								_AtpAccept_Manager_ValidateUser_Result.nResult = -1;
								strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"����������¼������");
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
		strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"�ʻ�������");
	}
	else
	{
		if (nIsCorrectPwd == 0)
		{
			_AtpAccept_Manager_ValidateUser_Result.nResult = -1;

			strcpy(_AtpAccept_Manager_ValidateUser_Result.szError,"�������");
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
//��ȡ�ʽ��˺ŵ���Ϣ 
int CATPDataBase::GetFundAccount(IN const char *pReqData,OUT char **ppAnsData,int *pnLen)
{
	int nAtpAccept_Manager_MsgHeadSize = sizeof AtpAccept_Manager_MsgHead;
	AtpAccept_Manager_MsgHead *pAtpAccept_Manager_MsgHead = (AtpAccept_Manager_MsgHead *)pReqData;

	int nAtpAccept_Manager_UserSize = sizeof AtpAccept_Manager_GetFoundAccount;
	AtpAccept_Manager_GetFoundAccount *pAtpAccept_Manager_ValidateUser = (AtpAccept_Manager_GetFoundAccount *)&pReqData[nAtpAccept_Manager_MsgHeadSize];
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	//�ʽ��ʻ���Ŀ
	int nAtpAccept_Manager_GetFoundAccount_Result_HeadSize = sizeof AtpAccept_Manager_GetFoundAccount_Result_Head;
	AtpAccept_Manager_GetFoundAccount_Result_Head _AtpAccept_Manager_GetFoundAccount_Result_Head = {0};
	//�ʽ��ʻ���Ϣ
	int nAtpAccept_Manager_GetFoundAccount_ResultSize = sizeof AtpAccept_Manager_GetFoundAccount_Result;
	AtpAccept_Manager_GetFoundAccount_Result *pAtpAccept_Manager_ValidateUser_Result = NULL;
	int nMark = 0;
	nMark = pAtpAccept_Manager_ValidateUser->nUserId-1;
	if (m_pATPDBSUser[nMark].nDeleteMark == FALSE && pAtpAccept_Manager_ValidateUser->nUserId == m_pATPDBSUser[nMark].nSerialNumber &&
		0 == strcmp(pAtpAccept_Manager_ValidateUser->szUserName,m_pATPDBSUser[nMark].szUserID))
	{
		//�ʽ��ʻ���Ŀ����0
		if (m_pATPDBSUser[nMark].nCanAssociateFundsAccount>0)
		{
			int nFundAccount = m_pATPDBSUser[nMark].nCanAssociateFundsAccount*12;
			pAtpAccept_Manager_ValidateUser_Result = new AtpAccept_Manager_GetFoundAccount_Result[nFundAccount];
			int i=0;/*�ʻ����г�������ѭ������*/
			int j=0;/*�ʻ�����ѭ����*/
			int k=0;/*�г�����ѭ������*/
			for (;j<m_pATPDBSUser[nMark].nCanAssociateFundsAccount;j++)
			{
				//ͬһ�ʻ��Ĳ�ͬ�г����ͱ���
				for (k=0;k<12;k++,i++)
				{
					if (m_pATPDBSUser[nMark].pATPFund[j].szMarkets[k] == -1)
					{
						//�г������ڣ�ֱ������
						break;
					}
					pAtpAccept_Manager_ValidateUser_Result[i].sType = m_pATPDBSUser[nMark].pATPFund[j].szMarkets[k];//�ʻ�����
					strcpy(pAtpAccept_Manager_ValidateUser_Result[i].szFound,m_pATPDBSUser[nMark].pATPFund[j].szFund);//�ʻ�
					strcpy(pAtpAccept_Manager_ValidateUser_Result[i].szOrghID,m_pATPDBSUser[nMark].pATPFund[j].szOrgID);//Ӫҵ��ID
				}
			}
			_AtpAccept_Manager_GetFoundAccount_Result_Head.nItems = i;
		}

	} 
	else//Ϊ�˷�ֹ����nSerialNumber�Ҳ���������
	{
		int n=0;
		for (;n<m_nUsedATPDBSUserItem;n++)
		{
			if (m_pATPDBSUser[n].nDeleteMark == FALSE && pAtpAccept_Manager_ValidateUser->nUserId == m_pATPDBSUser[n].nSerialNumber &&
				0 == strcmp(pAtpAccept_Manager_ValidateUser->szUserName,m_pATPDBSUser[n].szUserID))
			{
				//�ʽ��ʻ���Ŀ����0
				if (m_pATPDBSUser[n].nCanAssociateFundsAccount>0)
				{
					int nFundAccount = m_pATPDBSUser[n].nCanAssociateFundsAccount*12;
					pAtpAccept_Manager_ValidateUser_Result = new AtpAccept_Manager_GetFoundAccount_Result[nFundAccount];
					int i=0;/*�ʻ����г�������ѭ������*/
					int j=0;/*�ʻ�����ѭ����*/
					int k=0;/*�г�����ѭ������*/
					for (;j<m_pATPDBSUser[n].nCanAssociateFundsAccount;j++)
					{
						for (k=0;k<12;k++,i++)
						{
							if (m_pATPDBSUser[n].pATPFund[j].szMarkets[k] == -1)
							{
								//�г������ڣ�ֱ������
								break;
							}
							pAtpAccept_Manager_ValidateUser_Result[i].sType = m_pATPDBSUser[n].pATPFund[j].szMarkets[k];//�ʻ�����
							strcpy(pAtpAccept_Manager_ValidateUser_Result[i].szFound,m_pATPDBSUser[n].pATPFund[j].szFund);//�ʻ�
							strcpy(pAtpAccept_Manager_ValidateUser_Result[i].szOrghID,m_pATPDBSUser[n].pATPFund[j].szOrgID);//Ӫҵ��ID
						}
					}
					_AtpAccept_Manager_GetFoundAccount_Result_Head.nItems = i;
				}
				//�ҵ������������
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


//��ȡ�û�����ʹ�õ��㷨���㷨ʹ����Ϣ ���㷨��Ȩ�������� 
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
	//�㷨�����ṹ��
	int nAtpAccept_Manager_GetAlgoInfo_ResultHeadSize				= sizeof AtpAccept_Manager_GetAlgoInfo_ResultHead;
	AtpAccept_Manager_GetAlgoInfo_ResultHead _AtpAccept_Manager_GetAlgoInfo_ResultHead = {0};

	//�㷨��Ϣ
	int nAtpAccept_Manager_GetAlgoInfo_AlgoInfoSize					= sizeof AtpAccept_Manager_GetAlgoInfo_AlgoInfo;
	AtpAccept_Manager_GetAlgoInfo_AlgoInfo *pAtpAccept_Manager_GetAlgoInfo_AlgoInfo = new AtpAccept_Manager_GetAlgoInfo_AlgoInfo[1024];
	ASSERT(_CrtCheckMemory());
	//�㷨����
	int nAtp_Algoparam_InfoSize										= sizeof Atp_Algoparam_Info;
	Atp_Algoparam_Info *pAtp_Algoparam_Info							= new Atp_Algoparam_Info[1024*20];

	int nAlgoItems				= 0;//�㷨����
	int nAllParamItems			= 0;//��������
	int nAllExParamLen			= 0;//�����������ݳ���
	int nExistenceMark[1024]	={0};//�Ѵ��ڵķŽ�ȥ����
	ASSERT(_CrtCheckMemory());
	BOOL bExit=FALSE;
	//int nAtp_Algoparam_InfoSize = sizeof Atp_Algoparam_Info;

	if (pAtpAccept_Manager_ValidateUser->nUserId == m_pATPDBSUser[pAtpAccept_Manager_ValidateUser->nUserId-1].nSerialNumber &&
		0 == strcmp(pAtpAccept_Manager_ValidateUser->szUserName,m_pATPDBSUser[pAtpAccept_Manager_ValidateUser->nUserId-1].szUserID))
	{
		
		int nMark=pAtpAccept_Manager_ValidateUser->nUserId-1;//�û����±�
		//�㷨��
		int i=0;/*�û����㷨�����ѭ������*/
		int j=0;/*�㷨����ѭ������*/
		int k=0;/*�㷨��������ѭ������*/
		
		str.Format("�û��±�%d���㷨����%d���㷨��%d",nMark,m_pATPDBSUser[nMark].nAlgorithmGroupN,m_nUsedATPDBSAlgorithmItem);
		//AfxMessageBox(str);
		//�û���ӵ���㷨��ID  ��  �����㷨�������㷨���ID   ���бȽ�
		for (i=0;i<m_pATPDBSUser[nMark].nAlgorithmGroupN/*���û�ӵ���㷨�����*/;i++)
		{
			//continue
			for (j=0;j<m_nUsedATPDBSAlgorithmItem/*�����㷨����*/;j++)
			{
				//�㷨�в�����ͬ�㷨����㷨
				if (m_pATPDBSAlgorithm[j].nDeleteMark == FALSE/*���жϸ��㷨�Ƿ�ɾ��*/ && 
					m_pATPDBSUser[nMark].pAlgorithmGroupIDs[i].nID == m_pATPDBSAlgorithm[j].nGroupID/*���û���ӵ���㷨��ID==�㷨������ID*/
					)
				{
					//AfxMessageBox("3224");
					bExit=FALSE;
					for (int nM=0;nM<1024;nM++)
					{
						//�ҵ����һ��Ҳû���ظ�����ӵ�������
						if (nExistenceMark[nM] == 0)
						{
							nExistenceMark[nM]=m_pATPDBSAlgorithm[j].nSerialNumber;
							//bExit = TRUE;
							// ����ѭ��1024��
							break;
						}
						//����Ƿ��ظ�����
						if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[j].nSerialNumber)
						{
							bExit = TRUE;
							break;
						}
					}
					//�ظ����ڡ��������ѭ����
					if (bExit)
					{
						continue;
					}
					memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[j].AlgorithmID,sizeof GUID);
					pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo = m_pATPDBSAlgorithm[j].nParams;
					sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"˵��:%s-�ؼ���:%s-����:%s-����:%s",m_pATPDBSAlgorithm[j].szExplain,m_pATPDBSAlgorithm[j].szKeyword,m_pATPDBSAlgorithm[j].szWarning,m_pATPDBSAlgorithm[j].szStopReason);
					strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[j].szAlgorithmName);

					memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[j].AlgorithVer,sizeof struDataBaseAlgorithmVer);
					pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nAlgoLangType		= m_pATPDBSAlgorithm[j].nLanguageType;
					pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber		= m_pATPDBSAlgorithm[j].nSerialNumber;
					sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[j].szPath,m_pATPDBSAlgorithm[j].szMainDllName);
					//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[j].szPath);
					nAlgoItems++;//�㷨����
					//////////////////////////////////////////////////////////////////////////
										//��ȡ������Ϣ

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
							//������������
							pAtp_Algoparam_Info[nAllParamItems].pExtraData			= new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
							memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[j].pATPAlgorithmParamsEX[nExMark-1].ExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

						}

						nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
						nAllParamItems++;
					}
				}
			}
		}

		//�㷨
		i = 0;/*�û����㷨����ѭ������*/
		j = 0;/*�㷨����ѭ������*/
		k = 0;/*�㷨��������ѭ������*/

		//�û���ӵ�е��㷨ID   ��  �㷨�е�ID   ���бȽ�
		for (i=0;i<m_pATPDBSUser[nMark].nAlgorithmN;i++)
		{
			for (j=0;j<m_nUsedATPDBSAlgorithmItem/*�����㷨����*/;j++)
			{
				//GUID���
				if (m_pATPDBSAlgorithm[j].nDeleteMark			== FALSE && 
					m_pATPDBSUser[nMark].pAlgorithmIDs[i].nID	== m_pATPDBSAlgorithm[j].AlgorithmID)
				{

					bExit=FALSE;
					for (int nM=0;nM<1024;nM++)
					{
						//�ҵ����һ��Ҳû���ظ�
						if (nExistenceMark[nM] == 0)
						{
							nExistenceMark[nM]=m_pATPDBSAlgorithm[j].nSerialNumber;
							//bExit = FALSE;
							// ����ѭ��
							break;
						}
						//�ظ�����
						if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[j].nSerialNumber)
						{
							bExit = TRUE;
							break;
						}
					}
					//�ظ����ڡ��������ѭ����
					if (bExit)
					{
						continue;
					}


					memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[j].AlgorithmID,sizeof GUID);
					pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo		= m_pATPDBSAlgorithm[j].nParams;
					sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"˵��:%s-�ؼ���:%s-����:%s-����:%s",m_pATPDBSAlgorithm[j].szExplain,m_pATPDBSAlgorithm[j].szKeyword,m_pATPDBSAlgorithm[j].szWarning,m_pATPDBSAlgorithm[j].szStopReason);
					strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[j].szAlgorithmName);

					memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[j].AlgorithVer,sizeof struDataBaseAlgorithmVer);
					pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber			= m_pATPDBSAlgorithm[j].nSerialNumber;
					sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[j].szPath,m_pATPDBSAlgorithm[j].szMainDllName);
					//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[j].szPath);
					nAlgoItems++;//�㷨����

					//��ȡ������Ϣ

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
							//������������
							pAtp_Algoparam_Info[nAllParamItems].pExtraData						= new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
							memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[j].pATPAlgorithmParamsEX[nExMark-1].ExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

						}

						nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
						nAllParamItems++;
					}
				}
			}
		}

		//���û���
		i		= 0;//�û����û������ѭ������
		j		= 0;//�û������ѭ������
		k		= 0;
		int x	= 0;// �û�����㷨�����ѭ������
		int y	= 0;//�㷨����ѭ������
		int z	= 0;//�㷨��������ѭ������
		//�û����ֻ��ͬʱ���ĸ��û�����
		for (i=0;i<4;i++)
		{
			//�û������
			if (m_pATPDBSUser[nMark].nGroupIDs[i] > 0)
			{
				//���û������ĸ�λ���� 
				for (j=0;j<m_nUsedATPDBSUserGroupItem;j++)
				{
					//�鵽�û��е��û���ID���û����е�λ��
					if (m_pATPDBSUserGroup[j].nDeleteMark == FALSE &&
						m_pATPDBSUser[nMark].nGroupIDs[i] == m_pATPDBSUserGroup[j].nID)
					{
						//�����û���������Щ�㷨���㷨�飬��TMD���鷳��
						x = 0;// �û�����㷨�����ѭ������
						y = 0;//�㷨����ѭ������
						z = 0;//�㷨��������ѭ������
						//�����û����е��㷨��
						for (x=0;x<m_pATPDBSUserGroup[j].nAlgorithmGroupN;x++)
						{
							for (y=0;y<m_nUsedATPDBSAlgorithmItem;y++)
							{
								//�㷨�в�����ͬ�㷨����㷨
								if (m_pATPDBSAlgorithm[y].nDeleteMark == FALSE && 
									m_pATPDBSUserGroup[j].pAlgorithmGroupIDs[x].nID == m_pATPDBSAlgorithm[y].nGroupID)
								{
									bExit=FALSE;
									for (int nM=0;nM<1024;nM++)
									{
										//�ҵ����һ��Ҳû���ظ�
										if (nExistenceMark[nM] == 0)
										{
											nExistenceMark[nM] = m_pATPDBSAlgorithm[y].nSerialNumber;
											//bExit = TRUE;
											// ����ѭ��
											break;
										}
										//�ظ�����
										if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[y].nSerialNumber)
										{
											bExit = TRUE;
											break;
										}
									}
									//�ظ����ڡ��������ѭ����
									if (bExit)
									{
										continue;
									}

									memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[y].AlgorithmID,sizeof GUID);
									pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo		= m_pATPDBSAlgorithm[j].nParams;
									sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"˵��:%s-�ؼ���:%s-����:%s-����:%s",m_pATPDBSAlgorithm[y].szExplain,m_pATPDBSAlgorithm[y].szKeyword,m_pATPDBSAlgorithm[y].szWarning,m_pATPDBSAlgorithm[y].szStopReason);
									strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[y].szAlgorithmName);

									memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[y].AlgorithVer,sizeof struDataBaseAlgorithmVer);
									pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber			= m_pATPDBSAlgorithm[y].nSerialNumber;
									sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[y].szPath,m_pATPDBSAlgorithm[y].szMainDllName);
									//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[y].szPath);
									nAlgoItems++;//�㷨����

									//��ȡ������Ϣ

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
											//������������
											pAtp_Algoparam_Info[nAllParamItems].pExtraData = new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
											memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[y].pATPAlgorithmParamsEX[nExMark-1].ExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

										}

										nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
										nAllParamItems++;
									}
								}
							}
						}

						//�����û����е��㷨
						x = 0;//�û�����㷨����ѭ������
						y = 0;//�㷨����ѭ������
						z = 0;//�㷨��������ѭ������
						for (x=0;x<m_pATPDBSUserGroup[j].nAlgorithmN;x++)
						{
							for (y=0;y<m_nUsedATPDBSAlgorithmItem;y++)
							{
								//GUID���
								if (m_pATPDBSAlgorithm[y].nDeleteMark == FALSE && 
									m_pATPDBSUserGroup[j].nDeleteMark == FALSE &&
									m_pATPDBSUserGroup[j].pAlgorithmIDs[x].nID == m_pATPDBSAlgorithm[y].AlgorithmID)
								{

									bExit=FALSE;
									for (int nM=0;nM<1024;nM++)
									{
										//�ҵ����һ��Ҳû���ظ�
										if (nExistenceMark[nM] == 0)
										{
											nExistenceMark[nM]=m_pATPDBSAlgorithm[y].nSerialNumber;
											//bExit = TRUE;
											// ����ѭ��
											break;
										}
										//�ظ�����
										if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[y].nSerialNumber)
										{
											bExit = TRUE;
											break;
										}
									}
									//�ظ����ڡ��������ѭ����
									if (bExit)
									{
										continue;
									}


									memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[y].AlgorithmID,sizeof GUID);
									pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo = m_pATPDBSAlgorithm[y].nParams;
									sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"˵��:%s-�ؼ���:%s-����:%s-����:%s",m_pATPDBSAlgorithm[y].szExplain,m_pATPDBSAlgorithm[y].szKeyword,m_pATPDBSAlgorithm[y].szWarning,m_pATPDBSAlgorithm[y].szStopReason);
									strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[y].szAlgorithmName);

									memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[y].AlgorithVer,sizeof struDataBaseAlgorithmVer);
									pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber = m_pATPDBSAlgorithm[y].nSerialNumber;
									sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[y].szPath,m_pATPDBSAlgorithm[y].szMainDllName);
									//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[y].szPath);
									nAlgoItems++;//�㷨����

									//��ȡ������Ϣ

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
											//������������
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
						//�Ҳ�����������ûʲô�þ�ɥ��Ŷ 
					}
				}
			} 
			else
			{
				//�û��鶼�������ˣ����ܸ����أ����˰�
				break;
			}
		}




	}
	else
	{
		//AfxMessageBox("1");
		int nMark = 0;//�û������������û����±�
		for (;nMark<m_nUsedATPDBSUserItem;nMark++)
		{
			if (m_pATPDBSUser[nMark].nDeleteMark == FALSE &&//�жϸ��û��Ƿ�ɾ��
				pAtpAccept_Manager_ValidateUser->nUserId == m_pATPDBSUser[nMark].nSerialNumber &&//�Ƚ��û�ID
				0 == strcmp(pAtpAccept_Manager_ValidateUser->szUserName,m_pATPDBSUser[nMark].szUserID)//�Ƚ��û���
				)
			{
				//int nMark=n;//�û����±�
				//�㷨��
				int i=0,/*�û����㷨���������*/
					j=0,/*�㷨��������*/
					k=0;/*�㷨������������*/
				for (;i<m_pATPDBSUser[nMark].nAlgorithmGroupN;i++)
				{

					for (j=0;j<m_nUsedATPDBSAlgorithmItem;j++)
					{
						//�㷨�в�����ͬ�㷨����㷨
						if (m_pATPDBSAlgorithm[j].nDeleteMark == FALSE && //�жϸ��㷨�Ƿ�ɾ��
							m_pATPDBSUser[nMark].pAlgorithmGroupIDs[i].nID == m_pATPDBSAlgorithm[j].nGroupID//�Ƚ��û����㷨��ID �� �㷨�������㷨��ID
							)
						{
							bExit=FALSE;
							for (int nM=0;nM<1024;nM++)
							{
								//�ҵ����һ��Ҳû���ظ�����ӵ�������
								if (nExistenceMark[nM] == 0)
								{
									nExistenceMark[nM]=m_pATPDBSAlgorithm[j].nSerialNumber;
									//bExit = TRUE;
									// ����ѭ��1024��
									break;
								}
								//����Ƿ��ظ�����
								if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[j].nSerialNumber)
								{
									bExit = TRUE;
									break;//����Ѿ����ڣ���û��Ҫ����������
								}
							}
							//�ظ����ڡ��������ѭ����
							if (bExit)
							{
								continue;
							}
							memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[j].AlgorithmID,sizeof GUID);
							pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo = m_pATPDBSAlgorithm[j].nParams;
							sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"˵��:%s�ؼ���:%s����:%s����:%s",m_pATPDBSAlgorithm[j].szExplain,m_pATPDBSAlgorithm[j].szKeyword,m_pATPDBSAlgorithm[j].szWarning,m_pATPDBSAlgorithm[j].szStopReason);
							strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[j].szAlgorithmName);

							memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[j].AlgorithVer,sizeof struDataBaseAlgorithmVer);
							pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber = m_pATPDBSAlgorithm[j].nSerialNumber;
							sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[j].szPath,m_pATPDBSAlgorithm[j].szMainDllName);
							//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[j].szPath);
							nAlgoItems++;//�㷨����

							//��ȡ������Ϣ

							for (k=0;k<m_pATPDBSAlgorithm[j].nParams;k++)
							{
								//memcpy((char *)&pAtp_Algoparam_Info[nAllParamItems],(char *)&m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k],nAtp_Algoparam_InfoSize);
								//������������
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
									//������������
									pAtp_Algoparam_Info[nAllParamItems].pExtraData = new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
									memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[j].pATPAlgorithmParamsEX[nExMark-1].ExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

								}

								nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
								nAllParamItems++;
							}
						}
					}
				}

				//�㷨
				//i �û����㷨��������
				//j �㷨����
				//k �㷨�Ĳ�������
				for (i=0;i<m_pATPDBSUser[nMark].nAlgorithmN;i++)
				{
					for (j=0;j<m_nUsedATPDBSAlgorithmItem;j++)
					{
						//GUID���
						if (FALSE == m_pATPDBSAlgorithm[j].nDeleteMark && 
							m_pATPDBSUser[nMark].pAlgorithmIDs[i].nID == m_pATPDBSAlgorithm[j].AlgorithmID)
						{
							bExit=FALSE;
							for (int nM=0;nM<1024;nM++)
							{
								//�ҵ����һ��Ҳû���ظ�����ӵ�������
								if (nExistenceMark[nM] == 0)
								{
									nExistenceMark[nM]=m_pATPDBSAlgorithm[j].nSerialNumber;
									//bExit = TRUE;
									// ����ѭ��1024��
									break;
								}
								//����Ƿ��ظ�����
								if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[j].nSerialNumber)
								{
									bExit = TRUE;
									break;
								}
							}
							//�ظ����ڡ��������ѭ����
							if (bExit)
							{
								continue;
							}
							memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[j].AlgorithmID,sizeof GUID);
							pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo = m_pATPDBSAlgorithm[j].nParams;
							sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"˵��:%s�ؼ���:%s����:%s����:%s",m_pATPDBSAlgorithm[j].szExplain,m_pATPDBSAlgorithm[j].szKeyword,m_pATPDBSAlgorithm[j].szWarning,m_pATPDBSAlgorithm[j].szStopReason);
							strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[j].szAlgorithmName);

							memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[j].AlgorithVer,sizeof struDataBaseAlgorithmVer);
							pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber = m_pATPDBSAlgorithm[j].nSerialNumber;
							sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[j].szPath,m_pATPDBSAlgorithm[j].szMainDllName);
							//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[j].szPath);
							nAlgoItems++;//�㷨����

							//��ȡ������Ϣ

							for (k=0;k<m_pATPDBSAlgorithm[j].nParams;k++)
							{
								//memcpy((char *)&pAtp_Algoparam_Info[nAllParamItems],(char *)&m_pATPDBSAlgorithm[j].pATPAlgorithmParams[k],nAtp_Algoparam_InfoSize);
								//������������
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
									//������������
									pAtp_Algoparam_Info[nAllParamItems].pExtraData = new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
									memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[j].pATPAlgorithmParamsEX[nExMark-1].ExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

								}

								nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
								nAllParamItems++;
							}
						}
					}
				}



				//���û���
				i = 0;//�û����û������
				j = 0;//�û������
				k = 0;
				//�û����ֻ��ͬʱ���ĸ��û�����
				for (i=0;i<4;i++)
				{
					//�û����û��������
					if (m_pATPDBSUser[nMark].nGroupIDs[i] > 0)
					{
						//���û������ĸ�λ���� 
						for (j=0;j<m_nUsedATPDBSUserGroupItem;j++)
						{
							//�鵽�û��е��û���ID���û����е�λ��
							if (m_pATPDBSUser[nMark].nGroupIDs[i] == m_pATPDBSUserGroup[j].nID)
							{
								//�����û���������Щ�㷨���㷨�飬��TMD���鷳��
								int x = 0,//�û�����㷨�����
									y = 0,//�㷨��������
									z = 0;//
								//�����û����е��㷨��
								for (x=0;x<m_pATPDBSUserGroup[j].nAlgorithmGroupN;x++)
								{

									for (y=0;y<m_nUsedATPDBSAlgorithmItem;y++)
									{
										//�㷨�в�����ͬ�㷨����㷨
										if (FALSE == m_pATPDBSAlgorithm[y].nDeleteMark && 
											m_pATPDBSUserGroup[j].pAlgorithmGroupIDs[x].nID == m_pATPDBSAlgorithm[y].nGroupID)
										{
											bExit=FALSE;
											for (int nM=0;nM<1024;nM++)
											{
												//�ҵ����һ��Ҳû���ظ�����ӵ�������
												if (nExistenceMark[nM] == 0)
												{
													nExistenceMark[nM]=m_pATPDBSAlgorithm[y].nSerialNumber;
													//bExit = TRUE;
													// ����ѭ��1024��
													break;
												}
												//����Ƿ��ظ�����
												if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[y].nSerialNumber)
												{
													bExit = TRUE;
													break;
												}
											}
											//�ظ����ڡ��������ѭ����
											if (bExit)
											{
												continue;
											}
											memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[y].AlgorithmID,sizeof GUID);
											pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo = m_pATPDBSAlgorithm[j].nParams;
											sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"˵��:%s-�ؼ���:%s-����:%s-����:%s",m_pATPDBSAlgorithm[y].szExplain,m_pATPDBSAlgorithm[y].szKeyword,m_pATPDBSAlgorithm[y].szWarning,m_pATPDBSAlgorithm[y].szStopReason);
											strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[y].szAlgorithmName);

											memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[y].AlgorithVer,sizeof struDataBaseAlgorithmVer);
											pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber = m_pATPDBSAlgorithm[y].nSerialNumber;
											sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[y].szPath,m_pATPDBSAlgorithm[y].szMainDllName);
											//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[y].szPath);
											nAlgoItems++;//�㷨����

											//��ȡ������Ϣ

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
													//������������
													pAtp_Algoparam_Info[nAllParamItems].pExtraData = new BYTE[pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength];
													memcpy(pAtp_Algoparam_Info[nAllParamItems].pExtraData,m_pATPDBSAlgorithm[y].pATPAlgorithmParamsEX[nExMark-1].ExtraData,pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength);

												}

												nAllExParamLen += pAtp_Algoparam_Info[nAllParamItems].nExtraDataLength;
												nAllParamItems++;
											}
										}
									}
								}

								//�����û����е��㷨
								x =0;y = 0;z = 0;
								for (x=0;x<m_pATPDBSUserGroup[j].nAlgorithmN;x++)
								{
									for (y=0;y<m_nUsedATPDBSAlgorithmItem;y++)
									{
										//GUID���
										if (FALSE == m_pATPDBSAlgorithm[y].nDeleteMark && 
											m_pATPDBSUserGroup[j].pAlgorithmIDs[x].nID == m_pATPDBSAlgorithm[y].AlgorithmID)
										{
											bExit=FALSE;
											for (int nM=0;nM<1024;nM++)
											{
												//�ҵ����һ��Ҳû���ظ�����ӵ�������
												if (nExistenceMark[nM] == 0)
												{
													nExistenceMark[nM]=m_pATPDBSAlgorithm[y].nSerialNumber;
													//bExit = TRUE;
													// ����ѭ��1024��
													break;
												}
												//����Ƿ��ظ�����
												if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSAlgorithm[y].nSerialNumber)
												{
													bExit = TRUE;
													break;
												}
											}
											//�ظ����ڡ��������ѭ����
											if (bExit)
											{
												continue;
											}
											memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.guidAlgo,(char *)&m_pATPDBSAlgorithm[y].AlgorithmID,sizeof GUID);
											pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.nParamInfo = m_pATPDBSAlgorithm[y].nParams;
											sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoDescription,"˵��:%s-�ؼ���:%s-����:%s-����:%s",m_pATPDBSAlgorithm[y].szExplain,m_pATPDBSAlgorithm[y].szKeyword,m_pATPDBSAlgorithm[y].szWarning,m_pATPDBSAlgorithm[y].szStopReason);
											strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].algoInfo.szAlgoName,m_pATPDBSAlgorithm[y].szAlgorithmName);

											memcpy((char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].AlgorithVer,(char *)&m_pATPDBSAlgorithm[y].AlgorithVer,sizeof struDataBaseAlgorithmVer);
											pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].nSerialNumber = m_pATPDBSAlgorithm[y].nSerialNumber;
											sprintf(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,"%s\\%s",m_pATPDBSAlgorithm[y].szPath,m_pATPDBSAlgorithm[y].szMainDllName);
											//strcpy(pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[nAlgoItems].szAlgoPath,m_pATPDBSAlgorithm[y].szPath);
											nAlgoItems++;//�㷨����

											//��ȡ������Ϣ

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
													//������������
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
								//�Ҳ�����������ûʲô�þ�ɥ��Ŷ 
							}
						}
					} 
					else
					{
						//�û��鶼�������ˣ����ܸ����أ����˰�
						break;
					}
				}
				//���û��в��ҵ�һ�����ɣ������û��Ҫ���ң�û��ô��ʱ���˷Ѱ�
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
		memcpy((char *)&(*ppAnsData)[nCount],(char *)pAtpAccept_Manager_MsgHead,nAtpAccept_Manager_MsgHeadSize);//��׼����ͷ
		nCount += nAtpAccept_Manager_MsgHeadSize;
		memcpy((char *)&(*ppAnsData)[nCount],(char *)&_AtpAccept_Manager_GetAlgoInfo_ResultHead,nAtpAccept_Manager_GetAlgoInfo_ResultHeadSize);//�㷨����
		nCount += nAtpAccept_Manager_GetAlgoInfo_ResultHeadSize;
		int nParamMark = 0;
		int i=0,j=0;
		for (i=0;i<nAlgoItems;i++)
		{
			memcpy((char *)&(*ppAnsData)[nCount],(char *)&pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[i],nAtpAccept_Manager_GetAlgoInfo_AlgoInfoSize);//�㷨
			nCount += nAtpAccept_Manager_GetAlgoInfo_AlgoInfoSize;
			for (j=0;j<pAtpAccept_Manager_GetAlgoInfo_AlgoInfo[i].algoInfo.nParamInfo;j++,nParamMark++)
			{
				memcpy((char *)&(*ppAnsData)[nCount],(char *)&pAtp_Algoparam_Info[nParamMark],nAtp_Algoparam_InfoSize);//����
				nCount += nAtp_Algoparam_InfoSize;
				if (pAtp_Algoparam_Info[nParamMark].nExtraDataLength>0)
				{
					memcpy((char *)&(*ppAnsData)[nCount],pAtp_Algoparam_Info[nParamMark].pExtraData,pAtp_Algoparam_Info[nParamMark].nExtraDataLength);//��������ֵ
					nCount += pAtp_Algoparam_Info[nParamMark].nExtraDataLength;
				}


			}

		}
		str.Format("�����㷨��%d",nAlgoItems);
		//AfxMessageBox(str);
		ASSERT(_CrtCheckMemory());
		//�ͷŲ���\��������
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
		//�ͷ��㷨
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
	//����������
	int nAtpAccept_Manager_GetServerInfo_ResultHeadSize					= sizeof AtpAccept_Manager_GetServerInfo_ResultHead;
	AtpAccept_Manager_GetServerInfo_ResultHead _AtpAccept_Manager_GetServerInfo_ResultHead = {0};

	int nAtpAccept_Manager_GetServerInfo_AlgoServerSize					= sizeof AtpAccept_Manager_GetServerInfo_AlgoServer;
	AtpAccept_Manager_GetServerInfo_AlgoServer *pAtpAccept_Manager_GetServerInfo_AlgoServer = new AtpAccept_Manager_GetServerInfo_AlgoServer[1024];
	int nAlgoServerItems = 0;//����������
	int nExistenceMark[1024]={0};
	if (pAtpAccept_Manager_ValidateUser->nUserId == m_pATPDBSUser[pAtpAccept_Manager_ValidateUser->nUserId-1].nSerialNumber &&
		0 == strcmp(pAtpAccept_Manager_ValidateUser->szUserName,m_pATPDBSUser[pAtpAccept_Manager_ValidateUser->nUserId-1].szUserID))
	{
		int nMark = pAtpAccept_Manager_ValidateUser->nUserId-1;
		//��������
		if (m_pATPDBSUser[nMark].nServerGroupN>0)
		{
			int i=0;
			struATPDataBaseServer_QUERY _ATPDBSServer_QUERY = {0};
			struATPDataBaseServer *pATPDBSServer			= NULL;
			int nItems = 0;
			//��ѯ���û����еķ�������
			for (;i<m_pATPDBSUser[nMark].nServerGroupN;i++)
			{
				_ATPDBSServer_QUERY.nGroupID = m_pATPDBSUser[nMark].pServerGroupIDs[i].nID;
				//���ݷ������� ID ���ҷ��ϵķ�����
				nItems = QueryServer(&_ATPDBSServer_QUERY,&pATPDBSServer);
				int j=0;
				for (j=0;j<nItems;j++)
				{
					//�����ڲ�ͬ������������ͬ��������ÿ��������ֻ��������һ����������
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
		//������
		if (m_pATPDBSUser[nMark].nServerN>0)
		{
			//��ѯ���û�����ר��������
			int i=0;
			struATPDataBaseServer _ATPDBSServer			= {0};
			for (;i<m_pATPDBSUser[nMark].nServerN;i++)
			{

				//����i
				int j=0,nItems=0/*���ϼ�¼����*/;
				for (;j<m_nUsedATPDBSServerItem;j++)
				{

					if (m_pATPDBSUser[nMark].pServerIDs[i].nID == m_pATPDBSServer[j].nID)
					{
						ZeroMemory((char *)&_ATPDBSServer,sizeof struATPDataBaseServer);
						memcpy((char *)&_ATPDBSServer,&m_pATPDBSServer[j],sizeof struATPDataBaseServer);
						//�����Ƿ����
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

		//�û���
		int i = 0,j = 0,k = 0;
		for (i=0;i<4;i++)
		{
			//�û������
			if (m_pATPDBSUser[nMark].nGroupIDs[i] > 0)
			{
				//���û������ĸ�λ���� 
				for (j=0;j<m_nUsedATPDBSUserGroupItem;j++)
				{
					//�鵽�û��е��û���ID���û����е�λ��
					if (m_pATPDBSUser[nMark].nGroupIDs[i] == m_pATPDBSUserGroup[j].nID)
					{

						//�����û���������Щ�������ͷ������飬��TMD���鷳��
						int x = 0,y = 0,z = 0;
						for (x=0;x<m_pATPDBSUserGroup[j].nServerGroupN;x++)
						{

							for (y=0;y<m_nUsedATPDBSServerItem;y++)
							{
								//�������в�����ͬ��������ķ�����
								if (m_pATPDBSUserGroup[j].pServerGroupIDs[x].nID == m_pATPDBSServer[y].nGroupID)
								{

									int nExit = 0;
									for (int nM=0;nM<1024;nM++)
									{
										//�ҵ����һ��Ҳû���ظ�
										if (nExistenceMark[nM] == 0)
										{
											nExistenceMark[nM]=m_pATPDBSServer[y].nID;
											nExit = 0;
											// ����ѭ��
											break;
										}
										//�ظ�����
										if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSServer[y].nID)
										{
											nExit = 1;
											break;
										}
										//�ظ����ڡ��������ѭ����
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

						//�����û����еķ�����
						x =0;y = 0;z = 0;
						for (x=0;x<m_pATPDBSUserGroup[j].nServerN;x++)
						{
							for (y=0;y<m_nUsedATPDBSServerItem;y++)
							{
								//ID���
								if (m_pATPDBSServer[y].nID == m_pATPDBSUserGroup[j].pServerIDs[x].nID)
								{

									int nExit=0;
									for (int nM=0;nM<1024;nM++)
									{
										//�ҵ����һ��Ҳû���ظ�
										if (nExistenceMark[nM] == 0)
										{
											nExistenceMark[nM]=m_pATPDBSServer[y].nID;
											nExit = 0;
											// ����ѭ��
											break;
										}
										//�ظ�����
										if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSServer[y].nID)
										{
											nExit = 1;
											break;
										}
									}
									//�ظ����ڡ��������ѭ����
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
			//��������
			if (m_pATPDBSUser[n].nServerGroupN>0)
			{
				int i=0;
				struATPDataBaseServer_QUERY _ATPDBSServer_QUERY = {0};
				struATPDataBaseServer *pATPDBSServer			= NULL;
				int nItems = 0;
				//��ѯ���û����еķ�������
				for (;i<m_pATPDBSUser[n].nServerGroupN;i++)
				{
					_ATPDBSServer_QUERY.nGroupID = m_pATPDBSUser[n].pServerGroupIDs[i].nID;
					//���ݷ������� ID ���ҷ��ϵķ�����
					nItems = QueryServer(&_ATPDBSServer_QUERY,&pATPDBSServer);
					int j=0;
					for (;j<nItems;j++)
					{
						//�����ڲ�ͬ������������ͬ��������ÿ��������ֻ��������һ����������
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
			//������
			if (m_pATPDBSUser[n].nServerN>0)
			{
				//��ѯ���û�����ר��������
				int i=0;
				struATPDataBaseServer _ATPDBSServer			= {0};
				for (;i<m_pATPDBSUser[n].nServerN;i++)
				{

					//����i
					int j=0,nItems=0/*���ϼ�¼����*/;
					for (;j<m_nUsedATPDBSServerItem;j++)
					{

						if (m_pATPDBSUser[n].pServerIDs[i].nID == m_pATPDBSServer[j].nID)
						{
							ZeroMemory((char *)&_ATPDBSServer,sizeof struATPDataBaseServer);
							memcpy((char *)&_ATPDBSServer,&m_pATPDBSServer[j],sizeof struATPDataBaseServer);
							//�����Ƿ����
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

			//�û���
			int i = 0,j = 0,k = 0;
			for (i=0;i<4;i++)
			{
				//�û������
				if (m_pATPDBSUser[nMark].nGroupIDs[i] > 0)
				{
					//���û������ĸ�λ���� 
					for (j=0;j<m_nUsedATPDBSUserGroupItem;j++)
					{
						//�鵽�û��е��û���ID���û����е�λ��
						if (m_pATPDBSUser[nMark].nGroupIDs[i] == m_pATPDBSUserGroup[j].nID)
						{

							//�����û���������Щ�������ͷ������飬��TMD���鷳��
							int x = 0,y = 0,z = 0;
							for (x=0;x<m_pATPDBSUserGroup[j].nServerGroupN;x++)
							{

								for (y=0;y<m_nUsedATPDBSServerItem;y++)
								{
									//�������в�����ͬ��������ķ�����
									if (m_pATPDBSUserGroup[j].pServerGroupIDs[x].nID == m_pATPDBSServer[y].nGroupID)
									{

										int nExit = 0;
										for (int nM=0;nM<1024;nM++)
										{
											//�ҵ����һ��Ҳû���ظ�
											if (nExistenceMark[nM] == 0)
											{
												nExistenceMark[nM]=m_pATPDBSServer[y].nID;
												nExit = 0;
												// ����ѭ��
												break;
											}
											//�ظ�����
											if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSServer[y].nID)
											{
												nExit = 1;
												break;
											}
											//�ظ����ڡ��������ѭ����
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

							//�����û����еķ�����
							x =0;y = 0;z = 0;
							for (x=0;x<m_pATPDBSUserGroup[j].nServerN;x++)
							{
								for (y=0;y<m_nUsedATPDBSServerItem;y++)
								{
									//ID���
									if (m_pATPDBSServer[y].nID == m_pATPDBSUserGroup[j].pServerIDs[x].nID)
									{

										int nExit=0;
										for (int nM=0;nM<1024;nM++)
										{
											//�ҵ����һ��Ҳû���ظ�
											if (nExistenceMark[nM] == 0)
											{
												nExistenceMark[nM]=m_pATPDBSServer[y].nID;
												nExit = 0;
												// ����ѭ��
												break;
											}
											//�ظ�����
											if (nExistenceMark[nM]>0 && nExistenceMark[nM]==m_pATPDBSServer[y].nID)
											{
												nExit = 1;
												break;
											}
										}
										//�ظ����ڡ��������ѭ����
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
	//�˶�ֻ��ѯ�ʽ��ʺ������г���Ч
	int nAtpAccept_Manager_GetFundAccount_SecurityType_ResultSize = sizeof AtpAccept_Manager_GetFundAccount_SecurityType_Result;
	AtpAccept_Manager_GetFundAccount_SecurityType_Result _AtpAccept_Manager_GetFundAccount_SecurityType_Result = {0};
	//////////////////////////////////////////////////////////////////////////
	int i = 0,j = 0,k = 0;
	char szOrgIDTemp[8]={0};
	int nRepeatMark = 0;//�ظ���ǣ�0�򲻴��ڣ�����1�򻥳�
	int nUserMark = 0;//�ʽ��ʻ�ƥ��ɹ�ʱ���û��ı�
	//���������û�
	for (;i<m_nUsedATPDBSUserItem;i++)
	{
		//����ÿ���û��ĵ��ʽ��ʻ�
		for (j=0,k=0;j<m_pATPDBSUser[i].nCanAssociateFundsAccount;j++)
		{
			if (m_pATPDBSUser[i].nDeleteMark)
			{
				continue;
			}
			//Ӫҵ������
			ZeroMemory(szOrgIDTemp,0);
			strncpy(szOrgIDTemp,m_pATPDBSUser[i].pATPFund[j].szOrgID,8);
			//ƥ���ʽ��ʻ�
			if (0 == strcmp(m_pATPDBSUser[i].pATPFund[j].szFund,pAtpAccept_Manager_GetUserInfo_WithFundAccout->fundAccount.chUserID) &&
				0 == strcmp(szOrgIDTemp,pAtpAccept_Manager_GetUserInfo_WithFundAccout->fundAccount.chOrgID))
			{
				//ֻ�ǻ�ȡ�ʽ��ʺŵ������г�����
				if (bFlag)
				{
					int nMark1=0,nMark2=0;
					for (int x=0;x<12;x++)
					{
						if (m_pATPDBSUser[i].pATPFund[j].szMarkets[x] == -1)
						{
							break;
						}
						//��Ʊ�г�
						if (m_pATPDBSUser[i].pATPFund[j].szMarkets[x]==0 || m_pATPDBSUser[i].pATPFund[j].szMarkets[x]==1 ||
							m_pATPDBSUser[i].pATPFund[j].szMarkets[x]==2 || m_pATPDBSUser[i].pATPFund[j].szMarkets[x]==6)
						{
							nMark1 = 1;
						}
						//�ڻ��г�
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
					
					//�������ʽ��ʺ������г���������
					//goto END_GETACCOUNTBYFUND;
				}

				nRepeatMark += 1;
				if (nRepeatMark == 2)
				{
					//û������ȥ�������ˣ����˰�
					goto END_SELECTFUND;
				}
				nUserMark = i;//��¼�û����е�λ��
				//��䷵�ؽ��
				_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nUserId = m_pATPDBSUser[i].nSerialNumber;
				strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szUserName,m_pATPDBSUser[i].szUserID);
				strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szUserPwd,m_pATPDBSUser[i].szPwd);
			}			
		}
	}

END_SELECTFUND://��������
	if (bFlag)
	{
		if (nRepeatMark == 2 || nRepeatMark == 0)
		{
			//�ʽ��ʺŲ�����
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
		//û��Ҫ��ʲô�ˣ�û����ģ�ֱ�ӷ��ش�����Ϣ��
		_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nUserId = 0;
		strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szUserName,"");
		strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szUserPwd,"");
		_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
		strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"��֧��һ���ʽ��ʻ���Ӧ���ƽ̨�ʻ�");
	}
	else if (nRepeatMark == 0)
	{
		_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nUserId = 0;
		strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szUserName,"");
		strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szUserPwd,"");
		_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
		strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"�����ڸ��ʽ��ʻ�");
	}
	else if (nRepeatMark == 1)
	{
		char *ptr = NULL;
		if ((int)pAtpAccept_Manager_GetUserInfo_WithFundAccout->szLoginIpType == 4 || (int)pAtpAccept_Manager_GetUserInfo_WithFundAccout->szLoginIpType == 6)
		{
			ptr = strstr(m_pATPDBSUser[nUserMark].szIPs,pAtpAccept_Manager_GetUserInfo_WithFundAccout->szLoginIp);
			if (ptr)
			{
				//ip���Ƶ�¼
				_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
				strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"��IP��¼������");
				//break;
				goto END_GETACCOUNTBYFUND;
			}
		} 
		//mac ��ַ
		if (strlen(pAtpAccept_Manager_GetUserInfo_WithFundAccout->szMac))
		{
			ptr = strstr(m_pATPDBSUser[nUserMark].szMacMark,pAtpAccept_Manager_GetUserInfo_WithFundAccout->szMac);
			if (ptr)
			{
				//mac ��ַ ���Ƶ�¼
				_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
				strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"��MAC��ַ��¼������");
				//break;
				goto END_GETACCOUNTBYFUND;
			}
		}
		//Ӳ�����к�
		if (strlen(pAtpAccept_Manager_GetUserInfo_WithFundAccout->szDiskSerialNum))
		{
			ptr = strstr(m_pATPDBSUser[nUserMark].szDiskNum,pAtpAccept_Manager_GetUserInfo_WithFundAccout->szDiskSerialNum);
			if (ptr)
			{
				//Ӳ�����к� ���Ƶ�¼
				_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
				strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"��Ӳ�̵�¼������");
				//break;
				goto END_GETACCOUNTBYFUND;
			}
		}


		CTime t = CTime::GetCurrentTime(); 
		int nTime = t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();//235959

		//ʱ���
		if (m_pATPDBSUser[nUserMark].chLimitTimeMark&128)
		{
			if (m_pATPDBSUser[nUserMark].chLimitTimeMark&64)
			{
				if (m_pATPDBSUser[nUserMark].nLimitBeginTime[0]<nTime && nTime < m_pATPDBSUser[i].nLimitEndTime[0])
				{
					//��¼ʱ��������
					_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
					strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"��ʱ��ε�¼������");
					//break;
					goto END_GETACCOUNTBYFUND;
				}
			}
			if (m_pATPDBSUser[nUserMark].chLimitTimeMark&32)
			{
				if (m_pATPDBSUser[i].nLimitBeginTime[1]<nTime && nTime < m_pATPDBSUser[i].nLimitEndTime[1])
				{
					//��¼ʱ��������
					_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
					strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"��ʱ��ε�¼������");
					//break;
					goto END_GETACCOUNTBYFUND;
				}
			}
		}

		//����
		if (m_pATPDBSUser[nUserMark].chLimitWeek&128)
		{
			switch (t.GetDayOfWeek())
			{
			case 1://������
				{
					if (m_pATPDBSUser[nUserMark].chLimitWeek&64)
					{
						_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"�������յ�¼������");
					}
				}
				break;
			case 2://����һ
				{
					if (m_pATPDBSUser[nUserMark].chLimitWeek&32)
					{
						_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"������һ��¼������");
					}
				}
				break;
			case 3://��
				{
					if (m_pATPDBSUser[nUserMark].chLimitWeek&16)
					{
						_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"�����ڶ���¼������");
					}
				}
				break;
			case 4://��
				{
					if (m_pATPDBSUser[nUserMark].chLimitWeek&8)
					{
						_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"����������¼������");
					}
				}
				break;
			case 5://��
				{
					if (m_pATPDBSUser[nUserMark].chLimitWeek&4)
					{
						_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"�������ĵ�¼������");
					}
				}
				break;
			case 6://��
				{
					if (m_pATPDBSUser[nUserMark].chLimitWeek&2)
					{
						_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"���������¼������");
					}
				}
				break;
			case 7://��
				{
					if (m_pATPDBSUser[nUserMark].chLimitWeek&1)
					{
						_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.nResult = -1;
						strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout_Result.szError,"����������¼������");
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
		nRet = -1;//�������
	}
	else if (nAccountMark == 0)
	{
		nRet = -2;//�ʻ�������
	}
	return nRet;
}

