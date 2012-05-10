
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
	if (NodeName == "用户数据库服务器IP")
		m_strUDBIP = NodeText;
	else if (NodeName == "用户数据库名")
		m_strUDBName = NodeText;
	else if (NodeName == "用户数据库用户名")
		m_strUDBUserName = NodeText;
	else if (NodeName == "用户数据库密码")
		m_strUDBPassword = NodeText;

	else if (NodeName == "资讯数据库服务器IP")
		m_strIDBIP = NodeText;
	else if (NodeName == "资讯数据库名")
		m_strIDBName = NodeText;
	else if (NodeName == "资讯数据库用户名")
		m_strIDBUserName = NodeText;
	else if (NodeName == "资讯数据库密码")
		m_strIDBPassword = NodeText;

	else if (NodeName == "登陆")
		m_strLoginUrl = NodeText;
	else if (NodeName == "登出")
		m_strLogoutUrl = NodeText;
	else if (NodeName == "好股登陆")
		m_strHaoguLoginUrl = NodeText;
	else if (NodeName == "好股登出")
		m_strHaoguLogoutUrl = NodeText;

	else if (NodeName == "登陆成功")
		m_strLoginSuccessUrl = NodeText;
	else if (NodeName == "保持连接")
		m_strKeepLiveUrl = NodeText;
	else if (NodeName == "个性化设置")
		m_strSetUrl = NodeText;
	else if (NodeName == "服务")
		m_strServiceUrl = NodeText;
	else if (NodeName == "移动")
		m_strMobileUrl = NodeText;
	else if (NodeName == "个股")
		m_strStockUrl = NodeText;
	else if (NodeName == "新闻")
		m_strNewsUrl = NodeText;
	else if (NodeName == "主页")
		m_strHomeUrl = NodeText;
	else if (NodeName == "好股主页")
		m_strHaoguHomeUrl = NodeText;
	else if (NodeName == "验证")
		m_strVerifyUrl = NodeText;
	else if (NodeName == "验证成功")
		m_strVerifySuccessUrl = NodeText;
	else if (NodeName == "重置密码")
		m_strResetPasswordUrl = NodeText;
	else if (NodeName == "产品")
		m_strHelpUrl = NodeText;
	else if (NodeName == "评级图片")
		m_strPjPicUrl = NodeText;
	else if (NodeName == "盈利预测图片")
		m_strYlycPicUrl = NodeText;
	else if (NodeName == "好股排行榜")
		m_strHGSort = NodeText;
	else if (NodeName == "好股WEBSERVICE")
		m_strHGWebservice = NodeText;	
	else if (NodeName == "行情服务器IP")
	{
		if (pNode)
			pNode->m_strQuoteServerIP = NodeText;
		else
			m_strQuoteServerIP = NodeText;
	}
	else if (NodeName == "行情服务器IPBAK")
	{
		if (pNode)
			pNode->m_strQuoteServerIPBAK = NodeText;
		else
			m_strQuoteServerIPBAK = NodeText;
	}
	else if (NodeName == "行情服务器PORT")
	{
		if (pNode)
			pNode->m_nQuoteServerPort = atoi(NodeText.c_str());
		else
			m_nQuoteServerPort = atoi(NodeText.c_str());
	}
	else if (NodeName == "行情服务器PORTBAK")
	{
		if (pNode)
			pNode->m_nQuoteServerPortBAK = atoi(NodeText.c_str());
		else
			m_nQuoteServerPortBAK = atoi(NodeText.c_str());
	}
	else if (NodeName == "资讯服务器IP")
	{
		if (pNode)
			pNode->m_strNewsServerIP = NodeText;
		else
			m_strNewsServerIP = NodeText;
	}
	else if (NodeName == "资讯服务器PORT")
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


