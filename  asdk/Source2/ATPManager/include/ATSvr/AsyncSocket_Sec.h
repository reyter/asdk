/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 ��Ʊ�����׽ӿ�.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-7-7		��ΰ		 ����
-------------------------------------------------------------
*/
#pragma once
#include <afxsock.h>


// CAsyncSocket_Sec ����Ŀ��
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


