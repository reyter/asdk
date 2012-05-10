/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 OpenTD 协议.
* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			作者         修改说明
2010-6-1		李伟		 创建
-------------------------------------------------------------
*/
#pragma once

#ifndef __OPENTDPROTOCOL__H__
#define __OPENTDPROTOCOL__H__

#pragma pack(push,1)

#include "TDProtocolCommon.h"						//通用协议部分
#include "TDSECProtocol.h"							//证券交易协议
#include "TDFUTProtocol.h"							//期货交易协议

//#include "TDPushProtocol_Sec.h"	
//#include "TDPushProtocol_Fut.h"



#pragma pack(pop)

#endif //__OPENTDPROTOCOL__H__