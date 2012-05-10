#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"

// CDlgUpdate �Ի���

class CDlgUpdate : public CDialog
{
	DECLARE_DYNAMIC(CDlgUpdate)

public:
	CDlgUpdate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgUpdate();

// �Ի�������
	enum { IDD = IDD_UPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	bool m_bFirstShow;
	int m_nCancel;
	CString m_strUrl;//�ļ�����
	CString m_strFile;//�ļ�����
	CString m_strInfo;//����Ϣ
	CRect m_rectInfo;
	virtual BOOL OnInitDialog();
	void SetLayout();
	bool DownFile();
	bool DownFileDirect();
	void SetInfoRect(bool c_bMax);
	afx_msg LRESULT OnDownloadSize(WPARAM wParam,LPARAM lParam);

	CProgressCtrl m_progress;
	
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedBtnStart();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CXPButton m_btnClose;
	CXPButton m_btnStart;
	CXPButton m_btnCancel;
	CEdit m_edit;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
