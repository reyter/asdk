//
//  @ Project : ATP
//  @ File Name : CirularQueue.h
//  @ Date : 2011/7/7
//  @ Author : ������ 
//  
//  ����ATPTDF��ATPMAIN��������Ϣ
//  

#pragma once
#ifndef __ATPTDF_MAIN_DEFINDE_H__
#define __ATPTDF_MAIN_DEFINDE_H__

#pragma pack(push,1)

#define ID_MSG_ATPTDF_MAIN_REQALGSVCLIST	1	//�����㷨�����б�


/*
 *	���ط����б�ṹ
 */
struct	AtpTdf_Main_AlgSvcList
{
	int nItems;			//�������Ŀ
	int nAlgSvcList[1];	//�䳤����,�㷨����ID�б�
};

#pragma pack(pop)
#endif	//__ATPTDF_MAIN_DEFINDE_H__