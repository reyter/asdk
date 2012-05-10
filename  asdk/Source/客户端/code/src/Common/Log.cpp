#include "stdafx.h"
#include "Log.h"
#pragma   warning(disable:4996)


#define	MAXLOGFILESIZE  1024 << 10    // 日志文件大小限制1MB
#define	MAXLOGLEN          1024           // 单条日志长度

CLog g_Log;

void CLog::Write2File(const wchar_t* pszData, int nLevel )
{
	SYSTEMTIME sysCurrTime;
	GetLocalTime(&sysCurrTime);
	wchar_t szCurrTime[32] = {0};
	_snwprintf_s(szCurrTime,32, L"%d-%d-%d %d:%d:%d", sysCurrTime.wYear, sysCurrTime.wMonth,
		sysCurrTime.wDay, sysCurrTime.wHour, sysCurrTime.wMinute, sysCurrTime.wSecond);

	wchar_t szLevel[12] = {0};
	switch(nLevel)
	{
	case LEVEL_DEBUG:
		wcscpy_s(szLevel,sizeof(szLevel)/sizeof(wchar_t),L"DEBUG");
		break;
	case LEVEL_INFO:
		wcscpy_s(szLevel,sizeof(szLevel)/sizeof(wchar_t),L"INFO");
		break;
	case LEVEL_WARNING:
		wcscpy_s(szLevel,sizeof(szLevel)/sizeof(wchar_t),L"WARNING");
		break;
	case LEVEL_ERROR:
		wcscpy_s(szLevel,sizeof(szLevel)/sizeof(wchar_t),L"ERROR");
		break;
	default:
		wcscpy_s(szLevel,sizeof(szLevel)/sizeof(wchar_t),L"DEBUG");
		break;
	}

	wchar_t szLogBuf[MAXLOGLEN] = {0};
	_snwprintf_s(szLogBuf, MAXLOGLEN, L"%s[%u][%s]: %s\r\n", szCurrTime,GetCurrentThreadId(),szLevel, pszData);

	EnterCriticalSection(&m_csLock);

	FILE *pfLog =NULL;	
	if (_wfopen_s(&pfLog,m_strFileName.c_str(), L"a+b") == 0)
	{
		if(MAXLOGFILESIZE < _filelength(_fileno(pfLog)))
		{					
			fclose(pfLog);
			pfLog = NULL;
			wchar_t szBackLogName[64] = {0};
			_snwprintf_s(szBackLogName,64,L"log %d-%d-%d %d-%d-%d.back", sysCurrTime.wYear, sysCurrTime.wMonth,
				sysCurrTime.wDay, sysCurrTime.wHour, sysCurrTime.wMinute, sysCurrTime.wSecond);

			if (0 !=_wrename(m_strFileName.c_str(),szBackLogName))
			{
				LeaveCriticalSection(&m_csLock);
				return;
			}

			if(_wfopen_s(&pfLog,m_strFileName.c_str(), L"a+b") != 0)
			{
				LeaveCriticalSection(&m_csLock);
				return;
			}
		}	

		fwrite(szLogBuf,sizeof(wchar_t),wcslen(szLogBuf),pfLog);
		fclose(pfLog);
		pfLog = NULL;
	}

	LeaveCriticalSection(&m_csLock);
}

void CLog::LOG_DEBUG( const wchar_t* pszData, ... )
{
	wchar_t szBuffer[MAXLOGLEN]={0};
	va_list vlArgs;
	va_start(vlArgs,pszData);
	wvsprintf(szBuffer, pszData, vlArgs);
	va_end(vlArgs);
	Write2File(szBuffer, LEVEL_DEBUG);
}


void CLog::LOG_INFO( const wchar_t* pszData, ... )
{
	wchar_t szBuffer[MAXLOGLEN]={0};
	va_list vlArgs;
	va_start(vlArgs,pszData);
	wvsprintf(szBuffer, pszData, vlArgs);
	va_end(vlArgs);
	Write2File(szBuffer, LEVEL_INFO);
}

void CLog::LOG_WARNING( const wchar_t* pszData, ... )
{
	wchar_t szBuffer[MAXLOGLEN]={0};
	va_list vlArgs;
	va_start(vlArgs,pszData);
	wvsprintf(szBuffer, pszData, vlArgs);
	va_end(vlArgs);
	Write2File(szBuffer, LEVEL_WARNING);
}

void CLog::LOG_ERROR( const wchar_t* pszData, ... )
{
	wchar_t szBuffer[MAXLOGLEN]={0};
	va_list vlArgs;
	va_start(vlArgs,pszData);
	wvsprintf(szBuffer, pszData, vlArgs);
	va_end(vlArgs);
	Write2File(szBuffer, LEVEL_ERROR);
}
