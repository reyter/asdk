/*****************************************************************
 *  文件名：tripledes.h
 *  文件功能：加密头文件，标准的3des函数，此处提供了3key加密8字节的方法
 *  编程者：Wu Qing
 *  初作时间：2002/5/22
 *  版本: 1.0
 *  ------------------------------
 *时间    修改者注释
 *2002／05／22    Wu Qing创建
*****************************************************************/

#ifndef __TRIPLDES_H__
#define __TRIPLDES_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef struct _DES3TABLE {
    DESTable    keytab1;
    DESTable    keytab2;
    DESTable    keytab3;
} DES3TABLE, *PDES3TABLE;

#define DES3_TABLESIZE  sizeof(DES3TABLE)
#define DES2_KEYSIZE    16
#define DES3_KEYSIZE    24/*密码长度*/

void DES_TripleDes2Key(PDES3TABLE pDES3Table, BYTE *pbKey);

void DES_TripleDes3Key(PDES3TABLE pDES3Table, BYTE *pbKey);

void DES_TripleDes(BYTE *pbOut, BYTE *pbIn, void *pKey, int op);
/*
示例：
char acFrom[9],acTo[9],acKey[25];
DES3TABLE dt;

memset(acFrom,0,9);
memset(acTo,0,9);
memset(acKey,0,25);

sprintf(acFrom,"TEST STR");
sprintf(acKey,"TEST KEY1234567812345678");

DES_DesKey(&dt,acKey);首先生成key
DES_Des(acTo,acFrom,&dt,ENCRYPT);加密操作，8个字节

DES_Des(acFrom,acTo,&dt,DECRYPT);解密操作，8个字节，也必须先生成key，此处省略了
*/

#ifdef __cplusplus 
}
#endif

#endif /* __TRIPLDES_H__ */

