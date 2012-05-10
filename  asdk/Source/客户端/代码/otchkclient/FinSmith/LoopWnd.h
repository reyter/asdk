#pragma once


// CLoopWnd

class CLoopWnd : public CFrameWnd
{
	DECLARE_DYNAMIC(CLoopWnd)

public:
	CLoopWnd();
	virtual ~CLoopWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_nTime;
	CString m_strInfo;
	void Begin(CString);
	void End(void);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


