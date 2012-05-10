/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 UTI ����ӿ�.

�����㷨�ӿ�.
�㷨����(ע���㷨����ѯ�㷨��Ϣ������)			 

* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			 ����         �޸�˵��
2010-10-26	 ��ΰ		 ����
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
		* ��������ʹ�õ�ͨ������.
		*/
		typedef void* HENGUTI;


		/**
		*	����ͨ�þ��ԭ��.
		*	
		*/ 
		typedef HENGUTI (CALLBACK* ENGUTI_CREATE_HANDLER_FUN());
		

		/**
		* ���پ��ԭ��.
		* 
		*/
		typedef void (CALLBACK* ENGUTI_DESTROY_HANDLER_FUN(HENGUTI /*hEngUTI*/));



        


		/**
		*	ע��UTI������.
		*   @param nServiceType ��������.
		*/
		ENG_UTI_RegisterUTIService(
			int nServiceType
		
			);







#ifdef __cplusplus
}
#endif
