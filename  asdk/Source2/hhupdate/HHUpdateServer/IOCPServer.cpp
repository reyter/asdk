#include "StdAfx.h"
#include ".\iocpserver.h"
//#include <WinBase.h>
int nNew = 1;
int nDelete=1;
CIOCPServer::CIOCPServer(void)
{
	m_lThreadNums = 0;
	m_pWnd = NULL;
	m_ListenSocket = INVALID_SOCKET;
	m_hCompletionPort = NULL;
	//m_strVer = _T("");
}

CIOCPServer::~CIOCPServer(void)
{
	StopServer();
}

void CIOCPServer::AssociateWnd(CWnd *pWnd)
{
	m_pWnd = pWnd;
}

void CIOCPServer::SetLastErrorMsg(CString strErrorMsg)
{
	m_strErrorMsg = strErrorMsg;
}
CString CIOCPServer::GetLastErrorMsg()
{
	return m_strErrorMsg;
}

BOOL CIOCPServer::WinSockInit()
{
	WSADATA data = {0};
	if(WSAStartup(MAKEWORD(2, 2), &data))//����
		return FALSE;
	if ( LOBYTE(data.wVersion) !=2 || HIBYTE(data.wVersion) != 2 ){//���ֽڶ�����ֽ� �жϰ汾
		WSACleanup();//��ֹWindows Sockets DLL��ʹ��.
		return FALSE;
	}
	return TRUE;
}

CPerSocketData *CIOCPServer::AssignSocketToCompletionPort(SOCKET tSocket)
{
	ASSERT(tSocket != INVALID_SOCKET);
	CPerSocketData *pSockData = new CPerSocketData();
	pSockData->m_Socket = tSocket;
	m_cs.Lock();
	m_LsSocketData.AddTail(pSockData); //listen socket is also in the list;
	m_cs.Unlock();
	CreateIoCompletionPort((HANDLE)tSocket, m_hCompletionPort, (ULONG_PTR)pSockData, 0);
	return pSockData;
}

BOOL CIOCPServer::PostAccept(CPerSocketData *pSockData)
{
	DWORD dwBytesRecv = 0;
	ASSERT(pSockData != NULL);
	COverLappedEx *m_pOverLap = new COverLappedEx(IO_TYPE_ACCEPT);
	TRACE1("NEW PostAccept:%d\n",nNew++);
	m_cs.Lock();
	m_LsOverLapEx.AddTail(m_pOverLap);
	m_cs.Unlock();
	pSockData->m_AccSocket = WSASocket(AF_INET , SOCK_STREAM , IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	BOOL bRet = AcceptEx(pSockData->m_Socket, pSockData->m_AccSocket, (char *)&m_pOverLap->m_nRequestBuff, 0, sizeof(sockaddr_in)+16, sizeof(sockaddr_in)+16, &dwBytesRecv, &m_pOverLap->m_OLap);
	if (!bRet) 
	{
		if (WSAGetLastError() != WSA_IO_PENDING) 
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CIOCPServer::PostRecv(CPerSocketData *pSockData)
{
	ASSERT(pSockData != NULL);
	WSABUF wsaBuf = {0};
	COverLappedEx *m_pOverLap = new COverLappedEx(IO_TYPE_READ);

	TRACE1("NEW PostRecv:%d\n",nNew++);

	m_cs.Lock();
	m_LsOverLapEx.AddTail(m_pOverLap);
	m_cs.Unlock();
	wsaBuf.buf = (char *)&m_pOverLap->m_nRequestBuff;
	wsaBuf.len = MAX_BUF_SIZE;
	DWORD dwBytesRecv = 0, dwFlags = 0;
	int iRet = WSARecv(pSockData->m_Socket, &wsaBuf, 1, &dwBytesRecv, &dwFlags, &(m_pOverLap->m_OLap), NULL);
	if (iRet != NO_ERROR) 
	{
		if (WSAGetLastError() != WSA_IO_PENDING) 
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CIOCPServer::PostSend(_tagAnswer *pAnswerBuf, DWORD dwSizeInBytes, CPerSocketData *pSockData)
{
	DWORD dwSend = 0;
	//CPerSocketData *pSockData = NULL;
	COverLappedEx *pOverLapEx = NULL;

	if (pSockData->m_Socket != m_ListenSocket) 
	{
		pOverLapEx = new COverLappedEx(IO_TYPE_WRITE);
		TRACE1("NEW PostSend:%d\n",nNew++);
		memcpy((char *)&pOverLapEx->m_AnswerBuff, (char*)pAnswerBuf, dwSizeInBytes);
		WSABUF wsaBuff = {0};
		wsaBuff.buf = (char *)&pOverLapEx->m_AnswerBuff;
		wsaBuff.len = dwSizeInBytes;
		m_cs.Lock();
		m_LsOverLapEx.AddTail(pOverLapEx);
		m_cs.Unlock();
		WSASend(pSockData->m_Socket, &wsaBuff, 1, &dwSend, 0, &(pOverLapEx->m_OLap), NULL);
		Sleep(2);
	}
	return TRUE;
}

void CIOCPServer::MaxVersion(LPCTSTR lpVer1,LPCTSTR lpVer2,LPCTSTR lpVerMax)
{
	if (0 == strlen((char*)lpVer1) && 0 ==strlen((char*)lpVer2))
	{
		return;
	}
	if (0 == strlen((char*)lpVer1))
	{
		strcpy((char*)lpVerMax,(char*)lpVer2);
		return;
	}
	if (0 == strlen((char*)lpVer2))
	{
		return;
	}

	char *prt1=NULL,*prt2=NULL,c='.';
	char sz1[6]={0},sz2[6]={0};
	char szV1[16]={0},szV2[16]={0};
	strcpy(szV1,(char*)lpVer1);
	strcpy(szV2,(char*)lpVer2);
	for (int i=0;i<4;i++)
	{
		prt1 = strchr(szV1,c);
		if (prt1)
		{
			strncpy(sz1,szV1,strlen(szV1)-strlen(prt1));
			strcpy(szV1,&prt1[1]);
		}
		else
		{
			if (strlen(szV1)>0)
			{
				strcpy(sz1,szV1);
			}
		}
		
		prt2 = strchr(szV2,c);
		if (prt2)
		{
			strncpy(sz2,szV2,strlen(szV2)-strlen(prt2));
			strcpy(szV2,&prt2[1]);
		}
		else
		{
			if (strlen(szV2)>0)
			{
				strcpy(sz2,szV2);
			}
		}

		if (atoi(sz1)>atoi(sz2))
		{
			break;
		}
		if (atoi(sz1)<atoi(sz2))
		{
			strcpy((char*)lpVerMax,(char*)lpVer2);
			break;;
		}
		
	}
	
}
void CIOCPServer::GetLastAppVersion(LPCTSTR lpAppid,LPCTSTR lpAppVer)
{
	
		if (NULL == lpAppid)
		{
			return;
		}
		int nErr=0;
		HANDLE hFind;
		WIN32_FIND_DATA wfData;
		char szFullPath[MAX_PATH];memset(szFullPath,0,MAX_PATH);
		char szFolderPath[MAX_PATH];memset(szFolderPath,0,MAX_PATH);
		strcat(szFullPath,"*.*");

		hFind = FindFirstFile(szFullPath,&wfData);
		if(hFind == INVALID_HANDLE_VALUE)
		{
			strcpy((char*)lpAppVer,lpAppid);
			return ;
		}
		char szTempAppID[16]={0};
		int i = 0,nItem =0;
		char szFileName[MAX_PATH]={0};
		char szVerMax[16]={0};
		do
		{
			switch(wfData.dwFileAttributes)
			{
			case FILE_ATTRIBUTE_DIRECTORY://Ŀ¼
				{
					if(strcmp(wfData.cFileName,".") && strcmp(wfData.cFileName,".."))//�ų���ǰĿ¼���ϼ�Ŀ¼
					{
						strncpy(szTempAppID,wfData.cFileName,strlen(lpAppid));
						if (0 == strcmpi(szTempAppID,(char*)lpAppid))
						{
							MaxVersion(szVerMax,&wfData.cFileName[strlen(lpAppid)],szVerMax);
						}
					}
				}
				break;
			default:
				break;
			}
		}while(FindNextFile(hFind,&wfData));
		sprintf((char*)lpAppVer,"%s%s",lpAppid,szVerMax);
}
DWORD WINAPI CIOCPServer::ThreadPoolProc(LPVOID lpParam)
{
	COverLappedEx *pOverLaps = NULL;
	CPerSocketData *pPerSockData = NULL;
	CIOCPServer *pThis = (CIOCPServer *)lpParam;
	ASSERT(pThis != NULL);

	InterlockedIncrement(&pThis->m_lThreadNums);//�̼߳�һ
	BOOL bIORet = FALSE;
	DWORD dwTrans = 0;
	CString strVer="";

	while (TRUE) 
	{
		bIORet = GetQueuedCompletionStatus(pThis->m_hCompletionPort, &dwTrans, (PULONG_PTR)&pPerSockData, (LPOVERLAPPED *)&pOverLaps, INFINITE);
		
		if (!bIORet) 
		{
			continue;
		}

		if (dwTrans == 0 && pOverLaps && (
			pOverLaps->m_IOType == IO_TYPE_READ ||
			pOverLaps->m_IOType == IO_TYPE_WRITE ))//�ͻ��˹ر�
		{
			closesocket(pPerSockData->m_Socket);
			POSITION pos = pThis->m_LsSocketData.Find(pPerSockData);
			if (NULL != pos)
			{
				pThis->m_cs.Lock();
				pThis->m_LsSocketData.RemoveAt(pos);
				pThis->m_cs.Unlock();
				delete pPerSockData;
				pPerSockData = NULL;
			}

			pos = pThis->m_LsOverLapEx.Find(pOverLaps);
			if (NULL != pos)
			{
				///m_LsOverLapEx�б��жദ��ɾ�������ӣ�Ϊ�˷�ֹǰ�ڵ���ڵ�ոձ�ɾ����û��������ϣ�
				///�ֵ����ɾ����������԰����е�m_LsOverLapEx�������м�����.
				pThis->m_cs.Lock();
				pThis->m_LsOverLapEx.RemoveAt(pos);
				pThis->m_cs.Unlock();
				delete pOverLaps;
				pOverLaps = NULL;
				TRACE1("DEL OutLine:%d\n",nDelete++);
				
			}
			
			break;
		}
		if(bIORet && pOverLaps && pPerSockData) 
		{
			switch (pOverLaps->m_IOType)
			{
			case IO_TYPE_READ:
				{
					CString strFileName,strUserID;
					char szFileName[MAX_PATH]={0};
					char szLastAppVer[32]={0};
					if (0 == strlen(pOverLaps->m_nRequestBuff.szVersion))//û�а汾��
					{
						//��ȡ���°汾
						;
						char *ptr=NULL,c='\\';
						ptr = strchr(pOverLaps->m_nRequestBuff.szFileName,c);
						if (ptr)
						{
							pThis->GetLastAppVersion(pOverLaps->m_nRequestBuff.szAppID,szLastAppVer);
							strFileName.Format("%s%s",szLastAppVer,ptr);
							sprintf(szFileName,"%s",strFileName.GetBuffer());
							strFileName.ReleaseBuffer();
						}
						
					}
					else
					{
						strcpy(szFileName,pOverLaps->m_nRequestBuff.szFileName);
						strFileName.Format("%s",pOverLaps->m_nRequestBuff.szFileName);
					}

					int nType = pOverLaps->m_nRequestBuff.nFlag;
					strUserID.Format("%s",pOverLaps->m_nRequestBuff.szUserID);

					POSITION pos = pThis->m_LsOverLapEx.Find(pOverLaps);
					if (NULL != pos)
					{
						pThis->m_cs.Lock();
						pThis->m_LsOverLapEx.RemoveAt(pos);
						pThis->m_cs.Unlock();
						delete pOverLaps;
						pOverLaps = NULL;
						TRACE1("DEL Read:%d\n",nDelete++);
						
					}
					
					pThis->PostRecv(pPerSockData);
					
					switch(nType)
					{
					case RE_TYPE_README://����README�ļ�
						{
							char *ptr=NULL,c='\\';
							ptr = strrchr((char*)(LPCTSTR)strFileName,c);
							if (NULL != ptr)
							{
								strncpy((char*)(LPCTSTR)strVer,strFileName,ptr-strFileName);
								CString strMsg;
								strMsg.Format("%s%s%s",strUserID,"����",strVer);
								pThis->m_pWnd->SendMessage(WM_SHOW_MSG, 0, (LPARAM)(LPCTSTR)strMsg);
							}
							pThis->DealWithRequest(strFileName,RE_TYPE_README,pPerSockData,strVer);
							
						}
						break;
					case RE_TYPE_XML://����xml�ļ�
						{
							pThis->DealWithRequest(strFileName,RE_TYPE_XML,pPerSockData,strVer);
						}
						break;
					case RE_TYPE_HH://����ѹ���ļ�
						{
							strFileName.Format("%s",szFileName);
							pThis->DealWithRequest(strFileName,RE_TYPE_HH,pPerSockData,strVer);
						}
						break;
					default:break;
					}
					
				}
				break;
			case IO_TYPE_WRITE:
				{					
					POSITION pos = pThis->m_LsOverLapEx.Find(pOverLaps);
					if (NULL != pos)
					{
						pThis->m_cs.Lock();
						pThis->m_LsOverLapEx.RemoveAt(pos);
						pThis->m_cs.Unlock();
						delete pOverLaps;
						pOverLaps = NULL;
						TRACE1("DEL write:%d\n",nDelete++);
						
					}
					
				}
				break;
			case IO_TYPE_ACCEPT:
				{
					if (pPerSockData->m_AccSocket == INVALID_SOCKET) //ʧ��
					{
						continue;
					}
					QueueUserWorkItem(ThreadPoolProc, pThis, WT_EXECUTELONGFUNCTION);//�̳߳غ���
					CPerSocketData *pData = pThis->AssignSocketToCompletionPort(pPerSockData->m_AccSocket);//��������ɶ˿�
					pThis->PostRecv(pData);
					pThis->PostAccept(pPerSockData);
					
					POSITION pos = pThis->m_LsOverLapEx.Find(pOverLaps);
					if (NULL != pos)
					{
						pThis->m_cs.Lock();
						pThis->m_LsOverLapEx.RemoveAt(pos);
						pThis->m_cs.Unlock();
						delete pOverLaps;
						pOverLaps = NULL;
						TRACE1("DEL accept:%d\n",nDelete++);
						
					}
					
				}
				break;
			default:
				{
					POSITION pos = pThis->m_LsOverLapEx.Find(pOverLaps);
					if (NULL != pos)
					{
						pThis->m_cs.Lock();
						pThis->m_LsOverLapEx.RemoveAt(pos);
						pThis->m_cs.Unlock();
						delete pOverLaps;
						pOverLaps = NULL;
						TRACE1("DEL default:%d\n",nDelete++);
					}
					
				}
				break;
			}

			if (NULL != pOverLaps)
			{
				
				POSITION pos = pThis->m_LsOverLapEx.Find(pOverLaps);
				if (NULL != pos)
				{
					pThis->m_cs.Lock();
					pThis->m_LsOverLapEx.RemoveAt(pos);
					pThis->m_cs.Unlock();
					delete pOverLaps;
					pOverLaps = NULL;
					TRACE1("DEL default2:%d\n",nDelete++);
				}
				
			}
			
		}else if (!pOverLaps && !pPerSockData) 
		{
			//exit the thread;
			break;
		}

		if (NULL != pOverLaps)
		{
			POSITION pos = pThis->m_LsOverLapEx.Find(pOverLaps);
			if (NULL != pos)
			{
				pThis->m_cs.Lock();
				pThis->m_LsOverLapEx.RemoveAt(pos);
				pThis->m_cs.Unlock();
				delete pOverLaps;
				pOverLaps = NULL;
				TRACE1("DEL while end :%d\n",nDelete++);
			}
			
		}
		//pThis->m_cs.Unlock();
	}

	InterlockedDecrement(&pThis->m_lThreadNums);//�̼߳�һ
	return TRUE;
}

BOOL CIOCPServer::StartServer(UINT uListenPort)
{
	int hh = sizeof CPerSocketData;
	hh= sizeof COverLappedEx;

	if (!WinSockInit()) {//��ʼ��socket
		SetLastErrorMsg(_T("Socket ���ʼ��ʧ�ܣ�"));
		WriteError(_T("Socket ���ʼ��ʧ�ܣ�"));
		return FALSE;
	}
	
	m_ListenSocket = WSASocket(AF_INET , SOCK_STREAM , IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if ( m_ListenSocket == INVALID_SOCKET ) {
		SetLastErrorMsg(_T("�½�Socketʧ�ܣ�"));
		WriteError(_T("�½�Socketʧ�ܣ�"));
		goto __Error_End;
	}

	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = INADDR_ANY;
	service.sin_port = htons(uListenPort);

	if ( bind(m_ListenSocket, (sockaddr*)&service, sizeof(sockaddr_in)) == SOCKET_ERROR ) {
		SetLastErrorMsg(_T("�󶨶˿�ʧ�ܣ�"));
		WriteError(_T("�󶨶˿�ʧ�ܣ�"));
		goto __Error_End;
	}

	if( listen(m_ListenSocket, SOMAXCONN) == SOCKET_ERROR ) {
		SetLastErrorMsg(_T("����ʧ�ܣ�"));
		WriteError(_T("����ʧ�ܣ�"));
		goto __Error_End;
	}

	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);//����һ����ɶ˿�
	if ( m_hCompletionPort == NULL ) {
		SetLastErrorMsg(_T("��ɶ˿ڴ���ʧ�ܣ�"));
		WriteError(_T("��ɶ˿ڴ���ʧ�ܣ�"));
		goto __Error_End;
	}

	CPerSocketData *pSockData = AssignSocketToCompletionPort(m_ListenSocket);//�����׽��ֵ���ɶ˿�

	QueueUserWorkItem(ThreadPoolProc, this, WT_EXECUTELONGFUNCTION);//�̳߳�

	PostAccept(pSockData);
	return TRUE;

__Error_End:
	if (m_ListenSocket != INVALID_SOCKET) {
		closesocket(m_ListenSocket);
	}

	if (m_hCompletionPort != NULL) {
		CloseHandle(m_hCompletionPort);
		m_hCompletionPort = NULL;
	}

	WSACleanup();
	return FALSE;
}

void CIOCPServer::StopServer()
{
	CPerSocketData *pSocketData = NULL;
	POSITION pos = m_LsSocketData.GetHeadPosition();
	while(NULL != pos)
	{
		pSocketData = m_LsSocketData.GetNext(pos);
		if (NULL != pSocketData)
		{
			closesocket(pSocketData->m_Socket);
			delete pSocketData;
			pSocketData = NULL;
			
		}
	}
	m_LsSocketData.RemoveAll();
	/*
	for (int i=0;i<m_LsSocketData.GetCount();i++)
	{
		pos = m_LsSocketData.FindIndex(i);
		if (NULL != pos)
		{
			pSocketData = m_LsSocketData.GetAt(pos);
			if (NULL != pSocketData)
			{
				closesocket(pSocketData->m_Socket);
				delete pSocketData;
				pSocketData = NULL;
			}
		}		
	}
	*/
	
	TRACE1("----Count %d\n",m_LsOverLapEx.GetCount());//���1����ʾ�����������Ļ��ڴ����й©��.
	COverLappedEx *pOverLap = NULL;
	pos = m_LsOverLapEx.GetHeadPosition();
	while(NULL != pos)
	{
		pOverLap = m_LsOverLapEx.GetNext(pos);
		if (NULL != pOverLap)
		{
			delete pOverLap;
			pOverLap = NULL;
			TRACE1("---- STOP %d\n",nDelete++);
		}
	}
	m_LsOverLapEx.RemoveAll();
	/*
	for (int i=0;i<m_LsOverLapEx.GetCount();i++)
	{
		pos = m_LsOverLapEx.FindIndex(i);
		if (NULL != pos)
		{
			pOverLap = m_LsOverLapEx.GetAt(pos);
			if (NULL != pOverLap)
			{
				delete pOverLap;
				pOverLap = NULL;
			}
		}
	}
	*/
	

	while(m_lThreadNums > 0){
		PostQueuedCompletionStatus(m_hCompletionPort, 0, 0, NULL);
		Sleep(100);
	}

	if (m_hCompletionPort != NULL) {
		CloseHandle(m_hCompletionPort);
		m_hCompletionPort = NULL;
	}
	WSACleanup();
}

BOOL CIOCPServer::DealWithRequest(const LPCTSTR lpszFileName,int nFlag,CPerSocketData *pPerSockData,CString strVer)//��������
{
	_tagAnswer AnswerBuf = {0};
	ZeroMemory(AnswerBuf.szFileType,9);
	itoa(nFlag,AnswerBuf.szFileType,10);
	char szFileName[MAX_PATH]={0};
	strcpy(szFileName,lpszFileName);
	CFile readmeFile;
	if(!readmeFile.Open(szFileName, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone))
	{
		switch(nFlag)
		{
		case RE_TYPE_README:
			{
				//���� readme
				CFile out(szFileName,CFile::modeCreate|CFile::shareDenyNone|CFile::modeReadWrite|CFile::typeBinary);
				int n = strlen(strVer);
				out.Write(strVer,n);
				out.Close();
				
			}
			break;
		case RE_TYPE_XML:
			{
				//����XML
				char c = '\\';
				char *prt = strrchr(szFileName,c);
				memset(&szFileName[prt - szFileName+1],0,MAX_PATH-(prt - szFileName+1));
				strcat(szFileName,"update\\");
				m_hhTyXml.HHComposeXML(szFileName)/*lpszFileName*/;
			}
			break;
		case RE_TYPE_HH:
			{
				//ѹ���ļ�
				char c = '\\';
				char *prt = strchr(szFileName,c);
				memset(&szFileName[prt - szFileName+1],0,MAX_PATH-(prt - szFileName+1));
				strcat(szFileName,"update\\");
				m_hhCompress.BatchDecompress(szFileName);
			}
			break;
		default:break;
		}
		if(!readmeFile.Open(lpszFileName, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone))
		{
			TRACE("�Ҳ����ļ�!\n");
			CString strError;
			strError.Format("%s--%s%s",strVer,lpszFileName,"ȱʧ���벹�����������ѹ���ļ���XML�ļ�!");
			WriteError(strError);
			return FALSE;//�ļ�������
		}
	}
	ULONGLONG ulFileLength = readmeFile.GetLength(); // С�Ĵ����ļ�����Ϊ0
	if (0 == ulFileLength)
	{
		TRACE("�ļ�����Ϊ0!\n");
		CString strError;
		strError.Format("%s--%s%s",strVer,lpszFileName,"�ļ�����Ϊ0���벹�����������ѹ���ļ���XML�ļ�!");
		WriteError(strError);
		readmeFile.Close();
		uLong ulLen = 0;
		m_hhCompress.HHCompress(lpszFileName,&ulLen);
		readmeFile.Open(lpszFileName, CFile::modeRead | CFile::typeBinary| CFile::shareDenyNone );
		//return FALSE;//�ļ�������
	}
	ZeroMemory(AnswerBuf.szAllDataLength,9);
	itoa((int)ulFileLength,AnswerBuf.szAllDataLength,10);
	//AnswerBuf.ulAllDataLength = ulFileLength;
	ZeroMemory(AnswerBuf.szFlag,9);
	itoa(0,AnswerBuf.szFlag,10);
	//AnswerBuf.nFlag = 0;//��ʼ
	readmeFile.Seek(0,CFile::begin);//��λ�ļ�ָ�뵽�ļ���ʼ
	int nReadLen=0;
	int nTemp=0;
	//��ʼ����
	while(1)
	{
		nReadLen=readmeFile.Read(AnswerBuf.btBuff, MAX_BUF_SIZE);
		ZeroMemory(AnswerBuf.szBuffLen,9);
		itoa(nReadLen,AnswerBuf.szBuffLen,10);
		//AnswerBuf.nBuffLen = nReadLen;
		nTemp += nReadLen;
		if (nReadLen < MAX_BUF_SIZE)//���һ���ļ���
		{
			ZeroMemory(AnswerBuf.szFlag,9);
			itoa(1,AnswerBuf.szFlag,10);
			//AnswerBuf.nFlag = 1;//�������
		}
		else if (nTemp == ulFileLength)//���һ���ļ���
		{
			ZeroMemory(AnswerBuf.szFlag,9);
			itoa(1,AnswerBuf.szFlag,10);
			//AnswerBuf.nFlag = 1;
		}
		if(nReadLen==0) break;//���� for
		PostSend(&AnswerBuf,sizeof(_tagAnswer),pPerSockData);//����
		Sleep(1);
		ZeroMemory(AnswerBuf.btBuff,MAX_BUF_SIZE);
	}
	readmeFile.Close();
	return TRUE;
}
/*
void CIOCPServer::OverLapExRemoveAt(COverLappedEx *pOverLaps)
{
	
	POSITION pos = m_LsOverLapEx.Find(pOverLaps);
	if (NULL != pos)
	{
		m_LsOverLapEx.RemoveAt(pos);
		delete pOverLaps;
		pOverLaps = NULL;
		TRACE1("DEL :%d\n",nDelete++);
	}
}
*/