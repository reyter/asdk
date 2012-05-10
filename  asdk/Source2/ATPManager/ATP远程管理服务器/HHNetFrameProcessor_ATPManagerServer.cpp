// HHNetFrameProcessor_ATPManagerServer.cpp : ʵ���ļ�
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
	//�����Ͽ�
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
	//nRet ��ѯ�������
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
	//���ճ��Ȳ���С����Ϣ��ͷ����
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

	BOOL bWrongWayLogin = FALSE;//��¼��ʽ�Ĵ���

	if (0 == strlen(m_szAccount))
	{
		//�û�û�е�¼
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
			//����ĵ�¼��ʽ����
			if (bWrongWayLogin)
			{
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				break;
			}
			
			int nRet = ManagerLogin(&_MsgHeadInfo,&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize,&pSendData,&nSendLen);

			struReq_ATPManageLogin *pATPManageLogin = (struReq_ATPManageLogin *)&lpRecv[g_stru_ATPManageMsgHeadInfoSize];
			//��¼�ɹ�
			if (0 == nRet)
			{
				AddOperateLog(ID_ATPMANAGE_LOGIN,m_szAccount,"��¼�ɹ�");
				//////////////////////////////////////////////////////////////////////////
				//д���¼����
				//g_pATPFileDBApi->
				//AddLoginList(g_pATPFileDBApi->GetLoginList());
				struATPDataBaseManager *pATPDataBaseManager = NULL;
				//nRet ��ѯ�������
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
				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYMANAGERINFO;//��ѯ����Ա
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYSERVERGROUPINFO;//��ѯ��������
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
				struReq_ATPServerInfo_QUERY _ServerInfo_QUERY = {0};
				//ͨ����������ID��ѯ��������Ϊ�����ѯȫ��
				_ServerInfo_QUERY.nGroupID = 0;
				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYSERVERINFO;//��ѯȫ��������
				nLenT = g_stru_ATPManageMsgHeadInfoSize+sizeof struReq_ATPServerInfo_QUERY;
				//char szReqServer[nLenT];
				ZeroMemory(szReq,1024);
				memcpy(szReq,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				memcpy(&szReq[g_stru_ATPManageMsgHeadInfoSize],(char *)&_ServerInfo_QUERY,sizeof struReq_ATPServerInfo_QUERY);
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)szReq,nLenT,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYPERMISSIONINFO;//��ѯȨ��
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYALGORITHMGROUPINFO;//��ѯ�㷨��
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
				struReq_ATPAlgorithm_QUERY _Algorithm_QUERY = {0};
				_Algorithm_QUERY.nGroupID = 0;

				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYALGORITHMINFO;//��ѯȫ���㷨��Ϣ
				nLenT = g_stru_ATPManageMsgHeadInfoSize+sizeof struReq_ATPAlgorithm_QUERY;
				//char szReqAlgo[nLenT];
				ZeroMemory(szReq,1024);
				memcpy(szReq,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
				memcpy(&szReq[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Algorithm_QUERY,sizeof struReq_ATPAlgorithm_QUERY);
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)szReq,nLenT,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYUSERGROUPINFO;//��ѯ�û���
				OnReceiveData(strSrcDN,strDesDN,strSendDesDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize,nID,nIDSend,bDelRecv,lpSend,bDelSend,nFlags,nErrLen);
				//////////////////////////////////////////////////////////////////////////
				struReq_ATPUserInfo_QUERY _UserInfo_QUERY = {0};
				_UserInfo_QUERY.nGroupID = 0;

				_MsgHeadInfo.nMsgType = ID_ATPMANAGE_QUERYUSERINFO;//��ѯȫ���û�
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
				AddOperateLog(ID_ATPMANAGE_LOGIN,pATPManageLogin->szLoginID,"�������");
			}
			else if (-2 == nRet)
			{
				AddOperateLog(ID_ATPMANAGE_LOGIN,pATPManageLogin->szLoginID,"�ʺŲ�����");
			}

			if (pSendData)
			{
				//���ص�¼���
				CHHNetFrameProcessor::Send(strSrcDN,pSendData,nSendLen);
				delete []pSendData;
			}
			else
			{	
				CHHNetFrameProcessor::Send(strSrcDN,(char *)&_MsgHeadInfo,g_stru_ATPManageMsgHeadInfoSize);
			}
		}
		break;
	case ID_ATPMANAGE_CREATEMANAGER:					//50021	��������Ա(��������Ա)
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
	case ID_ATPMANAGE_DELETEMANAGER:					//50022	ɾ������Ա(��������Ա)
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
	case ID_ATPMANAGE_MODIFYMANAGER:					//50023	�޸Ĺ���Ա(��������Ա������Ա)
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
	case ID_ATPMANAGE_QUERYMANAGERINFO:				//50024	��ѯ����Ա(��������Ա)
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
	case ID_ATPMANAGE_CREATESERVERGROUP:			//50031	������������(��������Ա)
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
	case ID_ATPMANAGE_DELETESERVERGROUP:			//50032	ɾ����������(��������Ա)
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
	case ID_ATPMANAGE_MODIFYSERVERGROUP:			//50033	�޸ķ�������(��������Ա)
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
	case ID_ATPMANAGE_QUERYSERVERGROUPINFO:			//50034	��ѯ��������(��������Ա)
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
	case ID_ATPMANAGE_CREATESERVER:					//50041	����������(��������Ա)
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
	case ID_ATPMANAGE_DELETESERVER:					//50042	ɾ��������(��������Ա)
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
	case ID_ATPMANAGE_MODIFYSERVER:					//50043	�޸ķ�����(��������Ա)
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
	case ID_ATPMANAGE_QUERYSERVERINFO:				//50044	��ѯ������(��������Ա)
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
	case ID_ATPMANAGE_QUERYPERMISSIONINFO:			//50051	��ѯȨ��(��������Ա������Ա)
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
	case ID_ATPMANAGE_ADDALGORITHMGROUP:			//51011	����㷨��(����Ա)
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
	case ID_ATPMANAGE_DELETEALGORITHMGROUP:			//51012	ɾ���㷨��(����Ա)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_DELETEALGORITHMGROUP))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"û��Ȩ��");
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
	case ID_ATPMANAGE_MODIFYALGORITHMGROUP:			//51013	�޸��㷨��(����Ա)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_MODIFYALGORITHMGROUP))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"û��Ȩ��");
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
	case ID_ATPMANAGE_QUERYALGORITHMGROUPINFO:		//51014��ѯ�㷨��(����Ա)
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
	case ID_ATPMANAGE_ADDALGORITHM:					//51021	����㷨��Ϣ(����Ա)
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
	case ID_ATPMANAGE_DELETEALGORITHM:				//51022	ɾ���㷨��Ϣ(����Ա)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_DELETEALGORITHM))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"û��Ȩ��");
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
	case ID_ATPMANAGE_MODIFYALGORITHM:				//51023	�޸��㷨(����Ա)
		{
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}//break;
	case ID_ATPMANAGE_MODIFYALGORITHMINFO:			//51024	�޸��㷨��Ϣ(����Ա)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_MODIFYALGORITHMINFO))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"û��Ȩ��");
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
	case ID_ATPMANAGE_QUERYALGORITHMINFO:			//51025	��ѯ�㷨��Ϣ(����Ա)
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
	case ID_ATPMANAGE_QUERYALGORITHMPARAM:			//51026	��ѯ�㷨����
		{
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_QUERYALGORITHMVERSION:		//51027	��ѯ�㷨��ʷ�汾
		{
			//CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);		
		}break;
	case ID_ATPMANAGE_ADDUSERGROUP:					//51041	����û���(����Ա)
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
	case ID_ATPMANAGE_DELETEUSERGROUP:				//51042	ɾ���û���(����Ա)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_DELETEUSERGROUP))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"û��Ȩ��");
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
	case ID_ATPMANAGE_MODIFYUSERGROUP:				//51043	�޸��û���(����Ա)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_MODIFYUSERGROUP))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"û��Ȩ��");
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
	case ID_ATPMANAGE_QUERYUSERGROUPINFO:			//51044	��ѯ�û�����Ϣ(����Ա)
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
	case ID_ATPMANAGE_ADDUSER:						//51051	����û�(����Ա)
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
	case ID_ATPMANAGE_DELETEUSER:					//51052	ɾ���û�(����Ա)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_DELETEUSER))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"û��Ȩ��");
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
	case ID_ATPMANAGE_MODIFYUSER:					//51053	�޸��û�(����Ա)
		{
			if (0 != IsHavePermission(ATP_MANAGER,m_szAccount,ID_ATPMANAGE_MODIFYUSER))
			{
				char sz[g_stru_ATPManageMsgHeadInfoSize+sizeof struAns_Operate] = {0};
				struAns_Operate _Operate = {0};
				strcpy(_Operate.szInfo,"û��Ȩ��");
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
	case ID_ATPMANAGE_QUERYUSERINFO:				//51054	��ѯ�û���Ϣ
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
	case ID_ATPMANAGE_QUERYUSEROPERATELOG:			//51061	��ѯ�û�������־(����Ա)struReq_AT
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
	case ID_ATPMANAGE_QUERYUSEDALGORITHM:			//51071	��ѯ�㷨ͳ����Ϣ(����Ա)
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
	case ID_ATPMANAGE_QUERYUSERALGORITHM:			//51072	��ѯ�û�ʹ���㷨ͳ����Ϣ(����Ա)
		{
			CHHNetFrameProcessor::Send(strSrcDN,(char*)&_MsgHeadInfo,sizeof stru_ATPManageMsgHeadInfo);	
		}break;
	case ID_ATPMANAGE_QUERYSERVERALGORITHM:			//51073	��ѯ�����������㷨ͳ����Ϣ(����Ա)
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
	
	int nServerBlock			= 0;								//�������鳤��
	int nServerGroupBlock		= 0;								//��������鳤��
	int nATPManagerInfoSize		= sizeof stru_ATPManagerInfo;		//����Ա(�����)�ṹ�峤��
	
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
		strncpy(_DataBaseManager.szID,pManagerInfo->szID,sizeof _DataBaseManager.szID);											//	����ԱID
		strncpy(_DataBaseManager.szName,pManagerInfo->szName,sizeof _DataBaseManager.szName);										//	����
		strncpy(_DataBaseManager.szPwd,pManagerInfo->szPwd,sizeof _DataBaseManager.szPwd);										//	����
		_DataBaseManager.nStatus				= pManagerInfo->nStatus;															//	����Ա״̬  0 1 2
		strncpy(_DataBaseManager.szExplain,pManagerInfo->szExplain,sizeof _DataBaseManager.szExplain);							//	˵����Ϣ
		memcpy((char*)_DataBaseManager.nPermissionIDs,(char*)pManagerInfo->nPermissionIDs,sizeof _DataBaseManager.nPermissionIDs);//	Ȩ��ID
		
		CTime t = CTime::GetCurrentTime();

		_DataBaseManager.nCreateDate			= t.GetYear()*10000+t.GetMonth()*100+t.GetDay();														//	��������
		_DataBaseManager.nCreateTime			= t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();														//	����ʱ��
		_DataBaseManager.nLastDate				= 19800101;															//	����½����
		_DataBaseManager.nLastTime				= 235959;															//	����½ʱ��
		_DataBaseManager.nDeleteMark			= pManagerInfo->nDeleteMark;														//	ɾ����־
		_DataBaseManager.nServerN				= pManagerInfo->ServerBlock.nItems;													//	����������
		if (_DataBaseManager.pServerIDs)
		{
			memcpy(_DataBaseManager.pServerIDs,(char *)&pData[nATPManagerInfoSize],nServerBlock);											//	������IDs
		}
		
		_DataBaseManager.nServerGroupN			= pManagerInfo->ServerGroupBlock.nItems;											//	�����������
		if (_DataBaseManager.pServerGroupIDs)
		{
			memcpy(_DataBaseManager.pServerGroupIDs,(char *)&pData[nATPManagerInfoSize+nServerBlock],nServerGroupBlock);					//	��������IDs
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
			sprintf(sz,"��������Ա(ID):%s ʧ��-��������ΪNULL",_DataBaseManager.szID);
			break;
		case EXISTDATA:
			sprintf(sz,"��������Ա(ID):%s ʧ��-�ù���Ա�Ѿ�����",_DataBaseManager.szID);
			break;
		case NEWERROR:
			sprintf(sz,"��������Ա(ID):%s ʧ��-NEW����",_DataBaseManager.szID);
			break;
		case NULLHANDLE:
			sprintf(sz,"��������Ա(ID):%s ʧ��-�������ΪNULL",_DataBaseManager.szID);
			break;
		default:
			break;
		}
		
		AddOperateLog(ID_ATPMANAGE_CREATEMANAGER,m_szAccount,sz);
		goto END___ADDMANAGER;
	}
	//////////////////////////////////////////////////////////////////////////
	

	{
		_ManagerInfo.nSerialNumber				= _ATPDBSAlgorithm.nSerialNumber;								//	�Զ�����
		strncpy(_ManagerInfo.szID,_ATPDBSAlgorithm.szID,sizeof _ManagerInfo.szID);								//	����ԱID
		strncpy(_ManagerInfo.szName,_ATPDBSAlgorithm.szName,sizeof _ManagerInfo.szName);						//	����
		strncpy(_ManagerInfo.szPwd,_ATPDBSAlgorithm.szPwd,sizeof _ManagerInfo.szPwd);							//	����
		_ManagerInfo.nStatus					= _ATPDBSAlgorithm.nStatus;										//	����Ա״̬  0 1 2
		strncpy(_ManagerInfo.szExplain,_ATPDBSAlgorithm.szExplain,sizeof _ManagerInfo.szExplain);				//	˵����Ϣ
		memcpy(_ManagerInfo.nPermissionIDs,_ATPDBSAlgorithm.nPermissionIDs,sizeof _ManagerInfo.nPermissionIDs);	//	Ȩ��ID
		_ManagerInfo.nCreateDate				= _ATPDBSAlgorithm.nCreateDate;									//	��������
		_ManagerInfo.nCreateTime				= _ATPDBSAlgorithm.nCreateTime;									//	����ʱ��
		_ManagerInfo.nLastDate					= _ATPDBSAlgorithm.nLastDate;									//	����½����
		_ManagerInfo.nLastTime					= _ATPDBSAlgorithm.nLastTime;									//	����½ʱ��
		_ManagerInfo.nDeleteMark				= _ATPDBSAlgorithm.nDeleteMark;									//	ɾ����־
		_ManagerInfo.ServerBlock.nItems			= _ATPDBSAlgorithm.nServerN;									//	����������items	itemsize = sizeof(struATPAutoID)   ������IDs
		_ManagerInfo.ServerBlock.nItemSize		= sizeof struATPAutoID;
		_ManagerInfo.ServerGroupBlock.nItems	= _ATPDBSAlgorithm.nServerGroupN;								//	�����������items   itemsize = sizeof(struATPAutoID)  ��������IDs
		_ManagerInfo.ServerGroupBlock.nItemSize = sizeof struATPAutoID;
	}
	//////////////////////////////////////////////////////////////////////////
	nServerBlock = _ManagerInfo.ServerBlock.nItems*sizeof struATPAutoID;
	nServerGroupBlock = _ManagerInfo.ServerGroupBlock.nItems*sizeof struATPAutoID;
	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + nATPManagerInfoSize + nServerBlock + nServerGroupBlock];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"��������Ա(ID):%s �ɹ�-NEW����",_ManagerInfo.szID);
		AddOperateLog(ID_ATPMANAGE_CREATEMANAGER,m_szAccount,sz);
		nRet = NEWERROR;
		goto END___ADDMANAGER;
	}
	char sz[128]={0};
	sprintf(sz,"��������Ա(ID):%s �ɹ�",_ManagerInfo.szID);
	AddOperateLog(ID_ATPMANAGE_CREATEMANAGER,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + nATPManagerInfoSize + nServerBlock + nServerGroupBlock;
	//���Ƶ���������ڴ���
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

	
	int nServerBlock			= 0;									//�������鳤��
	int nServerGroupBlock		= 0;									//��������鳤��
	int nATPManagerInfoSize	= sizeof stru_ATPManagerInfo;				//����Ա(�����)�ṹ�峤��


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
		strncpy(_DataBaseManager.szID,pManagerInfo->szID,sizeof _DataBaseManager.szID);												//	����ԱID
		strncpy(_DataBaseManager.szName,pManagerInfo->szName,sizeof _DataBaseManager.szName);										//	����
		strncpy(_DataBaseManager.szPwd,pManagerInfo->szPwd,sizeof _DataBaseManager.szPwd);											//	����
		_DataBaseManager.nStatus				= pManagerInfo->nStatus;															//	����Ա״̬  0 1 2
		strncpy(_DataBaseManager.szExplain,pManagerInfo->szExplain,sizeof _DataBaseManager.szExplain);								//	˵����Ϣ
		memcpy((char*)_DataBaseManager.nPermissionIDs,(char*)pManagerInfo->nPermissionIDs,sizeof _DataBaseManager.nPermissionIDs);	//	Ȩ��ID
		_DataBaseManager.nCreateDate			= pManagerInfo->nCreateDate;														//	��������
		_DataBaseManager.nCreateTime			= pManagerInfo->nCreateTime;														//	����ʱ��
		_DataBaseManager.nLastDate				= pManagerInfo->nLastDate;															//	����½����
		_DataBaseManager.nLastTime				= pManagerInfo->nLastTime;															//	����½ʱ��
		_DataBaseManager.nDeleteMark			= pManagerInfo->nDeleteMark;														//	ɾ����־
		_DataBaseManager.nServerN				= pManagerInfo->ServerBlock.nItems;													//	����������
		if (_DataBaseManager.pServerIDs)
		{
			memcpy(_DataBaseManager.pServerIDs,(char *)&pData[nATPManagerInfoSize],nServerBlock);									//	������IDs
		}
		
		_DataBaseManager.nServerGroupN			= pManagerInfo->ServerGroupBlock.nItems;											//	�����������
		if (_DataBaseManager.pServerGroupIDs)
		{
			memcpy(_DataBaseManager.pServerGroupIDs,(char *)&pData[nATPManagerInfoSize+nServerBlock],nServerGroupBlock);			//	��������IDs
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
		strcpy(_Ans_Operate.szInfo,"�޸ĳɹ�");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"�޸Ĺ���Ա(ID):%s ʧ��-��������ΪNULL",_DataBaseManager.szID);
			break;
		case EXISTDATA:
			sprintf(sz,"�޸Ĺ���Ա(ID):%s ʧ��-�ù���Ա�Ѿ�����",_DataBaseManager.szID);
			break;
		case NEWERROR:
			sprintf(sz,"�޸Ĺ���Ա(ID):%s ʧ��-NEW����",_DataBaseManager.szID);
			break;
		case NULLHANDLE:
			sprintf(sz,"�޸Ĺ���Ա(ID):%s ʧ��-�������ΪNULL",_DataBaseManager.szID);
			break;
		case ZERORECORD:
			sprintf(sz,"�޸Ĺ���Ա(ID):%s ʧ��-û�иü�¼",_DataBaseManager.szID);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_MODIFYMANAGER,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"�޸�ʧ��");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"�޸Ĺ���Ա(ID):%s �ɹ�-NEW����",_DataBaseManager.szID);
		AddOperateLog(ID_ATPMANAGE_MODIFYMANAGER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"�޸Ĺ���Ա(ID):%s �ɹ�",_DataBaseManager.szID);
	AddOperateLog(ID_ATPMANAGE_MODIFYMANAGER,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);
	
	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::DelManager(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPManagerInfo *pManagerInfo			= (stru_ATPManagerInfo *)pData;
	struATPDataBaseManager _DataBaseManager	= {0};


	int nServerBlock			= 0;								//�������鳤��
	int nServerGroupBlock		= 0;								//��������鳤��
	int nATPManagerInfoSize	= sizeof stru_ATPManagerInfo;			//����Ա(�����)�ṹ�峤��


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
		strncpy(_DataBaseManager.szID,pManagerInfo->szID,sizeof _DataBaseManager.szID);												//	����ԱID
		strncpy(_DataBaseManager.szName,pManagerInfo->szName,sizeof _DataBaseManager.szName);										//	����
		strncpy(_DataBaseManager.szPwd,pManagerInfo->szPwd,sizeof _DataBaseManager.szPwd);											//	����
		_DataBaseManager.nStatus				= pManagerInfo->nStatus;															//	����Ա״̬  0 1 2
		strncpy(_DataBaseManager.szExplain,pManagerInfo->szExplain,sizeof _DataBaseManager.szExplain);								//	˵����Ϣ
		memcpy((char*)_DataBaseManager.nPermissionIDs,(char*)pManagerInfo->nPermissionIDs,sizeof _DataBaseManager.nPermissionIDs);	//	Ȩ��ID
		_DataBaseManager.nCreateDate			= pManagerInfo->nCreateDate;														//	��������
		_DataBaseManager.nCreateTime			= pManagerInfo->nCreateTime;														//	����ʱ��
		_DataBaseManager.nLastDate				= pManagerInfo->nLastDate;															//	����½����
		_DataBaseManager.nLastTime				= pManagerInfo->nLastTime;															//	����½ʱ��
		_DataBaseManager.nDeleteMark			= pManagerInfo->nDeleteMark;														//	ɾ����־
		_DataBaseManager.nServerN				= pManagerInfo->ServerBlock.nItems;													//	����������
		if (_DataBaseManager.pServerIDs)
		{
			memcpy(_DataBaseManager.pServerIDs,(char *)&pData[nATPManagerInfoSize],nServerBlock);									//	������IDs
		}
		
		_DataBaseManager.nServerGroupN			= pManagerInfo->ServerGroupBlock.nItems;											//	�����������
		if (_DataBaseManager.pServerGroupIDs)
		{
			memcpy(_DataBaseManager.pServerGroupIDs,(char *)&pData[nATPManagerInfoSize+nServerBlock],nServerGroupBlock);			//	��������IDs
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
		strcpy(_Ans_Operate.szInfo,"ɾ���ɹ�");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"ɾ������Ա(ID):%s ʧ��-��������ΪNULL",_DataBaseManager.szID);
			break;
		case EXISTDATA:
			sprintf(sz,"ɾ������Ա(ID):%s ʧ��-�ù���Ա�Ѿ�����",_DataBaseManager.szID);
			break;
		case NEWERROR:
			sprintf(sz,"ɾ������Ա(ID):%s ʧ��-NEW����",_DataBaseManager.szID);
			break;
		case NULLHANDLE:
			sprintf(sz,"ɾ������Ա(ID):%s ʧ��-�������ΪNULL",_DataBaseManager.szID);
			break;
		case ZERORECORD:
			sprintf(sz,"ɾ������Ա(ID):%s ʧ��-û�иü�¼",_DataBaseManager.szID);
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_DELETEMANAGER,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"ɾ��ʧ��");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"ɾ������Ա(ID):%s �ɹ�-NEW����",_DataBaseManager.szID);
		AddOperateLog(ID_ATPMANAGE_DELETEMANAGER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"ɾ������Ա(ID):%s �ɹ�",_DataBaseManager.szID);
	AddOperateLog(ID_ATPMANAGE_DELETEMANAGER,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::QueryManager(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseManager *pATPDataBaseManager = NULL;
	int nATPManagerInfoSize	= sizeof stru_ATPManagerInfo;		//����Ա(�����)�ṹ�峤��
	//nRet ��ѯ�������
	int nRet = g_pATPFileDBApi->QueryManager(m_szAccount,&pATPDataBaseManager);

	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"��ѯ����Ա ʧ��-��������ΪNULL");
			break;
		case EXISTDATA:
			sprintf(sz,"��ѯ����Ա ʧ��-�ù���Ա�Ѿ�����");
			break;
		case NEWERROR:
			sprintf(sz,"��ѯ����Ա ʧ��-NEW����");
			break;
		case NULLHANDLE:
			sprintf(sz,"��ѯ����Ա ʧ��-�������ΪNULL");
			break;
		case 0:
		case ZERORECORD:
			sprintf(sz,"��ѯ����Ա ʧ��-û�м�¼");
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_QUERYMANAGERINFO,m_szAccount,sz);
		return nRet;
	}
	
	int i = 0;
	*pnLen = g_stru_ATPManageMsgHeadInfoSize;//��ͷ����
	for (;i<nRet;i++)
	{
		(*pnLen) += (nATPManagerInfoSize+(pATPDataBaseManager[i].nServerN+pATPDataBaseManager[i].nServerGroupN)*sizeof struATPAutoID);
	}

	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"��ѯ����Ա �ɹ�-NEW����");
		AddOperateLog(ID_ATPMANAGE_QUERYMANAGERINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"��ѯ����Ա �ɹ�");
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

			_ManagerInfo.nSerialNumber				= pATPDataBaseManager[i].nSerialNumber;										//	�Զ�����
			strncpy(_ManagerInfo.szID,pATPDataBaseManager[i].szID,sizeof _ManagerInfo.szID);										//	����ԱID																
			strncpy(_ManagerInfo.szName,pATPDataBaseManager[i].szName,sizeof _ManagerInfo.szName);									//	����
			strncpy(_ManagerInfo.szPwd,pATPDataBaseManager[i].szPwd,sizeof _ManagerInfo.szPwd);									//	����
			_ManagerInfo.nStatus					= pATPDataBaseManager[i].nStatus;												//	����Ա״̬  0 1 2
			strncpy(_ManagerInfo.szExplain,pATPDataBaseManager[i].szExplain,sizeof _ManagerInfo.szExplain);						//	˵����Ϣ
			memcpy((char *)_ManagerInfo.nPermissionIDs,(char *)pATPDataBaseManager[i].nPermissionIDs,sizeof _ManagerInfo.nPermissionIDs);	//	Ȩ��ID

			_ManagerInfo.nCreateDate				= pATPDataBaseManager[i].nCreateDate;													//	��������
			_ManagerInfo.nCreateTime				= pATPDataBaseManager[i].nCreateTime;													//	����ʱ��
			_ManagerInfo.nLastDate					= pATPDataBaseManager[i].nLastDate;												//	����½����
			_ManagerInfo.nLastTime					= pATPDataBaseManager[i].nLastTime;												//	����½ʱ��

			_ManagerInfo.nDeleteMark				= pATPDataBaseManager[i].nDeleteMark;											//	ɾ����־
			_ManagerInfo.ServerBlock.nItems			= pATPDataBaseManager[i].nServerN;												//	����������items	itemsize = sizeof(struATPAutoID)   ������IDs
			_ManagerInfo.ServerBlock.nItemSize		= sizeof struATPAutoID;
			_ManagerInfo.ServerGroupBlock.nItems	= pATPDataBaseManager[i].nServerGroupN;										//	�����������items   itemsize = sizeof(struATPAutoID)  ��������IDs
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
			sprintf(sz,"��ӷ�������(NAME):%s ʧ��-��������ΪNULL",_DataBaseServerGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"��ӷ�������(NAME):%s ʧ��-�÷��������Ѿ�����",_DataBaseServerGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"��ӷ�������(NAME):%s ʧ��-NEW����",_DataBaseServerGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"��ӷ�������(NAME):%s ʧ��-�������ΪNULL",_DataBaseServerGroup.szName);
			break;
		//case 0:
		case ZERORECORD:
			sprintf(sz,"��ӷ�������(NAME):%s ʧ��-û�иü�¼",_DataBaseServerGroup.szName);
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
		sprintf(sz,"��ӷ�������(NAME):%s �ɹ�-NEW����",_DataBaseServerGroup.szName);
		AddOperateLog(ID_ATPMANAGE_CREATESERVERGROUP,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"��ӷ�������(NAME):%s �ɹ�",_DataBaseServerGroup.szName);
	AddOperateLog(ID_ATPMANAGE_CREATESERVERGROUP,m_szAccount,sz);
	//���Ƶ���������ڴ���
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
		strcpy(_Ans_Operate.szInfo,"�޸ĳɹ�");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"�޸ķ�������(NAME):%s ʧ��-��������ΪNULL",_DataBaseServerGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"�޸ķ�������(NAME):%s ʧ��-�÷��������Ѿ�����",_DataBaseServerGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"�޸ķ�������(NAME):%s ʧ��-NEW����",_DataBaseServerGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"�޸ķ�������(NAME):%s ʧ��-�������ΪNULL",_DataBaseServerGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"�޸ķ�������(NAME):%s ʧ��-û�иü�¼",_DataBaseServerGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_MODIFYSERVERGROUP,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"�޸�ʧ��");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"�޸ķ�������(NAME):%s �ɹ�-NEW����",_DataBaseServerGroup.szName);
		AddOperateLog(ID_ATPMANAGE_MODIFYSERVERGROUP,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"�޸ķ�������(NAME):%s �ɹ�",_DataBaseServerGroup.szName);
	AddOperateLog(ID_ATPMANAGE_MODIFYSERVERGROUP,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
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
		strcpy(_Ans_Operate.szInfo,"ɾ���ɹ�");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"ɾ����������(NAME):%s ʧ��-��������ΪNULL",_DataBaseServerGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"ɾ����������(NAME):%s ʧ��-�÷��������Ѿ�����",_DataBaseServerGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"ɾ����������(NAME):%s ʧ��-NEW����",_DataBaseServerGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"ɾ����������(NAME):%s ʧ��-�������ΪNULL",_DataBaseServerGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"ɾ����������(NAME):%s ʧ��-û�иü�¼",_DataBaseServerGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_DELETESERVERGROUP,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"ɾ��ʧ��");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"ɾ����������(NAME):%s �ɹ�-NEW����",_DataBaseServerGroup.szName);
		AddOperateLog(ID_ATPMANAGE_DELETESERVERGROUP,m_szAccount,sz);
		return -1;
	}
	char sz[128]={0};
	sprintf(sz,"ɾ����������(NAME):%s �ɹ�",_DataBaseServerGroup.szName);
	AddOperateLog(ID_ATPMANAGE_DELETESERVERGROUP,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::QueryServerGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseServerGroup *pATPDataBaseServerGroup = NULL;
	int nATPServerGroupInfoSize = sizeof stru_ATPServerGroupInfo;
	//nRet ��ѯ�������
	int nRet = g_pATPFileDBApi->QueryServerGroup(&pATPDataBaseServerGroup);

	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"��ѯ�������� ʧ��-��������ΪNULL");
			break;
		case EXISTDATA:
			sprintf(sz,"��ѯ�������� ʧ��-�÷��������Ѿ�����");
			break;
		case NEWERROR:
			sprintf(sz,"��ѯ�������� ʧ��-NEW����");
			break;
		case NULLHANDLE:
			sprintf(sz,"��ѯ�������� ʧ��-�������ΪNULL");
			break;
			case 0:
		case ZERORECORD:
			sprintf(sz,"��ѯ�������� �ɹ�-û�иü�¼");
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
		sprintf(sz,"��ѯ�������� �ɹ�-NEW����");
		AddOperateLog(ID_ATPMANAGE_QUERYSERVERGROUPINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"��ѯ�������� �ɹ�");
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
			sprintf(sz,"��ӷ�����(NAME/IP):%s ʧ��-��������ΪNULL",_DataBaseServer.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"��ӷ�����(NAME/IP):%s ʧ��-�÷��������Ѿ�����",_DataBaseServer.szName);
			break;
		case NEWERROR:
			sprintf(sz,"��ӷ�����(NAME/IP):%s ʧ��-NEW����",_DataBaseServer.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"��ӷ�����(NAME/IP):%s ʧ��-�������ΪNULL",_DataBaseServer.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"��ӷ�����(NAME/IP):%s ʧ��-û�иü�¼",_DataBaseServer.szName);
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
		sprintf(sz,"��ӷ�����(NAME/IP):%s �ɹ�-NEW����",_DataBaseServer.szName);
		AddOperateLog(ID_ATPMANAGE_CREATESERVER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"��ӷ�����(NAME/IP):%s �ɹ�",_DataBaseServer.szName);
	AddOperateLog(ID_ATPMANAGE_CREATESERVER,m_szAccount,sz);
	//���Ƶ���������ڴ���
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
		strcpy(_Ans_Operate.szInfo,"�޸ĳɹ�");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"�޸ķ�����(NAME/IP):%s ʧ��-��������ΪNULL",_DataBaseServer.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"�޸ķ�����(NAME/IP):%s ʧ��-�÷��������Ѿ�����",_DataBaseServer.szName);
			break;
		case NEWERROR:
			sprintf(sz,"�޸ķ�����(NAME/IP):%s ʧ��-NEW����",_DataBaseServer.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"�޸ķ�����(NAME/IP):%s ʧ��-�������ΪNULL",_DataBaseServer.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"�޸ķ�����(NAME/IP):%s ʧ��-û�иü�¼",_DataBaseServer.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_MODIFYSERVER,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"�޸�ʧ��");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"�޸ķ�����(NAME/IP):%s �ɹ�-NEW����",_DataBaseServer.szName);
		AddOperateLog(ID_ATPMANAGE_MODIFYSERVER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"�޸ķ�����(NAME/IP):%s �ɹ�",_DataBaseServer.szName);
	AddOperateLog(ID_ATPMANAGE_MODIFYSERVER,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
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
		strcpy(_Ans_Operate.szInfo,"ɾ���ɹ�");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"ɾ��������(NAME/IP):%s ʧ��-��������ΪNULL",_DataBaseServer.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"ɾ��������(NAME/IP):%s ʧ��-�÷��������Ѿ�����",_DataBaseServer.szName);
			break;
		case NEWERROR:
			sprintf(sz,"ɾ��������(NAME/IP):%s ʧ��-NEW����",_DataBaseServer.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"ɾ��������(NAME/IP):%s ʧ��-�������ΪNULL",_DataBaseServer.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"ɾ��������(NAME/IP):%s ʧ��-û�иü�¼",_DataBaseServer.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_DELETESERVER,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"ɾ��ʧ��");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"ɾ��������(NAME/IP):%s �ɹ�-NEW����",_DataBaseServer.szName);
		AddOperateLog(ID_ATPMANAGE_DELETESERVER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"ɾ��������(NAME/IP):%s �ɹ�",_DataBaseServer.szName);
	AddOperateLog(ID_ATPMANAGE_DELETESERVER,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::QueryServer(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseServer *pATPDataBaseServer = NULL;
	int nATPServerInfoSize = sizeof stru_ATPServerInfo;
	//nRet ��ѯ�������
	struATPDataBaseServer_QUERY *pATPDataBaseServer_QUERY = (struATPDataBaseServer_QUERY *)pData;
	int nRet = g_pATPFileDBApi->QueryServer(pATPDataBaseServer_QUERY,&pATPDataBaseServer);

	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"��ѯ������ ʧ��-��������ΪNULL");
			break;
		case EXISTDATA:
			sprintf(sz,"��ѯ������ ʧ��-�÷������Ѿ�����");
			break;
		case NEWERROR:
			sprintf(sz,"��ѯ������ ʧ��-NEW����");
			break;
		case NULLHANDLE:
			sprintf(sz,"��ѯ������ ʧ��-�������ΪNULL");
			break;
		case 0:
		case ZERORECORD:
			sprintf(sz,"��ѯ������ �ɹ�-û�иü�¼");
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
		sprintf(sz,"��ѯ�������� �ɹ�-NEW����");
		AddOperateLog(ID_ATPMANAGE_QUERYSERVERINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"��ѯ�������� �ɹ�");
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
	//nRet ��ѯ�������
	int nRet = g_pATPFileDBApi->QueryPermission(&pATPDataBasePermission);

	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"��ѯȨ�� ʧ��-��������ΪNULL");
			break;
		case EXISTDATA:
			sprintf(sz,"��ѯȨ�� ʧ��-��Ȩ���Ѿ�����");
			break;
		case NEWERROR:
			sprintf(sz,"��ѯȨ�� ʧ��-NEW����");
			break;
		case NULLHANDLE:
			sprintf(sz,"��ѯȨ�� ʧ��-�������ΪNULL");
			break;
			case 0:
		case ZERORECORD:
			sprintf(sz,"��ѯȨ�� ʧ��-û�иü�¼");
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
		sprintf(sz,"��ѯȨ�� ʧ��-NEW����");
		AddOperateLog(ID_ATPMANAGE_QUERYPERMISSIONINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"��ѯȨ�� ʧ��");
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


	int nAlgorithmBlock		= 0;									//�㷨��
	int nAlgorithmGroupBlock	= 0;								//������
	int nServerBlock			= 0;								//��������
	int nServerGroupBlock		= 0;								//���������
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
		
			
		_DataBaseUserGroup.nID					= pUserGroupInfo->nID;																//	��ID  �Զ�����
		_DataBaseUserGroup.nParentID			= pUserGroupInfo->nParentID;														//	����ID
		strncpy(_DataBaseUserGroup.szName,pUserGroupInfo->szName,sizeof _DataBaseUserGroup.szName);									//	����
		strncpy(_DataBaseUserGroup.szExplain,pUserGroupInfo->szExplain,sizeof _DataBaseUserGroup.szExplain);						//	˵����Ϣ
		_DataBaseUserGroup.nAlgorithmN			= pUserGroupInfo->AlgorithmBlock.nItems;											//	�㷨����
		if (_DataBaseUserGroup.pAlgorithmIDs)
		{
			memcpy(_DataBaseUserGroup.pAlgorithmIDs,&pData[nATPUserGroupInfoSize],nAlgorithmBlock);									//	�㷨ID
		}
		
		_DataBaseUserGroup.nAlgorithmGroupN		= pUserGroupInfo->AlgorithmGroupBlock.nItems;										//	�㷨�����
		if (_DataBaseUserGroup.pAlgorithmGroupIDs)
		{
			memcpy(_DataBaseUserGroup.pAlgorithmGroupIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock],nAlgorithmGroupBlock);		//	�㷨��ID
		}
		
		_DataBaseUserGroup.nServerN = pUserGroupInfo->ServerBlock.nItems;															//	����������
		if (_DataBaseUserGroup.pServerIDs)
		{
			memcpy(_DataBaseUserGroup.pServerIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock + nAlgorithmGroupBlock],nServerBlock);//	������ID
		}
		
		_DataBaseUserGroup.nServerGroupN		= pUserGroupInfo->ServerGroupBlock.nItems;											//	�����������
		if (_DataBaseUserGroup.pServerGroupIDs)
		{
			memcpy(_DataBaseUserGroup.pServerGroupIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock],nServerGroupBlock);//	��������ID
		}
		
		CTime t = CTime::GetCurrentTime();
		_DataBaseUserGroup.nCreateDate		= t.GetYear()*10000+t.GetMonth()*100+t.GetDay();																	//	��������
		_DataBaseUserGroup.nCreateTime		= t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();																	//	����ʱ��
		_DataBaseUserGroup.nDeleteMark			= pUserGroupInfo->nDeleteMark;														//	ɾ����־
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
			sprintf(sz,"����û���(NAME):%s ʧ��-��������ΪNULL",_DataBaseUserGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"����û���(NAME):%s ʧ��-�÷��������Ѿ�����",_DataBaseUserGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"����û���(NAME):%s ʧ��-NEW����",_DataBaseUserGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"����û���(NAME):%s ʧ��-�������ΪNULL",_DataBaseUserGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"����û���(NAME):%s ʧ��-û�иü�¼",_DataBaseUserGroup.szName);
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
		_UserGroupInfo.nID								= _ATPDBSUserGroup.nID;							//	��ID  �Զ�����
		_UserGroupInfo.nParentID						= _ATPDBSUserGroup.nParentID;					//	����ID
		strncpy(_UserGroupInfo.szName,_ATPDBSUserGroup.szName,sizeof _UserGroupInfo.szName);			//	����
		strncpy(_UserGroupInfo.szExplain,_ATPDBSUserGroup.szExplain,sizeof _UserGroupInfo.szExplain);	//	˵����Ϣ
		_UserGroupInfo.AlgorithmBlock.nItems			= _ATPDBSUserGroup.nAlgorithmN;					//	�㷨���� Item ,   itemsize=sizeof(struATPAutoAlgoID) �㷨IDs
		_UserGroupInfo.AlgorithmBlock.nItemSize			= sizeof struATPAutoAlgoID;								
		_UserGroupInfo.AlgorithmGroupBlock.nItems		= _ATPDBSUserGroup.nAlgorithmGroupN;			//	�㷨�����Item  , itemsize=sizeof(struATPAutoID)  �㷨��IDs
		_UserGroupInfo.AlgorithmGroupBlock.nItemSize	= sizeof struATPAutoID;	
		_UserGroupInfo.ServerBlock.nItems				= _ATPDBSUserGroup.nServerN;					//	����������Item,	itemsize=sizeof(struATPAutoID) ������IDs
		_UserGroupInfo.ServerBlock.nItemSize			= sizeof struATPAutoID;
		_UserGroupInfo.ServerGroupBlock.nItems			= _ATPDBSUserGroup.nServerGroupN;				//	�����������Item  ,itemsize=sizeof(struATPAutoID)  ��������IDs
		_UserGroupInfo.ServerGroupBlock.nItemSize		= sizeof struATPAutoID;
		_UserGroupInfo.nCreateDate						= _ATPDBSUserGroup.nCreateDate;					//	��������
		_UserGroupInfo.nCreateTime						= _ATPDBSUserGroup.nCreateTime;					//	����ʱ��
		_UserGroupInfo.nDeleteMark						= _ATPDBSUserGroup.nDeleteMark;					//	ɾ����־
	}

	//////////////////////////////////////////////////////////////////////////
	nAlgorithmBlock			= _UserGroupInfo.AlgorithmBlock.nItems*sizeof struATPAutoAlgoID;			//�㷨��
	nAlgorithmGroupBlock	= _UserGroupInfo.AlgorithmGroupBlock.nItems*sizeof struATPAutoID;			//������
	nServerBlock			= _UserGroupInfo.ServerBlock.nItems*sizeof struATPAutoID;
	nServerGroupBlock		= _UserGroupInfo.ServerGroupBlock.nItems*sizeof struATPAutoID;
	*pnLen					= g_stru_ATPManageMsgHeadInfoSize + nATPUserGroupInfoSize+ nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock + nServerGroupBlock;
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"����û���(NAME):%s �ɹ�-NEW����",_DataBaseUserGroup.szName);
		AddOperateLog(ID_ATPMANAGE_ADDUSERGROUP,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"����û���(NAME):%s �ɹ�",_DataBaseUserGroup.szName);
	AddOperateLog(ID_ATPMANAGE_ADDUSERGROUP,m_szAccount,sz);
	//���Ƶ���������ڴ���
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


	int nAlgorithmBlock			= 0;								//�㷨��
	int nAlgorithmGroupBlock	= 0;								//������
	int nServerBlock			= 0;								//��������
	int nServerGroupBlock		= 0;								//���������
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
		
		
		_DataBaseUserGroup.nID					= pUserGroupInfo->nID;																//	��ID  �Զ�����
		_DataBaseUserGroup.nParentID			= pUserGroupInfo->nParentID;														//	����ID
		strncpy(_DataBaseUserGroup.szName,pUserGroupInfo->szName,sizeof _DataBaseUserGroup.szName);									//	����
		strncpy(_DataBaseUserGroup.szExplain,pUserGroupInfo->szExplain,sizeof _DataBaseUserGroup.szExplain);						//	˵����Ϣ
		_DataBaseUserGroup.nAlgorithmN			= pUserGroupInfo->AlgorithmBlock.nItems;											//	�㷨����
		if (_DataBaseUserGroup.pAlgorithmIDs)
		{
			memcpy(_DataBaseUserGroup.pAlgorithmIDs,&pData[nATPUserGroupInfoSize],nAlgorithmBlock);									//	�㷨ID
		}
		
		_DataBaseUserGroup.nAlgorithmGroupN		= pUserGroupInfo->AlgorithmGroupBlock.nItems;										//	�㷨�����
		if (_DataBaseUserGroup.pAlgorithmGroupIDs)
		{
			memcpy(_DataBaseUserGroup.pAlgorithmGroupIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock],nAlgorithmGroupBlock);		//	�㷨��ID
		}
		
		_DataBaseUserGroup.nServerN = pUserGroupInfo->ServerBlock.nItems;															//	����������
		if (_DataBaseUserGroup.pServerIDs)
		{
			memcpy(_DataBaseUserGroup.pServerIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock + nAlgorithmGroupBlock],nServerBlock);	//	������ID
		}
		
		_DataBaseUserGroup.nServerGroupN		= pUserGroupInfo->ServerGroupBlock.nItems;											//	�����������
		if (_DataBaseUserGroup.pServerGroupIDs)
		{
			memcpy(_DataBaseUserGroup.pServerGroupIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock],nServerGroupBlock);//	��������ID
		}
		
		_DataBaseUserGroup.nCreateDate			= pUserGroupInfo->nCreateDate;														//	��������
		_DataBaseUserGroup.nCreateTime			= pUserGroupInfo->nCreateTime;														//	����ʱ��
		_DataBaseUserGroup.nDeleteMark			= pUserGroupInfo->nDeleteMark;														//	ɾ����־
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
		strcpy(_Ans_Operate.szInfo,"�޸ĳɹ�");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"�޸��û���(NAME):%s ʧ��-��������ΪNULL",_DataBaseUserGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"�޸��û���(NAME):%s ʧ��-�÷��������Ѿ�����",_DataBaseUserGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"�޸��û���(NAME):%s ʧ��-NEW����",_DataBaseUserGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"�޸��û���(NAME):%s ʧ��-�������ΪNULL",_DataBaseUserGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"�޸��û���(NAME):%s ʧ��-û�иü�¼",_DataBaseUserGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_MODIFYUSERGROUP,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"�޸�ʧ��");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"�޸��û���(NAME):%s �ɹ�-NEW����",_DataBaseUserGroup.szName);
		AddOperateLog(ID_ATPMANAGE_MODIFYUSERGROUP,m_szAccount,sz);
		return -1;
	}
	char sz[128]={0};
	sprintf(sz,"�޸��û���(NAME):%s �ɹ�",_DataBaseUserGroup.szName);
	AddOperateLog(ID_ATPMANAGE_MODIFYUSERGROUP,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);
	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::DelUserGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	stru_ATPUserGroupInfo *pUserGroupInfo		= (stru_ATPUserGroupInfo *)pData;
	struATPDataBaseUserGroup _DataBaseUserGroup	= {0};


	int nAlgorithmBlock			= 0;								//�㷨��
	int nAlgorithmGroupBlock	= 0;								//������
	int nServerBlock			= 0;								//��������
	int nServerGroupBlock		= 0;								//���������
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
		

		_DataBaseUserGroup.nID					= pUserGroupInfo->nID;																//	��ID  �Զ�����
		_DataBaseUserGroup.nParentID			= pUserGroupInfo->nParentID;														//	����ID
		strncpy(_DataBaseUserGroup.szName,pUserGroupInfo->szName,sizeof _DataBaseUserGroup.szName);									//	����
		strncpy(_DataBaseUserGroup.szExplain,pUserGroupInfo->szExplain,sizeof _DataBaseUserGroup.szExplain);						//	˵����Ϣ
		_DataBaseUserGroup.nAlgorithmN			= pUserGroupInfo->AlgorithmBlock.nItems;											//	�㷨����
		if (_DataBaseUserGroup.pAlgorithmIDs)
		{
			memcpy(_DataBaseUserGroup.pAlgorithmIDs,&pData[nATPUserGroupInfoSize],nAlgorithmBlock);										//	�㷨ID
		}
		
		_DataBaseUserGroup.nAlgorithmGroupN		= pUserGroupInfo->AlgorithmGroupBlock.nItems;										//	�㷨�����
		if (_DataBaseUserGroup.pAlgorithmGroupIDs)
		{
			memcpy(_DataBaseUserGroup.pAlgorithmGroupIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock],nAlgorithmGroupBlock);			//	�㷨��ID
		}
		
		_DataBaseUserGroup.nServerN = pUserGroupInfo->ServerBlock.nItems;															//	����������
		if (_DataBaseUserGroup.pServerIDs)
		{
			memcpy(_DataBaseUserGroup.pServerIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock + nAlgorithmGroupBlock],nServerBlock);	//	������ID
		}
		
		_DataBaseUserGroup.nServerGroupN		= pUserGroupInfo->ServerGroupBlock.nItems;											//	�����������
		if (_DataBaseUserGroup.pServerGroupIDs)
		{
			memcpy(_DataBaseUserGroup.pServerGroupIDs,&pData[nATPUserGroupInfoSize + nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock],nServerGroupBlock);//	��������ID
		}
		
		_DataBaseUserGroup.nCreateDate			= pUserGroupInfo->nCreateDate;														//	��������
		_DataBaseUserGroup.nCreateTime			= pUserGroupInfo->nCreateTime;														//	����ʱ��
		_DataBaseUserGroup.nDeleteMark			= pUserGroupInfo->nDeleteMark;														//	ɾ����־

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
		strcpy(_Ans_Operate.szInfo,"ɾ���ɹ�");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"ɾ���û���(NAME):%s ʧ��-��������ΪNULL",_DataBaseUserGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"ɾ���û���(NAME):%s ʧ��-�÷��������Ѿ�����",_DataBaseUserGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"ɾ���û���(NAME):%s ʧ��-NEW����",_DataBaseUserGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"ɾ���û���(NAME):%s ʧ��-�������ΪNULL",_DataBaseUserGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"ɾ���û���(NAME):%s ʧ��-û�иü�¼",_DataBaseUserGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_DELETEUSERGROUP,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"ɾ��ʧ��");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"ɾ���û���(NAME):%s �ɹ�-NEW����",_DataBaseUserGroup.szName);
		AddOperateLog(ID_ATPMANAGE_DELETEUSERGROUP,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"ɾ���û���(NAME):%s �ɹ�",_DataBaseUserGroup.szName);
	AddOperateLog(ID_ATPMANAGE_DELETEUSERGROUP,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);
	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::QueryUserGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseUserGroup *pATPDataBaseManager = NULL;
	int nATPUserGroupInfoSize	= sizeof stru_ATPUserGroupInfo;
	//nRet ��ѯ�������
	int nRet = g_pATPFileDBApi->QueryUserGroup(m_szAccount,&pATPDataBaseManager);
	//ASSERT(_CrtCheckMemory());
		
	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"��ѯ�û��� ʧ��-��������ΪNULL");
			break;
		case EXISTDATA:
			sprintf(sz,"��ѯ�û��� ʧ��-���û����Ѿ�����");
			break;
		case NEWERROR:
			sprintf(sz,"��ѯ�û��� ʧ��-NEW����");
			break;
		case NULLHANDLE:
			sprintf(sz,"��ѯ�û��� ʧ��-�������ΪNULL");
			break;
			case 0:
		case ZERORECORD:
			sprintf(sz,"��ѯ�û��� �ɹ�-û�иü�¼");
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
		sprintf(sz,"��ѯ�û��� �ɹ�-NEW����");
		AddOperateLog(ID_ATPMANAGE_QUERYUSERGROUPINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"��ѯ�û��� �ɹ�");
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
		_UserGroupInfo.nID								= pATPDataBaseManager[i].nID;						//	��ID  �Զ�����
		_UserGroupInfo.nParentID						= pATPDataBaseManager[i].nParentID;					//	����ID
		strncpy(_UserGroupInfo.szName,pATPDataBaseManager[i].szName,sizeof _UserGroupInfo.szName);			//	����
		strncpy(_UserGroupInfo.szExplain,pATPDataBaseManager[i].szExplain,sizeof _UserGroupInfo.szExplain);	//	˵����Ϣ
		_UserGroupInfo.AlgorithmBlock.nItems			= pATPDataBaseManager[i].nAlgorithmN;				//	�㷨���� Item ,   itemsize=sizeof(struATPAutoAlgoID) �㷨IDs
		_UserGroupInfo.AlgorithmBlock.nItemSize			= sizeof struATPAutoAlgoID;								
		_UserGroupInfo.AlgorithmGroupBlock.nItems		= pATPDataBaseManager[i].nAlgorithmGroupN;			//	�㷨�����Item  , itemsize=sizeof(struATPAutoID)  �㷨��IDs
		_UserGroupInfo.AlgorithmGroupBlock.nItemSize	= sizeof struATPAutoID;	
		_UserGroupInfo.ServerBlock.nItems				= pATPDataBaseManager[i].nServerN;					//	����������Item,	itemsize=sizeof(struATPAutoID) ������IDs
		_UserGroupInfo.ServerBlock.nItemSize			= sizeof struATPAutoID;
		_UserGroupInfo.ServerGroupBlock.nItems			= pATPDataBaseManager[i].nServerGroupN;				//	�����������Item  ,itemsize=sizeof(struATPAutoID)  ��������IDs
		_UserGroupInfo.ServerGroupBlock.nItemSize		= sizeof struATPAutoID;
		_UserGroupInfo.nCreateDate						= pATPDataBaseManager[i].nCreateDate;				//	��������
		_UserGroupInfo.nCreateTime						= pATPDataBaseManager[i].nCreateTime;				//	����ʱ��
		_UserGroupInfo.nDeleteMark						= pATPDataBaseManager[i].nDeleteMark;				//	ɾ����־
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
	int nAlgorithmBlock			= 0;									//�㷨��
	int nAlgorithmGroupBlock	= 0;								//������
	int nServerBlock			= 0;								//��������
	int nServerGroupBlock		= 0;								//���������
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
		
				
		_DataBaseUser.nSerialNumber				= pUserInfo->nSerialNumber;														//	�Զ�����
		strncpy(_DataBaseUser.szUserID,pUserInfo->szUserID,sizeof _DataBaseUser.szUserID);										//	�û�ID
		strncpy(_DataBaseUser.szPwd,pUserInfo->szPwd,sizeof _DataBaseUser.szPwd);												//	�û�����
		strncpy(_DataBaseUser.szUserName,pUserInfo->szUserName,sizeof _DataBaseUser.szUserName);								//	�û���
		strncpy(_DataBaseUser.szCardID,pUserInfo->szCardID,sizeof _DataBaseUser.szCardID);										//	���֤����
		memcpy((char *)_DataBaseUser.nGroupIDs,(char *)pUserInfo->nGroupIDs,sizeof _DataBaseUser.nGroupIDs);					//	�û���ID
		memcpy((char *)_DataBaseUser.nPermissionIDs,(char *)pUserInfo->nPermissionIDs,sizeof _DataBaseUser.nPermissionIDs);		//	Ȩ��ID
		_DataBaseUser.nAuthorizeBeginDate		= pUserInfo->nAuthorizeBeginDate;												//	��Ȩʹ�ÿ�ʼ����
		_DataBaseUser.nAuthorizeEndDate			= pUserInfo->nAuthorizeEndDate;													//	��Ȩʹ�ý�ֹ����
		_DataBaseUser.nStatus					= pUserInfo->nStatus;															//	�û�ʹ��״̬
		memcpy(_DataBaseUser.szMobiles,pUserInfo->szMobiles,sizeof _DataBaseUser.szMobiles);									//	�ֻ�����,������
		memcpy(_DataBaseUser.szTelephones,pUserInfo->szTelephones,sizeof _DataBaseUser.szTelephones);							//	�绰����
		memcpy((char *)_DataBaseUser.nQQNumbers,(char *)pUserInfo->nQQNumbers,sizeof _DataBaseUser.nQQNumbers);					//	QQ����
		memcpy(_DataBaseUser.szEmails,pUserInfo->szEmails,sizeof _DataBaseUser.szEmails);										//	Email����
		strncpy(_DataBaseUser.szUserExplain,pUserInfo->szUserExplain,sizeof _DataBaseUser.szUserExplain);						//	�û�˵��,����������
		strncpy(_DataBaseUser.szIPs,pUserInfo->szIPs,sizeof _DataBaseUser.szIPs);												//	����IP
		strncpy(_DataBaseUser.szMacMark,pUserInfo->szMacMark,sizeof _DataBaseUser.szMacMark);									//	����MAC��ַ
		strncpy(_DataBaseUser.szDiskNum,pUserInfo->szDiskNum,sizeof _DataBaseUser.szDiskNum);									//	����Ӳ�����к�
		memcpy(_DataBaseUser.nLimitBeginTime,pUserInfo->nLimitBeginTime,sizeof _DataBaseUser.nLimitBeginTime);					//	���ƿ�ʼʱ��
		memcpy(_DataBaseUser.nLimitEndTime,pUserInfo->nLimitEndTime,sizeof _DataBaseUser.nLimitEndTime);						//	���ƽ���ʱ��
		_DataBaseUser.chLimitWeek				= pUserInfo->chLimitWeek;														//	��������,0x80������
		_DataBaseUser.nCanAssociateFundsAccount	= pUserInfo->FundBlock.nItems;													//	��ǰ�ʽ��ʺŽṹ����,���10��
		if (_DataBaseUser.pATPFund)
		{
			memcpy(_DataBaseUser.pATPFund,&pData[nATPUserInfoSize],nFundBlock);													//	�ʽ��ʺŽṹ��
		}
		
		_DataBaseUser.nCanRunAlgorithm			= pUserInfo->nCanRunAlgorithm;													//	����ͬʱ�����㷨����
		_DataBaseUser.nAlgorithmN				= pUserInfo->AlgorithmBlock.nItems;												//	�㷨����
		if (_DataBaseUser.pAlgorithmIDs)
		{
			memcpy(_DataBaseUser.pAlgorithmIDs,&pData[nATPUserInfoSize + nFundBlock],nAlgorithmBlock);							//	�㷨IDs
		}
		
		_DataBaseUser.nAlgorithmGroupN			= pUserInfo->AlgorithmGroupBlock.nItems;										//	�㷨�����
		if (_DataBaseUser.pAlgorithmGroupIDs)
		{
			memcpy(_DataBaseUser.pAlgorithmGroupIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock],nAlgorithmGroupBlock);	//	�㷨��IDs
		}
		
		_DataBaseUser.nServerN = pUserInfo->ServerBlock.nItems;
		if (_DataBaseUser.pServerIDs)
		{
			memcpy(_DataBaseUser.pServerIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock + nAlgorithmGroupBlock],nServerBlock);//	ר��������
		}
		
		_DataBaseUser.nServerGroupN				= pUserInfo->ServerGroupBlock.nItems;											//	�����������
		if (_DataBaseUser.pServerGroupIDs)
		{
			memcpy(_DataBaseUser.pServerGroupIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock],nServerGroupBlock);//	��������IDs
		}
		
 		CTime t = CTime::GetCurrentTime();
		_DataBaseUser.nCreateDate					= t.GetYear()*10000+t.GetMonth()*100+t.GetDay();																//	��������
 		_DataBaseUser.nCreateTime					= t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();															//	����ʱ��
 		_DataBaseUser.nLastDate						= 19800101;																	//	����½����
		_DataBaseUser.nLastTime						= 235959;																	//	����½ʱ��
		_DataBaseUser.nDeleteMark					= pUserInfo->nDeleteMark;													//	ɾ����־
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
			sprintf(sz,"����û�(NAME):%s ʧ��-��������ΪNULL",_DataBaseUser.szUserID);
			break;
		case EXISTDATA:
			sprintf(sz,"����û�(NAME):%s ʧ��-�÷��������Ѿ�����",_DataBaseUser.szUserID);
			break;
		case NEWERROR:
			sprintf(sz,"����û�(NAME):%s ʧ��-NEW����",_DataBaseUser.szUserID);
			break;
		case NULLHANDLE:
			sprintf(sz,"����û�(NAME):%s ʧ��-�������ΪNULL",_DataBaseUser.szUserID);
			break;
		case ZERORECORD:
			sprintf(sz,"����û�(NAME):%s ʧ��-û�иü�¼",_DataBaseUser.szUserID);
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
		_UserInfo.nSerialNumber					= _ATPDBSUser.nSerialNumber;											//	�Զ�����
		strncpy(_UserInfo.szUserID,_ATPDBSUser.szUserID,sizeof _UserInfo.szUserID);										//	�û�ID
		strncpy(_UserInfo.szPwd,_ATPDBSUser.szPwd,sizeof _UserInfo.szPwd);												//	�û�����
		strncpy(_UserInfo.szUserName,_ATPDBSUser.szUserName,sizeof _UserInfo.szUserName);								//	�û���
		strncpy(_UserInfo.szCardID,_ATPDBSUser.szCardID,sizeof _UserInfo.szCardID);										//	���֤����
		memcpy((char *)_UserInfo.nGroupIDs,(char *)_ATPDBSUser.nGroupIDs,sizeof _UserInfo.nGroupIDs);					//	�û���ID
		memcpy((char *)_UserInfo.nPermissionIDs,(char *)_ATPDBSUser.nPermissionIDs,sizeof _UserInfo.nPermissionIDs);	//	Ȩ��ID
		_UserInfo.nAuthorizeBeginDate			= _ATPDBSUser.nAuthorizeBeginDate;										//	��Ȩʹ�ÿ�ʼ����
		_UserInfo.nAuthorizeEndDate				= _ATPDBSUser.nAuthorizeEndDate;										//	��Ȩʹ�ý�ֹ����
		_UserInfo.nStatus						= _ATPDBSUser.nStatus;													//	�û�ʹ��״̬
		memcpy((char *)_UserInfo.szMobiles,(char *)_ATPDBSUser.szMobiles,sizeof _UserInfo.szMobiles);					//	�ֻ�����,������
		memcpy((char *)_UserInfo.szTelephones,(char *)_ATPDBSUser.szTelephones,sizeof _UserInfo.szTelephones);			//	�绰����
		memcpy((char *)_UserInfo.nQQNumbers,(char *)_ATPDBSUser.nQQNumbers,sizeof _UserInfo.nQQNumbers);				//	QQ����
		memcpy(_UserInfo.szEmails,_ATPDBSUser.szEmails,sizeof _UserInfo.szEmails);										//	Email����
		strncpy(_UserInfo.szUserExplain,_ATPDBSUser.szUserExplain,sizeof _UserInfo.szUserExplain);						//	�û�˵��,����������
		strncpy(_UserInfo.szIPs,_ATPDBSUser.szIPs,sizeof _UserInfo.szIPs);												//	����IP
		strncpy(_UserInfo.szMacMark,_ATPDBSUser.szMacMark,sizeof _UserInfo.szMacMark);									//	����MAC��ַ
		strncpy(_UserInfo.szDiskNum,_ATPDBSUser.szDiskNum,sizeof _UserInfo.szDiskNum);									//	����Ӳ�����к�
		memcpy((char *)_UserInfo.nLimitBeginTime,(char *)_ATPDBSUser.nLimitBeginTime,sizeof _UserInfo.nLimitBeginTime);	//	���ƿ�ʼʱ��
		memcpy((char *)_UserInfo.nLimitEndTime,(char *)_ATPDBSUser.nLimitEndTime,sizeof _UserInfo.nLimitEndTime);		//	���ƽ���ʱ��
		_UserInfo.chLimitWeek					= _ATPDBSUser.chLimitWeek;												//	��������,0x80������
		_UserInfo.FundBlock.nItems				= _ATPDBSUser.nCanAssociateFundsAccount;								//	��ǰ�ʽ��ʺŽṹ����Items,���10��         itemsize = sizeof(struATPID)
		_UserInfo.FundBlock.nItemSize			= sizeof struATPDataBaseFund;	
		_UserInfo.nCanRunAlgorithm				= _ATPDBSUser.nCanRunAlgorithm;											//	����ͬʱ�����㷨����
		_UserInfo.AlgorithmBlock.nItems			= _ATPDBSUser.nAlgorithmN;												//	�㷨����items  ,  itemsize = sizeof(struATPAutoID)
		_UserInfo.AlgorithmBlock.nItemSize		= sizeof struATPAutoAlgoID;
		_UserInfo.AlgorithmGroupBlock.nItems	= _ATPDBSUser.nAlgorithmGroupN;											//	�㷨����� items, itemsize = sizeof(struATPAutoID)
		_UserInfo.AlgorithmGroupBlock.nItemSize = sizeof struATPAutoID;
		_UserInfo.ServerBlock.nItems			= _ATPDBSUser.nServerN;
		_UserInfo.ServerBlock.nItemSize			= sizeof struATPAutoID;
		_UserInfo.ServerGroupBlock.nItems		= _ATPDBSUser.nServerGroupN;
		_UserInfo.ServerGroupBlock.nItemSize	= sizeof struATPAutoID;
		_UserInfo.nCreateDate					= _ATPDBSUser.nCreateDate;												//	��������
		_UserInfo.nCreateTime					= _ATPDBSUser.nCreateTime;												//	����ʱ��
		_UserInfo.nLastDate						= _ATPDBSUser.nLastDate;												//	����½����
		_UserInfo.nLastTime						= _ATPDBSUser.nLastTime;												//	����½ʱ��
		_UserInfo.nDeleteMark					= _ATPDBSUser.nDeleteMark;												//	ɾ����־
	}

	//////////////////////////////////////////////////////////////////////////
	nFundBlock				= _UserInfo.FundBlock.nItems*sizeof struATPDataBaseFund;
	nAlgorithmBlock			= _UserInfo.AlgorithmBlock.nItems*sizeof struATPAutoAlgoID;									//�㷨��
	nAlgorithmGroupBlock	= _UserInfo.AlgorithmGroupBlock.nItems*sizeof struATPAutoID;								//������
	nServerBlock			= _UserInfo.ServerBlock.nItems*sizeof struATPAutoID;
	nServerGroupBlock		= _UserInfo.ServerGroupBlock.nItems*sizeof struATPAutoID;
	*pnLen					= g_stru_ATPManageMsgHeadInfoSize + nATPUserInfoSize+ nFundBlock + nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock + nServerGroupBlock;
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"����û�(NAME):%s �ɹ�-NEW����",_DataBaseUser.szUserID);
		AddOperateLog(ID_ATPMANAGE_ADDUSER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"����û�(NAME):%s �ɹ�",_DataBaseUser.szUserID);
	AddOperateLog(ID_ATPMANAGE_ADDUSER,m_szAccount,sz);
	//���Ƶ���������ڴ���
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
	int nAlgorithmBlock			= 0;								//�㷨��
	int nAlgorithmGroupBlock	= 0;								//������
	int nServerBlock			= 0;								//��������
	int nServerGroupBlock		= 0;								//���������
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
		
		

		_DataBaseUser.nSerialNumber				= pUserInfo->nSerialNumber;														//	�Զ�����
		strncpy(_DataBaseUser.szUserID,pUserInfo->szUserID,sizeof _DataBaseUser.szUserID);										//	�û�ID
		strncpy(_DataBaseUser.szPwd,pUserInfo->szPwd,sizeof _DataBaseUser.szPwd);												//	�û�����
		strncpy(_DataBaseUser.szUserName,pUserInfo->szUserName,sizeof _DataBaseUser.szUserName);								//	�û���
		strncpy(_DataBaseUser.szCardID,pUserInfo->szCardID,sizeof _DataBaseUser.szCardID);										//	���֤����
		memcpy((char *)_DataBaseUser.nGroupIDs,(char *)pUserInfo->nGroupIDs,sizeof _DataBaseUser.nGroupIDs);					//	�û���ID
		memcpy((char *)_DataBaseUser.nPermissionIDs,(char *)pUserInfo->nPermissionIDs,sizeof _DataBaseUser.nPermissionIDs);		//	Ȩ��ID
		_DataBaseUser.nAuthorizeBeginDate		= pUserInfo->nAuthorizeBeginDate;												//	��Ȩʹ�ÿ�ʼ����
		_DataBaseUser.nAuthorizeEndDate			= pUserInfo->nAuthorizeEndDate;													//	��Ȩʹ�ý�ֹ����
		_DataBaseUser.nStatus					= pUserInfo->nStatus;															//	�û�ʹ��״̬
		memcpy(_DataBaseUser.szMobiles,pUserInfo->szMobiles,sizeof _DataBaseUser.szMobiles);									//	�ֻ�����,������
		memcpy(_DataBaseUser.szTelephones,pUserInfo->szTelephones,sizeof _DataBaseUser.szTelephones);							//	�绰����
		memcpy((char *)_DataBaseUser.nQQNumbers,(char *)pUserInfo->nQQNumbers,sizeof _DataBaseUser.nQQNumbers);					//	QQ����
		memcpy(_DataBaseUser.szEmails,pUserInfo->szEmails,sizeof _DataBaseUser.szEmails);										//	Email����
		strncpy(_DataBaseUser.szUserExplain,pUserInfo->szUserExplain,sizeof _DataBaseUser.szUserExplain);						//	�û�˵��,����������
		strncpy(_DataBaseUser.szIPs,pUserInfo->szIPs,sizeof _DataBaseUser.szIPs);												//	����IP
		strncpy(_DataBaseUser.szMacMark,pUserInfo->szMacMark,sizeof _DataBaseUser.szMacMark);									//	����MAC��ַ
		strncpy(_DataBaseUser.szDiskNum,pUserInfo->szDiskNum,sizeof _DataBaseUser.szDiskNum);									//	����Ӳ�����к�
		memcpy(_DataBaseUser.nLimitBeginTime,pUserInfo->nLimitBeginTime,sizeof _DataBaseUser.nLimitBeginTime);					//	���ƿ�ʼʱ��
		memcpy(_DataBaseUser.nLimitEndTime,pUserInfo->nLimitEndTime,sizeof _DataBaseUser.nLimitEndTime);						//	���ƽ���ʱ��
		_DataBaseUser.chLimitWeek				= pUserInfo->chLimitWeek;														//	��������,0x80������
		_DataBaseUser.nCanAssociateFundsAccount	= pUserInfo->FundBlock.nItems;													//	��ǰ�ʽ��ʺŽṹ����,���10��
		if (_DataBaseUser.pATPFund)
		{
			memcpy((char *)_DataBaseUser.pATPFund,&pData[nATPUserInfoSize],nFundBlock);														//	�ʽ��ʺŽṹ��
		}
		
		_DataBaseUser.nCanRunAlgorithm			= pUserInfo->nCanRunAlgorithm;													//	����ͬʱ�����㷨����
		_DataBaseUser.nAlgorithmN				= pUserInfo->AlgorithmBlock.nItems;												//	�㷨����
		if (_DataBaseUser.pAlgorithmIDs)
		{
			memcpy((char *)_DataBaseUser.pAlgorithmIDs,&pData[nATPUserInfoSize + nFundBlock],nAlgorithmBlock);								//	�㷨IDs
		}
		
		_DataBaseUser.nAlgorithmGroupN			= pUserInfo->AlgorithmGroupBlock.nItems;										//	�㷨�����
		if (_DataBaseUser.pAlgorithmGroupIDs)
		{
			memcpy((char *)_DataBaseUser.pAlgorithmGroupIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock],nAlgorithmGroupBlock);	//	�㷨��IDs
		}
		
		_DataBaseUser.nServerN = pUserInfo->ServerBlock.nItems;
		if (_DataBaseUser.pServerIDs)
		{
			memcpy((char *)_DataBaseUser.pServerIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock + nAlgorithmGroupBlock],nServerBlock);//	ר��������
		}
		
		_DataBaseUser.nServerGroupN				= pUserInfo->ServerGroupBlock.nItems;											//	�����������
		if (_DataBaseUser.pServerGroupIDs)
		{
			memcpy((char *)_DataBaseUser.pServerGroupIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock],nServerGroupBlock);//	��������IDs
		}
		
		_DataBaseUser.nCreateDate				= pUserInfo->nCreateDate;														//	��������
		_DataBaseUser.nCreateTime				= pUserInfo->nCreateTime;														//	����ʱ��
		_DataBaseUser.nLastDate					= pUserInfo->nLastDate;															//	����½����
		_DataBaseUser.nLastTime					= pUserInfo->nLastTime;															//	����½ʱ��
		_DataBaseUser.nDeleteMark				= pUserInfo->nDeleteMark;														//	ɾ����־

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
		strcpy(_Ans_Operate.szInfo,"�޸ĳɹ�");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"�޸��û�(NAME):%s ʧ��-��������ΪNULL",_DataBaseUser.szUserID);
			break;
		case EXISTDATA:
			sprintf(sz,"�޸��û�(NAME):%s ʧ��-�÷��������Ѿ�����",_DataBaseUser.szUserID);
			break;
		case NEWERROR:
			sprintf(sz,"�޸��û�(NAME):%s ʧ��-NEW����",_DataBaseUser.szUserID);
			break;
		case NULLHANDLE:
			sprintf(sz,"�޸��û�(NAME):%s ʧ��-�������ΪNULL",_DataBaseUser.szUserID);
			break;
		case ZERORECORD:
			sprintf(sz,"�޸��û�(NAME):%s ʧ��-û�иü�¼",_DataBaseUser.szUserID);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_MODIFYUSER,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"�޸�ʧ��");
	}
	

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"�޸��û�(NAME):%s �ɹ�-NEW����",_DataBaseUser.szUserID);
		AddOperateLog(ID_ATPMANAGE_MODIFYUSER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"�޸��û�(NAME):%s �ɹ�",_DataBaseUser.szUserID);
	AddOperateLog(ID_ATPMANAGE_MODIFYUSER,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
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
	int nAlgorithmBlock			= 0;								//�㷨��
	int nAlgorithmGroupBlock	= 0;								//������
	int nServerBlock			= 0;								//��������
	int nServerGroupBlock		= 0;								//���������
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
		
		


		_DataBaseUser.nSerialNumber				= pUserInfo->nSerialNumber;														//	�Զ�����
		strncpy(_DataBaseUser.szUserID,pUserInfo->szUserID,sizeof _DataBaseUser.szUserID);										//	�û�ID
		strncpy(_DataBaseUser.szPwd,pUserInfo->szPwd,sizeof _DataBaseUser.szPwd);												//	�û�����
		strncpy(_DataBaseUser.szUserName,pUserInfo->szUserName,sizeof _DataBaseUser.szUserName);								//	�û���
		strncpy(_DataBaseUser.szCardID,pUserInfo->szCardID,sizeof _DataBaseUser.szCardID);										//	���֤����
		memcpy((char *)_DataBaseUser.nGroupIDs,(char *)pUserInfo->nGroupIDs,sizeof _DataBaseUser.nGroupIDs);					//	�û���ID
		memcpy((char *)_DataBaseUser.nPermissionIDs,(char *)pUserInfo->nPermissionIDs,sizeof _DataBaseUser.nPermissionIDs);		//	Ȩ��ID
		_DataBaseUser.nAuthorizeBeginDate		= pUserInfo->nAuthorizeBeginDate;												//	��Ȩʹ�ÿ�ʼ����
		_DataBaseUser.nAuthorizeEndDate			= pUserInfo->nAuthorizeEndDate;													//	��Ȩʹ�ý�ֹ����
		_DataBaseUser.nStatus					= pUserInfo->nStatus;															//	�û�ʹ��״̬
		memcpy(_DataBaseUser.szMobiles,pUserInfo->szMobiles,sizeof _DataBaseUser.szMobiles);									//	�ֻ�����,������
		memcpy(_DataBaseUser.szTelephones,pUserInfo->szTelephones,sizeof _DataBaseUser.szTelephones);							//	�绰����
		memcpy((char *)_DataBaseUser.nQQNumbers,(char *)pUserInfo->nQQNumbers,sizeof _DataBaseUser.nQQNumbers);					//	QQ����
		memcpy(_DataBaseUser.szEmails,pUserInfo->szEmails,sizeof _DataBaseUser.szEmails);										//	Email����
		strncpy(_DataBaseUser.szUserExplain,pUserInfo->szUserExplain,sizeof _DataBaseUser.szUserExplain);						//	�û�˵��,����������
		strncpy(_DataBaseUser.szIPs,pUserInfo->szIPs,sizeof _DataBaseUser.szIPs);												//	����IP
		strncpy(_DataBaseUser.szMacMark,pUserInfo->szMacMark,sizeof _DataBaseUser.szMacMark);									//	����MAC��ַ
		strncpy(_DataBaseUser.szDiskNum,pUserInfo->szDiskNum,sizeof _DataBaseUser.szDiskNum);									//	����Ӳ�����к�
		memcpy(_DataBaseUser.nLimitBeginTime,pUserInfo->nLimitBeginTime,sizeof _DataBaseUser.nLimitBeginTime);					//	���ƿ�ʼʱ��
		memcpy(_DataBaseUser.nLimitEndTime,pUserInfo->nLimitEndTime,sizeof _DataBaseUser.nLimitEndTime);						//	���ƽ���ʱ��
		_DataBaseUser.chLimitWeek				= pUserInfo->chLimitWeek;														//	��������,0x80������
		_DataBaseUser.nCanAssociateFundsAccount	= pUserInfo->FundBlock.nItems;													//	��ǰ�ʽ��ʺŽṹ����,���10��
		if (_DataBaseUser.pATPFund)
		{
			memcpy(_DataBaseUser.pATPFund,&pData[nATPUserInfoSize],nFundBlock);														//	�ʽ��ʺŽṹ��
		}
		
		_DataBaseUser.nCanRunAlgorithm			= pUserInfo->nCanRunAlgorithm;													//	����ͬʱ�����㷨����
		_DataBaseUser.nAlgorithmN				= pUserInfo->AlgorithmBlock.nItems;												//	�㷨����
		if (_DataBaseUser.pAlgorithmIDs)
		{
			memcpy(_DataBaseUser.pAlgorithmIDs,&pData[nATPUserInfoSize + nFundBlock],nAlgorithmBlock);								//	�㷨IDs
		}
		
		_DataBaseUser.nAlgorithmGroupN			= pUserInfo->AlgorithmGroupBlock.nItems;										//	�㷨�����
		if (_DataBaseUser.pAlgorithmGroupIDs)
		{
			memcpy(_DataBaseUser.pAlgorithmGroupIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock],nAlgorithmGroupBlock);	//	�㷨��IDs
		}
		
		_DataBaseUser.nServerN = pUserInfo->ServerBlock.nItems;
		if (_DataBaseUser.pServerIDs)
		{
			memcpy(_DataBaseUser.pServerIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock + nAlgorithmGroupBlock],nServerBlock);//	ר��������
		}
		
		_DataBaseUser.nServerGroupN				= pUserInfo->ServerGroupBlock.nItems;											//	�����������
		if (_DataBaseUser.pServerGroupIDs)
		{
			memcpy(_DataBaseUser.pServerGroupIDs,&pData[nATPUserInfoSize + nFundBlock + nAlgorithmBlock + nAlgorithmGroupBlock + nServerBlock],nServerGroupBlock);//	��������IDs
		}
		
		_DataBaseUser.nCreateDate				= pUserInfo->nCreateDate;													//	��������
		_DataBaseUser.nCreateTime				= pUserInfo->nCreateTime;													//	����ʱ��
		_DataBaseUser.nLastDate					= pUserInfo->nLastDate;															//	����½����
		_DataBaseUser.nLastTime					= pUserInfo->nLastTime;															//	����½ʱ��
		_DataBaseUser.nDeleteMark				= pUserInfo->nDeleteMark;														//	ɾ����־

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
		strcpy(_Ans_Operate.szInfo,"ɾ���ɹ�");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"ɾ���û�(NAME):%s ʧ��-��������ΪNULL",_DataBaseUser.szUserID);
			break;
		case EXISTDATA:
			sprintf(sz,"ɾ���û�(NAME):%s ʧ��-�÷��������Ѿ�����",_DataBaseUser.szUserID);
			break;
		case NEWERROR:
			sprintf(sz,"ɾ���û�(NAME):%s ʧ��-NEW����",_DataBaseUser.szUserID);
			break;
		case NULLHANDLE:
			sprintf(sz,"ɾ���û�(NAME):%s ʧ��-�������ΪNULL",_DataBaseUser.szUserID);
			break;
		case 0:
		case ZERORECORD:
			sprintf(sz,"ɾ���û�(NAME):%s ʧ��-û�иü�¼",_DataBaseUser.szUserID);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_DELETEUSER,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"ɾ��ʧ��");
	}


	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"ɾ���û�(NAME):%s �ɹ�-NEW����",_DataBaseUser.szUserID);
		AddOperateLog(ID_ATPMANAGE_DELETEUSER,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"ɾ���û�(NAME):%s �ɹ�",_DataBaseUser.szUserID);
	AddOperateLog(ID_ATPMANAGE_DELETEUSER,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
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
	//nRet ��ѯ�������
	int nRet = g_pATPFileDBApi->QueryUser(pATPDataBaseUser_QUERY,m_szAccount,&pATPDataBaseUser);

	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"��ѯ�û� ʧ��-��������ΪNULL");
			break;
		case EXISTDATA:
			sprintf(sz,"��ѯ�û� ʧ��-���û����Ѿ�����");
			break;
		case NEWERROR:
			sprintf(sz,"��ѯ�û� ʧ��-NEW����");
			break;
		case NULLHANDLE:
			sprintf(sz,"��ѯ�û� ʧ��-�������ΪNULL");
			break;
		case 0:
		case ZERORECORD:
			sprintf(sz,"��ѯ�û� �ɹ�-û�м�¼");
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
		sprintf(sz,"��ѯ�û� �ɹ�-NEW����");
		AddOperateLog(ID_ATPMANAGE_QUERYUSERINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"��ѯ�û� �ɹ�");
	AddOperateLog(ID_ATPMANAGE_QUERYUSERINFO,m_szAccount,sz);
	stru_ATPUserInfo _ManagerInfo	= {0};
	int nFundBlock				= 0;
	int nAlgorithmBlock			= 0;								//�㷨��
	int nAlgorithmGroupBlock	= 0;								//������
	int nServerBlock			= 0;								//��������
	int nServerGroupBlock		= 0;								//���������

	int nHead	= g_stru_ATPManageMsgHeadInfoSize;
	int nCount = 0;
	pHead->nItem = nRet;
	memcpy(*ppOutData,(char *)pHead,nHead);
	nCount = nHead;
	for (i=0;i<nRet;i++)
	{
		_ManagerInfo.nSerialNumber					= pATPDataBaseUser[i].nSerialNumber;											//	�Զ�����
		strncpy(_ManagerInfo.szUserID,pATPDataBaseUser[i].szUserID,sizeof _ManagerInfo.szUserID);									//	�û�ID
		strncpy(_ManagerInfo.szPwd,pATPDataBaseUser[i].szPwd,sizeof _ManagerInfo.szPwd);												//	�û�����
		strncpy(_ManagerInfo.szUserName,pATPDataBaseUser[i].szUserName,sizeof _ManagerInfo.szUserName);								//	�û���
		strncpy(_ManagerInfo.szCardID,pATPDataBaseUser[i].szCardID,sizeof _ManagerInfo.szCardID);									//	���֤����
		memcpy((char *)_ManagerInfo.nGroupIDs,(char *)pATPDataBaseUser[i].nGroupIDs,sizeof _ManagerInfo.nGroupIDs);		//	�û���ID
		memcpy((char *)_ManagerInfo.nPermissionIDs,(char *)pATPDataBaseUser[i].nPermissionIDs,sizeof _ManagerInfo.nPermissionIDs);		//	Ȩ��ID
		_ManagerInfo.nAuthorizeBeginDate			= pATPDataBaseUser[i].nAuthorizeBeginDate;									//	��Ȩʹ�ÿ�ʼ����
		_ManagerInfo.nAuthorizeEndDate				= pATPDataBaseUser[i].nAuthorizeEndDate;										//	��Ȩʹ�ý�ֹ����
		_ManagerInfo.nStatus						= pATPDataBaseUser[i].nStatus;											//	�û�ʹ��״̬
		memcpy((char *)_ManagerInfo.szMobiles,(char *)pATPDataBaseUser[i].szMobiles,sizeof _ManagerInfo.szMobiles);					//	�ֻ�����,������
		memcpy((char *)_ManagerInfo.szTelephones,(char *)pATPDataBaseUser[i].szTelephones,sizeof _ManagerInfo.szTelephones);			//	�绰����
		memcpy((char *)_ManagerInfo.nQQNumbers,(char *)pATPDataBaseUser[i].nQQNumbers,sizeof _ManagerInfo.nQQNumbers);				//	QQ����
		memcpy(_ManagerInfo.szEmails,pATPDataBaseUser[i].szEmails,sizeof _ManagerInfo.szEmails);									//	Email����
		strncpy(_ManagerInfo.szUserExplain,pATPDataBaseUser[i].szUserExplain,sizeof _ManagerInfo.szUserExplain);						//	�û�˵��,����������
		strncpy(_ManagerInfo.szIPs,pATPDataBaseUser[i].szIPs,sizeof _ManagerInfo.szIPs);											//	����IP
		strncpy(_ManagerInfo.szMacMark,pATPDataBaseUser[i].szMacMark,sizeof _ManagerInfo.szMacMark);								//	����MAC��ַ
		strncpy(_ManagerInfo.szDiskNum,pATPDataBaseUser[i].szDiskNum,sizeof _ManagerInfo.szDiskNum);								//	����Ӳ�����к�
		memcpy((char *)_ManagerInfo.nLimitBeginTime,(char *)pATPDataBaseUser[i].nLimitBeginTime,sizeof _ManagerInfo.nLimitBeginTime);	//	���ƿ�ʼʱ��
		memcpy((char *)_ManagerInfo.nLimitEndTime,(char *)pATPDataBaseUser[i].nLimitEndTime,sizeof _ManagerInfo.nLimitEndTime);		//	���ƽ���ʱ��
		_ManagerInfo.chLimitWeek					= pATPDataBaseUser[i].chLimitWeek;											//	��������,0x80������
		_ManagerInfo.FundBlock.nItems				= pATPDataBaseUser[i].nCanAssociateFundsAccount;								//	��ǰ�ʽ��ʺŽṹ����Items,���10��         itemsize = sizeof(struATPID)
		_ManagerInfo.FundBlock.nItemSize			= sizeof struATPDataBaseFund;	
		_ManagerInfo.nCanRunAlgorithm				= pATPDataBaseUser[i].nCanRunAlgorithm;										//	����ͬʱ�����㷨����
		_ManagerInfo.AlgorithmBlock.nItems			= pATPDataBaseUser[i].nAlgorithmN;										//	�㷨����items  ,  itemsize = sizeof(struATPAutoID)
		_ManagerInfo.AlgorithmBlock.nItemSize		= sizeof struATPAutoAlgoID;
		_ManagerInfo.AlgorithmGroupBlock.nItems	= pATPDataBaseUser[i].nAlgorithmGroupN;										//	�㷨����� items, itemsize = sizeof(struATPAutoID)
		_ManagerInfo.AlgorithmGroupBlock.nItemSize = sizeof struATPAutoID;
		_ManagerInfo.ServerBlock.nItems			= pATPDataBaseUser[i].nServerN;
		_ManagerInfo.ServerBlock.nItemSize			= sizeof struATPAutoID;
		_ManagerInfo.ServerGroupBlock.nItems		= pATPDataBaseUser[i].nServerGroupN;
		_ManagerInfo.ServerGroupBlock.nItemSize	= sizeof struATPAutoID;
		_ManagerInfo.nCreateDate					= pATPDataBaseUser[i].nCreateDate;											//	��������
		_ManagerInfo.nCreateTime					= pATPDataBaseUser[i].nCreateTime;											//	����ʱ��
		_ManagerInfo.nLastDate						= pATPDataBaseUser[i].nLastDate;											//	����½����
		_ManagerInfo.nLastTime						= pATPDataBaseUser[i].nLastTime;											//	����½ʱ��
		_ManagerInfo.nDeleteMark					= pATPDataBaseUser[i].nDeleteMark;											//	ɾ����־

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
			sprintf(sz,"����㷨��(NAME):%s ʧ��-��������ΪNULL",_DataBaseAlgorithmGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"����㷨��(NAME):%s ʧ��-���㷨�����Ѿ�����",_DataBaseAlgorithmGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"����㷨��(NAME):%s ʧ��-NEW����",_DataBaseAlgorithmGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"����㷨��(NAME):%s ʧ��-�������ΪNULL",_DataBaseAlgorithmGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"����㷨��(NAME):%s ʧ��-û�иü�¼",_DataBaseAlgorithmGroup.szName);
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
		sprintf(sz,"����㷨��(NAME):%s �ɹ�-NEW����",_DataBaseAlgorithmGroup.szName);
		AddOperateLog(ID_ATPMANAGE_ADDALGORITHMGROUP,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"����㷨��(NAME):%s �ɹ�",_DataBaseAlgorithmGroup.szName);
	AddOperateLog(ID_ATPMANAGE_ADDALGORITHMGROUP,m_szAccount,sz);
	//���Ƶ���������ڴ���
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
		strcpy(_Ans_Operate.szInfo,"�޸ĳɹ�");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"�޸��㷨��(NAME):%s ʧ��-��������ΪNULL",_DataBaseAlgorithmGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"�޸��㷨��(NAME):%s ʧ��-�÷��������Ѿ�����",_DataBaseAlgorithmGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"�޸��㷨��(NAME):%s ʧ��-NEW����",_DataBaseAlgorithmGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"�޸��㷨��(NAME):%s ʧ��-�������ΪNULL",_DataBaseAlgorithmGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"�޸��㷨��(NAME):%s ʧ��-û�иü�¼",_DataBaseAlgorithmGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_MODIFYALGORITHMGROUP,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"�޸�ʧ��");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"�޸��㷨��(NAME):%s �ɹ�-NEW����",_DataBaseAlgorithmGroup.szName);
		AddOperateLog(ID_ATPMANAGE_MODIFYALGORITHMGROUP,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"�޸��㷨��(NAME):%s �ɹ�",_DataBaseAlgorithmGroup.szName);
	AddOperateLog(ID_ATPMANAGE_MODIFYALGORITHMGROUP,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
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
		strcpy(_Ans_Operate.szInfo,"�޸ĳɹ�");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"ɾ���㷨��(NAME):%s ʧ��-��������ΪNULL",_DataBaseAlgorithmGroup.szName);
			break;
		case EXISTDATA:
			sprintf(sz,"ɾ���㷨��(NAME):%s ʧ��-�÷��������Ѿ�����",_DataBaseAlgorithmGroup.szName);
			break;
		case NEWERROR:
			sprintf(sz,"ɾ���㷨��(NAME):%s ʧ��-NEW����",_DataBaseAlgorithmGroup.szName);
			break;
		case NULLHANDLE:
			sprintf(sz,"ɾ���㷨��(NAME):%s ʧ��-�������ΪNULL",_DataBaseAlgorithmGroup.szName);
			break;
		case ZERORECORD:
			sprintf(sz,"ɾ���㷨��(NAME):%s ʧ��-û�иü�¼",_DataBaseAlgorithmGroup.szName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_DELETEALGORITHMGROUP,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"�޸�ʧ��");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"ɾ���㷨��(NAME):%s �ɹ�-NEW����",_DataBaseAlgorithmGroup.szName);
		AddOperateLog(ID_ATPMANAGE_DELETEALGORITHMGROUP,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"ɾ���㷨��(NAME):%s �ɹ�",_DataBaseAlgorithmGroup.szName);
	AddOperateLog(ID_ATPMANAGE_DELETEALGORITHMGROUP,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int CHHNetFrameProcessor_ATPManagerServer::QueryAlgorithmGroup(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseAlgorithmGroup *pATPDataBaseAlgorithmGroup = NULL;
	int nATPAlgorithmGroupInfoSize = sizeof stru_ATPAlgorithmGroupInfo;
	//nRet ��ѯ�������
	int nRet = g_pATPFileDBApi->QueryAlgorithmGroup(m_szAccount,&pATPDataBaseAlgorithmGroup);

	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"��ѯ�㷨�� ʧ��-��������ΪNULL");
			break;
		case EXISTDATA:
			sprintf(sz,"��ѯ�㷨�� ʧ��-���û����Ѿ�����");
			break;
		case NEWERROR:
			sprintf(sz,"��ѯ�㷨�� ʧ��-NEW����");
			break;
		case NULLHANDLE:
			sprintf(sz,"��ѯ�㷨�� ʧ��-�������ΪNULL");
			break;
			case 0:
		case ZERORECORD:
			sprintf(sz,"��ѯ�㷨�� �ɹ�-û�м�¼");
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
		sprintf(sz,"��ѯ�㷨�� �ɹ�-NEW����");
		AddOperateLog(ID_ATPMANAGE_QUERYALGORITHMGROUPINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"��ѯ�㷨�� �ɹ�");
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

		return -1;//û�и��ļ�
	}
	file.Write(pData,nLen);
	file.Close();

	int k;
	//�򿪺ϲ��ļ� CombinateText.dat
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
			
			
			

			//���ļ����ݴӺϲ��ļ��ж���
			
			//char *pData = pCombinateFile->ReadFile(&ptr[1], lFileLen, lFileDate, lFileTime);
			}
			char *pData = pCombinateFile->ReadFile(Info->strFileName.GetBuffer(), lFileLen, lFileDate, lFileTime);
			Info->strFileName.ReleaseBuffer();
			if(pData)
			{	//��ȡ�ɹ��������ݱ���Ϊ�ļ�
				CHHDataChannelCtrl::write_HFCFile(szFileNameTemp, pData, -1, Info->lFileLen, lFileDate, lFileTime);
				
				//ɾ���ڴ�
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
	int nATPAlgorithmInfoSize					= sizeof stru_ATPAlgorithmInfo;		//�����)�ṹ�峤��

	
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
			//����
			strcpy(szAlgoType,"Strategy");
		}
		break;
	case 2:
		{
			//ѡ������
			strcpy(szAlgoType,"Condition");
		}
		break;
	case 3:
		{
			//ѡ�ɷ���
			strcpy(szAlgoType,"Program");
		}
		break;
	default:
		//�㷨
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
		memcpy((char*)&_DataBaseAlgorithm.AlgorithmID,(char*)&pAlgoInfo->AlgorithmID,sizeof GUID);							//	guid Ψһ
		strncpy(_DataBaseAlgorithm.szAlgorithmName,pAlgoInfo->szAlgorithmName, sizeof _DataBaseAlgorithm.szAlgorithmName);	//	�㷨��
		memcpy((char*)&_DataBaseAlgorithm.AlgorithVer,(char*)&pAlgoInfo->AlgorithVer,sizeof struDataBaseAlgorithmVer);		//	�㷨�汾
		_DataBaseAlgorithm.nVersionAttribute	= pAlgoInfo->nVersionAttribute;												//	�㷨�汾���� ���԰�֮��
		_DataBaseAlgorithm.nCharge				= pAlgoInfo->nCharge;														//	�Ƿ��շ�
		_DataBaseAlgorithm.nAlgoType			= pAlgoInfo->nAlgoType;														//	�㷨����
		_DataBaseAlgorithm.nGroupID				= pAlgoInfo->nGroupID;														//	�㷨��
		_DataBaseAlgorithm.nMarketType			= pAlgoInfo->nMarketType;
		_DataBaseAlgorithm.nLanguageType		= pAlgoInfo->nLanguageType;													//	�г�����
		strncpy(_DataBaseAlgorithm.szExplain,pAlgoInfo->szExplain,sizeof _DataBaseAlgorithm.szExplain);						//	�㷨˵��
		strncpy(_DataBaseAlgorithm.szWarning,pAlgoInfo->szWarning,sizeof _DataBaseAlgorithm.szWarning);						//	�㷨����
		strncpy(_DataBaseAlgorithm.szKeyword,pAlgoInfo->szKeyword,sizeof _DataBaseAlgorithm.szKeyword);						//	�㷨�ؼ���
		_DataBaseAlgorithm.nStatus				= pAlgoInfo->nStatus;														//	�㷨״̬
		strncpy(_DataBaseAlgorithm.szStopReason, pAlgoInfo->szStopReason,sizeof  _DataBaseAlgorithm.szStopReason);			//	�㷨����ԭ��
		CTime t = CTime::GetCurrentTime();
		_DataBaseAlgorithm.nCreateDate			= t.GetYear()*10000+t.GetMonth()*100+t.GetDay();							//	�㷨��������
		_DataBaseAlgorithm.nCreateTime			= t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();						//	�㷨����ʱ��
		strncpy(_DataBaseAlgorithm.szMainDllName, pAlgoInfo->szMainDllName, sizeof _DataBaseAlgorithm.szMainDllName);
		strncpy(_DataBaseAlgorithm.szPath, szPath, MAX_PATH);																//	�㷨ʹ��·��,·��Ҫָ��
		_DataBaseAlgorithm.nParams				= pAlgoInfo->AlgorithmParamBlock.nItems;									//	�㷨��������
		if (_DataBaseAlgorithm.pATPAlgorithmParams)
		{
			memcpy((char *)_DataBaseAlgorithm.pATPAlgorithmParams,(char *)&pData[nATPAlgorithmInfoSize],nAlgorithmParamBlock);		//	�㷨����
		}
		
		_DataBaseAlgorithm.nParamsEx			= pAlgoInfo->AlgorithmParamEXBlock.nItems;
		if (_DataBaseAlgorithm.pATPAlgorithmParamsEX)
		{
			memcpy((char *)_DataBaseAlgorithm.pATPAlgorithmParamsEX,(char *)&pData[nATPAlgorithmInfoSize+nAlgorithmParamBlock],nAlgorithmParamEXBlock);
		}
		
		_DataBaseAlgorithm.nDeleteMark			= pAlgoInfo->nDeleteMark;												//	ɾ�����
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
			sprintf(sz,"����㷨(NAME/GUID):%s ʧ��-��������ΪNULL",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case EXISTGUID:
		case EXISTDATA:
			sprintf(sz,"����㷨(NAME/GUID):%s ʧ��-���㷨�Ѿ�����",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case NEWERROR:
			sprintf(sz,"����㷨(NAME/GUID):%s ʧ��-NEW����",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case NULLHANDLE:
			sprintf(sz,"����㷨(NAME/GUID):%s ʧ��-�������ΪNULL",_DataBaseAlgorithm.szAlgorithmName);
			break;
		//	case 0:
		case ZERORECORD:
			sprintf(sz,"����㷨(NAME/GUID):%s ʧ��-û�иü�¼",_DataBaseAlgorithm.szAlgorithmName);
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
	//����Ŀ¼
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

	// ��ӳɹ��������ļ����浽Ӳ��
	CHHFileCombinate _Combinate;
	UnCombinateFile(&_Combinate,(char *)&pData[nATPAlgorithmInfoSize+nAlgorithmParamBlock+nAlgorithmParamEXBlock],nLen-(nATPAlgorithmInfoSize+nAlgorithmParamBlock+nAlgorithmParamEXBlock),szPath);



	//////////////////////////////////////////////////////////////////////////
	stru_ATPAlgorithmInfo _ATPAlgorithmInfo = {0};

	{
		_ATPAlgorithmInfo.nSerialNumber						= _ATPDBSAlgorithm.nSerialNumber;								//	�Զ�����
		memcpy((char *)&_ATPAlgorithmInfo.AlgorithmID,(char *)&_ATPDBSAlgorithm.AlgorithmID,sizeof GUID);					//	guid Ψһ
		strcpy((char *)_ATPAlgorithmInfo.szAlgorithmName,(char *)_ATPDBSAlgorithm.szAlgorithmName);							//	�㷨��
		memcpy((char *)&_ATPAlgorithmInfo.AlgorithVer,(char *)&_ATPDBSAlgorithm.AlgorithVer,sizeof struDataBaseAlgorithmVer);				//	�㷨�汾
		_ATPAlgorithmInfo.nVersionAttribute					= _ATPDBSAlgorithm.nVersionAttribute;							//	�㷨�汾���� ���԰�֮��
		_ATPAlgorithmInfo.nCharge							= _ATPDBSAlgorithm.nCharge;										//	�Ƿ��շ�
		_ATPAlgorithmInfo.nAlgoType							= _ATPDBSAlgorithm.nAlgoType;										//	�㷨����
		_ATPAlgorithmInfo.nGroupID							= _ATPDBSAlgorithm.nGroupID;									//	�㷨��
		_ATPAlgorithmInfo.nMarketType						= _ATPDBSAlgorithm.nMarketType;
		_ATPAlgorithmInfo.nLanguageType						= _ATPDBSAlgorithm.nLanguageType;
		strcpy(_ATPAlgorithmInfo.szExplain,_ATPDBSAlgorithm.szExplain);														//	�㷨˵��
		strcpy(_ATPAlgorithmInfo.szWarning,_ATPDBSAlgorithm.szWarning);														//	�㷨����
		strcpy(_ATPAlgorithmInfo.szKeyword,_ATPDBSAlgorithm.szKeyword);														//	�㷨�ؼ���
		_ATPAlgorithmInfo.nStatus							= _ATPDBSAlgorithm.nStatus;										//	�㷨״̬
		strcpy(_ATPAlgorithmInfo.szStopReason,_ATPDBSAlgorithm.szStopReason);												//	�㷨����ԭ��
		_ATPAlgorithmInfo.nCreateDate						= _ATPDBSAlgorithm.nCreateDate;									//	�㷨��������
		_ATPAlgorithmInfo.nCreateTime						= _ATPDBSAlgorithm.nCreateTime;									//	�㷨����ʱ��
		strcpy(_ATPAlgorithmInfo.szPath,_ATPDBSAlgorithm.szPath);															//	�㷨ʹ��·��,·��Ҫָ��
		_ATPAlgorithmInfo.AlgorithmParamBlock.nItems		= _ATPDBSAlgorithm.nParams;										//	�㷨��������  �㷨����
		_ATPAlgorithmInfo.AlgorithmParamBlock.nItemSize		= sizeof struATPDataBaseAlgorithmParam;
		_ATPAlgorithmInfo.AlgorithmParamEXBlock.nItems		= _ATPDBSAlgorithm.nParamsEx;
		_ATPAlgorithmInfo.AlgorithmParamEXBlock.nItemSize	= sizeof struATPDataBaseAlgorithmParamEX;
		_ATPAlgorithmInfo.nDeleteMark						= _ATPDBSAlgorithm.nDeleteMark;									//	ɾ����־
	}
	//////////////////////////////////////////////////////////////////////////
	nAlgorithmParamBlock									= _ATPAlgorithmInfo.AlgorithmParamBlock.nItems*_ATPAlgorithmInfo.AlgorithmParamBlock.nItemSize;
	nAlgorithmParamEXBlock									= _ATPAlgorithmInfo.AlgorithmParamEXBlock.nItems*_ATPAlgorithmInfo.AlgorithmParamEXBlock.nItemSize;

	*pnLen = g_stru_ATPManageMsgHeadInfoSize + nATPAlgorithmInfoSize + nAlgorithmParamBlock + nAlgorithmParamEXBlock;
	*ppOutData = new char[*pnLen];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"����㷨(NAME/GUID):%s �ɹ�-NEW����",_DataBaseAlgorithm.szAlgorithmName);
		AddOperateLog(ID_ATPMANAGE_ADDALGORITHM,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"����㷨(NAME/GUID):%s �ɹ�",_DataBaseAlgorithm.szAlgorithmName);
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
	int nAlgorithmParamEXBlock					= 0;									//�㷨��
	
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
		
		
		
		_DataBaseAlgorithm.nSerialNumber			= pAlgoInfo->nSerialNumber;										//	�Զ����� Ψһ
		memcpy((char *)&_DataBaseAlgorithm.AlgorithVer,(char *)&pAlgoInfo->AlgorithVer,sizeof stru_AlgorithmVer);	//	�㷨�汾
		_DataBaseAlgorithm.nVersionAttribute		= pAlgoInfo->nVersionAttribute;									//	�㷨�汾���� ���԰�֮��
		_DataBaseAlgorithm.nCharge					= pAlgoInfo->nCharge;											//	�Ƿ��շ�
		_DataBaseAlgorithm.nAlgoType					= pAlgoInfo->nAlgoType;											//	
		_DataBaseAlgorithm.nGroupID					= pAlgoInfo->nGroupID;											//	�㷨��
		_DataBaseAlgorithm.nMarketType				= pAlgoInfo->nMarketType;
		_DataBaseAlgorithm.nLanguageType			= pAlgoInfo->nLanguageType;
		strcpy(_DataBaseAlgorithm.szExplain,pAlgoInfo->szExplain);													//	�㷨˵��
		strcpy(_DataBaseAlgorithm.szWarning,pAlgoInfo->szWarning);													//	�㷨����
		strcpy(_DataBaseAlgorithm.szKeyword,pAlgoInfo->szKeyword);													//	�㷨�ؼ���
		_DataBaseAlgorithm.nStatus					= pAlgoInfo->nStatus;											//	�㷨״̬
		strcpy(_DataBaseAlgorithm.szStopReason,pAlgoInfo->szStopReason);											//	�㷨����ԭ��
		_DataBaseAlgorithm.nParams = pAlgoInfo->AlgorithmParamBlock.nItems;											//	�㷨��������
		if (_DataBaseAlgorithm.pATPAlgorithmParams)
		{
			memcpy((char *)_DataBaseAlgorithm.pATPAlgorithmParams,&pData[nATPUserInfoSize],nAlgorithmParamBlock);	//	�㷨����
		}
		
		_DataBaseAlgorithm.nParamsEx				= pAlgoInfo->AlgorithmParamEXBlock.nItems;
		if (_DataBaseAlgorithm.pATPAlgorithmParamsEX)
		{
			memcpy((char *)_DataBaseAlgorithm.pATPAlgorithmParamsEX,&pData[nATPUserInfoSize+nAlgorithmParamBlock],nAlgorithmParamEXBlock);
		}
		
		_DataBaseAlgorithm.nDeleteMark = pAlgoInfo->nDeleteMark;					//	ɾ�����


		
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
		strcpy(_Ans_Operate.szInfo,"�޸ĳɹ�");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"�޸��㷨(NAME/GUID):%s ʧ��-��������ΪNULL",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case EXISTGUID:
		case EXISTDATA:
			sprintf(sz,"�޸��㷨(NAME/GUID):%s ʧ��-���㷨�Ѿ�����",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case NEWERROR:
			sprintf(sz,"�޸��㷨(NAME/GUID):%s ʧ��-NEW����",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case NULLHANDLE:
			sprintf(sz,"�޸��㷨(NAME/GUID):%s ʧ��-�������ΪNULL",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case ZERORECORD:
			sprintf(sz,"�޸��㷨(NAME/GUID):%s ʧ��-û�иü�¼",_DataBaseAlgorithm.szAlgorithmName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_MODIFYALGORITHMINFO,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"�޸�ʧ��");
	}


	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"�޸��㷨(NAME/GUID):%s �ɹ�-NEW����",_DataBaseAlgorithm.szAlgorithmName);
		AddOperateLog(ID_ATPMANAGE_MODIFYALGORITHMINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"�޸��㷨(NAME/GUID):%s �ɹ�",_DataBaseAlgorithm.szAlgorithmName);
	AddOperateLog(ID_ATPMANAGE_MODIFYALGORITHMINFO,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
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
	int nAlgorithmParamEXBlock					= 0;									//�㷨��

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
		
		

		_DataBaseAlgorithm.nSerialNumber			= pAlgoInfo->nSerialNumber;										//	�Զ����� Ψһ
		memcpy((char *)&_DataBaseAlgorithm.AlgorithmID,(char *)&pAlgoInfo->AlgorithmID,sizeof GUID);				//	guid Ψһ
		strcpy(_DataBaseAlgorithm.szAlgorithmName,pAlgoInfo->szAlgorithmName);										//	�㷨��
		memcpy((char *)&_DataBaseAlgorithm.AlgorithVer,(char *)&pAlgoInfo->AlgorithVer,sizeof stru_AlgorithmVer);	//	�㷨�汾
		_DataBaseAlgorithm.nVersionAttribute		= pAlgoInfo->nVersionAttribute;									//	�㷨�汾���� ���԰�֮��
		_DataBaseAlgorithm.nCharge					= pAlgoInfo->nCharge;											//	�Ƿ��շ�
		_DataBaseAlgorithm.nAlgoType					= pAlgoInfo->nAlgoType;											//	�Ƿ��շ�
		_DataBaseAlgorithm.nGroupID					= pAlgoInfo->nGroupID;											//	�㷨��
		_DataBaseAlgorithm.nMarketType				= pAlgoInfo->nMarketType;
		_DataBaseAlgorithm.nLanguageType			= pAlgoInfo->nLanguageType;
		strcpy(_DataBaseAlgorithm.szExplain,pAlgoInfo->szExplain);													//	�㷨˵��
		strcpy(_DataBaseAlgorithm.szWarning,pAlgoInfo->szWarning);													//	�㷨����
		strcpy(_DataBaseAlgorithm.szKeyword,pAlgoInfo->szKeyword);													//	�㷨�ؼ���
		_DataBaseAlgorithm.nStatus					= pAlgoInfo->nStatus;											//	�㷨״̬
		strcpy(_DataBaseAlgorithm.szStopReason,pAlgoInfo->szStopReason);											//	�㷨����ԭ��
		_DataBaseAlgorithm.nCreateDate				= pAlgoInfo->nCreateDate;										//	�㷨��������
		_DataBaseAlgorithm.nCreateTime				= pAlgoInfo->nCreateTime;										//	�㷨����ʱ��
		strcpy(_DataBaseAlgorithm.szPath,pAlgoInfo->szPath);														//	�㷨ʹ��·��,·��Ҫָ��
		strcpy(_DataBaseAlgorithm.szMainDllName,pAlgoInfo->szMainDllName);											//	�㷨���dll�ļ���
		_DataBaseAlgorithm.nParams					= pAlgoInfo->AlgorithmParamBlock.nItems;						//	�㷨��������
		if (_DataBaseAlgorithm.pATPAlgorithmParams)
		{
			memcpy((char *)_DataBaseAlgorithm.pATPAlgorithmParams,&pData[nATPUserInfoSize],nAlgorithmParamBlock);	//	�㷨����
		}
		
		_DataBaseAlgorithm.nParamsEx				= pAlgoInfo->AlgorithmParamEXBlock.nItems;
		if (_DataBaseAlgorithm.pATPAlgorithmParamsEX)
		{
			memcpy((char *)_DataBaseAlgorithm.pATPAlgorithmParamsEX,&pData[nATPUserInfoSize+nAlgorithmParamBlock],nAlgorithmParamEXBlock);
		}
		
		_DataBaseAlgorithm.nDeleteMark				= pAlgoInfo->nDeleteMark;										//	ɾ�����



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
		strcpy(_Ans_Operate.szInfo,"ɾ���ɹ�");
	}
	else
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"ɾ���㷨(NAME/GUID):%s ʧ��-��������ΪNULL",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case EXISTGUID:
		case EXISTDATA:
			sprintf(sz,"ɾ���㷨(NAME/GUID):%s ʧ��-���㷨�Ѿ�����",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case NEWERROR:
			sprintf(sz,"ɾ���㷨(NAME/GUID):%s ʧ��-NEW����",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case NULLHANDLE:
			sprintf(sz,"ɾ���㷨(NAME/GUID):%s ʧ��-�������ΪNULL",_DataBaseAlgorithm.szAlgorithmName);
			break;
		case ZERORECORD:
			sprintf(sz,"ɾ���㷨(NAME/GUID):%s ʧ��-û�иü�¼",_DataBaseAlgorithm.szAlgorithmName);
			break;
		default:
			break;
		}

		AddOperateLog(ID_ATPMANAGE_DELETEALGORITHM,m_szAccount,sz);
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"ɾ��ʧ��");
	}


	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		char sz[128]={0};
		sprintf(sz,"ɾ���㷨(NAME/GUID):%s �ɹ�-NEW����",_DataBaseAlgorithm.szAlgorithmName);
		AddOperateLog(ID_ATPMANAGE_DELETEALGORITHM,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"ɾ���㷨(NAME/GUID):%s �ɹ�",_DataBaseAlgorithm.szAlgorithmName);
	AddOperateLog(ID_ATPMANAGE_DELETEALGORITHM,m_szAccount,sz);
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
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
	//nRet ��ѯ�������
	int nRet = g_pATPFileDBApi->QueryAlgorithm(pATPDataBaseAlgorithm_QUERY,m_szAccount,&pATPDataBaseAlgorithm);

	if (nRet<=0)
	{
		char sz[128]={0};
		switch (nRet)
		{
		case NOTINIT:
			sprintf(sz,"��ѯ�㷨 ʧ��-��������ΪNULL");
			break;
		case EXISTGUID:
		case EXISTDATA:
			sprintf(sz,"��ѯ�㷨 ʧ��-���㷨�Ѿ�����");
			break;
		case NEWERROR:
			sprintf(sz,"��ѯ�㷨 ʧ��-NEW����");
			break;
		case NULLHANDLE:
			sprintf(sz,"��ѯ�㷨 ʧ��-�������ΪNULL");
			break;
			case 0:
		case ZERORECORD:
			sprintf(sz,"��ѯ�㷨 �ɹ�-û�иü�¼");
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
		sprintf(sz,"��ѯ�㷨 �ɹ�-NEW����");
		AddOperateLog(ID_ATPMANAGE_QUERYALGORITHMINFO,m_szAccount,sz);
		return NEWERROR;
	}
	char sz[128]={0};
	sprintf(sz,"��ѯ�㷨 �ɹ�");
	AddOperateLog(ID_ATPMANAGE_QUERYALGORITHMINFO,m_szAccount,sz);
	stru_ATPAlgorithmInfo _ManagerInfo		= {0};
	int nAlgorithmParamBlock				= 0;
	int nAlgorithmParamEXBlock				= 0;									//�㷨��

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
		_ManagerInfo.nSerialNumber						= pATPDataBaseAlgorithm[i].nSerialNumber;								//	�Զ�����
		memcpy((char *)&_ManagerInfo.AlgorithmID,(char *)&pATPDataBaseAlgorithm[i].AlgorithmID,sizeof GUID);					//	guid Ψһ
		strcpy(_ManagerInfo.szAlgorithmName,pATPDataBaseAlgorithm[i].szAlgorithmName);											//	�㷨��
		memcpy((char *)&_ManagerInfo.AlgorithVer,(char *)&pATPDataBaseAlgorithm[i].AlgorithVer,sizeof struDataBaseAlgorithmVer);				//	�㷨�汾
		_ManagerInfo.nVersionAttribute					= pATPDataBaseAlgorithm[i].nVersionAttribute;							//	�㷨�汾���� ���԰�֮��
		_ManagerInfo.nCharge							= pATPDataBaseAlgorithm[i].nCharge;										//	�Ƿ��շ�
		_ManagerInfo.nAlgoType							= pATPDataBaseAlgorithm[i].nAlgoType;										//	
		_ManagerInfo.nGroupID							= pATPDataBaseAlgorithm[i].nGroupID;									//	�㷨��
		_ManagerInfo.nMarketType						= pATPDataBaseAlgorithm[i].nMarketType;
		_ManagerInfo.nLanguageType						= pATPDataBaseAlgorithm[i].nLanguageType;
		strcpy(_ManagerInfo.szExplain,pATPDataBaseAlgorithm[i].szExplain);														//	�㷨˵��
		strcpy(_ManagerInfo.szWarning,pATPDataBaseAlgorithm[i].szWarning);														//	�㷨����
		strcpy(_ManagerInfo.szKeyword,pATPDataBaseAlgorithm[i].szKeyword);														//	�㷨�ؼ���
		_ManagerInfo.nStatus							= pATPDataBaseAlgorithm[i].nStatus;										//	�㷨״̬
		strcpy(_ManagerInfo.szStopReason,pATPDataBaseAlgorithm[i].szStopReason);												//	�㷨����ԭ��
		_ManagerInfo.nCreateDate						= pATPDataBaseAlgorithm[i].nCreateDate;									//	�㷨��������
		_ManagerInfo.nCreateTime						= pATPDataBaseAlgorithm[i].nCreateTime;									//	�㷨����ʱ��
		strcpy(_ManagerInfo.szMainDllName,pATPDataBaseAlgorithm[i].szMainDllName);
		strcpy(_ManagerInfo.szPath,pATPDataBaseAlgorithm[i].szPath);															//	�㷨ʹ��·��,·��Ҫָ��
		_ManagerInfo.AlgorithmParamBlock.nItems			= pATPDataBaseAlgorithm[i].nParams;										//	�㷨��������  �㷨����
		_ManagerInfo.AlgorithmParamBlock.nItemSize		= nATPDataBaseAlgorithmParamSize;
		_ManagerInfo.AlgorithmParamEXBlock.nItems		= pATPDataBaseAlgorithm[i].nParamsEx;
		_ManagerInfo.AlgorithmParamEXBlock.nItemSize	= nATPDataBaseAlgorithmParamEXSize;
		_ManagerInfo.nDeleteMark						= pATPDataBaseAlgorithm[i].nDeleteMark;									//	ɾ����־


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
	//nRet ��ѯ�������
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
		strcpy(_Ans_Operate.szInfo,"��ӳɹ�");
	}
	else
	{
		_Ans_Operate.nResult = FALSE;
		strcpy(_Ans_Operate.szInfo,"���ʧ��");
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		return -1;
	}
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}


int	CHHNetFrameProcessor_ATPManagerServer::QueryAlgorithmLog(stru_ATPManageMsgHeadInfo *pHead,char *pData,int nLen,char **ppOutData,int *pnLen)
{
	struATPDataBaseAlgorithmLog *pATPDataBaseAlgorithmLog = NULL;
	int nATPOperateLogInfoSize = sizeof stru_ATPAlgorithmRunLogInfo;
	//nRet ��ѯ�������
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
	_AtpVigil_Manager_UserInfo.uUserId = pATPDataBaseManager->nSerialNumber;		//����ԱId
	//_AtpVigil_Manager_UserInfo.nConnectId;		//���Ӿ�� ������ʶΨһ�� 
	strcpy(_AtpVigil_Manager_UserInfo.chAccount,pATPDataBaseManager->szID);	//����Ա�˺�
	strcpy(_AtpVigil_Manager_UserInfo.chStatus,"��¼");  //״̬˵��
	//_AtpVigil_Manager_UserInfo.chInfo1[48];	//����
	//_AtpVigil_Manager_UserInfo.chInfo2[48];	//����
	//_AtpVigil_Manager_UserInfo.nAppType;		//����
	_AtpVigil_Manager_UserInfo.nAppDate = pATPDataBaseManager->nLastDate;		//����
	_AtpVigil_Manager_UserInfo.nAppTime = pATPDataBaseManager->nCreateTime;
	_AtpVigil_Manager_UserInfo.nLocalPort = m_nPort;   	//����˿�
	//_AtpVigil_Manager_UserInfo.nRemotePort;	//��¼�Ķ˿�
	CString str = GetLinkedIPAddress();
	_AtpVigil_Manager_UserInfo.nRemoteIP = inet_addr(GetLinkedIPAddress());  	//��¼��IP
	
	g_wndMsgTransfer.SendData(ID_ATPSVC_MC,0,ID_MSG_ATPVIGIL_MANAGER_ADMINLOGIN,&_AtpVigil_Manager_UserInfo,sizeof AtpVigil_Manager_UserInfo);
	
	//////////////////////////////////////////////////////////////////////////

	pLoginList->AddTail(_AtpVigil_Manager_UserInfo);


}
void CHHNetFrameProcessor_ATPManagerServer::RemoveLoginList(CList <AtpVigil_Manager_UserInfo,AtpVigil_Manager_UserInfo> *pLoginList,struATPDataBaseManager *pATPDataBaseManager)
{
	AtpVigil_Manager_UserInfo _AtpVigil_Manager_UserInfo={0};
	_AtpVigil_Manager_UserInfo.uUserId = pATPDataBaseManager->nSerialNumber;		//����ԱId
	strcpy(_AtpVigil_Manager_UserInfo.chAccount,pATPDataBaseManager->szID);	//����Ա�˺�
	strcpy(_AtpVigil_Manager_UserInfo.chStatus,"�Ͽ�����");  //״̬˵��
	_AtpVigil_Manager_UserInfo.nAppDate = pATPDataBaseManager->nLastDate;		//����
	_AtpVigil_Manager_UserInfo.nAppTime = pATPDataBaseManager->nCreateTime;
	_AtpVigil_Manager_UserInfo.nLocalPort = m_nPort;   	//����˿�
	_AtpVigil_Manager_UserInfo.nRemoteIP = inet_addr(GetLinkedIPAddress());  	//��¼��IP

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
		strcpy(_Ans_Operate.szInfo,"��¼�ɹ�");
		_Ans_Operate.nResult = TRUE;
		strcpy(m_szAccount,pATPManageLogin->szLoginID);

	}
	else
	{
		_Ans_Operate.nResult = FALSE;
		if (nRet == -1)
		{
			strcpy(_Ans_Operate.szInfo,"�������");
		} 
		else//-2
		{
			strcpy(_Ans_Operate.szInfo,"�ʻ�������");
		}
		
	}

	*ppOutData = new char[g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate];
	if (*ppOutData == NULL)
	{
		return -1;
	}
	*pnLen = g_stru_ATPManageMsgHeadInfoSize + sizeof struAns_Operate;
	//���Ƶ���������ڴ���
	pHead->nItem = 1;
	memcpy(*ppOutData,(char *)pHead,g_stru_ATPManageMsgHeadInfoSize);
	memcpy((char *)&(*ppOutData)[g_stru_ATPManageMsgHeadInfoSize],(char *)&_Ans_Operate,sizeof struAns_Operate);

	return nRet;
}