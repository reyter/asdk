/**
* @Copyright �����д���Ƽ����޹�˾(www.hh.com.cn)
* @System	 ͨ��ͨ�ſ�(Common Communication Environment Core)
* @Brief	 ģ���࣬���ڶ����TCP Server��ַ.
* @Author	 wli
* @Usage	 �뽫���ļ� include �� stdafx.h ��	
* @Date      2010-10-21
*/

#pragma once
#ifndef _CCCESERVERLIST_H_
#define _CCCESERVERLIST_H_

#include "CCEDefine.h"

/**
*	���ӵķ�������Ϣ.
*
*/
class AFX_EXT_CLASS CCCETCPServerInfo
{
public:
	
	CCCETCPServerInfo(const char* szIp,
		int nPort,
		int nLevel,				//���������������ȼ�.
		const CCE_PROXYDATA* pProxy,	//���Ӹ÷�������ʹ�õĴ����ַ.
		const BYTE*	pExtraData,		//������Ϣ.
		int     nExtraDataLen);	//������Ϣ����.

	CCCETCPServerInfo(const CCCETCPServerInfo& right);	//������Ϣ����.

	
	virtual ~CCCETCPServerInfo();

	CCCETCPServerInfo& operator=( const CCCETCPServerInfo& right);

	bool operator>(const CCCETCPServerInfo& right) const;

public:
	CString				m_ip;			//IP��ַ
	USHORT				m_port;			//�˿�
	int					m_nLevel;		//���ȼ�.
	CCE_PROXYDATA		m_proxy;		//��ʹ�õĴ����������ַ
	BYTE*				m_pExtraData;	//���⸽������
	int                 m_nExtraDataLen;	//���⸽�ӵ����ݳ���.

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
*	���ӵķ�������Ϣ.
*	@param TExtraData ���⸽�ӵ�����.
*	@param bAutoSort  �Ƿ��Զ�����.
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
	* ȡ���ȵķ�������ַ.
	* ������ǰ��ַ��Ϊȡ�õĵ�ַ.
	*/
	const CCCETCPServerInfo* GetFirstServer();


	/**
	* ȡ��һ�ķ�������ַ.
	* ������ǰ��ַ��Ϊȡ�õĵ�ַ.
	* @param pSvr  ȡ�õ�ַ����һ��ַ.
	*/
	const CCCETCPServerInfo* GetNextServer(const CCCETCPServerInfo* pSvr);


private:

	//CCCETCPServerInfo* m_pCurrentSvr;	//��ǰʹ�õ�����.

	friend class CCCEClientProcessor_MultiServer;
};

#endif //_CCCESERVERLIST_H_