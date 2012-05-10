#include "StdAfx.h"
#include ".\channelmanager.h"
//#include "SystemConfigure.h"
#include "HHWPConnection.h"
#include "Mmsystem.h"



#include "HHWPConnection.h"


 __int64 g_iTotalClient=0;
 __int64 g_iTotalServer=0;


CChannelManager::CChannelManager(void)
{
	
}

CChannelManager::~CChannelManager(void)
{
	Clear();
}
void   CChannelManager::DelChannel(CChannel* pChannel)
{
	pChannel->Quit();

	POSITION pos = m_lsChannel.Find(pChannel);
	if(pos)
	{
		m_lsChannel.RemoveAt(pos);
	}
	SaveConfig();
}
CChannelManager* CChannelManager::s_gChannelManager=NULL;

void   CChannelManager::GetChannelsForDisplay(INT_PTR& nTotalConnections,HHWP_CHANNELINFO*& pInfo,INT_PTR* pNCount,bool& bAlarm)
{
	INT_PTR nNewCount  = m_lsChannel.GetCount();		//
	
	if(nNewCount>0 && nNewCount!=*pNCount)
	{
		if(pInfo)
		{
			delete []pInfo;			
		}
		pInfo = new HHWP_CHANNELINFO[nNewCount];
		
	}
	*pNCount = nNewCount;

	nTotalConnections = 0;
	POSITION pos = m_lsChannel.GetHeadPosition();
	int i=0;
    while (pos)
    {
		CChannel* pChannel = (CChannel*)m_lsChannel.GetNext(pos);
		if(pChannel)
		{
			//nTotalConnections += pChannel->GetConnectionCount();
			pChannel->GetChannelInfo(&(pInfo[i]));
			nTotalConnections += pInfo[i].nConnect;

			if(pChannel->m_core.nChannelStatus == ST_CANNOTCONN)
				bAlarm = true;

			++i;
		}
    }
}

CChannelManager* CChannelManager::GetInstance()
{
	if(s_gChannelManager==NULL)
	{
		s_gChannelManager = new CChannelManager();
		//if(PathFileExists(GetConfigFileName()))
		//{
		//	if( s_gChannelManager->OpenFile(GetConfigFileName(),false))
		//	{
		//		s_gChannelManager->Load();
		//		s_gChannelManager->CloseFile();
		//		/*POSITION pos = m_lsChannel.GetHeadPosition();
		//		while(pos)
		//		{

		//		}*/

		//	}else 
		//	{
		//		CString str;
		//		str.Format("��ȡͨ���ļ� %s ʧ��!",GetConfigFileName());
		//		::MessageBox(AfxGetMainWnd()->m_hWnd,str,"Error",MB_OK|MB_ICONINFORMATION);
		//		return false;
		//	}

		//}
		
	}
    return s_gChannelManager;
}

bool CChannelManager::OnDumpSave()
{
	INT_PTR nCount = m_lsChannel.GetCount();
	WriteBytes(&nCount,sizeof(nCount));
	CChannel* pChannel;
	for(POSITION pos = m_lsChannel.GetHeadPosition();pos;)
	{
		pChannel = (CChannel* )m_lsChannel.GetNext(pos);
        WriteBytes(&pChannel->m_core,sizeof(pChannel->m_core));
	}
	return true;
}

void CChannelManager::Clear()
{
	POSITION pos = m_lsChannel.GetHeadPosition();
	while(pos)
	{
		CChannel* pChannel = (CChannel*)m_lsChannel.GetNext(pos);
        delete pChannel;
	}
	m_lsChannel.RemoveAll();
}

//�Ӷ�Ӧ���ļ��������м��ض�Ӧ����Ϣ��
//�ڸú����е���LoadBytes�������ݡ�
//����nTotalCanBeReadΪ�ɶ�ȡ���ܵ����ݡ�
bool CChannelManager::OnDumpLoad(QWORD nTotalCanBeRead)
{
	try
	{

		Clear();
		int nCount;
		LoadBytes(&nCount,sizeof(nCount));
		nTotalCanBeRead -= sizeof(nCount);

		CHANNEL_INFO_CORE core;
		for(int i=0;i<nCount && nTotalCanBeRead>0 ;++i)
		{
			LoadBytes(&core,sizeof(core));
			AddChannel(&core,false);
		}	
		return true;
	}catch(...)
	{

		return false;
	}
	
}

CString CChannelManager::GetConfigFileName()
{
	char buffer[MAX_PATH];
	GetModuleFileName((HMODULE)AfxGetInstanceHandle(),buffer,MAX_PATH);
	CString str(buffer);
	str = str.Left(str.ReverseFind('\\')+1);
	str += DUME_CHANNEL_FILE;
	return str;
}

bool  CChannelManager::AddChannel(CHANNEL_INFO_CORE* pNewCore,bool bSaveConfig)
{
	//���в���
	POSITION pos = m_lsChannel.GetHeadPosition();
	while(pos)
	{
		CChannel* pChannel = (CChannel*)m_lsChannel.GetNext(pos);
		if(pChannel)
		{
			if(pChannel->m_core.nLocalPort == pNewCore->nLocalPort)
			{
				CString str;
				str.Format("ͨ��[%s]�Ѿ����䱾�ض˿�%d!",pChannel->m_core.szChannelName,pNewCore->nLocalPort);
				::MessageBox(AfxGetMainWnd()->m_hWnd,str,"��Ϣ",MB_OK|MB_ICONERROR);
				return false;
			}
		}
	}

	CChannel* pChannel = new CChannel(pNewCore);
	//pChannel->m_core = *pNewCore;

	m_lsChannel.AddTail(pChannel);
	//���ӳɹ�
	if(pChannel->m_core.nChannelStatus != ST_CLOSE)
	{
		if(!pChannel->Open())
		{
			pChannel->m_core.nChannelStatus = ST_CANNOTCONN;
			pChannel->m_szErrorInfo = "�޷��򿪱��ض˿ڽ�������";
			return false;
		}
	}
	if(bSaveConfig)
		SaveConfig();
	return true;
}
void  CChannelManager::AfterEditChannel(CChannel* pChannel)
{
	SaveConfig();
}

bool  CChannelManager::SaveConfig()
{	
	try{
		if(OpenFile(GetConfigFileName(),true))
		{
			Save();
			CloseFile();
			return true;
		}else
		{
			CString str;
			str.Format("����ͨ���ļ� %s ʧ��!",GetConfigFileName());
			::MessageBox(AfxGetMainWnd()->m_hWnd,str,"Error",MB_OK|MB_ICONINFORMATION);
			return false;
		}
		
	}catch (...) {
		CString str;
		str.Format("����ͨ���ļ� %s ʧ��!",GetConfigFileName());
		::MessageBox(AfxGetMainWnd()->m_hWnd,str,"Error",MB_OK|MB_ICONINFORMATION);
		return false;
	}
	
	//return false;
}



void CChannelManager::AddConnection(LPVOID pConn)	//�������
{
    ((CHHWPConnection*)pConn)->m_pChannel->AddConnection(pConn);
}
void CChannelManager::DeleteConnection(LPVOID pConn) //ɾ������
{
    ((CHHWPConnection*)pConn)->m_pChannel->DeleteConnection(pConn);
}

void CChannelManager::UnInit()
{
	if(s_gChannelManager)
	{
		s_gChannelManager->Clear();
		delete s_gChannelManager;
		s_gChannelManager = NULL;
	}
}