/**
* @Copyright 深圳市创真科技有限公司(www.hh.com.cn)
* @System	 通用通信库(Common Communication Environment Core)
* @Brief	 网络数据处理类
* @Author	 wli
* @Date      2010-10-21
*/

#pragma once

#ifndef __CCEPROCESSOR_H_
#define __CCEPROCESSOR_H_

#include "CCEDefine.h"

#define CCE_DEFAULT_RECV_LEN (8*1024)


class CHHWPConnection;
/**
*	 网络数据处理类
*	 提供接收与发送原始数据的接口.
*
*/ 
class AFX_EXT_CLASS CCCEProcessor : public CObject
{
	DECLARE_DYNCREATE(CCCEProcessor);

public:
	CCCEProcessor();
	virtual ~CCCEProcessor();

public:

	//由于3DES，要求数据长度是8的整数倍，因此需要取数据长度到8的最大填充.
	static int GetSafe3DesEncryptLength(int block_len);
	static int HHSafe3DesDecrypt(char* key,  int keylen, BYTE* source_buf, int block_len,  BYTE* dest_buf);
	static int HHSafe3DesEncrypt(char* key,  int keylen, BYTE* source_buf, int block_len,  BYTE* dest_buf);

public:

	/**
	* 设置日志参数.
	* @param pLogFun 回调函数
	* @param lParam  回调函数回调时传递的参数.
	*/	
	static CCE_LOG_FUN SetCCELogFun(CCE_LOG_FUN pLogFun,LPVOID lParam);

	/**
	* 创建一个网络服务。
	* @param szSvrName			服务名。
	* @param nPort				网络服务要绑定的侦听端口。
	* @param pRuntimeCalss		服务响应类，必须为CCCEProcessor的子类.
								并且要支持动态创建(DECLARE_DYNCREATE)
	* @param lParam             附加参数，该参数创建后设置到 m_lParam 变量中.
	* @param 返回服务是否创建成功。
	*/
	static bool CreateServer(LPCTSTR szSvrName,USHORT nPort,CRuntimeClass* pRuntimeClass,
		LPVOID lParam=NULL);


	/**
	*	发送数据.
	*	数据会放入缓存中进行发送.
	*/
	int SendRawData(const void* pData,int nLength);


	/**
	*	发送数据,
	*	发送完该数据包后，自动关闭此连接.(如发送注销信息后，断开连接)
	*/
	int SendRawDataThenClose(const void* pData,int nLength);


	/**
	* 设置接收缓存.
	* @param nSize 如果接收缓存大于8k,则设置为指定的值。否则，则自动设置为8k.
	* 
	*/
	void SetRecvBufferSize(int nSize);
	


	/**
	*	关闭连接.
	*	关闭连接后，会调用 OnClose，并且会delete this.
	*/ 
	void  CloseConnection();


	/**
	* 取状态.
	*/
	void   GetStatistics(__int64* pI64Send,__int64* pI64Recv);


	/**
	* 取对方IP地址.
	*/
	void   GetPeerAddr(sockaddr_in& addr);


	/**
	* 取本方IP地址.
	*/
	void  GetThisAddr(sockaddr_in& addr);

	
	//子类可以处理的通讯事件回调函数
protected:
	/**
	*	从网络上接收到数据的回调函数
	*	@param pData		数据起始地址
	*	@param nLength		数据长度
	*/
	virtual void OnRecvRawData(const void* pData,int nLength);

	/**
	*  发送数据完成的回调函数。
	*/
	virtual void OnSendDataFinish(const void* pData,int nLength);

	/**
	*	网络中断，会调用该函数，然后删除对应的Processor.
	*	因此，派生类，可在此做一些资源释放性等额外的工作。
	*	如果返回True ,表示，需要删除该Processor.否则，不删除.
	*	本基类默认返回TRUE.
	*/
	virtual bool OnClose();

	
	/**
	*	 网络连接已经建立.
	*/ 	
	virtual void OnConnectionInitFinish();


private:
	/**
	*	设置连接指针，
	*	仅供本库内库调用
	*/
	void SetConnectionPointer(CHHWPConnection* pConnection);

	friend class CHHWPConnection;			//友元类

	

protected:
	CHHWPConnection* m_pConnection;
	LPVOID	m_lParam;						//创建时的附加参数

private:
	int m_nRecvBufferSize;
	
};


#endif //__CCEPROCESSOR_H_