#include "StdAfx.h"
#include "AppSetting.h"
#include <atlbase.h>
#include "tinyxml.h"
#include "Common/CommonFunc.h"
#include "Common/GlobalMacro.h"
#include "CommonData.h"
#include "Common/RegistryUtil.h"
#include "Common/StringUtil.h"

CAppSetting CAppSetting::m_Instance;

CAppSetting& CAppSetting::GetInstance( void )
{
	return m_Instance;
}

CAppSetting::CAppSetting(void)
{
}

CAppSetting::~CAppSetting(void)
{
}

void CAppSetting::SetAutoStartup( BOOL bAutoRun )
{
	CString    strAutoRunPath;   
	GetModuleFileName(NULL,strAutoRunPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
	strAutoRunPath.ReleaseBuffer();   

	if (bAutoRun)
	{
		SetSysRegKeyValue(REGKEY_AUTOSTARTUP,REGKEY_NAME_APP_NAME,strAutoRunPath);
	}
	else
	{
		SetSysRegKeyValue(REGKEY_AUTOSTARTUP,REGKEY_NAME_APP_NAME,_T(""));
	}

}

BOOL CAppSetting::IsAutoStartup( void )
{
	CString    strAppPath;   
	GetModuleFileName(NULL,strAppPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
	strAppPath.ReleaseBuffer();   

	CString strAutoRunPath = QuerySysRegKeyValueToString(REGKEY_AUTOSTARTUP,REGKEY_NAME_APP_NAME);

	if (strAutoRunPath == strAppPath)
	{
		return TRUE;
	}

	return FALSE;	
}

DWORD CAppSetting::GetFixedServer( CServer& svr )
{
	CString strAppSettingFile(GetAppSettingFile());

	if (!CheckFileExist(strAppSettingFile))
	{
		//文件不存在
		g_Log.LOG_WARNING(L"%s if not exist.",strAppSettingFile.GetBuffer(0));
		return RETVAL_ERROR;
	}

	TiXmlDocument xmlDocument(ToCStringA(strAppSettingFile));

	if (!xmlDocument.LoadFile())
	{
		//加载xml文件失败
		g_Log.LOG_WARNING(L"load %s failed.",strAppSettingFile.GetBuffer(0));
		return RETVAL_ERROR;
	}

	TiXmlHandle docHandle(&xmlDocument);

	TiXmlNode* pSvrIpNode = docHandle.FirstChildElement("root").FirstChildElement("server").FirstChildElement("ip").Node();
	if (NULL != pSvrIpNode)
	{
		svr.m_strIPAddress = ToCStringW(pSvrIpNode->ToElement()->GetText());
	}
	else
	{
		return RETVAL_ERROR;
	}

	TiXmlNode* pSvrProtNode = docHandle.FirstChildElement("root").FirstChildElement("server").FirstChildElement("port").Node();
	if (NULL != pSvrProtNode)
	{
		svr.m_dwPort =(DWORD)atol(pSvrProtNode->ToElement()->GetText());
	}
	else
	{
		return RETVAL_ERROR;
	}

	return RETVAL_SUCCESS;
}



DWORD CAppSetting::GetServerGroup( std::vector<CServerGroup>& vtServerGroups )
{
	CStringA strAppSettingFile(GetSvrlistFile());

	if (!CheckFileExist(GetSvrlistFile()))
	{
		//svrlist.xml文件不存在
		g_Log.LOG_WARNING(L"svrlist.xml if not exist.");
		return RETVAL_ERROR;
	}

	TiXmlDocument xmlDoc(strAppSettingFile);

	if (!xmlDoc.LoadFile())
	{
		//加载xml文件失败
		g_Log.LOG_WARNING(L"load svrlist.xml failed.");
		return RETVAL_ERROR;
	}

	TiXmlHandle docHandle(&xmlDoc);

	TiXmlNode* pSvrNode = docHandle.FirstChildElement("SVRS").FirstChildElement("GRP").Node();

	if (NULL != pSvrNode)
	{
		TiXmlElement* pGroupElement = pSvrNode->ToElement();
		while(pGroupElement)
		{
			CServerGroup mServerGroup;//一个服务器组

			TiXmlAttribute* pGrpNameAttr =pGroupElement->FirstAttribute();//获取服务器组名
			if (NULL != pGrpNameAttr)
			{
				mServerGroup.m_strGroupName = pGrpNameAttr->ValueStr().c_str();
			}

			//一个用户认证服务器节点
			TiXmlElement* pAuthSvrElement = pGroupElement->FirstChildElement("USER");
			if (NULL != pAuthSvrElement)
			{
				TiXmlAttribute* pAttr =pAuthSvrElement->FirstAttribute();//获取服务器IP
				while (pAttr)
				{
					CStringA   strAttr = pAttr->Name();
					if("IP" == strAttr)
					{
						mServerGroup.m_AuthSvr.m_strIPAddress = pAttr->ValueStr().c_str();
					}
					else if("PORT" == strAttr)
					{
						mServerGroup.m_AuthSvr.m_dwPort = atol(pAttr->ValueStr().c_str());
					}
					pAttr = pAttr->Next();
				}
			}

			//多个行情服务器节点
			TiXmlElement* pPriceSvrElement = pGroupElement->FirstChildElement("SVR");
			while(pPriceSvrElement)
			{
				CServer mPriceSvr;

				TiXmlAttribute* pAttr =pAuthSvrElement->FirstAttribute();//获取服务器IP
				while (pAttr)
				{
					std::string  strAttr = pAttr->Name();
					if ("NAME" == strAttr)
					{
						mPriceSvr.m_strServerName = pAttr->ValueStr().c_str();
						if (mPriceSvr.m_strServerName.IsEmpty())
						{
							pPriceSvrElement = pPriceSvrElement->NextSiblingElement();
							continue;
						}
					}
					else if("IP" == strAttr)
					{
						mPriceSvr.m_strIPAddress = pAttr->ValueStr().c_str();
						if (mPriceSvr.m_strIPAddress.IsEmpty())
						{
							pPriceSvrElement = pPriceSvrElement->NextSiblingElement();
							continue;
						}
					}
					else if("PORT" == strAttr)
					{
						mPriceSvr.m_dwPort = atol(pAttr->ValueStr().c_str());
					}
					pAttr = pAttr->Next();
				}

				//IP地址不能为空
				mPriceSvr.m_strIPAddress.Trim();
				if (!mPriceSvr.m_strIPAddress.IsEmpty())
				{
					mServerGroup.m_vtPriceSvrs.push_back(mPriceSvr);
				}				
				pPriceSvrElement = pPriceSvrElement->NextSiblingElement();
			}

			mServerGroup.m_AuthSvr.m_strIPAddress.Trim();
			if (!mServerGroup.m_AuthSvr.m_strIPAddress.IsEmpty())
			{
				vtServerGroups.push_back(mServerGroup);
			}

			pGroupElement = pGroupElement->NextSiblingElement();
		}
	}

	return RETVAL_SUCCESS;
}

void CAppSetting::SetSaveAccount( BOOL bSave )
{
	SetSysRegKeyValue(REGKEY_OTCSYS,REGNAME_SAVEACCOUNT,bSave);
}

BOOL CAppSetting::IsSaveAccount( void )
{
	return (BOOL)QuerySysRegKeyValueToDWORD(REGKEY_OTCSYS,REGNAME_SAVEACCOUNT);
}

void CAppSetting::SetSavePassword( BOOL bSave )
{
	SetSysRegKeyValue(REGKEY_OTCSYS,REGNAME_SAVEPASSWORD,bSave);
}

BOOL CAppSetting::IsSavePassword( void )
{
	return (BOOL)QuerySysRegKeyValueToDWORD(REGKEY_OTCSYS,REGNAME_SAVEPASSWORD);
}



CString CAppSetting::GetAccount( void )
{
	return (CString)QuerySysRegKeyValueToString(REGKEY_OTCSYS,REGNAME_ACCOUNT);
}

void CAppSetting::SetAccount( CString strAccount )
{
	SetSysRegKeyValue(REGKEY_OTCSYS,REGNAME_ACCOUNT,strAccount);
}

CString CAppSetting::GetPassword( void )
{
	return CString(_T(""));
}

void CAppSetting::SetPassword( CString strPwd )
{

}






