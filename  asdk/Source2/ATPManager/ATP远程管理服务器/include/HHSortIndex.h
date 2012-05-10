#pragma once
#define HHIDLT_DEF_CHECKBOX		'j'			//选择框
#define HHIDLT_DEF_ORDER		'o'			//序号
#define HHIDLT_DEF_DATE			't'			//日期(YMD)
#define HHIDLT_DEF_TIME			'h'			//时间(HMS)
#define HHIDLT_DEF_MDHM			'T'			//日期+时间(月+日+时+分)
#define HHIDLT_DEF_YMDHM		0x00001001	//日期+时间(年+月+日+时+分)[中文]
#define HHIDLT_DEF_ymdhm		0x00001002	//日期+时间(年+月+日+时+分)
#define HHIDLT_DEF_ymdhms		0x00001003	//日期+时间(年+月+日+时+分+秒)
#define HHIDLT_DEF_TIMEHM		0x00001004	//时间(时+分)[中文]
#define HHIDLT_DEF_TIMEhm		0x00001005	//时间(时+分)
#define HHIDLT_DEF_CHARS		'c'			//字符串
#define HHIDLT_DEF_LONG			'l'			//long
#define HHIDLT_DEF_LONG_SPL		0x00000111	//long  使用','分割显示
#define HHIDLT_DEF_ULONG		'u'			//unsigned long
#define HHIDLT_DEF_ULONG_SPL	0x00000121	//unsigned long 使用','分割显示
#define HHIDLT_DEF_ULONG_KMG	0x00000122	//unsigned long 使用'g,m,g'显示
#define HHIDLT_DEF_SIZE_UL		0x00000101	//unsigned long 存储大小
#define HHIDLT_DEF_SIZE_DL		0x00000102	//double		存储大小
#define HHIDLT_DEF_SHORT		's'			//short
#define HHIDLT_DEF_INT			'n'			//int
#define HHIDLT_DEF_FLOAT		'f'			//float
#define HHIDLT_DEF_FLOAT_SPL	0x00000131	//float 使用','分割显示
#define HHIDLT_DEF_DOUBLE		'd'			//double
#define HHIDLT_DEF_DOUBLE_SPL	0x00000141	//double 使用','分割显示
#define HHIDLT_DEF_INT64		'6'			//int64
#define HHIDLT_DEF_INT64_SPL	0x00000151	//int64 使用','分割显示
#define HHIDLT_DEF_INT64_KMG	0x00000152	//int64 使用'k,m,g'显示
#define HHIDLT_DEF_PERCENT		'p'			//百分比(%)
#define HHIDLT_DEF_CSTRING		0x00008001	//CString
#define HHIDLT_DEF_CFILENAME	0x00008002	//CString(文件名称)

class AFX_EXT_CLASS CHHSortIndex
{
private:
	int  m_nOffset;
	int  m_nLen;
	int  m_nRecords;
	int  m_nRecordSize;
	char *m_pData;
	int  *m_pIndex;
	char *m_pFind;
	BOOL m_bAscend;
	int  m_nType;
	void QuickSort(int left, int right);
	void Sort();
	int *Index();
	int  m_nFindCount;
	int  m_nFindMax;
	int  Find(int left, int right, char &bReslute);
	int  Compare(int nRecord, char *pFind);
	int  Find(char &bReslute);
	int  GetDataType(int nType);
public:
	CHHSortIndex(void);
	~CHHSortIndex(void);
public:
	//排序
	void Sort(short   *pData, int nRecords, BOOL bAscend);	
	void Sort(unsigned short   *pData, int nRecords, BOOL bAscend);	
	void Sort(int     *pData, int nRecords, BOOL bAscend);
	void Sort(unsigned int     *pData, int nRecords, BOOL bAscend);
	void Sort(long    *pData, int nRecords, BOOL bAscend);
	void Sort(unsigned long    *pData, int nRecords, BOOL bAscend);
	void Sort(double  *pData, int nRecords, BOOL bAscend);
	void Sort(float   *pData, int nRecords, BOOL bAscend);
	void Sort(__int64 *pData, int nRecords, BOOL bAscend);
	void Sort(char    *pData, int nLen, int nRecords, BOOL bAscend);
	void Sort(void    *pData, int nOffset, int nLen, int nRecords, int nRecordSize, int nType, BOOL bAscend);//nType:'s':short 'l':int long 'd':double 'f':float '6':__int64  'c':str
public:
	//索引
	int *Index(short   *pData, int nRecords, BOOL bAscend);
	int *Index(unsigned short   *pData, int nRecords, BOOL bAscend);
	int *Index(int     *pData, int nRecords, BOOL bAscend);
	int *Index(unsigned int     *pData, int nRecords, BOOL bAscend);
	int *Index(long    *pData, int nRecords, BOOL bAscend);
	int *Index(unsigned long    *pData, int nRecords, BOOL bAscend);
	int *Index(double  *pData, int nRecords, BOOL bAscend);
	int *Index(float   *pData, int nRecords, BOOL bAscend);
	int *Index(__int64 *pData, int nRecords, BOOL bAscend);
	int *Index(char    *pData, int nLen, int nRecords, BOOL bAscend);
	int *Index(void    *pData, int nOffset, int nLen, int nRecords, int nRecordSize, int nType, BOOL bAscend);//nType:'s':short 'l':int long 'd':double 'f':float '6':__int64  'c':str
public:
	//查找(返回查找到的记录号, pData必须已经有序)
	int Find(short   *pData, int nRecords, short  find, char &bReslute);
	int Find(unsigned short   *pData, int nRecords, unsigned short  find, char &bReslute);
	int Find(int     *pData, int nRecords, int    find, char &bReslute);
	int Find(unsigned int     *pData, int nRecords, unsigned int    find, char &bReslute);
	int Find(long    *pData, int nRecords, long   find, char &bReslute);
	int Find(unsigned long    *pData, int nRecords, unsigned long   find, char &bReslute);
	int Find(double  *pData, int nRecords, double find, char &bReslute);
	int Find(float   *pData, int nRecords, float   find, char &bReslute);
	int Find(__int64 *pData, int nRecords, __int64 find, char &bReslute);
	int Find(char    *pData, int nLen, int nRecords, char  *find, char &bReslute);
	int Find(void    *pData, int nOffset, int nLen, int nRecords, int nRecordSize, int nType, void *find, char &bReslute);//nType:'s':short 'l':int long 'd':double 'f':float '6':__int64  'c':str
};
