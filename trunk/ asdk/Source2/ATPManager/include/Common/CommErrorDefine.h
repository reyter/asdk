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
#ifndef _COMMONERRORDEFINE_H__
#define _COMMONERRORDEFINE_H__

//1-100  内存保留
#define ERR_OUTOFMEMORY		1
#define ERR_NULLPOINTER		2
#define ERR_INVALIDHANDLER  3

//101-200 通讯保留
#define	ERR_NOT_CONNECT		101
#define	ERR_NOT_LOGINED		102
#define ERR_DISCONNECTED	103
#define ERR_NET_TIMEOUT		104

//1001-2000		TDF
#define ERR_TDF_NOT_FOUND_RESULT 	1001			//未找到相应的结果
#define ERR_TDF_NOT_STRAT_SNAP	 	1002			//没有开启快照
#define ERR_TDF_WROUNG_MARKET_CODE	1003			//错误的证券代码
#define ERR_TDF_RESULT_NOT_CORRECT	1004			//结果中有错误
#define ERR_TDF_NOT_ADD_SERVER		1005			//未添加TDF服务器
#define ERR_TDF_SOMEDATA_WRONG		1006			//有些数据是错误的
#define ERR_TDF_FINDMARKETDATA_FAIL	1007			//查找获取行情时失败

//2001-3000		TDB
#define ERR_TDB_NETBUSY             2001			//网络资源被占用
#define ERR_TDB_NOTSUPPORTMARKET	2002			//不支持查询的市场
#define ERR_TDB_NOT_PEERADDR		2003			//取对方地址失败
#define ERR_TDB_NO_DATA	            2004			//没有数据
#define ERR_TDB_EZF_ERROR			2005			//易编公式有错误
#define ERR_TDB_EZF_DELFAIL			2006			//删除指标失败

//3001-3999		LOG
#define ERR_LOG_CREATEINDEXFILE_FAIL		3001	// 创建或打开索引文件失败
#define ERR_LOG_CREATELOGFILE_FAIL			3002	// 创建或打开日志文件失败
#define ERR_LOG_INDEXFILE_NOTFOUND			3003	// 追加索引失败,索引文件没有找到
#define ERR_LOG_RECORD_NOT_FOUND			3004	// 日志记录没有找到	
#define ERR_LOG_NOT_CLASS					3005	// 日志分类不存在
#define ERR_LOG_FILENAME_TOO_LONG			3006	// 文件名超出了256个字符	
#define ERR_LOG_RECORD_TOO_MORE				3007	// 记录太多了
#define ERR_LOG_FILECRC_WRONG				3008	// 文件CRC校验错误
#define	ERR_LOG_RECORDCRC_WRONG				3009	// 记录CRC校验错误
#define ERR_LOG_UNKNOWN					3010	//	未知错误
//5001-6000		ALG

//6001-7000		TTD
#define ERR_TTD_CREATE_EVETN		6001	//创建事件错误.
#define ERR_TTD_FUNCTION_TIMEOUT	6002	//函数执行超时.
#define ERR_TTD_OPENFILE_FAIL		6003	//打开文件失败
#define ERR_TTD_DYNAMICKEY_FAIL		6004	//获取动态密钥失败
#define ERR_TTD_SNAPNOTFOUND		6005	//内存快照中没有找到
#define ERR_TTD_NOALGOONSERVER			6006	//服务器上没有算法
#define ERR_TTD_RELEASEMEM			6007		//释放内存出错
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
#define ERR_ENG_ALGHAVEREGISTED		9001          //同类型、同GUID的算法已经注册
#define ERR_ENG_ALGNOTFOUND			9002		  //算法未找到


#define ERR_ENG_SESSION_BEGIN		9500		  //Session出现的问题.



/**
错误描述信息.
*/
struct /*AFX_EXT_CLASS*/ ErrorDefine
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
		ON_ERROR(ERR_OUTOFMEMORY,		"内存不足")\
		ON_ERROR(ERR_NULLPOINTER,		"指针为空")\
		ON_ERROR(ERR_INVALIDHANDLER,		"非法句柄")\
		ON_ERROR(ERR_NOT_CONNECT,		"未连接")\
		ON_ERROR(ERR_NOT_LOGINED,		"尚未登录")\
		ON_ERROR(ERR_DISCONNECTED,		"已断开")\
		ON_ERROR(ERR_NET_TIMEOUT,		"网络超时")









//////////////////////////////////////////////////////////////////////////////////



#define END_ERROR_MAP() \
{0,_T("")}};




#endif //__COMMONERRORDEFINE_H__
