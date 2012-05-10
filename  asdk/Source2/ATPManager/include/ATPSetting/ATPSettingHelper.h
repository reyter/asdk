/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法管理器.
* @author	 李伟
* @histroy

-------------------------------------------------------------
日期			作者         修改说明
2010-6-1		李伟		 创建
-------------------------------------------------------------
*/

#pragma once


#ifndef	__ATPSETTINGHELPER_H
#define __ATPSETTINGHELPER_H


/**
* 配置文件中数据结构
*
* 2010-08-16 增加_HServer结构体
* 2010-08-18 修改 增加strMarketFlag(市场标志)
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
* 2010-08-16 修改HDFServer 
* 2010-08-18 修改 服务设置 、 HDBServer 
*/
struct AFX_EXT_CLASS _Config_Macro
{
	// ini文件路径
	TCHAR strIniPath[80];
	// 服务设置
	int bServiceCheck;
	TCHAR strServiceName[128];
	int nServicePort;
	TCHAR strMiddlewareDllPath[80];
	

	// HDBServer
	int nHDBServerItems;		// 表示_HDFServer结构有多少个
	_HServer* pHDBServers;
	//	HDFServer
	int nHDFServerItems;		// 表示_HDFServer结构有多少个
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
* 算法设置类，设置与获取算法交易服务器的一些配置信息.
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
	取配置文件路径.
	*/
	static CString GetPrivateProfileFile();

	/**
	取程序工作目录.
	*/	
	static CString GetWorkingPath();

	/**
	取程序日志目录.
	*/ 	
	static CString GetLogDir();
/**
* 2010-07-27新增
*/
public:
	/**
	写配置文件
	*/
	static void Write_Conf();
	/**
	读配置文件
	*/
	static void Read_Conf();
	
};

#endif //__ATPSETTINGHELPER_H