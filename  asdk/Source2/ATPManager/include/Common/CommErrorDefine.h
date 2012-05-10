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
#ifndef _COMMONERRORDEFINE_H__
#define _COMMONERRORDEFINE_H__

//1-100  �ڴ汣��
#define ERR_OUTOFMEMORY		1
#define ERR_NULLPOINTER		2
#define ERR_INVALIDHANDLER  3

//101-200 ͨѶ����
#define	ERR_NOT_CONNECT		101
#define	ERR_NOT_LOGINED		102
#define ERR_DISCONNECTED	103
#define ERR_NET_TIMEOUT		104

//1001-2000		TDF
#define ERR_TDF_NOT_FOUND_RESULT 	1001			//δ�ҵ���Ӧ�Ľ��
#define ERR_TDF_NOT_STRAT_SNAP	 	1002			//û�п�������
#define ERR_TDF_WROUNG_MARKET_CODE	1003			//�����֤ȯ����
#define ERR_TDF_RESULT_NOT_CORRECT	1004			//������д���
#define ERR_TDF_NOT_ADD_SERVER		1005			//δ���TDF������
#define ERR_TDF_SOMEDATA_WRONG		1006			//��Щ�����Ǵ����
#define ERR_TDF_FINDMARKETDATA_FAIL	1007			//���һ�ȡ����ʱʧ��

//2001-3000		TDB
#define ERR_TDB_NETBUSY             2001			//������Դ��ռ��
#define ERR_TDB_NOTSUPPORTMARKET	2002			//��֧�ֲ�ѯ���г�
#define ERR_TDB_NOT_PEERADDR		2003			//ȡ�Է���ַʧ��
#define ERR_TDB_NO_DATA	            2004			//û������
#define ERR_TDB_EZF_ERROR			2005			//�ױ๫ʽ�д���
#define ERR_TDB_EZF_DELFAIL			2006			//ɾ��ָ��ʧ��

//3001-3999		LOG
#define ERR_LOG_CREATEINDEXFILE_FAIL		3001	// ������������ļ�ʧ��
#define ERR_LOG_CREATELOGFILE_FAIL			3002	// ���������־�ļ�ʧ��
#define ERR_LOG_INDEXFILE_NOTFOUND			3003	// ׷������ʧ��,�����ļ�û���ҵ�
#define ERR_LOG_RECORD_NOT_FOUND			3004	// ��־��¼û���ҵ�	
#define ERR_LOG_NOT_CLASS					3005	// ��־���಻����
#define ERR_LOG_FILENAME_TOO_LONG			3006	// �ļ���������256���ַ�	
#define ERR_LOG_RECORD_TOO_MORE				3007	// ��¼̫����
#define ERR_LOG_FILECRC_WRONG				3008	// �ļ�CRCУ�����
#define	ERR_LOG_RECORDCRC_WRONG				3009	// ��¼CRCУ�����
#define ERR_LOG_UNKNOWN					3010	//	δ֪����
//5001-6000		ALG

//6001-7000		TTD
#define ERR_TTD_CREATE_EVETN		6001	//�����¼�����.
#define ERR_TTD_FUNCTION_TIMEOUT	6002	//����ִ�г�ʱ.
#define ERR_TTD_OPENFILE_FAIL		6003	//���ļ�ʧ��
#define ERR_TTD_DYNAMICKEY_FAIL		6004	//��ȡ��̬��Կʧ��
#define ERR_TTD_SNAPNOTFOUND		6005	//�ڴ������û���ҵ�
#define ERR_TTD_NOALGOONSERVER			6006	//��������û���㷨
#define ERR_TTD_RELEASEMEM			6007		//�ͷ��ڴ����
//8001-9000		UTI
#define	ERR_UTI_OTHER_COUNTER		8001
#define	ERR_UTI_WAITANS_TIMEOUT		8002
#define	ERR_UTI_UNFOUND_HOLDER		8003
#define	ERR_UTI_UNFOUND_FUTURESACC	8004
#define	ERR_UTI_UNKNOWN_BSSIDE		8005
#define	ERR_UTI_UNKNOWN_HEDGEFLAG	8006
#define	ERR_UTI_UNKNOWN_KPFLAG		8007
#define	ERR_UTI_UNKNOWN_CURRENCY	8008
#define	ERR_UTI_UNKNOWN_HOLDERTYPE	8009
#define	ERR_UTI_UNKNOWN_MARKET		8010
#define	ERR_UTI_UNMATCHED_MARKET	8011
#define	ERR_UTI_FAIL_LOADTRADEDLL	8012
#define	ERR_UTI_FAIL_GETTYPE		8013
#define	ERR_UTI_FAIL_READSET		8014
#define	ERR_UTI_FAIL_GETINFO		8015
#define	ERR_UTI_FAIL_MODISET		8016
#define	ERR_UTI_EMPTY_DLLPATH		8017
#define	ERR_UTI_EMPTY_INIPATH		8018
#define	ERR_UTI_UNKNOWN_DLLTYPE		8019
#define	ERR_UTI_ALREADY_BEGIN		8500
#define	ERR_UTI_ALREADY_END			8501


//9001-9999    ENGAPI
#define ERR_ENG_ALGHAVEREGISTED		9001          //ͬ���͡�ͬGUID���㷨�Ѿ�ע��
#define ERR_ENG_ALGNOTFOUND			9002		  //�㷨δ�ҵ�


#define ERR_ENG_SESSION_BEGIN		9500		  //Session���ֵ�����.



/**
����������Ϣ.
*/
struct /*AFX_EXT_CLASS*/ ErrorDefine
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
	static LPCTSTR GetErrorFromCode(DWORD dwError); \
	virtual CString GetLastError(); \
protected:\
	virtual void SetLastError(DWORD dwError);\
	virtual void SetLastDynamicError(DWORD dwError,CString strError);\






#define ON_ERROR(code,str) \
{code,str},\



#define BEGIN_ERROR_MAP(classname) \
	void classname::SetLastDynamicError(DWORD dwError,CString strError)\
	{\
		ASSERT(strError.GetLength()< (2<<16));\
		ASSERT(AfxCheckMemory());\
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
	LPCTSTR classname::GetErrorFromCode(DWORD dwError)			\
	{	\
		for(int i=0;s_ErrorDefineArray[i].nErrorCode!=0;++i) \
		{ \
			if(s_ErrorDefineArray[i].nErrorCode == dwError) \
			{ \
				return s_ErrorDefineArray[i].strError; \
			} \
		} \
		return _T("");\
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
	{\
		ON_ERROR(ERR_OUTOFMEMORY,		"�ڴ治��")\
		ON_ERROR(ERR_NULLPOINTER,		"ָ��Ϊ��")\
		ON_ERROR(ERR_INVALIDHANDLER,		"�Ƿ����")\
		ON_ERROR(ERR_NOT_CONNECT,		"δ����")\
		ON_ERROR(ERR_NOT_LOGINED,		"��δ��¼")\
		ON_ERROR(ERR_DISCONNECTED,		"�ѶϿ�")\
		ON_ERROR(ERR_NET_TIMEOUT,		"���糬ʱ")









//////////////////////////////////////////////////////////////////////////////////



#define END_ERROR_MAP() \
{0,_T("")}};




#endif //__COMMONERRORDEFINE_H__
