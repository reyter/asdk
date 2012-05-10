
#pragma once

#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include "CCEDefine.h"

///ͨ����,
class AFX_EXT_CLASS CChannel
{

public:
	CChannel(CHANNEL_INFO_CORE* core);
	~CChannel();

	CHANNEL_INFO_CORE m_core;

	SOCKET  m_sListenSocket;	//����

	WSAEVENT  m_hEventAccept;

	CWinThread* m_pListenThread;

	void  Quit();


	bool Open();	//��ͨ��

	void Stop();	//ֹͣ����

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

	INT_PTR  GetConnectionCount();			//ȡ�߽���

	void GetConnForDisPlay(CONNECT_INFO_SHOW*& pInfo,INT_PTR& nAlloc,INT_PTR& nData);

	bool m_bShutdown;	//ָʾ�Ƿ��ֶ��ر�

	bool m_bConnSvrOk;	//���ӷ������Ƿ�����.

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