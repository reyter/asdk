#pragma once

struct STECH
{
	CString m_strName;//名称
	unsigned short m_usCycle;//周期
	bool m_bDefault;//默认
	bool m_bMainPic;//是否主图
	int m_nParamCount;//参数个数
	bool m_bCanAdd;//可以添加
	char m_acParams[10][16];//参数列表
	char m_acDescs[10][64];//参数描述

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
	// 初始化
	int Init(void);
	// 取技术指标
	int getTech(STECH * c_pTech);
	int setTech(STECH * c_pTech);

	//取配置的技术指标
	CString getTechByIndex(int c_nIndex, bool c_bIsStock,unsigned short c_usCycle,CString c_strCode);
	int setTechByIndex(int c_nIndex, bool c_bIsStock, CString c_strTech,unsigned short c_usCycle);

	//指标是否支持
	bool isValid(CString c_strTech,bool c_bIsStock,unsigned short c_usCycle,CString c_strCode);

	//坐标
	int getAix();
	void setAix(int);
};
