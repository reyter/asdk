
#ifndef __QUOTE_FARM_SVR_H__
#define __QUOTE_FARM_SVR_H__

#include "stdafx.h"
#include "..\\public\\xml\\xmlparser.h"
#include <string>

struct SSvr//服务器
{
	CString m_strName;
	CString m_strIP;
	int		m_nPort;
};

struct SSvrGrp//服务器组
{
	CString m_strName;//名称
	std::vector<SSvr *>	m_vpSvrs;//服务列表
	SSvr	m_svrUserInfo;//用户服务
	SSvr	m_svrTrade;//交易服务
	std::vector<SSvr *>	m_vpTradeSvrs;//交易服务列表
	SSvr	m_svrTeaching;//在线培训
};

class CSvr : public TiXmlParser
{
public:
	CSvr();
	~CSvr();
	virtual void OnNode(TiXmlElement *pElm,NODEWAY way);//, void *lParam);
	virtual void* OnNode(std::string NodeName, void *lParam);
	virtual void OnText(std::string NodeName, std::string NodeText, void *lParam);
	virtual void OnAttr(std::string NodeName, std::string AttrName, std::string AttrText, void *lParam);

	bool Init();
	bool ChangeSystemItem(const char *c_pItemName,const char * c_pItemValue,bool c_bAdd)
	{
		TiXmlElement *pRootElm = RootElement();
		TiXmlElement * pElmSystem = pRootElm->FirstChildElement("SYSTEM");
		TiXmlElement * pElmItem = pElmSystem->FirstChildElement(c_pItemName);
		if (pElmItem == NULL && c_bAdd == false)
			return false;
		if (pElmItem == NULL)
		{
			pElmItem = new TiXmlElement(c_pItemName);
			TiXmlElement * pAddItem = (TiXmlElement *)pElmSystem->InsertEndChild(*pElmItem);
			pElmItem = pAddItem;
		}
		if (pElmItem)
			pElmItem->SetText(c_pItemValue);
	}
	bool ChangeServerItem(const char *c_pItemName,const char * c_pItemValue,bool c_bAdd)
	{
		TiXmlElement *pRootElm = RootElement();
		TiXmlElement * pElmSystem = pRootElm->FirstChildElement("SERVER");
		TiXmlElement * pElmItem = pElmSystem->FirstChildElement(c_pItemName);
		if (pElmItem == NULL && c_bAdd == false)
			return false;
		if (pElmItem == NULL)
		{
			pElmItem = new TiXmlElement(c_pItemName);
			TiXmlElement * pAddItem = (TiXmlElement *)pElmSystem->InsertEndChild(*pElmItem);
			pElmItem = pAddItem;
		}
		if (pElmItem)
			pElmItem->SetText(c_pItemValue);
		return true;
	}
	SSvrGrp * GetSvrGrpByName(CString c_strName)
	{
		for(int n=0; n<m_vpGrp.size(); n++)
		{
			if (m_vpGrp.at(n)->m_strName == c_strName)
				return m_vpGrp.at(n);
		}
		return NULL;
	}
	bool GetQuoteServer(CString &c_strIP,int &c_nPort,CString &c_strGrpName,int c_nUserID)
	{
		if (m_vpGrp.size() == 0)
			return false;

		SSvrGrp * pGrp = NULL;
		if (!c_strGrpName.IsEmpty())
			pGrp = GetSvrGrpByName(c_strGrpName);
		if (!pGrp)
		{
			pGrp = m_vpGrp.at(0);
			c_strGrpName = pGrp->m_strName;
		}
		if (pGrp->m_vpSvrs.size() == 0)
			return false;
		int nIndex = 0;
		if (c_nUserID > 0)
			nIndex = (c_nUserID+1) % pGrp->m_vpSvrs.size();
			//nIndex = (c_nUserID) % pGrp->m_vpSvrs.size();
		c_strIP = pGrp->m_vpSvrs.at(nIndex)->m_strIP;
		c_nPort = pGrp->m_vpSvrs.at(nIndex)->m_nPort;
		if (c_strGrpName.IsEmpty())
			c_strGrpName = pGrp->m_strName;

		if (pGrp->m_vpTradeSvrs.size() == 1)
		{
			pGrp->m_svrTrade.m_strIP = pGrp->m_vpTradeSvrs.at(0)->m_strIP;
			pGrp->m_svrTrade.m_nPort = pGrp->m_vpTradeSvrs.at(0)->m_nPort;
		}
		nIndex = 0;
		if (pGrp->m_vpTradeSvrs.size() > 1)
		{
			if (c_nUserID > 0)
				nIndex = (c_nUserID) % pGrp->m_vpTradeSvrs.size();
			pGrp->m_svrTrade.m_strIP = pGrp->m_vpTradeSvrs.at(nIndex)->m_strIP;
			pGrp->m_svrTrade.m_nPort = pGrp->m_vpTradeSvrs.at(nIndex)->m_nPort;
		}
		return true;
	}	
public:	
	std::vector<SSvrGrp *> m_vpGrp;
	SSvrGrp * m_pActiveGrp;
	SSvr	* m_pActiveSvr;	
};

extern CSvr gSvr;

#endif
