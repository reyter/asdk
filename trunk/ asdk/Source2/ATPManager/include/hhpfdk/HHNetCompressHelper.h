
/**
* @copyright �����д���Ƽ����޹�˾
* @system    HHPfdk   (Honghui Public Function development kit)
* @brief	   ͨѶ���ݳ���ѹ������
* @author	 wli
* @histroy
-------------------------------------------------------------
2008-06-05			wli                   ����Double�����ض����⡣���� NCH_(D)CMP_CHAR_STEP ��
-------------------------------------------------------------
*/
#pragma once

#pragma warning(disable:4244)	//�ӡ�double��ת������__int64�������ܶ�ʧ����

/**
* ����ָ��.
* @param pData Ҫ�����ָ��,ͨ��Ϊ(char*).
* @param nPos  �����ǣ�����Ϊ���ֻ����ַ���.
*/ 
#define NCH_SAVE_POINT(pData,nPos) char* __pSave_nch_point##pData##nPos = (char*)pData;


/**
* ��pData��ԭ������λ�á�
*/
#define NCH_RESTORE_POINT(pData,nPos)	pData = __pSave_nch_point##pData##nPos;

/**
* ����ѹ�������ݱ���.
*/
#define NCH_CALC_SIZE(pData,nSavePos)	(int)((pData - (char*)(__pSave_nch_point##pData##nSavePos)))


/**
* ��ʼѹ��.
* @param pData ���ڴ洢ѹ�����ݵĵ�ַ.
* @param nLength  pData�ĳ���.
* @param nVersion       0 NCH_CMP_INT_STEP ԭ INTѹ����  ( 1 NCH_CMP_INT_STEP ���ԭ INT64ѹ��.)
*/
#define NCH_BEGIN_CMP_VERSION(pData,nLength,nVersion) {\
	NCH_SAVE_POINT(pData,__nch_cmp_begin__);\
	int __nch_cmp_version  = nVersion;\
	int __nch_cmp_length__ = nLength;


/**
* ��ʼѹ��.
* @param pData ���ڴ洢ѹ�����ݵĵ�ַ.
* @param nLength  pData�ĳ���.
*/
#define NCH_BEGIN_CMP(pData,nLength) NCH_BEGIN_CMP_VERSION(pData,nLength,0)




/** 
* ����ѹ��.
* @param pData ���ڴ洢ѹ�����ݵĵ�ַ.
* @param ncmpLength ѹ�������ݵĳ���.
*/
#define NCH_END_CMP(pData,ncmpLength)	ncmpLength = NCH_CALC_SIZE(pData,__nch_cmp_begin__);\
	NCH_RESTORE_POINT(pData,__nch_cmp_begin__);\
	}


/**
* ��ʼ��ѹ.
* @param pData			Ҫ��ѹ�������ݷ�����ڴ�.
* @param nLength		nLength �ڴ���ܳ���.
* @param nVersion       0 NCH_DCMP_INT_STEP ԭ INT��ѹ��  ( 1 NCH_DCMP_INT_STEP ���ԭ INT64��ѹ.)
*/
#define NCH_BEGIN_DCMP_VERSION(pData,nLength,nVersion) {\
	NCH_SAVE_POINT(pData,__nch_dcmp_begin__);\
	int __nch_dcmp_version  = nVersion;\
	int __nch_dcmp_length__ = nLength;


/**
* ��ʼ��ѹ.
* @param pData			Ҫ��ѹ�������ݷ�����ڴ�.
* @param nLength		nLength �ڴ���ܳ���.
*/
#define NCH_BEGIN_DCMP(pData,nLength) NCH_BEGIN_DCMP_VERSION(pData,nLength,0)


/**
* ������ѹ.
* @param pData    ��NCH_BEGIN_DCMP��pData��ͬ.
* @param ndcmpLength	��ԭ�˵ĳ�����.
*/
#define NCH_END_DCMP(pData,ndcmpLength)	ndcmpLength = NCH_CALC_SIZE(pData,__nch_dcmp_begin__);\
	NCH_RESTORE_POINT(pData,__nch_dcmp_begin__);\
	}


#define __NCH_CHECK_DCMP(pData)	(pData - __pSave_nch_point##pData##__nch_dcmp_begin__ < __nch_dcmp_length__ )


/**
* ѹ������������.
*
*/
#define NCH_CMP_BINDATA_STEP(pData,pBin,nBinLen)	pData += CHHNetCompressHelper::NCH_compress_binData((char*)pData,(char*)pBin,(int)nBinLen);

/**
* ��ѹ����������.
*
*/
#define NCH_DCMP_BINDATA_STEP(pData,pBin,nBinLen,nOutLength)	__NCH_CHECK_DCMP(pData)	&& ( pData += CHHNetCompressHelper::NCH_decompress_binData((char*)pData,(char*)pBin,(int)nBinLen,*(&##nOutLength##)));



/**
* ѹ���������ݵ�pData��.
*/
#define NCH_CMP_INT_STEP(pData,nValue)\
	if(__nch_cmp_version == 0)\
	{\
		pData += CHHNetCompressHelper::NCH_compress_int(pData,(int)nValue);\
	}else if(__nch_cmp_version ==1)\
	{\
		pData += CHHNetCompressHelper::NCH_compress_int64(pData,nValue);\
	}
	

/**
* ��ѹ��������.
*/
#define NCH_DCMP_INT_STEP(pData,nValue)\
	if(__NCH_CHECK_DCMP(pData))\
	{\
		if(__nch_dcmp_version==0)\
		{\
			( pData += CHHNetCompressHelper::NCH_decompress_int(pData,*((int*)(&##nValue##))) );\
		}else\
		{\
			__int64 __i64Temp=0;\
			( pData += CHHNetCompressHelper::NCH_decompress_int64(pData,*((__int64*)(&##__i64Temp##))) );\
			nValue = __i64Temp;\
		}\
	}


/**
* ����һ��������Char
*
*/
#define NCH_CMP_CHAR_STEP(pData,nValue) {pData[0]=nValue; pData = ((char*)pData +1); }




#define NCH_DCMP_CHAR_STEP(pData,nValue) __NCH_CHECK_DCMP(pData) && (nValue = *((char*)pData),pData= pData = ((char*)pData +1));

/**
* ѹ��int64���ݵ�pData��.
*/
#define NCH_CMP_INT64_STEP(pData,iValue) pData += CHHNetCompressHelper::NCH_compress_int64(pData,iValue);

/**
* ��ѹ__int64����.
*/
#define NCH_DCMP_INT64_STEP(pData,iValue) 	__NCH_CHECK_DCMP(pData) && ( pData+= CHHNetCompressHelper::NCH_decompress_int64(pData,*(&##iValue##)) );



/**
* ѹ����λС��Double.
*/
#define NCH_CMP_DOUBLE2_STEP(pData,dValue) NCH_CMP_INT64_STEP(pData,((dValue+0.005)*((__int64)100)))

/**
* ��ѹ��λС��Double.
*/
#define NCH_DCMP_DOUBLE2_STEP(pData,dValue)	 if(__NCH_CHECK_DCMP(pData))\
					{\
						__int64 int64_;\
						pData+= CHHNetCompressHelper::NCH_decompress_int64(pData,int64_);\
						*(&##dValue)=(double)int64_/100.0f;\
					}


/**
* ѹ����λС��Double.
*/
#define NCH_CMP_DOUBLE3_STEP(pData,dValue) NCH_CMP_INT64_STEP(pData,(dValue+0.0005)*((__int64)1000) )

/**
* ��ѹ��λС��Double.
*/
#define NCH_DCMP_DOUBLE3_STEP(pData,dValue)	 if(__NCH_CHECK_DCMP(pData))\
					{\
						__int64 int64_;\
						pData+= CHHNetCompressHelper::NCH_decompress_int64(pData,int64_);\
						*(&##dValue)=(double)int64_/1000.0f;\
					}

/**
* ѹ����λС��Double.
*/
#define NCH_CMP_DOUBLE4_STEP(pData,dValue) NCH_CMP_INT64_STEP(pData, (dValue+0.00005)*((__int64)10000) )

/**
* ��ѹ��λС��Double.
*/
#define NCH_DCMP_DOUBLE4_STEP(pData,dValue)	 if(__NCH_CHECK_DCMP(pData))\
					{\
						__int64 int64_;\
						pData+= CHHNetCompressHelper::NCH_decompress_int64(pData,int64_);\
						*(&##dValue)=(double)int64_/10000.0f;\
					}

/**
* ѹ����λС��Double.
*/
#define NCH_CMP_DOUBLE6_STEP(pData,dValue) NCH_CMP_INT64_STEP(pData,(dValue+0.0000005)*((__int64)1000000) )

/**
* ��ѹ��λС��Double.
*/
#define NCH_DCMP_DOUBLE6_STEP(pData,dValue)	 if(__NCH_CHECK_DCMP(pData))\
					{\
						__int64 int64_;\
						pData+= CHHNetCompressHelper::NCH_decompress_int64(pData,int64_);\
						*(&##dValue)=(double)int64_/1000000.0f;\
					}


/**
* ѹ���ַ���.
*/
#define NCH_CMP_STRING_STEP(pData,pString) pData += CHHNetCompressHelper::NCH_compress_string(pData,pString);

/**
*��ѹ�ַ���.
*/
#define NCH_DCMP_STRING_STEP(pData,pOutString,nleng) 	__NCH_CHECK_DCMP(pData) && ( pData += CHHNetCompressHelper::NCH_decompress_string(pData,pOutString,nleng) );


/**
* �Ա�ѹ��֤ȯ����.
*/
#define NCH_CMP_SECCODE_COM_STEP(pData,pSecCode,pCompareCode)  pData+= CHHNetCompressHelper::NCH_compress_securitiesCode8(pData,pSecCode,pCompareCode) ;

/**
* �ԱȽ�ѹ֤ȯ����.
*/
#define NCH_DCMP_SECCODE_COM_STEP(pData,pSecCode,pCompareCode)		__NCH_CHECK_DCMP(pData) && ( pData+= CHHNetCompressHelper::NCH_decompress_securitiesCode8(pData,pSecCode,pCompareCode) );




/**
	<h1>ͨ������ͨ��ѹ��������</h1>

	<font color="ff0000">	
	<h2>���ͨ������ѹ��ԭ��:</h2>
	<li> ѹ���ٶȿ���
	<li> ���ϰ汾�������
	<li> ����չ��
	<li> ר��ѹ������ѹ����
	<li> �ɲ��ü�¼�Ա�ѹ��
	<li> ���ݲ�ͬ����������ʹ�ò�ͬ������ѹ������
	<li> �ṹ��ѹ����ѹ������ѹ�����ȡ˳�򲻱�
	</font>

	<br>
    <li><font color="0000ff">ʾ������<a href=".\cmptest.zip">cmptest.zip</a></font>

	* @see <a href="(HHPfdk__globals).html#NCH_SAVE_POINT(pData,nPos)">NCH_SAVE_POINT</a>
	* @see <a href="(HHPfdk__globals).html#NCH_RESTORE_POINT(pData,nPos)">NCH_RESTORE_POINT</a>

	* @see <a href="(HHPfdk__globals).html#NCH_CMP_INT_STEP(pData,nValue)">NCH_CMP_INT_STEP</a>
	* @see <a href="(HHPfdk__globals).html#NCH_DCMP_INT_STEP(pData,nValue)">NCH_DCMP_INT_STEP</a>

	* @see <a href="(HHPfdk__globals).html#NCH_CMP_INT64_STEP(pData,iValue)">NCH_CMP_INT64_STEP</a>
	* @see <a href="(HHPfdk__globals).html#NCH_DCMP_INT64_STEP(pData,iValue)">NCH_DCMP_INT64_STEP</a>

	* @see <a href="(HHPfdk__globals).html#NCH_CALC_SIZE(pData,nSavePos)">NCH_CALC_SIZE</a>


	* @see <a href="(HHPfdk__globals).html#NCH_CMP_DOUBLE2_STEP(pData,dValue)">NCH_CMP_DOUBLE2_STEP</a>
	* @see <a href="(HHPfdk__globals).html#NCH_DCMP_DOUBLE2_STEP(pData,dValue)">NCH_DCMP_DOUBLE2_STEP</a>

	* @see <a href="(HHPfdk__globals).html#NCH_CMP_DOUBLE3_STEP(pData,dValue)">NCH_CMP_DOUBLE3_STEP</a>
	* @see <a href="(HHPfdk__globals).html#NCH_DCMP_DOUBLE3_STEP(pData,dValue)">NCH_DCMP_DOUBLE3_STEP</a>

	* @see <a href="(HHPfdk__globals).html#NCH_CMP_DOUBLE4_STEP(pData,dValue)">NCH_CMP_DOUBLE4_STEP</a>
	* @see <a href="(HHPfdk__globals).html#NCH_DCMP_DOUBLE4_STEP(pData,dValue)">NCH_DCMP_DOUBLE4_STEP</a>

	* @see <a href="(HHPfdk__globals).html#NCH_CMP_DOUBLE6_STEP(pData,dValue)">NCH_CMP_DOUBLE6_STEP</a>
	* @see <a href="(HHPfdk__globals).html#NCH_DCMP_DOUBLE6_STEP(pData,dValue)">NCH_DCMP_DOUBLE6_STEP</a>

	* @see <a href="(HHPfdk__globals).html#NCH_CMP_STRING_STEP(pData,pString)">NCH_CMP_STRING_STEP</a>
	* @see <a href="(HHPfdk__globals).html#NCH_DCMP_STRING_STEP(pData,pOutString)">NCH_DCMP_STRING_STEP</a>

	* @see <a href="(HHPfdk__globals).html#NCH_CMP_SECCODE_COM_STEP(pData,pSecCode,pCompareCode)">NCH_CMP_SECCODE_COM_STEP</a>
	* @see <a href="(HHPfdk__globals).html#NCH_DCMP_SECCODE_COM_STEP(pData,pSecCode,pCompareCode)">NCH_DCMP_SECCODE_COM_STEP</a>
    
	* @see <a href="(HHPfdk__globals).html#NCH_BEGIN_CMP(pData,nLength)">NCH_BEGIN_CMP</a>
	* @see <a href="(HHPfdk__globals).html#NCH_END_CMP(pData,ncmpLength)">NCH_END_CMP</a>

	* @see <a href="(HHPfdk__globals).html#NCH_BEGIN_DCMP(pData,nLength)">NCH_BEGIN_DCMP</a>
	* @see <a href="(HHPfdk__globals).html#NCH_END_DCMP(pData,ndcmpLength)">NCH_END_DCMP</a>
	
*/

class AFX_EXT_CLASS CHHNetCompressHelper
{

public:

	/**
	* ���������ݽ���ѹ����
	* @param pBuffer ���ڴ��ѹ������������ݡ�
	* @param delta	 Ҫѹ����������.
	* @return ����ѹ���������ռ��pbuffer�ĳ��ȡ�
	* @see  #NCH_decompress_int
	*/
	static int NCH_compress_int(char *pbuffer, int delta);

	/**
	* ��ָ�����ڴ��н�ѹ�� �� NCH_compress_int ѹ������������.
	* @param pbuffer  Ҫ��ѹ���ڴ��ַ��
	* @param delta    ��ѹ�������������ݡ�
	* @return         ���ؽ�ѹ�˵��ֽ�����
	* @see		 #NCH_compress_int
	*/
	static int NCH_decompress_int(char *pbuffer, int &delta);



	/**
	* �� int  �����ݽ���ѹ������ѹ��������Ĳ��ݱ�־����chFlags��.
	* @param chFlags ���ڴ��ѹ����ı�־���ݡ� chFlags�ĵ���λ���õ���λ����ű�־��
	* @param pBuffer ���ڴ��ѹ������������ݡ�
	* @param delta	 Ҫѹ��������.
	* @return ����ѹ���������ռ��pbuffer�ĳ��ȡ�
	* @see  #NCH_decompress_int_2Flags
	*/
	static int NCH_compress_int_2Flags(char &chFlag, char *pbuffer, int delta);


	/**
	* ��ָ�����ڴ��н�ѹ���� {@link #compress_int_2Flags compress_int_2Flags} ѹ�����������ݡ�
	* @param chFlag	  ѹ��������ı�־��
	* @param pbuffer  Ҫ��ѹ���ڴ��ַ��
	* @param delta    ��ѹ�������������ݡ�
	* @return         ���ؽ�ѹ�˵��ֽ�����
	* @see  #NCH_compress_int_2Flags
	*/
	static int NCH_decompress_int_2Flags(char chFlag, char *pbuffer, int &delta);



	/**
	* �� __int64 �����ݽ���ѹ����
	* @param pBuffer ���ڴ��ѹ������������ݡ�
	* @param delta	 Ҫѹ����__int64���ݡ�
	* @return ����ѹ���������ռ��pbuffer�ĳ��ȡ�
	* @see #NCH_decompress_int64
	*/
	static int NCH_compress_int64(char *pbuffer, __int64 idelta);


	/**
	* ��ָ�����ڴ��н�ѹ�� �� {@link #NCH_compress_int64 NCH_compress_int64 }ѹ����__int64 ���ݡ�
	* @param pbuffer  Ҫ��ѹ���ڴ��ַ��
	* @param delta    ��ѹ������__int64���ݡ�
	* @return         ���ؽ�ѹ�˵��ֽ�����
	* @see  #NCH_compress_int64
	*/
	static int NCH_decompress_int64(char *pbuffer, __int64 &idelta);



	/**
	* �� __int64 �����ݽ���ѹ������ѹ��������Ĳ��ֱ�־����chFlags��.
	*
	* @param chFlags ���ڴ��ѹ����ı�־���ݡ� chFlags�ĵ���λ���õ���λ����ű�־��
	* @param pBuffer ���ڴ��ѹ������������ݡ�
	* @param delta	 Ҫѹ����__int64���ݡ�
	* @return ����ѹ���������ռ��pbuffer�ĳ���.
	* @see #NCH_decompress_int64_3Flags
	* @author wli
	*/
	static int NCH_compress_int64_3Flags(char &chFlags, char *pbuffer, __int64 idelta);


	/**
	* ��ָ�����ڴ��н�ѹ�� ��{@link #NCH_compress_int64_3Flags NCH_compress_int64_3Flags} ѹ����__int64 ���ݡ�<br>
	* @param chFlags ѹ��������ı�־��
	* @param pBuffer Ҫ��Ҫ�����ݡ�
	* @param delta	 ��ѹ����__int64���ݡ�	
	* @return 	���ؽ�ѹ�˵��ֽ����ݡ�
	* @see #NCH_compress_int64_3Flags
	*/
	static int NCH_decompress_int64_3Flags(char chFlags, char *pbuffer, __int64 &idelta);


	/**
	* ѹ��ָ�����ַ���
	* @param pbuffer ���ڴ��ѹ��������ݡ�
	* @param pstring ���ڴ��Ҫѹ�����ַ���.
	* @return ѹ����ռ��pbuffer���ֽ���.
	* @see #NCH_decompress_string
	*/
	static int NCH_compress_string(char* pbuffer,LPCTSTR pstring);

	/**
	* ��ѹ�ַ���
	* @param psrcbuffer Ҫ��ѹ���ڴ�.
	* @param pdes       ��ѹ����ִ��Ĵ�ŵ�ַ��
	* @param ndesLeng   pdes�ĳ���.
	* @return ���ؽ�ѹ��psrcbuffer�е��ֽ���.	
	* @see #NCH_compress_string
	*/
	static int NCH_decompress_string(char* psrcbuffer,char* pdes,int ndesLeng);


	/**
	* ѹ������������.
	* @param pbuffer ���ѹ���������.
	* @param pbinData Ҫѹ���Ķ���������.
	* @param nBinLength  ���������ݳ���.
	* @return ����ѹ����pbuffer�����ݳ���.
	* @see #NCH_decompress_binData 
	*/
	static int NCH_compress_binData(char* pbuffer,char* pbinData,int nBinLength);


	/**
	* ��ѹ������������.
	* @param pbuffer ѹ���������.
	* @param pbinData ��ѹ�����ݵĴ�ŵ�ַ��
	* @param nBinLength  pbinData�ĳ���.
	* @param nOutLength  ��ѹ���Ķ��������ݳ���
	* @return ���ؽ�ѹpbuffer�����ݳ���.
	* @see #NCH_compress_binData 
	*/
	static int NCH_decompress_binData(char* pbuffer,char* pbinData,int nBinLength,int& nOutLength);


	/**
	* �Ա�ѹ��֤ȯ���롣�ú���֧�ֵ�֤ȯ����λ��Ϊ8λ,(Ҫ��pCode��pCompare������ͬ���ҳ��Ȳ�����8).
	* @param pCode		Ҫѹ����֤ȯ����.
	* @param pCompare	����ѹ�����ԱȵĴ���.
	* @return  ����ѹ����ռ��pBuffer���ֽ���.
	* @see #NCH_decompress_securitiesCode8
	*/
	static int NCH_compress_securitiesCode8(char* pBuffer,LPCTSTR pCode,LPCTSTR pCompare);

	/**
	* ֤ȯ����ԱȽ�ѹ
	* @param pBuffer	Ҫ��ѹ���ڴ�.
	* @param pCode      ��ѹ��֤ȯ�������pCode.
	* @param pCompare   Ҫ�������ڽ�ѹ��Ʒ��.
	* @return ���ؽ�ѹ��pBuffer���ֽ���.
	* @see #NCH_compress_securitiesCode8
	*/
	static int NCH_decompress_securitiesCode8(char* pBuffer,char* pCode,LPCTSTR pCompare);



protected:	//���������������͵Ķ���
	CHHNetCompressHelper(void);
	virtual ~CHHNetCompressHelper(void);

};
