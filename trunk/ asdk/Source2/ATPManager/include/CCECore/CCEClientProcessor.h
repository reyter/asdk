#pragma once

#include "winsock2.h"

#include "CCEDefine.h"
#include "CCEProcessor.h"




//�ͻ��˴����࣬
//�������ӷ�����\����\�Զ�����\����.
class AFX_EXT_CLASS CCCEClientProcessor : public CCCEProcessor
{
	DECLARE_DYNCREATE(CCCEClientProcessor);

public:
	CCCEClientProcessor();
	virtual ~CCCEClientProcessor();

	/**
	* ���������첽���ӵ�ָ��������
	*/
	void SetSvrInfoAndConnect(const CString& host,
		int nPort,
		CCE_PROXYTYPE  iProxyType=PROXYTYPE_NOPROXY,		//ʹ�õĴ�������.
		const char* szProxyHost=NULL,	//�����ַ
		int  iProxyPort=0,		//����˿�
		const char* szProxyUser=NULL,	//�����û���
		const char* szProxyPass=NULL	//��������)
		);



	/**
	*	ֱ���������ӵ�ָ���ķ�����,ֱ���������Ӳ�������OnConnectResult���Ļص�֪ͨ
	*	@param host				���ӵķ�������ַ
	*	@param nPort			�˿�
	*	@param iProxyType		��������
	*	@param szProxyHost		�����ַ
	*	@param iProxyPort		����˿�
	*	@param szProxyUser		�����û���
	*	@param szProxyPass		��������
	*	@param pBStop			ָ���Ƿ�ֹͣ����
	*	@param return			�����Ƿ����ӳɹ�.True for Successed. False for Failed.
	*/
	bool ConnectToServer(const CString& host,
		int nPort,
		CCE_PROXYTYPE  iProxyType=PROXYTYPE_NOPROXY,		//ʹ�õĴ�������.
		const char* szProxyHost=NULL,	//�����ַ
		int  iProxyPort=0,		//����˿�
		const char* szProxyUser=NULL,	//�����û���
		const char* szProxyPass=NULL,	//��������)
		bool* pBStop=NULL);


	/**
	�����Ͽ��������������
	*/	
	void Disconnect();


    
	//����������صĺ���
protected:
	/**
	*	�����Ϸ�����ʱ�Ļص�����.
	*	����ɶҲ����.
	*	@param bRet ����
	*/	
	virtual void OnConnectResult(bool bRet);

	
	/**
	*	���ߴ���
	*/	
	virtual bool OnClose();


protected:
	//����״̬
	bool m_nCurrentStatus;

	//�Ƿ����������Ͽ�
	bool m_bMannualEnd;

private:
	//��������ʹ�õĴ���.
	void SetProxy(CCE_PROXYTYPE  iProxyType,		//ʹ�õĴ�������.
		const char* szProxyHost,	//�����ַ
		int  iProxyPort,		//����˿�
		const char* szProxyUser,	//�����û���
		const char* szProxyPass	//��������)
		);

	//���Ӵ���ʱʹ�õ�����.
	CCE_PROXYDATA  m_proxy_data;	//�����������ַ.
	SOCKET      m_hSocket;
	u_long      m_nPeerIP;
	u_short      m_nSvrPort;
	CString     m_strReAddr;

	/**
	�������Ӷ���.
	*/
	void GenConnectionObject();

	//ʹ�ô���������Ӵ������ӹ���.
	bool ConnectWithProxy(const char* svrAddress,UINT nPort,bool* pBStop=NULL);

	BOOL connect_sock4(SOCKET hConnect);
	BOOL connect_sock5(SOCKET hConnect);
	BOOL connect_http11(SOCKET hConnect);

public:
	/**
	* �����ããŰ��ڲ�����.
	*/
	void _CCEConnect();


};


