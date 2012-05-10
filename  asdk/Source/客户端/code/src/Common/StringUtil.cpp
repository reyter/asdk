#include "stdafx.h"
#include "StringUtil.h"
#include "GlobalMacro.h"


std::wstring& StdString2StdWString( std::wstring& strDest, const std::string& strSrc )
{
	strDest.clear();

	if (strSrc.empty())
	{
		return strDest;
	}

	int nLength = MultiByteToWideChar( CP_ACP, 0, strSrc.c_str(), -1, NULL, NULL );
	wchar_t* pszDest = new wchar_t[nLength];
	if (NULL != pszDest)
	{
		memset(pszDest,0,nLength);
		MultiByteToWideChar( CP_ACP, 0, strSrc.c_str(), -1, pszDest, nLength);
		strDest=pszDest;
		boost::checked_array_delete(pszDest);
		__DELETE_OBJECT(pszDest);
	}	
	return strDest;
}

std::string& StdWString2StdString( std::string& strDest, const std::wstring& strSrc )
{
	strDest.clear();

	if (strSrc.empty())
	{
		return strDest;
	}

	int nLength = WideCharToMultiByte(CP_OEMCP,NULL,strSrc.c_str(),-1,NULL,0,NULL,FALSE);
	char* pszDest = new char[nLength];
	if (NULL != pszDest)
	{
		memset(pszDest,0,nLength);
		WideCharToMultiByte(CP_OEMCP,NULL,strSrc.c_str(),-1,pszDest,nLength,NULL,FALSE);
		strDest=pszDest;
		__DELETE_OBJECT(pszDest);
	}
	return strDest;
}

std::wstring ToStdWString( const std::string& strSrc )
{
	std::wstring strTemp;
	return StdString2StdWString(strTemp,strSrc);
}


std::string ToStdString( const std::wstring& strSrc )
{
	std::string strTemp;
	return StdWString2StdString(strTemp,strSrc);
}

CStringW ToCStringW( const CStringA& strSrc )
{
	CStringW strTemp(strSrc);
	return strTemp;
}

CStringA ToCStringA( const CStringW& strSrc )
{
	CStringA strTemp(strSrc);
	return strTemp;
}


int toUnicode(char * c_pSrc,int c_nSrcLen,char * c_pDest,int c_nMaxLen)
{
	if (c_nSrcLen * 2 >= c_nMaxLen)
		return -1;
	return MultiByteToWideChar(CP_ACP,MB_ERR_INVALID_CHARS,c_pSrc,c_nSrcLen,(LPWSTR)(c_pDest),c_nSrcLen * 2);
}

CString toUnicodeString(char * c_pSrc,int c_nSrcLen)
{

	WCHAR *pTmp = new WCHAR[c_nSrcLen + 1];
	memset(pTmp,0,c_nSrcLen * 2 + 1);
	MultiByteToWideChar(CP_ACP,MB_ERR_INVALID_CHARS,c_pSrc,c_nSrcLen,pTmp,c_nSrcLen);
	pTmp[c_nSrcLen] = 0;
	CString strRet(_T(""));
	strRet = pTmp;
	delete [] pTmp;	
	return strRet;
}

int toUtf8(char * c_pSrc,char * c_pDes,int c_nDataLen)
{
	memset(c_pDes,0,c_nDataLen * 3);
	//ANSI to UNICODE
	char * pTmp = new char[c_nDataLen * 2 + 2];
	memset(pTmp,0,c_nDataLen * 2 + 2);
	MultiByteToWideChar(CP_ACP,MB_ERR_INVALID_CHARS,c_pSrc,	strlen(c_pSrc),(LPWSTR)(pTmp),c_nDataLen);

	//UNICODE to UTF8
	int u8Len = ::WideCharToMultiByte(CP_UTF8, NULL, (LPWSTR)(pTmp), wcslen((LPWSTR)(pTmp)), NULL, 0, NULL, NULL);
	::WideCharToMultiByte(CP_UTF8, NULL, (LPWSTR)(pTmp), wcslen((LPWSTR)(pTmp)), c_pDes, u8Len, NULL, NULL);
	//最后加上'\0'
	c_pDes[u8Len] = '\0';
	delete [] pTmp;
	return strlen(c_pDes);
}

int unicodeToAscii(CString c_strUnicode,char * c_pRet,int c_nMaxLen)
{
	int nLen = WideCharToMultiByte(CP_ACP,0,c_strUnicode.GetBuffer(0),-1,0,0,0,0);
	if (nLen > c_nMaxLen)
		return 0;
	int nRet = WideCharToMultiByte(CP_ACP,0,c_strUnicode,c_strUnicode.GetLength(),c_pRet,c_strUnicode.GetLength()*2,0,0);
	c_pRet[nLen] = 0;
	if (nRet > 0)
		c_pRet[nRet] = 0;
	return nLen;
}

int unicodeToAscii(WCHAR * c_wcUnicode,int c_nUnicodeLen,char * c_pRet,int c_nMaxLen)
{
	int nLen = WideCharToMultiByte(CP_ACP,0,c_wcUnicode,c_nUnicodeLen,0,0,0,0);
	if (nLen > c_nMaxLen)
		return 0;
	int nRet = WideCharToMultiByte(CP_ACP,0,c_wcUnicode,c_nUnicodeLen,c_pRet,c_nUnicodeLen*2,0,0);
	c_pRet[nLen] = 0;
	if (nRet > 0)
		c_pRet[nRet] = 0;
	return nLen;
}

int untf8ToAscii(char * c_pSrc,int c_nSrcLen,char * c_pDes,int c_nDataLen)
{
	int nValidLen;
	nValidLen = strlen(c_pSrc);
	if (nValidLen > c_nSrcLen)
		nValidLen = c_nSrcLen;
	//先UTF8 to UNICODE
	int uncodeLen = MultiByteToWideChar(CP_UTF8, NULL, c_pSrc,nValidLen, NULL, 0);
	wchar_t* wszString = new wchar_t[uncodeLen + 1];
	::MultiByteToWideChar(CP_UTF8, NULL, c_pSrc, nValidLen, wszString, uncodeLen);
	//最后加上'\0'
	wszString[uncodeLen] = '\0';

	//UNICODE to ANSI
	WideCharToMultiByte(CP_ACP,0,wszString,-1,c_pDes,c_nDataLen,NULL,NULL);
	delete [] wszString;
	return nValidLen;	
}

CString untf8ToString(char * c_pSrc,int c_nSrcLen)
{
	int nValidLen;
	nValidLen = strlen(c_pSrc);
	if (nValidLen > c_nSrcLen)
		nValidLen = c_nSrcLen;
	//先UTF8 to UNICODE
	int uncodeLen = MultiByteToWideChar(CP_UTF8, NULL, c_pSrc,nValidLen, NULL, 0);
	wchar_t* wszString = new wchar_t[uncodeLen + 1];
	::MultiByteToWideChar(CP_UTF8, NULL, c_pSrc, nValidLen, wszString, uncodeLen);
	//最后加上'\0'
	wszString[uncodeLen] = '\0';
	return wszString;
}