
#pragma once

#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include "CCEDefine.h"

///通道类,
class AFX_EXT_CLASS CChannel
{

public:
	CChannel(CHANNEL_INFO_CORE* core);
	~CChannel();

	CHANNEL_INFO_CORE m_core;

	SOCKET  m_sListenSocket;	//侦听

	WSAEVENT  m_hEventAccept;

	CWinThread* m_pListenThread;

	void  Quit();


	bool Open();	//打开通道

	void Stop();	//停止侦听

	static UINT ListnerThreadProc(LPVOID pParam);

	static int CALLBACK ConnectAcceptCondition(IN LPWSABUF lpCallerId,
		IN LPWSABUF lpCallerData,
		IN OUT LPQOS lpSQOS,
		IN OUT LPQOS lpGQOS,
		IN LPWSABUF lpCalleeId,
		OUT LPWSABUF lpCalleeData,
		OUT GROUP FAR *g,
		IN DWORD dwCallbackData);

	//static void //AppendLog(LPCTSTR mesg);

	bool EditChannel(CHANNEL_INFO_CORE* pNewCore);

	void  GetChannelInfo(HHWP_CHANNELINFO* pInfo);

	INT_PTR  GetConnectionCount();			//取边接数

	void GetConnForDisPlay(CONNECT_INFO_SHOW*& pInfo,INT_PTR& nAlloc,INT_PTR& nData);

	bool m_bShutdown;	//指示是否手动关闭

	bool m_bConnSvrOk;	//连接服务器是否正常.

	CString  m_szErrorInfo;

	CPtrList m_lsConnection;

	void AddConnection(LPVOID pConnection);
	void DeleteConnection(LPVOID pConnection);

protected:
	CRITICAL_SECTION  m_cslsConn;

	UINT			  m_nMaxConnection;

public:
	__int64 m_client2Server;
	__int64 m_server2Client;


};


#endif //__CHANNEL_H__