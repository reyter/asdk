/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨����ƽ̨��������
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-7-7		��ΰ		 ����
-------------------------------------------------------------
*/
#pragma once
#include <afxsock.h>

#include <list>
using namespace std;
#include "..\\include\\UTI\\TradingHandler.h"


class CAsyncSocket_Svr;

// CATPListenSocket ����Ŀ��

class AFX_EXT_CLASS CATPListenSocket : public CAsyncSocket
{
public:



	/**
	@param nServiceType ��������
			1   ֤ȯ����
			2   �ڻ�����.
	*/ 	
	CATPListenSocket(SERVICE_TYPE nServiceType);
	virtual ~CATPListenSocket();

	/**
	��ָ���˿��Ͽ�������.
	@param nPort ����˿�.
	*/ 	
	bool Begin(UINT nPort);


	/**
	ֹͣ����
	*/	
	void Stop();

	/**
	ȡ������.
	*/	
	int GetConnectionCount();



    


protected:
	/**
	��������.
	*/ 	
	virtual void OnAccept(int nErrorCode);


protected:
	/**
	���պ�������Ӧ����.
	*/	
	int		 m_nServiceType;

	
private:
	/**
	֪ͨɾ��.
	*/
	void OnDeleteClient(CAsyncSocket_Svr* pSocket);

	/**
	���ڷ���Ľӿڱ�.
	*/
	list<void*> m_lsSvrSocket;

	CRITICAL_SECTION m_cs;

	friend class CAsyncSocket_Svr;

	void SendAlgoStatus();

	CWinThread*			m_pWinThreadSendAlgo;

	//�����㷨״̬�߳�.
	static UINT	SendAlgoStatusThread(LPVOID lParam);
		
};


