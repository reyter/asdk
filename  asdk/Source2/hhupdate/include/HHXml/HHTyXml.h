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
	*	�����ļ���·�� �����ļ� ����Ԫ��.��HHComposeXML��ʹ��.
	*	@param pFolderPath �ļ�·��.
	*	@param Elem Ԫ��.
	**/
	int HHScan(const LPCTSTR pFolderPath,TiXmlElement *Elem);
	/**
	*	��ȡ�ļ���Ϣ ���ƥ����Ҫ�����ļ�. ��HHDecomposeXML��ʹ��.
	*	@param pNode �ӽڵ�
	*	@param pName ·����
	*/
	int HHGetFileInfo(const TiXmlElement *pNode, char *pName,const char *pLen,const char *pDate,const char *pTime, const char *pFileVer, const char *pCrc);
	
	/**
	*	��ȡ�ļ��汾��.
	*	@param pFolderPath �ļ�·��.
	*	@param [out]pFileVer ��ȡ���İ汾��.
	*/
	int GetFileVer(const LPCTSTR pFolderPath, LPCTSTR pFileVer);

	unsigned char *m_pBuff;			//CRCУ�������ڴ�.
	long m_lBuffCount;				//�����ڴ�����.
public:
	typedef struct
	{
		char szFileName[MAX_PATH];	//�ļ���.
		char szLen[16];				//�ļ�����.
		char szDate[16];			//�ļ�����޸�����.
		char szTime[16];			//�ļ�����޸�ʱ��.
		char szFileVer[MAX_PATH];	//�ļ��汾.
		char szCrc[16];				//�ļ���CRCУ����.
	}_tagAttribute,*PAttribute;
	typedef CList<PAttribute,PAttribute> LSXMLFILES;//��Ŷ�ȡXML���������ļ���(��·��)

	LSXMLFILES m_list;

	/**
	*	�ͷ�LSXMLFILES�б���ڴ�.
	*	@param pList LSXMLFILES�б�ָ��.
	*/
	void ReleaseXMLFILESList(LSXMLFILES *pList);

	/**
	*	��ȡ�����ļ�״̬
	*	@param filename �ļ���(��·��).
	*	@param lLen �ļ�����.
	*	@param lDate ����.
	*	@param  lTime ʱ��.
	*	@param nCrc CRCУ����.
	*/
	BOOL GetLocalFileStatus(char *pFilename, long &lLen, long &lDate, long &lTime,char *pFileVer,int &nCrc);

	/**
	*	CRC�ļ�У��.
	*	@param pData ��ҪУ������.
	*	@param nDataLen У�����ݵĳ���.
	*/
	int CalCRC(void *pData, int nDataLen);
public:

	/**
	*	����·��(�������ļ���) ���XML.
	*	@param pFolderPath �ļ���·��
	*/
	int HHComposeXML(const LPCTSTR pFolderPath);

	/**
	*	����XML�ļ� �ֽ�XML����ȡXML�������Ҫ���µ��ļ�·���б�,ƥ�䱾���ļ�.
	*	@param pFilePath xml�ļ�·��
	*	@param pList Clistָ�룬�����ļ�����.
	*/
	int HHDecomposeXML(const char* pXmlPath,LSXMLFILES *pList);

	
};
