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
	unsigned int	m_uiDataLen;		//�����ݰ��ĳ���
	//##ModelId=409DAB33024B
	unsigned int	m_uiReserved;		//��������
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
	CS_SetErr,   //ͨ�����ô���
	CS_ReConnect //��������
};

///////////////////////Add by hzg 2004/07/13//////////////////
//����ʹ�ø�ʽ��������
//����������Ӧ����
//////////////////////////////////////////////////////////////
//Socket4�����
struct Sock4Req  	
{
	char m_cVer;    //socket�汾
	char m_cCD;
	unsigned short m_usPort;     
	unsigned long  m_ulIPAddr; 
	char m_pcOther[1];
};

//socket 4 �Ĵ�������Ļ�Ӧ
struct Sock4Ans
{
	char m_cVer;  //socket�汾 
	char m_cCD;
};

//socket5 �Ĵ�������1
struct Sock5Req1 
{
	char m_cVer;             //socket�汾
	char m_cNMethods;        //��������
	char m_pcMethods[255];   //����
}; 

//socket5 �Ĵ�������1�Ļ�Ӧ
struct Sock5Ans1
{
	char m_cVer;         //�汾
	char m_cMethod;      //����
}; 

//socket5 �Ĵ�������2
struct Sock5Req2
{
	char m_cVer;    	//socket�汾
	char m_cCmd;        //����ʽ��(��CONNECT X'01' BIND X'02' UDP ASSOCIATE X'03' )
	char m_cRsv;		//RESERVED ����
	char m_cAtyp;		//address type (IPV4 address: X'01' DOMAINNAME: X'03' IPV6 address: X'04') 
	char m_pcOther[6];  //������������(���Ŀ�ĵ�ַ�Ͷ˿�)
	                    //Modify by hzg 2004/07/14 old:char m_pcOther[1];
}; 

//socket5 �Ĵ�������2�Ļ�Ӧ
struct Sock5Ans2 
{
	char m_cVer;    	//socket�汾
	char m_cRep;        //��������ɹ�״̬ 0 ��ʾ�ɹ�
	char m_cRsv;		//RESERVED ����
	char m_cAtyp;		//address type (IPV4 address: X'01' DOMAINNAME: X'03' IPV6 address: X'04') 
	char m_pcOther[6];  //������������(���Ŀ�ĵ�ַ�Ͷ˿�) ��ַ(4)+�˿�(2).ֻ�����IPV4  

};

//socket5 ���û���������֤����
struct AuthReq 
{ 
	char m_cVer;       //socket�汾
	char m_pcUserPassInfo[502];
	//char m_cUlen; 
	//char m_pcName[6]; 
	//char m_cPLen; 
	//char m_pcPass[6]; 
}; 

//socket5 ���û���������֤��Ӧ
struct AuthAns 
{
	char m_Ver;      //socket�汾 
	char m_cStatus;  //��������ɹ�״̬ 0 ��ʾ�ɹ�
}; 
////////////////////////////////////////////////////////////////

////////////////////�ͷ�����ͨ�Ű�ͷ�ṹ///////////////////////
struct SStagHead
{
	unsigned int  m_uiPackLen;
    unsigned int  m_uiReserve;
};

struct SHead
{
	unsigned short  m_usVer;    //��ǰͨѶ��ʽ�汾
	unsigned int    m_uiReserve;//����
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
	
	bool   IsConnect(void);               //�ж��Ƿ���������    
 	
	/**
	*	@���ͻ�������.
	*	@param p_iSockid �׽���ID.
	*	@param p_pcBuf ��������ָ��.
	*	@param p_iBufLen ���泤��.
	*/
    int    SendBuf(int p_iSockid,char * p_pcBuf,int p_iBufLen) ;    //��������
	/**
	*	@���ӵ�������.
	*	@param pnSocketId �׽���IDָ��.
	*	@param szHostIP ����IP.
	*	@param usHostPort �����˿�.
	*/
	int ConnectToServer(int * pnSocketId,char *szHostIP,unsigned short usHostPort);

	int MakeLineTestReq(char *);


	// ���ӵ�ǰָ���ķ�����
	int ConnectByHostInfo(int& rnSocketID,char *szHostIP,unsigned short usHostPort,CProxyOption * proxy);


	/**
	*	@��׼����.
	*	@param pnSocketId �׽���IDָ��.
	*	@param szHostIP ����IP.
	*	@param usHostPort �����˿�.
	*/
	int NormalConnect(int *pnSocketId,char *szHostIP,unsigned short usHostPort);	
	
	/**
	*	@HTTP������.
	*	@param pnSocketId �׽���ID.
	*	@param szHostIP ����IP.
	*	@param usHostPort �����˿�.
	*	@param proxy ����������.
	*/
	int HttpConnect(int *pnSocketId, char *szHostIP,unsigned short usHostPort,CProxyOption * proxy);		            
	
	/**
	*	@Socket5������.
	*	@param pnSocketId �׽���ID.
	*	@param szHostIP ����IP.
	*	@param usHostPort �����˿�.
	*	@param proxy ����������.
	*/
	int Socket5Connect(int *pnSocketId, char *szHostIP,unsigned short usHostPort,CProxyOption * proxy);	


	/**
	*	@Socket4������.
	*	@param pnSocketId �׽���ID.
	*	@param szHostIP ����IP.
	*	@param usHostPort �����˿�.
	*	@param proxy ����������.
	*/
	int Socket4Connect(int *pnSocketId, char *szHostIP,unsigned short usHostPort,CProxyOption * proxy);		

	/**
	*	@���ջ�������.
	*	@param p_sockid �׽���ID.
	*	@param p_pcBuf ��������ָ��.
	*	@param p_iRecvSize ���ճ���.
	*/
	int RecvBuf(int p_sockid,char * p_pcBuf,int p_iRecvSize);

	/**
	*	@����ź�.
	*	@param p_hSema �źž��.
	*/
	void ClearSemaphore(HANDLE p_hSema);

private:					    
    PacketHeadEx    m_PacketHead;		//��ͷ���ݽṹ
};

//BOOL CMasskySocket::m_bExitFlag = FALSE;
#pragma pack()
#endif // !defined(AFX_MASSKYSOCKET_H__BB5BF017_1309_429A_AAB9_3A0BB3DFE8E4__INCLUDED_)
