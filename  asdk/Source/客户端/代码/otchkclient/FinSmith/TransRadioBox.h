#pragma once


// CTransRadioBox

class CTransRadioBox : public CButton
{
	DECLARE_DYNAMIC(CTransRadioBox)

public:
	CTransRadioBox();
	virtual ~CTransRadioBox();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

	LOGFONT   m_lf;    //
	CFont    m_font;         // 获取原有的文本的字体
};


