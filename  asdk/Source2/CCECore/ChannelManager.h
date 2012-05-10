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





//ά��һ���б������
class AFX_EXT_CLASS CChannelManager :
	public CDumpObject
{
public:
	
	virtual ~CChannelManager(void);

	CPtrList  m_lsChannel;		//�����б�
	bool  AddChannel(CHANNEL_INFO_CORE* pNewCore,bool bSaveConfig=true);//����ͨ��


	void   DelChannel(CChannel* pChannel);								//ɾ��ͨ��
	//void      EditChannel(CChannel* pChannel,CHANNEL_INFO_CORE* pCore);		//�޸�ͨ��

	void  AfterEditChannel(CChannel* pChannel);

	
	
	//�����������ݵ��ļ���������Ӧ���ļ���
	//�ڸú����е���WriteBytesд�����ݡ�
	virtual bool OnDumpSave();		


	//�Ӷ�Ӧ���ļ��������м��ض�Ӧ����Ϣ��
	//�ڸú����е���LoadBytes�������ݡ�
	//����nTotalCanBeReadΪ�ɶ�ȡ���ܵ����ݡ�
	virtual bool OnDumpLoad(QWORD nTotalCanBeRead);	


	void    GetChannelsForDisplay(INT_PTR& nTotalConnections,HHWP_CHANNELINFO*& pInfo,INT_PTR* pNCount,bool& bAlarm);			//���������Թ���ʾ�á�

	static CChannelManager* GetInstance();


	static CString GetConfigFileName();

	void Clear();		//����б�����

	//����������д���ļ�.(��ʱ����ȫ��д�ķ�ʽ)
	bool  SaveConfig();

protected:
	CChannelManager(void);
	static CChannelManager* s_gChannelManager;
public:
	static void UnInit();

public:
	static void AddConnection(LPVOID pConn);	//�������
	static void DeleteConnection(LPVOID pConn); //ɾ������
};
