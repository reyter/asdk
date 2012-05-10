#pragma once
#include "..\\include\\compress\\HHCompress.h"
#include "..\\include\\HHXml\\HHTyXml.h"
// CHHSetting �Ի���

class CHHSetting : public CDialog
{
	DECLARE_DYNAMIC(CHHSetting)

public:
	CHHSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHHSetting();

// �Ի�������
	enum { IDD = IDD_DLG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBuildxml();
	afx_msg void OnBnClickedBtnCompress();
	CHHTyXml hhTyXml; 
	CHHCompress hhCompress;
	/**
	*	����ͬ��Ŀ¼����ͬʱ����ѹ��������XML.
	*	@param bMark TRUE:ѹ��   FALSE:����XML
	*/
	static UINT HHScanLevel1Folder(LPVOID lParam);
	BOOL m_bMark;
	virtual void OnCancel();
	CWinThread* m_pThread;
	BOOL m_bThreadRun;//�߳��Ƿ�������
	CListCtrl m_listShow;
	virtual BOOL OnInitDialog();
	//��ʼ��LIST
	void InitList();
	//��ʼ�������list����
	void InitListData();
	//list��ѡ�����
	int GetCheckCount();
	//��ȡ�����ļ���Ϣ
	BOOL GetLocalFileStatus(char *pFilename, long &lDate, long &lTime);
	afx_msg void OnBnClickedCheckSelectall();
	CButton m_checkSelectAll;
	afx_msg void OnBnClickedBtnOnekey();
};
