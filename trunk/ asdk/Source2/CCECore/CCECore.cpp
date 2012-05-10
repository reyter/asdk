// CCECore.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "CCEDefine.h"
#include "HHWPIOCP.h"
#include "ChannelManager.h"

CCE_LOG_FUN   g_pCCELogFun = NULL ;
LPVOID		  g_pCCELogParam=NULL;

void AppendLog(const char* pLog)
{
	if(g_pCCELogFun)
	{
		(*g_pCCELogFun)(pLog,g_pCCELogParam);
	}
}

static AFX_EXTENSION_MODULE CCECoreDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// ���ʹ�� lpReserved���뽫���Ƴ�
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("CCECore.DLL ���ڳ�ʼ����\n");
		
		// ��չ DLL һ���Գ�ʼ��
		if (!AfxInitExtensionModule(CCECoreDLL, hInstance))
			return 0;

		// ���� DLL ���뵽��Դ����
		// ע��: �������չ DLL ��
		//  MFC ���� DLL(�� ActiveX �ؼ�)��ʽ���ӵ�
		//  �������� MFC Ӧ�ó������ӵ�������Ҫ
		//  �����д� DllMain ���Ƴ������������һ��
		//  �Ӵ���չ DLL �����ĵ����ĺ����С�ʹ�ô���չ DLL ��
		//  ���� DLL Ȼ��Ӧ��ʽ
		//  ���øú����Գ�ʼ������չ DLL������
		//  CDynLinkLibrary ���󲻻ḽ�ӵ�
		//  ���� DLL ����Դ���������������ص�
		//  ���⡣

		new CDynLinkLibrary(CCECoreDLL);

		// �׽��ֳ�ʼ��
		// ע��: �������չ DLL ��
		//  MFC ���� DLL(�� ActiveX �ؼ�)��ʽ���ӵ���
		//  �������� MFC Ӧ�ó������ӵ�������Ҫ
		//  �������д� DllMain ���Ƴ��������Ƿ�����һ��
		//  �Ӵ���չ DLL �����ĵ����ĺ����С�ʹ�ô���չ DLL ��
		//  ���� DLL Ȼ��Ӧ��ʽ����
		//  �ú����Գ�ʼ������չ DLL��
		if (!AfxSocketInit())
		{
			return FALSE;
		}
		//��Ӧ��֮ʱ���ٳ�ʱ����
		//CHHWPIOCP::Init();	
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("CCECore.DLL ������ֹ��\n");
		CChannelManager::UnInit();
		CHHWPIOCP::UnInit();

		// �ڵ�����������֮ǰ��ֹ�ÿ�
		AfxTermExtensionModule(CCECoreDLL);
	}
	return 1;   // ȷ��
}
