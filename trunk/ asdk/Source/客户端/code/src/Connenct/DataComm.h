#pragma once
#include "Data.h"
class CData;
class CProxyOption;
class CShortSocket;

class CDataComm : public CData
{
public:
	CDataComm(void);
	~CDataComm(void);
public:	
	int MakeVersionReq(char *,unsigned int c_unProduct,char * c_pVer, char * c_pPatch);	
	int MakeUpgradeFileReq(char *,unsigned int c_unProduct,char * c_pVer,int &c_nFileLen);	//版本升级文件请求
	int MakeUserReq(char *,unsigned int c_unProduct,int c_nUserID,char * c_pUserCode,char * c_pNewsServerIP,int c_nNewsServerPort);
	int MakeIsUserOnlineReq(char *,int c_nUserId);
	int MakeUserChangePasswordReq(char *,unsigned int c_unProduct,char * c_pUserCode,char * c_pUserPassword,char * c_pNewPassword);
	int MakeLogInfoReq(char *,unsigned int c_unProduct,int c_nUserID,char * c_pNewsServerIP,int c_nNewsServerPort);
	int MakeUserRegReq(char *,unsigned int c_unProduct,char * c_pUserCode,char * c_pUserPassword,char * c_pEmail, char * c_pMobile, char * c_pTrueName, char * c_pSex,char * c_pBirthday);
	int MakeUserForceQuitReq(char *,int c_nUserID);
	int MakeUserOnlineReq(char *,int c_nUserID,int);//用户在线
	int MakeInitReq(char *);
	int MakeOnlineInitReq(char * c_pBuf,unsigned short c_usReqType);
	int MakeNormalReq(char * c_pBuf,unsigned short c_usReq,char *,int);

	int MakeLineTestReq(char *);
	int MakeQuoteSortReq(char *,char *,char *,unsigned short,unsigned short,unsigned short,unsigned short);
	int MakeReportReq(char *,int * , int c_nCount);
	int MakeUserDefReportReq(char *,int * c_pnFieldDef,int * c_pnStockId, int c_nCount);
	int MakePicReq(char *,int *c_pnStockId, int c_nCount);
	int MakeReportOnceReq(char *,int *, int c_nCount);

	int MakeHisDataReq(char *,unsigned short c_usType,unsigned short c_usCount,char * c_pCode,unsigned int c_unBDate,unsigned int c_unEDate,unsigned short c_usRight);
	int MakeMinHisDataReq(char *,unsigned short c_usType,unsigned short c_usCount,char * c_pCode,unsigned int c_unBDate,unsigned int c_unEDate);
	int MakeRealMinReq(char * c_pBuf,char * c_pCode,int c_nCount);
	int MakeRealMin_ExReq(char * c_pBuf,char * c_pCode,int c_nCodeCount,int c_nTime,int c_nRows);
	int MakeTraceReq(char * c_pBuf,char * c_pCode,int c_nBeginTime);

	int DealData(char *m_acData,int );
public:		
	int CommitUrl(CString c_strDownUrl,char * c_aczBuf,int c_iMaxCount);	
	void PutMin(int c_nStockId,MinUnit * c_pData,int c_nItemCount);
	void PutTick(int c_nStockid,TickUnit * c_pData,int c_nItemCount);		
	
	//For datas
	int GetHisKDataFromServer(char * c_pCode,unsigned short c_usCycle,unsigned short c_usWeight);
	int GetMinHisKDataFromServer(char * c_pCode,unsigned short c_usCycle,int c_nDays=0);
	int GetHisKData(char * c_pCode,unsigned short c_usCycle,unsigned short c_usWeight,char * c_pBuf, int c_nMaxLen, int c_nNewDate=0);
	int GetMinHisKData(char * c_pCode,unsigned short c_usCycle,int c_nDays,char * c_pBuf, int c_nMaxLen);
};