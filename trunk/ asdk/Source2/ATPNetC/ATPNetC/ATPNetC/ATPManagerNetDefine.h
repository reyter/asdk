#pragma once

#ifndef _ATPMANAGERNETDEFINE_H_
#define _ATPMANAGERNETDEFINE_H_

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

//	��Ϣ����
#define	ID_ATPMANAGE_LOGIN							50001//	��¼
//#define	ID_ATPMANAGE_LOGINANSWER					50002//	��¼Ӧ��

#define	ID_ATPMANAGE_QUERYOPERATELOG				50010//	��ѯ������־(��������Ա,����Ա)

/************************************************************************/
/*			��������Ա                                                                     */
/************************************************************************/
//����Ա
#define	ID_ATPMANAGE_CREATEMANAGER					50021//	��������Ա(��������Ա)
#define	ID_ATPMANAGE_DELETEMANAGER					50022//	ɾ������Ա(��������Ա)
#define	ID_ATPMANAGE_MODIFYMANAGER					50023//	�޸Ĺ���Ա(��������Ա������Ա)
#define	ID_ATPMANAGE_QUERYMANAGERINFO				50024//	��ѯ����Ա(��������Ա)

//��������
#define	ID_ATPMANAGE_CREATESERVERGROUP				50031//	������������(��������Ա)
#define	ID_ATPMANAGE_DELETESERVERGROUP				50032//	ɾ����������(��������Ա)
#define	ID_ATPMANAGE_MODIFYSERVERGROUP				50033//	�޸ķ�������(��������Ա)
#define	ID_ATPMANAGE_QUERYSERVERGROUPINFO			50034//	��ѯ��������(��������Ա)

//������
#define	ID_ATPMANAGE_CREATESERVER					50041//	����������(��������Ա)
#define	ID_ATPMANAGE_DELETESERVER					50042//	ɾ��������(��������Ա)
#define	ID_ATPMANAGE_MODIFYSERVER					50043//	�޸ķ�����(��������Ա)
#define	ID_ATPMANAGE_QUERYSERVERINFO				50044//	��ѯ������(��������Ա)

//Ȩ��
#define	ID_ATPMANAGE_QUERYPERMISSIONINFO			50051//	��ѯȨ��(��������Ա������Ա)

/************************************************************************/
/*                                       ����Ա                               */
/************************************************************************/

//�㷨��
#define	ID_ATPMANAGE_ADDALGORITHMGROUP				51011//	����㷨��(����Ա)
#define	ID_ATPMANAGE_DELETEALGORITHMGROUP			51012//	ɾ���㷨��(����Ա)
#define ID_ATPMANAGE_MODIFYALGORITHMGROUP			51013//	�޸��㷨��(����Ա)
#define ID_ATPMANAGE_QUERYALGORITHMGROUPINFO		51014//��ѯ�㷨��(����Ա)
													 
//�㷨
#define	ID_ATPMANAGE_ADDALGORITHM					51021//	����㷨��Ϣ(����Ա)
#define	ID_ATPMANAGE_DELETEALGORITHM				51022//	ɾ���㷨��Ϣ(����Ա)
#define	ID_ATPMANAGE_MODIFYALGORITHM				51023//	�޸��㷨(����Ա)
#define	ID_ATPMANAGE_MODIFYALGORITHMINFO			51024//	�޸��㷨��Ϣ(����Ա)

//�㷨����
#define	ID_ATPMANAGE_QUERYALGORITHMINFO				51025//	��ѯ�㷨��Ϣ(����Ա)
#define	ID_ATPMANAGE_QUERYALGORITHMPARAM			51026//	��ѯ�㷨����
#define	ID_ATPMANAGE_QUERYALGORITHMVERSION			51027//	��ѯ�㷨��ʷ�汾

//�û���												 
#define	ID_ATPMANAGE_ADDUSERGROUP					51041//	����û���(����Ա)
#define	ID_ATPMANAGE_DELETEUSERGROUP				51042//	ɾ���û���(����Ա)
#define	ID_ATPMANAGE_MODIFYUSERGROUP				51043//	�޸��û���(����Ա)
#define	ID_ATPMANAGE_QUERYUSERGROUPINFO				51044//	��ѯ�û�����Ϣ(����Ա)

//�û�
#define	ID_ATPMANAGE_ADDUSER						51051//	����û�(����Ա)
#define	ID_ATPMANAGE_DELETEUSER						51052//	ɾ���û�(����Ա)
#define	ID_ATPMANAGE_MODIFYUSER						51053//	�޸��û�(����Ա)
#define	ID_ATPMANAGE_QUERYUSERINFO					51054//	��ѯ�û���Ϣ(����Ա)

//�û�������־
#define	ID_ATPMANAGE_QUERYUSEROPERATELOG			51061//	��ѯ�û�������־(����Ա)struReq_ATPManage_ATPManageOperateLog

//�㷨��־
#define	ID_ATPMANAGE_QUERYUSEDALGORITHM				51071//	��ѯ�㷨ͳ����Ϣ(����Ա)
#define	ID_ATPMANAGE_QUERYUSERALGORITHM				51072//	��ѯ�û�ʹ���㷨ͳ����Ϣ(����Ա)
#define	ID_ATPMANAGE_QUERYSERVERALGORITHM			51073//	��ѯ�����������㷨ͳ����Ϣ(����Ա)




/************************************************************************/
/*                                   �û�����                                   */
/************************************************************************/
#define	ID_ATPMANAGE_USER_QUERYALGORITHM			520001//	��ѯ�㷨(�û�)
#define	ID_ATPMANAGE_USER_ADDALGORITHM				520002//	����㷨(�û�)
#define	ID_ATPMANAGE_USER_DELETEALGORITHM			520003//	ɾ���㷨(�û�)
#define	ID_ATPMANAGE_USER_RUNALGORITHM				520004//	�����㷨(�û�)
#define	ID_ATPMANAGE_USER_MODIFYINFO				520005//	�޸���Ϣ(�û�)

//////////////////////////////////////////////////////////////////////////




//! ��Ϣ��ͷ
struct stru_ATPManageMsgHeadInfo
{	
	UINT16 nHeadSize;				//	
	UINT16 nChannel;				//	����ͨ��
	UINT32 nMsgType;				//	��Ϣ����
	UINT32 nFlags;					//	
};
const int g_stru_ATPManageMsgHeadInfoSize = sizeof stru_ATPManageMsgHeadInfo;

struct stru_BlockHead
{
	UINT32 nItems;
	UINT32 nItemSize;

};

//�汾
struct stru_AlgorithmVer
{
	short Ver[4];
};

//	�㷨����
struct stru_ATPAlgorithmParam
{
	
};

//�ֹ������ID,
struct	stru_ATPID
{
	char	szID[16];
	char	szName[16];
};
//�Զ�����ID
struct	stru_ATPAutoID
{
	UINT32	nID;
	char	szName[16];
};

//��׼���ؽ��
struct	struAns_Operate
{
	char	szInfo[128];			//	������Ϣ
	UINT8	nResult;				//	���ؽ�� 0�ɹ�  �������
};


//! ***********************************************************************/
//!                    ��¼                                                
//! ***********************************************************************/


//! �û���¼
struct	struReq_ATPManageLogin
{
	char				szLoginID[16];		//	�˺�
	char				szIP[32];			//	�û�IP
	char				szMAC[16];			//	MAC
	char				szDiskNum[64];		//	Ӳ�����к�
	char				szPassword[32];		//	����
	char				chMD5[32];			//	MD5��֤��
	char				chProduct[16];		//	��Ʒ��
	stru_AlgorithmVer	Ver[4];				//	�汾��
};


//! ************************************************************************
//! ��������Ա  
//! ************************************************************************
   
//! ******************
//!    ����Ա 
//! ******************
struct	stru_ATPManagerInfo
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
	stru_BlockHead			ServerBlock;		//	����������items	itemsize = sizeof(struATPAutoID)   ������IDs
	stru_BlockHead			ServerGroupBlock;	//	�����������items   itemsize = sizeof(struATPAutoID)  ��������IDs
};				
//! ��ӹ���Ա
//ID_ATPMANAGE_CREATEMANAGER

//! �޸Ĺ���Ա
//ID_ATPMANAGE_MODIFYMANAGER

//! ɾ������Ա
//ID_ATPMANAGE_DELETEMANAGER

//! �鿴����Ա
//ID_ATPMANAGE_QUERYADMIN						-----�鿴���й���Ա����������ѯ


//////////////////////////////////////////////////////////////////////////
//! ******************
//!     ��������		  *
//! ******************
struct stru_ATPServerGroupInfo
{
	UINT32			nID;				//	��ID �Զ�����
	UINT32			nParentID;			//	����ID
	char			szName[16];			//	����
	char			szExplain[128];		//	˵��
	UINT32			nCreateDate;		//	��������
	UINT32			nCreateTime;		//	����ʱ��
	UINT8			nDeleteMark;		//	ɾ�����
};
//! ��ӷ�������	
//ID_ATPMANAGE_CREATESERVERGROUP

//! �޸ķ�������
//ID_ATPMANAGE_MODIFYSERVERGROUP
//! ɾ����������
//ID_ATPMANAGE_DELETESERVERGROUP

//! �鿴��������
//ID_ATPMANAGE_QUERYSERVERGROUP		------�鿴���з���������������ѯ


//////////////////////////////////////////////////////////////////////////
//! *****************
//!      ������       
//! *****************
struct	stru_ATPServerInfo
{
	UINT32			nID;						//	������ID �Զ�����
	char			szName[16];					//	��������
	char			szIP[16];					//	������IP
	UINT32			nPort;						//	�������˿ں�
	UINT32			nGroupID[16];				//	��������
	UINT32			nCreateDate;				//	��������
	UINT32			nCreateTime;				//	����ʱ��
	UINT8			nDeleteMark;				//	ɾ�����
};
//! ��ӷ�����
//ID_ATPMANAGE_CREATESERVER

//! �޸ķ�����
//ID_ATPMANAGE_MODIFYSERVER

//! ɾ��������
//ID_ATPMANAGE_DELETESERVER

//! �鿴������
//ͨ����ID��ѯ������
//ID_ATPMANAGE_QUERYSERVER						
struct struReq_ATPServerInfo_QUERY
{
	UINT32			nGroupID;						//	  �����ѯȫ��������
};


//////////////////////////////////////////////////////////////////////////
//! ******************
//!     Ȩ��		  *
//! ******************
struct stru_ATPPermissionInfo
{
	UINT32		nPermissionID;					//	Ȩ��ID �Զ�����
	char		szPermissionName[16];			//	Ȩ����
	UINT8		nPermissionType;				//	Ȩ������
};					
//! �鿴Ȩ��
//ͨ��Ȩ��ID��ѯȨ��
//ID_ATPMANAGE_QUERYPERMISSION					-----�鿴����Ȩ�ޣ�������������ѯ


//////////////////////////////////////////////////////////////////////////
/************************************************************************/
//!                      ��ͨ����Ա                                          
/************************************************************************/
//! *****************
//!       ����Ա      *
//! ******************
//! �޸Ĺ���Ա(�Լ�)��Ϣ
//ID_ATPMANAGE_MODIFYMANAGER
//stru_ATPManagerInfo


//////////////////////////////////////////////////////////////////////////
//! *****************
//!       �û���      *
//! ******************
struct	stru_ATPUserGroupInfo
{
	UINT32				nID;							//	��ID  �Զ�����
	UINT32				nParentID;						//	����ID
	char				szName[16];						//	����
	char				szCreateActor[16];				//	������ɫ
	char				szExplain[64];					//	˵����Ϣ
	stru_BlockHead		AlgorithmBlock;					//	�㷨���� Item ,   itemsize=sizeof(struATPAutoID) �㷨IDs
	stru_BlockHead		AlgorithmGroupBlock;			//	�㷨�����Item  , itemsize=sizeof(struATPAutoID)  �㷨��IDs
	stru_BlockHead		ServerBlock;					//	����������Item,	itemsize=sizeof(struATPAutoID) ������IDs
	stru_BlockHead		ServerGroupBlock;				//	�����������Item  ,itemsize=sizeof(struATPAutoID)  ��������IDs
	UINT32				nAlloc;							//	����ԭ��
	int					nCreateDate;					//	��������
	int					nCreateTime;					//	����ʱ��
	int					nDeleteDate;					//	ɾ������
	int					nDeleteTime;					//	ɾ��ʱ��
	UINT8				nDeleteMark;					//	ɾ����־
};
//! ����û���
//ID_ATPMANAGE_ADDUSERGROUP

//! �޸��û���
//ID_ATPMANAGE_MODIFYUSERGROUP

//! ɾ���û���
//ID_ATPMANAGE_DELETEUSERGROUP

//! �鿴�û���
//ID_ATPMANAGE_QUERYUSERGROUPINFO				----------�鿴�����û��飬��������ѯ


////////////////////////////////////////////////////////////////////////// 
//! *****************
//!     �û�      *
//! ******************
//! �û��ʺ����ʽ��ʺŹ���
struct stru_ATPFundInfo
{
	char	szFund[16];										//	�ʽ��ʺ�
	char	szOrgID[16];									//	Ӫҵ��ID
	char	szMarkets[12];									//	�г�
};
//! �û�
struct stru_ATPUserInfo
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
	stru_BlockHead			FundBlock;						//	��ǰ�ʽ��ʺŽṹ����Items,���10��         itemsize = sizeof(struATPID)
	UINT32					nCanRunAlgorithm;				//	����ͬʱ�����㷨����
	stru_BlockHead			AlgorithmBlock;					//	�㷨����items  ,  itemsize = sizeof(struATPAutoID)
	stru_BlockHead			AlgorithmGroupBlock;			//	�㷨����� items, itemsize = sizeof(struATPAutoID)
	char					szServer[16];
	stru_BlockHead			ServerGroupBlock;
	UINT32					nCreateDate;					//	��������
	UINT32					nCreateTime;					//	����ʱ��
	UINT32					nLastDate;						//	����½����
	UINT32					nLastTime;						//	����½ʱ��
	UINT8					nDeleteMark;					//	ɾ����־

};									
//! ����û�
//ID_ATPMANAGE_ADDUSER

//! �޸��û�
//ID_ATPMANAGE_MODIFYUSER

//! ɾ���û�
//ID_ATPMANAGE_DELETEUSER

//! �鿴�û�
//ID_ATPMANAGE_QUERYUSER
//ͨ���û���ID��ѯ�û�
struct struReq_ATPUserInfo_QUERY
{
	UINT32 nID;												//�����ѯȫ���û�
};


//////////////////////////////////////////////////////////////////////////
//! ******************
//!     ������־         *
//! ******************
struct	stru_ATPManageOperateLogInfo
{
	char	szActorID[16];					//	��ɫID
	UINT32	nRecords;						//	��¼��
	UINT32  nOperateType;					//	��������
	UINT32	nOperateDate;					//	��������
	UINT32	nOperateTime;					//	����ʱ��
	char	szInfo[128];					//	��¼��Ϣ

};
//! �鿴�û�������־
//ͨ����ʼ����ʱ�䣬�������͡��û�ID��ѯ�û�������־
//ID_ATPMANAGE_QUERYUSEROPERATELOG
struct struReq_ATPManageOperateLog_QUERY
{
	int		nBeginDate;
	int		nEndDate;
	int		nOperateType;
	char	szUserID[16];					//	�û�ID ����鿴ȫ��
};


//////////////////////////////////////////////////////////////////////////
//! *****************
//!        �㷨��     *
//! ******************
struct	stru_ATPAlgorithmGroupInfo
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
//! ����㷨��
//ID_ATPMANAGE_ADDALGORITHMGROUP

//! �޸��㷨��
//ID_ATPMANAGE_MODIFYALGORITHMGROUP

//! ɾ���㷨��
//ID_ATPMANAGE_DELETEALGORITHMGROUP

//! �鿴�㷨��
//ID_ATPMANAGE_QUERYALGORITHMGROUP			--------�鿴�����㷨�飬������������ѯ


//////////////////////////////////////////////////////////////////////////
//! ******************
//!        �㷨            *
//! ******************
struct stru_ATPAlgorithmInfo
{
	GUID					AlgorithmID;					//	guid Ψһ
	char					szAlgorithmName[16];			//	�㷨��
	stru_AlgorithmVer		AlgorithVer;					//	�㷨�汾
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
	stru_BlockHead			AlgorithmBlock;					//	�㷨��������  �㷨����
	UINT8					nDeleteMark;					//	ɾ����־
};

//! ����㷨
//ID_ATPMANAGE_ADDALGORITHM

//! �޸��û�
//ID_ATPMANAGE_MODIFYALGORITHM

//! ɾ���û�
//ID_ATPMANAGE_DELETEALGORITHM

//! �鿴�㷨.
//ͨ���㷨��ID��ѯ
//ID_ATPMANAGE_QUERYALGORITHM
struct struReq_ATPManage_QueryAlgorithm
{
	UINT32			nGroupID;								//	�����ѯȫ��
};

//ͨ���㷨ID��ѯ�㷨�汾
//ID_ATPMANAGE_QUERYALGORITHMVERSION
struct struReq_ATPManage_QueryAlgorithmHistoryVersion
{
	GUID			guid;									//	�㷨ID
};

//ͨ���㷨ID���汾����ѯ�㷨����
//ID_ATPMANAGE_QUERYALGORITHMPARAM
struct struReq_ATPManage_QueryAlgorithmParam
{
	GUID				guid;								//	�㷨ID  
	stru_AlgorithmVer	Ver;								//	�㷨�汾
};

//////////////////////////////////////////////////////////////////////////
//! ******************
//!        �㷨��־��   *
//! ******************
struct stru_ATPAlgorithmRunLogInfo
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
//! ��ѯ����־
//��ѯ�㷨
//ID_ATPMANAGE_QUERYUSEDALGORITHM
struct struReq_ATPAlgorithmRunLogInfo_QUERY
{
	UINT32					nRunBeginDate;					//	���п�ʼ����
	UINT32					nRunEndDate;					//	���н�������  Ϊ�����ѯ���������㷨 
	GUID					AlgorithmID;					//	�㷨ID  Ϊ����ȫ���㷨
};
//��ѯ�û�ʹ���㷨��Ϣ
//ID_ATPMANAGE_QUERYUSERALGORITHM
struct struReq_ATPUserRunLogInfo_QUERY
{
	UINT32					nRunBeginDate;					//	���п�ʼ����
	UINT32					nRunEndDate;					//	���н�������  Ϊ�ղ�ѯ���������㷨 
	char					szUserID[16];					//	�û�ID Ϊ����������û�
};
//��ѯ������ʹ���㷨��Ϣ
//ID_ATPMANAGE_QUERYSERVERALGORITHM
struct struReq_ATPServerRunLogInfo_QUERY
{
	UINT32					nRunBeginDate;					//	���п�ʼ����
	UINT32					nRunEndDate;					//	���н�������  Ϊ�ղ�ѯ���������㷨 
	UINT32					nServerID	;					//	������ID ����ȫ��������
};

#endif	//	_ATPMANAGEDEFINE_H_