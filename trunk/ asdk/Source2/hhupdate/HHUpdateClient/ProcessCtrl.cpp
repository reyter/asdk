#include "StdAfx.h"
#include "ProcessCtrl.h"
#pragma warning(disable:4996)
CProcessCtrl::CProcessCtrl(void)
{
}

CProcessCtrl::~CProcessCtrl(void)
{
	ClearAllData();
}

bool CProcessCtrl::EnableDebugPrivilege()
{
	HANDLE	hToken = NULL;
	LUID	luid;
	TOKEN_PRIVILEGES tkp; //令牌权限结构

	if( !OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES,&hToken) )
	{
		//printf("OpenProcessToken failed\n");
		return false;
	}
	if( !LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&luid) ) //查询 DEBUG 权限值
	{
		return false;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = luid;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; //权限属性使能
	//调整为 DEBUG 权限
	if( !AdjustTokenPrivileges(hToken,false,&tkp,sizeof(tkp),NULL,NULL) )
	{
		return false;
	}
	CloseHandle( hToken ); 
	return true;
}

DWORD CProcessCtrl::EnumProcess(LPCTSTR sTarget)
{
	//枚举进程
	if( NULL==sTarget ) InitValue( NULL );

    DWORD dwRet = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS,0 );
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof( PROCESSENTRY32 );
    Process32First( hSnapshot, &pe32 );
    do
    {
		
		/*
		if( NULL!=sTarget )
		{
			if( lstrcmpi(pe32.szExeFile,sTarget)==0 )
			{
				dwRet = pe32.th32ProcessID;
				break;
			}
		}
		else
		*/
		{
			InitValue(&pe32);	
		}
    } while ( Process32Next( hSnapshot, &pe32 ) );
    CloseHandle( hSnapshot );
    return dwRet;
}

void CProcessCtrl::InitValue(PROCESSENTRY32 *pe)
{
	if( NULL==pe ) 
	{
		ClearAllData();
		return;
	}
	//
	bool bCopy = false;

	PROCESSINFO pProcessInfo; 
	memset( (void*)&pProcessInfo,0,sizeof(pProcessInfo) );
	pProcessInfo.pid	= pe->th32ProcessID;
	strcpy( pProcessInfo.name,pe->szExeFile );	

	if( pProcessInfo.pid==0 )
	{
		return;
		//strcpy( pProcessInfo.path,"System Idle Process" );	
	}
	else if( pProcessInfo.pid==4 )
	{
		return;
		//strcpy( pProcessInfo.path,"System" );
	}
	else
	{	
		bCopy = true;
	}
	
	MODULESINFO m;
	memset( (void*)&m,0,sizeof(MODULESINFO) );
	HANDLE hSnapshot;
	MODULEENTRY32 md32;
	hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE,pProcessInfo.pid );
	md32.dwSize = sizeof(MODULEENTRY32);
	Module32First( hSnapshot,&md32 ); 
	if(bCopy) 
	{
		strcpy( pProcessInfo.path,md32.szExePath );
	}

	m.pid = pProcessInfo.pid;
	strcpy(m.ProcessName,pProcessInfo.name);
	strcpy(m.ProcessPath,pProcessInfo.path);
	char szFileName[MAX_PATH]={0};
	GetModuleFileName(NULL,szFileName,MAX_PATH);
	char *ptr=NULL,c='\\';
	ptr = strrchr(szFileName,c);

	//不保存360，卡巴斯基 等相关信息
	if (strcmpi(pProcessInfo.name,"svchost.exe")==0 
		|| strcmpi(pProcessInfo.name,"360tray.exe") ==0
		|| strcmpi(pProcessInfo.name,"avp.exe")==0
		|| strcmpi(pProcessInfo.name,"chrome.exe")==0
		|| strcmpi(pProcessInfo.name,"winlogon.exe")==0
		|| strcmpi(pProcessInfo.name,"iexplore.exe")==0
		|| strcmpi(pProcessInfo.name,"services.exe")==0
		|| strcmpi(pProcessInfo.name,"smss.exe")==0
		|| strcmpi(pProcessInfo.name,&ptr[1])==0)
	{
		return;
	}

	do
	{
		m.index= m_lsProcessFiles.GetCount() + 1;
		m.h	   = md32.hModule;
		m.size = md32.modBaseSize/1024;
		strcpy( m.path,md32.szExePath );
		strcpy( m.name,md32.szModule );
		strupr(md32.szExePath);
		if (!strstr(md32.szExePath,"C:\\WINDOWS\\SYSTEM32"))
		{
			if (!strstr(md32.szExePath,"360\\360SAFE"))
			{
				if (!strstr(md32.szExePath,"C:\\WINDOWS\\WINSXS"))
				{
					m_lsProcessFiles.AddTail( m );
					TRACE1("%s\n",md32.szExePath);
				}
				
			}
			
		}
		else
		{
			int hh =0;
			hh = 88;
		}
		
		ASSERT(_CrtCheckMemory());
	} while ( Module32Next( hSnapshot, &md32 ) );
	CloseHandle( hSnapshot );

	

	m_lsProcess.AddTail( pProcessInfo );

}

void CProcessCtrl::ClearAllData()
{

	if (m_lsProcessFiles.GetCount()>0)
	{	
		m_lsProcessFiles.RemoveAll();
	}
		

	if (m_lsProcess.GetCount()>0)
	{
		m_lsProcess.RemoveAll();
	}
}