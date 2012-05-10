#pragma once


// CKindComboBox

class CKindComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CKindComboBox)

public:
	CKindComboBox();
	virtual ~CKindComboBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


