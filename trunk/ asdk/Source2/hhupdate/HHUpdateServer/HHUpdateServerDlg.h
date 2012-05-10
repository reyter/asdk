// HHUpdateServerDlg.h : ͷ�ļ�
//

#pragma once
#include "IOCPServer.h"

// CHHUpdateServerDlg �Ի���
class CHHUpdateServerDlg : public CDialog
{
// ����
public:
	CHHUpdateServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CHHUpdateServerDlg();

// �Ի�������
	enum { IDD = IDD_HHUPDATESERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

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
	void ShowMsg(CString strMsg,BOOL bClear = FALSE);
	afx_msg void OnBnClickedBtnStart();
	CIOCPServer m_IocpServer;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnSet();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
