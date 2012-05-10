#pragma once

#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/locking.h>
#include <share.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define ID_ATPDBMODE_READ	0x01
#define ID_ATPDBMODE_WRITE	0x02

#define ID_ATPDB_OK				0	//�ɹ�
#define ID_ATPDB_FIELDEXIST		-1	//�ֶ��Ѿ�����
#define ID_ATPDB_FIELDNOEXIST	-2	//�ֶβ�����
#define	ID_ATPDB_FIELDMISMATCH	-3	//�ֶ����Ͳ�ƥ��
#define ID_ATPDB_FIELDNODEFINE	-4	//�ֶ�û�ж���
#define ID_ATPDB_NOOPEN			-5	//�ļ�û�д�
#define	ID_ATPDB_ISOPEN			-6	//�ļ��Ѿ���
#define	ID_ATPDB_BOF			-7	//�ѵ�ͷ��¼
#define ID_ATPDB_EOF			-8	//�ѵ�β��¼
#define ID_ATPDB_NOSELECT		-9	//û�����������ļ�¼
#define ID_ATPDB_CREATEFILEERR	-10	//�ļ�����ʧ��
#define ID_ATPDB_QUREYERR		-11	//��ѯ��������
#define ID_ATPDB_NOQUREY		-12	//�޴˲�ѯ

enum ATPDBTypeEnum
{
    adEmpty = 0,
    adChar = 1,
    adUnsignedChar = 2,
    adShort= 3,
    adUnsignedShort = 4,
    adInt = 5,
    adUnsignedInt = 6,
    adInt64 = 7,
    adUnsignedInt64 = 8,
    adFloat = 9,
    adDouble = 10,
    adBoolean = 11,
    adStr = 12,
    adVoid = 13,
};

struct DB_Field
{ 
	char Fieldname[16]; // �ֶ���
	ATPDBTypeEnum  Type;// ��������
	int  nWidth;		// ���
	int  nBegin;        // ��ʼλ��
	int  nResv;
};

struct DB_Head
{	
	int nMagicCode;
	int nFields;		// �ֶθ���
	int nRecords;       // �ܼ�¼��
	int nRecordSize;    // ��¼����
};

class AFX_EXT_CLASS CATPDBase
{
public:
	CATPDBase(void);
	~CATPDBase(void);
private:
	char	m_chFileName[256];
	struct	DB_Head  m_Head;
	struct	DB_Field *m_pField;
	struct	DB_Field *m_pSField;
	int     m_nFpt;
	int		m_nCurrentIndex;
	char	*m_pBuffer;
	int		m_nBufferRecords;
	char	*m_pSetCollect;
	CPtrList m_QureyList;
	int		GetSelectIndex(HANDLE hSelect);
	int		m_nFlags;
public:
	/**
	*	���ļ�
	*	@param char *pchFilename [in]	�ļ���
	*	@param int nOpenFlag	 [in]	�򿪷�ʽ
	*/
	BOOL	Open(char *pchFilename, int nOpenFlag = ID_ATPDBMODE_READ | ID_ATPDBMODE_WRITE);

	/**
	*	�ر��ļ�
	*/
	BOOL	Close();

	/**
	*	�����ݱ��浽�ļ�
	*/
	BOOL SaveToFile();

	/**
	*	�����ֶ���Ϣ
	*	@param char *pchField		[in]	�ֶ�����
	*	@param ATPDBTypeEnum Type	[in]	�ֶ�����
	*	@param int nSizeOfItem		[in]	���ݴ�С
	*	@return 0:�ɹ�
	*/
	int CreateField(char *pchField, enum ATPDBTypeEnum Type, int nSizeOfItem);

	/**
	*	�����ļ�
	*	@param char *pchFilename	[in]	�ļ���
	*	@return 0:�ɹ�
	*/
	int	Create(char *pchFilename);

	/**
	*	�����ֶ�
	*	@param char *pchField		[in]	�ֶ�����
	*	@param ATPDBTypeEnum Type	[in]	�ֶ�����
	*	@param int nSizeOfItem		[in]	���ݴ�С
	*	@return 0:�ɹ�
	*/
	int	AppendField(char *pchField, enum ATPDBTypeEnum Type, int nSizeOfItem);

	/**
	*	ɾ���ֶ�
	*	@param char *pchField		[in]	�ֶ�����
	*	@return 0:�ɹ�
	*/
	int	DeleteField(char *pchField);

	/**
	*	��ȡ�ֶ���Ϣ
	*	@param int  nIndex			[in]	�ֶ�����
	*	@param char *pchField		[out]	�ֶ�����
	*	@param ATPDBTypeEnum &Type	[out]	�ֶ�����
	*	@param int &nSizeOfItem		[out]	���ݴ�С
	*	@return 0:�ɹ�
	*/
	int  GetFieldDefine(int nIndex, char *pchField, enum ATPDBTypeEnum &Type, int &nSizeOfItem);

	/**
	*	��ȡ�ֶ�����
	*	@param char *pchField		[in]	�ֶ�����
	*	@param int &nSizeOfItem		[out]	���ݴ�С
	*	@return ATPDBTypeEnum �ֶ�����
	*/
	enum ATPDBTypeEnum GetFieldType(char *pchField, int &nSizeOfItem);

	/**
	* �����ֶ�����
	*	@param char *pchField		[in]	�ֶ�����
	*	@return ��ȡ�����ݳ���
	*/
	int	SetCollect(char *pchField, char				data);
	int	SetCollect(char *pchField, unsigned char	data);
	int	SetCollect(char *pchField, short			data);
	int	SetCollect(char *pchField, unsigned short	data);
	int	SetCollect(char *pchField, int				data);
	int	SetCollect(char *pchField, unsigned	int		data);
	int	SetCollect(char *pchField, __int64			data);
	int	SetCollect(char *pchField, unsigned	__int64	data);
	int	SetCollect(char *pchField, float			data);
	int	SetCollect(char *pchField, double			data);
	int	SetCollect(char *pchField, bool				data);
	int	SetCollect(char *pchField, char				*pdata);
	int	SetCollect(char *pchField, void				*pdata);

	/**
	*	��������, ����ǰ��¼���ݸ���Ϊ��������
	*/
	int Update();

	/**
	*	׷��һ���հ׼�¼
	*	@return ׷�ӵļ�¼��
	*/
	int Append();

	/**
	*	����һ���հ׼�¼
	*	@param int nIndex	[in] ������nIndex��-1��ʾAppend
	*	@return ����ļ�¼��
	*/
	int Insert(int nIndex=-1);

	/**
	*	��ȡ�ֶ�����
	*	@param char *pchField		[in]	�ֶ�����
	*	@param void *data			[out]
	*	@param HANDLE	hSelect		[in]	NULL��ʾ���м�¼
	*	@return 0:�ɹ�
	*/
	int	GetCollect(char *pchField, char				&data,		HANDLE hSelect=NULL);
	int	GetCollect(char *pchField, unsigned char	&data,		HANDLE hSelect=NULL);
	int	GetCollect(char *pchField, short			&data,		HANDLE hSelect=NULL);
	int	GetCollect(char *pchField, unsigned short	&data,		HANDLE hSelect=NULL);
	int	GetCollect(char *pchField, int				&data,		HANDLE hSelect=NULL);
	int	GetCollect(char *pchField, unsigned	int		&data,		HANDLE hSelect=NULL);
	int	GetCollect(char *pchField, __int64			&data,		HANDLE hSelect=NULL);
	int	GetCollect(char *pchField, unsigned	__int64	&data,		HANDLE hSelect=NULL);
	int	GetCollect(char *pchField, float			&data,		HANDLE hSelect=NULL);
	int	GetCollect(char *pchField, double			&data,		HANDLE hSelect=NULL);
	int	GetCollect(char *pchField, bool				&data,		HANDLE hSelect=NULL);
	int	GetCollect(char *pchField, char	*pdata,	int nBufferSize, HANDLE hSelect=NULL);
	int	GetCollect(char *pchField, void	*pdata,	int nBufferSize, HANDLE hSelect=NULL);

	/**
	*	��λ����¼
	*	@param int nIndex	[in]	��¼��
	*	@return 0:�ɹ�
	*/
	int	Go(int nIndex);

	/**
	*	�ӵ�ǰ��¼��nRecords��¼
	*	@param int nRecords		[in] ������¼��
	*	@return 0:�ɹ�
	*/
	int	Skip(int nRecords=1);

	/**
	*	�ӵ�ǰ��¼�ź�λ��¼
	*	@param char *pchCommand	[in] ����
	*	@return 0:�ɹ�
	*/
	int Go(char *pchCommand);
	
	/**
	*	��ȡ��¼��
	*	@return ��ǰ��¼��
	*/
	int	GetCurrentRecord();

	/**
	*	ɾ����¼
	*	@param int nIndex	[in] Ҫɾ���ļ�¼��-1λ��ǰ��¼
	*	@return 0:�ɹ�
	*/
	int Delete(int nIndex=-1);

	/**
	*	ɾ����ǰ��¼�ź����������ļ�¼
	*	@param char *pchCommand	[in]	����
	*	@return ɾ�����������ļ�¼����
	*/
	int	Delete(char *pchCommand);

	/**
	*	��ѯ����
	*	@param char *pchCommand	[in]	����
	*	@param int& nResults	[out]	���������ļ�¼��
	*	@param int& nError		[out]	�������
	*	@return	HANDLE	��������
	*/
	HANDLE	Select(char *pchCommand, int &nResults, int &nError);

	/**
	*	�ƶ�����һ����¼
	*	@param	HANDLE hSelect	[in]	��������
	*	@param  int nRecords	[in]	�ƶ���¼��
	*	@return 0:�ɹ�
	*/
	int		MoveNext(HANDLE hSelect, int nRecords=1);

	/**
	*	�رս����
	*	@param	HANDLE hSelect	[in]	��������
	*/
	int		CloseSelect(HANDLE hSelect);
};
