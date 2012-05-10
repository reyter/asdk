//config.h
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <vector>
#include <map>
#include "../../public/commx/synch.h"
//#include "../../public/xml/xmlparser.h"
#include "plugxmlparser.h"
#include "FinanPlugDef.h"

struct SSvrNode
{
	std::string  m_strQuoteServerIP;
	std::string  m_strQuoteServerIPBAK;
	int	m_nQuoteServerPort;
	int	m_nQuoteServerPortBAK;
	std::string  m_strNewsServerIP;
	int m_nNewsServerPort;
};
class CConfig : public TiPlugXmlParser
{
public:
	CConfig();
	~CConfig();
public:	
	virtual void* OnNode(std::string NodeName, void *lParam);
	virtual void OnText(std::string NodeName, std::string NodeText, void *lParam);
	virtual void OnAttr(std::string NodeName, std::string AttrName, std::string AttrText, void *lParam);

	//理财管家用户数据库
	std::string  m_strUDBIP;
	std::string  m_strUDBName;
	std::string  m_strUDBUserName;
	std::string  m_strUDBPassword;
	//资讯数据库
	std::string  m_strIDBIP;
	std::string  m_strIDBName;
	std::string  m_strIDBUserName;
	std::string  m_strIDBPassword;

	std::string	 m_strLoginUrl;
	std::string	 m_strHaoguLoginUrl;
	std::string	 m_strLogoutUrl;
	std::string	 m_strHaoguLogoutUrl;

	std::string	 m_strLoginSuccessUrl;
	std::string	 m_strKeepLiveUrl;
	std::string	 m_strSetUrl;
	std::string	 m_strServiceUrl;
	std::string  m_strMobileUrl;
	std::string	 m_strStockUrl;
	std::string	 m_strNewsUrl;
	std::string	 m_strHomeUrl;
	std::string	 m_strHelpUrl;

	std::string m_strPjPicUrl;
	std::string m_strYlycPicUrl;
	std::string m_strHGWebservice;
	std::string m_strHGSort;

	std::string  m_strQuoteServerIP;
	std::string  m_strQuoteServerIPBAK;
	int	m_nQuoteServerPort;
	int	m_nQuoteServerPortBAK;
	std::string  m_strNewsServerIP;
	int m_nNewsServerPort;
		
	std::string m_strVerifyUrl;
	std::string m_strVerifySuccessUrl;
	std::string m_strHaoguHomeUrl;
	std::string m_strResetPasswordUrl;

	std::string m_strPath;

	char m_acDesKey[16];

	//版本信息
	std::vector<tagUpgradeInfo *> m_vpUpgradeInfo;
};

extern CConfig g_cfg;

#endif
