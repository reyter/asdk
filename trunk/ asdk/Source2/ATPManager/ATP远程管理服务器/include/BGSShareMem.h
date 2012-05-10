#ifndef _VIGILDEFINE_HEAD_

#define _VIGILDEFINE_HEAD_


#define ID_SVR_STOPPROCESS		28800	//, OnSvrStopProcess)		//结束进程
#define ID_SVR_STARTPROCESS		28801	//, OnSvrStartProcess)		//启动进程
#define ID_SVR_RESTARTPROCESS	28802	//, OnSvrRestartProcess)	//重新启动进程
#define ID_SVR_REMOVE			28803	//, OnSvrRemoveItem)
#define ID_SVR_SET				28804	//, OnSvrSet)
#define ID_SVR_OPENFILELOCATION	28805	//, OnSvrOpenFileLocation)
#define ID_SVR_ACTIVEPROCESS	28806	//, OnSvrActiveProcess)

extern char *g_pVigilMem;

struct ATPMainHead
{
	int		nHeadSize;
	int		nDate;
	int		nTime;
	int		nItemSize;
	char	chATPName[32];	//系统名称
	int		nPort;			//分布式服务侦听端口
	int		nMainFlag;		//主系统标志
	int		nMaxItems;
	int		nSvcItems;		//服务个数
	int		nAlgItems;		//算法个数
	int     nStartAlgOuttime;
	//算法ID计数
	int		nAlgIDCount;
	//总资源信息
	int		nCPUUsage;
	int		nMemUsage;
	//通讯数据
	int		nSendBytes;
	int		nRecvBytes;
	__int64 iTotalSendBytes;
	__int64 iTotalRecvBytes;
	//ATPMain窗口句柄
	HWND	hWndATPMain;
#ifdef _M_IX86
	int		nWndATPMainFill;
#endif
};

#define ID_ATPFLAGS_TASKSET			0x00008000	//启动计划任务
#define ID_ATPFLAGS_WORKDATE		0x00004000	//工作日
#define ID_ATPFLAGS_TIMINGSTART		0x00000001	//定时启动
#define ID_ATPFLAGS_TIMINGSTOP		0x00000002	//定时停止
#define ID_ATPFLAGS_TIMINGRESTART1	0x00000004	//定时重启1
#define ID_ATPFLAGS_TIMINGRESTART2	0x00000008	//定时重启2
#define ID_ATPFLAGS_VIGILSET		0x80000000	//启动守护
#define ID_ATPFLAGS_NORESPONSE		0x00010000	//程序无响应时重新启动
#define ID_ATPFLAGS_ABNORMAL		0x00020000	//程序异常时重新启动

struct ATPMainItem
{
	//服务信息
	int	 nServiceClass;	//服务类别
	int	 nServiceID;	//服务ID
	char chService[36];	//服务名称
	char chExec[128];	//程序
	char chAccount[48];	//账号
	//计划任务&守护设置
	int	 nTaskFlags;	//0x80000000:启动守护 0x01:定时启动 0x02:定时结束 0x04:定时重启1 0x08:定时重启2 0x00004000:在工作日执行计划任务 0x8000:启动计划任务
	int  nStartupTime;	//启动时间
	int  nStopTime;		//结束时间
	int  nRestartTime1;	//重启时间1
	int  nRestartTime2;	//重启时间2
	int  nNoresponseCheckTime;	//无响应检测时间
	//服务运行状态
	char bExecRunning;
	char chRunCount;
	char chServiceRequestRestart; //=='e' 服务请求重新启动
	char chStartupCheck;	//启动检测计数器
	char chRunFlags;		//运行监控标志
	char chDPSStartFlag;	//分布式启动标志
	char chResv[2];
	int	 nRestartDate;
	int  nRestartTime;
	int	 nRestartDate1;
	int	 nRestartDate2;
	int  nStatusChangeFlags;
	int  nStatus;
	char chStatus[128];
	int	 nStartTime;		//启动时间
	int	 nStartDate;		//启动日期
	int  nCheckCount;		//无响应检测计数
	int	 nLastTime;			//检测时间
	char chLog[128];
	//统计信息///////
	int  nSendDataCount;	//发送消息
	int  nRecvDataCount;	//接收消息
	int	 nProcessedDataCount;//已处理消息
	int  nInfoData[32];
	//////////////////////////////////
	char chServerIP[32];
	int  nServerPort;
	//////////////////////////////////
	DWORD  dwProcessID;		//进程ID
	HANDLE hProcess;		//进程句柄
#ifdef _M_IX86
	char chHPROCESSFill[4];	
#endif
	__int64 iCurrentCPUUsage;
	__int64 iLastCPUUsage;
	__int64	iStartTick;		//启动时间Tick
	int  nCpuUsage;			//CPU使用率*100
	int  nMemoryUsage;		//内存使用(KB)
	int  nHandleCount;		//句柄
	int	 nThreadsCount;		//线程
	int  nRefreshTime;		//刷新间隔时间
	int  nRefreshCount;		//刷新计数
	HICON hIcon;			//图标
#ifdef _M_IX86
	char chHICONFill[4];	
#endif
	HWND hWndBGS;			//进程通讯窗口句柄
#ifdef _M_IX86
	char chHWNDFill[4];	
#endif
};


#endif