#ifndef CommonFunc_h__
#define CommonFunc_h__


#include <string>
#include <vector>
#include <io.h>
#include <boost\checked_delete.hpp>
#include <locale>
#include <atlstr.h>

//获取应用程序当前路径
CString GetAppPath(void);

//就否存在文件
BOOL CheckFileExist(const wchar_t* pszFile );

//获取操作系统版本
CString GetOSVersion(void);

//获取操作系统语言
CString GetOSLocale(void);

//获取当前客户端使用的语言
CString GetLanguageType( void );

//获取当前语言资源文件
CString	GetCurrentLanguageResource(void);

//获取程序的配置文件
CString GetAppSettingFile(void);

//获取代理配置文件
CString GetProxyFile(void);

//获取服务器列表配置文件
CString GetSvrlistFile(void);

char * ExtractDirFromFullPath(char * path);

#endif // CommonFunc_h__
