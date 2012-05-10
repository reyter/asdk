#pragma once
#include "cceclientprocessor.h"



#include "CCEServerList.h"

/**
*	支持多服务器自动切换的客户端
*/
class AFX_EXT_CLASS CCCEClientProcessor_MultiServer :
	public CCCEClientProcessor
{

	DECLARE_DYNCREATE(CCCEClientProcessor_MultiServer);

public:
	CCCEClientProcessor_MultiServer(void);

	virtual ~CCCEClientProcessor_MultiServer(void);

	/**
	*	添加服务器.
	*	仅支持在断开状态下进行添加服务器
	*/
	bool AddServer(const CCCETCPServerInfo* pInfo);	


	/**
	*	添加服务器.
	*	仅支持在断开状态下进行添加服务器
	*/
	bool AddServer(LPCSTR lpServer,
		int nPort,				
		int nLevel,				//连接优先级.
		CCE_PROXYTYPE  iProxyType,		//使用的代理类型.无代理时为零 
		const char* szProxyHost,	//代理地址, 无代理时为""
		int  iProxyPort,	//代理端口, 无代理时为0
		const char* szProxyUser,	//代理用户名, 无代理时为""
		const char* szProxyPass,	//代理密码),无代理时为"");	
		const BYTE* pExtraData,
		int   nExtraDataLength);
	
	/**
	*	开始运作，尝试连接服务器.
	*/
	void Begin();

	/**
	*	主动断开
	*   子类需要调用基类的END.
	*/
	void End();


	/**
	*	获取当前已经连接的连接信息.
	*/
	const CCCETCPServerInfo* GetCurrentConnectionInfo();


	//子类可以重载的事件函数
protected:

	/**
	*	连接结果回调. 建议连接成功时，处理此消息，连接失败时，调用本类的函数，
	*	以便尝试连接下一服务器.
	*	@param bRet 连接结果 True for Successed, false for Failed.
	*	
	*/
	virtual void OnConnectResult(bool bRet);


	/**
	* 默认不关闭，继续连接
	* 默认再向连接最优的服务器
	*/
	virtual bool OnClose();
	
private:

	/**
	* 向服务器发起连接.
	*/
	void DoConnect();

	/**
	* 网络断开后的处理策略为重新连接.
	*/
	void TryConnectServer();

	/**
	* 连接失败后的处理策略为连接下一服务器地址.
	*/
	void TryConnectNextServer();

	   
	CCCEServerList m_lsServer;

	/**
	* 当前要连接或欲连接的服务器信息
	*/
	const CCCETCPServerInfo* m_pCurrentServerInfo;
};

