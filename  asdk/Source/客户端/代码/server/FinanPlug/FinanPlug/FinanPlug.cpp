// FinanPlug.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "FinanPlugExport.h"
#include "DataProcess.h"
#include "config.h"
#include "Calc.h"
#include "FinanPlugDef.h"
#include "OtcMarket.h"
#include "..\\..\\public\\ShareData.h"
#include "..\\..\\public\\Data_struct.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

//平台提供的回调函数
_SendReply      pSendReply;
_IsUserOnline	pIsUserOnline;
_WriteOut		pWriteOut;
_PlugQuit       pPlugQuit;

CDataProcess    g_DataProc;
CShareData		g_ShareData;
SSystemParam	g_SystemParam;
COtcMarket * g_pOtcMarket;
char szVer[100] = {0};
//////////////////////////////////////////////////////////////////////////////
int _OnInit(unsigned int c_unPlugID,const char * c_pParam)
{
	std::string strExecutePath = GetExecutePath();
	strExecutePath = strExecutePath.substr(0, strExecutePath.rfind("\\") + 1);
	std::string strXmlPath = strExecutePath + "FinanPlug.xml";
	g_cfg.m_strPath = strExecutePath;
	g_cfg.Load(strXmlPath.c_str());
	g_ShareData.MapDataFile(SHARE_DATA_FILE);
	g_pOtcMarket = new COtcMarket();
	g_pOtcMarket->Init();
	return g_DataProc.OnInit(c_unPlugID,c_pParam);
}

void _OnRelease()
{
	g_pOtcMarket->Uninit();
	g_DataProc.OnRelease();
}

int _OnUpdateData(char* c_pBuf, int c_iLen)
{
	//添加代码
	return 0;
}

int _OnRequest(SMsgID* c_pMsgID, char* c_pBuf, int c_iLen)
{
	return g_DataProc.OnRequest(c_pMsgID, c_pBuf, c_iLen);
}

int _DoRequest(char* c_pBuf, int c_iLen,char * c_pRetBuf,int c_nRetMaxLen)
{
	return g_DataProc.DoRequest(c_pBuf, c_iLen,c_pRetBuf,c_nRetMaxLen);
}

void _OnSocketClose(unsigned int c_unID,unsigned int c_unSocket)
{
	//REPORT(MN,T("OnSocketClose [%u][%u]\n",c_unID,c_unSocket),RPT_INFO);
	g_DataProc.OnSocketClose(c_unID,c_unSocket);
}

void _Set_SendReplay(_SendReply c_pFunc)
{
	//设置发送函数指针
	pSendReply = c_pFunc;
}

void _Set_IsUserOnline(_IsUserOnline c_pFunc)
{
	pIsUserOnline = c_pFunc;
}

void _Set_WriteOut(_WriteOut c_pFunc)
{
	//设置发送函数指针
	pWriteOut = c_pFunc;
}

void _Set_PlugQuit(_PlugQuit c_pFunc)
{
	//设置通知退出处理函数指针
	pPlugQuit = c_pFunc;
}

void GetModuleVer(char** pBuf)
{
	char* pCommxVer = NULL;
	CommxVer(&pCommxVer);

	strcpy_s((char*)szVer,	100, pCommxVer);
	int nLen = (int)strlen(szVer);
	strcpy_s((char*)szVer+nLen, 100-nLen, FINANPLUGVER);

	*pBuf = (char*)szVer;
}
