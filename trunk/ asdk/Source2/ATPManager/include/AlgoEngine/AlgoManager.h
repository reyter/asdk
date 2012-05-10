/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 �㷨������.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-1		��ΰ		 ����
-------------------------------------------------------------
*/

#pragma once

#include <list>
#include <map>
using namespace std;
#include "AbstractAlgo.h"
#include "AlgoSession.h"

#include "AlgorithmInfo.h"
#include "..\Include\ATPSetting\ATPErrorDefine.h"
#include "..\Include\ATSvr\OpenTDProtocol.h"
#include "AlgoUser.h"




/**
�㷨��Ҫ export �� function
*/
#define ALGO_LOAD_FUN_NAME  _T("_OnAlgoDllLoad")
extern "C" typedef void (*ONALGODLLLOAD_FUN)();





/**
�㷨��������.
*/
class AFX_EXT_CLASS CAlgoManager	
{
public:
	/**
	ע���㷨.
	@param  pAlgoInfo Ҫע����㷨��Ϣ. 
	@param  pParamInfo �㷨��Ӧ�Ĳ�����Ϣ�����׵�ַ��
	@param  nParam     ������Ϣ������������Ϣ��Ҫ��pAlgoInfo�еĲ�����Ϣ������ͬ.
	@param  pAlgoClass �㷨����ʱ�࣬RUNTIME_CLASS(Cxxxx),Cxxxx������CAbstractAlgo��������.
	@return ���أ��Ƿ�ע��ɹ�.  
	*/
	static bool RegisterAlgorithm(ATP_ALGORITHM_INFO* pAlgoInfo,ATP_ALGOPARAM_INFO* pParamInfo,int nParam,CRuntimeClass* pAlgoClass);


	/**
	����ָ�����Ƶ��㷨��Ϣ.
	@param guidAlgo      �㷨GUID.
	@param ������ҳɹ������㷨��Ϣ�����򣬷���NULL.
	*/
	static const CAlgorithmInfo* FindAlgorigthmInfo(const GUID& guidAlgo);



public:
	/**
	�����㷨Dll
	*/
	static void LoadAlgos();

	

	/**
	ȡ��һʵ��.
	*/
	static CAlgoManager* GetInstance();




	/**
	���������㷨�Ự.
	*/
	static void BeforeBeginAlgo(CAbstractAlgo* pAlgo,CAlgoSession* pAlgoSession);


	/**
	����ָ���û����㷨״̬.
	@param pInfo	�û���Ϣ
	@param nItems	�����㷨״̬��.
	@return         ����״̬����.
	*/ 
	static ATP_Msg_Sec_CurrentAlgoStatus* QueryRunningAlgoInfo(const ATP_User_Info& info,int& nItems);
	

protected:
	CAlgoManager(void);

	DECLARE_ERROR_MAP();

public:	
	virtual ~CAlgoManager(void);


	/**
	�о����е��㷨.
	@param nItems   ������ע����㷨��.
	@return			�����㷨���飬�ڴ���new ���� �������߸������  delete [] ɾ���ڴ�.
	*/
	static CAlgorithmInfo* ListAllAlgorithmInfo(int& nItems);


	/**
	�����㷨���׻Ự.
	@param userInfo		 �û���Ϣ.
	@param guidAlgo      �㷨GUID.
	@param pParamters	 �㷨�Ĳ���.
	@param nParams		 ��������.
	@param dwSession	[out] ��������ɹ������ػỰID.
	@param	strReason	[out] ����ʱ��ԭ��
	@return				��������㣬��ʾ�����ɹ������򣬷��س�����Ϣ.
	*/
	static int Begin(
		CTradingHandler_Security* pHandlerSec, 
		CTradingHandler_Futures* pHandlerFut,
		ATP_User_Info& userInfo,
		const GUID& guidAlgo,
		ATP_ALGOPARAM_VALUE* pParams,
		int nParams,
		CAlgoSession*& pSession,
		CString& strReason);



	/**
	�����Ựָ�����㷨����.
	@param	dwSession  �ỰID
	


	*/
	int End(DWORD dwSession);	

	/**
	��ѯ�Ự��Ϣ.
	*/
	LPVOID*	Query(DWORD dwSessiong);

protected:
	
	/**
	����ָ�����Ƶ��㷨��Ϣ.
	@param guidAlgo      �㷨GUID.
	@param ������ҳɹ������㷨��Ϣ�����򣬷���NULL.
	*/
	const CAlgorithmInfo* FindAlgorigthmInfo_Impl(const GUID& guidAlgo);


	/**
	����ָ�������㷨������ʱ��.
	@param guidAlgo      �㷨GUID.
	@return ������ҳɹ�����������ʱ�࣬���򣬷���NULL.
	*/
	const CRuntimeClass* FindRuntimeCalss(const GUID& guidAlgo);


	/**
	ȫ���㷨������ָ��
	*/ 	
	static CAlgoManager* s_pAlgoManager;

	/**
	ע���㷨ʱ������㷨��Ϣ,��Ϊֻ����ɾ���ʲ�����.
	*/
	std::list<LPVOID> m_lsAlgoInfo;


	/**
	��ǰ�������еĻỰ.	
	*/ 
	std::map<CAlgoSession*,CAbstractAlgo*> m_mapCurrentSession;


	/**
	��ѯȫ���㷨��Ϣ.
	*/ 	
	CAlgorithmInfo* ListAllAlgorithmInfo_Impl(int& nItems);


	/**
	�����㷨���׻Ự.
	@param userInfo		 �û���Ϣ.
	@param guidAlgo      �㷨GUID.
	@param pParamters	 �㷨�Ĳ���.
	@param nParams		 ��������.
	@param dwSession	[out] ��������ɹ������ػỰID.
	@param	strReason	[out] ����ʱ��ԭ��
	@return				��������㣬��ʾ�����ɹ������򣬷��س�����Ϣ.
	*/
	int Begin_Impl(CTradingHandler_Security* pHandlerSec, CTradingHandler_Futures* pHandlerFut,ATP_User_Info& userInfo,const GUID& guidAlgo,ATP_ALGOPARAM_VALUE* pParams,int nParams,CAlgoSession*& pSession,CString& strReason);



	ATP_Msg_Sec_CurrentAlgoStatus* QueryRunningAlgoInfo_Impl(const ATP_User_Info& info,int& nItems);

	

	
	std::map<ATP_User_Info,CAlgoUser*> m_mapAlgoUser;


	/**
	�ỰMAP���ٽ������Ա�֤����Ӻ�ɾ��ʱ�����Զ��̲߳���.
	*/
	CRITICAL_SECTION m_csUser;



	/**
	�㷨ִ�н��ٵ�֪ͨ.
	@param pAglo �㷨
	@param nRetCode �˳�����
	*/
	void OnAlgoFinish(CAbstractAlgo* pAlgo,int nRetCode);


	friend class CWinThread_ExecAlgo;




	/**
	@param pAlgo  ��Ҫ���ٵ��㷨.
	@param pAlgoSession  ���Ӧ�ĻỰ.
	*/ 	
	void OnAlgoDestroy(CAlgoSession* pAlgoSession);

	/**
	�㷨��ʼ��ʧ��ʱ��֪ͨ
	@param pAlgo �㷨�Ự.
	@param strReason ����ԭ��
	*/
	void OnInitError(CAlgoSession* pAlgoSession,CString& strReason);



	CAlgoUser* GetAlgoUser(ATP_User_Info& userInfo);
};



