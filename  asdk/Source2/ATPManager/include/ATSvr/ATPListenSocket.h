/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法交易平台侦听服务
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-7-7		李伟		 创建
-------------------------------------------------------------
*/
#pragma once
#include <afxsock.h>

#include <list>
using namespace std;
#include "..\\include\\UTI\\TradingHandler.h"


class CAsyncSocket_Svr;

// CATPListenSocket 命令目标

class AFX_EXT_CLASS CATPListenSocket : public CAsyncSocket
{
public:



	/**
	@param nServiceType 服务类型
			1   证券服务
			2   期货服务.
	*/ 	
	CATPListenSocket(SERVICE_TYPE nServiceType);
	virtual ~CATPListenSocket();

	/**
	在指定端口上开启服务.
	@param nPort 服务端口.
	*/ 	
	bool Begin(UINT nPort);


	/**
	停止服务
	*/	
	void Stop();

	/**
	取连接数.
	*/	
	int GetConnectionCount();



    


protected:
	/**
	接收连接.
	*/ 	
	virtual void OnAccept(int nErrorCode);


protected:
	/**
	接收后用于响应在类.
	*/	
	int		 m_nServiceType;

	
private:
	/**
	通知删除.
	*/
	void OnDeleteClient(CAsyncSocket_Svr* pSocket);

	/**
	正在服务的接口表.
	*/
	list<void*> m_lsSvrSocket;

	CRITICAL_SECTION m_cs;

	friend class CAsyncSocket_Svr;

	void SendAlgoStatus();

	CWinThread*			m_pWinThreadSendAlgo;

	//发送算法状态线程.
	static UINT	SendAlgoStatusThread(LPVOID lParam);
		
};


