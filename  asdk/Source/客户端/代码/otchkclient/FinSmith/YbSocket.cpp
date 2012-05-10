// YbSocket.cpp : 实现文件
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


// CYbSocket 成员函数

void CYbSocket::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnConnect(nErrorCode);
}

void CYbSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnReceive(nErrorCode);
}

void CYbSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnClose(nErrorCode);
}
