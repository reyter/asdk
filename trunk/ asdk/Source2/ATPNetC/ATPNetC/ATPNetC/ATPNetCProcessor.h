#pragma once

#ifdef _ATPNETCLIENT_
#define ATPNETCAPI _declspec(dllexport) 
#else		
#define ATPNETCAPI _declspec(dllimport) 	
#endif



class ATPNETCAPI CATPNetCProcessor:public CHHNetFrameProcessor
{
	DECLARE_DYNCREATE(CATPNetCProcessor)
public:
	CATPNetCProcessor(void);
	virtual ~CATPNetCProcessor(void);

private:
	virtual BOOL OnCreate();
	virtual BOOL OnDestroy(BOOL bInterrupt);
	virtual int  OnReceiveData(const CString &strSrcDN, const CString &strDesDN, CString &strSendDesDN, char *lpRecv, int nSize, unsigned int nID, unsigned int &nIDSend, BOOL &bDelRecv, char **lpSend, BOOL &bDelSend, int &nFlags, int &nErrLen);
	virtual int  OnSendData(CString &strSendDesDN, char **lpSend, unsigned int &nID, BOOL &bDelete, int &nFlags, int &nErrLen);

protected:
	virtual int OnRecvData(int nType,const char *lpRecv, int nSize);
	virtual int OnSendData(int nType,const char *lpRecv, int nSize);



private:
void Receive_CREATEMANAGER(const char *pRecvData,int nLength);				//50021//	创建管理员(超级管理员)
void Receive_DELETEMANAGER(const char *pRecvData,int nLength);				//50022//	删除管理员(超级管理员)
void Receive_MODIFYMANAGER(const char *pRecvData,int nLength);				//50023//	修改管理员(超级管理员，管理员)
void Receive_QUERYMANAGERINFO(const char *pRecvData,int nLength);			//50024//	查询管理员(超级管理员)

	//服务器组
void Receive_CREATESERVERGROUP(const char *pRecvData,int nLength);			//0031//	创建服务器组(超级管理员)
void Receive_DELETESERVERGROUP(const char *pRecvData,int nLength);			//50032//	删除服务器组(超级管理员)
void Receive_MODIFYSERVERGROUP(const char *pRecvData,int nLength);			//50033//	修改服务器组(超级管理员)
void Receive_QUERYSERVERGROUPINFO(const char *pRecvData,int nLength);		//50034//	查询服务器组(超级管理员)

	//服务器
void Receive_CREATESERVER(const char *pRecvData,int nLength);				//50041//	创建服务器(超级管理员)
void Receive_DELETESERVER(const char *pRecvData,int nLength);				//50042//	删除服务器(超级管理员)
void Receive_MODIFYSERVER(const char *pRecvData,int nLength);				//50043//	修改服务器(超级管理员)
void Receive_QUERYSERVERINFO(const char *pRecvData,int nLength);			//50044//	查询服务器(超级管理员)

	//权限
void Receive_QUERYPERMISSIONINFO(const char *pRecvData,int nLength);		//50051//	查询权限(超级管理员、管理员)

	/************************************************************************/
	/*                                       管理员                               */
	/************************************************************************/

	//算法组
void Receive_ADDALGORITHMGROUP(const char *pRecvData,int nLength);			//51011//	添加算法组(管理员)
void Receive_DELETEALGORITHMGROUP(const char *pRecvData,int nLength);		//51012//	删除算法组(管理员)
void Receive_MODIFYALGORITHMGROUP(const char *pRecvData,int nLength);		//51013//	修改算法组(管理员)
void Receive_QUERYALGORITHMGROUPINFO(const char *pRecvData,int nLength);	//51014//查询算法组(管理员)

	//算法
void Receive_ADDALGORITHM(const char *pRecvData,int nLength);				//51021//	添加算法信息(管理员)
void Receive_DELETEALGORITHM(const char *pRecvData,int nLength);			//51022//	删除算法信息(管理员)
void Receive_MODIFYALGORITHM(const char *pRecvData,int nLength);			//51023//	修改算法(管理员)
void Receive_MODIFYALGORITHMINFO(const char *pRecvData,int nLength);		//51024//	修改算法信息(管理员)

	//算法属性
void Receive_QUERYALGORITHMINFO(const char *pRecvData,int nLength);		//51025//	查询算法信息(管理员)
void Receive_QUERYALGORITHMPARAM(const char *pRecvData,int nLength);		//51026//	查询算法参数
void Receive_QUERYALGORITHMVERSION(const char *pRecvData,int nLength);		//51027//	查询算法历史版本

	//用户组												 
void Receive_ADDUSERGROUP(const char *pRecvData,int nLength);				//51041//	添加用户组(管理员)
void Receive_DELETEUSERGROUP(const char *pRecvData,int nLength);			//51042//	删除用户组(管理员)
void Receive_MODIFYUSERGROUP(const char *pRecvData,int nLength);			//51043//	修改用户组(管理员)
void Receive_QUERYUSERGROUPINFO(const char *pRecvData,int nLength);		//51044//	查询用户组信息(管理员)

	//用户
void Receive_ADDUSER(const char *pRecvData,int nLength);					//51051//	添加用户(管理员)
void Receive_DELETEUSER(const char *pRecvData,int nLength);				//51052//	删除用户(管理员)
void Receive_MODIFYUSER(const char *pRecvData,int nLength);				//51053//	修改用户(管理员)
void Receive_QUERYUSERINFO(const char *pRecvData,int nLength);				//51054//	查询用户信息(管理员)

	//用户操作日志
void Receive_QUERYUSEROPERATELOG(const char *pRecvData,int nLength);		//51061//	查询用户操作日志(管理员)struReq_ATPManage_ATPManageOperateLog

	//算法日志
void Receive_QUERYUSEDALGORITHM(const char *pRecvData,int nLength);		//51071//	查询算法统计信息(管理员)
void Receive_QUERYUSERALGORITHM(const char *pRecvData,int nLength);		//51072//	查询用户使用算法统计信息(管理员)
void Receive_QUERYSERVERALGORITHM(const char *pRecvData,int nLength);		//51073//	查询服务器运行算法统计信息(管理员)

private:
	struct struRecvData
	{
		size_t					_nUsedMemory;							//已经使用的内存
		size_t					_nHadMemory;							//已经分配的内存
		BYTE					*_pAnswerData;							//请求返回的数据
		struRecvData()
		{
			_nUsedMemory = 0;
			_nHadMemory = 1024*1024;
			_pAnswerData = new BYTE[_nHadMemory];
		}
	};
	struRecvData m_recvManagerData;
	struRecvData m_recvServerGroupRecvData;
	struRecvData m_recvServerData;
	struRecvData m_recvPermissionData;
	struRecvData m_recvUserGroupRecvData;
	struRecvData m_recvFundData;
	struRecvData m_recvUserData;
	struRecvData m_recvOperateLogData;
	struRecvData m_recvAlgorithmGroupRecvData;
	struRecvData m_recvAlgorithmData;
	struRecvData m_recvAlgorithmLogData;

	void InitMemory();
	void AllocateMemory(struRecvData* pRecvData,int nNeed);
};

