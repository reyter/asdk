/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 ��־��������
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-11-17		��ΰ		 ����
-------------------------------------------------------------
*/

//������־������
#define DECLARE_COMMON_LOG_FUN(prefix,mode)\
	typedef void (CALLBACK* ##prefix##_LOG_FUN)(LPCTSTR,LPVOID);\
	mode(void) ##prefix##_SetLogFun(##prefix##_LOG_FUN pFun,LPVOID lParam);\
	

//������־����ʹ�õĸ�������
#define DECLARE_COMMON_LOG_HELPER(prefix)\
	extern prefix##_LOG_FUN __g_##prefix##LogFun;\
	extern LPVOID			 __g_##prefix##LogLParam;

//ʵ����־�����ĸ�������
#define IMPLEMENT_COMMON_LOG_HELPER(prefix)\
	prefix##_LOG_FUN __g_##prefix##LogFun=NULL;\
	LPVOID			 __g_##prefix##LogLParam=NULL;
	

//ʵ����־����
#define IMPLEMENT_COMMON_LOG_FUN(prefix,mode)\
	mode(void) prefix##_SetLogFun(##prefix##_LOG_FUN pFun,LPVOID lParam)\
	{\
		__g_##prefix##LogFun = pFun;\
		__g_##prefix##LogLParam = lParam;\
	}


//��¼��־
#define LOG_COMMON(prefix,lpLog)\
	if(__g_##prefix##LogFun)\
	{\
		(*__g_##prefix##LogFun)(lpLog,__g_##prefix##LogLParam);\
	}

/**
* �Ƿ�Ϊ��ָ��.
*/
#define IsNullCommLogFun(prefix) (__g_##prefix##LogFun)