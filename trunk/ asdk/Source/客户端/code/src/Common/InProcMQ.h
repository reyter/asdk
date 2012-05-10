#ifndef InProcMQ_h__
#define InProcMQ_h__
#include <deque>
#include <map>


struct CMSG
{
	DWORD			m_dwSeqId;	             
	DWORD			m_dwCmdId;
	DWORD           m_dwDestThrId;
	DWORD           m_dwSrcThrId;
	LONG_PTR		m_pData;              
	DWORD			m_dwLen;              
	BOOL				m_bNeedDelete;
};

//后台消息处理指针函数声明
typedef void (*MQCallbackFunc)(CMSG msg);

class CInProcMQ
{
public:
	CInProcMQ(void);
	~CInProcMQ(void);
	static CInProcMQ& GetInstance(void);

	void RegCallbackFunc(MQCallbackFunc func);
	void SyncProcess(DWORD dwCmdID,LONG_PTR pData,DWORD dwLen);
	void AsyncProcess(DWORD dwCmdID,LONG_PTR pData,DWORD dwLen);
	void DispatchMsg(void);
	void Run(void);
	
private:
	std::deque<CMSG> m_queMsgs;//消息列队
	MQCallbackFunc m_CallbackFunc;
	CCriticalSection m_csLock;
	CEvent m_evt;

private:
	static CInProcMQ m_Instance;
};


#endif // InProcMQ_h__
