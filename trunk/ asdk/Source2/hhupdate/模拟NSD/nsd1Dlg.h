// nsd1Dlg.h : ͷ�ļ�
//

#pragma once


// Cnsd1Dlg �Ի���
class Cnsd1Dlg : public CDialog
{
// ����
public:
	Cnsd1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NSD1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	
	typedef struct tagUpgradeInfo
	{
		HWND hWnd;					// ����������Ϣ���ڵľ��,�����ô˾���ط�����
		char chAppName[128];		// �����е�exe�ļ���
		char szAppID[16];			// APPID
		char szUserID[16];        //�û�����
		char szServerIP[32];      // ����������IP��ַ
		int  nServerPort;         // �����������˿�
		bool bForce;				//�Ƿ�ǿ������
		char szVersion[16];       // �汾��
		DWORD dwFlags;           // flags
	};

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
