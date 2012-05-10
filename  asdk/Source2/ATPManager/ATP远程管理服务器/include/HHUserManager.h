#pragma once

typedef int (*FN_HHUSERMANAGER_CALLBACK_PTR)(CWnd *pParent, char **ppchAdv, int &nLenAdv);

#define ID_UMERROR_NOUSER	-1	//无此用户或密码错误
#define ID_UMERROR_STOP		-2	//已经停止使用
#define ID_UMERROR_DATE		-3	//不在授权期内
#define ID_UMERROR_WORKDAY	-4	//不在授权日内
#define ID_UMERROR_TIME		-5	//不在授权时间内
#define ID_UMERROR_NUMBER	-6	//超出登陆数量
#define ID_UMERROR_IP		-7	//IP地址不正确

struct HHUserList_Packet
{
	char chUserName[32];
	char chPW[40];
	char nCheckLimited;			//日期(0x01)、每周(0x02)、每天限制(0x04)、连接数(0x08)、IP限制(0x10)
	char chCheckWeek;			//每周限制(从星期日到星期六: 0x01,0x02,0x04,0x08,0x10,0x20,0x40)
	char chCheckTime;
	char chStatus;				//状态 0:正常, 1:暂停
	int  nCheckDateBegin;		//起始日期
	int  nCheckDateEnd;			//截至日期
	int  nCheckDayTimeBegin[8];	//开始时间
	int  nCheckDayTimeEnd[8];	//结束时间
	int  nLimitedNumber;		//限制数量
	int  nRightsFlags;			//权限
	int  nRightsExFlags;		//扩展权限
	char chCheckIP[48];			//IP地址限制
	int  nLoginNumber;			//已登陆数量
	char chNote[80];			//说明
	char chIdentify[8];			//识别字串
	int  lLoginDate;
	int  lLoginTime;
	int  lTotalLogins;			//累计登陆次数
	int  lThisLogins;			//本次登陆次数
	char chLastLog[32];
	int  nNumberAdv;
	int  nLenAdv;				//高级设置数据长度
	char *pchAdv;				//高级设置数据地址(必须使用 new char[] 分配)

	HHUserList_Packet()
	{
		memset(this, 0, sizeof(HHUserList_Packet));
	}
	~HHUserList_Packet()
	{
		if(pchAdv) delete pchAdv;
	}
};

class AFX_EXT_CLASS CHHUserManager
{
public:
	CHHUserManager(void);
	~CHHUserManager(void);

	BOOL OpenUserList(char *pFileName, BOOL bMD5Flag=TRUE);
	BOOL SaveUserList();

	int  DoManager(FN_HHUSERMANAGER_CALLBACK_PTR pfunc_OnSetAdv=NULL);

	//检查用户, 如果有登陆数量限制，登陆数量会自动加1
	//返回值定义
	//1：正确
	//#define ID_UMERROR_NOUSER		-1	//无此用户或密码错误
	//#define ID_UMERROR_STOP		-2	//已经停止使用
	//#define ID_UMERROR_DATE		-3	//不在授权期内
	//#define ID_UMERROR_WORKDAY	-4	//不在授权日内
	//#define ID_UMERROR_TIME		-5	//不在授权时间内
	//#define ID_UMERROR_NUMBER		-6	//超出登陆数量
	//#define ID_UMERROR_IP			-7	//IP地址不正确
	int  CheckUser(char *pUserName, char *pPassword, int &nRights, int &nRightsEx, char *pchIP=NULL, char *pchError=NULL, char *pchRemark=NULL, char *pchIdentify=NULL);
	//检测是否在有效设置时间段
	int  CheckUserValidWorkTime(char *pUserName, char *pPassword, char *pchError=NULL);
	//获取备注信息
	int  GetUserRemark(char *pUserName, char *pPassword, char *pRemark);
	//获取限制数量
	int  GetUserLimitedNumber(char *pUserName, char *pPassword);
	//获取已登陆数量
	int  GetUserLoginNumber(char *pUserName, char *pPassword);
	//设置登陆数量
	int  SetUserLoginNumber(char *pUserName, char *pPassword, int nNumber);

	int  GetUserRightsFlag();
	int  GetUserRightsExFlag();

	BOOL GetLimitedDate(char *pUserName, char *pPassword, int &lBeginDate, int &lEndDate);
	HHUserList_Packet GetUserRightInfo(char *pUserName, char *pPassword);
	char *GetUserAdvSet(char *pUserName, char *pPassword, int &nLen);	//返回的指针数据需要delete

	BOOL ClearAll();

	BOOL IsMD5()
	{
		return m_bMD5Flag;
	}
	static CString GetMD5(BYTE* pBuf, UINT nLength);
	
	void SetNumberAdvName(char *pNumberName);
	void SetUserRights(int nIndex, char *pchRightsName, char *pchRightsShortName=NULL);
	void SetUserRightsEx(int nIndex, char *pchRightsName, char *pchRightsShortName=NULL);
	char *GetUserRightsName(int nIndex);
	char *GetUserRightsExName(int nIndex);
	char *GetUserRightsShortName(int nIndex);
	char *GetUserRightsExShortName(int nIndex);
	char *GetUserNumberAdvName();

	HHUserList_Packet *GetUserList(int &nCount);


private:
	CRITICAL_SECTION	m_cs;
	BOOL m_bMD5Flag;
	HHUserList_Packet *m_pUserList;
	int  m_nUserListCount;
	char m_chUserListFileName[128];

	char m_chRights[32][32];
	char m_chRightsShortName[32][32];
	char m_chRightsEx[32][32];
	char m_chRightsShortNameEx[32][32];

	char m_chNumerAdvName[32];
};
