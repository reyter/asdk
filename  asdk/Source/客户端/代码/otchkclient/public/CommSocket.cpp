// CommSocket.cpp : 实现文件
//
#include "stdafx.h"
#include "CommSocket.h"
#include "ProxySocket.h"
#include "Commfunc.h"
#include "Data.h"
#include "../Winunit/IUserWin.h"

// CCommSocket
CCommSocket * gpCommSocket;
int SendFunc(IUserWin * c_pWnd,char * c_pData,int c_nLen,char * c_pRetBuf,int c_nMaxLen,bool c_bWaitReturn)
{
	int nRet = c_nLen;
	nRet = gpCommSocket->SendData(c_pData,c_nLen,c_bWaitReturn,c_pRetBuf,c_nMaxLen);
	return nRet;
}

int g_iStep = 0;
CCommSocket::CCommSocket()
: m_uiRecvLen(0)
, m_uiPackLen(0)
, m_bRecving(false)
, m_usState(0)
{
	m_iSocketHeart = 0;
	m_socket = INVALID_SOCKET;
	m_pRecvBuf = (char *)malloc(MAX_RECV_LEN);
	m_pPackData = (char *)malloc(MAX_RECV_LEN);
	m_usWaitRecvSeq = 0;
	m_hRecvEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	SetAppFunc(SendFunc,NULL);
	//m_hThreadRecv = CreateThread(NULL,0,RecvRoutine,(LPVOID)this,0,NULL);
}

CCommSocket::~CCommSocket()
{
	CloseHandle(m_hRecvEvent);
	free(m_pRecvBuf);
	free(m_pPackData);
}


// CCommSocket 成员函数
int g_iHead = 0;

bool CCommSocket::ClearSocketHeart()
{
	m_iSocketHeart = 0;
	return true;
}

bool CCommSocket::SetSocketHeart(int c_iSecond)
{
	m_iSocketHeart += c_iSecond;
	if (m_iSocketHeart > 12)
	{
		m_iSocketHeart = 0;
		return false;
	}
	return true;
}

SOCKET CCommSocket::ConnectTo(CString c_strHost, int c_nPort)
{
	char acHost[32];
	acHost[30] = 0;
	unicodeToAscii(c_strHost,acHost,30);
	return ConnectTo(acHost,c_nPort);
}

SOCKET CCommSocket::ConnectTo(char * c_pHost, int c_nPort)
{		
	int nSock = 0;
	nSock = socket(AF_INET,SOCK_STREAM,0);
	if (nSock > 0)
	{
		int timeout ;
		timeout = 5 * 1000 ; // 5秒		
		setsockopt(nSock , SOL_SOCKET , SO_SNDTIMEO , (char *)&timeout ,  sizeof(timeout)) ;
		timeout = 20 * 1000 ; // 5秒
		setsockopt(nSock , SOL_SOCKET , SO_RCVTIMEO , (char *)&timeout ,  sizeof(timeout)) ;
		int nRet = CProxySocket::_instance->ConnectByHostInfo(nSock,c_pHost,c_nPort,m_pproxyOption);			
		if (nRet < 0)
			nSock = INVALID_SOCKET;
	}
	m_socket = nSock;
	strcpy(m_acHost,c_pHost);
	m_nPort = c_nPort;
	return (SOCKET)nSock;
}

void CCommSocket::Disconnect()
{
	if (m_socket != INVALID_SOCKET)
	{
		shutdown(m_socket,SD_BOTH);
		closesocket(m_socket);
	}
	m_socket = INVALID_SOCKET;
	m_usState = 0;//0未连接，1已经连接，-1出错
	m_uiRecvLen = 0;
	m_uiPackLen = 0;
	m_iSocketHeart = 0;
	::PostMessage(::AfxGetMainWnd()->GetSafeHwnd(),WM_CONNECT_SUCCESS,0,0);
}


bool CCommSocket::RecvDataOld(unsigned short &c_usType)
{
///-	char acBuf[4096];
	int nn = 0;
	m_uiRecvLen = 0;
	while(true)
	//if (true)
	{
		int iLen;
		int iPackLen;
		int timeout = 6000; //3s

		setsockopt(m_socket,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout));

		setsockopt(m_socket,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));

		//int ticka,tickb;
		while(m_uiRecvLen < 8)
		{
			iLen = recv(m_socket,m_pRecvBuf + m_uiRecvLen,8,0);
			if (iLen == SOCKET_ERROR)
			{
				int err = ::WSAGetLastError();
				if (err > 0 && err != WSAEWOULDBLOCK && err != WSAETIMEDOUT)
				{
					Disconnect();					
					return false;
				}
			}
			else
				m_uiRecvLen += iLen;
		}

		if (strnicmp(m_pRecvBuf,"http",4) == 0)//是http协议，需要跳过http头
		{
			iLen = recv(m_socket,m_pRecvBuf,112,0);
			if (iLen < 112)
			{
				Disconnect();				
				return false;
			}
			char * pEnd = strstr(m_pRecvBuf,"\r\n\r\n");
			if (pEnd == NULL)
			{
				Disconnect();				
				return false;
			}
			int nEnd = pEnd - m_pRecvBuf + 4;
			memcpy(m_pRecvBuf,pEnd + 4,iLen - nEnd);
			m_uiRecvLen = iLen - nEnd;
			iLen = recv(m_socket,m_pRecvBuf + m_uiRecvLen,8-m_uiRecvLen,0);
			if (iLen < 8-m_uiRecvLen)
			{				
				Disconnect();				
				return false;
			}
			m_uiRecvLen += iLen;
		}

		SCommHead * pHead = (SCommHead *)(m_pRecvBuf);
		if (pHead->m_head.GetVersion() != 3 || pHead->m_head.GetLength() > MAX_RECV_LEN - 8 || pHead->m_head.GetLength() <= 0 )
		{
			Disconnect();			
			return false;
		}
		iPackLen = pHead->m_head.GetLength() + 8;
		while(m_uiRecvLen < iPackLen)
		{
			iLen = recv(m_socket,m_pRecvBuf + m_uiRecvLen,iPackLen - m_uiRecvLen,0);
			if (iLen == SOCKET_ERROR || iLen == 0)
			{
				int err = ::WSAGetLastError();
				if (err > 0 && err != WSAEWOULDBLOCK && err != WSAETIMEDOUT)
				{
					Disconnect();					
					return false;
				}
				else
					continue;
			}
			m_uiRecvLen += iLen;
		}
		if (m_uiRecvLen == iPackLen)
		{			
			memcpy(m_pPackData,m_pRecvBuf,m_uiRecvLen);//复制所有的数据
			m_uiRecvLen -= iPackLen;

			unsigned short us,usType;
			us = *(unsigned short *)(m_pPackData + 2);
			usType = *(unsigned short *)(m_pPackData + 8);
#ifdef _DEBUG
			if (true)//usType == 33108)// && usType != 3)//|| usType == 3017 )//|| usType == 3)//usType == 3013 || usType == 3014 || usType == 5 || usType == 6 || usType == 7)
			{
			FILE *f;
			char aczFile[100];
			//sprintf(aczFile,"c:\\test\\%d.%.3d.rcv.%d",nn++,us,usType);
			sprintf(aczFile,"c:\\test\\%d.rcv.%d",us,usType);
			f = fopen(aczFile,"wb");
			if (f)
			{
				fwrite((void *)m_pPackData,1,iPackLen,f);
				fclose(f);
			}
			}
#endif			
			ClearSocketHeart();/*
							   m_pData->m_lockData.lock();
							   m_pData->PutRep(m_pPackData,iPackLen);
							   m_pData->m_lockData.unlock();*/
			c_usType = usType;
/*
			if (m_usWaitRecvSeq > 0)
				if (pHead->m_head.SerialNo == m_usWaitRecvSeq)
				{
					m_usWaitRecvSeq = 0;
					SetEvent(m_hRecvEvent);
				}*/
				//return true;
				m_nPackLen = iPackLen;
				if (m_usWaitRecvSeq > 0 && pHead->m_head.SerialNo == m_usWaitRecvSeq)
				{
					m_usWaitRecvSeq = 0;
					SetEvent(m_hRecvEvent);
						//由等待的函数处理返回结果
				}
				else
				{
				
					gpData->m_lockData.lock();
					int nDone = gpData->DealData(m_pPackData,iPackLen);
					gpData->m_lockData.unlock();

					if (nDone != 0 && nDone !=-1)//本地不能处理，交给具体的窗口来处理
					{/*
						gpData->m_lockData.lock();
						gpData->PutRep(m_pPackData,iPackLen);
						gpData->m_lockData.unlock();*/
						/*wuqing 20110412
						if(gpData->m_pDlgGroup)
						gpData->m_pDlgGroup->OnRecvData(m_pPackData,iPackLen);					*/
					}				

				}				
				return true;
		}
	}	
	return false;
}

bool CCommSocket::RecvData(unsigned short &c_usType)
{
///-	char acBuf[4096];
	int nn = 0;
	m_uiRecvLen = 0;
	while(true)
	//if (true)
	{
		int iLen;		
		int timeout = 6000; //3s

		setsockopt(m_socket,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout));

		setsockopt(m_socket,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));
		
		while(true)
		{
			iLen = recv(m_socket,m_pRecvBuf + m_uiRecvLen,4096,0);
			if (iLen == SOCKET_ERROR)
			{
				int err = ::WSAGetLastError();
				if (err > 0 && err != WSAEWOULDBLOCK && err != WSAETIMEDOUT)
				{
					Disconnect();
					return false;
				}
			}
			else
			{
				m_uiRecvLen += iLen;
				//检查数据是否收完了
				char * pPack = NULL;
				int nPackLen = 0;
				int nHeadLen = 0;
				if (strnicmp(m_pRecvBuf,"http",4) == 0)
				{
					pPack = strstr(m_pRecvBuf,"\r\n\r\n") + 4;
					nHeadLen = pPack - m_pRecvBuf;
				}
				else
					pPack = m_pRecvBuf;

				SCommHead * pHead = (SCommHead *)(pPack);
				if (pHead->m_head.GetVersion() != 3 || pHead->m_head.GetLength() > MAX_RECV_LEN - 8 || pHead->m_head.GetLength() <= 0 )
				{
					Disconnect();
					return false;
				}

				nPackLen = pHead->m_head.GetLength() + 8;
				if (nPackLen + nHeadLen > m_uiRecvLen)
					continue;
				
				memcpy(m_pPackData,pPack,nPackLen);//复制所有的数据
				m_uiRecvLen -= nPackLen + nHeadLen;
				for(int n=0; n<m_uiRecvLen; n++)
				{
					*m_pRecvBuf = *(pPack + nPackLen);
				}
				unsigned short us,usType;
				us = *(unsigned short *)(m_pPackData + 2);
				usType = *(unsigned short *)(m_pPackData + 8);
				ClearSocketHeart();
				c_usType = usType;
				m_nPackLen = nPackLen;

#ifdef _DEBUG
			if (true)//usType == 33108)// && usType != 3)//|| usType == 3017 )//|| usType == 3)//usType == 3013 || usType == 3014 || usType == 5 || usType == 6 || usType == 7)
			{
			FILE *f;
			char aczFile[100];
			//sprintf(aczFile,"c:\\test\\%d.%.3d.rcv.%d",nn++,us,usType);
			sprintf(aczFile,"c:\\test\\%d.rcv.%d",us,usType);
			f = fopen(aczFile,"wb");
			if (f)
			{
				fwrite((void *)m_pPackData,1,nPackLen,f);
				fclose(f);
			}
			}
#endif			
				if (m_usWaitRecvSeq > 0 && pHead->m_head.SerialNo == m_usWaitRecvSeq)
				{
					m_usWaitRecvSeq = 0;
					SetEvent(m_hRecvEvent);
						//由等待的函数处理返回结果
				}
				else
				{				
					gpData->m_lockData.lock();
					int nDone = gpData->DealData(m_pPackData,nPackLen);
					gpData->m_lockData.unlock();
				}
			}
		}
	}
	return false;
}
//int nToSend = 0;
int CCommSocket::SendData(char * c_pBuf,int c_nLen,bool c_bNew,char * c_pRetBuf,int c_nRetBufMaxLen)
{
	if (m_socket == INVALID_SOCKET)
		return -1;

//如果使用http协议格式则先发送http包头
	char acHttp[1024];
	acHttp[0] = 0;
	if (m_pproxyOption && m_pproxyOption->m_bUseHttpHead)
		sprintf(acHttp,"GET http://%s:%d HTTP/1.0\r\ncontent-type: audio/mp3;\r\ncontent-source : invest\r\nContent-Length: %d\r\nCache-Control: no-cache\r\nProxy-Connection: Keep-Alive\r\n\r\n",m_acHost,m_nPort,c_nLen);

//
	SCommHead * pHead;
	
	pHead = (SCommHead *)c_pBuf;

	if (c_nLen <= 8 || pHead->m_head.GetLength()==4)
	{
		return -1;
	}
	m_lockSocket.lock();
	if (m_usWaitRecvSeq > 0)
	{
		m_lockSocket.unlock();
		return -3;
	}
	if (pHead->m_head.SerialNo == 19)
	{
		pHead->m_head.SerialNo = 19;
	}
#ifdef _DEBUG	
	FILE * f;
	char acFile[256];
	sprintf(acFile,"e:\\test\\%d.req",pHead->m_head.SerialNo);
	f = fopen(acFile,"wb");
	if (f)
	{
		fwrite(c_pBuf,1,c_nLen,f);
		fclose(f);
	}
#endif
	int nRet = 0;
	if (strlen(acHttp))
	{
		nRet = send(m_socket,acHttp,strlen(acHttp),0);
		if (nRet < 0)//strlen(acHttp))
		{
			Disconnect();
			m_lockSocket.unlock();
			return -4;
		}
	}

	nRet = send(m_socket,c_pBuf,c_nLen,0);
	//m_lockSocket.unlock();
	if (nRet != c_nLen)
	{
		Disconnect();
		m_lockSocket.unlock();
		return -2;
	}
	//记录在本地等待应答
	if (true)//c_bNew)
	{
		SCommHead * pHead;
		pHead = (SCommHead *)c_pBuf;
		m_usWaitRecvSeq = pHead->m_head.SerialNo;
		int nResult = WaitForSingleObject(m_hRecvEvent, 5000);
		m_lockSocket.unlock();
		if (nResult != WAIT_OBJECT_0)
		{
			m_usWaitRecvSeq = 0;			
			return -3;
		}
		else
		{
			if (c_pRetBuf != NULL)
			{
				if (c_nRetBufMaxLen < m_nPackLen)
				{					
					return -1;
				}
				memcpy(c_pRetBuf,m_pPackData,m_nPackLen);				
				return m_nPackLen;
			}			

			gpData->m_lockData.lock();
			int nDone = gpData->DealData(m_pPackData,m_nPackLen);
			gpData->m_lockData.unlock();

			if (nDone != 0 && nDone !=-1)//本地不能处理，交给具体的窗口来处理
			{
				
			}				

			return nRet;
		}
	}	
	return nRet;
}
