#pragma  once

#ifndef _COMMHANDLERCHECK_H_
#define _COMMHANDLERCHECK_H_



#ifndef _SET_
#include <set>
using namespace std;
#endif


#include "CommErrorDefine.h"


/**
* ���������� DECLARE_HANDLER_CHECK(CXxxxxx)
*/
#define DECLARE_HANDLER_CHECK(classname)\
private: \
	static set<classname*>  s_setHandlerCheck;\
public:\
	static bool	_IsValidHandler(LPVOID handler);


/**
* ��CPP����д IMPLEMENT_HANDLER_CHECK(CXxxxxx)
*/
#define IMPLEMENT_HANDLER_CHECK(classname)\
	set<classname*>	classname::s_setHandlerCheck;\
	bool	classname::_IsValidHandler(LPVOID handler)\
	{\
		return s_setHandlerCheck.find((classname*)handler)!=s_setHandlerCheck.end();\
	}\


/**
*  �ڹ��캯���е���  ON_CREATE_HANDLER()
*/
#define ON_CREATE_HANDLER()		s_setHandlerCheck.insert(this);



/**
* �������������е���  ON_DESTROY_HANDLER()
*/
#define ON_DESTROY_HANDLER()	s_setHandlerCheck.erase(this);


/**
* ������Ƿ�Ϸ�.
*/
#define IsValidHandler(classname,handler)	(classname::_IsValidHandler(handler))



/**
* ����Ƿ�Ƿ��������ش���
*/
#define IF_INVALID_HANDLER_RETURN(classname,handler)\
	if(!IsValidHandler(classname,handler))\
		return ERR_INVALIDHANDLER;


#endif //_COMMHANDLERCHECK_H_
