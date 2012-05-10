/************************************************************************************
*
* �ļ���  : AdoDB.h
*
* �ļ�����: ���ݿ������
*
* ������  : dingjing, 2008-12-31
*
* �汾��  : 1.0
*
* �޸ļ�¼:
*
************************************************************************************/
#ifndef _ADODB_H_
#define _ADODB_H_
#include <string>
using std::string;

#define DB_MSG_BUF_LEN 400          //LogEvent������־��������С
#define WM_LOGEVENT WM_USER + 109   //���û�ж��������࣬�ض����麯��LogEvent(), �����ʹ���Ϣ

//#import "C:\Program Files\common files\system\ado\msado15.dll" no_namespace rename("EOF", "adoEOF")
#import "D:\�����\msado15.dll" no_namespace rename("EOF", "adoEOF")

class CDataBase
{
public: //��������
	CDataBase();
#ifdef _MFC_VER
	CDataBase(HWND hWnd);
#endif
	virtual ~CDataBase();
	
public: //����
	_ConnectionPtr& GetConnection() { return m_pCon; }

	/********************************************************************************
	* ������: IsOpen
	* ��  ��: ������ݿ��Ƿ��
	* ����ֵ: �Ѵ򿪷���TRUE, ����FALSE
	********************************************************************************/
	BOOL IsOpen();

	/********************************************************************************
	* ������: SetCursorLocation
	* ��  ��:
	*		  CursorLocationEnum CursorLocation [IN] : �α�����λ��
	*												   adUseNone        : ��ʹ���α���񡣣��˳��������ϲ���ֻ��Ϊ�������ݲų��֡���
	*												   adUseServer      : Ĭ��ֵ��ʹ�������ṩ�߻����������ṩ���αꡣ��Щ�α���ʱ�������Զ����֪�����˶�����Դ�����ĸ��ġ����ǣ�Microsoft Cursor Service for OLE DB ��ĳЩ���ܣ�����Ͽ� Recordset ���󣩲����÷��������α�ģ�⣬��Щ�����ڴ������н������á�
	*												   adUseClient		: ʹ�ñ����α���ṩ�Ŀͻ��˵��αꡣ�����α����ͨ������ִ�����������ṩ���α������������๦�ܣ����ʹ�ô����ÿ��Գ�����ü������õĹ��ܡ�Ϊ���������ݣ���֧��ͬ���� adUseClientBatch��
	*												   adUseClientBatch :
	* ��  ��: �����α�����λ��
	********************************************************************************/
	void SetCursorLocation(CursorLocationEnum CursorLocation);

#ifdef _MFC_VER
	void SetMsgWnd(HWND hWnd){m_hWnd = hWnd;}
	HWND GetMsgWnd(){return m_hWnd;}
#endif

public:	//����
	/********************************************************************************
	* ������: Open
	* ��  ��:
	*		  const char* lpConStr [IN] : �����ַ���������������Ϣ
	*         long    nOptions [IN] : ����ѡ��
	*		                         adConnectUnspecified (Ĭ��)ͬ����ʽ������
	*                                adAsyncConnect		  �첽��ʽ������
	* ��  ��: �������ݿ�
	* ����ֵ: ���ӳɹ�����TRUE, ����FALSE
	********************************************************************************/
	BOOL Open(const char* lpConStr, long nOptions = adConnectUnspecified);
	
	/********************************************************************************
	* ������: Close
	* ��  ��: �ر����ݿ�����
	********************************************************************************/
	void Close();
	
	/********************************************************************************
	* ������: Execute
	* ��  ��:
	*		  LPCTSTR lpSQL    [IN] : Ҫִ�е�SQL���
	*         long    nOptions [IN] : ��ʾCommandText�����ݵ�����
	*                                 adCmdText   : ����CommandText���ı�����
	*                                 adCmdTable  : ����CommandText��һ������
	*                                 adCmdProc   : ����CommandText��һ���洢����
	*                                 adCmdUnknown: δ֪
	* ��  ��: ִ��SQL���
	* ����ֵ: ���ӳɹ�����_RecordsetPtrָ��, ����NULL
	********************************************************************************/
	_RecordsetPtr Execute(LPCTSTR lpSQL, long nOptions = adCmdText);

	/********************************************************************************
	* ������: BeginTrans
	* ��  ��: ��ʼ����
	* ����ֵ: ����֧��Ƕ����������ݿ���˵, ���Ѵ򿪵������е��� BeginTrans 
	          ��������ʼ�µ�Ƕ������. ����ֵ��ָʾǶ�ײ��: ����ֵΪ 1 ��ʾ�Ѵ򿪶���
	          ����, ����ֵΪ 2 ��ʾ�Ѵ򿪵ڶ�������, ��������
	********************************************************************************/
	long BeginTrans();

	/********************************************************************************
	* ������: CommitTrans
	* ��  ��: �ύ����
	* ����ֵ: �ɹ�����TRUE, ����FALSE
	********************************************************************************/
	BOOL CommitTrans();

	/********************************************************************************
	* ������: RollbackTrans
	* ��  ��: ȡ������
	* ����ֵ: �ɹ�����TRUE, ����FALSE
	********************************************************************************/
	BOOL RollbackTrans();

protected:
	/********************************************************************************
	* ������: LogEvent
	* ��  ��:
	*		  unsigned short nLogType [IN] : ��־������
	*                                        RPT_DEBUG   : ��ʾ�ǵ�����Ϣ
	*										 RPT_INFO    : ��ʾ����ʾ��Ϣ
	*										 RPT_WARNING : ��ʾ�Ǿ�����Ϣ
	*                                        RPT_ERROR   : ��ʾ�Ǵ�����Ϣ
	* ��  ��: ������־
	********************************************************************************/
	virtual void LogEvent(unsigned short nLogType, const char* pFormat, ...);

	//Attributes
	_ConnectionPtr        m_pCon;

#ifdef _MFC_VER
	HWND        m_hWnd;  //������Ϣ�Ĵ���
#endif

private:

};

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

class CRecordSet
{
public: //��������
	CRecordSet();
	CRecordSet(_ConnectionPtr pCon);
	CRecordSet(CDataBase* pDB);
	virtual ~CRecordSet();

public: //����
	/********************************************************************************
	* ������: SetConnectionPtr
	* ��  ��:
	*		  _ConnectionPtr pCon [IN] : ��_RecordsetPtr������_ConnectionPtr
	* ��  ��: _RecordsetPtrָ����_ConnectionPtrָ�����
	********************************************************************************/
	void SetConnectionPtr(_ConnectionPtr pCon){m_pCon  = pCon;}

	/********************************************************************************
	* ������: GetAbsolutePosition
	* ��  ��: ��ȡ��ǰ��¼��λ��
	* ��  ��: ���ص�ǰ��¼�����
	********************************************************************************/
	long GetAbsolutePosition();

	/********************************************************************************
	* ������: SetAbsolutePosition
	* ��  ��:
	*         int nPosition [IN] : Ҫ���õ�λ��
	* ��  ��: ���õ�ǰ��¼��λ��
	* ��  ��: �ɹ�����TRUE, ����FALSE
	********************************************************************************/
	BOOL SetAbsolutePosition(int nPosition);

	/********************************************************************************
	* ������: GetRecordset
	* ��  ��: ����_RecordsetPtrָ��m_pRset
	* ��  ��: ����m_pRset
	********************************************************************************/
	_RecordsetPtr& GetRecordset(){return m_pRset;}

public:	//����
	/********************************************************************************
	* ������: Open
	* ��  ��:
	*		  const char* lpSql             [IN] : Ҫִ�е�SQL���
	*         CursorTypeEnum CursorType	[IN] : �������
	*                                          adOpenUnspecified : �����ر�ָ��
    *                                          adOpenForwardOnly : ǰ����̬���, ���ֹ��ֻ����ǰ�����¼����������MoveNext��ǰ����,���ַ�ʽ�����������ٶ�, ������BookMark,RecordCount,AbsolutePosition,AbsolutePage������ʹ��
    *                                          adOpenKeyset      : �������ֹ��ļ�¼�������������û���������ɾ�������������ڸ���ԭ�м�¼�Ĳ��������ǿɼ���
    *                                          adOpenDynamic     : ��̬���, �������ݿ�Ĳ������������ڸ��û���¼���Ϸ�Ӧ����
    *                                          adOpenStatic      : ��̬���, ��Ϊ��ļ�¼������һ����̬���ݣ��������û���������ɾ�������²�������ļ�¼����˵�ǲ��ɼ���
	*         LockTypeEnum LockType 	[IN] : ��������
	*										   adLockUnspecified     : δָ�� 
	*										   adLockReadOnly        : ֻ����¼��
	*										   adLockPessimistic     : ����������ʽ, �����ڸ���ʱ�����������ж����������ȫ����������
	*										   adLockOptimistic      : �ֹ�������ʽ, ֻ���������Update����ʱ��������¼���ڴ�֮ǰ��Ȼ���������ݵĸ��¡����롢ɾ���ȶ���
	*										   adLockBatchOptimistic : �ֹ۷�������, �༭ʱ��¼�������������ġ����뼰ɾ������������ģʽ����ɡ�
	*         long lOption				[IN] : ��������Execute��lOption
	* ��  ��: �����ݱ�
	* ����ֵ: �ɹ�����TRUE, ����FALSE
	********************************************************************************/
	BOOL Open(const char* lpSql, CursorTypeEnum CursorType = adOpenDynamic, 
		LockTypeEnum LockType = adLockOptimistic, long lOption = adCmdText);

	/********************************************************************************
	* ������: Close
	* ��  ��: �ر����ݱ�
	********************************************************************************/
	void Close();

	/********************************************************************************
	* ������: GetRecordCount
	* ��  ��: ��ȡ��¼����
	* ����ֵ: ���ؼ�¼����
	********************************************************************************/
	long GetRecordCount();

	BOOL IsBOF();
	BOOL IsEOF();
	void MoveFirst();
	void MoveLast();
	void MoveNext();
	void MovePrevious();

	BOOL AddNew();
	BOOL Update();

	/********************************************************************************
	* ������: Delete
	* ��  ��:
	*		  AffectEnum AffectRecords [IN] : Delete ��Ӱ��ļ�¼��
	*                                         AdAffectCurrent     : Ĭ��, ��ɾ����ǰ��¼
	*										  AdAffectGroup       : ɾ�����㵱ǰ Filter �������õļ�¼, Ҫʹ�ø�ѡ��, ���뽫 Filter ��������Ϊ��Ч��Ԥ���峣��֮һ
	*										  adAffectAll         : ɾ�����м�¼
	*										  adAffectAllChapters :	ɾ�������Ӽ���¼
	* ��  ��: ɾ����¼
	* ����ֵ: �ɹ�����TRUE������FALSE
	********************************************************************************/
	BOOL Delete(AffectEnum AffectRecords = adAffectCurrent);

	/********************************************************************************
	* ������: Requery
	* ��  ��:
	*		  long Options [IN] : ָʾӰ��ò���ѡ���λ����
	*                             AdAffectCurrent : Ĭ��
	*							  AdAffectGroup   : ����ò�������Ϊ adAsyncExecute, ��ò������첽ִ�в���������ʱ����RecordsetChangeComplete �¼�
	* ��  ��: ���¼�¼
	* ����ֵ: �ɹ�����TRUE������FALSE
	********************************************************************************/
	BOOL Requery(long Options = adConnectUnspecified);

	/********************************************************************************
	* ������: SetFilter
	* ��  ��:
	*		  LPCTSTR lpszFilter [IN] : ɸѡ����
	* ��  ��: ����ɸѡ����
	* ����ֵ: �ɹ�����TRUE������FALSE
	********************************************************************************/
	BOOL SetFilter(LPCTSTR lpszFilter);

	/********************************************************************************
	* ������: SetSort
	* ��  ��:
	*		  LPCTSTR lpszCriteria [IN] : ��������
	* ��  ��: ������������
	* ����ֵ: �ɹ�����TRUE������FALSE
	********************************************************************************/
	BOOL SetSort(LPCTSTR lpszCriteria);

	BOOL PutCollect(LPCSTR lpFieldName,  const _variant_t &value);
	void GetCollect(LPCSTR lpFieldName,  unsigned int     &nValue,unsigned int unDef=0);
	BOOL GetCollect(LPCSTR lpFieldName,  SYSTEMTIME*      pValue);
	void GetCollect(LPCSTR lpFieldName,  LPCSTR lpValue,  int nMaxLen);
	void GetCollect(LPCSTR lpFieldName,  std::string      &strValue);
	void GetCollect(LPCSTR lpFieldName,  double           &Value,double dDef=0);
	void GetCollect(LPCSTR lpFieldName,  int              &nValue,int nDef=0);
	void GetCollect(LPCSTR lpFieldName, unsigned short& nValue,unsigned short usDef=0);

	void GetCollectBlob(LPCSTR lpFieldName,  LPCSTR lpValue,  int nMaxLen);

protected:
	virtual void LogEvent(unsigned short nLogType, const char* pFormat, ...);

	//Attributes
	_RecordsetPtr    m_pRset;
	_ConnectionPtr   m_pCon;
	CDataBase*       m_pDB;

private:

};


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
class CAccessDB : public CDataBase
{
public:	//��������
	CAccessDB();

#ifdef _MFC_VER
	CAccessDB(HWND hWnd);
#endif
	virtual ~CAccessDB();

public:	//����

public:	//����
	/********************************************************************************
	* ������: Open
	* ��  ��:
	*		  const char* lpDBPath   [IN] : ���ݿ�·��
	*		  const char* lpPassword [IN] : ���ݿ�����
	*         long    lOptions	 [IN] : ͬ��
	* ��  ��: �������ݿ�
	* ����ֵ: ���ӳɹ�����TRUE, ����FALSE
	********************************************************************************/
	BOOL Open(const char* lpDBPath, const char* lpPassword = NULL, long lOptions = adConnectUnspecified);

protected:
	virtual void LogEvent(unsigned short nLogType, const char* pFormat, ...);

private:
};

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
class CSQLServerDB : public CDataBase
{
public:	//��������
	CSQLServerDB();
	virtual ~CSQLServerDB();

public:	//����
	/********************************************************************************
	* ������: IsConnectNormal
	* ��  ��:
	*		  const char* strTestTable [IN] : �������������Ƿ����������ݿ��
	* ��  ��: �ж������Ƿ�����
	* ����ֵ: ������������TRUE, ����FALSE
	********************************************************************************/
	BOOL IsConnectNormal(const char* strTestTable);

public:	//����
	/********************************************************************************
	* ������: Open
	* ��  ��:
	*		  const char* strSerIP    [IN] : ���ݿ������IP
	*		  const char* strDBName   [IN] : ���ݿ���
	*		  const char* strUserName [IN] : �û���
	*		  const char* strPassword [IN] : ����
	*         long    lOptions	 [IN] : ͬ��
	* ��  ��: �������ݿ�
	* ����ֵ: ���ӳɹ�����TRUE, ����FALSE
	********************************************************************************/
	BOOL Open(const char* strSerIP, const char* strDBName, const char* strUserName, const char* strPassword,
		long lOptions = adConnectUnspecified);

	/********************************************************************************
	* ������: Reconnect
	* ��  ��:
	* ��  ��: ��������
	* ����ֵ: ���ӳɹ�����TRUE, ����FALSE
	********************************************************************************/
	BOOL Reconnect();

protected:

private: //����
	string     m_strCon;   //��������
	long       m_lOptions; //��������

};

////////////////////////////////////////////////////////////////////////////////////
#endif