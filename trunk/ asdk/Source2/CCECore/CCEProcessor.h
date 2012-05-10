/**
* @Copyright �����д���Ƽ����޹�˾(www.hh.com.cn)
* @System	 ͨ��ͨ�ſ�(Common Communication Environment Core)
* @Brief	 �������ݴ�����
* @Author	 wli
* @Date      2010-10-21
*/

#pragma once

#ifndef __CCEPROCESSOR_H_
#define __CCEPROCESSOR_H_

#include "CCEDefine.h"

#define CCE_DEFAULT_RECV_LEN (8*1024)


class CHHWPConnection;
/**
*	 �������ݴ�����
*	 �ṩ�����뷢��ԭʼ���ݵĽӿ�.
*
*/ 
class AFX_EXT_CLASS CCCEProcessor : public CObject
{
	DECLARE_DYNCREATE(CCCEProcessor);

public:
	CCCEProcessor();
	virtual ~CCCEProcessor();

public:

	//����3DES��Ҫ�����ݳ�����8���������������Ҫȡ���ݳ��ȵ�8��������.
	static int GetSafe3DesEncryptLength(int block_len);
	static int HHSafe3DesDecrypt(char* key,  int keylen, BYTE* source_buf, int block_len,  BYTE* dest_buf);
	static int HHSafe3DesEncrypt(char* key,  int keylen, BYTE* source_buf, int block_len,  BYTE* dest_buf);

public:

	/**
	* ������־����.
	* @param pLogFun �ص�����
	* @param lParam  �ص������ص�ʱ���ݵĲ���.
	*/	
	static CCE_LOG_FUN SetCCELogFun(CCE_LOG_FUN pLogFun,LPVOID lParam);

	/**
	* ����һ���������
	* @param szSvrName			��������
	* @param nPort				�������Ҫ�󶨵������˿ڡ�
	* @param pRuntimeCalss		������Ӧ�࣬����ΪCCCEProcessor������.
								����Ҫ֧�ֶ�̬����(DECLARE_DYNCREATE)
	* @param lParam             ���Ӳ������ò������������õ� m_lParam ������.
	* @param ���ط����Ƿ񴴽��ɹ���
	*/
	static bool CreateServer(LPCTSTR szSvrName,USHORT nPort,CRuntimeClass* pRuntimeClass,
		LPVOID lParam=NULL);


	/**
	*	��������.
	*	���ݻ���뻺���н��з���.
	*/
	int SendRawData(const void* pData,int nLength);


	/**
	*	��������,
	*	����������ݰ����Զ��رմ�����.(�緢��ע����Ϣ�󣬶Ͽ�����)
	*/
	int SendRawDataThenClose(const void* pData,int nLength);


	/**
	* ���ý��ջ���.
	* @param nSize ������ջ������8k,������Ϊָ����ֵ���������Զ�����Ϊ8k.
	* 
	*/
	void SetRecvBufferSize(int nSize);
	


	/**
	*	�ر�����.
	*	�ر����Ӻ󣬻���� OnClose�����һ�delete this.
	*/ 
	void  CloseConnection();


	/**
	* ȡ״̬.
	*/
	void   GetStatistics(__int64* pI64Send,__int64* pI64Recv);


	/**
	* ȡ�Է�IP��ַ.
	*/
	void   GetPeerAddr(sockaddr_in& addr);


	/**
	* ȡ����IP��ַ.
	*/
	void  GetThisAddr(sockaddr_in& addr);

	
	//������Դ����ͨѶ�¼��ص�����
protected:
	/**
	*	�������Ͻ��յ����ݵĻص�����
	*	@param pData		������ʼ��ַ
	*	@param nLength		���ݳ���
	*/
	virtual void OnRecvRawData(const void* pData,int nLength);

	/**
	*  ����������ɵĻص�������
	*/
	virtual void OnSendDataFinish(const void* pData,int nLength);

	/**
	*	�����жϣ�����øú�����Ȼ��ɾ����Ӧ��Processor.
	*	��ˣ������࣬���ڴ���һЩ��Դ�ͷ��Եȶ���Ĺ�����
	*	�������True ,��ʾ����Ҫɾ����Processor.���򣬲�ɾ��.
	*	������Ĭ�Ϸ���TRUE.
	*/
	virtual bool OnClose();

	
	/**
	*	 ���������Ѿ�����.
	*/ 	
	virtual void OnConnectionInitFinish();


private:
	/**
	*	��������ָ�룬
	*	���������ڿ����
	*/
	void SetConnectionPointer(CHHWPConnection* pConnection);

	friend class CHHWPConnection;			//��Ԫ��

	

protected:
	CHHWPConnection* m_pConnection;
	LPVOID	m_lParam;						//����ʱ�ĸ��Ӳ���

private:
	int m_nRecvBufferSize;
	
};


#endif //__CCEPROCESSOR_H_