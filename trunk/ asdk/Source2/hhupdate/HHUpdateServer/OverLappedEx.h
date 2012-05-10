#pragma once
#include "..\\include\\Compress\\zconf.h"
enum IO_TYPE {
	IO_TYPE_ACCEPT,
	IO_TYPE_READ,
	IO_TYPE_WRITE,
	IO_TYPE_UNKNOWN
};

enum REQUEST_TYPE{
	RE_TYPE_README=10101,	//请求readme.txt
	RE_TYPE_XML,			//请求xml文件列表xml
	RE_TYPE_HH,				//请求HH压缩文件
};
#pragma pack(push)
#pragma pack(1)
typedef struct
{
	int nFlag;//请求标记
	char szUserID[16];
	char szAppID[16];			// APPID
	char szVersion[16];       // 版本号
	char szFileName[MAX_PATH];//文件名
}_tagRequest;

typedef struct 
{
	char szAllDataLength[9];		//文件总长度. 
	Byte btBuff[MAX_BUF_SIZE];		//接收内容.
	char szBuffLen[9];				//接收内容长度.
	char szFileType[9];				//文件类型 10101:readme   10102:xml文件    10103:.hh文件
	char szFlag[9];					//1结束   其余0
}_tagAnswer;

#pragma pack(pop)
class COverLappedEx
{
public:
	COverLappedEx(void);
	COverLappedEx(IO_TYPE ioType);
	~COverLappedEx(void);
	
	

public:
	OVERLAPPED m_OLap;
	IO_TYPE m_IOType;
	_tagRequest m_nRequestBuff;
	_tagAnswer m_AnswerBuff;
	
};
