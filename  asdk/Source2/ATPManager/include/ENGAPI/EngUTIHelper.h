/**
* @copyright 深圳市创真科技有限公司
* @system    宏汇算法交易平台(ATP)
* @brief	 UTI 引擎接口.

定义算法接口.
算法管理(注册算法、查询算法信息及参数)			 

* @author	 李伟
* @histroy
-------------------------------------------------------------
日期			 作者         修改说明
2010-10-26	 李伟		 创建
-------------------------------------------------------------
*/


#pragma once 

#ifdef _ENGAPILIB
#define ENGAPI(type)  type __declspec(dllexport) 
#else
#define ENGAPI(type)  type __declspec(dllimport) 
#endif

#ifdef __cplusplus
extern "C"
{
#endif
		
		/**
		* 定义引擎使用的通用类型.
		*/
		typedef void* HENGUTI;


		/**
		*	创建通用句柄原型.
		*	
		*/ 
		typedef HENGUTI (CALLBACK* ENGUTI_CREATE_HANDLER_FUN());
		

		/**
		* 销毁句柄原型.
		* 
		*/
		typedef void (CALLBACK* ENGUTI_DESTROY_HANDLER_FUN(HENGUTI /*hEngUTI*/));



        


		/**
		*	注册UTI服务类.
		*   @param nServiceType 服务类型.
		*/
		ENG_UTI_RegisterUTIService(
			int nServiceType
		
			);







#ifdef __cplusplus
}
#endif
