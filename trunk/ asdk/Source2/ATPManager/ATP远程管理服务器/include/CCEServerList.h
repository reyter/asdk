/**
* @Copyright 深圳市创真科技有限公司(www.hh.com.cn)
* @System	 通用通信库(Common Communication Environment Core)
* @Brief	 模板类，用于定义多TCP Server地址.
* @Author	 wli
* @Usage	 请将此文件 include 到 stdafx.h 中	
* @Date      2010-10-21
*/

#pragma once
#ifndef _CCCESERVERLIST_H_
#define _CCCESERVERLIST_H_

#include "CCEDefine.h"

/**
*	连接的服务器信息.
*
*/
class AFX_EXT_CLASS CCCETCPServerInfo
{
public:
	
	CCCETCPServerInfo(const char* szIp,
		int nPort,
		int nLevel,				//服务器的连接优先级.
		const CCE_PROXYDATA* pProxy,	//连接该服务器所使用的代理地址.
		const BYTE*	pExtraData,		//附加信息.
		int     nExtraDataLen);	//附加信息长度.

	CCCETCPServerInfo(const CCCETCPServerInfo& right);	//附加信息长度.

	
	virtual ~CCCETCPServerInfo();

	CCCETCPServerInfo& operator=( const CCCETCPServerInfo& right);

	bool operator>(const CCCETCPServerInfo& right) const;

public:
	CString				m_ip;			//IP地址
	USHORT				m_port;			//端口
	int					m_nLevel;		//优先级.
	CCE_PROXYDATA		m_proxy;		//欲使用的代理服务器地址
	BYTE*				m_pExtraData;	//额外附加数据
	int                 m_nExtraDataLen;	//额外附加的数据长度.

	friend class CCCEClientProcessor_MultiServer;
};

// TEMPLATE STRUCT delete_Pointer
template<class Type>
struct CCE_delete_Pointer
{
	void operator()(Type* elem) const
	{
		delete elem;
	}
};

// TEMPLATE STRUCT greater_PointerServerInfo
struct CCE_greater_PointerServerInfo
	: public binary_function<CCCETCPServerInfo*, CCCETCPServerInfo*, bool>
{	
	bool operator()(CCCETCPServerInfo *& _Left,CCCETCPServerInfo *& _Right) const
	{	
		return ( *_Left > *_Right);
	}
};



/**
*	连接的服务器信息.
*	@param TExtraData 额外附加的数据.
*	@param bAutoSort  是否自动排序.
*/

class AFX_EXT_CLASS CCCEServerList: protected list<CCCETCPServerInfo*>
		
{
public:
	CCCEServerList(void);
	virtual ~CCCEServerList(void);
	
	/**
	*	Add Server 2 list
	*/	
	void AddServer(const CCCETCPServerInfo* pSvr);

	
	/**
	* 取最先的服务器地址.
	* 并将当前地址设为取得的地址.
	*/
	const CCCETCPServerInfo* GetFirstServer();


	/**
	* 取下一的服务器地址.
	* 并将当前地址设为取得的地址.
	* @param pSvr  取该地址的下一地址.
	*/
	const CCCETCPServerInfo* GetNextServer(const CCCETCPServerInfo* pSvr);


private:

	//CCCETCPServerInfo* m_pCurrentSvr;	//当前使用的连接.

	friend class CCCEClientProcessor_MultiServer;
};

#endif //_CCCESERVERLIST_H_