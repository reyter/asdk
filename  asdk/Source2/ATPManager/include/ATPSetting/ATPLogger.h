 /**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 ��־��¼��.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-1		��ΰ		 ����
-------------------------------------------------------------
*/
#pragma once



#include <fstream>
using namespace std;

typedef struct AFX_EXT_CLASS __tagLogFileHead
{
	int nMagicNumber;		//ħ����0x5d
	int nVersion;			//�汾��1
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
* ��־��¼��
*/
class AFX_EXT_CLASS CATPLogger
{
public:	
	virtual ~CATPLogger();

	/**
	��־����
	*/
	enum ATP_LOG_LEVEL
	{
		/**
		������Ϣ
		*/
		LOG_LEVEL_DEBUG,			
		/**
		��ͨ��Ϣ
		*/
		LOG_LEVEL_INFO,				

		/**
		������Ϣ
		*/
		LOG_LEVEL_WARNING,			

		/**
		������Ϣ
		*/
		LOG_LEVEL_ERROR,

		/**
		ϵͳ����
		*/
		LOG_LEVEL_SYSTEM
	};

	/**
	������־��¼����.
	ֻ�и��ڻ���ڴ˼������־�Żᱻ��¼
	@param	nLevel    ��־����
	*/
	static void SetLogLevel(int nLevel=LOG_LEVEL_INFO);
	
	/**
	��¼��־,ֻ��¼�����Ѿ����õ���־�������־.
	@param nLevel	��־����
	@param strLog	��־����	
	*/	
	static void Log(const char* strLog,int nLevel= LOG_LEVEL_INFO);

	/**
	��¼��־,ֻ��¼�����Ѿ����õ���־�������־.
	@param nLevel		��־����
	@param strFormat	��־���ݸ�ʽ.ͬprintf��
	*/ 	
	static void Log(int nLevel,const char* strFormat,...);

	static CString GetLogFileName();


	/**
	д˽����־.д����������־�ļ�����.
	*/ 	
	void  PrivateLog(const char* strLog,int nLevel = LOG_LEVEL_INFO);


	/**
	��¼��־,ֻ��¼�����Ѿ����õ���־�������־.
	@param nLevel		��־����
	@param strFormat	��־���ݸ�ʽ.ͬprintf��
	*/ 	
	void PrivateLog(int nLevel,const char* strFormat,...);

	/**
	����˽����־����.
	*/ 	
	void  SetPrivateLogLevel(int nLevel=LOG_LEVEL_INFO);


protected:

	CATPLogger(CString strLogName);


	/**
	��־����
	*/
	int m_nLogLevel;

	/**
	���ܶ���̼߳�¼��־����ˣ���Ҫ�ٽ���.
	*/
	CRITICAL_SECTION m_csLog;

	static CATPLogger* s_pLogger;


	static CATPLogger* GetInstance();

	void LogImpl(const char* strLog,int nLevel);

	char* GetBytes(const char* strLog,int nLevel,int& nLength,int& nCheck);

protected:
	/**
	��־�����
	*/ 	
	ofstream m_ofsLog;

	int m_nLogFpt;

	CString  m_strLogFileName;
	
	LOGFILEHEAD	m_fileHead;

	friend class CAlgoManager;
};
