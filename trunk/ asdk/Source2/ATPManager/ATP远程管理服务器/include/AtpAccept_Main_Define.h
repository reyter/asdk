
#ifndef __ATPACCEPT_MAIN_DEFINE_H__
#define __ATPACCEPT_MAIN_DEFINE_H__

#pragma pack(push,1)

/*
 *	��Ϣ���Ͷ��� 
 */
#define ID_MSG_ATPACCEPT_MAIN_STARTALGO	1	//���������������㷨ָ��,��ӦҲ�ô���Ϣ
#define ID_MSG_ATPACCEPT_MAIN_ALGOEND	2	//���㷨�����˳�ʱ��ATPMain��ATPACCEPT���ʹ���Ϣ ATPACCEPT�����Ӧ����Ϣ 

#define  ID_ALGMATCHINE_DEBUGWIN32		0
#define  ID_ALGMATCHINE_RELEASEWIN32	1
#define  ID_ALGMATCHINE_DEBUGX64		2
#define  ID_ALGMATCHINE_RELEASEX64		3

/*
*�����㷨�ı�����Ϣ
*/
struct AtpAccept_Main_StartAlgoInfo
{
	/*
	 *	�������� 
	 *	0:DEBUG Win32
	 *	1:RELEASE	Win32
	 *	2:DEBUG	x64
	 *	3:RELEASE x64
	 */
	int		nMachineType;			//�������� 

	
	char	szAlgoName[64];			//�㷨����
	char	szUserId[16];			//�û�ID
	int		nUserConnectId;			//���Ӿ��
	char	cIpType;				//IP�汾����	4:IPv4 6:IPv6
	char	szUserIp[16];			//�û����ӽ�����IP IPv4 �ô� IPv6 ���ֽ� 
	char	szUserMac[16];			//�û���Mac��ַ
	//int		nAlgSrvCount;		//���Ը��ظ��㷨�ķ������б�

	char	cAlgSvrIpType;			//IP�汾����	4:IPv4 6:IPv6
	char	szAlgSvr[16];			//���ظ��㷨�ķ�������IP IPv4 �ô� IPv6 ���ֽ� 
	int		nAlgSvrServiceId;		//�����㷨�ķ�����������ķ���ID
};

/*
 *	�����㷨�ķ�������Ϣ
 */
// struct AtpAccept_Main_AlgoSvrInfo
// {
// 	char	cIpType;				//IP�汾����	4:IPv4 6:IPv6
// 	char	szAlgoSvrIp[16];		//������Ip��ַ  IPv4 �ô� IPv6 ���ֽ� 
// 	unsigned int m_uPort;			//�������˿ں� �㷨����������Ķ˿�
// };

/*
 *�����㷨���
 */
struct AtpAccept_Main_StartAlgoResult
{
	/*
	 *	�������� 
	 *	0:DEBUG Win32
	 *	1:RELEASE	Win32
	 *	2:DEBUG	x64
	 *	3:RELEASE x64
	 */
	int		nMachineType;			//�������� 
	char	szAlgoName[64];			//�㷨����
	char	szUserId[16];			//�û�ID
	int		nUserConnectId;			//���Ӿ��
	char	cIpType;				//IP�汾����	4:IPv4 6:IPv6
	char	szUserIp[16];			//�û����ӽ�����IP IPv4 �ô� IPv6 ���ֽ� 
	char	szUserMac[16];			//�û���Mac��ַ
	int		nServiceId;				//�����ɹ����㷨ID
	int		nResult;				//�ɹ�Ϊ0������ʱΪ����ֵ
	char	szError[256];			//����˵��
};

/*
 *	�㷨�����˳�ʱ
 *	ATPMain��ATPACCEPT���ʹ���Ϣ
 */
struct AtpAccept_Main_AlgoEnd
{
	int nAlgoServiceId;		//�㷨����ID
};

#pragma pack(pop)
#endif	//__ATPACCEPT_MAIN_DEFINE_H__