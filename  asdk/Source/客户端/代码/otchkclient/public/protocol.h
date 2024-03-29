
#ifndef __PROTOCOL_QUOTE_H__
#define __PROTOCOL_QUOTE_H__
#include "windows.h"
/** @brief   通讯包头
*  @ingroup 
*  
*/
static unsigned short	reverse_s(unsigned short	usData)
{
	return	(usData>>8)+((usData & 0xff)<<8);
}

static unsigned int	reverse_i(unsigned int	uiData)
{
	unsigned char	aucData[4];

	int i;
	for( i=0;i<4;i++)
		aucData[i]=uiData>>((3-i)*8);
	uiData=0;

	for(i=0;i<4;i++)
		uiData+=(aucData[i]<<(i*8));
	return	uiData;
}

struct CommxHead
{
	typedef unsigned char CommxProp;		/**< 重定义通讯包属性 */
	typedef unsigned char CommxFeed;		/**< 重定义通讯包路由目标 */

	CommxProp Prop;						/**< 通讯包属性 */
	CommxFeed Feed;						/**< 通讯包路由目标 */
	unsigned short SerialNo;			/**< 业务包序列号，原来原去 */
	unsigned long Length;				/**< 业务包长度，不包括#CommxHead包头 */

	enum BYTE_ORDER {HOSTORDER = 0, NETORDER};		/**< 枚举字节序 */
	enum ENCODING {ANSI = 0, UTF16LE, UTF8};		/**< 枚举编码方式 */

	/** @brief      生成通讯包属性
	*
	*  11110000 | 00001110 | 00000001
	*  @param      ver，通讯包版本号
	*  @param      encoding，业务包编码方式（0表示ANSI字符集）
	*  @param      byteorder，业务包字节序（网络字节序，主机字节序）
	*  @retval     CommxProp，通讯包属性
	*  @warning    
	*  @see        
	*  @ingroup    
	*  @exception  
	*/
	static CommxProp MakeProp(unsigned char ver, ENCODING encoding, BYTE_ORDER byteorder)
	{
		return (ver << 4) | ((encoding << 2) & 0x0e) | (byteorder & 0x01);
	}

	/** @brief      获得版本号
	*
	*  11110000
	*  @retval     unsigned char，版本号
	*  @warning    
	*  @see        
	*  @ingroup    
	*  @exception  
	*/
	unsigned char GetVersion()
	{
		return ((Prop & 0xf0)>>4);
	}

	/** @brief      获得业务包编码方式
	*
	*  00001110
	*  @retval     ENCODING，编码方式
	*  @warning    
	*  @see        
	*  @ingroup    
	*  @exception  
	*/
	ENCODING GetEncoding()
	{
		return (ENCODING)((Prop & 0x0e)>>2);
	}

	/** @brief      获得业务包字节序
	*
	*  00000001
	*  @retval     BYTE_ORDER，字节序
	*  @warning    
	*  @see        
	*  @ingroup    
	*  @exception  
	*/
	BYTE_ORDER GetByteorder()
	{
		return (BYTE_ORDER)(Prop & 0x01);
	}
	unsigned long SetLength(unsigned long c_un)
	{
		Length = c_un;
		if (GetByteorder() == NETORDER)
		{
			Length = reverse_i(Length);
		}
		return Length;
	}

	unsigned long GetLength()
	{
		if (GetByteorder() == NETORDER)
		{
			unsigned long nRet = Length;
			return reverse_i(nRet);
		}
		return Length;
	}

	unsigned short GetUS(unsigned short c_us)
	{
		if (GetByteorder() == NETORDER)
		{
			unsigned short us = c_us;
			return reverse_s(us);
		}
		return c_us;
	}

	unsigned long GetUI(unsigned long c_un)
	{
		if (GetByteorder() == NETORDER)
		{
			unsigned long nRet = c_un;
			return reverse_i(nRet);
		}
		return c_un;
	}

	//返回源的有效长度
	int GetStr(char * c_pSrc,int c_nSrcLen,char * c_pDes,int c_nDataLen)
	{
		int nValidLen;
		if (GetEncoding() == ANSI)
		{
			nValidLen = strlen(c_pSrc);
			if (nValidLen > c_nSrcLen)
				nValidLen = c_nSrcLen;
			strncpy(c_pDes,c_pSrc,nValidLen);
			return nValidLen;//直接取长度
		}
		return -1;
	}

	//返回目标有效长度
	int PutStr(char * c_pSrc,char * c_pDes,int c_nDataLen)
	{
		if (GetEncoding() == ANSI)
		{
			memset(c_pDes,0,c_nDataLen);
			strncpy(c_pDes,c_pSrc,c_nDataLen);
			return strlen(c_pDes)>c_nDataLen?c_nDataLen:strlen(c_pDes);
		}
		return -1;
	}

	bool IsValid()
	{
		if (GetVersion() != 0x03)
		{
			return false;
		}
		if (GetByteorder() != NETORDER && GetByteorder() != HOSTORDER)
		{
			return false;
		}
		if (GetEncoding() != ANSI && GetEncoding() != UTF8 && GetEncoding() != UTF16LE)
		{
			return false;
		}
		if (GetLength() < 6)
		{
			return false;
		}
		return true;
	}
};

struct SPackageHead
{
	CommxHead		head;	//头
	unsigned short	usMainFunc;//主要功能号，服务端据此域进行分配处理模块
	unsigned short  usFuncCount;//本包含有功能数
};

struct SFunc
{
	unsigned short usFunc;//功能号
	char			data;//数据
};

#pragma pack()

#endif
