#include "StdAfx.h"
#include ".\hhcompress.h"

#define LIMITSIZE 50*1024*1024

CHHCompress::CHHCompress(void)
{
	m_nFilePropertiesSize = sizeof _tagFileProperties;
	memset((char *)&m_fileproperties,0,sizeof _tagFileProperties);
}

CHHCompress::~CHHCompress(void)
{
}

int  CHHCompress::HHCompress (const LPCTSTR pFilename/*含路径、后缀名，的文件名*/,uLongf *pDestLen)
{
	int nErr;

	CFile isFile;
	if(!isFile.Open(pFilename, CFile::modeRead | CFile::typeBinary))
	{
		nErr = -1;
		return nErr;//没有给文件
	}

	uLong ulSourceLen = (uLong)isFile.GetLength(); //获取压缩文件长度
	*pDestLen = ulSourceLen*2;//为了防止压缩后数据变大
	if (ulSourceLen<=0)
	{
		nErr = -2;//该文件长度为0
		return nErr;
	}
	if (ulSourceLen >= (LIMITSIZE-m_nFilePropertiesSize))//后面m_nFilePropertiesSize个字节保留
	{
		nErr = -3;//数据源大于50M 不进行处理
		return nErr;
	}

	if (ulSourceLen<100)//压缩后长度有可能比现在的还要长
	{
		*pDestLen = 1000;
	}

	//读需压缩文件
	Bytef *pSource = new Bytef[ulSourceLen+m_nFilePropertiesSize]; memset(pSource,0,ulSourceLen+m_nFilePropertiesSize);
	Byte *pDest = new Byte[*pDestLen+m_nFilePropertiesSize]; memset(pDest,0,*pDestLen+m_nFilePropertiesSize);
	if (0==isFile.Read(pSource,ulSourceLen))
	{
		nErr = -2;	//该文件长度为0
		return nErr;
	}
	isFile.Close();

	//压缩
	const char *ptr = NULL,c = '\\';
	ptr = strrchr(pFilename,c);//在串中查找指定字符的最后一个出现  获取文件名
	nErr = compress(pDest, pDestLen, pSource, ulSourceLen);//压缩
	if (nErr != Z_OK)
	{
		delete []pSource;
		delete []pDest;
		return nErr;
	}

	//将文件相关信息附加到压缩文件中  待解压有用
	if (ptr)
	{
		strcpy(m_fileproperties.szFilename,&ptr[1]);
	}
	else
	{
		strcpy(m_fileproperties.szFilename,pFilename);	//没有路径  只是一个文件名
	}
	m_fileproperties.nFileLength = ulSourceLen;
	memcpy((char*)&pDest[*pDestLen],(char*)&m_fileproperties,m_nFilePropertiesSize);
	*pDestLen =*pDestLen + m_nFilePropertiesSize;//更新压缩后文件长度
	
	
	//更换后缀名
	char szFilename[FILENAME_MAX]={0};
	strcpy(szFilename,pFilename);
	strcat(szFilename,_T(".hh"));

	//写文件
	CFileException e;
	CFile os;
	if(!os.Open(szFilename,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary,&e)) //存文件
	{
#ifdef _DEBUG
		afxDump<<"File could not be opened"<<e.m_cause<<"\n";
#endif
	}
	else
	{
		os.Write(pDest,*pDestLen);
		os.Close();
	}
	
	

	delete []pSource;
	delete []pDest;

	return nErr;
}

int  CHHCompress::HHUncompress (const LPCTSTR pFilename,uLongf *pDestLen)
{
	int nErr;

	CFile isFile;
	if(!isFile.Open(pFilename, CFile::modeRead | CFile::typeBinary))
	{
		nErr = -1;
		return nErr;//没有给文件
	}

	uLong ulSourceLen = (uLong)isFile.GetLength(); 
	if (ulSourceLen<=0)
	{
		nErr = -2;//该文件长度为0
		return nErr;
	}
	if (ulSourceLen >= (LIMITSIZE-m_nFilePropertiesSize))//解压数据源不能大于50M
	{
		nErr = -3;
		return nErr;
	}

	//读取需解压文件
	Bytef *pSource = new Bytef[ulSourceLen];memset(pSource,0,ulSourceLen);
	if (!isFile.Read(pSource,ulSourceLen))
	{
		if (pSource)
		{
			delete []pSource;
		}
		
		nErr = -2;//该文件长度为0
		return nErr;
	}
	isFile.Close();

	//获取文件压缩前的相关信息  文件名和文件长度
	_tagFileProperties Fileproperties;
	memcpy(&Fileproperties,(_tagFileProperties *)&pSource[ulSourceLen-m_nFilePropertiesSize],m_nFilePropertiesSize) ;
	*pDestLen = Fileproperties.nFileLength;//获取压缩文件前文件大小
	memset(&pSource[ulSourceLen-m_nFilePropertiesSize],0,m_nFilePropertiesSize);//清空需解压数据 后面无需文件相关信息

	//解压
	Byte *pDest = new Byte[*pDestLen];memset(pDest,0,*pDestLen);
	nErr = uncompress(pDest, pDestLen, pSource, ulSourceLen-m_nFilePropertiesSize);
	if (nErr != Z_OK)
	{
		if (pSource)
		{
			delete []pSource;
		}
		if (pDest)
		{
			delete []pDest;
		}
		
		return nErr;
	}

	//还原文件名
	char *ptr = NULL,c = '\\';
	char szFilename[FILENAME_MAX]={0};
	strcpy(szFilename,pFilename);
	ptr = strrchr(szFilename,c);
	if (ptr)
	{
		memset((char*)&szFilename[ptr-szFilename+1],0,strlen(ptr)-1);//清空传入文件名
		strcpy((char*)&szFilename[ptr-szFilename+1],Fileproperties.szFilename);//根据原文件属性还原
	} 
	else
	{
		strcpy(szFilename,Fileproperties.szFilename);
	}

	//写文件
	try
	{
		CFile fs(szFilename,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); //存文件
		fs.Write(pDest,*pDestLen);
		fs.Close();
	}
	catch (CFileException* e)
	{
	}
	
	

	delete []pSource;
	delete []pDest;
	return nErr;
}

int  CHHCompress::HHUncompress2 (const LPCTSTR pDesFilename,const LPCTSTR pResFilename,uLongf *pDestLen,int nCrc)
{
	int nErr=0;

	CFile isFile;
	if(!isFile.Open(pResFilename, CFile::modeRead | CFile::typeBinary))
	{
		nErr = -1;
		CString strError;
		strError.Format("%s%s",pResFilename,"文件缺失!");
		WriteError(strError);
		return nErr;//没有该文件
	}

	uLong ulSourceLen = (uLong)isFile.GetLength(); 
	if (ulSourceLen<=0)
	{
		isFile.Close();
		CString strError;
		strError.Format("%s%s",pResFilename,"文件长度为0!");
		WriteError(strError);
		nErr = -2;//该文件长度为0
		return nErr;
	}
	if (ulSourceLen >= (LIMITSIZE-m_nFilePropertiesSize))//解压数据源不能大于50M
	{
		isFile.Close();
		CString strError;
		strError.Format("%s%s",pResFilename,"文件大于50M，不进行处理!");
		WriteError(strError);
		nErr = -3;
		return nErr;
	}

	//读取需解压文件
	Bytef *pSource = new Bytef[ulSourceLen];memset(pSource,0,ulSourceLen);
	if (!isFile.Read(pSource,ulSourceLen))
	{
		if (pSource)
		{
			delete []pSource;
		}

		isFile.Close();
		CString strError;
		strError.Format("%s%s",pResFilename,"文件长度为0!");
		WriteError(strError);
		nErr = -2;//该文件长度为0
		return nErr;
	}
	isFile.Close();

	//获取文件压缩前的相关信息  文件名和文件长度
	_tagFileProperties Fileproperties;
	memcpy(&Fileproperties,(_tagFileProperties *)&pSource[ulSourceLen-m_nFilePropertiesSize],m_nFilePropertiesSize) ;
	*pDestLen = Fileproperties.nFileLength;//获取压缩文件前文件大小
	memset(&pSource[ulSourceLen-m_nFilePropertiesSize],0,m_nFilePropertiesSize);//清空需解压数据 后面无需文件相关信息

	//解压
	Byte *pDest = new Byte[*pDestLen];memset(pDest,0,*pDestLen);
	nErr = uncompress(pDest, pDestLen, pSource, ulSourceLen-m_nFilePropertiesSize);
	if (nErr != Z_OK)
	{
		if (pSource)
		{
			delete []pSource;
		}
		if (pDest)
		{
			delete []pDest;
		}

		CString strError;
		strError.Format("%s%s",pResFilename,"压缩出错!");
		WriteError(strError);
		return nErr;
	}

	//还原文件名
	char *ptr = NULL,c = '\\';
	char szFilename[FILENAME_MAX]={0};
	strcpy(szFilename,pResFilename);
	ptr = strrchr(szFilename,c);
	if (ptr)
	{
		memset((char*)&szFilename[ptr-szFilename+1],0,strlen(ptr)-1);//清空传入文件名
		strcpy((char*)&szFilename[ptr-szFilename+1],Fileproperties.szFilename);//根据原文件属性还原
	} 
	else
	{
		strcpy(szFilename,Fileproperties.szFilename);
	}

	try
	{
		if (nCrc == CalCRC(pDest,*pDestLen))
		{
			//写文件
			CFile fs(pDesFilename,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); //存文件
			fs.Write(pDest,*pDestLen);
			fs.Close();
		}
		else
		{
			CString strError;
			strError.Format("%s%s",pDesFilename,"CRC校验码不匹配!");
			WriteError(strError);
			nErr = -5;//CRC校验码不匹配.
		}
		
	}
	catch (CFileException* e)
	{
		if (e->m_cause == CFileException::badPath)//全部或部分路径无效。 
		{
			if (!HHMkdir(pDesFilename))//返回0 成功
			{
				CFile fs(pDesFilename,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); //存文件
				fs.Write(pDest,*pDestLen);
				fs.Close();
			}
		}
	}
	

	delete []pSource;
	delete []pDest;
	return nErr;
}
//CRC校验
int CHHCompress::CalCRC(const void *pData, int nDataLen)
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
int CHHCompress::HHMkdir(const LPCTSTR pFileName)
{
	int nErr = 0;
	char szFileName[MAX_PATH] = {0};
	strcpy(szFileName,pFileName);

	char dir[MAX_PATH]={0};
	char temp[MAX_PATH] = {0};

	char c='\\';
	char *ptr = NULL;

	ptr = strchr(szFileName,c);
	for (; NULL!= ptr;ptr = strchr(szFileName,c))
	{
		strncpy(temp,szFileName,ptr-szFileName+1);
		strcat(dir,temp);

		if (strcmpi("..\\",temp))//不相等
		{
			mkdir(dir);
		}
		strcpy(szFileName,&szFileName[ptr-szFileName+1]);
		memset(temp,0,MAX_PATH);
	}
	return nErr;
}

int CHHCompress::BatchDecompress(const LPCTSTR pFolderPath,BOOL bCompress)
{
	//m_bStopBatchDecompress = FALSE;
	int nErr = 0;
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
			if(strcmp(wfData.cFileName,".") && strcmp(wfData.cFileName,".."))//排除当前目录和上级目录
			{
				char szPath[MAX_PATH] = {0};
				strcpy(szPath,szFullPath);
				memset(&szPath[strlen(szPath)-3],0,3);
				sprintf(szSubdir,"%s%s\\",szPath,wfData.cFileName);
				BatchDecompress(szSubdir,bCompress);//递归调用，遍历
			}
			break;
		default://压缩
			{
				uLong ulLen = 0;
				if (bCompress)
				{
					if (strcmpi(&wfData.cFileName[strlen(wfData.cFileName)-3],".hh"))
					{
						char szPath[MAX_PATH] = {0};
						strcpy(szPath,szFullPath);
						memset(&szPath[strlen(szPath)-3],0,3);
						strcat(szPath,wfData.cFileName);

						int flag = HHCompress(szPath,&ulLen);
						switch(flag)
						{
						case -1:
							{
								CString strError;
								strError.Format("%s%s",szPath,"文件缺失!");
								WriteError(strError);
							}
							break;
						case -2:
							{
								CString strError;
								strError.Format("%s%s",szPath,"文件长度为0!");
								WriteError(strError);
							}
							break;
						case -3:
							{
								CString strError;
								strError.Format("%s%s",szPath,"文件大于50M，不进行处理!");
								WriteError(strError);
							}
							break;
						default:
							break;
						}
					}
				} 
				else//解压
				{
					if (!strcmpi(&wfData.cFileName[strlen(wfData.cFileName)-3],".hh"))
					{
						char szPath[MAX_PATH] = {0};
						strcpy(szPath,szFullPath);
						memset(&szPath[strlen(szPath)-3],0,3);
						strcat(szPath,wfData.cFileName);
						//memset(&szPath[strlen(szPath)-3],0,3);
						HHUncompress(szPath,&ulLen);
					}
				}
			}
			break;
		}
	}while(FindNextFile(hFind,&wfData));

	return nErr;
}

