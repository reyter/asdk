 /**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 日志记录器.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-1		李伟		 创建
-------------------------------------------------------------
*/
#pragma once



#include <fstream>
using namespace std;

typedef struct AFX_EXT_CLASS __tagLogFileHead
{
	int nMagicNumber;		//魔法数0x5d
	int nVersion;			//版本号1
	int nHeadLength;		//
	int nFileLength;
	int nMessages;
	int nCheck;
	__tagLogFileHead()
	{
		memset(this,0,sizeof(*this));
		nMagicNumber = 0x5d;
		nVersion = 1;
		nHeadLength = sizeof(*this);		
	}
}LOGFILEHEAD;
//
//struct AFX_EXT_CLASS LogInfo
//{
//	SYSTEMTIME time;
//	int        nLevel;
//	int        nDataLength;
//	char*      pData;
//
//	LogInfo()
//	{
//		memset(this,0,sizeof(this));
//	}
//	~LogInfo()
//	{
//		if(pData)
//			delete []pData;
//	}
//};


/**
* 日志记录器
*/
class AFX_EXT_CLASS CATPLogger
{
public:	
	virtual ~CATPLogger();

	/**
	日志级别
	*/
	enum ATP_LOG_LEVEL
	{
		/**
		调试信息
		*/
		LOG_LEVEL_DEBUG,			
		/**
		普通信息
		*/
		LOG_LEVEL_INFO,				

		/**
		警告信息
		*/
		LOG_LEVEL_WARNING,			

		/**
		出错信息
		*/
		LOG_LEVEL_ERROR,

		/**
		系统级别
		*/
		LOG_LEVEL_SYSTEM
	};

	/**
	设置日志记录级别.
	只有高于或等于此级别的日志才会被记录
	@param	nLevel    日志级别
	*/
	static void SetLogLevel(int nLevel=LOG_LEVEL_INFO);
	
	/**
	记录日志,只记录高于已经设置的日志级别的日志.
	@param nLevel	日志级别
	@param strLog	日志内容	
	*/	
	static void Log(const char* strLog,int nLevel= LOG_LEVEL_INFO);

	/**
	记录日志,只记录高于已经设置的日志级别的日志.
	@param nLevel		日志级别
	@param strFormat	日志内容格式.同printf。
	*/ 	
	static void Log(int nLevel,const char* strFormat,...);

	static CString GetLogFileName();


	/**
	写私有日志.写到单独的日志文件里面.
	*/ 	
	void  PrivateLog(const char* strLog,int nLevel = LOG_LEVEL_INFO);


	/**
	记录日志,只记录高于已经设置的日志级别的日志.
	@param nLevel		日志级别
	@param strFormat	日志内容格式.同printf。
	*/ 	
	void PrivateLog(int nLevel,const char* strFormat,...);

	/**
	设置私有日志级别.
	*/ 	
	void  SetPrivateLogLevel(int nLevel=LOG_LEVEL_INFO);


protected:

	CATPLogger(CString strLogName);


	/**
	日志级别
	*/
	int m_nLogLevel;

	/**
	可能多个线程记录日志，因此，需要临界区.
	*/
	CRITICAL_SECTION m_csLog;

	static CATPLogger* s_pLogger;


	static CATPLogger* GetInstance();

	void LogImpl(const char* strLog,int nLevel);

	char* GetBytes(const char* strLog,int nLevel,int& nLength,int& nCheck);

protected:
	/**
	日志输出器
	*/ 	
	ofstream m_ofsLog;

	int m_nLogFpt;

	CString  m_strLogFileName;
	
	LOGFILEHEAD	m_fileHead;

	friend class CAlgoManager;
};
