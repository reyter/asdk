#pragma once
#ifndef _LOGAPIHELPER_H_
#define _LOGAPIHELPER_H_

/*
1������LOG_CreateHandler����������
2������LOG_SetDeveloper��LOG_SetFileVersion���ÿ����ߣ��汾��
3������LOG_OpenFile�򿪻��ߴ�����������־�ļ�
4������LOG_SetLogTimer��ʱ�ѻ���������д���ļ�
5������LOG_AppendLogInfoToBuffer׷�ӵ�������
6���ڳ����˳�֮ǰ����LOG_LogProcStart�ѻ���������д���ļ�(ƽʱ���Բ���)

��ʹ��ʱ������LOG_KillLogTimer��LOG_CloseFile��LOG_DestroyHandler
�رն�ʱ�����ر��ļ������ٴ���������
*/

#include "LOGApiDefine.h"

#ifdef _LOGAPILIB
	#define LOGAPI(type) type __declspec(dllexport)
#else
	#define LOGAPI(type) type __declspec(dllimport)
#endif

#pragma  pack(push,1)

#ifdef __cplusplus
extern "C"
{
#endif


/**
*	LOG���������
*/
typedef void* HLOG;

/**
*	����һ�����������
*	@param szLogName  ��־����
*   @param pHLog	  [0ut] ����򿪵ľ��.
*	@return �����������Ĵ�����
*/
LOGAPI(int) LOG_OpenLog(LPCTSTR szLogName,HLOG* pHLog);

/**
*  �Ƿ��¼ĳһ����־.ȱʡ����¼���������־.
*  @param hLogger ��־��¼���.
*  @param nClass  ��־���.
*  @param bEnable �Ƿ�����.
*/
LOGAPI(int) LOG_EnableLogClass(HLOG hLogger,int nClass,bool bEnable);

/**
*  д����־���ַ�����
*  @param hLogger ��־��¼���.
*  @param nClass  ��־���.
*  @param lpszLog Ҫ��¼��־�ַ���.
*/
LOGAPI(int) LOG_LogString(HLOG hLogger,int nClass,LPCTSTR lpszLog);

/**
*  д����־��ԭʼ�����ƣ�
*  @param hLogger ��־��¼���.
*  @param nClass  ��־���.
*  @param pLog	  �����׵�ַ
*  @param nLength ���ݳ���
*/
LOGAPI(int) LOG_LogRaw(HLOG hLogger,int nClass,const void* pLog,int nLength);


/**
*  ����д����־�����С����־��ȡ��ʱ��ȱʡ1���֣�������(ȱʡ64k)���Ʊ��棬��
*  @param hLogger ��־��¼���.
*  @param nLogBufferSize �»����С
*  @return ����ԭ���Ļ����С.
*/
LOGAPI(size_t) LOG_SetLogBufferSize(HLOG hLogger,size_t nLogBufferSize);

/**
*  ����д����־����д��������־��ȡ��ʱ��ȱʡ1���֣�������(ȱʡ64k)���Ʊ��棬��
*  @param hLogger		 ��־��¼���.
*  @param dwMillSeconds  �¼��
*  @return ����ԭ���ļ��
*/
LOGAPI(DWORD) LOG_SetLogTimer(HLOG hLogger,DWORD dwMilliseconds);

/**
*  ǿ�ƽ��þ���ϵĻ���д������ļ���
*  @param hLogger		 ��־��¼���.
*/
LOGAPI(int) LOG_Commit(HLOG hLogger);

/**
*  �ر���־
*  @param hLogger		 ��־��¼���.
*/
LOGAPI(int) LOG_CloseLog(HLOG hLogger);

/**
* ���ش�������.
*/
LOGAPI(LPCTSTR) LOG_GetError(int nErrorCode);

/**
* �����ִ���־�۲촰��
*  WPARAM  �������������־��š�
*  LPARAM  NULL.
*  @param hLogger		 ��־��¼���.
*  @param hWnd			 ���ڱ����
*  @param nMessageID     ��ϢID.
*  @param bEnable        �Ƿ�۲�.
*/
LOGAPI(int)    LOG_EnableWatchWindow(HLOG hLogger,HWND hWnd,int nMessageID,bool bEnable);

/**
* ��ȡָ������ϵ���־��¼��.
* @param hLogger ��־��¼���.
* @param pnCount [out] �����־��
* @return        0 ��������������Ϊ������.���� LOG_GetError() ��ʽ��.
*/
LOGAPI(int)    LOG_GetLogCount(HLOG hLogger,size_t* pnCount);

/**
* ��ȡָ������ϵ�ָ����ŵ���־* .
* @param hLogger ��־��¼���.
* @param nSN ���(��1��ʼ).
* @param pHead [out] �����־�����Ϣ.
* @param ppLog  [out] �����־���ݣ� ����� LOG_Release(*ppLog) �ͷ���Ӧ���ڴ�
* @return        0 ��������������Ϊ������.���� LOG_GetError() ��ʽ��.
*/
LOGAPI(int)    LOG_GetLog(HLOG hLogger,int nSN,LogRecordHead* pHead,void** ppLog);

/**
* �ͷ��ڴ�
*/
LOGAPI(void)    LOG_Release(void* pData);



enum LOG_DATA_TYPE
{
	LDT_STRING =1,		//�ַ���char*
	LDT_BINARAY = 2		//����������
};

/**
* д��־�ص�ԭ��.
*/
typedef void (CALLBACK* LOGHOOK_FUN)(HLOG /*hLogger*/,
	LOG_DATA_TYPE /*nType*/,
	int /*nClass*/,
	const void* /*pData*/,
	int /*nLength*/);

/**
* ����д��־����
*/
LOGAPI(void)	LOG_SetLogHook(HLOG hLogger,LOGHOOK_FUN pHook);


#ifdef __cplusplus
}
#endif


#pragma  pack(pop)

#endif //_LOGAPIHELPER_H_