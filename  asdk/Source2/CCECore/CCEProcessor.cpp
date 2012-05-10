// HHIOCPProcessor.cpp : 实现文件
//

#include "stdafx.h"
//#include "TQX.h"
#include "CCEProcessor.h"
#include "HHWPConnection.h"
#include "ChannelManager.h"

#include "CCEDefine.h"
#include "d3des.h"
#include "ResourceLock.h"




IMPLEMENT_DYNCREATE(CCCEProcessor,CObject)
// CCCEProcessor

CCCEProcessor::CCCEProcessor()
:m_pConnection(NULL)
,m_lParam(NULL)
,m_nRecvBufferSize(CCE_DEFAULT_RECV_LEN)
{
}

CCCEProcessor::~CCCEProcessor()
{
}


// CCCEProcessor 成员函数

bool CCCEProcessor::CreateServer(LPCTSTR szSvrName,USHORT nPort,CRuntimeClass* pRuntimeClass,
								 LPVOID lParam)
{
	CHANNEL_INFO_CORE core;
	strncpy(core.szChannelName,szSvrName,sizeof(core.szChannelName)-1);
	core.nLocalPort = nPort;
	core.pSvrRunTimeClass = pRuntimeClass;
	core.lParam = lParam;
	//创建一侦听线程.
	return CChannelManager::GetInstance()->AddChannel(&core,false);
}

//发送数据.
int CCCEProcessor::SendRawData(const void* pData,int nLength)
{
	if(m_pConnection)
	{
        return (m_pConnection)->SendData(pData,nLength);
	}else
		return -1;
}

void CCCEProcessor::OnSendDataFinish(const void* pData,int nLength)
{

}

void  CCCEProcessor::CloseConnection()
{
	if(m_pConnection)
	{
		(m_pConnection)->NotifyExit();
	}
}
void CCCEProcessor::SetRecvBufferSize(int nSize)
{
	m_nRecvBufferSize = max(CCE_DEFAULT_RECV_LEN,nSize);
	if(m_pConnection)
		m_pConnection->SetRecvBufferSize(m_nRecvBufferSize);

}


int CCCEProcessor::SendRawDataThenClose(const void* pData,int nLength)
{
	if(m_pConnection)
	{
		return (m_pConnection)->SendData(pData,nLength,CHHWPConnection::SD_FLAG_SEND_THEN_CLOSE);
	}else
		return -1;
}

void CCCEProcessor::SetConnectionPointer(CHHWPConnection* pConnection)
{
	m_pConnection = pConnection;
}

void CCCEProcessor::OnRecvRawData(const void* pData,int nLength)
{

}
bool CCCEProcessor::OnClose()
{
	m_pConnection = NULL;
	//默认返回TRUE.
	return true;
}

void CCCEProcessor::OnConnectionInitFinish()
{

}

CCE_LOG_FUN CCCEProcessor::SetCCELogFun(CCE_LOG_FUN pLogFun,LPVOID lParam)
{
	CCE_LOG_FUN temp = g_pCCELogFun;
	g_pCCELogFun = pLogFun;
    g_pCCELogParam = lParam;
	return g_pCCELogFun;
}

void  CCCEProcessor::GetStatistics(__int64* pI64Send,__int64* pI64Recv)
{
	if(m_pConnection)
	{
		if(pI64Send)
			(*pI64Send) = (m_pConnection)->m_connInfo.sendBytes;
		if(pI64Recv)
			(*pI64Recv) = (m_pConnection)->m_connInfo.recvBytes;
	}else
	{
		if(pI64Send)
			(*pI64Send) = 0;
		if(pI64Recv)
			(*pI64Recv) = 0;
	}
}
void   CCCEProcessor::GetPeerAddr(sockaddr_in& addr)
{
	if(m_pConnection)
	{
        m_pConnection->GetPeerAddr(addr);
	}
}
void  CCCEProcessor::GetThisAddr(sockaddr_in& addr)
{
	if(m_pConnection)
	{
		m_pConnection->GetThisAddr(addr);
	}

}

//UINT CCCEProcessor::OnUserDefine(int nCommand)
//{
//	return 0;
//}
//void CCCEProcessor::SendUserDefineCommand(int nCommand)
//{
//	if(m_pConnection)
//		m_pConnection->SendUserDefine(nCommand);
//}




int CCCEProcessor::GetSafe3DesEncryptLength(int block_len)
{
	return (block_len+7)/8*8;
}


int CCCEProcessor::HHSafe3DesDecrypt(char* key,  int keylen, BYTE* source_buf, int block_len,  BYTE* dest_buf)
{
	//解压
	ASSERT(block_len%8==0);

	if(block_len%8!=0)
	{
		return -1;

	}else
	{
		//CResourceLock cs(&g_csDES);
		des3key((unsigned char*)key,1);
		for(int i=0;i<block_len/8;++i)
		{
			Ddes(source_buf+i*8,dest_buf+i*8);
		}
	}
	return 0;
}

static CRITICAL_SECTION g_csDES;

int CCCEProcessor::HHSafe3DesEncrypt(char* key,  int keylen, BYTE* source_buf, int block_len,  BYTE* dest_buf)
{

	int nBufferLen=0;
	unsigned char *pTemp;


	if(block_len%8==0)
	{
		nBufferLen = block_len;		
		pTemp = source_buf;
	}
	else
	{	
		nBufferLen = GetSafe3DesEncryptLength(block_len);
		pTemp = new unsigned char[nBufferLen];
		memset(pTemp,0,nBufferLen);
		memcpy(pTemp,source_buf,block_len);
	}

	{
		static bool bDesInit=false;
		if(!bDesInit)
		{
			InitializeCriticalSection(&g_csDES);
			bDesInit = true;
		}

		CResourceLock cs(&g_csDES);
		des3key((unsigned char*)key,0);
		for(int i=0;i<nBufferLen/8;++i)
		{
			Ddes(pTemp+i*8,dest_buf+i*8);
		}
	}

	if(pTemp != source_buf)
		delete []pTemp;	
	return 0;
}
