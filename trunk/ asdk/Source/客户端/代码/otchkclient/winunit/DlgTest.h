#pragma once
#include "IUserWin.h"

// CDlgTest 对话框

class CDlgTest : public CDialog,public IUserWin
{
	DECLARE_DYNAMIC(CDlgTest)

public:
	CDlgTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTest();

// 对话框数据
	enum { IDD = IDD_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
