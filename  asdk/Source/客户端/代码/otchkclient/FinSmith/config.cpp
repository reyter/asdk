
#include "stdafx.h"
#include "config.h"

CConfig gCfg;

CConfig::CConfig()
{
	//m_bCanReg = false;
	m_bCanReg = true;
	m_strUser = "";
	memset(m_acPatch,0,sizeof(m_acPatch));
	m_nFixedPort = 0;
	m_strFixedSvrGrp = "";
	m_strTeachingApp = "";
	m_usUpdateType = 0;
	strcpy(m_acDesKey,DES_KEY);
	memset(m_acDmkPath,0,sizeof(m_acDmkPath));
}

CConfig::~CConfig()
{
}

void* CConfig::OnNode(std::string NodeName, void *lParam)
{
	return NULL;
}

void CConfig::OnText(std::string NodeName, std::string NodeText, void *lParam)
{
	if (NodeName == "PRODUCT")
	{
		m_nProduct = atoi(NodeText.c_str());
	}
	else
	if (NodeName == "ROLE")
	{
		m_nRole = atoi(NodeText.c_str());
	}
	else
	if (NodeName == "IP")
	{
		m_strDeployIP = NodeText;
	}
	else
	if (NodeName == "IPBAK")
	{
		m_strDeployIPBak = NodeText;
	}
	else
	if (NodeName == "PORT")
	{
		m_nDeployPort = atoi(NodeText.c_str());
	}
	else
	if (NodeName == "PATCH")
	{
		strncpy(m_acPatch,NodeText.c_str(),10);
	}
	else
	if (NodeName == "TEACHING")
	{
		m_strTeachingApp = toUnicodeString((char *)NodeText.c_str(),NodeText.length());
	}
	else
	if (NodeName == "DMKPATH")
	{
		strncpy(m_acDmkPath,NodeText.c_str(),32);
	}
}

void CConfig::OnAttr(std::string NodeName, std::string AttrName, std::string AttrText, void *lParam)
{

}

bool CConfig::Init()
{
	///m_pDllManager->LoadDll();
	return true;
}

int CConfig::GetDeployPort()
{
	if (m_nFixedPort > 0)
		return m_nFixedPort;
	return m_nDeployPort;
}

int CConfig::GetQuotePort()
{
	if (m_nFixedPort > 0)
		return m_nFixedPort;
	return m_nQuotePort;
}
	
int CConfig::GetUserPort()
{
	if (m_nFixedPort > 0)
		return m_nFixedPort;
	return m_nUserPort;
}

int CConfig::GetTradePort()
{
	if (m_nFixedPort > 0 && m_nTradePort == 0)
		return m_nFixedPort;
	return m_nTradePort;
}

int CConfig::GetTeacherPort()
{
	if (m_nTeacherPort > 0)
		return m_nTeacherPort;
	if (m_nFixedPort > 0)
		return m_nFixedPort;	
	return m_nQuotePort;
}
