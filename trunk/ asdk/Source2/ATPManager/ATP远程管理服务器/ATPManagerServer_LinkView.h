#pragma once
#include "HHNetFrameProcessor_LinkView.h"
#include "WndBGS.h"
// CATPManagerServer_LinkView ��ͼ





class CATPManagerServer_LinkView : public CHHNetFrameProcessor_LinkView
{
	DECLARE_DYNCREATE(CATPManagerServer_LinkView)

protected:
	CATPManagerServer_LinkView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CATPManagerServer_LinkView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	void OnOpenUserDocument(CString strUserDocumentPath, CString strUserDocumentName);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	
	
	
};


