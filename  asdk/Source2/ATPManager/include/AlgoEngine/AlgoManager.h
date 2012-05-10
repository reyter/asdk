/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 算法管理器.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-1		李伟		 创建
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
算法需要 export 的 function
*/
#define ALGO_LOAD_FUN_NAME  _T("_OnAlgoDllLoad")
extern "C" typedef void (*ONALGODLLLOAD_FUN)();





/**
算法管理器类.
*/
class AFX_EXT_CLASS CAlgoManager	
{
public:
	/**
	注册算法.
	@param  pAlgoInfo 要注册的算法信息. 
	@param  pParamInfo 算法对应的参数信息数组首地址。
	@param  nParam     参数信息个数，参数信息需要与pAlgoInfo中的参数信息个数相同.
	@param  pAlgoClass 算法运行时类，RUNTIME_CLASS(Cxxxx),Cxxxx必须是CAbstractAlgo的派生类.
	@return 返回，是否注册成功.  
	*/
	static bool RegisterAlgorithm(ATP_ALGORITHM_INFO* pAlgoInfo,ATP_ALGOPARAM_INFO* pParamInfo,int nParam,CRuntimeClass* pAlgoClass);


	/**
	查找指定名称的算法信息.
	@param guidAlgo      算法GUID.
	@param 如果查找成功，返算法信息，否则，返回NULL.
	*/
	static const CAlgorithmInfo* FindAlgorigthmInfo(const GUID& guidAlgo);



public:
	/**
	加载算法Dll
	*/
	static void LoadAlgos();

	

	/**
	取单一实例.
	*/
	static CAlgoManager* GetInstance();




	/**
	即将开启算法会话.
	*/
	static void BeforeBeginAlgo(CAbstractAlgo* pAlgo,CAlgoSession* pAlgoSession);


	/**
	查找指定用户的算法状态.
	@param pInfo	用户信息
	@param nItems	返回算法状态数.
	@return         返回状态数据.
	*/ 
	static ATP_Msg_Sec_CurrentAlgoStatus* QueryRunningAlgoInfo(const ATP_User_Info& info,int& nItems);
	

protected:
	CAlgoManager(void);

	DECLARE_ERROR_MAP();

public:	
	virtual ~CAlgoManager(void);


	/**
	列举所有的算法.
	@param nItems   返回已注册的算法数.
	@return			返回算法数组，内存由new 分配 ，调用者负责调用  delete [] 删除内存.
	*/
	static CAlgorithmInfo* ListAllAlgorithmInfo(int& nItems);


	/**
	开启算法交易会话.
	@param userInfo		 用户信息.
	@param guidAlgo      算法GUID.
	@param pParamters	 算法的参数.
	@param nParams		 参数个数.
	@param dwSession	[out] 如果开启成功，返回会话ID.
	@param	strReason	[out] 出错时的原因
	@return				如果返回零，表示启动成功，否则，返回出错信息.
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
	结束会话指定的算法交易.
	@param	dwSession  会话ID
	


	*/
	int End(DWORD dwSession);	

	/**
	查询会话信息.
	*/
	LPVOID*	Query(DWORD dwSessiong);

protected:
	
	/**
	查找指定名称的算法信息.
	@param guidAlgo      算法GUID.
	@param 如果查找成功，返算法信息，否则，返回NULL.
	*/
	const CAlgorithmInfo* FindAlgorigthmInfo_Impl(const GUID& guidAlgo);


	/**
	查找指定名称算法的运行时类.
	@param guidAlgo      算法GUID.
	@return 如果查找成功，返回运行时类，否则，返回NULL.
	*/
	const CRuntimeClass* FindRuntimeCalss(const GUID& guidAlgo);


	/**
	全局算法管理器指针
	*/ 	
	static CAlgoManager* s_pAlgoManager;

	/**
	注册算法时保存的算法信息,因为只增不删，故不加锁.
	*/
	std::list<LPVOID> m_lsAlgoInfo;


	/**
	当前正在运行的会话.	
	*/ 
	std::map<CAlgoSession*,CAbstractAlgo*> m_mapCurrentSession;


	/**
	查询全部算法信息.
	*/ 	
	CAlgorithmInfo* ListAllAlgorithmInfo_Impl(int& nItems);


	/**
	开启算法交易会话.
	@param userInfo		 用户信息.
	@param guidAlgo      算法GUID.
	@param pParamters	 算法的参数.
	@param nParams		 参数个数.
	@param dwSession	[out] 如果开启成功，返回会话ID.
	@param	strReason	[out] 出错时的原因
	@return				如果返回零，表示启动成功，否则，返回出错信息.
	*/
	int Begin_Impl(CTradingHandler_Security* pHandlerSec, CTradingHandler_Futures* pHandlerFut,ATP_User_Info& userInfo,const GUID& guidAlgo,ATP_ALGOPARAM_VALUE* pParams,int nParams,CAlgoSession*& pSession,CString& strReason);



	ATP_Msg_Sec_CurrentAlgoStatus* QueryRunningAlgoInfo_Impl(const ATP_User_Info& info,int& nItems);

	

	
	std::map<ATP_User_Info,CAlgoUser*> m_mapAlgoUser;


	/**
	会话MAP的临界区，以保证在添加和删除时，可以多线程操作.
	*/
	CRITICAL_SECTION m_csUser;



	/**
	算法执行结速的通知.
	@param pAglo 算法
	@param nRetCode 退出代码
	*/
	void OnAlgoFinish(CAbstractAlgo* pAlgo,int nRetCode);


	friend class CWinThread_ExecAlgo;




	/**
	@param pAlgo  正要销毁的算法.
	@param pAlgoSession  其对应的会话.
	*/ 	
	void OnAlgoDestroy(CAlgoSession* pAlgoSession);

	/**
	算法初始化失败时的通知
	@param pAlgo 算法会话.
	@param strReason 出错原因
	*/
	void OnInitError(CAlgoSession* pAlgoSession,CString& strReason);



	CAlgoUser* GetAlgoUser(ATP_User_Info& userInfo);
};



