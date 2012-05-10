
// OTCHK_ClientView.h : COTCHK_ClientView 类的接口
//


#pragma once


class COTCHK_ClientView : public CFormView
{
protected: // 仅从序列化创建
	COTCHK_ClientView();
	DECLARE_DYNCREATE(COTCHK_ClientView)

public:
	enum{ IDD = IDD_OTCHK_CLIENT_FORM };

// 属性
public:
	COTCHK_ClientDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~COTCHK_ClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // OTCHK_ClientView.cpp 中的调试版本
inline COTCHK_ClientDoc* COTCHK_ClientView::GetDocument() const
   { return reinterpret_cast<COTCHK_ClientDoc*>(m_pDocument); }
#endif

