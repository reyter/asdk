#pragma once

#ifdef _UTIAPILIB
#define UTIAPI(type)  type __declspec(dllexport) 
#else
#define UTIAPI(type)  type __declspec(dllimport) 
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
*	���׷���������.
*	@param lpszDllPath dll�ӿ��ļ�·��.
*	@param lpszIniPath ini�����ļ�·��.
*	@param pnDllType dll�ӿ��ļ�������.
*	@param hWnd ��־��ʾ�Ĵ��ھ��
*	@param lMessage ��־��Ϣ.
*	@param wParam ��־��Ϣ����
<table border="1">
<tr><td>1</td><td>֤ȯ���׽ӿ�.</td></tr>
<tr><td>2</td><td>�ڻ����׽ӿ�.</td></tr>
</table>
*	@return �����ɹ��򷵻�0,���򷵻�����ֵ.
*/
UTIAPI(int) UTI_Begin(LPCSTR lpszDllPath, LPCSTR lpszIniPath, int* pnDllType, HWND hWnd, long lMessage, int wParam);

/**
*	���ý��׽ӿ��������.
*	@param lpszDllPath dll�ӿ��ļ�·��.
*	@param lpszIniPath ini�����ļ�·��.
*	@return ���óɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_Set(LPCSTR lpszDllPath, LPCSTR lpszIniPath);

/**
*	���ÿͻ���IP��ַ��MAC��ַ.
*	@param lpszIPAddr dll�ӿ��ļ�·��.
*	@param lpszMacAddr ini�����ļ�·��.
*	@return ���óɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_SetIPMacAddr(LPCSTR lpszIPAddr, LPCSTR lpszMacAddr);

/**
*	���׷�����ֹͣ.
*	@return ֹͣ�ɹ��򷵻�0�����򷵻�����ֵ.
*/
UTIAPI(int) UTI_End();

/**
*	�ͷ��������ڴ������.
*	@param pData ���ݵ�ַָ��.
*/
UTIAPI(void) UTI_Release(void* pData);




typedef void (CALLBACK* UTI_LOG_FUN)(LPCTSTR,LPVOID);

/**
* ����UTI��־��¼
* @param pFun ��־��¼����
* @param lParam �ص�����־��¼�����Ĳ���
*/
UTIAPI(void) UTI_SetLogFun(UTI_LOG_FUN pFun,LPVOID lParam);


UTIAPI (int) GetPackSumData(char *pPackSum, int nPackSumSize, int nNumber);

#ifdef __cplusplus
}
#endif