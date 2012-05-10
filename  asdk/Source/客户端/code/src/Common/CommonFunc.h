#ifndef CommonFunc_h__
#define CommonFunc_h__


#include <string>
#include <vector>
#include <io.h>
#include <boost\checked_delete.hpp>
#include <locale>
#include <atlstr.h>

//��ȡӦ�ó���ǰ·��
CString GetAppPath(void);

//�ͷ�����ļ�
BOOL CheckFileExist(const wchar_t* pszFile );

//��ȡ����ϵͳ�汾
CString GetOSVersion(void);

//��ȡ����ϵͳ����
CString GetOSLocale(void);

//��ȡ��ǰ�ͻ���ʹ�õ�����
CString GetLanguageType( void );

//��ȡ��ǰ������Դ�ļ�
CString	GetCurrentLanguageResource(void);

//��ȡ����������ļ�
CString GetAppSettingFile(void);

//��ȡ���������ļ�
CString GetProxyFile(void);

//��ȡ�������б������ļ�
CString GetSvrlistFile(void);

char * ExtractDirFromFullPath(char * path);

#endif // CommonFunc_h__
