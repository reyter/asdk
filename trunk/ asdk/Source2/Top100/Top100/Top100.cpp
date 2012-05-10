// Top100.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Top100.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

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
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			_tprintf(_T("错误: MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: 在此处为应用程序的行为编写代码。
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
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}



// Top100.cpp : 定义控制台应用程序的入口点。
//






void find()
{//
	int number = 100000000;// 一亿个数
	int maxnum = 1000000000;// 随机数最大值
	int i = 0;
	int topnum = 100;// 取最大的多少个

	clock_t start, finish;
	start = clock();
	

	
	int* top = new int[topnum];
	for (i = 0; i < topnum; i++) {
		top[i] = abs((rand()+rand()*100000+rand()*10000000))%maxnum;//设置为随机数
		//			top[i] = getNum(i);
	}

	buildHeap(top, 0, topnum);// 构建最小堆， top[0]为最小元素
	for (i = topnum; i < number; i++) {

		int currentNumber2 = abs((rand()+rand()*100000+rand()*10000000))%maxnum;//设置为随机数
		//			int currentNumber2 = getNum(i);
		// 大于 top[0]则交换currentNumber2  重构最小堆
		if (top[0] < currentNumber2) {
			top[0] = currentNumber2;
			shift(top, 0, topnum, 0); // 构建最小堆 top[0]为最小元素
		}
	}
	//System.out.println(Arrays.toString(top));
	sort(top,topnum);
	//System.out.println(Arrays.toString(top));

	finish = clock();
	printf("用了%d毫秒",(finish-start));
	//System.out.println("用了"+(endTime.getTime() - startTime.getTime())+"毫秒");

}

//构造排序数组
void buildHeap(int* array, int from, int len) 
{
	int pos = (len - 1) / 2;
	for (int i = pos; i >= 0; i--) 
	{
		shift(array, from, len, i);
	}
}
/**
* @param array top数组
* @param from 开始
* @param len 数组长度
* @param pos 当前节点index
* */
void shift(int* array,int from, int len, int pos) 
{
	// 保存该节点的值 
	int tmp = array[from + pos];

	int index = pos * 2 + 1;// 得到当前pos节点的左节点
	while (index < len)//  存在左节点
	{
		if (index + 1 < len
			&& array[from + index] > array[from + index + 1])// 如果存在右节点
		{
			// 如果右边节点比左边节点小，就和右边的比较
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
	// 最终全部置换完毕后 ，把临时变量赋给最后的节点
	array[from + pos] = tmp;
}


void sort(int* array,int arrayLen)
{  
	for(int i = 0; i < arrayLen - 1; i++)
	{  
		//当前值当作最小值  
		int min = array[i];  
		for(int j = i+1; j < arrayLen; j++)
		{  
			if(min>array[j])
			{  
				//如果后面有比min值还小的就交换  
				min = array[j];  
				array[j] = array[i];  
				array[i] = min;  
			}  
		}  
	}  
}


