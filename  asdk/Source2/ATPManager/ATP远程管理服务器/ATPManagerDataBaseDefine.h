#pragma once
#include "ATPACCEPT_MANAGER_DEFINE.H"
#ifndef _ATPMANAGERDATABASEDEFINE_H_
#define _ATPMANAGERDATABASEDEFINE_H_

#define	BYTE			unsigned char

#define	UINT8			unsigned char
#define INT8			char						

#define UINT16			unsigned short
#define INT16			short

#define UINT32			unsigned int				
#define INT32			int							

#ifndef _WINDOWS_
#define UINT64		unsigned __int64
#define INT64		__int64					
#else
#define UINT64		unsigned long long
#define INT64		long long
#endif

//	�㷨����״̬
#define ALGSTATUS_START		0			//��ʼ
#define ALGSTATUS_RUN		1			//��������
#define ALGSTATUS_END		2			//����
#define ALGSTATUS_ABORT		3			//�û���ֹ

//���ֽڶ���
#pragma pack(push, 1)

//�汾
struct struDataBaseAlgorithmVer
{
	short Ver[4];
};

//��׼���ؽ��
struct	struAnsOperate
{
	char		szInfo[128];			//	������Ϣ
	UINT8		nResult;				//	���ؽ�� TRUE �ɹ�  �������
};






//�ֹ������ID,
struct	struATID
{
	char	szID[16];
	char	szName[16];
};
//�Զ�����ID
struct	struATPAutoID
{
	UINT32	nID;
	char	szName[16];
};
//�㷨
struct	struATPAutoAlgoID
{
	GUID	nID;
	char	szName[16];
};

//	��������Ա
struct struATPDataBaseSuperAdmin
{
	char	szPwd[32];
	UINT32	nPort;		//	��������˿�
};

//	��ͨ����Ա
struct	struATPDataBaseManager
{
	UINT32					nSerialNumber;		//	�Զ����� Ψһ
	char					szID[16];			//	����ԱID
	char					szName[16];			//	����
	char					szPwd[32];			//	����
	UINT32					nStatus;			//	����Ա״̬  0 1 2
	char					szExplain[64];		//	˵����Ϣ
	UINT32					nPermissionIDs[32];	//	Ȩ��ID
	UINT32					nCreateDate;		//	��������
	UINT32					nCreateTime;		//	����ʱ��
	UINT32					nLastDate;			//	����½����
	UINT32					nLastTime;			//	����½ʱ��
	UINT8					nDeleteMark;		//	ɾ����־
	UINT32					nServerN;			//	����������
	struATPAutoID*			pServerIDs;			//	������IDs
	UINT32					nServerGroupN;		//	�����������
	struATPAutoID*			pServerGroupIDs;	//	��������IDs
};

//	��������
struct struATPDataBaseServerGroup
{
	UINT32			nID;				//	��ID �Զ�����  Ψһ
	UINT32			nParentID;			//	����ID
	char			szName[16];			//	����
	char			szExplain[128];		//	˵��
	UINT32			nCreateDate;		//	��������
	UINT32			nCreateTime;		//	����ʱ��
	UINT8			nDeleteMark;		//	ɾ�����
};

//������
struct	struATPDataBaseServer
{
	UINT32			nID;						//	������ID �Զ����� Ψһ
	char			szName[16];					//	��������
	char			szIP[16];					//	������IP
	UINT32			nIPType;					//	4,6
	UINT32			nPort;						//	�������˿ں�
	UINT32			nGroupID;					//	��������
	UINT32			nAlloc;						//	����ԭ��
	UINT32			nCreateDate;				//	��������
	UINT32			nCreateTime;				//	����ʱ��
	UINT8			nDeleteMark;				//	ɾ�����
};

struct	struATPDataBaseServer_QUERY
{
	UINT32			nGroupID;				//	��������
};


//Ȩ��
struct struATPDataBasePermission
{
	UINT32		nPermissionID;					//	Ȩ��ID �Զ����� Ψһ
	char		szPermissionName[16];			//	Ȩ����
	UINT8		nPermissionType;				//	Ȩ������
};					

//	�û���
struct	struATPDataBaseUserGroup
{
	UINT32				nID;							//	��ID  �Զ����� Ψһ
	UINT32				nParentID;						//	����ID
	char				szName[16];						//	����
	char				szExplain[64];					//	˵����Ϣ
	UINT32				nAlgorithmN;					//	�㷨����
	struATPAutoAlgoID*	pAlgorithmIDs;					//	�㷨ID
	UINT32				nAlgorithmGroupN;				//	�㷨�����
	struATPAutoID*		pAlgorithmGroupIDs;				//	�㷨��ID
	UINT32				nServerN;						//	����������
	struATPAutoID*		pServerIDs;						//	������ID
	UINT32				nServerGroupN;					//	�����������
	struATPAutoID*		pServerGroupIDs;				//	��������ID
	UINT32				nCreateDate;					//	��������
	UINT32				nCreateTime;					//	����ʱ��
	UINT8				nDeleteMark;					//	ɾ����־
	char				szManagerID[16];				//	����ԱID
};
//	�û��ʺ����ʽ��ʺŹ���
struct struATPDataBaseFund
{
	UINT32	nSerialNumber;									//	�Զ����� Ψһ
	char	szFund[16];										//	�ʽ��ʺ�
	char	szOrgID[16];									//	Ӫҵ��ID
	char	szMarkets[12];									//	�г�
};
//�û�
struct struATPDataBaseUser
{
	UINT32					nSerialNumber;					//	�Զ����� Ψһ
	char					szUserID[16];					//	�û�ID
	char					szPwd[32];						//	�û�����
	char					szUserName[16];					//	�û���
	char					szCardID[18];					//	���֤����
	UINT32					nGroupIDs[4];					//	�û���ID
	UINT32					nPermissionIDs[32];				//	Ȩ��ID
	UINT32					nAuthorizeBeginDate;			//	��Ȩʹ�ÿ�ʼ����
	UINT32					nAuthorizeEndDate;				//	��Ȩʹ�ý�ֹ����
	UINT32					nStatus;						//	�û�ʹ��״̬
	char					szMobiles[2][16];				//	�ֻ�����,������
	char					szTelephones[2][12];			//	�绰����
	UINT64					nQQNumbers[2];					//	QQ����
	char					szEmails[2][64];				//	Email����
	char					szUserExplain[128];				//	�û�˵��,����������
	char					szIPs[128];						//	����IP
	char					szMacMark[40];					//	����MAC��ַ
	char					szDiskNum[32];					//	����Ӳ�����к�
	char					chLimitTimeMark;				///�Ƿ����Ƶ�¼ʱ��
	UINT32					nLimitBeginTime[4];				//	���ƿ�ʼʱ��
	UINT32					nLimitEndTime[4];				//	���ƽ���ʱ��
	char					chLimitWeek;					//	��������,0x80������
	UINT32					nCanAssociateFundsAccount;		//	��ǰ�ʽ��ʺŽṹ����,���10��
	struATPDataBaseFund*	pATPFund;						//	�ʽ��ʺŽṹ��
	UINT32					nCanRunAlgorithm;				//	����ͬʱ�����㷨����
	UINT32					nAlgorithmN;					//	�㷨����
	struATPAutoAlgoID*		pAlgorithmIDs;					//	�㷨IDs
	UINT32					nAlgorithmGroupN;				//	�㷨�����
	struATPAutoID*			pAlgorithmGroupIDs;				//	�㷨��IDs
	UINT32					nServerN;
	struATPAutoID*			pServerIDs;						//	ר��������
	UINT32					nServerGroupN;					//	�����������
	struATPAutoID*			pServerGroupIDs;				//	��������IDs
	UINT32					nCreateDate;					//	��������
	UINT32					nCreateTime;					//	����ʱ��
	UINT32					nLastDate;						//	����½����
	UINT32					nLastTime;						//	����½ʱ��
	UINT8					nDeleteMark;					//	ɾ����־
	char					szManagerID[16];				//	����ԱID
};									
struct struATPDataBaseUser_QUERY
{
	UINT32				nID;							//	��ID  �Զ�����
};
//������־
struct	struATPDataBaseOperateLog
{
	UINT32		nSerialNumber;					//	�Զ����� Ψһ
	char		szActorID[16];					//	��ɫID
	UINT32		nRecords;						//	��¼��
	UINT32		nOperateType;					//	��������
	UINT32		nOperateDate;					//	��������
	UINT32		nOperateTime;					//	����ʱ��
	char		szInfo[128];					//	��¼��Ϣ

};

struct	struATPDataBaseOperateLog_QUERY
{
	int		nBeginDate;
	int		nEndDate;
	int		nOperateType;
	char	szUserID[16];					//	�û�ID ����鿴ȫ��
};


//	�㷨��
struct	struATPDataBaseAlgorithmGroup
{
	UINT32			nID;							//	��ID  �Զ����� Ψһ
	UINT32			nParentID;						//	����ID
	char			szName[16];						//	����
	int				nCreateDate;					//	��������
	int				nCreateTime;					//	����ʱ��
	UINT8			nDeleteMark;					//	ɾ����־
	char			szManagerID[16];				//	����ԱID
};

//�㷨����
struct struATPDataBaseAlgorithmParam
{
	UINT32				nSerialNumber;						//	�Զ����� Ψһ
	int					nExtraDataLength;					//	�������ݳ���	
	ATP_ALGOPARAM_TYPE  nType;								//	��������.
	char				szParamName[64];					//	������	
	char				szParamDescription[512];			//	������Ϣ
	ATP_Msg_MakeOrderByAlgo_ParamValue defaultValue;		//	Ĭ��ֵ.
	UINT32				nExtraDataIndex;					//	������������
};

//�㷨������������
struct struATPDataBaseAlgorithmParamEX
{
	UINT32	nSerialNumber;									//	�Զ����� Ψһ
	int		nExtraDataLength;								//	�������ݳ���	
	BYTE    ExtraData[512];
};


//	�㷨
struct struATPDataBaseAlgorithm 
{
	UINT32					nSerialNumber;					//	�Զ����� Ψһ
	GUID					AlgorithmID;					//	guid Ψһ
	char					szAlgorithmName[16];			//	�㷨��
	struDataBaseAlgorithmVer AlgorithVer;					//	�㷨�汾
	UINT8					nVersionAttribute;				//	�㷨�汾���� ���԰�֮��
	UINT8					nCharge;						//	�Ƿ��շ�
	UINT32					nAlgoType;						//0 ��ʾ���㷨��  1-�����Ե� 2-ѡ��������, 3-ѡ�ɷ�����...
	UINT32					nGroupID;						//	�㷨��
	UINT32					nMarketType;					//	�㷨�������г�����
	UINT32					nLanguageType;					//	�㷨��д����������
	char					szExplain[128];					//	�㷨˵��
	char					szWarning[32];					//	�㷨����
	char					szKeyword[128];					//	�㷨�ؼ���
	UINT8					nStatus;						//	�㷨״̬
	char					szStopReason[128];				//	�㷨����ԭ��
	UINT32					nCreateDate;					//	�㷨��������
	UINT32					nCreateTime;					//	�㷨����ʱ��
	char					szPath[MAX_PATH];				//	�㷨ʹ��·��,·��Ҫָ��
	char					szMainDllName[32];				//	�㷨���dll�ļ���
	int						nParams;						//	�㷨��������
	struATPDataBaseAlgorithmParam*	pATPAlgorithmParams;	//	�㷨����
	int						nParamsEx;
	struATPDataBaseAlgorithmParamEX* pATPAlgorithmParamsEX;
	UINT8					nDeleteMark;					//	ɾ�����
	char					szManagerID[16];				//	����ԱID
};

struct struATPDataBaseAlgorithm_QUERY
{
	UINT32			nID;									//	��ID  �Զ�����
};


//	�㷨��־��ÿ�ղ���һ�ļ�
struct struATPDataBaseAlgorithmLog
{
	UINT32		nSerialNumber;				//	�Զ����� Ψһ
	GUID		AlgorithmID;				//	�㷨ID
	char		szUserID[16];				//	�û�ID
	INT64		iAlgoInsID;					//	�㷨����ʵ��ID		20110916		
	UINT32		nUserGroupID;
	UINT32		nServerID	;				//	������ID		
	UINT32		nStatus;					//	�㷨����״̬
	UINT32		nRunBeginDate;				//	���п�ʼ����
	UINT32		nRunBeginTime;				//	���п�ʼʱ��
	UINT32		nRunEndDate;				//	���н�������
	UINT32		nRunEndTime;				//	���н���ʱ��
	UINT64		nVolume;					//	�ɽ���
	UINT64		nTurnover;					//	�ɽ���
	UINT32		nCount[20];					//	���ײ���ͳ�ƣ��������������ֲֲ�ѯ���ɽ���ѯ��ί�в�ѯ,�ɳ�����ѯ���ʲ���ѯ
	UINT32		nCompletion;				//	�㷨��ɶ�,�ٷֱ�
	char		szAlgoRemark[256];			// �㷨������	
};

//�㷨ʹ��������ܣ�ͨ���㷨ʹ��ͳ�ƣ�ֻ����һ�ļ���ÿ��ÿ���㷨����һ����¼
struct struATPDataBaseAlgorithmSummaryByAlgoDaily 
{
	UINT32		nSerialNumber;				//	�Զ����� Ψһ
	GUID		AlgorithmID;				//	�㷨ID
	UINT32		nDate;
	UINT64		nVolume;					//	�ɽ���
	UINT64		nTurnover;					//	�ɽ���
	UINT32		nCount[20];					//	���ײ���ͳ�ƣ��������ֲ֣��ɳ������г�
};

//�㷨ʹ��������ܣ�ͨ���û�ʹ��ͳ�ƣ�ֻ����һ�ļ���ÿ��ÿ���û�����һ����¼
struct struATPDataBaseAlgorithmSummaryByAccountDaily 
{
	UINT32		nSerialNumber;				//	�Զ����� Ψһ
	char		szUserID[16];				//	�û�ID
	UINT32		nDate;
	UINT64		nVolume;					//	�ɽ���
	UINT64		nTurnover;					//	�ɽ���
	UINT32		nCount[20];					//	���ײ���ͳ�ƣ��������ֲ֣��ɳ������г�
};

//�㷨ʹ��������ܣ�ͨ���㷨���û�ʹ��ͳ�ƣ�ֻ����һ�ļ�������ÿ���㷨��ÿ���û�����һ����¼
struct struATPDataBaseAlgorithmSummary 
{
	UINT32		nSerialNumber;				//	�Զ����� Ψһ
	GUID		AlgorithmID;				//	�㷨ID
	char		szUserID[16];				//	�û�ID
	UINT32		nDate;
	UINT64		nVolume;					//	�ɽ���
	UINT64		nTurnover;					//	�ɽ���
	UINT32		nCount[20];					//	���ײ���ͳ�ƣ��������ֲ֣��ɳ������г�
};





struct struATPDataBaseAlgorithmLog_QUERY
{
	UINT32				nRunBeginDate;			//	���п�ʼ����
	UINT32				nRunEndDate;			//	���н�������  Ϊ�����ѯ���������㷨 
	GUID				AlgorithmID;			//	�㷨ID  Ϊ����ȫ���㷨
	char				szUserID[16];			//	�û�ID
	UINT32				nServerID;				//	������ID		
};
#pragma pack(pop)
#endif	//	_ATPMANAGEDEFINE_H_