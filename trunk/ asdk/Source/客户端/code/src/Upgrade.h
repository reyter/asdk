#ifndef Upgrade_h__
#define Upgrade_h__
#include "Connenct\ServerMg.h"

#define RETVAL_VERSION_SAME		0//相同版本，无需更新
#define RETVAL_VERSION_NEW			1//有新版本，需要更新
#define RETVAL_VERSION_FAILED		 -1//版本检查失败

#define RETVAL_UPGRADE_DONOT				0//无需升级
#define RETVAL_UPGRADE_SUCCESS				1 //升级成功
#define RETVAL_UPGRADE_FAILED				-1//升级失败


class CUpgrade
{
public:
	CUpgrade(void);
	~CUpgrade(void);

public:
	//************************************
	// Method:    DoUpgrade
	// FullName:  CUpgrade::DoUpgrade
	// Access:    public 
	// Returns:   DWORD RETVAL_UPGRADE_DONOT\RETVAL_UPGRADE_SUCCESS\RETVAL_UPGRADE_FAILED
	// Description:执行升级过程
	// Parameter: void
	//************************************
	DWORD DoUpgrade(void);

private:
	//************************************
	// Method:    UpgradeServerGroupData
	// FullName:  CUpgrade::UpgradeServerGroupData
	// Access:    public 
	// Returns:   void
	// Description:更新服务器地址
	// Parameter: DWORD
	//************************************
	DWORD UpgradeServerGroupData(void);


	//************************************
	// Method:    GetCurrentClientVersion
	// FullName:  CUpgrade::GetCurrentClientVersion
	// Access:    public 
	// Returns:   CString
	// Description:获取当前客户端版本号
	// Parameter: void
	//************************************
	CString GetCurrentClientVersion(void);

	//************************************
	// Method:    CheckClientVersion
	// FullName:  CUpgrade::CheckClientVersion
	// Access:    public 
	// Returns:   DWORD  RETVAL_VERSION_SAME\RETVAL_VERSION_NEW\RETVAL_VERSION_FAILED
	// Description:检查客户端版本
	// Parameter: CString & strNewVersion   返回新版本号
	// Parameter: const CString & strCurVersion 当前客户端的版本号
	//************************************
	DWORD CheckClientVersion(CString& strNewVersion,const CString& strCurVersion);

	//************************************
	// Method:    DownLoadUpgradeFile
	// FullName:  CUpgrade::DownLoadUpgradeFile
	// Access:    public 
	// Returns:   DWORD
	// Description:下载客户端升级文件
	// Parameter: const CString & strUpgradfFile
	//************************************
	DWORD DownLoadUpgradeFile(const CString& strUpgradfFile);

	//************************************
	// Method:    ForceQuit
	// FullName:  CUpgrade::ForceQuit
	// Access:    public 
	// Returns:   void
	// Description:强行退出进程
	// Parameter: void
	//************************************
	void ForceQuit(void);			
};
#endif // Upgrade_h__
