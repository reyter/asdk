// YbSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinSmith.h"
#include "YbSocket.h"


// CYbSocket

CYbSocket::CYbSocket()
{
}

CYbSocket::~CYbSocket()
{
}


// CYbSocket ��Ա����

void CYbSocket::OnConnect(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnConnect(nErrorCode);
}

void CYbSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnReceive(nErrorCode);
}

void CYbSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnClose(nErrorCode);
}
