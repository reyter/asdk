#pragma once

//服务类型定义
#define ID_ATPSVC_MAIN		0	//系统主程序		ATPMain.exe
#define ID_ATPSVC_MANAGER	1	//系统管理服务	ATPManager.exe
#define ID_ATPSVC_ACCEPT	2	//用户接入服务	ATPAccept.exe
#define ID_ATPSVC_UTI		3	//沪深交易服务	ATPUTI.exe
#define ID_ATPSVC_TDF		4	//TDF数据服务	ATPTDF.exe
#define ID_ATPSVC_TDB		5	//TDB数据服务	ATPTDF.exe
#define ID_ATPSVC_MC		6	//系统监控服务	ATPMC.exe
#define ID_ATPSVC_ALG		8	//算法			ATPALG.exe
#define ID_ATPSVC_DPS		9	//分布式算法服务	ATPDPSMain.exe

//交易服务ID
#define ID_ATPUTI_CNSE		0	//沪深证券交易服务
#define ID_ATPUTI_CNIF		1	//股指期货交易服务
#define ID_ATPUTI_CNFU		2	//商品期货交易服务

//通讯信息
#define ID_APTSTAT_SENDPACKETS		0	//进程发送数据包个数
#define ID_APTSTAT_SENDBYTES		1	//进程发送数据字节
#define ID_APTSTAT_RECVPACKETS		2	//进程接收数据包个数
#define ID_APTSTAT_RECVBYTES		3	//进程接收数据字节

//交易信息统计
#define ID_ATPSTAT_UTI_BUY			10	//买入
#define ID_ATPSTAT_UTI_SALE			11	//卖出
#define ID_ATPSTAT_UTI_CANCEL		12	//撤单
#define ID_ATPSTAT_UTI_MATCH		13	//成交查询
#define ID_ATPSTAT_UTI_ORDER		14	//委托查询
#define ID_ATPSTAT_UTI_CANCANCEL	15	//可撤单查询
#define ID_ATPSTAT_UTI_CAPITAL		16	//资金查询
#define ID_ATPSTAT_UTI_OTHER		17	//其他查询

// CWndBGSManager
#define ID_HHFCBGSACTIVEAPP (WM_USER+96)		//激活到前端显示
#define ID_HHFCBGSKILLAPP	(WM_USER+97)		//手动结束进程前的消息通知

#define ID_HHFCBGSDATA	  (WM_USER+98)
#define ID_HHFCBGSMESSAGE (WM_USER+99)

class AFX_EXT_CLASS CWndBGSManager : public CWnd
{
public:
	/**
	* 初始化BGS服务
	* @param nServiceClass	[in] 服务类型
	* @param nServiceID		[in] 服务ID
	* @return 0：启动成功
	*	m_pWndGBS = new CWndBGS;
	*	int i = m_pWndGBS->Create(6, 0, this);
	*	if(i<0)
	*	{
	*		CString str;
	*		str.Format("%d", i);
	*		MessageBox("启动失败!", str);
	*		exit(-1);
	*	}
	*/
	LRESULT Create(int nServiceClass, int nServiceID, CWnd *pWndParent);

	/**
	* 向指定服务发送数据
	* @param nServiceClass	[in] 服务类型
	* @param nServiceID		[in] 服务ID
	* @param lParam			[in] 参数
	* @param pData			[in] 数据指针
	* @param nLen			[in] 数据长度
	* @return 发送长度
	*/
	int SendData(int nServiceClass, int nServiceID, int nID, void *pData, int nLen);

	/**
	* 接收服务数据（重新函数）
	* @param nServiceClass	[in] 服务类型
	* @param nServiceID		[in] 服务ID
	* @param lParam			[in] 参数
	* @param pData			[in] 数据指针
	* @param nLen			[in] 数据长度
	* @param bDel			[out] 是否有系统删除pData, 缺省为TRUE, 如果应用程序需要保存pData直接使用就将bDel=FALSE 
	*/
	virtual int OnRecvData(int nServiceClass, int nServiceID, int nID, void *pData, int nLen, BOOL &bDel);

	/**
	* 设置信息数据
	* @param nID	[in] 信息ID (0-32)
	* @param nData	[in] 统计数据
	* @return >=0 成功
	*/
	int SetInfoData(int nInfoID, int nData);

	/**
	* 设置监控状态信息
	* @param pchStatus [in] 状态文本
	* @return >=0 成功
	*/
	int SetStatusInfo(char *pchStatus);

	/**
	* 设置监控日志信息
	* @param pchLog [in] 日志文本
	* @return >=0 成功
	*/
	int SetLogInfo(char *pchLog);

	/**
	* 生成MD5码
	* @param pData [in] 源数据
	* @param nLen  [in] 长度
	* @return MD5码
	*/
	static CString GetMD5(char *pData, int nLen);

	/**
	* 获取本服务类型
	*/
	int GetServiceClass();

	/**
	* 获取本服务ID
	*/
	int GetServiceID();

	/**
	* 启用内部设置BGS服务运行检测标志，通知本程序运行正常
	* @param nCheckTime [in] 内部设置检测标志时间(s)
	*/
	void EnableInternalBGSCheckFlag(int nCheckTime);

	/**
	* 设置BGS服务运行检测标志，通知本程序运行正常
	*/
	int SetBGSCheckFlag();

	/**
	* 获取ATP名称
	* @param char *pchATPName [out] 名称(最大长度32)
	*/
	void GetATPName(char *pchName);


	DECLARE_DYNCREATE(CWndBGSManager)

public:
	CWndBGSManager();
	virtual ~CWndBGSManager();

protected:
	DECLARE_MESSAGE_MAP()

	LRESULT OnHHFCBGSMessage(WPARAM wParam, LPARAM lParam);
	LRESULT OnHHFCBGSData(WPARAM wParam, LPARAM lParam);
	int m_nServiceClass;
	int m_nServiceID;
	HANDLE m_hBGSHandle;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


