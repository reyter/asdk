#pragma once

class CProxyOption
{
public:
	CProxyOption(void);
	~CProxyOption(void);


	int m_nProxyType;//代理类型
	bool m_bIsValid;
	bool m_bUseHttpHead;

	CString m_strProxyIP;//代理IP
	int m_nProxyPort;//代理端口
	CString m_strProxyUser;//代理用户名
	CString m_strProxyPass;//代理密码



	int Init(CString c_strIniFile);
	int Save(CString c_strIniFile);
	bool getIsValid(){return m_bIsValid;};
	void setIsValid(bool c_b){m_bIsValid = c_b;};
	int getProxyType(){return m_nProxyType;};
	void setProxyType(int c_n){m_nProxyType = c_n;};
	CString getProxyIP(){return m_strProxyIP;};
	void setProxyIP(CString c_str){m_strProxyIP = c_str;};
	int getProxyPort(){return m_nProxyPort;};
	void setProxyPort(int c_n){m_nProxyPort = c_n;};
	CString getProxyUser(){return m_strProxyUser;};
	void setProxyUser(CString c_str){m_strProxyUser = c_str;};
	CString getProxyPass(){return m_strProxyPass;};
	void setProxyPass(CString c_str){m_strProxyPass = c_str;};
};
