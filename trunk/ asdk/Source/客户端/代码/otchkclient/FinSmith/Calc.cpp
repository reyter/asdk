#include "stdafx.h"
#include "Calc.h"

BOOL    InValid(float  x)
{
	BOOL	ret = memcmp(&x,INVALIDF,sizeof(float));
	return (ret==0);
}

//设置成为无效数字
#define SetInValid(x) { memcpy(&x,INVALIDF,sizeof(float)); }

//跳过无效数字
__declspec( naked ) int SkipInvalid(float*fpData,int nDataNum,unsigned long InValidByte=0xFFFFFF7F)
{
    __asm
	{
		push	ebp
		mov		ebp, esp
		sub     esp, __LOCAL_SIZE
		;----------------------
		mov     eax,[InValidByte]
		mov		edi,[fpData]
		mov		ecx,0
	
Copy_Loop:
		cmp		[edi+ecx*4],eax
		jne		Invalid_Break
		inc		ecx
		cmp     ecx,nDataNum
		jne		Copy_Loop
Invalid_Break:
		mov	    eax,ecx		
		;----------------------
		mov		esp, ebp
		pop     ebp
		ret
	}
}

//函数功能：裸函数，快速跳过无效数字
//函数参数：fpData是目标数组，nDataNum是个数，InValidByte是无效数字
//函数返回：返回跳过几个
void QSetInValid(float*fpData,int nDataNum,unsigned long InValidByte)
{
    __asm
	{
		mov     eax,[InValidByte]
		mov		edi,[fpData]
		mov		ecx,0
			
Copy_Loop:
		mov		[edi+ecx*4],eax
		inc		ecx
		cmp     ecx,nDataNum
		jne		Copy_Loop
		mov	    eax,ecx		
	}
}


//简单平均
//float * fRet;				返回
//float * fValue;			值
//int c_nCount;				个数
//unsigned short c_usNum	周期
float* Calc_Ma(float * c_fRet,float* c_fValue,int c_nCount,unsigned short c_usNum)
{
	float	fval=0;
	short	j=SkipInvalid(c_fValue,c_nCount),i=j;//跳过无效的数字
	
	QSetInValid(c_fRet,c_nCount);//设置返回值
	if(c_usNum < 1 || c_usNum+i > c_nCount) //有效数太少,不需要计算
	{
		return c_fRet;
	}
	for(;i<c_nCount && InValid(c_fValue[i]);i++);	
	for(;i<j+c_usNum;i++)
	{
		if ( InValid(c_fValue[i]) && i-1>0 )
			c_fValue[i] = c_fValue[i-1];		
		fval += c_fValue[i];
	} 
	for(c_fRet[i-1]=fval/c_usNum;i<c_nCount;i++)
	{	
		if(i-c_usNum>=0 && !InValid(c_fValue[i]) && !InValid(c_fValue[i-c_usNum]))
		{
			fval+=(c_fValue[i]-c_fValue[i-c_usNum]);  //出了num,num是fPb参数跳跃,但是i-num要大于j
			c_fRet[i] = fval/c_usNum;
		}
		else
		{
			continue;
		}
	}
	return c_fRet;
}

/*几何函数: @{
Class=AGOY_FUNC,Code=EMA,Name=异同移动平均,Param="220",Call=Sys_Ema,
Info="返回异同移动平均
用法:
EMA(X,M):X的M日异同移动平均"}@ */
//异同移动平均,算法：EMA=(buffer[i] * 2+(para-1)*EMA[i-1])/(para+1)
float* Calc_Ema(float*fRet,float*fPa,int c_nCount,int c_num)
{
	short i=0; 
	QSetInValid(fRet,c_nCount);		
	for(;i<c_nCount && InValid(fPa[i]);i++);
	if(c_num<1 || c_num+i>c_nCount) return fRet; 
	
	for(fRet[i]=fPa[i++];i<c_nCount;i++)
	{
		fRet[i]=(2*fPa[i]+(c_num-1)*fRet[i-1])/(c_num+1);
	}
	return fRet;
}
//EMA加入权重
float* Calc_Sma(float*fRet,float*fPa,int c_nCount,int c_num,int c_nWeight)
{
	short i=0; 
	QSetInValid(fRet,c_nCount);		
	for(;i<c_nCount && InValid(fPa[i]);i++);
	if(c_num<1 || c_num+i>c_nCount) return fRet; 
	
	for(fRet[i]=fPa[i++];i<c_nCount;i++)
	{
		fRet[i]=(fPa[i]*c_nWeight+(c_num-c_nWeight)*fRet[i-1])/(c_num);
	}
	return fRet;
}

//c_num日最低
float * Calc_LLV(float * fRet,float *nP,int c_nCount,int c_num)
{
	if(c_nCount == 0 || c_num == 0 || c_nCount < c_num)
		return fRet;

	for(int n=0; n<c_nCount; n++)
		fRet[n] = nP[n];

	for(int k=0; k<c_nCount; k++)
	{
		for(int n=0; n<c_num; n++)		
		{
			if(k-n >= 0)
			{
				if (fRet[k] > nP[k-n])
					fRet[k] = nP[k-n];
			}
		}
	}
	return fRet;
}
//c_num日最高
float * Calc_HHV(float * fRet,float *nP,int c_nCount,int c_num)
{
	if(c_nCount == 0 || c_num == 0 || c_nCount < c_num)
		return fRet;

	for(int n=0; n<c_nCount; n++)
		fRet[n] = nP[n];

	for(int k=0; k<c_nCount; k++)
	{
		for(int n=0; n<c_num; n++)		
		{
			if(k-n >= 0)
			{
				if (fRet[k] < nP[k-n])
					fRet[k] = nP[k-n];
			}
		}
	}
	return fRet;
}

float * Calc_Std(float*fRet,float*fPa,int c_nItemCount,short c_sNum)       //估算标准差
{	
	short	num=c_sNum;
	float	Exp=0,DeltaPower=0;	//期望
	int		i=0,j=0,k=0;
	//初始化
	QSetInValid(fRet,c_nItemCount);
	//跳过无效数字
	for(;i<c_nItemCount&&InValid(fPa[i]);i++);
	if(num<1||num+i>c_nItemCount) 
		return fRet;
	for(Exp=0,DeltaPower=0;i<c_nItemCount&&j<num;i++,j++)
		Exp+=fPa[i]/num;
	if(j==num)
	{	
		for(i--;k<num;k++) 
			DeltaPower += (fPa[i-k]-Exp)*(fPa[i-k]-Exp);
		fRet[i++]=(float)sqrt(DeltaPower/num);
	}
	for(;i<c_nItemCount;i++)
	{  
		Exp+=(fPa[i]-fPa[i-num])/num;
		for(DeltaPower=0,k=0;k<num;k++) 
			DeltaPower +=(fPa[i-k]-Exp)*(fPa[i-k]-Exp);
		fRet[i]=(float)sqrt(DeltaPower/num);
	}
	return fRet;
}

float * Calc_Slope(float*fRet,float*fPa,int c_nItemCount,short c_sNum)       //SLOPE
{	
	short	num=c_sNum;
	float	Exp=0,DeltaPower=0;	//期望
	int		i=0,j=0,k=0;
	float fYAvg = 0;
	for(int n=1; n<=c_sNum; n++)
	{
		fYAvg += n;
	}
	fYAvg /= c_sNum;//平均数

	float *fY = new float[c_sNum];
	float fDiv = 0;
	for(int n=1; n<=c_sNum; n++)
	{
		fY[n-1] = n;
		fY[n-1] -= fYAvg;
		fDiv += fY[n-1] * fY[n-1];
	}
	//初始化
	QSetInValid(fRet,c_nItemCount);
	//跳过无效数字
	for(;i<c_nItemCount&&InValid(fPa[i]);i++);
	if(num<1||num+i>c_nItemCount) 
	{
		delete [] fY;
		return fRet;
	}
	i += num;
	if (i > c_nItemCount)
	{
		delete [] fY;
		return fRet;
	}
	i--;
	for(;i<c_nItemCount;i++)
	{  	
		float fXAvg = 0;
		for(int k=i; k>i-num; k--)
		{
			fXAvg += fPa[k];
		}
		fXAvg /= num;
		float a = 0;
		;
		for(int k=i; k>i-num; k--)
		{
			a += fY[num-(i-k)-1] * (fPa[k] - fXAvg);
		}
		fRet[i] = a / fDiv;
	}
	delete [] fY;
	return fRet;
}
