#include "StdAfx.h"
#include ".\hhtyxml.h"

CHHTyXml::CHHTyXml(void)
{
	m_lBuffCount = 10*1024*1024;//10M
	m_pBuff = new unsigned char[m_lBuffCount];
}

CHHTyXml::~CHHTyXml(void)
{
	if (m_pBuff)
	{
		delete []m_pBuff;
		m_lBuffCount = 0;
	}
	ReleaseXMLFILESList(&m_list);
}

int CHHTyXml::HHGetFileInfo(const TiXmlElement *pNode, char *pName,const  char *pLen,const  char *pDate,const  char *pTime, const char *pFileVer, const char *pCrc)
{
	if (!pNode->NoChildren())
	{
		const TiXmlElement* child;
		int i = 0;
		for (child = (const TiXmlElement*)pNode->FirstChild();child;child = (const TiXmlElement*)child->NextSibling())
		{
			const char * s = child->Value();
			if (child->Type() == TiXmlNode::TINYXML_ELEMENT)
			{
				char* MesType="Name";

				const char* asciiname= child->Value();
				const char* asciivalue= child->Attribute(_T("Name"));
				const char* asciivalue1= child->Attribute(_T("Len"));
				const char* asciivalue2= child->Attribute(_T("Date"));
				const char* asciivalue3= child->Attribute(_T("Time"));
				const char* asciivalue4= child->Attribute(_T("Version"));
				const char* asciivalue5= child->Attribute(_T("Crc"));

				strcat(pName,_T("\\"));
				strcat(pName,asciivalue);

				if (-1 == HHGetFileInfo(child,pName,asciivalue1,asciivalue2,asciivalue3,asciivalue4,asciivalue5))//没有儿子了
				{
					int e=0;
					char c = '\\';
					char *ptr = NULL;
					ptr = strrchr(pName,c);
					if (ptr)
					{
						memset(&pName[ptr-pName],0,strlen(ptr));
					}
				}

				if (child == pNode->LastChild())//是否父亲的最后一个儿子
				{
					//自杀  再告诉父亲没有儿子了
					int e=0;
					char c = '\\';
					char *ptr = NULL;
					ptr = strrchr(pName,c);
					if (ptr)
					{
						memset(&pName[ptr-pName],0,strlen(ptr));
					}
				}
			}
		}
		return 0;
	}
	else
	{
		const char* asciiname= pNode->Value();
		if (strcmpi(asciiname,"folder"))//不添加文件夹
		{
			PAttribute pNmae1 = new _tagAttribute();
			memset(pNmae1,0,sizeof _tagAttribute);
			if (pName)
			{
				strcpy(pNmae1->szFileName,pName);
			}
			if (pLen)
			{
				strcpy(pNmae1->szLen,pLen);
			}
			if (pDate)
			{
				strcpy(pNmae1->szDate,pDate);
			}
			if (pTime)
			{
				strcpy(pNmae1->szTime,pTime);
			}
			if (pFileVer)
			{
				strcpy(pNmae1->szFileVer,pFileVer);
			}
			if (pCrc)
			{
				strcpy(pNmae1->szCrc,pCrc);
			}

			m_list.AddTail(pNmae1);
		}
		else
		{
			//mkdir();
		}
		
		return -1;//没有儿子了
	}
}

int CHHTyXml::HHDecomposeXML(const char* pXmlPath,LSXMLFILES *pList)
{
	TiXmlDocument xmlDoc(pXmlPath);
	xmlDoc.LoadFile();
	if ( !xmlDoc.Parse(pXmlPath) )
	{
		cout << xmlDoc.ErrorDesc() << endl;
		return -1;
	}

	TiXmlElement *root = xmlDoc.RootElement();
	int i = 0;

	char szName[MAX_PATH]={0};
	char szLen[16]={0};
	char szDate[16]={0};
	char szTime[16]={0};
	char szFileVer[MAX_PATH]={0};
	char szCrc[16]={0};

	ReleaseXMLFILESList(&m_list);
	HHGetFileInfo(root,szName,szLen,szDate,szTime,szFileVer,szCrc);

	POSITION  pos = m_list.GetHeadPosition();
	while(NULL != pos)
	{
		PAttribute pAttribute = m_list.GetNext(pos);
		if (pAttribute)
		{
			pList->AddTail(pAttribute);
		}
	}

	return 0;
}
void CHHTyXml::ReleaseXMLFILESList(LSXMLFILES *pList)
{
	if(pList == NULL)
		return;

	PAttribute  pStruct = NULL;
	POSITION pos;
	int i;
	i = 0;

	for (; i<pList->GetCount(); i++)
	{
		if (NULL==(pos=pList->FindIndex(i)))
		{
			continue;
		}
		pStruct = pList->GetAt(pos);
		if (pStruct!=NULL)
		{
			delete pStruct;
			pStruct = NULL;
		}
	}

	pList->RemoveAll();
}

int CHHTyXml::HHComposeXML(const LPCTSTR pFolderPath)
{
	int nErr = 0;

	TiXmlDeclaration * xmlDec = new TiXmlDeclaration("1.0", "GB2312", "yes");
	if (NULL != xmlDec)
	{
		TiXmlDocument * xmlDocs = new TiXmlDocument();
		xmlDocs->LinkEndChild(xmlDec);

		TiXmlElement * element = new TiXmlElement("HHNSD");
		xmlDocs->LinkEndChild(element);

		HHScan(pFolderPath,element);
		if (m_pBuff)
		{
			delete []m_pBuff;
			m_pBuff = NULL;
			m_lBuffCount = 0;
		}
		char outputFileName[128] = {0};
		strcpy(outputFileName,pFolderPath);
		char c = '\\';
		char *ptr = strchr(outputFileName,c);
		memset(&outputFileName[ptr - outputFileName+1],0,128-(ptr - outputFileName +1));
		strcat(outputFileName,"update.xml");
		xmlDocs->SaveFile(outputFileName);

		delete xmlDocs;
	}
	else
	{
		nErr = 4;
	}

	return nErr;
}

int CHHTyXml::HHScan(const LPCTSTR pFolderPath,TiXmlElement *Elem)
{
	int nErr=0;
	HANDLE hFind;
	WIN32_FIND_DATA wfData;
	char szFullPath[MAX_PATH];memset(szFullPath,0,MAX_PATH);
	char szSubdir[MAX_PATH];memset(szSubdir,0,MAX_PATH);

	strcpy(szFullPath,pFolderPath);
	char c = '\\';
	if (strrchr(szFullPath,c)-szFullPath != strlen(szFullPath)-1)
	{
		szFullPath[strlen(szFullPath)] = '\\';
	}
	strcat(szFullPath,"*.*");

	hFind = FindFirstFile(szFullPath,&wfData);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		nErr = -1;//没有
		return nErr;
	}

	do
	{
		switch(wfData.dwFileAttributes)
		{
		case FILE_ATTRIBUTE_DIRECTORY://目录
			{
				if(strcmp(wfData.cFileName,".") && strcmp(wfData.cFileName,".."))//排除当前目录和上级目录
				{
					char szPath[MAX_PATH] = {0};
					strcpy(szPath,szFullPath);
					memset(&szPath[strlen(szPath)-3],0,3);
					sprintf(szSubdir,"%s%s\\",szPath,wfData.cFileName);
					TiXmlElement*  prodElem = new TiXmlElement("Folder");
					prodElem->SetAttribute("Name", wfData.cFileName);
					Elem->LinkEndChild(prodElem);
					HHScan(szSubdir,prodElem);//递归调用，遍历
				}
			}
			break;
		default://文件
			{
				if (strcmpi(&wfData.cFileName[strlen(wfData.cFileName)-3],".hh") && strcmpi(wfData.cFileName,"Thumbs.db"))
				{
					long lLen=0,lDate=0,lTime=0;
					int nCrc = 0;
					char szPath[MAX_PATH] = {0};
					char szPath2[MAX_PATH] = {0};
					char szFileVer[MAX_PATH] = {0};
					strcpy(szPath,szFullPath);
					memset(&szPath[strlen(szPath)-3],0,3);
					sprintf(szPath2,"%s%s",szPath,wfData.cFileName);
					GetLocalFileStatus(szPath2,lLen,lDate,lTime,szFileVer,nCrc);
					TiXmlElement*  prodElem = new TiXmlElement("file");
					Elem->LinkEndChild(prodElem);
					prodElem->SetAttribute("Name", wfData.cFileName);
					prodElem->SetAttribute("Len", lLen);
					prodElem->SetAttribute("Date",lDate);
					prodElem->SetAttribute("Time",lTime);
					prodElem->SetAttribute("Crc",nCrc);
					if (!strcmpi((char *)&wfData.cFileName[strlen(wfData.cFileName)-4],".dll") || !strcmpi((char *)&wfData.cFileName[strlen(wfData.cFileName)-4],".exe"))
					{
						prodElem->SetAttribute("Version",szFileVer);
					}
					
				}				
			}

			break;
		}
	}while(FindNextFile(hFind,&wfData));
}

BOOL CHHTyXml::GetLocalFileStatus(char *pFilename, long &lLen, long &lDate, long &lTime,char *pFileVer, int &nCrc)
{
	CTime tFile=CTime::GetCurrentTime();
	lLen=lDate=lTime=0;
	CFileFind  fileFind;
	BOOL	bResult=fileFind.FindFile(pFilename);
	if(bResult)
	{
		fileFind.FindNextFile();
		lLen=fileFind.GetLength();
		fileFind.GetLastWriteTime(tFile);
		lDate=tFile.GetYear()*10000+tFile.GetMonth()*100+tFile.GetDay();
		lTime=tFile.GetHour()*10000+tFile.GetMinute()*100+tFile.GetSecond();
		if (!strcmpi((char *)&pFilename[strlen(pFilename)-4],".dll") || !strcmpi((char *)&pFilename[strlen(pFilename)-4],".exe"))
		{
			GetFileVer(pFilename,pFileVer);
		}

		if (NULL == m_pBuff)
		{
			m_lBuffCount = 10*1024*1024;
			m_pBuff = new unsigned char[m_lBuffCount];
			ZeroMemory(m_pBuff,m_lBuffCount);
		}
		if (lLen>m_lBuffCount)
		{
			
			if (NULL != m_pBuff)
			{
				delete []m_pBuff;
				m_pBuff = NULL;
				m_lBuffCount = 0;
				m_pBuff = new unsigned char[lLen];
				m_lBuffCount = lLen;
				ZeroMemory(m_pBuff,m_lBuffCount);
			}
		}
		
		CFile fs(pFilename,CFile::modeRead|CFile::typeBinary|CFile::shareDenyNone); 
		fs.Seek(0,CFile::begin);
		fs.Read(m_pBuff,lLen);
		nCrc = CalCRC(m_pBuff,lLen);
		fs.Close();
	}
	fileFind.Close();
	return bResult;
}

#pragma comment(lib,"Version.lib")
int CHHTyXml::GetFileVer(const LPCTSTR pFolderPath, LPCTSTR pFileVer)
{
	char cPath[MAX_PATH];
	DWORD dwHandle,InfoSize;
	CString strVersion;
	strcpy(cPath,pFolderPath);
	InfoSize = GetFileVersionInfoSize(cPath,&dwHandle); //将版本信息资源读入缓冲区
	if(InfoSize==0) 
	{
		//获取版本信息出错
		return -1;
	}
	char *InfoBuf = new char[InfoSize];ZeroMemory(InfoBuf,InfoSize);
	GetFileVersionInfo(cPath,0,InfoSize,InfoBuf); //获得生成文件使用的代码页及文件版本
	unsigned int  cbTranslate = 0;
	struct LANGANDCODEPAGE 
	{
		WORD wLanguage;
		WORD wCodePage;
	} *lpTranslate;
	try
	{
		VerQueryValue(InfoBuf, TEXT("\\VarFileInfo\\Translation"),(LPVOID*)&lpTranslate,&cbTranslate);
	}
	catch(...)
	{
		if (InfoBuf)
		{
			delete []InfoBuf;
			InfoBuf = NULL;
		}
	}
	
	for( int i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
	{
		char  SubBlock[200];
		wsprintf( SubBlock,
			TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
			lpTranslate[i].wLanguage,
			lpTranslate[i].wCodePage);
		void *lpBuffer=NULL;
		unsigned int dwBytes=0;
		VerQueryValue(InfoBuf,
			SubBlock,
			&lpBuffer,
			&dwBytes);
		CString strTemp=(char *)lpBuffer;
		strVersion+=strTemp;
	}

	if (InfoBuf)
	{
		delete []InfoBuf;
		InfoBuf = NULL;
	}
	
	
	strcpy((char *)pFileVer,strVersion.GetBuffer());
	strVersion.ReleaseBuffer();
	return 0;
}

//CRC校验
int CHHTyXml::CalCRC(void *pData, int nDataLen)
{
	int acc = 0;
	int i;
	unsigned char* Data = (unsigned char*) pData;

	while(nDataLen--)
	{
		acc = acc ^ (*Data++ << 8);
		for(i = 0; i++ < 8; )
			if(acc & 0x8000)
				acc = (acc << 1) ^ 0x1021;
			else
				acc <<= 1;
	}

	// Swap High and Low byte
	i = ( (int) ( ((unsigned char)acc) << 8) ) | ((int)(acc >> 8));

	return i;
}
