//
//@Proejct:ATP3
//@Date:2011/10/12
//@Author:������
//@Description:�㷨����ƽ̨������������������ά��ط�������ͨ�Ŷ���
//

#pragma once
#ifndef __ATPVIGIL_MANAGER_DEFINE_H__
#define __ATPVIGIL_MANAGER_DEFINE_H__

#pragma pack(push,1)

#define ID_MSG_ATPVIGIL_MANAGER_ADMINLOGIN	1		//��¼
#define ID_MSG_ATPVIGIL_MANAGER_UNCONNECT	2		//�Ͽ����� 

struct AtpVigil_Manager_UserInfo 
{
	UINT uUserId;		//����ԱId
	int nConnectId;		//���Ӿ�� ������ʶΨһ�� 
	char chAccount[24];	//����Ա�˺�
	char chStatus[40];  //״̬˵��
	char chInfo1[48];	//����
	char chInfo2[48];	//����
	int  nAppType;		//����
	int  nAppDate;		//����
	int nAppTime;		//ʱ��
	int  nLocalPort;   	//����˿�
	int  nRemotePort;	//��¼�Ķ˿�
	int  nRemoteIP;  	//��¼��IP
};

#pragma pack(pop)

#endif	//__ATPVIGIL_MANAGER_DEFINE_H__