/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法用户，每个用户其独自的算法管理.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-7-28		李伟		 创建
-------------------------------------------------------------
*/
#pragma once
#ifndef __ALGOUSER_H_
#define __ALGOUSER_H_


#include <list>
using namespace std;

class CAlgoSession;

#include "..\Include\ATSvr\OpenTDProtocol.h"


/**
用户信息,用于判断是否是同一用户.
*/
struct AFX_EXT_CLASS ATP_User_Info
{
	CString szUserOrg;
	CString szUserID;

	ATP_User_Info()
	{

	}

	ATP_User_Info(UTI_LoginRequest& req)
	{
		szUserID = req.chOrgID;
		szUserOrg = req.chUserID;
	}

	ATP_User_Info& operator = (UTI_LoginRequest& req )
	{
		szUserID = req.chOrgID;
		szUserOrg = req.chUserID;
		return *this;
	}

	bool operator == (ATP_User_Info& right) 
	{
		return (szUserOrg == szUserOrg && szUserID==szUserID);
	}

	bool operator<(const ATP_User_Info& right) const
	{
		return (szUserOrg + szUserID) < (right.szUserOrg + right.szUserID);
	}

	operator LPCTSTR()
	{
		return szUserOrg+szUserID;
	}
};


/**
算法用户类。
每一个使用算法的用户，会在内存中有此镜像.
*/ 
class AFX_EXT_CLASS CAlgoUser
{
public:
	CAlgoUser();
	virtual ~CAlgoUser(void);

protected:
	CRITICAL_SECTION m_cs;

public:

	/**
	用户信息.
	*/	
	ATP_User_Info  m_userInfo;
	
	/**
	一个用户可能开启多个算法会话.
	*/	
	void Append(CAlgoSession* pSession);

	/**
	删除会话.
	*/
	void Remove(CAlgoSession* pSession);


	/**
	是否是空用户.
	*/ 	
    bool IsEmpty();

	/**
	查询会话的状态.
	@param nItems  返回数组数
	@return 返回状态数据.
	*/	
	ATP_Msg_Sec_CurrentAlgoStatus* QueryAlgoStatus(int& nItems);

protected:
    list<CAlgoSession*> m_lsAlgoSession;
};


#endif //__ALGOUSER_H_