#pragma once
#include "..\\include\\compress\\HHCompress.h"
#include "..\\include\\HHXml\\HHTyXml.h"
// CHHSetting 对话框

class CHHSetting : public CDialog
{
	DECLARE_DYNAMIC(CHHSetting)

public:
	CHHSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHHSetting();

// 对话框数据
	enum { IDD = IDD_DLG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBuildxml();
	afx_msg void OnBnClickedBtnCompress();
	CHHTyXml hhTyXml; 
	CHHCompress hhCompress;
	/**
	*	查找同级目录，并同时进行压缩或生成XML.
	*	@param bMark TRUE:压缩   FALSE:生成XML
	*/
	static UINT HHScanLevel1Folder(LPVOID lParam);
	BOOL m_bMark;
	virtual void OnCancel();
	CWinThread* m_pThread;
	BOOL m_bThreadRun;//线程是否在运行
	CListCtrl m_listShow;
	virtual BOOL OnInitDialog();
	//初始化LIST
	void InitList();
	//初始化或更新list数据
	void InitListData();
	//list被选择个数
	int GetCheckCount();
	//获取本地文件信息
	BOOL GetLocalFileStatus(char *pFilename, long &lDate, long &lTime);
	afx_msg void OnBnClickedCheckSelectall();
	CButton m_checkSelectAll;
	afx_msg void OnBnClickedBtnOnekey();
};
