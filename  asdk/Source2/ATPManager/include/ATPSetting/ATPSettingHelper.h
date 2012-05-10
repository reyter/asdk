/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨������.
* @author	 ��ΰ
* @histroy

-------------------------------------------------------------
����			����         �޸�˵��
2010-6-1		��ΰ		 ����
-------------------------------------------------------------
*/

#pragma once


#ifndef	__ATPSETTINGHELPER_H
#define __ATPSETTINGHELPER_H


/**
* �����ļ������ݽṹ
*
* 2010-08-16 ����_HServer�ṹ��
* 2010-08-18 �޸� ����strMarketFlag(�г���־)
*/
struct AFX_EXT_CLASS _HServer
{
	TCHAR strIp[48];
	int nPort;
	TCHAR strUser[40];
	TCHAR strPassword[80];
	int nDataFlag;
	TCHAR strMarketFlag[128];
	_HServer()
	{
		memset(this,0,sizeof(_HServer));
	}

};

/**
* 2010-08-16 �޸�HDFServer 
* 2010-08-18 �޸� �������� �� HDBServer 
*/
struct AFX_EXT_CLASS _Config_Macro
{
	// ini�ļ�·��
	TCHAR strIniPath[80];
	// ��������
	int bServiceCheck;
	TCHAR strServiceName[128];
	int nServicePort;
	TCHAR strMiddlewareDllPath[80];
	

	// HDBServer
	int nHDBServerItems;		// ��ʾ_HDFServer�ṹ�ж��ٸ�
	_HServer* pHDBServers;
	//	HDFServer
	int nHDFServerItems;		// ��ʾ_HDFServer�ṹ�ж��ٸ�
	_HServer* pHDFServers;

	_Config_Macro(){		
		memset(this,0,sizeof(_Config_Macro));

		pHDBServers = NULL;
		nHDBServerItems = 0;

		pHDFServers = NULL;
		nHDFServerItems = 0;
	}
};

extern _Config_Macro Config_Macro;
/**
* �㷨�����࣬�������ȡ�㷨���׷�������һЩ������Ϣ.
*
*/
class AFX_EXT_CLASS CATPSettingHelper
{
public:
	CATPSettingHelper(void);
	virtual ~CATPSettingHelper(void);

public:
	static const _Config_Macro* GetSetting();
	static void DoSetting();

public:
	/**
	ȡ�����ļ�·��.
	*/
	static CString GetPrivateProfileFile();

	/**
	ȡ������Ŀ¼.
	*/	
	static CString GetWorkingPath();

	/**
	ȡ������־Ŀ¼.
	*/ 	
	static CString GetLogDir();
/**
* 2010-07-27����
*/
public:
	/**
	д�����ļ�
	*/
	static void Write_Conf();
	/**
	�������ļ�
	*/
	static void Read_Conf();
	
};

#endif //__ATPSETTINGHELPER_H