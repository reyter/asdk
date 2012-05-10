#pragma once

class CPerSocketData
{
public:
	CPerSocketData(void);
	~CPerSocketData(void);
public:
	SOCKET m_Socket;
	SOCKET m_AccSocket;
};
