#pragma once
#include "IUserWin.h"

// CDlgTest �Ի���

class CDlgTest : public CDialog,public IUserWin
{
	DECLARE_DYNAMIC(CDlgTest)

public:
	CDlgTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTest();

// �Ի�������
	enum { IDD = IDD_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
