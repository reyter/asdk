#include "StdAfx.h"
#include "Data.h"
#include <wininet.h>
#include <AFXINET.H>
#include "..//zip//zlib.h"

#define QFSET(F, B) ((F)[((B)/32)] |= (1 << ((B)%32)))
#define QFGET(F, B) (((F)[((B)/32)]) & (1 << ((B)%32)))

CData::CData(void)
{
	m_nMemberType = 1;
	m_usWeight = 2;
	m_usSeq = 0;

	m_nStockSource = 0;
	m_nWorkDay = 0;
	m_nWorkState = 0;
	InitQuickKey();
	m_strResetPassUrl = _T("");
	for(int n=0; n<32; n++)
	{
		SUserDefReportItem * pItem = (SUserDefReportItem *)malloc(sizeof(SUserDefReportItem));
		pItem->nCount = 0;
		pItem->hwndFrom = 0;
		m_vpUserDefReportItems.push_back(pItem);
	}

	USES_CONVERSION;
	WCHAR acPath[MAX_PATH];
	//GetCurrentDirectory(MAX_PATH,acPath);

	GetModuleFileName(NULL,acPath,MAX_PATH);
	strcpy(m_acCurPath,(char *)W2A(acPath));
	ExtractDirFromFullPath(m_acCurPath);
	
	sprintf(m_acDataPath,"%s\\tmpdata",m_acCurPath);
	sprintf(m_acIniFile,"%s\\lcgj.ini",m_acCurPath);   

}

CData::~CData(void)
{
	while(m_vpStocks.size() > 0)
	{
		SStock * pStock = *m_vpStocks.begin();
		m_vpStocks.erase(m_vpStocks.begin());
		if (pStock->m_pMinData)
			free(pStock->m_pMinData);
		delete pStock;
	}
	while(m_vpUserDefReportItems.size())
	{
		//SUserDefReportItem * pItem = (SUserDefReportItem *)(m_vpUserDefReportItems.back());
		free((SUserDefReportItem *)m_vpUserDefReportItems.back());
		m_vpUserDefReportItems.pop_back();
	}
	while(m_vpQuickKey.size())
	{
		delete m_vpQuickKey.back();
		m_vpQuickKey.pop_back();
	}

	while(m_mapStocks.size())
	{
		m_mapStocks.clear();
	}
	while(m_mapUNStocks.size())
	{
		m_mapUNStocks.clear();
	}
	//_CrtDumpMemoryLeaks();
	//CloseHandle(m_hRecvEvent);
}

SStock * CData::GetStock(unsigned int unCode)
{
	if (m_mapUNStocks.find(unCode) != m_mapUNStocks.end())
		return m_mapUNStocks[unCode];
	return NULL;
}
SStock * CData::GetStock(CString c_strCode)
{
	CString strCode;
	strCode = c_strCode;
	if (m_mapStocks.find(strCode) != m_mapStocks.end())
		return m_mapStocks[strCode];

	std::vector<SStock *>::iterator iter;
	for(iter = m_vpStocks.begin(); iter != m_vpStocks.end(); iter++)	
	{		
		if (strlen((*iter)->m_acKind) > 0 && (*iter)->m_strName == c_strCode)
			return *iter;
	}
	return NULL;	
}
SStock * CData::GetStock(char * c_pStockCode)
{
	CString strCode;
	strCode = c_pStockCode;
	if (m_mapStocks.find(strCode) != m_mapStocks.end())
		return m_mapStocks[strCode];

	std::vector<SStock *>::iterator iter;
	for(iter = m_vpStocks.begin(); iter != m_vpStocks.end(); iter++)	
	{
		//if (strlen((*iter)->m_acKind) > 0 && strcmp((*iter)->m_acName,c_pStockCode) == 0)
		if (strlen((*iter)->m_acKind) > 0 && ((*iter)->m_strName == c_pStockCode))
			return *iter;
	}
	return NULL;
}


void CData::SetNotifyHwnd(HWND c_hwnd)
{
	m_hwndMain = c_hwnd;
	m_hwndNotify = c_hwnd;
}

CString CData::GetTail(CString c_strText,CString c_strSperate)
{
	int iFind;
	iFind = c_strText.Find(c_strSperate);
	CString strLeft;
	strLeft = c_strText;
	while(iFind != -1)
	{
		strLeft = strLeft.Right(strLeft.GetLength() - iFind - 1);
		iFind = strLeft.Find(c_strSperate);
	}
	return strLeft;
}

unsigned short CData::NewSeq()
{
	m_lockSeq.lock();
	if (++m_usSeq > 0XFF)
		m_usSeq = 1;
	m_lockSeq.unlock();
	return m_usSeq;
}

bool CData::IsSameWeek(unsigned int uiNow, unsigned int uiPrev)
{//比较今日和所给定日期是否在同一周内
	tm	stPrevTime,stNowTime;
	memset(&stPrevTime,0,sizeof(tm));
	stPrevTime.tm_year=uiPrev/10000-1900;
	stPrevTime.tm_mon=uiPrev%10000/100-1;
	stPrevTime.tm_mday=uiPrev%100;
	time_t stPrev=mktime(&stPrevTime);

	memset(&stNowTime,0,sizeof(tm));
	stNowTime.tm_year=uiNow/10000-1900;
	stNowTime.tm_mon=uiNow%10000/100-1;
	stNowTime.tm_mday=uiNow%100;
	time_t stNow=mktime(&stNowTime);

	if(stNow>stPrev && difftime(stNow,stPrev)>=7*24*3600)
		return	false;
	else if(stPrev>stNow && difftime(stPrev,stNow)>=7*24*3600)
		return	false;
	if(stNowTime.tm_wday<stPrevTime.tm_wday && stNow>stPrev)
		return	false;
	else if(stNowTime.tm_wday>stPrevTime.tm_wday && stNow<stPrev)
		return	false;
	return	true;
}


bool CData::IsSameMonth(unsigned int uiNow, unsigned int uiPrev)
{//比较今日和所给定日期是否在同一月内
	unsigned char ucNowMonth=uiNow%10000/100;
	unsigned char ucPrevMonth=uiPrev%10000/100;
	if(uiNow/10000 != uiPrev/10000)
		return false;
	if(ucNowMonth!=ucPrevMonth)
		return false;
	return	true;
}

CString CData::NumToStr(int c_nNum)
{
	CString strRet;
	if (c_nNum < 0)
		return _T("");
	else
		if (c_nNum < 100000)
		{
			strRet.Format(_T("%d"),c_nNum);
			return strRet;
		}
		else
			if (c_nNum < 10000 * 100)
			{
				strRet.Format(_T("%.1f万"),float(c_nNum)/(10000));
				return strRet;
			}
			else
				if (c_nNum < 10000 * 10000)
				{
					strRet.Format(_T("%.1f百万"),float(c_nNum)/(10000*100));
					return strRet;
				}
				else
				{
					strRet.Format(_T("%.1f亿"),float(c_nNum)/(10000*10000));
					return strRet;
				}
				return strRet;
}

int CData::GetFileData(char * c_acFileName,char * c_pBuf,int c_nMaxLen)
{
	char acFile[MAX_PATH];
	sprintf(acFile,"%s\\%s",m_acDataPath,c_acFileName);
	FILE * f;
	f = fopen(acFile,"rb");
	if (f)
	{
		int nRet = fread(c_pBuf,1,c_nMaxLen,f);
		fclose(f);
		return nRet;
	}
	return 0;
}


SStock * CData::GetNextStock(SStock * c_pStock,int c_nWay)
{
	std::map<CString,SStock *>::iterator iter;
	iter = m_mapStocks.find(toUnicodeString(c_pStock->m_sQuote.szStockCode,strlen(c_pStock->m_sQuote.szStockCode)));
	if (iter == m_mapStocks.end())
		return NULL;
	while(true)
	{
		if (c_nWay == 1)
			iter++;
		if (c_nWay == -1)
			iter--;
		if (iter == m_mapStocks.end())
			return NULL;
		if (IsStock(iter->second))
			break;
	}
	if (iter == m_mapStocks.end())
		return NULL;

	return iter->second;
}

bool CData::IsStock(CString c_strCode)
{
	return true;

}

bool CData::IsStock(char * c_pCode)
{
	return true;
}

bool CData::IsStock(SStock * c_pStock)
{	
	return true;
}

CString CData::GetStockValueByName(SStock * c_pStock,CString c_strName)
{
	CString strRet;
	if (c_strName == STR_DM)
	{
		strRet.Format(_T("%.6s"),toUnicodeString(c_pStock->m_sQuote.szStockCode,strlen(c_pStock->m_sQuote.szStockCode)));
	}
	else
	if (c_strName == STR_JC)
	{
		strRet = c_pStock->m_strName;
	}
	else
	if (c_strName == STR_XJ)
	{
		if (c_pStock->m_sQuote.zjjg == 0)
			strRet = "-";
		else
			strRet.Format(_T("%.2f"),float(c_pStock->m_sQuote.zjjg) / 1000);
	}
	if (c_strName == STR_JRKP)
	{
		if (c_pStock->m_sQuote.jrkp == 0)
			strRet = "-";
		else
			strRet.Format(_T("%.2f"),float(c_pStock->m_sQuote.jrkp) / 1000);
	}
	else
	if (c_strName == STR_ZRSP)
	{
		strRet.Format(_T("%.2f"),float(c_pStock->m_sQuote.zrsp) / 1000);
	}
	else
	if (c_strName == STR_ZGJG)
	{
		if (c_pStock->m_sQuote.zgjg == 0)
			strRet = "-";
		else
			strRet.Format(_T("%.2f"),float(c_pStock->m_sQuote.zgjg) / 1000);
	}
	else
	if (c_strName == STR_ZDJG)
	{
		if (c_pStock->m_sQuote.zdjg == 0)
			strRet = "-";
		else
			strRet.Format(_T("%.2f"),float(c_pStock->m_sQuote.zdjg) / 1000);
	}
	else
	if (c_strName == STR_ZRSP)
	{
		strRet.Format(_T("%.2f"),float(c_pStock->m_sQuote.zdjg) / 1000);
	}
	else
	if (c_strName == STR_ZDF)
	{
		strRet.Format(_T("%.2f"),float(c_pStock->m_sQuote.zdfd) / 100);
	}
	else
	if (c_strName == STR_ZF)
	{
		if (c_pStock->m_sQuote.zrsp > 0 && c_pStock->m_sQuote.zgjg > 0 && c_pStock->m_sQuote.zdjg > 0)
			strRet.Format(_T("%.2f"),float(c_pStock->m_sQuote.zgjg-c_pStock->m_sQuote.zdjg) / c_pStock->m_sQuote.zrsp * 100);
	}
	else
	if (c_strName == STR_ZD)
	{
		strRet.Format(_T("%.2f"),float(c_pStock->m_sQuote.zd) / 1000);
	}
	else
	if (c_strName == STR_BUY)
	{
		if (c_pStock->m_sQuote.BP1 == 0)
			strRet = "-";
		else
			strRet.Format(_T("%.2f"),float(c_pStock->m_sQuote.BP1) / 1000);
	}
	else
	if (c_strName == STR_SELL)
	{
		if (c_pStock->m_sQuote.SP1 == 0)
			strRet = "-";
		else
			strRet.Format(_T("%.2f"),float(c_pStock->m_sQuote.SP1) / 1000);
	}
	else
	if (c_strName == STR_CJL)
	{
		strRet.Format(_T("%d"),c_pStock->m_sQuote.cjsl);
	}
	else
	if (c_strName == STR_LB)
	{
		strRet.Format(_T("%.2f"),float(c_pStock->m_sQuote.lb)/10000);
	}
	else
	if (c_strName == STR_CJJE)
	{
		strRet.Format(_T("%d"),int(c_pStock->m_sQuote.cjje));
	}
	else
	if (c_strName == STR_HSL)
	{
		if (c_pStock->m_dLtg > 0)
			strRet.Format(_T("%.2f"),float(c_pStock->m_sQuote.cjsl) * 100 * 100 / c_pStock->m_dLtg);
	}
	else
	if (c_strName == STR_QHSL)
	{
		strRet.Format(_T("%.2f"),float(c_pStock->m_sQuote.hsl) / 100);
	}
	else
	if (c_strName == STR_ZSZ)
	{
		strRet.Format(_T("%.3f亿"),float(c_pStock->m_dValue / 100000000));
	}
	return strRet;
}

void CData::InitQuickKey()
{
	SQuickKey * pKey;

	pKey = new SQuickKey();
	memset(pKey,0,sizeof(SQuickKey));
	strcpy(pKey->m_acKey,"KDJ");
	strcpy(pKey->m_acKeyDesc,"KDJ");
	m_vpQuickKey.push_back(pKey);

	pKey = new SQuickKey();
	memset(pKey,0,sizeof(SQuickKey));
	strcpy(pKey->m_acKey,"MACD");
	strcpy(pKey->m_acKeyDesc,"MACD");
	m_vpQuickKey.push_back(pKey);
	pKey = new SQuickKey();
	memset(pKey,0,sizeof(SQuickKey));
	strcpy(pKey->m_acKey,"BOLL");
	strcpy(pKey->m_acKeyDesc,"BOLL");
	m_vpQuickKey.push_back(pKey);
	pKey = new SQuickKey();
	memset(pKey,0,sizeof(SQuickKey));
	strcpy(pKey->m_acKey,"RSI");
	strcpy(pKey->m_acKeyDesc,"RSI");
	m_vpQuickKey.push_back(pKey);
	pKey = new SQuickKey();
	memset(pKey,0,sizeof(SQuickKey));
	strcpy(pKey->m_acKey,"EMA");
	strcpy(pKey->m_acKeyDesc,"EMA");
	m_vpQuickKey.push_back(pKey);
	pKey = new SQuickKey();
	memset(pKey,0,sizeof(SQuickKey));
	strcpy(pKey->m_acKey,"MA");
	strcpy(pKey->m_acKeyDesc,"MA");
	m_vpQuickKey.push_back(pKey);

	pKey = new SQuickKey();
	memset(pKey,0,sizeof(SQuickKey));
	strcpy(pKey->m_acKey,"VOLUME");
	strcpy(pKey->m_acKeyDesc,"成交量");
	m_vpQuickKey.push_back(pKey);
}

int CData::FormatStockMinKData(unsigned short c_usCycle,SStock * c_pStock,KLINE *c_pK,int c_nCount)
{
	if (c_pStock->m_nMinItemCount == 0)
		return 0;	

	int nUnitTime = 1;
	if (c_usCycle == HISKMINDATA)
		nUnitTime = 1;
	else
		if (c_usCycle == HISKMIN5DATA)
			nUnitTime = 5;
		else
			if (c_usCycle == HISKMIN15DATA)
				nUnitTime = 15;
			else
				if (c_usCycle == HISKMIN30DATA)
					nUnitTime = 30;
				else
					if (c_usCycle == HISKMIN60DATA)
						nUnitTime = 60;

	int nKCount = 0;
	MinUnit * pMinUnit = (MinUnit *)c_pStock->m_pMinData;	
	KLINE * pKUnit = c_pK;	

	int nTime = 570;
	if (nUnitTime == 1)
	{
		for(int n=0; n<c_pStock->m_nMinItemCount; n++)
		{
			pKUnit[n].day = pMinUnit[n].Time + gpData->m_nWorkDay % 1000000 * 10000;
			pKUnit[n].open = pMinUnit[n].OpenPrice;
			pKUnit[n].close = pMinUnit[n].NewPrice;
			pKUnit[n].high = pMinUnit[n].MaxPrice;
			pKUnit[n].low = pMinUnit[n].MinPrice;
			pKUnit[n].volume = pMinUnit[n].Volume;
			pKUnit[n].amount = pMinUnit[n].Volume * pMinUnit[n].AvgPrice;
			if (pKUnit[n].open == 0)
				pKUnit[n].open = pKUnit[n].close;			
			if (pKUnit[n].high == 0)
				pKUnit[n].high = pKUnit[n].close;
			if (pKUnit[n].low == 0)
				pKUnit[n].low = pKUnit[n].close;

		}
		return c_pStock->m_nMinItemCount;
	}
	else
	{
		pKUnit[nKCount].day = pMinUnit[0].Time + gpData->m_nWorkDay % 1000000 * 10000;
		pKUnit[nKCount].open = pMinUnit[0].OpenPrice;
		pKUnit[nKCount].close = pMinUnit[0].NewPrice;
		pKUnit[nKCount].high = pMinUnit[0].MaxPrice;
		pKUnit[nKCount].low = pMinUnit[0].MinPrice;
		pKUnit[nKCount].volume = pMinUnit[0].Volume;
		pKUnit[nKCount].amount = pMinUnit[0].Volume * pMinUnit[0].AvgPrice;

		for(int n=1; n<c_pStock->m_nMinItemCount; n++)
		{	
			nTime = n;
			if (nTime > 120)
				nTime--;
			//if (pMinUnit[n].Time % nUnitTime == 1 && pMinUnit[n].Time != 570 && pMinUnit[n].Time != 571)
			if (nTime % nUnitTime == 1 && nTime != 1)
			{
				nKCount++;
				pKUnit[nKCount].day = pMinUnit[n].Time + gpData->m_nWorkDay % 1000000 * 10000;
				pKUnit[nKCount].open = pMinUnit[n].OpenPrice;
				pKUnit[nKCount].close = pMinUnit[n].NewPrice;
				pKUnit[nKCount].high = pMinUnit[n].MaxPrice;
				pKUnit[nKCount].low = pMinUnit[n].MinPrice;
				pKUnit[nKCount].volume = pMinUnit[n].Volume;
				pKUnit[nKCount].amount = pMinUnit[n].Volume * pMinUnit[n].AvgPrice;
			}
			else
			{
				pKUnit[nKCount].day = pMinUnit[n].Time + gpData->m_nWorkDay % 1000000 * 10000;
				pKUnit[nKCount].close = pMinUnit[n].NewPrice;
				if (pMinUnit[n].MaxPrice > pKUnit[nKCount].high)
					pKUnit[nKCount].high = pMinUnit[n].MaxPrice;
				if (pMinUnit[n].MinPrice < pKUnit[nKCount].low)
					pKUnit[nKCount].low = pMinUnit[n].MinPrice;
				pKUnit[nKCount].volume += pMinUnit[n].Volume;
				pKUnit[nKCount].amount += pMinUnit[n].Volume * pMinUnit[n].AvgPrice;
			}
		}
		return nKCount + 1;
	}
}

int CData::WriteToFile(char * c_pFileName,char * c_pData,int c_nLen)
{
	FILE * f;
	char acFile[MAX_PATH];
	sprintf(acFile,"%s\\%s",m_acDataPath,c_pFileName);
	f = fopen(acFile,"wb");
	if (f)
	{
		fwrite(c_pData,1,c_nLen,f);
		fclose(f);
		return c_nLen;
	}
	return -1;
}

int CData::GetFromFile(char * c_pFileName,char * c_pData,int c_nMaxLen)
{
	FILE * f;
	char acFile[MAX_PATH];
	sprintf(acFile,"%s\\%s",m_acDataPath,c_pFileName);
	f = fopen(acFile,"rb");
	if (f)
	{
		int nRead = fread(c_pData,1,c_nMaxLen,f);
		fclose(f);
		return nRead;
	}
	return -1;
}

int CData::GetFromFileTail(char * c_pFileName,char * c_pData,int c_nLen)
{
	FILE * f;
	char acFile[MAX_PATH];
	sprintf(acFile,"%s\\%s",m_acDataPath,c_pFileName);
	f = fopen(acFile,"rb");
	if (f)
	{				
		fseek(f,0,SEEK_END);
		int nPos = ftell(f);
		if (c_nLen < nPos)
			fseek(f,c_nLen * -1,SEEK_CUR);
		else
			fseek(f,0,SEEK_SET);
		int nRead = fread(c_pData,1,c_nLen,f);
		fclose(f);
		return nRead;
	}
	return -1;
}

void CData::AddUserDefReportItem(HWND c_hwnd,int * c_pnStockId,int c_nCount)
{
	int nCount = c_nCount;
	if (nCount > 64)
		nCount = 64;
	if (c_nCount <= 0)
	{
		RemoveUserDefReportItem(c_hwnd);
		return;
	}
	std::vector<SUserDefReportItem *>::iterator iter;
	for(iter=m_vpUserDefReportItems.begin(); iter!=m_vpUserDefReportItems.end(); iter++)
	{
		if ((*iter)->hwndFrom == c_hwnd)
		{			
			for(int k=0; k<nCount; k++)
			{
				(*iter)->nStockId[k] = c_pnStockId[k];
			}
			(*iter)->nCount = nCount;
			::PostMessage(m_hwndNotify,WM_UPDATE_QUOTEDATA,USERDEFREPORTDATA,200);//立即更新数据
			return;
		}
	}
	for(iter=m_vpUserDefReportItems.begin(); iter!=m_vpUserDefReportItems.end(); iter++)
	{
		if ((*iter)->hwndFrom == 0)
		{
			(*iter)->hwndFrom = c_hwnd;
			for(int k=0; k<nCount; k++)
				(*iter)->nStockId[k] = c_pnStockId[k];
			(*iter)->nCount = nCount;
			::PostMessage(m_hwndNotify,WM_UPDATE_QUOTEDATA,USERDEFREPORTDATA,200);//立即更新数据
			return;
		}
	}
	//::PostMessage(m_hwndNotify,WM_UPDATE_QUOTEDATA,USERDEFREPORTDATA,200);//立即更新数据
	//SUserDefReportItem * pItem = (SUserDefReportItem *)malloc(sizeof(SUserDefReportItem));
	//pItem->hwndFrom = c_hwnd;
	//memcpy(pItem->acStocks,c_pStocks,nCount * STOCK_CODE_LEN);
	//pItem->nCount = nCount;
	//m_vpUserDefReportItems.push_back(pItem);
}

void CData::RemoveUserDefReportItem(HWND c_hwnd)
{
	std::vector<SUserDefReportItem *>::iterator iter;
	for(iter=m_vpUserDefReportItems.begin(); iter!=m_vpUserDefReportItems.end(); iter++)
	{
		if ((*iter)->hwndFrom == c_hwnd)
		{	
			(*iter)->hwndFrom = 0;
			//delete *iter;
			//m_vpUserDefReportItems.erase(iter);
			return;
		}
	}
}

void CData::CheckUserDefReportItems()
{
	std::vector<SUserDefReportItem *>::iterator iter;
	iter=m_vpUserDefReportItems.begin();
	while(iter!=m_vpUserDefReportItems.end())	
	{
		//if (CWnd::FromHandle((*iter)->hwndFrom))
		if (IsWindow((*iter)->hwndFrom))
			iter++;
		else
		{	
			(*iter)->hwndFrom = 0;
			iter++;
			//free(*iter);
			//iter = m_vpUserDefReportItems.erase(iter);
		}
	}
}

//返回有效个数
int CData::GetUserDefReportItems(char * c_pBuf,int & c_nLen,int c_nMaxLen)
{
	int nCount = 0;
	std::vector<SUserDefReportItem *>::iterator iter;
	for(iter=m_vpUserDefReportItems.begin(); iter!=m_vpUserDefReportItems.end(); iter++)
	{
		if ((*iter)->hwndFrom == 0)
			continue;
		if (!IsWindow((*iter)->hwndFrom))
			continue;
		if (!CWnd::FromHandle((*iter)->hwndFrom)->IsWindowVisible())
			continue;
		for(int k=0; k<(*iter)->nCount; k++)
		{			
			bool bExists = false;
			for(int j=0; j<nCount; j++)
			{
				if (*(int *)(c_pBuf + j * sizeof(int)) == (*iter)->nStockId[k])
				{
					bExists = true;
					break;
				}
			}
			if (bExists == false)
			{
				*(int *)(c_pBuf + nCount * sizeof(int)) = (*iter)->nStockId[k];
				nCount++;
				if (nCount * (sizeof(int) + 1) > c_nMaxLen)
					break;
			}
			if (nCount * (sizeof(int) + 1) > c_nMaxLen)
				break;
		}
	}
	c_nLen = nCount * sizeof(int);
	return nCount;
}

void CData::OnOpenDay(int)
{
	std::vector<SStock *>::iterator iter;
	for(iter = m_vpStocks.begin(); iter != m_vpStocks.end(); iter++)	
	{
		(*iter)->m_nLastMinTime = 0;
	}
}
