/**
* @copyright �����д���Ƽ����޹�˾
* @system    ����㷨����ƽ̨(ATP)
* @brief	 OpenTD Э��.
* @author	 ��ΰ
* @histroy
-------------------------------------------------------------
����			����         �޸�˵��
2010-6-1		��ΰ		 ����
-------------------------------------------------------------
*/

#pragma once

#ifndef __TDPROTOCOLCOMMON__H__
#define __TDPROTOCOLCOMMON__H__


#include "..\\include\\UTI\\UTIDefine.h"
#include "..\\include\\UTI\\UTIDefine_Sec.h"
#include "..\\include\\UTI\\UTIDefine_Fut.h"




//ȫ��һ�ֽڷ�ʽ����
#pragma pack(push,1)

//��Ϣͷ��־.
#define ATP_MSG_FLAG   (0x0716)



//�㷨��������Ϣ����.
enum    ATP_MSG_TYPE
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////ϵͳ��¼����//////////////////////////////////////////////////////////////////

	/**
	ϵͳ��¼
	*/	
	ATP_MSG_LOGIN = 1,

	/**
	ϵͳ��¼Ӧ��.
	*/ 
	ATP_MSG_LOGIN_ANSWER = 2,
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////�㷨��Ϣ��ѯ����//////////////////////////////////////////////////////////////	


	/**
	��ѯ�㷨������Ϣ��Ϣ
	*/
	ATP_MSG_QUERY_ALGOINFO=10000,

	/**
	��ѯ�㷨������Ϣ��ϢӦ��
	*/ 
	ATP_MSG_QUERY_ALGOINFO_ANSWER=10001,


	/**
	��ѯ�㷨������Ϣ.
	*/ 	
	ATP_MSG_QUERY_ALGO_PARAMETER_INFO = 10002,


	/**
	��ѯ�㷨������ϢӦ��
	*/ 
	ATP_MSG_QUERY_ALGO_PARAMETER_INFO_ANSWER = 10003,


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////֤ȯָ���//////////////////////////////////////////////////////////////////////	
	
	/**
	��ͨ�µ���֤ȯ��
	*/ 	
	ATP_MSG_SEC_MAKE_ORDER = 11000,

	/**
	�µ�Ӧ��
	*/ 	
	ATP_MSG_SEC_MAKE_ORDER_ANSWER = 11001,


	/**
	�ֲֲ�ѯ��֤ȯ��
	*/ 
	ATP_MSG_SEC_QUERYHOLD = 11002,


	/**
	�ֲֲ�ѯӦ��
	*/ 	
	ATP_MSG_SEC_QUERYHOLD_ANSWER = 11003,


	/**
	����ί�м�¼��ѯ��֤ȯ��
	*/ 
	ATP_MSG_SEC_QUERYORDERRECORD = 11004,


	/**
	����ί�м�¼��ѯ��֤ȯ��Ӧ��
	*/
	ATP_MSG_SEC_QUERYORDERRECORD_ANSWER = 11005,


	/**
	�ɳ�����ѯ��֤ȯ��
	*/ 
	ATP_MSG_SEC_QUERYCANCANCEL  =  11006,


	/**
	�ɳ�����ѯ��֤ȯ��Ӧ��
	*/ 
	ATP_MSG_SEC_QUERYCANCANCEL_ANSWER  =  11007,


	/**
	�ʲ���ѯ��֤ȯ��
	*/ 
	ATP_MSG_SEC_QUERYASSETS	 = 11008,


	/**
	�ʲ���ѯ��֤ȯ��Ӧ��
	*/ 
	ATP_MSG_SEC_QUERYASSETS_ANSWER	 = 11009,


	/**
	����ָ��(֤ȯ)
	*/ 	
	ATP_MSG_SEC_CANCELORDER	 =  11010,


	/**
	����ָ��(֤ȯ)Ӧ��
	*/ 	
	ATP_MSG_SEC_CANCELORDER_ANSWER	 =  11011,

	/**
	�ɽ���ѯ(֤ȯ)
	*/ 	
	ATP_MSG_SEC_QUERYMATCH =11012,


	/**
	�ɽ���ѯ(֤ȯ)Ӧ��
	*/ 	
	ATP_MSG_SEC_QUERYMATCH_ANSWER =11013,



	/**
	���ɽ�����(֤ȯ)��ѯ
	*/
	ATP_MSG_SEC_QUERYMAXVOLUME=11014,

	/**
	���ɽ�������ѯӦ��.
	*/ 
	ATP_MSG_SEC_QUERYMAXVOLUME_ANSWER=11015,





	/**
	�㷨�µ���֤ȯ��
	*/ 	
	ATP_MSG_SEC_MAKE_ORDER_BY_ALGO = 12000,

	/**
	�㷨�µ����Ӧ��.
	*/	
	ATP_MSG_SEC_MAKE_ORDER_BY_ALGO_ANSWER = 12001,

	/**
	��ǰ�ʻ��������е��㷨״̬��ѯ
	*/	
	ATP_MSG_SEC_QUERY_CURRENT_ALGO_STATUS = 12002,

	/**
	��ǰ�ʻ��������е��㷨״̬��ѯ--���صĽ��.
	*/ 
	ATP_MSG_SEC_QUERY_CURRENT_ALGO_STATUS_ANSWER = 12003,	
	
	
	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////�ڻ�ָ���//////////////////////////////////////////////////////////////////////	
	
	/**
	��ͨ�µ����ڻ���
	*/ 	
	ATP_MSG_FUT_MAKE_ORDER = 13000,

	/**
	�µ�Ӧ��
	*/ 	
	ATP_MSG_FUT_MAKE_ORDER_ANSWER = 13001,


	/**
	�ֲֲ�ѯ���ڻ���
	*/ 
	ATP_MSG_FUT_QUERYHOLD = 13002,


	/**
	�ֲֲ�ѯӦ��
	*/ 	
	ATP_MSG_FUT_QUERYHOLD_ANSWER = 13003,


	/**
	����ί�м�¼��ѯ���ڻ���
	*/ 
	ATP_MSG_FUT_QUERYORDERRECORD = 13004,


	/**
	����ί�м�¼��ѯ���ڻ���Ӧ��
	*/
	ATP_MSG_FUT_QUERYORDERRECORD_ANSWER = 13005,


	/**
	�ɳ�����ѯ���ڻ���
	*/ 
	ATP_MSG_FUT_QUERYCANCANCEL  =  13006,


	/**
	�ɳ�����ѯ���ڻ���Ӧ��
	*/ 
	ATP_MSG_FUT_QUERYCANCANCEL_ANSWER  =  13007,


	/**
	�ʲ���ѯ���ڻ���
	*/ 
	ATP_MSG_FUT_QUERYASSETS	 = 13008,


	/**
	�ʲ���ѯ���ڻ���Ӧ��
	*/ 
	ATP_MSG_FUT_QUERYASSETS_ANSWER	 = 13009,


	/**
	����ָ��(�ڻ�)
	*/ 	
	ATP_MSG_FUT_CANCELORDER	 =  13010,


	/**
	����ָ��(�ڻ�)Ӧ��
	*/ 	
	ATP_MSG_FUT_CANCELORDER_ANSWER	 =  13011,

	/**
	�ɽ���ѯ(�ڻ�)
	*/ 	
	ATP_MSG_FUT_QUERYMATCH =13012,


	/**
	�ɽ���ѯ(�ڻ�)Ӧ��
	*/ 	
	ATP_MSG_FUT_QUERYMATCH_ANSWER =13013,



	/**
	���ɽ�����(�ڻ�)��ѯ
	*/
	ATP_MSG_FUT_QUERYMAXVOLUME=13014,

	/**
	���ɽ�������ѯӦ��.
	*/ 
	ATP_MSG_FUT_QUERYMAXVOLUME_ANSWER=13015,





	/**
	�㷨�µ����ڻ���
	*/ 	
	ATP_MSG_FUT_MAKE_ORDER_BY_ALGO = 14000,

	/**
	�㷨�µ����Ӧ��.
	*/	
	ATP_MSG_FUT_MAKE_ORDER_BY_ALGO_ANSWER = 14001,

	/**
	��ǰ�ʻ��������е��㷨״̬��ѯ
	*/	
	ATP_MSG_FUT_QUERY_CURRENT_ALGO_STATUS = 14002,

	/**
	��ǰ�ʻ��������е��㷨״̬��ѯ--���صĽ��.
	*/ 
	ATP_MSG_FUT_QUERY_CURRENT_ALGO_STATUS_ANSWER = 14003,	


	
	
	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	ϵͳ��Ϣ
	*/ 	
	ATP_MSG_SYSTEM_MESSAGE = 999999,


	ATP_MSG_END
};


//--------------------------��Ϣͷ------------------------------------------------------/
/**
��Ϣͷ,ÿһ����Ϣ��ǰ�棬�����д���Ϣͷ�����Ӧ����Ϊ ATP_MSG_TYPE. 
@see ATP_MSG_TYPE
*/ 
typedef UTI_MsgHead					ATP_MsgHead;
//-------------------------------------------------------------------------------------/


/**
�㷨���׷�����ϵͳ��Ϣ��
*/
struct ATP_Msg_SystemMessage
{
	/**
	��Ϣ����
	0	��ͨ��Ϣ
	1	������Ϣ
	*/ 	
	int nType;	

	/**
	��Ϣ.
	*/ 	
	char szMsg[128];
};



/**
������Ϣͷ��Ϣ.
*/ 
struct ATP_Msg_Array_Head
{
	/**
	�����ļ�¼��
	*/ 	
	int nItems;

	/**
	������¼��С
	*/ 	
	int nItemSize;
};






/**
�㷨��������
*/
enum ATP_ALGOPARAM_TYPE
{
	/**
	����.
	*/
	AP_TYPE_INT=0,

	/** 
	������.
	*/
	AP_TYPE_DOUBLE=1,

	/**
	INT64.
	*/
	AP_TYPE_INT64,

	/**
	�ַ���.
	*/
	AP_TYPE_STRING,
};



//--------------------------������֧�ֵ��㷨��ѯ--------------------------------------/
/////////////////////// ���� ////////////////////////////////////////////////////////// 

//  ����ʱ������ָ����Ϣ����Ϊ ATP_MSG_QUERY_ALGOINFO

/////////////////////////����///////////////////////////////////////////////////////////

/**
��ѯ�㷨�󷴻ص���Ϣͷ.
����Ϣͷ�󣬽�����Ӧ�� ATP_ALGORITHM_INFO ����.
�����ָ����¼��  ATP_ALGORITHM_INFO ����.
@see ATP_ALGORITHM_INFO
*/ 
typedef ATP_Msg_Array_Head			ATP_Msg_QueryAlgoInfoAnswer_Head;


/**
�㷨��Ϣ.
*/
struct ATP_ALGORITHM_INFO
{
	/**
	�㷨��GUID.
	*/ 	
	GUID guidAlgo;

	/**
	�㷨����.
	*/ 	
	char szAlgoName[32];

	/**
	�㷨������
	*/ 
	char szAlgoDescription[1024];

	/**
	�㷨��������.
	*/
	int nParamInfo;	
};

//---------------------------------------------------------------------------------------/






//--------------------------�㷨�Ĳ�����ϸ��ѯ----------------------------------------/
/////////////////////// ���� ////////////////////////////////////////////////////////// 

/**
��ѯָ���㷨������Ϣ.
*/
struct ATP_Msg_QueryAlgoParamterInfo
{
	/**
	�㷨��GUID.
	*/ 	
	GUID guidAlgo;
};


/////////////////////////����///////////////////////////////////////////////////////////

/**
����ͷ��Ϣ
*/
struct ATP_Msg_QueryAlgoParamterInfo_Answer_Head
{
	/**
	�㷨��GUID.
	*/ 	
	GUID guidAlgo;

	/**
	������Ĳ�����Ϣ����.
	*/ 	
	int  nParamter;

	/**
	��¼��С��ӦΪsizeof( ATP_ALGOPARAM_INFO )
	*/ 
	int  nItemsize;
};


/**
�㷨������ϸ��Ϣ
*/
struct ATP_ALGOPARAM_INFO
{
	/**
	��������.
	*/ 	
	int nType;	

	/**
	������
	*/ 
	char szParamName[64];

	/**
	������Ϣ
	*/ 	
	char szParamDescription[512];

};











//--------------------------�㷨��ʽ�µ�      ----------------------------------------/
/////////////////////// ���� ////////////////////////////////////////////////////////// 

/**
�㷨��ʽ���µ������潫ָ�������� ATP_ALGOPARAM_VALUE �������顣

*/ 
struct ATP_Msg_MakeOrderByAlgo_Head
{
	/**
	�㷨GUID
	*/ 	
	GUID gudiAlgo;

	/**
	��������Item��С��ӦΪ sizeof(ATP_ALGOPARAM_VALUE)
	*/	
	int nParamterItemSize;

	/**
	����ֵ����
	*/ 	
    int  nParamterValue;

};

/**
�㷨����ֵ.
��Ҫ����nType ��ȷ��Data��Ա��ֵ.
@see ATP_ALGOPARAM_TYPE
*/ 
struct ATP_Msg_MakeOrderByAlgo_ParamValue
{
	int nType;
	union {
		int			iVal;		
		double		dVal;
		INT64		i64Val;
		char		chVal[256];		
	}data;
};

/////////////////////////����///////////////////////////////////////////////////////////

struct ATP_Msg_MakeOrderByAlgo_Answer
{
	/**
	0��ʾ�ɹ�������ֵ��ʾʧ�ܣ�
	*/ 	
	INT  nResult;			

	/**
	����ʱ���ӵ���Ϣ
	*/
	char szInfo[128];	
};

//--------------------------------------------------------------------------------------/

typedef    ATP_Msg_MakeOrderByAlgo_Head    ATP_Msg_Sec_MakeOrderByAlgo_Head;
typedef    ATP_Msg_MakeOrderByAlgo_Head    ATP_Msg_Fut_MakeOrderByAlgo_Head;
typedef   ATP_Msg_MakeOrderByAlgo_ParamValue  	ATP_ALGOPARAM_VALUE;
typedef   ATP_Msg_MakeOrderByAlgo_ParamValue 	 ATP_Msg_Sec_MakeOrderByAlgo_ParamValue;
typedef   ATP_Msg_MakeOrderByAlgo_ParamValue  	ATP_Msg_Fut_MakeOrderByAlgo_ParamValue;
typedef   ATP_Msg_MakeOrderByAlgo_Answer       ATP_Msg_Sec_MakeOrderByAlgo_Answer;
typedef   ATP_Msg_MakeOrderByAlgo_Answer       ATP_Msg_Fut_MakeOrderByAlgo_Answer;




//-------------------------���ʺŵ�ǰ�������е��㷨��ѯ---------------------------------/
/////////////////////// ���� ////////////////////////////////////////////////////////////
//ֻ�������Ϣ����

/////////////////////////����///////////////////////////////////////////////////////////

/**
��Ϣͷ��Ϣ.
*/
typedef ATP_Msg_Array_Head			ATP_Msg_CurrentAlgoStatus_Head;

struct ATP_Msg_CurrentAlgoStatus{
		/**
		�㷨����
		*/
		char szName[64];				

		/**
		��ʼʱ��,��ʽ, HHMMSSmmm
		*/
		UINT nBeginTime;				

		/**
		�µ�����
		*/ 
		UINT nMakeOrderTimes;
		
		/**
		�������.
		*/		
		UINT nFinish;

		/**
		����
		*/ 
		UINT nTotal;

		/**
		״̬˵��
		*/
        char szStatus[64];				
};

//--------------------------------------------------------------------------------------/

typedef ATP_Msg_CurrentAlgoStatus_Head ATP_Msg_Sec_CurrentAlgoStatus_Head;
typedef ATP_Msg_CurrentAlgoStatus_Head ATP_Msg_Fut_CurrentAlgoStatus_Head;
typedef ATP_Msg_CurrentAlgoStatus ATP_Msg_Sec_CurrentAlgoStatus;
typedef ATP_Msg_CurrentAlgoStatus ATP_Msg_Fut_CurrentAlgoStatus;




//---------------------------------------------------------------------------------------/


#pragma pack(pop)

#endif	//TDPROTOCOLCOMMON

