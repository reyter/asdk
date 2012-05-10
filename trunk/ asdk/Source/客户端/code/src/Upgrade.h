#ifndef Upgrade_h__
#define Upgrade_h__
#include "Connenct\ServerMg.h"

#define RETVAL_VERSION_SAME		0//��ͬ�汾���������
#define RETVAL_VERSION_NEW			1//���°汾����Ҫ����
#define RETVAL_VERSION_FAILED		 -1//�汾���ʧ��

#define RETVAL_UPGRADE_DONOT				0//��������
#define RETVAL_UPGRADE_SUCCESS				1 //�����ɹ�
#define RETVAL_UPGRADE_FAILED				-1//����ʧ��


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
	// Description:ִ����������
	// Parameter: void
	//************************************
	DWORD DoUpgrade(void);

private:
	//************************************
	// Method:    UpgradeServerGroupData
	// FullName:  CUpgrade::UpgradeServerGroupData
	// Access:    public 
	// Returns:   void
	// Description:���·�������ַ
	// Parameter: DWORD
	//************************************
	DWORD UpgradeServerGroupData(void);


	//************************************
	// Method:    GetCurrentClientVersion
	// FullName:  CUpgrade::GetCurrentClientVersion
	// Access:    public 
	// Returns:   CString
	// Description:��ȡ��ǰ�ͻ��˰汾��
	// Parameter: void
	//************************************
	CString GetCurrentClientVersion(void);

	//************************************
	// Method:    CheckClientVersion
	// FullName:  CUpgrade::CheckClientVersion
	// Access:    public 
	// Returns:   DWORD  RETVAL_VERSION_SAME\RETVAL_VERSION_NEW\RETVAL_VERSION_FAILED
	// Description:���ͻ��˰汾
	// Parameter: CString & strNewVersion   �����°汾��
	// Parameter: const CString & strCurVersion ��ǰ�ͻ��˵İ汾��
	//************************************
	DWORD CheckClientVersion(CString& strNewVersion,const CString& strCurVersion);

	//************************************
	// Method:    DownLoadUpgradeFile
	// FullName:  CUpgrade::DownLoadUpgradeFile
	// Access:    public 
	// Returns:   DWORD
	// Description:���ؿͻ��������ļ�
	// Parameter: const CString & strUpgradfFile
	//************************************
	DWORD DownLoadUpgradeFile(const CString& strUpgradfFile);

	//************************************
	// Method:    ForceQuit
	// FullName:  CUpgrade::ForceQuit
	// Access:    public 
	// Returns:   void
	// Description:ǿ���˳�����
	// Parameter: void
	//************************************
	void ForceQuit(void);			
};
#endif // Upgrade_h__
