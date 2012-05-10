/**
* @Copyright �����д���Ƽ����޹�˾
* @Brief     ����������Ϣ
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



//�����ص�IO.
struct OVERLAPPLUS
{
	OVERLAPPED _olp;

	//�������� IOTYPE, ������չ.
	int     ntype;	

	LPVOID        nUserDefineType;

	WSABUFPLUS* pBuff;	//�����շ����ݵĵ�ַ.
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
			delete pBuff;	//ɾ�����ַ.
	}
};



//����
class CSendBuffer:public std::list<void*>
{
protected:
	CRITICAL_SECTION m_cs;
public:	
	CSendBuffer();
	~CSendBuffer();
	WSABUFPLUS*   GetSendData();		//����������.
	bool		  AddSendData(void* pData,int nLength);	
};


class CCCEProcessor;
/**
* Ϊ��֤����˳�򵽴����һ�����󣬲�����������İ���
* ����Ҳ����ˣ��ݲ�����������⡣ 
*
*/
class AFX_EXT_CLASS CHHWPConnection
{
public:
	CHHWPConnection(SOCKET sockPeer,CChannel* pChannel);	//��������Ӧ�á�

	CHHWPConnection(SOCKET sockPeer,CCCEProcessor* pProcessor);	//�����ͻ���Ӧ��.

	virtual ~CHHWPConnection(void);

	//��������.
	//ע�⣺���������ݰ�̫��ʱ����Ҫ��������ô�������
	enum {
		SD_FLAG_SEND_THEN_CLOSE	=1	//������ɺ�ر��׽���.
	};

	bool SendData(const void* pData,int nLength,int nFlags=0);	

	void NotifyExit();


	void GetConnInfo(struct CONNECT_INFO_SHOW* pInfo);
	
	long GetRefCount();


	/**
	* ���ý��ջ���.
	* @param nSize ������ջ������8k,������Ϊָ����ֵ���������Զ�����Ϊ8k.
	* 
	*/
	void SetRecvBufferSize(int nSize);


	void GetPeerAddr(sockaddr_in& addr);

	void GetThisAddr(sockaddr_in& addr);



	CCCEProcessor* m_pProcessor;

private:
	enum {
		WSASendData_FUN=0,	//���͹���
		WSARecvData_FUN=1,	//���չ���
		
		MAX_FUN_SIZE	//���ģ���֮ǰ���룬������֮�����.
	};
	
	std::bitset<CHHWPConnection::MAX_FUN_SIZE>	m_bsErrorFlag;

	//void WSASendData();

protected:
	SOCKET  m_hSockets;						
	volatile long     m_nRefCount;		//���ڷ��ͼ�������
	

	
	//CSendBuffer		   m_bufferSend;		//���ͻ�����.

	bool m_bError;
	

	friend class CHHWPIOCP;
	

	

	//Add by wli 2009-02-26 ʹ�շ�ͬ����
	//int  m_nSendBufferCount;	//���ͻ�������
	//bool m_bCanNotGetRecvBuff;

	CONNECT_INFO   m_connInfo;


	//friend class CWinThread_ConnManager;


	//ȫ˫��.
	CRITICAL_SECTION  m_csSend;
	//CRITICAL_SECTION  m_csRecv;

public:
	CChannel* m_pChannel;	//�����ͨ����

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


	void OnError(OVERLAPPLUS* lpOverlapped);			//������

	UINT OnUserDefine(OVERLAPPLUS* pOverlapPlus);


	//void OnExit(DWORD numBerOfBytes,OVERLAPPLUS* lpOverlapped);

	int WSASendData(const void* pData,int nLength,int nFlags=0);
	//@param lpOw ʹ���Ѿ�����õ��ڴ棬���ٴ��·����ڴ�
	int WSARecvData(OVERLAPPLUS* lpOw=NULL);



	//�����յ�����ʱ���еĲ�����
	UINT OnReceiveData(DWORD numBerOfBytes,OVERLAPPLUS* lpOverlapped);

	UINT OnSendDataFin(DWORD numBerOfBytes,OVERLAPPLUS* lpOverlapped);	//�����������

	friend class CCCEProcessor;
	friend class CHHWPIOCP;

private:
	int m_nRecvBufferSize;
};



#endif //_HHWPCONNECTION_H_