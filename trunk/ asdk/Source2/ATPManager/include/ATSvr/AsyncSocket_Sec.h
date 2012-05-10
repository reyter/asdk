/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 股票服务套接口.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-7-7		李伟		 创建
-------------------------------------------------------------
*/
#pragma once
#include <afxsock.h>


// CAsyncSocket_Sec 命令目标
#include "ATSvrProcessor_Sec.h"

class AFX_EXT_CLASS CAsyncSocket_Sec : public CAsyncSocket
{
	DECLARE_DYNCREATE(CAsyncSocket_Sec);
public:
	CAsyncSocket_Sec();
	virtual ~CAsyncSocket_Sec();
protected:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);			
	//virtual void OnClose(int nErrorCode);

protected:
	//CATSvrProcessor* m_pProcessor;
	CATSvrProcessor_Sec		m_Processor;
};


