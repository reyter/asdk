#include "StdAfx.h"
#include "Data.h"
#include "DataComm.h"
#include <wininet.h>
#include <AFXINET.H>
#include "..//zip//zlib.h"
#include "../public/deslib.h"
#include "../public/ShortSocket.h"

#define QFSET(F, B) ((F)[((B)/32)] |= (1 << ((B)%32)))
#define QFGET(F, B) (((F)[((B)/32)]) & (1 << ((B)%32)))

//extern void Log(char *,int);

CDataComm::CDataComm(void)
{
}

CDataComm::~CDataComm(void)
{
}

int CDataComm::MakeVersionReq(char * c_pBuf,unsigned int c_unProduct,char * c_pVer,char * c_pPatch)
{
	SCommHead * pHead;
	
	pHead = (SCommHead *)c_pBuf;

	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = 3085;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = 3085;
	*(unsigned int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = c_unProduct;
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int),c_pVer,10);
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) + 10,c_pPatch,10);
	pHead->m_head.SetLength(sizeof(unsigned short) * 3 + sizeof(unsigned int) + 20) ;
	
	return pHead->m_head.GetLength() + 8;
}

int CDataComm::MakeUpgradeFileReq(char * c_pBuf,unsigned int c_unProduct,char * c_pVer,int &c_nFileLen)
{
	FILE *f;
	char acFile[MAX_PATH];
	sprintf(acFile,"%s\\%s.exe",m_acCurPath,c_pVer);
	f = fopen(acFile,"rb");
	int nFileLen = 0;
	if (f)
	{
		fseek(f,0,SEEK_END);
		nFileLen = ftell(f);
		fclose(f);
		c_nFileLen = nFileLen;
	}
	SCommHead * pHead;
	
	pHead = (SCommHead *)c_pBuf;

	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = UPGRADEFILE;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = UPGRADEFILE;
	*(unsigned int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = c_unProduct;//产品号
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int),c_pVer,10);//版本号
	*(int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) + 10) = nFileLen;//开始位置
	pHead->m_head.SetLength(sizeof(unsigned short) * 3 + sizeof(unsigned int) + 10 + sizeof(int)) ;
	
	return pHead->m_head.GetLength() + 8;
}

int CDataComm::MakeUserReq(char * c_pBuf,unsigned int c_unProduct,int c_nUserID,char * c_pUserCode,char * c_pNewsServerIP,int c_nNewsServerPort)
{
	SCommHead * pHead;
	
	pHead = (SCommHead *)c_pBuf;

	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = 3007;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = 3007;
	*(unsigned int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = c_unProduct;
	*( int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int)) = c_nUserID;
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) * 2,c_pUserCode,30);
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) * 2 + 30,c_pNewsServerIP,20);
	*( int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) * 2 + 30 + 20) = c_nNewsServerPort;
	pHead->m_head.SetLength(sizeof(unsigned short) * 3 + sizeof(unsigned int) * 2 + 30 + 20 + sizeof(int));
	
	return pHead->m_head.GetLength() + 8;
}

int CDataComm::MakeIsUserOnlineReq(char * c_pBuf,int c_nUserID)
{
	SCommHead * pHead;
	
	pHead = (SCommHead *)c_pBuf;

	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = ISUSERONLINE;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = ISUSERONLINE;
	*(int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = c_nUserID;	
	pHead->m_head.SetLength(sizeof(unsigned short) * 3 + sizeof(unsigned int));
	
	return pHead->m_head.GetLength() + 8;
}

int CDataComm::MakeUserChangePasswordReq(char * c_pBuf,unsigned int c_unProduct,char * c_pUserCode,char * c_pUserPassword,char *c_pNewPassword)
{
	SCommHead * pHead;
	
	pHead = (SCommHead *)c_pBuf;

	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = 3129;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = 3129;
	*(unsigned int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = c_unProduct;
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) ,c_pUserCode,30);
	memcpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int)  + 30,c_pUserPassword,48);
	memcpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) + 30 + 48,c_pNewPassword,48);
	pHead->m_head.SetLength(sizeof(unsigned short) * 3 + sizeof(unsigned int) + 30 + 48*2 + sizeof(int));
	
	return pHead->m_head.GetLength() + 8;
}

int CDataComm::MakeNormalReq(char * c_pBuf,unsigned short c_usFunc,char * c_pData,int c_nSize)
{	
	SCommHead * pHead;
	pHead = (SCommHead *)c_pBuf;
	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = c_usFunc;//组合请求
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = c_usFunc;//报文类型	持仓(请求)
	memcpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short),c_pData,c_nSize);
	pHead->m_head.SetLength(sizeof(unsigned short) * 3 + c_nSize);		
	return pHead->m_head.GetLength() + 8;
}

int CDataComm::MakeLogInfoReq(char * c_pBuf,unsigned int c_unProduct,int c_nUserID,char * c_pNewsServerIP,int c_nNewsServerPort)
{
	SCommHead * pHead;
	
	pHead = (SCommHead *)c_pBuf;

	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = 3082;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = 3082;
	*(unsigned int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = c_unProduct;
	*( int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int)) = c_nUserID;
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) * 2,c_pNewsServerIP,20);
	*( int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) * 2 + 20) = c_nNewsServerPort;
	pHead->m_head.SetLength(sizeof(unsigned short) * 3 + sizeof(unsigned int) * 2 + 20 + sizeof(int));
	
	return pHead->m_head.GetLength() + 8;
}

int CDataComm::MakeUserRegReq(char * c_pBuf,unsigned int c_unProduct,char * c_pUserCode,char * c_pUserPassword,char * c_pEmail, char * c_pMobile,char * c_pTrueName,char * c_pSex,char * c_pBirthday)
{
	SCommHead * pHead;
	
	pHead = (SCommHead *)c_pBuf;

	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = 3008;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = 3008;
	*(unsigned int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = c_unProduct;
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int),c_pUserCode,30);
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) + 30,c_pUserPassword,30);
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) + 30 * 2,c_pEmail,100);
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) + 30 * 2 + 100 ,c_pMobile,15);
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) + 30 * 2 + 100 + 15,c_pTrueName,20);
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) + 30 * 2 + 100 + 15 + 20,c_pSex,2);
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int) + 30 * 2 + 100 + 15 + 20 + 2,c_pBirthday,20);
	pHead->m_head.SetLength(sizeof(unsigned short) * 3 + sizeof(unsigned int) + 30 * 2 + 100 + 15 + 20 + 2 + 20);
	
	return pHead->m_head.GetLength() + 8;
}

int CDataComm::MakeUserForceQuitReq(char * c_pBuf,int c_nUserID)
{
	SCommHead * pHead;
	
	pHead = (SCommHead *)c_pBuf;

	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = 3010;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = 3010;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = 1000;//通知退出
	*(unsigned short *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) * 2) = sizeof(int);//附加数据
	*(unsigned int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) * 3 ) = c_nUserID;
	pHead->m_head.SetLength(sizeof(unsigned short) * 5 + sizeof(unsigned int));	
	return pHead->m_head.GetLength() + 8;
}

int CDataComm::MakeUserOnlineReq(char * c_pBuf,int c_nUserID,int c_nFirst)
{
	SCommHead * pHead;
	
	pHead = (SCommHead *)c_pBuf;

	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = 0x000F;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = 0x000F;
	*(unsigned int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = c_nUserID;
	*(unsigned int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) + sizeof(unsigned int)) = c_nFirst;
	pHead->m_head.SetLength(sizeof(unsigned short) * 3 + sizeof(unsigned int) * 2);	
	return pHead->m_head.GetLength() + 8;
}

int CDataComm::MakeMinHisDataReq(char * c_pBuf,unsigned short c_usType,unsigned short c_usCount,char * c_pCode,unsigned int c_unBDate,unsigned int c_unEDate)
{
	SCommHead * pHead;
	pHead = (SCommHead *)c_pBuf;
	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = c_usType;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = c_usType;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = c_usCount;//证券个数
	for(int i=0; i<c_usCount; i++)
	{
		strcpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)*2 + i * (16 + sizeof(int)*2 + sizeof(unsigned short)),c_pCode + i * 16);
		*(unsigned int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)*2 + i * (16 + sizeof(int)*2 + sizeof(unsigned short)) + 16) = c_unBDate;
		*(unsigned int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)*2 + i * (16 + sizeof(int)*2 + sizeof(unsigned short)) + 16 + sizeof(int)) = c_unEDate;
	}
	pHead->m_head.SetLength(sizeof(unsigned short) * 4 + c_usCount * (16 + 2 * sizeof(int)));
	
	return pHead->m_head.GetLength() + 8;
}

int CDataComm::MakeHisDataReq(char * c_pBuf,unsigned short c_usType,unsigned short c_usCount,char * c_pCode,unsigned int c_unBDate,unsigned int c_unEDate,unsigned short c_usRight)
{
	SCommHead * pHead;
	pHead = (SCommHead *)c_pBuf;
	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = c_usType;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = c_usType;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = c_usCount;//证券个数
	for(int i=0; i<c_usCount; i++)
	{
		strcpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)*2 + i * (16 + sizeof(int)*2 + sizeof(unsigned short)),c_pCode + i * 16);
		*(unsigned int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)*2 + i * (16 + sizeof(int)*2 + sizeof(unsigned short)) + 16) = c_unBDate;
		*(unsigned int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)*2 + i * (16 + sizeof(int)*2 + sizeof(unsigned short)) + 16 + sizeof(int)) = c_unEDate;
		*(unsigned short *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)*2 + i * (16 + sizeof(int)*2 + sizeof(unsigned short)) + 16 + sizeof(int) * 2) = c_usRight;
	}
	pHead->m_head.SetLength(sizeof(unsigned short) * 4 + c_usCount * (16 + 2 * sizeof(int) + sizeof(unsigned short)));
	
	return pHead->m_head.GetLength() + 8;
}
int CDataComm::MakeTraceReq(char * c_pBuf,char * c_pCode,int c_nBeginTime)
{
	SCommHead * pHead;
	pHead = (SCommHead *)c_pBuf;
	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = 2;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = 2;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = 1;//证券个数
	strncpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)*2,c_pCode,16);
	*(unsigned short *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)*2 + 16) = c_nBeginTime;//开始时间
	pHead->m_head.SetLength(sizeof(unsigned short) * 4 + 16 + sizeof(unsigned short));
	
	return pHead->m_head.GetLength() + 8;
}
int CDataComm::MakeRealMinReq(char * c_pBuf,char *c_pCode,int c_nCount)
{
	SCommHead * pHead;
	pHead = (SCommHead *)c_pBuf;
	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = 4;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = 4;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = c_nCount;//证券个数
	memset(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)*2,0,c_nCount*16);//前12个字符为股票代码，后4个字节作为开始分钟时间，默认为0
	for(int i=0; i<c_nCount; i++)
	{
		strcpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)*2 + i * 16,c_pCode + i * 16);		
	}
	pHead->m_head.SetLength(sizeof(unsigned short) * 4 + c_nCount * 16);
	
	return pHead->m_head.GetLength() + 8;
}

int CDataComm::MakeRealMin_ExReq(char * c_pBuf,char *c_pCode,int c_nCount,int c_nTime,int c_nRows)
{
	SCommHead * pHead;
	pHead = (SCommHead *)c_pBuf;
	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usFuncNo = 11;
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = 11;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = c_nCount;//证券个数
	*(int *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) * 2) = c_nTime;//开始时间
	*(unsigned short *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short) * 2 + sizeof(int)) = c_nRows;//记录条数
	memset(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)*2 + sizeof(int) + sizeof(unsigned short),0,c_nCount*16);//
	for(int i=0; i<c_nCount; i++)
	{
		strcpy(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)*2 + sizeof(int) + sizeof(unsigned short) + i * 16,c_pCode + i * 16);		
	}
	pHead->m_head.SetLength(sizeof(unsigned short) * 4 + sizeof(int) + sizeof(unsigned short) + c_nCount * 16);
	
	return pHead->m_head.GetLength() + 8;
}

int CDataComm::MakeInitReq(char * c_pBuf)
{
	SCommHead * pHead;
	pHead = (SCommHead *)c_pBuf;
	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = 0;
	pHead->m_head.SetLength(sizeof(unsigned short) * 4);
	pHead->m_usFuncNo = 1;
	return pHead->m_head.GetLength() + 8;
}

int CDataComm::MakeOnlineInitReq(char * c_pBuf,unsigned short c_usReqType)
{
	SCommHead * pHead;
	pHead = (SCommHead *)c_pBuf;
	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = c_usReqType;//ONLINEINITDATA;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = 0;
	pHead->m_head.SetLength(sizeof(unsigned short) * 4);
	pHead->m_usFuncNo = c_usReqType;//ONLINEINITDATA;
	return pHead->m_head.GetLength() + 8;
}

//发送线路测试
int CDataComm::MakeLineTestReq(char * c_pBuf)
{
	SCommHead * pHead;
	pHead = (SCommHead *)c_pBuf;

	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usReqCount = 1;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead)) = LINETESTREQ;
	*(unsigned short *)(c_pBuf + sizeof(SCommHead) + sizeof(unsigned short)) = 0;
	pHead->m_head.SetLength(sizeof(unsigned short) * 4);
	pHead->m_usFuncNo = LINETESTREQ;
	return pHead->m_head.GetLength() + 8;
}

//发送报价表
int CDataComm::MakeQuoteSortReq(char * c_pBuf,char * c_pStockKinds, char * c_pCols,unsigned short c_usIndexCol,unsigned short c_usSortType,unsigned short c_usBegin,unsigned short c_usCount)
{	
	SCommHead *pHead;
	pHead = (SCommHead *)c_pBuf;
	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	char *pRun = c_pBuf + sizeof(SCommHead);	

	pHead->m_usReqCount++;
	*((unsigned short *)pRun)  = QUOTESORTDATA;				pRun += sizeof(unsigned short);
	*((unsigned short *)pRun)  = strlen(c_pStockKinds);		pRun += sizeof(unsigned short);
	strcpy(pRun,c_pStockKinds);								pRun += strlen(c_pStockKinds);
	*(unsigned short *)pRun = strlen(c_pCols);				pRun += sizeof(unsigned short);
	strcpy(pRun,c_pCols);									pRun += strlen(c_pCols);
	*(unsigned short *)pRun = c_usIndexCol;					pRun += sizeof(unsigned short);
	*(unsigned short *)pRun = c_usSortType;					pRun += sizeof(unsigned short);
	*(unsigned short *)pRun = c_usBegin;					pRun += sizeof(unsigned short);
	*(unsigned short *)pRun = c_usCount;					pRun += sizeof(unsigned short);
	
	pHead->m_head.SetLength(pRun - c_pBuf - 8);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usReqCount = 1;
	pHead->m_usFuncNo = QUOTESORTDATA;
	return pHead->m_head.GetLength() + 8;;
}

//发送报价表
int CDataComm::MakeReportReq(char * c_pBuf,int * c_pnStockId, int c_nCount)
{
	unsigned usCount = 0;
	
	SCommHead *pHead;
	pHead = (SCommHead *)c_pBuf;
	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	char *pRun = c_pBuf + sizeof(SCommHead);
	//首先生成REPORTDATA
	usCount = 0;
	usCount = c_nCount;	
	if (usCount > 0)
	{
		pHead->m_usReqCount++;
		*((unsigned short *)pRun)  = REPORTDATA;// | REAL_PUSH_REQ;
		pRun += sizeof(unsigned short);
		*((unsigned short *)pRun)  = usCount;
		pRun += sizeof(unsigned short);
		memcpy(pRun,c_pnStockId,c_nCount * sizeof(int));
		pRun += sizeof(int) * c_nCount;

	}
	
	pHead->m_head.SetLength(pRun - c_pBuf - 8);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usReqCount = 1;
	pHead->m_usFuncNo = REPORTDATA;// | REAL_PUSH_REQ;
	return pHead->m_head.GetLength() + 8;;
}

//发送报价表
int CDataComm::MakeUserDefReportReq(char * c_pBuf,int * c_pnFieldDef,int * c_pnStockId, int c_nCount)
{
	unsigned usCount = 0;
	
	SCommHead *pHead;
	pHead = (SCommHead *)c_pBuf;
	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	char *pRun = c_pBuf + sizeof(SCommHead);
	//首先生成REPORTDATA
	usCount = 0;
	usCount = c_nCount;	
	if (usCount > 0)
	{
		pHead->m_usReqCount++;
		*((unsigned short *)pRun)  = USERDEFREPORTDATA;// | REAL_PUSH_REQ;
		pRun += sizeof(unsigned short);
		memcpy(pRun,(char *)c_pnFieldDef,sizeof(int) * 4);
		pRun += sizeof(int) * 4;
		*((unsigned short *)pRun)  = usCount;
		pRun += sizeof(unsigned short);
		memcpy(pRun,(char *)c_pnStockId,usCount*sizeof(int));
		pRun += sizeof(int) * usCount;
	}
	
	pHead->m_head.SetLength(pRun - c_pBuf - 8);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usReqCount = 1;
	pHead->m_usFuncNo = USERDEFREPORTDATA;// | REAL_PUSH_REQ;
	return pHead->m_head.GetLength() + 8;;
}

int CDataComm::MakePicReq(char * c_pBuf,int *c_pnStockId, int c_nCount)
{
	SStock * pStock = GetStock(*c_pnStockId);
	
	unsigned usCount = 0;
	
	SCommHead *pHead;
	pHead = (SCommHead *)c_pBuf;
	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	char *pRun = c_pBuf + sizeof(SCommHead);
	//首先生成REPORTDATA
	usCount = 0;
	usCount = c_nCount;	
	pHead->m_usReqCount = 0;
	if (usCount > 0)
	{
		pHead->m_usReqCount++;
		*((unsigned short *)pRun)  = BUYSALELIST;//REPORTDATA;// | REAL_PUSH_REQ;
		pRun += sizeof(unsigned short);
		*((unsigned short *)pRun)  = usCount;
		pRun += sizeof(unsigned short);
		for(int i=0; i<usCount; i++)
		{
			*(int *)pRun = c_pnStockId[i];
			pRun += sizeof(int);
		}
	}

	if (usCount > 0)
	{
		pHead->m_usReqCount++;
		*((unsigned short *)pRun) = 4;
		pRun += sizeof(unsigned short);
		*((unsigned short *)pRun) = usCount;
		pRun += sizeof(unsigned short);
		for(int i= 0; i<usCount; i++)
		{
			*(int *)pRun = c_pnStockId[i];
			pRun += sizeof(int);
			if (pStock)
			{
				*(unsigned int *)pRun = pStock->m_nLastMinTime;
			}
			else
				*(unsigned int *)pRun = 0;
			pRun += sizeof(unsigned int);
		}
	}

	if (usCount > 0)
	{
		pHead->m_usReqCount++;
		*((unsigned short *)pRun) = 2;
		pRun += sizeof(unsigned short);
		*((unsigned short *)pRun) = usCount;
		pRun += sizeof(unsigned short);
		for(int i= 0; i<usCount; i++)
		{
			*(int *)pRun = c_pnStockId[i];
			pRun += sizeof(int);
		}
		if (pStock)
		{
			char acFile[32];
			sprintf(acFile,"%s.trc.%d",pStock->m_sQuote.szStockCode,m_nWorkDay);
			TickUnit tu;
			int nRead = GetFromFileTail(acFile,(char *)&tu,sizeof(TickUnit));
			if(nRead == sizeof(TickUnit))
			{				
				if (tu.Time > pStock->m_nLastMinTime)
					*((unsigned short *)pRun) = 0;
				else
				*((unsigned short *)pRun) = tu.Time;
			}
			else
				*((unsigned short *)pRun) = 0;
		}
		else
			*((unsigned short *)pRun) = 0;
		pRun += sizeof(unsigned short);
	}

	pHead->m_head.SetLength(pRun - c_pBuf - 8);
	pHead->m_head.SerialNo = NewSeq();
	//pHead->m_usReqCount = 1;
	pHead->m_usFuncNo = REPORTDATA;// | REAL_PUSH_REQ;
	return pHead->m_head.GetLength() + 8;;
}

//发送报价表
int CDataComm::MakeReportOnceReq(char * c_pBuf,int * c_pnStockId, int c_nCount)
{
	unsigned usCount = 0;
	
	SCommHead *pHead;
	pHead = (SCommHead *)c_pBuf;
	pHead->m_head.Prop = pHead->m_head.MakeProp(0x03,CommxHead::ANSI,CommxHead::HOSTORDER);
	char *pRun = c_pBuf + sizeof(SCommHead);
	//首先生成REPORTDATA
	usCount = 0;
	usCount = c_nCount;	
	if (usCount > 0)
	{
		pHead->m_usReqCount++;
		*((unsigned short *)pRun)  = REPORTDATA;//| REAL_PUSH_REQ;
		pRun += sizeof(unsigned short);
		*((unsigned short *)pRun)  = usCount;
		pRun += sizeof(unsigned short);
		memcpy(pRun,(char *)c_pnStockId,c_nCount * sizeof(int));
		pRun += sizeof(int) * c_nCount;
	}
	
	pHead->m_head.SetLength(pRun - c_pBuf - 8);
	pHead->m_head.SerialNo = NewSeq();
	pHead->m_usReqCount = 1;
	pHead->m_usFuncNo = REPORTDATA;// | REAL_PUSH_REQ;
	return pHead->m_head.GetLength() + 8;;
}

void GetFieldInt(int c_nFldDef ,char * c_pBuf,unsigned int &c_unValue,int &c_iRetLen)
{
	if (c_nFldDef)
	{
		c_unValue = *(unsigned int *)c_pBuf;
		c_iRetLen += sizeof(unsigned int);
	}
}

void GetFieldInt(int c_nFldDef ,char * c_pBuf,int &c_nValue,int &c_iRetLen)
{
	if (c_nFldDef)
	{
		c_nValue = *(int *)c_pBuf;
		c_iRetLen += sizeof(int);
	}
}

//处理数据包
int CDataComm::DealData(char *m_acData,int c_nLen)
{
	SCommHead * pCommHead;
	pCommHead = (SCommHead *)m_acData;
///-	STrade trade;
	int i;
	unsigned usReq;//命令
	char * p;
	unsigned int unStockCount;
///-	char *pStocks;
	char acStockCode[STOCK_CODE_LEN + 1];
	char acStockName[STOCK_NAME_LEN + 1];
	int j;///-,k;
	SStock * pItem;
///-	unsigned int unTimes;
///-	char acMarket[3];

	int nProduct;
	int nUserId,nRoleId;
	unsigned short usItemCount;
	unsigned int unItemCount;
///-	char acBuf[1024];

	
	if (pCommHead->m_head.GetLength() < 7)
	{
		return -1;
	}
	if (pCommHead->m_head.GetLength() != c_nLen - 8)//检查正确的包长
		return -1;

	if ((pCommHead->m_head.SerialNo & 0XFF00) > 0)
	{	
		//m_pDlgGroup->OnRecvData(m_acData,c_nLen);
		return 9;
	}
	if (pCommHead->m_usFuncNo == 0XFFFF || pCommHead->m_usFuncNo == 0XFFFE)//返回错误
	{
		if (pCommHead->m_usFuncNo == 0XFFFE)
		{						
			m_nErrorCode = 0xFFFE;
			m_strErrorMsg = toUnicodeString(m_acData + sizeof(CommxHead) + sizeof(short),pCommHead->m_head.GetLength() - sizeof(short));
			return -998;
		}
		return -999;
	}
	if (pCommHead->m_usFuncNo == 15)
		return 0;

	if ((pCommHead->m_usFuncNo == 3117 ||pCommHead->m_usFuncNo == 3118) && pCommHead->m_head.GetLength() - 2 >= 8)
	{		
		int nSize = (pCommHead->m_head.GetLength() - 4)/8 * 8;
		char * pTmp = (char *)malloc(nSize);
		memcpy(pTmp,m_acData + sizeof(SCommHead),nSize);
		Decrypt(pTmp,nSize,m_acData + sizeof(SCommHead),gCfg.m_acDesKey);
		free(pTmp);
	}

///-	int nType;
	int nLen;
///-	char * pTmp,*pBuf;
///-	int nRet;
///-	int nDest;
	int nStockId;
	int nOldDateOpen = 0;
	p = m_acData + sizeof(SCommHead);
	for(i=0; i<pCommHead->m_usReqCount; i++)
	{
		usReq = *(unsigned short *)(p);
		
		p += sizeof(unsigned short);
		switch(usReq & 0x0FFF)
		{
		case LINETESTREP:
			nOldDateOpen = m_nWorkDay;
			m_nWorkDay = *(int *)p; p += sizeof(int);
			m_nWorkState = *(int *)p; p += sizeof(int);
			m_nWorkTime = *(int *)p; p += sizeof(int);

			if (nOldDateOpen != m_nWorkDay && nOldDateOpen != 0)			
			{//开盘，更新数据
				if (m_hwndNotify)
				{
					::PostMessage(m_hwndNotify,WM_UPDATE_QUOTEDATA,REPORTDATA,101);
					OnOpenDay(m_nWorkDay);
				}
			}
			break;
		case SERVERLIST:
			nLen = *((int *)p);
			p += sizeof(int);
			if (nLen == 0)
				continue;
			if (nLen > 0)
			{
				FILE * f;
				f = fopen("svrlist.xml","wb");
				if (f)
				{
					fwrite(p,1,nLen,f);
					fclose(f);
				}
			}
			break;
		case HISKMINDATA:
		case HISKMIN5DATA:
		case HISKMIN15DATA:
		case HISKMIN30DATA:
		case HISKMIN60DATA:
			unStockCount = *((unsigned short *)p);//个数
			p += sizeof(unsigned short);
			for(j=0; j<unStockCount; j++)
			{
				strncpy(acStockCode,p,STOCK_CODE_LEN);
				acStockCode[STOCK_CODE_LEN] = 0;
				p += STOCK_CODE_LEN;
				
				unItemCount = *(int *)p;	p += sizeof(int);//K线数
				
				FILE *f;
				char acFile[256];
				sprintf(acFile,"%s\\%s.%d",m_acDataPath,acStockCode,usReq);
				f = fopen(acFile,"wb");
				KLINE kline;
				MinUnit *pMin;
				if (f)
				{
					pMin = (MinUnit *)p;
					for(int n=0; n<unItemCount; n++)
					{
						kline.day = pMin[n].Time;
						kline.open = pMin[n].OpenPrice;
						kline.high = pMin[n].MaxPrice;
						kline.low = pMin[n].MinPrice;
						kline.close = pMin[n].NewPrice;
						kline.volume = pMin[n].Volume;
						kline.amount = pMin[n].Volume / 1000 * pMin[n].AvgPrice;
						fwrite(&kline,1,sizeof(KLINE),f);
					}					
					fclose(f);
				}
				else
					::PostMessage(m_hwndNotify,WM_UPDATE_QUOTEDATA,-1,-1);
				p += unItemCount * sizeof(MinUnit);
			}
			break;
		case HISKDAYDATA://日线
		case HISKWEEKDATA://周线
		case HISKMONTHDATA://月线
			unStockCount = *((unsigned short *)p);//个数
			p += sizeof(unsigned short);
			for(j=0; j<unStockCount; j++)
			{
				strncpy(acStockCode,p,STOCK_CODE_LEN);
				acStockCode[STOCK_CODE_LEN] = 0;
				p += STOCK_CODE_LEN;
				unsigned short usWeight = *(unsigned short *)p;
				p += sizeof(unsigned short);//还权标志
				unItemCount = *(int *)p;	p += sizeof(int);//K线数
				
				FILE *f;
				char acFile[256];
				sprintf(acFile,"%s\\%s.%d.%d",m_acDataPath,acStockCode,usReq,usWeight);
				f = fopen(acFile,"wb");
				if (f)
				{	
					int nValid  = 0;
					while(nValid <= unItemCount && *(int *)(p + (unItemCount-1)*sizeof(KLINE) - nValid * sizeof(KLINE)) > HISK_BEGIN_DATE)
						nValid++;
					if (nValid > 0)
					if (fwrite(p + (unItemCount - nValid) * sizeof(KLINE),1,nValid*sizeof(KLINE),f) <= 0)
					{
						::PostMessage(m_hwndNotify,WM_UPDATE_QUOTEDATA,-1,-1);
					}
					fclose(f);
				}
				else
				{
					::PostMessage(m_hwndNotify,WM_UPDATE_QUOTEDATA,-1,-1);
				}
				p += unItemCount * sizeof(KLINE);
			}
			break;
		case TRACEDATA:
			unStockCount = *((unsigned short *)p);//
			p += sizeof(unsigned short);
			for(j=0; j<unStockCount; j++)
			{
				nStockId = *(int *)p;
				p += sizeof(int);

				unItemCount = *(unsigned short *)p;
				p += sizeof(unsigned short);
				PutTick(nStockId,(TickUnit *)p,unItemCount);
				p += unItemCount * sizeof(TickUnit);
			}
			::PostMessage(m_hwndNotify,WM_UPDATE_QUOTEDATA,TRACEDATA,0);
			break;
		case REALMINSDATA:
			unStockCount = *((unsigned short *)p);//
			p += sizeof(unsigned short);
			for(j=0; j<unStockCount; j++)
			{
				nStockId = *(int *)p;
				p += sizeof(int);

				unItemCount = *(unsigned short *)p;
				p += sizeof(unsigned short);
				//if (unItemCount > 0)
				PutMin(nStockId,(MinUnit *)p,unItemCount);
				p += unItemCount * sizeof(MinUnit);
			}
			::PostMessage(m_hwndNotify,WM_UPDATE_QUOTEDATA,REALMINSDATA,0);
			break;
		case REPORTDATA:
			unStockCount = *((unsigned short *)p);
			p += sizeof(unsigned short);
			if (unStockCount == 0)
				continue;
			
			for(j=0; j<unStockCount; j++)
			{
				//获取证券代码
				nStockId = *(int *)p;
				p += sizeof(int);
				pItem = GetStock(nStockId);				
				if (pItem)
				{
					pItem->m_sQuote.zrsp = *(unsigned int *)(p);					//昨日收盘
					pItem->m_sQuote.jrkp = *(unsigned int *)(p + 1 * sizeof(unsigned int));					//今开
					pItem->m_sQuote.ztjg = *(unsigned int *)(p + 2 * sizeof(unsigned int));					//涨停价
					pItem->m_sQuote.dtjg = *(unsigned int *)(p + 3 * sizeof(unsigned int));					//跌停价
					pItem->m_sQuote.syl1 = *(unsigned int *)(p + 4 * sizeof(unsigned int));					//市盈率1
					pItem->m_sQuote.syl2 = *(unsigned int *)(p + 5 * sizeof(unsigned int));					//市盈率2
					pItem->m_sQuote.zgjg = *(unsigned int *)(p + 6 * sizeof(unsigned int));					//最高价格
					pItem->m_sQuote.zdjg = *(unsigned int *)(p + 7 * sizeof(unsigned int));					//最低价格
					pItem->m_sQuote.zjjg = *(unsigned int *)(p + 8 * sizeof(unsigned int));					//最近成交价
					pItem->m_sQuote.zjcj = *(unsigned int *)(p + 9 * sizeof(unsigned int));					//最近成交量
					pItem->m_sQuote.cjsl = *(unsigned int *)(p + 10 * sizeof(unsigned int));					//总成交量
					pItem->m_sQuote.cjje = *(unsigned int *)(p + 11 * sizeof(unsigned int));					//成交金额
					pItem->m_sQuote.cjbs = *(unsigned int *)(p + 12 * sizeof(unsigned int));					//成交笔数
					pItem->m_sQuote.BP1 = *(unsigned int *)(p + 13 * sizeof(unsigned int));
					pItem->m_sQuote.BM1 = *(unsigned int *)(p + 14 * sizeof(unsigned int));
					pItem->m_sQuote.BP2 = *(unsigned int *)(p + 15 * sizeof(unsigned int));
					pItem->m_sQuote.BM2 = *(unsigned int *)(p + 16 * sizeof(unsigned int));
					pItem->m_sQuote.BP3 = *(unsigned int *)(p + 17 * sizeof(unsigned int));
					pItem->m_sQuote.BM3 = *(unsigned int *)(p + 18 * sizeof(unsigned int));
					pItem->m_sQuote.BP4 = *(unsigned int *)(p + 19 * sizeof(unsigned int));
					pItem->m_sQuote.BM4 = *(unsigned int *)(p + 20 * sizeof(unsigned int));
					pItem->m_sQuote.BP5 = *(unsigned int *)(p + 21 * sizeof(unsigned int));
					pItem->m_sQuote.BM5 = *(unsigned int *)(p + 22 * sizeof(unsigned int));
					pItem->m_sQuote.SP1 = *(unsigned int *)(p + 23 * sizeof(unsigned int));
					pItem->m_sQuote.SM1 = *(unsigned int *)(p + 24 * sizeof(unsigned int));
					pItem->m_sQuote.SP2 = *(unsigned int *)(p + 25 * sizeof(unsigned int));
					pItem->m_sQuote.SM2 = *(unsigned int *)(p + 26 * sizeof(unsigned int));
					pItem->m_sQuote.SP3 = *(unsigned int *)(p + 27 * sizeof(unsigned int));
					pItem->m_sQuote.SM3 = *(unsigned int *)(p + 28 * sizeof(unsigned int));
					pItem->m_sQuote.SP4 = *(unsigned int *)(p + 29 * sizeof(unsigned int));
					pItem->m_sQuote.SM4 = *(unsigned int *)(p + 30 * sizeof(unsigned int));
					pItem->m_sQuote.SP5 = *(unsigned int *)(p + 31 * sizeof(unsigned int));
					pItem->m_sQuote.SM5 = *(unsigned int *)(p + 32 * sizeof(unsigned int));
					pItem->m_sQuote.day5pjzs = *(unsigned int *)(p + 33 * sizeof(unsigned int));				//5日平均总手
					pItem->m_sQuote.pjjg = *(unsigned int *)(p + 34 * sizeof(unsigned int));					//均价
					pItem->m_sQuote.wb = *(unsigned int *)(p + 35 * sizeof(unsigned int));					//委比
					pItem->m_sQuote.lb = *(unsigned int *)(p + 36 * sizeof(unsigned int));					//量比
					pItem->m_sQuote.np = *(unsigned int *)(p + 37 * sizeof(unsigned int));					//内盘
					pItem->m_sQuote.wp = *(unsigned int *)(p + 38 * sizeof(unsigned int));					//外盘
					pItem->m_sQuote.zd = *(int *)(p + 39 * sizeof(int));					//涨跌
					pItem->m_sQuote.zdfd = *(int *)(p + 40 * sizeof(int));					//涨跌幅
					pItem->m_sQuote.zf = *(int *)(p + 41 * sizeof(int));					//振幅					

							if (pItem->m_sQuote.zdjg == 99999999)
								pItem->m_sQuote.zdjg = 0;
							
							if (pItem->m_sQuote.zgjg == 99999999)
								pItem->m_sQuote.zgjg = 0;
							if (pItem->m_sQuote.zjjg == 99999999)
								pItem->m_sQuote.zjjg = 0;

					pItem->m_unPrevClose = pItem->m_sQuote.zrsp;
				}
				p += 42 * sizeof(unsigned int);
			}
			::PostMessage(m_hwndNotify,WM_UPDATE_QUOTEDATA,usReq & 0x0FFF,0);
			break;

		case BUYSALELIST:
			unStockCount = *((unsigned short *)p);
			p += sizeof(unsigned short);
			if (unStockCount == 0)
				continue;
			
			for(j=0; j<unStockCount; j++)
			{
				//获取证券代码
				nStockId = *(int *)p;
				p += sizeof(int);
				pItem = GetStock(nStockId);				
				if (pItem)
				{
					pItem->m_sQuote.zrsp = *(unsigned int *)(p);					//昨日收盘
					pItem->m_sQuote.jrkp = *(unsigned int *)(p + 1 * sizeof(unsigned int));					//今开
					pItem->m_sQuote.ztjg = *(unsigned int *)(p + 2 * sizeof(unsigned int));					//涨停价
					pItem->m_sQuote.dtjg = *(unsigned int *)(p + 3 * sizeof(unsigned int));					//跌停价
					pItem->m_sQuote.syl1 = *(unsigned int *)(p + 4 * sizeof(unsigned int));					//市盈率1
					pItem->m_sQuote.syl2 = *(unsigned int *)(p + 5 * sizeof(unsigned int));					//市盈率2
					pItem->m_sQuote.zgjg = *(unsigned int *)(p + 6 * sizeof(unsigned int));					//最高价格
					pItem->m_sQuote.zdjg = *(unsigned int *)(p + 7 * sizeof(unsigned int));					//最低价格
					pItem->m_sQuote.zjjg = *(unsigned int *)(p + 8 * sizeof(unsigned int));					//最近成交价
					pItem->m_sQuote.zjcj = *(unsigned int *)(p + 9 * sizeof(unsigned int));					//最近成交量
					pItem->m_sQuote.cjsl = *(unsigned int *)(p + 10 * sizeof(unsigned int));					//总成交量
					pItem->m_sQuote.cjje = *(unsigned int *)(p + 11 * sizeof(unsigned int));					//成交金额
					pItem->m_sQuote.cjbs = *(unsigned int *)(p + 12 * sizeof(unsigned int));					//成交笔数
					pItem->m_sQuote.BP1 = *(unsigned int *)(p + 13 * sizeof(unsigned int));
					pItem->m_sQuote.BM1 = *(unsigned int *)(p + 14 * sizeof(unsigned int));
					pItem->m_sQuote.BP2 = *(unsigned int *)(p + 15 * sizeof(unsigned int));
					pItem->m_sQuote.BM2 = *(unsigned int *)(p + 16 * sizeof(unsigned int));
					pItem->m_sQuote.BP3 = *(unsigned int *)(p + 17 * sizeof(unsigned int));
					pItem->m_sQuote.BM3 = *(unsigned int *)(p + 18 * sizeof(unsigned int));
					pItem->m_sQuote.BP4 = *(unsigned int *)(p + 19 * sizeof(unsigned int));
					pItem->m_sQuote.BM4 = *(unsigned int *)(p + 20 * sizeof(unsigned int));
					pItem->m_sQuote.BP5 = *(unsigned int *)(p + 21 * sizeof(unsigned int));
					pItem->m_sQuote.BM5 = *(unsigned int *)(p + 22 * sizeof(unsigned int));
					pItem->m_sQuote.SP1 = *(unsigned int *)(p + 23 * sizeof(unsigned int));
					pItem->m_sQuote.SM1 = *(unsigned int *)(p + 24 * sizeof(unsigned int));
					pItem->m_sQuote.SP2 = *(unsigned int *)(p + 25 * sizeof(unsigned int));
					pItem->m_sQuote.SM2 = *(unsigned int *)(p + 26 * sizeof(unsigned int));
					pItem->m_sQuote.SP3 = *(unsigned int *)(p + 27 * sizeof(unsigned int));
					pItem->m_sQuote.SM3 = *(unsigned int *)(p + 28 * sizeof(unsigned int));
					pItem->m_sQuote.SP4 = *(unsigned int *)(p + 29 * sizeof(unsigned int));
					pItem->m_sQuote.SM4 = *(unsigned int *)(p + 30 * sizeof(unsigned int));
					pItem->m_sQuote.SP5 = *(unsigned int *)(p + 31 * sizeof(unsigned int));
					pItem->m_sQuote.SM5 = *(unsigned int *)(p + 32 * sizeof(unsigned int));
					pItem->m_sQuote.day5pjzs = *(unsigned int *)(p + 33 * sizeof(unsigned int));				//5日平均总手
					pItem->m_sQuote.pjjg = *(unsigned int *)(p + 34 * sizeof(unsigned int));					//均价
					pItem->m_sQuote.wb = *(unsigned int *)(p + 35 * sizeof(unsigned int));					//委比
					pItem->m_sQuote.lb = *(unsigned int *)(p + 36 * sizeof(unsigned int));					//量比
					pItem->m_sQuote.np = *(unsigned int *)(p + 37 * sizeof(unsigned int));					//内盘
					pItem->m_sQuote.wp = *(unsigned int *)(p + 38 * sizeof(unsigned int));					//外盘
					pItem->m_sQuote.zd = *(int *)(p + 39 * sizeof(int));					//涨跌
					pItem->m_sQuote.zdfd = *(int *)(p + 40 * sizeof(int));					//涨跌幅
					pItem->m_sQuote.zf = *(int *)(p + 41 * sizeof(int));					//振幅					

							if (pItem->m_sQuote.zdjg == 99999999)
								pItem->m_sQuote.zdjg = 0;
							
							if (pItem->m_sQuote.zgjg == 99999999)
								pItem->m_sQuote.zgjg = 0;
							if (pItem->m_sQuote.zjjg == 99999999)
								pItem->m_sQuote.zjjg = 0;
					pItem->m_sQuote.MBP1 = *(unsigned int *)(p + 42 * sizeof(unsigned int));
					pItem->m_sQuote.MBM1 = *(unsigned int *)(p + 43 * sizeof(unsigned int));
					pItem->m_sQuote.MBP2 = *(unsigned int *)(p + 44 * sizeof(unsigned int));
					pItem->m_sQuote.MBM2 = *(unsigned int *)(p + 45 * sizeof(unsigned int));
					pItem->m_sQuote.MBP3 = *(unsigned int *)(p + 46 * sizeof(unsigned int));
					pItem->m_sQuote.MBM3 = *(unsigned int *)(p + 47 * sizeof(unsigned int));
					pItem->m_sQuote.MBP4 = *(unsigned int *)(p + 48 * sizeof(unsigned int));
					pItem->m_sQuote.MBM4 = *(unsigned int *)(p + 49 * sizeof(unsigned int));
					pItem->m_sQuote.MBP5 = *(unsigned int *)(p + 50 * sizeof(unsigned int));
					pItem->m_sQuote.MBM5 = *(unsigned int *)(p + 51 * sizeof(unsigned int));
					pItem->m_sQuote.MSP1 = *(unsigned int *)(p + 52 * sizeof(unsigned int));
					pItem->m_sQuote.MSM1 = *(unsigned int *)(p + 53 * sizeof(unsigned int));
					pItem->m_sQuote.MSP2 = *(unsigned int *)(p + 54 * sizeof(unsigned int));
					pItem->m_sQuote.MSM2 = *(unsigned int *)(p + 55 * sizeof(unsigned int));
					pItem->m_sQuote.MSP3 = *(unsigned int *)(p + 56 * sizeof(unsigned int));
					pItem->m_sQuote.MSM3 = *(unsigned int *)(p + 57 * sizeof(unsigned int));
					pItem->m_sQuote.MSP4 = *(unsigned int *)(p + 58 * sizeof(unsigned int));
					pItem->m_sQuote.MSM4 = *(unsigned int *)(p + 59 * sizeof(unsigned int));
					pItem->m_sQuote.MSP5 = *(unsigned int *)(p + 60 * sizeof(unsigned int));
					pItem->m_sQuote.MSM5 = *(unsigned int *)(p + 61 * sizeof(unsigned int));

					pItem->m_unPrevClose = pItem->m_sQuote.zrsp;
				}
				p += 42 * sizeof(unsigned int);
			}
			::PostMessage(m_hwndNotify,WM_UPDATE_QUOTEDATA,usReq & 0x0FFF,0);
			break;
		case USERDEFREPORTDATA:
			{
				int nFieldDef[4] = {0};
				nFieldDef[0] = *(int *)p;	p += sizeof(int);
				nFieldDef[1] = *(int *)p;	p += sizeof(int);
				nFieldDef[2] = *(int *)p;	p += sizeof(int);
				nFieldDef[3] = *(int *)p;	p += sizeof(int);
			unStockCount = *((unsigned short *)p);
			p += sizeof(unsigned short);
			if (unStockCount == 0)
				continue;
			
			for(j=0; j<unStockCount; j++)
			{
				//获取证券代码
				if (QFGET(nFieldDef,QFD_STOCKCODE))
				{
					strncpy(acStockCode,p,STOCK_CODE_LEN);
					acStockCode[STOCK_CODE_LEN] = 0;
					p += STOCK_CODE_LEN;
				}
				acStockName[0] = 0;
				if (QFGET(nFieldDef,QFD_STOCKNAME))
				{
					strncpy(acStockName,p,STOCK_NAME_LEN);
					p += STOCK_NAME_LEN;
				}
				pItem = GetStock(acStockCode);				
				if (pItem)
				{
					if(strlen(acStockName) > 0)
					{
						pItem->m_strName = toUnicodeString(acStockName,strlen(acStockName));
						strncpy(pItem->m_sQuote.szStockName,acStockName,STOCK_NAME_LEN);
					}
					int iRetLen = 0;
					GetFieldInt(QFGET(nFieldDef, QFD_ZRSP),p + iRetLen,pItem->m_sQuote.zrsp,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_JRKP),p + iRetLen,pItem->m_sQuote.jrkp,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_ZTJG),p + iRetLen,pItem->m_sQuote.ztjg,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_DTJG),p + iRetLen,pItem->m_sQuote.dtjg,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_SYL1),p + iRetLen,pItem->m_sQuote.syl1,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_SYL2),p + iRetLen,pItem->m_sQuote.syl2,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_ZGJG),p + iRetLen,pItem->m_sQuote.zgjg,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_ZDJG),p + iRetLen,pItem->m_sQuote.zdjg,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_ZJJG),p + iRetLen,pItem->m_sQuote.zjjg,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_ZJCJ),p + iRetLen,pItem->m_sQuote.zjcj,iRetLen);						
					GetFieldInt(QFGET(nFieldDef, QFD_CJSL),p + iRetLen,pItem->m_sQuote.cjsl,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_CJJE),p + iRetLen,pItem->m_sQuote.cjje,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_CJBS),p + iRetLen,pItem->m_sQuote.cjbs,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_BP1) ,p + iRetLen,pItem->m_sQuote.BP1,iRetLen);								
					GetFieldInt(QFGET(nFieldDef, QFD_BM1) ,p + iRetLen,pItem->m_sQuote.BM1,iRetLen);												
					GetFieldInt(QFGET(nFieldDef, QFD_BP2) ,p + iRetLen,pItem->m_sQuote.BP2,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_BM2) ,p + iRetLen,pItem->m_sQuote.BM2,iRetLen);						
					GetFieldInt(QFGET(nFieldDef, QFD_BP3) ,p + iRetLen,pItem->m_sQuote.BP3,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_BM3) ,p + iRetLen,pItem->m_sQuote.BM3,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_BP4) ,p + iRetLen,pItem->m_sQuote.BP4,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_BM4) ,p + iRetLen,pItem->m_sQuote.BM4,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_BP5) ,p + iRetLen,pItem->m_sQuote.BP5,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_BM5) ,p + iRetLen,pItem->m_sQuote.BM5,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_SP1) ,p + iRetLen,pItem->m_sQuote.SP1,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_SM1) ,p + iRetLen,pItem->m_sQuote.SM1,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_SP2) ,p + iRetLen,pItem->m_sQuote.SP2,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_SM2) ,p + iRetLen,pItem->m_sQuote.SM2,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_SP3) ,p + iRetLen,pItem->m_sQuote.SP3,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_SM3) ,p + iRetLen,pItem->m_sQuote.SM3,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_SP4) ,p + iRetLen,pItem->m_sQuote.SP4,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_SM4) ,p + iRetLen,pItem->m_sQuote.SM4,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_SP5) ,p + iRetLen,pItem->m_sQuote.SP5,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_SM5) ,p + iRetLen,pItem->m_sQuote.SM5,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_5RPJZS),p + iRetLen,pItem->m_sQuote.day5pjzs,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_PJJG),p + iRetLen,pItem->m_sQuote.pjjg,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_WB),p + iRetLen,pItem->m_sQuote.wb,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_LB),p + iRetLen,pItem->m_sQuote.lb,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_NP),p + iRetLen,pItem->m_sQuote.np,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_WP),p + iRetLen,pItem->m_sQuote.wp,iRetLen);						
					GetFieldInt(QFGET(nFieldDef, QFD_ZDF),p + iRetLen,pItem->m_sQuote.zdfd,iRetLen);
					GetFieldInt(QFGET(nFieldDef, QFD_ZF),p + iRetLen,pItem->m_sQuote.zf,iRetLen);
					if (pItem->m_sQuote.zrsp > 0)
						pItem->m_sQuote.zd = int(pItem->m_sQuote.zjjg) - int(pItem->m_sQuote.zrsp);
					else
						pItem->m_sQuote.zd = 0;	
					pItem->m_unPrevClose = pItem->m_sQuote.zrsp;
					p += iRetLen;
				}
			}
			::PostMessage(m_hwndNotify,WM_UPDATE_QUOTEDATA,usReq & 0x0FFF,0);
			break;
			}
		case 3119:
			{
			memset(m_acLoginCode,0,sizeof(m_acLoginCode));
			memset(m_acEndDate,0,sizeof(m_acEndDate));
			memset(m_acNikeName,0,sizeof(m_acNikeName));
			memset(m_acMail,0,sizeof(m_acMail));
			memset(m_acTel,0,sizeof(m_acTel));
			memset(m_acMobile,0,sizeof(m_acMobile));
			tagUserInfo *pInfo = (tagUserInfo *)p;
			m_nMemberType = pInfo->nMemberType;
			p += sizeof(tagUserInfo);
			m_nUserID = pInfo->nUserId;			
			strncpy(m_acLoginCode,pInfo->szLoginCode,64); p += 30;
			strncpy(m_acNikeName,pInfo->szNickName,64); p += 20;			
			gCfg.m_strUser = m_acLoginCode;
			break;
			}
		case INITDATA://STOCKINFO
			{
				unStockCount = *(unsigned short *)p; p+= sizeof(unsigned short);
				for(int n=0; n<unStockCount; n++)
				{
					int nZrsp;
					char acStockCode[16];
					char acStockName[64];
					double dStockAmount;
					nStockId = *(int *)p;
					p += sizeof(int);
					strncpy(acStockCode,p,16);	p += 16;
					acStockCode[16] = 0;
					memset(acStockName,0,64);
					strncpy(acStockName,p,64);	p += 64;
					nZrsp = *(int *)p;	p += sizeof(int);
					dStockAmount = *(double *)p;p += sizeof(double);

					bool bNew = false;
					SStock * pItem = NULL;
					pItem = GetStock(nStockId);
					if (pItem == NULL)
					{
						bNew = true;
						pItem = new SStock();
						pItem->init();
					}
					pItem->m_sQuote.nStockId = nStockId;
					strncpy(pItem->m_sQuote.szStockCode,acStockCode,16);
					pItem->m_sQuote.szStockCode[16] = 0;
					strncpy(pItem->m_sQuote.szStockName,acStockName,64);
					pItem->m_strName = toUnicodeString(pItem->m_sQuote.szStockName,strlen(pItem->m_sQuote.szStockName));
					pItem->m_dZgb = dStockAmount;
					pItem->m_unPrevClose = nZrsp;
					if (bNew)
					{
						m_vpStocks.push_back(pItem);
						m_mapStocks[toUnicodeString(pItem->m_sQuote.szStockCode,strlen(pItem->m_sQuote.szStockCode))] = pItem;
						m_mapUNStocks[nStockId] = pItem;
					}

				}
				break;
			};
		case 3085:
			nProduct = *(int *)p; p += sizeof(int);

			strncpy(gCfg.m_acVer,p,10); p += 10;
			strncpy(gCfg.m_acPatch,p,10); p += 10;			
			gCfg.m_usUpdateType = *(unsigned short *)p; p += sizeof(unsigned short);
			gCfg.m_usForce = *(unsigned short *)p; p += sizeof(unsigned short);
			strncpy(gCfg.m_acVerUrl,p,100); p += 100;
			strncpy(gCfg.m_acPatchUrl,p,100); p += 100;
			strncpy(gCfg.m_acUpdateInfo,p,1024); p += 1024;
			break;
		case UPGRADEFILE:
			{
				nProduct = *(int *)p; p += sizeof(int);
				char acVer[11];
				strncpy(acVer,p,10); p += 10;
				acVer[10] = 0;
				int nFileBeginPos = *(int *)p; p += sizeof(int);//开始位置
				int nFileTotalLen = *(int *)p; p += sizeof(int);//总长度
				int nDataLen = *(int *)p; p += sizeof(int);//当前数据长度
				if (nFileTotalLen <= 0)
					return -999;
				FILE *f;
				char acFile[MAX_PATH];
				sprintf(acFile,"%s\\%s.exe",m_acCurPath,acVer);
				f = fopen(acFile,"ab");
				if (f)
				{
					fseek(f,0,SEEK_END);
					int nCurLen = ftell(f);
					if(nCurLen != nFileBeginPos)//开始位置不正确
					{
						fclose(f);
						return -1;
					}
					if (fwrite(p,1,nDataLen,f) != nDataLen)
					{
						fclose(f);
						return -2;
					}
					fclose(f);
					if (nDataLen + nFileBeginPos == nFileTotalLen)
					{
						return 1;//完成了
					}
					return 0;
				}
				else
					return -9;
				break;
			}
		case 3103:
			nUserId = *(int *)p; p += sizeof(int);
			nRoleId = *(int *)p; p += sizeof(int);
			usItemCount = *(unsigned short *)p; p += sizeof(unsigned short);
            
			if (usItemCount > 0)
			{
                int nSet = 0;
                nSet = *(unsigned int *)p; p += sizeof(unsigned int);

                ::PostMessage(m_hwndNotify,WM_UPDATE_QUOTEDATA,usReq & 0x0FFF,nSet);
			}
			break;
		case 3109:
			nUserId = *(int *)p; p += sizeof(int);
			nRoleId = *(int *)p; p += sizeof(int);
			usItemCount = *(unsigned short *)p; p += sizeof(unsigned short);
            
			if (usItemCount > 0)
			{
                int nSet = 0;
				int nStkSet = 0;
                nSet = *(unsigned int *)p; p += sizeof(unsigned int);
				nStkSet = *(unsigned int *)p; p += sizeof(unsigned int);
                ::PostMessage(m_hwndNotify,WM_UPDATE_QUOTEDATA,usReq & 0x0FFF,nSet);
			}
			break;
		case 3010://通知退出
			if (*(unsigned short *)p != 1000)
				return 0;
			p += sizeof(unsigned short);
			p += sizeof(unsigned short);
			nUserId = *(int *)p;
			if (nUserId != m_nUserID)
				return 0;
			::PostMessage(m_hwndNotify,WM_FORCE_QUIT,0,0);
			break;
		default:
			return -1;
		}
	}
	return 0;
}

//提交Url，获取返回信息
int CDataComm::CommitUrl(CString c_strDownUrl,char * c_aczBuf,int c_iMaxCount)
{
	CString strSentence, strWriteName;;
	CInternetSession sess;
	CHttpFile* fileGet;
	unsigned int	uiTotalLen = 0;
	sess.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000);      // 5秒的连接超时
	sess.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 2000);           // 1秒的发送超时
	sess.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 1000 * 60);        // 60秒的接收超时
	sess.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 2000);     // 2秒的发送超时
	sess.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 1000 * 60);       // 60秒的接收超时
	sess.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);          // 1次重试

	try
	{
		fileGet=(CHttpFile*)sess.OpenURL(c_strDownUrl);
	}
	catch(CException* )
	{
		fileGet = 0;
		return -9;
		//throw;
	}    

	if(fileGet)
	{
		DWORD dwStatus;
		DWORD dwBuffLen = sizeof(dwStatus);
		BOOL bSuccess = fileGet->QueryInfo(HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER, &dwStatus, &dwBuffLen);
		CString strEnter;
		strEnter = "\n";
		if( bSuccess && dwStatus>= 200&& dwStatus<300 ) 
		{ 
			int n;
			while(uiTotalLen < c_iMaxCount)
			{
				n = fileGet->Read(c_aczBuf + uiTotalLen ,c_iMaxCount - uiTotalLen);
				if (n<=0)
					break;
				uiTotalLen += n;
			}
		}
		else 
		{
			strSentence.Format(_T("打开网页文件出错，错误码：%d"), dwStatus);
			return -2;
		}
		fileGet->Close();
		delete fileGet;
	}
	else
		return -3;

	sess.Close();
	return 0;
}

void CDataComm::PutTick(int c_nStockId,TickUnit * c_pData,int c_nItemCount)
{
	SStock * pStock = GetStock(c_nStockId);	
	char acFile[32];		
	int nSize = sizeof(TickUnit);
	if (pStock)
	{
		sprintf(acFile,"%s.trc.%d",pStock->m_sQuote.szStockCode,m_nWorkDay);
		char * pData = (char *)malloc(nSize * 100000);
		int nRead = GetFromFile(acFile,pData,100000 * nSize);
		int nTraceCount = 0;
		nTraceCount = nRead;
		
		nTraceCount /= nSize;
		if (nRead < nSize)
		{
			WriteToFile(acFile,(char *)c_pData,c_nItemCount * nSize);
			free(pData);
			return;
		}
		else
		{
			int nPos = nTraceCount;
			while(nPos > 0)
			{
				if (((TickUnit *)pData)[nPos-1].Time < ((TickUnit *)c_pData)->Time)
				{					
					memcpy(pData + nSize * nPos,c_pData,c_nItemCount * nSize);
					WriteToFile(acFile,pData,(nPos + c_nItemCount) * nSize);					
					free(pData);
					return;
				}
				nPos--;
			}
			WriteToFile(acFile,(char *)c_pData,c_nItemCount * nSize);
			free(pData);
			return;
		}
	}
}
void CDataComm::PutMin(int c_nStockId,MinUnit * c_pData,int c_nItemCount)
{
	SStock * pStock = GetStock(c_nStockId);
	if (pStock == NULL)
		return;
	MinUnit * pMin;///-, *pNewMin;	
	bool bInit = false;
	if (pStock->m_nMinItemCount == 0)
	{
		if (pStock->m_pMinData == NULL)
			pStock->m_pMinData = (char *)malloc(256 * sizeof(MinUnit));
		memset(pStock->m_pMinData,0,sizeof(MinUnit) * 256);
		pMin = (MinUnit *)pStock->m_pMinData;
		bInit = true;
		pStock->m_nLastMinTime = 0;
	}
	else
	{
		if (c_nItemCount == 0)
		{
			pStock->m_nMinItemCount = 0;
			bInit = true;
			pStock->m_nLastMinTime = 0;
		}
		pMin = (MinUnit *)pStock->m_pMinData;
	}
	if (pMin && bInit)
	{
		//需要初始化分时
		for(int n=0; n<121; n++)
		{
			pMin[n].Time = 570 + n;
			pMin[n].NewPrice = pStock->m_sQuote.zrsp;
			pMin[n].AvgPrice = pStock->m_sQuote.zrsp;
		}
		for(int n=0; n<121; n++)
		{
			pMin[121 + n].Time = 780 + n;
			pMin[121 + n].NewPrice = pStock->m_sQuote.zrsp;
			pMin[121 + n].AvgPrice = pStock->m_sQuote.zrsp;
		}
	}

	if (c_nItemCount == 0)
		return;

	MinUnit * pSrc = (MinUnit *)c_pData;
	int k=0;
	while(pMin[k].Time < pSrc[0].Time)
	{
		k++;
	}
	for(int n=0; n<c_nItemCount; n++)
	{
		while(true)
		{			
			pStock->m_nLastMinTime = pSrc[n].Time;
			if (pMin[k].Time == pSrc[n].Time)
			{
				if (pSrc[n].AvgPrice > 0)
					pMin[k].AvgPrice = pSrc[n].AvgPrice;
				else
					pMin[k].AvgPrice = pSrc[n].NewPrice;
				pMin[k].MaxPrice = pSrc[n].MaxPrice;
				pMin[k].MinPrice = pSrc[n].MinPrice;
				pMin[k].NewPrice = pSrc[n].NewPrice;
				pMin[k].OpenPrice = pSrc[n].OpenPrice;
				pMin[k].Volume = pSrc[n].Volume;
				k++;
				break;
			}
			else
			{
				if (k > 242)
					break;
				pMin[k].AvgPrice = pSrc[n].AvgPrice;
				pMin[k].MaxPrice = pSrc[n].MaxPrice;
				pMin[k].MinPrice = pSrc[n].MinPrice;
				pMin[k].NewPrice = pSrc[n].NewPrice;
				pMin[k].OpenPrice = pSrc[n].OpenPrice;
				pMin[k].Volume = 0;
				k++;
			}
		}
		if (k > 242)
			break;
	}
	pStock->m_nMinItemCount = k;
}

int CDataComm::GetMinHisKDataFromServer(char * c_pCode,unsigned short c_usCycle,int c_nDays)
{
	char acBuf[1024];
	int nRet = 0;	
	nRet = MakeMinHisDataReq(acBuf,c_usCycle,1,c_pCode,HISK_BEGIN_DATE,c_nDays);	
	if (nRet > 0)
		if (gpCommSocket)
			gpCommSocket->SendData(acBuf,nRet,true);
	return 0;
}

int CDataComm::GetHisKDataFromServer(char * c_pCode,unsigned short c_usCycle,unsigned short c_usWeight)
{
	char acBuf[1024];
	int nRet = 0;	
	nRet = MakeHisDataReq(acBuf,c_usCycle,1,c_pCode,HISK_BEGIN_DATE,0,c_usWeight);	
	if (nRet > 0)
		if (gpCommSocket)
			gpCommSocket->SendData(acBuf,nRet,true);
	return 0;
}

int CDataComm::GetMinHisKData(char * c_pCode,unsigned short c_usCycle,int c_nDays,char * c_pBuf, int c_nMaxLen)
{
	//读入历史文件
	char acFile[MAX_PATH];
	int nReadLen = 0;
	SStock * pStock = GetStock(c_pCode);
	if (pStock == NULL)
		return 0;
	sprintf(acFile,"%s\\%s.%d",m_acDataPath,c_pCode,c_usCycle);
	FILE * f;

	if (true)//直接去服务器请求
	{//服务器请求
		GetMinHisKDataFromServer(c_pCode,c_usCycle,c_nDays);
		//再去读文件
		f = fopen(acFile,"rb");
		if (f)
		{
			nReadLen = fread(c_pBuf,1,c_nMaxLen,f);		
			fclose(f);
		}
	}
	return nReadLen;
}

int CDataComm::GetHisKData(char * c_pCode,unsigned short c_usCycle,unsigned short c_usWeight,char * c_pBuf, int c_nMaxLen,int c_nNewDate)
{
	//读入历史文件
	char acFile[MAX_PATH];
	int nReadLen = 0;
	SStock * pStock = GetStock(c_pCode);
	if (pStock == NULL)
		return 0;
	sprintf(acFile,"%s\\%s.%d.%d",m_acDataPath,c_pCode,c_usCycle,c_usWeight);
	FILE * f;
	/*
	if (true)//直接去服务器请求
	{//服务器请求
		GetHisKDataFromServer(c_pCode,c_usCycle);
		//再去读文件
		f = fopen(acFile,"rb");
		if (f)
		{
			nReadLen = fread(c_pBuf,1,c_nMaxLen,f);		
			fclose(f);
		}
	}
	return nReadLen;
	*/
	if (c_nNewDate > 0)
	{
		f = fopen(acFile,"rb");
		if (f)
		{
			nReadLen = fread(c_pBuf,1,c_nMaxLen,f);		
			fclose(f);
		}
		if (nReadLen > 0)//检查是否需要更新
		{
			int nDate;
			nDate = *(int *)(c_pBuf + nReadLen - sizeof(KLINE));
			if (nDate < c_nNewDate)
			{			
				nReadLen = 0;
			}
		}
	}
	if (nReadLen <= 0)
	{//服务器请求
		GetHisKDataFromServer(c_pCode,c_usCycle,c_usWeight);
		//再去读文件
		f = fopen(acFile,"rb");
		if (f)
		{
			nReadLen = fread(c_pBuf,1,c_nMaxLen,f);		
			fclose(f);
		}
	}
	return nReadLen;
}
