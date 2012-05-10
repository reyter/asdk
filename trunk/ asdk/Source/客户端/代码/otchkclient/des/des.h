/*****************************************************************
 *  �ļ���      ��des.h
 *  �ļ�����    ��des����ͷ�ļ�����׼��des���ܺ���
 *  �����      ��Wu Qing
 *  ����ʱ��    ��2002/5/22
 *  �汾        : 1.0
 *  ------------------------------
 *      ʱ��                �޸���      ע��
 *      2002��05��22        Wu Qing     ����
*****************************************************************/

#ifndef __DES_H__
#define __DES_H__

#include "nttype.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ��������*/
#define ENCRYPT     1
#define DECRYPT     0

typedef struct  _destable{
    unsigned long   keytab[16][2];
} DESTable;

#define DES_TABLESIZE   (sizeof(DESTable))
#define DES_BLOCKLEN    (8)/*ÿ�ν��м��ܲ����Ŀ�ĳ���*/
#define DES_KEYSIZE     (8)/*Ҫ������ĳ���*/

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
ʾ����
char acFrom[9],acTo[9],acKey[9];
DESTable dt;

memset(acFrom,0,9);
memset(acTo,0,9);
memset(acKey,0,9);

sprintf(acFrom,"TEST STR");
sprintf(acKey,"TEST KEY");

DES_DesKey(&dt,acKey);��������key
DES_Des(acTo,acFrom,&dt,ENCRYPT);���ܲ�����8���ֽ�

DES_Des(acFrom,acTo,&dt,DECRYPT);���ܲ�����8���ֽڣ�Ҳ����������key���˴�ʡ����
*/

#ifdef __cplusplus
}
#endif

#endif /* __DES_H__*/

