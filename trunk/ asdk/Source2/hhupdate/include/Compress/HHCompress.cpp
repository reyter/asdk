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

int  CHHCompress::HHCompress (const LPCTSTR pFilename/*��·������׺�������ļ���*/,uLongf *pDestLen)
{
	int nErr;

	CFile isFile;
	if(!isFile.Open(pFilename, CFile::modeRead | CFile::typeBinary))
	{
		nErr = -1;
		return nErr;//û�и��ļ�
	}

	uLong ulSourceLen = (uLong)isFile.GetLength(); //��ȡѹ���ļ�����
	*pDestLen = ulSourceLen*2;//Ϊ�˷�ֹѹ�������ݱ��
	if (ulSourceLen<=0)
	{
		nErr = -2;//���ļ�����Ϊ0
		return nErr;
	}
	if (ulSourceLen >= (LIMITSIZE-m_nFilePropertiesSize))//����m_nFilePropertiesSize���ֽڱ���
	{
		nErr = -3;//����Դ����50M �����д���
		return nErr;
	}

	if (ulSourceLen<100)//ѹ���󳤶��п��ܱ����ڵĻ�Ҫ��
	{
		*pDestLen = 1000;
	}

	//����ѹ���ļ�
	Bytef *pSource = new Bytef[ulSourceLen+m_nFilePropertiesSize]; memset(pSource,0,ulSourceLen+m_nFilePropertiesSize);
	Byte *pDest = new Byte[*pDestLen+m_nFilePropertiesSize]; memset(pDest,0,*pDestLen+m_nFilePropertiesSize);
	if (0==isFile.Read(pSource,ulSourceLen))
	{
		nErr = -2;	//���ļ�����Ϊ0
		return nErr;
	}
	isFile.Close();

	//ѹ��
	const char *ptr = NULL,c = '\\';
	ptr = strrchr(pFilename,c);//�ڴ��в���ָ���ַ������һ������  ��ȡ�ļ���
	nErr = compress(pDest, pDestLen, pSource, ulSourceLen);//ѹ��
	if (nErr != Z_OK)
	{
		delete []pSource;
		delete []pDest;
		return nErr;
	}

	//���ļ������Ϣ���ӵ�ѹ���ļ���  ����ѹ����
	if (ptr)
	{
		strcpy(m_fileproperties.szFilename,&ptr[1]);
	}
	else
	{
		strcpy(m_fileproperties.szFilename,pFilename);	//û��·��  ֻ��һ���ļ���
	}
	m_fileproperties.nFileLength = ulSourceLen;
	memcpy((char*)&pDest[*pDestLen],(char*)&m_fileproperties,m_nFilePropertiesSize);
	*pDestLen =*pDestLen + m_nFilePropertiesSize;//����ѹ�����ļ�����
	
	
	//������׺��
	char szFilename[FILENAME_MAX]={0};
	strcpy(szFilename,pFilename);
	strcat(szFilename,_T(".hh"));

	//д�ļ�
	CFileException e;
	CFile os;
	if(!os.Open(szFilename,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary,&e)) //���ļ�
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
		return nErr;//û�и��ļ�
	}

	uLong ulSourceLen = (uLong)isFile.GetLength(); 
	if (ulSourceLen<=0)
	{
		nErr = -2;//���ļ�����Ϊ0
		return nErr;
	}
	if (ulSourceLen >= (LIMITSIZE-m_nFilePropertiesSize))//��ѹ����Դ���ܴ���50M
	{
		nErr = -3;
		return nErr;
	}

	//��ȡ���ѹ�ļ�
	Bytef *pSource = new Bytef[ulSourceLen];memset(pSource,0,ulSourceLen);
	if (!isFile.Read(pSource,ulSourceLen))
	{
		if (pSource)
		{
			delete []pSource;
		}
		
		nErr = -2;//���ļ�����Ϊ0
		return nErr;
	}
	isFile.Close();

	//��ȡ�ļ�ѹ��ǰ�������Ϣ  �ļ������ļ�����
	_tagFileProperties Fileproperties;
	memcpy(&Fileproperties,(_tagFileProperties *)&pSource[ulSourceLen-m_nFilePropertiesSize],m_nFilePropertiesSize) ;
	*pDestLen = Fileproperties.nFileLength;//��ȡѹ���ļ�ǰ�ļ���С
	memset(&pSource[ulSourceLen-m_nFilePropertiesSize],0,m_nFilePropertiesSize);//������ѹ���� ���������ļ������Ϣ

	//��ѹ
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

	//��ԭ�ļ���
	char *ptr = NULL,c = '\\';
	char szFilename[FILENAME_MAX]={0};
	strcpy(szFilename,pFilename);
	ptr = strrchr(szFilename,c);
	if (ptr)
	{
		memset((char*)&szFilename[ptr-szFilename+1],0,strlen(ptr)-1);//��մ����ļ���
		strcpy((char*)&szFilename[ptr-szFilename+1],Fileproperties.szFilename);//����ԭ�ļ����Ի�ԭ
	} 
	else
	{
		strcpy(szFilename,Fileproperties.szFilename);
	}

	//д�ļ�
	try
	{
		CFile fs(szFilename,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); //���ļ�
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
		strError.Format("%s%s",pResFilename,"�ļ�ȱʧ!");
		WriteError(strError);
		return nErr;//û�и��ļ�
	}

	uLong ulSourceLen = (uLong)isFile.GetLength(); 
	if (ulSourceLen<=0)
	{
		isFile.Close();
		CString strError;
		strError.Format("%s%s",pResFilename,"�ļ�����Ϊ0!");
		WriteError(strError);
		nErr = -2;//���ļ�����Ϊ0
		return nErr;
	}
	if (ulSourceLen >= (LIMITSIZE-m_nFilePropertiesSize))//��ѹ����Դ���ܴ���50M
	{
		isFile.Close();
		CString strError;
		strError.Format("%s%s",pResFilename,"�ļ�����50M�������д���!");
		WriteError(strError);
		nErr = -3;
		return nErr;
	}

	//��ȡ���ѹ�ļ�
	Bytef *pSource = new Bytef[ulSourceLen];memset(pSource,0,ulSourceLen);
	if (!isFile.Read(pSource,ulSourceLen))
	{
		if (pSource)
		{
			delete []pSource;
		}

		isFile.Close();
		CString strError;
		strError.Format("%s%s",pResFilename,"�ļ�����Ϊ0!");
		WriteError(strError);
		nErr = -2;//���ļ�����Ϊ0
		return nErr;
	}
	isFile.Close();

	//��ȡ�ļ�ѹ��ǰ�������Ϣ  �ļ������ļ�����
	_tagFileProperties Fileproperties;
	memcpy(&Fileproperties,(_tagFileProperties *)&pSource[ulSourceLen-m_nFilePropertiesSize],m_nFilePropertiesSize) ;
	*pDestLen = Fileproperties.nFileLength;//��ȡѹ���ļ�ǰ�ļ���С
	memset(&pSource[ulSourceLen-m_nFilePropertiesSize],0,m_nFilePropertiesSize);//������ѹ���� ���������ļ������Ϣ

	//��ѹ
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
		strError.Format("%s%s",pResFilename,"ѹ������!");
		WriteError(strError);
		return nErr;
	}

	//��ԭ�ļ���
	char *ptr = NULL,c = '\\';
	char szFilename[FILENAME_MAX]={0};
	strcpy(szFilename,pResFilename);
	ptr = strrchr(szFilename,c);
	if (ptr)
	{
		memset((char*)&szFilename[ptr-szFilename+1],0,strlen(ptr)-1);//��մ����ļ���
		strcpy((char*)&szFilename[ptr-szFilename+1],Fileproperties.szFilename);//����ԭ�ļ����Ի�ԭ
	} 
	else
	{
		strcpy(szFilename,Fileproperties.szFilename);
	}

	try
	{
		if (nCrc == CalCRC(pDest,*pDestLen))
		{
			//д�ļ�
			CFile fs(pDesFilename,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); //���ļ�
			fs.Write(pDest,*pDestLen);
			fs.Close();
		}
		else
		{
			CString strError;
			strError.Format("%s%s",pDesFilename,"CRCУ���벻ƥ��!");
			WriteError(strError);
			nErr = -5;//CRCУ���벻ƥ��.
		}
		
	}
	catch (CFileException* e)
	{
		if (e->m_cause == CFileException::badPath)//ȫ���򲿷�·����Ч�� 
		{
			if (!HHMkdir(pDesFilename))//����0 �ɹ�
			{
				CFile fs(pDesFilename,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary); //���ļ�
				fs.Write(pDest,*pDestLen);
				fs.Close();
			}
		}
	}
	

	delete []pSource;
	delete []pDest;
	return nErr;
}
//CRCУ��
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

		if (strcmpi("..\\",temp))//�����
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
		nErr = -1;//û��
		return nErr;
	}

	do
	{
		switch(wfData.dwFileAttributes)
		{
		case FILE_ATTRIBUTE_DIRECTORY://Ŀ¼
			if(strcmp(wfData.cFileName,".") && strcmp(wfData.cFileName,".."))//�ų���ǰĿ¼���ϼ�Ŀ¼
			{
				char szPath[MAX_PATH] = {0};
				strcpy(szPath,szFullPath);
				memset(&szPath[strlen(szPath)-3],0,3);
				sprintf(szSubdir,"%s%s\\",szPath,wfData.cFileName);
				BatchDecompress(szSubdir,bCompress);//�ݹ���ã�����
			}
			break;
		default://ѹ��
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
								strError.Format("%s%s",szPath,"�ļ�ȱʧ!");
								WriteError(strError);
							}
							break;
						case -2:
							{
								CString strError;
								strError.Format("%s%s",szPath,"�ļ�����Ϊ0!");
								WriteError(strError);
							}
							break;
						case -3:
							{
								CString strError;
								strError.Format("%s%s",szPath,"�ļ�����50M�������д���!");
								WriteError(strError);
							}
							break;
						default:
							break;
						}
					}
				} 
				else//��ѹ
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

