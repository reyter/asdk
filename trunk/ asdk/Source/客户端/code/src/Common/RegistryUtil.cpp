#include "stdafx.h"
#include "RegistryUtil.h"
#include "GlobalMacro.h"
#include <atlbase.h>

CString QuerySysRegKeyValueToString( CString strKeyName, CString strValueName,CString strDefValue /*= _T("")*/ )
{
	CRegKey	regKey;
	if (ERROR_SUCCESS == regKey.Open(HKEY_LOCAL_MACHINE,strKeyName,KEY_READ))
	{
		TCHAR szData[MAX_PATH] = {0};
		ULONG ulLen = 0;
		if (ERROR_SUCCESS ==  regKey.QueryStringValue(strValueName,szData,&ulLen))
		{
			return szData;
		}
	}
	regKey.Close();
	return strDefValue;
}

DWORD QuerySysRegKeyValueToDWORD( CString strKeyName, CString strValueName,DWORD dwDefValue /*= 0*/ )
{
	CRegKey	regKey;
	if (ERROR_SUCCESS == regKey.Open(HKEY_LOCAL_MACHINE,strKeyName,KEY_READ))
	{
		DWORD ulValue;
		if (ERROR_SUCCESS ==  regKey.QueryDWORDValue(strValueName,ulValue))
		{
			return (DWORD)ulValue;
		}
	}
	regKey.Close();
	return dwDefValue;
}

BOOL SetSysRegKeyValue( CString strKeyName, CString strValueName,CString strValue )
{
	CRegKey	regKey;
	if (ERROR_SUCCESS == regKey.Open(HKEY_LOCAL_MACHINE,strKeyName,KEY_WRITE))
	{
		if (ERROR_SUCCESS ==  regKey.SetStringValue(strValueName,strValue))
		{
			return RETVAL_SUCCESS;
		}
	}
	regKey.Close();
	return RETVAL_ERROR;
}

BOOL SetSysRegKeyValue( CString strKeyName, CString strValueName,DWORD dwDValue )
{
	CRegKey	regKey;
	if (ERROR_SUCCESS == regKey.Open(HKEY_LOCAL_MACHINE,strKeyName,KEY_WRITE))
	{
		if (ERROR_SUCCESS ==  regKey.SetDWORDValue(strValueName,dwDValue))
		{
			return RETVAL_SUCCESS;
		}
	}
	regKey.Close();
	return RETVAL_ERROR;
}

