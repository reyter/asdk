#pragma once


// CTransCheckBox

class CTransCheckBox : public CButton
{
	DECLARE_DYNAMIC(CTransCheckBox)

public:
	CTransCheckBox();
	virtual ~CTransCheckBox();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

	LOGFONT   m_lf;    //
	CFont    m_font;         // 获取原有的文本的字体
};


