#include "stdafx.h"
#include "CommonFunc.h"
#include "RegistryUtil.h"
#include "..\CommonData.h"


CString GetAppPath( void )
{
	CString strCurPath(_T(""));
	GetModuleFileName(NULL, strCurPath.GetBuffer(MAX_PATH), MAX_PATH);	
	strCurPath.ReleaseBuffer();	
	strCurPath = strCurPath.Left(strCurPath.ReverseFind(_T('\\')));
	return strCurPath;
}

BOOL CheckFileExist( const wchar_t* pszFile )
{	
	return _waccess(pszFile, 0) == 0 ? true : false;
}

CString GetOSVersion( void )
{

	return _T("");
}

CString GetOSLocale( void )
{
	return _T("");
}


CString GetLanguageType( void )
{
	return QuerySysRegKeyValueToString(REGKEY_OTCSYS,REGNAME_LANGUAGE,_T("chinese"));
}

CString GetCurrentLanguageResource( void )
{
	CString strLangResource(_T(""));
	strLangResource.Format(_T("%s\\lang\\%s.xml"),GetAppPath(),GetLanguageType());
	return strLangResource;
}

CString GetAppSettingFile( void )
{
	CString strClientConfig(_T(""));
	strClientConfig.Format(_T("%s\\config\\AppSetting.xml"),GetAppPath());
	return strClientConfig;
}

CString GetProxyFile( void )
{
	CString strFile(_T(""));
	strFile.Format(_T("%s\\config\\proxy.ini"),GetAppPath());
	return strFile;
}

CString GetSvrlistFile( void )
{
	CString strClientConfig(_T(""));
	strClientConfig.Format(_T("%s\\svrlist.xml"),GetAppPath());
	return strClientConfig;
}


char * ExtractDirFromFullPath(char * path)
{
	char *p = path;
	char *tag = p;
	while (*p)
	{
		if ( (*p) == '\\' )
			tag = p;
		++p;
	}
	*tag = '\0';
	return path;
}




