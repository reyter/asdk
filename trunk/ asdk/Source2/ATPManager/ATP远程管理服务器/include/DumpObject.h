#pragma once

//#include "HHNetCompressHelper.h"
#include "WinDNS.h"

/**
* �ļ���ȡ��������
* ÿһ����Ҫд��Ķ�����Դ���һ������
*/
class AFX_EXT_CLASS CDumpObject
{
public:
	CDumpObject(void);
	virtual ~CDumpObject(void);

	/**
	* szOpenFile  Ҫ�򿪵��ļ���
	* bCreateMode     �Ǵ������ļ�,���Ǵ��ļ�������Ǵ��ļ��������м��顣
	*/
	bool OpenFile(LPCTSTR szOpenFile,bool bCreateMode) throw(/*LPCTSTR*/); 

	void CloseFile();	//�ر�

	bool Save()	throw(/*LPCTSTR*/);		//�׳���ϢΪ������Ϣ��

	bool Load()	throw(/*LPCTSTR*/);		//�׳���ϢΪ������Ϣ��

	//д�����ݡ�
	bool WriteBytes(void* pBuffer,int nBufferSize) throw();

	//����ָ����С�����ݵ�������
	bool LoadBytes(void* pBuffer,int nBufferSize) throw();

	//�����������ݵ��ļ���������Ӧ���ļ���
	//�ڸú����е���WriteBytesд�����ݡ�
    virtual bool OnDumpSave()=0;				


	//�Ӷ�Ӧ���ļ��������м��ض�Ӧ����Ϣ��
	//�ڸú����е���LoadBytes�������ݡ�
	//����nTotalCanBeReadΪ�ɶ�ȡ���ܵ����ݡ�
	virtual bool OnDumpLoad(QWORD nTotalCanBeRead)=0;	

	
	

private:	
	BYTE CalcCheckSum();
	QWORD LoadHeadCheck();	//����ֵ ���ͨ������ֵ���ڵ�����(��ʾCustomeWriteSize)�����򷴻ظ���
	
	//��ȫ��д
	static bool SafeRead(int nFile,void* pBuffer,int nSize);
	static bool SafeWrite(int nFile,void* pBuffer,int nSize);

private:
	int  m_nFileDescriptor;								//�ļ�������
	//QWORD  m_nTotalWriteBytes;							//�ܼ�д��������
	CString  m_szFileName;
};
