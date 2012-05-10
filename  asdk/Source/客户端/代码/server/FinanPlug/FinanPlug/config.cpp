
#include "stdafx.h"
#include "config.h"

CConfig g_cfg;

CConfig::CConfig()
{
	strcpy(m_acDesKey,"investzs");
}

CConfig::~CConfig()
{
}
void* CConfig::OnNode(std::string NodeName, void *lParam)
{
	SSvrNode * pNode = NULL;
	if (NodeName == "SVR")
	{
		pNode = NULL;
		return pNode;
	}
	else
	if (NodeName == "SVRNODE")
	{
	}
	else
	if (NodeName == "UPGRADE")
	{
	}
	return NULL;
}

void CConfig::OnText(std::string NodeName, std::string NodeText, void *lParam)
{
	SSvrNode * pNode = (SSvrNode *)lParam;
	tagUpgradeInfo * pItem = (tagUpgradeInfo *)lParam;
	if (NodeName == "�û����ݿ������IP")
		m_strUDBIP = NodeText;
	else if (NodeName == "�û����ݿ���")
		m_strUDBName = NodeText;
	else if (NodeName == "�û����ݿ��û���")
		m_strUDBUserName = NodeText;
	else if (NodeName == "�û����ݿ�����")
		m_strUDBPassword = NodeText;

	else if (NodeName == "��Ѷ���ݿ������IP")
		m_strIDBIP = NodeText;
	else if (NodeName == "��Ѷ���ݿ���")
		m_strIDBName = NodeText;
	else if (NodeName == "��Ѷ���ݿ��û���")
		m_strIDBUserName = NodeText;
	else if (NodeName == "��Ѷ���ݿ�����")
		m_strIDBPassword = NodeText;

	else if (NodeName == "��½")
		m_strLoginUrl = NodeText;
	else if (NodeName == "�ǳ�")
		m_strLogoutUrl = NodeText;
	else if (NodeName == "�ùɵ�½")
		m_strHaoguLoginUrl = NodeText;
	else if (NodeName == "�ùɵǳ�")
		m_strHaoguLogoutUrl = NodeText;

	else if (NodeName == "��½�ɹ�")
		m_strLoginSuccessUrl = NodeText;
	else if (NodeName == "��������")
		m_strKeepLiveUrl = NodeText;
	else if (NodeName == "���Ի�����")
		m_strSetUrl = NodeText;
	else if (NodeName == "����")
		m_strServiceUrl = NodeText;
	else if (NodeName == "�ƶ�")
		m_strMobileUrl = NodeText;
	else if (NodeName == "����")
		m_strStockUrl = NodeText;
	else if (NodeName == "����")
		m_strNewsUrl = NodeText;
	else if (NodeName == "��ҳ")
		m_strHomeUrl = NodeText;
	else if (NodeName == "�ù���ҳ")
		m_strHaoguHomeUrl = NodeText;
	else if (NodeName == "��֤")
		m_strVerifyUrl = NodeText;
	else if (NodeName == "��֤�ɹ�")
		m_strVerifySuccessUrl = NodeText;
	else if (NodeName == "��������")
		m_strResetPasswordUrl = NodeText;
	else if (NodeName == "��Ʒ")
		m_strHelpUrl = NodeText;
	else if (NodeName == "����ͼƬ")
		m_strPjPicUrl = NodeText;
	else if (NodeName == "ӯ��Ԥ��ͼƬ")
		m_strYlycPicUrl = NodeText;
	else if (NodeName == "�ù����а�")
		m_strHGSort = NodeText;
	else if (NodeName == "�ù�WEBSERVICE")
		m_strHGWebservice = NodeText;	
	else if (NodeName == "���������IP")
	{
		if (pNode)
			pNode->m_strQuoteServerIP = NodeText;
		else
			m_strQuoteServerIP = NodeText;
	}
	else if (NodeName == "���������IPBAK")
	{
		if (pNode)
			pNode->m_strQuoteServerIPBAK = NodeText;
		else
			m_strQuoteServerIPBAK = NodeText;
	}
	else if (NodeName == "���������PORT")
	{
		if (pNode)
			pNode->m_nQuoteServerPort = atoi(NodeText.c_str());
		else
			m_nQuoteServerPort = atoi(NodeText.c_str());
	}
	else if (NodeName == "���������PORTBAK")
	{
		if (pNode)
			pNode->m_nQuoteServerPortBAK = atoi(NodeText.c_str());
		else
			m_nQuoteServerPortBAK = atoi(NodeText.c_str());
	}
	else if (NodeName == "��Ѷ������IP")
	{
		if (pNode)
			pNode->m_strNewsServerIP = NodeText;
		else
			m_strNewsServerIP = NodeText;
	}
	else if (NodeName == "��Ѷ������PORT")
	{
		if (pNode)
			pNode->m_nNewsServerPort = atoi(NodeText.c_str());
		else
			m_nNewsServerPort = atoi(NodeText.c_str());
	}
}

void CConfig::OnAttr(std::string NodeName, std::string AttrName, std::string AttrText, void *lParam)
{
}


