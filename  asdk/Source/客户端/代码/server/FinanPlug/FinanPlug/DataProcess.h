//DataProcess.h
#ifndef _DATAPROCESS_H_
#define _DATAPROCESS_H_

#include "../../public/protocol.h"
#include "WorkThread.h"
#include "DataQueue.h"
#include "AdoDB.h"
#include <map>

struct Quote;
class CDataProcess
{
public:
	CDataProcess();
	virtual ~CDataProcess();
protected:
	static UINT WINAPI _WorkThread(void* pParam);
	UINT WorkThread();
public:
	int OnInit(unsigned int c_unPlugID,const char * c_pParam);
	int InitDB();
	void OnRelease();
	int OnRequest(SMsgID* c_pMsgID, char* c_pBuf, int c_iLen);
	int DoRequest(char * c_pIn,int c_nInLen, char * c_pOut,int c_nOutMaxLen);
	void OnSocketClose(unsigned int c_unID,unsigned int c_unSocket)
	{
	}

	int InitStockInfo();
	int GetZRSP(int);
	int GetSystemParam();
	int GetMoneyDone(int c_nDelegateId,float &c_fAmountDone,float &c_fMoneyDone);
	
	BOOL CheckUserDBConnect();

	int GetUserInfoByLoginCode(tagUserLogReq *,tagUserInfo * c_pUserInfo,bool c_bCheckPass);
	int GetUserRole(int c_nUserID,DWORD &c_dwRole,DWORD &c_dwRoleEx);
	void GetAccount(int c_nUserId,tagAccount * c_pItem);
	void ProcStockInfo(char* pData, unsigned int& nOffset,char * c_pOut,int c_nOutMaxLen);
	void ProcReqVersion(char* pData, unsigned int& nOffset,char *,int);	
	void ProcCommand(char* pData, unsigned int& nOffset,char *,int);
	void ProcUserInfoLogByPass(char* pData, unsigned int& nOffset,char *,int,bool c_bDes);
	void ProcUserChangePassword(char* pData, unsigned int& nOffset,char *,int,bool c_bDes);
	void ProcPutLogInfo(char* pData, unsigned int& nOffset);
	void ProcMakerStock(char* pData, unsigned int& nOffset,char *,int);
	bool CheckPass(tagUserPass *,int);
	void ProcPosition(char* pData, unsigned int& nOffset,char *,int);
	void ProcConsign(char* pData, unsigned int& nOffset,char *,int);
	void ProcMakerConsign(char* pData, unsigned int& nOffset,char *,int);
	int PutMakerConsign(int,tagMakerConsignReq *);

	void ProcConsignHistory(char* pData, unsigned int& nOffset,char *,int);
	void ProcBargain(char* pData, unsigned int& nOffset,char *,int);

	void GetCurTime(char* pTime, int nMaxLen);
				
	void Log(char * c_pName,const char * c_pData,int c_nLen);

	bool Lock()
	{
		return m_rwLock.WaitWrite();
	}
	void UnLock()
	{
		m_rwLock.EndWrite();
	}
	int WriteOutToFile(char * c_pCode,char * c_pBuf,int c_iLen,int c_nZip);

	bool	IsWorkDay(int);

public:
	BOOL IsThreadRun(){return m_bRun;};

public:
	unsigned int m_unPlugID;
	CWorkThread* m_pWorkThread;       //数据处理线程

	CDataQueue	 m_dataQueue;		  //数据队列
	BOOL		 m_bRun;              //线程运行标志

	CSQLServerDB m_sqlServUser;		  //用户数据库

	char*        m_pSendBuf;          //发送缓冲区指针
	unsigned int m_nSendBufSize;	  //发送缓冲区大小
	char*		 m_pZipBuf;			  //zip用缓冲区

	int		m_nErrorCode;			//错误号
	char	m_acErrorMsg[1024 * 4];		//错误信息

	RWLock	m_rwLock;
	char m_acLastNotifyTime[30];

	int AddMemberStock(int c_nMemberId,int c_nStockId,int c_nAmount);
	int AddMemberMoney(int,float);

	int RecordStockBook(int c_nOperateType,int c_nSourceType,int c_nSourceId,int c_nMemberId,int c_nRelatedMemberId,int c_nStockId,int c_nAmount,int c_nAmountLocked);
	int RecordMoneyBook(int c_nOperateType,int c_nSourceType,int c_nSourceId,int c_nMemberId,int c_nRelatedMemberId,float c_fMoney,float c_fMoneyLocked,int c_nMoneyType);
};

/////////////////////////////////////////////////////////////////////////////
#endif

