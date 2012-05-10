#pragma once

#ifdef _UTIAPILIB
#define UTIAPI(type)  type __declspec(dllexport) 
#else
#define UTIAPI(type)  type __declspec(dllimport) 
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
*	交易服务器启动.
*	@param lpszDllPath dll接口文件路径.
*	@param lpszIniPath ini配置文件路径.
*	@param pnDllType dll接口文件的类型.
*	@param hWnd 日志显示的窗口句柄
*	@param lMessage 日志消息.
*	@param wParam 日志消息类型
<table border="1">
<tr><td>1</td><td>证券交易接口.</td></tr>
<tr><td>2</td><td>期货交易接口.</td></tr>
</table>
*	@return 启动成功则返回0,否则返回其它值.
*/
UTIAPI(int) UTI_Begin(LPCSTR lpszDllPath, LPCSTR lpszIniPath, int* pnDllType, HWND hWnd, long lMessage, int wParam);

/**
*	设置交易接口相关配置.
*	@param lpszDllPath dll接口文件路径.
*	@param lpszIniPath ini配置文件路径.
*	@return 设置成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_Set(LPCSTR lpszDllPath, LPCSTR lpszIniPath);

/**
*	设置客户端IP地址和MAC地址.
*	@param lpszIPAddr dll接口文件路径.
*	@param lpszMacAddr ini配置文件路径.
*	@return 设置成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_SetIPMacAddr(LPCSTR lpszIPAddr, LPCSTR lpszMacAddr);

/**
*	交易服务器停止.
*	@return 停止成功则返回0，否则返回其它值.
*/
UTIAPI(int) UTI_End();

/**
*	释放已申请内存的数据.
*	@param pData 数据地址指针.
*/
UTIAPI(void) UTI_Release(void* pData);




typedef void (CALLBACK* UTI_LOG_FUN)(LPCTSTR,LPVOID);

/**
* 设置UTI日志记录
* @param pFun 日志记录函数
* @param lParam 回调给日志记录函数的参数
*/
UTIAPI(void) UTI_SetLogFun(UTI_LOG_FUN pFun,LPVOID lParam);


UTIAPI (int) GetPackSumData(char *pPackSum, int nPackSumSize, int nNumber);

#ifdef __cplusplus
}
#endif