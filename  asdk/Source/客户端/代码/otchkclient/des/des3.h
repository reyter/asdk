/*------------------------------------------------------------------------------
** Copyright (c) Microsoft Corporation.  All rights reserved.
**
** File Name:    des3.h
**
**------------------------------------------------------------------------------*/

#ifndef __DES3_H__
#define __DES3_H__

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
#define DES3_KEYSIZE    24

// In des2key.c:
//
//   Fill in the DES3Table structs with the decrypt and encrypt
//   key expansions.
//
//   Assumes that the second parameter points to 2 * DES_BLOCKLEN
//   bytes of key.
//
//

void  des2key(PDES3TABLE pDES3Table, PBYTE pbKey);

// In des3key.c:
//
//   Fill in the DES3Table structs with the decrypt and encrypt
//   key expansions.
//
//   Assumes that the second parameter points to 3 * DES_BLOCKLEN
//   bytes of key.
//
//

void  des3key(PDES3TABLE pDES3Table, PBYTE pbKey);

//
//   Encrypt or decrypt with the key in pKey
//

void  des3(PBYTE pbIn, PBYTE pbOut, void *pKey, int op);

//
// set the parity on the DES key to be odd
//

void  desparity(PBYTE pbKey, DWORD cbKey);

#ifdef __cplusplus
}
#endif

#endif // __DES3_H__

