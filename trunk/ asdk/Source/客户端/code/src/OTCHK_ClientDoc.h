
// OTCHK_ClientDoc.h : COTCHK_ClientDoc ��Ľӿ�
//


#pragma once


class COTCHK_ClientDoc : public CDocument
{
protected: // �������л�����
	COTCHK_ClientDoc();
	DECLARE_DYNCREATE(COTCHK_ClientDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~COTCHK_ClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


