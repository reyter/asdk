/**
*@Copyright �����д���Ƽ����޹�˾(www.hh.com.cn)
*@System	 ����㷨����ƽ̨ϵͳ
*@Brief	 TTD-API
*@Author	 ������
*@Date      2010-10-15
*
*	��Ʊ����API.
*	���ȵ���Begin������ʼ���繤��.
*	Ȼ���¼������.
*	�ڿͻ���׼��������,�ɵ���TTD_SEC_StartPush��������
*	֮����Է���������ָ���Ĳ�������,����������Ӧ���,
*	�⽫�������Ӧ�Ļص�����.
*	����ʱ����TTD_SEC_Release�ͷ���TTD������ڴ�,Ȼ����TTD_SEC_End��ֹTTD�Ĺ���..	
*/
#pragma once

#include "../Include/utiapi/utidefine_sec.h"
#include "../include/Protocol/tdprotocolcommon.h"
#include "../include/Protocol/TDSECProtocol.h"
#include "../Include/utiapi/utidefine.h"



#ifdef _TTDAPILIB
#define TTDAPI(type)  type __declspec(dllexport) 
#else
#define TTDAPI(type)  type __declspec(dllimport) 
#endif

#ifdef __cplusplus
extern "C"
{
#endif


#ifndef __TTDAPILIB_TYPE_DEFINE__
#define __TTDAPILIB_TYPE_DEFINE__

	/**
	*	�����¼�����.
	*/
	enum TTD_NETEVENT_TYPE
	{
		TTD_NETEVENT_CONNECTED,		//�����Ϸ�������.
		TTD_NETEVENT_DISCONNECTED	//�Ͽ�������������.
	};

	/**
	*	�����¼��ص�����ԭ��.
	*	@param	uType	�����¼�����.
	*	@return ��������bool,����false�򲻻�ɾ���������Ӷ���
	*/
	typedef bool (CALLBACK *ON_TTD_NET_EVENT)(TTD_NETEVENT_TYPE uType);

	/**
	 *  ���յ�����TDF�����������ݻص�֪ͨ����
	*	@param handler  ������.
	*	@param pHead ��Ϣͷ, ��Ϣͷ�г��õ����ݳ�Ա sDataType �� nTime .
	*				 sDataType ָ���������ͣ�����Ĳ���������sDataType��ǿ��ת��Ϊ��Ӧ�Ľṹ.
	*				 nTime     Ϊ�������������ݵĻ���ʱ��,��ʽΪ HHMMSSmmm.
	*	@param pApplicationHead  Ӧ��ͷ��ͨ��ָ���������ݵ�����\��ʶ\��¼���ȡ�ĳ����Ϣ�޴�Ӧ��ͷ���ʴ˲�������ΪNULL.
	*	@param nApplicationHeadSize  Ӧ��ͷ����,����Ϊ�㡣
	*	@param pData                 ��ѹ������ݵ���ʼλ��.�������ͣ������ pHead �� sDataType ��ֵ������ת��.
	*								 ����sDataType����������Ϣ��ʽ���ɲμ� �ӿ�pdf �� ʾ�����롣
	*	@param nItemSize			 ÿһ����¼�Ĵ�С��
	*	@param nItems				 ��¼��	.
	*	
	*	@Remark	һ�������,pHead�������pData,pApplicationHead��nItemSize��nItems����һ����Ч
	*	������������Ϣ�Ķ���,��pHead��pData���ȡ��Ҫ������.
	*/
	typedef void (CALLBACK *ON_TTD_RECV_DATA_HANDLER)(
		const ATP_MsgHead * /*pHead*/,
		const void * /*pApplicationHead*/,
		int /*nApplicationHeadSize*/,
		const void * /*pData*/,
		int /*nItemSize*/,
		int /*nItems*/);

#endif  //end of __TTDAPILIB_TYPE_DEFINE__

	/**
	����ͨѶ���������. 
	�ڵ��� <a href="#TTD_SEC_Begin">TTD_SEC_Begin</a>֮ǰ���ã�
	����ͨ������������������ӣ��ɲ����øú���.
	�ڵ���TTD_SEC_SetServerInfo��������òŻ���Ч��

	*	@param iProxyType ʹ�õĴ�������<br>	
	<li>0			��ʹ�ô���.
	<li>1			SOCK4
	<li>2			SOCK4A
	<li>3			SOCK5
	<li>4			HTTP1.1
	*	@param szProxyHost	�����������ַ. 
	*   @param iProxyPort	����������˿� 
	*	@param szProxyUser  �û��� ���û�������ʱ��Ϊ�㳤���ַ���"" .
	*	@param szProxyPass	����. 
	*/
	TTDAPI(int) TTD_SEC_SetProxy( 
		int  iProxyType,		//ʹ�õĴ�������.
		char *lpszProxyHost,	//�����ַ
		int  iProxyPort,		//����˿�
		char *lpszProxyUser,	//�����û���
		char *lpszProxyPass		//��������)
		);

	/**
	*	���÷�������Ϣ.
	*	@param lpszServer	������ip��ַ.
	*	@param	uPort		�������˿�.
	*/
	TTDAPI(int) TTD_SEC_SetServerInfo(char *lpszServer,UINT uPort);

	/**
	*	�����û���Ϣ.
	*	@param ttdHandler				���������.
	*	@param lpszUserName				�û���.
	*	@param lpszPassword				����.
	*	@param lpszSaleDepartmentCode	Ӫҵ����ţ�8�ֽڳ���.
	*/
	TTDAPI(int) TTD_SEC_SetUserInfo(char *lpszUserName,char *lpszPassword,char *lpszSaleDepartmentCode);

	/**
	*	���翪ʼ����.
	*	�������ӷ�����,���ӳɹ�,�ɴ������ӳɹ������¼�.
	*/
	TTDAPI(int) TTD_SEC_Begin();

	/**
	*	ֹͣ����.
	*	�Ͽ���������,�ɴ����Ͽ����������¼�.
	*/
	TTDAPI(int) TTD_SEC_End();


	/**
	*	�Ƿ��Ѿ������Ϸ�����.
	*	@return �Ѿ����Ϸ���������true,���򷵻�false.
	*/
	TTDAPI(bool) TTD_SEC_IsConnect();

	/**
	*	�û��Ƿ��Ѿ���¼��ϵͳ.
	*	@return ��¼�˷���true,���򷵻�false.
	*/
	TTDAPI(bool) TTD_SEC_IsLogin();

	/**
	*	�ͷ��ɿ��Լ�������ڴ�.
	*/
	TTDAPI(int) TTD_SEC_Release(void *pData);

	/**
	*	�ͷ��㷨������Ϣ�ڴ�
	*/
	TTDAPI(int) TTD_SEC_ReleaseAlgoparam(Atp_Algoparam_Info *pAlgoparam);

	/**
	*	��¼.
	*	@param	pAns ���ص�¼���.
	*	@return ��������Ϊint��,����ϵͳ�������,�������ʾ�޴������.
	*/
	TTDAPI(int) TTD_SEC_Login(UTI_SEC_LoginAnswer *pAns);

	/**
	*	��������
	*/
	TTDAPI(int) TTD_SEC_StartPush();

	/**
	*	�����㷨��Ϣ.
	*	@param	ppArrAns	�����㷨����Ϣ,�������Ҫ��Release�����ͷ��ڴ�.
	*	@param	pnSize	���ؽ����¼����Ŀ.
	*	@return ��������Ϊint��,����ϵͳ�������,�������ʾ�޴������.
	*/
	TTDAPI(int) TTD_SEC_GetAlgoInfo(Atp_Algorithm_Info **ppArrAns,int *pnSize);

	/**
	*	�����㷨����������Ϣ.
	*	@param	pQuery	�㷨�ı�ʶGuid��Ϣ.
	*	@param	ppArrAns	�����㷨����������,�������Ҫ��Release�����ͷ��ڴ�.
	*	@param	pnSize	���ؽ����¼����Ŀ.
	*	@return ��������Ϊint��,����ϵͳ�������,�������ʾ�޴������.
	*/
	TTDAPI(int) TTD_SEC_GetAlgoParamsInfo(ATP_Msg_QueryAlgoParamterInfo *pQuery,Atp_Algoparam_Info **ppArrAns, int *pnSize);

	/**
	*	��ȡ�㷨״̬��Ϣ..
	*	@param	pQuery	�㷨�ı�ʶGuid��Ϣ.
	*	@param	ppArrAns	�����㷨����������,�������Ҫ��Release�����ͷ��ڴ�.
	*	@param	pnSize	���ؽ����¼����Ŀ.
	*	@return ��������Ϊint��,����ϵͳ�������,�������ʾ�޴������.
	*/
	TTDAPI(int) TTD_SEC_GetAlgoStatus(ATP_Msg_CurrentAlgoStatus **ppArrAns, int *pnSize);

	/**
	*	��ͨ�µ�.
	*	@param	pArr		�µ�����ָ��.
	*	@param	ppArrAns		�洢�µ������Ϣ������ָ��,�˿��ڴ���Ҫ�û��Լ�����,�ڴ�Ҫ�ܹ�������nArrSize���巵�ؽṹ��.
	*	@param	nArrSize	����Ĵ�С.
	*	@return ��������Ϊint��,����ϵͳ�������,�������ʾ�޴������.
	*/
	TTDAPI(int) TTD_SEC_GetCommonMakeOrder(const ATP_Msg_Sec_MakeOrder *pArrAsk,ATP_Msg_Sec_MakeOrder_Answer **ppArrAns,int nArrSize);

	/**
	*	�㷨�µ�����.

	*	@param	algoGuid	�㷨��ʶGuid,ָ��Ҫʹ�õ��㷨.
	*	@param	pArr		�㷨����ֵ������,˳��Ҫ���㷨ָ����˳��һ��.
	*	@param	pAns		�洢�㷨�µ������Ϣ��ָ��,�˿��ڴ���Ҫ�û��Լ�����.
	*	@param	nArrSize	����Ĵ�С.
	*	@return ��������Ϊint��,����ϵͳ�������,�������ʾ�޴������.
	*/
	TTDAPI(int) TTD_SEC_GetAlgoMakeOrder(
		GUID algoGuid,
		ATP_Msg_Sec_MakeOrderByAlgo_ParamValue *pArr,
		ATP_Msg_Sec_MakeOrderByAlgo_Answer *pAns,int nArrSize
		);

	/**
	*	������������.
	*	@param	pArr		�ɳ�������.
	*	@param	nArrSize	����Ĵ�С.
	*	@param	ppArrAns		�洢�㷨�µ������Ϣ������ָ��,�˿��ڴ���Ҫ�û��Լ�����,�ڴ�Ҫ�ܹ�������nArrSize���巵�ؽṹ��.
	*	@return ��������Ϊint��,����ϵͳ�������,�������ʾ�޴������.
	*/
	TTDAPI(int) TTD_SEC_GetMakeCancelOrder(ATP_Msg_Sec_MakeCancelOrder *pArr,ATP_Msg_Sec_MakeCancelOrder_Answer **pArrAns,int nArrSize);

	/**
	*	��ֹ�������е��㷨.
	*	@param	pQuery Ҫ��ֹ���㷨��Ϣ.
	*	@return ��������Ϊint��,����ϵͳ�������,�������ʾ�޴������.
	*/
	TTDAPI(int) TTD_SEC_TerminateAlgos(ATP_Msg_SEC_Run_Algo_Info *pQuery);

	/**
	*	�ֲֲ�ѯ����.
	*	@param	pQuery		���趨��Ʊ����Ͳ�ѯ��ʽ.
	*	@param	ppArrAns		���ؽ��������ָ��,�������Ҫ��Release�����ͷ��ڴ�.
	*	@param	pnSize		���ؽ���м�¼����Ŀ.
	*	@return ��������Ϊint��,����ϵͳ�������,�������ʾ�޴������.
	*/
	TTDAPI(int) TTD_SEC_GetHoldPosQuery(
		ATP_Msg_Sec_QueryHoldPositions *pQuery,
		ATP_Msg_Sec_HoldPosition **ppArrAns,
		int *pnSize
		);

	/**
	*	�ɽ���ѯ����.
	*	@param	query			���趨��Ʊ����Ͳ�ѯ��ʽ.
	*	@return ��������Ϊint��,����ϵͳ�������,�������ʾ�޴������.
	*/
	TTDAPI(int) TTD_SEC_GetMatchQuery(
		ATP_Msg_Sec_QueryMatch *pQuery,
		ATP_Msg_Sec_QueryMatch_Answer **ppArrAns,
		int *pnSize
		);

	/**
	*	ί�в�ѯ����.
	*	@param	pQuery		���趨��Ʊ����Ͳ�ѯ��ʽ.
	*	@param	ppArrAns		���ؽ��������ָ��,�������Ҫ��Release�����ͷ��ڴ�.
	*	@param	pnSize		���ؽ���м�¼����Ŀ.
	*	@return ��������Ϊint��,����ϵͳ�������,�������ʾ�޴������.
	*/
	TTDAPI(int) TTD_SEC_GetOrderRecordsQuery(
		ATP_Msg_Sec_QueryOrderRecords *pQuery,
		ATP_Msg_Sec_QueryOrderRecords_Answer **ppArrAns,
		int *pnSize
		);

	/**
	*	�ɳ�����ѯ����.	
	*	@param	pQuery		���趨��Ʊ����Ͳ�ѯ��ʽ.
	*	@param	ppArrAns		���ؽ��������ָ��,�������Ҫ��Release�����ͷ��ڴ�.
	*	@param	pnSize		���ؽ���м�¼����Ŀ.
	*	@return ��������Ϊint��,����ϵͳ�������,�������ʾ�޴������.
	*/
	TTDAPI(int) TTD_SEC_GetCanCancelQuery(
		ATP_Msg_Sec_QueryCanCancel *pQuery,
		ATP_Msg_Sec_QueryCanCancel_Answer **ppArrAns,
		int *pnSize
		);

	/**
	*	�ʲ���ѯ����.	
	*	@param	pQuery		���趨��Ʊ����Ͳ�ѯ��ʽ.
	*	@param	ppArrAns		���ؽ��������ָ��,�������Ҫ��Release�����ͷ��ڴ�.
	*	@param	pnSize		���ؽ���м�¼����Ŀ.
	*	@return ��������Ϊint��,����ϵͳ�������,�������ʾ�޴������.
	*/
	TTDAPI(int) TTD_SEC_GetAssetsQuery(
		ATP_Msg_Sec_QueryAssets *pQuery,
		ATP_Msg_Sec_QueryAssets_Answer **ppArrAns,
		int *pnSize
		);

	/**
	*	���ɳɽ�����ѯ����.
	*	@param	pQuery		���趨��Ʊ����Ͳ�ѯ��ʽ.
	*	@param	pAns		�������ɽ����Ľ��,�û��Լ����ڴ�.
	*	@return ��������Ϊint��,����ϵͳ�������,�������ʾ�޴������.
	*/
	TTDAPI(int) TTD_SEC_GetMaxVolumeQuery(
		ATP_Msg_Sec_QueryMaxVolume *pQuery,
		ATP_Msg_Sec_QueryMaxVolume_Answer *pAns
		);

	

	//////////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------------------------------------------
	//�¼�.
	//////////////////////////////////////////////////////////////////////////


	/**
	*	���ûص�����.
	*	@param	ttdHandler					���������,ָ��Ҫ���õĴ�����.
	*	@param	pNetEventHandler			�����¼��ص�����.
	*	@param	pServerAnsEventHandler		������Ӧ���¼��ص�����.
	*	@return void.
	*/
	TTDAPI(int) TTD_SEC_SetTTDEventHandler(
		ON_TTD_NET_EVENT pNetEventHandler,
		ON_TTD_RECV_DATA_HANDLER pRecvDataHandler
		);
	/**
	*	���������¼��ص�����.
	*	@param	pNetEventHandler			�����¼��ص�����.
	*	@return ����ԭ���������¼��ص�������ַ.
	*/
	TTDAPI(ON_TTD_NET_EVENT) TTD_SEC_SetTTDNetEventHandler(
		ON_TTD_NET_EVENT pNetEventHandler
		);

	/**
	*	���÷�����Ӧ���¼��ص�����.
	*	@param	pServerAnsEventHandler		������Ӧ���¼��ص�����.
	*	@return ����ԭ���ķ�����Ӧ���¼��ص�������ַ.
	*/
	TTDAPI(ON_TTD_RECV_DATA_HANDLER) TTD_SEC_SetTTDServerAnsEventHandler(
		ON_TTD_RECV_DATA_HANDLER pRecvDataHandler
		);

	/**
	*	��ȡ�����ַ���.
	*	@param	nErrorCode	����ֵ.
	*	@return ���ش���˵�����ַ���.
	*/
	TTDAPI(LPCTSTR) TTD_SEC_GetError(int nErrorCode);

	/**
	 **		�ϴ��ļ�
	 **		@param lpszFilePath �ļ�·��
	 **		@pRes	�ϴ����
	 **		@return �ɹ�����0
	 **/
	TTDAPI(int)	TTD_SEC_UploadFile(LPCTSTR lpszFilePath,ATP_Msg_UploadFileResult *pRes);
	//compatibilit with c plus plus
#ifdef __cplusplus
}
#endif


/**
*	
*/















