#ifndef Log_h__
#define Log_h__

#include <string>
#include <io.h>
#include <Windows.h>

 // 日志级别定义
enum LogLevel                  
{ 
	LEVEL_DEBUG,		// 调试
	LEVEL_INFO,			// 信息
	LEVEL_WARNING,	// 告警
	LEVEL_ERROR,		// 错误
};


class CLog
{
public:
	CLog(void)
	{
		InitializeCriticalSection(&m_csLock);
	}

	~CLog(void)
	{
		DeleteCriticalSection(&m_csLock);
	}

	void SetLogFile( std::wstring strFileName)
	{
		m_strFileName = strFileName;
	}

public:
	void LOG_DEBUG(const wchar_t* pszData, ...);
	void LOG_INFO(const wchar_t* pszData, ...);
	void LOG_WARNING(const wchar_t* pszData, ...);
	void LOG_ERROR(const wchar_t* pszData, ...);

protected:
	 void Write2File(const wchar_t* pszData, int nLevel);

private: 
	std::wstring m_strFileName;
	CRITICAL_SECTION m_csLock;   
};



extern CLog g_Log;


#endif // Log_h__
