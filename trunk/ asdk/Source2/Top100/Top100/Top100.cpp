// Top100.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Top100.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;
void find();
void buildHeap(int* array, int from, int len);
void shift(int* array,int from, int len, int pos);
void sort(int* array,int nLen);

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
			find();
// 			int i; 
// 
// 			printf("Ten random numbers from 0 to 99\n\n"); 
// 			for(i=0; i<10; i++) 
// 				printf("%d\n", abs((rand()+rand()*100000+rand()*10000000)) % 1000000000); 


		}
	}
	else
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}



// Top100.cpp : �������̨Ӧ�ó������ڵ㡣
//






void find()
{//
	int number = 100000000;// һ�ڸ���
	int maxnum = 1000000000;// ��������ֵ
	int i = 0;
	int topnum = 100;// ȡ���Ķ��ٸ�

	clock_t start, finish;
	start = clock();
	

	
	int* top = new int[topnum];
	for (i = 0; i < topnum; i++) {
		top[i] = abs((rand()+rand()*100000+rand()*10000000))%maxnum;//����Ϊ�����
		//			top[i] = getNum(i);
	}

	buildHeap(top, 0, topnum);// ������С�ѣ� top[0]Ϊ��СԪ��
	for (i = topnum; i < number; i++) {

		int currentNumber2 = abs((rand()+rand()*100000+rand()*10000000))%maxnum;//����Ϊ�����
		//			int currentNumber2 = getNum(i);
		// ���� top[0]�򽻻�currentNumber2  �ع���С��
		if (top[0] < currentNumber2) {
			top[0] = currentNumber2;
			shift(top, 0, topnum, 0); // ������С�� top[0]Ϊ��СԪ��
		}
	}
	//System.out.println(Arrays.toString(top));
	sort(top,topnum);
	//System.out.println(Arrays.toString(top));

	finish = clock();
	printf("����%d����",(finish-start));
	//System.out.println("����"+(endTime.getTime() - startTime.getTime())+"����");

}

//������������
void buildHeap(int* array, int from, int len) 
{
	int pos = (len - 1) / 2;
	for (int i = pos; i >= 0; i--) 
	{
		shift(array, from, len, i);
	}
}
/**
* @param array top����
* @param from ��ʼ
* @param len ���鳤��
* @param pos ��ǰ�ڵ�index
* */
void shift(int* array,int from, int len, int pos) 
{
	// ����ýڵ��ֵ 
	int tmp = array[from + pos];

	int index = pos * 2 + 1;// �õ���ǰpos�ڵ����ڵ�
	while (index < len)//  ������ڵ�
	{
		if (index + 1 < len
			&& array[from + index] > array[from + index + 1])// ��������ҽڵ�
		{
			// ����ұ߽ڵ����߽ڵ�С���ͺ��ұߵıȽ�
			index += 1;
		}

		if (tmp > array[from + index]) 
		{
			array[from + pos] = array[from + index];
			pos = index;
			index = pos * 2 + 1;
		} else 
		{
			break;
		}
	}
	// ����ȫ���û���Ϻ� ������ʱ�����������Ľڵ�
	array[from + pos] = tmp;
}


void sort(int* array,int arrayLen)
{  
	for(int i = 0; i < arrayLen - 1; i++)
	{  
		//��ǰֵ������Сֵ  
		int min = array[i];  
		for(int j = i+1; j < arrayLen; j++)
		{  
			if(min>array[j])
			{  
				//��������б�minֵ��С�ľͽ���  
				min = array[j];  
				array[j] = array[i];  
				array[i] = min;  
			}  
		}  
	}  
}


