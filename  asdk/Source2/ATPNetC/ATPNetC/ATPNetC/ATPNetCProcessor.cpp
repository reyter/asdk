#include "StdAfx.h"
#include "ATPNetCProcessor.h"
#include "ATPManagerNetDefine.h"

#include "ATPManagerDataBaseDefine.h"
#include "ATPManagerNetDefine.h"

#define MEMORYCOUNT 1024*1024

IMPLEMENT_DYNCREATE(CATPNetCProcessor, CHHNetFrameProcessor)
CATPNetCProcessor::CATPNetCProcessor(void)
{

}


CATPNetCProcessor::~CATPNetCProcessor(void)
{

}


int CATPNetCProcessor::OnRecvData(int nType,const char *lpRecv, int nSize)
{
	//(CATPNetCProcessor*)RecvData(int nType,const char *lpRecv, int nSize);

	return 0;
}

int CATPNetCProcessor::OnSendData(int nType,const char *lpRecv, int nSize)
{
	return 0;
}

void CATPNetCProcessor::AllocateMemory(struRecvData* pData,int nNeed)
{
	if (nNeed<0)
	{
		return ;
	}

	if (nNeed==0)
	{
		ZeroMemory(pData->_pAnswerData,pData->_nHadMemory);
		pData->_nUsedMemory = 0;
	}

	if (nNeed+pData->_nUsedMemory > pData->_nHadMemory)
	{
		BYTE *pNEWTemp = new BYTE[pData->_nHadMemory+max(nNeed,MEMORYCOUNT)];
		ASSERT(pNEWTemp);
		ASSERT(pData);
		ZeroMemory(pNEWTemp,pData->_nHadMemory+max(nNeed,MEMORYCOUNT));
		memcpy(pNEWTemp,pData->_pAnswerData,pData->_nUsedMemory);

		delete [](pData->_pAnswerData);
		pData->_pAnswerData = pNEWTemp;

		pData->_nHadMemory = pData->_nHadMemory+max(nNeed,MEMORYCOUNT);
	}
}

BOOL CATPNetCProcessor::OnCreate()
{
	return TRUE;
}

BOOL CATPNetCProcessor::OnDestroy(BOOL bInterrupt)
{
	return TRUE;
}

int  CATPNetCProcessor::OnReceiveData(const CString &strSrcDN, const CString &strDesDN, CString &strSendDesDN, char *lpRecv, int nSize, unsigned int nID, unsigned int &nIDSend, BOOL &bDelRecv, char **lpSend, BOOL &bDelSend, int &nFlags, int &nErrLen)
{
	

	//接收长度不能小于信息包头长度
	if (nSize<g_stru_ATPManageMsgHeadInfoSize)
	{
		return 0;
	}
	stru_ATPManageMsgHeadInfo _MsgHeadInfo={0};
	memcpy((char*)&_MsgHeadInfo,lpRecv,g_stru_ATPManageMsgHeadInfoSize);

	switch (_MsgHeadInfo.nMsgType)
	{
	case ID_ATPMANAGE_CREATEMANAGER:					//50021	创建管理员(超级管理员)
		 {	 
			 //Receive_CREATEMANAGER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
			  OnRecvData(ID_ATPMANAGE_CREATEMANAGER,(char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize], nSize-g_stru_ATPManageMsgHeadInfoSize);
			 if (_MsgHeadInfo.nFlags == 1)
			 {
				 OnRecvData(ID_ATPMANAGE_CREATEMANAGER,(char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize], nSize-g_stru_ATPManageMsgHeadInfoSize);
			 }
			 
		 }break;
	case ID_ATPMANAGE_DELETEMANAGER:					//50022	删除管理员(超级管理员)
		 {
			 OnRecvData(ID_ATPMANAGE_DELETEMANAGER,(char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize], nSize-g_stru_ATPManageMsgHeadInfoSize);
			 //Receive_DELETEMANAGER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYMANAGER:					//50023	修改管理员(超级管理员，管理员)
		 {
			 Receive_MODIFYMANAGER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);	
		 }break;
	case ID_ATPMANAGE_QUERYMANAGERINFO:				//50024	查询管理员(超级管理员)
		 {
			 Receive_QUERYMANAGERINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
			 OnRecvData(ID_ATPMANAGE_QUERYMANAGERINFO,(char *)m_recvManagerData._pAnswerData,m_recvManagerData._nUsedMemory);
		 }break;
	case ID_ATPMANAGE_CREATESERVERGROUP:			//50031	创建服务器组(超级管理员)
		 {
			 Receive_CREATESERVERGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_DELETESERVERGROUP:			//50032	删除服务器组(超级管理员)
		 {
			 Receive_DELETESERVERGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYSERVERGROUP:			//50033	修改服务器组(超级管理员)
		 {
			 Receive_MODIFYSERVERGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYSERVERGROUPINFO:			//50034	查询服务器组(超级管理员)
		 {
			 Receive_QUERYSERVERGROUPINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_CREATESERVER:					//50041	创建服务器(超级管理员)
		 {
			 Receive_CREATESERVER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_DELETESERVER:					//50042	删除服务器(超级管理员)
		 {
			 Receive_DELETESERVER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYSERVER:					//50043	修改服务器(超级管理员)
		 {
			 Receive_MODIFYSERVER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYSERVERINFO:				//50044	查询服务器(超级管理员)
		 {
			 Receive_QUERYSERVERINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYPERMISSIONINFO:			//50051	查询权限(超级管理员、管理员)
		 {
			 Receive_QUERYPERMISSIONINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_ADDALGORITHMGROUP:			//51011	添加算法组(管理员)
		 {
			 Receive_ADDALGORITHMGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_DELETEALGORITHMGROUP:			//51012	删除算法组(管理员)
		 {
			 Receive_DELETEALGORITHMGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYALGORITHMGROUP:			//51013	修改算法组(管理员)
		 {
			 Receive_MODIFYALGORITHMGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYALGORITHMGROUPINFO:		//51014查询算法组(管理员)
		 {
			 Receive_QUERYALGORITHMGROUPINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_ADDALGORITHM:					//51021	添加算法信息(管理员)
		 {
			 Receive_ADDALGORITHM((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_DELETEALGORITHM:				//51022	删除算法信息(管理员)
		 {
			 Receive_DELETEALGORITHM((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYALGORITHM:				//51023	修改算法(管理员)
		 {
			 Receive_MODIFYALGORITHM((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYALGORITHMINFO:			//51024	修改算法信息(管理员)
		 {
			 Receive_MODIFYALGORITHMINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYALGORITHMINFO:			//51025	查询算法信息(管理员)
		 {
			 Receive_QUERYALGORITHMINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYALGORITHMPARAM:			//51026	查询算法参数
		 {
			 Receive_QUERYALGORITHMPARAM((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYALGORITHMVERSION:		//51027	查询算法历史版本
		 {
			 Receive_QUERYALGORITHMVERSION((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_ADDUSERGROUP:					//51041	添加用户组(管理员)
		 {
			 Receive_ADDUSERGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_DELETEUSERGROUP:				//51042	删除用户组(管理员)
		 {
			 Receive_DELETEUSERGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYUSERGROUP:				//51043	修改用户组(管理员)
		 {
			 Receive_MODIFYUSERGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYUSERGROUPINFO:			//51044	查询用户组信息(管理员)
		 {
			 Receive_QUERYUSERGROUPINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_ADDUSER:						//51051	添加用户(管理员)
		 {
			 Receive_ADDUSER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_DELETEUSER:					//51052	删除用户(管理员)
		 {
			 Receive_DELETEUSER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYUSER:					//51053	修改用户(管理员)
		 {
			 Receive_MODIFYUSER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYUSERINFO:				//51054	查询用户信息(管理员)
		 {
			 Receive_QUERYUSERINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYUSEROPERATELOG:			//51061	查询用户操作日志(管理员)struReq_AT
		 {
			 Receive_QUERYUSEROPERATELOG((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYUSEDALGORITHM:			//51071	查询算法统计信息(管理员)
		 {
			 Receive_QUERYUSEDALGORITHM((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYUSERALGORITHM:			//51072	查询用户使用算法统计信息(管理员)
		  {
			  Receive_QUERYUSERALGORITHM((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		  }break;
	case ID_ATPMANAGE_QUERYSERVERALGORITHM:			//51073	查询服务器运行算法统计信息(管理员)
		  {
			  Receive_QUERYSERVERALGORITHM((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		  }break;
	default:
		break;
	}

	return 0;
}

int  CATPNetCProcessor::OnSendData(CString &strSendDesDN, char **lpSend, unsigned int &nID, BOOL &bDelete, int &nFlags, int &nErrLen)
{
	return true;
}


//50021//	创建管理员(超级管理员)
void CATPNetCProcessor::Receive_CREATEMANAGER(const char *pRecvData,int nLength)
{

}

//50022//	删除管理员(超级管理员)
void CATPNetCProcessor::Receive_DELETEMANAGER(const char *pRecvData,int nLength)
{

}

//50023//	修改管理员(超级管理员，管理员)
void CATPNetCProcessor::Receive_MODIFYMANAGER(const char *pRecvData,int nLength)
{

}

//50024//	查询管理员(超级管理员)				
void CATPNetCProcessor::Receive_QUERYMANAGERINFO(const char *pRecvData,int nLength)
{
	AllocateMemory(&m_recvManagerData,nLength);
	stru_ATPManagerInfo *pManagerInfo = NULL;
	struATPDataBaseManager *pDataBaseManager = NULL;
	char *pData = NULL;
	int i = 0;
	int nUsedCount = 0;//每次使用内存数量
	int nServerBlock=0,nServerGroupBlock=0;
	int nstru_ATPManagerInfoSize = sizeof stru_ATPManagerInfo;
	for (;i<nLength;)
	{
		nUsedCount = 0;
		pManagerInfo		= (stru_ATPManagerInfo *)&pRecvData[i];
		nServerBlock		= pManagerInfo->ServerBlock.nItems*pManagerInfo->ServerBlock.nItemSize;
		nServerGroupBlock	= pManagerInfo->ServerGroupBlock.nItems*pManagerInfo->ServerGroupBlock.nItemSize;
		int blockBegin = i+sizeof stru_ATPManagerInfo;

		//memcpy(pData,(char *)&pRecvData[i+sizeof stru_ATPManagerInfo],nServerBlock+nServerGroupBlock);



		pDataBaseManager = (struATPDataBaseManager *)&m_recvManagerData._pAnswerData[m_recvManagerData._nUsedMemory];
		pDataBaseManager->pServerIDs = (struATPAutoID *)&m_recvManagerData._pAnswerData[m_recvManagerData._nUsedMemory+sizeof stru_ATPManagerInfo];
		pDataBaseManager->pServerGroupIDs = (struATPAutoID *)&m_recvManagerData._pAnswerData[m_recvManagerData._nUsedMemory+sizeof stru_ATPManagerInfo+nServerBlock];

		{

				strncpy(pDataBaseManager->szID,pManagerInfo->szID,sizeof pDataBaseManager->szID);									//	管理员ID
				strncpy(pDataBaseManager->szName,pManagerInfo->szName,sizeof pDataBaseManager->szName);								//	名字
				strncpy(pDataBaseManager->szPwd,pManagerInfo->szPwd,sizeof pDataBaseManager->szPwd);								//	密码
				pDataBaseManager->nStatus=pManagerInfo->nStatus;										//	管理员状态  0 1 2
				strncpy(pDataBaseManager->szExplain,pManagerInfo->szExplain,sizeof pDataBaseManager->szExplain);						//	说明信息
				memcpy((char*)pDataBaseManager->nPermissionIDs,(char*)pManagerInfo->nPermissionIDs,sizeof pDataBaseManager->nPermissionIDs);	//	权限ID
				pDataBaseManager->nCreateDate=pManagerInfo->nCreateDate;								//	创建日期
				pDataBaseManager->nCreateTime=pManagerInfo->nCreateTime;								//	创建时间
				pDataBaseManager->nLastDate=pManagerInfo->nLastDate;									//	最后登陆日期
				pDataBaseManager->nLastTime=pManagerInfo->nLastTime;									//	最后登陆时间
				pDataBaseManager->nDeleteMark=pManagerInfo->nDeleteMark;								//	删除标志
				pDataBaseManager->nServerN=pManagerInfo->ServerBlock.nItems;							//	服务器个数
				memcpy(pDataBaseManager->pServerIDs,(char *)&pRecvData[blockBegin],nServerBlock);													//	服务器IDs
				pDataBaseManager->nServerGroupN=pManagerInfo->ServerGroupBlock.nItems;					//	服务器组个数
				memcpy(pDataBaseManager->pServerGroupIDs,(char *)&pRecvData[blockBegin+nServerBlock],nServerGroupBlock);												//	服务器组IDs

		}

		nUsedCount = nstru_ATPManagerInfoSize + nServerBlock + nServerGroupBlock;
		i += nUsedCount;
		m_recvManagerData._nUsedMemory+=nUsedCount;
	}
	
	

	
}			

//服务器组
//0031//	创建服务器组(超级管理员)
void CATPNetCProcessor::Receive_CREATESERVERGROUP(const char *pRecvData,int nLength)
{

}
//50032//	删除服务器组(超级管理员)
void CATPNetCProcessor::Receive_DELETESERVERGROUP(const char *pRecvData,int nLength)
{

}
//50033//	修改服务器组(超级管理员)
void CATPNetCProcessor::Receive_MODIFYSERVERGROUP(const char *pRecvData,int nLength)
{

}
//50034//	查询服务器组(超级管理员)
void CATPNetCProcessor::Receive_QUERYSERVERGROUPINFO(const char *pRecvData,int nLength)
{

}		

//服务器
//50041//	创建服务器(超级管理员)
void CATPNetCProcessor::Receive_CREATESERVER(const char *pRecvData,int nLength)
{

}

//50042//	删除服务器(超级管理员)
void CATPNetCProcessor::Receive_DELETESERVER(const char *pRecvData,int nLength)
{

}

//50043//	修改服务器(超级管理员)
void CATPNetCProcessor::Receive_MODIFYSERVER(const char *pRecvData,int nLength)
{

}

//50044//	查询服务器(超级管理员)
void CATPNetCProcessor::Receive_QUERYSERVERINFO(const char *pRecvData,int nLength)
{

}			

//权限

//50051//	查询权限(超级管理员、管理员)
void CATPNetCProcessor::Receive_QUERYPERMISSIONINFO(const char *pRecvData,int nLength)
{

}		

/************************************************************************/
/*                                       管理员                               */
/************************************************************************/

//算法组
//51011//	添加算法组(管理员)
void CATPNetCProcessor::Receive_ADDALGORITHMGROUP(const char *pRecvData,int nLength)
{

}

//51012//	删除算法组(管理员)
void CATPNetCProcessor::Receive_DELETEALGORITHMGROUP(const char *pRecvData,int nLength)
{

}

//51013//	修改算法组(管理员)
void CATPNetCProcessor::Receive_MODIFYALGORITHMGROUP(const char *pRecvData,int nLength)
{

}

//51014//查询算法组(管理员)
void CATPNetCProcessor::Receive_QUERYALGORITHMGROUPINFO(const char *pRecvData,int nLength)
{

}	

//算法
//51021//	添加算法信息(管理员)
void CATPNetCProcessor::Receive_ADDALGORITHM(const char *pRecvData,int nLength)
{

}

//51022//	删除算法信息(管理员)
void CATPNetCProcessor::Receive_DELETEALGORITHM(const char *pRecvData,int nLength)
{

}

//51023//	修改算法(管理员)
void CATPNetCProcessor::Receive_MODIFYALGORITHM(const char *pRecvData,int nLength)
{

}

//51024//	修改算法信息(管理员)
void CATPNetCProcessor::Receive_MODIFYALGORITHMINFO(const char *pRecvData,int nLength)
{

}		

//算法属性
//51025//	查询算法信息(管理员)
void CATPNetCProcessor::Receive_QUERYALGORITHMINFO(const char *pRecvData,int nLength)
{

}

//51026//	查询算法参数
void CATPNetCProcessor::Receive_QUERYALGORITHMPARAM(const char *pRecvData,int nLength)
{

}

//51027//	查询算法历史版本
void CATPNetCProcessor::Receive_QUERYALGORITHMVERSION(const char *pRecvData,int nLength)
{

}	

//用户组	
//51041//	添加用户组(管理员)				 
void CATPNetCProcessor::Receive_ADDUSERGROUP(const char *pRecvData,int nLength)
{

}

//51042//	删除用户组(管理员)
void CATPNetCProcessor::Receive_DELETEUSERGROUP(const char *pRecvData,int nLength)
{

}

//51043//	修改用户组(管理员)
void CATPNetCProcessor::Receive_MODIFYUSERGROUP(const char *pRecvData,int nLength)
{

}

//51044//	查询用户组信息(管理员)
void CATPNetCProcessor::Receive_QUERYUSERGROUPINFO(const char *pRecvData,int nLength)
{

}		

//用户

//51051//	添加用户(管理员)
void CATPNetCProcessor::Receive_ADDUSER(const char *pRecvData,int nLength)
{

}

//51052//	删除用户(管理员)
void CATPNetCProcessor::Receive_DELETEUSER(const char *pRecvData,int nLength)
{

}

//51053//	修改用户(管理员)
void CATPNetCProcessor::Receive_MODIFYUSER(const char *pRecvData,int nLength)
{

}

//51054//	查询用户信息(管理员)
void CATPNetCProcessor::Receive_QUERYUSERINFO(const char *pRecvData,int nLength)
{

}				

//用户操作日志

//51061//	查询用户操作日志(管理员)struReq_ATPManage_ATPManageOperateLog
void CATPNetCProcessor::Receive_QUERYUSEROPERATELOG(const char *pRecvData,int nLength)
{

}		

//算法日志

//51071//	查询算法统计信息(管理员)
void CATPNetCProcessor::Receive_QUERYUSEDALGORITHM(const char *pRecvData,int nLength)
{

}

//51072//	查询用户使用算法统计信息(管理员)
void CATPNetCProcessor::Receive_QUERYUSERALGORITHM(const char *pRecvData,int nLength)
{

}

//51073//	查询服务器运行算法统计信息(管理员)
void CATPNetCProcessor::Receive_QUERYSERVERALGORITHM(const char *pRecvData,int nLength)
{

}


