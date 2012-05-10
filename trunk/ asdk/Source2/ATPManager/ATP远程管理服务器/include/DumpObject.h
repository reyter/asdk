#pragma once

//#include "HHNetCompressHelper.h"
#include "WinDNS.h"

/**
* 文件存取和载入类
* 每一个需要写入的对像可以处理一个该类
*/
class AFX_EXT_CLASS CDumpObject
{
public:
	CDumpObject(void);
	virtual ~CDumpObject(void);

	/**
	* szOpenFile  要打开的文件名
	* bCreateMode     是创建新文件,还是打开文件，如果是打开文件，将进行检验。
	*/
	bool OpenFile(LPCTSTR szOpenFile,bool bCreateMode) throw(/*LPCTSTR*/); 

	void CloseFile();	//关闭

	bool Save()	throw(/*LPCTSTR*/);		//抛出信息为出错信息。

	bool Load()	throw(/*LPCTSTR*/);		//抛出信息为出错信息。

	//写入数据。
	bool WriteBytes(void* pBuffer,int nBufferSize) throw();

	//读出指定大小的数据到缓冲中
	bool LoadBytes(void* pBuffer,int nBufferSize) throw();

	//保存具体的数据到文件描述符对应的文件中
	//在该函数中调用WriteBytes写入数据。
    virtual bool OnDumpSave()=0;				


	//从对应的文件描述符中加载对应的信息。
	//在该函数中调用LoadBytes读出数据。
	//参数nTotalCanBeRead为可读取的总的数据。
	virtual bool OnDumpLoad(QWORD nTotalCanBeRead)=0;	

	
	

private:	
	BYTE CalcCheckSum();
	QWORD LoadHeadCheck();	//返回值 检测通过返回值大于等于零(表示CustomeWriteSize)，否则反回负数
	
	//安全独写
	static bool SafeRead(int nFile,void* pBuffer,int nSize);
	static bool SafeWrite(int nFile,void* pBuffer,int nSize);

private:
	int  m_nFileDescriptor;								//文件描述符
	//QWORD  m_nTotalWriteBytes;							//总计写入数据量
	CString  m_szFileName;
};
