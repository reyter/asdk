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
	*	压缩.
	*	@param pFilename 文件名(含路径和后缀名).
	*	@param pDestLen  压缩后文件长度.
	*/
	int  HHCompress (const LPCTSTR pFilename,uLongf *pDestLen);

	/**
	*	解压.
	*	@param pFilename 文件名(含路径和后缀名).
	*	@param pDestLen  压缩后文件长度.
	*
	*/
	int  HHUncompress (const LPCTSTR pFilename,uLongf *pDestLen);
	/**
	*	解压2.
	*	@param pDesFilename 目的文件名(含路径和后缀名).
	*	@param pResFilename 源文件名(含路径和后缀名).
	*	@param pDestLen  压缩后文件长度.
	*	@param nCrc CRC校验码.
	*/
	int  HHUncompress2 (const LPCTSTR pDesFilename,const LPCTSTR pResFilename,uLongf *pDestLen, int nCrc);

	/**
	*	批量压缩、解压.
	*	@param pFolderPath 文件夹路径.
	*	@param bCompress 是否压缩、解压.
	*/
	int BatchDecompress (const LPCTSTR pFolderPath,BOOL bCompress=TRUE);

private:

	/**
	*	创建文件夹.
	*	@param pFileName 文件路径.
	*	例如:	"..\\..\\123\\456\\789.exe" 创建123 456.
	*			"..\\..\\123\\456\\789\\"	创建123 456 789.
	**/
	int HHMkdir(const LPCTSTR pFileName);

	/**
	*	CRC文件校验.
	*	@param pData 需要校验数据.
	*	@param nDataLen 校验数据的长度.
	*/
	int CalCRC(const void *pData, int nDataLen);
	
private:
	//文件属性结构体
	// 用于附加到压缩数据后面
	struct _tagFileProperties
	{
		char szFilename[FILENAME_MAX];//文件名 含后缀名  不含路径
		uLong nFileLength;
	};

	_tagFileProperties m_fileproperties;
	int m_nFilePropertiesSize;//文件属性大小.

	
};
