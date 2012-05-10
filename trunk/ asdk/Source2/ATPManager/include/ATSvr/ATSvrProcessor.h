/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 实时行情类.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-1		李伟		 创建
-------------------------------------------------------------
*/
#pragma once

#include "OpenTDProtocol.h"

class CAsyncSocket_Svr;
#include "..\Include\AlgoEngine\AlgoManager.h"
#include "..\Include\AlgoEngine\AlgoUser.h"

/**
* 算法交易服务器服务类,用于接收和应答客户端发送来的数据报文.
*/
class AFX_EXT_CLASS CATSvrProcessor
{
public:
	CATSvrProcessor(void);
	virtual ~CATSvrProcessor(void);

	//发送算法交易平台算法状态信息.
	virtual void SendAlgoStatus();

	/**
	原始的接收数据.
	*/
	void OnReceive(char* pData, int nLength);


	void OnReceiveFilter(char* pMsg,int nLength);

	/**
	接收到消息.了类重载此函数，以完成其自有逻辑的处理.
	*/
	virtual void OnReceiveMsg(char* pMsg,int nLegnth);


	/**
	登录消息
	*/ 	
	virtual bool OnLoginMsg(const UTI_LoginRequest* pLogin,UTI_LoginAnswer& answer)=0;


	/**
	发送消息.
	@param nMsgType	消息类型
	@param pMsgBody 消息首地址
	@param nBodyLegnth 消息长度
	*/ 
	void SendATPMsg(int nMsgType,void* pMsgBody,int nBodyLength);

	/**
	发送带一个头的消息.
	@param nMsgType	消息类型
	@param pMsgHead 消息头
	@param nHeadLength 消息头长度.
	@param pMsgBody 消息首地址
	@param nBodyLegnth 消息长度	
	*/ 	
	void SendATPMsg(int nMsgType,void* pMsgHead,int nHeadLength,void* pMsgBody,int nBodyLength);

	
	void SendATPSystemMsg(int nType,CString strMsg);


	/**
	发送消息，并在消息发送后，关闭连接.
	@param nMsgType	消息类型
	@param pMsgBody 消息首地址
	@param nBodyLegnth 消息长度
	*/ 	
	void  SendATPMsgThenClose(int nMsgType,void* pMsgBody,int nBodyLength);

    /**
	关闭处理器，并清除内存
	*/
	//void  Close();

	virtual void GetTradingHandler(CTradingHandler_Security*& pHandlerSec,
		CTradingHandler_Futures*& pHandlerFuture)=0;

protected:
	/**
	消息顺序号.
	*/ 	
	volatile  long    m_lOrder;


	/**
	是否已经成功登录
	*/
	bool			  m_bLoginOk;


	
	/**
	登录消息处理
	*/ 	
	void OnLoginMsg(char* pMsg,int nLength);

	/**
	查询算法信息.
	*/	
	void OnQueryAlgoInfo();


	/**
	查询算法参数信息
	*/ 
	void OnQueryAlgoParamter(char* pMsg,int nLength);


	/**
	算法方式下单.
	让子类去重写
	*/
	virtual void OnAlgoOrder(char* pMsg,int nLength);


	/**
	在线算法状态查询
	*/ 	
	void OnQueryCurrentAlgoStatus(char* pMsg,int nLength);


protected:	
	char*               m_pRealData;
	int					m_nAllocRealDataItem;
	int					m_nRecvOffset;	//接收到数据的内容.

	ATP_User_Info		m_UserInfo;


	//发送消息时，生成消息序.
	long GetMsgOrder(); 

	//内部函数，将多余的内存，归并到m_pRealData上.
	void MergeMem(char* pData,int nLength);


	
	//取当前时间.
	static int GetCurrentMsgTime();

public:
	CAsyncSocket_Svr*	m_pSocket;	
};
