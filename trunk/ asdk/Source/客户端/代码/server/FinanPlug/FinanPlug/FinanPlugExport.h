//FinanPlugExport.h
#ifndef _FINANPLUGEXPORT_H_
#define _FINANPLUGEXPORT_H_

#ifdef _DLL
#define FINPLUGAPI __declspec(dllexport)
#else
#define FINPLUGAPI __declspec(dllimport)
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SMsgID
{
	unsigned int m_unID;
	unsigned int m_unSocket;
};


typedef int (*_SendReply)( SMsgID* c_pMsgID, char* c_pBuf, int c_iLen);
typedef int (*_IsUserOnline)(int);
typedef int (*_WriteOut)(char *,char *,int,int);
typedef void (*_PlugQuit)(unsigned int c_unPlugID);

/**********************************************************************
Function  : ��ʼ��
c_unPlugID:	ƽ̨������˲����ID��
return    : 0��ʾ�ɹ�������ʧ��
***********************************************************************/
extern "C" FINPLUGAPI int _OnInit(unsigned int c_unPlugID,const char * c_pParam);

/**********************************************************************
Function  : �������
c_unPlugID:	
return    : 
***********************************************************************/
extern "C" FINPLUGAPI void _OnRelease();

/**********************************************************************
Function  : ��Ӧ���ݸ��´���(Ҫ���첽��������ڵõ����ݺ���������)
c_pBuf    :	�������ݸ��µ���Ŀ
c_iLen    :	c_pBuf����Ч����
return    : 0��ʾ�ɹ�������ʧ��
***********************************************************************/
extern "C" FINPLUGAPI int _OnUpdateData(char * c_pBuf,int c_iLen);

/**********************************************************************
Function  : ��Ӧ�ⲿ����(�첽������������)
c_pMsgID  :	�����ʶ�������Ҫ���ƴ˽ṹ���ݣ���������ָ�룬
            �ڴ�����ɺ���Ӧ��ʱ��Ҫ���������ͻ�
c_pBuf    :	��������
c_iLen    :	c_pBuf����Ч����
return    : 0��ʾ�ɹ�������ʧ��
***********************************************************************/
extern "C" FINPLUGAPI int _OnRequest(SMsgID * c_pMsgID,char * c_pBuf,int c_iLen);

/**********************************************************************
Function  : ��Ӧ�ⲿ����(ͬ��������������)
c_pBuf    :	��������
c_iLen    :	c_pBuf����Ч����
c_pRetBuf :	��������
c_nRetMaxLen:��󷵻س���
return    : ����0��ʾ�������ݳ��ȣ�����ʧ��
***********************************************************************/
extern "C" FINPLUGAPI int _DoRequest(char* c_pBuf, int c_iLen,char * c_pRetBuf,int c_nRetMaxLen);

/**********************************************************************
Function  : ����Ӧ��
c_pFunc   :	����ָ��
            typedef int (*_SendReply)( SMsgID * c_pMsgID,char * c_pBuf,int c_iLen);
			c_pMsgID: �����ʶ����OnRequestʱ����������
            c_pBuf  : �������ݣ�ָ��һ���������ݵ�Ԫ
            c_iLen  : �������ݳ���
return    :
***********************************************************************/
extern "C" FINPLUGAPI void _OnSocketClose(unsigned int c_unID,unsigned int c_unSocket);

/**********************************************************************
Funciton  :���ӶϿ�����
***********************************************************************/
extern "C" FINPLUGAPI void _Set_SendReplay(_SendReply c_pFunc);
extern "C" FINPLUGAPI void _Set_IsUserOnline(_IsUserOnline c_pFunc);
extern "C" FINPLUGAPI void _Set_WriteOut(_WriteOut c_pFunc);

/**********************************************************************
Function  : ֪ͨ�˳�
c_pFunc   :	����ָ��
            typedef void (*_PlugQuit)(unsigned int c_unPlugID);
			c_unPlugID: ƽ̨������˲����ID��
return    :
***********************************************************************/
extern "C" FINPLUGAPI int _GetNewsDirect(unsigned int *c_punCode,unsigned int c_unCount,char * c_pOutBuf,int c_nMaxLen,int c_nType);
/**********************************************************************
Function	:ֱ��ȡ����
unsigned int	* c_punCode;	��Ʊ����ҵ��������
unsigned int	  c_unCount		����
char			* c_pOutBuf		���������
int				  c_nMaxLen		��������󳤶�
return			  ����ռ�û���������
***********************************************************************/

extern "C" FINPLUGAPI void _Set_PlugQuit(_PlugQuit c_pFunc);

extern "C" FINPLUGAPI void GetModuleVer(char** pBuf);

extern "C" FINPLUGAPI float* _Calc_Ma(float * c_fRet,float* c_fValue,int c_nCount,unsigned short c_usNum);
extern "C" FINPLUGAPI float* _Calc_Ema(float*fRet,float*fPa,int c_nCount,int c_num);
extern "C" FINPLUGAPI float* _Calc_Sma(float*fRet,float*fPa,int c_nCount,int c_num,int c_nWeight);
extern "C" FINPLUGAPI float * _Calc_Std(float*fRet,float*fPa,int c_nItemCount,short c_sNum);       //�����׼��


////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif