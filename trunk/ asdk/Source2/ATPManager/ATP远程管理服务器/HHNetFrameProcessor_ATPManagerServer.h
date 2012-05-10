#pragma once
#include "include/ATPFileDBApi.h"
#include "ATPManagerNetDefine.h"
#include "ATPManagerDataBaseDefine.h"
//#include "ATPManagerDBServerDefine.h"
// CHHNetFrameProcessor_ATPManagerServer 视图



class CHHNetFrameProcessor_ATPManagerServer : public CHHNetFrameProcessor
{
	DECLARE_DYNCREATE(CHHNetFrameProcessor_ATPManagerServer)

protected: 
	CHHNetFrameProcessor_ATPManagerServer();           // 动态创建所使用的受保护的构造函数
	virtual ~CHHNetFrameProcessor_ATPManagerServer();
public:
	virtual BOOL OnCreate();
	virtual BOOL OnDestroy(BOOL bInterrupt);
	virtual int  OnReceiveData(const CString &strSrcDN, const CString &strDesDN, CString &strSendDesDN, char *lpRecv, int nSize, unsigned int nID, unsigned int &nIDSend, BOOL &bDelRecv, char **lpSend, BOOL &bDelSend, int &nFlags, int &nErrLen);
	virtual int  OnSendData(CString &strSendDesDN, char **lpSend, unsigned int &nID, BOOL &bDelete, int &nFlags, int &nErrLen);

	int m_nID;
	char m_szAccount[16];
public:
	BOOL m_bInitiativeBreak;

public:
	int AddManager(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int ModifyManager(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int DelManager(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int QueryManager(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);

	int AddServerGroup(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int ModifyServerGroup(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int DelServerGroup(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int QueryServerGroup(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);

	int AddServer(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int ModifyServer(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int DelServer(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int QueryServer(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);

	int QueryPermission(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);

	int AddUserGroup(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int ModifyUserGroup(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int DelUserGroup(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int QueryUserGroup(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);

	int AddUser(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int ModifyUser(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int DelUser(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int QueryUser(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);

	int AddAlgorithmGroup(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int ModifyAlgorithmGroup(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int DelAlgorithmGroup(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int QueryAlgorithmGroup(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);

	int AddAlgorithm(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int ModifyAlgorithm(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int DelAlgorithm(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int QueryAlgorithm(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);

	int	AddOperateLog(int nOperateType,char *pAccount,char *pInfo);
	int	QueryOperateLog(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);

	int	AddAlgorithmLog(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	int	QueryAlgorithmLog(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);

	int ManagerLogin(stru_ATPManageMsgHeadInfo *,char *pData,int nLen,char **ppOutData,int *pnLen);
	void AddLoginList(CList <AtpVigil_Manager_UserInfo,AtpVigil_Manager_UserInfo> *pLoginList,struATPDataBaseManager *pATPDataBaseManager);
	void RemoveLoginList(CList <AtpVigil_Manager_UserInfo,AtpVigil_Manager_UserInfo> *pLoginList,struATPDataBaseManager *pATPDataBaseManager);

	int UnCombinateFile(CHHFileCombinate *pCombinateFile,char *pData,int nLen,char *pPath);

	int IsHavePermission(int nAccountType,const char *AccountID,int nPermissionType);
	//CATPFileDBApi *m_pATPFileDBApi;
};



struct  StackList
{
	int nID;
	CHHNetFrameProcessor_ATPManagerServer *pCHHNetFrameProcessor_ATPManagerServer;
};