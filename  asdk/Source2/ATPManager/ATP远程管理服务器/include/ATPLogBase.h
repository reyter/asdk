#pragma once
#include "ATPManagerDataBaseDefine.h"

class CATPLogBase:public CHHDataChannelCtrl
{
public:
	CATPLogBase(int nMark);
	CATPLogBase(int nMark,int nDate);
	virtual ~CATPLogBase(void);
public:
	//	为注册结构分配内存,只有需要注册结构指针时才需要使用这两个虚函数
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

