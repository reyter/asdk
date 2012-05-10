
// OTCHK_ClientView.h : COTCHK_ClientView ��Ľӿ�
//


#pragma once


class COTCHK_ClientView : public CFormView
{
protected: // �������л�����
	COTCHK_ClientView();
	DECLARE_DYNCREATE(COTCHK_ClientView)

public:
	enum{ IDD = IDD_OTCHK_CLIENT_FORM };

// ����
public:
	COTCHK_ClientDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~COTCHK_ClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // OTCHK_ClientView.cpp �еĵ��԰汾
inline COTCHK_ClientDoc* COTCHK_ClientView::GetDocument() const
   { return reinterpret_cast<COTCHK_ClientDoc*>(m_pDocument); }
#endif

