#pragma once

typedef int (*FN_HHUSERMANAGER_CALLBACK_PTR)(CWnd *pParent, char **ppchAdv, int &nLenAdv);

#define ID_UMERROR_NOUSER	-1	//�޴��û����������
#define ID_UMERROR_STOP		-2	//�Ѿ�ֹͣʹ��
#define ID_UMERROR_DATE		-3	//������Ȩ����
#define ID_UMERROR_WORKDAY	-4	//������Ȩ����
#define ID_UMERROR_TIME		-5	//������Ȩʱ����
#define ID_UMERROR_NUMBER	-6	//������½����
#define ID_UMERROR_IP		-7	//IP��ַ����ȷ

struct HHUserList_Packet
{
	char chUserName[32];
	char chPW[40];
	char nCheckLimited;			//����(0x01)��ÿ��(0x02)��ÿ������(0x04)��������(0x08)��IP����(0x10)
	char chCheckWeek;			//ÿ������(�������յ�������: 0x01,0x02,0x04,0x08,0x10,0x20,0x40)
	char chCheckTime;
	char chStatus;				//״̬ 0:����, 1:��ͣ
	int  nCheckDateBegin;		//��ʼ����
	int  nCheckDateEnd;			//��������
	int  nCheckDayTimeBegin[8];	//��ʼʱ��
	int  nCheckDayTimeEnd[8];	//����ʱ��
	int  nLimitedNumber;		//��������
	int  nRightsFlags;			//Ȩ��
	int  nRightsExFlags;		//��չȨ��
	char chCheckIP[48];			//IP��ַ����
	int  nLoginNumber;			//�ѵ�½����
	char chNote[80];			//˵��
	char chIdentify[8];			//ʶ���ִ�
	int  lLoginDate;
	int  lLoginTime;
	int  lTotalLogins;			//�ۼƵ�½����
	int  lThisLogins;			//���ε�½����
	char chLastLog[32];
	int  nNumberAdv;
	int  nLenAdv;				//�߼��������ݳ���
	char *pchAdv;				//�߼��������ݵ�ַ(����ʹ�� new char[] ����)

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

	//����û�, ����е�½�������ƣ���½�������Զ���1
	//����ֵ����
	//1����ȷ
	//#define ID_UMERROR_NOUSER		-1	//�޴��û����������
	//#define ID_UMERROR_STOP		-2	//�Ѿ�ֹͣʹ��
	//#define ID_UMERROR_DATE		-3	//������Ȩ����
	//#define ID_UMERROR_WORKDAY	-4	//������Ȩ����
	//#define ID_UMERROR_TIME		-5	//������Ȩʱ����
	//#define ID_UMERROR_NUMBER		-6	//������½����
	//#define ID_UMERROR_IP			-7	//IP��ַ����ȷ
	int  CheckUser(char *pUserName, char *pPassword, int &nRights, int &nRightsEx, char *pchIP=NULL, char *pchError=NULL, char *pchRemark=NULL, char *pchIdentify=NULL);
	//����Ƿ�����Ч����ʱ���
	int  CheckUserValidWorkTime(char *pUserName, char *pPassword, char *pchError=NULL);
	//��ȡ��ע��Ϣ
	int  GetUserRemark(char *pUserName, char *pPassword, char *pRemark);
	//��ȡ��������
	int  GetUserLimitedNumber(char *pUserName, char *pPassword);
	//��ȡ�ѵ�½����
	int  GetUserLoginNumber(char *pUserName, char *pPassword);
	//���õ�½����
	int  SetUserLoginNumber(char *pUserName, char *pPassword, int nNumber);

	int  GetUserRightsFlag();
	int  GetUserRightsExFlag();

	BOOL GetLimitedDate(char *pUserName, char *pPassword, int &lBeginDate, int &lEndDate);
	HHUserList_Packet GetUserRightInfo(char *pUserName, char *pPassword);
	char *GetUserAdvSet(char *pUserName, char *pPassword, int &nLen);	//���ص�ָ��������Ҫdelete

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
