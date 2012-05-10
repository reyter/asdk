/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 日志辅助函数
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-11-17		李伟		 创建
-------------------------------------------------------------
*/

//声明日志方法宏
#define DECLARE_COMMON_LOG_FUN(prefix,mode)\
	typedef void (CALLBACK* ##prefix##_LOG_FUN)(LPCTSTR,LPVOID);\
	mode(void) ##prefix##_SetLogFun(##prefix##_LOG_FUN pFun,LPVOID lParam);\
	

//声明日志方法使用的辅助内容
#define DECLARE_COMMON_LOG_HELPER(prefix)\
	extern prefix##_LOG_FUN __g_##prefix##LogFun;\
	extern LPVOID			 __g_##prefix##LogLParam;

//实现日志方法的辅助内容
#define IMPLEMENT_COMMON_LOG_HELPER(prefix)\
	prefix##_LOG_FUN __g_##prefix##LogFun=NULL;\
	LPVOID			 __g_##prefix##LogLParam=NULL;
	

//实现日志方法
#define IMPLEMENT_COMMON_LOG_FUN(prefix,mode)\
	mode(void) prefix##_SetLogFun(##prefix##_LOG_FUN pFun,LPVOID lParam)\
	{\
		__g_##prefix##LogFun = pFun;\
		__g_##prefix##LogLParam = lParam;\
	}


//记录日志
#define LOG_COMMON(prefix,lpLog)\
	if(__g_##prefix##LogFun)\
	{\
		(*__g_##prefix##LogFun)(lpLog,__g_##prefix##LogLParam);\
	}

/**
* 是否为空指针.
*/
#define IsNullCommLogFun(prefix) (__g_##prefix##LogFun)