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

//�汾
struct struDataBaseAlgorithmVer
{
	short Ver[4];
};
//	�㷨����
struct struATPDataBaseAlgorithmParam
{
	
};
struct	struATID
{
	char	szID[16];
	char	szName[16];
};

struct	struATPAutoID
{
	UINT32	nID;
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
	struATPAutoID*		pServerIDs;			//	������IDs
	UINT32					nServerGroupN;		//	�����������
	struATPAutoID*		pServerGroupIDs;	//	��������IDs
};

//	��������
struct struATPDataBaseServerGroup
{
	UINT32			nID;				//	��ID �Զ�����
	UINT32			nParentID;			//	����ID
	char			szName[16];			//	����
	char			szExplain[128];		//	˵��
	UINT32			nCreateDate;		//	��������
	UINT32			nCreateTime;		//	����ʱ��
	UINT8			nDeleteMark;		//	ɾ�����
};

//������
struct	struATPServer
{
	UINT32			nID;						//	������ID �Զ�����
	char			szName[16];					//	��������
	char			szIP[16];					//	������IP
	UINT32			nPort;						//	�������˿ں�
	UINT32			nGroupID[16];				//	��������
	char			szAdminID[16];
	UINT32			nCreateDate;				//	��������
	UINT32			nCreateTime;				//	����ʱ��
	UINT8			nDeleteMark;				//	ɾ�����
};

//Ȩ��
struct struATPDataBasePermission
{
	UINT32		nPermissionID;					//	Ȩ��ID �Զ�����
	char		szPermissionName[16];			//	Ȩ����
	UINT8		nPermissionType;				//	Ȩ������
};					

//	�û���
struct	struATPDataBaseUserGroup
{
	UINT32				nID;							//	��ID  �Զ�����
	UINT32				nParentID;						//	����ID
	char				szName[16];						//	����
	char				szCreateActor[16];				//	������ɫ
	char				szExplain[64];					//	˵����Ϣ
	UINT32				nAlgorithmN;					//	�㷨����
	GUID*				pAlgorithmIDs;					//	�㷨ID
	UINT32				nAlgorithmGroupN;				//	�㷨�����
	struATPAutoID*	pAlgorithmGroupIDs;				//	�㷨��ID
	UINT32				nServerN;						//	����������
	struATPAutoID*	pServerIDs;						//	������ID
	UINT32				nServerGroupN;					//	�����������
	struATPAutoID*	pServerGroupIDs;				//	��������ID
	UINT32				nAlloc;							//	����ԭ��
	int					nCreateDate;					//	��������
	int					nCreateTime;					//	����ʱ��
	int					nDeleteDate;					//	ɾ������
	int					nDeleteTime;					//	ɾ��ʱ��
	UINT8				nDeleteMark;					//	ɾ����־
};
//	�û��ʺ����ʽ��ʺŹ���
struct struATPDataBaseFund
{
	char	szFund[16];										//	�ʽ��ʺ�
	char	szOrgID[16];									//	Ӫҵ��ID
	char	szMarkets[12];									//	�г�
};
//�û�
struct struATPDataBaseUser
{
	char					szUserID[16];					//	�û�ID
	char					szPwd[32];						//	�û�����
	char					szUserName[16];					//	�û���
	char					szCardID[18];					//	���֤����
	UINT32					szUserGroupIDs[4][16];			//	�û���ID
	UINT32					nPermissionIDs[32];				//	Ȩ��ID
	UINT32					nAuthorizeBeginDate;			//	��Ȩʹ�ÿ�ʼ����
	UINT32					nAuthorizeEndDate;				//	��Ȩʹ�ý�ֹ����
	UINT32					nUserStatus;					//	�û�ʹ��״̬
	char					szMobiles[2][16];				//	�ֻ�����,������
	char					szTelephones[2][12];			//	�绰����
	UINT64					nQQNumbers[2];					//	QQ����
	char					szEmails[2][64];				//	Email����
	char					szUserExplain[128];				//	�û�˵��,����������
	char					szIPs[128];						//	����IP
	char					szMacMark[40];					//	����MAC��ַ
	char					szDiskNum[32];					//	����Ӳ�����к�
	UINT32					nLimitBeginTime[4];				//	���ƿ�ʼʱ��
	UINT32					nLimitEndTime[4];				//	���ƽ���ʱ��
	char					chLimitWeek;					//	��������,0x80������
	char					chDeleteMark;					//	ɾ�����
	UINT8					nCanAssociateFundsAccount;		//	��ǰ�ʽ��ʺŽṹ����,���10��
	struATPDataBaseFund*			pATPFund;						//	�ʽ��ʺŽṹ��
	UINT32					nCanRunAlgorithm;				//	����ͬʱ�����㷨����
	UINT32					nAlgorithmN;					//	�㷨����
	GUID*					pAlgorithmIDs;					//	�㷨IDs
	UINT32					nAlgorithmGroupN;				//	�㷨�����
	struATPAutoID*		pAlgorithmGroupIDs;				//	�㷨��IDs
	char szServer[16];//ר��������
	UINT32					nServerGruopN;	
	struATPDataBaseServerGroup* pServerGruopIDs;
	char					szAdminID[16];					//	����ԱID
	UINT32					nCreateDate;					//	��������
	UINT32					nCreateTime;					//	����ʱ��
	UINT32					nLastDate;						//	����½����
	UINT32					nLastTime;						//	����½ʱ��
	UINT8					nDeleteMark;					//	ɾ����־
};									

//������־
struct	struATPManageDataBaseOperateLog
{
	char	szActorID[16];					//	��ɫID
	UINT32	nRecords;						//	��¼��
	UINT32  nOperateType;					//	��������
	UINT32	nOperateDate;					//	��������
	UINT32	nOperateTime;					//	����ʱ��
	char	szInfo[128];					//	��¼��Ϣ

};
//	�㷨��
struct	struATPDataBaseAlgorithmGroup
{
	UINT32			nID;							//	��ID  �Զ�����
	UINT32			nParentID;						//	����ID
	char			szName[16];						//	����
	char			szCreateActor[16];				//	������ɫ
	int				nCreateDate;					//	��������
	int				nCreateTime;					//	����ʱ��
	int				nDeleteDate;					//	ɾ������
	int				nDeleteTime;					//	ɾ��ʱ��
	UINT8			nDeleteMark;					//	ɾ����־
};


//	�㷨
struct struATPDataBaseAlgorithm 
{
	GUID					AlgorithmID;					//	guid Ψһ
	char					szAlgorithmName[16];			//	�㷨��
	struDataBaseAlgorithmVer		AlgorithVer;					//	�㷨�汾
	UINT8					nVersionAttribute;				//	�㷨�汾���� ���԰�֮��
	UINT8					nCharge;						//	�Ƿ��շ�
	UINT32					nGroupID;						//	�㷨��
	char					szExplain[128];					//	�㷨˵��
	char					szWarning[32];					//	�㷨����
	char					szKeyword[128];					//	�㷨�ؼ���
	UINT8					nStatus;						//	�㷨״̬
	char					szStopReason[128];				//	�㷨����ԭ��
	UINT32					nCreateDate;					//	�㷨��������
	UINT32					nCreateTime;					//	�㷨����ʱ��
	char					szPath[128];					//	�㷨ʹ��·��,·��Ҫָ��
	int						nParams;						//	�㷨��������
	struATPDataBaseAlgorithmParam*	pATPAlgorithmParams;	//	�㷨����
	UINT8					nDeleteMark;					//	ɾ�����
	char					szAdminID[16];					//	����ԱID
};


//	�㷨��־
struct struATPDataBaseAlgorithmLog
{
	GUID					AlgorithmID;					//	�㷨ID
	char					szUserID[16];					//	�û�ID
	UINT32					nUserGroupID;
	UINT32					nServerID	;					//	������ID		
	UINT32					nStatus;						//	�㷨����״̬
	UINT32					nRunBeginDate;					//	���п�ʼ����
	UINT32					nRunBeginTime;					//	���п�ʼʱ��
	UINT32					nRunEndDate;					//	���н�������
	UINT32					nRunEndTime;					//	���н���ʱ��
	UINT64					nVolume;						//	�ɽ���
	UINT64					nTurnover;						//	�ɽ���
	UINT32					nCount[20];						//	���ײ���ͳ�ƣ��������ֲ֣��ɳ������г�
	UINT32					nCompletion;					//	�㷨��ɶ�,�ٷֱ�
};

#endif	//	_ATPMANAGEDEFINE_H_