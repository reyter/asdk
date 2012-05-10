//
// @project:atp3
// @author:������
// @date:2011/7/29
// @description:����ATPACCEPT��ATPManager֮���ͨ��Э��
//
// 

#pragma once
#ifndef __ATPACCEPT_MANAGER_DEFINE_H__
#define __ATPACCEPT_MANAGER_DEFINE_H__

#include "../../include/Protocol/TDProtocolCommon.h"
#include "ATPManagerDataBaseDefine.h"
#pragma pack(push,1)

//
//��ȡ�û���Ϣ
//��ȡ�û��ʽ��ʺ�
//��ȡ�û�ʹ���㷨�б� 
//
// ��֤�û���Ҫ����Ϣ:
// 1.�û���
// 2.����
// 3.IP
// 4.Mac
// 5.Ӳ�����к� 
//
#define ID_MSG_ATPACCEPT_MANAGER_VALIDATEUSER					1	//��֤�û� 
#define ID_MSG_ATPACCEPT_MANAGER_GETFUNDACCOUNT					2	//��ȡ�ʽ��˺ŵ���Ϣ 
#define ID_MSG_ATPACCEPT_MANAGER_GETALGOINFO					3	//��ȡ�û�����ʹ�õ��㷨���㷨ʹ����Ϣ ���㷨��Ȩ�������� 
#define	ID_MSG_ATPACCEPT_MANAGER_GETSERVERINFO					4	//��ȡ�û�����Ȩ������ 
#define ID_MSG_ATPACCEPT_MANAGER_GETUSERINFO_WITHFUNDACCOUNT	5	//ͨ���ʽ��ʺŻ�ȡ�û���Ϣ 
#define ID_MSG_ATPACCEPT_MANAGER_GETFUNDACCOUNT_SECURITYTYPE	6	//��ȡ�ʽ��ʺŵ�֤ȯ����
#define ID_MSG_ATPACCEPT_MANAGER_SET_ALGO_RUNLOG				7	//�����㷨���е���־
#define ID_MSG_ATPACCEPT_MANAGER_UPDATE_ALGO_RUNLOG				8	//�û�����ģ�� ��ȡ���µ��㷨������־
#define	ID_MSG_ATPACCEPT_MANAGER_UPLOADALGO_TACTICS				9	//���ز���

//IP��ַ�ṹ
//֧��IPv6
// struct AtpAccept_Manager_UserIP
// {
// 	int nFiled1;		//�ֶ�1
// 	int nFiled2;		//�ֶ�2
// 	int nFiled3;		//�ֶ�3
// 	int nFiled4;		//�ֶ�4 ���ΪIPv4 ǰ�����ֶ�Ϊ0 ���ֶ�ΪIPv4��ֵ  
// };

//	�㷨����״̬
#define ALGSTATUS_START		0			//��ʼ
#define ALGSTATUS_RUN		1			//��������
#define ALGSTATUS_END		2			//����
#define ALGSTATUS_ABORT		3			//�û���ֹ

/*
 *	��Ϣͷ
 *	��Ҫ�ǰ��� Ϊ�߳�ͬ��
 */
struct AtpAccept_Manager_MsgHead
{
	int nVersion;		//�汾
	long lPacketNo;		//���� 
};

/*
 *	��֤�û���Ϣ 
 */
struct AtpAccept_Manager_ValidateUser{
	char szUserName[16];			//�û��ʺ�
	char szUserPwd[32];				//����
	char szLoginIpType;				//4:IPv4 6:IPv6
	char szLoginIp[16];				//��¼Ip ֧��IPv6 
	char szMac[16];					//mac��ַ
	char szDiskSerialNum[32];		//Ӳ�����к� 
};

/*
 *	��֤�û������Ϣ 
 */
struct AtpAccept_Manager_ValidateUser_Result
{
	unsigned int nUserId;	//�û�ID 
	int nResult;			//0��ʾ��¼�ɹ� ������ʾʧ��
	char szError[64];		//ʧ��˵�� 
};

/*
 *	�û���Ϣ
 */
struct AtpAccept_Manager_User
{
	unsigned int nUserId;	//�û�ID 
	char szUserName[16];	//�û��ʺ�
};

/*
 * ��ȡ�ʽ��ʺ���Ϣ 
 */
typedef AtpAccept_Manager_User AtpAccept_Manager_GetFoundAccount;

/*
 *	��ȡ�ʽ��ʺŷ��ؽ�� 
 */
struct AtpAccept_Manager_GetFoundAccount_Result_Head
{
	int nItems;	//�ʽ��˺ŵ���Ŀ 
};
/*
 *	��ȡ�ʽ��ʺŷ��ؽ�� 
 */
struct AtpAccept_Manager_GetFoundAccount_Result
{
	char szFound[16];		//�ʽ��ʺ�
	char szOrghID[16];		//Ӫҵ�����
	short sType;			//֤ȯ���� 
	int nCaptialType;		//�ʽ��к����� 1���ʽ��˺� 2�������˺�
};


/*
 *	��ȡ����ʹ�õ��㷨 
 *	һ���Ӱ��㷨�������㷨������ȫȡ����
 */
typedef AtpAccept_Manager_User AtpAccept_Manager_GetAlgoInfo;

/*
 *	��ȡ�㷨���ص�ͷ��Ϣ 
 */
struct AtpAccept_Manager_GetAlgoInfo_ResultHead
{
	int nAlgoCount;			//�㷨��Ŀ 
};

/*
 *	�㷨��Ϣ 
 */

struct AtpAccept_Manager_GetAlgoInfo_AlgoInfo
{
	UINT32						nSerialNumber;					//	�Զ����� Ψһ
	Atp_Algorithm_Info			algoInfo;						//ԭ���Ķ��ڵ��㷨��Ϣ�ṹ
	/*
	 *	0:C++ ��׼��(C#����C++��׼������)
	 *	1:����ױ��
	 *	2:Lua�ű�
	 *	3:Matlab�㷨
	 */
	int		nAlgoLangType;			//�㷨��������
	struDataBaseAlgorithmVer	AlgorithVer;					//	�㷨�汾
	char						szAlgoPath[MAX_PATH];			//�㷨�ļ���·��
};

/*
 *	�㷨��ͷ 
 */
// struct AtpAccept_Manager_GetAlgoInfo_AlgoHead
// {
// 	int nAlgoParamCount;	// �㷨��������
// 	int nAlgServerCount;	// �㷨�����з������ĸ��� 
// };
// 
// ��ȡ��Ȩ��������������Ϣ 
typedef AtpAccept_Manager_User AtpAccept_Manager_GetServerInfo;

/*
 *	�����������Ϣ���ص�ͷ
 *	
 *
 */
struct  AtpAccept_Manager_GetServerInfo_ResultHead
{
	int nItems;			//��¼��Ŀ
	int nItemSize;		//��¼�Ĵ�С 
};

/*
 *	�㷨��Ȩ�ķ�������Ϣ 
 */
struct  AtpAccept_Manager_GetServerInfo_AlgoServer
{
	char cIpType;			//IP����
	char szServerIp[16];	//������IP
	int nPort;				//����˿� 
	UINT32 nServerID;		//��������¼ID(�㷨����ģ��ļ�¼ID)

	AtpAccept_Manager_GetServerInfo_AlgoServer(){ZeroMemory(this,sizeof(AtpAccept_Manager_GetServerInfo_AlgoServer));}

	AtpAccept_Manager_GetServerInfo_AlgoServer(const AtpAccept_Manager_GetServerInfo_AlgoServer &other)
	{
		memcpy(this,&other,sizeof(AtpAccept_Manager_GetServerInfo_AlgoServer));
	}

	AtpAccept_Manager_GetServerInfo_AlgoServer & operator=(const AtpAccept_Manager_GetServerInfo_AlgoServer &other)
	{
		memcpy(this,&other,sizeof(AtpAccept_Manager_GetServerInfo_AlgoServer));
		return (*this);
	}

};	


/*
 *	ͨ���ʽ��ʺŻ�ȡ�û���Ϣ 
 */
struct AtpAccept_Manager_GetUserInfo_WithFundAccout
{	
	ATP_Msg_Login fundAccount;		///>�ʽ��ʺ�
	char szLoginIpType;				///>4:IPv4 6:IPv6
	char szLoginIp[16];				///>��¼Ip ֧��IPv6 
	char szMac[16];					///>mac��ַ
	char szDiskSerialNum[32];		///>Ӳ�����к� 
	int nSecurityType;				///>֤ȯ���� 
};

/*
 *	ͨ���ʽ��ʺŻ�ȡ�û���Ϣ 
 *	���صĽ�� 
 */
struct AtpAccept_Manager_GetUserInfo_WithFundAccout_Result
{
	char szUserName[16];			//�û��ʺ�
	char szUserPwd[32];				//����
	unsigned int nUserId;			//�û�ID 
	int nResult;					//0��ʾ��¼�ɹ� ������ʾʧ��
	char szError[64];				//ʧ��˵�� 
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*
 *	��ȡ�ʽ��ʺ�����
 */
struct AtpAccept_Manager_GetFundAccount_SecurityType
{
	/**
	*	Ӫҵ������.
	*/
	char chOrgID[8];	
	/**
	*	�ͻ���.
	*/
	char chUserID[16];	
};

/*
 *	��ȡ�ʽ��ʺ����ͽ��
 */
struct AtpAccept_Manager_GetFundAccount_SecurityType_Result
{
	int nSecurityType;	//-1:�����ڸ��ʽ��ʺţ�0:û���г� 1��Ʊ 2:�ڻ� 3:����
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*
 *	�����㷨������־
 *	�����Ӧ
 */
struct AtpAccept_Manager_SetAlgoRunLog
{
	GUID		AlgorithmID;					//	�㷨ID
	char		szUserID[16];					//	�û�ID
	INT64		iAlgoInsID;						//	�㷨����ʵ��ID		20110916		
	UINT32		nServerID;						//	������ID		
	UINT32		nStatus;						//	�㷨����״̬
	UINT32		nRunBeginDate;					//	���п�ʼ����
	UINT32		nRunBeginTime;					//	���п�ʼʱ��
	UINT32		nRunEndDate;					//	���н�������
	UINT32		nRunEndTime;					//	���н���ʱ��
	UINT64		nVolume;						//	�ɽ���
	UINT64		nTurnover;						//	�ɽ���
	UINT32		nCount[20];						//	���ײ���ͳ�ƣ��������ֲ֣��ɳ������г�
	UINT32		nCompletion;					//	�㷨��ɶ�,�ٷֱ�
	char		szAlgoRemark[256];				//	�㷨������	
};

/*
 *	�����㷨������־
 */
typedef AtpAccept_Manager_SetAlgoRunLog AtpAccept_Manager_UpdateAlgoRunLog;

/*
*	���ز���
*/
struct AtpAccept_Manager_UploadTactics
{
	//�û���Ϣ
	UINT32		uUserId;						// �û�ID����ID
	char		szUserId[16];						// �û�ID
	//������Ϣ
	GUID		guid;							// ���Ե�GUID(���пͻ��˻����û������������)
	char		szAlgorithmName[16];			//	�㷨������
	UINT32		nAlgoType;						//0 ��ʾ���㷨��  1-�����Ե� 2-ѡ��������, 3-ѡ�ɷ�����...
	UINT32 		nSecurityType; 					//֤������
	UINT32		nLanguageType;					//	��������
	char		szExplain[128];					//	�㷨˵��
	UINT32		uContentLength;					//  ��������
	//�˽ṹ�������������������
};

/*
*	���ز��Խ��
*/
struct AtpAccept_Manager_UploadTactics_Result
{
	union
	{
		struct 
		{
			char		szFileName[64];					//	���Ե�����
			char		szPath[MAX_PATH];				//	�㷨ʹ��·��,·��Ҫָ��
		}success;
		
		struct 
		{
			int			nResult;						//	����ֵ
			char		szError[128];					//	�����˵��
		}fail;
	}result;
};

#pragma pack(pop)

#endif	//__ATPACCEPT_MANAGER_DEFINE_H__