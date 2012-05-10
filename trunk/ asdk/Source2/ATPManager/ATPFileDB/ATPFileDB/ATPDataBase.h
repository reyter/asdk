#pragma once
#include "ATPManagerDataBaseDefine.h"
#include "ATPManagerNetDefine.h"
class CATPDataBase:public CHHDataChannelCtrl
{
public:
	CATPDataBase(void);
	virtual ~CATPDataBase(void);
public:
	//	Ϊע��ṹ�����ڴ�,ֻ����Ҫע��ṹָ��ʱ����Ҫʹ���������麯��
	virtual void	*NewRegisterSaveDataStruct(int nID, int nItems);
	virtual BOOL	DeleteRegisterSaveDataStruct(int nID, int nItems);

private:
	void				RegisterData();
	int				InitDBFile(char *pFilename);
public:
	int AddManager(IN struATPDataBaseManager *pInData,struATPDataBaseManager *pOutData);
	int ModifyManager(IN struATPDataBaseManager*pInData);
	int DelManager(IN struATPDataBaseManager*pInData);
	int QueryManager(IN char *pAccount,OUT struATPDataBaseManager **ppOutData);

	int AddServerGroup(IN struATPDataBaseServerGroup *pInData,OUT struATPDataBaseServerGroup *pOutData);
	int ModifyServerGroup(IN struATPDataBaseServerGroup *pInData);
	int DelServerGroup(IN struATPDataBaseServerGroup *pInData);
	int QueryServerGroup(OUT struATPDataBaseServerGroup **);

	int AddServer(IN struATPDataBaseServer *pInData,OUT struATPDataBaseServer *pOutData);
	int ModifyServer(IN struATPDataBaseServer *pInData);
	int DelServer(IN struATPDataBaseServer *pInData);
	int QueryServer(IN struATPDataBaseServer_QUERY *pInData,OUT struATPDataBaseServer **ppOutData);

	//int AddPermission(struATPDataBasePermission *);
	//int ModifyPermission(struATPDataBasePermission *);
	//int DelPermission(struATPDataBasePermission *);
	int QueryPermission(IN struATPDataBasePermission **);

	int AddUserGroup(IN struATPDataBaseUserGroup *pInData,OUT struATPDataBaseUserGroup *pOutData);
	int ModifyUserGroup(IN struATPDataBaseUserGroup *pInData);
	int DelUserGroup(IN struATPDataBaseUserGroup *pInData);
	int QueryUserGroup(IN char *pAccount,OUT struATPDataBaseUserGroup **ppOutData);

	int AddUser(IN struATPDataBaseUser *pInData,OUT struATPDataBaseUser *pOutData);
	int ModifyUser(IN struATPDataBaseUser *pInData);
	int DelUser(IN struATPDataBaseUser *pInData);
	int QueryUser(IN struATPDataBaseUser_QUERY *pInData,IN char *pAccount,OUT struATPDataBaseUser **ppOutData);

	int AddAlgorithmGroup(IN struATPDataBaseAlgorithmGroup *pInData,OUT struATPDataBaseAlgorithmGroup *pOutData);
	int ModifyAlgorithmGroup(IN struATPDataBaseAlgorithmGroup *pInData);
	int DelAlgorithmGroup(IN struATPDataBaseAlgorithmGroup *pInData);
	int QueryAlgorithmGroup(IN char *pAccount,OUT struATPDataBaseAlgorithmGroup **ppOutData);

	int AddAlgorithm(IN struATPDataBaseAlgorithm *pInData,OUT struATPDataBaseAlgorithm *pOutData,BOOL bScript);
	int ModifyAlgorithm(IN struATPDataBaseAlgorithm *pInData);
	int DelAlgorithm(IN struATPDataBaseAlgorithm *pInData);
	int QueryAlgorithm(IN struATPDataBaseAlgorithm_QUERY *pInData,IN char *pAccount,OUT struATPDataBaseAlgorithm **ppOutData);

	//////////////////////////////////////////////////////////////////////////
	///���̼�ͨѶ����
	//��֤�û� 
	int UserLogin(IN const char *pReqData,OUT char **ppAnsData,int *pnLen);
	//��ȡ�ʽ��˺ŵ���Ϣ 
	int GetFundAccount(IN const char *pReqData,OUT char **ppAnsData,int *pnLen);
	//��ȡ�û�����ʹ�õ��㷨���㷨ʹ����Ϣ ���㷨��Ȩ�������� 
	int GetAlgoInfo(IN const char *pReqData,OUT char **ppAnsData,int *pnLen);
	//��ȡ��������Ϣ
	int GetServerInfo(IN const char *pReqData,OUT char **ppAnsData,int *pnLen);
	//ͨ���ʽ��ʻ���ȡ�û��ʺ�
	int GetAccountByFund(IN const char *pReqData,OUT char **ppAnsData,int *pnLen,BOOL bFlag = FALSE);
	//��ȡ�ʽ��ʻ������г�
	int GetFundMarket(IN const char *pReqData,OUT char **ppAnsData,int *pnLen);


	//////////////////////////////////////////////////////////////////////////

	//����Ա��¼
	int ManagerLogin(IN struReq_ATPManageLogin *pInData);

	int IsHavePermission(int nAccountType,const char *AccountID,int nPermissionType);
	int TranslationPermission(int nAccountType,int nPermissionType);
	//int GetAdministratorPermission(const char *AccountID,OUT int **ppPermission,int *pnItem);
	int GetManagerPermission(const char *AccountID,OUT int **ppPermission);
	int GetUserPermission(const char *AccountID,OUT int **ppPermission);
private:
	//����Ա
	int								m_nUsedATPDBSManagerItem;
	int								m_nATPDBSManagerItem;
	struATPDataBaseManager			*m_pATPDBSManager;
	//��������
	int								m_nUsedATPDBSServerGroupItem;
	int								m_nATPDBSServerGroupItem;
	struATPDataBaseServerGroup		*m_pATPDBSServerGroup;
	//������
	int								m_nUsedATPDBSServerItem;
	int								m_nATPDBSServerItem;
	struATPDataBaseServer			*m_pATPDBSServer;
	//Ȩ��
	int								m_nUsedATPDBSPermissionItem;
	int								m_nATPDBSPermissionItem;
	struATPDataBasePermission		*m_pATPDBSPermission;
	//�û���
	int								m_nUsedATPDBSUserGroupItem;
	int								m_nATPDBSUserGroupItem;
	struATPDataBaseUserGroup		*m_pATPDBSUserGroup;
	//�û�
	int								m_nUsedATPDBSUserItem;
	int								m_nATPDBSUserItem;
	struATPDataBaseUser				*m_pATPDBSUser;
	//�㷨��
	int								m_nUsedATPDBSAlgorithmGroupItem;
	int								m_nATPDBSAlgorithmGroupItem;
	struATPDataBaseAlgorithmGroup	*m_pATPDBSAlgorithmGroup;
	//�㷨��������ֵ
// 	int								m_nUsedATPDataBaseAlgorithmParamEXItem;
// 	int								m_nATPDataBaseAlgorithmParamEXItem;
// 	struATPDataBaseAlgorithmParamEX *m_pATPDataBaseAlgorithmParamEX;
	//�㷨
	int								m_nUsedATPDBSAlgorithmItem;
	int								m_nATPDBSAlgorithmItem;
	struATPDataBaseAlgorithm		*m_pATPDBSAlgorithm;
};

