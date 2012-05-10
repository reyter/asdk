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


#include "..\\UTIAPI\\UTIDefine.h"
#include "..\\UTIAPI\\UTIDefine_Sec.h"
#include "..\\UTIAPI\\UTIDefine_Fut.h"




//ȫ��һ�ֽڷ�ʽ����
#pragma pack(push,1)

//��Ϣͷ��־.
#define ATP_MSG_MAGICNUMBER   (0x2010)


//�㷨��������Ϣ����.
enum    ATP_MSG_TYPE
{

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	ϵͳ��Ϣ
	*/ 	
	ATP_MSG_SYSTEM_MESSAGE = 0,


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


	/**
	* ���õ�ַ��Ϣ.
	*/ 
	ATP_MSG_SET_ADDR_INFO=3,

	
	/**
	* ���������Ͷ�̬����
	* һ��¼����������ᷢ��̬����˿��������㷨���׷�����3DES��¼��ͬʱ����¼��Ϣͷ��nCryptCompressMethod�ĸ�λ������Ϊ2.
	*/
	ATP_MSG_SET_DYNAMIC_PASSWORD=4,


	

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
	//��ǰ�ʻ��������е��㷨״̬��ѯ
	*/	
	ATP_MSG_SEC_QUERY_CURRENT_ALGO_STATUS = 12002,

	/**
	��ǰ�ʻ��������е��㷨״̬��ѯ--���صĽ��.
	*/ 
	ATP_MSG_SEC_QUERY_CURRENT_ALGO_STATUS_ANSWER = 12003,	

	
	
	/**
	* ָʾ�㷨���
	*/
	ATP_MSG_SEC_ALGO_FINISH	= 12004,
	
	

	/**
	* ��ֹ�������е��㷨.
	*/
	ATP_MSG_SEC_KILL_ALGO  = 12005,

	/**
	 *	�㷨������־��ʷ����
	 */
	ATP_MSG_SEC_ALGO_TODAY_LOGHISTORY_QUERY = 12006,

	 /**
	 *	�㷨������־��ʷ��Ӧ
	 */

	 ATP_MSG_SEC_ALGO_TODAY_LOGHISTORY_ANSWER = 12007,

	 /**
	 *	�㷨��־��ʷ����
	 */
	 ATP_MSG_SEC_ALGO_LOGHISTORY_QUERY = 12008,

	 /**
	 *	�㷨��־��ʷ��Ӧ
	 */
	 ATP_MSG_SEC_ALGO_LOGHISTORY_ANSWER = 12009,

	 /*
	*	������־
	*/
	ATP_MSG_SEC_PUSH_ALGO_LOG = 12010,

	/*
	 *	��־�������
	 */
	 ATP_MSG_SEC_ALGO_LOGCATEGORY_QUERY = 12011,

	 /*
	  *	��־����Ӧ
	  */
	 ATP_MSG_SEC_ALGO_LOGCATEGORY_ANSWER = 12012,

	 /*
	  *	������־����
	  */
	 ATP_MSG_SEC_SUBSCRIBE_ALOGLOG_QUERY = 12013,

	 /*
	  *	������־��Ӧ
	  */
	ATP_MSG_SEC_SUBSCRIBE_ALOGLOG_ANSWER = 12014, 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///�ϴ��ļ����ͷ����ϴ��ļ����Ա����.

	/**
	* �ϴ��ļ�
	* 
	*/
	ATP_MSG_UPLOAD_FILE  =  12901,
	

	/**
	* �ϴ��ļ����
	*/
	ATP_MSG_UPLOAD_FILE_RESULT = 12902,




	
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
	* �����ڻ����㵥.
	*/
	ATP_MSG_FUT_PUSH_SETTLEMENT = 13016,

	/**
	* ȷ���ڻ����㵥
	*/
	ATP_MSG_FUT_CONFIRMSETTLEMENT = 13017,




	/**
	�㷨�µ����ڻ���
	*/ 	
	ATP_MSG_FUT_MAKE_ORDER_BY_ALGO = 14000,

//////////////////////////////////////////////////////////////////////////////////////////

	/**
	* �㷨�µ����Ӧ��.
	*/	
	ATP_MSG_FUT_MAKE_ORDER_BY_ALGO_ANSWER = 14001,

	/**
	* ��ǰ�ʻ��������е��㷨״̬��ѯ
	*/	
	ATP_MSG_FUT_QUERY_CURRENT_ALGO_STATUS = 14002,

	/**
	��ǰ�ʻ��������е��㷨״̬��ѯ--���صĽ��.
	*/ 
	ATP_MSG_FUT_QUERY_CURRENT_ALGO_STATUS_ANSWER = 14003,	


	/**
	* ָʾ�㷨���
	*/
	ATP_MSG_FUT_ALGO_FINISH	= 14004,


	/**
	* ��ֹ�������е��㷨.
	*/
	ATP_MSG_FUT_KILL_ALGO  = 14005,
	

    


	ATP_MSG_END
};




#define TTD_HH_COMPRESS_METHOD		0x01  //���ѹ����ʽ

//--------------------------��Ϣͷ------------------------------------------------------/
/**
��Ϣͷ,ÿһ����Ϣ��ǰ�棬�����д���Ϣͷ�����Ӧ����Ϊ ATP_MSG_TYPE. 
@see ATP_MSG_TYPE
*/ 
//���ݰ�ʶ��ͷ
struct ATP_MsgHead
{
	USHORT                nMagicNum; //ħ������  ATP_MSG_MAGICNUMBER

	/**
	*					  ������������ nMagicNum �� nCRC �� ��CRC����ֵ.
	*/
	int					  nCRC;

	/**
	*   ����Ϣͷ����
	*/
	USHORT                nHeadLen;

	/**
	*	���ݳ��ȣ�������ʶ��ͷ��
	*/
	UINT32				  nDataLen;

	/**
	*	ʹ�õ�Э��汾��,��ǰ�汾Ϊ 1  
	*/
	USHORT  			  sVersion;

	/**
	*	����ѹ����ʽ,��ѹ���ټ���.(�Ƚ����ٽ�ѹ)
	*	LOBYTE        ѹ������  0����ѹ��, 1�����ѹ�� 
	*       HIBYTE        ���ܷ���. 0���޼��ܡ�1��3DES�̶�����,2��3DES ��̬����, 4�������㷨
	*/
	USHORT				  nCryptCompressMethod;

	/**
	* ��������
	*/
	USHORT  			  sDataType;

	/**
	* ��������ʱ�������ȷ������,��ʽHHMMSSmmm��
	*/
	UINT				  nTime;

	/**
	* �����ţ�����ǻ�Ӧ�ͻ��˵�����
	* ��ñ��Ϊ�ͻ��˷������������š�
	* ���������͵ķ�Ӧ�����������ź�Ϊ0xFFFFFFFF
	*/
	UINT                  nReqOrder;

	/**
	32�ֽ� ��ˮ�ţ�����������̫��ʱ��Ч��ÿ������˳����룩
	*/
	int     			  nOrder;
	
};
//-------------------------------------------------------------------------------------/



typedef UTI_LoginRequest  ATP_Msg_Login;	//��¼����.

typedef UTI_LoginAnswer   ATP_Msg_Login_Answer;	//��¼Ӧ��.



/**
* ��ַ��Ϣ
*/
struct ATP_Msg_Addr_Info
{
	/**
	* IPV4��ַ,IPv6�ݲ����ǣ��Ժ�����
	*/
	char szIP[16];			
	
	/**
	* mac ��ַ.
	*/
	char szMAC[18];
};

/**
* ��̬����
*/
struct ATP_Msg_Dynamic_Password
{
	char szDynPassword[24];
};




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
	AP_TYPE_INT64=2,

	/**
	�ַ���.
	*/
	AP_TYPE_STRING=3,

	/**
	* ����
	*/
	AP_TYPE_DATE=4,

	/**
	* ʱ��
	*/
	AP_TYPE_TIME=5,
    
	/**
	* �б�
	*/
	AP_TYPE_LIST=6

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
struct Atp_Algorithm_Info
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
�㷨����ֵ.
��Ҫ����nType ��ȷ��Data��Ա��ֵ.
@see ATP_ALGOPARAM_TYPE
*/ 
struct ATP_Msg_MakeOrderByAlgo_ParamValue
{
	ATP_ALGOPARAM_TYPE  nType;			//ATP_ALGOPARAM_TYPE
	union {
		int			iVal;				//AP_TYPE_LIST index.
		double		dVal;
		INT64		i64Val;
		char		chVal[64];			//AP_TYPE_STRING
	}data;
};



/**
* �㷨������ϸ��Ϣ
* �䳤.
*/
struct Atp_Algoparam_Info
{
	/**
	* �������ݳ���	
	*/ 
	int		nExtraDataLength;	

	/**
	��������.
	*/ 	
	ATP_ALGOPARAM_TYPE  nType;	

	/**
	������
	*/ 
	char     szParamName[64];
	
	/**
	������Ϣ
	*/ 	
	char	szParamDescription[512];

	//Ĭ��ֵ.
	ATP_Msg_MakeOrderByAlgo_ParamValue defaultValue;	

	/**
	* ��������
	*/	
	BYTE    *pExtraData;

	////////////////////helper functions/////////
	
	Atp_Algoparam_Info()
	{
		memset(this,0,sizeof(*this));
	}
	Atp_Algoparam_Info(const Atp_Algoparam_Info& other)
	{
		memset(this,0,sizeof(*this));
		*this = other;
	}
	~Atp_Algoparam_Info()
	{
		if(pExtraData && nExtraDataLength>0)
			delete []pExtraData;
	}
	void SetExtraData(BYTE* pData,int nLength)
	{
		if(pExtraData && nExtraDataLength>0)
		{			
			delete []pExtraData;
			pExtraData  = NULL;
		}
		nExtraDataLength = nLength; 
		if(pData && nLength>0)
		{
			pExtraData = new BYTE[nLength+1];
			memset(pExtraData,0,nLength+1);
			memcpy(pExtraData,pData,nLength);
		}
	}
	int FromByte(const char* pData,int nDataLen)
	{
		if(pExtraData && nExtraDataLength>0)
		{			
			delete []pExtraData;
			pExtraData  = NULL;

		}
		memset(this,0,sizeof(*this));	//�����.
		
		//�Ӻ�㴫��Ķ��������ϻָ�.
		//�������η�һ�����ٴ������ݡ�
		int* pItemLen = (int*)pData;
		pData += sizeof(int);
		memcpy(this,pData,offsetof(Atp_Algoparam_Info,pExtraData));
		pExtraData = new BYTE[nExtraDataLength+1];
		pExtraData[nExtraDataLength] = 0;
		memcpy(pExtraData,pData+offsetof(Atp_Algoparam_Info,pExtraData),nExtraDataLength);
		return *pItemLen + sizeof(int);
	}
	Atp_Algoparam_Info& operator=(const Atp_Algoparam_Info& other)
	{
		memcpy(this,&other,offsetof(Atp_Algoparam_Info,pExtraData));	
		SetExtraData(other.pExtraData,other.nExtraDataLength);
		return *this;
	}	
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
		* ��ʶ����
		*/
		INT64	nIdentity;

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
       	char szStatus[256];				
};

//--------------------------------------------------------------------------------------/

typedef ATP_Msg_CurrentAlgoStatus_Head ATP_Msg_Sec_CurrentAlgoStatus_Head;
typedef ATP_Msg_CurrentAlgoStatus_Head ATP_Msg_Fut_CurrentAlgoStatus_Head;
typedef ATP_Msg_CurrentAlgoStatus ATP_Msg_Sec_CurrentAlgoStatus;
typedef ATP_Msg_CurrentAlgoStatus ATP_Msg_Fut_CurrentAlgoStatus;




//---------------------------------------------------------------------------------------/



/**
* �㷨��ɽ����
*/ 
struct ATP_Msg_AlgoFinish
{
	/**
	* ��ʶ����
	*/
	INT64	nIdentity;

	/**
	* �˳�����.
	*/
	int         nRetCode;


	/**
	* �˳���Ϣ.
	*/
	char        szMsg[256];

};



/**
* ������ɱ��ָʾ���㷨.
*/
struct ATP_Msg_Run_Algo_Info
{
	/**
	* ��ʶ����
	*/
	INT64	nIdentity;
};


typedef ATP_Msg_AlgoFinish ATP_Msg_SEC_AlgoFinish;
typedef ATP_Msg_AlgoFinish ATP_Msg_Fut_AlgoFinish;

typedef ATP_Msg_Run_Algo_Info ATP_Msg_SEC_Run_Algo_Info;
typedef ATP_Msg_Run_Algo_Info ATP_Msg_FUT_Run_Algo_Info;


/**
�㷨���׷������ϴ��ļ����
*/
struct ATP_Msg_UploadFileResult
{
	/**
	��Ϣ����
	0	�ϴ��ļ��ɹ�
	������������
	*/ 	
	int nType;	

	/**
	*��Ϣ.
	*/ 	
	char szResultMsg[128];
};

/**
 *	������־�ṹ
 *
 */
#define PER_LOG_MAX_LENGTH 256
struct ATP_Msg_AlgoLog
{
	int nId;							//�Զ����
	INT64 iSrcIdentity;					//��Դ�ı�ʾ ���㷨�ı�ʶ
	int nType;							//����
	int nCategory;						//���
	int nGrade;							//����
	int nTime;							//ʱ��
	int nDataLen;						//���ݳ���
	char *pData;						//����
	
	ATP_Msg_AlgoLog()
	{
		nId = 0;
		nType = 0;
		nCategory = 0;
		nGrade = 0;
		nTime = 0;
		nDataLen = 0;
		pData = 0;
	}

	~ATP_Msg_AlgoLog()
	{
		if (pData)
		{
			delete []pData;
		}
	}
};

/**
 *	��־���ṹ
 *
 */
struct ATP_Msg_Algo_LogCategory
{
	int nCate;					//���
	char szDescription[16];		//���˵��
};

/**
 *	��־����ͷ�ṹ
 *
 */
struct ATP_Msg_Algo_LogSubscribe_Head
{
	GUID guidAlgo;
	ATP_Msg_Array_Head arrHead;
};

/**
 *	��־���Ľṹ
 *
 */
struct ATP_Msg_Algo_LogSubscribe
{
	int nCate;		//���
};

/**
 *	��־���Ľṹ
 *
 */
struct ATP_Msg_Algo_LogSubscribe_Result
{
	int nResult;		//���ؽ�� 0��ʾ�ɹ�������ʾʧ��
};


#pragma pack(pop)

#endif	//TDPROTOCOLCOMMON

