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
	

	//���ճ��Ȳ���С����Ϣ��ͷ����
	if (nSize<g_stru_ATPManageMsgHeadInfoSize)
	{
		return 0;
	}
	stru_ATPManageMsgHeadInfo _MsgHeadInfo={0};
	memcpy((char*)&_MsgHeadInfo,lpRecv,g_stru_ATPManageMsgHeadInfoSize);

	switch (_MsgHeadInfo.nMsgType)
	{
	case ID_ATPMANAGE_CREATEMANAGER:					//50021	��������Ա(��������Ա)
		 {	 
			 //Receive_CREATEMANAGER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
			  OnRecvData(ID_ATPMANAGE_CREATEMANAGER,(char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize], nSize-g_stru_ATPManageMsgHeadInfoSize);
			 if (_MsgHeadInfo.nFlags == 1)
			 {
				 OnRecvData(ID_ATPMANAGE_CREATEMANAGER,(char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize], nSize-g_stru_ATPManageMsgHeadInfoSize);
			 }
			 
		 }break;
	case ID_ATPMANAGE_DELETEMANAGER:					//50022	ɾ������Ա(��������Ա)
		 {
			 OnRecvData(ID_ATPMANAGE_DELETEMANAGER,(char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize], nSize-g_stru_ATPManageMsgHeadInfoSize);
			 //Receive_DELETEMANAGER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYMANAGER:					//50023	�޸Ĺ���Ա(��������Ա������Ա)
		 {
			 Receive_MODIFYMANAGER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);	
		 }break;
	case ID_ATPMANAGE_QUERYMANAGERINFO:				//50024	��ѯ����Ա(��������Ա)
		 {
			 Receive_QUERYMANAGERINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
			 OnRecvData(ID_ATPMANAGE_QUERYMANAGERINFO,(char *)m_recvManagerData._pAnswerData,m_recvManagerData._nUsedMemory);
		 }break;
	case ID_ATPMANAGE_CREATESERVERGROUP:			//50031	������������(��������Ա)
		 {
			 Receive_CREATESERVERGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_DELETESERVERGROUP:			//50032	ɾ����������(��������Ա)
		 {
			 Receive_DELETESERVERGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYSERVERGROUP:			//50033	�޸ķ�������(��������Ա)
		 {
			 Receive_MODIFYSERVERGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYSERVERGROUPINFO:			//50034	��ѯ��������(��������Ա)
		 {
			 Receive_QUERYSERVERGROUPINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_CREATESERVER:					//50041	����������(��������Ա)
		 {
			 Receive_CREATESERVER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_DELETESERVER:					//50042	ɾ��������(��������Ա)
		 {
			 Receive_DELETESERVER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYSERVER:					//50043	�޸ķ�����(��������Ա)
		 {
			 Receive_MODIFYSERVER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYSERVERINFO:				//50044	��ѯ������(��������Ա)
		 {
			 Receive_QUERYSERVERINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYPERMISSIONINFO:			//50051	��ѯȨ��(��������Ա������Ա)
		 {
			 Receive_QUERYPERMISSIONINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_ADDALGORITHMGROUP:			//51011	����㷨��(����Ա)
		 {
			 Receive_ADDALGORITHMGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_DELETEALGORITHMGROUP:			//51012	ɾ���㷨��(����Ա)
		 {
			 Receive_DELETEALGORITHMGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYALGORITHMGROUP:			//51013	�޸��㷨��(����Ա)
		 {
			 Receive_MODIFYALGORITHMGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYALGORITHMGROUPINFO:		//51014��ѯ�㷨��(����Ա)
		 {
			 Receive_QUERYALGORITHMGROUPINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_ADDALGORITHM:					//51021	����㷨��Ϣ(����Ա)
		 {
			 Receive_ADDALGORITHM((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_DELETEALGORITHM:				//51022	ɾ���㷨��Ϣ(����Ա)
		 {
			 Receive_DELETEALGORITHM((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYALGORITHM:				//51023	�޸��㷨(����Ա)
		 {
			 Receive_MODIFYALGORITHM((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYALGORITHMINFO:			//51024	�޸��㷨��Ϣ(����Ա)
		 {
			 Receive_MODIFYALGORITHMINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYALGORITHMINFO:			//51025	��ѯ�㷨��Ϣ(����Ա)
		 {
			 Receive_QUERYALGORITHMINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYALGORITHMPARAM:			//51026	��ѯ�㷨����
		 {
			 Receive_QUERYALGORITHMPARAM((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYALGORITHMVERSION:		//51027	��ѯ�㷨��ʷ�汾
		 {
			 Receive_QUERYALGORITHMVERSION((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_ADDUSERGROUP:					//51041	����û���(����Ա)
		 {
			 Receive_ADDUSERGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_DELETEUSERGROUP:				//51042	ɾ���û���(����Ա)
		 {
			 Receive_DELETEUSERGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYUSERGROUP:				//51043	�޸��û���(����Ա)
		 {
			 Receive_MODIFYUSERGROUP((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYUSERGROUPINFO:			//51044	��ѯ�û�����Ϣ(����Ա)
		 {
			 Receive_QUERYUSERGROUPINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_ADDUSER:						//51051	����û�(����Ա)
		 {
			 Receive_ADDUSER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_DELETEUSER:					//51052	ɾ���û�(����Ա)
		 {
			 Receive_DELETEUSER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_MODIFYUSER:					//51053	�޸��û�(����Ա)
		 {
			 Receive_MODIFYUSER((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYUSERINFO:				//51054	��ѯ�û���Ϣ(����Ա)
		 {
			 Receive_QUERYUSERINFO((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYUSEROPERATELOG:			//51061	��ѯ�û�������־(����Ա)struReq_AT
		 {
			 Receive_QUERYUSEROPERATELOG((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYUSEDALGORITHM:			//51071	��ѯ�㷨ͳ����Ϣ(����Ա)
		 {
			 Receive_QUERYUSEDALGORITHM((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		 }break;
	case ID_ATPMANAGE_QUERYUSERALGORITHM:			//51072	��ѯ�û�ʹ���㷨ͳ����Ϣ(����Ա)
		  {
			  Receive_QUERYUSERALGORITHM((char*)&lpRecv[g_stru_ATPManageMsgHeadInfoSize],nSize-g_stru_ATPManageMsgHeadInfoSize);
		  }break;
	case ID_ATPMANAGE_QUERYSERVERALGORITHM:			//51073	��ѯ�����������㷨ͳ����Ϣ(����Ա)
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


//50021//	��������Ա(��������Ա)
void CATPNetCProcessor::Receive_CREATEMANAGER(const char *pRecvData,int nLength)
{

}

//50022//	ɾ������Ա(��������Ա)
void CATPNetCProcessor::Receive_DELETEMANAGER(const char *pRecvData,int nLength)
{

}

//50023//	�޸Ĺ���Ա(��������Ա������Ա)
void CATPNetCProcessor::Receive_MODIFYMANAGER(const char *pRecvData,int nLength)
{

}

//50024//	��ѯ����Ա(��������Ա)				
void CATPNetCProcessor::Receive_QUERYMANAGERINFO(const char *pRecvData,int nLength)
{
	AllocateMemory(&m_recvManagerData,nLength);
	stru_ATPManagerInfo *pManagerInfo = NULL;
	struATPDataBaseManager *pDataBaseManager = NULL;
	char *pData = NULL;
	int i = 0;
	int nUsedCount = 0;//ÿ��ʹ���ڴ�����
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

				strncpy(pDataBaseManager->szID,pManagerInfo->szID,sizeof pDataBaseManager->szID);									//	����ԱID
				strncpy(pDataBaseManager->szName,pManagerInfo->szName,sizeof pDataBaseManager->szName);								//	����
				strncpy(pDataBaseManager->szPwd,pManagerInfo->szPwd,sizeof pDataBaseManager->szPwd);								//	����
				pDataBaseManager->nStatus=pManagerInfo->nStatus;										//	����Ա״̬  0 1 2
				strncpy(pDataBaseManager->szExplain,pManagerInfo->szExplain,sizeof pDataBaseManager->szExplain);						//	˵����Ϣ
				memcpy((char*)pDataBaseManager->nPermissionIDs,(char*)pManagerInfo->nPermissionIDs,sizeof pDataBaseManager->nPermissionIDs);	//	Ȩ��ID
				pDataBaseManager->nCreateDate=pManagerInfo->nCreateDate;								//	��������
				pDataBaseManager->nCreateTime=pManagerInfo->nCreateTime;								//	����ʱ��
				pDataBaseManager->nLastDate=pManagerInfo->nLastDate;									//	����½����
				pDataBaseManager->nLastTime=pManagerInfo->nLastTime;									//	����½ʱ��
				pDataBaseManager->nDeleteMark=pManagerInfo->nDeleteMark;								//	ɾ����־
				pDataBaseManager->nServerN=pManagerInfo->ServerBlock.nItems;							//	����������
				memcpy(pDataBaseManager->pServerIDs,(char *)&pRecvData[blockBegin],nServerBlock);													//	������IDs
				pDataBaseManager->nServerGroupN=pManagerInfo->ServerGroupBlock.nItems;					//	�����������
				memcpy(pDataBaseManager->pServerGroupIDs,(char *)&pRecvData[blockBegin+nServerBlock],nServerGroupBlock);												//	��������IDs

		}

		nUsedCount = nstru_ATPManagerInfoSize + nServerBlock + nServerGroupBlock;
		i += nUsedCount;
		m_recvManagerData._nUsedMemory+=nUsedCount;
	}
	
	

	
}			

//��������
//0031//	������������(��������Ա)
void CATPNetCProcessor::Receive_CREATESERVERGROUP(const char *pRecvData,int nLength)
{

}
//50032//	ɾ����������(��������Ա)
void CATPNetCProcessor::Receive_DELETESERVERGROUP(const char *pRecvData,int nLength)
{

}
//50033//	�޸ķ�������(��������Ա)
void CATPNetCProcessor::Receive_MODIFYSERVERGROUP(const char *pRecvData,int nLength)
{

}
//50034//	��ѯ��������(��������Ա)
void CATPNetCProcessor::Receive_QUERYSERVERGROUPINFO(const char *pRecvData,int nLength)
{

}		

//������
//50041//	����������(��������Ա)
void CATPNetCProcessor::Receive_CREATESERVER(const char *pRecvData,int nLength)
{

}

//50042//	ɾ��������(��������Ա)
void CATPNetCProcessor::Receive_DELETESERVER(const char *pRecvData,int nLength)
{

}

//50043//	�޸ķ�����(��������Ա)
void CATPNetCProcessor::Receive_MODIFYSERVER(const char *pRecvData,int nLength)
{

}

//50044//	��ѯ������(��������Ա)
void CATPNetCProcessor::Receive_QUERYSERVERINFO(const char *pRecvData,int nLength)
{

}			

//Ȩ��

//50051//	��ѯȨ��(��������Ա������Ա)
void CATPNetCProcessor::Receive_QUERYPERMISSIONINFO(const char *pRecvData,int nLength)
{

}		

/************************************************************************/
/*                                       ����Ա                               */
/************************************************************************/

//�㷨��
//51011//	����㷨��(����Ա)
void CATPNetCProcessor::Receive_ADDALGORITHMGROUP(const char *pRecvData,int nLength)
{

}

//51012//	ɾ���㷨��(����Ա)
void CATPNetCProcessor::Receive_DELETEALGORITHMGROUP(const char *pRecvData,int nLength)
{

}

//51013//	�޸��㷨��(����Ա)
void CATPNetCProcessor::Receive_MODIFYALGORITHMGROUP(const char *pRecvData,int nLength)
{

}

//51014//��ѯ�㷨��(����Ա)
void CATPNetCProcessor::Receive_QUERYALGORITHMGROUPINFO(const char *pRecvData,int nLength)
{

}	

//�㷨
//51021//	����㷨��Ϣ(����Ա)
void CATPNetCProcessor::Receive_ADDALGORITHM(const char *pRecvData,int nLength)
{

}

//51022//	ɾ���㷨��Ϣ(����Ա)
void CATPNetCProcessor::Receive_DELETEALGORITHM(const char *pRecvData,int nLength)
{

}

//51023//	�޸��㷨(����Ա)
void CATPNetCProcessor::Receive_MODIFYALGORITHM(const char *pRecvData,int nLength)
{

}

//51024//	�޸��㷨��Ϣ(����Ա)
void CATPNetCProcessor::Receive_MODIFYALGORITHMINFO(const char *pRecvData,int nLength)
{

}		

//�㷨����
//51025//	��ѯ�㷨��Ϣ(����Ա)
void CATPNetCProcessor::Receive_QUERYALGORITHMINFO(const char *pRecvData,int nLength)
{

}

//51026//	��ѯ�㷨����
void CATPNetCProcessor::Receive_QUERYALGORITHMPARAM(const char *pRecvData,int nLength)
{

}

//51027//	��ѯ�㷨��ʷ�汾
void CATPNetCProcessor::Receive_QUERYALGORITHMVERSION(const char *pRecvData,int nLength)
{

}	

//�û���	
//51041//	����û���(����Ա)				 
void CATPNetCProcessor::Receive_ADDUSERGROUP(const char *pRecvData,int nLength)
{

}

//51042//	ɾ���û���(����Ա)
void CATPNetCProcessor::Receive_DELETEUSERGROUP(const char *pRecvData,int nLength)
{

}

//51043//	�޸��û���(����Ա)
void CATPNetCProcessor::Receive_MODIFYUSERGROUP(const char *pRecvData,int nLength)
{

}

//51044//	��ѯ�û�����Ϣ(����Ա)
void CATPNetCProcessor::Receive_QUERYUSERGROUPINFO(const char *pRecvData,int nLength)
{

}		

//�û�

//51051//	����û�(����Ա)
void CATPNetCProcessor::Receive_ADDUSER(const char *pRecvData,int nLength)
{

}

//51052//	ɾ���û�(����Ա)
void CATPNetCProcessor::Receive_DELETEUSER(const char *pRecvData,int nLength)
{

}

//51053//	�޸��û�(����Ա)
void CATPNetCProcessor::Receive_MODIFYUSER(const char *pRecvData,int nLength)
{

}

//51054//	��ѯ�û���Ϣ(����Ա)
void CATPNetCProcessor::Receive_QUERYUSERINFO(const char *pRecvData,int nLength)
{

}				

//�û�������־

//51061//	��ѯ�û�������־(����Ա)struReq_ATPManage_ATPManageOperateLog
void CATPNetCProcessor::Receive_QUERYUSEROPERATELOG(const char *pRecvData,int nLength)
{

}		

//�㷨��־

//51071//	��ѯ�㷨ͳ����Ϣ(����Ա)
void CATPNetCProcessor::Receive_QUERYUSEDALGORITHM(const char *pRecvData,int nLength)
{

}

//51072//	��ѯ�û�ʹ���㷨ͳ����Ϣ(����Ա)
void CATPNetCProcessor::Receive_QUERYUSERALGORITHM(const char *pRecvData,int nLength)
{

}

//51073//	��ѯ�����������㷨ͳ����Ϣ(����Ա)
void CATPNetCProcessor::Receive_QUERYSERVERALGORITHM(const char *pRecvData,int nLength)
{

}


