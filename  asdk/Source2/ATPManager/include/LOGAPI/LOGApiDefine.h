#ifndef _LOGAPIDEFINE_H_
#define _LOGAPIDEFINE_H_

//#pragma pack(push,1)
typedef struct LogRecordHead
{
	UINT nSN;								// 日志记录 序号
	UINT nDate;								// 日志记录 时间
	UINT nTime;								// 时间 HHMMSSmmm
	int  nClass;							// 分类.  
	int	 nType;								// 0 字串 1 二进制.
	int	 nLength;							// 日志长度
}LogRecordHead;
//#pragma pack(push,1)
#endif