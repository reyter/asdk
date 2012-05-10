#pragma once

#include "CCEDefine.h"
#include "dumpobject.h"
//#include "HHWPIOCP.h"
//#include "HHSelectCtrl_ChanInfo.h"
//#include "HHWPConnection.h"

#include "Channel.h"


#define DUME_CHANNEL_FILE  "ccecore.chl"

extern __int64   g_iTotalClient;
extern __int64   g_iTotalServer;





//维护一个列表来完成
class AFX_EXT_CLASS CChannelManager :
	public CDumpObject
{
public:
	
	virtual ~CChannelManager(void);

	CPtrList  m_lsChannel;		//连接列表
	bool  AddChannel(CHANNEL_INFO_CORE* pNewCore,bool bSaveConfig=true);//增加通道


	void   DelChannel(CChannel* pChannel);								//删除通道
	//void      EditChannel(CChannel* pChannel,CHANNEL_INFO_CORE* pCore);		//修改通道

	void  AfterEditChannel(CChannel* pChannel);

	
	
	//保存具体的数据到文件描述符对应的文件中
	//在该函数中调用WriteBytes写入数据。
	virtual bool OnDumpSave();		


	//从对应的文件描述符中加载对应的信息。
	//在该函数中调用LoadBytes读出数据。
	//参数nTotalCanBeRead为可读取的总的数据。
	virtual bool OnDumpLoad(QWORD nTotalCanBeRead);	


	void    GetChannelsForDisplay(INT_PTR& nTotalConnections,HHWP_CHANNELINFO*& pInfo,INT_PTR* pNCount,bool& bAlarm);			//反回数据以供显示用。

	static CChannelManager* GetInstance();


	static CString GetConfigFileName();

	void Clear();		//清队列表数据

	//将数据重新写入文件.(暂时采用全量写的方式)
	bool  SaveConfig();

protected:
	CChannelManager(void);
	static CChannelManager* s_gChannelManager;
public:
	static void UnInit();

public:
	static void AddConnection(LPVOID pConn);	//添加连接
	static void DeleteConnection(LPVOID pConn); //删除连接
};
