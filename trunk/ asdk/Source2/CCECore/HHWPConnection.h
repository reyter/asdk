/**
* @Copyright 深圳市创真科技有限公司
* @Brief     管理连接信息
*
*/

#pragma once
#ifndef _HHWPCONNECTION_H_
#define _HHWPCONNECTION_H_


#ifndef _LIST_
#include <list>
#endif

#include "Channel.h"




#pragma pack(push,4)


struct WSABUFPLUS
{
	WSABUF wsabuf;
	
	//static int nCount_;
	WSABUFPLUS(const void* pData,int nLength)
	{
		wsabuf.len = nLength;
		wsabuf.buf = new char[nLength];
		memcpy(wsabuf.buf,pData,nLength);		
	}
	WSABUFPLUS(int nLength)
	{
		wsabuf.len = nLength;
		wsabuf.buf = new char[nLength];
		memset(wsabuf.buf,0,nLength);		
	}
	~WSABUFPLUS()
	{
		if(wsabuf.buf)
			delete []wsabuf.buf;
	}
};
#pragma pack(pop)



//用于重叠IO.
struct OVERLAPPLUS
{
	OVERLAPPED _olp;

	//操作类型 IOTYPE, 并可扩展.
	int     ntype;	

	LPVOID        nUserDefineType;

	WSABUFPLUS* pBuff;	//用于收发数据的地址.
	OVERLAPPLUS(int nType,WSABUFPLUS* pBuff)
	{
		nUserDefineType =0;
		memset(&_olp,0,sizeof(_olp));
		this->ntype = nType;		
		this->pBuff = pBuff;
	}
	~OVERLAPPLUS()
	{
		if(pBuff)
			delete pBuff;	//删除其地址.
	}
};



//缓冲
class CSendBuffer:public std::list<void*>
{
protected:
	CRITICAL_SECTION m_cs;
public:	
	CSendBuffer();
	~CSendBuffer();
	WSABUFPLUS*   GetSendData();		//用于收数据.
	bool		  AddSendData(void* pData,int nLength);	
};


class CCCEProcessor;
/**
* 为保证包的顺序到达，发完一个包后，才请允许发后面的包。
* 接收也是如此，暂不考虑组包问题。 
*
*/
class AFX_EXT_CLASS CHHWPConnection
{
public:
	CHHWPConnection(SOCKET sockPeer,CChannel* pChannel);	//创建服务应用。

	CHHWPConnection(SOCKET sockPeer,CCCEProcessor* pProcessor);	//创建客户端应用.

	virtual ~CHHWPConnection(void);

	//发送数据.
	//注意：当发送数据包太大时，需要拆包处理，该处不处理。
	enum {
		SD_FLAG_SEND_THEN_CLOSE	=1	//发送完成后关闭套接字.
	};

	bool SendData(const void* pData,int nLength,int nFlags=0);	

	void NotifyExit();


	void GetConnInfo(struct CONNECT_INFO_SHOW* pInfo);
	
	long GetRefCount();


	/**
	* 设置接收缓存.
	* @param nSize 如果接收缓存大于8k,则设置为指定的值。否则，则自动设置为8k.
	* 
	*/
	void SetRecvBufferSize(int nSize);


	void GetPeerAddr(sockaddr_in& addr);

	void GetThisAddr(sockaddr_in& addr);



	CCCEProcessor* m_pProcessor;

private:
	enum {
		WSASendData_FUN=0,	//发送功能
		WSARecvData_FUN=1,	//接收功能
		
		MAX_FUN_SIZE	//最大的，在之前插入，不能在之后插入.
	};
	
	std::bitset<CHHWPConnection::MAX_FUN_SIZE>	m_bsErrorFlag;

	//void WSASendData();

protected:
	SOCKET  m_hSockets;						
	volatile long     m_nRefCount;		//正在发送计数请求
	

	
	//CSendBuffer		   m_bufferSend;		//发送缓冲区.

	bool m_bError;
	

	friend class CHHWPIOCP;
	

	

	//Add by wli 2009-02-26 使收发同步。
	//int  m_nSendBufferCount;	//发送缓冲数，
	//bool m_bCanNotGetRecvBuff;

	CONNECT_INFO   m_connInfo;


	//friend class CWinThread_ConnManager;


	//全双工.
	CRITICAL_SECTION  m_csSend;
	//CRITICAL_SECTION  m_csRecv;

public:
	CChannel* m_pChannel;	//父类的通道。

private:

	void Init();

	void SetErrorFlag(int nWhere,bool bFromIOCP=false);

	void PostDeleteThisMessage();

	bool m_bDeleteProcessor;

	bool IsError();

	void SetInnerIpAddr(in_addr& addr);


	static OVERLAPPLUS* GetOverlapPlus(int nType,WSABUFPLUS* pBuff);
	static void ReleaseOverlapPlus(OVERLAPPLUS* pOverlapplus);
	static void SendRegisterUserCommand(int nCommand,LPVOID lParam);


	void OnError(OVERLAPPLUS* lpOverlapped);			//出错处理

	UINT OnUserDefine(OVERLAPPLUS* pOverlapPlus);


	//void OnExit(DWORD numBerOfBytes,OVERLAPPLUS* lpOverlapped);

	int WSASendData(const void* pData,int nLength,int nFlags=0);
	//@param lpOw 使用已经分配好的内存，不再从新分配内存
	int WSARecvData(OVERLAPPLUS* lpOw=NULL);



	//当接收到数据时进行的操作。
	UINT OnReceiveData(DWORD numBerOfBytes,OVERLAPPLUS* lpOverlapped);

	UINT OnSendDataFin(DWORD numBerOfBytes,OVERLAPPLUS* lpOverlapped);	//发送数据完成

	friend class CCCEProcessor;
	friend class CHHWPIOCP;

private:
	int m_nRecvBufferSize;
};



#endif //_HHWPCONNECTION_H_