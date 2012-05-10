/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨�û���ÿ���û�����Ե��㷨����.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-7-28		��ΰ		 ����
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
�û���Ϣ,�����ж��Ƿ���ͬһ�û�.
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
�㷨�û��ࡣ
ÿһ��ʹ���㷨���û��������ڴ����д˾���.
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
	�û���Ϣ.
	*/	
	ATP_User_Info  m_userInfo;
	
	/**
	һ���û����ܿ�������㷨�Ự.
	*/	
	void Append(CAlgoSession* pSession);

	/**
	ɾ���Ự.
	*/
	void Remove(CAlgoSession* pSession);


	/**
	�Ƿ��ǿ��û�.
	*/ 	
    bool IsEmpty();

	/**
	��ѯ�Ự��״̬.
	@param nItems  ����������
	@return ����״̬����.
	*/	
	ATP_Msg_Sec_CurrentAlgoStatus* QueryAlgoStatus(int& nItems);

protected:
    list<CAlgoSession*> m_lsAlgoSession;
};


#endif //__ALGOUSER_H_