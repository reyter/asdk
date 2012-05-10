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
	// Description:�����¼��֤
		// Parameter: const CServer authsvr     ��֤������
	// Parameter: const CString & strAccount �˺�
	// Parameter: const CString & strPwd       δ���ܵ�����
	//************************************
	DWORD Login(const CServer authsvr,const CString& strAccount,const CString& strPwd);

	//************************************
	// Method:    Logout
	// FullName:  CAuthentication::RequestLogout
	// Access:    public 
	// Returns:   DWORD
	// Description:����ע��
	// Parameter: void
	//************************************
	DWORD Logout(void);


	//************************************
	// Method:    ModifyPwd
	// FullName:  CAuthentication::ModifyPwd
	// Access:    public 
	// Returns:   DWORD
	// Description:�޸�����
	// Parameter: const CString & strNewPwd ������
	// Parameter: const CString & strOldPwd   ������
	//************************************
	DWORD ModifyPwd(const CString& strNewPwd,const CString& strOldPwd);

private:
	//��֤��������IP��ַ
	CServer m_AuthSvr;

};
#endif // Authentication_h__
