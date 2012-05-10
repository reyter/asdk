#ifndef Authentication_h__
#define Authentication_h__
#include "Connenct\ServerMg.h"

class CAuthentication
{
public:
	CAuthentication(void);
	~CAuthentication(void);

public:
	//************************************
	// Method:    Login
	// FullName:  CAuthentication::RequestUserAuth
	// Access:    public 
	// Returns:   DWORD
	// Description:请求登录认证
		// Parameter: const CServer authsvr     认证服务器
	// Parameter: const CString & strAccount 账号
	// Parameter: const CString & strPwd       未加密的密码
	//************************************
	DWORD Login(const CServer authsvr,const CString& strAccount,const CString& strPwd);

	//************************************
	// Method:    Logout
	// FullName:  CAuthentication::RequestLogout
	// Access:    public 
	// Returns:   DWORD
	// Description:请求注销
	// Parameter: void
	//************************************
	DWORD Logout(void);


	//************************************
	// Method:    ModifyPwd
	// FullName:  CAuthentication::ModifyPwd
	// Access:    public 
	// Returns:   DWORD
	// Description:修改密码
	// Parameter: const CString & strNewPwd 新密码
	// Parameter: const CString & strOldPwd   旧密码
	//************************************
	DWORD ModifyPwd(const CString& strNewPwd,const CString& strOldPwd);

private:
	//认证服务器的IP地址
	CServer m_AuthSvr;

};
#endif // Authentication_h__
