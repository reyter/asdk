#pragma once

//无效的float
const	BYTE	INVALIDF[8] = {0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
#define SetInValid(x) { memcpy(&x,INVALIDF,sizeof(float)); }

BOOL    InValid(float  x);
//float	SetInValid(float & x);
short	SkipInvalid(float*fpData,short nDataNum);
void	QSetInValid(float*fpData,int nDataNum,unsigned long InValidByte=0xFFFFFF7F);
float* Calc_Ma(float * c_fRet,float* c_fValue,int c_nCount,unsigned short c_usNum);
float* Calc_Ema(float*fRet,float*fPa,int c_nCount,int c_num);
float* Calc_Sma(float*fRet,float*fPa,int c_nCount,int c_num,int c_nWeight);
float *  Calc_LLV(float * fRet,float *fData,int c_nCount,int c_num);
float *  Calc_HHV(float * fRet,float *fData,int c_nCount,int c_num);
float * Calc_Std(float*fRet,float*fPa,int c_nItemCount,short c_sNum);       //估算标准差
float * Calc_Slope(float*fRet,float*fPa,int c_nItemCount,short c_sNum);       //SLOPE

void FormatSysDateTime(char *c_pTime);