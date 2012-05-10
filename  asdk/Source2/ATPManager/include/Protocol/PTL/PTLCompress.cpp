#include "stdafx.h"
#include "PTLCompress.h"


int ptl_compress(const Atp_Algorithm_Info* pAlgoInfo,
				 int nItems,
				 char* pData,
				 int nLength)
{
	int nTotalclen = 0;
	

	for(int i=0;i<nItems;++i)
	{
		int nThisclen=0;
		
		char* pLastPos = pData;	//保留指针.

		int *pLen = (int*)pData;

		pData += sizeof(int);
		nTotalclen += sizeof(int);



		//全量解压
		NCH_BEGIN_CMP_VERSION(pData,nLength ,1)	

			memcpy(pData,&pAlgoInfo[i].guidAlgo,sizeof(pAlgoInfo[i].guidAlgo));
			pData += sizeof(pAlgoInfo[i].guidAlgo);

			NCH_CMP_STRING_STEP(pData,pAlgoInfo[i].szAlgoName);
			NCH_CMP_STRING_STEP(pData,pAlgoInfo[i].szAlgoDescription);
			NCH_CMP_INT_STEP(pData,pAlgoInfo[i].nParamInfo);
		NCH_END_CMP(pData,nThisclen);


		nTotalclen += nThisclen;

		*pLen = nThisclen;	//回改数据.

		pData	 = pLastPos +  sizeof(int) + nThisclen;	//向后移

	}
	
	return nTotalclen;	//返回长度.


}



/**
*	解压缩算法信息 
*
*/
extern int ptl_decmpress(char* pData,
						 int nLength,
						 Atp_Algorithm_Info* pAlgoInfo
						 ,int nItems)
{

	int nTotaldeclen = 0;

	

	for(int i=0;i<nItems;++i)
	{
		int nThisdeclen = 0;

		char* pLastPos = pData;	//保留指针. 

		int nItemLen = *( (int*)pData);	//后面数据长度.

		pData += sizeof(int);
		
		

		//全量解压
		NCH_BEGIN_DCMP_VERSION(pData,nLength ,1)
			memcpy(&pAlgoInfo[i].guidAlgo,pData,sizeof(pAlgoInfo[i].guidAlgo));
			pData += sizeof(pAlgoInfo[i].guidAlgo);

			NCH_DCMP_STRING_STEP(pData,pAlgoInfo[i].szAlgoName,sizeof(pAlgoInfo[i].szAlgoName));
			NCH_DCMP_STRING_STEP(pData,pAlgoInfo[i].szAlgoDescription,sizeof(pAlgoInfo[i].szAlgoDescription));
			NCH_DCMP_INT_STEP(pData,pAlgoInfo[i].nParamInfo);
		NCH_END_DCMP(pData,nThisdeclen);
	
		ASSERT(nItemLen >= nThisdeclen);

		nTotaldeclen += nItemLen + sizeof(int);

		pData  = pLastPos  + nItemLen + sizeof(int);

	}
	return nTotaldeclen;	//返回长度
}



int ptl_compressAlgoParam(const BYTE* pParaterInfo,
								 int nParaterLength,
								 int nParamter,
								 char* pData,
								 int nLength)
{
	int nTotalclen = 0;

	char* pParaterPos = (char*)pParaterInfo;

	for(int i=0;i<nParamter;++i)
	{
		int nThisclen=0;

		char* pLastPos = pData;	//保留指针.

		int *pLen = (int*)pData;

		pData += sizeof(int);
		nTotalclen += sizeof(int);

		int nSourceItemLen = *((int*)pParaterPos);

		Atp_Algoparam_Info item;

		int nSourceItemlen = item.FromByte(pParaterPos,nParaterLength - (pParaterPos - (char*)pParaterInfo) );


		//全量解压
		NCH_BEGIN_CMP_VERSION(pData,nLength ,1)	
			NCH_CMP_INT_STEP(pData,item.nExtraDataLength);	
			NCH_CMP_INT_STEP(pData,item.nType);
			NCH_CMP_STRING_STEP(pData,item.szParamName);
			NCH_CMP_STRING_STEP(pData,item.szParamDescription);
			
			memcpy(pData,&item.defaultValue,sizeof(item.defaultValue));
			pData += sizeof(item.defaultValue);

			memcpy(pData,item.pExtraData,item.nExtraDataLength);
			pData += item.nExtraDataLength;
			
		NCH_END_CMP(pData,nThisclen);

		pParaterPos += nSourceItemlen;



		nTotalclen += nThisclen;

		*pLen = nThisclen;	//回改数据.

		pData	 = pLastPos +  sizeof(int) + nThisclen;	//向后移
	}

	return nTotalclen;	//返回长度.
}


int ptl_decompressAlgoParam(char* pData,
							int nLength,
							Atp_Algoparam_Info* pParam,
							int nItems)
{
	int nTotaldeclen = 0;

	for(int i=0;i<nItems;++i)
	{
		int nThisdeclen = 0;

		char* pLastPos = pData;	//保留指针. 

		int nItemLen = *( (int*)pData);	//后面数据长度.

		pData += sizeof(int);

		

		//全量解压
		NCH_BEGIN_DCMP_VERSION(pData,nLength ,1)
			NCH_DCMP_INT_STEP(pData,pParam[i].nExtraDataLength);
			__int64 iTemp=0;
			NCH_DCMP_INT_STEP(pData,iTemp);
			pParam[i].nType = (ATP_ALGOPARAM_TYPE)iTemp;

			NCH_DCMP_STRING_STEP(pData,pParam[i].szParamName,sizeof(pParam[i].szParamName));
			NCH_DCMP_STRING_STEP(pData,pParam[i].szParamDescription,sizeof(pParam[i].szParamDescription));

			memcpy(&pParam[i].defaultValue,pData,sizeof(pParam[i].defaultValue));
			pData += sizeof(pParam[i].defaultValue);

			pParam[i].SetExtraData((BYTE*)pData,pParam[i].nExtraDataLength);
			pData += pParam[i].nExtraDataLength;

		NCH_END_DCMP(pData,nThisdeclen);

		ASSERT(nItemLen >= nThisdeclen);

		nTotaldeclen += nItemLen + sizeof(int);

		pData  = pLastPos  + nItemLen + sizeof(int);

	}
	return nTotaldeclen;	//返回长度

}
