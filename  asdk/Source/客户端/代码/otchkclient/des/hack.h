/*------------------------------------------------------------------------------
** Copyright (c) Microsoft Corporation.  All rights reserved.
**
** File Name:   hack.h
**
**------------------------------------------------------------------------------*/
#ifndef _HACK_H_
#define _HACK_H_


/* ROTATE_LEFT rotates x left n bits.
 */
#ifndef NO_INLINE_ROTATE
#define ROTATE_LEFT(x, n) _rotl((x), (n))
#else
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#endif /* UNDER_CE*/

/* ROTATE_RIGHT rotates x right n bits.
 */
#ifndef NO_INLINE_ROTATE
#define ROTATE_RIGHT(x, n) _rotr((x), (n))
#else
#define ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (32-(n))))
#endif /* UNDER_CE */



/* rotlr functions */

extern unsigned int _rotl(unsigned int value, int shift);
extern unsigned int _rotr(unsigned int value, int shift);

#endif


