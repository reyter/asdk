#include "StdAfx.h"
#include ".\hhwpiocp.h"
#include "HHWPConnection.h"
#include "io.h"
#include "fcntl.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "share.h"


#include "CCEDefine.h"

//#include "TQXDataChannelCtrl.h"
//#include "SystemConfigure.h"

//int nLogfd=-1;
//CRITICAL_SECTION g_csLog;
//CString g_szLogFileName ="";

//void CHHWPIOCP::AppendLog(LPCSTR sMesg)
//{
//	
//	if(nLogfd!=-1)
//	{
//		//if(!CSystemConfigure::GetInstance()->m_bLogMessage)
//		//	return;
//
//		CString str;
//		CTime timet = CTime::GetCurrentTime();
//		str.Format("%04d-%02d-%02d %02d:%02d:%02d   %s\r\n",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),sMesg);
//		EnterCriticalSection(&g_csLog);
//		write(nLogfd,str.GetBuffer(),str.GetLength());
//		LeaveCriticalSection(&g_csLog);
//	}
//}

CHHWPIOCP::CHHWPIOCP(void)
{
	//m_hCompletionPort = NULL;
	//创建完成端口，
	//创建工作线程.
	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,0,0,0);
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	int nCount = info.dwNumberOfProcessors*2+2;
	for(int i=0;i<nCount;++i)
	{
		CWinThread* pThread = AfxBeginThread(CHHWPIOCP::ThreadIOCPFun,m_hCompletionPort);
		if(pThread)
		{
			//设置优先级。先处理.
			::SetThreadPriority(pThread->m_hThread,THREAD_PRIORITY_ABOVE_NORMAL);
		}
	}


	AppendLog("网络库初始化成功");


	//测试一下
	/*char temp[35];
	char temp2[35];
	for(int i=0;i<35;++i)
		temp[i]=i;
	
	#define TQXDES_PASSWORD ("MATCHPUSPASSWORDPUSHMACH")
	CTQXDataChannelCtrl::HHSafe3DesEncrypt(TQXDES_PASSWORD,strlen(TQXDES_PASSWORD),(BYTE*)temp,sizeof(temp),(BYTE*)temp2);

	CTQXDataChannelCtrl::HHSafe3DesDecrypt(TQXDES_PASSWORD,strlen(TQXDES_PASSWORD),(BYTE*)temp2,sizeof(temp2),(BYTE*)temp);*/

}



CHHWPIOCP::~CHHWPIOCP(void)
{
	if(m_hCompletionPort)
		CloseHandle(m_hCompletionPort);
	
}
//void CHHWPIOCP:://AppendLog(LPCSTR mesg)
//{
//
//}

static multimap<int,LPUSERCOMMANDFUN> g_lsCommandFunMap;

bool CHHWPIOCP::RegisterIOCPUserCommand(int nCommand,LPUSERCOMMANDFUN pFun)
{
	if(nCommand < eIOMAXSYS)
		return false;
	else
	{
		g_lsCommandFunMap.insert(pair<int,LPUSERCOMMANDFUN>(nCommand,pFun));
		return true;
	}
}
void CHHWPIOCP::SendUserRegisterCommand(int nCommand,LPVOID lParam)
{
	return CHHWPConnection::SendRegisterUserCommand(nCommand,lParam);
}

UINT CHHWPIOCP::ThreadIOCPFun(LPVOID lParam)
{
	AfxSocketInit();
	AfxOleInit();

	

	HANDLE hCompletionPort = (HANDLE)lParam;

	DWORD dwIoSize=0;
	LPOVERLAPPED lpOverlapped=NULL;
	CHHWPConnection* pConnection=NULL;
	OVERLAPPLUS*	pOverlapPlus=NULL;
	BOOL			bError=FALSE;
	BOOL			bEnterRead=FALSE;

    for(;true;)
	{
		//ASSERT(AfxCheckMemory());

		try
		{
			//线程一直运行
			dwIoSize=0;
			lpOverlapped=NULL;
			pConnection=NULL;
			pOverlapPlus=NULL;
			bError=FALSE;
			bEnterRead=FALSE;


			BOOL bIORet = GetQueuedCompletionStatus(hCompletionPort,&dwIoSize,
				(LPDWORD)&pConnection,&lpOverlapped,/*100*/INFINITE);

			pOverlapPlus = (OVERLAPPLUS*)lpOverlapped;

			if(!bIORet)
			{
				DWORD dwIOError = GetLastError();
				if(dwIOError != WAIT_TIMEOUT)
				{	
					//超时.
					//需要再询问 ,因为无限期等待，应该是不需要再询问的。
					pConnection->OnError(pOverlapPlus);
					continue;
				}else
				{	
					OnSysIdle();
				}
			}else
			{
				if( (!pOverlapPlus) ||  
					( (!pConnection) && (pOverlapPlus->ntype<=eIOMAXSYS))
					)
					continue;


				//先处理用户自定义消息.
				if(pOverlapPlus->ntype > eIOMAXSYS)
				{
					int nType = pOverlapPlus->ntype;
					LPVOID lParam = pOverlapPlus->nUserDefineType;
					CHHWPConnection::ReleaseOverlapPlus(pOverlapPlus);

					for( multimap<int,LPUSERCOMMANDFUN>::iterator it = g_lsCommandFunMap.begin();it!= g_lsCommandFunMap.end();++it)
					{
						if( it->first == nType )
						{
							(*(it->second))(lParam);
						}

					}
					continue;
				}


				if( (pConnection->IsError() || dwIoSize<=0 )
					&& (pOverlapPlus->ntype != eIODeleteThis ) )
				{
					DWORD dwIOError = GetLastError();
					//丢掉数据
					pConnection->OnError(pOverlapPlus);
					//delete pConnection;
					continue;					
				}else 
				{
					if(pOverlapPlus)
					{
						switch(pOverlapPlus->ntype)
						{
						case eIORead:
							{
								//ASSERT(AfxCheckMemory());

								//InterlockedDecrement(&pConnection->m_nRefCount);
								pConnection->OnReceiveData(dwIoSize,pOverlapPlus);

								//ASSERT(AfxCheckMemory());

							}break;
						case eIOWrite:
							{
	
								//ASSERT(AfxCheckMemory());
								//InterlockedDecrement(&pConnection->m_nRefCount);
								pConnection->OnSendDataFin(dwIoSize,pOverlapPlus);
								//ASSERT(AfxCheckMemory());
							}break;
						case eIODeleteThis:
							{
								//ASSERT(AfxCheckMemory());
								CHHWPConnection::ReleaseOverlapPlus(pOverlapPlus);
								delete pConnection;
								//ASSERT(AfxCheckMemory());
							}break;
							/*case eIOSendBufferData:
							{
							pConnection->OnSendBufferData(pOverlapPlus);
							}break;*/
							//case eIOExit:
							//	{
							//		pConnection->OnIOCPExit(pOverlapPlus);
							//		//pConnection->OnExit(dwIoSize,pOverlapPlus);
							//	}break;					
							/*case eUserDefine:
							{
							pConnection->OnUserDefine(pOverlapPlus);
							}break;*/
						}
					}
				}
			}

		}catch(exception e)
		{
				TRACE1("%s",e.what());
		}catch(...)
		{
				TRACE0("Error");            
		}
		
	}
}

CHHWPIOCP*  CHHWPIOCP::g_pHHWPIOCP =NULL;

CHHWPIOCP* CHHWPIOCP::Init()
{
    if(!g_pHHWPIOCP)
	{
		g_pHHWPIOCP = new CHHWPIOCP();
	}
	return g_pHHWPIOCP;
}

void CHHWPIOCP::UnInit()
{
	if(g_pHHWPIOCP)
	{
		delete g_pHHWPIOCP;
		g_pHHWPIOCP = NULL;
	}
}

void OnSysIdle()
{
	//TODO：
	//该功能暂不实现.
	//static bool bOnSysIdle = false;
	//if(!bOnSysIdle)
	//{
	//	bOnSysIdle = true;
	//	//TODO: 添加空闲代码.
	//	bOnSysIdle = false;
	//}else
	//{
	//}
}

//BOOL CHHWPIOCP::StartListen(CChannel& channel)
//{
//	//AppendLog("---------------------");
//	CString str;
//	str.Format("准备开启通道 %s(%u)",channel.m_core.szChannelName,channel.m_core.nLocalPort);
//	//AppendLog(str);
//
//	//Create IO Completion Port
//	if(m_hCompletionPort == NULL )
//	{
//		//Create it.
//		/*SOCKET s;
//		s = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
//		if(s == INVALID_SOCKET)
//		{
//			//AppendLog("Create Socket Failed!");
//			return false;
//		}*/
//		m_hCompletionPort = CreateIoCompletionPort(/*(HANDLE)s*/INVALID_HANDLE_VALUE,NULL,0,0);
//		if(m_hCompletionPort == NULL)
//		{
//			//AppendLog("Create IOCP failed!");
//			//closesocket(s);
//            return false;
//		}
//	}
//
//	
//}
// 