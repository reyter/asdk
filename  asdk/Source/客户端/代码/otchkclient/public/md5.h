/*****************************************************************
 *  文件名：	md5.h
 *  文件功能：	md5.c头文件
 *  编程者：	Wu Qing
 *  初作时间：	2002/5/22
 *  版本: 		1.0
 *  ------------------------------
 *			时间    			修改者			注释
 *			2002／05／22    	Wu Qing			创建
*****************************************************************/

/* typedef a 32-bit type */ 
typedef long int32; 
typedef unsigned long uint32; 
typedef unsigned long int UINT4; 
 
/* Data structure for MD5 (Message-Digest) computation */ 
typedef struct { 
    UINT4 i[2];            /* number of _bits_ handled mod 2^64*/
    UINT4 buf[4];          /* scratch buffer */
    unsigned char in[64];  /* input buffer */
    unsigned char digest[16];   /* actual digest after MD5Final call */
} MD5_CTX; 
 
#define SIG_MAX_LEN 200 
 
void  MD5_Init(); 
void  MD5_Update(); 
void  MD5_Final(); 
int	MD5_Sig_Get(unsigned char * pczSrc,int iSrcLen,char * pczSig,int iSigLen);
