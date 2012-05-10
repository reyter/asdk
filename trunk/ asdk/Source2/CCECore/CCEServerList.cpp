#include "StdAfx.h"
#include ".\cceserverlist.h"



CCCETCPServerInfo::CCCETCPServerInfo(const char* szIp,
				  int nPort,
				  int nLevel,
				  const CCE_PROXYDATA* pProxy,
				  const BYTE*	pExtraData,
				  int     nExtraDataLen)
		:m_ip(szIp),
		m_port(nPort),
		m_nLevel(nLevel),
		m_proxy(*pProxy),
		m_pExtraData(NULL),
		m_nExtraDataLen(nExtraDataLen)

{
	if(pExtraData && nExtraDataLen>0)
	{
		m_pExtraData = new BYTE[nExtraDataLen];
		memcpy(m_pExtraData,pExtraData,nExtraDataLen);
	}
}

CCCETCPServerInfo::CCCETCPServerInfo(const CCCETCPServerInfo& right)	//附加信息长度
:m_pExtraData(NULL)
{
	*this = right;
}

CCCETCPServerInfo::~CCCETCPServerInfo()
{
	if(m_pExtraData)
	{
		delete []m_pExtraData;
	}

}

CCCETCPServerInfo& CCCETCPServerInfo::operator=( const CCCETCPServerInfo& right)
{
	if(this != &right)
	{
		m_ip = right.m_ip;
		m_port = right.m_port;
		m_proxy = right.m_proxy;
		delete m_pExtraData;			//ReAlloc And Copy.
		m_pExtraData = new BYTE[right.m_nExtraDataLen];
		m_nExtraDataLen = right.m_nExtraDataLen;
		if(right.m_pExtraData)
			memcpy(m_pExtraData,right.m_pExtraData,m_nExtraDataLen);
	}
	return *this;
}


bool CCCETCPServerInfo::operator>(const CCCETCPServerInfo& right) const
{
	return m_nLevel > right.m_nLevel;
}


////////////////////////////////////////////////////////////////////////////////////////////


void CCCEServerList::AddServer(const CCCETCPServerInfo* pSvr)
{
	push_back(new CCCETCPServerInfo(*pSvr));
	sort( CCE_greater_PointerServerInfo() );	
	
}

//const CCCETCPServerInfo* CCCEServerList::GetCurrentServerInfo()
//{
//	return m_pCurrentSvr;
//}

CCCEServerList::CCCEServerList()
	//:m_pCurrentSvr(NULL)
{	
	
}

CCCEServerList::~CCCEServerList()
{
	for_each<CCCEServerList::iterator,CCE_delete_Pointer<CCCETCPServerInfo> >(begin(),end(),CCE_delete_Pointer<CCCETCPServerInfo>());
	clear();
}

const CCCETCPServerInfo* CCCEServerList::GetFirstServer()
{
	CCCETCPServerInfo* pCurrentSvr=NULL;
	if(size()==0)
		pCurrentSvr = NULL;
	else 
		pCurrentSvr = *(begin());

	return pCurrentSvr;
}

const CCCETCPServerInfo* CCCEServerList::GetNextServer(const CCCETCPServerInfo* pSvr)
{
	CCCETCPServerInfo* pCurrentSvr=NULL;

	if(pSvr == NULL)
	{
		if(size()>0)
			return *begin();
		else
			return NULL;
	}else
	{
		ASSERT(size()>0);

		iterator it = find<iterator>(begin(),end(),pSvr);

		if(it!=end())
			++it;

		// Increment.
		if(it==end())
		{
			it = begin();
		}

		if(it!=end())
		{
			pCurrentSvr = *(it);
		}else 
		{
			pCurrentSvr = NULL;
		}

		return pCurrentSvr;
	}
}