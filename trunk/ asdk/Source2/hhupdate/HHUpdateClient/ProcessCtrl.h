#pragma once
#include <TLHELP32.H>	//ö�ٽ���
#pragma comment(lib,"comctl32.lib")
#include <iostream>
#include <vector>
using namespace std;
#ifndef ListView_SetCheckState
#define ListView_SetCheckState(hwndLV, i, fCheck) \
	ListView_SetItemState(hwndLV, i, \
	INDEXTOSTATEIMAGEMASK((fCheck)+1), LVIS_STATEIMAGEMASK)
#endif
//------------------------------------------------------------------------------
//#define Msg(str) MessageBox(0,str,"Infomation",MB_OK|MB_ICONINFORMATION)
#define MAX_SIZE	512
#define NOR_SIZE	512
//#define DELAYTIME	2000
//------------------------------------------------------------------------------
typedef struct tag_ModulesInfo
{
	int		index;
	
	HMODULE	h;
	DWORD	size;
	char	path[MAX_SIZE];
	char	name[NOR_SIZE]; //������

	DWORD	pid;
	char	ProcessName[NOR_SIZE];
	char	ProcessPath[MAX_SIZE];
}MODULESINFO, *LPMODULESINFO;
typedef CList<MODULESINFO,MODULESINFO&> THELSMD;

typedef struct tag_ProcessInfo
{
	DWORD	pid;
	char	name[NOR_SIZE];
	char	path[MAX_SIZE];
}PROCESSINFO, *LPPROCESSINFO;
typedef CList<PROCESSINFO,PROCESSINFO&> THELIST;
class CProcessCtrl
{
public:
	CProcessCtrl(void);
	~CProcessCtrl(void);
public:
	//������ǰ����Ϊ Debug Ȩ�ޣ��ɹҽӡ�ǿɱϵͳ����
	bool EnableDebugPrivilege();
	void ClearAllData();
	void InitValue(PROCESSENTRY32 *pe);
	DWORD EnumProcess(LPCTSTR sTarget);
	THELIST	m_lsProcess;
	THELSMD m_lsProcessFiles;
};

