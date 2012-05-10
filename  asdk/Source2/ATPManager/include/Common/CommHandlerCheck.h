#pragma  once

#ifndef _COMMHANDLERCHECK_H_
#define _COMMHANDLERCHECK_H_



#ifndef _SET_
#include <set>
using namespace std;
#endif


#include "CommErrorDefine.h"


/**
* 在类中声明 DECLARE_HANDLER_CHECK(CXxxxxx)
*/
#define DECLARE_HANDLER_CHECK(classname)\
private: \
	static set<classname*>  s_setHandlerCheck;\
public:\
	static bool	_IsValidHandler(LPVOID handler);


/**
* 在CPP中书写 IMPLEMENT_HANDLER_CHECK(CXxxxxx)
*/
#define IMPLEMENT_HANDLER_CHECK(classname)\
	set<classname*>	classname::s_setHandlerCheck;\
	bool	classname::_IsValidHandler(LPVOID handler)\
	{\
		return s_setHandlerCheck.find((classname*)handler)!=s_setHandlerCheck.end();\
	}\


/**
*  在构造函数中调用  ON_CREATE_HANDLER()
*/
#define ON_CREATE_HANDLER()		s_setHandlerCheck.insert(this);



/**
* 在析构函数数中调用  ON_DESTROY_HANDLER()
*/
#define ON_DESTROY_HANDLER()	s_setHandlerCheck.erase(this);


/**
* 检查句柄是否合法.
*/
#define IsValidHandler(classname,handler)	(classname::_IsValidHandler(handler))



/**
* 检查是否非法，并返回错误。
*/
#define IF_INVALID_HANDLER_RETURN(classname,handler)\
	if(!IsValidHandler(classname,handler))\
		return ERR_INVALIDHANDLER;


#endif //_COMMHANDLERCHECK_H_
