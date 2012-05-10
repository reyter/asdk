// nsd1Dlg.h : 头文件
//

#pragma once


// Cnsd1Dlg 对话框
class Cnsd1Dlg : public CDialog
{
// 构造
public:
	Cnsd1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NSD1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	
	typedef struct tagUpgradeInfo
	{
		HWND hWnd;					// 发送升级信息窗口的句柄,可以用此句柄回发数据
		char chAppName[128];		// 现运行的exe文件名
		char szAppID[16];			// APPID
		char szUserID[16];        //用户代码
		char szServerIP[32];      // 升级服务器IP地址
		int  nServerPort;         // 升级服务器端口
		bool bForce;				//是否强制升级
		char szVersion[16];       // 版本号
		DWORD dwFlags;           // flags
	};

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	
	afx_msg void OnBnClickedButton3();

	void updateMSG();
	BOOL m_bForce;
};
