/*****************************************************************
 *	文件名		：deskey.c
 *	文件功能	：key相关的函数	
 *	编程者		：	
 *	初作时间	: 2002/05/27
 *	版本		: 1.0
 *	------------------------------	
 *		时间			修改者		注释	
 *		2002/05/27		Wu Qing		初期作成	
*****************************************************************/

#include <string.h>

#include "nttype.h"
#include "des.h"
#include "tripledes.h"
#include "hack.h"
#include "sel.h"
#include "deslib.h"


/* really BOOL flags compressed to byte */
const unsigned char double_shift[16]={0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0};
extern const DWORD Sel[8][64];

#define PERM_OP(a,b,t,n,m) ((t)=((((a)>>(n))^(b))&(m)),\
    (b)^=(t),\
    (a)^=((t)<<(n)))

#define HPERM_OP(a,t,n,m) ((t)=((((a)<<(16-(n)))^(a))&(m)),\
    (a)=(a)^(t)^(t>>(16-(n))))





/* Generate key schedule for encryption or decryption
 * depending on the value of "decrypt"
 */
void
DES_DesKey(
        DESTable        *k,
        BYTE            *key
        )
{
    DWORD csel,dsel,t,s;
    DWORD i;

    DWORD *kp = (DWORD *)k;

#ifndef BIGENDIAN
    csel = ((DWORD *)key)[0];
    dsel = ((DWORD *)key)[1];
#else
    DWORDFromLittleEndian (&csel, &key[0], sizeof(csel));
    DWORDFromLittleEndian (&dsel, &key[4], sizeof(dsel));
#endif  /* BIGENDIAN */

    PERM_OP (dsel,csel,t,4,0x0f0f0f0f);
    HPERM_OP(csel,t,-2,0xcccc0000);
    HPERM_OP(dsel,t,-2,0xcccc0000);
    PERM_OP (dsel,csel,t,1,0x55555555);
    PERM_OP (csel,dsel,t,8,0x00ff00ff);
    PERM_OP (dsel,csel,t,1,0x55555555);
    dsel=  (((dsel & 0x000000ff) << 16) | (dsel & 0x0000ff00)    |
            ((dsel & 0x00ff0000) >> 16) | ((csel & 0xf0000000)>>4));
    csel &= 0x0fffffff;

    for(i = 0; i < 16; i++)
    {
        DWORD temp;

        if(double_shift[i]) {
            csel = ((csel >> 2) | (csel << 26));
            dsel = ((dsel >> 2) | (dsel << 26));
        } else {
            csel = ((csel >> 1) | (csel << 27));
            dsel = ((dsel >> 1) | (dsel << 27));
        }

        csel &= 0x0fffffff;
        dsel &= 0x0fffffff;

        s =  Sel[0][ (csel      )&0x3f                ];
        s |= Sel[1][((csel >>  6)&0x03) | ((csel >>  7)&0x3c)];
        s |= Sel[2][((csel >> 13)&0x0f) | ((csel >> 14)&0x30)];
        s |= Sel[3][((csel >> 20)&0x01) | ((csel >> 21)&0x06)|((csel >> 22)&0x38)];
        t =  Sel[4][ (dsel      )&0x3f                ];
        t |= Sel[5][((dsel >>  7)&0x03) | ((dsel >>  8)&0x3c)];
        t |= Sel[6][ (dsel >> 15)&0x3f                ];
        t |= Sel[7][((dsel >> 21)&0x0f) | ((dsel >> 22)&0x30)];

        temp = ((t << 16) | (s & 0x0000ffff)) ;
        *(kp++) = ROTATE_LEFT(temp, 2);

        temp = ((s >> 16) | (t & 0xffff0000));
        *(kp++) = ROTATE_LEFT(temp, 6);
    }
}

BYTE DESParityTable[] = {0x00,0x01,0x01,0x02,0x01,0x02,0x02,0x03,
                      0x01,0x02,0x02,0x03,0x02,0x03,0x03,0x04};

/*
** set the parity on the DES key to be odd
** NOTE : must be called before DES_DesKey
** key must be cbKey number of bytes
*/

void
DES_DesParityonKey(
        BYTE            *pbKey,
        DWORD           cbKey
        )
{
    DWORD i;

    for (i=0;i<cbKey;i++)
    {
        if (!((DESParityTable[pbKey[i]>>4] + DESParityTable[pbKey[i]&0x0F]) % 2))
            pbKey[i] = pbKey[i] ^ 0x01;
    }
}


/*   DES_TripleDes2Key:
**
**   Fill in the DES3Table structs with the decrypt and encrypt
**   key expansions.
**
**   Assumes that the second parameter points to 2 * DES_BLOCKLEN
**   bytes of key.
**
*/

void
DES_TripleDes2Key(
        PDES3TABLE      pDES3Table,
        BYTE            *pbKey
        )
{
    int iLen;

    DES_DesKey(&pDES3Table->keytab1, pbKey);
    DES_DesKey(&pDES3Table->keytab2, pbKey+DES_KEYSIZE);
    memcpy(&pDES3Table->keytab3, &pDES3Table->keytab1, DES_TABLESIZE);
}

/*   DES_TripleDes3Key:
**
**   Fill in the DES3Table structs with the decrypt and encrypt
**   key expansions.
**
**   Assumes that the second parameter points to 3 * DES_BLOCKLEN
**   bytes of key.
**
*/

void
DES_TripleDes3Key(
        PDES3TABLE      pDES3Table,
        BYTE            *pbKey
        )
{
    DES_DesKey(&pDES3Table->keytab1, pbKey);
    DES_DesKey(&pDES3Table->keytab2, pbKey+DES_KEYSIZE);
    DES_DesKey(&pDES3Table->keytab3, pbKey+2*DES_KEYSIZE);
}


int Encrypt(char * c_pIn,int c_nInLen,char * c_pOut,char * c_pKey)
{
	DESTable dt;
	int n;
	if(c_nInLen % 8 > 0)
		return -1;

	DES_DesKey(&dt,c_pKey);	//首先生成key
	for(n=0; n<c_nInLen/8; n++)
		DES_Des(c_pOut + n * 8,c_pIn + n * 8,&dt,ENCRYPT);//加密
	return c_nInLen;
}


int Decrypt(char * c_pIn,int c_nInLen,char * c_pOut,char * c_pKey)
{
	DESTable dt;
	int n;
	if(c_nInLen % 8 > 0)
		return -1;

	DES_DesKey(&dt,c_pKey);	//首先生成key
	for(n=0; n<c_nInLen/8; n++)
		DES_Des(c_pOut + n * 8,c_pIn + n * 8,&dt,DECRYPT);//加密
	return c_nInLen;
}
