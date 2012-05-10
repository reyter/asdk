#include "StdAfx.h"
#include "ATPLogBase.h"


CATPLogBase::CATPLogBase(int nMark)
{
	m_pATPDBSOperateLog = NULL;
	m_pATPDBSAlgorithmLog = NULL;
	
	if (nMark == OPERATELOG || nMark == ALGOLOG)
	{
		m_nLogMark = nMark;
	} 
	else
	{
		m_nLogMark = OPERATELOG;
	}
	ZeroMemory(m_szFileName,MAX_PATH);
	InitDBLog("");
	
	//ReadRegistSaveData();
}
CATPLogBase::CATPLogBase(int nMark,int nDate)
{
	m_pATPDBSOperateLog = NULL;
	m_pATPDBSAlgorithmLog = NULL;
	if (nMark == OPERATELOG || nMark == ALGOLOG)
	{
		m_nLogMark = nMark;
	} 
	else
	{
		m_nLogMark = OPERATELOG;
	}
	char sz[MAX_PATH]={0};
	sprintf(sz,"%d",nDate);
	InitDBLog(sz);
}

CATPLogBase::~CATPLogBase(void)
{
	SaveRegistSaveData();//保存数据
	//m_OperateFile.Close();
}



void*	CATPLogBase::NewRegisterSaveDataStruct(int nID, int nItems)
{
	if (nID == 7)
	{
		m_pATPDBSOperateLog	= new struATPDataBaseOperateLog[nItems];
		return m_pATPDBSOperateLog;
	}
	if (nID == 10)
	{
		m_pATPDBSAlgorithmLog = new struATPDataBaseAlgorithmLog[nItems];
		return m_pATPDBSAlgorithmLog;
	}
	return 0;
}

BOOL	CATPLogBase::DeleteRegisterSaveDataStruct(int nID, int nItems)
{
// 	if (nID == 7)
// 	{
// 		if (m_pATPDBSOperateLog)
// 		{
// 			delete m_pATPDBSOperateLog;
// 		}
// 	}
// 
// 	if (nID == 10)
// 	{
// 		if (m_pATPDBSAlgorithmLog)
// 		{
// 			delete m_pATPDBSAlgorithmLog;
// 		}
// 	}
	return TRUE;
}


void	CATPLogBase::RegisterData(char *pFilename)
{
	CONST UINT32 nUINT8SIZE		= sizeof(UINT8);
	CONST UINT32 nUINT32SIZE	= sizeof(UINT32);
	CONST UINT32 nUINT64SIZE	= sizeof(UINT64);
	CONST UINT32 nATPAUTOID		= sizeof(struATPAutoID);
	CONST UINT32 nATPAUTOALGOID = sizeof(struATPAutoAlgoID);
	CTime t = CTime::GetCurrentTime();
	mkdir("..\\Log");
	mkdir("..\\Log\\Operate");
	mkdir("..\\Log\\Algo");
	//char szTime[32]={0};

	char szFilename[MAX_PATH]={0};


	if (m_nLogMark==OPERATELOG)
	{
		//操作日志
		if (strlen(pFilename)>0)
		{
			sprintf(szFilename,"..\\Log\\Operate\\%s.log",pFilename);
		} 
		else
		{
			sprintf(szFilename,"..\\Log\\Operate\\%d.log",t.GetYear()*10000+t.GetMonth()*100+t.GetDay());
		}
		
		SetSaveDataFileName(szFilename);	

		RegisterSaveData(5,&m_nUsedATPDBSOperateLogItem,1);
		RegisterSaveData(6,&m_nATPDBSOperateLogItem,1);

		//struATPDataBaseOperateLog		*m_pATPDBSOperateLog;
		struATPDataBaseOperateLog _ATPDBSOperateLog;
		CONST UINT32 nATPDBSOPERATELOGSIZE = sizeof(struATPDataBaseOperateLog);
		RegisterSaveDataStruct(7, 1, &_ATPDBSOperateLog, nATPDBSOPERATELOGSIZE,&_ATPDBSOperateLog.nSerialNumber,nUINT32SIZE);
		RegisterSaveDataStruct(7, 2, &_ATPDBSOperateLog, nATPDBSOPERATELOGSIZE, _ATPDBSOperateLog.szActorID,	sizeof(_ATPDBSOperateLog.szActorID));
		RegisterSaveDataStruct(7, 3, &_ATPDBSOperateLog, nATPDBSOPERATELOGSIZE,&_ATPDBSOperateLog.nRecords,		nUINT32SIZE);
		RegisterSaveDataStruct(7, 4, &_ATPDBSOperateLog, nATPDBSOPERATELOGSIZE,&_ATPDBSOperateLog.nOperateType,	nUINT32SIZE);
		RegisterSaveDataStruct(7, 5, &_ATPDBSOperateLog, nATPDBSOPERATELOGSIZE,&_ATPDBSOperateLog.nOperateDate,	nUINT32SIZE);
		RegisterSaveDataStruct(7, 6, &_ATPDBSOperateLog, nATPDBSOPERATELOGSIZE,&_ATPDBSOperateLog.nOperateTime,	nUINT32SIZE);
		RegisterSaveDataStruct(7, 7, &_ATPDBSOperateLog, nATPDBSOPERATELOGSIZE, _ATPDBSOperateLog.szInfo,		sizeof(_ATPDBSOperateLog.szInfo));

		RegisterSaveDataAddress(7, (void**)&m_pATPDBSOperateLog, nATPDBSOPERATELOGSIZE, &m_nATPDBSOperateLogItem, 0, 10240);

	} 
	else
	{
		//算法日志
		if (strlen(pFilename)>0)
		{
			sprintf(szFilename,"..\\Log\\Algo\\%s.log",pFilename);
		} 
		else
		{
			sprintf(szFilename,"..\\Log\\Algo\\%d.log",t.GetYear()*10000+t.GetMonth()*100+t.GetDay());
		}
		
		SetSaveDataFileName(szFilename);	


		RegisterSaveData(8,&m_nUsedATPDBSAlgorithmLogItem,1);
		RegisterSaveData(9,&m_nATPDBSAlgorithmLogItem,1);

		//struATPDataBaseAlgorithmLog		*m_pATPDBSAlgorithmLog;
		struATPDataBaseAlgorithmLog _ATPDBSAlgorithmLog;
		CONST UINT32 nATPDBSALGORITHMLOGSIZE = sizeof(struATPDataBaseAlgorithmLog);
		RegisterSaveDataStruct(10, 1,  &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE,&_ATPDBSAlgorithmLog.nSerialNumber,nUINT32SIZE);
		RegisterSaveDataStruct(10, 2,  &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE,&_ATPDBSAlgorithmLog.AlgorithmID,	sizeof(GUID));
		RegisterSaveDataStruct(10, 3,  &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE, _ATPDBSAlgorithmLog.szUserID,		sizeof(_ATPDBSAlgorithmLog.szUserID));
		RegisterSaveDataStruct(10, 4,  &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE,&_ATPDBSAlgorithmLog.nUserGroupID,	nUINT32SIZE);
		RegisterSaveDataStruct(10, 5,  &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE,&_ATPDBSAlgorithmLog.nServerID,	nUINT32SIZE);
		RegisterSaveDataStruct(10, 6,  &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE,&_ATPDBSAlgorithmLog.nStatus,		nUINT32SIZE);
		RegisterSaveDataStruct(10, 7,  &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE,&_ATPDBSAlgorithmLog.nRunBeginDate,nUINT32SIZE);
		RegisterSaveDataStruct(10, 8,  &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE,&_ATPDBSAlgorithmLog.nRunBeginTime,nUINT32SIZE);
		RegisterSaveDataStruct(10, 9,  &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE,&_ATPDBSAlgorithmLog.nRunEndDate,	nUINT32SIZE);
		RegisterSaveDataStruct(10, 10, &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE,&_ATPDBSAlgorithmLog.nRunEndTime,	nUINT32SIZE);
		RegisterSaveDataStruct(10, 11, &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE,&_ATPDBSAlgorithmLog.nVolume,		nUINT64SIZE);
		RegisterSaveDataStruct(10, 12, &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE,&_ATPDBSAlgorithmLog.nTurnover,	nUINT64SIZE);
		RegisterSaveDataStruct(10, 13, &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE, _ATPDBSAlgorithmLog.nCount,		sizeof(_ATPDBSAlgorithmLog.nCount));
		RegisterSaveDataStruct(10, 14, &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE,&_ATPDBSAlgorithmLog.nCompletion,	nUINT64SIZE);
		RegisterSaveDataStruct(10, 15, &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE,&_ATPDBSAlgorithmLog.iAlgoInsID,	nUINT64SIZE);
		RegisterSaveDataStruct(10, 16, &_ATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE, _ATPDBSAlgorithmLog.szAlgoRemark,	sizeof(_ATPDBSAlgorithmLog.szAlgoRemark));


		RegisterSaveDataAddress(10, (void**)&m_pATPDBSAlgorithmLog, nATPDBSALGORITHMLOGSIZE, &m_nATPDBSAlgorithmLogItem, 0, 10240);
	}
}


int	CATPLogBase::InitDBLog(char *pFilename)
{
	RegisterData(pFilename);
	CTime t = CTime::GetCurrentTime();
	mkdir("..\\Log");
	mkdir("..\\Log\\Operate");
	mkdir("..\\Log\\Algo");
	char szFilename[MAX_PATH]={0},szFilename2[MAX_PATH]={0};
	if (m_nLogMark == 1)
	{
		if (strlen(pFilename)>0)
		{
			sprintf(szFilename,"..\\Log\\Operate\\%s.log",pFilename);
			sprintf(szFilename2,"..\\Log\\Operate\\%s.txt",pFilename);
			//m_file.Open(szFilename2,CFile::modeReadWrite|CFile::modeCreate,NULL,NULL);
		} 
		else
		{
			sprintf(szFilename,"..\\Log\\Operate\\%d.log",t.GetYear()*10000+t.GetMonth()*100+t.GetDay());
			sprintf(szFilename2,"..\\Log\\Operate\\%d.txt",t.GetYear()*10000+t.GetMonth()*100+t.GetDay());
			//m_file.Open(szFilename2,CFile::modeReadWrite|CFile::modeCreate,NULL,NULL);
		}
		
		CFileFind  fileFind;
		BOOL	bResult=fileFind.FindFile(szFilename);

		if(!bResult)
		{

			m_nUsedATPDBSOperateLogItem = 0;
			m_nATPDBSOperateLogItem		= 10240;//操作日志默认1024
			m_pATPDBSOperateLog			= new struATPDataBaseOperateLog[m_nATPDBSOperateLogItem];
			if (NULL == m_pATPDBSOperateLog)
			{
				return NEWERROR;
			}
			ZeroMemory((char*)m_pATPDBSOperateLog,m_nATPDBSOperateLogItem*sizeof(struATPDataBaseOperateLog));


			
			SaveRegistSaveData();//保存数据
			if (m_pATPDBSOperateLog)
			{
				delete m_pATPDBSOperateLog;m_pATPDBSOperateLog = NULL;
			}
		
		}
		fileFind.Close();
	} 
	else
	{
		if (strlen(pFilename)>0)
		{
			sprintf(szFilename,"..\\Log\\Algo\\%s.log",pFilename);
			//sprintf(szFilename2,"..\\Log\\Algo\\%s.log",pFilename);
			//m_file.Open(szFilename2,CFile::modeReadWrite|CFile::modeCreate,NULL,NULL);
		} 
		else
		{
			sprintf(szFilename,"..\\Log\\Algo\\%d.log",t.GetYear()*10000+t.GetMonth()*100+t.GetDay());
			//sprintf(szFilename2,"..\\Log\\Algo\\%d.log",t.GetYear()*10000+t.GetMonth()*100+t.GetDay());
			//m_file.Open(szFilename2,CFile::modeReadWrite|CFile::modeCreate,NULL,NULL);
		}
		
		CFileFind  fileFind;
		BOOL	bResult=fileFind.FindFile(szFilename);

		if(!bResult)
		{

			
			m_nUsedATPDBSAlgorithmLogItem	= 0;
			m_nATPDBSAlgorithmLogItem		= 10240;//算法日志默认10240
			m_pATPDBSAlgorithmLog			= new struATPDataBaseAlgorithmLog[m_nATPDBSAlgorithmLogItem];
			if (NULL == m_pATPDBSAlgorithmLog)
			{
				return NEWERROR;
			}
			ZeroMemory((char*)m_pATPDBSAlgorithmLog,m_nATPDBSAlgorithmLogItem*sizeof(struATPDataBaseAlgorithmLog));
			SaveRegistSaveData();//保存数据
			
			if (m_pATPDBSAlgorithmLog)
			{
				delete m_pATPDBSAlgorithmLog;m_pATPDBSAlgorithmLog = NULL;
			}
		}
		fileFind.Close();
	}

	strcpy(m_szFileName,szFilename2);
	

	ReadRegistSaveData();
	return 0;
}


//////////////////////////////////////////////////////////////////////////
int CATPLogBase::AddOperateLog(struATPDataBaseOperateLog *pATPDBSOperateLog)
{
	if (NULL == m_pATPDBSOperateLog)
	{
		return NOTINIT;
	}
	//查看内存使用情况
	//***


	memcpy((char *)&m_pATPDBSOperateLog[m_nUsedATPDBSOperateLogItem],(char *)pATPDBSOperateLog,sizeof struATPDataBaseOperateLog);
	//序号递增
	if (m_nUsedATPDBSOperateLogItem == 0)
	{
		m_pATPDBSOperateLog[m_nUsedATPDBSOperateLogItem].nSerialNumber = 1;
	} 
	else
	{
		m_pATPDBSOperateLog[m_nUsedATPDBSOperateLogItem].nSerialNumber = m_pATPDBSOperateLog[m_nUsedATPDBSOperateLogItem-1].nSerialNumber + 1;
	}
	
	//使用标记+1
	m_nUsedATPDBSOperateLogItem += 1;
	/*
	struct	struATPDataBaseOperateLog
	{
	UINT32		nSerialNumber;					//	自动增长 唯一
	char		szActorID[16];					//	角色ID
	UINT32		nRecords;						//	记录数
	UINT32		nOperateType;					//	操作类型
	UINT32		nOperateDate;					//	操作日期
	UINT32		nOperateTime;					//	操作时间
	char		szInfo[128];					//	记录信息

	};
	*/
	if (strlen(m_szFileName)>0)
	{
		m_OperateFile.Open(m_szFileName,CFile::modeReadWrite|CFile::modeCreate,NULL,NULL);
		char sz[256]={0};
		for (int i=0;i<m_nUsedATPDBSOperateLogItem;i++)
		{
			ZeroMemory(sz,256);
			sprintf(sz,"%d-%02d:%02d:%02d-%s-%s\r\n",
				m_pATPDBSOperateLog[i].nOperateDate,m_pATPDBSOperateLog[i].nOperateTime/10000,m_pATPDBSOperateLog[i].nOperateTime%10000/100,
				m_pATPDBSOperateLog[i].nOperateTime%10000%100,m_pATPDBSOperateLog[i].szActorID,
				m_pATPDBSOperateLog[i].szInfo);
			m_OperateFile.Write(sz,strlen(sz));
		}
		m_OperateFile.Close();

	}
	

	SaveRegistSaveData();
	return 0;
}


int CATPLogBase::QueryOperateLog(struATPDataBaseOperateLog_QUERY *pATPDBSOperateLog_QUERY,OUT struATPDataBaseOperateLog **ppATPDBSOperateLog)
{
	if (NULL == m_pATPDBSOperateLog)
	{
		return NOTINIT;
	}

	if (m_nUsedATPDBSOperateLogItem<=0)
	{
		//没有记录
		return ZERORECORD;
	}

	*ppATPDBSOperateLog = new struATPDataBaseOperateLog[m_nUsedATPDBSOperateLogItem];
	if (NULL == *ppATPDBSOperateLog)
	{
		return NEWERROR;
	}
	
	//查找
	int i=0,nItems=0/*符合记录条数*/;
	for (;i<m_nUsedATPDBSOperateLogItem;i++)
	{
		//需要匹配条件
		if (0==strcmp(pATPDBSOperateLog_QUERY->szUserID,m_pATPDBSOperateLog[i].szActorID) || 0==strlen(pATPDBSOperateLog_QUERY->szUserID))
		{
			ZeroMemory((char *)&(*ppATPDBSOperateLog)[nItems],sizeof struATPDataBaseOperateLog);
			memcpy((char *)&(*ppATPDBSOperateLog)[nItems++],&m_pATPDBSOperateLog[i],sizeof struATPDataBaseOperateLog);
		}
	}
	if (nItems==0)
	{
		//没有一条纪录，释放已经分配的内存
		delete *ppATPDBSOperateLog;
		*ppATPDBSOperateLog = NULL;
	}

	//释放  *ppATPDBSServerGroup  在外面
	return nItems;
}
    
//////////////////////////////////////////////////////////////////////////
int CATPLogBase::AddAlgorithmLog(struATPDataBaseAlgorithmLog *pATPDBSAlgorithmLog)
{
	if (NULL == m_pATPDBSAlgorithmLog)
	{
		return NOTINIT;
	}
	//查看内存使用情况
	//***


	memcpy((char *)&m_pATPDBSAlgorithmLog[m_nUsedATPDBSAlgorithmLogItem],(char *)pATPDBSAlgorithmLog,sizeof struATPDataBaseAlgorithmLog);
	//序号递增
	if (m_nUsedATPDBSAlgorithmLogItem == 0)
	{
		m_pATPDBSAlgorithmLog[m_nUsedATPDBSAlgorithmLogItem].nSerialNumber = 1;
	} 
	else
	{
		m_pATPDBSAlgorithmLog[m_nUsedATPDBSAlgorithmLogItem].nSerialNumber = m_pATPDBSAlgorithmLog[m_nUsedATPDBSAlgorithmLogItem-1].nSerialNumber + 1;
	}
	//使用标记+1
	m_nUsedATPDBSAlgorithmLogItem += 1;

	SaveRegistSaveData();
	return 0;
}


int CATPLogBase::QueryAlgorithmLog(struATPDataBaseAlgorithmLog_QUERY *pATPDBSAlgorithmLog_QUERY,OUT struATPDataBaseAlgorithmLog **ppATPDBSAlgorithmLog)
{
	if (NULL == m_pATPDBSAlgorithmLog)
	{
		return NOTINIT;
	}

	if (m_nUsedATPDBSAlgorithmLogItem<=0)
	{
		//没有记录
		return ZERORECORD;
	}

	*ppATPDBSAlgorithmLog = new struATPDataBaseAlgorithmLog[m_nUsedATPDBSAlgorithmLogItem];
	if (NULL == *ppATPDBSAlgorithmLog)
	{
		return NEWERROR;
	}


	BOOL b1=FALSE,b2=FALSE;
	if (strlen(pATPDBSAlgorithmLog_QUERY->szUserID)==0)
	{
		b1 = TRUE;
	}
	if (pATPDBSAlgorithmLog_QUERY->AlgorithmID.Data1==0)
	{
		b2 = TRUE;
	}

	//查找
	int i=0,nItems=0/*符合记录条数*/;
	for (;i<m_nUsedATPDBSAlgorithmLogItem;i++)
	{
		//需要匹配条件
		if (b1&&b2)
		{
			//查全部
			memcpy((char *)&(*ppATPDBSAlgorithmLog)[nItems++],&m_pATPDBSAlgorithmLog[i],sizeof struATPDataBaseServer);
		} 
		else if (b1)
		{
			//按算法查
			if (pATPDBSAlgorithmLog_QUERY->AlgorithmID==m_pATPDBSAlgorithmLog[i].AlgorithmID)
			{
				memcpy((char *)&(*ppATPDBSAlgorithmLog)[nItems++],&m_pATPDBSAlgorithmLog[i],sizeof struATPDataBaseServer);
			}
		}
		else if (b2)
		{
			//按用户查
			if (0==strcmp(pATPDBSAlgorithmLog_QUERY->szUserID,m_pATPDBSAlgorithmLog[i].szUserID))
			{
				memcpy((char *)&(*ppATPDBSAlgorithmLog)[nItems++],&m_pATPDBSAlgorithmLog[i],sizeof struATPDataBaseServer);
			}
		}

		
	}
	if (nItems==0)
	{
		//没有一条纪录，释放已经分配的内存
		delete *ppATPDBSAlgorithmLog;
		*ppATPDBSAlgorithmLog = NULL;
	}

	//释放  *ppATPDBSServerGroup  在外面
	return nItems;
}