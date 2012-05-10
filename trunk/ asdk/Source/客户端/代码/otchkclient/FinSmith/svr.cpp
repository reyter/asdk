
#include "stdafx.h"
#include "svr.h"

CSvr gSvr;

CSvr::CSvr()
{	
	m_pActiveGrp = NULL;
	m_pActiveSvr = NULL;
}

CSvr::~CSvr()
{
}
void CSvr::OnNode(TiXmlElement *pElm, TiXmlParser::NODEWAY way)//, void *lParam)
{
	if (way != TiXmlParser::ENTER)
		return;

	std::string NodeName = pElm->ValueStr();
	if (NodeName == "GRP")
	{
		SSvrGrp * pGrp = new SSvrGrp();
		m_vpGrp.push_back(pGrp);
		m_pActiveGrp = pGrp;
		m_pActiveSvr = NULL;
	}
	else
	if (NodeName == "SVR")
	{
		if (m_pActiveGrp == NULL)
			return;
		SSvr * pSvr = new SSvr();
		m_pActiveGrp->m_vpSvrs.push_back(pSvr);
		m_pActiveSvr = pSvr;
	}
	else
	if (NodeName == "USER")
	{
		if (m_pActiveGrp == NULL)
			return;
		m_pActiveSvr = &(m_pActiveGrp->m_svrUserInfo);
	}
	else
	if (NodeName == "TEACHER")
	{
		if (m_pActiveGrp == NULL)
			return;
		m_pActiveSvr = &(m_pActiveGrp->m_svrTeaching);
	}
	else
	if (NodeName == "TRADE")
	{
		if (m_pActiveGrp == NULL)
			return;		

		SSvr * pSvr = new SSvr();
		m_pActiveGrp->m_vpTradeSvrs.push_back(pSvr);
		m_pActiveSvr = pSvr;
	}

}
void* CSvr::OnNode(std::string NodeName, void *lParam)
{
	return NULL;
}

void CSvr::OnText(std::string NodeName, std::string NodeText, void *lParam)
{
	std::string homeUrl;
	std::string helpUrl;

	homeUrl = "HOMEURL";
	helpUrl = "HELPURL";

	if (gCfg.m_nProduct > 1)//特殊版本使用自定义的主页和帮助页面
	{
		char acPd[10];
		sprintf(acPd,"_%d",gCfg.m_nProduct);
		homeUrl += acPd;
		helpUrl += acPd;
	}

	if (NodeName == "NEWSURL")
	{
		gpData->m_strNewsUrl = NodeText.c_str();
#ifdef CCTV_TV
		gpData->m_strNewsUrl.Replace(_T("newscontent.jsp"),_T("newscontent_1.jsp"));
#endif
	}
	else
	if (NodeName == "PDFURL")
	{
		gpData->m_strPDFUrl = NodeText.c_str();
	}
	else
	if (NodeName == "F10URL")
	{
		gpData->m_strF10Url = toUnicodeString((char *)NodeText.c_str(),NodeText.length());
	}
	else
	if (NodeName == "HOMEURL")
	{
		gpData->m_strHomeUrl = toUnicodeString((char *)NodeText.c_str(),NodeText.length());
	}
	else
	if (NodeName == "HELPURL")
	{
		gpData->m_strHelpUrl = toUnicodeString((char *)NodeText.c_str(),NodeText.length());
	}
	else
	if (NodeName == homeUrl)
	{
		gpData->m_strHomeUrl = toUnicodeString((char *)NodeText.c_str(),NodeText.length());
	}
	else
	if (NodeName == helpUrl)
	{
		gpData->m_strHelpUrl = toUnicodeString((char *)NodeText.c_str(),NodeText.length());
	}
	else
	if (NodeName == "SZURL")
	{
		gpData->m_strSZUrl = toUnicodeString((char *)NodeText.c_str(),NodeText.length());
	}
	else
	if (NodeName == "REGURL")
	{
		gpData->m_strRegUrl = toUnicodeString((char *)NodeText.c_str(),NodeText.length());
	}
	else
	if (NodeName == "RESETPASSURL")
	{
		gpData->m_strResetPassUrl = toUnicodeString((char *)NodeText.c_str(),NodeText.length());
	}

}

void CSvr::OnAttr(std::string NodeName, std::string AttrName, std::string AttrText, void *lParam)
{
	if (NodeName == "GRP")
	{
		if (m_pActiveGrp == NULL)
			return;
		if (AttrName == "NAME")
			m_pActiveGrp->m_strName = toUnicodeString((char *)AttrText.c_str(),AttrText.length());
	}
	else
	if (NodeName == "SVR" || NodeName == "USER" || NodeName == "TEACHER" || NodeName == "TRADE")
	{
		if (m_pActiveGrp == NULL)
			return;
		if (m_pActiveSvr == NULL)
		{
			if (NodeName == "SVR")
			{
				SSvr * pSvr = new SSvr();
				m_pActiveGrp->m_vpSvrs.push_back(pSvr);
				m_pActiveSvr = pSvr;
			}
			else
			if (NodeName == "USER")
				m_pActiveSvr = &m_pActiveGrp->m_svrUserInfo;
			else
			if (NodeName == "TEACHER")
				m_pActiveSvr = &m_pActiveGrp->m_svrTeaching;
			else
			if (NodeName == "TRADE")
			{				
				SSvr * pSvr = new SSvr();
				m_pActiveGrp->m_vpTradeSvrs.push_back(pSvr);
				m_pActiveSvr = pSvr;
			}
			else
				return;
		}			
		if (AttrName == "NAME")
			m_pActiveSvr->m_strName = toUnicodeString((char *)AttrText.c_str(),AttrText.length());
		else
		if (AttrName == "IP")
			m_pActiveSvr->m_strIP = AttrText.c_str();
		else
		if (AttrName == "PORT")
			m_pActiveSvr->m_nPort = atoi(AttrText.c_str());
	}
}

bool CSvr::Init()
{
	return true;
}