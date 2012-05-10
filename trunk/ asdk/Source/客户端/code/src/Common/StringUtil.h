#include <string>
#include <Windows.h>
#include <boost/checked_delete.hpp>
#include <atlstr.h>

//��std::stringתΪstd::wstring 
std::wstring& StdString2StdWString(std::wstring& strDest, const std::string& strSrc);

//��std::wstringתΪstd::string 
std::string& StdWString2StdString(std::string& strDest, const std::wstring& strSrc);

//��std::stringתΪstd::wstring 
std::wstring ToStdWString(const std::string& strSrc);

//��std::wstringתΪstd::string 
std::string ToStdString(const std::wstring& strSrc);

//��CStringAתΪCStringW
CStringW ToCStringW(const CStringA& strSrc);

//��CStringWתΪCStringA
CStringA ToCStringA(const CStringW& strSrc);


int toUnicode(char * c_pSrc,int c_nSrcLen,char * c_pDest,int c_nMaxLen);

CString toUnicodeString(char * c_pSrc,int c_nSrcLen);

int toUtf8(char * c_pSrc,char * c_pDes,int c_nDataLen);

int unicodeToAscii(CString c_strUnicode,char * c_pRet,int c_nMaxLen);

int  unicodeToAscii(WCHAR * c_wcUnicode,int c_nUnicodeLen,char * c_pRet,int c_nMaxLen);

int untf8ToAscii(char * c_pSrc,int c_nSrcLen,char * c_pDes,int c_nDataLen);

CString untf8ToString(char * c_pSrc,int c_nSrcLen);

