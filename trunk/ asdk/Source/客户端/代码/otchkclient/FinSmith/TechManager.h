#pragma once

struct STECH
{
	CString m_strName;//����
	unsigned short m_usCycle;//����
	bool m_bDefault;//Ĭ��
	bool m_bMainPic;//�Ƿ���ͼ
	int m_nParamCount;//��������
	bool m_bCanAdd;//�������
	char m_acParams[10][16];//�����б�
	char m_acDescs[10][64];//��������

	void Init()
	{
		m_bDefault = true;
		m_bMainPic = false;
		m_bCanAdd = false;
		m_nParamCount = 0;
		for(int n=0; n<10; n++)
		{
			m_acParams[n][0] = 0;
			m_acDescs[n][0] = 0;
		}
	}
};

class CTechManager
{
public:
	CTechManager(void);
	~CTechManager(void);

	static CTechManager * m_instance;
	static CTechManager * getInstance();
	static void freeInstance();
	// ��ʼ��
	int Init(void);
	// ȡ����ָ��
	int getTech(STECH * c_pTech);
	int setTech(STECH * c_pTech);

	//ȡ���õļ���ָ��
	CString getTechByIndex(int c_nIndex, bool c_bIsStock,unsigned short c_usCycle,CString c_strCode);
	int setTechByIndex(int c_nIndex, bool c_bIsStock, CString c_strTech,unsigned short c_usCycle);

	//ָ���Ƿ�֧��
	bool isValid(CString c_strTech,bool c_bIsStock,unsigned short c_usCycle,CString c_strCode);

	//����
	int getAix();
	void setAix(int);
};
