// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// HHUpdateClient.pch ����Ԥ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


#pragma comment(lib,"..\\lib\\zlibwapi.lib")

void WriteError(LPCTSTR lpError)
{
	char szError[1024]={0};
	CTime t = CTime::GetCurrentTime(); 
	sprintf(szError,"%d-%d-%d %d:%d:%d		",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
	FILE *stream;
	if ((stream = fopen("error.txt", "at+")) == NULL)
	{
		//fprintf(stderr, "Cannot open output file.\n"); 
		return; 
	}
	strcat(szError,lpError);
	strcat(szError,"\n");
	fwrite(szError, strlen(szError), 1, stream);
	fclose(stream);
}