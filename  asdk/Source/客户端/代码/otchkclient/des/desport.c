/*****************************************************************
 *	文件名		：desport.c
 *	文件功能	：des相关函数	
 *	编程者		：	
 *	初作时间	: 2002/05/27
 *	版本		: 1.0
 *	------------------------------	
 *		时间			修改者		注释	
 *		2002/05/27		Wu Qing		初期作成	
*****************************************************************/

#include "nttype.h"
#include "des.h"
#include "tripledes.h"
#include "hack.h"
#include "spbox.h"

#define F(l,r,S) { \
    work = ((DWORD *)keyin)[S  ]; \
    zork = ((DWORD *)keyin)[S+1];  \
    work ^= r; \
    zork ^= r; \
    zork = ROTATE_RIGHT(zork, 4); \
    l ^= *(DWORD *)((LPBYTE)Spbox[0] + (work      & 0xfc)); \
    l ^= *(DWORD *)((LPBYTE)Spbox[1] + (zork      & 0xfc)); \
    l ^= *(DWORD *)((LPBYTE)Spbox[2] + ((work>> 8)& 0xfc)); \
    l ^= *(DWORD *)((LPBYTE)Spbox[3] + ((zork>> 8)& 0xfc)); \
    l ^= *(DWORD *)((LPBYTE)Spbox[4] + ((work>>16)& 0xfc)); \
    l ^= *(DWORD *)((LPBYTE)Spbox[5] + ((zork>>16)& 0xfc)); \
    l ^= *(DWORD *)((LPBYTE)Spbox[6] + ((work>>24)& 0xfc)); \
    l ^= *(DWORD *)((LPBYTE)Spbox[7] + ((zork>>24)& 0xfc)); }

void DWORDToLittleEndian (
    unsigned char *output,
    const DWORD *input,
    unsigned int len
    );

void DWORDFromLittleEndian (
    DWORD *output,
    const unsigned char *input,
    unsigned int len
    );




/* Encrypt or decrypt a block of data in ECB mode */
void
DES_Des(
        BYTE        *pbOut,
        BYTE        *pbIn,
        void        *keyin,
        int         op
        )
{
    DWORD   left,right, work, zork;

    /* Read input block and place in left, right */
#ifndef BIGENDIAN
    if( (((ULONG)(ULONG_PTR)pbIn) & (sizeof(ULONG_PTR)-1)) == 0 )
    {
        right = ((DWORD *)pbIn)[0];
        left = ((DWORD *)pbIn)[1];
    } 
    else {
        memcpy( &right, pbIn, sizeof(right) );
        memcpy( &left, pbIn+sizeof(right), sizeof(left) );
    }
#else
    DWORDFromLittleEndian (&right, &pbIn[0], sizeof(right));
    DWORDFromLittleEndian (&left, &pbIn[4], sizeof(left));
#endif  /* BIGENDIAN */


    /* Hoey's clever initial permutation algorithm, from Outerbridge
     * (see Schneier p 478)
     *
     * The convention here is the same as Outerbridge: rotate each
     * register left by 1 bit, i.e., so that "left" contains permuted
     * input bits 2, 3, 4, ... 1 and "right" contains 33, 34, 35, ... 32
     * (using origin-1 numbering as in the FIPS). This allows us to avoid
     * one of the two rotates that would otherwise be required in each of
     * the 16 rounds.
     */

    right = ROTATE_LEFT(right, 4);
    work = right;
    right ^= left;
    right &= 0xf0f0f0f0;
    work ^= right;
    left ^= right;

    left = ROTATE_LEFT(left, 20);
    right = work;
    work ^= left;
    work &= 0xfff0000f;
    right ^= work;
    left ^= work;

    left = ROTATE_LEFT(left,14);
    work = right;
    right ^= left;
    right &= 0x33333333;
    work ^= right;
    left ^= right;

    work = ROTATE_LEFT(work, 22);
    right = work;
    work ^= left;
    work &= 0x03fc03fc;
    right ^= work;
    left ^= work;

    right = ROTATE_LEFT(right, 9);
    work = right;
    right ^= left;
    right &= 0xaaaaaaaa;
    work ^= right;
    left ^= right;

    left = ROTATE_LEFT(left, 1);
    right = work;


    /* Now do the 16 rounds */
    if(op == DECRYPT)
    {
#ifdef _X86_
        F(left, right, 30);
        F(right, left, 28);
        F(left, right, 26);
        F(right, left, 24);
        F(left, right, 22);
        F(right, left, 20);
        F(left, right, 18);
        F(right, left, 16);
        F(left, right, 14);
        F(right, left, 12);
        F(left, right, 10);
        F(right, left, 8);
        F(left, right, 6);
        F(right, left, 4);
        F(left, right, 2);
        F(right, left, 0);
#else
        signed int i;

        for(i=30; i > -2 ; i-=4) {
            F(left, right, i);
            F(right, left, i-2);
        }
#endif
    }
    else
    {
#ifdef _X86_
        F(left, right, 0);
        F(right, left, 2);
        F(left, right, 4);
        F(right, left, 6);
        F(left, right, 8);
        F(right, left, 10);
        F(left, right, 12);
        F(right, left, 14);
        F(left, right, 16);
        F(right, left, 18);
        F(left, right, 20);
        F(right, left, 22);
        F(left, right, 24);
        F(right, left, 26);
        F(left, right, 28);
        F(right, left, 30);
#else
        unsigned int i;

        for(i=0; i < 32 ; i+=4) {
            F(left, right, i);
            F(right, left, i+2);
        }
#endif
    }


    /* Inverse permutation, also from Hoey via Outerbridge and Schneier */

    right = ROTATE_RIGHT(right, 1);
    work = left;
    work ^= right;
    work &= 0xaaaaaaaa;
    right ^= work;
    left ^= work;

    left = ROTATE_RIGHT(left, 9);
    work = right;
    right ^= left;
    right &= 0x03fc03fc;
    work ^= right;
    left ^= right;

    left = ROTATE_RIGHT(left, 22);
    right = work;
    work ^= left;
    work &= 0x33333333;
    right ^= work;
    left ^= work;

    right = ROTATE_RIGHT(right, 14);
    work = right;
    right ^= left;
    right &= 0xfff0000f;
    work ^= right;
    left ^= right;

    work = ROTATE_RIGHT(work, 20);
    right = work;
    work ^= left;
    work &= 0xf0f0f0f0;
    right ^= work;
    left ^= work;

    left = ROTATE_RIGHT(left, 4);

    /* Put the block back into the user's buffer with final swap */
#ifndef BIGENDIAN
    if( (((ULONG)(ULONG_PTR)pbOut) & (sizeof(ULONG_PTR)-1)) == 0 )
    {
        ((DWORD *)pbOut)[0] = left;
        ((DWORD *)pbOut)[1] = right;
    }
    else {
        memcpy( pbOut, &left, sizeof(left) );
        memcpy( pbOut+sizeof(left), &right, sizeof(right) );
    }

#else
    DWORDToLittleEndian (&pbOut[0], &left, sizeof(left));
    DWORDToLittleEndian (&pbOut[4], &right, sizeof(right));
#endif  /* BIGENDIAN */
}


/*
**   Encrypt or decrypt with the key in pKey (DES3Table)
*/

void
DES_TripleDes(
        BYTE        *pbOut,
        BYTE        *pbIn,
        void        *pKey,
        int         op
        )
{
    PDES3TABLE  pDES3Table = (PDES3TABLE)pKey;
    BYTE        rgbEnc1[DES_BLOCKLEN];
    BYTE        rgbEnc2[DES_BLOCKLEN];

    if (ENCRYPT == op)      /* encrypt case */
    {
        DES_Des(rgbEnc1, pbIn, &pDES3Table->keytab1, ENCRYPT);
        DES_Des(rgbEnc2, rgbEnc1, &pDES3Table->keytab2, DECRYPT);
        DES_Des(pbOut, rgbEnc2, &pDES3Table->keytab3, ENCRYPT);
    }
    else                    /* decrypt case */
    {
        DES_Des(rgbEnc1, pbIn, &pDES3Table->keytab3, DECRYPT);
        DES_Des(rgbEnc2, rgbEnc1, &pDES3Table->keytab2, ENCRYPT);
        DES_Des(pbOut, rgbEnc2, &pDES3Table->keytab1, DECRYPT);
    }


    ((UINT *)rgbEnc1)[0] = 0;
    ((UINT *)rgbEnc2)[0] = 0;
}


void DWORDToLittleEndian (
    unsigned char *output,
    const DWORD *input,
    unsigned int len
    )
{
#ifdef BIGENDIAN
  unsigned int i, j;

  if(output == (unsigned char *)input) {

    for (i = 0 ; i < len / sizeof(DWORD) ; i++) {
      j = (input[i] << 16) | (input[i] >> 16);
      ((DWORD*)output)[i] = ((j & 0xFF00FF00) >> 8) | ((j & 0x00FF00FF) << 8);
    }
  } else {

    for (i = 0, j = 0; j < len; i++, j += 4) {
      output[j] = (unsigned char)(input[i] & 0xff);
      output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
      output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
      output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
    }
  }
#else
  memcpy(output, (unsigned char *)input, len);
#endif

}

void DWORDFromLittleEndian (
    DWORD *output,
    const unsigned char *input,
    unsigned int len
    )
{
#ifdef BIGENDIAN
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4)
    output[i] = ((DWORD)input[j]) | (((DWORD)input[j+1]) << 8) |
      (((DWORD)input[j+2]) << 16) | (((DWORD)input[j+3]) << 24);
#else
  memcpy((unsigned char *)output, input, len);
#endif
}


