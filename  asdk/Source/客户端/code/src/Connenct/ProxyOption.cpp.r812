#include "StdAfx.h"
#include "ProxyOption.h"

CProxyOption::CProxyOption(void)
: m_nProxyType(0)
, m_bIsValid(false)
, m_strProxyIP(_T(""))
, m_nProxyPort(0)
, m_strProxyUser(_T(""))
, m_strProxyPass(_T(""))
{
}

CProxyOption::~CProxyOption(void)
{
}

int CProxyOption::Init(CString c_strIniFile)
{
	int nRet = GetPrivateProfileInt(_T("PROXY"),_T("VALID"),0,c_strIniFile);
	if (nRet > 0)
	{
		m_bIsValid = true;
	}
	else
	{
		m_bIsValid = false;
	}
		
	nRet = GetPrivateProfileInt(_T("PROXY"),_T("HTTPHEAD"),0,c_strIniFile);
	if (nRet > 0)
	{
		m_bUseHttpHead = true;
	}
	else
	{
		m_bUseHttpHead = false;
	}

	m_nProxyType = GetPrivateProfileInt(_T("PROXY"),_T("TYPE"),0,c_strIniFile);
	
	m_nProxyPort = GetPrivateProfileInt(_T("PROXY"),_T("PORT"),0,c_strIniFile);
	
	WCHAR wcRet[128];
	GetPrivateProfileString(_T("PROXY"),_T("IP"),_T(""),wcRet,128,c_strIniFile);
	
	m_strProxyIP = wcRet;
	
	GetPrivateProfileString(_T("PROXY"),_T("USER"),_T(""),wcRet,128,c_strIniFile);
	m_strProxyUser = wcRet;
	
	GetPrivateProfileString(_T("PROXY"),_T("PASS"),_T(""),wcRet,128,c_strIniFile);
	m_strProxyPass = wcRet;

	return 0;
}

int CProxyOption::Save(CString c_strIniFile)
{
	CString strValue;

	if (m_bIsValid)
	{
		WritePrivateProfileString(_T("PROXY"),_T("VALID"),_T("1"),c_strIniFile);
	}
	else
	{
		WritePrivateProfileString(_T("PROXY"),_T("VALID"),_T("0"),c_strIniFile);
	}

	if (m_bUseHttpHead)
	{
		WritePrivateProfileString(_T("PROXY"),_T("HTTPHEAD"),_T("1"),c_strIniFile);
	}
	else
	{
		WritePrivateProfileString(_T("PROXY"),_T("HTTPHEAD"),_T("0"),c_strIniFile);
	}

	strValue.Format(_T("%d"),m_nProxyType);
	WritePrivateProfileString(_T("PROXY"),_T("TYPE"),strValue,c_strIniFile);

	WritePrivateProfileString(_T("PROXY"),_T("IP"),m_strProxyIP,c_strIniFile);
	
	strValue.Format(_T("%d"),m_nProxyPort);
	WritePrivateProfileString(_T("PROXY"),_T("PORT"),strValue,c_strIniFile);
	
	WritePrivateProfileString(_T("PROXY"),_T("USER"),m_strProxyUser,c_strIniFile);
	
	WritePrivateProfileString(_T("PROXY"),_T("PASS"),m_strProxyPass,c_strIniFile);

	return 0;
}
