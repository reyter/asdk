#ifndef MultiLanguage_h__
#define MultiLanguage_h__

#include <map>
#include <string>

typedef std::map<std::wstring,std::wstring> CIDS2StringMap;

class CMultiLanguage
{
public:
	CMultiLanguage(void);
	~CMultiLanguage(void);
	static CMultiLanguage& GetInstance(void);

public:
	bool LoadResources(void);
	std::wstring LoadWString(std::wstring strIDS);

private:
	CIDS2StringMap m_mapIDS2String;
	static CMultiLanguage m_Instance;	
};



#endif // MultiLanguage_h__
