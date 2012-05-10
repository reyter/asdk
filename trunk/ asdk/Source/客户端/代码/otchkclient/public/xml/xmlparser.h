
#ifndef __TIXML_PARSER_H__
#define __TIXML_PARSER_H__

#include "tinyxml.h"

class TiXmlParser : public TiXmlDocument
{
protected:
	enum NODEWAY {ENTER, LEAVE};
public:
	void Read(const char *lpXmlText)
	{
		Parse(lpXmlText);
		TiXmlElement *pRootElm = RootElement();
		ParseNode(pRootElm, NULL);
	}

	void Load(const char *lpFile)
	{
		LoadFile(lpFile);
		TiXmlElement *pRootElm = RootElement();
		
		ParseNode(pRootElm, NULL);
	}
	void Save(const char *lpFile)
	{
		TiXmlElement *pRootElm = RootElement();
		TiXmlDocument * pDoc = pRootElm->GetDocument();
		pDoc->SaveFile(lpFile);
	}
	virtual void OnNode(TiXmlElement *pElm, NODEWAY way) {};
	virtual void* OnNode(std::string NodeName, void *lParam) = 0;
	virtual void OnText(std::string NodeName, std::string NodeText, void *lParam) = 0;
	virtual void OnAttr(std::string NodeName, std::string AttrName, std::string AttrText, void *lParam) = 0;

private:
	void ParseNode(TiXmlElement *pElm, void *lParam)
	{
		if (!pElm)
			return;
		OnNode(pElm, ENTER);

		TiXmlAttribute *pAttr = pElm->FirstAttribute();
		while (pAttr)
		{
			OnAttr(pElm->Value(), pAttr->Name(), pAttr->Value(), lParam);
			pAttr = pAttr->Next();
		}

		void *lpSubParam = NULL;
		TiXmlElement *pNextElm = NULL;
		lpSubParam = OnNode(pElm->Value(), lParam);
		if (pElm->GetText())
			OnText(pElm->Value(), pElm->GetText(), lParam);

		pNextElm = pElm->FirstChildElement();
		ParseNode(pNextElm, lpSubParam);
		pNextElm = pElm->NextSiblingElement();
		ParseNode(pNextElm, lParam);

		OnNode(pElm, LEAVE);
	}
};

#endif
