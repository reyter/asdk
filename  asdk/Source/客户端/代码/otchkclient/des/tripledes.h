/*****************************************************************
 *  �ļ�����tripledes.h
 *  �ļ����ܣ�����ͷ�ļ�����׼��3des�������˴��ṩ��3key����8�ֽڵķ���
 *  ����ߣ�Wu Qing
 *  ����ʱ�䣺2002/5/22
 *  �汾: 1.0
 *  ------------------------------
 *ʱ��    �޸���ע��
 *2002��05��22    Wu Qing����
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
#define DES3_KEYSIZE    24/*���볤��*/

void DES_TripleDes2Key(PDES3TABLE pDES3Table, BYTE *pbKey);

void DES_TripleDes3Key(PDES3TABLE pDES3Table, BYTE *pbKey);

void DES_TripleDes(BYTE *pbOut, BYTE *pbIn, void *pKey, int op);
/*
ʾ����
char acFrom[9],acTo[9],acKey[25];
DES3TABLE dt;

memset(acFrom,0,9);
memset(acTo,0,9);
memset(acKey,0,25);

sprintf(acFrom,"TEST STR");
sprintf(acKey,"TEST KEY1234567812345678");

DES_DesKey(&dt,acKey);��������key
DES_Des(acTo,acFrom,&dt,ENCRYPT);���ܲ�����8���ֽ�

DES_Des(acFrom,acTo,&dt,DECRYPT);���ܲ�����8���ֽڣ�Ҳ����������key���˴�ʡ����
*/

#ifdef __cplusplus 
}
#endif

#endif /* __TRIPLDES_H__ */

