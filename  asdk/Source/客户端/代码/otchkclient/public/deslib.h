/*****************************************************************
 *  ÎÄ¼þÃû      £ºdeslib.h
*****************************************************************/

#ifndef __DES_LIB_H__
#define __DES_LIB_H__

#ifdef __cplusplus
extern "C" {
#endif

int Encrypt(char * c_pIn,int c_nInLen,char * c_pOut,char * c_pKey);
int Decrypt(char * c_pIn,int c_nInLen,char * c_pOut,char * c_pKey);

#ifdef __cplusplus
}
#endif

#endif /* __DES_LIB_H__*/

