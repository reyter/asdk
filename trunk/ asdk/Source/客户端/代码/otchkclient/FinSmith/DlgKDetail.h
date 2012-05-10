/************************************************************************/
/* ����K�������                                                                     */
/************************************************************************/


#pragma once


// CDlgKDetail �Ի���
class CPicWnd;
class CDlgKDetail : public CDialog
{
	DECLARE_DYNAMIC(CDlgKDetail)

public:
	CDlgKDetail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgKDetail();

// �Ի�������
	enum { IDD = IDD_K_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void PaintMe(CDC * c_pDC);
	void SetSSTOCK(SStock * c_pStock);
	void SetKLINE(KLINE * c_pKLine,int c_nZrsp,int c_nCycle);	
	void SetDefaultRect(CRect);
	bool IsDefaultRect(CRect);
	KLINE m_kline;
	SStock *m_pStock;
	int m_nZrsp;
	int m_nCycle;
	CPicWnd * m_pPicWnd;
	CRect m_rectDefault;//Ĭ��λ��
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
