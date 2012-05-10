#pragma once
/**
* 深圳市创真科技有限公司，李伟
*
*/

//IO操作
enum IOTYPE
{
	//eIOInit,	//初始化
	eIORead,		//读取完成
	eIOWrite,		//发送完成
	eIOExit,		//退出
	eIOSysIdle,		//系统空闲.
	eIOSendBufferData,	//通知发送缓冲区中的数据.
	eIODeleteThis,		//删除连接对象
	eUserDefine,		//用户自定义，这样可以扩充请求类型.

	eIOMAXSYS=100		//系统保留100以下的。
};


typedef void (CALLBACK* LPUSERCOMMANDFUN)(LPVOID /*lParam*/);

class AFX_EXT_CLASS CHHWPIOCP
{
protected:
	CHHWPIOCP(void);

public:
	virtual ~CHHWPIOCP(void);
	static 	CHHWPIOCP* Init();
	static  void UnInit();

	static UINT    ThreadIOCPFun(LPVOID lParam);			//ＩＯＣＰ工作线程

	//写入系统日志信息
	//static void AppendLog(LPCSTR sMesg);


	//发送命令.
	static void SendUserRegisterCommand(int nCommand,LPVOID lParam);
	static bool RegisterIOCPUserCommand(int nCommand,LPUSERCOMMANDFUN pFun);

	/**
	* 开启一个侦听通道
	*
	*
	*/
//	BOOL StartListen(CChannel& channel);


    
	/**
	* 记录日志信息
	*/
	//virtual void //AppendLog(LPCSTR mesg);

public:

	static CHHWPIOCP* g_pHHWPIOCP;

public:
	HANDLE m_hCompletionPort; //Io Completion Port;

	
};

//系统不忙的时候调用该函数.
void OnSysIdle();