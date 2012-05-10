#ifndef SocketFactory_h__
#define SocketFactory_h__

#include "ServerMg.h"
#include "ShortSocket.h"

class CServerFactory:protected CServerMgr
{
public:
	CServerFactory(void);
	~CServerFactory(void);
	
public:
	static CServerFactory& GetInstance(void);

	std::vector<CServerGroup>& GetServerGroup(void);

	CProxyOption& GetProxyOptionObject(void);

public:
	//初始化连接参数配置
	BOOL Init(void);

	//清除连接参数配置
	void UnInit(void);

	//创建固定主机连接
	CShortSocket* CreateFixedConnect(void);
	
	//创建认证服务Socket连接
	BOOL CreateAuthConnect(CShortSocket* pSocket);

	//创建行情服务Socket连接
	BOOL CreateMarketConnect(CShortSocket* pSocket);

	//关闭Socket连接
	void Disconnect(CShortSocket* pSocket);

private:
	static CServerFactory m_instance;
	CProxyOption m_ProxyOption;
	CString m_strProxyFlie;
};
#endif // SocketFactory_h__