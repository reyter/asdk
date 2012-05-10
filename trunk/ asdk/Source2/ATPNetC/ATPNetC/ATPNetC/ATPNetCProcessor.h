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
void Receive_CREATEMANAGER(const char *pRecvData,int nLength);				//50021//	��������Ա(��������Ա)
void Receive_DELETEMANAGER(const char *pRecvData,int nLength);				//50022//	ɾ������Ա(��������Ա)
void Receive_MODIFYMANAGER(const char *pRecvData,int nLength);				//50023//	�޸Ĺ���Ա(��������Ա������Ա)
void Receive_QUERYMANAGERINFO(const char *pRecvData,int nLength);			//50024//	��ѯ����Ա(��������Ա)

	//��������
void Receive_CREATESERVERGROUP(const char *pRecvData,int nLength);			//0031//	������������(��������Ա)
void Receive_DELETESERVERGROUP(const char *pRecvData,int nLength);			//50032//	ɾ����������(��������Ա)
void Receive_MODIFYSERVERGROUP(const char *pRecvData,int nLength);			//50033//	�޸ķ�������(��������Ա)
void Receive_QUERYSERVERGROUPINFO(const char *pRecvData,int nLength);		//50034//	��ѯ��������(��������Ա)

	//������
void Receive_CREATESERVER(const char *pRecvData,int nLength);				//50041//	����������(��������Ա)
void Receive_DELETESERVER(const char *pRecvData,int nLength);				//50042//	ɾ��������(��������Ա)
void Receive_MODIFYSERVER(const char *pRecvData,int nLength);				//50043//	�޸ķ�����(��������Ա)
void Receive_QUERYSERVERINFO(const char *pRecvData,int nLength);			//50044//	��ѯ������(��������Ա)

	//Ȩ��
void Receive_QUERYPERMISSIONINFO(const char *pRecvData,int nLength);		//50051//	��ѯȨ��(��������Ա������Ա)

	/************************************************************************/
	/*                                       ����Ա                               */
	/************************************************************************/

	//�㷨��
void Receive_ADDALGORITHMGROUP(const char *pRecvData,int nLength);			//51011//	����㷨��(����Ա)
void Receive_DELETEALGORITHMGROUP(const char *pRecvData,int nLength);		//51012//	ɾ���㷨��(����Ա)
void Receive_MODIFYALGORITHMGROUP(const char *pRecvData,int nLength);		//51013//	�޸��㷨��(����Ա)
void Receive_QUERYALGORITHMGROUPINFO(const char *pRecvData,int nLength);	//51014//��ѯ�㷨��(����Ա)

	//�㷨
void Receive_ADDALGORITHM(const char *pRecvData,int nLength);				//51021//	����㷨��Ϣ(����Ա)
void Receive_DELETEALGORITHM(const char *pRecvData,int nLength);			//51022//	ɾ���㷨��Ϣ(����Ա)
void Receive_MODIFYALGORITHM(const char *pRecvData,int nLength);			//51023//	�޸��㷨(����Ա)
void Receive_MODIFYALGORITHMINFO(const char *pRecvData,int nLength);		//51024//	�޸��㷨��Ϣ(����Ա)

	//�㷨����
void Receive_QUERYALGORITHMINFO(const char *pRecvData,int nLength);		//51025//	��ѯ�㷨��Ϣ(����Ա)
void Receive_QUERYALGORITHMPARAM(const char *pRecvData,int nLength);		//51026//	��ѯ�㷨����
void Receive_QUERYALGORITHMVERSION(const char *pRecvData,int nLength);		//51027//	��ѯ�㷨��ʷ�汾

	//�û���												 
void Receive_ADDUSERGROUP(const char *pRecvData,int nLength);				//51041//	����û���(����Ա)
void Receive_DELETEUSERGROUP(const char *pRecvData,int nLength);			//51042//	ɾ���û���(����Ա)
void Receive_MODIFYUSERGROUP(const char *pRecvData,int nLength);			//51043//	�޸��û���(����Ա)
void Receive_QUERYUSERGROUPINFO(const char *pRecvData,int nLength);		//51044//	��ѯ�û�����Ϣ(����Ա)

	//�û�
void Receive_ADDUSER(const char *pRecvData,int nLength);					//51051//	����û�(����Ա)
void Receive_DELETEUSER(const char *pRecvData,int nLength);				//51052//	ɾ���û�(����Ա)
void Receive_MODIFYUSER(const char *pRecvData,int nLength);				//51053//	�޸��û�(����Ա)
void Receive_QUERYUSERINFO(const char *pRecvData,int nLength);				//51054//	��ѯ�û���Ϣ(����Ա)

	//�û�������־
void Receive_QUERYUSEROPERATELOG(const char *pRecvData,int nLength);		//51061//	��ѯ�û�������־(����Ա)struReq_ATPManage_ATPManageOperateLog

	//�㷨��־
void Receive_QUERYUSEDALGORITHM(const char *pRecvData,int nLength);		//51071//	��ѯ�㷨ͳ����Ϣ(����Ա)
void Receive_QUERYUSERALGORITHM(const char *pRecvData,int nLength);		//51072//	��ѯ�û�ʹ���㷨ͳ����Ϣ(����Ա)
void Receive_QUERYSERVERALGORITHM(const char *pRecvData,int nLength);		//51073//	��ѯ�����������㷨ͳ����Ϣ(����Ա)

private:
	struct struRecvData
	{
		size_t					_nUsedMemory;							//�Ѿ�ʹ�õ��ڴ�
		size_t					_nHadMemory;							//�Ѿ�������ڴ�
		BYTE					*_pAnswerData;							//���󷵻ص�����
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

