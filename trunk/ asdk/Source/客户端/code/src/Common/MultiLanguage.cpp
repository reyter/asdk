#include "stdafx.h"
#include "MultiLanguage.h"
#include "Log.h"
#include "tinyxml/tinyxml.h"
#include "StringUtil.h"
#include "CommonFunc.h"
#include "../CommonData.h"

CMultiLanguage CMultiLanguage::m_Instance;	

CMultiLanguage::CMultiLanguage(void)
:m_mapIDS2String()
{
}

CMultiLanguage::~CMultiLanguage(void)
{
}


bool CMultiLanguage::LoadResources(void)
{
	CString strLangFile = GetCurrentLanguageResource();

	//判断指定的语言资源是否存在
	if (!CheckFileExist(strLangFile))
	{
		g_Log.LOG_WARNING(L"Not find language resources:%s.",strLangFile);
		return false;
	}

	//加载XML文件
	TiXmlDocument Document(ToCStringA(strLangFile));
	if (!Document.LoadFile())
	{
		g_Log.LOG_WARNING(L"Load language resources failed.");
		return false;
	}

	TiXmlElement *pRootElement = Document.RootElement();
	if (NULL == pRootElement)
	{
		g_Log.LOG_WARNING(L"Load language resources failed.");
		return false;
	}

	TiXmlElement *pFirstElement = pRootElement->FirstChildElement();
	while(pFirstElement)
	{
		TiXmlAttribute* pAttrIDS = NULL;
		TiXmlAttribute* pAttrValue = NULL;

		pAttrIDS = pFirstElement->FirstAttribute();
		if (NULL == pAttrIDS)
		{
			continue;
		}

		pAttrValue = pAttrIDS->Next();
		if (NULL == pAttrValue)
		{
			continue;
		}

		std::wstring strIDS = ToStdWString(pAttrIDS->ValueStr());
		std::wstring strValue =ToStdWString(pAttrValue->ValueStr());
		m_mapIDS2String.insert(std::make_pair<std::wstring,std::wstring>(strIDS,strValue));

		pFirstElement = pFirstElement->NextSiblingElement();
	}

	return true;
}


std::wstring CMultiLanguage::LoadWString( std::wstring strIDS )
{
	CIDS2StringMap::iterator itFind = m_mapIDS2String.find(strIDS);

	if (itFind == m_mapIDS2String.end())
	{
		g_Log.LOG_WARNING(L"Not find:%s",strIDS.c_str());
		static std::wstring strNotFind = L"Not Find";
		return strNotFind;
	}

	return itFind->second;
}

CMultiLanguage& CMultiLanguage::GetInstance( void )
{
	return m_Instance;
}
