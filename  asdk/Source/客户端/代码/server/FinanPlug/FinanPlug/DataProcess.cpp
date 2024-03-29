//DataProcess.cpp
#include "stdafx.h"
#include "DataProcess.h"
#include "time.h"
#include "config.h"
#include "ShortSocket.h"
#include "Calc.h"
#include "StockQueue.h"
#include "OtcMarket.h"

#include "../../public/data_struct.h"
#include "../../public/ShareData.h"
#include "../../public/zip/zip.h"
#include "../../public/zip/zlib.h"
#include "../../public/deslib.h"

extern _WriteOut		pWriteOut;
extern _SendReply		pSendReply;
extern _IsUserOnline	pIsUserOnline;
extern _PlugQuit		pPlugQuit;

extern CShareData		g_ShareData;
extern SSystemParam		g_SystemParam;
extern COtcMarket		*g_pOtcMarket;

#pragma warning(disable:4018)
//////////////////////////////////////////////////////////////////

CDataProcess::CDataProcess()
{
	g_SystemParam.Init();
	m_unPlugID = 0;
	m_pWorkThread = NULL;
	m_bRun = TRUE;

	pIsUserOnline = 0;
	m_nSendBufSize = 1024 * 512 * 4;
	m_pSendBuf = (char *)malloc(m_nSendBufSize);
	m_pZipBuf = (char *)malloc(1024 * 512 * 4);
}

CDataProcess::~CDataProcess()
{
	if (m_pSendBuf != NULL)
		free(m_pSendBuf);
	if (m_pZipBuf)
		free(m_pZipBuf);
}

int CDataProcess::OnInit(unsigned int c_unPlugID, const char * c_pParam)
{
	InitDB();

	if (!m_dataQueue.Init())
	{
		REPORT(MN, T("初始化数据请求队列失败\n"), RPT_ERROR);
		return -1;
	}

	m_pWorkThread = new CWorkThread(_WorkThread, this);
	if (m_pWorkThread == NULL)
	{
		REPORT(MN, T("创建线程失败，new CWorkThread() failed\n"), RPT_ERROR);
		return -1;
	}
	if (!m_pWorkThread->Start())
	{
		REPORT(MN, T("启动线程失败，m_pWorkThread->Start() failed\n"), RPT_ERROR);
		return -1;
	}

	//记录插件标识
	m_unPlugID = c_unPlugID;
	return 0;
}

int CDataProcess::InitDB()
{
	if (!m_sqlServUser.Open(g_cfg.m_strUDBIP.c_str(), g_cfg.m_strUDBName.c_str(),
		g_cfg.m_strUDBUserName.c_str(), g_cfg.m_strUDBPassword.c_str()))
	{
		REPORT(MN, T("打开用户数据库[%s:%s]失败\n", g_cfg.m_strUDBIP.c_str(), g_cfg.m_strUDBName.c_str()), RPT_ERROR);
		return -1;
	}
	REPORT(MN, T("打开用户数据库[%s:%s]成功\n", g_cfg.m_strUDBIP.c_str(), g_cfg.m_strUDBName.c_str()), RPT_INFO);
	m_sqlServUser.SetCursorLocation(adUseClient);
	return 0;
}

void CDataProcess::OnRelease()
{
	m_bRun = FALSE;

	if (m_pWorkThread != NULL)
	{
		m_pWorkThread->Stop();
		delete m_pWorkThread;
		m_pWorkThread = NULL;
	}

	m_dataQueue.Release();
}

int CDataProcess::OnRequest(SMsgID* c_pMsgID, char* c_pBuf, int c_iLen)
{
	if (c_pMsgID == NULL || c_pBuf == NULL || c_iLen <= 0)
	{
		REPORT(MN, T("OnRequest()参数有误，c_pMsgID=0x%x c_pBuf=0x%x c_iLen=%d\n", c_pMsgID, c_pBuf, c_iLen), RPT_ERROR);
		return -1;
	}

	tagReturnMsgID* pMsgID = new tagReturnMsgID;
	if (pMsgID == NULL)
	{
		REPORT(MN, T("pMsgID = new tagReturnMsgID failed\n"), RPT_ERROR);
		return -1;
	}

	pMsgID->id.m_unID     = c_pMsgID->m_unID;
	pMsgID->id.m_unSocket = c_pMsgID->m_unSocket;
	pMsgID->pBuf = new char[c_iLen];
	if (pMsgID->pBuf == NULL)
	{
		REPORT(MN, T("分配内存[pMsgID->pBuf]失败\n"), RPT_ERROR);
		return -1;
	}
	memcpy(pMsgID->pBuf,c_pBuf,c_iLen);
	pMsgID->nBufSize = c_iLen;

	m_dataQueue.PushBack(pMsgID);
	return 0;
}

UINT CDataProcess::_WorkThread(void* pParam)
{
	CDataProcess* pDataPro = (CDataProcess*)pParam;
	return pDataPro->WorkThread();
}

bool CDataProcess::IsWorkDay(int c_nDay)
{
	CRecordSet recset(&m_sqlServUser);
	char acSql[256];
	sprintf(acSql,"select convert(int,CONVERT(varchar(12),LogDate,112)) from Holidays where convert(int,CONVERT(varchar(12),LogDate,112))=%d",c_nDay);
	if (!recset.Open(acSql))
	{
		REPORT(MN, T("Open [%s] failed\n", acSql), RPT_ERROR);
		if (CheckUserDBConnect())
		{
			if (!recset.Open(acSql))
				return true;
		}
		else
			return true;
	}

	if (recset.GetRecordCount() > 0)
	{
		recset.Close();
		return false;
	}
	recset.Close();
	return true;
}

int CDataProcess::DoRequest(char * c_pIn,int c_nInLen, char * c_pOut,int c_nOutMaxLen)
{
	char* pBufPos = c_pIn;
	tagPackHead* packHead = (tagPackHead*)pBufPos;
	pBufPos += sizeof(tagPackHead);

	if (packHead->comxHead.Length != c_nInLen - sizeof(CommxHead))
	{
		REPORT(MN, T("接收数据大小[%d]与包头定义大小[%d]不一致\n", c_nInLen - sizeof(CommxHead),packHead->comxHead.Length), RPT_ERROR);			
		return -1;			
	}
		
	unsigned short us1,us2;
	unsigned int nOffset = sizeof(tagPackHead);
	for(int i=0; i<packHead->nReqCount; i++)
	{
		unsigned short* pPackType = (unsigned short*)pBufPos;
		REPORT(MN, T("DoRequest[%d]............................\n", *pPackType), RPT_INFO);
		switch(*pPackType)   //报文类型
		{
			case PT_USER_CHANGEPASSWORD://更改密码
			{
				ProcUserChangePassword(pBufPos, nOffset,c_pOut,c_nOutMaxLen,false);
				pBufPos += sizeof(unsigned short) + sizeof(unsigned int) + 30;
				break;
			}
			case PT_USER_CHANGEPASSWORD_DES://更改密码
			{
				ProcUserChangePassword(pBufPos, nOffset,c_pOut,c_nOutMaxLen,true);
				pBufPos += sizeof(unsigned short) + sizeof(unsigned int) + 30;
				break;
			}
			case PT_PRIVATE_USER_LOG_DES://登陆密码DES
			{
				ProcUserInfoLogByPass(pBufPos, nOffset,c_pOut,c_nOutMaxLen,true);				
				pBufPos += sizeof(unsigned short) + sizeof(unsigned int) + 30;
				break;
			}
			case PT_STOCKINFO:    //STOCKINFO
			{
				ProcStockInfo(pBufPos, nOffset,c_pOut,c_nOutMaxLen);
				pBufPos += sizeof(unsigned short) + sizeof(unsigned int) * 3;
				break;
			}
			case PT_MAKERSTOCK:    //Maker-Stock
			{
				ProcMakerStock(pBufPos, nOffset,c_pOut,c_nOutMaxLen);
				pBufPos += sizeof(unsigned short) + sizeof(unsigned int);
				break;
			}/*
			case PT_POSITION:    //持仓
			{
				ProcPosition(pBufPos, nOffset,m_pSendBuf,m_nSendBufSize);
				pBufPos += sizeof(unsigned short) + sizeof(unsigned int);
				break;
			}
			case PT_CONSIGN:    //委托
			{
				ProcConsign(pBufPos, nOffset,m_pSendBuf,m_nSendBufSize);
				pBufPos += sizeof(unsigned short) + sizeof(unsigned int);
				break;
			}
			case PT_CONSIGN_HISTORY:    //委托历史
			{
				ProcConsignHistory(pBufPos, nOffset,m_pSendBuf,m_nSendBufSize);
				pBufPos += sizeof(unsigned short) + sizeof(tagConsignHistory);
				break;
			}
			case PT_BARGAIN:    //成交
			{
				ProcBargain(pBufPos, nOffset,m_pSendBuf,m_nSendBufSize);
				pBufPos += sizeof(unsigned short) + sizeof(tagBargainReq);
				break;
			}*/
			case PT_COMMAND:
			{
				ProcCommand(pBufPos, nOffset,c_pOut,c_nOutMaxLen);
				break;
			}
			case PT_VERSION:
			{
				ProcReqVersion(pBufPos, nOffset,c_pOut,c_nOutMaxLen);
				pBufPos += sizeof(unsigned short) + sizeof(unsigned int);
				break;
			}
			default:
			{
				REPORT(MN, T("不能处理DoRequest报文类型[%d]\n", *pPackType), RPT_ERROR);
				return -2;
			}
		}

		if (nOffset > sizeof(tagPackHead))
		{
			packHead->comxHead.Length = nOffset - sizeof(CommxHead);
			memcpy(c_pOut, packHead, sizeof(tagPackHead));

			REPORT(MN, T("报文处理结束 DoRequest,[%d]\n",nOffset), RPT_INFO);
			return nOffset;
		}		
	}
	return 0;
}

UINT CDataProcess::WorkThread()
{
	m_bRun = TRUE;
	REPORT(MN,T("WorkThread Runing\n"),RPT_INFO);
	while(m_bRun)
	{
		tagReturnMsgID* pMsgID = m_dataQueue.PopFront();
		if (pMsgID == NULL)
			continue;
		//处理
		char* pBufPos = pMsgID->pBuf;
		tagPackHead* packHead = (tagPackHead*)pBufPos;
		pBufPos += sizeof(tagPackHead);

		if (packHead->comxHead.Length != pMsgID->nBufSize - sizeof(CommxHead))
		{
			REPORT(MN, T("接收数据大小[%d]与包头定义大小[%d]不一致\n", pMsgID->nBufSize - sizeof(CommxHead),packHead->comxHead.Length), RPT_ERROR);
			//释放	
			delete []pMsgID->pBuf;
			delete pMsgID;
			continue;
		}
		
		unsigned short us1,us2;
		unsigned int nOffset = sizeof(tagPackHead);
		for(int i=0; i<packHead->nReqCount; i++)
		{
			unsigned short* pPackType = (unsigned short*)pBufPos;
			REPORT(MN, T("正在处理业务[%d][id=%d][socket=%d]\n", *pPackType,pMsgID->id.m_unID,pMsgID->id.m_unSocket), RPT_INFO);
			switch(*pPackType)   //报文类型
			{
			case PT_USER_CHANGEPASSWORD:
				{
					ProcUserChangePassword(pBufPos, nOffset,m_pSendBuf,m_nSendBufSize,false);
					pBufPos += sizeof(unsigned short) + sizeof(unsigned int) + 30;
					break;
				}
			case PT_MAKERSTOCK:    //组合
				{
					ProcMakerStock(pBufPos, nOffset,m_pSendBuf,m_nSendBufSize);
					pBufPos += sizeof(unsigned short) + sizeof(unsigned int);
					break;
				}
			case PT_POSITION:    //持仓
				{
					ProcPosition(pBufPos, nOffset,m_pSendBuf,m_nSendBufSize);
					pBufPos += sizeof(unsigned short) + sizeof(unsigned int);
					break;
				}
			case PT_CONSIGN:    //委托
			{
				ProcConsign(pBufPos, nOffset,m_pSendBuf,m_nSendBufSize);
				pBufPos += sizeof(unsigned short) +sizeof(tagUserPass) +  sizeof(tagConsignReq);
				break;
			}
			case PT_MAKERCONSIGN:    //委托
			{
				ProcMakerConsign(pBufPos, nOffset,m_pSendBuf,m_nSendBufSize);
				pBufPos += sizeof(unsigned short) +sizeof(tagUserPass) + sizeof(int)+ sizeof(tagMakerConsignReq);
				break;
			}
			case PT_CONSIGN_HISTORY:    //委托历史
			{
				ProcConsignHistory(pBufPos, nOffset,m_pSendBuf,m_nSendBufSize);
				pBufPos += sizeof(unsigned short) + sizeof(tagConsignHistory);
				break;
			}
			case PT_BARGAIN:    //成交
			{
				ProcBargain(pBufPos, nOffset,m_pSendBuf,m_nSendBufSize);
				pBufPos += sizeof(unsigned short) + sizeof(tagBargainReq);
				break;
			}
			case PT_COMMAND:
				{
					ProcCommand(pBufPos, nOffset,m_pSendBuf,m_nSendBufSize);
					break;
				}
			case PT_VERSION:
				{
					ProcReqVersion(pBufPos, nOffset,m_pSendBuf,m_nSendBufSize);
					pBufPos += sizeof(unsigned short) + sizeof(unsigned int);
					break;
				}
			default:
				{
					REPORT(MN, T("不能处理的报文类型[%d]\n", *pPackType), RPT_ERROR);
				}
			}
		}

		if (nOffset > sizeof(tagPackHead))
		{
			packHead->comxHead.Length = nOffset - sizeof(CommxHead);
			memcpy(m_pSendBuf, packHead, sizeof(tagPackHead));

			pSendReply(&pMsgID->id, m_pSendBuf, nOffset);
			REPORT(MN, T("报文处理结束,[%d]\n",nOffset), RPT_INFO);
		}
		memset(m_pSendBuf, 0, m_nSendBufSize);

		//释放	
		delete []pMsgID->pBuf;
		delete pMsgID;
	}
	return 0;
}

BOOL CDataProcess::CheckUserDBConnect()
{
	int nRetry  = 0;
	if (!Lock())
		return FALSE;
	if (!m_sqlServUser.IsConnectNormal("Member"))
	{
		REPORT(MN, T("连接断开，正在重连...\n"), RPT_WARNING);
		while (m_bRun)  //重连
		{
			if (m_sqlServUser.Reconnect())
			{
				UnLock();
				return TRUE;
			}
			if (++nRetry > 10)
				break;
			Sleep(1000);
		}
	}
	UnLock();
	return FALSE;
}

int CDataProcess::InitStockInfo()
{
	int nStockCount = 0;
	if (g_ShareData.m_lpData == NULL || g_ShareData.m_lpStock == NULL)
		return 0;
	CRecordSet recset(&m_sqlServUser);
	REPORT(MN, T("InitStockInfo Begin \n"), RPT_INFO);

	char acSql[256];
	strcpy(acSql,"select stockid,stockdisplay,dbo.f_lang(StockName,'cn') stockname,totalamount,openprice from Stock where status=1 order by stockid");
	//strcpy(acSql,"select stockid,stockdisplay, stockname,totalamount,openprice from Stock where status=1 order by stockid");
	if (!recset.Open(acSql))
	{
		REPORT(MN, T("Open [%s] failed\n", acSql), RPT_ERROR);
		if (CheckUserDBConnect())
		{
			if (!recset.Open(acSql))
				return -1;
		}
		else
			return -1;
	}

	nStockCount = (unsigned short)recset.GetRecordCount();
	if (nStockCount < 0)
		nStockCount = 0;

	///////////////////////////////////////////////////////////////////////////
	REPORT(MN,T("STOCKINFO nStockCount = %d\n",nStockCount),RPT_INFO);
	int nTmp = 0;
	double dTmp = 0;
	Quote *pQuote;
	
	for (int i=0; i<nStockCount; i++)
	{
		pQuote = (Quote *)g_ShareData.GetStockByIndex(i,false);
		recset.GetCollect("STOCKID", pQuote->nStockId);
		recset.GetCollect("STOCKDISPLAY",pQuote->szStockCode,16);
		recset.GetCollect("STOCKNAME",pQuote->szStockDisplay,64);
		recset.GetCollect("STOCKNAME", pQuote->szStockName,64);
		recset.GetCollect("TOTALAMOUNT", pQuote->dZgb);

		recset.GetCollect("openprice", dTmp);
		pQuote->ipoprice = int(dTmp * 1000);//IPO价格
		recset.MoveNext();
	}
	recset.Close();

	for(int n=0; n<nStockCount; n++)
	{
		pQuote = (Quote *)g_ShareData.GetStockByIndex(n,true);
		if (pQuote)
		{
			pQuote->zrsp = GetZRSP(pQuote->nStockId);
		}
	}
	g_ShareData.SetStockCount(nStockCount);
	return nStockCount;
}

int CDataProcess::GetSystemParam()
{
	CRecordSet recset(&m_sqlServUser);

	char acSql[256];
	sprintf(acSql,"select * from SystemParameter");
	if (!recset.Open(acSql))
	{
		REPORT(MN, T("Open [%s] failed\n", acSql), RPT_ERROR);
		if (CheckUserDBConnect())
		{
			if (!recset.Open(acSql))
				return 0;
		}
		else
			return 0;
	}

	if (recset.GetRecordCount() == 0)
	{
		recset.Close();
		return 0;
	}	
	double dTmp = 0;
	
	recset.GetCollect("DailyLimit", dTmp);	
	g_SystemParam.fUpLimit = dTmp;
	recset.GetCollect("DownLimit", dTmp);
	g_SystemParam.fDownLimit = dTmp;
	recset.GetCollect("BuyFee", dTmp);
	g_SystemParam.fBuyFeeRate = dTmp;
	recset.GetCollect("SellFee", dTmp);
	g_SystemParam.fSaleFeeRate = dTmp;

	recset.GetCollect("OpenTimeAM", g_SystemParam.nOpenAM);
	recset.GetCollect("CloseTimeAM", g_SystemParam.nCloseAM);
	recset.GetCollect("OpenTimePM", g_SystemParam.nOpenPM);
	recset.GetCollect("CloseTimePM", g_SystemParam.nClosePM);

	recset.Close();
	return 1;
}
int CDataProcess::GetZRSP(int c_nStockId)
{
	CRecordSet recset(&m_sqlServUser);

	char acSql[256];
	sprintf(acSql,"select TodayClosePrice from StockCurrent where StockId=%d and status=0 order by StockDate desc",c_nStockId);
	if (!recset.Open(acSql))
	{
		REPORT(MN, T("Open [%s] failed\n", acSql), RPT_ERROR);
		if (CheckUserDBConnect())
		{
			if (!recset.Open(acSql))
				return 0;
		}
		else
			return 0;
	}

	if (recset.GetRecordCount() == 0)
	{
		recset.Close();
		return 0;
	}	
	double dTmp = 0;
	
	recset.GetCollect("TodayClosePrice", dTmp);

	recset.Close();
	return int(dTmp * 1000);
}

int CDataProcess::GetMoneyDone(int c_nDelegateId,float &c_fAmountDone,float &c_fMoneyDone)
{
	CRecordSet recset(&m_sqlServUser);

	char acSql[256];
	sprintf(acSql,"select SUM(DoneAmount) AMOUNT,SUM(DoneMoney) MONEY from StockDone where DelegateId=%d ",c_nDelegateId);
	if (!recset.Open(acSql))
	{
		REPORT(MN, T("Open [%s] failed\n", acSql), RPT_ERROR);
		if (CheckUserDBConnect())
		{
			if (!recset.Open(acSql))
				return 0;
		}
		else
			return 0;
	}

	if (recset.GetRecordCount() == 0)
	{
		recset.Close();
		return 0;
	}	
	double dTmp = 0;
	
	recset.GetCollect("AMOUNT", dTmp);
	c_fAmountDone = dTmp;
	recset.GetCollect("MONEY",dTmp);
	c_fMoneyDone = dTmp;
	recset.Close();
	return int(dTmp * 1000);

}

void CDataProcess::ProcStockInfo(char* pData, unsigned int& nOffset,char * c_pOut,int c_nMaxOutLen)
{
	short nStockCount = 0;
	CRecordSet recset(&m_sqlServUser);
	REPORT(MN, T("ProcStockInfo [3101] \n"), RPT_INFO);

	string strSql=  "select * from Stock";
	if (!recset.Open(strSql.c_str()))
	{
		REPORT(MN, T("Open [%s] failed\n", strSql.c_str()), RPT_ERROR);
		if (CheckUserDBConnect())
		{
			if (!recset.Open(strSql.c_str()))
				return;
		}
		else
			return;
	}

	nStockCount = (unsigned short)recset.GetRecordCount();
	if (nStockCount < 0)
		nStockCount = 0;

	///////////////////////////////////////////////////////////////////////////
	memcpy(c_pOut+nOffset, pData, sizeof(unsigned short));
	nOffset += sizeof(unsigned short);
	memcpy(c_pOut+nOffset, &nStockCount, sizeof(unsigned short));
	nOffset += sizeof(unsigned short);
	REPORT(MN,T("STOCKINFO nStockCount = %d\n",nStockCount),RPT_INFO);
	int nTmp = 0;
	for (int i=0; i<nStockCount; i++)
	{
		recset.GetCollect("STOCKID", nTmp);
		*(int *)(c_pOut + nOffset) = nTmp;
		nOffset += sizeof(int);
		recset.GetCollect("STOCKDISPLAY", c_pOut + nOffset,16);
		nOffset += 16;
		recset.GetCollect("STOCKDISPLAY", c_pOut + nOffset,64);
		nOffset += 64;
		recset.GetCollect("STOCKNAME", c_pOut + nOffset,64);
		nOffset += 64;
		double dTmp = 0;
		recset.GetCollect("TOTALAMOUNT", dTmp);
		*(double *)(c_pOut + nOffset) = dTmp;
		nOffset += sizeof(double);
		recset.MoveNext();
	}
	recset.Close();
}

void CDataProcess::ProcCommand(char* pData, unsigned int& nOffset,char * c_pOut,int c_nOutMaxLen)
{
	unsigned short unCommandID = *(unsigned short*)(pData + sizeof(unsigned short));
	unsigned short usDataLen = *(unsigned short *)(pData + sizeof(unsigned short) * 2);
	char * pDataBuf = pData + sizeof(unsigned short) * 3;//数据长度

	//REPORT(MN, T("COMMAND 3010 [%d]\n",unCommandID), RPT_DEBUG);

	unsigned int nNeedBufSize = nOffset + sizeof(tagCommandInfo);

	tagCommandInfo* pInfo = (tagCommandInfo*)(c_pOut+nOffset);
	pInfo->nCommandID = unCommandID;
	pInfo->nResult = 0;
	nOffset += sizeof(tagCommandInfo);
	*(unsigned short *)(c_pOut + nOffset) = 0;//附加数据长度为0
	nOffset += sizeof(unsigned short);

	if (unCommandID == 2)
	{
	}
	if (unCommandID == 1)
	{
		std::string strExecutePath = GetExecutePath();
		strExecutePath = strExecutePath.substr(0, strExecutePath.rfind("\\") + 1);
		std::string strXmlPath = strExecutePath + "FinanPlug.xml";
		g_cfg.Load(strXmlPath.c_str());
	}
	if (unCommandID == 1000)//通知退出
	{
	}
}

void CDataProcess::ProcReqVersion(char* pData, unsigned int& nOffset,char * c_pOut,int c_nOutMaxLen)
{
	unsigned int unProductId = *(unsigned int*)(pData + sizeof(unsigned short));
	char acVer[10];
	char acPatch[10];
	memset(acVer,0,sizeof(acVer));
	memset(acPatch,0,sizeof(acPatch));
	strncpy(acVer,pData + sizeof(unsigned short) + sizeof(unsigned int),10);
	strncpy(acPatch,pData + sizeof(unsigned short) + sizeof(unsigned int) + 10,10);
	REPORT(MN, T("3085 [%d][%s][%s]\n",unProductId, acVer,acPatch), RPT_DEBUG);

	unsigned int nNeedBufSize = nOffset + sizeof(unsigned short) + sizeof(unsigned int) + sizeof(tagVersionInfo);

	memcpy(c_pOut + nOffset, pData, sizeof(unsigned short) + sizeof(unsigned int));
	nOffset += sizeof(unsigned short) + sizeof(unsigned int);

	tagVersionInfo* pVersionInfo = (tagVersionInfo*)(c_pOut + nOffset);
	
	tagUpgradeInfo * pGrd = NULL;//g_cfg.GetUpgradeInfo(unProductId);
	if (pGrd)
	{		
		//以下是版本控制
		memcpy(pVersionInfo,&(pGrd->stInfo),sizeof(tagVersionInfo));
		
		if (strcmp(acVer,pVersionInfo->szVer) < 0)
		{
			pVersionInfo->usUpdateType = 1;//0不更新，1安装，2补丁
			REPORT(MN, T("3085 [%d][%s][%s][%s] to upgrade\n",unProductId, acVer,acPatch,pGrd->stInfo.szVer), RPT_DEBUG);
		}
		else
			pVersionInfo->usUpdateType = 0;
	}
	else
	{
		memset(pVersionInfo,0,sizeof(tagVersionInfo));
	}
	nOffset += sizeof(tagVersionInfo);
}

int CDataProcess::GetUserInfoByLoginCode(tagUserLogReq * c_pReq,tagUserInfo * c_pUserInfo,bool c_bCheckPass)
{
	int nRet = 0;
	CRecordSet recset(&m_sqlServUser);
	char acSql[1024];
	sprintf(acSql,"select * from member where browsepassword='%s' and membername='%s' and status=1",c_pReq->acPass,c_pReq->acCode);
	//REPORT(MN, T("Open [%s] beforefailed\n", acSql), RPT_ERROR);
	if (!recset.Open(acSql))
	{
		REPORT(MN, T("Open [%s] failed\n", acSql), RPT_ERROR);
		if (CheckUserDBConnect())
		{
			if (!recset.Open(acSql))
				return -1;
		}
		else return -2;
	}

	if (!recset.IsEOF())  //找到记录
	{
		recset.GetCollect("MemberId", c_pUserInfo->nUserID);
		REPORT(MN, T("AAAAAAAAAAa %d\n", c_pUserInfo->nUserID), RPT_ERROR);
		recset.GetCollect("MemberType", c_pUserInfo->nMemberType);
		REPORT(MN, T("AAAAAAAAAAb %d\n", c_pUserInfo->nMemberType), RPT_ERROR);
		nRet = c_pUserInfo->nUserID;
		recset.GetCollect("MemberName", c_pUserInfo->szLoginCode,64);
		REPORT(MN, T("AAAAAAAAAAc %s\n", c_pUserInfo->szLoginCode), RPT_ERROR);
		recset.GetCollect("NickName", c_pUserInfo->szNickName, 64);
		REPORT(MN, T("AAAAAAAAAAd %s\n", c_pUserInfo->szNickName), RPT_ERROR);
		recset.Close();
	}
	else
	{
		recset.Close();
		c_pUserInfo->nUserID = 0;
		return  -100;
	}
	return nRet;
}

void CDataProcess::ProcUserInfoLogByPass(char* pData, unsigned int& nOffset,char *c_pOut,int c_nMaxLen,bool c_bDes)
{
	unsigned short *pusReq = (unsigned short *)pData;
	tagUserLogReq * pReq = (tagUserLogReq *)(pData + sizeof(unsigned short));
	

	tagUserInfo userInfo = {0};
	memset(&userInfo,0,sizeof(tagUserInfo));
	if (GetUserInfoByLoginCode(pReq,&userInfo,true) > 0)
	{
		REPORT(MN,T("%s login %s ret=%d\n ",pReq->acCode,pReq->acPass,userInfo.nUserID),RPT_DEBUG);
	}

	memcpy(c_pOut + nOffset, pData, sizeof(unsigned short));
	nOffset += sizeof(unsigned short);
	memcpy(c_pOut + nOffset, &userInfo, sizeof(tagUserInfo));
	nOffset += sizeof(tagUserInfo);
	//REPORT(MN,T("3009 nOffset = [%d]\n",nOffset),RPT_DEBUG);
}

void CDataProcess::ProcUserChangePassword(char* pData, unsigned int& nOffset,char * c_pOut,int c_nOutMaxLen,bool c_bDes)
{
	unsigned short *pusReq = (unsigned short *)pData;
	tagChangePass * pPass = (tagChangePass *)(pData + sizeof(unsigned short));

	CRecordSet recset(&m_sqlServUser);
	char acSql[1024];
	if (pPass->nType == 0)
	{
		if (pPass->nUserId > 0)
			sprintf(acSql,"select * from Member where MemberId=%d and browsepassword='%s' and status=1",pPass->nUserId,pPass->acPass);
		else
			sprintf(acSql,"select * from Member where MemberName='%s' and browsepassword='%s' and status=1",pPass->acCode,pPass->acPass);
	}
	else
	{
		if (pPass->nUserId > 0)
			sprintf(acSql,"select * from Member where MemberId=%d and optionpassword='%s' and status=1",pPass->nUserId,pPass->acPass);
		else
			sprintf(acSql,"select * from Member where MemberName='%s' and optionpassword='%s' and status=1",pPass->acCode,pPass->acPass);
	}
	
	int nResult = 0;
	if (!recset.Open(acSql))
	{
		REPORT(MN, T("Open [%s] failed\n", acSql), RPT_ERROR);
		if (CheckUserDBConnect())
		{
			if (!recset.Open(acSql))
			{
				nResult = -1;
				return;
			}
		}
		else 
		{
			nResult = -1;
			return;
		}
	}
	
	if (nResult == 0)
	{
		if (recset.GetRecordCount() == 1)
		{
			recset.Close();
			if (pPass->nType == 0)
			{
				if (pPass->nUserId > 0)
					sprintf(acSql,"update Member set browsepassword='%s' where MemberId=%d and status=1",pPass->acNewPass,pPass->nUserId);
				else
					sprintf(acSql,"update Member set browsepassword='%s' where MemberName=%s and status=1",pPass->acNewPass,pPass->acCode);
			}
			else
			{
				if (pPass->nUserId > 0)
					sprintf(acSql,"update Member set optionpassword='%s' where MemberId=%d and status=1",pPass->acNewPass,pPass->nUserId);
				else
					sprintf(acSql,"update Member set optionpassword='%s' where MemberName=%s and status=1",pPass->acNewPass,pPass->acCode);
			}
			//REPORT(MN, T("ProcUserChangePassword update [%s] \n", acSql), RPT_ERROR);
			if (m_sqlServUser.Execute(acSql))
			{
				REPORT(MN, T("ProcUserChangePassword update success[%s] \n", acSql), RPT_ERROR);
				nResult = 1;
			}
		}
		else
			recset.Close();
	}
	memcpy(c_pOut+nOffset, pData, sizeof(unsigned short));//req
	nOffset += sizeof(unsigned short);
	memcpy(c_pOut+nOffset, &nResult, sizeof(int));
	nOffset += sizeof(int);
}

//记录本次登录信息
void CDataProcess::ProcPutLogInfo(char* pData, unsigned int& nOffset)
{
	unsigned short *pusReq = (unsigned short *)pData;
	unsigned int* pRoleID = (unsigned int*)(pData + sizeof(unsigned short));
	int* pUserID = ( int*)(pData + sizeof(unsigned short) + sizeof(unsigned int));

	char szLoginIP[20] = {0};
	int *pLoginPort;
	memcpy(szLoginIP, pData + sizeof(unsigned short) + sizeof(unsigned int) * 2, 20);//登陆服务器IP
	pLoginPort = (int *)(pData + sizeof(unsigned short) + sizeof(unsigned int) * 2 + 20);//登陆服务器PORT

	CRecordSet recset(&m_sqlServUser);
	char acSql[1024];
	int nResult = -1;
	if (*pUserID > 0)  //找到记录
	{		
		//获取上次登陆信息
		bool bExist = false;

		sprintf(acSql,"select * from UserLogState where FB500=%d",*pUserID);

		if (recset.Open(acSql))
		{
			if (!recset.IsEOF() && !recset.IsBOF())
			{
				bExist = true;
			}
			recset.Close();

			//记录本次登陆信息
			if (bExist)
				sprintf(acSql,"update UserLogState set LOGIN_TM=getdate(),ip='%s',port=%d,state=1 where FB500=%d",szLoginIP,*pLoginPort,*pUserID);
			else
				sprintf(acSql,"insert UserLogState (FB500,LOGIN_TM,ip,port,state) values (%d,getdate(),'%s',%d,1)",*pUserID,szLoginIP,*pLoginPort);

			if (m_sqlServUser.Execute(acSql))
			{
				nResult = 0;
			}
		}
	}		

	///////////////////////////////////////////////////////////////////////////
	unsigned int nNeedBufSize = nOffset + sizeof(unsigned short) + sizeof(int) * 3;
	if (nNeedBufSize > m_nSendBufSize)
	{
		char *pNewBuf = new char[nNeedBufSize];
		memcpy(pNewBuf, m_pSendBuf, m_nSendBufSize);

		delete []m_pSendBuf;
		m_pSendBuf = pNewBuf;
		m_nSendBufSize = nNeedBufSize;
	}

	memcpy(m_pSendBuf+nOffset, pData, sizeof(unsigned short) + sizeof(int) * 2);
	nOffset += sizeof(unsigned short);
	*(int *)(m_pSendBuf+nOffset) = nResult;
	nOffset += sizeof(int);
}

void CDataProcess::ProcMakerStock(char* pData, unsigned int& nOffset,char * c_pOut,int c_nOutMaxLen)
{
	unsigned short usReq = *(unsigned short*)(pData);
	unsigned int   nUserId = *(unsigned int*)(pData + sizeof(unsigned short));

	CRecordSet recset(&m_sqlServUser);
	char acSql[256];

	sprintf(acSql,"SELECT * FROM StockMakerRelation WHERE MemberID=%d and status=1",nUserId);
	REPORT(MN, T("ProcMakerStock [%s]\n", acSql), RPT_ERROR);
	if (!recset.Open(acSql))
	{
		REPORT(MN, T("Open [%s] failed\n", acSql), RPT_ERROR);
		if (CheckUserDBConnect())
		{
			if (!recset.Open(acSql))
				return;
		}
		else return;
	}

	long nRecCount = recset.GetRecordCount();
	int nAmount = 0;
	memcpy(c_pOut + nOffset, pData, sizeof(unsigned short));
	nOffset += sizeof(unsigned short);

	*(int *)(c_pOut + nOffset) = nRecCount;
	nOffset += sizeof(int);
	while(!recset.IsEOF())
	{
		int nId;
		recset.GetCollect("STOCKID", nId);
		*(int *)(c_pOut + nOffset) = nId;	nOffset += sizeof(int);
		recset.MoveNext();
	}
	recset.Close();
	////////////////////////////////////////////////////////////////////////////////////////////////////////
}

bool CDataProcess::CheckPass(tagUserPass * c_pPass,int c_nType)
{
	CRecordSet recset(&m_sqlServUser);

	char acSql[256];
	if (c_nType == 0)//查询密码
	{
		if (c_pPass->nId > 0)
			sprintf(acSql,"SELECT * FROM Member WHERE MemberID=%d and browsepassword='%s' and status=1",c_pPass->nId,c_pPass->acPass);
		else
			sprintf(acSql,"SELECT * FROM Member WHERE MemberName='%s' and browsepassword='%s' and status=1",c_pPass->acCode,c_pPass->acPass);
	}
	else
	if (c_nType == 1)//交易密码
	{
		if (c_pPass->nId > 0)
			sprintf(acSql,"SELECT * FROM Member WHERE MemberID=%d and optionpassword='%s' and status=1",c_pPass->nId,c_pPass->acPass);
		else
			sprintf(acSql,"SELECT * FROM Member WHERE MemberName='%s' and optionpassword='%s' and status=1",c_pPass->acCode,c_pPass->acPass);
	}
	if (!recset.Open(acSql))
		return false;

	if (recset.GetRecordCount() == 0)
	{
		recset.Close();
		return false;
	}
	recset.Close();
	return true;
}

void CDataProcess::GetAccount(int c_nUserId,tagAccount * c_pItem)
{
	CRecordSet recset(&m_sqlServUser);

	char acSql[256];
	sprintf(acSql,"SELECT * FROM MemberMoney WHERE MemberID=%d",c_nUserId);
	if(!recset.Open(acSql))
	{
		return;
	}

	double dCash = 0;
	double dValidCash = 0;
	if(!recset.IsEOF())
	{
		recset.GetCollect("Cash",dCash);
		recset.GetCollect("ValidCash",dValidCash);
		c_pItem->fCash = dCash;
		c_pItem->fFreezeCash = 0;//dCash - dValidCash;
	}
	recset.Close();

	sprintf(acSql,"select * from MoneyBook where MemberId=%d and Status=0 order by BookId",c_nUserId);
	if (!recset.Open(acSql))
	{
		return;
	}
	int nRelatedMemberId = 0;
	double dAmount;
	double dAmountLocked;
	while(!recset.IsEOF())
	{
		recset.GetCollect("RelatedMemberId",nRelatedMemberId);
		recset.GetCollect("Amount",dAmount);
		recset.GetCollect("AmountLocked",dAmountLocked);
		c_pItem->fCash += dAmount;
		c_pItem->fFreezeCash += dAmountLocked;
		recset.MoveNext();
	}
	recset.Close();
}

void CDataProcess::ProcPosition(char* pData, unsigned int& nOffset,char * c_pOut,int c_nOutMaxLen)
{
	unsigned short usReq = *(unsigned short*)(pData);
	tagUserPass * pPass = (tagUserPass *)(pData + sizeof(unsigned short));

	if(CheckPass(pPass,1) == false)
	{
		*(unsigned short *)(c_pOut + nOffset) = 0XFFFD;
		nOffset += sizeof(unsigned short);
		strcpy(c_pOut + nOffset,"UserId or Password is invalid! please check!");
		nOffset += 256;
		return;
	}
	CRecordSet recset(&m_sqlServUser);

	char acSql[256];
	sprintf(acSql,"SELECT * FROM MemberStock WHERE MemberID=%d",pPass->nId);

	if (!recset.Open(acSql))
	{
		REPORT(MN, T("Open [%s] failed\n", acSql), RPT_ERROR);
		if (CheckUserDBConnect())
		{
			if (!recset.Open(acSql))
				return;
		}
		else return;
	}

	long nRecCount = recset.GetRecordCount();
	int nAmount = 0;
	memcpy(c_pOut + nOffset, pData, sizeof(unsigned short));
	nOffset += sizeof(unsigned short);

	tagAccount * pAccount = (tagAccount *)(c_pOut + nOffset);
	pAccount->fAssets = 0;
	pAccount->fCash = 0;
	pAccount->fFreezeCash = 0;
	pAccount->fProfit = 0;

	GetAccount(pPass->nId,pAccount);
	nOffset += sizeof(tagAccount);

	*(int *)(c_pOut + nOffset) = nRecCount;
	int nCountOffset = nOffset;
	nOffset += sizeof(int);
	std::map<int,tagPosition *> mapPosition;
	while(!recset.IsEOF())
	{
		tagPosition * pOut = (tagPosition *)(c_pOut + nOffset);
		int nId;
		recset.GetCollect("STOCKID", nId);
		pOut->nStockId = nId;
		recset.GetCollect("STOCKAMOUNT",pOut->nAmount);//现有持仓数
		pOut->fCost = 0;
		pOut->nBuyToday = 0;
		pOut->nSaleToday = 0;
		pOut->nFreezeAmount = 0;
		mapPosition[pOut->nStockId] = pOut;
		nOffset += sizeof(tagPosition);
		recset.MoveNext();
	}
	recset.Close();
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	int nId = 0;
	int nStockId =0;
	int nRelatedMemberId = 0;
	//统计股票台帐，今日买、今日卖
	sprintf(acSql,"SELECT * FROM StockBook WHERE MemberID=%d and Status=0 order by BookId",pPass->nId);//未清算状态

	if(!recset.Open(acSql))
	{
		return;
	}
	REPORT(MN,T("%s\n",acSql),RPT_INFO);

	int nBuySale = 0;
	int nAmountLocked = 0;
	while(!recset.IsEOF())
	{
		recset.GetCollect("StockID",nStockId);
		recset.GetCollect("Amount",nAmount);
		recset.GetCollect("AmountLocked",nAmountLocked);
		recset.GetCollect("RelatedMemberId",nRelatedMemberId);
		if (nStockId > 0)
		{
			if (mapPosition.find(nStockId) != mapPosition.end())
			{
				mapPosition[nStockId]->nAmount += nAmount;//证券数量
				mapPosition[nStockId]->nFreezeAmount += nAmountLocked;//不能交易的数量

				if(pPass->nId != nRelatedMemberId)
				{
					if (nAmount > 0)
						mapPosition[nStockId]->nBuyToday += nAmount;//今日买进
					else
						mapPosition[nStockId]->nSaleToday += nAmount;//今日卖出
				}
			}
			else//没有找到
			{
				tagPosition * pOut = (tagPosition *)(c_pOut + nOffset);
				pOut->nStockId = nStockId;
				pOut->nAmount = 0;
				pOut->nBuyToday = 0;
				pOut->nFreezeAmount = 0;
				pOut->nSaleToday = 0;
				pOut->nAmount += nAmount;//证券数量
				pOut->nFreezeAmount += nAmountLocked;//不能交易的数量
				if (nAmount > 0)
					pOut->nBuyToday += nAmount;//今日买进
				else
					pOut->nSaleToday += nAmount;//今日卖出
				mapPosition[nStockId] = pOut;
				nOffset += sizeof(tagPosition);
				*(int *)(c_pOut + nCountOffset) = *(int *)(c_pOut + nCountOffset) + 1;
			}
		}
		recset.MoveNext();
	}
	recset.Close();
	REPORT(MN,T("BBBBBBBBBBBBBBBBBBBBBBBBBBB\n"),RPT_INFO);

	//取冻结数
	sprintf(acSql,"SELECT * FROM MemberStockDetail WHERE MemberID=%d order by createdate",pPass->nId);
	if(!recset.Open(acSql))
	{
		return;
	}

	while(!recset.IsEOF())
	{
		recset.GetCollect("StockID",nStockId);
		recset.GetCollect("LockAmount",nAmount);
		if (nStockId > 0 && nAmount > 0)
		{
			if (mapPosition.find(nStockId) != mapPosition.end())
			{
				mapPosition[nStockId]->nFreezeAmount += nAmount;
			}
		}
		recset.MoveNext();
	}
	recset.Close();
	REPORT(MN,T("CCCCCCCCCCCCCCCCCCCCCCCCCCCCc\n"),RPT_INFO);

}

void CDataProcess::ProcConsign(char* pData, unsigned int& nOffset,char * c_pOut,int c_nOutMaxLen)
{
	char acSql[1024];
	unsigned short usReq = *(unsigned short*)(pData);
	tagUserPass * pPass = (tagUserPass *)(pData + sizeof(unsigned short));
	REPORT(MN,T("[%d][%s]\n",pPass->nId,pPass->acPass),RPT_INFO);
	if(CheckPass(pPass,1) == false)
	{
		return;
	}
	REPORT(MN,T("[%d][%s] CheckPass OK\n",pPass->nId,pPass->acPass),RPT_INFO);
	int nConsignCount = *(int *)(pData + sizeof(short) + sizeof(tagUserPass));
	REPORT(MN,T("nConsignCount == %d\n",nConsignCount),RPT_INFO);
	tagConsignReq * pConsign = (tagConsignReq *)(pData + sizeof(unsigned short) + sizeof(tagUserPass) + sizeof(int));
	for(int n=0; n<nConsignCount; n++)
	{
		pConsign = (tagConsignReq *)(pData + sizeof(unsigned short) + sizeof(tagUserPass) + sizeof(int) + sizeof(tagConsignReq)*n);
		REPORT(MN,T("nOperate == %d\n",pConsign->nOperate),RPT_INFO);

		if (pConsign->nOperate == 0 || pConsign->nOperate == 1)
		{
			if (g_pOtcMarket->CheckConsign(pPass->nId,pConsign->nStockId,pConsign->nAmount,pConsign->fPrice,pConsign->nOperate) < 0)
			{
				*(unsigned short *)(c_pOut + nOffset) = 0XFFFC;
				nOffset += sizeof(unsigned short);
				strcpy(c_pOut + nOffset,"不能提交委托");
				nOffset += 256;
				return;
			}
			g_pOtcMarket->OnConsign(pPass->nId,pConsign->nStockId,pConsign->nAmount,pConsign->fPrice,pConsign->nOperate);
		}
		else
		if (pConsign->nOperate == 2)
		{
			sprintf(acSql,"insert into StockDelegate(StockId,MemberId,Price,Amount,DelegateDate,AmountDone,AmountLeft,Status,BuySale,OperatorName,Sign,CancelID,totalfee)\
			values(%d,%d,%.3f,%d,GETDATE(),0,%d,1,2,'client',1,%d,0)",pConsign->nStockId,pPass->nId,pConsign->fPrice,pConsign->nAmount,pConsign->nAmount,pConsign->nConsignID);
			m_sqlServUser.Execute(acSql);
		}
		else
		{
			return;
		}
	}
	int nAmount = 0;
	memcpy(c_pOut + nOffset, pData,sizeof(unsigned short)+ sizeof(int));
	nOffset += sizeof(unsigned short)+sizeof(int);
	REPORT(MN,T("ProcConsign Over\n"),RPT_INFO);
}
int CDataProcess::RecordStockBook(int c_nOperateType,int c_nSourceType,int c_nSourceId,int c_nMemberId,int c_nRelatedMemberId,int c_nStockId,int c_nAmount,int c_nAmountLocked)
{
	char acSql[512];
	sprintf(acSql,"insert into StockBook(OperateType,StockId,Amount,AmountLocked,MemberId,RelatedMemberId,SourceId,SourceType,CreateDate,Status) values(%d,%d,%d,%d,%d,%d,%d,%d,getdate(),0)",c_nOperateType,c_nStockId,c_nAmount,c_nAmountLocked,c_nMemberId,c_nRelatedMemberId,c_nSourceId,c_nSourceType);
	m_sqlServUser.Execute(acSql);
	return 0;
}

int CDataProcess::RecordMoneyBook(int c_nOperateType,int c_nSourceType,int c_nSourceId,int c_nMemberId,int c_nRelatedMemberId,float c_fMoney,float c_fMoneyLocked,int c_nMoneyType)
{
	char acSql[512];
	sprintf(acSql,"insert into MoneyBook(OperateType,Amount,AmountLocked,MemberId,RelatedMemberId,SourceId,SourceType,CreateDate,MoneyType,status) values(%d,%.4f,%.4f,%d,%d,%d,%d,getdate(),%d,0)",c_nOperateType,c_fMoney,c_fMoneyLocked,c_nMemberId,c_nRelatedMemberId,c_nSourceId,c_nSourceType,c_nMoneyType);
	m_sqlServUser.Execute(acSql);
	return 0;
}

int CDataProcess::AddMemberMoney(int c_nMemberId,float c_fMoney)
{
	char acSql[256];

	sprintf(acSql,"update MemberMoney set Cash=%.2f + Cash,LastUpdateDate=getdate() where MemberId=%d",c_fMoney,c_nMemberId);
	REPORT(MN,T("AddMemberMoney SQL[%s]\n",acSql),RPT_INFO);
	m_sqlServUser.Execute(acSql);
	return 1;

}

int CDataProcess::AddMemberStock(int c_nMemberId,int c_nStockId,int c_nAmount)
{
	int nId = 0;
	CRecordSet recset(&m_sqlServUser);

	char acSql[256];

	sprintf(acSql,"SELECT * FROM MemberStock where memberid=%d and stockid=%d",c_nMemberId,c_nStockId);
	REPORT(MN,T("AddMemberStock %s[%d]\n",acSql,c_nAmount),RPT_INFO);
	if (!recset.Open(acSql))
		return nId;

	if (recset.IsEOF())
	{
		if (recset.AddNew() == FALSE)
		{
			recset.Close();
			return nId;
		}

		recset.PutCollect("MemberId",long(c_nMemberId));
		recset.PutCollect("StockId",long(c_nStockId));
		recset.PutCollect("StockAmount",long(c_nAmount));
		time_t cur;
		char acTime[32];
		time(&cur);
		struct tm *ltCur = localtime(&cur);
		unsigned int unYear = ltCur->tm_year + 1990;
		unsigned int unMonth = ltCur->tm_mon + 1;
		unsigned int unDay = ltCur->tm_mday;
		unsigned int unHour = ltCur->tm_hour;
		unsigned int unMinute = ltCur->tm_min;
		unsigned int unSecond = ltCur->tm_sec;
		sprintf(acTime,"%d-%d-%d %d:%d:%d",unYear,unMonth,unDay,unHour,unMinute,unSecond);
		recset.PutCollect("CreateDate",acTime);
		recset.Update();
	}
	else
	{
		int nAmount = 0;
		recset.GetCollect("StockAmount",nAmount);
		nAmount += c_nAmount;
		recset.PutCollect("StockAmount",long(nAmount));
		recset.Update();
	}
	recset.Close();

	//锁定
	if (c_nAmount > 0)//买入的需要锁定
	{
		//sprintf(acSql,"insert into MemberStockDetail(MemberId,StockID,LockAmount,CreateDate,LockDays,UnlockDate) Values(%d,%d,%d,getdate(),1,getdate()+1)",c_nMemberId,c_nStockId,c_nAmount);
		//m_sqlServUser.Execute(acSql);
	}
	return 1;

}

int CDataProcess::PutMakerConsign(int c_nUserId,tagMakerConsignReq * c_pReq)
{
	int nId = 0;
	CRecordSet recset(&m_sqlServUser);

	char acSql[256];

	sprintf(acSql,"SELECT * FROM StockQuoteDetail where memberid=%d and stockid=%d",c_nUserId,c_pReq->nStockId);

	if (!recset.Open(acSql))
		return nId;
	if (recset.AddNew() == FALSE)
	{
		recset.Close();
		return nId;
	}

	recset.PutCollect("MemberId",long(c_nUserId));
	recset.PutCollect("StockId",long(c_pReq->nStockId));
	recset.PutCollect("BuyPrice",double(c_pReq->fBuyPrice));
	recset.PutCollect("BuyAmount",long(c_pReq->nBuyAmount));
	recset.PutCollect("SellPrice",double(c_pReq->fSalePrice));
	recset.PutCollect("SellAmount",long(c_pReq->nSaleAmount));
	time_t cur;
	char acTime[32];
	time(&cur);
	struct tm *ltCur = localtime(&cur);
	unsigned int unYear = ltCur->tm_year + 1990;
	unsigned int unMonth = ltCur->tm_mon + 1;
	unsigned int unDay = ltCur->tm_mday;
	unsigned int unHour = ltCur->tm_hour;
	unsigned int unMinute = ltCur->tm_min;
	unsigned int unSecond = ltCur->tm_sec;
	sprintf(acTime,"%d-%d-%d %d:%d:%d",unYear,unMonth,unDay,unHour,unMinute,unSecond);
	recset.PutCollect("CreateDate",acTime);
	recset.PutCollect("Status",long(1));
	recset.Update();
	recset.GetCollect("QuoteDetailId",nId);

	recset.Close();
	return nId;
}

void CDataProcess::ProcMakerConsign(char* pData, unsigned int& nOffset,char * c_pOut,int c_nOutMaxLen)
{
	char acSql[1024];
	unsigned short usReq = *(unsigned short*)(pData);
	tagUserPass * pPass = (tagUserPass *)(pData + sizeof(unsigned short));
	REPORT(MN,T("[%d][%s]\n",pPass->nId,pPass->acPass),RPT_INFO);
	if(CheckPass(pPass,1) == false)
	{
		return;
	}
	REPORT(MN,T("[%d][%s] CheckPass OK\n",pPass->nId,pPass->acPass),RPT_INFO);
	int nConsignCount = *(int *)(pData + sizeof(short) + sizeof(tagUserPass));
	REPORT(MN,T("nConsignCount == %d\n",nConsignCount),RPT_INFO);
	tagMakerConsignReq * pConsign = (tagMakerConsignReq *)(pData + sizeof(unsigned short) + sizeof(tagUserPass) + sizeof(int));
	for(int n=0; n<nConsignCount; n++)
	{
		pConsign = (tagMakerConsignReq *)(pData + sizeof(unsigned short) + sizeof(tagUserPass) + sizeof(int) + sizeof(tagMakerConsignReq)*n);
		if (g_pOtcMarket->CheckMakerConsign(pPass->nId,pConsign->nStockId,pConsign->nBuyAmount,pConsign->fBuyPrice,pConsign->nSaleAmount,pConsign->fSalePrice) < 0)
		{
			*(unsigned short *)(c_pOut + nOffset) = 0XFFFC;
			nOffset += sizeof(unsigned short);
			strcpy(c_pOut + nOffset,"不满足庄家委托条件，不能提交委托");
			nOffset += 256;
			return;
		}
		int nMakerConsignId = PutMakerConsign(pPass->nId,pConsign);
		REPORT(MN,T("nMakerConsignId == %d\n",nMakerConsignId),RPT_INFO);
		if (pConsign->nType == 1)//先撤销先前的
		{
			sprintf(acSql,"insert into StockDelegate(StockId,MemberId,Price,Amount,DelegateDate,AmountDone,AmountLeft,Status,BuySale,OperatorName,Sign,CancelID,totalfee,MakerQuoteDetailID)\
			values(%d,%d,0,0,GETDATE(),0,0,1,2,'client',1,0,0,%d)",pConsign->nStockId,pPass->nId,nMakerConsignId);
			m_sqlServUser.Execute(acSql);
		}
		
		if (pConsign->nBuyAmount > 0)
		{
			//sprintf(acSql,"insert into StockDelegate(StockId,MemberId,Price,Amount,DelegateDate,AmountDone,AmountLeft,Status,BuySale,OperatorName,Sign,totalfee,MakerQuoteDetailID)\
			//values(%d,%d,%.3f,%d,GETDATE(),0,%d,1,0,'client',1,0,%d)",pConsign->nStockId,pPass->nId,pConsign->fBuyPrice,pConsign->nBuyAmount,pConsign->nBuyAmount,nMakerConsignId);
			//m_sqlServUser.Execute(acSql);
			g_pOtcMarket->OnConsign(pPass->nId,pConsign->nStockId,pConsign->nBuyAmount,pConsign->fBuyPrice,0,nMakerConsignId);
		}

		if (pConsign->nSaleAmount > 0)
		{
			//sprintf(acSql,"insert into StockDelegate(StockId,MemberId,Price,Amount,DelegateDate,AmountDone,AmountLeft,Status,BuySale,OperatorName,Sign,totalfee,MakerQuoteDetailID)\
			//values(%d,%d,%.3f,%d,GETDATE(),0,%d,1,1,'client',1,0,%d)",pConsign->nStockId,pPass->nId,pConsign->fSalePrice,pConsign->nSaleAmount,pConsign->nSaleAmount,nMakerConsignId);
			//m_sqlServUser.Execute(acSql);
			g_pOtcMarket->OnConsign(pPass->nId,pConsign->nStockId,pConsign->nSaleAmount,pConsign->fSalePrice,1,nMakerConsignId);
		}

		
	}
	int nAmount = 0;
	memcpy(c_pOut + nOffset, pData,sizeof(unsigned short)+ sizeof(int));
	nOffset += sizeof(unsigned short)+sizeof(int);
}

void CDataProcess::ProcConsignHistory(char* pData, unsigned int& nOffset,char * c_pOut,int c_nOutMaxLen)
{
	unsigned short usReq = *(unsigned short*)(pData);
	tagUserPass * pPass = (tagUserPass *)(pData + sizeof(unsigned short));

	if(CheckPass(pPass,1) == false)
	{
		return;
	}

	tagConsignHistoryReq *pReq = (tagConsignHistoryReq *)(pData + sizeof(unsigned short) + sizeof(tagUserPass));

	CRecordSet recset(&m_sqlServUser);
	char acSql[1024];

	sprintf(acSql,"SELECT * FROM StockDelegate WHERE MemberID=%d",pPass->nId);

	if (!recset.Open(acSql))
	{
		REPORT(MN, T("Open [%s] failed\n", acSql), RPT_ERROR);
		if (CheckUserDBConnect())
		{
			if (!recset.Open(acSql))
				return;
		}
		else return;
	}

	long nRecCount = recset.GetRecordCount();
	int nAmount = 0;
	memcpy(c_pOut + nOffset, pData, sizeof(unsigned short));
	nOffset += sizeof(unsigned short);

	*(int *)(c_pOut + nOffset) = nRecCount;
	nOffset += sizeof(int);
	double dPrice;
	while(!recset.IsEOF())
	{
		tagConsignHistory * pOut = (tagConsignHistory *)(c_pOut + nOffset);
		int nId;
		recset.GetCollect("STOCKDELEGATEID",pOut->nConsignID);
		recset.GetCollect("STOCKID", nId);	
		pOut->nStockId = nId;
		recset.GetCollect("AMOUNT",pOut->nAmount);
		recset.GetCollect("AMOUNTDONE",pOut->nBargainAmount);
		recset.GetCollect("DELEGATEDATE",pOut->acDateTime,24);
		recset.GetCollect("PRICE",dPrice);
		pOut->fPrice = dPrice;
		recset.GetCollect("BUYSALE",pOut->nOperate);
		recset.GetCollect("STATUS",pOut->nState);
		nOffset += sizeof(tagConsignHistory);
		recset.MoveNext();
	}
	recset.Close();
	////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void CDataProcess::ProcBargain(char* pData, unsigned int& nOffset,char * c_pOut,int c_nOutMaxLen)
{
	unsigned short usReq = *(unsigned short*)(pData);
	tagUserPass * pPass = (tagUserPass *)(pData + sizeof(unsigned short));

	if(CheckPass(pPass,1) == false)
	{
		return;
	}
	tagBargainReq *pReq = (tagBargainReq *)(pData + sizeof(unsigned short) + sizeof(tagUserPass));

	CRecordSet recset(&m_sqlServUser);
	char acSql[1024];

	sprintf(acSql,"SELECT * FROM stockdone WHERE MemberID=%d",pPass->nId);

	if (!recset.Open(acSql))
	{
		REPORT(MN, T("Open [%s] failed\n", acSql), RPT_ERROR);
		if (CheckUserDBConnect())
		{
			if (!recset.Open(acSql))
				return;
		}
		else return;
	}

	long nRecCount = recset.GetRecordCount();
	int nAmount = 0;
	memcpy(c_pOut + nOffset, pData, sizeof(unsigned short));
	nOffset += sizeof(unsigned short);

	*(int *)(c_pOut + nOffset) = nRecCount;
	nOffset += sizeof(int);
	double dPrice;
	while(!recset.IsEOF())
	{
		tagBargain * pOut = (tagBargain *)(c_pOut + nOffset);
		int nId;
		recset.GetCollect("DELEGATEID",pOut->nConsignID);
		recset.GetCollect("STOCKID", pOut->nStockId);	
		recset.GetCollect("DONEAMOUNT",pOut->nAmount);
		recset.GetCollect("DONEMONEY",dPrice);
		pOut->fMoney = dPrice;
		recset.GetCollect("DONEPRICE",dPrice);
		pOut->fPrice = dPrice;
		recset.GetCollect("SELLFEE",dPrice);
		pOut->fFee= dPrice;
		recset.GetCollect("DONEDATE",pOut->acDateTime,24);

		recset.GetCollect("DONEPRICE",dPrice);
		pOut->fPrice = dPrice;
		recset.GetCollect("BUYSALE",pOut->nOperate);
		pOut->nState = 4;
		nOffset += sizeof(tagBargain);
		recset.MoveNext();
	}
	recset.Close();
	////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void CDataProcess::GetCurTime(char* pTime, int nMaxLen)
{
	time_t  timeCur;
	time(&timeCur);
	tm tmCur;
	localtime_s(&tmCur, &timeCur);

	sprintf_s(pTime, nMaxLen, "%d-%d-%d %d:%d:%d", tmCur.tm_year+1900, tmCur.tm_mon+1, tmCur.tm_mday,
		tmCur.tm_hour, tmCur.tm_min, tmCur.tm_sec);
}

int CDataProcess::GetUserRole(int c_nUserID,DWORD &c_dwRole,DWORD &c_dwRoleEx)
{
	int nRet = 0;
/*	CRecordSet recset(&m_sqlServUser);
	char acSql[1024];
	sprintf(acSql,"select FB500,functionCode,startDate,endDate from User_Function where status=1 and fb500=%d and endDate>getdate()-1",c_nUserID);

	if (!recset.Open(acSql))
	{
		REPORT(MN, T("Open [%s] failed\n", acSql), RPT_ERROR);
		return -3;
	}

	int nCode;
	while (!recset.IsEOF())
	{			
		recset.GetCollect("functionCode",nCode);
		//REPORT(MN, T("GetUserRole [%d][%d][%d] \n", c_nUserID,nCode,c_dwRole), RPT_INFO);
		if (nCode == 1) c_dwRole |= ROLE_YJBG;
		else
		if (nCode == 1001) c_dwRole |= ROLE_YJBG_HZ | ROLE_YJBG;
		else
		if (nCode == 1002) c_dwRole |= ROLE_YJBG_FHZ | ROLE_YJBG;
		else
		if (nCode == 2) c_dwRole |= ROLE_HLDXG;
		else
		if (nCode == 3)	c_dwRole |= ROLE_LEDS_HIST | ROLE_LEDS_CHANGE;
		else
		if (nCode == 3001)	c_dwRole |= ROLE_LEDS_HIST;
		else
		if (nCode == 3002) c_dwRole |= ROLE_LEDS_CHANGE;
		else
		if (nCode == 4)	c_dwRole |= ROLE_ALERT | ROLE_PRICE_ALERT |ROLE_MARKET_RADA | ROLE_TRADE_AREA | ROLE_CUT_LINE;
		else
		if (nCode == 4001)c_dwRole |= ROLE_PRICE_ALERT;
		else
		if (nCode == 4002)c_dwRole |= ROLE_MARKET_RADA;
		else
		if (nCode == 4003)c_dwRole |= ROLE_TRADE_AREA;
		else
		if (nCode == 4004)c_dwRole |= ROLE_CUT_LINE;
		else
		//if (nCode == 4005)c_dwRole |= ROLE_JGMM | ROLE_NBJY;
		if (nCode == 4005)c_dwRole |= ROLE_NBJY;
		else
		if (nCode == 5) c_dwRole |= ROLE_MACRO_DATA;

		recset.MoveNext();
	}
	recset.Close();
*/	
	return nRet;
}

void CDataProcess::Log(char * c_pName,const char * c_pData,int c_nLen)
{
	char acFile[MAX_PATH];
	sprintf(acFile,".\\log\\%s",c_pName);
	FILE *f;
	f = fopen(acFile,"wb");
	if (f)
	{
		fwrite(c_pData,1,c_nLen,f);
		fclose(f);
	}
}



