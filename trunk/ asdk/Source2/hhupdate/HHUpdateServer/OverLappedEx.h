#pragma once
#include "..\\include\\Compress\\zconf.h"
enum IO_TYPE {
	IO_TYPE_ACCEPT,
	IO_TYPE_READ,
	IO_TYPE_WRITE,
	IO_TYPE_UNKNOWN
};

enum REQUEST_TYPE{
	RE_TYPE_README=10101,	//����readme.txt
	RE_TYPE_XML,			//����xml�ļ��б�xml
	RE_TYPE_HH,				//����HHѹ���ļ�
};
#pragma pack(push)
#pragma pack(1)
typedef struct
{
	int nFlag;//������
	char szUserID[16];
	char szAppID[16];			// APPID
	char szVersion[16];       // �汾��
	char szFileName[MAX_PATH];//�ļ���
}_tagRequest;

typedef struct 
{
	char szAllDataLength[9];		//�ļ��ܳ���. 
	Byte btBuff[MAX_BUF_SIZE];		//��������.
	char szBuffLen[9];				//�������ݳ���.
	char szFileType[9];				//�ļ����� 10101:readme   10102:xml�ļ�    10103:.hh�ļ�
	char szFlag[9];					//1����   ����0
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
