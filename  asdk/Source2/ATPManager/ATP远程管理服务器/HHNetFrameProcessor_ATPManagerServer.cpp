// HHNetFrameProcessor_ATPManagerServer.cpp : 实现文件
//

#include "stdafx.h"
#include "ATPManager.h"
#include "HHNetFrameProcessor_ATPManagerServer.h"
#include <direct.h>
#include "WndBGS.h"
#include "ATPErrorDefine.h"
extern CATPFileDBApi *g_pATPFileDBApi;
extern CWndATPManagerBGS g_wndMsgTransfer;
extern CPtrList g_StackList;

#define LACKACCESS 2

// CHHNetFrameProcessor_ATPManagerServer
IMPLEMENT_DYNCREATE(CHHNetFrameProcessor_ATPManagerServer, CHHNetFrameProcessor)
CHHNetFrameProcessor_ATPManagerServer::CHHNetFrameProcessor_ATPManagerServer()
{
	ZeroMemory(m_szAccount,16);
	m_nID = 0;
	m_bInitiativeBreak = TRUE;
}

CHHNetFrameProcessor_ATPManagerServer::~CHHNetFrameProcessor_ATPManagerServer()
{
	int i;
	i=0;
	//主动断开
	if (m_bInitiativeBreak)
	{
		StackList *pStackList=NULL;
		POSITION pos = g_StackList.GetHeadPosition();
		while(pos)
		{
			pStackList = (StackList *)g_StackList.GetAt(pos);
			if (m_nID==pStackList->nID)
			{
				g_StackList.RemoveAt(pos);
				delete pStackList;
				break;
			}
			g_StackList.GetNext(pos);
		}
	}
	
	
}

BOOL CHHNetFrameProcessor_ATPManagerServer::OnCreate()
{
	return TRUE;
}

BOOL CHHNetFrameProcessor_ATPManagerServer::OnDestroy(BOOL bInterrupt)
{
	struATPDataBaseManager *pATPDataBaseManager = NULL;
	//nRet 查询结果条数
	int nRet1 = g_pATPFileDBApi->QueryManager(m_szAccount,&pATPDataBaseManager);
	if (nRet1>0)
	{
		RemoveLoginList(g_pATPFileDBApi->GetLoginList(),pATPDataBaseManager);
		delete pATPDataBaseManager;
	}
	return TRUE;
}

int CHHNetFrameProcessor_ATPManagerServer::IsHavePermission(int nAccountType,const char *pAccountID,int nPermissionType)
{
	return g_pATPFileDBApi->IsHavePermission(nAccountType,pAccountID,nPermissionType);
}


int  CHHNetFrameProcessor_ATPManagerServer::OnReceiveData(const CString &strSrcDN, const CString &strDesDN, CString &strSendDesDN, char *lpRecv, int nSize, unsigned int nID, unsigned int &nIDSend, BOOL &bDelRecv, char **lpSend, BOOL &bDelSend, int &nFlags, int &nErrLen)
{
	//接收长度不能小于信息包头长度
	if (nSize<g_stru_ATPManageMsgHeadInfoSize)
	{
		return 0;
	}


	stru_ATPManageMsgHeadInfo _MsgHeadInfo={0};
	memcpy((char*)&_MsgHeadInfo,lpRecv,g_stru_ATPManageMsgHeadInfoSize);

	//////////////////////////////////////////////////////////////////////////
	


	_MsgHeadInfo.nChannel = 0;
	_MsgHeadInfo.nHeadSize = sizeof stru_ATPManageMsgHeadInfo;
	_MsgHeadInfo.nItem=0;
	_MsgHeadInfo.nFlags=1;

	BOOL bWrongWayLogin = FALSE;//登录方式的错误

	if (0 == strlen(m_szAccount))
	{
		//用户没有登录
		if (_MsgHeadInfo.nMsgType != ID_ATPMANAGE_LOGIN)
		{
			_MsgHeadInfo.nMsgType = ID_ATPMANAGE_LOGIN;
			bWrongWayLogin = TRUE;
		}
	} 



	switch (_MsgHeadInfo.nMsgType)
	{
	case ID_ATPMANAGE_LOGIN:
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			//错误的登录方式处理
			if (bWrongWayLogin)
			{
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				break;
			}
			
			int nRet = ManagerLogin(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			struReq_ATPManageLogin *pATPManageLogin = (struReq_ATPManageLogin *)&lpRecv[g_stru_ATPManageMsgHeadInfoSize];
			//登录成功
			if (0 == nRet)
			{
				AddOperateLog(ID_ATPMANAGE_LOGIN,m_szAccount,"登录成功");
				//////////////////////////////////////////////////////////////////////////
				//写入登录链表
				//g_pATPFileDBApi->
				//AddLoginList(g_pATPFileDBApi->GetLoginList());
				struATPDataBaseManager *pATPDataBaseManager = NULL;
				//nRet 查询结果条数
				int nRet1 = g_pATPFileDBApi->QueryManager(m_szAccount,&pATPDataBaseManager);
				if (nRet1>0)
				{
					AddLoginList(g_pATPFileDBApi->GetLoginList(),pATPDataBaseManager);


					StackList *pStackListT = new StackList(),*pStackList=NULL;
					pStackListT->nID = m_nID = pATPDataBaseManager->nSerialNumber;
					pStackListT->pCHHNetFrameProcessor_ATPManagerServer = this;


					POSITION pos = g_StackList.GetHeadPosition();
					while (pos)
					{
						pStackList = (StackList*)g_StackList.GetAt(pos);

						if (pStackListT->nID==pStackList->nID)
						{
							pStackList->pCHHNetFrameProcessor_ATPManagerServer->m_bInitiativeBreak = FALSE;
							pStackList->pCHHNetFrameProcessor_ATPManagerServer->DeleteThisNetFrameProcessor();
							g_StackList.RemoveAt(pos);
							delete pStackList;
							break;
						}
						g_StackList.GetNext(pos);

					}
					g_StackList.AddTail(pStackListT);

					delete pATPDataBaseManager;
				}
				//////////////////////////////////////////////////////////////////////////

				int nLenT = 0;
				char szReq[1024];
				stru_ATPManageMsgHeadInfo _MsgHeadInfoTemp={0};
				//////////////////////////////////////////////////////////////////////////
				memcpy((char *)&_MsgHeadInfoTemp,(char *)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYMANAGERINFO;//查询管理员
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYSERVERGROUPINFO;//查询服务器组
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
				struReq_ATPServerInfo_QUERY _ServerInfo_QUERY = {0};
				//通过服务器组ID查询服务器，为空则查询全部
				_ServerInfo_QUERY.nGroupID = 0;
				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYSERVERINFO;//查询全部服务器
				nLenT = g_stru_ATPManageMsgHeadInfoSize+sizeof struReq_ATPServerInfo_QUERY;
				//char szReqServer[nLenT];
				ZeroMemory(szReq,1024);
				memcpy(szReq,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				memcpy(&szReq[g_stru_ATPManageMsgHeadInfoSize],(char *)&_ServerInfo_QUERY,sizeof struReq_ATPServerInfo_QUERY);
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)szReq,nLenT,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYPERMISSIONINFO;//查询权限
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYALGORITHMGROUPINFO;//查询算法组
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
				struReq_ATPAlgorithm_QUERY _Algorithm_QUERY = {0};
				_Algorithm_QUERY.nGroupID = 0;

				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYALGORITHMINFO;//查询全部算法信息
				nLenT = g_stru_ATPManageMsgHeadInfoSize+sizeof struReq_ATPAlgorithm_QUERY;
				//char szReqAlgo[nLenT];
				ZeroMemory(szReq,1024);
				memcpy(szReq,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				memcpy(&szReq[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Algorithm_QUERY,sizeof struReq_ATPAlgorithm_QUERY);
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)szReq,nLenT,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYUSERGROUPINFO;//查询用户组
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
				struReq_ATPUserInfo_QUERY _UserInfo_QUERY = {0};
				_UserInfo_QUERY.nGroupID = 0;

				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYUSERINFO;//查询全部用户
				nLenT = g_stru_ATPManageMsgHeadInfoSize+sizeof struReq_ATPUserInfo_QUERY;
				//char szReqAlgo[nLenT];
				ZeroMemory(szReq,1024);
				memcpy(szReq,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				memcpy(&szReq[g_stru_ATPManageMsgHeadInfoSize],(char *)&_UserInfo_QUERY,sizeof struReq_ATPUserInfo_QUERY);
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)szReq,nLenT,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
			
			}
			else if (-1 == nRet)
			{
				AddOperateLog(ID_ATPMANAGE_LOGIN,pATPManageLogin->szLoginID,"密码错误");
			}
			else if (-2 == nRet)
			{
				AddOperateLog(ID_ATPMANAGE_LOGIN,pATPManageLogin->szLoginID,"帐号不存在");
			}

			if (pSendData)
			{
				//返回登录结果
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
		}
		break;
	case ID_ATPMANAGE_CREATEMANAGER:					//50021	创建管理员(超级管理员)
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			AddManager(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			
		}break;
	case ID_ATPMANAGE_DELETEMANAGER:					//50022	删除管理员(超级管理员)
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			DelManager(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,sz,1024);
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
		}break;
	case ID_ATPMANAGE_MODIFYMANAGER:					//50023	修改管理员(超级管理员，管理员)
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			ModifyManager(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
		}break;
	case ID_ATPMANAGE_QUERYMANAGERINFO:				//50024	查询管理员(超级管理员)
		{
			
			char *pSendData = NULL;
			int nSendLen = 0;
			QueryManager(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
		}break;
	case ID_ATPMANAGE_CREATESERVERGROUP:			//50031	创建服务器组(超级管理员)
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			AddServerGroup(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
		}break;
	case ID_ATPMANAGE_DELETESERVERGROUP:			//50032	删除服务器组(超级管理员)
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			DelServerGroup(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
		}break;
	case ID_ATPMANAGE_MODIFYSERVERGROUP:			//50033	修改服务器组(超级管理员)
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			ModifyServerGroup(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
		}break;
	case ID_ATPMANAGE_QUERYSERVERGROUPINFO:			//50034	查询服务器组(超级管理员)
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			QueryServerGroup(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
		}break;
	case ID_ATPMANAGE_CREATESERVER:					//50041	创建服务器(超级管理员)
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			AddServer(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
		}break;
	case ID_ATPMANAGE_DELETESERVER:					//50042	删除服务器(超级管理员)
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			DelServer(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
		}break;
	case ID_ATPMANAGE_MODIFYSERVER:					//50043	修改服务器(超级管理员)
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			ModifyServer(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
		}break;
	case ID_ATPMANAGE_QUERYSERVERINFO:				//50044	查询服务器(超级管理员)
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			QueryServer(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
		}break;
	case ID_ATPMANAGE_QUERYPERMISSIONINFO:			//50051	查询权限(超级管理员、管理员)
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			QueryPermission(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);
			ASSERT(_CrtCheckMemory());
			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
		}break;
	case ID_ATPMANAGE_ADDALGORITHMGROUP:			//51011	添加算法组(管理员)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_ADDALGORITHMGROUP))
			{
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				break;
			}
			char *pSendData = NULL;
			int nSendLen = 0;
			AddAlgorithmGroup(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
		}break;
	case ID_ATPMANAGE_DELETEALGORITHMGROUP:			//51012	删除算法组(管理员)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_DELETEALGORITHMGROUP))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"没有权限");
				_Operate.nResult = LACKACCESS;
				memcpy(sz,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				memcpy(&sz[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Operate,sizeof struAns_Operate);
				CHHNetFrameProcessor::Send(strSrcDN,sz,g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate);
				break;
			}
			char *pSendData = NULL;
			int nSendLen = 0;
			DelAlgorithmGroup(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_MODIFYALGORITHMGROUP:			//51013	修改算法组(管理员)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_MODIFYALGORITHMGROUP))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"没有权限");
				_Operate.nResult = LACKACCESS;
				memcpy(sz,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				memcpy(&sz[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Operate,sizeof struAns_Operate);
				CHHNetFrameProcessor::Send(strSrcDN,sz,g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate);
				break;
			}
			char *pSendData = NULL;
			int nSendLen = 0;
			ModifyAlgorithmGroup(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_QUERYALGORITHMGROUPINFO:		//51014查询算法组(管理员)
		{
// 			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_QUERYALGORITHMGROUPINFO))
// 			{
// 				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
// 				break;
// 			}
			char *pSendData = NULL;
			int nSendLen = 0;
			QueryAlgorithmGroup(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_ADDALGORITHM:					//51021	添加算法信息(管理员)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_ADDALGORITHM))
			{
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				break;
			}
			char *pSendData = NULL;
			int nSendLen = 0;
			AddAlgorithm(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_DELETEALGORITHM:				//51022	删除算法信息(管理员)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_DELETEALGORITHM))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"没有权限");
				_Operate.nResult = LACKACCESS;
				memcpy(sz,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				memcpy(&sz[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Operate,sizeof struAns_Operate);
				CHHNetFrameProcessor::Send(strSrcDN,sz,g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate);
				break;
			}
			char *pSendData = NULL;
			int nSendLen = 0;
			DelAlgorithm(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
		}break;
	case ID_ATPMANAGE_MODIFYALGORITHM:				//51023	修改算法(管理员)
		{
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}//break;
	case ID_ATPMANAGE_MODIFYALGORITHMINFO:			//51024	修改算法信息(管理员)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_MODIFYALGORITHMINFO))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"没有权限");
				_Operate.nResult = LACKACCESS;
				memcpy(sz,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				memcpy(&sz[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Operate,sizeof struAns_Operate);
				CHHNetFrameProcessor::Send(strSrcDN,sz,g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate);
				break;
			}
			char *pSendData = NULL;
			int nSendLen = 0;
			ModifyAlgorithm(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_QUERYALGORITHMINFO:			//51025	查询算法信息(管理员)
		{
// 			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_QUERYALGORITHMINFO))
// 			{
// 				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
// 				break;
// 			}
			char *pSendData = NULL;
			int nSendLen = 0;
			QueryAlgorithm(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_QUERYALGORITHMPARAM:			//51026	查询算法参数
		{
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_QUERYALGORITHMVERSION:		//51027	查询算法历史版本
		{
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_ADDUSERGROUP:					//51041	添加用户组(管理员)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_ADDUSERGROUP))
			{
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				break;
			}
			char *pSendData = NULL;
			int nSendLen = 0;
			AddUserGroup(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_DELETEUSERGROUP:				//51042	删除用户组(管理员)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_DELETEUSERGROUP))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"没有权限");
				_Operate.nResult = LACKACCESS;
				memcpy(sz,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				memcpy(&sz[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Operate,sizeof struAns_Operate);
				CHHNetFrameProcessor::Send(strSrcDN,sz,g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate);
				break;
			}
			char *pSendData = NULL;
			int nSendLen = 0;
			DelUserGroup(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_MODIFYUSERGROUP:				//51043	修改用户组(管理员)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_MODIFYUSERGROUP))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"没有权限");
				_Operate.nResult = LACKACCESS;
				memcpy(sz,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				memcpy(&sz[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Operate,sizeof struAns_Operate);
				CHHNetFrameProcessor::Send(strSrcDN,sz,g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate);
				break;
			}
			char *pSendData = NULL;
			int nSendLen = 0;
			ModifyUserGroup(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_QUERYUSERGROUPINFO:			//51044	查询用户组信息(管理员)
		{
// 			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_QUERYUSERGROUPINFO))
// 			{
// 				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
// 				break;
// 			}
			char *pSendData = NULL;
			int nSendLen = 0;
			QueryUserGroup(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_ADDUSER:						//51051	添加用户(管理员)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_ADDUSER))
			{
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				break;
			}
			char *pSendData = NULL;
			int nSendLen = 0;
			AddUser(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_DELETEUSER:					//51052	删除用户(管理员)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_DELETEUSER))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"没有权限");
				_Operate.nResult = LACKACCESS;
				memcpy(sz,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				memcpy(&sz[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Operate,sizeof struAns_Operate);
				CHHNetFrameProcessor::Send(strSrcDN,sz,g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate);
				break;
			}
			char *pSendData = NULL;
			int nSendLen = 0;
			DelUser(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_MODIFYUSER:					//51053	修改用户(管理员)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_MODIFYUSER))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"没有权限");
				_Operate.nResult = LACKACCESS;
				memcpy(sz,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				memcpy(&sz[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Operate,sizeof struAns_Operate);
				CHHNetFrameProcessor::Send(strSrcDN,sz,g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate);
				break;
			}
			char *pSendData = NULL;
			int nSendLen = 0;
			ModifyUser(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_QUERYUSERINFO:				//51054	查询用户信息
		{
// 			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_QUERYUSERINFO))
// 			{
// 				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
// 				break;
// 			}
			char *pSendData = NULL;
			int nSendLen = 0;
			QueryUser(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);	
		}break;
	case ID_ATPMANAGE_QUERYUSEROPERATELOG:			//51061	查询用户操作日志(管理员)struReq_AT
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			QueryOperateLog(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_QUERYUSEDALGORITHM:			//51071	查询算法统计信息(管理员)
		{
			char *pSendData = NULL;
			int nSendLen = 0;
			QueryAlgorithmLog(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			if (pSendData)
			{
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_QUERYUSERALGORITHM:			//51072	查询用户使用算法统计信息(管理员)
		{
			CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);	
		}break;
	case ID_ATPMANAGE_QUERYSERVERALGORITHM:			//51073	查询服务器运行算法统计信息(管理员)
		{
			CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);
		}break;
	default:
		break;
	}


	return 0;
	//CHHNetFrameProcessor::Send(strDN,"Hello,World!",strlen("Hello,World!"));
}

int  CHHNetFrameProcessor_ATPManagerServer::OnSendData(CString &strSendDesDN, char **lpSend, unsigned int &nID, BOOL &bDelete, int &nFlags, int &nErrLen)
{
	return true;
}


int CHHNetFrameProcessor_ATPManagerServer::AddManager(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{

	stru_ATPManagerInfo *pManagerInfo			= (stru_ATPManagerInfo *)pData;
	struATPDataBaseManager _DataBaseManager = {0};
	
	int nServerBlock			= 0;								//服务器块长度
	int nServerGroupBlock		= 0;								//服务器组块长度
	int nATPManagerInfoSize		= sizeof stru_ATPManagerInfo;		//管理员(网络包)结构体长度
	
	stru_ATPManagerInfo _ManagerInfo = {0};

	nServerBlock		= pManagerInfo->ServerBlock.nItems*pManagerInfo->ServerBlock.nItemSize;
	nServerGroupBlock	= pManagerInfo->ServerGroupBlock.nItems*pManagerInfo->ServerGroupBlock.nItemSize;

	_DataBaseManager.pServerIDs = NULL;
	if (pManagerInfo->ServerBlock.nItems>0)
	{
		_DataBaseManager.pServerIDs					= new struATPAutoID[pManagerInfo->ServerBlock.nItems];
	}
	_DataBaseManager.pServerGroupIDs = NULL;
	if (pManagerInfo->ServerGroupBlock.nItems>0)
	{
		_DataBaseManager.pServerGroupIDs			= new struATPAutoID[pManagerInfo->ServerGroupBlock.nItems];
	}
	
	
	
	{
		_DataBaseManager.nSerialNumber			= 0/*pManagerInfo->nSerialNumber*/;		
		strncpy(_DataBaseManager.szID,pManagerInfo->szID,sizeof _DataBaseManager.szID);											//	管理员ID
		strncpy(_DataBaseManager.szName,pManagerInfo->szName,sizeof _DataBaseManager.szName);										//	名字
		strncpy(_DataBaseManager.szPwd,pManagerInfo->szPwd,sizeof _DataBaseManager.szPwd);										//	密码
		_DataBaseManager.nStatus				= pManagerInfo->nStatus;															//	管理员状态  0 1 2
		strncpy(_DataBaseManager.szExplain,pManagerInfo->szExplain,sizeof _DataBaseManager.szExplain);							//	说明信息
		memcpy((char*)_DataBaseManager.nPermissionIDs,(char*)pManagerInfo->nPermissionIDs,sizeof _DataBaseManager.nPermissionIDs);//	权限ID
		
		CTime t = CTime::GetCurrentTime();

		_DataBaseManager.nCreateDate			= t.GetYear()*10000+t.GetMonth()*100+t.GetDay();														//	创建日期
		_DataBaseManager.nCreateTime			= t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();														//	创建时间
		_DataBaseManager.nLastDate				= 19800101;															//	最后登陆日期
		_DataBaseManager.nLastTime				= 235959;															//	最后登陆时间
		_DataBaseManager.nDeleteMark			= pManagerInfo->nDeleteMark;														//	删除标志
		_DataBaseManager.nServerN				= pManagerInfo->ServerBlock.nItems;													//	服务器个数
		if (_DataBaseManager.pServerIDs)
		{
			memcpy(_DataBaseManager.pServerIDs,(char *)&pData[nATPManagerInfoSize],nServerBlock);											//	服务器IDs
		}
		
		_DataBaseManager.nServerGroupN			= pManagerInfo->ServerGroupBlock.nItems;											//	服务器组个数
		if (_DataBaseManager.pServerGroupIDs)
		{
			memcpy(_DataBaseManager.pServerGroupIDs,(char *)&pData[nATPManagerInfoSize+nServerBlock],nServerGroupBlock);					//	服务器组IDs
		}
		
		
	}

	//////////////////////////////////////////////////////////////////////////
	struATPDataBaseManager _ATPDBSAlgorithm = {0};
	int nRet = g_pATPFileDBApi->AddManager(&_DataBaseManager,&_ATPDBSAlgorithm);
	
	if (_DataBaseManager.pServerIDs)
	{
		delete _DataBaseManager.pServerIDs;	_DataBaseManager.pServerIDs = NULL;
	}
	if (_DataBaseManager.pServerGroupIDs)
	{
		delete _DataBaseManager.pServerGroupIDs;_DataBaseManager.pServerGroupIDs = NULL;
	}
	
	

	if (nRet != 0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"创建管理员(ID):%s 失败-传入数据为NULL",_DataBaseManager.szID);
			break;
		case EXISTDATA:
			sprintf(sz,"创建管理员(ID):%s 失败-该管理员已经存在",_DataBaseManager.szID);
			break;
		case NEWERROR:
			sprintf(sz,"创建管理员(ID):%s 失败-NEW出错",_DataBaseManager.szID);
			break;
		case NULLHANDLE:
			sprintf(sz,"创建管理员(ID):%s 失败-操作句柄为NULL",_DataBaseManager.szID);
			break;
		default:
			break;
		}
		
		AddOperateLog(ID_ATPMANAGE_CREATEMANAGER,m_szAccount,sz);
		goto END___ADDMANAGER;
	}
	//////////////////////////////////////////////////////////////////////////
	

	{
		_ManagerInfo.nSerialNumber				= _ATPDBSAlgorithm.nSerialNumber;								//	自动增长
		strncpy(_ManagerInfo.szID,_ATPDBSAlgorithm.szID,sizeof _ManagerInfo.szID);								//	管理员ID
		strncpy(_ManagerInfo.szName,_ATPDBSAlgorithm.szName,sizeof _ManagerInfo.szName);						//	名字
		strncpy(_ManagerInfo.szPwd,_ATPDBSAlgorithm.szPwd,sizeof _ManagerInfo.szPwd);							//	密码
		_ManagerInfo.nStatus					= _ATPDBSAlgorithm.nStatus;										//	管理员状态  0 1 2
		strncpy(_ManagerInfo.szExplain,_ATPDBSAlgorithm.szExplain,sizeof _ManagerInfo.szExplain);				//	说明信息
		memcpy(_ManagerInfo.nPermissionIDs,_ATPDBSAlgorithm.nPermissionIDs,sizeof _ManagerInfo.nPermissionIDs);	//	权限ID
		_ManagerInfo.nCreateDate				= _ATPDBSAlgorithm.nCreateDate;									//	创建日期
		_ManagerInfo.nCreateTime				= _ATPDBSAlgorithm.nCreateTime;									//	创建时间
		_ManagerInfo.nLastDate					= _ATPDBSAlgorithm.nLastDate;									//	最后登陆日期
		_ManagerInfo.nLastTime					= _ATPDBSAlgorithm.nLastTime;									//	最后登陆时间
		_ManagerInfo.nDeleteMark				= _ATPDBSAlgorithm.nDeleteMark;									//	删除标志
		_ManagerInfo.ServerBlock.nItems			= _ATPDBSAlgorithm.nServerN;									//	服务器个数items	itemsize = sizeof(struATPAutoID)   服务器IDs
		_ManagerInfo.ServerBlock.nItemSize		= sizeof struATPAutoID;
		_ManagerInfo.ServerGroupBlock.nItems	= _ATPDBSAlgorithm.nServerGroupN;								//	服务器组个数items   itemsize = sizeof(struATPAutoID)  服务器组IDs
		_ManagerInfo.ServerGroupBlock.nItemSize = sizeof struATPAutoID;
	}
	//////////////////////////////////////////////////////////////////////////
	nServerBlock = _ManagerInfo.ServerBlock.nItems*sizeof struATPAutoID;
	nServerGroupBlock = _ManagerInfo.ServerGroupBlock.nItems*sizeof struATPAutoID;
	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + nATPManagerInfoSize + nServerBlock + nServerGroupBlock];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"创建管理员(ID):%s 成功-NEW出错",_ManagerInfo.szID);
		AddOperateLog(ID_ATPMANAGE_CREATEMANAGER,m_szAccount,sz);
		nRet = NEWERROR;
		goto END___ADDMANAGER;
	}
	char sz[128]={0};
	sprintf(sz,"创建管理员(ID):%s 成功",_ManagerInfo.szID);
	AddOperateLog(ID_ATPMANAGE_CREATEMANAGER,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + nATPManagerInfoSize + nServerBlock + nServerGroupBlock;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_ManagerInfo,nATPManagerInfoSize);
	if (_ATPDBSAlgorithm.pServerIDs)
	{
		memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize+nATPManagerInfoSize],(char *)_ATPDBSAlgorithm.pServerIDs,nServerBlock);
	}
	if (_ATPDBSAlgorithm.pServerGroupIDs)
	{
		memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize+nATPManagerInfoSize+nServerBlock],(char *)_ATPDBSAlgorithm.pServerGroupIDs,nServerGroupBlock);
	}
	
END___ADDMANAGER:

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::ModifyManager(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPManagerInfo *pManagerInfo			= (stru_ATPManagerInfo *)pData;
	struATPDataBaseManager _DataBaseManager	= {0};

	
	int nServerBlock			= 0;									//服务器块长度
	int nServerGroupBlock		= 0;									//服务器组块长度
	int nATPManagerInfoSize	= sizeof stru_ATPManagerInfo;				//管理员(网络包)结构体长度


	nServerBlock				= pManagerInfo->ServerBlock.nItems*pManagerInfo->ServerBlock.nItemSize;
	nServerGroupBlock			= pManagerInfo->ServerGroupBlock.nItems*pManagerInfo->ServerGroupBlock.nItemSize;
	_DataBaseManager.pServerIDs = NULL;
	if (pManagerInfo->ServerBlock.nItems>0)
	{
		_DataBaseManager.pServerIDs					= new struATPAutoID[pManagerInfo->ServerBlock.nItems];
	}
	_DataBaseManager.pServerGroupIDs = NULL;
	if (pManagerInfo->ServerGroupBlock.nItems>0)
	{
		_DataBaseManager.pServerGroupIDs			= new struATPAutoID[pManagerInfo->ServerGroupBlock.nItems];
	}
	
	

	{
		_DataBaseManager.nSerialNumber			= pManagerInfo->nSerialNumber;		
		strncpy(_DataBaseManager.szID,pManagerInfo->szID,sizeof _DataBaseManager.szID);												//	管理员ID
		strncpy(_DataBaseManager.szName,pManagerInfo->szName,sizeof _DataBaseManager.szName);										//	名字
		strncpy(_DataBaseManager.szPwd,pManagerInfo->szPwd,sizeof _DataBaseManager.szPwd);											//	密码
		_DataBaseManager.nStatus				= pManagerInfo->nStatus;															//	管理员状态  0 1 2
		strncpy(_DataBaseManager.szExplain,pManagerInfo->szExplain,sizeof _DataBaseManager.szExplain);								//	说明信息
		memcpy((char*)_DataBaseManager.nPermissionIDs,(char*)pManagerInfo->nPermissionIDs,sizeof _DataBaseManager.nPermissionIDs);	//	权限ID
		_DataBaseManager.nCreateDate			= pManagerInfo->nCreateDate;														//	创建日期
		_DataBaseManager.nCreateTime			= pManagerInfo->nCreateTime;														//	创建时间
		_DataBaseManager.nLastDate				= pManagerInfo->nLastDate;															//	最后登陆日期
		_DataBaseManager.nLastTime				= pManagerInfo->nLastTime;															//	最后登陆时间
		_DataBaseManager.nDeleteMark			= pManagerInfo->nDeleteMark;														//	删除标志
		_DataBaseManager.nServerN				= pManagerInfo->ServerBlock.nItems;													//	服务器个数
		if (_DataBaseManager.pServerIDs)
		{
			memcpy(_DataBaseManager.pServerIDs,(char *)&pData[nATPManagerInfoSize],nServerBlock);									//	服务器IDs
		}
		
		_DataBaseManager.nServerGroupN			= pManagerInfo->ServerGroupBlock.nItems;											//	服务器组个数
		if (_DataBaseManager.pServerGroupIDs)
		{
			memcpy(_DataBaseManager.pServerGroupIDs,(char *)&pData[nATPManagerInfoSize+nServerBlock],nServerGroupBlock);			//	服务器组IDs
		}
		

	}
	//////////////////////////////////////////////////////////////////////////
	int nRet = g_pATPFileDBApi->ModifyManager(&_DataBaseManager);

	if (_DataBaseManager.pServerIDs)
	{
		delete _DataBaseManager.pServerIDs;	_DataBaseManager.pServerIDs = NULL;
	}
	if (_DataBaseManager.pServerGroupIDs)
	{
		delete _DataBaseManager.pServerGroupIDs;_DataBaseManager.pServerGroupIDs = NULL;
	}
	
	

	//////////////////////////////////////////////////////////////////////////
	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;
	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"修改成功");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"修改管理员(ID):%s 失败-传入数据为NULL",_DataBaseManager.szID);
			break;
		case EXISTDATA:
			sprintf(sz,"修改管理员(ID):%s 失败-该管理员已经存在",_DataBaseManager.szID);
			break;
		case NEWERROR:
			sprintf(sz,"修改管理员(ID):%s 失败-NEW出错",_DataBaseManager.szID);
			break;
		case NULLHANDLE:
			sprintf(sz,"修改管理员(ID):%s 失败-操作句柄为NULL",_DataBaseManager.szID);
			break;
		case ZERORECORD:
			sprintf(sz,"修改管理员(ID):%s 失败-没有该记录",_DataBaseManager.szID);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_MODIFYMANAGER,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"修改失败");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"修改管理员(ID):%s 成功-NEW出错",_DataBaseManager.szID);
		AddOperateLog(ID_ATPMANAGE_MODIFYMANAGER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"修改管理员(ID):%s 成功",_DataBaseManager.szID);
	AddOperateLog(ID_ATPMANAGE_MODIFYMANAGER,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);
	
	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::DelManager(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPManagerInfo *pManagerInfo			= (stru_ATPManagerInfo *)pData;
	struATPDataBaseManager _DataBaseManager	= {0};


	int nServerBlock			= 0;								//服务器块长度
	int nServerGroupBlock		= 0;								//服务器组块长度
	int nATPManagerInfoSize	= sizeof stru_ATPManagerInfo;			//管理员(网络包)结构体长度


	nServerBlock		= pManagerInfo->ServerBlock.nItems*pManagerInfo->ServerBlock.nItemSize;
	nServerGroupBlock	= pManagerInfo->ServerGroupBlock.nItems*pManagerInfo->ServerGroupBlock.nItemSize;
	_DataBaseManager.pServerIDs = NULL;
	if (pManagerInfo->ServerBlock.nItems>0)
	{
		_DataBaseManager.pServerIDs					= new struATPAutoID[pManagerInfo->ServerBlock.nItems];
	}
	if (pManagerInfo->ServerGroupBlock.nItems>0)
	{
		_DataBaseManager.pServerGroupIDs			= new struATPAutoID[pManagerInfo->ServerGroupBlock.nItems];
	}
	
	

	{
		_DataBaseManager.nSerialNumber			= pManagerInfo->nSerialNumber;		
		strncpy(_DataBaseManager.szID,pManagerInfo->szID,sizeof _DataBaseManager.szID);												//	管理员ID
		strncpy(_DataBaseManager.szName,pManagerInfo->szName,sizeof _DataBaseManager.szName);										//	名字
		strncpy(_DataBaseManager.szPwd,pManagerInfo->szPwd,sizeof _DataBaseManager.szPwd);											//	密码
		_DataBaseManager.nStatus				= pManagerInfo->nStatus;															//	管理员状态  0 1 2
		strncpy(_DataBaseManager.szExplain,pManagerInfo->szExplain,sizeof _DataBaseManager.szExplain);								//	说明信息
		memcpy((char*)_DataBaseManager.nPermissionIDs,(char*)pManagerInfo->nPermissionIDs,sizeof _DataBaseManager.nPermissionIDs);	//	权限ID
		_DataBaseManager.nCreateDate			= pManagerInfo->nCreateDate;														//	创建日期
		_DataBaseManager.nCreateTime			= pManagerInfo->nCreateTime;														//	创建时间
		_DataBaseManager.nLastDate				= pManagerInfo->nLastDate;															//	最后登陆日期
		_DataBaseManager.nLastTime				= pManagerInfo->nLastTime;															//	最后登陆时间
		_DataBaseManager.nDeleteMark			= pManagerInfo->nDeleteMark;														//	删除标志
		_DataBaseManager.nServerN				= pManagerInfo->ServerBlock.nItems;													//	服务器个数
		if (_DataBaseManager.pServerIDs)
		{
			memcpy(_DataBaseManager.pServerIDs,(char *)&pData[nATPManagerInfoSize],nServerBlock);									//	服务器IDs
		}
		
		_DataBaseManager.nServerGroupN			= pManagerInfo->ServerGroupBlock.nItems;											//	服务器组个数
		if (_DataBaseManager.pServerGroupIDs)
		{
			memcpy(_DataBaseManager.pServerGroupIDs,(char *)&pData[nATPManagerInfoSize+nServerBlock],nServerGroupBlock);			//	服务器组IDs
		}
		

	}
	//////////////////////////////////////////////////////////////////////////
	int nRet = g_pATPFileDBApi->DelManager(&_DataBaseManager);

	if (_DataBaseManager.pServerIDs)
	{
		delete _DataBaseManager.pServerIDs;	
	}
	if (_DataBaseManager.pServerGroupIDs)
	{
		delete _DataBaseManager.pServerGroupIDs;
	}


	//////////////////////////////////////////////////////////////////////////
	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;
	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"删除成功");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"删除管理员(ID):%s 失败-传入数据为NULL",_DataBaseManager.szID);
			break;
		case EXISTDATA:
			sprintf(sz,"删除管理员(ID):%s 失败-该管理员已经存在",_DataBaseManager.szID);
			break;
		case NEWERROR:
			sprintf(sz,"删除管理员(ID):%s 失败-NEW出错",_DataBaseManager.szID);
			break;
		case NULLHANDLE:
			sprintf(sz,"删除管理员(ID):%s 失败-操作句柄为NULL",_DataBaseManager.szID);
			break;
		case ZERORECORD:
			sprintf(sz,"删除管理员(ID):%s 失败-没有该记录",_DataBaseManager.szID);
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_DELETEMANAGER,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"删除失败");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"删除管理员(ID):%s 成功-NEW出错",_DataBaseManager.szID);
		AddOperateLog(ID_ATPMANAGE_DELETEMANAGER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"删除管理员(ID):%s 成功",_DataBaseManager.szID);
	AddOperateLog(ID_ATPMANAGE_DELETEMANAGER,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::QueryManager(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseManager *pATPDataBaseManager = NULL;
	int nATPManagerInfoSize	= sizeof stru_ATPManagerInfo;		//管理员(网络包)结构体长度
	//nRet 查询结果条数
	int nRet = g_pATPFileDBApi->QueryManager(m_szAccount,&pATPDataBaseManager);

	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"查询管理员 失败-传入数据为NULL");
			break;
		case EXISTDATA:
			sprintf(sz,"查询管理员 失败-该管理员已经存在");
			break;
		case NEWERROR:
			sprintf(sz,"查询管理员 失败-NEW出错");
			break;
		case NULLHANDLE:
			sprintf(sz,"查询管理员 失败-操作句柄为NULL");
			break;
		case 0:
		case ZERORECORD:
			sprintf(sz,"查询管理员 失败-没有记录");
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_QUERYMANAGERINFO,m_szAccount,sz);
		return nRet;
	}
	
	int i = 0;
	*pnLen = g_stru_ATPManageMsgHeadInfoSize;//包头长度
	for (;i<nRet;i++)
	{
		(*pnLen) += (nATPManagerInfoSize+(pATPDataBaseManager[i].nServerN+pATPDataBaseManager[i].nServerGroupN)*sizeof struATPAutoID);
	}

	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"查询管理员 成功-NEW出错");
		AddOperateLog(ID_ATPMANAGE_QUERYMANAGERINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"查询管理员 成功");
	AddOperateLog(ID_ATPMANAGE_QUERYMANAGERINFO,m_szAccount,sz);
	stru_ATPManagerInfo _ManagerInfo	= {0};
	int nServerBlock = 0,nServerGroupBlock = 0;
	int nHead	= g_stru_ATPManageMsgHeadInfoSize;
	int nBody	= sizeof stru_ATPManagerInfo;
	int nEX		= 0;
	int nCount = 0;

	pHead->nItem = nRet;
	memcpy(*ppOutData,(char *)pHead,nHead);
	nCount = nHead;
	for (i=0;i<nRet;i++)
	{

			_ManagerInfo.nSerialNumber				= pATPDataBaseManager[i].nSerialNumber;										//	自动增长
			strncpy(_ManagerInfo.szID,pATPDataBaseManager[i].szID,sizeof _ManagerInfo.szID);										//	管理员ID																
			strncpy(_ManagerInfo.szName,pATPDataBaseManager[i].szName,sizeof _ManagerInfo.szName);									//	名字
			strncpy(_ManagerInfo.szPwd,pATPDataBaseManager[i].szPwd,sizeof _ManagerInfo.szPwd);									//	密码
			_ManagerInfo.nStatus					= pATPDataBaseManager[i].nStatus;												//	管理员状态  0 1 2
			strncpy(_ManagerInfo.szExplain,pATPDataBaseManager[i].szExplain,sizeof _ManagerInfo.szExplain);						//	说明信息
			memcpy((char *)_ManagerInfo.nPermissionIDs,(char *)pATPDataBaseManager[i].nPermissionIDs,sizeof _ManagerInfo.nPermissionIDs);	//	权限ID

			_ManagerInfo.nCreateDate				= pATPDataBaseManager[i].nCreateDate;													//	创建日期
			_ManagerInfo.nCreateTime				= pATPDataBaseManager[i].nCreateTime;													//	创建时间
			_ManagerInfo.nLastDate					= pATPDataBaseManager[i].nLastDate;												//	最后登陆日期
			_ManagerInfo.nLastTime					= pATPDataBaseManager[i].nLastTime;												//	最后登陆时间

			_ManagerInfo.nDeleteMark				= pATPDataBaseManager[i].nDeleteMark;											//	删除标志
			_ManagerInfo.ServerBlock.nItems			= pATPDataBaseManager[i].nServerN;												//	服务器个数items	itemsize = sizeof(struATPAutoID)   服务器IDs
			_ManagerInfo.ServerBlock.nItemSize		= sizeof struATPAutoID;
			_ManagerInfo.ServerGroupBlock.nItems	= pATPDataBaseManager[i].nServerGroupN;										//	服务器组个数items   itemsize = sizeof(struATPAutoID)  服务器组IDs
			_ManagerInfo.ServerGroupBlock.nItemSize	= sizeof struATPAutoID;


		nServerBlock = pATPDataBaseManager[i].nServerN*sizeof struATPAutoID;
		nServerGroupBlock = pATPDataBaseManager[i].nServerGroupN*sizeof struATPAutoID;
		memcpy(&(*ppOutData)[nCount],(char *)&_ManagerInfo,nBody);
		nCount += nBody;
		memcpy(&(*ppOutData)[nCount],(char*)pATPDataBaseManager[i].pServerIDs,nServerBlock);
		nCount += nServerBlock;
		memcpy(&(*ppOutData)[nCount],(char*)pATPDataBaseManager[i].pServerGroupIDs,nServerGroupBlock);
		nCount += nServerGroupBlock;
	}

	delete pATPDataBaseManager;
	pATPDataBaseManager = NULL;
	return nRet;
}



int CHHNetFrameProcessor_ATPManagerServer::AddServerGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPServerGroupInfo *pServerGroupInfo			= (stru_ATPServerGroupInfo *)pData;
	struATPDataBaseServerGroup _DataBaseServerGroup = {0};

	int nATPServerGroupInfoSize = sizeof stru_ATPServerGroupInfo;

	memcpy((char *)&_DataBaseServerGroup,(char *)pServerGroupInfo,nATPServerGroupInfoSize);

	//////////////////////////////////////////////////////////////////////////
	struATPDataBaseServerGroup _ATPDBSServerGroup = {0};
	int nRet = g_pATPFileDBApi->AddServerGroup(&_DataBaseServerGroup,&_ATPDBSServerGroup);


	if (nRet != 0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"添加服务器组(NAME):%s 失败-传入数据为NULL",_DataBaseServerGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"添加服务器组(NAME):%s 失败-该服务器组已经存在",_DataBaseServerGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"添加服务器组(NAME):%s 失败-NEW出错",_DataBaseServerGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"添加服务器组(NAME):%s 失败-操作句柄为NULL",_DataBaseServerGroup.szName);
			break;
		//case 0:
		case ZERORECORD:
			sprintf(sz,"添加服务器组(NAME):%s 失败-没有该记录",_DataBaseServerGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_CREATESERVERGROUP,m_szAccount,sz);
		return nRet;
	}
	
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + nATPServerGroupInfoSize;
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"添加服务器组(NAME):%s 成功-NEW出错",_DataBaseServerGroup.szName);
		AddOperateLog(ID_ATPMANAGE_CREATESERVERGROUP,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"添加服务器组(NAME):%s 成功",_DataBaseServerGroup.szName);
	AddOperateLog(ID_ATPMANAGE_CREATESERVERGROUP,m_szAccount,sz);
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_ATPDBSServerGroup,nATPServerGroupInfoSize);
	
	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::ModifyServerGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPServerGroupInfo *pServerGroupInfo			= (stru_ATPServerGroupInfo *)pData;
	struATPDataBaseServerGroup _DataBaseServerGroup = {0};

	int nATPServerGroupInfoSize = sizeof stru_ATPServerGroupInfo;
	memcpy((char *)&_DataBaseServerGroup,(char *)pServerGroupInfo,nATPServerGroupInfoSize);

	//////////////////////////////////////////////////////////////////////////
	
	int nRet = g_pATPFileDBApi->ModifyServerGroup(&_DataBaseServerGroup);


	//////////////////////////////////////////////////////////////////////////
	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;
	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"修改成功");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"修改服务器组(NAME):%s 失败-传入数据为NULL",_DataBaseServerGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"修改服务器组(NAME):%s 失败-该服务器组已经存在",_DataBaseServerGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"修改服务器组(NAME):%s 失败-NEW出错",_DataBaseServerGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"修改服务器组(NAME):%s 失败-操作句柄为NULL",_DataBaseServerGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"修改服务器组(NAME):%s 失败-没有该记录",_DataBaseServerGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_MODIFYSERVERGROUP,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"修改失败");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"修改服务器组(NAME):%s 成功-NEW出错",_DataBaseServerGroup.szName);
		AddOperateLog(ID_ATPMANAGE_MODIFYSERVERGROUP,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"修改服务器组(NAME):%s 成功",_DataBaseServerGroup.szName);
	AddOperateLog(ID_ATPMANAGE_MODIFYSERVERGROUP,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::DelServerGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPServerGroupInfo *pServerGroupInfo			= (stru_ATPServerGroupInfo *)pData;
	struATPDataBaseServerGroup _DataBaseServerGroup = {0};

	int nATPServerGroupInfoSize = sizeof stru_ATPServerGroupInfo;
	memcpy((char *)&_DataBaseServerGroup,(char *)pServerGroupInfo,nATPServerGroupInfoSize);

	//////////////////////////////////////////////////////////////////////////

	int nRet = g_pATPFileDBApi->DelServerGroup(&_DataBaseServerGroup);


	//////////////////////////////////////////////////////////////////////////
	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;
	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"删除成功");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"删除服务器组(NAME):%s 失败-传入数据为NULL",_DataBaseServerGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"删除服务器组(NAME):%s 失败-该服务器组已经存在",_DataBaseServerGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"删除服务器组(NAME):%s 失败-NEW出错",_DataBaseServerGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"删除服务器组(NAME):%s 失败-操作句柄为NULL",_DataBaseServerGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"删除服务器组(NAME):%s 失败-没有该记录",_DataBaseServerGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_DELETESERVERGROUP,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"删除失败");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"删除服务器组(NAME):%s 成功-NEW出错",_DataBaseServerGroup.szName);
		AddOperateLog(ID_ATPMANAGE_DELETESERVERGROUP,m_szAccount,sz);
		return -1;
	}
	char sz[128]={0};
	sprintf(sz,"删除服务器组(NAME):%s 成功",_DataBaseServerGroup.szName);
	AddOperateLog(ID_ATPMANAGE_DELETESERVERGROUP,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::QueryServerGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseServerGroup *pATPDataBaseServerGroup = NULL;
	int nATPServerGroupInfoSize = sizeof stru_ATPServerGroupInfo;
	//nRet 查询结果条数
	int nRet = g_pATPFileDBApi->QueryServerGroup(&pATPDataBaseServerGroup);

	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"查询服务器组 失败-传入数据为NULL");
			break;
		case EXISTDATA:
			sprintf(sz,"查询服务器组 失败-该服务器组已经存在");
			break;
		case NEWERROR:
			sprintf(sz,"查询服务器组 失败-NEW出错");
			break;
		case NULLHANDLE:
			sprintf(sz,"查询服务器组 失败-操作句柄为NULL");
			break;
			case 0:
		case ZERORECORD:
			sprintf(sz,"查询服务器组 成功-没有该记录");
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_QUERYSERVERGROUPINFO,m_szAccount,sz);
		return nRet;
	}
	
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + nRet*nATPServerGroupInfoSize;
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"查询服务器组 成功-NEW出错");
		AddOperateLog(ID_ATPMANAGE_QUERYSERVERGROUPINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"查询服务器组 成功");
	AddOperateLog(ID_ATPMANAGE_QUERYSERVERGROUPINFO,m_szAccount,sz);
	stru_ATPManagerInfo _ManagerInfo	= {0};
	int nHead	= g_stru_ATPManageMsgHeadInfoSize;

	int nCount = 0;
	pHead->nItem = nRet;
	memcpy(*ppOutData,(char *)pHead,nHead);
	int i = 0;
	nCount = nHead;
	for (i=0;i<nRet;i++)
	{
		memcpy(&(*ppOutData)[nCount],(char *)&pATPDataBaseServerGroup[i],nATPServerGroupInfoSize);
		nCount += nATPServerGroupInfoSize;
		
	}

	delete pATPDataBaseServerGroup;
	pATPDataBaseServerGroup = NULL;
	return nRet;
}



int CHHNetFrameProcessor_ATPManagerServer::AddServer(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPServerInfo *pServerInfo			= (stru_ATPServerInfo *)pData;
	struATPDataBaseServer _DataBaseServer = {0};

	int nATPServerInfoSize = sizeof stru_ATPServerInfo;

	memcpy((char *)&_DataBaseServer,(char *)pServerInfo,nATPServerInfoSize);

	//////////////////////////////////////////////////////////////////////////
	struATPDataBaseServer _ATPDBSServer = {0};
	int nRet = g_pATPFileDBApi->AddServer(&_DataBaseServer,&_ATPDBSServer);


	if (nRet != 0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"添加服务器(NAME/IP):%s 失败-传入数据为NULL",_DataBaseServer.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"添加服务器(NAME/IP):%s 失败-该服务器组已经存在",_DataBaseServer.szName);
			break;
		case NEWERROR:
			sprintf(sz,"添加服务器(NAME/IP):%s 失败-NEW出错",_DataBaseServer.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"添加服务器(NAME/IP):%s 失败-操作句柄为NULL",_DataBaseServer.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"添加服务器(NAME/IP):%s 失败-没有该记录",_DataBaseServer.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_CREATESERVER,m_szAccount,sz);
		return nRet;
	}

	*pnLen = g_stru_ATPManageMsgHeadInfoSize + nATPServerInfoSize;
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"添加服务器(NAME/IP):%s 成功-NEW出错",_DataBaseServer.szName);
		AddOperateLog(ID_ATPMANAGE_CREATESERVER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"添加服务器(NAME/IP):%s 成功",_DataBaseServer.szName);
	AddOperateLog(ID_ATPMANAGE_CREATESERVER,m_szAccount,sz);
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_ATPDBSServer,nATPServerInfoSize);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::ModifyServer(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPServerInfo *pServerInfo			= (stru_ATPServerInfo *)pData;
	struATPDataBaseServer _DataBaseServer = {0};

	int nATPServerInfoSize = sizeof stru_ATPServerInfo;
	memcpy((char *)&_DataBaseServer,(char *)pServerInfo,nATPServerInfoSize);

	//////////////////////////////////////////////////////////////////////////

	int nRet = g_pATPFileDBApi->ModifyServer(&_DataBaseServer);

	//////////////////////////////////////////////////////////////////////////
	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;
	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"修改成功");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"修改服务器(NAME/IP):%s 失败-传入数据为NULL",_DataBaseServer.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"修改服务器(NAME/IP):%s 失败-该服务器组已经存在",_DataBaseServer.szName);
			break;
		case NEWERROR:
			sprintf(sz,"修改服务器(NAME/IP):%s 失败-NEW出错",_DataBaseServer.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"修改服务器(NAME/IP):%s 失败-操作句柄为NULL",_DataBaseServer.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"修改服务器(NAME/IP):%s 失败-没有该记录",_DataBaseServer.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_MODIFYSERVER,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"修改失败");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"修改服务器(NAME/IP):%s 成功-NEW出错",_DataBaseServer.szName);
		AddOperateLog(ID_ATPMANAGE_MODIFYSERVER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"修改服务器(NAME/IP):%s 成功",_DataBaseServer.szName);
	AddOperateLog(ID_ATPMANAGE_MODIFYSERVER,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::DelServer(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPServerInfo *pServerInfo			= (stru_ATPServerInfo *)pData;
	struATPDataBaseServer _DataBaseServer = {0};

	int nATPServerInfoSize = sizeof stru_ATPServerInfo;
	memcpy((char *)&_DataBaseServer,(char *)pServerInfo,nATPServerInfoSize);

	//////////////////////////////////////////////////////////////////////////

	int nRet = g_pATPFileDBApi->DelServer(&_DataBaseServer);

	//////////////////////////////////////////////////////////////////////////
	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;
	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"删除成功");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"删除服务器(NAME/IP):%s 失败-传入数据为NULL",_DataBaseServer.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"删除服务器(NAME/IP):%s 失败-该服务器组已经存在",_DataBaseServer.szName);
			break;
		case NEWERROR:
			sprintf(sz,"删除服务器(NAME/IP):%s 失败-NEW出错",_DataBaseServer.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"删除服务器(NAME/IP):%s 失败-操作句柄为NULL",_DataBaseServer.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"删除服务器(NAME/IP):%s 失败-没有该记录",_DataBaseServer.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_DELETESERVER,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"删除失败");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"删除服务器(NAME/IP):%s 成功-NEW出错",_DataBaseServer.szName);
		AddOperateLog(ID_ATPMANAGE_DELETESERVER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"删除服务器(NAME/IP):%s 成功",_DataBaseServer.szName);
	AddOperateLog(ID_ATPMANAGE_DELETESERVER,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::QueryServer(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseServer *pATPDataBaseServer = NULL;
	int nATPServerInfoSize = sizeof stru_ATPServerInfo;
	//nRet 查询结果条数
	struATPDataBaseServer_QUERY *pATPDataBaseServer_QUERY = (struATPDataBaseServer_QUERY *)pData;
	int nRet = g_pATPFileDBApi->QueryServer(pATPDataBaseServer_QUERY,&pATPDataBaseServer);

	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"查询服务器 失败-传入数据为NULL");
			break;
		case EXISTDATA:
			sprintf(sz,"查询服务器 失败-该服务器已经存在");
			break;
		case NEWERROR:
			sprintf(sz,"查询服务器 失败-NEW出错");
			break;
		case NULLHANDLE:
			sprintf(sz,"查询服务器 失败-操作句柄为NULL");
			break;
		case 0:
		case ZERORECORD:
			sprintf(sz,"查询服务器 成功-没有该记录");
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_QUERYSERVERINFO,m_szAccount,sz);
		return nRet;
	}

	*pnLen = g_stru_ATPManageMsgHeadInfoSize + nRet*nATPServerInfoSize;
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"查询服务器组 成功-NEW出错");
		AddOperateLog(ID_ATPMANAGE_QUERYSERVERINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"查询服务器组 成功");
	AddOperateLog(ID_ATPMANAGE_QUERYSERVERINFO,m_szAccount,sz);
	stru_ATPManagerInfo _ManagerInfo	= {0};

	int nHead	= g_stru_ATPManageMsgHeadInfoSize;

	int nCount = 0;
	pHead->nItem = nRet;
	memcpy(*ppOutData,(char *)pHead,nHead);
	int i = 0;
	nCount = nHead;
	for (i=0;i<nRet;i++)
	{
		memcpy(&(*ppOutData)[nCount],(char *)&pATPDataBaseServer[i],nATPServerInfoSize);
		nCount += nATPServerInfoSize;

	}

	delete pATPDataBaseServer;
	pATPDataBaseServer = NULL;
	return nRet;
}



int CHHNetFrameProcessor_ATPManagerServer::QueryPermission(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBasePermission *pATPDataBasePermission = NULL;
	int nATPDataBasePermissionSize = sizeof struATPDataBasePermission;
	//nRet 查询结果条数
	int nRet = g_pATPFileDBApi->QueryPermission(&pATPDataBasePermission);

	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"查询权限 失败-传入数据为NULL");
			break;
		case EXISTDATA:
			sprintf(sz,"查询权限 失败-该权限已经存在");
			break;
		case NEWERROR:
			sprintf(sz,"查询权限 失败-NEW出错");
			break;
		case NULLHANDLE:
			sprintf(sz,"查询权限 失败-操作句柄为NULL");
			break;
			case 0:
		case ZERORECORD:
			sprintf(sz,"查询权限 失败-没有该记录");
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_QUERYPERMISSIONINFO,m_szAccount,sz);
		return nRet;
	}

	
	*pnLen = g_stru_ATPManageMsgHeadInfoSize +nRet*nATPDataBasePermissionSize;
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"查询权限 失败-NEW出错");
		AddOperateLog(ID_ATPMANAGE_QUERYPERMISSIONINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"查询权限 失败");
	AddOperateLog(ID_ATPMANAGE_QUERYPERMISSIONINFO,m_szAccount,sz);
	//ASSERT(_CrtCheckMemory());
	stru_ATPManagerInfo _ManagerInfo	= {0};
	
	int nHead	= g_stru_ATPManageMsgHeadInfoSize;
	int nCount = 0;
	pHead->nItem = nRet;
	memcpy(*ppOutData,(char *)pHead,nHead);
	int i = 0;
	nCount = nHead;
	//ASSERT(_CrtCheckMemory());
	for (i=0;i<nRet;i++)
	{
		memcpy(&(*ppOutData)[nCount],(char *)&pATPDataBasePermission[i],nATPDataBasePermissionSize);
		nCount += nATPDataBasePermissionSize;

	}
	//ASSERT(_CrtCheckMemory());
	if (pATPDataBasePermission)
	{
		delete pATPDataBasePermission;
		pATPDataBasePermission = NULL;
	}
	
	//ASSERT(_CrtCheckMemory());
	return nRet;
}



int CHHNetFrameProcessor_ATPManagerServer::AddUserGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPUserGroupInfo *pUserGroupInfo		= (stru_ATPUserGroupInfo *)pData;
	struATPDataBaseUserGroup _DataBaseUserGroup	= {0};


	int nAlgorithmBlock		= 0;									//算法块
	int nAlgorithmGroupBlock	= 0;								//算分组块
	int nServerBlock			= 0;								//服务器块
	int nServerGroupBlock		= 0;								//服务器组块
	int nATPUserGroupInfoSize	= sizeof stru_ATPUserGroupInfo;

	{

		nAlgorithmBlock			= pUserGroupInfo->AlgorithmBlock.nItems*pUserGroupInfo->AlgorithmBlock.nItemSize;	
		nAlgorithmGroupBlock	= pUserGroupInfo->AlgorithmGroupBlock.nItems*pUserGroupInfo->AlgorithmGroupBlock.nItemSize;
		nServerBlock			= pUserGroupInfo->ServerBlock.nItems*pUserGroupInfo->ServerBlock.nItemSize;
		nServerGroupBlock		= pUserGroupInfo->ServerGroupBlock.nItems*pUserGroupInfo->ServerGroupBlock.nItemSize;

		_DataBaseUserGroup.pAlgorithmIDs = NULL;
		if (pUserGroupInfo->AlgorithmBlock.nItems>0)
		{
			_DataBaseUserGroup.pAlgorithmIDs		= new struATPAutoAlgoID[pUserGroupInfo->AlgorithmBlock.nItems];
		}
		_DataBaseUserGroup.pAlgorithmGroupIDs = NULL;
		if (pUserGroupInfo->AlgorithmGroupBlock.nItems>0)
		{
			_DataBaseUserGroup.pAlgorithmGroupIDs	= new struATPAutoID[pUserGroupInfo->AlgorithmGroupBlock.nItems];
		}
		_DataBaseUserGroup.pServerIDs = NULL;
		if (pUserGroupInfo->ServerBlock.nItems>0)
		{
			_DataBaseUserGroup.pServerIDs			= new struATPAutoID[pUserGroupInfo->ServerBlock.nItems];
		}
		_DataBaseUserGroup.pServerGroupIDs = NULL;
		if (pUserGroupInfo->ServerGroupBlock.nItems>0)
		{
			_DataBaseUserGroup.pServerGroupIDs		= new struATPAutoID[pUserGroupInfo->ServerGroupBlock.nItems];
		}
		
			
		_DataBaseUserGroup.nID					= pUserGroupInfo->nID;																//	组ID  自动生成
		_DataBaseUserGroup.nParentID			= pUserGroupInfo->nParentID;														//	父组ID
		strncpy(_DataBaseUserGroup.szName,pUserGroupInfo->szName,sizeof _DataBaseUserGroup.szName);									//	组名
		strncpy(_DataBaseUserGroup.szExplain,pUserGroupInfo->szExplain,sizeof _DataBaseUserGroup.szExplain);						//	说明信息
		_DataBaseUserGroup.nAlgorithmN			= pUserGroupInfo->AlgorithmBlock.nItems;											//	算法个数
		if (_DataBaseUserGroup.pAlgorithmIDs)
		{
			memcpy(_DataBaseUserGroup.pAlgorithmIDs,&pData[nATPUserGroupInfoSize],nAlgorithmBlock);									//	算法ID
		}
		
		_DataBaseUserGroup.nAlgorithmGroupN		= pUserGroupInfo->AlgorithmGroupBlock.nItems;										//	算法组个数
		if (_DataBaseUserGroup.pAlgorithmGroupIDs)
		{
			memcpy(_DataBaseUserGroup.pAlgorithmGroupIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock],nAlgorithmGroupBlock);		//	算法组ID
		}
		
		_DataBaseUserGroup.nServerN = pUserGroupInfo->ServerBlock.nItems;															//	服务器个数
		if (_DataBaseUserGroup.pServerIDs)
		{
			memcpy(_DataBaseUserGroup.pServerIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock + nAlgorithmGroupBlock],nServerBlock);//	服务器ID
		}
		
		_DataBaseUserGroup.nServerGroupN		= pUserGroupInfo->ServerGroupBlock.nItems;											//	服务器组个数
		if (_DataBaseUserGroup.pServerGroupIDs)
		{
			memcpy(_DataBaseUserGroup.pServerGroupIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock],nServerGroupBlock);//	服务器组ID
		}
		
		CTime t = CTime::GetCurrentTime();
		_DataBaseUserGroup.nCreateDate		= t.GetYear()*10000+t.GetMonth()*100+t.GetDay();																	//	创建日期
		_DataBaseUserGroup.nCreateTime		= t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();																	//	创建时间
		_DataBaseUserGroup.nDeleteMark			= pUserGroupInfo->nDeleteMark;														//	删除标志
		strcpy(_DataBaseUserGroup.szManagerID,m_szAccount);
		
	}
	//////////////////////////////////////////////////////////////////////////
	struATPDataBaseUserGroup _ATPDBSUserGroup = {0};
	int nRet = g_pATPFileDBApi->AddUserGroup(&_DataBaseUserGroup,&_ATPDBSUserGroup);

	if (_DataBaseUserGroup.pAlgorithmIDs)
	{
		delete _DataBaseUserGroup.pAlgorithmIDs;_DataBaseUserGroup.pAlgorithmIDs = NULL;
	}
	if (_DataBaseUserGroup.pAlgorithmGroupIDs)
	{
		delete _DataBaseUserGroup.pAlgorithmGroupIDs;_DataBaseUserGroup.pAlgorithmGroupIDs = NULL;
	}
	if (_DataBaseUserGroup.pServerIDs)
	{
		delete _DataBaseUserGroup.pServerIDs;_DataBaseUserGroup.pServerIDs = NULL;
	}
	if (_DataBaseUserGroup.pServerGroupIDs)
	{
		delete _DataBaseUserGroup.pServerGroupIDs;_DataBaseUserGroup.pServerGroupIDs = NULL;
	}
	
	
	if (nRet != 0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"添加用户组(NAME):%s 失败-传入数据为NULL",_DataBaseUserGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"添加用户组(NAME):%s 失败-该服务器组已经存在",_DataBaseUserGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"添加用户组(NAME):%s 失败-NEW出错",_DataBaseUserGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"添加用户组(NAME):%s 失败-操作句柄为NULL",_DataBaseUserGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"添加用户组(NAME):%s 失败-没有该记录",_DataBaseUserGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_ADDUSERGROUP,m_szAccount,sz);
		return nRet;
	}
	//////////////////////////////////////////////////////////////////////////
	stru_ATPUserGroupInfo _UserGroupInfo	= {0};

	{
		_UserGroupInfo.nID								= _ATPDBSUserGroup.nID;							//	组ID  自动生成
		_UserGroupInfo.nParentID						= _ATPDBSUserGroup.nParentID;					//	父组ID
		strncpy(_UserGroupInfo.szName,_ATPDBSUserGroup.szName,sizeof _UserGroupInfo.szName);			//	组名
		strncpy(_UserGroupInfo.szExplain,_ATPDBSUserGroup.szExplain,sizeof _UserGroupInfo.szExplain);	//	说明信息
		_UserGroupInfo.AlgorithmBlock.nItems			= _ATPDBSUserGroup.nAlgorithmN;					//	算法个数 Item ,   itemsize=sizeof(struATPAutoAlgoID) 算法IDs
		_UserGroupInfo.AlgorithmBlock.nItemSize			= sizeof struATPAutoAlgoID;								
		_UserGroupInfo.AlgorithmGroupBlock.nItems		= _ATPDBSUserGroup.nAlgorithmGroupN;			//	算法组个数Item  , itemsize=sizeof(struATPAutoID)  算法组IDs
		_UserGroupInfo.AlgorithmGroupBlock.nItemSize	= sizeof struATPAutoID;	
		_UserGroupInfo.ServerBlock.nItems				= _ATPDBSUserGroup.nServerN;					//	服务器个数Item,	itemsize=sizeof(struATPAutoID) 服务器IDs
		_UserGroupInfo.ServerBlock.nItemSize			= sizeof struATPAutoID;
		_UserGroupInfo.ServerGroupBlock.nItems			= _ATPDBSUserGroup.nServerGroupN;				//	服务器组个数Item  ,itemsize=sizeof(struATPAutoID)  服务器组IDs
		_UserGroupInfo.ServerGroupBlock.nItemSize		= sizeof struATPAutoID;
		_UserGroupInfo.nCreateDate						= _ATPDBSUserGroup.nCreateDate;					//	创建日期
		_UserGroupInfo.nCreateTime						= _ATPDBSUserGroup.nCreateTime;					//	创建时间
		_UserGroupInfo.nDeleteMark						= _ATPDBSUserGroup.nDeleteMark;					//	删除标志
	}

	//////////////////////////////////////////////////////////////////////////
	nAlgorithmBlock			= _UserGroupInfo.AlgorithmBlock.nItems*sizeof struATPAutoAlgoID;			//算法块
	nAlgorithmGroupBlock	= _UserGroupInfo.AlgorithmGroupBlock.nItems*sizeof struATPAutoID;			//算分组块
	nServerBlock			= _UserGroupInfo.ServerBlock.nItems*sizeof struATPAutoID;
	nServerGroupBlock		= _UserGroupInfo.ServerGroupBlock.nItems*sizeof struATPAutoID;
	*pnLen					= g_stru_ATPManageMsgHeadInfoSize + nATPUserGroupInfoSize+ nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock + nServerGroupBlock;
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"添加用户组(NAME):%s 成功-NEW出错",_DataBaseUserGroup.szName);
		AddOperateLog(ID_ATPMANAGE_ADDUSERGROUP,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"添加用户组(NAME):%s 成功",_DataBaseUserGroup.szName);
	AddOperateLog(ID_ATPMANAGE_ADDUSERGROUP,m_szAccount,sz);
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_UserGroupInfo,nATPUserGroupInfoSize);
	if (_ATPDBSUserGroup.pAlgorithmIDs)
	{
		memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize+nATPUserGroupInfoSize],(char *)_ATPDBSUserGroup.pAlgorithmIDs,nAlgorithmBlock);
	}
	
	if (_ATPDBSUserGroup.pAlgorithmGroupIDs)
	{
		memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize+nATPUserGroupInfoSize+nAlgorithmBlock],(char *)_ATPDBSUserGroup.pAlgorithmGroupIDs,nAlgorithmGroupBlock);
	}
	
	if (_ATPDBSUserGroup.pServerIDs)
	{
		memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize+nATPUserGroupInfoSize+nAlgorithmBlock+nAlgorithmGroupBlock],(char *)_ATPDBSUserGroup.pServerIDs,nServerBlock);
	}
	if (_ATPDBSUserGroup.pServerGroupIDs)
	{
		memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize+nATPUserGroupInfoSize+nAlgorithmBlock+nAlgorithmGroupBlock+nServerBlock],(char *)_ATPDBSUserGroup.pServerGroupIDs,nServerGroupBlock);
	}
	
	

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::ModifyUserGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPUserGroupInfo *pUserGroupInfo		= (stru_ATPUserGroupInfo *)pData;
	struATPDataBaseUserGroup _DataBaseUserGroup	= {0};


	int nAlgorithmBlock			= 0;								//算法块
	int nAlgorithmGroupBlock	= 0;								//算分组块
	int nServerBlock			= 0;								//服务器块
	int nServerGroupBlock		= 0;								//服务器组块
	int nATPUserGroupInfoSize	= sizeof stru_ATPUserGroupInfo;

	{

		nAlgorithmBlock			= pUserGroupInfo->AlgorithmBlock.nItems*pUserGroupInfo->AlgorithmBlock.nItemSize;	
		nAlgorithmGroupBlock	= pUserGroupInfo->AlgorithmGroupBlock.nItems*pUserGroupInfo->AlgorithmGroupBlock.nItemSize;
		nServerBlock			= pUserGroupInfo->ServerBlock.nItems*pUserGroupInfo->ServerBlock.nItemSize;
		nServerGroupBlock		= pUserGroupInfo->ServerGroupBlock.nItems*pUserGroupInfo->ServerGroupBlock.nItemSize;
		_DataBaseUserGroup.pAlgorithmIDs = NULL;
		if (pUserGroupInfo->AlgorithmBlock.nItems>0)
		{
			_DataBaseUserGroup.pAlgorithmIDs		= new struATPAutoAlgoID[pUserGroupInfo->AlgorithmBlock.nItems];
		}
		_DataBaseUserGroup.pAlgorithmGroupIDs = NULL;
		if (pUserGroupInfo->AlgorithmGroupBlock.nItems>0)
		{
			_DataBaseUserGroup.pAlgorithmGroupIDs	= new struATPAutoID[pUserGroupInfo->AlgorithmGroupBlock.nItems];
		}
		_DataBaseUserGroup.pServerIDs = NULL;
		if (pUserGroupInfo->ServerBlock.nItems>0)
		{
			_DataBaseUserGroup.pServerIDs			= new struATPAutoID[pUserGroupInfo->ServerBlock.nItems];
		}
		_DataBaseUserGroup.pServerGroupIDs = NULL;
		if (pUserGroupInfo->ServerGroupBlock.nItems>0)
		{
			_DataBaseUserGroup.pServerGroupIDs		= new struATPAutoID[pUserGroupInfo->ServerGroupBlock.nItems];
		}
		
		
		_DataBaseUserGroup.nID					= pUserGroupInfo->nID;																//	组ID  自动生成
		_DataBaseUserGroup.nParentID			= pUserGroupInfo->nParentID;														//	父组ID
		strncpy(_DataBaseUserGroup.szName,pUserGroupInfo->szName,sizeof _DataBaseUserGroup.szName);									//	组名
		strncpy(_DataBaseUserGroup.szExplain,pUserGroupInfo->szExplain,sizeof _DataBaseUserGroup.szExplain);						//	说明信息
		_DataBaseUserGroup.nAlgorithmN			= pUserGroupInfo->AlgorithmBlock.nItems;											//	算法个数
		if (_DataBaseUserGroup.pAlgorithmIDs)
		{
			memcpy(_DataBaseUserGroup.pAlgorithmIDs,&pData[nATPUserGroupInfoSize],nAlgorithmBlock);									//	算法ID
		}
		
		_DataBaseUserGroup.nAlgorithmGroupN		= pUserGroupInfo->AlgorithmGroupBlock.nItems;										//	算法组个数
		if (_DataBaseUserGroup.pAlgorithmGroupIDs)
		{
			memcpy(_DataBaseUserGroup.pAlgorithmGroupIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock],nAlgorithmGroupBlock);		//	算法组ID
		}
		
		_DataBaseUserGroup.nServerN = pUserGroupInfo->ServerBlock.nItems;															//	服务器个数
		if (_DataBaseUserGroup.pServerIDs)
		{
			memcpy(_DataBaseUserGroup.pServerIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock + nAlgorithmGroupBlock],nServerBlock);	//	服务器ID
		}
		
		_DataBaseUserGroup.nServerGroupN		= pUserGroupInfo->ServerGroupBlock.nItems;											//	服务器组个数
		if (_DataBaseUserGroup.pServerGroupIDs)
		{
			memcpy(_DataBaseUserGroup.pServerGroupIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock],nServerGroupBlock);//	服务器组ID
		}
		
		_DataBaseUserGroup.nCreateDate			= pUserGroupInfo->nCreateDate;														//	创建日期
		_DataBaseUserGroup.nCreateTime			= pUserGroupInfo->nCreateTime;														//	创建时间
		_DataBaseUserGroup.nDeleteMark			= pUserGroupInfo->nDeleteMark;														//	删除标志
		strcpy(_DataBaseUserGroup.szManagerID,m_szAccount);
	}
	//////////////////////////////////////////////////////////////////////////
	
	int nRet = g_pATPFileDBApi->ModifyUserGroup(&_DataBaseUserGroup);

	if (_DataBaseUserGroup.pAlgorithmIDs)
	{
		delete _DataBaseUserGroup.pAlgorithmIDs;_DataBaseUserGroup.pAlgorithmIDs = NULL;
	}
	if (_DataBaseUserGroup.pAlgorithmGroupIDs)
	{
		delete _DataBaseUserGroup.pAlgorithmGroupIDs;_DataBaseUserGroup.pAlgorithmGroupIDs = NULL;
	}
	if (_DataBaseUserGroup.pServerIDs)
	{
		delete _DataBaseUserGroup.pServerIDs;	_DataBaseUserGroup.pServerIDs = NULL;
	}
	if (_DataBaseUserGroup.pServerGroupIDs)
	{
		delete _DataBaseUserGroup.pServerGroupIDs;_DataBaseUserGroup.pServerGroupIDs = NULL;
	}
	

	//////////////////////////////////////////////////////////////////////////
	
	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;
	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"修改成功");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"修改用户组(NAME):%s 失败-传入数据为NULL",_DataBaseUserGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"修改用户组(NAME):%s 失败-该服务器组已经存在",_DataBaseUserGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"修改用户组(NAME):%s 失败-NEW出错",_DataBaseUserGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"修改用户组(NAME):%s 失败-操作句柄为NULL",_DataBaseUserGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"修改用户组(NAME):%s 失败-没有该记录",_DataBaseUserGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_MODIFYUSERGROUP,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"修改失败");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"修改用户组(NAME):%s 成功-NEW出错",_DataBaseUserGroup.szName);
		AddOperateLog(ID_ATPMANAGE_MODIFYUSERGROUP,m_szAccount,sz);
		return -1;
	}
	char sz[128]={0};
	sprintf(sz,"修改用户组(NAME):%s 成功",_DataBaseUserGroup.szName);
	AddOperateLog(ID_ATPMANAGE_MODIFYUSERGROUP,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);
	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::DelUserGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPUserGroupInfo *pUserGroupInfo		= (stru_ATPUserGroupInfo *)pData;
	struATPDataBaseUserGroup _DataBaseUserGroup	= {0};


	int nAlgorithmBlock			= 0;								//算法块
	int nAlgorithmGroupBlock	= 0;								//算分组块
	int nServerBlock			= 0;								//服务器块
	int nServerGroupBlock		= 0;								//服务器组块
	int nATPUserGroupInfoSize	= sizeof stru_ATPUserGroupInfo;

	{

		nAlgorithmBlock			= pUserGroupInfo->AlgorithmBlock.nItems*pUserGroupInfo->AlgorithmBlock.nItemSize;	
		nAlgorithmGroupBlock	= pUserGroupInfo->AlgorithmGroupBlock.nItems*pUserGroupInfo->AlgorithmGroupBlock.nItemSize;
		nServerBlock			= pUserGroupInfo->ServerBlock.nItems*pUserGroupInfo->ServerBlock.nItemSize;
		nServerGroupBlock		= pUserGroupInfo->ServerGroupBlock.nItems*pUserGroupInfo->ServerGroupBlock.nItemSize;
		_DataBaseUserGroup.pAlgorithmIDs = NULL;
		if (pUserGroupInfo->AlgorithmBlock.nItems>0)
		{
			_DataBaseUserGroup.pAlgorithmIDs		= new struATPAutoAlgoID[pUserGroupInfo->AlgorithmBlock.nItems];
		}
		_DataBaseUserGroup.pAlgorithmGroupIDs = NULL;
		if (pUserGroupInfo->AlgorithmGroupBlock.nItems>0)
		{
			_DataBaseUserGroup.pAlgorithmGroupIDs	= new struATPAutoID[pUserGroupInfo->AlgorithmGroupBlock.nItems];
		}
		_DataBaseUserGroup.pServerIDs = NULL;
		if (pUserGroupInfo->ServerBlock.nItems>0)
		{
			_DataBaseUserGroup.pServerIDs			= new struATPAutoID[pUserGroupInfo->ServerBlock.nItems];
		}
		_DataBaseUserGroup.pServerGroupIDs = NULL;
		if (pUserGroupInfo->ServerGroupBlock.nItems>0)
		{
			_DataBaseUserGroup.pServerGroupIDs		= new struATPAutoID[pUserGroupInfo->ServerGroupBlock.nItems];
		}
		

		_DataBaseUserGroup.nID					= pUserGroupInfo->nID;																//	组ID  自动生成
		_DataBaseUserGroup.nParentID			= pUserGroupInfo->nParentID;														//	父组ID
		strncpy(_DataBaseUserGroup.szName,pUserGroupInfo->szName,sizeof _DataBaseUserGroup.szName);									//	组名
		strncpy(_DataBaseUserGroup.szExplain,pUserGroupInfo->szExplain,sizeof _DataBaseUserGroup.szExplain);						//	说明信息
		_DataBaseUserGroup.nAlgorithmN			= pUserGroupInfo->AlgorithmBlock.nItems;											//	算法个数
		if (_DataBaseUserGroup.pAlgorithmIDs)
		{
			memcpy(_DataBaseUserGroup.pAlgorithmIDs,&pData[nATPUserGroupInfoSize],nAlgorithmBlock);										//	算法ID
		}
		
		_DataBaseUserGroup.nAlgorithmGroupN		= pUserGroupInfo->AlgorithmGroupBlock.nItems;										//	算法组个数
		if (_DataBaseUserGroup.pAlgorithmGroupIDs)
		{
			memcpy(_DataBaseUserGroup.pAlgorithmGroupIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock],nAlgorithmGroupBlock);			//	算法组ID
		}
		
		_DataBaseUserGroup.nServerN = pUserGroupInfo->ServerBlock.nItems;															//	服务器个数
		if (_DataBaseUserGroup.pServerIDs)
		{
			memcpy(_DataBaseUserGroup.pServerIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock + nAlgorithmGroupBlock],nServerBlock);	//	服务器ID
		}
		
		_DataBaseUserGroup.nServerGroupN		= pUserGroupInfo->ServerGroupBlock.nItems;											//	服务器组个数
		if (_DataBaseUserGroup.pServerGroupIDs)
		{
			memcpy(_DataBaseUserGroup.pServerGroupIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock],nServerGroupBlock);//	服务器组ID
		}
		
		_DataBaseUserGroup.nCreateDate			= pUserGroupInfo->nCreateDate;														//	创建日期
		_DataBaseUserGroup.nCreateTime			= pUserGroupInfo->nCreateTime;														//	创建时间
		_DataBaseUserGroup.nDeleteMark			= pUserGroupInfo->nDeleteMark;														//	删除标志

	}
	//////////////////////////////////////////////////////////////////////////

	int nRet = g_pATPFileDBApi->DelUserGroup(&_DataBaseUserGroup);

	if (_DataBaseUserGroup.pAlgorithmIDs)
	{
		delete _DataBaseUserGroup.pAlgorithmIDs;_DataBaseUserGroup.pAlgorithmIDs = NULL;
	}
	if (_DataBaseUserGroup.pAlgorithmGroupIDs)
	{
		delete _DataBaseUserGroup.pAlgorithmGroupIDs;_DataBaseUserGroup.pAlgorithmGroupIDs = NULL;
	}
	if (_DataBaseUserGroup.pServerIDs)
	{
		delete _DataBaseUserGroup.pServerIDs;	_DataBaseUserGroup.pServerIDs = NULL;
	}
	if (_DataBaseUserGroup.pServerGroupIDs)
	{
		delete _DataBaseUserGroup.pServerGroupIDs;_DataBaseUserGroup.pServerGroupIDs = NULL;
	}
	

	
	//////////////////////////////////////////////////////////////////////////

	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;
	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"删除成功");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"删除用户组(NAME):%s 失败-传入数据为NULL",_DataBaseUserGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"删除用户组(NAME):%s 失败-该服务器组已经存在",_DataBaseUserGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"删除用户组(NAME):%s 失败-NEW出错",_DataBaseUserGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"删除用户组(NAME):%s 失败-操作句柄为NULL",_DataBaseUserGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"删除用户组(NAME):%s 失败-没有该记录",_DataBaseUserGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_DELETEUSERGROUP,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"删除失败");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"删除用户组(NAME):%s 成功-NEW出错",_DataBaseUserGroup.szName);
		AddOperateLog(ID_ATPMANAGE_DELETEUSERGROUP,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"删除用户组(NAME):%s 成功",_DataBaseUserGroup.szName);
	AddOperateLog(ID_ATPMANAGE_DELETEUSERGROUP,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);
	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::QueryUserGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseUserGroup *pATPDataBaseManager = NULL;
	int nATPUserGroupInfoSize	= sizeof stru_ATPUserGroupInfo;
	//nRet 查询结果条数
	int nRet = g_pATPFileDBApi->QueryUserGroup(m_szAccount,&pATPDataBaseManager);
	//ASSERT(_CrtCheckMemory());
		
	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"查询用户组 失败-传入数据为NULL");
			break;
		case EXISTDATA:
			sprintf(sz,"查询用户组 失败-该用户组已经存在");
			break;
		case NEWERROR:
			sprintf(sz,"查询用户组 失败-NEW出错");
			break;
		case NULLHANDLE:
			sprintf(sz,"查询用户组 失败-操作句柄为NULL");
			break;
			case 0:
		case ZERORECORD:
			sprintf(sz,"查询用户组 成功-没有该记录");
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_QUERYUSERGROUPINFO,m_szAccount,sz);
		return nRet;
	}
	*pnLen = g_stru_ATPManageMsgHeadInfoSize;
	int i = 0;
	for (;i<nRet;i++)
	{
		//ASSERT(_CrtCheckMemory());
		(*pnLen) += nATPUserGroupInfoSize + (((pATPDataBaseManager[i].nAlgorithmGroupN+pATPDataBaseManager[i].nServerN+pATPDataBaseManager[i].nServerGroupN)*sizeof(struATPAutoID))+pATPDataBaseManager[i].nAlgorithmN*sizeof struATPAutoAlgoID);
	}
	//ASSERT(_CrtCheckMemory());
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"查询用户组 成功-NEW出错");
		AddOperateLog(ID_ATPMANAGE_QUERYUSERGROUPINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"查询用户组 成功");
	AddOperateLog(ID_ATPMANAGE_QUERYUSERGROUPINFO,m_szAccount,sz);
	stru_ATPUserGroupInfo _UserGroupInfo	= {0};
	int nAlgoBlock = 0,nAlgoGroupBlock = 0,nServerBlock = 0,nServerGroupBlock = 0;
	int nHead	= g_stru_ATPManageMsgHeadInfoSize;
	int nBody	= sizeof stru_ATPUserGroupInfo;
	int nEX		= 0;
	int nCount = 0;

	pHead->nItem = nRet;
	memcpy(*ppOutData,(char *)pHead,nHead);
	nCount = nHead;
	for (i=0;i<nRet;i++)
	{
		//ASSERT(_CrtCheckMemory());
		_UserGroupInfo.nID								= pATPDataBaseManager[i].nID;						//	组ID  自动生成
		_UserGroupInfo.nParentID						= pATPDataBaseManager[i].nParentID;					//	父组ID
		strncpy(_UserGroupInfo.szName,pATPDataBaseManager[i].szName,sizeof _UserGroupInfo.szName);			//	组名
		strncpy(_UserGroupInfo.szExplain,pATPDataBaseManager[i].szExplain,sizeof _UserGroupInfo.szExplain);	//	说明信息
		_UserGroupInfo.AlgorithmBlock.nItems			= pATPDataBaseManager[i].nAlgorithmN;				//	算法个数 Item ,   itemsize=sizeof(struATPAutoAlgoID) 算法IDs
		_UserGroupInfo.AlgorithmBlock.nItemSize			= sizeof struATPAutoAlgoID;								
		_UserGroupInfo.AlgorithmGroupBlock.nItems		= pATPDataBaseManager[i].nAlgorithmGroupN;			//	算法组个数Item  , itemsize=sizeof(struATPAutoID)  算法组IDs
		_UserGroupInfo.AlgorithmGroupBlock.nItemSize	= sizeof struATPAutoID;	
		_UserGroupInfo.ServerBlock.nItems				= pATPDataBaseManager[i].nServerN;					//	服务器个数Item,	itemsize=sizeof(struATPAutoID) 服务器IDs
		_UserGroupInfo.ServerBlock.nItemSize			= sizeof struATPAutoID;
		_UserGroupInfo.ServerGroupBlock.nItems			= pATPDataBaseManager[i].nServerGroupN;				//	服务器组个数Item  ,itemsize=sizeof(struATPAutoID)  服务器组IDs
		_UserGroupInfo.ServerGroupBlock.nItemSize		= sizeof struATPAutoID;
		_UserGroupInfo.nCreateDate						= pATPDataBaseManager[i].nCreateDate;				//	创建日期
		_UserGroupInfo.nCreateTime						= pATPDataBaseManager[i].nCreateTime;				//	创建时间
		_UserGroupInfo.nDeleteMark						= pATPDataBaseManager[i].nDeleteMark;				//	删除标志
		//ASSERT(_CrtCheckMemory());
		nAlgoBlock = pATPDataBaseManager[i].nAlgorithmN*sizeof struATPAutoAlgoID;
		nAlgoGroupBlock = pATPDataBaseManager[i].nAlgorithmGroupN*sizeof struATPAutoID;
		nServerBlock = pATPDataBaseManager[i].nServerN*sizeof struATPAutoID;
		nServerGroupBlock = pATPDataBaseManager[i].nServerGroupN*sizeof struATPAutoID;
		memcpy(&(*ppOutData)[nCount],(char *)&_UserGroupInfo,nBody);
		nCount += nBody;
		if (pATPDataBaseManager[i].pAlgorithmIDs&&nAlgoBlock>0)
		{
			memcpy(&(*ppOutData)[nCount],(char*)pATPDataBaseManager[i].pAlgorithmIDs,nAlgoBlock);
			nCount += nAlgoBlock;
		}
		
		if (pATPDataBaseManager[i].pAlgorithmGroupIDs&&nAlgoGroupBlock>0)
		{
			memcpy(&(*ppOutData)[nCount],(char*)pATPDataBaseManager[i].pAlgorithmGroupIDs,nAlgoGroupBlock);
			nCount += nAlgoGroupBlock;
		}
		
		if (pATPDataBaseManager[i].pServerIDs&&nServerBlock>0)
		{
			memcpy(&(*ppOutData)[nCount],(char*)pATPDataBaseManager[i].pServerIDs,nServerBlock);
			nCount += nServerBlock;
		}
		
		if (pATPDataBaseManager[i].pServerGroupIDs&&nServerGroupBlock>0)
		{
			memcpy(&(*ppOutData)[nCount],(char*)pATPDataBaseManager[i].pServerGroupIDs,nServerGroupBlock);
			nCount += nServerGroupBlock;
		}
		
		//ASSERT(_CrtCheckMemory());
	}

	delete pATPDataBaseManager;
	pATPDataBaseManager = NULL;
	return nRet;
}



int CHHNetFrameProcessor_ATPManagerServer::AddUser(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPUserInfo *pUserInfo		= (stru_ATPUserInfo *)pData;
	struATPDataBaseUser _DataBaseUser	= {0};

	int nFundBlock				= 0;
	int nAlgorithmBlock			= 0;									//算法块
	int nAlgorithmGroupBlock	= 0;								//算分组块
	int nServerBlock			= 0;								//服务器块
	int nServerGroupBlock		= 0;								//服务器组块
	int nATPUserInfoSize	= sizeof stru_ATPUserInfo;
	


	{
		nFundBlock				= pUserInfo->FundBlock.nItems*pUserInfo->FundBlock.nItemSize;
		nAlgorithmBlock			= pUserInfo->AlgorithmBlock.nItems*pUserInfo->AlgorithmBlock.nItemSize;	
		nAlgorithmGroupBlock	= pUserInfo->AlgorithmGroupBlock.nItems*pUserInfo->AlgorithmGroupBlock.nItemSize;
		nServerBlock			= pUserInfo->ServerBlock.nItems*pUserInfo->ServerBlock.nItemSize;
		nServerGroupBlock		= pUserInfo->ServerGroupBlock.nItems*pUserInfo->ServerGroupBlock.nItemSize;

		_DataBaseUser.pATPFund = NULL;
		if (pUserInfo->FundBlock.nItems>0)
		{
			_DataBaseUser.pATPFund				= new struATPDataBaseFund[pUserInfo->FundBlock.nItems];
		}
		_DataBaseUser.pAlgorithmIDs = NULL;
		if (pUserInfo->AlgorithmBlock.nItems>0)
		{
			_DataBaseUser.pAlgorithmIDs			= new struATPAutoAlgoID[pUserInfo->AlgorithmBlock.nItems];
		}
		_DataBaseUser.pAlgorithmGroupIDs = NULL;
		if (pUserInfo->AlgorithmGroupBlock.nItems>0)
		{
			_DataBaseUser.pAlgorithmGroupIDs	= new struATPAutoID[pUserInfo->AlgorithmGroupBlock.nItems];
		}
		_DataBaseUser.pServerIDs = NULL;
		if (pUserInfo->ServerBlock.nItems>0)
		{
			_DataBaseUser.pServerIDs			= new struATPAutoID[pUserInfo->ServerBlock.nItems];
		}
		_DataBaseUser.pServerGroupIDs = NULL;
		if (pUserInfo->ServerGroupBlock.nItems>0)
		{
			_DataBaseUser.pServerGroupIDs		= new struATPAutoID[pUserInfo->ServerGroupBlock.nItems];
		}
		
				
		_DataBaseUser.nSerialNumber				= pUserInfo->nSerialNumber;														//	自动增长
		strncpy(_DataBaseUser.szUserID,pUserInfo->szUserID,sizeof _DataBaseUser.szUserID);										//	用户ID
		strncpy(_DataBaseUser.szPwd,pUserInfo->szPwd,sizeof _DataBaseUser.szPwd);												//	用户密码
		strncpy(_DataBaseUser.szUserName,pUserInfo->szUserName,sizeof _DataBaseUser.szUserName);								//	用户名
		strncpy(_DataBaseUser.szCardID,pUserInfo->szCardID,sizeof _DataBaseUser.szCardID);										//	身份证号码
		memcpy((char *)_DataBaseUser.nGroupIDs,(char *)pUserInfo->nGroupIDs,sizeof _DataBaseUser.nGroupIDs);					//	用户组ID
		memcpy((char *)_DataBaseUser.nPermissionIDs,(char *)pUserInfo->nPermissionIDs,sizeof _DataBaseUser.nPermissionIDs);		//	权限ID
		_DataBaseUser.nAuthorizeBeginDate		= pUserInfo->nAuthorizeBeginDate;												//	授权使用开始日期
		_DataBaseUser.nAuthorizeEndDate			= pUserInfo->nAuthorizeEndDate;													//	授权使用截止日期
		_DataBaseUser.nStatus					= pUserInfo->nStatus;															//	用户使用状态
		memcpy(_DataBaseUser.szMobiles,pUserInfo->szMobiles,sizeof _DataBaseUser.szMobiles);									//	手机号码,含区号
		memcpy(_DataBaseUser.szTelephones,pUserInfo->szTelephones,sizeof _DataBaseUser.szTelephones);							//	电话号码
		memcpy((char *)_DataBaseUser.nQQNumbers,(char *)pUserInfo->nQQNumbers,sizeof _DataBaseUser.nQQNumbers);					//	QQ号码
		memcpy(_DataBaseUser.szEmails,pUserInfo->szEmails,sizeof _DataBaseUser.szEmails);										//	Email号码
		strncpy(_DataBaseUser.szUserExplain,pUserInfo->szUserExplain,sizeof _DataBaseUser.szUserExplain);						//	用户说明,含禁用理由
		strncpy(_DataBaseUser.szIPs,pUserInfo->szIPs,sizeof _DataBaseUser.szIPs);												//	限制IP
		strncpy(_DataBaseUser.szMacMark,pUserInfo->szMacMark,sizeof _DataBaseUser.szMacMark);									//	限制MAC地址
		strncpy(_DataBaseUser.szDiskNum,pUserInfo->szDiskNum,sizeof _DataBaseUser.szDiskNum);									//	限制硬盘序列号
		memcpy(_DataBaseUser.nLimitBeginTime,pUserInfo->nLimitBeginTime,sizeof _DataBaseUser.nLimitBeginTime);					//	限制开始时间
		memcpy(_DataBaseUser.nLimitEndTime,pUserInfo->nLimitEndTime,sizeof _DataBaseUser.nLimitEndTime);						//	限制结束时间
		_DataBaseUser.chLimitWeek				= pUserInfo->chLimitWeek;														//	限制星期,0x80是限制
		_DataBaseUser.nCanAssociateFundsAccount	= pUserInfo->FundBlock.nItems;													//	当前资金帐号结构体数,最多10个
		if (_DataBaseUser.pATPFund)
		{
			memcpy(_DataBaseUser.pATPFund,&pData[nATPUserInfoSize],nFundBlock);													//	资金帐号结构体
		}
		
		_DataBaseUser.nCanRunAlgorithm			= pUserInfo->nCanRunAlgorithm;													//	允许同时运行算法个数
		_DataBaseUser.nAlgorithmN				= pUserInfo->AlgorithmBlock.nItems;												//	算法个数
		if (_DataBaseUser.pAlgorithmIDs)
		{
			memcpy(_DataBaseUser.pAlgorithmIDs,&pData[nATPUserInfoSize + nFundBlock],nAlgorithmBlock);							//	算法IDs
		}
		
		_DataBaseUser.nAlgorithmGroupN			= pUserInfo->AlgorithmGroupBlock.nItems;										//	算法组个数
		if (_DataBaseUser.pAlgorithmGroupIDs)
		{
			memcpy(_DataBaseUser.pAlgorithmGroupIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock],nAlgorithmGroupBlock);	//	算法组IDs
		}
		
		_DataBaseUser.nServerN = pUserInfo->ServerBlock.nItems;
		if (_DataBaseUser.pServerIDs)
		{
			memcpy(_DataBaseUser.pServerIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock + nAlgorithmGroupBlock],nServerBlock);//	专属服务器
		}
		
		_DataBaseUser.nServerGroupN				= pUserInfo->ServerGroupBlock.nItems;											//	服务器组个数
		if (_DataBaseUser.pServerGroupIDs)
		{
			memcpy(_DataBaseUser.pServerGroupIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock],nServerGroupBlock);//	服务器组IDs
		}
		
 		CTime t = CTime::GetCurrentTime();
		_DataBaseUser.nCreateDate					= t.GetYear()*10000+t.GetMonth()*100+t.GetDay();																//	创建日期
 		_DataBaseUser.nCreateTime					= t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();															//	创建时间
 		_DataBaseUser.nLastDate						= 19800101;																	//	最后登陆日期
		_DataBaseUser.nLastTime						= 235959;																	//	最后登陆时间
		_DataBaseUser.nDeleteMark					= pUserInfo->nDeleteMark;													//	删除标志
		strcpy(_DataBaseUser.szManagerID,m_szAccount);
	}
	//////////////////////////////////////////////////////////////////////////
	struATPDataBaseUser _ATPDBSUser = {0};
	int nRet = g_pATPFileDBApi->AddUser(&_DataBaseUser,&_ATPDBSUser);

	if (_DataBaseUser.pATPFund)
	{
		delete _DataBaseUser.pATPFund;_DataBaseUser.pATPFund = NULL;
	}
	if (_DataBaseUser.pAlgorithmIDs)
	{
		delete _DataBaseUser.pAlgorithmIDs;_DataBaseUser.pAlgorithmIDs = NULL;
	}
	if (_DataBaseUser.pAlgorithmGroupIDs)
	{
		delete _DataBaseUser.pAlgorithmGroupIDs;_DataBaseUser.pAlgorithmGroupIDs = NULL;
	}
	if (_DataBaseUser.pServerIDs)
	{
		delete _DataBaseUser.pServerIDs;_DataBaseUser.pServerIDs = NULL;
	}
	if (_DataBaseUser.pServerGroupIDs)
	{
		delete _DataBaseUser.pServerGroupIDs;_DataBaseUser.pServerGroupIDs = NULL;
	}

	if (nRet != 0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"添加用户(NAME):%s 失败-传入数据为NULL",_DataBaseUser.szUserID);
			break;
		case EXISTDATA:
			sprintf(sz,"添加用户(NAME):%s 失败-该服务器组已经存在",_DataBaseUser.szUserID);
			break;
		case NEWERROR:
			sprintf(sz,"添加用户(NAME):%s 失败-NEW出错",_DataBaseUser.szUserID);
			break;
		case NULLHANDLE:
			sprintf(sz,"添加用户(NAME):%s 失败-操作句柄为NULL",_DataBaseUser.szUserID);
			break;
		case ZERORECORD:
			sprintf(sz,"添加用户(NAME):%s 失败-没有该记录",_DataBaseUser.szUserID);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_ADDUSER,m_szAccount,sz);
		return nRet;
	}
	//////////////////////////////////////////////////////////////////////////
	stru_ATPUserInfo _UserInfo	= {0};

	{
		_UserInfo.nSerialNumber					= _ATPDBSUser.nSerialNumber;											//	自动增长
		strncpy(_UserInfo.szUserID,_ATPDBSUser.szUserID,sizeof _UserInfo.szUserID);										//	用户ID
		strncpy(_UserInfo.szPwd,_ATPDBSUser.szPwd,sizeof _UserInfo.szPwd);												//	用户密码
		strncpy(_UserInfo.szUserName,_ATPDBSUser.szUserName,sizeof _UserInfo.szUserName);								//	用户名
		strncpy(_UserInfo.szCardID,_ATPDBSUser.szCardID,sizeof _UserInfo.szCardID);										//	身份证号码
		memcpy((char *)_UserInfo.nGroupIDs,(char *)_ATPDBSUser.nGroupIDs,sizeof _UserInfo.nGroupIDs);					//	用户组ID
		memcpy((char *)_UserInfo.nPermissionIDs,(char *)_ATPDBSUser.nPermissionIDs,sizeof _UserInfo.nPermissionIDs);	//	权限ID
		_UserInfo.nAuthorizeBeginDate			= _ATPDBSUser.nAuthorizeBeginDate;										//	授权使用开始日期
		_UserInfo.nAuthorizeEndDate				= _ATPDBSUser.nAuthorizeEndDate;										//	授权使用截止日期
		_UserInfo.nStatus						= _ATPDBSUser.nStatus;													//	用户使用状态
		memcpy((char *)_UserInfo.szMobiles,(char *)_ATPDBSUser.szMobiles,sizeof _UserInfo.szMobiles);					//	手机号码,含区号
		memcpy((char *)_UserInfo.szTelephones,(char *)_ATPDBSUser.szTelephones,sizeof _UserInfo.szTelephones);			//	电话号码
		memcpy((char *)_UserInfo.nQQNumbers,(char *)_ATPDBSUser.nQQNumbers,sizeof _UserInfo.nQQNumbers);				//	QQ号码
		memcpy(_UserInfo.szEmails,_ATPDBSUser.szEmails,sizeof _UserInfo.szEmails);										//	Email号码
		strncpy(_UserInfo.szUserExplain,_ATPDBSUser.szUserExplain,sizeof _UserInfo.szUserExplain);						//	用户说明,含禁用理由
		strncpy(_UserInfo.szIPs,_ATPDBSUser.szIPs,sizeof _UserInfo.szIPs);												//	限制IP
		strncpy(_UserInfo.szMacMark,_ATPDBSUser.szMacMark,sizeof _UserInfo.szMacMark);									//	限制MAC地址
		strncpy(_UserInfo.szDiskNum,_ATPDBSUser.szDiskNum,sizeof _UserInfo.szDiskNum);									//	限制硬盘序列号
		memcpy((char *)_UserInfo.nLimitBeginTime,(char *)_ATPDBSUser.nLimitBeginTime,sizeof _UserInfo.nLimitBeginTime);	//	限制开始时间
		memcpy((char *)_UserInfo.nLimitEndTime,(char *)_ATPDBSUser.nLimitEndTime,sizeof _UserInfo.nLimitEndTime);		//	限制结束时间
		_UserInfo.chLimitWeek					= _ATPDBSUser.chLimitWeek;												//	限制星期,0x80是限制
		_UserInfo.FundBlock.nItems				= _ATPDBSUser.nCanAssociateFundsAccount;								//	当前资金帐号结构体数Items,最多10个         itemsize = sizeof(struATPID)
		_UserInfo.FundBlock.nItemSize			= sizeof struATPDataBaseFund;	
		_UserInfo.nCanRunAlgorithm				= _ATPDBSUser.nCanRunAlgorithm;											//	允许同时运行算法个数
		_UserInfo.AlgorithmBlock.nItems			= _ATPDBSUser.nAlgorithmN;												//	算法个数items  ,  itemsize = sizeof(struATPAutoID)
		_UserInfo.AlgorithmBlock.nItemSize		= sizeof struATPAutoAlgoID;
		_UserInfo.AlgorithmGroupBlock.nItems	= _ATPDBSUser.nAlgorithmGroupN;											//	算法组个数 items, itemsize = sizeof(struATPAutoID)
		_UserInfo.AlgorithmGroupBlock.nItemSize = sizeof struATPAutoID;
		_UserInfo.ServerBlock.nItems			= _ATPDBSUser.nServerN;
		_UserInfo.ServerBlock.nItemSize			= sizeof struATPAutoID;
		_UserInfo.ServerGroupBlock.nItems		= _ATPDBSUser.nServerGroupN;
		_UserInfo.ServerGroupBlock.nItemSize	= sizeof struATPAutoID;
		_UserInfo.nCreateDate					= _ATPDBSUser.nCreateDate;												//	创建日期
		_UserInfo.nCreateTime					= _ATPDBSUser.nCreateTime;												//	创建时间
		_UserInfo.nLastDate						= _ATPDBSUser.nLastDate;												//	最后登陆日期
		_UserInfo.nLastTime						= _ATPDBSUser.nLastTime;												//	最后登陆时间
		_UserInfo.nDeleteMark					= _ATPDBSUser.nDeleteMark;												//	删除标志
	}

	//////////////////////////////////////////////////////////////////////////
	nFundBlock				= _UserInfo.FundBlock.nItems*sizeof struATPDataBaseFund;
	nAlgorithmBlock			= _UserInfo.AlgorithmBlock.nItems*sizeof struATPAutoAlgoID;									//算法块
	nAlgorithmGroupBlock	= _UserInfo.AlgorithmGroupBlock.nItems*sizeof struATPAutoID;								//算分组块
	nServerBlock			= _UserInfo.ServerBlock.nItems*sizeof struATPAutoID;
	nServerGroupBlock		= _UserInfo.ServerGroupBlock.nItems*sizeof struATPAutoID;
	*pnLen					= g_stru_ATPManageMsgHeadInfoSize + nATPUserInfoSize+ nFundBlock + nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock + nServerGroupBlock;
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"添加用户(NAME):%s 成功-NEW出错",_DataBaseUser.szUserID);
		AddOperateLog(ID_ATPMANAGE_ADDUSER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"添加用户(NAME):%s 成功",_DataBaseUser.szUserID);
	AddOperateLog(ID_ATPMANAGE_ADDUSER,m_szAccount,sz);
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_UserInfo,nATPUserInfoSize);
	if (_ATPDBSUser.pATPFund)
	{
		memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize+nATPUserInfoSize],(char *)_ATPDBSUser.pATPFund,nFundBlock);
	}
	
	if (_ATPDBSUser.pAlgorithmIDs)
	{
		memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize+nATPUserInfoSize+nFundBlock],(char *)_ATPDBSUser.pAlgorithmIDs,nAlgorithmBlock);
	}
	
	if (_ATPDBSUser.pAlgorithmGroupIDs)
	{
		memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize+nATPUserInfoSize+nFundBlock+nAlgorithmBlock],(char *)_ATPDBSUser.pAlgorithmGroupIDs,nAlgorithmGroupBlock);
	}
	
	if (_ATPDBSUser.pServerIDs)
	{
		memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize+nATPUserInfoSize+nFundBlock+nAlgorithmBlock+nAlgorithmGroupBlock],(char *)_ATPDBSUser.pServerIDs,nServerBlock);
	}
	
	if (_ATPDBSUser.pServerGroupIDs)
	{
		memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize+nATPUserInfoSize+nFundBlock+nAlgorithmBlock+nAlgorithmGroupBlock+nServerBlock],(char *)_ATPDBSUser.pServerGroupIDs,nServerGroupBlock);
	}
	


	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::ModifyUser(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPUserInfo *pUserInfo		= (stru_ATPUserInfo *)pData;
	struATPDataBaseUser _DataBaseUser	= {0};

	int nFundBlock				= 0;
	int nAlgorithmBlock			= 0;								//算法块
	int nAlgorithmGroupBlock	= 0;								//算分组块
	int nServerBlock			= 0;								//服务器块
	int nServerGroupBlock		= 0;								//服务器组块
	int nATPUserInfoSize	= sizeof stru_ATPUserInfo;



	{
		nFundBlock				= pUserInfo->FundBlock.nItems*pUserInfo->FundBlock.nItemSize;
		nAlgorithmBlock			= pUserInfo->AlgorithmBlock.nItems*pUserInfo->AlgorithmBlock.nItemSize;	
		nAlgorithmGroupBlock	= pUserInfo->AlgorithmGroupBlock.nItems*pUserInfo->AlgorithmGroupBlock.nItemSize;
		nServerBlock			= pUserInfo->ServerBlock.nItems*pUserInfo->ServerBlock.nItemSize;
		nServerGroupBlock		= pUserInfo->ServerGroupBlock.nItems*pUserInfo->ServerGroupBlock.nItemSize;
		_DataBaseUser.pATPFund = NULL;
		if (pUserInfo->FundBlock.nItems>0)
		{
			_DataBaseUser.pATPFund				= new struATPDataBaseFund[pUserInfo->FundBlock.nItems];
		}
		_DataBaseUser.pAlgorithmIDs	= NULL;
		if (pUserInfo->AlgorithmBlock.nItems>0)
		{
			_DataBaseUser.pAlgorithmIDs			= new struATPAutoAlgoID[pUserInfo->AlgorithmBlock.nItems];
		}
		_DataBaseUser.pAlgorithmGroupIDs = NULL;
		if (pUserInfo->AlgorithmGroupBlock.nItems>0)
		{
			_DataBaseUser.pAlgorithmGroupIDs	= new struATPAutoID[pUserInfo->AlgorithmGroupBlock.nItems];
		}
		_DataBaseUser.pServerIDs = NULL;
		if (pUserInfo->ServerBlock.nItems>0)
		{
			_DataBaseUser.pServerIDs			= new struATPAutoID[pUserInfo->ServerBlock.nItems];
		}
		_DataBaseUser.pServerGroupIDs = NULL;
		if (pUserInfo->ServerGroupBlock.nItems>0)
		{
			_DataBaseUser.pServerGroupIDs		= new struATPAutoID[pUserInfo->ServerGroupBlock.nItems];
		}
		
		

		_DataBaseUser.nSerialNumber				= pUserInfo->nSerialNumber;														//	自动增长
		strncpy(_DataBaseUser.szUserID,pUserInfo->szUserID,sizeof _DataBaseUser.szUserID);										//	用户ID
		strncpy(_DataBaseUser.szPwd,pUserInfo->szPwd,sizeof _DataBaseUser.szPwd);												//	用户密码
		strncpy(_DataBaseUser.szUserName,pUserInfo->szUserName,sizeof _DataBaseUser.szUserName);								//	用户名
		strncpy(_DataBaseUser.szCardID,pUserInfo->szCardID,sizeof _DataBaseUser.szCardID);										//	身份证号码
		memcpy((char *)_DataBaseUser.nGroupIDs,(char *)pUserInfo->nGroupIDs,sizeof _DataBaseUser.nGroupIDs);					//	用户组ID
		memcpy((char *)_DataBaseUser.nPermissionIDs,(char *)pUserInfo->nPermissionIDs,sizeof _DataBaseUser.nPermissionIDs);		//	权限ID
		_DataBaseUser.nAuthorizeBeginDate		= pUserInfo->nAuthorizeBeginDate;												//	授权使用开始日期
		_DataBaseUser.nAuthorizeEndDate			= pUserInfo->nAuthorizeEndDate;													//	授权使用截止日期
		_DataBaseUser.nStatus					= pUserInfo->nStatus;															//	用户使用状态
		memcpy(_DataBaseUser.szMobiles,pUserInfo->szMobiles,sizeof _DataBaseUser.szMobiles);									//	手机号码,含区号
		memcpy(_DataBaseUser.szTelephones,pUserInfo->szTelephones,sizeof _DataBaseUser.szTelephones);							//	电话号码
		memcpy((char *)_DataBaseUser.nQQNumbers,(char *)pUserInfo->nQQNumbers,sizeof _DataBaseUser.nQQNumbers);					//	QQ号码
		memcpy(_DataBaseUser.szEmails,pUserInfo->szEmails,sizeof _DataBaseUser.szEmails);										//	Email号码
		strncpy(_DataBaseUser.szUserExplain,pUserInfo->szUserExplain,sizeof _DataBaseUser.szUserExplain);						//	用户说明,含禁用理由
		strncpy(_DataBaseUser.szIPs,pUserInfo->szIPs,sizeof _DataBaseUser.szIPs);												//	限制IP
		strncpy(_DataBaseUser.szMacMark,pUserInfo->szMacMark,sizeof _DataBaseUser.szMacMark);									//	限制MAC地址
		strncpy(_DataBaseUser.szDiskNum,pUserInfo->szDiskNum,sizeof _DataBaseUser.szDiskNum);									//	限制硬盘序列号
		memcpy(_DataBaseUser.nLimitBeginTime,pUserInfo->nLimitBeginTime,sizeof _DataBaseUser.nLimitBeginTime);					//	限制开始时间
		memcpy(_DataBaseUser.nLimitEndTime,pUserInfo->nLimitEndTime,sizeof _DataBaseUser.nLimitEndTime);						//	限制结束时间
		_DataBaseUser.chLimitWeek				= pUserInfo->chLimitWeek;														//	限制星期,0x80是限制
		_DataBaseUser.nCanAssociateFundsAccount	= pUserInfo->FundBlock.nItems;													//	当前资金帐号结构体数,最多10个
		if (_DataBaseUser.pATPFund)
		{
			memcpy((char *)_DataBaseUser.pATPFund,&pData[nATPUserInfoSize],nFundBlock);														//	资金帐号结构体
		}
		
		_DataBaseUser.nCanRunAlgorithm			= pUserInfo->nCanRunAlgorithm;													//	允许同时运行算法个数
		_DataBaseUser.nAlgorithmN				= pUserInfo->AlgorithmBlock.nItems;												//	算法个数
		if (_DataBaseUser.pAlgorithmIDs)
		{
			memcpy((char *)_DataBaseUser.pAlgorithmIDs,&pData[nATPUserInfoSize + nFundBlock],nAlgorithmBlock);								//	算法IDs
		}
		
		_DataBaseUser.nAlgorithmGroupN			= pUserInfo->AlgorithmGroupBlock.nItems;										//	算法组个数
		if (_DataBaseUser.pAlgorithmGroupIDs)
		{
			memcpy((char *)_DataBaseUser.pAlgorithmGroupIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock],nAlgorithmGroupBlock);	//	算法组IDs
		}
		
		_DataBaseUser.nServerN = pUserInfo->ServerBlock.nItems;
		if (_DataBaseUser.pServerIDs)
		{
			memcpy((char *)_DataBaseUser.pServerIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock + nAlgorithmGroupBlock],nServerBlock);//	专属服务器
		}
		
		_DataBaseUser.nServerGroupN				= pUserInfo->ServerGroupBlock.nItems;											//	服务器组个数
		if (_DataBaseUser.pServerGroupIDs)
		{
			memcpy((char *)_DataBaseUser.pServerGroupIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock],nServerGroupBlock);//	服务器组IDs
		}
		
		_DataBaseUser.nCreateDate				= pUserInfo->nCreateDate;														//	创建日期
		_DataBaseUser.nCreateTime				= pUserInfo->nCreateTime;														//	创建时间
		_DataBaseUser.nLastDate					= pUserInfo->nLastDate;															//	最后登陆日期
		_DataBaseUser.nLastTime					= pUserInfo->nLastTime;															//	最后登陆时间
		_DataBaseUser.nDeleteMark				= pUserInfo->nDeleteMark;														//	删除标志

	}
	//////////////////////////////////////////////////////////////////////////

	int nRet = g_pATPFileDBApi->ModifyUser(&_DataBaseUser);

	
	if (_DataBaseUser.pATPFund)
	{
		delete _DataBaseUser.pATPFund;_DataBaseUser.pATPFund = NULL;
	}
	if (_DataBaseUser.pAlgorithmIDs)
	{
		delete _DataBaseUser.pAlgorithmIDs;_DataBaseUser.pAlgorithmIDs = NULL;
	}
	if (_DataBaseUser.pAlgorithmGroupIDs)
	{
		delete _DataBaseUser.pAlgorithmGroupIDs;_DataBaseUser.pAlgorithmGroupIDs = NULL;
	}
	if (_DataBaseUser.pServerIDs)
	{
		delete _DataBaseUser.pServerIDs;_DataBaseUser.pServerIDs = NULL;
	}
	if (_DataBaseUser.pServerGroupIDs)
	{
		delete _DataBaseUser.pServerGroupIDs;_DataBaseUser.pServerGroupIDs = NULL;
	}


	//////////////////////////////////////////////////////////////////////////
	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;

	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"修改成功");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"修改用户(NAME):%s 失败-传入数据为NULL",_DataBaseUser.szUserID);
			break;
		case EXISTDATA:
			sprintf(sz,"修改用户(NAME):%s 失败-该服务器组已经存在",_DataBaseUser.szUserID);
			break;
		case NEWERROR:
			sprintf(sz,"修改用户(NAME):%s 失败-NEW出错",_DataBaseUser.szUserID);
			break;
		case NULLHANDLE:
			sprintf(sz,"修改用户(NAME):%s 失败-操作句柄为NULL",_DataBaseUser.szUserID);
			break;
		case ZERORECORD:
			sprintf(sz,"修改用户(NAME):%s 失败-没有该记录",_DataBaseUser.szUserID);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_MODIFYUSER,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"修改失败");
	}
	

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"修改用户(NAME):%s 成功-NEW出错",_DataBaseUser.szUserID);
		AddOperateLog(ID_ATPMANAGE_MODIFYUSER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"修改用户(NAME):%s 成功",_DataBaseUser.szUserID);
	AddOperateLog(ID_ATPMANAGE_MODIFYUSER,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::DelUser(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPUserInfo *pUserInfo		= (stru_ATPUserInfo *)pData;
	struATPDataBaseUser _DataBaseUser	= {0};

	int nFundBlock				= 0;
	int nAlgorithmBlock			= 0;								//算法块
	int nAlgorithmGroupBlock	= 0;								//算分组块
	int nServerBlock			= 0;								//服务器块
	int nServerGroupBlock		= 0;								//服务器组块
	int nATPUserInfoSize	= sizeof stru_ATPUserInfo;



	{
		nFundBlock				= pUserInfo->FundBlock.nItems*pUserInfo->FundBlock.nItemSize;
		nAlgorithmBlock			= pUserInfo->AlgorithmBlock.nItems*pUserInfo->AlgorithmBlock.nItemSize;	
		nAlgorithmGroupBlock	= pUserInfo->AlgorithmGroupBlock.nItems*pUserInfo->AlgorithmGroupBlock.nItemSize;
		nServerBlock			= pUserInfo->ServerBlock.nItems*pUserInfo->ServerBlock.nItemSize;
		nServerGroupBlock		= pUserInfo->ServerGroupBlock.nItems*pUserInfo->ServerGroupBlock.nItemSize;

		_DataBaseUser.pATPFund = NULL;
		if (pUserInfo->FundBlock.nItems>0)
		{
			_DataBaseUser.pATPFund				= new struATPDataBaseFund[pUserInfo->FundBlock.nItems];
		}
		_DataBaseUser.pAlgorithmIDs	 = NULL;
		if (pUserInfo->AlgorithmBlock.nItems>0)
		{
			_DataBaseUser.pAlgorithmIDs			= new struATPAutoAlgoID[pUserInfo->AlgorithmBlock.nItems];
		}
		_DataBaseUser.pAlgorithmGroupIDs = NULL;
		if (pUserInfo->AlgorithmGroupBlock.nItems>0)
		{
			_DataBaseUser.pAlgorithmGroupIDs	= new struATPAutoID[pUserInfo->AlgorithmGroupBlock.nItems];
		}
		_DataBaseUser.pServerIDs = NULL;
		if (pUserInfo->ServerBlock.nItems>0)
		{
			_DataBaseUser.pServerIDs			= new struATPAutoID[pUserInfo->ServerBlock.nItems];
		}
		_DataBaseUser.pServerGroupIDs = NULL;
		if (pUserInfo->ServerGroupBlock.nItems>0)
		{
			_DataBaseUser.pServerGroupIDs		= new struATPAutoID[pUserInfo->ServerGroupBlock.nItems];
		}
		
		


		_DataBaseUser.nSerialNumber				= pUserInfo->nSerialNumber;														//	自动增长
		strncpy(_DataBaseUser.szUserID,pUserInfo->szUserID,sizeof _DataBaseUser.szUserID);										//	用户ID
		strncpy(_DataBaseUser.szPwd,pUserInfo->szPwd,sizeof _DataBaseUser.szPwd);												//	用户密码
		strncpy(_DataBaseUser.szUserName,pUserInfo->szUserName,sizeof _DataBaseUser.szUserName);								//	用户名
		strncpy(_DataBaseUser.szCardID,pUserInfo->szCardID,sizeof _DataBaseUser.szCardID);										//	身份证号码
		memcpy((char *)_DataBaseUser.nGroupIDs,(char *)pUserInfo->nGroupIDs,sizeof _DataBaseUser.nGroupIDs);					//	用户组ID
		memcpy((char *)_DataBaseUser.nPermissionIDs,(char *)pUserInfo->nPermissionIDs,sizeof _DataBaseUser.nPermissionIDs);		//	权限ID
		_DataBaseUser.nAuthorizeBeginDate		= pUserInfo->nAuthorizeBeginDate;												//	授权使用开始日期
		_DataBaseUser.nAuthorizeEndDate			= pUserInfo->nAuthorizeEndDate;													//	授权使用截止日期
		_DataBaseUser.nStatus					= pUserInfo->nStatus;															//	用户使用状态
		memcpy(_DataBaseUser.szMobiles,pUserInfo->szMobiles,sizeof _DataBaseUser.szMobiles);									//	手机号码,含区号
		memcpy(_DataBaseUser.szTelephones,pUserInfo->szTelephones,sizeof _DataBaseUser.szTelephones);							//	电话号码
		memcpy((char *)_DataBaseUser.nQQNumbers,(char *)pUserInfo->nQQNumbers,sizeof _DataBaseUser.nQQNumbers);					//	QQ号码
		memcpy(_DataBaseUser.szEmails,pUserInfo->szEmails,sizeof _DataBaseUser.szEmails);										//	Email号码
		strncpy(_DataBaseUser.szUserExplain,pUserInfo->szUserExplain,sizeof _DataBaseUser.szUserExplain);						//	用户说明,含禁用理由
		strncpy(_DataBaseUser.szIPs,pUserInfo->szIPs,sizeof _DataBaseUser.szIPs);												//	限制IP
		strncpy(_DataBaseUser.szMacMark,pUserInfo->szMacMark,sizeof _DataBaseUser.szMacMark);									//	限制MAC地址
		strncpy(_DataBaseUser.szDiskNum,pUserInfo->szDiskNum,sizeof _DataBaseUser.szDiskNum);									//	限制硬盘序列号
		memcpy(_DataBaseUser.nLimitBeginTime,pUserInfo->nLimitBeginTime,sizeof _DataBaseUser.nLimitBeginTime);					//	限制开始时间
		memcpy(_DataBaseUser.nLimitEndTime,pUserInfo->nLimitEndTime,sizeof _DataBaseUser.nLimitEndTime);						//	限制结束时间
		_DataBaseUser.chLimitWeek				= pUserInfo->chLimitWeek;														//	限制星期,0x80是限制
		_DataBaseUser.nCanAssociateFundsAccount	= pUserInfo->FundBlock.nItems;													//	当前资金帐号结构体数,最多10个
		if (_DataBaseUser.pATPFund)
		{
			memcpy(_DataBaseUser.pATPFund,&pData[nATPUserInfoSize],nFundBlock);														//	资金帐号结构体
		}
		
		_DataBaseUser.nCanRunAlgorithm			= pUserInfo->nCanRunAlgorithm;													//	允许同时运行算法个数
		_DataBaseUser.nAlgorithmN				= pUserInfo->AlgorithmBlock.nItems;												//	算法个数
		if (_DataBaseUser.pAlgorithmIDs)
		{
			memcpy(_DataBaseUser.pAlgorithmIDs,&pData[nATPUserInfoSize + nFundBlock],nAlgorithmBlock);								//	算法IDs
		}
		
		_DataBaseUser.nAlgorithmGroupN			= pUserInfo->AlgorithmGroupBlock.nItems;										//	算法组个数
		if (_DataBaseUser.pAlgorithmGroupIDs)
		{
			memcpy(_DataBaseUser.pAlgorithmGroupIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock],nAlgorithmGroupBlock);	//	算法组IDs
		}
		
		_DataBaseUser.nServerN = pUserInfo->ServerBlock.nItems;
		if (_DataBaseUser.pServerIDs)
		{
			memcpy(_DataBaseUser.pServerIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock + nAlgorithmGroupBlock],nServerBlock);//	专属服务器
		}
		
		_DataBaseUser.nServerGroupN				= pUserInfo->ServerGroupBlock.nItems;											//	服务器组个数
		if (_DataBaseUser.pServerGroupIDs)
		{
			memcpy(_DataBaseUser.pServerGroupIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock],nServerGroupBlock);//	服务器组IDs
		}
		
		_DataBaseUser.nCreateDate				= pUserInfo->nCreateDate;													//	创建日期
		_DataBaseUser.nCreateTime				= pUserInfo->nCreateTime;													//	创建时间
		_DataBaseUser.nLastDate					= pUserInfo->nLastDate;															//	最后登陆日期
		_DataBaseUser.nLastTime					= pUserInfo->nLastTime;															//	最后登陆时间
		_DataBaseUser.nDeleteMark				= pUserInfo->nDeleteMark;														//	删除标志

	}
	//////////////////////////////////////////////////////////////////////////

	int nRet = g_pATPFileDBApi->DelUser(&_DataBaseUser);

	if (_DataBaseUser.pATPFund)
	{
		delete _DataBaseUser.pATPFund;_DataBaseUser.pATPFund = NULL;
	}
	if (_DataBaseUser.pAlgorithmIDs)
	{
		delete _DataBaseUser.pAlgorithmIDs;_DataBaseUser.pAlgorithmIDs = NULL;
	}
	if (_DataBaseUser.pAlgorithmGroupIDs)
	{
		delete _DataBaseUser.pAlgorithmGroupIDs;_DataBaseUser.pAlgorithmGroupIDs = NULL;
	}
	if (_DataBaseUser.pServerIDs)
	{
		delete _DataBaseUser.pServerIDs;_DataBaseUser.pServerIDs = NULL;
	}
	if (_DataBaseUser.pServerGroupIDs)
	{
		delete _DataBaseUser.pServerGroupIDs;_DataBaseUser.pServerGroupIDs = NULL;
	}


	//////////////////////////////////////////////////////////////////////////
	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;

	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"删除成功");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"删除用户(NAME):%s 失败-传入数据为NULL",_DataBaseUser.szUserID);
			break;
		case EXISTDATA:
			sprintf(sz,"删除用户(NAME):%s 失败-该服务器组已经存在",_DataBaseUser.szUserID);
			break;
		case NEWERROR:
			sprintf(sz,"删除用户(NAME):%s 失败-NEW出错",_DataBaseUser.szUserID);
			break;
		case NULLHANDLE:
			sprintf(sz,"删除用户(NAME):%s 失败-操作句柄为NULL",_DataBaseUser.szUserID);
			break;
		case 0:
		case ZERORECORD:
			sprintf(sz,"删除用户(NAME):%s 失败-没有该记录",_DataBaseUser.szUserID);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_DELETEUSER,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"删除失败");
	}


	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"删除用户(NAME):%s 成功-NEW出错",_DataBaseUser.szUserID);
		AddOperateLog(ID_ATPMANAGE_DELETEUSER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"删除用户(NAME):%s 成功",_DataBaseUser.szUserID);
	AddOperateLog(ID_ATPMANAGE_DELETEUSER,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::QueryUser(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseUser *pATPDataBaseUser = NULL;
	struATPDataBaseUser_QUERY *pATPDataBaseUser_QUERY= (struATPDataBaseUser_QUERY *)pData;
	int nATPUserInfoSize	= sizeof stru_ATPUserInfo;
	//nRet 查询结果条数
	int nRet = g_pATPFileDBApi->QueryUser(pATPDataBaseUser_QUERY,m_szAccount,&pATPDataBaseUser);

	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"查询用户 失败-传入数据为NULL");
			break;
		case EXISTDATA:
			sprintf(sz,"查询用户 失败-该用户组已经存在");
			break;
		case NEWERROR:
			sprintf(sz,"查询用户 失败-NEW出错");
			break;
		case NULLHANDLE:
			sprintf(sz,"查询用户 失败-操作句柄为NULL");
			break;
		case 0:
		case ZERORECORD:
			sprintf(sz,"查询用户 成功-没有记录");
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_QUERYUSERINFO,m_szAccount,sz);
		return nRet;
	}

	int i = 0;
	*pnLen  = g_stru_ATPManageMsgHeadInfoSize;
	for (;i<nRet;i++)
	{
		(*pnLen) += (nATPUserInfoSize+(pATPDataBaseUser[i].nAlgorithmGroupN+pATPDataBaseUser[i].nServerN+pATPDataBaseUser[i].nServerGroupN)*sizeof struATPAutoID+pATPDataBaseUser[i].nCanAssociateFundsAccount*sizeof struATPDataBaseFund+pATPDataBaseUser[i].nAlgorithmN*sizeof struATPAutoAlgoID);
	}

	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"查询用户 成功-NEW出错");
		AddOperateLog(ID_ATPMANAGE_QUERYUSERINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"查询用户 成功");
	AddOperateLog(ID_ATPMANAGE_QUERYUSERINFO,m_szAccount,sz);
	stru_ATPUserInfo _ManagerInfo	= {0};
	int nFundBlock				= 0;
	int nAlgorithmBlock			= 0;								//算法块
	int nAlgorithmGroupBlock	= 0;								//算分组块
	int nServerBlock			= 0;								//服务器块
	int nServerGroupBlock		= 0;								//服务器组块

	int nHead	= g_stru_ATPManageMsgHeadInfoSize;
	int nCount = 0;
	pHead->nItem = nRet;
	memcpy(*ppOutData,(char *)pHead,nHead);
	nCount = nHead;
	for (i=0;i<nRet;i++)
	{
		_ManagerInfo.nSerialNumber					= pATPDataBaseUser[i].nSerialNumber;											//	自动增长
		strncpy(_ManagerInfo.szUserID,pATPDataBaseUser[i].szUserID,sizeof _ManagerInfo.szUserID);									//	用户ID
		strncpy(_ManagerInfo.szPwd,pATPDataBaseUser[i].szPwd,sizeof _ManagerInfo.szPwd);												//	用户密码
		strncpy(_ManagerInfo.szUserName,pATPDataBaseUser[i].szUserName,sizeof _ManagerInfo.szUserName);								//	用户名
		strncpy(_ManagerInfo.szCardID,pATPDataBaseUser[i].szCardID,sizeof _ManagerInfo.szCardID);									//	身份证号码
		memcpy((char *)_ManagerInfo.nGroupIDs,(char *)pATPDataBaseUser[i].nGroupIDs,sizeof _ManagerInfo.nGroupIDs);		//	用户组ID
		memcpy((char *)_ManagerInfo.nPermissionIDs,(char *)pATPDataBaseUser[i].nPermissionIDs,sizeof _ManagerInfo.nPermissionIDs);		//	权限ID
		_ManagerInfo.nAuthorizeBeginDate			= pATPDataBaseUser[i].nAuthorizeBeginDate;									//	授权使用开始日期
		_ManagerInfo.nAuthorizeEndDate				= pATPDataBaseUser[i].nAuthorizeEndDate;										//	授权使用截止日期
		_ManagerInfo.nStatus						= pATPDataBaseUser[i].nStatus;											//	用户使用状态
		memcpy((char *)_ManagerInfo.szMobiles,(char *)pATPDataBaseUser[i].szMobiles,sizeof _ManagerInfo.szMobiles);					//	手机号码,含区号
		memcpy((char *)_ManagerInfo.szTelephones,(char *)pATPDataBaseUser[i].szTelephones,sizeof _ManagerInfo.szTelephones);			//	电话号码
		memcpy((char *)_ManagerInfo.nQQNumbers,(char *)pATPDataBaseUser[i].nQQNumbers,sizeof _ManagerInfo.nQQNumbers);				//	QQ号码
		memcpy(_ManagerInfo.szEmails,pATPDataBaseUser[i].szEmails,sizeof _ManagerInfo.szEmails);									//	Email号码
		strncpy(_ManagerInfo.szUserExplain,pATPDataBaseUser[i].szUserExplain,sizeof _ManagerInfo.szUserExplain);						//	用户说明,含禁用理由
		strncpy(_ManagerInfo.szIPs,pATPDataBaseUser[i].szIPs,sizeof _ManagerInfo.szIPs);											//	限制IP
		strncpy(_ManagerInfo.szMacMark,pATPDataBaseUser[i].szMacMark,sizeof _ManagerInfo.szMacMark);								//	限制MAC地址
		strncpy(_ManagerInfo.szDiskNum,pATPDataBaseUser[i].szDiskNum,sizeof _ManagerInfo.szDiskNum);								//	限制硬盘序列号
		memcpy((char *)_ManagerInfo.nLimitBeginTime,(char *)pATPDataBaseUser[i].nLimitBeginTime,sizeof _ManagerInfo.nLimitBeginTime);	//	限制开始时间
		memcpy((char *)_ManagerInfo.nLimitEndTime,(char *)pATPDataBaseUser[i].nLimitEndTime,sizeof _ManagerInfo.nLimitEndTime);		//	限制结束时间
		_ManagerInfo.chLimitWeek					= pATPDataBaseUser[i].chLimitWeek;											//	限制星期,0x80是限制
		_ManagerInfo.FundBlock.nItems				= pATPDataBaseUser[i].nCanAssociateFundsAccount;								//	当前资金帐号结构体数Items,最多10个         itemsize = sizeof(struATPID)
		_ManagerInfo.FundBlock.nItemSize			= sizeof struATPDataBaseFund;	
		_ManagerInfo.nCanRunAlgorithm				= pATPDataBaseUser[i].nCanRunAlgorithm;										//	允许同时运行算法个数
		_ManagerInfo.AlgorithmBlock.nItems			= pATPDataBaseUser[i].nAlgorithmN;										//	算法个数items  ,  itemsize = sizeof(struATPAutoID)
		_ManagerInfo.AlgorithmBlock.nItemSize		= sizeof struATPAutoAlgoID;
		_ManagerInfo.AlgorithmGroupBlock.nItems	= pATPDataBaseUser[i].nAlgorithmGroupN;										//	算法组个数 items, itemsize = sizeof(struATPAutoID)
		_ManagerInfo.AlgorithmGroupBlock.nItemSize = sizeof struATPAutoID;
		_ManagerInfo.ServerBlock.nItems			= pATPDataBaseUser[i].nServerN;
		_ManagerInfo.ServerBlock.nItemSize			= sizeof struATPAutoID;
		_ManagerInfo.ServerGroupBlock.nItems		= pATPDataBaseUser[i].nServerGroupN;
		_ManagerInfo.ServerGroupBlock.nItemSize	= sizeof struATPAutoID;
		_ManagerInfo.nCreateDate					= pATPDataBaseUser[i].nCreateDate;											//	创建日期
		_ManagerInfo.nCreateTime					= pATPDataBaseUser[i].nCreateTime;											//	创建时间
		_ManagerInfo.nLastDate						= pATPDataBaseUser[i].nLastDate;											//	最后登陆日期
		_ManagerInfo.nLastTime						= pATPDataBaseUser[i].nLastTime;											//	最后登陆时间
		_ManagerInfo.nDeleteMark					= pATPDataBaseUser[i].nDeleteMark;											//	删除标志

		nFundBlock				= pATPDataBaseUser[i].nCanAssociateFundsAccount*sizeof struATPDataBaseFund;
		nAlgorithmBlock			= pATPDataBaseUser[i].nAlgorithmN*sizeof struATPAutoAlgoID;
		nAlgorithmGroupBlock	= pATPDataBaseUser[i].nAlgorithmGroupN*sizeof struATPAutoID;
		nServerBlock			= pATPDataBaseUser[i].nServerN*sizeof struATPAutoID;
		nServerGroupBlock		= pATPDataBaseUser[i].nServerGroupN*sizeof struATPAutoID;

		memcpy(&(*ppOutData)[nCount],(char *)&_ManagerInfo,nATPUserInfoSize);
		nCount += nATPUserInfoSize;
		if (pATPDataBaseUser[i].pATPFund)
		{
			memcpy(&(*ppOutData)[nCount],(char*)pATPDataBaseUser[i].pATPFund,nFundBlock);
			nCount += nFundBlock;
		}
		
		if (pATPDataBaseUser[i].pAlgorithmIDs)
		{
			memcpy(&(*ppOutData)[nCount],(char*)pATPDataBaseUser[i].pAlgorithmIDs,nAlgorithmBlock);
			nCount += nAlgorithmBlock;
		}
		
		if (pATPDataBaseUser[i].pAlgorithmGroupIDs)
		{
			memcpy(&(*ppOutData)[nCount],(char*)pATPDataBaseUser[i].pAlgorithmGroupIDs,nAlgorithmGroupBlock);
			nCount += nAlgorithmGroupBlock;
		}
		
		if (pATPDataBaseUser[i].pServerIDs)
		{
			memcpy(&(*ppOutData)[nCount],(char*)pATPDataBaseUser[i].pServerIDs,nServerBlock);
			nCount += nServerBlock;
		}
		
		if (pATPDataBaseUser[i].pServerGroupIDs)
		{
			memcpy(&(*ppOutData)[nCount],(char*)pATPDataBaseUser[i].pServerGroupIDs,nServerGroupBlock);
			nCount += nServerGroupBlock;
		}
		
	}

	delete pATPDataBaseUser;
	pATPDataBaseUser = NULL;
	return nRet;
}



int CHHNetFrameProcessor_ATPManagerServer::AddAlgorithmGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPAlgorithmGroupInfo *pAlgorithmGroupInfo			= (stru_ATPAlgorithmGroupInfo *)pData;
	struATPDataBaseAlgorithmGroup _DataBaseAlgorithmGroup = {0};

	int nAlgorithmGroupInfoSize = sizeof stru_ATPAlgorithmGroupInfo;

	memcpy((char *)&_DataBaseAlgorithmGroup,(char *)pAlgorithmGroupInfo,nAlgorithmGroupInfoSize);
	strcpy(_DataBaseAlgorithmGroup.szManagerID,m_szAccount);
	CTime t = CTime::GetCurrentTime();
	_DataBaseAlgorithmGroup.nCreateDate = t.GetYear()*10000+t.GetMonth()*100+t.GetDay();
	_DataBaseAlgorithmGroup.nCreateTime = t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();

	
	//////////////////////////////////////////////////////////////////////////
	struATPDataBaseAlgorithmGroup _ATPDBSAlgorithmGroup = {0};
	int nRet = g_pATPFileDBApi->AddAlgorithmGroup(&_DataBaseAlgorithmGroup,&_ATPDBSAlgorithmGroup);


	if (nRet != 0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"添加算法组(NAME):%s 失败-传入数据为NULL",_DataBaseAlgorithmGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"添加算法组(NAME):%s 失败-该算法器组已经存在",_DataBaseAlgorithmGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"添加算法组(NAME):%s 失败-NEW出错",_DataBaseAlgorithmGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"添加算法组(NAME):%s 失败-操作句柄为NULL",_DataBaseAlgorithmGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"添加算法组(NAME):%s 失败-没有该记录",_DataBaseAlgorithmGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_ADDALGORITHMGROUP,m_szAccount,sz);
		return nRet;
	}

	*pnLen = g_stru_ATPManageMsgHeadInfoSize + nAlgorithmGroupInfoSize;
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"添加算法组(NAME):%s 成功-NEW出错",_DataBaseAlgorithmGroup.szName);
		AddOperateLog(ID_ATPMANAGE_ADDALGORITHMGROUP,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"添加算法组(NAME):%s 成功",_DataBaseAlgorithmGroup.szName);
	AddOperateLog(ID_ATPMANAGE_ADDALGORITHMGROUP,m_szAccount,sz);
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_ATPDBSAlgorithmGroup,nAlgorithmGroupInfoSize);

	return nRet;;
}


int CHHNetFrameProcessor_ATPManagerServer::ModifyAlgorithmGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPAlgorithmGroupInfo *pAlgorithmGroupInfo			= (stru_ATPAlgorithmGroupInfo *)pData;
	struATPDataBaseAlgorithmGroup _DataBaseAlgorithmGroup = {0};

	int nAlgorithmGroupInfoSize = sizeof stru_ATPAlgorithmGroupInfo;
	memcpy((char *)&_DataBaseAlgorithmGroup,(char *)pAlgorithmGroupInfo,nAlgorithmGroupInfoSize);

	//////////////////////////////////////////////////////////////////////////

	int nRet = g_pATPFileDBApi->ModifyAlgorithmGroup(&_DataBaseAlgorithmGroup);


	//////////////////////////////////////////////////////////////////////////
	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;
	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"修改成功");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"修改算法组(NAME):%s 失败-传入数据为NULL",_DataBaseAlgorithmGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"修改算法组(NAME):%s 失败-该服务器组已经存在",_DataBaseAlgorithmGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"修改算法组(NAME):%s 失败-NEW出错",_DataBaseAlgorithmGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"修改算法组(NAME):%s 失败-操作句柄为NULL",_DataBaseAlgorithmGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"修改算法组(NAME):%s 失败-没有该记录",_DataBaseAlgorithmGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_MODIFYALGORITHMGROUP,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"修改失败");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"修改算法组(NAME):%s 成功-NEW出错",_DataBaseAlgorithmGroup.szName);
		AddOperateLog(ID_ATPMANAGE_MODIFYALGORITHMGROUP,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"修改算法组(NAME):%s 成功",_DataBaseAlgorithmGroup.szName);
	AddOperateLog(ID_ATPMANAGE_MODIFYALGORITHMGROUP,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::DelAlgorithmGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPAlgorithmGroupInfo *pAlgorithmGroupInfo			= (stru_ATPAlgorithmGroupInfo *)pData;
	struATPDataBaseAlgorithmGroup _DataBaseAlgorithmGroup = {0};

	int nAlgorithmGroupInfoSize = sizeof stru_ATPAlgorithmGroupInfo;
	memcpy((char *)&_DataBaseAlgorithmGroup,(char *)pAlgorithmGroupInfo,nAlgorithmGroupInfoSize);

	//////////////////////////////////////////////////////////////////////////

	int nRet = g_pATPFileDBApi->DelAlgorithmGroup(&_DataBaseAlgorithmGroup);


	//////////////////////////////////////////////////////////////////////////
	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;
	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"修改成功");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"删除算法组(NAME):%s 失败-传入数据为NULL",_DataBaseAlgorithmGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"删除算法组(NAME):%s 失败-该服务器组已经存在",_DataBaseAlgorithmGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"删除算法组(NAME):%s 失败-NEW出错",_DataBaseAlgorithmGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"删除算法组(NAME):%s 失败-操作句柄为NULL",_DataBaseAlgorithmGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"删除算法组(NAME):%s 失败-没有该记录",_DataBaseAlgorithmGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_DELETEALGORITHMGROUP,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"修改失败");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"删除算法组(NAME):%s 成功-NEW出错",_DataBaseAlgorithmGroup.szName);
		AddOperateLog(ID_ATPMANAGE_DELETEALGORITHMGROUP,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"删除算法组(NAME):%s 成功",_DataBaseAlgorithmGroup.szName);
	AddOperateLog(ID_ATPMANAGE_DELETEALGORITHMGROUP,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::QueryAlgorithmGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseAlgorithmGroup *pATPDataBaseAlgorithmGroup = NULL;
	int nATPAlgorithmGroupInfoSize = sizeof stru_ATPAlgorithmGroupInfo;
	//nRet 查询结果条数
	int nRet = g_pATPFileDBApi->QueryAlgorithmGroup(m_szAccount,&pATPDataBaseAlgorithmGroup);

	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"查询算法组 失败-传入数据为NULL");
			break;
		case EXISTDATA:
			sprintf(sz,"查询算法组 失败-该用户组已经存在");
			break;
		case NEWERROR:
			sprintf(sz,"查询算法组 失败-NEW出错");
			break;
		case NULLHANDLE:
			sprintf(sz,"查询算法组 失败-操作句柄为NULL");
			break;
			case 0:
		case ZERORECORD:
			sprintf(sz,"查询算法组 成功-没有记录");
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_QUERYALGORITHMGROUPINFO,m_szAccount,sz);
		return nRet;
	}

	*pnLen = g_stru_ATPManageMsgHeadInfoSize + nRet*nATPAlgorithmGroupInfoSize;
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"查询算法组 成功-NEW出错");
		AddOperateLog(ID_ATPMANAGE_QUERYALGORITHMGROUPINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"查询算法组 成功");
	AddOperateLog(ID_ATPMANAGE_QUERYALGORITHMGROUPINFO,m_szAccount,sz);
	stru_ATPManagerInfo _ManagerInfo	= {0};
	int nHead	= g_stru_ATPManageMsgHeadInfoSize;

	int nCount = 0;
	pHead->nItem = nRet;
	memcpy(*ppOutData,(char *)pHead,nHead);
	int i = 0;
	nCount = nHead;
	for (i=0;i<nRet;i++)
	{
		memcpy(&(*ppOutData)[nCount],(char *)&pATPDataBaseAlgorithmGroup[i],nATPAlgorithmGroupInfoSize);
		nCount += nATPAlgorithmGroupInfoSize;
	}

	delete pATPDataBaseAlgorithmGroup;
	pATPDataBaseAlgorithmGroup = NULL;
	return nRet;
}

int CHHNetFrameProcessor_ATPManagerServer::UnCombinateFile(CHHFileCombinate *pCombinateFile,char *pData,int nLen,char *pPath)
{
	char szFileName[MAX_PATH] = {0};
	sprintf(szFileName,"%s\\CombinateText.dat",pPath);

	CFile file;
	if(!file.Open(szFileName, CFile::modeReadWrite | CFile::typeBinary | CFile::modeCreate))
	{

		return -1;//没有给文件
	}
	file.Write(pData,nLen);
	file.Close();

	int k;
	//打开合并文件 CombinateText.dat
	k = pCombinateFile->OpenCombinatedFile(szFileName);


	char szFileNameTemp[MAX_PATH] = {0};
	char *ptr = NULL,c='\\';
	ptr = strrchr(szFileName,c);
	int nOffset = 0;
	if (ptr)
	{
		nOffset = ptr-szFileName+1;
		strncpy(szFileNameTemp,szFileName,nOffset);
	}



	if(k==TRUE)
	{	
		POSITION pos;
		HHCOMBINATEDFILE_INFO *Info;
		pos = pCombinateFile->GetFirstFilePosition();
		long lFileLen = 0, lFileDate = 0, lFileTime = 0;
		for(;pos;)
		{
			Info = (HHCOMBINATEDFILE_INFO *)pCombinateFile->GetNextFile(pos);

			ZeroMemory(&szFileNameTemp[nOffset],MAX_PATH-nOffset);
			ptr = strrchr(Info->strFileName.GetBuffer(),c);
			Info->strFileName.ReleaseBuffer();
			if (ptr)
			{
				strcat(&szFileNameTemp[nOffset],&ptr[1]);
			
			
			

			//将文件内容从合并文件中读出
			
			//char *pData = pCombinateFile->ReadFile(&ptr[1], lFileLen, lFileDate, lFileTime);
			}
			char *pData = pCombinateFile->ReadFile(Info->strFileName.GetBuffer(), lFileLen, lFileDate, lFileTime);
			Info->strFileName.ReleaseBuffer();
			if(pData)
			{	//读取成功，将数据保存为文件
				CHHDataChannelCtrl::write_HFCFile(szFileNameTemp, pData, -1, Info->lFileLen, lFileDate, lFileTime);
				
				//删除内存
				delete []pData;
			}
		}
	}
	return 0;
}

	


int CHHNetFrameProcessor_ATPManagerServer::AddAlgorithm(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPAlgorithmInfo *pAlgoInfo			= (stru_ATPAlgorithmInfo *)pData;
	struATPDataBaseAlgorithm _DataBaseAlgorithm = {0};

	int nAlgorithmParamBlock					= 0;	
	int nAlgorithmParamEXBlock					= 0;
	int nATPAlgorithmInfoSize					= sizeof stru_ATPAlgorithmInfo;		//网络包)结构体长度

	
	nAlgorithmParamBlock						= pAlgoInfo->AlgorithmParamBlock.nItems*pAlgoInfo->AlgorithmParamBlock.nItemSize;
	nAlgorithmParamEXBlock						= pAlgoInfo->AlgorithmParamEXBlock.nItems*pAlgoInfo->AlgorithmParamEXBlock.nItemSize;
	_DataBaseAlgorithm.pATPAlgorithmParams = NULL;
	if (pAlgoInfo->AlgorithmParamBlock.nItems>0)
	{
		_DataBaseAlgorithm.pATPAlgorithmParams		= new struATPDataBaseAlgorithmParam[pAlgoInfo->AlgorithmParamBlock.nItems];
	}
	_DataBaseAlgorithm.pATPAlgorithmParamsEX = NULL;
	if (pAlgoInfo->AlgorithmParamEXBlock.nItems>0)
	{
		_DataBaseAlgorithm.pATPAlgorithmParamsEX		= new struATPDataBaseAlgorithmParamEX[pAlgoInfo->AlgorithmParamEXBlock.nItems];
	}
	


	//////////////////////////////////////////////////////////////////////////
	char szAlgoType[MAX_PATH]={0};
	switch(pAlgoInfo->nAlgoType)
	{
	case 1:
		{
			//策略
			strcpy(szAlgoType,"Strategy");
		}
		break;
	case 2:
		{
			//选股条件
			strcpy(szAlgoType,"Condition");
		}
		break;
	case 3:
		{
			//选股方案
			strcpy(szAlgoType,"Program");
		}
		break;
	default:
		//算法
		strcpy(szAlgoType,"Algo");
		break;
	}
	char szPath[MAX_PATH]={0};
	sprintf(szPath,"..\\SysAlgo\\%s\\%s\\%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",m_szAccount,szAlgoType,
		pAlgoInfo->AlgorithmID.Data1, pAlgoInfo->AlgorithmID.Data2, pAlgoInfo->AlgorithmID.Data3, pAlgoInfo->AlgorithmID.Data4[0], 
		pAlgoInfo->AlgorithmID.Data4[1], pAlgoInfo->AlgorithmID.Data4[2], pAlgoInfo->AlgorithmID.Data4[3], pAlgoInfo->AlgorithmID.Data4[4], 
		pAlgoInfo->AlgorithmID.Data4[5], pAlgoInfo->AlgorithmID.Data4[6], pAlgoInfo->AlgorithmID.Data4[7]);
	ASSERT(_CrtCheckMemory());
	{
		//_DataBaseAlgorithm.nSerialNumber		= pAlgoInfo->nSerialNumber;
		memcpy((char*)&_DataBaseAlgorithm.AlgorithmID,(char*)&pAlgoInfo->AlgorithmID,sizeof GUID);							//	guid 唯一
		strncpy(_DataBaseAlgorithm.szAlgorithmName,pAlgoInfo->szAlgorithmName, sizeof _DataBaseAlgorithm.szAlgorithmName);	//	算法名
		memcpy((char*)&_DataBaseAlgorithm.AlgorithVer,(char*)&pAlgoInfo->AlgorithVer,sizeof struDataBaseAlgorithmVer);		//	算法版本
		_DataBaseAlgorithm.nVersionAttribute	= pAlgoInfo->nVersionAttribute;												//	算法版本属性 测试版之类
		_DataBaseAlgorithm.nCharge				= pAlgoInfo->nCharge;														//	是否收费
		_DataBaseAlgorithm.nAlgoType			= pAlgoInfo->nAlgoType;														//	算法类型
		_DataBaseAlgorithm.nGroupID				= pAlgoInfo->nGroupID;														//	算法组
		_DataBaseAlgorithm.nMarketType			= pAlgoInfo->nMarketType;
		_DataBaseAlgorithm.nLanguageType		= pAlgoInfo->nLanguageType;													//	市场类型
		strncpy(_DataBaseAlgorithm.szExplain,pAlgoInfo->szExplain,sizeof _DataBaseAlgorithm.szExplain);						//	算法说明
		strncpy(_DataBaseAlgorithm.szWarning,pAlgoInfo->szWarning,sizeof _DataBaseAlgorithm.szWarning);						//	算法警告
		strncpy(_DataBaseAlgorithm.szKeyword,pAlgoInfo->szKeyword,sizeof _DataBaseAlgorithm.szKeyword);						//	算法关键字
		_DataBaseAlgorithm.nStatus				= pAlgoInfo->nStatus;														//	算法状态
		strncpy(_DataBaseAlgorithm.szStopReason, pAlgoInfo->szStopReason,sizeof  _DataBaseAlgorithm.szStopReason);			//	算法禁用原因
		CTime t = CTime::GetCurrentTime();
		_DataBaseAlgorithm.nCreateDate			= t.GetYear()*10000+t.GetMonth()*100+t.GetDay();							//	算法发布日期
		_DataBaseAlgorithm.nCreateTime			= t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();						//	算法发布时间
		strncpy(_DataBaseAlgorithm.szMainDllName, pAlgoInfo->szMainDllName, sizeof _DataBaseAlgorithm.szMainDllName);
		strncpy(_DataBaseAlgorithm.szPath, szPath, MAX_PATH);																//	算法使用路径,路径要指定
		_DataBaseAlgorithm.nParams				= pAlgoInfo->AlgorithmParamBlock.nItems;									//	算法参数个数
		if (_DataBaseAlgorithm.pATPAlgorithmParams)
		{
			memcpy((char *)_DataBaseAlgorithm.pATPAlgorithmParams,(char *)&pData[nATPAlgorithmInfoSize],nAlgorithmParamBlock);		//	算法参数
		}
		
		_DataBaseAlgorithm.nParamsEx			= pAlgoInfo->AlgorithmParamEXBlock.nItems;
		if (_DataBaseAlgorithm.pATPAlgorithmParamsEX)
		{
			memcpy((char *)_DataBaseAlgorithm.pATPAlgorithmParamsEX,(char *)&pData[nATPAlgorithmInfoSize+nAlgorithmParamBlock],nAlgorithmParamEXBlock);
		}
		
		_DataBaseAlgorithm.nDeleteMark			= pAlgoInfo->nDeleteMark;												//	删除标记
		strcpy(_DataBaseAlgorithm.szManagerID,m_szAccount);
	}
	ASSERT(_CrtCheckMemory());
	//////////////////////////////////////////////////////////////////////////
	
	struATPDataBaseAlgorithm _ATPDBSAlgorithm	= {0};
	int nRet = g_pATPFileDBApi->AddAlgorithm(&_DataBaseAlgorithm,&_ATPDBSAlgorithm);

	if (_DataBaseAlgorithm.pATPAlgorithmParams)
	{
		delete _DataBaseAlgorithm.pATPAlgorithmParams;_DataBaseAlgorithm.pATPAlgorithmParams = NULL;
	}
	if (_DataBaseAlgorithm.pATPAlgorithmParamsEX)
	{
		delete _DataBaseAlgorithm.pATPAlgorithmParamsEX;_DataBaseAlgorithm.pATPAlgorithmParamsEX = NULL;
	}
	
	

	

	if (nRet < 0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"添加算法(NAME/GUID):%s 失败-传入数据为NULL",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case EXISTGUID:
		case EXISTDATA:
			sprintf(sz,"添加算法(NAME/GUID):%s 失败-该算法已经存在",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case NEWERROR:
			sprintf(sz,"添加算法(NAME/GUID):%s 失败-NEW出错",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case NULLHANDLE:
			sprintf(sz,"添加算法(NAME/GUID):%s 失败-操作句柄为NULL",_DataBaseAlgorithm.szAlgorithmName);
			break;
		//	case 0:
		case ZERORECORD:
			sprintf(sz,"添加算法(NAME/GUID):%s 失败-没有该记录",_DataBaseAlgorithm.szAlgorithmName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_ADDALGORITHM,m_szAccount,sz);
		return nRet;
	}
	
	if (nRet>0)
	{
		_ATPDBSAlgorithm.AlgorithVer.Ver[3] = nRet;
		nRet = 0;
	}


	ZeroMemory(szPath,MAX_PATH);
	sprintf(szPath,"..\\SysAlgo\\%s\\%s\\%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X\\%d.%d.%d.%d",m_szAccount,szAlgoType,
		pAlgoInfo->AlgorithmID.Data1, pAlgoInfo->AlgorithmID.Data2, pAlgoInfo->AlgorithmID.Data3, pAlgoInfo->AlgorithmID.Data4[0], 
		pAlgoInfo->AlgorithmID.Data4[1], pAlgoInfo->AlgorithmID.Data4[2], pAlgoInfo->AlgorithmID.Data4[3], pAlgoInfo->AlgorithmID.Data4[4], 
		pAlgoInfo->AlgorithmID.Data4[5], pAlgoInfo->AlgorithmID.Data4[6], pAlgoInfo->AlgorithmID.Data4[7],_ATPDBSAlgorithm.AlgorithVer.Ver[0],
		_ATPDBSAlgorithm.AlgorithVer.Ver[1],_ATPDBSAlgorithm.AlgorithVer.Ver[2],_ATPDBSAlgorithm.AlgorithVer.Ver[3]);
	//strcpy(szPath,"..\\%s\\%d-%d-%d-%s",m_szAccount,);
	
	//////////////////////////////////////////////////////////////////////////
	//创建目录
	char *ptr = NULL,*ptr2 = NULL;
	char c = '\\';
	ptr = strchr(szPath,c);
	char szT[MAX_PATH]={0};
	while (ptr)
	{
		if (ptr2)
		{
			ptr = strchr(&ptr[1],c);
		}
		ptr2 = strchr(&ptr[1],c);
		if (ptr2)
		{
			strncpy(szT,szPath,ptr2-szPath);
			mkdir(szT);
		}
		else
		{
			strcpy(szT,szPath);
			mkdir(szT);
			break;
		}
	}
	//////////////////////////////////////////////////////////////////////////

	// 添加成功　　把文件保存到硬盘
	CHHFileCombinate _Combinate;
	UnCombinateFile(&_Combinate,(char *)&pData[nATPAlgorithmInfoSize+nAlgorithmParamBlock+nAlgorithmParamEXBlock],nLen-(nATPAlgorithmInfoSize+nAlgorithmParamBlock+nAlgorithmParamEXBlock),szPath);



	//////////////////////////////////////////////////////////////////////////
	stru_ATPAlgorithmInfo _ATPAlgorithmInfo = {0};

	{
		_ATPAlgorithmInfo.nSerialNumber						= _ATPDBSAlgorithm.nSerialNumber;								//	自动增长
		memcpy((char *)&_ATPAlgorithmInfo.AlgorithmID,(char *)&_ATPDBSAlgorithm.AlgorithmID,sizeof GUID);					//	guid 唯一
		strcpy((char *)_ATPAlgorithmInfo.szAlgorithmName,(char *)_ATPDBSAlgorithm.szAlgorithmName);							//	算法名
		memcpy((char *)&_ATPAlgorithmInfo.AlgorithVer,(char *)&_ATPDBSAlgorithm.AlgorithVer,sizeof struDataBaseAlgorithmVer);				//	算法版本
		_ATPAlgorithmInfo.nVersionAttribute					= _ATPDBSAlgorithm.nVersionAttribute;							//	算法版本属性 测试版之类
		_ATPAlgorithmInfo.nCharge							= _ATPDBSAlgorithm.nCharge;										//	是否收费
		_ATPAlgorithmInfo.nAlgoType							= _ATPDBSAlgorithm.nAlgoType;										//	算法类型
		_ATPAlgorithmInfo.nGroupID							= _ATPDBSAlgorithm.nGroupID;									//	算法组
		_ATPAlgorithmInfo.nMarketType						= _ATPDBSAlgorithm.nMarketType;
		_ATPAlgorithmInfo.nLanguageType						= _ATPDBSAlgorithm.nLanguageType;
		strcpy(_ATPAlgorithmInfo.szExplain,_ATPDBSAlgorithm.szExplain);														//	算法说明
		strcpy(_ATPAlgorithmInfo.szWarning,_ATPDBSAlgorithm.szWarning);														//	算法警告
		strcpy(_ATPAlgorithmInfo.szKeyword,_ATPDBSAlgorithm.szKeyword);														//	算法关键字
		_ATPAlgorithmInfo.nStatus							= _ATPDBSAlgorithm.nStatus;										//	算法状态
		strcpy(_ATPAlgorithmInfo.szStopReason,_ATPDBSAlgorithm.szStopReason);												//	算法禁用原因
		_ATPAlgorithmInfo.nCreateDate						= _ATPDBSAlgorithm.nCreateDate;									//	算法发布日期
		_ATPAlgorithmInfo.nCreateTime						= _ATPDBSAlgorithm.nCreateTime;									//	算法发布时间
		strcpy(_ATPAlgorithmInfo.szPath,_ATPDBSAlgorithm.szPath);															//	算法使用路径,路径要指定
		_ATPAlgorithmInfo.AlgorithmParamBlock.nItems		= _ATPDBSAlgorithm.nParams;										//	算法参数个数  算法参数
		_ATPAlgorithmInfo.AlgorithmParamBlock.nItemSize		= sizeof struATPDataBaseAlgorithmParam;
		_ATPAlgorithmInfo.AlgorithmParamEXBlock.nItems		= _ATPDBSAlgorithm.nParamsEx;
		_ATPAlgorithmInfo.AlgorithmParamEXBlock.nItemSize	= sizeof struATPDataBaseAlgorithmParamEX;
		_ATPAlgorithmInfo.nDeleteMark						= _ATPDBSAlgorithm.nDeleteMark;									//	删除标志
	}
	//////////////////////////////////////////////////////////////////////////
	nAlgorithmParamBlock									= _ATPAlgorithmInfo.AlgorithmParamBlock.nItems*_ATPAlgorithmInfo.AlgorithmParamBlock.nItemSize;
	nAlgorithmParamEXBlock									= _ATPAlgorithmInfo.AlgorithmParamEXBlock.nItems*_ATPAlgorithmInfo.AlgorithmParamEXBlock.nItemSize;

	*pnLen = g_stru_ATPManageMsgHeadInfoSize + nATPAlgorithmInfoSize + nAlgorithmParamBlock + nAlgorithmParamEXBlock;
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"添加算法(NAME/GUID):%s 成功-NEW出错",_DataBaseAlgorithm.szAlgorithmName);
		AddOperateLog(ID_ATPMANAGE_ADDALGORITHM,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"添加算法(NAME/GUID):%s 成功",_DataBaseAlgorithm.szAlgorithmName);
	AddOperateLog(ID_ATPMANAGE_ADDALGORITHM,m_szAccount,sz);
	pHead->nItem = 1;
	int nCount = 0;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	nCount += g_stru_ATPManageMsgHeadInfoSize;
	memcpy((char *)&((*ppOutData)[nCount]),(char *)&_ATPAlgorithmInfo,nATPAlgorithmInfoSize);
	nCount += nATPAlgorithmInfoSize;
	if (_ATPDBSAlgorithm.pATPAlgorithmParams)
	{
		memcpy((char *)&((*ppOutData)[nCount]),(char *)_ATPDBSAlgorithm.pATPAlgorithmParams,nAlgorithmParamBlock);
		nCount += nAlgorithmParamBlock;
	}
	
	if (_ATPDBSAlgorithm.pATPAlgorithmParamsEX)
	{
		memcpy((char *)&((*ppOutData)[nCount]),(char *)_ATPDBSAlgorithm.pATPAlgorithmParamsEX,nAlgorithmParamEXBlock);
	}
	
	
	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::ModifyAlgorithm(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPAlgorithmInfo *pAlgoInfo			= (stru_ATPAlgorithmInfo *)pData;
	struATPDataBaseAlgorithm _DataBaseAlgorithm	= {0};

	int nAlgorithmParamBlock					= 0;
	int nAlgorithmParamEXBlock					= 0;									//算法块
	
	int nATPUserInfoSize	= sizeof stru_ATPAlgorithmInfo;



	{
		nAlgorithmParamBlock						= pAlgoInfo->AlgorithmParamBlock.nItems*pAlgoInfo->AlgorithmParamBlock.nItemSize;	
		nAlgorithmParamEXBlock						= pAlgoInfo->AlgorithmParamEXBlock.nItems*pAlgoInfo->AlgorithmParamEXBlock.nItemSize;
		_DataBaseAlgorithm.pATPAlgorithmParams = NULL;
		if (pAlgoInfo->AlgorithmParamBlock.nItems>0)
		{
			_DataBaseAlgorithm.pATPAlgorithmParams		= new struATPDataBaseAlgorithmParam[pAlgoInfo->AlgorithmParamBlock.nItems];
		}
		_DataBaseAlgorithm.pATPAlgorithmParamsEX = NULL;
		if (pAlgoInfo->AlgorithmParamEXBlock.nItems>0)
		{
			_DataBaseAlgorithm.pATPAlgorithmParamsEX	= new struATPDataBaseAlgorithmParamEX[pAlgoInfo->AlgorithmParamEXBlock.nItems];
		}
		
		
		
		_DataBaseAlgorithm.nSerialNumber			= pAlgoInfo->nSerialNumber;										//	自动增长 唯一
		memcpy((char *)&_DataBaseAlgorithm.AlgorithVer,(char *)&pAlgoInfo->AlgorithVer,sizeof stru_AlgorithmVer);	//	算法版本
		_DataBaseAlgorithm.nVersionAttribute		= pAlgoInfo->nVersionAttribute;									//	算法版本属性 测试版之类
		_DataBaseAlgorithm.nCharge					= pAlgoInfo->nCharge;											//	是否收费
		_DataBaseAlgorithm.nAlgoType					= pAlgoInfo->nAlgoType;											//	
		_DataBaseAlgorithm.nGroupID					= pAlgoInfo->nGroupID;											//	算法组
		_DataBaseAlgorithm.nMarketType				= pAlgoInfo->nMarketType;
		_DataBaseAlgorithm.nLanguageType			= pAlgoInfo->nLanguageType;
		strcpy(_DataBaseAlgorithm.szExplain,pAlgoInfo->szExplain);													//	算法说明
		strcpy(_DataBaseAlgorithm.szWarning,pAlgoInfo->szWarning);													//	算法警告
		strcpy(_DataBaseAlgorithm.szKeyword,pAlgoInfo->szKeyword);													//	算法关键字
		_DataBaseAlgorithm.nStatus					= pAlgoInfo->nStatus;											//	算法状态
		strcpy(_DataBaseAlgorithm.szStopReason,pAlgoInfo->szStopReason);											//	算法禁用原因
		_DataBaseAlgorithm.nParams = pAlgoInfo->AlgorithmParamBlock.nItems;											//	算法参数个数
		if (_DataBaseAlgorithm.pATPAlgorithmParams)
		{
			memcpy((char *)_DataBaseAlgorithm.pATPAlgorithmParams,&pData[nATPUserInfoSize],nAlgorithmParamBlock);	//	算法参数
		}
		
		_DataBaseAlgorithm.nParamsEx				= pAlgoInfo->AlgorithmParamEXBlock.nItems;
		if (_DataBaseAlgorithm.pATPAlgorithmParamsEX)
		{
			memcpy((char *)_DataBaseAlgorithm.pATPAlgorithmParamsEX,&pData[nATPUserInfoSize+nAlgorithmParamBlock],nAlgorithmParamEXBlock);
		}
		
		_DataBaseAlgorithm.nDeleteMark = pAlgoInfo->nDeleteMark;					//	删除标记


		
	}
	//////////////////////////////////////////////////////////////////////////

	int nRet = g_pATPFileDBApi->ModifyAlgorithm(&_DataBaseAlgorithm);

	if (_DataBaseAlgorithm.pATPAlgorithmParams)
	{
		delete _DataBaseAlgorithm.pATPAlgorithmParams;_DataBaseAlgorithm.pATPAlgorithmParams = NULL;
	}
	if (_DataBaseAlgorithm.pATPAlgorithmParamsEX)
	{
		delete _DataBaseAlgorithm.pATPAlgorithmParamsEX;_DataBaseAlgorithm.pATPAlgorithmParamsEX = NULL;
	}
	

	//////////////////////////////////////////////////////////////////////////
	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;

	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"修改成功");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"修改算法(NAME/GUID):%s 失败-传入数据为NULL",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case EXISTGUID:
		case EXISTDATA:
			sprintf(sz,"修改算法(NAME/GUID):%s 失败-该算法已经存在",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case NEWERROR:
			sprintf(sz,"修改算法(NAME/GUID):%s 失败-NEW出错",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case NULLHANDLE:
			sprintf(sz,"修改算法(NAME/GUID):%s 失败-操作句柄为NULL",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case ZERORECORD:
			sprintf(sz,"修改算法(NAME/GUID):%s 失败-没有该记录",_DataBaseAlgorithm.szAlgorithmName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_MODIFYALGORITHMINFO,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"修改失败");
	}


	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"修改算法(NAME/GUID):%s 成功-NEW出错",_DataBaseAlgorithm.szAlgorithmName);
		AddOperateLog(ID_ATPMANAGE_MODIFYALGORITHMINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"修改算法(NAME/GUID):%s 成功",_DataBaseAlgorithm.szAlgorithmName);
	AddOperateLog(ID_ATPMANAGE_MODIFYALGORITHMINFO,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::DelAlgorithm(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPAlgorithmInfo *pAlgoInfo			= (stru_ATPAlgorithmInfo *)pData;
	struATPDataBaseAlgorithm _DataBaseAlgorithm	= {0};

	int nAlgorithmParamBlock					= 0;
	int nAlgorithmParamEXBlock					= 0;									//算法块

	int nATPUserInfoSize	= sizeof stru_ATPAlgorithmInfo;



	{
		nAlgorithmParamBlock						= pAlgoInfo->AlgorithmParamBlock.nItems*pAlgoInfo->AlgorithmParamBlock.nItemSize;	
		nAlgorithmParamEXBlock						= pAlgoInfo->AlgorithmParamEXBlock.nItems*pAlgoInfo->AlgorithmParamEXBlock.nItemSize;
		_DataBaseAlgorithm.pATPAlgorithmParams = NULL;
		if (pAlgoInfo->AlgorithmParamBlock.nItems>0)
		{
			_DataBaseAlgorithm.pATPAlgorithmParams		= new struATPDataBaseAlgorithmParam[pAlgoInfo->AlgorithmParamBlock.nItems];
		}
		_DataBaseAlgorithm.pATPAlgorithmParamsEX = NULL;
		if (pAlgoInfo->AlgorithmParamEXBlock.nItems>0)
		{
			_DataBaseAlgorithm.pATPAlgorithmParamsEX	= new struATPDataBaseAlgorithmParamEX[pAlgoInfo->AlgorithmParamEXBlock.nItems];
		}
		
		

		_DataBaseAlgorithm.nSerialNumber			= pAlgoInfo->nSerialNumber;										//	自动增长 唯一
		memcpy((char *)&_DataBaseAlgorithm.AlgorithmID,(char *)&pAlgoInfo->AlgorithmID,sizeof GUID);				//	guid 唯一
		strcpy(_DataBaseAlgorithm.szAlgorithmName,pAlgoInfo->szAlgorithmName);										//	算法名
		memcpy((char *)&_DataBaseAlgorithm.AlgorithVer,(char *)&pAlgoInfo->AlgorithVer,sizeof stru_AlgorithmVer);	//	算法版本
		_DataBaseAlgorithm.nVersionAttribute		= pAlgoInfo->nVersionAttribute;									//	算法版本属性 测试版之类
		_DataBaseAlgorithm.nCharge					= pAlgoInfo->nCharge;											//	是否收费
		_DataBaseAlgorithm.nAlgoType					= pAlgoInfo->nAlgoType;											//	是否收费
		_DataBaseAlgorithm.nGroupID					= pAlgoInfo->nGroupID;											//	算法组
		_DataBaseAlgorithm.nMarketType				= pAlgoInfo->nMarketType;
		_DataBaseAlgorithm.nLanguageType			= pAlgoInfo->nLanguageType;
		strcpy(_DataBaseAlgorithm.szExplain,pAlgoInfo->szExplain);													//	算法说明
		strcpy(_DataBaseAlgorithm.szWarning,pAlgoInfo->szWarning);													//	算法警告
		strcpy(_DataBaseAlgorithm.szKeyword,pAlgoInfo->szKeyword);													//	算法关键字
		_DataBaseAlgorithm.nStatus					= pAlgoInfo->nStatus;											//	算法状态
		strcpy(_DataBaseAlgorithm.szStopReason,pAlgoInfo->szStopReason);											//	算法禁用原因
		_DataBaseAlgorithm.nCreateDate				= pAlgoInfo->nCreateDate;										//	算法发布日期
		_DataBaseAlgorithm.nCreateTime				= pAlgoInfo->nCreateTime;										//	算法发布时间
		strcpy(_DataBaseAlgorithm.szPath,pAlgoInfo->szPath);														//	算法使用路径,路径要指定
		strcpy(_DataBaseAlgorithm.szMainDllName,pAlgoInfo->szMainDllName);											//	算法入口dll文件名
		_DataBaseAlgorithm.nParams					= pAlgoInfo->AlgorithmParamBlock.nItems;						//	算法参数个数
		if (_DataBaseAlgorithm.pATPAlgorithmParams)
		{
			memcpy((char *)_DataBaseAlgorithm.pATPAlgorithmParams,&pData[nATPUserInfoSize],nAlgorithmParamBlock);	//	算法参数
		}
		
		_DataBaseAlgorithm.nParamsEx				= pAlgoInfo->AlgorithmParamEXBlock.nItems;
		if (_DataBaseAlgorithm.pATPAlgorithmParamsEX)
		{
			memcpy((char *)_DataBaseAlgorithm.pATPAlgorithmParamsEX,&pData[nATPUserInfoSize+nAlgorithmParamBlock],nAlgorithmParamEXBlock);
		}
		
		_DataBaseAlgorithm.nDeleteMark				= pAlgoInfo->nDeleteMark;										//	删除标记



	}
	//////////////////////////////////////////////////////////////////////////

	int nRet = g_pATPFileDBApi->DelAlgorithm(&_DataBaseAlgorithm);

	if (_DataBaseAlgorithm.pATPAlgorithmParams)
	{
		delete _DataBaseAlgorithm.pATPAlgorithmParams;_DataBaseAlgorithm.pATPAlgorithmParams = NULL;
	}
	if (_DataBaseAlgorithm.pATPAlgorithmParamsEX)
	{
		delete _DataBaseAlgorithm.pATPAlgorithmParamsEX;_DataBaseAlgorithm.pATPAlgorithmParamsEX = NULL;
	}
	
	



	//////////////////////////////////////////////////////////////////////////
	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;

	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"删除成功");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"删除算法(NAME/GUID):%s 失败-传入数据为NULL",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case EXISTGUID:
		case EXISTDATA:
			sprintf(sz,"删除算法(NAME/GUID):%s 失败-该算法已经存在",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case NEWERROR:
			sprintf(sz,"删除算法(NAME/GUID):%s 失败-NEW出错",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case NULLHANDLE:
			sprintf(sz,"删除算法(NAME/GUID):%s 失败-操作句柄为NULL",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case ZERORECORD:
			sprintf(sz,"删除算法(NAME/GUID):%s 失败-没有该记录",_DataBaseAlgorithm.szAlgorithmName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_DELETEALGORITHM,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"删除失败");
	}


	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"删除算法(NAME/GUID):%s 成功-NEW出错",_DataBaseAlgorithm.szAlgorithmName);
		AddOperateLog(ID_ATPMANAGE_DELETEALGORITHM,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"删除算法(NAME/GUID):%s 成功",_DataBaseAlgorithm.szAlgorithmName);
	AddOperateLog(ID_ATPMANAGE_DELETEALGORITHM,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::QueryAlgorithm(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseAlgorithm *pATPDataBaseAlgorithm				= NULL;
	struATPDataBaseAlgorithm_QUERY *pATPDataBaseAlgorithm_QUERY	= (struATPDataBaseAlgorithm_QUERY *)pData;
	int nATPAlgorithmInfoSize									= sizeof stru_ATPAlgorithmInfo;
	int nATPDataBaseAlgorithmParamSize							= sizeof struATPDataBaseAlgorithmParam;
	int nATPDataBaseAlgorithmParamEXSize						= sizeof struATPDataBaseAlgorithmParamEX;
	//nRet 查询结果条数
	int nRet = g_pATPFileDBApi->QueryAlgorithm(pATPDataBaseAlgorithm_QUERY,m_szAccount,&pATPDataBaseAlgorithm);

	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"查询算法 失败-传入数据为NULL");
			break;
		case EXISTGUID:
		case EXISTDATA:
			sprintf(sz,"查询算法 失败-该算法已经存在");
			break;
		case NEWERROR:
			sprintf(sz,"查询算法 失败-NEW出错");
			break;
		case NULLHANDLE:
			sprintf(sz,"查询算法 失败-操作句柄为NULL");
			break;
			case 0:
		case ZERORECORD:
			sprintf(sz,"查询算法 成功-没有该记录");
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_QUERYALGORITHMINFO,m_szAccount,sz);
		return nRet;
	}

	int i = 0;
	*pnLen  = g_stru_ATPManageMsgHeadInfoSize;
	for (;i<nRet;i++)
	{
		if (pATPDataBaseAlgorithm[i].nDeleteMark == TRUE)
		{
			continue;
		}
		(*pnLen) += nATPAlgorithmInfoSize+pATPDataBaseAlgorithm[i].nParams*nATPDataBaseAlgorithmParamSize + pATPDataBaseAlgorithm[i].nParamsEx*nATPDataBaseAlgorithmParamEXSize;
	}

	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"查询算法 成功-NEW出错");
		AddOperateLog(ID_ATPMANAGE_QUERYALGORITHMINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"查询算法 成功");
	AddOperateLog(ID_ATPMANAGE_QUERYALGORITHMINFO,m_szAccount,sz);
	stru_ATPAlgorithmInfo _ManagerInfo		= {0};
	int nAlgorithmParamBlock				= 0;
	int nAlgorithmParamEXBlock				= 0;									//算法块

	int nHead								= g_stru_ATPManageMsgHeadInfoSize;

	int nCount								= 0;
	pHead->nItem							= nRet;
	memcpy(*ppOutData,(char *)pHead,nHead);
	nCount									= nHead;
	for (i=0;i<nRet;i++)
	{
		if (pATPDataBaseAlgorithm[i].nDeleteMark == TRUE)
		{
			continue;
		}
		_ManagerInfo.nSerialNumber						= pATPDataBaseAlgorithm[i].nSerialNumber;								//	自动增长
		memcpy((char *)&_ManagerInfo.AlgorithmID,(char *)&pATPDataBaseAlgorithm[i].AlgorithmID,sizeof GUID);					//	guid 唯一
		strcpy(_ManagerInfo.szAlgorithmName,pATPDataBaseAlgorithm[i].szAlgorithmName);											//	算法名
		memcpy((char *)&_ManagerInfo.AlgorithVer,(char *)&pATPDataBaseAlgorithm[i].AlgorithVer,sizeof struDataBaseAlgorithmVer);				//	算法版本
		_ManagerInfo.nVersionAttribute					= pATPDataBaseAlgorithm[i].nVersionAttribute;							//	算法版本属性 测试版之类
		_ManagerInfo.nCharge							= pATPDataBaseAlgorithm[i].nCharge;										//	是否收费
		_ManagerInfo.nAlgoType							= pATPDataBaseAlgorithm[i].nAlgoType;										//	
		_ManagerInfo.nGroupID							= pATPDataBaseAlgorithm[i].nGroupID;									//	算法组
		_ManagerInfo.nMarketType						= pATPDataBaseAlgorithm[i].nMarketType;
		_ManagerInfo.nLanguageType						= pATPDataBaseAlgorithm[i].nLanguageType;
		strcpy(_ManagerInfo.szExplain,pATPDataBaseAlgorithm[i].szExplain);														//	算法说明
		strcpy(_ManagerInfo.szWarning,pATPDataBaseAlgorithm[i].szWarning);														//	算法警告
		strcpy(_ManagerInfo.szKeyword,pATPDataBaseAlgorithm[i].szKeyword);														//	算法关键字
		_ManagerInfo.nStatus							= pATPDataBaseAlgorithm[i].nStatus;										//	算法状态
		strcpy(_ManagerInfo.szStopReason,pATPDataBaseAlgorithm[i].szStopReason);												//	算法禁用原因
		_ManagerInfo.nCreateDate						= pATPDataBaseAlgorithm[i].nCreateDate;									//	算法发布日期
		_ManagerInfo.nCreateTime						= pATPDataBaseAlgorithm[i].nCreateTime;									//	算法发布时间
		strcpy(_ManagerInfo.szMainDllName,pATPDataBaseAlgorithm[i].szMainDllName);
		strcpy(_ManagerInfo.szPath,pATPDataBaseAlgorithm[i].szPath);															//	算法使用路径,路径要指定
		_ManagerInfo.AlgorithmParamBlock.nItems			= pATPDataBaseAlgorithm[i].nParams;										//	算法参数个数  算法参数
		_ManagerInfo.AlgorithmParamBlock.nItemSize		= nATPDataBaseAlgorithmParamSize;
		_ManagerInfo.AlgorithmParamEXBlock.nItems		= pATPDataBaseAlgorithm[i].nParamsEx;
		_ManagerInfo.AlgorithmParamEXBlock.nItemSize	= nATPDataBaseAlgorithmParamEXSize;
		_ManagerInfo.nDeleteMark						= pATPDataBaseAlgorithm[i].nDeleteMark;									//	删除标志


		nAlgorithmParamBlock							= pATPDataBaseAlgorithm[i].nParams*nATPDataBaseAlgorithmParamSize;
		nAlgorithmParamEXBlock							= pATPDataBaseAlgorithm[i].nParamsEx*nATPDataBaseAlgorithmParamEXSize;
		

		memcpy(&(*ppOutData)[nCount],(char *)&_ManagerInfo,nATPAlgorithmInfoSize);
		nCount += nATPAlgorithmInfoSize;
		if (pATPDataBaseAlgorithm[i].pATPAlgorithmParams)
		{
			memcpy(&(*ppOutData)[nCount],(char*)pATPDataBaseAlgorithm[i].pATPAlgorithmParams,nAlgorithmParamBlock);
			nCount += nAlgorithmParamBlock;
		}
		
		if (pATPDataBaseAlgorithm[i].pATPAlgorithmParamsEX)
		{
			memcpy(&(*ppOutData)[nCount],(char*)pATPDataBaseAlgorithm[i].pATPAlgorithmParamsEX,nAlgorithmParamEXBlock);
			nCount += nAlgorithmParamEXBlock;
		}
		
	
	}

	delete pATPDataBaseAlgorithm;
	pATPDataBaseAlgorithm = NULL;
	return nRet;
}



int	CHHNetFrameProcessor_ATPManagerServer::AddOperateLog(int nOperateType,char *pAccount,char *pInfo)
{
	CTime t = CTime::GetCurrentTime();
	struATPDataBaseOperateLog _struATPDataBaseOperateLog = {0};
	_struATPDataBaseOperateLog.nOperateDate = t.GetYear()*10000+t.GetMonth()*100+t.GetDay();
	_struATPDataBaseOperateLog.nOperateTime = t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();
	_struATPDataBaseOperateLog.nOperateType = nOperateType;
	strcpy(_struATPDataBaseOperateLog.szActorID,pAccount);
	strcpy(_struATPDataBaseOperateLog.szInfo,pInfo);
	//////////////////////////////////////////////////////////////////////////
	int nRet = g_pATPFileDBApi->AddOperateLog(&_struATPDataBaseOperateLog);
	

	return nRet;
}


int	CHHNetFrameProcessor_ATPManagerServer::QueryOperateLog(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseOperateLog *pATPDataBaseOperateLog = NULL;
	int nATPOperateLogInfoSize = sizeof stru_ATPOperateLogInfo;
	//nRet 查询结果条数
	struATPDataBaseOperateLog_QUERY *pATPDataBaseOperateLog_QUERY = (struATPDataBaseOperateLog_QUERY *)pData;
	int nRet = g_pATPFileDBApi->QueryOperateLog(pATPDataBaseOperateLog_QUERY,&pATPDataBaseOperateLog);

	if (nRet<=0)
	{
		return nRet;
	}

	*pnLen			= g_stru_ATPManageMsgHeadInfoSize + nRet*nATPOperateLogInfoSize;
	*ppOutData		= new char[*pnLen];
	if (*ppOutData == NULL)
	{
		return -1;
	}

	int nHead		= g_stru_ATPManageMsgHeadInfoSize;

	int nCount		= 0;
	pHead->nItem	= nRet;
	memcpy(*ppOutData,(char *)pHead,nHead);
	int i			= 0;
	nCount			= nHead;
	for (i=0;i<nRet;i++)
	{
		memcpy(&(*ppOutData)[nCount],(char *)&pATPDataBaseOperateLog[i],nATPOperateLogInfoSize);
		nCount += nATPOperateLogInfoSize;

	}

	delete pATPDataBaseOperateLog;
	pATPDataBaseOperateLog = NULL;
	return nRet;
}



int	CHHNetFrameProcessor_ATPManagerServer::AddAlgorithmLog(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPAlgorithmRunLogInfo *pAlgorithmRunLogInfo			= (stru_ATPAlgorithmRunLogInfo *)pData;
	struATPDataBaseAlgorithmLog _DataBaseAlgorithmLog = {0};

	int nATPAlgorithmRunLogInfoSize = sizeof stru_ATPAlgorithmRunLogInfo;

	memcpy((char *)&_DataBaseAlgorithmLog,(char *)pAlgorithmRunLogInfo,nATPAlgorithmRunLogInfoSize);

	//////////////////////////////////////////////////////////////////////////
	int nRet = g_pATPFileDBApi->AddAlgorithmLog(&_DataBaseAlgorithmLog);
	struAns_Operate _Ans_Operate = {0};
	_Ans_Operate.nResult = TRUE;
	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"添加成功");
	}
	else
	{
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"添加失败");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		return -1;
	}
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int	CHHNetFrameProcessor_ATPManagerServer::QueryAlgorithmLog(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseAlgorithmLog *pATPDataBaseAlgorithmLog = NULL;
	int nATPOperateLogInfoSize = sizeof stru_ATPAlgorithmRunLogInfo;
	//nRet 查询结果条数
	struATPDataBaseAlgorithmLog_QUERY *pATPDataBaseAlgorithmLog_QUERY = (struATPDataBaseAlgorithmLog_QUERY *)pData;
	int nRet = g_pATPFileDBApi->QueryAlgorithmLog(pATPDataBaseAlgorithmLog_QUERY,&pATPDataBaseAlgorithmLog);

	if (nRet<=0)
	{
		return nRet;
	}

	*pnLen = g_stru_ATPManageMsgHeadInfoSize + nRet*nATPOperateLogInfoSize;
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		return -1;
	}

	int nHead	= g_stru_ATPManageMsgHeadInfoSize;

	int nCount = 0;
	pHead->nItem = nRet;
	memcpy(*ppOutData,(char *)pHead,nHead);
	int i = 0;
	nCount = nHead;
	for (i=0;i<nRet;i++)
	{
		memcpy(&(*ppOutData)[nCount],(char *)&pATPDataBaseAlgorithmLog[i],nATPOperateLogInfoSize);
		nCount += nATPOperateLogInfoSize;

	}

	delete pATPDataBaseAlgorithmLog;
	pATPDataBaseAlgorithmLog = NULL;
	return nRet;
}

void CHHNetFrameProcessor_ATPManagerServer::AddLoginList(CList <AtpVigil_Manager_UserInfo,AtpVigil_Manager_UserInfo> *pLoginList,struATPDataBaseManager *pATPDataBaseManager)
{
	AtpVigil_Manager_UserInfo _AtpVigil_Manager_UserInfo={0};
	_AtpVigil_Manager_UserInfo.uUserId = pATPDataBaseManager->nSerialNumber;		//管理员Id
	//_AtpVigil_Manager_UserInfo.nConnectId;		//连接句柄 用来标识唯一性 
	strcpy(_AtpVigil_Manager_UserInfo.chAccount,pATPDataBaseManager->szID);	//管理员账号
	strcpy(_AtpVigil_Manager_UserInfo.chStatus,"登录");  //状态说明
	//_AtpVigil_Manager_UserInfo.chInfo1[48];	//保留
	//_AtpVigil_Manager_UserInfo.chInfo2[48];	//保留
	//_AtpVigil_Manager_UserInfo.nAppType;		//保留
	_AtpVigil_Manager_UserInfo.nAppDate = pATPDataBaseManager->nLastDate;		//日期
	_AtpVigil_Manager_UserInfo.nAppTime = pATPDataBaseManager->nCreateTime;
	_AtpVigil_Manager_UserInfo.nLocalPort = m_nPort;   	//服务端口
	//_AtpVigil_Manager_UserInfo.nRemotePort;	//登录的端口
	CString str = GetLinkedIPAddress();
	_AtpVigil_Manager_UserInfo.nRemoteIP = inet_addr(GetLinkedIPAddress());  	//登录的IP
	
	g_wndMsgTransfer.SendData(ID_ATPSVC_MC,0,ID_MSG_ATPVIGIL_MANAGER_ADMINLOGIN,&_AtpVigil_Manager_UserInfo,sizeof AtpVigil_Manager_UserInfo);
	
	//////////////////////////////////////////////////////////////////////////

	pLoginList->AddTail(_AtpVigil_Manager_UserInfo);


}
void CHHNetFrameProcessor_ATPManagerServer::RemoveLoginList(CList <AtpVigil_Manager_UserInfo,AtpVigil_Manager_UserInfo> *pLoginList,struATPDataBaseManager *pATPDataBaseManager)
{
	AtpVigil_Manager_UserInfo _AtpVigil_Manager_UserInfo={0};
	_AtpVigil_Manager_UserInfo.uUserId = pATPDataBaseManager->nSerialNumber;		//管理员Id
	strcpy(_AtpVigil_Manager_UserInfo.chAccount,pATPDataBaseManager->szID);	//管理员账号
	strcpy(_AtpVigil_Manager_UserInfo.chStatus,"断开连接");  //状态说明
	_AtpVigil_Manager_UserInfo.nAppDate = pATPDataBaseManager->nLastDate;		//日期
	_AtpVigil_Manager_UserInfo.nAppTime = pATPDataBaseManager->nCreateTime;
	_AtpVigil_Manager_UserInfo.nLocalPort = m_nPort;   	//服务端口
	_AtpVigil_Manager_UserInfo.nRemoteIP = inet_addr(GetLinkedIPAddress());  	//登录的IP

	g_wndMsgTransfer.SendData(ID_ATPSVC_MC,0,ID_MSG_ATPVIGIL_MANAGER_UNCONNECT,&_AtpVigil_Manager_UserInfo,sizeof AtpVigil_Manager_UserInfo);

	//////////////////////////////////////////////////////////////////////////

	POSITION pos = pLoginList->GetHeadPosition();
	while(pos)
	{
		_AtpVigil_Manager_UserInfo = pLoginList->GetAt(pos);
		if (0==strcmp(_AtpVigil_Manager_UserInfo.chAccount,m_szAccount))
		{
			pLoginList->RemoveAt(pos);
			break;
		}
		pLoginList->GetNext(pos);
	}
}


int CHHNetFrameProcessor_ATPManagerServer::ManagerLogin(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struReq_ATPManageLogin *pATPManageLogin = (struReq_ATPManageLogin *)pData;
	int nRet = 0;
	nRet = g_pATPFileDBApi->ManagerLogin(pATPManageLogin);

	struAns_Operate _Ans_Operate = {0};
	
	if (nRet == 0)
	{
		strcpy(_Ans_Operate.szInfo,"登录成功");
		_Ans_Operate.nResult = TRUE;
		strcpy(m_szAccount,pATPManageLogin->szLoginID);

	}
	else
	{
		_Ans_Operate.nResult = FALSE;
		if (nRet == -1)
		{
			strcpy(_Ans_Operate.szInfo,"密码错误");
		} 
		else//-2
		{
			strcpy(_Ans_Operate.szInfo,"帐户不存在");
		}
		
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		return -1;
	}
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//复制到输出数据内存中
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}