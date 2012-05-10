// ProxySocket.cpp: implementation of the CMasskySocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "ProxyOption.h"
#include "ProxySocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static int g_iSend = 0;
static int g_iRecv = 0;
static const int LOGIN_CONNECT_OUT_TIME = 10; // 登陆连接超时时间

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void GetSystemTime(char * p_buf)
{
	time_t  l_cur_time ;
	struct tm * ltm_time = NULL ;
	char  lc_time[20] ;
	
	time(&l_cur_time) ;
	ltm_time = localtime(&l_cur_time) ;
	sprintf(lc_time,"%4d%02d%02d%02d%02d%02d",ltm_time->tm_year + 1900,ltm_time->tm_mon +1,ltm_time->tm_mday,ltm_time->tm_hour, ltm_time->tm_min,ltm_time->tm_sec) ;
	
	strncpy(p_buf,lc_time,14) ;  	
	p_buf[14] = '\0' ;
	return ;
}

void UserLog(const char *p_fmt, ...) 
{
    va_list  v_va ;
    char buf[10240];   
    FILE * fp = NULL;
    char lc_time[20] ;
    return;
    va_start (v_va,p_fmt);
    _vsnprintf(buf,sizeof(buf),p_fmt,v_va) ;
    buf[strlen(buf)] = '\0' ;
    if((fp = fopen("Userlog.dat","a")) == NULL)
    {
		perror("Open Userlog.dat file error\n") ;
		return ;
    }
    
    GetSystemTime(lc_time) ; 
    fprintf(fp,"%s	",lc_time) ;
    fprintf(fp,"%s\n",buf) ;
    fclose(fp) ;
    va_end(v_va) ;
    fp = NULL ;
    return ;
}


CProxySocket* CProxySocket::_instance = NULL;
////**** public
CProxySocket* CProxySocket::Instance()
{
	if(!_instance)
	{
		_instance = new CProxySocket;
	}
	return _instance;
}

void CProxySocket::ExitInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = NULL;
	}
}

CProxySocket::CProxySocket()
{
	//获取应用程序路径
		
	WORD wVersionRequested;
	WSADATA wsaData;	
	wVersionRequested = MAKEWORD(2,2);
	WSAStartup(wVersionRequested,&wsaData);					
}

CProxySocket::~CProxySocket()
{		
	WSACleanup() ;  //清除通信现场(com)  
}


int CProxySocket::RecvBuf(int nSockId,char *szRecvBuf,int nRecvSize)
{
	int  nRet ;
	int  nCurRecvLen = 0 ;
	int  nErrNo ;
	
Label1:
	nRet =  recv(nSockId,szRecvBuf + nCurRecvLen,nRecvSize - nCurRecvLen,0) ;
	nErrNo = WSAGetLastError() ;
	
	if(nRet == 0)    return -1 ;
	if(nRet == SOCKET_ERROR) 
	{
		if(nErrNo == WSAEINTR) goto Label1 ;
		if(nErrNo == WSAEINPROGRESS || nErrNo == WSAEWOULDBLOCK)
		{
			struct timeval l_sTimeOut ;
			fd_set fd_read ;
			int    l_iErrLen = sizeof(int) ;
			
			l_sTimeOut.tv_sec = 0 ;
			l_sTimeOut.tv_usec = 10 ;
			FD_ZERO(&fd_read) ;
			FD_SET(nSockId,&fd_read) ;
			
			if(select(nSockId +1,&fd_read,NULL,NULL,&l_sTimeOut) > 0)
			{
				char l_acErrTmp[100];
				memset(l_acErrTmp,0,sizeof(l_acErrTmp));
				getsockopt(nSockId, SOL_SOCKET, SO_ERROR, l_acErrTmp, &l_iErrLen); 
				if(strlen(l_acErrTmp) == 0)   goto Label1 ;
				else return -1 ;
			}
			else return -1 ;
		}
		
		return -1 ;
	}
	
	nCurRecvLen += nRet ;
	
	if(nCurRecvLen < nRecvSize) goto Label1 ;
	
	return 0 ;
}

void CProxySocket::ClearSemaphore(HANDLE hSema)
{
	while(WaitForSingleObject(hSema,100) == WAIT_OBJECT_0)  ;
}

int g_iBuf = 0;
int CProxySocket::SendBuf(int p_iSockid,char * p_pcBuf,int p_iBufLen)
{
	int needsendbytes;
	int sendbytes = 0;
	char *currptr = NULL;
	
	//  struct timeval l_timeout ;
	fd_set fd_write ; 
	int li_ret ;
	int li_flag = 0 ;
	int errno ;
	/*FILE * f;
	char aczFileName[100];
	sprintf(aczFileName,"c:\\record\\%d.buf",g_iBuf++);
	f = fopen(aczFileName,"wb");
	fwrite(p_pcBuf,1,p_iBufLen,f);
	fclose(f);*/
	
	FD_ZERO(&fd_write);
	FD_SET(p_iSockid,&fd_write);
	
	currptr = p_pcBuf;
	needsendbytes = p_iBufLen;
	
	while(needsendbytes > 0)
	{
		errno = 0 ;
		li_ret = select(p_iSockid + 1,NULL,&fd_write,NULL,NULL);
		errno = WSAGetLastError() ;
		if(li_ret <= 0)
		{
			if(li_ret == 0)    /*timeout be happened.*/
			{
				li_flag = -1 ;
				//m_nSocketErrNo = errno ;
				goto LABEL1 ;
			}
			else
				if(errno == WSAEINTR)   goto LABEL3 ;
				else
				{
					li_flag = -1 ;
					//m_nSocketErrNo = errno ;
					goto LABEL1 ;
				}
		}
		
		if(FD_ISSET(p_iSockid,&fd_write))
		{
			errno = 0 ;
			sendbytes = send(p_iSockid,currptr,needsendbytes,0);
			errno = WSAGetLastError() ;
			if (sendbytes == -1)
			{        
				if(errno == WSAEINTR) goto LABEL3;     /*Interrupt Occur...*/
				else
					if(errno == WSAENOBUFS)  Sleep(1000) ;
					else
					{
						//m_nSocketErrNo = errno ;
						return -1 ;        
					}
			}
			else
			{
				needsendbytes -= sendbytes;       /*Remain Bytes....... */
				currptr += sendbytes;
			}
		}
		
LABEL3:     
		FD_ZERO(&fd_write);
		FD_SET(p_iSockid,&fd_write);
	}
	
LABEL1:  
	return li_flag ;
}


int CProxySocket::NormalConnect(int * pnSocketId, char *szHostIP,unsigned short usHostPort)
{
	if( usHostPort == 0)
	{
		shutdown((* pnSocketId),2);
		return -1;	
	}

	try
	{
    	if( -1 == ConnectToServer(pnSocketId,szHostIP,usHostPort))
		{
			*pnSocketId = INVALID_SOCKET;
			return -1;
		}
	}
	catch(...)
	{
		return -1;
	}
	
	return 0 ;
}

int CProxySocket::Socket4Connect(int *pnSocketId,char *szHostIP,unsigned short usHostPort,CProxyOption *proxy)								  
{
	char  szRecvData[600] ;
    int	  nRet = 0,nHavaDateLen ;
	
	try
	{
		char szProxyIP[100];
		memset(szProxyIP,0,sizeof(szProxyIP));
		unicodeToAscii(proxy->getProxyIP(),szProxyIP,32);		
		if( ConnectToServer(pnSocketId,szProxyIP,proxy->getProxyPort()) == -1)  
			return -1 ;
		
		Sock4Req sSock4Req ;     //Socket4请求包
		memset(&sSock4Req,0,sizeof(Sock4Req));
		sSock4Req.m_cVer = 4;
		sSock4Req.m_cCD = 1;
		sSock4Req.m_usPort = htons(usHostPort);
		sSock4Req.m_ulIPAddr = inet_addr(szHostIP);
		
		if( -1 == SendBuf((* pnSocketId),(char *)&sSock4Req,sizeof(sSock4Req)))
		{
			shutdown((* pnSocketId),2);
			return -1 ;
		}   //请求不能发送
		
		nHavaDateLen = 0;
		memset(szRecvData,0,sizeof(szRecvData)) ;
		while(1)
		{
			 nRet = recv((* pnSocketId),szRecvData+nHavaDateLen,600 - nHavaDateLen,0);
			 if( nRet <= 0)
			 {
				nRet = -1; 
				break ;
			}
			nHavaDateLen += nRet ;
			if(nHavaDateLen > 2)
				break ;
		}
	   	   
		if(nRet == -1)
		{
			shutdown((* pnSocketId),2);
			return -1 ;
		}  //接收失败
		
		Sock4Ans * psSock4Rep = (Sock4Ans *)szRecvData ;
		if(psSock4Rep->m_cVer != 0 || psSock4Rep->m_cCD != 90)
		{
			shutdown((* pnSocketId),2);  
			return -1 ; 
		}
		
		return 0 ;
	}
	catch(...)
	{
		return -1 ;
	}
}

int CProxySocket::Socket5Connect(int * pnSocketId, char *szHostIP,unsigned short usHostPort,CProxyOption * proxy)								  
{
 	int	nRet = 0 ;
  	try
	{
		char szProxyIP[100];
		memset(szProxyIP,0,sizeof(szProxyIP));
		unicodeToAscii(proxy->getProxyIP(),szProxyIP,32);		
		if( ConnectToServer(pnSocketId,szProxyIP,proxy->getProxyPort()) == -1)  
			return -1 ;
		
		char  szRecvData[600];
		memset(szRecvData,0,sizeof(szRecvData)) ;
		Sock5Req1 * socket5proxyreq1;
		socket5proxyreq1 = (Sock5Req1 *)szRecvData ;
		
		socket5proxyreq1->m_cVer = 5; 
		socket5proxyreq1->m_cNMethods = 2; 
		socket5proxyreq1->m_pcMethods[0] = 0; 
		socket5proxyreq1->m_pcMethods[1] = 2; 
		
		//请求不能发送
		if( -1 == SendBuf((* pnSocketId),szRecvData,4) )
		{
		   shutdown((* pnSocketId),2);
		   return -1 ;
		} 		
		
		Sock5Ans1 socket5proxyans1;		
		memset(&socket5proxyans1,0,sizeof(socket5proxyans1));
		if( -1 == RecvBuf((* pnSocketId),(char *)&socket5proxyans1,sizeof(socket5proxyans1)))
		{
			shutdown((* pnSocketId),2);
			return -1 ;
		} 		
		if(socket5proxyans1.m_cVer != 5 
			|| (socket5proxyans1.m_cMethod !=0 && socket5proxyans1.m_cMethod!=2))
		{
			shutdown((* pnSocketId),2);  
			return -1 ;
		} 
		
		if(socket5proxyans1.m_cMethod == 2)
		{
			int   nBufLen = 0,nDataLen =0,l_iTotalLen = 1 ;
			
			memset(szRecvData,0,sizeof(szRecvData)) ;  //初始化
			
			szRecvData[0] = 1 ;  //版本号		  
			l_iTotalLen = 1 ;

			CString strTmp;			
			char acTmp[32];
			strTmp = proxy->getProxyUser();
			strTmp.TrimRight() ;
			nDataLen = strTmp.GetLength() ;
			memset(acTmp,0,sizeof(acTmp)) ;
			unicodeToAscii(strTmp,acTmp,32);			
			nDataLen = strlen(acTmp);

			szRecvData[l_iTotalLen] = nDataLen ;   //用户名长度
			l_iTotalLen ++ ;
			
			strncpy(szRecvData+l_iTotalLen,acTmp,nDataLen) ; //用户名
			l_iTotalLen += nDataLen ;
			
			strTmp = proxy->getProxyPass();
			strTmp.TrimRight() ;
			
			nDataLen = strTmp.GetLength() ;
			memset(acTmp,0,sizeof(acTmp)) ;
			unicodeToAscii(strTmp,acTmp,32);			
			nDataLen = strlen(acTmp);

			szRecvData[l_iTotalLen] = nDataLen ;    //口令长度
			l_iTotalLen ++ ;
			
			strncpy(szRecvData + l_iTotalLen,acTmp,nDataLen) ;   //口令
			l_iTotalLen += nDataLen ;
			
			nRet = SendBuf((* pnSocketId),szRecvData,l_iTotalLen);
			if(nRet == -1) 
			{
				shutdown((* pnSocketId),2);  
				return -1 ; 
			}
			
		    memset(szRecvData,0,sizeof(szRecvData)) ;  //初始化
			int nRecvDataLen = 0 ;
			while(1)
			{
				nRet = recv((* pnSocketId),szRecvData + nRecvDataLen,600 - nRecvDataLen,0);
				if(nRet == -1)
					break ;
				nRecvDataLen += nRet ;
				if(nRecvDataLen >= sizeof(AuthAns)) 
					break ;
			}
			
			if(nRet == -1) 
			{
				shutdown((* pnSocketId),2);  
				return -1 ; 
			}
			
			AuthAns * authans = (AuthAns *)szRecvData ;
			if(authans->m_Ver != 1 || authans->m_cStatus != 0) 
			{
				shutdown((* pnSocketId),2);  
				return -1 ; 
			}
		}   //End if 认证通过
		
		Sock5Req2  sock5Req2;		
		memset(&sock5Req2,0,sizeof(Sock5Req2)) ;
		sock5Req2.m_cVer = 5;
		sock5Req2.m_cCmd = 1;
		sock5Req2.m_cRsv = 0; 
		sock5Req2.m_cAtyp = 1;
		
		unsigned long ulIPAddr = inet_addr(szHostIP);//保存 ip 地址
		unsigned short usPort = htons(usHostPort) ;
		memcpy(sock5Req2.m_pcOther,&ulIPAddr,4);
		memcpy(sock5Req2.m_pcOther+4,&usPort,2);
		
		if( -1 ==  SendBuf((* pnSocketId),(char *)&sock5Req2,sizeof(Sock5Req2)) )
		{
			shutdown((* pnSocketId),2);  
			return -1 ; 
		}
		
		Sock5Ans2 *  sock5Ans2 ;
		memset(szRecvData,0,sizeof(szRecvData)) ;
		int nRecvDataLen = 0 ;
		while(1)
		{
			nRet = recv((* pnSocketId),szRecvData + nRecvDataLen,600 - nRecvDataLen,0);
			if(nRet == -1) 
				break ;
			nRecvDataLen += nRet ;
			if(nRecvDataLen >= sizeof(Sock5Ans2))  
				break ;
		}
		
		if(nRet == -1)
		{
			shutdown((* pnSocketId),2);  
			return -1 ; 
		}
		sock5Ans2 = (Sock5Ans2 *)szRecvData ;
		if(sock5Ans2->m_cVer != 5 || sock5Ans2->m_cRep != 0)
		{
			shutdown((* pnSocketId),2);  
			return -1 ; 
		}
		
		return 0 ;
	}
	catch(...)
	{
		return -1 ;
	}
}

static void to64frombits(unsigned char *out, const unsigned char *in, int inlen)
{
	const char base64digits[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	for (; inlen >= 3; inlen -= 3)
	{
		*out++ = base64digits[in[0] >> 2];
		*out++ = base64digits[((in[0] << 4) & 0x30) | (in[1] >> 4)];
		*out++ = base64digits[((in[1] << 2) & 0x3c) | (in[2] >> 6)];
		*out++ = base64digits[in[2] & 0x3f];
		in += 3;
	}
	if (inlen > 0)
	{
		unsigned char fragment;
		
		*out++ = base64digits[in[0] >> 2];
		fragment = (in[0] << 4) & 0x30;
		if (inlen > 1)
			fragment |= in[1] >> 4;
		*out++ = base64digits[fragment];
		*out++ = (inlen < 2) ? '=' : base64digits[(in[1] << 2) & 0x3c];
		*out++ = '=';
	}
	*out = '\0';
};


int CProxySocket::MakeLineTestReq(char * c_pBuf)
{
	SCommHead * pHead;
	pHead = (SCommHead *)c_pBuf;

	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = 0;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = LINETESTREQ;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = 0;
	pHead->m_head.SetLength(sizeof(unsigned short) * 4);
	pHead->m_usFuncNo = LINETESTREQ;
	return pHead->m_head.GetLength() + 8;
}

int CProxySocket::HttpConnect(int * pnSocketId, char *szHostIP,unsigned short usHostPort,CProxyOption * proxy)							   
{
    int	nRet = 0 ;
	UserLog("A\n");
	try
	{
		char szProxyIP[100];
		memset(szProxyIP,0,sizeof(szProxyIP));
		unicodeToAscii(proxy->getProxyIP(),szProxyIP,32);		
		if( ConnectToServer(pnSocketId,szProxyIP,proxy->getProxyPort()) == -1)  
			return -1 ;
		
		char acLineTest[256];
		int nLineTest = MakeLineTestReq(acLineTest);
		char szHttpBuff[1024] ;
		memset(szHttpBuff,0,sizeof(szHttpBuff)) ;
		//sprintf(szHttpBuff,"%s%s:%d%s","CONNECT ",szHostIP, usHostPort," HTTP/1.0\r\n"); 
		//sprintf(szHttpBuff,"GET http://www.investoday.com.cn:80 HTTP/1.0\r\n"); 
		sprintf(szHttpBuff,"GET http://%s:%d HTTP/1.0\r\ncontent-type: audio/mp3;\r\ncontent-source : invest\r\nContent-Length: %d\r\nCache-Control: no-cache\r\nProxy-Connection: Keep-Alive\r\n\r\n",szHostIP,usHostPort,nLineTest);
		//sprintf(szHttpBuff,"GET http://192.168.12.25:9999 HTTP/1.0\r\n"); 
		//sprintf(szHttpBuff,"%s%s:%d%s","CONNECT ","www.investoday.com.cn", 80," HTTP/1.0\r\n"); 
		UserLog(szHttpBuff);
		// 添加代理验证使用的用户名和密码
		CString strTmp;
		strTmp = proxy->getProxyUser();;
		strTmp.TrimLeft();
		strTmp.TrimRight();
		if( strTmp.GetLength() > 0)
		{
			CString strUser = strTmp;
			
			strTmp = proxy->getProxyPass();
			strTmp.TrimLeft();
			strTmp.TrimRight();
			
			CString strPassword = strTmp;
			
			char szAuth[1024 + 1] = {""};
			char szAuthT[1024 + 1] = {""};
			char acUser[32];
			char acPass[32];
			unicodeToAscii(strUser,acUser,32);
			unicodeToAscii(strPassword,acPass,32);
			sprintf(szAuthT, "%s:%s", acUser,acPass);
			to64frombits((UCHAR *)szAuth, (UCHAR *)szAuthT, strlen(szAuthT));
			
			sprintf(szHttpBuff,"%sProxy-Authorization: Basic %s\r\n",szHttpBuff,szAuth);
			UserLog("B\n");
			UserLog(szHttpBuff);
		}
		
		//sprintf(szHttpBuff,"%s%s",szHttpBuff,"User-Agent: MyApp/0.1\r\n\r\n");	  
		UserLog("AA\n");
		UserLog(szHttpBuff);
		if( -1 == SendBuf((* pnSocketId),szHttpBuff,strlen(szHttpBuff)) )
		{
			UserLog("C\n");
			shutdown((* pnSocketId),2) ;
			return -1 ;
		}
		if( -1 == SendBuf((* pnSocketId),acLineTest,nLineTest ))
		{
			UserLog("CC\n");
			shutdown((* pnSocketId),2) ;
			return -1 ;
		}
		
		int  nFlag = -1 ;
		int  nCurPos = 0,nErrNo = 0 ;
Labe1:
		nRet = recv((* pnSocketId),szHttpBuff+nCurPos,1000,0);
		nErrNo = WSAGetLastError() ;
		if(nRet == -1)
		{
			UserLog("D\n");
			if(nErrNo == WSAEINTR)  goto Labe1 ;
			shutdown((* pnSocketId),2) ;
			return -1 ;
		}
		UserLog(szHttpBuff);
		//if(strstr(szHttpBuff, "HTTP/1.0 200 Connection established") != NULL) //连接成功 
		if(strstr(szHttpBuff, "HTTP/1.1 200 OK") != NULL) //连接成功 
		{
			nFlag = 0 ;
		}
		nCurPos += nRet;
		if(strstr(szHttpBuff,"\r\n\r\n") == NULL)  goto Labe1 ;
		
		if(nFlag == -1)
		{
			shutdown((* pnSocketId),2);
			return -1 ;
		}
		
		return 0 ;
	}
    catch(...)
	{
		return -1 ;
	}
	
	return 0 ;
}

int CProxySocket::ConnectToServer(int * pnSocketId, char *szHostIP, unsigned short usHostPort)
{
	struct sockaddr_in ls_sockaddr ;
    int  nRet = 0,nErrNo ;
	int  nSocketId = (* pnSocketId);
	unsigned long ul = 1;
	
	try
	{
		ls_sockaddr.sin_family = AF_INET ;
		ls_sockaddr.sin_port = htons(usHostPort);
		ls_sockaddr.sin_addr.s_addr = inet_addr(szHostIP);
		
Label1:
		ioctlsocket(nSocketId, FIONBIO, (unsigned long*)&ul);
		nRet = connect(nSocketId,(struct sockaddr *)&ls_sockaddr,sizeof(struct sockaddr)) ;
		nErrNo =  WSAGetLastError() ;
		if(nRet != 0)	    	
		{
			if(nErrNo == WSAEISCONN) 
			{
				(* pnSocketId) = socket(AF_INET,SOCK_STREAM,0) ;
				closesocket(nSocketId) ;
				nSocketId = (*pnSocketId) ;
				goto Label1 ;
			}
			
			if(nErrNo == WSAEWOULDBLOCK || nErrNo == WSAEINPROGRESS)
			{
				struct timeval timeout ;
				fd_set r;
				
				FD_ZERO(&r);
				FD_SET(nSocketId, &r);
				timeout.tv_sec = LOGIN_CONNECT_OUT_TIME; 
				timeout.tv_usec = 0;
				nRet = select(nSocketId + 1, 0, &r, 0, &timeout);
				if(nRet > 0 )  
				{
					int  l_iErrLen = sizeof(int) ;
					char l_acErrTmp[100];
					memset(l_acErrTmp,0,sizeof(l_acErrTmp));
					getsockopt(nSocketId, SOL_SOCKET, SO_ERROR, l_acErrTmp, &l_iErrLen); 
					if(strlen(l_acErrTmp) == 0)  
					{
						nRet = 0 ;
					}
					else 
					{
						nRet = -1 ;
					}
				}
				else nRet = -1 ;
			}
			else   nRet = -1 ;
		}
	}
	catch(...)
	{
		return -1 ;
	}
	
    if(nRet == 0)
	{
		ul = 0 ;
		ioctlsocket(nSocketId, FIONBIO, (unsigned long*)&ul);
	}
	return  nRet ;	
}

int  CProxySocket::ConnectByHostInfo(int& rnSocketID,char *szHostIP,unsigned short usHostPort,CProxyOption * proxy)
{
	if( usHostPort <= 0 )
		return -1;		
		
	if(proxy != NULL && proxy->getIsValid()) 
	{
		if( proxy->getProxyPort() <= 0)
			return -1;
		
		if(proxy->getProxyType() == 1)
		{
			return Socket4Connect(&rnSocketID,szHostIP,usHostPort,proxy);  //使用Socket4代理
		}
		else if(proxy->getProxyType() == 2)
		{
			return Socket5Connect(&rnSocketID,szHostIP,usHostPort,proxy); //使用Socket5代理
		}
		else if(proxy->getProxyType() == 3)
		{
			return HttpConnect(&rnSocketID,szHostIP,usHostPort,proxy);  //使用Http代理
		}		
	}			
	
	return NormalConnect(&rnSocketID,szHostIP,usHostPort);
}




