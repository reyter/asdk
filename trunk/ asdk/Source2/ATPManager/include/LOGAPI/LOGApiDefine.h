#ifndef _LOGAPIDEFINE_H_
#define _LOGAPIDEFINE_H_

//#pragma pack(push,1)
typedef struct LogRecordHead
{
	UINT nSN;								// ��־��¼ ���
	UINT nDate;								// ��־��¼ ʱ��
	UINT nTime;								// ʱ�� HHMMSSmmm
	int  nClass;							// ����.  
	int	 nType;								// 0 �ִ� 1 ������.
	int	 nLength;							// ��־����
}LogRecordHead;
//#pragma pack(push,1)
#endif