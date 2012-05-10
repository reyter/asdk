
/**
* @copyright 深圳市创真科技有限公司
* @system    HHPfdk   (Honghui Public Function development kit)
* @brief	   通讯数据常用压缩方法
* @author	 wli
* @histroy
-------------------------------------------------------------
2008-06-05			wli                   修正Double溢出与截断问题。增加 NCH_(D)CMP_CHAR_STEP 宏
-------------------------------------------------------------
*/
#pragma once

#pragma warning(disable:4244)	//从“double”转换到“__int64”，可能丢失数据

/**
* 保存指针.
* @param pData 要保存的指针,通常为(char*).
* @param nPos  保存标记，可以为数字或者字符串.
*/ 
#define NCH_SAVE_POINT(pData,nPos) char* __pSave_nch_point##pData##nPos = (char*)pData;


/**
* 将pData还原到保存位置。
*/
#define NCH_RESTORE_POINT(pData,nPos)	pData = __pSave_nch_point##pData##nPos;

/**
* 计算压缩后数据便移.
*/
#define NCH_CALC_SIZE(pData,nSavePos)	(int)((pData - (char*)(__pSave_nch_point##pData##nSavePos)))


/**
* 开始压缩.
* @param pData 用于存储压缩数据的地址.
* @param nLength  pData的长度.
* @param nVersion       0 NCH_CMP_INT_STEP 原 INT压缩，  ( 1 NCH_CMP_INT_STEP 变成原 INT64压缩.)
*/
#define NCH_BEGIN_CMP_VERSION(pData,nLength,nVersion) {\
	NCH_SAVE_POINT(pData,__nch_cmp_begin__);\
	int __nch_cmp_version  = nVersion;\
	int __nch_cmp_length__ = nLength;


/**
* 开始压缩.
* @param pData 用于存储压缩数据的地址.
* @param nLength  pData的长度.
*/
#define NCH_BEGIN_CMP(pData,nLength) NCH_BEGIN_CMP_VERSION(pData,nLength,0)




/** 
* 结束压缩.
* @param pData 用于存储压缩数据的地址.
* @param ncmpLength 压缩后数据的长度.
*/
#define NCH_END_CMP(pData,ncmpLength)	ncmpLength = NCH_CALC_SIZE(pData,__nch_cmp_begin__);\
	NCH_RESTORE_POINT(pData,__nch_cmp_begin__);\
	}


/**
* 开始解压.
* @param pData			要将压缩后数据放入的内存.
* @param nLength		nLength 内存的总长度.
* @param nVersion       0 NCH_DCMP_INT_STEP 原 INT解压，  ( 1 NCH_DCMP_INT_STEP 变成原 INT64解压.)
*/
#define NCH_BEGIN_DCMP_VERSION(pData,nLength,nVersion) {\
	NCH_SAVE_POINT(pData,__nch_dcmp_begin__);\
	int __nch_dcmp_version  = nVersion;\
	int __nch_dcmp_length__ = nLength;


/**
* 开始解压.
* @param pData			要将压缩后数据放入的内存.
* @param nLength		nLength 内存的总长度.
*/
#define NCH_BEGIN_DCMP(pData,nLength) NCH_BEGIN_DCMP_VERSION(pData,nLength,0)


/**
* 结束解压.
* @param pData    与NCH_BEGIN_DCMP的pData相同.
* @param ndcmpLength	还原了的长度数.
*/
#define NCH_END_DCMP(pData,ndcmpLength)	ndcmpLength = NCH_CALC_SIZE(pData,__nch_dcmp_begin__);\
	NCH_RESTORE_POINT(pData,__nch_dcmp_begin__);\
	}


#define __NCH_CHECK_DCMP(pData)	(pData - __pSave_nch_point##pData##__nch_dcmp_begin__ < __nch_dcmp_length__ )


/**
* 压缩二进制数据.
*
*/
#define NCH_CMP_BINDATA_STEP(pData,pBin,nBinLen)	pData += CHHNetCompressHelper::NCH_compress_binData((char*)pData,(char*)pBin,(int)nBinLen);

/**
* 解压二进制数据.
*
*/
#define NCH_DCMP_BINDATA_STEP(pData,pBin,nBinLen,nOutLength)	__NCH_CHECK_DCMP(pData)	&& ( pData += CHHNetCompressHelper::NCH_decompress_binData((char*)pData,(char*)pBin,(int)nBinLen,*(&##nOutLength##)));



/**
* 压缩整型数据到pData中.
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
* 解压整型数据.
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
* 存入一个单独的Char
*
*/
#define NCH_CMP_CHAR_STEP(pData,nValue) {pData[0]=nValue; pData = ((char*)pData +1); }




#define NCH_DCMP_CHAR_STEP(pData,nValue) __NCH_CHECK_DCMP(pData) && (nValue = *((char*)pData),pData= pData = ((char*)pData +1));

/**
* 压缩int64数据到pData中.
*/
#define NCH_CMP_INT64_STEP(pData,iValue) pData += CHHNetCompressHelper::NCH_compress_int64(pData,iValue);

/**
* 解压__int64数据.
*/
#define NCH_DCMP_INT64_STEP(pData,iValue) 	__NCH_CHECK_DCMP(pData) && ( pData+= CHHNetCompressHelper::NCH_decompress_int64(pData,*(&##iValue##)) );



/**
* 压缩两位小数Double.
*/
#define NCH_CMP_DOUBLE2_STEP(pData,dValue) NCH_CMP_INT64_STEP(pData,((dValue+0.005)*((__int64)100)))

/**
* 解压两位小数Double.
*/
#define NCH_DCMP_DOUBLE2_STEP(pData,dValue)	 if(__NCH_CHECK_DCMP(pData))\
					{\
						__int64 int64_;\
						pData+= CHHNetCompressHelper::NCH_decompress_int64(pData,int64_);\
						*(&##dValue)=(double)int64_/100.0f;\
					}


/**
* 压缩三位小数Double.
*/
#define NCH_CMP_DOUBLE3_STEP(pData,dValue) NCH_CMP_INT64_STEP(pData,(dValue+0.0005)*((__int64)1000) )

/**
* 解压三位小数Double.
*/
#define NCH_DCMP_DOUBLE3_STEP(pData,dValue)	 if(__NCH_CHECK_DCMP(pData))\
					{\
						__int64 int64_;\
						pData+= CHHNetCompressHelper::NCH_decompress_int64(pData,int64_);\
						*(&##dValue)=(double)int64_/1000.0f;\
					}

/**
* 压缩四位小数Double.
*/
#define NCH_CMP_DOUBLE4_STEP(pData,dValue) NCH_CMP_INT64_STEP(pData, (dValue+0.00005)*((__int64)10000) )

/**
* 解压四位小数Double.
*/
#define NCH_DCMP_DOUBLE4_STEP(pData,dValue)	 if(__NCH_CHECK_DCMP(pData))\
					{\
						__int64 int64_;\
						pData+= CHHNetCompressHelper::NCH_decompress_int64(pData,int64_);\
						*(&##dValue)=(double)int64_/10000.0f;\
					}

/**
* 压缩六位小数Double.
*/
#define NCH_CMP_DOUBLE6_STEP(pData,dValue) NCH_CMP_INT64_STEP(pData,(dValue+0.0000005)*((__int64)1000000) )

/**
* 解压六位小数Double.
*/
#define NCH_DCMP_DOUBLE6_STEP(pData,dValue)	 if(__NCH_CHECK_DCMP(pData))\
					{\
						__int64 int64_;\
						pData+= CHHNetCompressHelper::NCH_decompress_int64(pData,int64_);\
						*(&##dValue)=(double)int64_/1000000.0f;\
					}


/**
* 压缩字符串.
*/
#define NCH_CMP_STRING_STEP(pData,pString) pData += CHHNetCompressHelper::NCH_compress_string(pData,pString);

/**
*解压字符串.
*/
#define NCH_DCMP_STRING_STEP(pData,pOutString,nleng) 	__NCH_CHECK_DCMP(pData) && ( pData += CHHNetCompressHelper::NCH_decompress_string(pData,pOutString,nleng) );


/**
* 对比压缩证券代码.
*/
#define NCH_CMP_SECCODE_COM_STEP(pData,pSecCode,pCompareCode)  pData+= CHHNetCompressHelper::NCH_compress_securitiesCode8(pData,pSecCode,pCompareCode) ;

/**
* 对比解压证券代码.
*/
#define NCH_DCMP_SECCODE_COM_STEP(pData,pSecCode,pCompareCode)		__NCH_CHECK_DCMP(pData) && ( pData+= CHHNetCompressHelper::NCH_decompress_securitiesCode8(pData,pSecCode,pCompareCode) );




/**
	<h1>通信数据通用压缩方法类</h1>

	<font color="ff0000">	
	<h2>宏汇通信数据压缩原则:</h2>
	<li> 压缩速度快速
	<li> 新老版本互相兼容
	<li> 可扩展性
	<li> 专用压缩，大压缩比
	<li> 可采用记录对比压缩
	<li> 根据不同的数据类型使用不同的数据压缩函数
	<li> 结构体压缩：压缩，解压缩与读取顺序不变
	</font>

	<br>
    <li><font color="0000ff">示例代码<a href=".\cmptest.zip">cmptest.zip</a></font>

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
	* 对整型数据进行压缩。
	* @param pBuffer 用于存放压缩完成生的数据。
	* @param delta	 要压缩的整形数.
	* @return 返回压缩后的数据占用pbuffer的长度。
	* @see  #NCH_decompress_int
	*/
	static int NCH_compress_int(char *pbuffer, int delta);

	/**
	* 从指定的内存中解压出 以 NCH_compress_int 压缩的整型数据.
	* @param pbuffer  要解压的内存地址。
	* @param delta    解压出来的整型数据。
	* @return         返回解压了的字节数。
	* @see		 #NCH_compress_int
	*/
	static int NCH_decompress_int(char *pbuffer, int &delta);



	/**
	* 对 int  型数据进行压缩。将压缩后产生的部份标志放入chFlags中.
	* @param chFlags 用于存放压缩后的标志数据。 chFlags的低两位将用低两位来存放标志。
	* @param pBuffer 用于存放压缩完成生的数据。
	* @param delta	 要压缩的整数.
	* @return 返回压缩后的数据占用pbuffer的长度。
	* @see  #NCH_decompress_int_2Flags
	*/
	static int NCH_compress_int_2Flags(char &chFlag, char *pbuffer, int delta);


	/**
	* 从指定的内存中解压出以 {@link #compress_int_2Flags compress_int_2Flags} 压缩的整型数据。
	* @param chFlag	  压缩后产生的标志。
	* @param pbuffer  要解压的内存地址。
	* @param delta    解压出来的整型数据。
	* @return         返回解压了的字节数。
	* @see  #NCH_compress_int_2Flags
	*/
	static int NCH_decompress_int_2Flags(char chFlag, char *pbuffer, int &delta);



	/**
	* 对 __int64 型数据进行压缩。
	* @param pBuffer 用于存放压缩完成生的数据。
	* @param delta	 要压缩的__int64数据。
	* @return 返回压缩后的数据占用pbuffer的长度。
	* @see #NCH_decompress_int64
	*/
	static int NCH_compress_int64(char *pbuffer, __int64 idelta);


	/**
	* 从指定的内存中解压出 以 {@link #NCH_compress_int64 NCH_compress_int64 }压缩的__int64 数据。
	* @param pbuffer  要解压的内存地址。
	* @param delta    解压出来的__int64数据。
	* @return         返回解压了的字节数。
	* @see  #NCH_compress_int64
	*/
	static int NCH_decompress_int64(char *pbuffer, __int64 &idelta);



	/**
	* 对 __int64 型数据进行压缩。将压缩后产生的部分标志放入chFlags中.
	*
	* @param chFlags 用于存放压缩后的标志数据。 chFlags的低两位将用低三位来存放标志。
	* @param pBuffer 用于存放压缩完成生的数据。
	* @param delta	 要压缩的__int64数据。
	* @return 返回压缩后的数据占用pbuffer的长度.
	* @see #NCH_decompress_int64_3Flags
	* @author wli
	*/
	static int NCH_compress_int64_3Flags(char &chFlags, char *pbuffer, __int64 idelta);


	/**
	* 从指定的内存中解压出 以{@link #NCH_compress_int64_3Flags NCH_compress_int64_3Flags} 压缩的__int64 数据。<br>
	* @param chFlags 压缩后产生的标志。
	* @param pBuffer 要解要的数据。
	* @param delta	 解压出的__int64数据。	
	* @return 	返回解压了的字节数据。
	* @see #NCH_compress_int64_3Flags
	*/
	static int NCH_decompress_int64_3Flags(char chFlags, char *pbuffer, __int64 &idelta);


	/**
	* 压缩指定的字符串
	* @param pbuffer 用于存放压缩后的数据。
	* @param pstring 用于存放要压缩的字符串.
	* @return 压缩后占用pbuffer的字节数.
	* @see #NCH_decompress_string
	*/
	static int NCH_compress_string(char* pbuffer,LPCTSTR pstring);

	/**
	* 解压字符串
	* @param psrcbuffer 要解压的内存.
	* @param pdes       解压后的字串的存放地址。
	* @param ndesLeng   pdes的长度.
	* @return 返回解压了psrcbuffer中的字节数.	
	* @see #NCH_compress_string
	*/
	static int NCH_decompress_string(char* psrcbuffer,char* pdes,int ndesLeng);


	/**
	* 压缩二进制数据.
	* @param pbuffer 存放压缩后的数据.
	* @param pbinData 要压缩的二进制数据.
	* @param nBinLength  二进制数据长度.
	* @return 返回压缩进pbuffer的数据长度.
	* @see #NCH_decompress_binData 
	*/
	static int NCH_compress_binData(char* pbuffer,char* pbinData,int nBinLength);


	/**
	* 解压缩二进制数据.
	* @param pbuffer 压缩后的数据.
	* @param pbinData 解压出数据的存放地址。
	* @param nBinLength  pbinData的长度.
	* @param nOutLength  解压出的二进制数据长度
	* @return 返回解压pbuffer的数据长度.
	* @see #NCH_compress_binData 
	*/
	static int NCH_decompress_binData(char* pbuffer,char* pbinData,int nBinLength,int& nOutLength);


	/**
	* 对比压缩证券代码。该函数支持的证券代码位数为8位,(要求pCode和pCompare长度相同，且长度不超过8).
	* @param pCode		要压缩的证券代码.
	* @param pCompare	用于压缩而对比的代码.
	* @return  返回压缩后占用pBuffer的字节数.
	* @see #NCH_decompress_securitiesCode8
	*/
	static int NCH_compress_securitiesCode8(char* pBuffer,LPCTSTR pCode,LPCTSTR pCompare);

	/**
	* 证券代码对比解压
	* @param pBuffer	要解压的内存.
	* @param pCode      解压后将证券代码存入pCode.
	* @param pCompare   要参照用于解压的品种.
	* @return 返回解压了pBuffer的字节数.
	* @see #NCH_compress_securitiesCode8
	*/
	static int NCH_decompress_securitiesCode8(char* pBuffer,char* pCode,LPCTSTR pCompare);



protected:	//不允许构建该种类型的对象
	CHHNetCompressHelper(void);
	virtual ~CHHNetCompressHelper(void);

};
