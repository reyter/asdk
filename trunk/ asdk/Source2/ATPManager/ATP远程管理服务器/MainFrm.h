
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once


class CMainFrame : public CHHMainFrame
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)
	DECLARE_MENUXP()

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	//CStatusBar        m_wndStatusBar;
	//CChildView    m_wndView;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClose();
//	afx_msg BOOL OnQueryOpen();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};


