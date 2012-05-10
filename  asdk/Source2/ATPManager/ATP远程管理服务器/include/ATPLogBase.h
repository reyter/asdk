#pragma once
#include "ATPManagerDataBaseDefine.h"

class CATPLogBase:public CHHDataChannelCtrl
{
public:
	CATPLogBase(int nMark);
	CATPLogBase(int nMark,int nDate);
	virtual ~CATPLogBase(void);
public:
	//	Ϊע��ṹ�����ڴ�,ֻ����Ҫע��ṹָ��ʱ����Ҫʹ���������麯��
	virtual void	*NewRegisterSaveDataStruct(int nID, int nItems);
	virtual BOOL	DeleteRegisterSaveDataStruct(int nID, int nItems);

private:
	void			RegisterData(char *pFilename);
	int				InitDBLog(char *pFilename);

	CFile m_OperateFile;
	char m_szFileName[MAX_PATH];
public:
	int				AddOperateLog(struATPDataBaseOperateLog *);
	int				QueryOperateLog(struATPDataBaseOperateLog_QUERY *,OUT struATPDataBaseOperateLog **);

	int				AddAlgorithmLog(struATPDataBaseAlgorithmLog *);
	int				QueryAlgorithmLog(struATPDataBaseAlgorithmLog_QUERY *,OUT struATPDataBaseAlgorithmLog **);
private:

	int							m_nUsedATPDBSOperateLogItem;
	int							m_nATPDBSOperateLogItem;
	struATPDataBaseOperateLog	*m_pATPDBSOperateLog;

	int							m_nUsedATPDBSAlgorithmLogItem;
	int							m_nATPDBSAlgorithmLogItem;
	struATPDataBaseAlgorithmLog	*m_pATPDBSAlgorithmLog;

	int m_nLogMark;
};

