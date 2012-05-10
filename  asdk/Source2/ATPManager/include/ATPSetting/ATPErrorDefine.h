/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨������.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-1		��ΰ		 ����
-------------------------------------------------------------
*/

#pragma once

/**
����������Ϣ.
*/
struct AFX_EXT_CLASS ErrorDefine
{
	int nErrorCode;
	CString strError;
};


/**
���������Ϣ��.���ڹ���������Windows SDK ���Ƶ� һ�� ErrorCode ,��Ӧһ�� �����ִ�.
*/
#define DECLARE_ERROR_MAP() \
private: \
	static const struct ErrorDefine s_ErrorDefineArray[]; \
	DWORD m_dwLastError; \
	int   m_nErrorType;\
	CString  m_strLastError;\
public: \
	virtual DWORD GetLastErrorCode(); \
	static CString GetErrorFromCode(DWORD dwError); \
	virtual CString GetLastError(); \
protected:\
	virtual void SetLastError(DWORD dwError);\
	virtual void SetLastDynamicError(DWORD dwError,CString strError);\






#define BEGIN_ERROR_MAP(classname) \
	void classname::SetLastDynamicError(DWORD dwError,CString strError)\
	{\
		m_dwLastError = dwError;\
		m_strLastError = strError;\
		m_nErrorType   = 0x738B;\
	}\
	DWORD classname::GetLastErrorCode() \
	{	\
		if(m_nErrorType  == 0x738B)\
		{\
			return m_dwLastError;\
		}else\
			return (::GetLastError()==m_dwLastError)?m_dwLastError:m_dwLastError&(~(1<<29)); \
	}	\
	CString classname::GetErrorFromCode(DWORD dwError)			\
	{	\
		for(int i=0;s_ErrorDefineArray[i].nErrorCode!=0;++i) \
		{ \
			if(s_ErrorDefineArray[i].nErrorCode == dwError) \
			{ \
				return s_ErrorDefineArray[i].strError; \
			} \
		} \
		return _T("Unknown Error");\
	} \
	CString classname::GetLastError() \
	{ \
		if(m_nErrorType == 0x738B)\
		{\
			return m_strLastError;\
		}else\
			return GetErrorFromCode(m_dwLastError); \
	}	\
	void classname::SetLastError(DWORD dwError) \
	{ \
		m_dwLastError = dwError; \
		::SetLastErrorEx(dwError|(1<<29),0); \
		m_nErrorType = 0;\
	}\
	AFX_COMDAT const ErrorDefine classname::s_ErrorDefineArray[]=\
	{






#define ON_ERROR(code,str) \
{code,str},\




#define END_ERROR_MAP() \
{0,_T("")}};





