#pragma once

//应用程序名
#define  STR_OTCHK_CLIENT_NAME _T("OTCHK_Client")

//日志文件名
#define STR_LOG_NAME _T("log")

//////////////////////////////////////////////////////////////////////////
//注册表键值
//////////////////////////////////////////////////////////////////////////

//是否自动运行
#define REGKEY_AUTOSTARTUP  _T("SOFTWARE\\MicroSoft\\Windows\\CurrentVersion\\Run")
#define REGKEY_NAME_APP_NAME _T("otchk_client")

#define REGKEY_OTCSYS _T("SOFTWARE\\OTCHK\\Client")
#define REGNAME_SAVEACCOUNT _T("SaveAccount")//是否记住账号
#define REGNAME_SAVEPASSWORD _T("SavePassword")//是否保存密码
#define REGNAME_LASTACCOUNT _T("LastAccount") //上一次保存的账号
#define REGNAME_LANGUAGE _T("Language") //语言类型
#define REGNAME_ACCOUNT _T("Account") //账号

//////////////////////////////////////////////////////////////////////////
//报文编号
//
#define  REQID_LOGIN 3119





//////////////////////////////////////////////////////////////////////////
//全局对象

