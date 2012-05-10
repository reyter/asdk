#ifndef GlobalMacro_h__
#define GlobalMacro_h__
#include <boost/checked_delete.hpp>


//通用返回值定义

#define RETVAL_SUCCESS 1 //返回成功
#define RETVAL_ERROR 0     //返回失败


//设置界面字符串
#define STR_LOADSTRING(IDS)			(CMultiLanguage::GetInstance().LoadWString(IDS).c_str())
#define CTRL_LOADSTRING(IDC)	(GetDlgItem(IDC)->SetWindowText(STR_LOADSTRING(L#IDC)))
#define DLG_LOADSTRING(IDD)	(SetWindowText(STR_LOADSTRING(L#IDD)))

//资源回收
#define  __DELETE_OBJECT(ptrOBJ)\
{\
	if (NULL != ptrOBJ)\
	{\
		boost::checked_delete(ptrOBJ);\
		ptrOBJ = NULL;\
	}\
}\

#define __DELETE_ARRAY_OBJECT(ptrARRAY)\
{\
	if (NULL != ptrARRAY)\
	{\
		boost::checked_array_delete(ptrARRAY);\
		ptrARRAY = NULL;\
	}\
}\

#define  __FREE_OBJECT(ptrOBJ)\
{\
	if (NULL != ptrOBJ)\
	{\
	free((void*)ptrOBJ);\
	ptrOBJ = NULL;\
	}\
}\


#endif // GlobalMacro_h__