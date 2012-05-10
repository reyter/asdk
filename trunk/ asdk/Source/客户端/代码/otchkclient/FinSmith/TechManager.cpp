#include "StdAfx.h"
#include "PicWnd.h"
#include "TechManager.h"

CTechManager::CTechManager(void)
{
	m_instance = NULL;
}

CTechManager::~CTechManager(void)
{
}

CTechManager * CTechManager::getInstance()
{
	if (m_instance == NULL)
		m_instance = new CTechManager();
	return m_instance;
}

void  CTechManager::freeInstance()
{
	if (m_instance)
		delete m_instance;
	m_instance = NULL;
}

// 初始化
int CTechManager::Init(void)
{
	return 0;
}

// 取技术指标
int CTechManager::getTech(STECH * c_pTech)
{
	USES_CONVERSION;
	CString strSection;
	CString strKey;
	strSection.Format(_T("%s_%d"),c_pTech->m_strName,c_pTech->m_usCycle);
	
	int nDefault = GetPrivateProfileInt(strSection,_T("default"),1,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));	
	c_pTech->m_nParamCount = GetPrivateProfileInt(strSection,_T("count"),0,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
	c_pTech->m_bCanAdd = false;
	if (c_pTech->m_strName == PIC_EMA || c_pTech->m_strName == PIC_MA || c_pTech->m_strName == PIC_MMA || c_pTech->m_strName == PIC_HISK_VOL)
	{
		c_pTech->m_bCanAdd = true;
	}
	if (nDefault == 0 && c_pTech->m_nParamCount > 0)
	{
		c_pTech->m_bDefault = false;
		for(int n=0; n<c_pTech->m_nParamCount; n++)
		{
			strKey.Format(_T("param%d"),n);
			WCHAR wc[64];
			GetPrivateProfileString(strSection,strKey,_T("5"),wc,15,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
			strcpy(c_pTech->m_acParams[n],W2A(wc));
			strKey.Format(_T("desc%d"),n);
			GetPrivateProfileString(strSection,strKey,_T(""),wc,63,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
			strcpy(c_pTech->m_acDescs[n],W2A(wc));
		}
		return 0;			
	}
	c_pTech->m_bDefault = true;
	if (c_pTech->m_strName == PIC_MA)
	{
		c_pTech->m_bCanAdd = true;
		c_pTech->m_nParamCount = 2;
		strcpy(c_pTech->m_acParams[0],"5");
		strcpy(c_pTech->m_acParams[1],"10");
		sprintf(c_pTech->m_acDescs[0],"日平均");
		sprintf(c_pTech->m_acDescs[1],"日平均");
	}
	else
	if (c_pTech->m_strName == PIC_HISK_VOL)
	{
		c_pTech->m_bCanAdd = true;
		c_pTech->m_nParamCount = 1;
		strcpy(c_pTech->m_acParams[0],"12");		
		sprintf(c_pTech->m_acDescs[0],"日平均");
	}
	else
	if (c_pTech->m_strName == PIC_BOLL)
	{
		c_pTech->m_nParamCount = 3;
		strcpy(c_pTech->m_acParams[0],"56");		
		sprintf(c_pTech->m_acDescs[0],"日平均线");
		strcpy(c_pTech->m_acParams[1],"26");		
		sprintf(c_pTech->m_acDescs[1],"日布林线");
		strcpy(c_pTech->m_acParams[2],"55");		
		sprintf(c_pTech->m_acDescs[2],"日布林线");
	}
	else
	if (c_pTech->m_strName == PIC_EMA)
	{
		c_pTech->m_bCanAdd = true;
		c_pTech->m_nParamCount = 2;
		strcpy(c_pTech->m_acParams[0],"12");
		strcpy(c_pTech->m_acParams[1],"60");
		sprintf(c_pTech->m_acDescs[0],"日移动平均");
		sprintf(c_pTech->m_acDescs[1],"日移动平均");
	}
	else
	if (c_pTech->m_strName == PIC_RSI)
	{
		c_pTech->m_nParamCount = 3;
		strcpy(c_pTech->m_acParams[0],"6");
		strcpy(c_pTech->m_acParams[1],"12");
		strcpy(c_pTech->m_acParams[2],"24");
		sprintf(c_pTech->m_acDescs[0],"日 RSI");
		sprintf(c_pTech->m_acDescs[1],"日 RSI");
		sprintf(c_pTech->m_acDescs[2],"日 RSI");
	}
	else
	if (c_pTech->m_strName == PIC_KDJ)
	{
		c_pTech->m_nParamCount = 3;
		strcpy(c_pTech->m_acParams[0],"9");
		strcpy(c_pTech->m_acParams[1],"3");
		strcpy(c_pTech->m_acParams[2],"3");
		sprintf(c_pTech->m_acDescs[0],"天");
		sprintf(c_pTech->m_acDescs[1],"天");
		sprintf(c_pTech->m_acDescs[2],"天");
	}
	else
	if (c_pTech->m_strName == PIC_MACD)
	{
		c_pTech->m_nParamCount = 3;
		strcpy(c_pTech->m_acParams[0],"12");
		strcpy(c_pTech->m_acParams[1],"26");
		strcpy(c_pTech->m_acParams[2],"9");
		sprintf(c_pTech->m_acDescs[0],"日快线移动平均");
		sprintf(c_pTech->m_acDescs[1],"日慢线移动平均");
		sprintf(c_pTech->m_acDescs[2],"日移动平均");
	}
	return 0;
}

// 设置技术指标
int CTechManager::setTech(STECH * c_pTech)
{
	CString strSection;
	CString strKey;
	strSection.Format(_T("%s_%d"),c_pTech->m_strName,c_pTech->m_usCycle);
	
	if (c_pTech->m_bDefault)
	{
		WritePrivateProfileString(strSection,_T("default"),_T("1"),toUnicodeString(gpData->m_acIniFile,(int)strlen(gpData->m_acIniFile)));
		return 0;
	}
	else
		WritePrivateProfileString(strSection,_T("default"),_T("0"),toUnicodeString(gpData->m_acIniFile,(int)strlen(gpData->m_acIniFile)));
	char acBuf[16];
	sprintf(acBuf,"%d",c_pTech->m_nParamCount);
	WritePrivateProfileString(strSection,_T("count"),toUnicodeString(acBuf,(int)strlen(acBuf)),toUnicodeString(gpData->m_acIniFile,(int)strlen(gpData->m_acIniFile)));
	
	for(int n=0; n<c_pTech->m_nParamCount; n++)
	{
		strKey.Format(_T("param%d"),n);
		WritePrivateProfileString(strSection,strKey,toUnicodeString(c_pTech->m_acParams[n],(int)strlen(c_pTech->m_acParams[n])),toUnicodeString(gpData->m_acIniFile,(int)strlen(gpData->m_acIniFile)));	
		strKey.Format(_T("desc%d"),n);
		WritePrivateProfileString(strSection,strKey,toUnicodeString(c_pTech->m_acDescs[n],(int)strlen(c_pTech->m_acDescs[n])),toUnicodeString(gpData->m_acIniFile,(int)strlen(gpData->m_acIniFile)));		
	}
	return 0;
}


CString CTechManager::getTechByIndex(int c_nIndex, bool c_bIsStock,unsigned short c_usCycle,CString c_strCode)
{
	CString strSection;
	if (c_bIsStock)
		strSection.Format(_T("STOCK_TECH_%d"),c_usCycle);
	else
		strSection.Format(_T("INDEX_TECH_%d"),c_usCycle);
	if (c_bIsStock == false && c_strCode != _T("000001.SH") && c_strCode != _T("399001.SZ"))
	{
		if (c_nIndex == 1)
			return PIC_HISK_VOL;
		if (c_nIndex == 2)
			return PIC_MACD;		
	}
	int nDefault = GetPrivateProfileInt(strSection,_T("default"),1,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
	if (nDefault == 1)
	{
		if (c_bIsStock)
		{
			if (c_nIndex == 0)
				return PIC_EMA;
			else
			if (c_nIndex == 1)
				return PIC_HISK_VOL;
			else
			if (c_nIndex == 2)
			{
					return PIC_MACD;
			}
			return _T("");
		}
		else
		{
			if (c_nIndex == 0)
				return PIC_EMA;
			else
			if (c_nIndex == 1)
				return PIC_HISK_VOL;
			else
			if (c_nIndex == 2)
			{
					return PIC_MACD;
			}
			return _T("");
		}
	}
	else
	{
		CString strKey;
		WCHAR wcRet[32];
		strKey.Format(_T("TECH_%d"),c_nIndex);
		GetPrivateProfileString(strSection,strKey,PIC_HISK_VOL,wcRet,32,toUnicodeString(gpData->m_acIniFile,strlen(gpData->m_acIniFile)));
		return wcRet;
	}
}

int CTechManager::getAix()
{
	return GetPrivateProfileInt(_T("CURRENTSET"),_T("AIX"),0,toUnicodeString(gpData->m_acIniFile,(int)strlen(gpData->m_acIniFile)));
}

void CTechManager::setAix(int c_n)
{
	CString strValue;
	strValue.Format(_T("%d"),c_n);
	WritePrivateProfileString(_T("CURRENTSET"),_T("AIX"),strValue,toUnicodeString(gpData->m_acIniFile,(int)strlen(gpData->m_acIniFile)));
}

int CTechManager::setTechByIndex(int c_nIndex, bool c_bIsStock, CString c_strTech,unsigned short c_usCycle)
{
	CString strSection;
	if (c_bIsStock)
		strSection.Format(_T("STOCK_TECH_%d"),c_usCycle);
	else
		strSection.Format(_T("INDEX_TECH_%d"),c_usCycle);
	CString strKey;	
	strKey.Format(_T("TECH_%d"),c_nIndex);
	WritePrivateProfileString(strSection,_T("default"),_T("0"),toUnicodeString(gpData->m_acIniFile,(int)strlen(gpData->m_acIniFile)));
	WritePrivateProfileString(strSection,strKey,c_strTech,toUnicodeString(gpData->m_acIniFile,(int)strlen(gpData->m_acIniFile)));	

	return 0;
}

bool CTechManager::isValid(CString c_strTech,bool c_bIsStock,unsigned short c_usCycle,CString c_strCode)
{
	return true;
}