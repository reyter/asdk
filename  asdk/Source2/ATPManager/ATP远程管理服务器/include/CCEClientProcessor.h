#pragma once

#include "winsock2.h"

#include "CCEDefine.h"
#include "CCEProcessor.h"




//客户端处理类，
//增加连接服务器\代理\自动重连\功能.
class AFX_EXT_CLASS CCCEClientProcessor : public CCCEProcessor
{
	DECLARE_DYNCREATE(CCCEClientProcessor);

public:
	CCCEClientProcessor();
	virtual ~CCCEClientProcessor();

	/**
	* 非阻塞，异步连接到指定服务器
	*/
	void SetSvrInfoAndConnect(const CString& host,
		int nPort,
		CCE_PROXYTYPE  iProxyType=PROXYTYPE_NOPROXY,		//使用的代理类型.
		const char* szProxyHost=NULL,	//代理地址
		int  iProxyPort=0,		//代理端口
		const char* szProxyUser=NULL,	//代理用户名
		const char* szProxyPass=NULL	//代理密码)
		);



	/**
	*	直接阻塞连接到指定的服务器,直接阻塞连接不会引起　OnConnectResult　的回调通知
	*	@param host				连接的服务器地址
	*	@param nPort			端口
	*	@param iProxyType		代理类型
	*	@param szProxyHost		代理地址
	*	@param iProxyPort		代理端口
	*	@param szProxyUser		代理用户名
	*	@param szProxyPass		代理密码
	*	@param pBStop			指定是否停止连接
	*	@param return			返回是否连接成功.True for Successed. False for Failed.
	*/
	bool ConnectToServer(const CString& host,
		int nPort,
		CCE_PROXYTYPE  iProxyType=PROXYTYPE_NOPROXY,		//使用的代理类型.
		const char* szProxyHost=NULL,	//代理地址
		int  iProxyPort=0,		//代理端口
		const char* szProxyUser=NULL,	//代理用户名
		const char* szProxyPass=NULL,	//代理密码)
		bool* pBStop=NULL);


	/**
	主动断开与服务器的连接
	*/	
	void Disconnect();


    
	//子类可以重载的函数
protected:
	/**
	*	连接上服务器时的回调函数.
	*	本类啥也不做.
	*	@param bRet 连接
	*/	
	virtual void OnConnectResult(bool bRet);

	
	/**
	*	断线处理
	*/	
	virtual bool OnClose();


protected:
	//在线状态
	bool m_nCurrentStatus;

	//是否请求主动断开
	bool m_bMannualEnd;

private:
	//设置连接使用的代理.
	void SetProxy(CCE_PROXYTYPE  iProxyType,		//使用的代理类型.
		const char* szProxyHost,	//代理地址
		int  iProxyPort,		//代理端口
		const char* szProxyUser,	//代理用户名
		const char* szProxyPass	//代理密码)
		);

	//连接代理时使用的数据.
	CCE_PROXYDATA  m_proxy_data;	//代理服务器地址.
	SOCKET      m_hSocket;
	u_long      m_nPeerIP;
	u_short      m_nSvrPort;
	CString     m_strReAddr;

	/**
	创建连接对象.
	*/
	void GenConnectionObject();

	//使用代理进行连接代理连接功能.
	bool ConnectWithProxy(const char* svrAddress,UINT nPort,bool* pBStop=NULL);

	BOOL connect_sock4(SOCKET hConnect);
	BOOL connect_sock5(SOCKET hConnect);
	BOOL connect_http11(SOCKET hConnect);

public:
	/**
	* 仅供ＣＣＥ包内部调用.
	*/
	void _CCEConnect();


};


