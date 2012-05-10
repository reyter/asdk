#pragma once

// CCommThread
class CCommSocket;
class CCommThread : public CWinThread
{
	DECLARE_DYNCREATE(CCommThread)

public:
	CCommThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CCommThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual int Run();
	bool m_bExitFlag;
	bool m_bFirst;
	HWND m_hwndMain;
	CCommSocket * m_pComm;

	void SetCommSocket(CCommSocket * c_pComm);
	void SetMainHwnd(HWND c_hwnd);
};

extern CCommThread * gpCommThread;

