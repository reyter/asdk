#pragma once

#include "..\\Compress\\zlib.h"
#include <direct.h> 
#ifdef STDC
#  include <string.h>
#  include <stdlib.h>
#endif

class CHHCompress
{
public:
	CHHCompress(void);
	~CHHCompress(void);
public:
	

	/**
	*	ѹ��.
	*	@param pFilename �ļ���(��·���ͺ�׺��).
	*	@param pDestLen  ѹ�����ļ�����.
	*/
	int  HHCompress (const LPCTSTR pFilename,uLongf *pDestLen);

	/**
	*	��ѹ.
	*	@param pFilename �ļ���(��·���ͺ�׺��).
	*	@param pDestLen  ѹ�����ļ�����.
	*
	*/
	int  HHUncompress (const LPCTSTR pFilename,uLongf *pDestLen);
	/**
	*	��ѹ2.
	*	@param pDesFilename Ŀ���ļ���(��·���ͺ�׺��).
	*	@param pResFilename Դ�ļ���(��·���ͺ�׺��).
	*	@param pDestLen  ѹ�����ļ�����.
	*	@param nCrc CRCУ����.
	*/
	int  HHUncompress2 (const LPCTSTR pDesFilename,const LPCTSTR pResFilename,uLongf *pDestLen, int nCrc);

	/**
	*	����ѹ������ѹ.
	*	@param pFolderPath �ļ���·��.
	*	@param bCompress �Ƿ�ѹ������ѹ.
	*/
	int BatchDecompress (const LPCTSTR pFolderPath,BOOL bCompress=TRUE);

private:

	/**
	*	�����ļ���.
	*	@param pFileName �ļ�·��.
	*	����:	"..\\..\\123\\456\\789.exe" ����123 456.
	*			"..\\..\\123\\456\\789\\"	����123 456 789.
	**/
	int HHMkdir(const LPCTSTR pFileName);

	/**
	*	CRC�ļ�У��.
	*	@param pData ��ҪУ������.
	*	@param nDataLen У�����ݵĳ���.
	*/
	int CalCRC(const void *pData, int nDataLen);
	
private:
	//�ļ����Խṹ��
	// ���ڸ��ӵ�ѹ�����ݺ���
	struct _tagFileProperties
	{
		char szFilename[FILENAME_MAX];//�ļ��� ����׺��  ����·��
		uLong nFileLength;
	};

	_tagFileProperties m_fileproperties;
	int m_nFilePropertiesSize;//�ļ����Դ�С.

	
};
