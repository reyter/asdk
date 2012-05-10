// WndBGS.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ATPManager.h"
#include "WndBGS.h"
#include "ATPACCEPT_MANAGER_DEFINE.H"
#include "include/ATPFileDBApi.h"
#include "ATPErrorDefine.h"
// CWndBGS

extern CATPFileDBApi *g_pATPFileDBApi;
extern HWND g_hWndMainWnd;

IMPLEMENT_DYNAMIC(CWndATPManagerBGS, CWndBGSManager)

CWndATPManagerBGS::CWndATPManagerBGS()
{

}

CWndATPManagerBGS::~CWndATPManagerBGS()
{
}


BEGIN_MESSAGE_MAP(CWndATPManagerBGS, CWndBGSManager)
	ON_MESSAGE(ID_HHFCBGSACTIVEAPP,OnMsgActiveMainWindow)
END_MESSAGE_MAP()



// CWndATPManagerBGS ��Ϣ�������

int CWndATPManagerBGS::OnRecvData(int nServiceClass, int nServiceID, int nID, void *pData, int nLen, BOOL &bDel)
{
// 	if (ID_ATPSVC_MANAGER != nServiceClass)
// 	{
// 		return -1;
// 	}
	switch(nID)
	{
	case ID_MSG_ATPACCEPT_MANAGER_VALIDATEUSER:
		{
			//do else

			char *pSendData=NULL;
			int nLen = 0;
			g_pATPFileDBApi->UserLogin((const char *)pData,&pSendData,&nLen);
			SendData(nServiceClass,0,nID,pSendData,nLen);
			if (pSendData)
			{
				delete []pSendData;
				pSendData = NULL;
			}
		}
		break;
	case ID_MSG_ATPACCEPT_MANAGER_GETFUNDACCOUNT:
		{

			//doelse

			char *pSendData=NULL;
			int nLen = 0;
			g_pATPFileDBApi->GetFundAccount((const char *)pData,&pSendData,&nLen);
			SendData(nServiceClass,0,nID,pSendData,nLen);
			if (pSendData)
			{
				delete []pSendData;
				pSendData = NULL;
			}
		}
		break;
	case ID_MSG_ATPACCEPT_MANAGER_GETALGOINFO:
		{

			//doelse

			char *pSendData=NULL;
			int nLen = 0;
			g_pATPFileDBApi->GetAlgoInfo((const char *)pData,&pSendData,&nLen);
			SendData(nServiceClass,0,nID,pSendData,nLen);
			if (pSendData)
			{
				delete []pSendData;
				pSendData = NULL;
			}
		}
		break;
	case ID_MSG_ATPACCEPT_MANAGER_GETSERVERINFO:
		{
			char *pSendData=NULL;
			int nLen = 0;
			g_pATPFileDBApi->GetServerInfo((const char *)pData,&pSendData,&nLen);
			SendData(nServiceClass,0,nID,pSendData,nLen);
			if (pSendData)
			{
				delete []pSendData;
				pSendData = NULL;
			}
		}
		break;
	case ID_MSG_ATPACCEPT_MANAGER_GETUSERINFO_WITHFUNDACCOUNT:
		{
			char *pSendData=NULL;
			int nLen = 0;
			
			g_pATPFileDBApi->GetAccountByFund((const char *)pData,&pSendData,&nLen);
			SendData(nServiceClass,0,nID,pSendData,nLen);
			if (pSendData)
			{
				delete []pSendData;
				pSendData = NULL;
			}

			
		}
		break;
	case ID_MSG_ATPACCEPT_MANAGER_GETFUNDACCOUNT_SECURITYTYPE:
		{
			char *pSendData=NULL;
			int nLen = 0;
			//////////////////////////////////////////////////////////////////////////
			int nAtpAccept_Manager_MsgHeadSize						= sizeof AtpAccept_Manager_MsgHead;
			int nAtpAccept_Manager_GetUserInfo_WithFundAccoutSize	= sizeof AtpAccept_Manager_GetUserInfo_WithFundAccout;
			AtpAccept_Manager_GetUserInfo_WithFundAccout _AtpAccept_Manager_GetUserInfo_WithFundAccout = {0};
			char *pDataT = new char[nAtpAccept_Manager_MsgHeadSize+nAtpAccept_Manager_GetUserInfo_WithFundAccoutSize];
			char *pD = (char *)pData;
			memcpy(pDataT,pD,nAtpAccept_Manager_MsgHeadSize);


			AtpAccept_Manager_GetFundAccount_SecurityType *pAtpAccept_Manager_GetFundAccount_SecurityType = NULL;
			pAtpAccept_Manager_GetFundAccount_SecurityType = (AtpAccept_Manager_GetFundAccount_SecurityType *)&pD[nAtpAccept_Manager_MsgHeadSize];
			strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout.fundAccount.chOrgID,pAtpAccept_Manager_GetFundAccount_SecurityType->chOrgID);//Ӫҵ������
			strcpy(_AtpAccept_Manager_GetUserInfo_WithFundAccout.fundAccount.chUserID,pAtpAccept_Manager_GetFundAccount_SecurityType->chUserID);//�ʽ��ʺ�
			memcpy(&pDataT[nAtpAccept_Manager_MsgHeadSize],&_AtpAccept_Manager_GetUserInfo_WithFundAccout,nAtpAccept_Manager_GetUserInfo_WithFundAccoutSize);
			//////////////////////////////////////////////////////////////////////////
			g_pATPFileDBApi->GetFundMarket((const char *)pDataT,&pSendData,&nLen);
			SendData(nServiceClass,0,nID,pSendData,nLen);
			if (pSendData)
			{
				delete []pSendData;
				pSendData = NULL;
			}
		}
	case ID_MSG_ATPACCEPT_MANAGER_SET_ALGO_RUNLOG://д
		{
			char *pD = (char *)pData;
			int nAtpAccept_Manager_MsgHeadSize									= sizeof AtpAccept_Manager_MsgHead;
			AtpAccept_Manager_SetAlgoRunLog *pAtpAccept_Manager_SetAlgoRunLog = (AtpAccept_Manager_SetAlgoRunLog *)&pD[nAtpAccept_Manager_MsgHeadSize];
			struATPDataBaseAlgorithmLog _struATPDataBaseAlgorithmLog = {0};
			

			memcpy(&_struATPDataBaseAlgorithmLog.AlgorithmID,&pAtpAccept_Manager_SetAlgoRunLog->AlgorithmID,sizeof GUID);				//	�㷨ID
			memcpy(_struATPDataBaseAlgorithmLog.szUserID,pAtpAccept_Manager_SetAlgoRunLog->szUserID,16);				//	�û�ID
			_struATPDataBaseAlgorithmLog.iAlgoInsID = pAtpAccept_Manager_SetAlgoRunLog->iAlgoInsID;					//	�㷨����ʵ��ID		20110916		
			_struATPDataBaseAlgorithmLog.nServerID = pAtpAccept_Manager_SetAlgoRunLog->nServerID;				//	������ID		
			_struATPDataBaseAlgorithmLog.nStatus = pAtpAccept_Manager_SetAlgoRunLog->nStatus;					//	�㷨����״̬
			_struATPDataBaseAlgorithmLog.nRunBeginDate = pAtpAccept_Manager_SetAlgoRunLog->nRunBeginDate;				//	���п�ʼ����
			_struATPDataBaseAlgorithmLog.nRunBeginTime = pAtpAccept_Manager_SetAlgoRunLog->nRunBeginTime;				//	���п�ʼʱ��
			_struATPDataBaseAlgorithmLog.nRunEndDate = pAtpAccept_Manager_SetAlgoRunLog->nRunEndDate;				//	���н�������
			_struATPDataBaseAlgorithmLog.nRunEndTime = pAtpAccept_Manager_SetAlgoRunLog->nRunEndTime;				//	���н���ʱ��
			_struATPDataBaseAlgorithmLog.nVolume = pAtpAccept_Manager_SetAlgoRunLog->nVolume;					//	�ɽ���
			_struATPDataBaseAlgorithmLog.nTurnover = pAtpAccept_Manager_SetAlgoRunLog->nTurnover;					//	�ɽ���
			memcpy(_struATPDataBaseAlgorithmLog.nCount,pAtpAccept_Manager_SetAlgoRunLog->nCount,sizeof pAtpAccept_Manager_SetAlgoRunLog->nCount);					//	���ײ���ͳ�ƣ��������������ֲֲ�ѯ���ɽ���ѯ��ί�в�ѯ,�ɳ�����ѯ���ʲ���ѯ
			_struATPDataBaseAlgorithmLog.nCompletion = pAtpAccept_Manager_SetAlgoRunLog->nCompletion;				//	�㷨��ɶ�,�ٷֱ�
			memcpy(_struATPDataBaseAlgorithmLog.szAlgoRemark,pAtpAccept_Manager_SetAlgoRunLog->szAlgoRemark,256);			// �㷨������	
			
			g_pATPFileDBApi->AddAlgorithmLog(&_struATPDataBaseAlgorithmLog);
			
		}
		break;
	case ID_MSG_ATPACCEPT_MANAGER_UPDATE_ALGO_RUNLOG://��
		{
// 			char *pSendData=NULL;
// 			int nLen = 0;
// 
// 			g_pATPFileDBApi->GetAccountByFund((const char *)k,&pSendData,&nLen);
// 			SendData(nServiceClass,0,nID,pSendData,nLen);
// 			if (pSendData)
// 			{
// 				delete []pSendData;
// 				pSendData = NULL;
// 			}
		}
		break;
	case ID_MSG_ATPACCEPT_MANAGER_UPLOADALGO_TACTICS:
		{
			char *pD = (char *)pData;
			int nAtpAccept_Manager_MsgHeadSize									= sizeof AtpAccept_Manager_MsgHead;
			AtpAccept_Manager_UploadTactics *pAtpAccept_Manager_UploadTactics = (AtpAccept_Manager_UploadTactics *)&pD[nAtpAccept_Manager_MsgHeadSize];
			struATPDataBaseAlgorithm _DataBaseAlgorithm = {0};

			_DataBaseAlgorithm.pATPAlgorithmParams = NULL;
			_DataBaseAlgorithm.pATPAlgorithmParamsEX = NULL;



			//////////////////////////////////////////////////////////////////////////
			char szAlgoType[MAX_PATH]={0};
			switch(pAtpAccept_Manager_UploadTactics->nAlgoType)
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
			sprintf(szPath,"..\\Script\\%s\\%s",pAtpAccept_Manager_UploadTactics->szUserId,szAlgoType);
			ASSERT(_CrtCheckMemory());
			{
				memcpy((char*)&_DataBaseAlgorithm.AlgorithmID,(char*)&pAtpAccept_Manager_UploadTactics->guid,sizeof GUID);							//	guid Ψһ
				strncpy(_DataBaseAlgorithm.szAlgorithmName,pAtpAccept_Manager_UploadTactics->szAlgorithmName, sizeof _DataBaseAlgorithm.szAlgorithmName);	//	�㷨��
				_DataBaseAlgorithm.nAlgoType			= pAtpAccept_Manager_UploadTactics->nAlgoType;														//	�㷨����
				_DataBaseAlgorithm.nMarketType			= pAtpAccept_Manager_UploadTactics->nSecurityType;
				_DataBaseAlgorithm.nLanguageType		= pAtpAccept_Manager_UploadTactics->nLanguageType;													//	�г�����
				strncpy(_DataBaseAlgorithm.szExplain,pAtpAccept_Manager_UploadTactics->szExplain,sizeof _DataBaseAlgorithm.szExplain);						//	�㷨˵��
				CTime t = CTime::GetCurrentTime();
				_DataBaseAlgorithm.nCreateDate			= t.GetYear()*10000+t.GetMonth()*100+t.GetDay();							//	�㷨��������
				_DataBaseAlgorithm.nCreateTime			= t.GetHour()*10000+t.GetMinute()*100+t.GetSecond();						//	�㷨����ʱ��
				strncpy(_DataBaseAlgorithm.szPath, szPath, MAX_PATH);																//	�㷨ʹ��·��,·��Ҫָ��

				strcpy(_DataBaseAlgorithm.szManagerID,pAtpAccept_Manager_UploadTactics->szUserId);
			}
			ASSERT(_CrtCheckMemory());
			//////////////////////////////////////////////////////////////////////////

			struATPDataBaseAlgorithm _ATPDBSAlgorithm	= {0};
			int nRet = g_pATPFileDBApi->AddAlgorithm(&_DataBaseAlgorithm,&_ATPDBSAlgorithm,TRUE);
			char szErr[128]={0};
			AtpAccept_Manager_UploadTactics_Result _AtpAccept_Manager_UploadTactics_Result = {0};
			if (nRet != 0)
			{
				_AtpAccept_Manager_UploadTactics_Result.result.fail.nResult=-1;
				switch (nRet)
				{
				case NOTINIT:
					sprintf(_AtpAccept_Manager_UploadTactics_Result.result.fail.szError,"����㷨(NAME/GUID):%s ʧ��-��������ΪNULL",_DataBaseAlgorithm.szAlgorithmName);
					break;
				case EXISTGUID:
				case EXISTDATA:
					sprintf(_AtpAccept_Manager_UploadTactics_Result.result.fail.szError,"����㷨(NAME/GUID):%s ʧ��-���㷨�Ѿ�����",_DataBaseAlgorithm.szAlgorithmName);
					break;
				case NEWERROR:
					sprintf(_AtpAccept_Manager_UploadTactics_Result.result.fail.szError,"����㷨(NAME/GUID):%s ʧ��-NEW����",_DataBaseAlgorithm.szAlgorithmName);
					break;
				case NULLHANDLE:
					sprintf(_AtpAccept_Manager_UploadTactics_Result.result.fail.szError,"����㷨(NAME/GUID):%s ʧ��-�������ΪNULL",_DataBaseAlgorithm.szAlgorithmName);
					break;
					//	case 0:
				case ZERORECORD:
					sprintf(_AtpAccept_Manager_UploadTactics_Result.result.fail.szError,"����㷨(NAME/GUID):%s ʧ��-û�иü�¼",_DataBaseAlgorithm.szAlgorithmName);
					break;
				default:
					break;
				}
				

			}
			else
			{
				strcpy(_AtpAccept_Manager_UploadTactics_Result.result.success.szFileName,pAtpAccept_Manager_UploadTactics->szAlgorithmName);
				strcpy(_AtpAccept_Manager_UploadTactics_Result.result.success.szPath,szPath);
			}
			
			int nLen = nAtpAccept_Manager_MsgHeadSize+sizeof AtpAccept_Manager_UploadTactics_Result;
			char *pSendData = new char[nLen];
			memcpy(pSendData,pD,nAtpAccept_Manager_MsgHeadSize);
			memcpy(&pSendData[nAtpAccept_Manager_MsgHeadSize],&_AtpAccept_Manager_UploadTactics_Result,sizeof AtpAccept_Manager_UploadTactics_Result);
			SendData(nServiceClass,0,nID,pSendData,nLen);


		}
		break;
	default: 
		break;
	}


	int i = 1;
	return i;
}

LRESULT CWndATPManagerBGS::OnMsgActiveMainWindow(WPARAM wParam,LPARAM lParam)
{
	BOOL bRet = TRUE;
	//�����
	if(::IsWindowVisible(g_hWndMainWnd))
	{
		::SetWindowPos(g_hWndMainWnd,HWND_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}
	else
	{
		::ShowWindow(g_hWndMainWnd,SW_SHOW);
	}

	return bRet;
	return 0;
}