
#ifndef __QUOTE_FARM_CONFIG_H__
#define __QUOTE_FARM_CONFIG_H__

#include "stdafx.h"
#include "..\\public\\xml\\xmlparser.h"
#include "../public/ProxyOption.h"
#include <string>

//class CDllManager;
//class CBtnArray;
class CConfig : public TiXmlParser
{
public:
	CConfig();
	~CConfig();

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
	int GetDeployPort();
	int	GetQuotePort();
	int GetUserPort();
	int GetTradePort();
	int GetTeacherPort();

	void SetDeployPort(int c_nPort){m_nDeployPort = c_nPort;};
	void SetQuotePort(int c_nPort){m_nQuotePort = c_nPort;};
	void SetUserPort(int c_nPort){m_nUserPort = c_nPort;};
	void SetTradePort(int c_nPort){m_nTradePort = c_nPort;};
	void SetTeacherPort(int c_nPort){m_nTeacherPort = c_nPort;};

private:
	int m_nDeployPort;
	int  m_nQuotePort;	
	int	m_nUserPort;
	int m_nTradePort;
	int m_nTeacherPort;
public:		
	bool m_bCanReg;
	int m_nProduct;
	int m_nRole;
	std::string m_strUser;//用户登陆名称
	std::string m_strPass;
	std::string m_strPassMD5;
	std::string m_strMsg;//信息
	std::string m_strDeployIP;
	std::string m_strDeployIPBak;
	

	CString m_strUserIP;
	CString m_strQuoteIP;	
	CString m_strTradeIP;	
	CString m_strTeacherIP;	

	char m_acPreLoginTime[30];
	char m_acPreServIP[20];
	int  m_nPrePort;

	int m_nFixedPort;
	CString m_strFixedSvrGrp;//默认主机，记录主机的所在组

	char m_acVer[10];
	char m_acPatch[10];
	char m_acDmkPath[256];
	unsigned short m_usUpdateType;
	unsigned short m_usForce;
	char m_acVerUrl[100];
	char m_acPatchUrl[100];
	char m_acUpdateInfo[1024];	

	CString m_strMac;
	CString m_strTeachingApp;

	CProxyOption m_proxyOption;
	CString m_strNewsUrl;
	CString m_strPDFUrl;

	char m_acDesKey[16];
};

extern CConfig gCfg;
#endif
