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
Function  : 初始化
c_unPlugID:	平台分配给此插件的ID号
return    : 0表示成功，否则失败
***********************************************************************/
extern "C" FINPLUGAPI int _OnInit(unsigned int c_unPlugID,const char * c_pParam);

/**********************************************************************
Function  : 清理操作
c_unPlugID:	
return    : 
***********************************************************************/
extern "C" FINPLUGAPI void _OnRelease();

/**********************************************************************
Function  : 响应数据更新处理(要求异步处理，插件在得到数据后，立即返回)
c_pBuf    :	本次数据更新的项目
c_iLen    :	c_pBuf的有效长度
return    : 0表示成功，否则失败
***********************************************************************/
extern "C" FINPLUGAPI int _OnUpdateData(char * c_pBuf,int c_iLen);

/**********************************************************************
Function  : 响应外部请求(异步处理，立即返回)
c_pMsgID  :	请求标识，插件需要复制此结构内容，不允许保留指针，
            在处理完成后在应答时需要将此内容送回
c_pBuf    :	请求内容
c_iLen    :	c_pBuf的有效长度
return    : 0表示成功，否则失败
***********************************************************************/
extern "C" FINPLUGAPI int _OnRequest(SMsgID * c_pMsgID,char * c_pBuf,int c_iLen);

/**********************************************************************
Function  : 响应外部请求(同步处理，立即返回)
c_pBuf    :	请求内容
c_iLen    :	c_pBuf的有效长度
c_pRetBuf :	返回数据
c_nRetMaxLen:最大返回长度
return    : 大于0表示返回数据长度，否则失败
***********************************************************************/
extern "C" FINPLUGAPI int _DoRequest(char* c_pBuf, int c_iLen,char * c_pRetBuf,int c_nRetMaxLen);

/**********************************************************************
Function  : 发送应答
c_pFunc   :	函数指针
            typedef int (*_SendReply)( SMsgID * c_pMsgID,char * c_pBuf,int c_iLen);
			c_pMsgID: 请求标识，在OnRequest时候复制下来的
            c_pBuf  : 返回内容，指向一个行情数据单元
            c_iLen  : 返回数据长度
return    :
***********************************************************************/
extern "C" FINPLUGAPI void _OnSocketClose(unsigned int c_unID,unsigned int c_unSocket);

/**********************************************************************
Funciton  :连接断开处理
***********************************************************************/
extern "C" FINPLUGAPI void _Set_SendReplay(_SendReply c_pFunc);
extern "C" FINPLUGAPI void _Set_IsUserOnline(_IsUserOnline c_pFunc);
extern "C" FINPLUGAPI void _Set_WriteOut(_WriteOut c_pFunc);

/**********************************************************************
Function  : 通知退出
c_pFunc   :	函数指针
            typedef void (*_PlugQuit)(unsigned int c_unPlugID);
			c_unPlugID: 平台分配给此插件的ID号
return    :
***********************************************************************/
extern "C" FINPLUGAPI int _GetNewsDirect(unsigned int *c_punCode,unsigned int c_unCount,char * c_pOutBuf,int c_nMaxLen,int c_nType);
/**********************************************************************
Function	:直接取新闻
unsigned int	* c_punCode;	股票和行业编码数组
unsigned int	  c_unCount		个数
char			* c_pOutBuf		输出缓冲区
int				  c_nMaxLen		缓冲区最大长度
return			  返回占用缓冲区长度
***********************************************************************/

extern "C" FINPLUGAPI void _Set_PlugQuit(_PlugQuit c_pFunc);

extern "C" FINPLUGAPI void GetModuleVer(char** pBuf);

extern "C" FINPLUGAPI float* _Calc_Ma(float * c_fRet,float* c_fValue,int c_nCount,unsigned short c_usNum);
extern "C" FINPLUGAPI float* _Calc_Ema(float*fRet,float*fPa,int c_nCount,int c_num);
extern "C" FINPLUGAPI float* _Calc_Sma(float*fRet,float*fPa,int c_nCount,int c_num,int c_nWeight);
extern "C" FINPLUGAPI float * _Calc_Std(float*fRet,float*fPa,int c_nItemCount,short c_sNum);       //估算标准差


////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif