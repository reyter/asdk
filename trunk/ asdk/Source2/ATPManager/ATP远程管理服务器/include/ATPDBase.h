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

#define ID_ATPDB_OK				0	//成功
#define ID_ATPDB_FIELDEXIST		-1	//字段已经存在
#define ID_ATPDB_FIELDNOEXIST	-2	//字段不存在
#define	ID_ATPDB_FIELDMISMATCH	-3	//字段类型不匹配
#define ID_ATPDB_FIELDNODEFINE	-4	//字段没有定义
#define ID_ATPDB_NOOPEN			-5	//文件没有打开
#define	ID_ATPDB_ISOPEN			-6	//文件已经打开
#define	ID_ATPDB_BOF			-7	//已到头记录
#define ID_ATPDB_EOF			-8	//已到尾记录
#define ID_ATPDB_NOSELECT		-9	//没有满足条件的记录
#define ID_ATPDB_CREATEFILEERR	-10	//文件创建失败
#define ID_ATPDB_QUREYERR		-11	//查询参数错误
#define ID_ATPDB_NOQUREY		-12	//无此查询

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
	char Fieldname[16]; // 字段名
	ATPDBTypeEnum  Type;// 数据类型
	int  nWidth;		// 宽度
	int  nBegin;        // 开始位置
	int  nResv;
};

struct DB_Head
{	
	int nMagicCode;
	int nFields;		// 字段个数
	int nRecords;       // 总记录数
	int nRecordSize;    // 记录长度
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
	*	打开文件
	*	@param char *pchFilename [in]	文件名
	*	@param int nOpenFlag	 [in]	打开方式
	*/
	BOOL	Open(char *pchFilename, int nOpenFlag = ID_ATPDBMODE_READ | ID_ATPDBMODE_WRITE);

	/**
	*	关闭文件
	*/
	BOOL	Close();

	/**
	*	将数据保存到文件
	*/
	BOOL SaveToFile();

	/**
	*	创建字段信息
	*	@param char *pchField		[in]	字段名称
	*	@param ATPDBTypeEnum Type	[in]	字段类型
	*	@param int nSizeOfItem		[in]	数据大小
	*	@return 0:成功
	*/
	int CreateField(char *pchField, enum ATPDBTypeEnum Type, int nSizeOfItem);

	/**
	*	创建文件
	*	@param char *pchFilename	[in]	文件名
	*	@return 0:成功
	*/
	int	Create(char *pchFilename);

	/**
	*	增加字段
	*	@param char *pchField		[in]	字段名称
	*	@param ATPDBTypeEnum Type	[in]	字段类型
	*	@param int nSizeOfItem		[in]	数据大小
	*	@return 0:成功
	*/
	int	AppendField(char *pchField, enum ATPDBTypeEnum Type, int nSizeOfItem);

	/**
	*	删除字段
	*	@param char *pchField		[in]	字段名称
	*	@return 0:成功
	*/
	int	DeleteField(char *pchField);

	/**
	*	读取字段信息
	*	@param int  nIndex			[in]	字段索引
	*	@param char *pchField		[out]	字段名称
	*	@param ATPDBTypeEnum &Type	[out]	字段类型
	*	@param int &nSizeOfItem		[out]	数据大小
	*	@return 0:成功
	*/
	int  GetFieldDefine(int nIndex, char *pchField, enum ATPDBTypeEnum &Type, int &nSizeOfItem);

	/**
	*	读取字段类型
	*	@param char *pchField		[in]	字段名称
	*	@param int &nSizeOfItem		[out]	数据大小
	*	@return ATPDBTypeEnum 字段类型
	*/
	enum ATPDBTypeEnum GetFieldType(char *pchField, int &nSizeOfItem);

	/**
	* 设置字段数据
	*	@param char *pchField		[in]	字段名称
	*	@return 读取的数据长度
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
	*	更新数据, 将当前记录数据更新为设置数据
	*/
	int Update();

	/**
	*	追加一条空白记录
	*	@return 追加的记录号
	*/
	int Append();

	/**
	*	插入一条空白记录
	*	@param int nIndex	[in] 插入在nIndex后，-1表示Append
	*	@return 插入的记录号
	*/
	int Insert(int nIndex=-1);

	/**
	*	读取字段数据
	*	@param char *pchField		[in]	字段名称
	*	@param void *data			[out]
	*	@param HANDLE	hSelect		[in]	NULL表示现行记录
	*	@return 0:成功
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
	*	定位到记录
	*	@param int nIndex	[in]	记录号
	*	@return 0:成功
	*/
	int	Go(int nIndex);

	/**
	*	从当前记录跳nRecords记录
	*	@param int nRecords		[in] 跳动记录数
	*	@return 0:成功
	*/
	int	Skip(int nRecords=1);

	/**
	*	从当前记录号后定位记录
	*	@param char *pchCommand	[in] 条件
	*	@return 0:成功
	*/
	int Go(char *pchCommand);
	
	/**
	*	读取记录号
	*	@return 当前记录号
	*/
	int	GetCurrentRecord();

	/**
	*	删除记录
	*	@param int nIndex	[in] 要删除的记录，-1位当前记录
	*	@return 0:成功
	*/
	int Delete(int nIndex=-1);

	/**
	*	删除当前记录号后满足条件的记录
	*	@param char *pchCommand	[in]	条件
	*	@return 删除满足条件的记录个数
	*/
	int	Delete(char *pchCommand);

	/**
	*	查询操作
	*	@param char *pchCommand	[in]	条件
	*	@param int& nResults	[out]	符合条件的记录数
	*	@param int& nError		[out]	错误代码
	*	@return	HANDLE	结果集句柄
	*/
	HANDLE	Select(char *pchCommand, int &nResults, int &nError);

	/**
	*	移动到下一个记录
	*	@param	HANDLE hSelect	[in]	结果集句柄
	*	@param  int nRecords	[in]	移动记录数
	*	@return 0:成功
	*/
	int		MoveNext(HANDLE hSelect, int nRecords=1);

	/**
	*	关闭结果集
	*	@param	HANDLE hSelect	[in]	结果集句柄
	*/
	int		CloseSelect(HANDLE hSelect);
};
