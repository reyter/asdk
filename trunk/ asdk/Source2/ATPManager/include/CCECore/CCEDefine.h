/**
* @Copyright �����д���Ƽ����޹�˾(www.hh.com.cn)
* @System	 ͨ��ͨ�ſ�(Common Communication Environment Core)
* @Brief	 ͨ�ö���
* @Author	 wli
* @Date      2010-10-21
*/

#pragma once

#ifndef __CCEDEFINE_H_
#define __CCEDEFINE_H_

#ifndef _LIST_
#include <list>
using namespace std;
#endif

#ifndef _MAP_
#include <map>
using namespace std;
#endif

#ifndef _BITSET_
#include <bitset>
using namespace std;
#endif

#ifndef _ALGORITHM_
#include <algorithm>
using namespace std;
#endif


/**	
*  ��������
*/
enum CCE_PROXYTYPE
{
		PROXYTYPE_NOPROXY=0,	//��ʹ�ô���
		PROXYTYPE_SOCKS4=1,		//SOCK4
		PROXYTYPE_SOCKS4A=2,	//SOCK4A
		PROXYTYPE_SOCKS5=3,		//SOCK5
		PROXYTYPE_HTTP11=4		//HTTP1.1
};

/**
*	��������
*/
struct CCE_PROXYDATA 
{
	CCE_PROXYTYPE  iProxyType;		//ʹ�õĴ�������.
	char szProxyHost[32];	//�����ַ
	int  iProxyPort;		//����˿�
	char szProxyUser[32];	//�����û���
	char szProxyPass[32];	//��������	
};


/**
*   ����״̬ 
*/
enum CCE_CONN_STATUS
{
	CCE_CONN_STATUS_OFFLINE=0,	//����
	CCE_CONN_STATUS_ONLINE=1	//����
};




#define CCE_CREATE_CONNECTION	(10000)	//��������ָ��.




extern "C"
{
	//CCE����־��¼����ԭ��.
	typedef void (CALLBACK* CCE_LOG_FUN)(const char *pLog,LPVOID lParam);
}



class CHHWPConnection;

//������Ϣ
struct CONNECT_INFO
{
	in_addr	addrFromOuter;		//�Է�������ַ.
	in_addr addrFromInner;		//�Է�������ַ.
	time_t	connTime;			//���ӽ���ʱ��.
	__int64	sendBytes;			//�����ֽ���
	__int64	recvBytes;			//�����ֽ���
	CHHWPConnection*  pConnection;

};

//�����б���ʾ�Ľṹ.
struct CONNECT_INFO_SHOW
{
	char  clientAddr[64];	//�ͻ�����ʾ��ַ.
	char  connectTime[24];	//�ͻ���¼ʱ�� YYYY-MM-DD HH:MM:SS
	__int64	sendBytes;			//�����ֽ���
	__int64	recvBytes;			//�����ֽ���
	CHHWPConnection*  pConnection;

	CONNECT_INFO_SHOW& operator=(CONNECT_INFO& info)
	{
		sprintf(clientAddr,"%d.%d.%d.%d<-%d.%d.%d.%d",
			info.addrFromOuter.S_un.S_un_b.s_b1,
			info.addrFromOuter.S_un.S_un_b.s_b2,
			info.addrFromOuter.S_un.S_un_b.s_b3,
			info.addrFromOuter.S_un.S_un_b.s_b4,
			info.addrFromInner.S_un.S_un_b.s_b1,
			info.addrFromInner.S_un.S_un_b.s_b2,
			info.addrFromInner.S_un.S_un_b.s_b3,
			info.addrFromInner.S_un.S_un_b.s_b4);	//��ʽ��IP��ַ��ʾ��

		CTime timecc(info.connTime);
		sprintf(connectTime,"%04d-%02d-%02d %02d:%02d:%02d",
			timecc.GetYear(),
			timecc.GetMonth(),
			timecc.GetDay(),
			timecc.GetHour(),
			timecc.GetMinute(),
			timecc.GetSecond());

		this->sendBytes = info.sendBytes;
		this->recvBytes = info.recvBytes;
		this->pConnection = info.pConnection;

		return *this;        
	}

};


#pragma  pack(push,8)

enum __CHANNEL_STATE_
{
	ST_OPENING,				//����������
	ST_CLOSE,				//�ֶ��ر�
	ST_CANNOTCONN,			//�������޷��������У���Ҫ����	
	ST_TRYOPEN,
	ST_CANNOTOPEN,			//�޷���
	ST_UNINIT				//��δ��ʼ��
};

struct CHANNEL_INFO_CORE
{
	char szChannelName[32];				//ͨ������
	USHORT  nLocalPort;	
	CRuntimeClass* pSvrRunTimeClass;	//����ʱ֧����Ϣ.
	//bool bOpen;						//�Ƿ�Ϊ��״̬����ʼ��ʱ���Ƿ�򿪣����ļ����غ��Ƿ�򿪡�
	int nChannelStatus;
	LPVOID lParam;						//Add by wli 2010-10-26,wli

	CHANNEL_INFO_CORE()
	{
		nChannelStatus = ST_UNINIT;
	}
};
#pragma  pack(pop)


typedef struct  _tagChannelInfo
{
	int  nChannelStatus;	//״̬���������رգ��ж�(��Ҫ����)��
	char szChanName[32];	//ͨ����	
	double  client2server;	//�ͻ��˵��������ֽ���M
	double  server2client;	//���������ͻ����ֽ���M
	LPVOID	  pChannel;	//ָ�������
	INT_PTR       nConnect;
	INT_PTR		  nMaxConnect;	//�����������
}HHWP_CHANNELINFO;


//CCECore lib ר��.
#ifdef _CCECORE_LIB_
extern CCE_LOG_FUN   g_pCCELogFun;
extern LPVOID		g_pCCELogParam;
extern void AppendLog(const char* pLog);
#endif 

#endif	//__CCEDEFINE_H_