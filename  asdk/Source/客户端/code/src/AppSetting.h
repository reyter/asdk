#pragma once
#include <atlstr.h>
#include <vector>
#include "Connenct\ServerMg.h"
#include "Common\Log.h"
#include "tinyxml.h"

class CAppSetting
{
public:
	CAppSetting(void);
	~CAppSetting(void);
	static CAppSetting& GetInstance(void);

public:
	//************************************
	// Method:    SetAutoStartup
	// FullName:  CAppSetting::SetAutoStartup
	// Access:    public 
	// Returns:   void
	// Description:设置系统启动客户端自动运行
	// Parameter: BOOL bAutoRun
	//************************************
	void SetAutoStartup(BOOL bAutoRun);


	//************************************
	// Method:    IsAutoStartup
	// FullName:  CAppSetting::IsAutoStartup
	// Access:    public 
	// Returns:   BOOL
	// Description:客户端是否系统启动自动行动
	// Parameter: void
	//************************************
	BOOL IsAutoStartup(void);

	//************************************
	// Method:    GetFixedServer
	// FullName:  CAppSetting::GetFixedServer
	// Access:    public 
	// Returns:   DWORD
	// Description:获取固定服务器地址
	// Parameter: CServer& svr
	//************************************
	DWORD GetFixedServer(CServer& svr);


	//************************************
	// Method:    GetServerListData
	// FullName:  CAppSetting::GetServerListData
	// Access:    public 
	// Returns:   DWORD
	// Description:获取服务器列表信息
	// Parameter: std::vector<CServerGroup> & m_vtServerGroups
	//************************************
	DWORD GetServerGroup(std::vector<CServerGroup>& vtServerGroups);


	//************************************
	// Method:    SetSaveAccount
	// FullName:  CAppSetting::SetSaveAccount
	// Access:    public 
	// Returns:   void
	// Description:是否记住当前账号
	// Parameter: BOOL bSave
	//************************************
	void SetSaveAccount(BOOL bSave);

	//************************************
	// Method:    IsSaveAccount
	// FullName:  CAppSetting::IsSaveAccount
	// Access:    public 
	// Returns:   BOOL
	// Description:是否记住当前账号
	// Parameter: void
	//************************************
	BOOL IsSaveAccount(void);


	//************************************
	// Method:    SetSavePassword
	// FullName:  CAppSetting::SetSavePassword
	// Access:    public 
	// Returns:   void
	// Description:是否保存密码
	// Parameter: BOOL bSave
	//************************************
	void SetSavePassword(BOOL bSave);

	//************************************
	// Method:    IsSavePassword
	// FullName:  CAppSetting::IsSavePassword
	// Access:    public 
	// Returns:   BOOL
	// Description:是否保存密码
	// Parameter: void
	//************************************
	BOOL IsSavePassword(void);

	//************************************
	// Method:    GetAccount
	// FullName:  CAppSetting::GetAccount
	// Access:    public 
	// Returns:   CString
	// Description:
	// Parameter: void
	//************************************
	CString GetAccount(void);

	//************************************
	// Method:    SetAccount
	// FullName:  CAppSetting::SetAccount
	// Access:    public 
	// Returns:   void
	// Description:
	// Parameter: CString strAccount
	//************************************
	void SetAccount(CString strAccount);

	//************************************
	// Method:    GetPassword
	// FullName:  CAppSetting::GetPassword
	// Access:    public 
	// Returns:   CString
	// Description:
	// Parameter: void
	//************************************
	CString GetPassword(void);

	//************************************
	// Method:    SetPassword
	// FullName:  CAppSetting::SetPassword
	// Access:    public 
	// Returns:   void
	// Description:
	// Parameter: CString strPwd
	//************************************
	void SetPassword(CString strPwd);


private:
	static CAppSetting m_Instance; 
};


