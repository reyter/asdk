#pragma once

// CDownThread
class CDlgLogin;
class CDownThread : public CWinThread
{
	DECLARE_DYNCREATE(CDownThread)

public:
	CDownThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CDownThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual int Run();
	bool m_bExitFlag;
	HWND m_hwndMain;
	CDlgLogin * m_pLogin;
	CShortSocket m_sk;
	void SetMainHwnd(HWND c_hwnd);
};


