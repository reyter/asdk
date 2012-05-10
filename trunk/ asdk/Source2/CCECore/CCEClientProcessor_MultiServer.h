#pragma once
#include "cceclientprocessor.h"



#include "CCEServerList.h"

/**
*	֧�ֶ�������Զ��л��Ŀͻ���
*/
class AFX_EXT_CLASS CCCEClientProcessor_MultiServer :
	public CCCEClientProcessor
{

	DECLARE_DYNCREATE(CCCEClientProcessor_MultiServer);

public:
	CCCEClientProcessor_MultiServer(void);

	virtual ~CCCEClientProcessor_MultiServer(void);

	/**
	*	��ӷ�����.
	*	��֧���ڶϿ�״̬�½�����ӷ�����
	*/
	bool AddServer(const CCCETCPServerInfo* pInfo);	


	/**
	*	��ӷ�����.
	*	��֧���ڶϿ�״̬�½�����ӷ�����
	*/
	bool AddServer(LPCSTR lpServer,
		int nPort,				
		int nLevel,				//�������ȼ�.
		CCE_PROXYTYPE  iProxyType,		//ʹ�õĴ�������.�޴���ʱΪ�� 
		const char* szProxyHost,	//�����ַ, �޴���ʱΪ""
		int  iProxyPort,	//����˿�, �޴���ʱΪ0
		const char* szProxyUser,	//�����û���, �޴���ʱΪ""
		const char* szProxyPass,	//��������),�޴���ʱΪ"");	
		const BYTE* pExtraData,
		int   nExtraDataLength);
	
	/**
	*	��ʼ�������������ӷ�����.
	*/
	void Begin();

	/**
	*	�����Ͽ�
	*   ������Ҫ���û����END.
	*/
	void End();


	/**
	*	��ȡ��ǰ�Ѿ����ӵ�������Ϣ.
	*/
	const CCCETCPServerInfo* GetCurrentConnectionInfo();


	//����������ص��¼�����
protected:

	/**
	*	���ӽ���ص�. �������ӳɹ�ʱ���������Ϣ������ʧ��ʱ�����ñ���ĺ�����
	*	�Ա㳢��������һ������.
	*	@param bRet ���ӽ�� True for Successed, false for Failed.
	*	
	*/
	virtual void OnConnectResult(bool bRet);


	/**
	* Ĭ�ϲ��رգ���������
	* Ĭ�������������ŵķ�����
	*/
	virtual bool OnClose();
	
private:

	/**
	* ���������������.
	*/
	void DoConnect();

	/**
	* ����Ͽ���Ĵ������Ϊ��������.
	*/
	void TryConnectServer();

	/**
	* ����ʧ�ܺ�Ĵ������Ϊ������һ��������ַ.
	*/
	void TryConnectNextServer();

	   
	CCCEServerList m_lsServer;

	/**
	* ��ǰҪ���ӻ������ӵķ�������Ϣ
	*/
	const CCCETCPServerInfo* m_pCurrentServerInfo;
};

