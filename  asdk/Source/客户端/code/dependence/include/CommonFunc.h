#pragma once


#include <string>
#include <vector>
#include <io.h>
#include <boost\checked_delete.hpp>
#include <locale>
#include <atlstr.h>
#include <Windows.h>


	//��ȡӦ�ó���ǰ·��
	CString GetAppPath(void);

	//�ͷ�����ļ�
	BOOL IsFileExists(const wchar_t* pszFile );

	//��ȡ����ϵͳ�汾
	CString GetOSVersion(void);

	//��ȡ����ϵͳ����
	CString GetOSLocale(void);


