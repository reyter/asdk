/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法管理器.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-1		李伟		 创建
-------------------------------------------------------------
*/

#pragma once

/**
错误描述信息.
*/
struct AFX_EXT_CLASS ErrorDefine
{
	int nErrorCode;
	CString strError;
};


/**
定义错误消息宏.用于管理类似于Windows SDK 类似的 一个 ErrorCode ,对应一个 错误字串.
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





