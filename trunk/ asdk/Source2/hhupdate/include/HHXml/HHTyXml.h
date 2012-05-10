#pragma once
#include <afxtempl.h>
#include <iostream>
#include <fstream>
#include "tinyxml.h"
#include <WinVer.h>
using namespace std;

class CHHTyXml
{
public:
	CHHTyXml(void);
	~CHHTyXml(void);
private:
	
	/**
	*	根据文件夹路径 查找文件 生成元素.在HHComposeXML中使用.
	*	@param pFolderPath 文件路径.
	*	@param Elem 元素.
	**/
	int HHScan(const LPCTSTR pFolderPath,TiXmlElement *Elem);
	/**
	*	获取文件信息 随后匹配需要更新文件. 在HHDecomposeXML中使用.
	*	@param pNode 子节点
	*	@param pName 路径名
	*/
	int HHGetFileInfo(const TiXmlElement *pNode, char *pName,const char *pLen,const char *pDate,const char *pTime, const char *pFileVer, const char *pCrc);
	
	/**
	*	获取文件版本号.
	*	@param pFolderPath 文件路径.
	*	@param [out]pFileVer 获取到的版本号.
	*/
	int GetFileVer(const LPCTSTR pFolderPath, LPCTSTR pFileVer);

	unsigned char *m_pBuff;			//CRC校验数据内存.
	long m_lBuffCount;				//创建内存数量.
public:
	typedef struct
	{
		char szFileName[MAX_PATH];	//文件名.
		char szLen[16];				//文件长度.
		char szDate[16];			//文件最后修改日期.
		char szTime[16];			//文件最后修改时间.
		char szFileVer[MAX_PATH];	//文件版本.
		char szCrc[16];				//文件的CRC校验码.
	}_tagAttribute,*PAttribute;
	typedef CList<PAttribute,PAttribute> LSXMLFILES;//存放读取XML生成所有文件名(含路径)

	LSXMLFILES m_list;

	/**
	*	释放LSXMLFILES列表的内存.
	*	@param pList LSXMLFILES列表指针.
	*/
	void ReleaseXMLFILESList(LSXMLFILES *pList);

	/**
	*	获取本地文件状态
	*	@param filename 文件名(含路径).
	*	@param lLen 文件长度.
	*	@param lDate 日期.
	*	@param  lTime 时间.
	*	@param nCrc CRC校验码.
	*/
	BOOL GetLocalFileStatus(char *pFilename, long &lLen, long &lDate, long &lTime,char *pFileVer,int &nCrc);

	/**
	*	CRC文件校验.
	*	@param pData 需要校验数据.
	*	@param nDataLen 校验数据的长度.
	*/
	int CalCRC(void *pData, int nDataLen);
public:

	/**
	*	根据路径(不包含文件名) 组合XML.
	*	@param pFolderPath 文件夹路径
	*/
	int HHComposeXML(const LPCTSTR pFolderPath);

	/**
	*	根据XML文件 分解XML，读取XML保存的需要更新的文件路径列表,匹配本地文件.
	*	@param pFilePath xml文件路径
	*	@param pList Clist指针，保存文件属性.
	*/
	int HHDecomposeXML(const char* pXmlPath,LSXMLFILES *pList);

	
};
