//
//  @ Project : ATP
//  @ File Name : CirularQueue.h
//  @ Date : 2011/7/7
//  @ Author : 梁兴其 
//  
//  定义ATPTDF和ATPMAIN交互的信息
//  

#pragma once
#ifndef __ATPTDF_MAIN_DEFINDE_H__
#define __ATPTDF_MAIN_DEFINDE_H__

#pragma pack(push,1)

#define ID_MSG_ATPTDF_MAIN_REQALGSVCLIST	1	//请求算法服务列表


/*
 *	返回服务列表结构
 */
struct	AtpTdf_Main_AlgSvcList
{
	int nItems;			//服务的数目
	int nAlgSvcList[1];	//变长数组,算法服务ID列表
};

#pragma pack(pop)
#endif	//__ATPTDF_MAIN_DEFINDE_H__