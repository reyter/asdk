#pragma once

class COTCBaseObject
{
public:
	COTCBaseObject(void);
	~COTCBaseObject(void);

public:
	//************************************
	// Method:    LoadMultiLanguage
	// FullName:  COTCBaseObject::LoadMultiLanguage
	// Access:    virtual public 
	// Returns:   void
	// Description:�л��������
	// Parameter: void
	//************************************
	virtual void LoadMultiLanguage(void) = 0;
};
