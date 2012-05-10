/*****************************************************************
 *  文件名      ：des.h
 *  文件功能    ：des加密头文件，标准的des加密函数
 *  编程者      ：Wu Qing
 *  初作时间    ：2002/5/22
 *  版本        : 1.0
 *  ------------------------------
 *      时间                修改者      注释
 *      2002／05／22        Wu Qing     创建
*****************************************************************/

#ifndef __DES_H__
#define __DES_H__

#include "nttype.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 操作常量*/
#define ENCRYPT     1
#define DECRYPT     0

typedef struct  _destable{
    unsigned long   keytab[16][2];
} DESTable;

#define DES_TABLESIZE   (sizeof(DESTable))
#define DES_BLOCKLEN    (8)/*每次进行加密操作的块的长度*/
#define DES_KEYSIZE     (8)/*要求密码的长度*/

typedef struct _desxtable {
    unsigned char inWhitening[8];
    unsigned char outWhitening[8];
    DESTable desTable;
} DESXTable;

#define DESX_TABLESIZE  (sizeof(DESXTable))
#define DESX_BLOCKLEN   (8)
#define DESX_KEYSIZE    (24)

void DES_DesKey(DESTable *,unsigned char *);
void DES_Des(UCHAR *pbOut, UCHAR *pbIn, void *key, int op);
/*
示例：
char acFrom[9],acTo[9],acKey[9];
DESTable dt;

memset(acFrom,0,9);
memset(acTo,0,9);
memset(acKey,0,9);

sprintf(acFrom,"TEST STR");
sprintf(acKey,"TEST KEY");

DES_DesKey(&dt,acKey);首先生成key
DES_Des(acTo,acFrom,&dt,ENCRYPT);加密操作，8个字节

DES_Des(acFrom,acTo,&dt,DECRYPT);解密操作，8个字节，也必须先生成key，此处省略了
*/

#ifdef __cplusplus
}
#endif

#endif /* __DES_H__*/

