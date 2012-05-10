#pragma once

class CProxyOption
{
public:
	CProxyOption(void);
	~CProxyOption(void);
	int m_nProxyType;
	bool m_bIsValid;
	bool m_bUseHttpHead;
	CString m_strProxyIP;
	int m_nProxyPort;
	CString m_strProxyUser;
	CString m_strProxyPass;
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
