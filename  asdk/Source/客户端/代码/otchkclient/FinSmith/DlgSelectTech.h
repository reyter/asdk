#pragma once
#include "afxwin.h"


// CDlgSelectTech �Ի���

class CDlgSelectTech : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectTech)

public:
	CDlgSelectTech(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSelectTech();

// �Ի�������
	enum { IDD = IDD_DLG_SELECT_TECH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnDblclkListTechs();
	afx_msg void OnBnClickedOk();
	CListBox m_listTechs;
	CString m_strSelected;
	CString m_strStockCode;
	bool m_bMainPic;//��ͼ
	bool m_bIndex;//�Ƿ�ָ��
	unsigned short m_usCycle;//����
};
