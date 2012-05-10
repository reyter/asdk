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
	//��ʼ�����Ӳ�������
	BOOL Init(void);

	//������Ӳ�������
	void UnInit(void);

	//�����̶���������
	CShortSocket* CreateFixedConnect(void);
	
	//������֤����Socket����
	BOOL CreateAuthConnect(CShortSocket* pSocket);

	//�����������Socket����
	BOOL CreateMarketConnect(CShortSocket* pSocket);

	//�ر�Socket����
	void Disconnect(CShortSocket* pSocket);

private:
	static CServerFactory m_instance;
	CProxyOption m_ProxyOption;
	CString m_strProxyFlie;
};
#endif // SocketFactory_h__