#include "stdafx.h"
#include "MsgProcess.h"
#include "Common\GlobalMacro.h"

void MsgProcessEntry( CMSG msg )
{
	switch(msg.m_dwCmdId)
	{

	}

	if (msg.m_bNeedDelete)
	{
		__FREE_OBJECT(msg.m_pData);
	}
}

