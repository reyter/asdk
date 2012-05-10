// MasskySocket.h: interface for the CMasskySocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROXYSOCKET_H__BB5BF017_1309_429A_AAB9_3A0BB3DFE8E4__INCLUDED_)
#define AFX_PROXYSOCKET_H__BB5BF017_1309_429A_AAB9_3A0BB3DFE8E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma pack(1)

#include <afxsock.h>

//##ModelId=409DAB330239
struct PacketHeadEx
{
	//##ModelId=409DAB33024A
	unsigned int	m_uiDataLen;		//本数据包的长度
	//##ModelId=409DAB33024B
	unsigned int	m_uiReserved;		//保留数据
};

struct SendBufHead
{
  unsigned int m_uiDatalen ;
};

//##ModelId=409DAB3202D6
enum CommStatusEx
{
	
	//##ModelId=409DAB3202E6
	CS_NotOpen = 1, 
	//##ModelId=409DAB3202E7
	CS_Open,
	//##ModelId=409DAB3202F5
	CS_Transmit,  
	CS_SetErr,   //通信设置错误
	CS_ReConnect //重新连接
};

///////////////////////Add by hzg 2004/07/13//////////////////
//用于使用各式代理连接
//代理请求晌应分析
//////////////////////////////////////////////////////////////
//Socket4请求包
struct Sock4Req  	
{
	char m_cVer;    //socket版本
	char m_cCD;
	unsigned short m_usPort;     
	unsigned long  m_ulIPAddr; 
	char m_pcOther[1];
};

//socket 4 的代理请求的回应
struct Sock4Ans
{
	char m_cVer;  //socket版本 
	char m_cCD;
};

//socket5 的代理请求1
struct Sock5Req1 
{
	char m_cVer;             //socket版本
	char m_cNMethods;        //方法个数
	char m_pcMethods[255];   //方法
}; 

//socket5 的代理请求1的回应
struct Sock5Ans1
{
	char m_cVer;         //版本
	char m_cMethod;      //方法
}; 

//socket5 的代理请求2
struct Sock5Req2
{
	char m_cVer;    	//socket版本
	char m_cCmd;        //请求方式，(是CONNECT X'01' BIND X'02' UDP ASSOCIATE X'03' )
	char m_cRsv;		//RESERVED 保留
	char m_cAtyp;		//address type (IPV4 address: X'01' DOMAINNAME: X'03' IPV6 address: X'04') 
	char m_pcOther[6];  //二进制数据流(存放目的地址和端口)
	                    //Modify by hzg 2004/07/14 old:char m_pcOther[1];
}; 

//socket5 的代理请求2的回应
struct Sock5Ans2 
{
	char m_cVer;    	//socket版本
	char m_cRep;        //返回请求成功状态 0 表示成功
	char m_cRsv;		//RESERVED 保留
	char m_cAtyp;		//address type (IPV4 address: X'01' DOMAINNAME: X'03' IPV6 address: X'04') 
	char m_pcOther[6];  //二进制数据流(存放目的地址和端口) 地址(4)+端口(2).只是针对IPV4  

};

//socket5 的用户名密码验证请求
struct AuthReq 
{ 
	char m_cVer;       //socket版本
	char m_pcUserPassInfo[502];
	//char m_cUlen; 
	//char m_pcName[6]; 
	//char m_cPLen; 
	//char m_pcPass[6]; 
}; 

//socket5 的用户名密码验证回应
struct AuthAns 
{
	char m_Ver;      //socket版本 
	char m_cStatus;  //返回请求成功状态 0 表示成功
}; 
////////////////////////////////////////////////////////////////

////////////////////和分配器通信包头结构///////////////////////
struct SStagHead
{
	unsigned int  m_uiPackLen;
    unsigned int  m_uiReserve;
};

struct SHead
{
	unsigned short  m_usVer;    //当前通讯格式版本
	unsigned int    m_uiReserve;//保留
};
///////////////////////////////////////////////////////////////
class CProxyOption;
class CProxySocket  
{
public:
	static CProxySocket* Instance();
	static void ExitInstance();
	static CProxySocket* _instance;
private:
	CProxySocket();
	virtual ~CProxySocket();
	
public:
	
	bool   IsConnect(void);               //判断是否连接正常    
 	
	/**
	*	@发送缓存数据.
	*	@param p_iSockid 套接字ID.
	*	@param p_pcBuf 缓存数据指针.
	*	@param p_iBufLen 缓存长度.
	*/
    int    SendBuf(int p_iSockid,char * p_pcBuf,int p_iBufLen) ;    //发送数据
	/**
	*	@连接到服务器.
	*	@param pnSocketId 套接字ID指针.
	*	@param szHostIP 主机IP.
	*	@param usHostPort 主机端口.
	*/
	int ConnectToServer(int * pnSocketId,char *szHostIP,unsigned short usHostPort);

	int MakeLineTestReq(char *);


	// 连接当前指定的服务器
	int ConnectByHostInfo(int& rnSocketID,char *szHostIP,unsigned short usHostPort,CProxyOption * proxy);


	/**
	*	@标准连接.
	*	@param pnSocketId 套接字ID指针.
	*	@param szHostIP 主机IP.
	*	@param usHostPort 主机端口.
	*/
	int NormalConnect(int *pnSocketId,char *szHostIP,unsigned short usHostPort);	
	
	/**
	*	@HTTP的连接.
	*	@param pnSocketId 套接字ID.
	*	@param szHostIP 主机IP.
	*	@param usHostPort 主机端口.
	*	@param proxy 代理设置类.
	*/
	int HttpConnect(int *pnSocketId, char *szHostIP,unsigned short usHostPort,CProxyOption * proxy);		            
	
	/**
	*	@Socket5的连接.
	*	@param pnSocketId 套接字ID.
	*	@param szHostIP 主机IP.
	*	@param usHostPort 主机端口.
	*	@param proxy 代理设置类.
	*/
	int Socket5Connect(int *pnSocketId, char *szHostIP,unsigned short usHostPort,CProxyOption * proxy);	


	/**
	*	@Socket4的连接.
	*	@param pnSocketId 套接字ID.
	*	@param szHostIP 主机IP.
	*	@param usHostPort 主机端口.
	*	@param proxy 代理设置类.
	*/
	int Socket4Connect(int *pnSocketId, char *szHostIP,unsigned short usHostPort,CProxyOption * proxy);		

	/**
	*	@接收缓存数据.
	*	@param p_sockid 套接字ID.
	*	@param p_pcBuf 缓存数据指针.
	*	@param p_iRecvSize 接收长度.
	*/
	int RecvBuf(int p_sockid,char * p_pcBuf,int p_iRecvSize);

	/**
	*	@清空信号.
	*	@param p_hSema 信号句柄.
	*/
	void ClearSemaphore(HANDLE p_hSema);

private:					    
    PacketHeadEx    m_PacketHead;		//包头数据结构
};

//BOOL CMasskySocket::m_bExitFlag = FALSE;
#pragma pack()
#endif // !defined(AFX_MASSKYSOCKET_H__BB5BF017_1309_429A_AAB9_3A0BB3DFE8E4__INCLUDED_)
