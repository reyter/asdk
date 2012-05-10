#ifndef _COMM_FUNC_H__
#define _COMM_FUNC_H__
#include <afx.h>
#include "../public/data.h"


#define WM_DOWNLOAD_LEN			WM_USER + 401
#define INVALID_INT				0x7FFFFFFF

CString GetFileVersion(char*  FileName);
CString GetCurrentAppDirectory();
CString GetModifyTime(CString appname);
char * ExtractDirFromFullPath(char * path);
int DownLoadData(CString c_strDownUrl,CString c_strWriteFileName,HWND c_hwnd,int *c_pnCancel);
int DeleteTmpFile(char *);
CString GetMac();

void CaclLineInRect(CPoint c_ptA,CPoint c_ptB,CRect c_rectDraw,CPoint &c_ptRetA,CPoint &c_ptRetB);
void CaclPointByMidLine(CPoint,CPoint,CPoint,CPoint &);
void CaclArrow(CPoint c_ptA,CPoint c_ptB,CPoint &c_ptRetA,CPoint &c_ptRetB);

bool IsNearLine(CPoint,CPoint,CPoint,int,int);
bool IsNearRect(CPoint c_ptA,CPoint c_ptB,CPoint c_ptC,int);
bool IsInRect(CPoint c_ptA,CPoint c_ptB,CPoint c_ptC);
bool IsNearArc(CPoint c_ptA,CPoint c_ptB,CPoint  c_ptC,int);
bool IsNearRound(CPoint c_ptA,CPoint c_ptB,CPoint c_ptC,int);

void CaclParallel(CPoint c_ptA,CPoint c_ptB,CPoint c_ptC,CPoint &c_ptD,double c_dPercent,CPoint &c_ptE,CPoint &c_ptF);

int toUnicode(char * c_pSrc,int c_nSrcLen,char * c_pDest,int c_nMaxLen);
CString toUnicodeString(char * c_pSrc,int c_nSrcLen);
int toUtf8(char * c_pSrc,char * c_pDes,int c_nDataLen);
int unicodeToAscii(CString c_strUnicode,char * c_pRet,int c_nMaxLen);
int	unicodeToAscii(WCHAR * c_wcUnicode,int c_nUnicodeLen,char * c_pRet,int c_nMaxLen);
int untf8ToAscii(char * c_pSrc,int c_nSrcLen,char * c_pDes,int c_nDataLen);
CString untf8ToString(char * c_pSrc,int c_nSrcLen);

int HttpTradeData(char * c_pHost,int c_nPort,char * c_pSendData,int c_nSendLen,char * c_pRetData);

bool IsSameWeek(unsigned int,unsigned int);
bool IsSameMonth(unsigned int,unsigned int);

//判断程序是否运行
int IsProccessExists(CString c_strApp);

int LogFile(char * c_pFile,char * c_pData,int c_nLen);
int AlignKData(KLINE * c_pKBase,int c_nBaseCount,KLINE * c_pK,int c_nKCount);

//是否跳空买
bool IsJumpDownBuy(KLINE * c_pBlock,int c_nPos);
#endif