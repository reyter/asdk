//
// @Project:ATP3
// @Author:������
// @Date:2011-10-19
// @Description:ϵͳ���ģ���������ͨ�Ŷ���
// 

#pragma once

#ifndef __ATPVIGIL_MAIN_DEFINE_H__
#define __ATPVIGIL_MAIN_DEFINE_H__

#pragma pack(push,1)

//
//֮ǰФ�ܶ�����ϢID��������100��101
// ��������1000��ʼ
// 

#define ID_MSG_ATPVIGIL_MAIN_OPENSERVICE			1001		//�򿪷������
#define ID_MSG_ATPVIGIL_MAIN_TERMINATESERVICE		1002		//��ֹ�������
#define ID_MSG_ATPVIGIL_MAIN_RESTARTSERVICE			1003		//�����������
#define ID_MSG_ATPVIGIL_MAIN_SAVEWATCHINFO			1004		//�����������Ϣ 

/*
 *	����������Ϣ
 */
struct AtpVigil_Main_Service
{
	int nServerID;			//��������ʶ�����ڷֲ�ʽϵͳ�У�0��ʾ��������
	int nServiceClass;		//�������
	int nServiceID;			//����ID
};



#pragma pack(pop)


#endif
