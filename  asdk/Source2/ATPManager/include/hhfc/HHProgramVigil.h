#pragma once
#include "psapi.h"
#define ID_VIGILLOGFLAGS_ALARM		0x80000000	//报警
#define ID_VIGILLOGFLAGS_ALARMSTOP  0x40000000	//解除报警

class AFX_EXT_CLASS CHHProgramVigil
{
public:
	/**
	* 启动监控进程
	* @param szVigilExec [in] 执行文件名称, 已经废弃，设置为NULL
	* @param nCheckTime	 [in] 检查进程无响应的检测时间(秒)，-1:不检测
	* @return 1:成功
	*/
	static BOOL StartVigilProcess(LPCSTR szVigilExec, int nCheckTime=-1);

	/**
	* 结束监控进程
	* @param szVigilExec [in] 执行文件名称, 已经废弃，设置为NULL
	* @return 1:成功
	*/
	static BOOL StopVigilProcess(LPCSTR szVigilExec);

	/**
	* 设置监控进程信息(通知进程正常工作), 如果设置了进出无响应检测时间，就必须在检测时间类调用此函数
	* @param szVigilExec [in] 执行文件名称, 已经废弃，设置为NULL
	* @return 1:成功
	*/
	static BOOL SetVigilProcessOK(LPCSTR szVigilExec);

	/**
	* 设置监控进程时间(返回上次检测时间)
	* @param szVigilExec [in] 执行文件名称, 已经废弃，设置为NULL
	* @param nCheckTime	 [in] 检查进程无响应的检测时间(秒)，-1:不检测
	* @return 1:成功
	*/
	static int  SetVigilProcessCheckTime(LPCSTR szVigilExec, int nCheckTime);

public:
	/**
	* 获取进程信息
	* @param szPathFile [in] 执行文件名称
	* @param pMemInfo	[out] 内存信息
	* @param dwProcessID[out] 进程ID
	* @return 1:成功
	*/
	static BOOL GetProcessMemoryInfo(LPCSTR szPathFile,PPROCESS_MEMORY_COUNTERS pMemInfo,DWORD& dwProcessID);

	/**
	* 结束指定可执行文件的进程
	* @param szPathFile [in] 执行文件名称
	* @return 1:成功
	*/
	static BOOL KillProcess(LPCSTR szPathFile);

	/**
	* 启动进程
	* @param szPathFile [in] 执行文件名称
	* @return 1:成功
	*/
	static BOOL StartProcess(LPCSTR szPathFile);

	/**
	* 设置监控进程的附加信息
	* @param nType  [in] 信息类型
	* @param pInfo	[in] 信息数据
	* @param nSize	[in] 信息数据长度
	* @return 1:成功
	*/
	static BOOL SetVigilProcessData(int nType, char *pInfo, int nSize);

	/**
	* 获取监控进程的附加信息
	* @param nIndex  [in] 信息索引
	* @param nType	 [in] 信息类型
	* @param pchExecFile [out] 执行文件
	* @param pInfo	 [out] 信息数据
	* @param nSize	 [out] 信息数据长度
	* @param nRunningFlag [out] 正在运行标志
	*/
	static int GetVigilProcessData(int nIndex, int nType, char *pchExecFile, char *pInfo, int &nSize, int &nRunningFlag);
	
	/**
	* 获取监控进程的信息
	* @param nIndex [in] 信息索引
	* @param nType	[in] 信息类型
	* @param pInfo	[out] 信息数据
	* @param nSize	[out] 信息数据长度
	*/
	static int GetVigilProcessInfo(int nIndex, int nType, char *pInfo, int &nSize);
	
	/**
	* 获取守护日志(nID为日志记录唯一识别符, 顺序增加, 如果返回值为-1表示日志已经结束, nID=-1时获取最后一个日志)
	* @param nID [in] 日志记录唯一识别符,nID=-1时获取最后一个日志
	* @param pLog [out] 日志数据
	* @param nSize [out] 日志数据长度
	*/
	static int GetVigilLog(int nID, char *pLog, int &nSize);
	
	/**
	* 设置应用程序更新数据
	* @param nAppType	[in] 应用数据类型
	* @param nAppDate	[in] 数据更新日期 yyyymmdd
	* @param nAppTime	[in] 数据更新时间 hhmmss
	*/
	static BOOL SetVigilProcessAppUpdateTime(int nAppType, int nAppDate, int nAppTime);

	/**
	* 设置应用程序状态
	* @param nStatus	[in] 状态
	* @param pchStatus	[in] 状态信息
	*/
	static BOOL SetVigilProcessAppStatus(int nStatus, char *pchStatus);
	
	/**
	* 设置应用程序文字信息
	* @param pchMessage [in] 信息
	* @return 1:成功
	*/
	static BOOL SetVigilProcessTxtMessage(char *pchMessage);
	
	//2010.11.18增加通讯端口信息
	static int SetVigilPortInfo(int nLocalPort, int  nRemotePort, int nRemoteIP, char *pchAccount, char *pchStatus=NULL, char *pchInfo1=NULL, char *pchInfo2=NULL);
	static int SetVigilPortInfo(int nLocalPort, int  nRemotePort, int nRemoteIP, char *pchAccount, int  nAppType ,int  nAppDate, int  nAppTime);
	static int RemoveVigilPortInfo(int nLocalPort, int  nRemotePort, int nRemoteIP);
	static int RemoveAllVigilPortInfo();
	

	/**
	* 设置应用程序日志信息(2011.5.24增加日志传送)
	* @param nLogFlags	[in] 日志标志, 参见 ID_VIGILLOGFLAGS_ 定义
	* @param pLog		[in] 日志数据
	* @param nLogSize	[in] 日志数据长度(必须<128)
	* @return 成功:日志记录数  失败:0:守护程序没有启动
	*/
	static int SetVigilProcessLog(int nLogFlags, char *pLog, int nLogSize);
	
	/**
	* HHFC内部使用函数
	*/
	static char *GetVigilPortInfo(int &nItems, int &nItemSize);
public:
	CHHProgramVigil(void);
	~CHHProgramVigil(void);
};
