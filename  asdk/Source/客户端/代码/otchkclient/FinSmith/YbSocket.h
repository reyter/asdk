#pragma once

// CYbSocket ����Ŀ��

class CYbSocket : public CAsyncSocket
{
public:
	CYbSocket();
	virtual ~CYbSocket();
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


