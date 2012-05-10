#pragma once


// CStockWnd ���
class CStockWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CStockWnd)
public:
	CStockWnd(CRect &c_rect,BOOL c_bModal,bool c_bTitle = true);
	CStockWnd();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CStockWnd();

protected:
	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnClose();
public:
	CWnd * m_pwndCtrl;
	BOOL	m_bModal;//�Ƿ���ģʽ��ʾ
public:
	void SetControlWnd(CWnd * m_pwndCtrl);
public:
	CWnd  * GetControlWnd(void);
public:
	CView *m_pView;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	int ShowUrl(CString c_strUrl);
public:
	// ��ǰ�õ�url
	CString m_strUrl;
    bool  m_state;
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    virtual void PostNcDestroy();
    
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    bool b_front;
};


