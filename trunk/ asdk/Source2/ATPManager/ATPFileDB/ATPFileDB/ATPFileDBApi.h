#pragma once
#include "ATPManagerDataBaseDefine.h"
#include "ATPDataBase.h"
#include "ATPLogBase.h"
#include "ATPVigil_Manager_Define.h"

#ifdef _ATPFILEDBAPI_
#define ATPFILEDBAPI _declspec(dllexport) 
#else		
#define ATPFILEDBAPI _declspec(dllimport) 	
#endif
// CATPFileDBApi 命令目标

class ATPFILEDBAPI CATPFileDBApi
{
public:
	CATPFileDBApi();
	virtual ~CATPFileDBApi();

public:


	int WriteATPFileDB();
	int ReadATPFileDB();
public:
	int AddManager(IN struATPDataBaseManager *pInData,OUT struATPDataBaseManager *pOutATPDBSManager);
	int ModifyManager(IN struATPDataBaseManager *pInData);
	int DelManager(IN struATPDataBaseManager *pInData);
	int QueryManager(IN char *pAccount,OUT struATPDataBaseManager **ppOutData);

	int AddServerGroup(IN struATPDataBaseServerGroup *pInData,OUT struATPDataBaseServerGroup *pOutData);
	int ModifyServerGroup(IN struATPDataBaseServerGroup *pInData);
	int DelServerGroup(IN struATPDataBaseServerGroup *pInData);
	int QueryServerGroup(OUT struATPDataBaseServerGroup **ppOutData);

	int AddServer(IN struATPDataBaseServer *pInData,OUT struATPDataBaseServer *pOutData);
	int ModifyServer(IN struATPDataBaseServer *pInData);
	int DelServer(IN struATPDataBaseServer *pInData);
	int QueryServer(IN struATPDataBaseServer_QUERY *pInData,OUT struATPDataBaseServer **ppOutData);

	//int AddPermission(struATPDataBasePermission *);
	//int ModifyPermission(struATPDataBasePermission *);
	//int DelPermission(struATPDataBasePermission *);
	int QueryPermission(OUT struATPDataBasePermission **ppOutData);

	int AddUserGroup(IN struATPDataBaseUserGroup *pInData,OUT struATPDataBaseUserGroup *pOutData);
	int ModifyUserGroup(IN struATPDataBaseUserGroup *pInData);
	int DelUserGroup(IN struATPDataBaseUserGroup *pInData);
	int QueryUserGroup(IN char *pAccount,OUT struATPDataBaseUserGroup **ppOutData);

	int AddUser(IN struATPDataBaseUser *pInData,OUT struATPDataBaseUser *pOutData);
	int ModifyUser(IN struATPDataBaseUser *pInData);
	int DelUser(IN struATPDataBaseUser *pInData);
	int QueryUser(IN struATPDataBaseUser_QUERY *,IN char *pAccount,OUT struATPDataBaseUser **ppOutData);

	int AddAlgorithmGroup(IN struATPDataBaseAlgorithmGroup *pInData,OUT struATPDataBaseAlgorithmGroup *pOutData);
	int ModifyAlgorithmGroup(IN struATPDataBaseAlgorithmGroup *pInData);
	int DelAlgorithmGroup(IN struATPDataBaseAlgorithmGroup *pInData);
	int QueryAlgorithmGroup(IN char *pAccount,OUT struATPDataBaseAlgorithmGroup **ppOutData);

	int AddAlgorithm(IN struATPDataBaseAlgorithm *pInData,OUT struATPDataBaseAlgorithm *pOutData,BOOL bScript=FALSE);
	int ModifyAlgorithm(IN struATPDataBaseAlgorithm *pInData);
	int DelAlgorithm(IN struATPDataBaseAlgorithm *pInData);
	int QueryAlgorithm(IN struATPDataBaseAlgorithm_QUERY *,IN char *pAccount,OUT struATPDataBaseAlgorithm **ppOutData);

	int	AddOperateLog(IN struATPDataBaseOperateLog *pInData);
	int	QueryOperateLog(IN struATPDataBaseOperateLog_QUERY *,OUT struATPDataBaseOperateLog **ppOutData);

	int	AddAlgorithmLog(IN struATPDataBaseAlgorithmLog *pInData);
	int	QueryAlgorithmLog(IN struATPDataBaseAlgorithmLog_QUERY *pInData,OUT struATPDataBaseAlgorithmLog **ppOutData);

	///进程间通讯函数
	//验证用户 
	int UserLogin(IN const char *pReqData,OUT char **ppAnsData,int *pnLen);
	//获取资金账号的信息 
	int GetFundAccount(IN const char *pReqData,OUT char **ppAnsData,int *pnLen);
	//获取用户可以使用的算法及算法使用信息 及算法授权服务器组 
	int GetAlgoInfo(IN const char *pReqData,OUT char **ppAnsData,int *pnLen);
	int GetServerInfo(IN const char *pReqData,OUT char **ppAnsData,int *pnLen);
	/**
	*	bFlag 是否被GetFundMarket调用
	*/
	int GetAccountByFund(IN const char *pReqData,OUT char **ppAnsData,int *pnLen,BOOL bFlag = FALSE);
	int GetFundMarket(IN const char *pReqData,OUT char **ppAnsData,int *pnLen);
	//////////////////////////////////////////////////////////////////////////
	int ManagerLogin(IN struReq_ATPManageLogin *pInData);

	int IsHavePermission(int nAccountType,const char *AccountID,int nPermissionType);


	/*	let the information of the algorithm run across to the wirte db file module.
		*	@param	nServiceType	the type of security
		*	@param	pAlgoInfo		the information of the algorithm
		*	@param	pParamInfo		the information of the algorithm's parameters.
		*	@return If the function succeeds, the return value is zero.
		*/
		typedef int (CALLBACK * alg_run_across_alg_inforamtion)(
		int nServiceType,
		const Atp_Algorithm_Info* pAlgoInfo,
		const Atp_Algoparam_Info* pParamInfo
		);

	CList <AtpVigil_Manager_UserInfo,AtpVigil_Manager_UserInfo>* GetLoginList();
private:
	CATPDataBase *m_pATPDataBase;
	CATPLogBase  *m_pATPOperateLogBase;
	CATPLogBase  *m_pATPAlgoLogBase;
	CList <AtpVigil_Manager_UserInfo,AtpVigil_Manager_UserInfo> m_LoginList;

	//struATPDataBasePermission *m_pATPDBSPermission;
	//int m_nPermissionN;

	int SetAlgoParam(int nServiceType,
		const Atp_Algorithm_Info* pAlgoInfo,
		const Atp_Algoparam_Info* pParamInfo);
};


